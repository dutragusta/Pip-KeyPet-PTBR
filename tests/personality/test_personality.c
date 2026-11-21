#include "pip_personality.h"
#include "moods.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const int64_t start = 1760000000;
    pip_personality_t pip;
    pip_personality_status_t status;

    assert(!pip_personality_init(NULL, start, -180, 123));
    assert(!pip_personality_init(&pip, start, 900, 123));
    assert(pip_personality_init(&pip, start, -180, 123));

    assert(pip_personality_get_status(&pip, &status));
    assert(status.food > 0.89f && status.food <= 0.91f);
    assert(status.energy > 0.89f && status.energy <= 0.91f);

    /* The upstream pet starts at 90% food, so an extra meal is a little too much. */
    int reaction = pip_personality_event(&pip, PIP_PERSONALITY_FEED, start + 1);
    assert(reaction == PIP_NAUSEOUS);
    reaction = pip_personality_event(&pip, PIP_PERSONALITY_PLAY, start + 2);
    assert(reaction == PIP_HAPPY);

    assert(pip_personality_get_status(&pip, &status));
    assert(status.food <= 1.0f && status.fun <= 1.0f);
    assert(status.mood >= 0 && status.mood < PIP_MOOD_COUNT);

    uint8_t snapshot[sizeof(pet_t)];
    memset(snapshot, 0, sizeof(snapshot));
    assert(pip_personality_state_size() == sizeof(pet_t));
    assert(pip_personality_export(&pip, snapshot, sizeof(snapshot)));

    pip_personality_t restored;
    assert(pip_personality_restore(&restored, snapshot, sizeof(snapshot), -180));
    assert(pip_personality_get_status(&restored, &status));
    assert(status.food == pip.state.food);
    assert(status.energy == pip.state.energy);

    memset(snapshot, 0, sizeof(uint32_t));
    assert(!pip_personality_restore(&restored, snapshot, sizeof(snapshot), -180));
    assert(!pip_personality_restore(&restored, snapshot, sizeof(snapshot) - 1, -180));
    puts("Pip personality tests passed.");
    return 0;
}
