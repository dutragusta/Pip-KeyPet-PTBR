#!/usr/bin/env sh
set -eu
ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)"
MUSE="$ROOT/vendor/muse-gadget-sdk/esp32"
PIP="$ROOT/vendor/pip-keypet/ui"
[ -f "$PIP/face.c" ] || { echo "Pip-KeyPet submodule não encontrado." >&2; exit 1; }
[ -f "$MUSE/components/muse/CMakeLists.txt" ] || { echo "Muse Gadget SDK submodule não encontrado." >&2; exit 1; }
mkdir -p "$MUSE/components/muse/avatar"
cp "$ROOT/firmware/muse-overlay/muse_pixel.c" "$MUSE/components/muse/avatar/muse_pixel.c"
python3 - "$ROOT" "$MUSE" <<'PY'
from pathlib import Path
import sys
root, muse = map(Path, sys.argv[1:])
def replace_once(path, old, new):
    text = path.read_text()
    if new in text: return
    if old not in text: raise SystemExit(f"Trecho esperado não encontrado em {path}")
    path.write_text(text.replace(old, new, 1))
replace_once(muse / "CMakeLists.txt",
    'include("${CMAKE_CURRENT_LIST_DIR}/cmake/project.cmake")',
    'set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../../firmware/components/pip_personality")\n'
    'include("${CMAKE_CURRENT_LIST_DIR}/cmake/project.cmake")')
replace_once(muse / "main" / "CMakeLists.txt",
    '    muse\n    # WebAssembly apps',
    '    muse\n    pip_personality\n    # WebAssembly apps')
replace_once(muse / "components" / "muse" / "CMakeLists.txt",
    '    PRIV_REQUIRES ${muse_priv_requires}\n)\n',
    '    PRIV_REQUIRES ${muse_priv_requires}\n)\n\n'
    'if(custom_avatar)\n'
    '    set(PIP_UI_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../../../vendor/pip-keypet/ui")\n'
    '    target_sources(${COMPONENT_LIB} PRIVATE "${PIP_UI_DIR}/face.c"\n'
    '        "${CMAKE_CURRENT_LIST_DIR}/../../../../../firmware/muse-overlay/pip_muse_bridge.c")\n'
    '    target_include_directories(${COMPONENT_LIB} PRIVATE "${PIP_UI_DIR}"\n'
    '        "${CMAKE_CURRENT_LIST_DIR}/../../../../../firmware/muse-overlay"\n'
    '        "${CMAKE_CURRENT_LIST_DIR}/../../../../../firmware/components/pip_personality/include")\n'
    '    set_source_files_properties("${PIP_UI_DIR}/face.c" PROPERTIES\n'
    '        COMPILE_OPTIONS "-fno-math-errno;-O2")\n'
    'endif()\n')
header = muse / "components" / "muse" / "muse_pixel.h"
replace_once(header, "#define MUSE_PX_W 64", "#define MUSE_PX_W 128")
replace_once(header, "#define MUSE_PX_H 64", "#define MUSE_PX_H 128")
state = muse / "components" / "muse" / "muse_state.c"
replace_once(state, '#include "muse_state.h"\n', '#include "muse_state.h"\n#include "pip_muse_bridge.h"\n')
replace_once(state, '    s_last_poke_us = now;\n', '    s_last_poke_us = now;\n    pip_muse_bridge_init();\n')
replace_once(state, '    s_mode = mode;\n', '    s_mode = mode;\n    pip_muse_bridge_on_mode(mode);\n')
replace_once(state, 'muse_mode_t muse_state_mode(float *secs_in_mode)\n{\n', 'muse_mode_t muse_state_mode(float *secs_in_mode)\n{\n    pip_muse_bridge_tick();\n')
ui = muse / "components" / "muse" / "muse_ui.c"
replace_once(ui, '#include "muse_state.h"\n', '#include "muse_state.h"\n#include "pip_muse_bridge.h"\n')
replace_once(ui, '        muse_state_make_happy();\n', '        muse_state_make_happy();\n        pip_muse_bridge_on_touch();\n')
print("Overlay Muse + Pip aplicado (voz + toque + personalidade).")
PY
