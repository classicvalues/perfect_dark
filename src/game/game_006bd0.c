#include <ultra64.h>
#include "constants.h"
#include "game/chr/chraction.h"
#include "game/dlights.h"
#include "game/game_006900.h"
#include "game/nbomb.h"
#include "game/chr/chr.h"
#include "game/chr/chraction.h"
#include "game/prop.h"
#include "game/game_095320.h"
#include "game/atan2f.h"
#include "game/game_0b3350.h"
#include "game/game_0d4690.h"
#include "game/bg.h"
#include "game/file.h"
#include "game/gfxmemory.h"
#include "bss.h"
#include "lib/lib_09a80.h"
#include "lib/snd.h"
#include "lib/rng.h"
#include "lib/lib_159b0.h"
#include "lib/lib_16110.h"
#include "lib/lib_317f0.h"
#include "data.h"
#include "types.h"

#if VERSION >= VERSION_NTSC_1_0
// In ntsc-bta, this function is in a different file
f32 func0f006bd0(f32 arg0)
{
	s32 ival = arg0 * 4.0f;
	f32 fval = arg0 * 4.0f - (f32)(ival / 4) * 4.0f;

	if (fval < 1.0f) {
		return fval;
	}

	if (fval < 2.0f) {
		return 1.0f;
	}

	if (fval < 3.0f) {
		return 1.0f - (fval - 2.0f);
	}

	return 0.0f;
}
#endif
