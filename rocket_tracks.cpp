// sync data implementation
#ifdef SYNC_PLAYER
#include "rocket/track.h"
static track_key faceScale_keys[] = {{ 0, 0.699997, KEY_STEP}, };
const sync_track faceScale = { "faceScale", faceScale_keys,1};
static track_key faceRotation_keys[] = {{ 0, 5.900002, KEY_STEP}, };
const sync_track faceRotation = { "faceRotation", faceRotation_keys,1};
static track_key faceZeta_keys[] = {{ 0, -49.000000, KEY_STEP}, };
const sync_track faceZeta = { "faceZeta", faceZeta_keys,1};
static track_key presentY_keys[] = {{ 0, -17.799995, KEY_STEP}, };
const sync_track presentY = { "presentY", presentY_keys,1};
static track_key presentZ_keys[] = {{ 0, -10.800010, KEY_STEP}, };
const sync_track presentZ = { "presentZ", presentZ_keys,1};
static track_key presentVisible_keys[] = {{ 0, 1.000000, KEY_STEP}, };
const sync_track presentVisible = { "presentVisible", presentVisible_keys,1};
static track_key scrollX_keys[] = {{ 0, 0.000000, KEY_STEP}, };
const sync_track scrollX = { "scrollX", scrollX_keys,1};
static track_key scrollY_keys[] = {{ 0, 140.000000, KEY_STEP}, };
const sync_track scrollY = { "scrollY", scrollY_keys,1};
static track_key scrollSize_keys[] = {{ 0, 36.000000, KEY_STEP}, };
const sync_track scrollSize = { "scrollSize", scrollSize_keys,1};
#endif
 // SYNC_PLAYER