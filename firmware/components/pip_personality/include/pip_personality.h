#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "pet.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Thin application-facing owner for Pip's pure-C Tamagotchi simulation.
 * LVGL, board drivers, audio and Muse transport deliberately stay outside
 * this component so the Muse firmware remains the sole hardware owner.
 */
typedef struct {
    pet_t state;
    int timezone_minutes;
    bool initialized;
} pip_personality_t;

bool pip_personality_init(pip_personality_t *personality,
                          int64_t unix_seconds,
                          int timezone_minutes,
                          uint32_t random_seed);

void pip_personality_update(pip_personality_t *personality,
                            int64_t unix_seconds);

int pip_personality_event(pip_personality_t *personality, int event);

int pip_personality_mood(const pip_personality_t *personality);

#ifdef __cplusplus
}
#endif
