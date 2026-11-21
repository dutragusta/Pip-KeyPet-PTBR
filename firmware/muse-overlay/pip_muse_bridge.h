#pragma once
#include <stdbool.h>
#include "muse_state.h"
#include "pip_personality.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Runtime bridge: Muse owns input/voice; Pip receives semantic events only. */
void pip_muse_bridge_init(void);
void pip_muse_bridge_on_mode(muse_mode_t mode);
void pip_muse_bridge_on_touch(void);
void pip_muse_bridge_on_lift(void);
void pip_muse_bridge_tick(void);
bool pip_muse_bridge_status(pip_personality_status_t *out);

#ifdef __cplusplus
}
#endif
