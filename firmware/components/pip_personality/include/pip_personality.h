#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "pet.h"
#ifdef __cplusplus
extern "C" {
#endif

/* Muse owns hardware, LVGL, audio, connectivity and storage. This component owns only Pip's portable simulation. */
typedef struct {
    pet_t state;
    int timezone_minutes;
    bool initialized;
} pip_personality_t;

typedef struct {
    float food, energy, fun, love, walk, valence;
    bool asleep;
    int mood, hour;
} pip_personality_status_t;

typedef enum {
    PIP_PERSONALITY_FEED = PET_FEED,
    PIP_PERSONALITY_PLAY = PET_PLAY,
    PIP_PERSONALITY_STROKE = PET_STROKE,
    PIP_PERSONALITY_POKE = PET_POKE,
    PIP_PERSONALITY_STEP = PET_STEP,
    PIP_PERSONALITY_SHAKE = PET_SHAKE,
    PIP_PERSONALITY_WAKE = PET_WAKE,
    PIP_PERSONALITY_SLEEP = PET_SLEEP,
    PIP_PERSONALITY_SEEN = PET_SEEN,
    PIP_PERSONALITY_WIN = PET_WIN,
    PIP_PERSONALITY_LOSE = PET_LOSE,
    PIP_PERSONALITY_RECORD = PET_RECORD,
    PIP_PERSONALITY_FRIGHT = PET_FRIGHT,
    PIP_PERSONALITY_FLOOD = PET_FLOOD,
    PIP_PERSONALITY_FED_UP = PET_FED_UP
} pip_personality_event_t;

bool pip_personality_init(pip_personality_t *, int64_t, int, uint32_t);
void pip_personality_update(pip_personality_t *, int64_t);
int pip_personality_event(pip_personality_t *, pip_personality_event_t, int64_t);
int pip_personality_mood(pip_personality_t *);
bool pip_personality_get_status(pip_personality_t *, pip_personality_status_t *);
size_t pip_personality_state_size(void);
bool pip_personality_export(const pip_personality_t *, void *, size_t);
bool pip_personality_restore(pip_personality_t *, const void *, size_t, int);

#ifdef __cplusplus
}
#endif
