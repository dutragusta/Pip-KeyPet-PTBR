#!/usr/bin/env sh
set -eu
ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)"
OUT="${TMPDIR:-/tmp}/pip-personality-test"
cc -std=c11 -Wall -Wextra \
  -I"$ROOT/vendor/pip-keypet/ui" \
  -I"$ROOT/firmware/components/pip_personality/include" \
  "$ROOT/tests/personality/test_personality.c" \
  "$ROOT/firmware/components/pip_personality/pip_personality.c" \
  "$ROOT/vendor/pip-keypet/ui/pet.c" \
  -lm -o "$OUT"
"$OUT"
