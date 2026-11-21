# Reuse the original portable Tamagotchi simulation from the pinned submodule.
# No Pip firmware entry point or hardware driver is compiled into Muse.
get_filename_component(PIP_UI_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../vendor/pip-keypet/ui" ABSOLUTE)

if(NOT EXISTS "${PIP_UI_DIR}/pet.c" OR NOT EXISTS "${PIP_UI_DIR}/pet.h" OR NOT EXISTS "${PIP_UI_DIR}/moods.h")
    message(FATAL_ERROR "Pip-KeyPet submodule is missing. Initialize git submodules before configuring the firmware.")
endif()

idf_component_register(
    SRCS "pip_personality.c" "${PIP_UI_DIR}/pet.c"
    INCLUDE_DIRS "include" "${PIP_UI_DIR}"
)
