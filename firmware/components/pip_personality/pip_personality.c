#include "pip_personality.h"

#include <stddef.h>

bool pip_personality_init(pip_personality_t *personality,
                          int64_t unix_seconds,
                          int timezone_minutes,
                          uint32_t random_seed)
{
    if (personality == NULL || unix_seconds <= 0) {
        return false;
    }

    personality->timezone_minutes = timezone_minutes;
    pet_init(&personality->state, unix_seconds, timezone_minutes, random_seed);
    personality->initialized = true;
    return true;
}

void pip_personality_update(pip_personality_t *personality,
                            int64_t unix_seconds)
{
    if (personality == NULL || !personality->initialized || unix_seconds <= 0) {
        return;
    }

    pet_update(&personality->state, unix_seconds,
               personality->timezone_minutes);
}

int pip_personality_event(pip_personality_t *personality, int event)
{
    if (personality == NULL || !personality->initialized) {
        return -1;
    }

    return pet_event(&personality->state, event);
}

int pip_personality_mood(const pip_personality_t *personality)
{
    if (personality == NULL || !personality->initialized) {
        return -1;
    }

    return pet_mood(&personality->state, personality->timezone_minutes);
}
