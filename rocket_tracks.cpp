// sync data implementation
#ifdef SYNC_PLAYER
#include "rocket/track.h"
static track_key faceScale_keys[] = {{ 0, 2.000000, KEY_STEP}, };
const sync_track faceScale = { "faceScale", faceScale_keys,1};
static track_key presentY_keys[] = {{ 0, -17.799995, KEY_STEP}, };
const sync_track presentY = { "presentY", presentY_keys,1};
static track_key presentZ_keys[] = {{ 0, -10.800010, KEY_STEP}, };
const sync_track presentZ = { "presentZ", presentZ_keys,1};
static track_key presentVisible_keys[] = {{ 0, 1.000000, KEY_STEP}, };
const sync_track presentVisible = { "presentVisible", presentVisible_keys,1};
#endif
 // SYNC_PLAYER