#include "pip_personality.h"
#include <math.h>
#include <string.h>

#define PIP_TZ_MINUTES_MIN (-14 * 60)
#define PIP_TZ_MINUTES_MAX ( 14 * 60)

static bool valid_timezone(int tz)
{
    return tz >= PIP_TZ_MINUTES_MIN && tz <= PIP_TZ_MINUTES_MAX;
}

static bool valid_state(const pet_t *s)
{
    return s && s->version == PET_VERSION && s->last > 0 &&
        isfinite(s->food) && s->food >= 0.0f && s->food <= 1.0f &&
        isfinite(s->energy) && s->energy >= 0.0f && s->energy <= 1.0f &&
        isfinite(s->fun) && s->fun >= 0.0f && s->fun <= 1.0f &&
        isfinite(s->love) && s->love >= 0.0f && s->love <= 1.0f &&
        isfinite(s->walk) && s->walk >= 0.0f && s->walk <= 1.0f &&
        isfinite(s->day_mood) && s->day_mood >= -1.0f && s->day_mood <= 1.0f;
}

bool pip_personality_init(pip_personality_t *p, int64_t now, int tz, uint32_t seed)
{
    if (!p || now <= 0 || !valid_timezone(tz)) return false;
    memset(p, 0, sizeof(*p));
    p->timezone_minutes = tz;
    pet_init(&p->state, now, tz, seed);
    p->initialized = true;
    return true;
}

void pip_personality_update(pip_personality_t *p, int64_t now)
{
    if (!p || !p->initialized || now <= 0) return;
    pet_update(&p->state, now, p->timezone_minutes);
}

int pip_personality_event(pip_personality_t *p, pip_personality_event_t event, int64_t now)
{
    if (!p || !p->initialized || now <= 0) return -1;
    pip_personality_update(p, now);
    return pet_event(&p->state, (int)event);
}

int pip_personality_mood(pip_personality_t *p)
{
    if (!p || !p->initialized) return -1;
    return pet_settle(&p->state, p->timezone_minutes);
}

bool pip_personality_get_status(pip_personality_t *p, pip_personality_status_t *out)
{
    if (!p || !out || !p->initialized) return false;
    out->food = p->state.food;
    out->energy = p->state.energy;
    out->fun = p->state.fun;
    out->love = p->state.love;
    out->walk = p->state.walk;
    out->valence = pet_valence(&p->state);
    out->asleep = p->state.asleep;
    out->mood = pip_personality_mood(p);
    out->reaction_mood = -1;
    out->hour = pet_hour(p->state.last, p->timezone_minutes);
    return true;
}

size_t pip_personality_state_size(void) { return sizeof(pet_t); }

bool pip_personality_export(const pip_personality_t *p, void *buffer, size_t size)
{
    if (!p || !buffer || !p->initialized || size < sizeof(pet_t) ||
        !valid_state(&p->state)) return false;
    memcpy(buffer, &p->state, sizeof(pet_t));
    return true;
}

bool pip_personality_restore(pip_personality_t *p, const void *buffer, size_t size, int tz)
{
    if (!p || !buffer || size != sizeof(pet_t) || !valid_timezone(tz)) return false;
    pet_t candidate;
    memcpy(&candidate, buffer, sizeof(candidate));
    if (!valid_state(&candidate)) return false;
    memset(p, 0, sizeof(*p));
    p->state = candidate;
    p->timezone_minutes = tz;
    p->initialized = true;
    return true;
}
