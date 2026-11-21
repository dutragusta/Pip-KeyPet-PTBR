# Reuse the Pip pet simulation without copying or forking its upstream source.
# The upstream repository is pinned as vendor/pip-keypet via .gitmodules.
get_filename_component(PIP_UI_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../vendor/pip-keypet/ui" ABSOLUTE)

idf_component_register(
    SRCS
        "pip_personality.c"
        "${PIP_UI_DIR}/pet.c"
    INCLUDE_DIRS
        "include"
        "${PIP_UI_DIR}"
)
