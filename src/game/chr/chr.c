#include <ultra64.h>
#include "lib/sched.h"
#include "constants.h"
#include "game/bondmove.h"
#include "game/cheats.h"
#include "game/chr/chraction.h"
#include "game/debug.h"
#include "game/chr/chr.h"
#include "game/prop.h"
#include "game/game_092610.h"
#include "game/game_095320.h"
#include "game/game_096360.h"
#include "game/bondgun.h"
#include "game/game_0abe70.h"
#include "game/game_0b0fd0.h"
#include "game/game_0b28d0.h"
#include "game/game_0b3350.h"
#include "game/game_0b4950.h"
#include "game/game_0b69d0.h"
#include "game/game_0c33f0.h"
#include "game/game_127910.h"
#include "game/game_128f30.h"
#include "game/game_129210.h"
#include "game/explosions/explosions.h"
#include "game/smoke/smoke.h"
#include "game/sparks/sparks.h"
#include "game/bg.h"
#include "game/game_165670.h"
#include "game/file.h"
#include "game/mplayer/setup.h"
#include "game/game_190260.h"
#include "game/game_1999b0.h"
#include "game/mplayer/mplayer.h"
#include "game/pad.h"
#include "game/propobj.h"
#include "game/splat.h"
#include "game/wallhit.h"
#include "bss.h"
#include "lib/lib_09a80.h"
#include "lib/main.h"
#include "lib/model.h"
#include "lib/rng.h"
#include "lib/lib_159b0.h"
#include "lib/lib_16110.h"
#include "lib/lib_233c0.h"
#include "lib/lib_24e40.h"
#include "data.h"
#include "types.h"

void *var8009ccc0[20];
s32 g_NumChrs;
s16 *g_Chrnums;
s16 *g_ChrIndexes;
u32 var8009cd1c;

u8 g_FileState = 0;
u8 var80062944 = 0;
u8 var80062948 = 0;
u8 var8006294c = 0;
u32 var80062950 = 100;
bool g_WeatherTickEnabled = true;
u32 var80062958 = 0x00000000;
u32 var8006295c = 0x00000000;

#if VERSION >= VERSION_PAL_FINAL
u32 var80062640pf = 99;
u32 var80062644pf = 0;
u32 var80062648pf = 0;
u32 var8006264cpf = 0;
#endif

void *var80062960 = NULL;
u32 var80062964 = 0x00000000;
f32 var80062968 = 0;
bool var8006296c = false;
s32 g_SelectedAnimNum = 0;
u32 var80062974 = 0x00000000;
u32 var80062978 = 0x00000000;
u32 var8006297c = 0;
u32 var80062980 = 0;
s32 g_NextChrnum = 5000;

// 80062988
struct chrdata *g_ChrSlots = NULL;

// 8006298c
s32 g_NumChrSlots = 0;

u32 var80062990 = 0x00000000;
u32 var80062994 = 0x00000000;
u32 var80062998 = 0x00000000;
u32 var8006299c = 0x00000001;
u32 var800629a0 = 0x00000003;
u32 var800629a4 = 0x00000000;
u32 var800629a8 = 0x00000000;
u32 var800629ac = 0x00000000;
u32 var800629b0 = 0x00000000;
u32 var800629b4 = 0x00000000;
u32 var800629b8 = 0x00000000;
u32 var800629bc = 0x00000000;
u32 var800629c0 = 0x00000000;
u32 var800629c4 = 0x00000000;
u32 var800629c8 = 0x00000000;
u32 var800629cc = 0x00000000;
u32 var800629d0 = 0x00000000;
u32 var800629d4 = 0x00000000;

void propsTick2(void)
{
	s32 i;
	struct prop *prop;
	struct prop *next;
	struct prop *next2;
	s32 done;
	s32 tickop;

	for (i = 0; i < PLAYERCOUNT(); i++) {
		g_Vars.players[i]->bondextrapos.x = 0;
		g_Vars.players[i]->bondextrapos.y = 0;
		g_Vars.players[i]->bondextrapos.z = 0;
	}

	func0f02c9b0();
	func0f048398();

	prop = g_Vars.activeprops;

	do {
		next = prop->next;
		done = next == g_Vars.pausedprops;
		tickop = TICKOP_NONE;

		if (prop->type == PROPTYPE_CHR) {
			tickop = chrTickBeams(prop);
		} else if (prop->type == PROPTYPE_OBJ || prop->type == PROPTYPE_WEAPON || prop->type == PROPTYPE_DOOR) {
			tickop = func0f07e474(prop);
		} else if (prop->type == PROPTYPE_EXPLOSION) {
			tickop = func0f12bbdc(prop);
		} else if (prop->type == PROPTYPE_SMOKE) {
			tickop = func0f12e848(prop);
		} else if (prop->type == PROPTYPE_PLAYER) {
			tickop = playerTickBeams(prop);
		}

		if (tickop == TICKOP_5) {
			next2 = next;
		} else {
			next2 = prop->next;
			done = next2 == g_Vars.pausedprops;

			if (tickop == TICKOP_RETICK) {
				propDelist(prop);
				propActivateThisFrame(prop);

				if (done) {
					next2 = prop;
					done = false;
				}
			} else {
				propExecuteTickOperation(prop, tickop);
			}
		}

		prop = next2;
	} while (!done);
}

s32 getNumChrSlots(void)
{
	return g_NumChrSlots;
}

void chrSetChrnum(struct chrdata *chr, s16 chrnum)
{
	s32 i;
	bool modified;
	s16 tmp;

	// Set the new chrnum
	for (i = 0; i < g_NumChrs; i++) {
		if (g_Chrnums[i] == chr->chrnum) {
			g_Chrnums[i] = chrnum;
			break;
		}

	}

	chr->chrnum = chrnum;

	// Sort the g_Chrnums and g_ChrIndexes arrays
	do {
		modified = false;

		for (i = 0; i < g_NumChrs - 1; i++) {
			if (g_Chrnums[i] > g_Chrnums[i + 1]) {
				tmp = g_Chrnums[i];
				g_Chrnums[i] = g_Chrnums[i + 1];
				g_Chrnums[i + 1] = tmp;

				tmp = g_ChrIndexes[i];
				g_ChrIndexes[i] = g_ChrIndexes[i + 1];
				g_ChrIndexes[i + 1] = tmp;

				modified = true;
			}
		}
	} while (modified);
}

void chrRegister(s32 chrnum, s32 chrindex)
{
	s32 i;
	s16 tmp;

	for (i = 0; i < g_NumChrs; i++) {
		if (g_Chrnums[i] > chrnum) {
			tmp = g_Chrnums[i];
			g_Chrnums[i] = chrnum;
			chrnum = tmp;

			tmp = g_ChrIndexes[i];
			g_ChrIndexes[i] = chrindex;
			chrindex = tmp;
		}
	}

	g_Chrnums[g_NumChrs] = chrnum;
	g_ChrIndexes[g_NumChrs] = chrindex;
	g_NumChrs++;
}

void chrDeregister(s32 chrnum)
{
	s32 i;

	for (i = 0; i < g_NumChrs; i++) {
		if (g_Chrnums[i] == chrnum) {
			s32 j = i + 1;

			while (j < g_NumChrs) {
				g_Chrnums[i] = g_Chrnums[j];
				g_ChrIndexes[i] = g_ChrIndexes[j];
				i++;
				j++;
			}

			g_NumChrs--;
			return;
		}
	}
}

struct gfxvtx *chrAllocateVertices(s32 numvertices)
{
	return (struct gfxvtx *) gfxAllocate(numvertices * sizeof(struct gfxvtx));
}

void setVar8006297c(u32 arg0)
{
	var8006297c = arg0;
}

u32 getVar8006297c(void)
{
	return var8006297c;
}

void setVar80062980(u32 arg0)
{
	var80062980 = arg0;
}

u32 getVar80062980(void)
{
	return var80062980;
}

void chrSetOrUnsetHiddenFlag00000100(struct chrdata *chr, bool unset)
{
	if (chr) {
		if (unset) {
			chr->hidden &= ~CHRHFLAG_00000100;
		} else {
			chr->hidden |= CHRHFLAG_00000100;
		}
	}
}

/**
 * When a chr is being pushed by a player, this function is called with the new
 * pos and rooms for the chr. It does collision checks and updates dstpos and
 * dstrooms to valid ones if needed.
 */
void chrCalculatePushPos(struct chrdata *chr, struct coord *dstpos, s16 *dstrooms, bool arg3)
{
	f32 ymax;
	f32 ymin;
	f32 width;
	bool moveok = false;
	f32 movex;
	f32 movez;
	struct prop *prop = chr->prop;
	u32 stack;
	f32 halfwidth;
	struct defaultobj *chair = NULL;
	s32 cdresult;
	s16 sp84[20];
#if VERSION < VERSION_NTSC_1_0
	s32 i;
#endif
	struct coord sp78;
	struct coord sp6c;
	struct coord sp60;
	struct coord sp54;
	f32 value;
	struct coord sp44;
#if VERSION < VERSION_NTSC_1_0
	s32 j;
	s32 k;
	s32 l;
#endif

	// The eyespy can't be pushed
	if (CHRRACE(chr) == RACE_EYESPY) {
		roomsCopy(prop->rooms, dstrooms);
		chrSetOrUnsetHiddenFlag00000100(chr, true);
		return;
	}

	propChrGetBbox(prop, &width, &ymax, &ymin);
	halfwidth = width * 0.5f;
	chrSetOrUnsetHiddenFlag00000100(chr, false);

	// myspecial is the chr's chair. This might be disabling collision checks on
	// the chair so they don't interfere with the rest of the checks in this
	// function.
	if (chr->myspecial != -1) {
		chair = objFindByTagId(chr->myspecial);

		if (chair && chair->prop) {
			propObjSetOrUnsetHiddenFlag00400000(chair->prop, false);
		}
	}

	func0f065dfc(&prop->pos, prop->rooms, dstpos, dstrooms, sp84, 20);

#if VERSION < VERSION_NTSC_1_0
	for (i = 0; dstrooms[i] != -1; i++) {
		if (dstrooms[i] == chr->floorroom) {
			dstrooms[0] = chr->floorroom;
			dstrooms[1] = -1;
			break;
		}
	}
#endif

	func0f021fa8(chr, dstpos, dstrooms);

	movex = dstpos->x - prop->pos.x;
	movez = dstpos->z - prop->pos.z;

	if (movex > halfwidth || movez > halfwidth || movex < -halfwidth || movez < -halfwidth) {
		cdresult = func0002d8b8(&prop->pos, prop->rooms, dstpos, dstrooms, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);

		if (cdresult == CDRESULT_NOCOLLISION) {
			cdresult = func0002a6fc(&prop->pos, dstpos, width, dstrooms, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);
		}
	} else {
		cdresult = func0002a6fc(&prop->pos, dstpos, width, sp84, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);
	}

	if (cdresult != CDRESULT_ERROR) {
		if (cdresult == CDRESULT_NOCOLLISION) {
			// The move was completely valid
			if (arg3) {
				chr->invalidmove = 0;
				chr->lastmoveok60 = g_Vars.lvframe60;
			}

			moveok = true;
		} else {
#if VERSION >= VERSION_NTSC_1_0
			func00024e4c(&sp78, &sp6c, 453, "chr/chr.c");
#else
			func00024e4c(&sp78, &sp6c, 451, "chr.c");
#endif

			// Attempt to find a valid position - method #1
			sp60.x = dstpos->x - prop->pos.x;
			sp60.z = dstpos->z - prop->pos.z;

			if (sp78.f[0] != sp6c.f[0] || sp78.f[2] != sp6c.f[2]) {
				sp54.x = sp6c.x - sp78.x;
				sp54.z = sp6c.z - sp78.z;

				value = 1.0f / sqrtf(sp54.f[0] * sp54.f[0] + sp54.f[2] * sp54.f[2]);

				sp54.x *= value;
				sp54.z *= value;

				value = sp60.f[0] * sp54.f[0] + sp60.f[2] * sp54.f[2];

				sp44.x = sp54.x * value + prop->pos.x;
				sp44.y = dstpos->y;
				sp44.z = sp54.z * value + prop->pos.z;

				func0f065dfc(&prop->pos, prop->rooms, &sp44, dstrooms, sp84, 20);

#if VERSION < VERSION_NTSC_1_0
				for (j = 0; dstrooms[j] != -1; j++) {
					if (dstrooms[j] == chr->floorroom) {
						dstrooms[0] = chr->floorroom;
						dstrooms[1] = -1;
						break;
					}
				}
#endif

				func0f021fa8(chr, &sp44, dstrooms);

				movex = sp44.x - prop->pos.x;
				movez = sp44.z - prop->pos.z;

				if (movex > halfwidth || movez > halfwidth || movex < -halfwidth || movez < -halfwidth) {
					cdresult = cdTestAToB2(&prop->pos, prop->rooms, &sp44, dstrooms, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);

					if (cdresult == CDRESULT_NOCOLLISION) {
						cdresult = cdTestVolume(&sp44, width, dstrooms, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);
					}
				} else {
					cdresult = cdTestVolume(&sp44, width, sp84, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);
				}

				if (cdresult == CDRESULT_NOCOLLISION) {
					dstpos->x = sp44.x;
					dstpos->z = sp44.z;
					chr->invalidmove = 2;
					moveok = true;
				}
			}

			if (!moveok) {
				// Attempt to find a valid position - method #2
				sp54.x = sp78.x - dstpos->x;
				sp54.z = sp78.z - dstpos->z;

				if (sp54.f[0] * sp54.f[0] + sp54.f[2] * sp54.f[2] <= width * width) {
					if (sp78.f[0] != prop->pos.f[0] || sp78.f[2] != prop->pos.f[2]) {
						sp54.x = -(sp78.z - prop->pos.z);
						sp54.z = sp78.x - prop->pos.x;

						value = 1.0f / sqrtf(sp54.f[0] * sp54.f[0] + sp54.f[2] * sp54.f[2]);

						sp54.x *= value;
						sp54.z *= value;

						value = sp60.f[0] * sp54.f[0] + sp60.f[2] * sp54.f[2];

						sp44.x = sp54.x * value + prop->pos.x;
						sp44.y = dstpos->y;
						sp44.z = sp54.z * value + prop->pos.z;

						func0f065dfc(&prop->pos, prop->rooms, &sp44, dstrooms, sp84, 20);

#if VERSION < VERSION_NTSC_1_0
						for (k = 0; dstrooms[k] != -1; k++) {
							if (dstrooms[k] == chr->floorroom) {
								dstrooms[0] = chr->floorroom;
								dstrooms[1] = -1;
								break;
							}
						}
#endif

						func0f021fa8(chr, &sp44, dstrooms);

						movex = sp44.x - prop->pos.x;
						movez = sp44.z - prop->pos.z;

						if (movex > halfwidth || movez > halfwidth || movex < -halfwidth || movez < -halfwidth) {
							cdresult = cdTestAToB2(&prop->pos, prop->rooms, &sp44, dstrooms, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);

							if (cdresult == CDRESULT_NOCOLLISION) {
								cdresult = cdTestVolume(&sp44, width, dstrooms, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);
							}
						} else {
							cdresult = cdTestVolume(&sp44, width, sp84, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);
						}

						if (cdresult == CDRESULT_NOCOLLISION) {
							dstpos->x = sp44.x;
							dstpos->z = sp44.z;
							chr->invalidmove = 2;
							moveok = true;
						}
					}
				} else {
					sp54.x = sp6c.x - dstpos->x;
					sp54.z = sp6c.z - dstpos->z;

					if (sp54.f[0] * sp54.f[0] + sp54.f[2] * sp54.f[2] <= width * width) {
						if (sp6c.f[0] != prop->pos.f[0] || sp6c.f[2] != prop->pos.f[2]) {
							sp54.x = -(sp6c.z - prop->pos.z);
							sp54.z = sp6c.x - prop->pos.x;

							value = 1.0f / sqrtf(sp54.f[0] * sp54.f[0] + sp54.f[2] * sp54.f[2]);

							sp54.x *= value;
							sp54.z *= value;

							value = sp60.f[0] * sp54.f[0] + sp60.f[2] * sp54.f[2];

							sp44.x = sp54.x * value + prop->pos.x;
							sp44.y = dstpos->y;
							sp44.z = sp54.z * value + prop->pos.z;

							func0f065dfc(&prop->pos, prop->rooms, &sp44, dstrooms, sp84, 20);

#if VERSION < VERSION_NTSC_1_0
							for (l = 0; dstrooms[l] != -1; l++) {
								if (dstrooms[l] == chr->floorroom) {
									dstrooms[0] = chr->floorroom;
									dstrooms[1] = -1;
									break;
								}
							}
#endif

							func0f021fa8(chr, &sp44, dstrooms);

							movex = sp44.x - prop->pos.x;
							movez = sp44.z - prop->pos.z;

							if (movex > halfwidth || movez > halfwidth || movex < -halfwidth || movez < -halfwidth) {
								cdresult = cdTestAToB2(&prop->pos, prop->rooms, &sp44, dstrooms, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);

								if (cdresult == CDRESULT_NOCOLLISION) {
									cdresult = cdTestVolume(&sp44, width, dstrooms, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);
								}
							} else {
								cdresult = cdTestVolume(&sp44, width, sp84, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y);
							}

							if (cdresult == CDRESULT_NOCOLLISION) {
								dstpos->x = sp44.x;
								dstpos->z = sp44.z;
								chr->invalidmove = 2;
								moveok = true;
							}
						}
					}
				}
			}
		}
	}

	if (!moveok) {
		// Keep chr where they are
		dstpos->x = prop->pos.x;
		dstpos->z = prop->pos.z;
		roomsCopy(prop->rooms, dstrooms);
		chr->invalidmove = 1;
	}

	chrSetOrUnsetHiddenFlag00000100(chr, true);

	if (chair && chair->prop) {
		propObjSetOrUnsetHiddenFlag00400000(chair->prop, true);
	}
}

bool func0f01f264(struct chrdata *chr, struct coord *pos, s16 *rooms, f32 arg3, bool arg4)
{
	bool result;
	struct coord newpos;
	s16 newrooms[8];
	f32 ymax;
	f32 ymin;
	f32 width;

	newpos.x = pos->x;
	newpos.y = pos->y + arg3;
	newpos.z = pos->z;

	propChrGetBbox(chr->prop, &width, &ymax, &ymin);
	func0f065e74(pos, rooms, &newpos, newrooms);
	func0f021fa8(chr, &newpos, newrooms);
	chrSetOrUnsetHiddenFlag00000100(chr, false);
	result = cdTestVolume(&newpos, width, newrooms, CDTYPE_ALL, 1,
			ymax - chr->prop->pos.y,
			ymin - chr->prop->pos.y);
	chrSetOrUnsetHiddenFlag00000100(chr, true);

#if VERSION >= VERSION_NTSC_1_0
	if (result == true && arg4) {
		pos->y = newpos.y;
		roomsCopy(newrooms, rooms);
	}
#endif

	return result == true;
}

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0f01f378
.late_rodata
glabel var7f1a98dcpf
.word 0xc9742400
glabel var7f1a98e0pf
.word 0x4106ae1e
glabel var7f1a98e4pf
.word 0x4099999a
glabel var7f1a98e8pf
.word 0x4099999a
glabel var7f1a98ecpf
.word 0x3f8ccccd
glabel var7f1a98f0pf
.word 0x3f8ccccd
glabel var7f1a98f4pf
.word 0x3f666666
glabel var7f1a98f8pf
.word 0x3dcccccd
glabel var7f1a98fcpf
.word 0x4106ae1e
glabel var7f1a9900pf
.word 0x4106ae1e
glabel var7f1a9904pf
.word 0xc7c35000
glabel var7f1a9908pf
.word 0xc7c35000
glabel var7f1a990cpf
.word 0x4106ae1e
glabel var7f1a9910pf
.word 0xc6ea6000
glabel var7f1a9914pf
.word 0x4106ae1e
glabel var7f1a9918pf
.word 0x3f619653
glabel var7f1a991cpf
.word 0x3df34d68
glabel var7f1a9920pf
.word 0x4106ae1e
glabel var7f1a9924pf
.word 0x3dcccccd
glabel var7f1a9928pf
.word 0xbdcccccd
glabel var7f1a992cpf
.word 0x3dcccccd
.text
/*  f01f498:	27bdfee0 */ 	addiu	$sp,$sp,-288
/*  f01f49c:	afbf0034 */ 	sw	$ra,0x34($sp)
/*  f01f4a0:	afb10030 */ 	sw	$s1,0x30($sp)
/*  f01f4a4:	afb0002c */ 	sw	$s0,0x2c($sp)
/*  f01f4a8:	afa40120 */ 	sw	$a0,0x120($sp)
/*  f01f4ac:	afa50124 */ 	sw	$a1,0x124($sp)
/*  f01f4b0:	afa7012c */ 	sw	$a3,0x12c($sp)
/*  f01f4b4:	8c900004 */ 	lw	$s0,0x4($a0)
/*  f01f4b8:	3c08800a */ 	lui	$t0,0x800a
/*  f01f4bc:	44808000 */ 	mtc1	$zero,$f16
/*  f01f4c0:	8e0f001c */ 	lw	$t7,0x1c($s0)
/*  f01f4c4:	00c08825 */ 	move	$s1,$a2
/*  f01f4c8:	2508a510 */ 	addiu	$t0,$t0,-23280
/*  f01f4cc:	afaf0118 */ 	sw	$t7,0x118($sp)
/*  f01f4d0:	c60400b4 */ 	lwc1	$f4,0xb4($s0)
/*  f01f4d4:	12000004 */ 	beqz	$s0,.PF0f01f4e8
/*  f01f4d8:	e7a400f8 */ 	swc1	$f4,0xf8($sp)
/*  f01f4dc:	921802fe */ 	lbu	$t8,0x2fe($s0)
/*  f01f4e0:	10000002 */ 	b	.PF0f01f4ec
/*  f01f4e4:	afb800f4 */ 	sw	$t8,0xf4($sp)
.PF0f01f4e8:
/*  f01f4e8:	afa000f4 */ 	sw	$zero,0xf4($sp)
.PF0f01f4ec:
/*  f01f4ec:	c506004c */ 	lwc1	$f6,0x4c($t0)
/*  f01f4f0:	8fa90120 */ 	lw	$t1,0x120($sp)
/*  f01f4f4:	e7b000f0 */ 	swc1	$f16,0xf0($sp)
/*  f01f4f8:	a7a000ea */ 	sh	$zero,0xea($sp)
/*  f01f4fc:	e7a600dc */ 	swc1	$f6,0xdc($sp)
/*  f01f500:	8d2a0020 */ 	lw	$t2,0x20($t1)
/*  f01f504:	3c198006 */ 	lui	$t9,0x8006
/*  f01f508:	8f39ecbc */ 	lw	$t9,-0x1344($t9)
/*  f01f50c:	854b0000 */ 	lh	$t3,0x0($t2)
/*  f01f510:	8d060034 */ 	lw	$a2,0x34($t0)
/*  f01f514:	c50c0044 */ 	lwc1	$f12,0x44($t0)
/*  f01f518:	000b6080 */ 	sll	$t4,$t3,0x2
/*  f01f51c:	018b6023 */ 	subu	$t4,$t4,$t3
/*  f01f520:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f01f524:	032c6821 */ 	addu	$t5,$t9,$t4
/*  f01f528:	91ae000b */ 	lbu	$t6,0xb($t5)
/*  f01f52c:	c7aa00f8 */ 	lwc1	$f10,0xf8($sp)
/*  f01f530:	31cf0002 */ 	andi	$t7,$t6,0x2
/*  f01f534:	51e0003a */ 	beqzl	$t7,.PF0f01f620
/*  f01f538:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*  f01f53c:	8e180014 */ 	lw	$t8,0x14($s0)
/*  f01f540:	8fab0118 */ 	lw	$t3,0x118($sp)
/*  f01f544:	02203025 */ 	move	$a2,$s1
/*  f01f548:	00184b80 */ 	sll	$t1,$t8,0xe
/*  f01f54c:	0521000a */ 	bgez	$t1,.PF0f01f578
/*  f01f550:	25640008 */ 	addiu	$a0,$t3,0x8
/*  f01f554:	8faa0118 */ 	lw	$t2,0x118($sp)
/*  f01f558:	02203025 */ 	move	$a2,$s1
/*  f01f55c:	27a700fc */ 	addiu	$a3,$sp,0xfc
/*  f01f560:	25450028 */ 	addiu	$a1,$t2,0x28
/*  f01f564:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f01f568:	0fc1984a */ 	jal	func0f065e98
/*  f01f56c:	25440008 */ 	addiu	$a0,$t2,0x8
/*  f01f570:	10000006 */ 	b	.PF0f01f58c
/*  f01f574:	8e050024 */ 	lw	$a1,0x24($s0)
.PF0f01f578:
/*  f01f578:	25650028 */ 	addiu	$a1,$t3,0x28
/*  f01f57c:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f01f580:	0fc19841 */ 	jal	func0f065e74
/*  f01f584:	27a700fc */ 	addiu	$a3,$sp,0xfc
/*  f01f588:	8e050024 */ 	lw	$a1,0x24($s0)
.PF0f01f58c:
/*  f01f58c:	26190191 */ 	addiu	$t9,$s0,0x191
/*  f01f590:	27ac00ea */ 	addiu	$t4,$sp,0xea
/*  f01f594:	260d02b2 */ 	addiu	$t5,$s0,0x2b2
/*  f01f598:	27ae00ec */ 	addiu	$t6,$sp,0xec
/*  f01f59c:	27af0114 */ 	addiu	$t7,$sp,0x114
/*  f01f5a0:	afaf0020 */ 	sw	$t7,0x20($sp)
/*  f01f5a4:	afae001c */ 	sw	$t6,0x1c($sp)
/*  f01f5a8:	afad0018 */ 	sw	$t5,0x18($sp)
/*  f01f5ac:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f01f5b0:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f01f5b4:	02202025 */ 	move	$a0,$s1
/*  f01f5b8:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f01f5bc:	0c00a6ac */ 	jal	cdFindGroundY
/*  f01f5c0:	2607018a */ 	addiu	$a3,$s0,0x18a
/*  f01f5c4:	3c017f1b */ 	lui	$at,0x7f1b
/*  f01f5c8:	c42898dc */ 	lwc1	$f8,-0x6724($at)
/*  f01f5cc:	44808000 */ 	mtc1	$zero,$f16
/*  f01f5d0:	46000086 */ 	mov.s	$f2,$f0
/*  f01f5d4:	4608003c */ 	c.lt.s	$f0,$f8
/*  f01f5d8:	3c017f1b */ 	lui	$at,0x7f1b
/*  f01f5dc:	45020003 */ 	bc1fl	.PF0f01f5ec
/*  f01f5e0:	e60200b8 */ 	swc1	$f2,0xb8($s0)
/*  f01f5e4:	46008086 */ 	mov.s	$f2,$f16
/*  f01f5e8:	e60200b8 */ 	swc1	$f2,0xb8($s0)
.PF0f01f5ec:
/*  f01f5ec:	e6100038 */ 	swc1	$f16,0x38($s0)
/*  f01f5f0:	e61000bc */ 	swc1	$f16,0xbc($s0)
/*  f01f5f4:	e61000c0 */ 	swc1	$f16,0xc0($s0)
/*  f01f5f8:	e61000c4 */ 	swc1	$f16,0xc4($s0)
/*  f01f5fc:	e60200b4 */ 	swc1	$f2,0xb4($s0)
/*  f01f600:	c42a98e0 */ 	lwc1	$f10,-0x6720($at)
/*  f01f604:	460a1482 */ 	mul.s	$f18,$f2,$f10
/*  f01f608:	e61200b0 */ 	swc1	$f18,0xb0($s0)
/*  f01f60c:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*  f01f610:	46022181 */ 	sub.s	$f6,$f4,$f2
/*  f01f614:	100003c5 */ 	b	.PF0f02052c
/*  f01f618:	e6260004 */ 	swc1	$f6,0x4($s1)
/*  f01f61c:	c6280004 */ 	lwc1	$f8,0x4($s1)
.PF0f01f620:
/*  f01f620:	3c098006 */ 	lui	$t1,0x8006
/*  f01f624:	25292670 */ 	addiu	$t1,$t1,0x2670
/*  f01f628:	460a4480 */ 	add.s	$f18,$f8,$f10
/*  f01f62c:	e6320004 */ 	swc1	$f18,0x4($s1)
/*  f01f630:	8e1802d4 */ 	lw	$t8,0x2d4($s0)
/*  f01f634:	53000040 */ 	beqzl	$t8,.PF0f01f738
/*  f01f638:	82020007 */ 	lb	$v0,0x7($s0)
/*  f01f63c:	8d210000 */ 	lw	$at,0x0($t1)
/*  f01f640:	27a500b8 */ 	addiu	$a1,$sp,0xb8
/*  f01f644:	02002025 */ 	move	$a0,$s0
/*  f01f648:	aca10000 */ 	sw	$at,0x0($a1)
/*  f01f64c:	8d2b0004 */ 	lw	$t3,0x4($t1)
/*  f01f650:	18c0002e */ 	blez	$a2,.PF0f01f70c
/*  f01f654:	acab0004 */ 	sw	$t3,0x4($a1)
/*  f01f658:	8e0202d4 */ 	lw	$v0,0x2d4($s0)
/*  f01f65c:	90430078 */ 	lbu	$v1,0x78($v0)
/*  f01f660:	50600014 */ 	beqzl	$v1,.PF0f01f6b4
/*  f01f664:	8e0f031c */ 	lw	$t7,0x31c($s0)
/*  f01f668:	8e19001c */ 	lw	$t9,0x1c($s0)
/*  f01f66c:	246effff */ 	addiu	$t6,$v1,-1
/*  f01f670:	28c10019 */ 	slti	$at,$a2,0x19
/*  f01f674:	932c0001 */ 	lbu	$t4,0x1($t9)
/*  f01f678:	318d0080 */ 	andi	$t5,$t4,0x80
/*  f01f67c:	11a00003 */ 	beqz	$t5,.PF0f01f68c
/*  f01f680:	00000000 */ 	nop
/*  f01f684:	1000001a */ 	b	.PF0f01f6f0
/*  f01f688:	a0400078 */ 	sb	$zero,0x78($v0)
.PF0f01f68c:
/*  f01f68c:	14200018 */ 	bnez	$at,.PF0f01f6f0
/*  f01f690:	a04e0078 */ 	sb	$t6,0x78($v0)
/*  f01f694:	3c014080 */ 	lui	$at,0x4080
/*  f01f698:	44816000 */ 	mtc1	$at,$f12
/*  f01f69c:	3c017f1b */ 	lui	$at,0x7f1b
/*  f01f6a0:	c42498e4 */ 	lwc1	$f4,-0x671c($at)
/*  f01f6a4:	24060010 */ 	li	$a2,0x10
/*  f01f6a8:	10000011 */ 	b	.PF0f01f6f0
/*  f01f6ac:	e7a400dc */ 	swc1	$f4,0xdc($sp)
/*  f01f6b0:	8e0f031c */ 	lw	$t7,0x31c($s0)
.PF0f01f6b4:
/*  f01f6b4:	51e0000f */ 	beqzl	$t7,.PF0f01f6f4
/*  f01f6b8:	8fa700dc */ 	lw	$a3,0xdc($sp)
/*  f01f6bc:	8e18001c */ 	lw	$t8,0x1c($s0)
/*  f01f6c0:	28c10019 */ 	slti	$at,$a2,0x19
/*  f01f6c4:	930a0001 */ 	lbu	$t2,0x1($t8)
/*  f01f6c8:	314900c0 */ 	andi	$t1,$t2,0xc0
/*  f01f6cc:	55200009 */ 	bnezl	$t1,.PF0f01f6f4
/*  f01f6d0:	8fa700dc */ 	lw	$a3,0xdc($sp)
/*  f01f6d4:	14200006 */ 	bnez	$at,.PF0f01f6f0
/*  f01f6d8:	3c014080 */ 	lui	$at,0x4080
/*  f01f6dc:	44816000 */ 	mtc1	$at,$f12
/*  f01f6e0:	3c017f1b */ 	lui	$at,0x7f1b
/*  f01f6e4:	c42698e8 */ 	lwc1	$f6,-0x6718($at)
/*  f01f6e8:	24060010 */ 	li	$a2,0x10
/*  f01f6ec:	e7a600dc */ 	swc1	$f6,0xdc($sp)
.PF0f01f6f0:
/*  f01f6f0:	8fa700dc */ 	lw	$a3,0xdc($sp)
.PF0f01f6f4:
/*  f01f6f4:	0fc64cac */ 	jal	func0f1921f8
/*  f01f6f8:	e7ac00e0 */ 	swc1	$f12,0xe0($sp)
/*  f01f6fc:	3c08800a */ 	lui	$t0,0x800a
/*  f01f700:	44808000 */ 	mtc1	$zero,$f16
/*  f01f704:	2508a510 */ 	addiu	$t0,$t0,-23280
/*  f01f708:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
.PF0f01f70c:
/*  f01f70c:	8fab0124 */ 	lw	$t3,0x124($sp)
/*  f01f710:	c7a800b8 */ 	lwc1	$f8,0xb8($sp)
/*  f01f714:	c56a0000 */ 	lwc1	$f10,0x0($t3)
/*  f01f718:	460a4480 */ 	add.s	$f18,$f8,$f10
/*  f01f71c:	e6320000 */ 	swc1	$f18,0x0($s1)
/*  f01f720:	8fb90124 */ 	lw	$t9,0x124($sp)
/*  f01f724:	c7a400bc */ 	lwc1	$f4,0xbc($sp)
/*  f01f728:	c7260008 */ 	lwc1	$f6,0x8($t9)
/*  f01f72c:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f01f730:	e6280008 */ 	swc1	$f8,0x8($s1)
/*  f01f734:	82020007 */ 	lb	$v0,0x7($s0)
.PF0f01f738:
/*  f01f738:	2401000e */ 	li	$at,0xe
/*  f01f73c:	10410002 */ 	beq	$v0,$at,.PF0f01f748
/*  f01f740:	2401000f */ 	li	$at,0xf
/*  f01f744:	14410021 */ 	bne	$v0,$at,.PF0f01f7cc
.PF0f01f748:
/*  f01f748:	3c014020 */ 	lui	$at,0x4020
/*  f01f74c:	44819000 */ 	mtc1	$at,$f18
/*  f01f750:	c60a0024 */ 	lwc1	$f10,0x24($s0)
/*  f01f754:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01f758:	3c013f80 */ 	lui	$at,0x3f80
/*  f01f75c:	46125102 */ 	mul.s	$f4,$f10,$f18
/*  f01f760:	44819000 */ 	mtc1	$at,$f18
/*  f01f764:	8e02001c */ 	lw	$v0,0x1c($s0)
/*  f01f768:	c6060028 */ 	lwc1	$f6,0x28($s0)
/*  f01f76c:	240d0040 */ 	li	$t5,0x40
/*  f01f770:	c442000c */ 	lwc1	$f2,0xc($v0)
/*  f01f774:	46060200 */ 	add.s	$f8,$f0,$f6
/*  f01f778:	44052000 */ 	mfc1	$a1,$f4
/*  f01f77c:	260e0320 */ 	addiu	$t6,$s0,0x320
/*  f01f780:	46120100 */ 	add.s	$f4,$f0,$f18
/*  f01f784:	244c0028 */ 	addiu	$t4,$v0,0x28
/*  f01f788:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f01f78c:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f01f790:	afae0018 */ 	sw	$t6,0x18($sp)
/*  f01f794:	e7ac00e0 */ 	swc1	$f12,0xe0($sp)
/*  f01f798:	46022181 */ 	sub.s	$f6,$f4,$f2
/*  f01f79c:	44065000 */ 	mfc1	$a2,$f10
/*  f01f7a0:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f01f7a4:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f01f7a8:	44073000 */ 	mfc1	$a3,$f6
/*  f01f7ac:	0c00a63f */ 	jal	func00029ffc
/*  f01f7b0:	00000000 */ 	nop
/*  f01f7b4:	3c08800a */ 	lui	$t0,0x800a
/*  f01f7b8:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
/*  f01f7bc:	44808000 */ 	mtc1	$zero,$f16
/*  f01f7c0:	ae02031c */ 	sw	$v0,0x31c($s0)
/*  f01f7c4:	10000002 */ 	b	.PF0f01f7d0
/*  f01f7c8:	2508a510 */ 	addiu	$t0,$t0,-23280
.PF0f01f7cc:
/*  f01f7cc:	ae00031c */ 	sw	$zero,0x31c($s0)
.PF0f01f7d0:
/*  f01f7d0:	8e0f02d4 */ 	lw	$t7,0x2d4($s0)
/*  f01f7d4:	3c014339 */ 	lui	$at,0x4339
/*  f01f7d8:	51e0007b */ 	beqzl	$t7,.PF0f01f9c8
/*  f01f7dc:	820a0007 */ 	lb	$t2,0x7($s0)
/*  f01f7e0:	44817000 */ 	mtc1	$at,$f14
/*  f01f7e4:	82020007 */ 	lb	$v0,0x7($s0)
/*  f01f7e8:	2401000f */ 	li	$at,0xf
/*  f01f7ec:	e60e0028 */ 	swc1	$f14,0x28($s0)
/*  f01f7f0:	5441000a */ 	bnel	$v0,$at,.PF0f01f81c
/*  f01f7f4:	2401000f */ 	li	$at,0xf
/*  f01f7f8:	92180065 */ 	lbu	$t8,0x65($s0)
/*  f01f7fc:	3c014307 */ 	lui	$at,0x4307
/*  f01f800:	330a0080 */ 	andi	$t2,$t8,0x80
/*  f01f804:	51400005 */ 	beqzl	$t2,.PF0f01f81c
/*  f01f808:	2401000f */ 	li	$at,0xf
/*  f01f80c:	44814000 */ 	mtc1	$at,$f8
/*  f01f810:	1000004a */ 	b	.PF0f01f93c
/*  f01f814:	e6080028 */ 	swc1	$f8,0x28($s0)
/*  f01f818:	2401000f */ 	li	$at,0xf
.PF0f01f81c:
/*  f01f81c:	14410009 */ 	bne	$v0,$at,.PF0f01f844
/*  f01f820:	00000000 */ 	nop
/*  f01f824:	92090065 */ 	lbu	$t1,0x65($s0)
/*  f01f828:	3c0142b4 */ 	lui	$at,0x42b4
/*  f01f82c:	312b0040 */ 	andi	$t3,$t1,0x40
/*  f01f830:	11600004 */ 	beqz	$t3,.PF0f01f844
/*  f01f834:	00000000 */ 	nop
/*  f01f838:	44815000 */ 	mtc1	$at,$f10
/*  f01f83c:	1000003f */ 	b	.PF0f01f93c
/*  f01f840:	e60a0028 */ 	swc1	$f10,0x28($s0)
.PF0f01f844:
/*  f01f844:	3c017f1b */ 	lui	$at,0x7f1b
/*  f01f848:	c42498ec */ 	lwc1	$f4,-0x6714($at)
/*  f01f84c:	c6120024 */ 	lwc1	$f18,0x24($s0)
/*  f01f850:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01f854:	3c014120 */ 	lui	$at,0x4120
/*  f01f858:	46049182 */ 	mul.s	$f6,$f18,$f4
/*  f01f85c:	44819000 */ 	mtc1	$at,$f18
/*  f01f860:	8e02001c */ 	lw	$v0,0x1c($s0)
/*  f01f864:	240c1000 */ 	li	$t4,0x1000
/*  f01f868:	460e0200 */ 	add.s	$f8,$f0,$f14
/*  f01f86c:	c442000c */ 	lwc1	$f2,0xc($v0)
/*  f01f870:	44053000 */ 	mfc1	$a1,$f6
/*  f01f874:	46120101 */ 	sub.s	$f4,$f0,$f18
/*  f01f878:	24590028 */ 	addiu	$t9,$v0,0x28
/*  f01f87c:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f01f880:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f01f884:	e7ac00e0 */ 	swc1	$f12,0xe0($sp)
/*  f01f888:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f01f88c:	46022181 */ 	sub.s	$f6,$f4,$f2
/*  f01f890:	44065000 */ 	mfc1	$a2,$f10
/*  f01f894:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f01f898:	44073000 */ 	mfc1	$a3,$f6
/*  f01f89c:	0c00a68f */ 	jal	func0002a13c
/*  f01f8a0:	00000000 */ 	nop
/*  f01f8a4:	10400005 */ 	beqz	$v0,.PF0f01f8bc
/*  f01f8a8:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
/*  f01f8ac:	3c014307 */ 	lui	$at,0x4307
/*  f01f8b0:	44814000 */ 	mtc1	$at,$f8
/*  f01f8b4:	10000021 */ 	b	.PF0f01f93c
/*  f01f8b8:	e6080028 */ 	swc1	$f8,0x28($s0)
.PF0f01f8bc:
/*  f01f8bc:	3c017f1b */ 	lui	$at,0x7f1b
/*  f01f8c0:	c43298f0 */ 	lwc1	$f18,-0x6710($at)
/*  f01f8c4:	c60a0024 */ 	lwc1	$f10,0x24($s0)
/*  f01f8c8:	3c014307 */ 	lui	$at,0x4307
/*  f01f8cc:	44813000 */ 	mtc1	$at,$f6
/*  f01f8d0:	46125102 */ 	mul.s	$f4,$f10,$f18
/*  f01f8d4:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01f8d8:	3c014120 */ 	lui	$at,0x4120
/*  f01f8dc:	44819000 */ 	mtc1	$at,$f18
/*  f01f8e0:	8e02001c */ 	lw	$v0,0x1c($s0)
/*  f01f8e4:	46060200 */ 	add.s	$f8,$f0,$f6
/*  f01f8e8:	240e0800 */ 	li	$t6,0x800
/*  f01f8ec:	44052000 */ 	mfc1	$a1,$f4
/*  f01f8f0:	46120101 */ 	sub.s	$f4,$f0,$f18
/*  f01f8f4:	c442000c */ 	lwc1	$f2,0xc($v0)
/*  f01f8f8:	244d0028 */ 	addiu	$t5,$v0,0x28
/*  f01f8fc:	afad0010 */ 	sw	$t5,0x10($sp)
/*  f01f900:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f01f904:	e7ac00e0 */ 	swc1	$f12,0xe0($sp)
/*  f01f908:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f01f90c:	46022181 */ 	sub.s	$f6,$f4,$f2
/*  f01f910:	44065000 */ 	mfc1	$a2,$f10
/*  f01f914:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f01f918:	44073000 */ 	mfc1	$a3,$f6
/*  f01f91c:	0c00a68f */ 	jal	func0002a13c
/*  f01f920:	00000000 */ 	nop
/*  f01f924:	10400005 */ 	beqz	$v0,.PF0f01f93c
/*  f01f928:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
/*  f01f92c:	3c0142b4 */ 	lui	$at,0x42b4
/*  f01f930:	44814000 */ 	mtc1	$at,$f8
/*  f01f934:	00000000 */ 	nop
/*  f01f938:	e6080028 */ 	swc1	$f8,0x28($s0)
.PF0f01f93c:
/*  f01f93c:	8e0402d4 */ 	lw	$a0,0x2d4($s0)
/*  f01f940:	e7ac00e0 */ 	swc1	$f12,0xe0($sp)
/*  f01f944:	0fc32fa5 */ 	jal	bmove0f0cb904
/*  f01f948:	24840108 */ 	addiu	$a0,$a0,0x108
/*  f01f94c:	8e0f02d4 */ 	lw	$t7,0x2d4($s0)
/*  f01f950:	3c028007 */ 	lui	$v0,0x8007
/*  f01f954:	244260d0 */ 	addiu	$v0,$v0,0x60d0
/*  f01f958:	c4520024 */ 	lwc1	$f18,0x24($v0)
/*  f01f95c:	c5ea0108 */ 	lwc1	$f10,0x108($t7)
/*  f01f960:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f01f964:	3c013f00 */ 	lui	$at,0x3f00
/*  f01f968:	46125102 */ 	mul.s	$f4,$f10,$f18
/*  f01f96c:	44810000 */ 	mtc1	$at,$f0
/*  f01f970:	c6320000 */ 	lwc1	$f18,0x0($s1)
/*  f01f974:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
/*  f01f978:	3c08800a */ 	lui	$t0,0x800a
/*  f01f97c:	44808000 */ 	mtc1	$zero,$f16
/*  f01f980:	2508a510 */ 	addiu	$t0,$t0,-23280
/*  f01f984:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f01f988:	00000000 */ 	nop
/*  f01f98c:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f01f990:	460a9100 */ 	add.s	$f4,$f18,$f10
/*  f01f994:	e6240000 */ 	swc1	$f4,0x0($s1)
/*  f01f998:	8e1802d4 */ 	lw	$t8,0x2d4($s0)
/*  f01f99c:	c4480024 */ 	lwc1	$f8,0x24($v0)
/*  f01f9a0:	c7aa00dc */ 	lwc1	$f10,0xdc($sp)
/*  f01f9a4:	c7060110 */ 	lwc1	$f6,0x110($t8)
/*  f01f9a8:	46083482 */ 	mul.s	$f18,$f6,$f8
/*  f01f9ac:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*  f01f9b0:	460a9102 */ 	mul.s	$f4,$f18,$f10
/*  f01f9b4:	00000000 */ 	nop
/*  f01f9b8:	46002182 */ 	mul.s	$f6,$f4,$f0
/*  f01f9bc:	46064480 */ 	add.s	$f18,$f8,$f6
/*  f01f9c0:	e6320008 */ 	swc1	$f18,0x8($s1)
/*  f01f9c4:	820a0007 */ 	lb	$t2,0x7($s0)
.PF0f01f9c8:
/*  f01f9c8:	24010004 */ 	li	$at,0x4
/*  f01f9cc:	5541002d */ 	bnel	$t2,$at,.PF0f01fa84
/*  f01f9d0:	c60202e8 */ 	lwc1	$f2,0x2e8($s0)
/*  f01f9d4:	c6020038 */ 	lwc1	$f2,0x38($s0)
/*  f01f9d8:	8fa90120 */ 	lw	$t1,0x120($sp)
/*  f01f9dc:	4602803c */ 	c.lt.s	$f16,$f2
/*  f01f9e0:	00000000 */ 	nop
/*  f01f9e4:	45020027 */ 	bc1fl	.PF0f01fa84
/*  f01f9e8:	c60202e8 */ 	lwc1	$f2,0x2e8($s0)
/*  f01f9ec:	8d2b0020 */ 	lw	$t3,0x20($t1)
/*  f01f9f0:	c608003c */ 	lwc1	$f8,0x3c($s0)
/*  f01f9f4:	c56a0074 */ 	lwc1	$f10,0x74($t3)
/*  f01f9f8:	46081181 */ 	sub.s	$f6,$f2,$f8
/*  f01f9fc:	c6080040 */ 	lwc1	$f8,0x40($s0)
/*  f01fa00:	460c5102 */ 	mul.s	$f4,$f10,$f12
/*  f01fa04:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f01fa08:	46062482 */ 	mul.s	$f18,$f4,$f6
/*  f01fa0c:	46029003 */ 	div.s	$f0,$f18,$f2
/*  f01fa10:	c6320008 */ 	lwc1	$f18,0x8($s1)
/*  f01fa14:	46004102 */ 	mul.s	$f4,$f8,$f0
/*  f01fa18:	46045180 */ 	add.s	$f6,$f10,$f4
/*  f01fa1c:	e6260000 */ 	swc1	$f6,0x0($s1)
/*  f01fa20:	c6080048 */ 	lwc1	$f8,0x48($s0)
/*  f01fa24:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f01fa28:	460a9100 */ 	add.s	$f4,$f18,$f10
/*  f01fa2c:	e6240008 */ 	swc1	$f4,0x8($s1)
/*  f01fa30:	c6080044 */ 	lwc1	$f8,0x44($s0)
/*  f01fa34:	c7a600f0 */ 	lwc1	$f6,0xf0($sp)
/*  f01fa38:	8fb90120 */ 	lw	$t9,0x120($sp)
/*  f01fa3c:	46004482 */ 	mul.s	$f18,$f8,$f0
/*  f01fa40:	46123280 */ 	add.s	$f10,$f6,$f18
/*  f01fa44:	e7aa00f0 */ 	swc1	$f10,0xf0($sp)
/*  f01fa48:	8f2c0020 */ 	lw	$t4,0x20($t9)
/*  f01fa4c:	c604003c */ 	lwc1	$f4,0x3c($s0)
/*  f01fa50:	c60a0038 */ 	lwc1	$f10,0x38($s0)
/*  f01fa54:	c5880074 */ 	lwc1	$f8,0x74($t4)
/*  f01fa58:	46086182 */ 	mul.s	$f6,$f12,$f8
/*  f01fa5c:	46062480 */ 	add.s	$f18,$f4,$f6
/*  f01fa60:	e612003c */ 	swc1	$f18,0x3c($s0)
/*  f01fa64:	c608003c */ 	lwc1	$f8,0x3c($s0)
/*  f01fa68:	4608503c */ 	c.lt.s	$f10,$f8
/*  f01fa6c:	00000000 */ 	nop
/*  f01fa70:	4502002e */ 	bc1fl	.PF0f01fb2c
/*  f01fa74:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01fa78:	1000002b */ 	b	.PF0f01fb28
/*  f01fa7c:	e6100038 */ 	swc1	$f16,0x38($s0)
/*  f01fa80:	c60202e8 */ 	lwc1	$f2,0x2e8($s0)
.PF0f01fa84:
/*  f01fa84:	8fad0120 */ 	lw	$t5,0x120($sp)
/*  f01fa88:	4602803c */ 	c.lt.s	$f16,$f2
/*  f01fa8c:	00000000 */ 	nop
/*  f01fa90:	45020026 */ 	bc1fl	.PF0f01fb2c
/*  f01fa94:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01fa98:	8dae0020 */ 	lw	$t6,0x20($t5)
/*  f01fa9c:	c61202ec */ 	lwc1	$f18,0x2ec($s0)
/*  f01faa0:	c5c40074 */ 	lwc1	$f4,0x74($t6)
/*  f01faa4:	46121281 */ 	sub.s	$f10,$f2,$f18
/*  f01faa8:	c61202f0 */ 	lwc1	$f18,0x2f0($s0)
/*  f01faac:	460c2182 */ 	mul.s	$f6,$f4,$f12
/*  f01fab0:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f01fab4:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f01fab8:	46024003 */ 	div.s	$f0,$f8,$f2
/*  f01fabc:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*  f01fac0:	46009182 */ 	mul.s	$f6,$f18,$f0
/*  f01fac4:	46062280 */ 	add.s	$f10,$f4,$f6
/*  f01fac8:	e62a0000 */ 	swc1	$f10,0x0($s1)
/*  f01facc:	c61202f8 */ 	lwc1	$f18,0x2f8($s0)
/*  f01fad0:	46009102 */ 	mul.s	$f4,$f18,$f0
/*  f01fad4:	46044180 */ 	add.s	$f6,$f8,$f4
/*  f01fad8:	e6260008 */ 	swc1	$f6,0x8($s1)
/*  f01fadc:	c61202f4 */ 	lwc1	$f18,0x2f4($s0)
/*  f01fae0:	c7aa00f0 */ 	lwc1	$f10,0xf0($sp)
/*  f01fae4:	8faf0120 */ 	lw	$t7,0x120($sp)
/*  f01fae8:	46009202 */ 	mul.s	$f8,$f18,$f0
/*  f01faec:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f01faf0:	e7a400f0 */ 	swc1	$f4,0xf0($sp)
/*  f01faf4:	8df80020 */ 	lw	$t8,0x20($t7)
/*  f01faf8:	c60602ec */ 	lwc1	$f6,0x2ec($s0)
/*  f01fafc:	c60402e8 */ 	lwc1	$f4,0x2e8($s0)
/*  f01fb00:	c7120074 */ 	lwc1	$f18,0x74($t8)
/*  f01fb04:	46126282 */ 	mul.s	$f10,$f12,$f18
/*  f01fb08:	460a3200 */ 	add.s	$f8,$f6,$f10
/*  f01fb0c:	e60802ec */ 	swc1	$f8,0x2ec($s0)
/*  f01fb10:	c61202ec */ 	lwc1	$f18,0x2ec($s0)
/*  f01fb14:	4612203c */ 	c.lt.s	$f4,$f18
/*  f01fb18:	00000000 */ 	nop
/*  f01fb1c:	45020003 */ 	bc1fl	.PF0f01fb2c
/*  f01fb20:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01fb24:	e61002e8 */ 	swc1	$f16,0x2e8($s0)
.PF0f01fb28:
/*  f01fb28:	c6000304 */ 	lwc1	$f0,0x304($s0)
.PF0f01fb2c:
/*  f01fb2c:	c7a800dc */ 	lwc1	$f8,0xdc($sp)
/*  f01fb30:	46008032 */ 	c.eq.s	$f16,$f0
/*  f01fb34:	00000000 */ 	nop
/*  f01fb38:	45000006 */ 	bc1f	.PF0f01fb54
/*  f01fb3c:	00000000 */ 	nop
/*  f01fb40:	c6060308 */ 	lwc1	$f6,0x308($s0)
/*  f01fb44:	46068032 */ 	c.eq.s	$f16,$f6
/*  f01fb48:	00000000 */ 	nop
/*  f01fb4c:	45030043 */ 	bc1tl	.PF0f01fc5c
/*  f01fb50:	c60600bc */ 	lwc1	$f6,0xbc($s0)
.PF0f01fb54:
/*  f01fb54:	46080102 */ 	mul.s	$f4,$f0,$f8
/*  f01fb58:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f01fb5c:	3c017f1b */ 	lui	$at,0x7f1b
/*  f01fb60:	c42298f4 */ 	lwc1	$f2,-0x670c($at)
/*  f01fb64:	46045480 */ 	add.s	$f18,$f10,$f4
/*  f01fb68:	c6240008 */ 	lwc1	$f4,0x8($s1)
/*  f01fb6c:	e6320000 */ 	swc1	$f18,0x0($s1)
/*  f01fb70:	c6060308 */ 	lwc1	$f6,0x308($s0)
/*  f01fb74:	c7a800dc */ 	lwc1	$f8,0xdc($sp)
/*  f01fb78:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f01fb7c:	460a2480 */ 	add.s	$f18,$f4,$f10
/*  f01fb80:	e6320008 */ 	swc1	$f18,0x8($s1)
/*  f01fb84:	c6060304 */ 	lwc1	$f6,0x304($s0)
/*  f01fb88:	c6040308 */ 	lwc1	$f4,0x308($s0)
/*  f01fb8c:	46023202 */ 	mul.s	$f8,$f6,$f2
/*  f01fb90:	e6080304 */ 	swc1	$f8,0x304($s0)
/*  f01fb94:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01fb98:	46022282 */ 	mul.s	$f10,$f4,$f2
/*  f01fb9c:	46008032 */ 	c.eq.s	$f16,$f0
/*  f01fba0:	00000000 */ 	nop
/*  f01fba4:	45000006 */ 	bc1f	.PF0f01fbc0
/*  f01fba8:	e60a0308 */ 	swc1	$f10,0x308($s0)
/*  f01fbac:	c6120308 */ 	lwc1	$f18,0x308($s0)
/*  f01fbb0:	46128032 */ 	c.eq.s	$f16,$f18
/*  f01fbb4:	00000000 */ 	nop
/*  f01fbb8:	45030028 */ 	bc1tl	.PF0f01fc5c
/*  f01fbbc:	c60600bc */ 	lwc1	$f6,0xbc($s0)
.PF0f01fbc0:
/*  f01fbc0:	c6020308 */ 	lwc1	$f2,0x308($s0)
/*  f01fbc4:	46021182 */ 	mul.s	$f6,$f2,$f2
/*  f01fbc8:	00000000 */ 	nop
/*  f01fbcc:	46000202 */ 	mul.s	$f8,$f0,$f0
/*  f01fbd0:	0c0127b4 */ 	jal	sqrtf
/*  f01fbd4:	46083300 */ 	add.s	$f12,$f6,$f8
/*  f01fbd8:	44808000 */ 	mtc1	$zero,$f16
/*  f01fbdc:	3c08800a */ 	lui	$t0,0x800a
/*  f01fbe0:	2508a510 */ 	addiu	$t0,$t0,-23280
/*  f01fbe4:	4600803c */ 	c.lt.s	$f16,$f0
/*  f01fbe8:	3c017f1b */ 	lui	$at,0x7f1b
/*  f01fbec:	c7aa00dc */ 	lwc1	$f10,0xdc($sp)
/*  f01fbf0:	45020018 */ 	bc1fl	.PF0f01fc54
/*  f01fbf4:	e6100304 */ 	swc1	$f16,0x304($s0)
/*  f01fbf8:	c42498f8 */ 	lwc1	$f4,-0x6708($at)
/*  f01fbfc:	3c013f80 */ 	lui	$at,0x3f80
/*  f01fc00:	44813000 */ 	mtc1	$at,$f6
/*  f01fc04:	460a2482 */ 	mul.s	$f18,$f4,$f10
/*  f01fc08:	46009303 */ 	div.s	$f12,$f18,$f0
/*  f01fc0c:	460c303e */ 	c.le.s	$f6,$f12
/*  f01fc10:	00000000 */ 	nop
/*  f01fc14:	45020005 */ 	bc1fl	.PF0f01fc2c
/*  f01fc18:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01fc1c:	e6100304 */ 	swc1	$f16,0x304($s0)
/*  f01fc20:	1000000d */ 	b	.PF0f01fc58
/*  f01fc24:	e6100308 */ 	swc1	$f16,0x308($s0)
/*  f01fc28:	c6000304 */ 	lwc1	$f0,0x304($s0)
.PF0f01fc2c:
/*  f01fc2c:	c6020308 */ 	lwc1	$f2,0x308($s0)
/*  f01fc30:	460c0202 */ 	mul.s	$f8,$f0,$f12
/*  f01fc34:	00000000 */ 	nop
/*  f01fc38:	460c1282 */ 	mul.s	$f10,$f2,$f12
/*  f01fc3c:	46080101 */ 	sub.s	$f4,$f0,$f8
/*  f01fc40:	460a1481 */ 	sub.s	$f18,$f2,$f10
/*  f01fc44:	e6040304 */ 	swc1	$f4,0x304($s0)
/*  f01fc48:	10000003 */ 	b	.PF0f01fc58
/*  f01fc4c:	e6120308 */ 	swc1	$f18,0x308($s0)
/*  f01fc50:	e6100304 */ 	swc1	$f16,0x304($s0)
.PF0f01fc54:
/*  f01fc54:	e6100308 */ 	swc1	$f16,0x308($s0)
.PF0f01fc58:
/*  f01fc58:	c60600bc */ 	lwc1	$f6,0xbc($s0)
.PF0f01fc5c:
/*  f01fc5c:	c7a800dc */ 	lwc1	$f8,0xdc($sp)
/*  f01fc60:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f01fc64:	24010003 */ 	li	$at,0x3
/*  f01fc68:	46083102 */ 	mul.s	$f4,$f6,$f8
/*  f01fc6c:	46045480 */ 	add.s	$f18,$f10,$f4
/*  f01fc70:	c6240008 */ 	lwc1	$f4,0x8($s1)
/*  f01fc74:	e6320000 */ 	swc1	$f18,0x0($s1)
/*  f01fc78:	c7a800dc */ 	lwc1	$f8,0xdc($sp)
/*  f01fc7c:	c60600c4 */ 	lwc1	$f6,0xc4($s0)
/*  f01fc80:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f01fc84:	460a2480 */ 	add.s	$f18,$f4,$f10
/*  f01fc88:	e6320008 */ 	swc1	$f18,0x8($s1)
/*  f01fc8c:	8faa00f4 */ 	lw	$t2,0xf4($sp)
/*  f01fc90:	55410013 */ 	bnel	$t2,$at,.PF0f01fce0
/*  f01fc94:	820d0007 */ 	lb	$t5,0x7($s0)
/*  f01fc98:	0fc0f072 */ 	jal	chrToEyespy
/*  f01fc9c:	02002025 */ 	move	$a0,$s0
/*  f01fca0:	50400043 */ 	beqzl	$v0,.PF0f01fdb0
/*  f01fca4:	8fac0118 */ 	lw	$t4,0x118($sp)
/*  f01fca8:	90490035 */ 	lbu	$t1,0x35($v0)
/*  f01fcac:	51200040 */ 	beqzl	$t1,.PF0f01fdb0
/*  f01fcb0:	8fac0118 */ 	lw	$t4,0x118($sp)
/*  f01fcb4:	8e0b001c */ 	lw	$t3,0x1c($s0)
/*  f01fcb8:	c5660008 */ 	lwc1	$f6,0x8($t3)
/*  f01fcbc:	e6260000 */ 	swc1	$f6,0x0($s1)
/*  f01fcc0:	8e19001c */ 	lw	$t9,0x1c($s0)
/*  f01fcc4:	c728000c */ 	lwc1	$f8,0xc($t9)
/*  f01fcc8:	e6280004 */ 	swc1	$f8,0x4($s1)
/*  f01fccc:	8e0c001c */ 	lw	$t4,0x1c($s0)
/*  f01fcd0:	c5840010 */ 	lwc1	$f4,0x10($t4)
/*  f01fcd4:	10000035 */ 	b	.PF0f01fdac
/*  f01fcd8:	e6240008 */ 	swc1	$f4,0x8($s1)
/*  f01fcdc:	820d0007 */ 	lb	$t5,0x7($s0)
.PF0f01fce0:
/*  f01fce0:	24010023 */ 	li	$at,0x23
/*  f01fce4:	55a10013 */ 	bnel	$t5,$at,.PF0f01fd34
/*  f01fce8:	8e0a031c */ 	lw	$t2,0x31c($s0)
/*  f01fcec:	920e002c */ 	lbu	$t6,0x2c($s0)
/*  f01fcf0:	24010001 */ 	li	$at,0x1
/*  f01fcf4:	55c1000f */ 	bnel	$t6,$at,.PF0f01fd34
/*  f01fcf8:	8e0a031c */ 	lw	$t2,0x31c($s0)
/*  f01fcfc:	920f002d */ 	lbu	$t7,0x2d($s0)
/*  f01fd00:	55e0000c */ 	bnezl	$t7,.PF0f01fd34
/*  f01fd04:	8e0a031c */ 	lw	$t2,0x31c($s0)
/*  f01fd08:	8d180038 */ 	lw	$t8,0x38($t0)
/*  f01fd0c:	53000009 */ 	beqzl	$t8,.PF0f01fd34
/*  f01fd10:	8e0a031c */ 	lw	$t2,0x31c($s0)
/*  f01fd14:	c60a0040 */ 	lwc1	$f10,0x40($s0)
/*  f01fd18:	e62a0000 */ 	swc1	$f10,0x0($s1)
/*  f01fd1c:	c6120044 */ 	lwc1	$f18,0x44($s0)
/*  f01fd20:	e7b200f0 */ 	swc1	$f18,0xf0($sp)
/*  f01fd24:	c6060048 */ 	lwc1	$f6,0x48($s0)
/*  f01fd28:	10000020 */ 	b	.PF0f01fdac
/*  f01fd2c:	e6260008 */ 	swc1	$f6,0x8($s1)
/*  f01fd30:	8e0a031c */ 	lw	$t2,0x31c($s0)
.PF0f01fd34:
/*  f01fd34:	8fa90124 */ 	lw	$t1,0x124($sp)
/*  f01fd38:	5140001d */ 	beqzl	$t2,.PF0f01fdb0
/*  f01fd3c:	8fac0118 */ 	lw	$t4,0x118($sp)
/*  f01fd40:	c5200000 */ 	lwc1	$f0,0x0($t1)
/*  f01fd44:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f01fd48:	c6240008 */ 	lwc1	$f4,0x8($s1)
/*  f01fd4c:	c52a0008 */ 	lwc1	$f10,0x8($t1)
/*  f01fd50:	46004081 */ 	sub.s	$f2,$f8,$f0
/*  f01fd54:	e6200000 */ 	swc1	$f0,0x0($s1)
/*  f01fd58:	8fab0124 */ 	lw	$t3,0x124($sp)
/*  f01fd5c:	460a2381 */ 	sub.s	$f14,$f4,$f10
/*  f01fd60:	46021182 */ 	mul.s	$f6,$f2,$f2
/*  f01fd64:	c5720008 */ 	lwc1	$f18,0x8($t3)
/*  f01fd68:	460e7202 */ 	mul.s	$f8,$f14,$f14
/*  f01fd6c:	e6320008 */ 	swc1	$f18,0x8($s1)
/*  f01fd70:	0c0127b4 */ 	jal	sqrtf
/*  f01fd74:	46083300 */ 	add.s	$f12,$f6,$f8
/*  f01fd78:	3c0142c8 */ 	lui	$at,0x42c8
/*  f01fd7c:	44816000 */ 	mtc1	$at,$f12
/*  f01fd80:	46000086 */ 	mov.s	$f2,$f0
/*  f01fd84:	c7a400f0 */ 	lwc1	$f4,0xf0($sp)
/*  f01fd88:	4600603c */ 	c.lt.s	$f12,$f0
/*  f01fd8c:	00000000 */ 	nop
/*  f01fd90:	45020003 */ 	bc1fl	.PF0f01fda0
/*  f01fd94:	46022280 */ 	add.s	$f10,$f4,$f2
/*  f01fd98:	46006086 */ 	mov.s	$f2,$f12
/*  f01fd9c:	46022280 */ 	add.s	$f10,$f4,$f2
.PF0f01fda0:
/*  f01fda0:	24190004 */ 	li	$t9,0x4
/*  f01fda4:	e7aa00f0 */ 	swc1	$f10,0xf0($sp)
/*  f01fda8:	a2190191 */ 	sb	$t9,0x191($s0)
.PF0f01fdac:
/*  f01fdac:	8fac0118 */ 	lw	$t4,0x118($sp)
.PF0f01fdb0:
/*  f01fdb0:	24010006 */ 	li	$at,0x6
/*  f01fdb4:	02002025 */ 	move	$a0,$s0
/*  f01fdb8:	918d0000 */ 	lbu	$t5,0x0($t4)
/*  f01fdbc:	02202825 */ 	move	$a1,$s1
/*  f01fdc0:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f01fdc4:	55a10017 */ 	bnel	$t5,$at,.PF0f01fe24
/*  f01fdc8:	8e0a0018 */ 	lw	$t2,0x18($s0)
/*  f01fdcc:	820e0007 */ 	lb	$t6,0x7($s0)
/*  f01fdd0:	24010019 */ 	li	$at,0x19
/*  f01fdd4:	55c10013 */ 	bnel	$t6,$at,.PF0f01fe24
/*  f01fdd8:	8e0a0018 */ 	lw	$t2,0x18($s0)
/*  f01fddc:	c5920008 */ 	lwc1	$f18,0x8($t4)
/*  f01fde0:	27a500fc */ 	addiu	$a1,$sp,0xfc
/*  f01fde4:	e6320000 */ 	swc1	$f18,0x0($s1)
/*  f01fde8:	8faf0118 */ 	lw	$t7,0x118($sp)
/*  f01fdec:	c5e60010 */ 	lwc1	$f6,0x10($t7)
/*  f01fdf0:	e6260008 */ 	swc1	$f6,0x8($s1)
/*  f01fdf4:	8fa40118 */ 	lw	$a0,0x118($sp)
/*  f01fdf8:	24840028 */ 	addiu	$a0,$a0,0x28
/*  f01fdfc:	0fc1968d */ 	jal	roomsCopy
/*  f01fe00:	afa40048 */ 	sw	$a0,0x48($sp)
/*  f01fe04:	3c08800a */ 	lui	$t0,0x800a
/*  f01fe08:	2508a510 */ 	addiu	$t0,$t0,-23280
/*  f01fe0c:	a2000009 */ 	sb	$zero,0x9($s0)
/*  f01fe10:	8d180008 */ 	lw	$t8,0x8($t0)
/*  f01fe14:	44808000 */ 	mtc1	$zero,$f16
/*  f01fe18:	10000013 */ 	b	.PF0f01fe68
/*  f01fe1c:	ae1800d8 */ 	sw	$t8,0xd8($s0)
/*  f01fe20:	8e0a0018 */ 	lw	$t2,0x18($s0)
.PF0f01fe24:
/*  f01fe24:	8fab0124 */ 	lw	$t3,0x124($sp)
/*  f01fe28:	31494000 */ 	andi	$t1,$t2,0x4000
/*  f01fe2c:	11200006 */ 	beqz	$t1,.PF0f01fe48
/*  f01fe30:	00000000 */ 	nop
/*  f01fe34:	c5680000 */ 	lwc1	$f8,0x0($t3)
/*  f01fe38:	e6280000 */ 	swc1	$f8,0x0($s1)
/*  f01fe3c:	8fb90124 */ 	lw	$t9,0x124($sp)
/*  f01fe40:	c7240008 */ 	lwc1	$f4,0x8($t9)
/*  f01fe44:	e6240008 */ 	swc1	$f4,0x8($s1)
.PF0f01fe48:
/*  f01fe48:	0fc07a45 */ 	jal	chrCalculatePushPos
/*  f01fe4c:	24070001 */ 	li	$a3,0x1
/*  f01fe50:	8fad0118 */ 	lw	$t5,0x118($sp)
/*  f01fe54:	3c08800a */ 	lui	$t0,0x800a
/*  f01fe58:	44808000 */ 	mtc1	$zero,$f16
/*  f01fe5c:	25ae0028 */ 	addiu	$t6,$t5,0x28
/*  f01fe60:	afae0048 */ 	sw	$t6,0x48($sp)
/*  f01fe64:	2508a510 */ 	addiu	$t0,$t0,-23280
.PF0f01fe68:
/*  f01fe68:	820c0007 */ 	lb	$t4,0x7($s0)
/*  f01fe6c:	24010023 */ 	li	$at,0x23
/*  f01fe70:	55810021 */ 	bnel	$t4,$at,.PF0f01fef8
/*  f01fe74:	8e0b031c */ 	lw	$t3,0x31c($s0)
/*  f01fe78:	920f002c */ 	lbu	$t7,0x2c($s0)
/*  f01fe7c:	24010001 */ 	li	$at,0x1
/*  f01fe80:	55e1001d */ 	bnel	$t7,$at,.PF0f01fef8
/*  f01fe84:	8e0b031c */ 	lw	$t3,0x31c($s0)
/*  f01fe88:	9218002d */ 	lbu	$t8,0x2d($s0)
/*  f01fe8c:	5700001a */ 	bnezl	$t8,.PF0f01fef8
/*  f01fe90:	8e0b031c */ 	lw	$t3,0x31c($s0)
/*  f01fe94:	8d0a0038 */ 	lw	$t2,0x38($t0)
/*  f01fe98:	02002025 */ 	move	$a0,$s0
/*  f01fe9c:	02202825 */ 	move	$a1,$s1
/*  f01fea0:	11400014 */ 	beqz	$t2,.PF0f01fef4
/*  f01fea4:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f01fea8:	24090001 */ 	li	$t1,0x1
/*  f01feac:	afa90010 */ 	sw	$t1,0x10($sp)
/*  f01feb0:	0fc07ce1 */ 	jal	func0f01f264
/*  f01feb4:	8fa700f0 */ 	lw	$a3,0xf0($sp)
/*  f01feb8:	10400005 */ 	beqz	$v0,.PF0f01fed0
/*  f01febc:	3c017f1b */ 	lui	$at,0x7f1b
/*  f01fec0:	c60a00b4 */ 	lwc1	$f10,0xb4($s0)
/*  f01fec4:	c7b200f0 */ 	lwc1	$f18,0xf0($sp)
/*  f01fec8:	46125180 */ 	add.s	$f6,$f10,$f18
/*  f01fecc:	e60600b4 */ 	swc1	$f6,0xb4($s0)
.PF0f01fed0:
/*  f01fed0:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01fed4:	c42898fc */ 	lwc1	$f8,-0x6704($at)
/*  f01fed8:	e60000b8 */ 	swc1	$f0,0xb8($s0)
/*  f01fedc:	46080102 */ 	mul.s	$f4,$f0,$f8
/*  f01fee0:	e60400b0 */ 	swc1	$f4,0xb0($s0)
/*  f01fee4:	c62a0004 */ 	lwc1	$f10,0x4($s1)
/*  f01fee8:	46005481 */ 	sub.s	$f18,$f10,$f0
/*  f01feec:	1000018f */ 	b	.PF0f02052c
/*  f01fef0:	e6320004 */ 	swc1	$f18,0x4($s1)
.PF0f01fef4:
/*  f01fef4:	8e0b031c */ 	lw	$t3,0x31c($s0)
.PF0f01fef8:
/*  f01fef8:	02002025 */ 	move	$a0,$s0
/*  f01fefc:	8fad00f4 */ 	lw	$t5,0xf4($sp)
/*  f01ff00:	11600016 */ 	beqz	$t3,.PF0f01ff5c
/*  f01ff04:	24010003 */ 	li	$at,0x3
/*  f01ff08:	24190001 */ 	li	$t9,0x1
/*  f01ff0c:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f01ff10:	02202825 */ 	move	$a1,$s1
/*  f01ff14:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f01ff18:	0fc07ce1 */ 	jal	func0f01f264
/*  f01ff1c:	8fa700f0 */ 	lw	$a3,0xf0($sp)
/*  f01ff20:	10400005 */ 	beqz	$v0,.PF0f01ff38
/*  f01ff24:	3c017f1b */ 	lui	$at,0x7f1b
/*  f01ff28:	c60600b4 */ 	lwc1	$f6,0xb4($s0)
/*  f01ff2c:	c7a800f0 */ 	lwc1	$f8,0xf0($sp)
/*  f01ff30:	46083100 */ 	add.s	$f4,$f6,$f8
/*  f01ff34:	e60400b4 */ 	swc1	$f4,0xb4($s0)
.PF0f01ff38:
/*  f01ff38:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01ff3c:	c42a9900 */ 	lwc1	$f10,-0x6700($at)
/*  f01ff40:	e60000b8 */ 	swc1	$f0,0xb8($s0)
/*  f01ff44:	460a0482 */ 	mul.s	$f18,$f0,$f10
/*  f01ff48:	e61200b0 */ 	swc1	$f18,0xb0($s0)
/*  f01ff4c:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*  f01ff50:	46003201 */ 	sub.s	$f8,$f6,$f0
/*  f01ff54:	10000175 */ 	b	.PF0f02052c
/*  f01ff58:	e6280004 */ 	swc1	$f8,0x4($s1)
.PF0f01ff5c:
/*  f01ff5c:	15a10003 */ 	bne	$t5,$at,.PF0f01ff6c
/*  f01ff60:	8fae0118 */ 	lw	$t6,0x118($sp)
/*  f01ff64:	10000093 */ 	b	.PF0f0201b4
/*  f01ff68:	c60200b4 */ 	lwc1	$f2,0xb4($s0)
.PF0f01ff6c:
/*  f01ff6c:	91cc0000 */ 	lbu	$t4,0x0($t6)
/*  f01ff70:	24010006 */ 	li	$at,0x6
/*  f01ff74:	c7aa00f8 */ 	lwc1	$f10,0xf8($sp)
/*  f01ff78:	55810010 */ 	bnel	$t4,$at,.PF0f01ffbc
/*  f01ff7c:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*  f01ff80:	0fc4a513 */ 	jal	propGetPlayerNum
/*  f01ff84:	01c02025 */ 	move	$a0,$t6
/*  f01ff88:	3c08800a */ 	lui	$t0,0x800a
/*  f01ff8c:	2508a510 */ 	addiu	$t0,$t0,-23280
/*  f01ff90:	00027880 */ 	sll	$t7,$v0,0x2
/*  f01ff94:	010fc021 */ 	addu	$t8,$t0,$t7
/*  f01ff98:	8f030064 */ 	lw	$v1,0x64($t8)
/*  f01ff9c:	44808000 */ 	mtc1	$zero,$f16
/*  f01ffa0:	946a161a */ 	lhu	$t2,0x161a($v1)
/*  f01ffa4:	c4620074 */ 	lwc1	$f2,0x74($v1)
/*  f01ffa8:	a60a018a */ 	sh	$t2,0x18a($s0)
/*  f01ffac:	9069161e */ 	lbu	$t1,0x161e($v1)
/*  f01ffb0:	10000080 */ 	b	.PF0f0201b4
/*  f01ffb4:	a2090191 */ 	sb	$t1,0x191($s0)
/*  f01ffb8:	c6240004 */ 	lwc1	$f4,0x4($s1)
.PF0f01ffbc:
/*  f01ffbc:	3c01428a */ 	lui	$at,0x428a
/*  f01ffc0:	44810000 */ 	mtc1	$at,$f0
/*  f01ffc4:	460a2481 */ 	sub.s	$f18,$f4,$f10
/*  f01ffc8:	27a60088 */ 	addiu	$a2,$sp,0x88
/*  f01ffcc:	27a70078 */ 	addiu	$a3,$sp,0x78
/*  f01ffd0:	27ab00fc */ 	addiu	$t3,$sp,0xfc
/*  f01ffd4:	4600903c */ 	c.lt.s	$f18,$f0
/*  f01ffd8:	00000000 */ 	nop
/*  f01ffdc:	45020013 */ 	bc1fl	.PF0f02002c
/*  f01ffe0:	afb10098 */ 	sw	$s1,0x98($sp)
/*  f01ffe4:	46005200 */ 	add.s	$f8,$f10,$f0
/*  f01ffe8:	afa60098 */ 	sw	$a2,0x98($sp)
/*  f01ffec:	afa70094 */ 	sw	$a3,0x94($sp)
/*  f01fff0:	c6260000 */ 	lwc1	$f6,0x0($s1)
/*  f01fff4:	e7a8008c */ 	swc1	$f8,0x8c($sp)
/*  f01fff8:	02202025 */ 	move	$a0,$s1
/*  f01fffc:	e7a60088 */ 	swc1	$f6,0x88($sp)
/*  f020000:	c6240008 */ 	lwc1	$f4,0x8($s1)
/*  f020004:	27a500fc */ 	addiu	$a1,$sp,0xfc
/*  f020008:	0fc19841 */ 	jal	func0f065e74
/*  f02000c:	e7a40090 */ 	swc1	$f4,0x90($sp)
/*  f020010:	02002025 */ 	move	$a0,$s0
/*  f020014:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f020018:	0fc08839 */ 	jal	func0f021fa8
/*  f02001c:	27a60078 */ 	addiu	$a2,$sp,0x78
/*  f020020:	10000004 */ 	b	.PF0f020034
/*  f020024:	8e050024 */ 	lw	$a1,0x24($s0)
/*  f020028:	afb10098 */ 	sw	$s1,0x98($sp)
.PF0f02002c:
/*  f02002c:	afab0094 */ 	sw	$t3,0x94($sp)
/*  f020030:	8e050024 */ 	lw	$a1,0x24($s0)
.PF0f020034:
/*  f020034:	2607018a */ 	addiu	$a3,$s0,0x18a
/*  f020038:	26020191 */ 	addiu	$v0,$s0,0x191
/*  f02003c:	27b900ea */ 	addiu	$t9,$sp,0xea
/*  f020040:	260302b2 */ 	addiu	$v1,$s0,0x2b2
/*  f020044:	27ad00ec */ 	addiu	$t5,$sp,0xec
/*  f020048:	27ac0114 */ 	addiu	$t4,$sp,0x114
/*  f02004c:	afac0020 */ 	sw	$t4,0x20($sp)
/*  f020050:	afad001c */ 	sw	$t5,0x1c($sp)
/*  f020054:	afa30018 */ 	sw	$v1,0x18($sp)
/*  f020058:	afa30040 */ 	sw	$v1,0x40($sp)
/*  f02005c:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f020060:	afa20010 */ 	sw	$v0,0x10($sp)
/*  f020064:	afa20044 */ 	sw	$v0,0x44($sp)
/*  f020068:	afa7004c */ 	sw	$a3,0x4c($sp)
/*  f02006c:	8fa40098 */ 	lw	$a0,0x98($sp)
/*  f020070:	0c00a6ac */ 	jal	cdFindGroundY
/*  f020074:	8fa60094 */ 	lw	$a2,0x94($sp)
/*  f020078:	8e0202d4 */ 	lw	$v0,0x2d4($s0)
/*  f02007c:	3c08800a */ 	lui	$t0,0x800a
/*  f020080:	44808000 */ 	mtc1	$zero,$f16
/*  f020084:	2508a510 */ 	addiu	$t0,$t0,-23280
/*  f020088:	10400036 */ 	beqz	$v0,.PF0f020164
/*  f02008c:	46000086 */ 	mov.s	$f2,$f0
/*  f020090:	904e0078 */ 	lbu	$t6,0x78($v0)
/*  f020094:	3c017f1b */ 	lui	$at,0x7f1b
/*  f020098:	55c00033 */ 	bnezl	$t6,.PF0f020168
/*  f02009c:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f0200a0:	c42c9904 */ 	lwc1	$f12,-0x66fc($at)
/*  f0200a4:	460c003c */ 	c.lt.s	$f0,$f12
/*  f0200a8:	00000000 */ 	nop
/*  f0200ac:	4502002e */ 	bc1fl	.PF0f020168
/*  f0200b0:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f0200b4:	8d0f0038 */ 	lw	$t7,0x38($t0)
/*  f0200b8:	29e10005 */ 	slti	$at,$t7,0x5
/*  f0200bc:	5420002a */ 	bnezl	$at,.PF0f020168
/*  f0200c0:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f0200c4:	8e18001c */ 	lw	$t8,0x1c($s0)
/*  f0200c8:	240b000a */ 	li	$t3,0xa
/*  f0200cc:	930a0001 */ 	lbu	$t2,0x1($t8)
/*  f0200d0:	31490080 */ 	andi	$t1,$t2,0x80
/*  f0200d4:	55200024 */ 	bnezl	$t1,.PF0f020168
/*  f0200d8:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f0200dc:	a04b0078 */ 	sb	$t3,0x78($v0)
/*  f0200e0:	8fb90118 */ 	lw	$t9,0x118($sp)
/*  f0200e4:	27a500fc */ 	addiu	$a1,$sp,0xfc
/*  f0200e8:	c7320008 */ 	lwc1	$f18,0x8($t9)
/*  f0200ec:	e6320000 */ 	swc1	$f18,0x0($s1)
/*  f0200f0:	8fad0118 */ 	lw	$t5,0x118($sp)
/*  f0200f4:	c5a6000c */ 	lwc1	$f6,0xc($t5)
/*  f0200f8:	e6260004 */ 	swc1	$f6,0x4($s1)
/*  f0200fc:	8fac0118 */ 	lw	$t4,0x118($sp)
/*  f020100:	c58a0010 */ 	lwc1	$f10,0x10($t4)
/*  f020104:	e62a0008 */ 	swc1	$f10,0x8($s1)
/*  f020108:	0fc1968d */ 	jal	roomsCopy
/*  f02010c:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f020110:	44808000 */ 	mtc1	$zero,$f16
/*  f020114:	8fae0044 */ 	lw	$t6,0x44($sp)
/*  f020118:	8fb80040 */ 	lw	$t8,0x40($sp)
/*  f02011c:	e7b000dc */ 	swc1	$f16,0xdc($sp)
/*  f020120:	8e050024 */ 	lw	$a1,0x24($s0)
/*  f020124:	27af00ea */ 	addiu	$t7,$sp,0xea
/*  f020128:	27aa00ec */ 	addiu	$t2,$sp,0xec
/*  f02012c:	27a90114 */ 	addiu	$t1,$sp,0x114
/*  f020130:	afa90020 */ 	sw	$t1,0x20($sp)
/*  f020134:	afaa001c */ 	sw	$t2,0x1c($sp)
/*  f020138:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f02013c:	02202025 */ 	move	$a0,$s1
/*  f020140:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f020144:	8fa7004c */ 	lw	$a3,0x4c($sp)
/*  f020148:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f02014c:	0c00a6ac */ 	jal	cdFindGroundY
/*  f020150:	afb80018 */ 	sw	$t8,0x18($sp)
/*  f020154:	3c08800a */ 	lui	$t0,0x800a
/*  f020158:	44808000 */ 	mtc1	$zero,$f16
/*  f02015c:	2508a510 */ 	addiu	$t0,$t0,-23280
/*  f020160:	46000086 */ 	mov.s	$f2,$f0
.PF0f020164:
/*  f020164:	8fab00ec */ 	lw	$t3,0xec($sp)
.PF0f020168:
/*  f020168:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02016c:	c42c9908 */ 	lwc1	$f12,-0x66f8($at)
/*  f020170:	51600008 */ 	beqzl	$t3,.PF0f020194
/*  f020174:	920f032d */ 	lbu	$t7,0x32d($s0)
/*  f020178:	920d032d */ 	lbu	$t5,0x32d($s0)
/*  f02017c:	35ac0080 */ 	ori	$t4,$t5,0x80
/*  f020180:	a20c032d */ 	sb	$t4,0x32d($s0)
/*  f020184:	8fae0114 */ 	lw	$t6,0x114($sp)
/*  f020188:	10000005 */ 	b	.PF0f0201a0
/*  f02018c:	ae0e0364 */ 	sw	$t6,0x364($s0)
/*  f020190:	920f032d */ 	lbu	$t7,0x32d($s0)
.PF0f020194:
/*  f020194:	ae000364 */ 	sw	$zero,0x364($s0)
/*  f020198:	31f8ff7f */ 	andi	$t8,$t7,0xff7f
/*  f02019c:	a218032d */ 	sb	$t8,0x32d($s0)
.PF0f0201a0:
/*  f0201a0:	460c003c */ 	c.lt.s	$f0,$f12
/*  f0201a4:	00000000 */ 	nop
/*  f0201a8:	45020003 */ 	bc1fl	.PF0f0201b8
/*  f0201ac:	8e0a0018 */ 	lw	$t2,0x18($s0)
/*  f0201b0:	46006086 */ 	mov.s	$f2,$f12
.PF0f0201b4:
/*  f0201b4:	8e0a0018 */ 	lw	$t2,0x18($s0)
.PF0f0201b8:
/*  f0201b8:	e60200b8 */ 	swc1	$f2,0xb8($s0)
/*  f0201bc:	c7a800f0 */ 	lwc1	$f8,0xf0($sp)
/*  f0201c0:	31490001 */ 	andi	$t1,$t2,0x1
/*  f0201c4:	51200020 */ 	beqzl	$t1,.PF0f020248
/*  f0201c8:	c60c00c0 */ 	lwc1	$f12,0xc0($s0)
/*  f0201cc:	c60400b8 */ 	lwc1	$f4,0xb8($s0)
/*  f0201d0:	c7a600f8 */ 	lwc1	$f6,0xf8($sp)
/*  f0201d4:	8fab0120 */ 	lw	$t3,0x120($sp)
/*  f0201d8:	46044480 */ 	add.s	$f18,$f8,$f4
/*  f0201dc:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*  f0201e0:	8d790008 */ 	lw	$t9,0x8($t3)
/*  f0201e4:	2401fffe */ 	li	$at,-2
/*  f0201e8:	46069281 */ 	sub.s	$f10,$f18,$f6
/*  f0201ec:	8f250000 */ 	lw	$a1,0x0($t9)
/*  f0201f0:	460a4100 */ 	add.s	$f4,$f8,$f10
/*  f0201f4:	94a20000 */ 	lhu	$v0,0x0($a1)
/*  f0201f8:	e6240004 */ 	swc1	$f4,0x4($s1)
/*  f0201fc:	8e0c0018 */ 	lw	$t4,0x18($s0)
/*  f020200:	c60200b8 */ 	lwc1	$f2,0xb8($s0)
/*  f020204:	304d00ff */ 	andi	$t5,$v0,0xff
/*  f020208:	01817024 */ 	and	$t6,$t4,$at
/*  f02020c:	ae0e0018 */ 	sw	$t6,0x18($s0)
/*  f020210:	3c017f1b */ 	lui	$at,0x7f1b
/*  f020214:	e60200b4 */ 	swc1	$f2,0xb4($s0)
/*  f020218:	c432990c */ 	lwc1	$f18,-0x66f4($at)
/*  f02021c:	24010001 */ 	li	$at,0x1
/*  f020220:	46121182 */ 	mul.s	$f6,$f2,$f18
/*  f020224:	15a10005 */ 	bne	$t5,$at,.PF0f02023c
/*  f020228:	e60600b0 */ 	swc1	$f6,0xb0($s0)
/*  f02022c:	0c0069eb */ 	jal	modelGetNodeRwData
/*  f020230:	8fa40120 */ 	lw	$a0,0x120($sp)
/*  f020234:	c4480028 */ 	lwc1	$f8,0x28($v0)
/*  f020238:	e4480038 */ 	swc1	$f8,0x38($v0)
.PF0f02023c:
/*  f02023c:	100000b8 */ 	b	.PF0f020520
/*  f020240:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020244:	c60c00c0 */ 	lwc1	$f12,0xc0($s0)
.PF0f020248:
/*  f020248:	8faf0118 */ 	lw	$t7,0x118($sp)
/*  f02024c:	27a400f0 */ 	addiu	$a0,$sp,0xf0
/*  f020250:	460c8032 */ 	c.eq.s	$f16,$f12
/*  f020254:	27a50068 */ 	addiu	$a1,$sp,0x68
/*  f020258:	45020008 */ 	bc1fl	.PF0f02027c
/*  f02025c:	91f80000 */ 	lbu	$t8,0x0($t7)
/*  f020260:	c60200b8 */ 	lwc1	$f2,0xb8($s0)
/*  f020264:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020268:	4600103c */ 	c.lt.s	$f2,$f0
/*  f02026c:	00000000 */ 	nop
/*  f020270:	4502004a */ 	bc1fl	.PF0f02039c
/*  f020274:	4602003e */ 	c.le.s	$f0,$f2
/*  f020278:	91f80000 */ 	lbu	$t8,0x0($t7)
.PF0f02027c:
/*  f02027c:	24010003 */ 	li	$at,0x3
/*  f020280:	00001825 */ 	move	$v1,$zero
/*  f020284:	17010008 */ 	bne	$t8,$at,.PF0f0202a8
/*  f020288:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02028c:	c42a9910 */ 	lwc1	$f10,-0x66f0($at)
/*  f020290:	c60400b4 */ 	lwc1	$f4,0xb4($s0)
/*  f020294:	460a203e */ 	c.le.s	$f4,$f10
/*  f020298:	00000000 */ 	nop
/*  f02029c:	45020003 */ 	bc1fl	.PF0f0202ac
/*  f0202a0:	e7ac0068 */ 	swc1	$f12,0x68($sp)
/*  f0202a4:	24030001 */ 	li	$v1,0x1
.PF0f0202a8:
/*  f0202a8:	e7ac0068 */ 	swc1	$f12,0x68($sp)
.PF0f0202ac:
/*  f0202ac:	8fa600dc */ 	lw	$a2,0xdc($sp)
/*  f0202b0:	0fc25941 */ 	jal	func0f0965e4
/*  f0202b4:	a3a30067 */ 	sb	$v1,0x67($sp)
/*  f0202b8:	02002025 */ 	move	$a0,$s0
/*  f0202bc:	02202825 */ 	move	$a1,$s1
/*  f0202c0:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f0202c4:	8fa700f0 */ 	lw	$a3,0xf0($sp)
/*  f0202c8:	0fc07ce1 */ 	jal	func0f01f264
/*  f0202cc:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f0202d0:	44808000 */ 	mtc1	$zero,$f16
/*  f0202d4:	10400007 */ 	beqz	$v0,.PF0f0202f4
/*  f0202d8:	93a30067 */ 	lbu	$v1,0x67($sp)
/*  f0202dc:	c61200b4 */ 	lwc1	$f18,0xb4($s0)
/*  f0202e0:	c7a600f0 */ 	lwc1	$f6,0xf0($sp)
/*  f0202e4:	46069200 */ 	add.s	$f8,$f18,$f6
/*  f0202e8:	e60800b4 */ 	swc1	$f8,0xb4($s0)
/*  f0202ec:	c7aa0068 */ 	lwc1	$f10,0x68($sp)
/*  f0202f0:	e60a00c0 */ 	swc1	$f10,0xc0($s0)
.PF0f0202f4:
/*  f0202f4:	c60200b8 */ 	lwc1	$f2,0xb8($s0)
/*  f0202f8:	c60400b4 */ 	lwc1	$f4,0xb4($s0)
/*  f0202fc:	3c017f1b */ 	lui	$at,0x7f1b
/*  f020300:	4602203e */ 	c.le.s	$f4,$f2
/*  f020304:	00000000 */ 	nop
/*  f020308:	4500000b */ 	bc1f	.PF0f020338
/*  f02030c:	00000000 */ 	nop
/*  f020310:	e60200b4 */ 	swc1	$f2,0xb4($s0)
/*  f020314:	c4329914 */ 	lwc1	$f18,-0x66ec($at)
/*  f020318:	e61000c0 */ 	swc1	$f16,0xc0($s0)
/*  f02031c:	46121182 */ 	mul.s	$f6,$f2,$f18
/*  f020320:	e60600b0 */ 	swc1	$f6,0xb0($s0)
/*  f020324:	97aa00ea */ 	lhu	$t2,0xea($sp)
/*  f020328:	31494000 */ 	andi	$t1,$t2,0x4000
/*  f02032c:	11200002 */ 	beqz	$t1,.PF0f020338
/*  f020330:	00000000 */ 	nop
/*  f020334:	24030001 */ 	li	$v1,0x1
.PF0f020338:
/*  f020338:	5060005b */ 	beqzl	$v1,.PF0f0204a8
/*  f02033c:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020340:	8e0b02d4 */ 	lw	$t3,0x2d4($s0)
/*  f020344:	51600011 */ 	beqzl	$t3,.PF0f02038c
/*  f020348:	8e0d0014 */ 	lw	$t5,0x14($s0)
/*  f02034c:	860200ec */ 	lh	$v0,0xec($s0)
/*  f020350:	04400006 */ 	bltz	$v0,.PF0f02036c
/*  f020354:	00000000 */ 	nop
/*  f020358:	861900ee */ 	lh	$t9,0xee($s0)
/*  f02035c:	1b200003 */ 	blez	$t9,.PF0f02036c
/*  f020360:	00000000 */ 	nop
/*  f020364:	10000004 */ 	b	.PF0f020378
/*  f020368:	00402825 */ 	move	$a1,$v0
.PF0f02036c:
/*  f02036c:	0fc63831 */ 	jal	mpPlayerGetIndex
/*  f020370:	02002025 */ 	move	$a0,$s0
/*  f020374:	00402825 */ 	move	$a1,$v0
.PF0f020378:
/*  f020378:	0fc0d930 */ 	jal	chrDie
/*  f02037c:	02002025 */ 	move	$a0,$s0
/*  f020380:	10000049 */ 	b	.PF0f0204a8
/*  f020384:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020388:	8e0d0014 */ 	lw	$t5,0x14($s0)
.PF0f02038c:
/*  f02038c:	35ac0020 */ 	ori	$t4,$t5,0x20
/*  f020390:	10000044 */ 	b	.PF0f0204a4
/*  f020394:	ae0c0014 */ 	sw	$t4,0x14($s0)
/*  f020398:	4602003e */ 	c.le.s	$f0,$f2
.PF0f02039c:
/*  f02039c:	00000000 */ 	nop
/*  f0203a0:	45020041 */ 	bc1fl	.PF0f0204a8
/*  f0203a4:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f0203a8:	8d0e0038 */ 	lw	$t6,0x38($t0)
/*  f0203ac:	00001025 */ 	move	$v0,$zero
/*  f0203b0:	3c017f1b */ 	lui	$at,0x7f1b
/*  f0203b4:	19c00011 */ 	blez	$t6,.PF0f0203fc
/*  f0203b8:	00000000 */ 	nop
/*  f0203bc:	c4209918 */ 	lwc1	$f0,-0x66e8($at)
/*  f0203c0:	c60800b0 */ 	lwc1	$f8,0xb0($s0)
.PF0f0203c4:
/*  f0203c4:	c61200bc */ 	lwc1	$f18,0xbc($s0)
/*  f0203c8:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f0203cc:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f0203d0:	c60800c4 */ 	lwc1	$f8,0xc4($s0)
/*  f0203d4:	46009182 */ 	mul.s	$f6,$f18,$f0
/*  f0203d8:	46025100 */ 	add.s	$f4,$f10,$f2
/*  f0203dc:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f0203e0:	e60600bc */ 	swc1	$f6,0xbc($s0)
/*  f0203e4:	e60400b0 */ 	swc1	$f4,0xb0($s0)
/*  f0203e8:	e60a00c4 */ 	swc1	$f10,0xc4($s0)
/*  f0203ec:	8d0f0038 */ 	lw	$t7,0x38($t0)
/*  f0203f0:	004f082a */ 	slt	$at,$v0,$t7
/*  f0203f4:	5420fff3 */ 	bnezl	$at,.PF0f0203c4
/*  f0203f8:	c60800b0 */ 	lwc1	$f8,0xb0($s0)
.PF0f0203fc:
/*  f0203fc:	3c017f1b */ 	lui	$at,0x7f1b
/*  f020400:	c432991c */ 	lwc1	$f18,-0x66e4($at)
/*  f020404:	c60400b0 */ 	lwc1	$f4,0xb0($s0)
/*  f020408:	3c0141f0 */ 	lui	$at,0x41f0
/*  f02040c:	44813000 */ 	mtc1	$at,$f6
/*  f020410:	46122002 */ 	mul.s	$f0,$f4,$f18
/*  f020414:	3c017f1b */ 	lui	$at,0x7f1b
/*  f020418:	46061301 */ 	sub.s	$f12,$f2,$f6
/*  f02041c:	460c003c */ 	c.lt.s	$f0,$f12
/*  f020420:	e60000b4 */ 	swc1	$f0,0xb4($s0)
/*  f020424:	45000005 */ 	bc1f	.PF0f02043c
/*  f020428:	00000000 */ 	nop
/*  f02042c:	e60c00b4 */ 	swc1	$f12,0xb4($s0)
/*  f020430:	c4289920 */ 	lwc1	$f8,-0x66e0($at)
/*  f020434:	46086282 */ 	mul.s	$f10,$f12,$f8
/*  f020438:	e60a00b0 */ 	swc1	$f10,0xb0($s0)
.PF0f02043c:
/*  f02043c:	3c017f1b */ 	lui	$at,0x7f1b
/*  f020440:	c4249924 */ 	lwc1	$f4,-0x66dc($at)
/*  f020444:	c60000bc */ 	lwc1	$f0,0xbc($s0)
/*  f020448:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02044c:	4604003c */ 	c.lt.s	$f0,$f4
/*  f020450:	00000000 */ 	nop
/*  f020454:	45020014 */ 	bc1fl	.PF0f0204a8
/*  f020458:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f02045c:	c4229928 */ 	lwc1	$f2,-0x66d8($at)
/*  f020460:	3c017f1b */ 	lui	$at,0x7f1b
/*  f020464:	4600103c */ 	c.lt.s	$f2,$f0
/*  f020468:	00000000 */ 	nop
/*  f02046c:	4502000e */ 	bc1fl	.PF0f0204a8
/*  f020470:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020474:	c60000c4 */ 	lwc1	$f0,0xc4($s0)
/*  f020478:	c432992c */ 	lwc1	$f18,-0x66d4($at)
/*  f02047c:	4612003c */ 	c.lt.s	$f0,$f18
/*  f020480:	00000000 */ 	nop
/*  f020484:	45020008 */ 	bc1fl	.PF0f0204a8
/*  f020488:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f02048c:	4600103c */ 	c.lt.s	$f2,$f0
/*  f020490:	00000000 */ 	nop
/*  f020494:	45020004 */ 	bc1fl	.PF0f0204a8
/*  f020498:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f02049c:	e61000c4 */ 	swc1	$f16,0xc4($s0)
/*  f0204a0:	e61000bc */ 	swc1	$f16,0xbc($s0)
.PF0f0204a4:
/*  f0204a4:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
.PF0f0204a8:
/*  f0204a8:	c7a600f8 */ 	lwc1	$f6,0xf8($sp)
/*  f0204ac:	46003032 */ 	c.eq.s	$f6,$f0
/*  f0204b0:	00000000 */ 	nop
/*  f0204b4:	4503001b */ 	bc1tl	.PF0f020524
/*  f0204b8:	c6320004 */ 	lwc1	$f18,0x4($s1)
/*  f0204bc:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f0204c0:	27a400fc */ 	addiu	$a0,$sp,0xfc
/*  f0204c4:	27a500c0 */ 	addiu	$a1,$sp,0xc0
/*  f0204c8:	e7a800d0 */ 	swc1	$f8,0xd0($sp)
/*  f0204cc:	c62a0004 */ 	lwc1	$f10,0x4($s1)
/*  f0204d0:	e7aa00d4 */ 	swc1	$f10,0xd4($sp)
/*  f0204d4:	c6240008 */ 	lwc1	$f4,0x8($s1)
/*  f0204d8:	0fc1968d */ 	jal	roomsCopy
/*  f0204dc:	e7a400d8 */ 	swc1	$f4,0xd8($sp)
/*  f0204e0:	c61200b4 */ 	lwc1	$f18,0xb4($s0)
/*  f0204e4:	c7a600f8 */ 	lwc1	$f6,0xf8($sp)
/*  f0204e8:	c62a0004 */ 	lwc1	$f10,0x4($s1)
/*  f0204ec:	27a400d0 */ 	addiu	$a0,$sp,0xd0
/*  f0204f0:	46069201 */ 	sub.s	$f8,$f18,$f6
/*  f0204f4:	27a500c0 */ 	addiu	$a1,$sp,0xc0
/*  f0204f8:	02203025 */ 	move	$a2,$s1
/*  f0204fc:	27a700fc */ 	addiu	$a3,$sp,0xfc
/*  f020500:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f020504:	0fc19841 */ 	jal	func0f065e74
/*  f020508:	e6240004 */ 	swc1	$f4,0x4($s1)
/*  f02050c:	02002025 */ 	move	$a0,$s0
/*  f020510:	02202825 */ 	move	$a1,$s1
/*  f020514:	0fc08839 */ 	jal	func0f021fa8
/*  f020518:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f02051c:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
.PF0f020520:
/*  f020520:	c6320004 */ 	lwc1	$f18,0x4($s1)
.PF0f020524:
/*  f020524:	46009181 */ 	sub.s	$f6,$f18,$f0
/*  f020528:	e6260004 */ 	swc1	$f6,0x4($s1)
.PF0f02052c:
/*  f02052c:	c60a00b4 */ 	lwc1	$f10,0xb4($s0)
/*  f020530:	8fb8012c */ 	lw	$t8,0x12c($sp)
/*  f020534:	8fa40118 */ 	lw	$a0,0x118($sp)
/*  f020538:	24010023 */ 	li	$at,0x23
/*  f02053c:	e70a0000 */ 	swc1	$f10,0x0($t8)
/*  f020540:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f020544:	e4880008 */ 	swc1	$f8,0x8($a0)
/*  f020548:	c61200b4 */ 	lwc1	$f18,0xb4($s0)
/*  f02054c:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*  f020550:	46122180 */ 	add.s	$f6,$f4,$f18
/*  f020554:	e486000c */ 	swc1	$f6,0xc($a0)
/*  f020558:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*  f02055c:	e48a0010 */ 	swc1	$f10,0x10($a0)
/*  f020560:	820a0007 */ 	lb	$t2,0x7($s0)
/*  f020564:	1541000c */ 	bne	$t2,$at,.PF0f020598
/*  f020568:	00000000 */ 	nop
/*  f02056c:	c6020050 */ 	lwc1	$f2,0x50($s0)
/*  f020570:	c488000c */ 	lwc1	$f8,0xc($a0)
/*  f020574:	4602403c */ 	c.lt.s	$f8,$f2
/*  f020578:	00000000 */ 	nop
/*  f02057c:	45000006 */ 	bc1f	.PF0f020598
/*  f020580:	00000000 */ 	nop
/*  f020584:	e482000c */ 	swc1	$f2,0xc($a0)
/*  f020588:	c6000050 */ 	lwc1	$f0,0x50($s0)
/*  f02058c:	e60000b4 */ 	swc1	$f0,0xb4($s0)
/*  f020590:	8fa9012c */ 	lw	$t1,0x12c($sp)
/*  f020594:	e5200000 */ 	swc1	$f0,0x0($t1)
.PF0f020598:
/*  f020598:	0fc197b5 */ 	jal	propDeregisterRooms
/*  f02059c:	00000000 */ 	nop
/*  f0205a0:	27a400fc */ 	addiu	$a0,$sp,0xfc
/*  f0205a4:	0fc1968d */ 	jal	roomsCopy
/*  f0205a8:	8fa50048 */ 	lw	$a1,0x48($sp)
/*  f0205ac:	8fa60118 */ 	lw	$a2,0x118($sp)
/*  f0205b0:	24010003 */ 	li	$at,0x3
/*  f0205b4:	90cb0000 */ 	lbu	$t3,0x0($a2)
/*  f0205b8:	15610016 */ 	bne	$t3,$at,.PF0f020614
/*  f0205bc:	00000000 */ 	nop
/*  f0205c0:	84d90028 */ 	lh	$t9,0x28($a2)
/*  f0205c4:	2405ffff */ 	li	$a1,-1
/*  f0205c8:	00c01025 */ 	move	$v0,$a2
/*  f0205cc:	10b90011 */ 	beq	$a1,$t9,.PF0f020614
/*  f0205d0:	00000000 */ 	nop
/*  f0205d4:	860402b2 */ 	lh	$a0,0x2b2($s0)
/*  f0205d8:	84c30028 */ 	lh	$v1,0x28($a2)
.PF0f0205dc:
/*  f0205dc:	5483000a */ 	bnel	$a0,$v1,.PF0f020608
/*  f0205e0:	8443002a */ 	lh	$v1,0x2a($v0)
/*  f0205e4:	0fc197b5 */ 	jal	propDeregisterRooms
/*  f0205e8:	00c02025 */ 	move	$a0,$a2
/*  f0205ec:	8fac0118 */ 	lw	$t4,0x118($sp)
/*  f0205f0:	860d02b2 */ 	lh	$t5,0x2b2($s0)
/*  f0205f4:	2405ffff */ 	li	$a1,-1
/*  f0205f8:	a585002a */ 	sh	$a1,0x2a($t4)
/*  f0205fc:	10000005 */ 	b	.PF0f020614
/*  f020600:	a58d0028 */ 	sh	$t5,0x28($t4)
/*  f020604:	8443002a */ 	lh	$v1,0x2a($v0)
.PF0f020608:
/*  f020608:	24420002 */ 	addiu	$v0,$v0,0x2
/*  f02060c:	14a3fff3 */ 	bne	$a1,$v1,.PF0f0205dc
/*  f020610:	00000000 */ 	nop
.PF0f020614:
/*  f020614:	0fc0887a */ 	jal	func0f0220ac
/*  f020618:	02002025 */ 	move	$a0,$s0
/*  f02061c:	8fa40118 */ 	lw	$a0,0x118($sp)
/*  f020620:	260500fc */ 	addiu	$a1,$s0,0xfc
/*  f020624:	0fc1a4f3 */ 	jal	func0f069144
/*  f020628:	9606018a */ 	lhu	$a2,0x18a($s0)
/*  f02062c:	8fbf0034 */ 	lw	$ra,0x34($sp)
/*  f020630:	8fb0002c */ 	lw	$s0,0x2c($sp)
/*  f020634:	8fb10030 */ 	lw	$s1,0x30($sp)
/*  f020638:	27bd0120 */ 	addiu	$sp,$sp,0x120
/*  f02063c:	03e00008 */ 	jr	$ra
/*  f020640:	24020001 */ 	li	$v0,0x1
);
#elif VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func0f01f378
.late_rodata
glabel var7f1a86ac
.word 0xc9742400
glabel var7f1a86b0
.word 0x411ffffe
glabel var7f1a86b4
.word 0x3f8ccccd
glabel var7f1a86b8
.word 0x3f8ccccd
glabel var7f1a86bc
.word 0x3f666666
glabel var7f1a86c0
.word 0x3f666666
glabel var7f1a86c4
.word 0x3dcccccd
glabel var7f1a86c8
.word 0x3f666666
glabel var7f1a86cc
.word 0x3f666666
glabel var7f1a86d0
.word 0x3f666666
glabel var7f1a86d4
.word 0x3f666666
glabel var7f1a86d8
.word 0x3f666666
glabel var7f1a86dc
.word 0x411ffffe
glabel var7f1a86e0
.word 0x411ffffe
glabel var7f1a86e4
.word 0x3f666666
glabel var7f1a86e8
.word 0x3f666666
glabel var7f1a86ec
.word 0x3f666666
glabel var7f1a86f0
.word 0x3f666666
glabel var7f1a86f4
.word 0xc7c35000
glabel var7f1a86f8
.word 0x3f666666
glabel var7f1a86fc
.word 0x3f666666
glabel var7f1a8700
.word 0xc7c35000
glabel var7f1a8704
.word 0x411ffffe
glabel var7f1a8708
.word 0xc6ea6000
glabel var7f1a870c
.word 0x411ffffe
glabel var7f1a8710
.word 0x3dccccd0
glabel var7f1a8714
.word 0x411ffffe
glabel var7f1a8718
.word 0x3dcccccd
glabel var7f1a871c
.word 0xbdcccccd
glabel var7f1a8720
.word 0x3dcccccd
.text
/*  f01f378:	27bdfee0 */ 	addiu	$sp,$sp,-288
/*  f01f37c:	afbf0034 */ 	sw	$ra,0x34($sp)
/*  f01f380:	afb10030 */ 	sw	$s1,0x30($sp)
/*  f01f384:	afb0002c */ 	sw	$s0,0x2c($sp)
/*  f01f388:	afa40120 */ 	sw	$a0,0x120($sp)
/*  f01f38c:	afa50124 */ 	sw	$a1,0x124($sp)
/*  f01f390:	afa7012c */ 	sw	$a3,0x12c($sp)
/*  f01f394:	8c900004 */ 	lw	$s0,0x4($a0)
/*  f01f398:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f01f39c:	44809000 */ 	mtc1	$zero,$f18
/*  f01f3a0:	8e0f001c */ 	lw	$t7,0x1c($s0)
/*  f01f3a4:	00c08825 */ 	or	$s1,$a2,$zero
/*  f01f3a8:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f01f3ac:	afaf0118 */ 	sw	$t7,0x118($sp)
/*  f01f3b0:	c60400b4 */ 	lwc1	$f4,0xb4($s0)
/*  f01f3b4:	12000004 */ 	beqz	$s0,.L0f01f3c8
/*  f01f3b8:	e7a400f8 */ 	swc1	$f4,0xf8($sp)
/*  f01f3bc:	921802fe */ 	lbu	$t8,0x2fe($s0)
/*  f01f3c0:	10000002 */ 	b	.L0f01f3cc
/*  f01f3c4:	afb800f4 */ 	sw	$t8,0xf4($sp)
.L0f01f3c8:
/*  f01f3c8:	afa000f4 */ 	sw	$zero,0xf4($sp)
.L0f01f3cc:
/*  f01f3cc:	c506004c */ 	lwc1	$f6,0x4c($t0)
/*  f01f3d0:	8fa90120 */ 	lw	$t1,0x120($sp)
/*  f01f3d4:	e7b200f0 */ 	swc1	$f18,0xf0($sp)
/*  f01f3d8:	a7a000ea */ 	sh	$zero,0xea($sp)
/*  f01f3dc:	e7a600dc */ 	swc1	$f6,0xdc($sp)
/*  f01f3e0:	8d2a0020 */ 	lw	$t2,0x20($t1)
/*  f01f3e4:	3c198006 */ 	lui	$t9,%hi(g_Anims)
/*  f01f3e8:	8f39f00c */ 	lw	$t9,%lo(g_Anims)($t9)
/*  f01f3ec:	854b0000 */ 	lh	$t3,0x0($t2)
/*  f01f3f0:	8d060034 */ 	lw	$a2,0x34($t0)
/*  f01f3f4:	c50c0044 */ 	lwc1	$f12,0x44($t0)
/*  f01f3f8:	000b6080 */ 	sll	$t4,$t3,0x2
/*  f01f3fc:	018b6023 */ 	subu	$t4,$t4,$t3
/*  f01f400:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f01f404:	032c6821 */ 	addu	$t5,$t9,$t4
/*  f01f408:	91ae000b */ 	lbu	$t6,0xb($t5)
/*  f01f40c:	c7a400f8 */ 	lwc1	$f4,0xf8($sp)
/*  f01f410:	31cf0002 */ 	andi	$t7,$t6,0x2
/*  f01f414:	51e0003a */ 	beqzl	$t7,.L0f01f500
/*  f01f418:	c62a0004 */ 	lwc1	$f10,0x4($s1)
/*  f01f41c:	8e180014 */ 	lw	$t8,0x14($s0)
/*  f01f420:	8fab0118 */ 	lw	$t3,0x118($sp)
/*  f01f424:	02203025 */ 	or	$a2,$s1,$zero
/*  f01f428:	00184b80 */ 	sll	$t1,$t8,0xe
/*  f01f42c:	0521000a */ 	bgez	$t1,.L0f01f458
/*  f01f430:	25640008 */ 	addiu	$a0,$t3,0x8
/*  f01f434:	8faa0118 */ 	lw	$t2,0x118($sp)
/*  f01f438:	02203025 */ 	or	$a2,$s1,$zero
/*  f01f43c:	27a700fc */ 	addiu	$a3,$sp,0xfc
/*  f01f440:	25450028 */ 	addiu	$a1,$t2,0x28
/*  f01f444:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f01f448:	0fc197a6 */ 	jal	func0f065e98
/*  f01f44c:	25440008 */ 	addiu	$a0,$t2,0x8
/*  f01f450:	10000006 */ 	b	.L0f01f46c
/*  f01f454:	8e050024 */ 	lw	$a1,0x24($s0)
.L0f01f458:
/*  f01f458:	25650028 */ 	addiu	$a1,$t3,0x28
/*  f01f45c:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f01f460:	0fc1979d */ 	jal	func0f065e74
/*  f01f464:	27a700fc */ 	addiu	$a3,$sp,0xfc
/*  f01f468:	8e050024 */ 	lw	$a1,0x24($s0)
.L0f01f46c:
/*  f01f46c:	26190191 */ 	addiu	$t9,$s0,0x191
/*  f01f470:	27ac00ea */ 	addiu	$t4,$sp,0xea
/*  f01f474:	260d02b2 */ 	addiu	$t5,$s0,0x2b2
/*  f01f478:	27ae00ec */ 	addiu	$t6,$sp,0xec
/*  f01f47c:	27af0114 */ 	addiu	$t7,$sp,0x114
/*  f01f480:	afaf0020 */ 	sw	$t7,0x20($sp)
/*  f01f484:	afae001c */ 	sw	$t6,0x1c($sp)
/*  f01f488:	afad0018 */ 	sw	$t5,0x18($sp)
/*  f01f48c:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f01f490:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f01f494:	02202025 */ 	or	$a0,$s1,$zero
/*  f01f498:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f01f49c:	0c00a86c */ 	jal	cdFindGroundY
/*  f01f4a0:	2607018a */ 	addiu	$a3,$s0,0x18a
/*  f01f4a4:	3c017f1b */ 	lui	$at,%hi(var7f1a86ac)
/*  f01f4a8:	c42886ac */ 	lwc1	$f8,%lo(var7f1a86ac)($at)
/*  f01f4ac:	44809000 */ 	mtc1	$zero,$f18
/*  f01f4b0:	46000086 */ 	mov.s	$f2,$f0
/*  f01f4b4:	4608003c */ 	c.lt.s	$f0,$f8
/*  f01f4b8:	3c017f1b */ 	lui	$at,%hi(var7f1a86b0)
/*  f01f4bc:	45020003 */ 	bc1fl	.L0f01f4cc
/*  f01f4c0:	e60200b8 */ 	swc1	$f2,0xb8($s0)
/*  f01f4c4:	46009086 */ 	mov.s	$f2,$f18
/*  f01f4c8:	e60200b8 */ 	swc1	$f2,0xb8($s0)
.L0f01f4cc:
/*  f01f4cc:	e6120038 */ 	swc1	$f18,0x38($s0)
/*  f01f4d0:	e61200bc */ 	swc1	$f18,0xbc($s0)
/*  f01f4d4:	e61200c0 */ 	swc1	$f18,0xc0($s0)
/*  f01f4d8:	e61200c4 */ 	swc1	$f18,0xc4($s0)
/*  f01f4dc:	e60200b4 */ 	swc1	$f2,0xb4($s0)
/*  f01f4e0:	c42a86b0 */ 	lwc1	$f10,%lo(var7f1a86b0)($at)
/*  f01f4e4:	460a1102 */ 	mul.s	$f4,$f2,$f10
/*  f01f4e8:	e60400b0 */ 	swc1	$f4,0xb0($s0)
/*  f01f4ec:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*  f01f4f0:	46023201 */ 	sub.s	$f8,$f6,$f2
/*  f01f4f4:	100003ca */ 	b	.L0f020420
/*  f01f4f8:	e6280004 */ 	swc1	$f8,0x4($s1)
/*  f01f4fc:	c62a0004 */ 	lwc1	$f10,0x4($s1)
.L0f01f500:
/*  f01f500:	3c098006 */ 	lui	$t1,%hi(var80062990)
/*  f01f504:	25292990 */ 	addiu	$t1,$t1,%lo(var80062990)
/*  f01f508:	46045180 */ 	add.s	$f6,$f10,$f4
/*  f01f50c:	e6260004 */ 	swc1	$f6,0x4($s1)
/*  f01f510:	8e1802d4 */ 	lw	$t8,0x2d4($s0)
/*  f01f514:	5300003c */ 	beqzl	$t8,.L0f01f608
/*  f01f518:	82020007 */ 	lb	$v0,0x7($s0)
/*  f01f51c:	8d210000 */ 	lw	$at,0x0($t1)
/*  f01f520:	27a500b8 */ 	addiu	$a1,$sp,0xb8
/*  f01f524:	02002025 */ 	or	$a0,$s0,$zero
/*  f01f528:	aca10000 */ 	sw	$at,0x0($a1)
/*  f01f52c:	8d2b0004 */ 	lw	$t3,0x4($t1)
/*  f01f530:	18c0002a */ 	blez	$a2,.L0f01f5dc
/*  f01f534:	acab0004 */ 	sw	$t3,0x4($a1)
/*  f01f538:	8e0202d4 */ 	lw	$v0,0x2d4($s0)
/*  f01f53c:	90430078 */ 	lbu	$v1,0x78($v0)
/*  f01f540:	50600012 */ 	beqzl	$v1,.L0f01f58c
/*  f01f544:	8e0f031c */ 	lw	$t7,0x31c($s0)
/*  f01f548:	8e19001c */ 	lw	$t9,0x1c($s0)
/*  f01f54c:	246effff */ 	addiu	$t6,$v1,-1
/*  f01f550:	28c10019 */ 	slti	$at,$a2,0x19
/*  f01f554:	932c0001 */ 	lbu	$t4,0x1($t9)
/*  f01f558:	318d0080 */ 	andi	$t5,$t4,0x80
/*  f01f55c:	11a00003 */ 	beqz	$t5,.L0f01f56c
/*  f01f560:	00000000 */ 	nop
/*  f01f564:	10000016 */ 	b	.L0f01f5c0
/*  f01f568:	a0400078 */ 	sb	$zero,0x78($v0)
.L0f01f56c:
/*  f01f56c:	14200014 */ 	bnez	$at,.L0f01f5c0
/*  f01f570:	a04e0078 */ 	sb	$t6,0x78($v0)
/*  f01f574:	3c014080 */ 	lui	$at,0x4080
/*  f01f578:	44816000 */ 	mtc1	$at,$f12
/*  f01f57c:	24060010 */ 	addiu	$a2,$zero,0x10
/*  f01f580:	1000000f */ 	b	.L0f01f5c0
/*  f01f584:	e7ac00dc */ 	swc1	$f12,0xdc($sp)
/*  f01f588:	8e0f031c */ 	lw	$t7,0x31c($s0)
.L0f01f58c:
/*  f01f58c:	51e0000d */ 	beqzl	$t7,.L0f01f5c4
/*  f01f590:	8fa700dc */ 	lw	$a3,0xdc($sp)
/*  f01f594:	8e18001c */ 	lw	$t8,0x1c($s0)
/*  f01f598:	28c10019 */ 	slti	$at,$a2,0x19
/*  f01f59c:	930a0001 */ 	lbu	$t2,0x1($t8)
/*  f01f5a0:	314900c0 */ 	andi	$t1,$t2,0xc0
/*  f01f5a4:	55200007 */ 	bnezl	$t1,.L0f01f5c4
/*  f01f5a8:	8fa700dc */ 	lw	$a3,0xdc($sp)
/*  f01f5ac:	14200004 */ 	bnez	$at,.L0f01f5c0
/*  f01f5b0:	3c014080 */ 	lui	$at,0x4080
/*  f01f5b4:	44816000 */ 	mtc1	$at,$f12
/*  f01f5b8:	24060010 */ 	addiu	$a2,$zero,0x10
/*  f01f5bc:	e7ac00dc */ 	swc1	$f12,0xdc($sp)
.L0f01f5c0:
/*  f01f5c0:	8fa700dc */ 	lw	$a3,0xdc($sp)
.L0f01f5c4:
/*  f01f5c4:	0fc6487e */ 	jal	func0f1921f8
/*  f01f5c8:	e7ac00e0 */ 	swc1	$f12,0xe0($sp)
/*  f01f5cc:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f01f5d0:	44809000 */ 	mtc1	$zero,$f18
/*  f01f5d4:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f01f5d8:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
.L0f01f5dc:
/*  f01f5dc:	8fab0124 */ 	lw	$t3,0x124($sp)
/*  f01f5e0:	c7a800b8 */ 	lwc1	$f8,0xb8($sp)
/*  f01f5e4:	c56a0000 */ 	lwc1	$f10,0x0($t3)
/*  f01f5e8:	460a4100 */ 	add.s	$f4,$f8,$f10
/*  f01f5ec:	e6240000 */ 	swc1	$f4,0x0($s1)
/*  f01f5f0:	8fb90124 */ 	lw	$t9,0x124($sp)
/*  f01f5f4:	c7a600bc */ 	lwc1	$f6,0xbc($sp)
/*  f01f5f8:	c7280008 */ 	lwc1	$f8,0x8($t9)
/*  f01f5fc:	46083280 */ 	add.s	$f10,$f6,$f8
/*  f01f600:	e62a0008 */ 	swc1	$f10,0x8($s1)
/*  f01f604:	82020007 */ 	lb	$v0,0x7($s0)
.L0f01f608:
/*  f01f608:	2401000e */ 	addiu	$at,$zero,0xe
/*  f01f60c:	10410003 */ 	beq	$v0,$at,.L0f01f61c
/*  f01f610:	2401000f */ 	addiu	$at,$zero,0xf
/*  f01f614:	54410022 */ 	bnel	$v0,$at,.L0f01f6a0
/*  f01f618:	ae00031c */ 	sw	$zero,0x31c($s0)
.L0f01f61c:
/*  f01f61c:	8e02001c */ 	lw	$v0,0x1c($s0)
/*  f01f620:	c6120024 */ 	lwc1	$f18,0x24($s0)
/*  f01f624:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01f628:	c6100028 */ 	lwc1	$f16,0x28($s0)
/*  f01f62c:	c442000c */ 	lwc1	$f2,0xc($v0)
/*  f01f630:	3c014020 */ 	lui	$at,0x4020
/*  f01f634:	46100400 */ 	add.s	$f16,$f0,$f16
/*  f01f638:	44817000 */ 	mtc1	$at,$f14
/*  f01f63c:	3c013f80 */ 	lui	$at,0x3f80
/*  f01f640:	44815000 */ 	mtc1	$at,$f10
/*  f01f644:	460e9382 */ 	mul.s	$f14,$f18,$f14
/*  f01f648:	46028401 */ 	sub.s	$f16,$f16,$f2
/*  f01f64c:	244c0028 */ 	addiu	$t4,$v0,0x28
/*  f01f650:	240d0040 */ 	addiu	$t5,$zero,0x40
/*  f01f654:	260e0320 */ 	addiu	$t6,$s0,0x320
/*  f01f658:	460a0280 */ 	add.s	$f10,$f0,$f10
/*  f01f65c:	44068000 */ 	mfc1	$a2,$f16
/*  f01f660:	44057000 */ 	mfc1	$a1,$f14
/*  f01f664:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f01f668:	46025281 */ 	sub.s	$f10,$f10,$f2
/*  f01f66c:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f01f670:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f01f674:	afae0018 */ 	sw	$t6,0x18($sp)
/*  f01f678:	44075000 */ 	mfc1	$a3,$f10
/*  f01f67c:	0c00a7ff */ 	jal	func00029ffc
/*  f01f680:	e7ac00e0 */ 	swc1	$f12,0xe0($sp)
/*  f01f684:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f01f688:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
/*  f01f68c:	44809000 */ 	mtc1	$zero,$f18
/*  f01f690:	ae02031c */ 	sw	$v0,0x31c($s0)
/*  f01f694:	10000002 */ 	b	.L0f01f6a0
/*  f01f698:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f01f69c:	ae00031c */ 	sw	$zero,0x31c($s0)
.L0f01f6a0:
/*  f01f6a0:	8e0f02d4 */ 	lw	$t7,0x2d4($s0)
/*  f01f6a4:	3c014339 */ 	lui	$at,0x4339
/*  f01f6a8:	51e0007a */ 	beqzl	$t7,.L0f01f894
/*  f01f6ac:	820a0007 */ 	lb	$t2,0x7($s0)
/*  f01f6b0:	44817000 */ 	mtc1	$at,$f14
/*  f01f6b4:	82020007 */ 	lb	$v0,0x7($s0)
/*  f01f6b8:	2401000f */ 	addiu	$at,$zero,0xf
/*  f01f6bc:	e60e0028 */ 	swc1	$f14,0x28($s0)
/*  f01f6c0:	5441000a */ 	bnel	$v0,$at,.L0f01f6ec
/*  f01f6c4:	2401000f */ 	addiu	$at,$zero,0xf
/*  f01f6c8:	92180065 */ 	lbu	$t8,0x65($s0)
/*  f01f6cc:	3c014307 */ 	lui	$at,0x4307
/*  f01f6d0:	330a0080 */ 	andi	$t2,$t8,0x80
/*  f01f6d4:	51400005 */ 	beqzl	$t2,.L0f01f6ec
/*  f01f6d8:	2401000f */ 	addiu	$at,$zero,0xf
/*  f01f6dc:	44813000 */ 	mtc1	$at,$f6
/*  f01f6e0:	1000004a */ 	b	.L0f01f80c
/*  f01f6e4:	e6060028 */ 	swc1	$f6,0x28($s0)
/*  f01f6e8:	2401000f */ 	addiu	$at,$zero,0xf
.L0f01f6ec:
/*  f01f6ec:	14410009 */ 	bne	$v0,$at,.L0f01f714
/*  f01f6f0:	00000000 */ 	nop
/*  f01f6f4:	92090065 */ 	lbu	$t1,0x65($s0)
/*  f01f6f8:	3c0142b4 */ 	lui	$at,0x42b4
/*  f01f6fc:	312b0040 */ 	andi	$t3,$t1,0x40
/*  f01f700:	11600004 */ 	beqz	$t3,.L0f01f714
/*  f01f704:	00000000 */ 	nop
/*  f01f708:	44814000 */ 	mtc1	$at,$f8
/*  f01f70c:	1000003f */ 	b	.L0f01f80c
/*  f01f710:	e6080028 */ 	swc1	$f8,0x28($s0)
.L0f01f714:
/*  f01f714:	3c017f1b */ 	lui	$at,%hi(var7f1a86b4)
/*  f01f718:	c42486b4 */ 	lwc1	$f4,%lo(var7f1a86b4)($at)
/*  f01f71c:	c60a0024 */ 	lwc1	$f10,0x24($s0)
/*  f01f720:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01f724:	3c014120 */ 	lui	$at,0x4120
/*  f01f728:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f01f72c:	44812000 */ 	mtc1	$at,$f4
/*  f01f730:	8e02001c */ 	lw	$v0,0x1c($s0)
/*  f01f734:	240c1000 */ 	addiu	$t4,$zero,0x1000
/*  f01f738:	460e0200 */ 	add.s	$f8,$f0,$f14
/*  f01f73c:	c442000c */ 	lwc1	$f2,0xc($v0)
/*  f01f740:	44053000 */ 	mfc1	$a1,$f6
/*  f01f744:	46040181 */ 	sub.s	$f6,$f0,$f4
/*  f01f748:	24590028 */ 	addiu	$t9,$v0,0x28
/*  f01f74c:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f01f750:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f01f754:	e7ac00e0 */ 	swc1	$f12,0xe0($sp)
/*  f01f758:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f01f75c:	46023201 */ 	sub.s	$f8,$f6,$f2
/*  f01f760:	44065000 */ 	mfc1	$a2,$f10
/*  f01f764:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f01f768:	44074000 */ 	mfc1	$a3,$f8
/*  f01f76c:	0c00a84f */ 	jal	func0002a13c
/*  f01f770:	00000000 */ 	nop
/*  f01f774:	10400005 */ 	beqz	$v0,.L0f01f78c
/*  f01f778:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
/*  f01f77c:	3c014307 */ 	lui	$at,0x4307
/*  f01f780:	44815000 */ 	mtc1	$at,$f10
/*  f01f784:	10000021 */ 	b	.L0f01f80c
/*  f01f788:	e60a0028 */ 	swc1	$f10,0x28($s0)
.L0f01f78c:
/*  f01f78c:	3c017f1b */ 	lui	$at,%hi(var7f1a86b8)
/*  f01f790:	c42686b8 */ 	lwc1	$f6,%lo(var7f1a86b8)($at)
/*  f01f794:	c6040024 */ 	lwc1	$f4,0x24($s0)
/*  f01f798:	3c014307 */ 	lui	$at,0x4307
/*  f01f79c:	44815000 */ 	mtc1	$at,$f10
/*  f01f7a0:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f01f7a4:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01f7a8:	3c014120 */ 	lui	$at,0x4120
/*  f01f7ac:	8e02001c */ 	lw	$v0,0x1c($s0)
/*  f01f7b0:	240e0800 */ 	addiu	$t6,$zero,0x800
/*  f01f7b4:	460a0100 */ 	add.s	$f4,$f0,$f10
/*  f01f7b8:	c442000c */ 	lwc1	$f2,0xc($v0)
/*  f01f7bc:	44054000 */ 	mfc1	$a1,$f8
/*  f01f7c0:	44814000 */ 	mtc1	$at,$f8
/*  f01f7c4:	46022181 */ 	sub.s	$f6,$f4,$f2
/*  f01f7c8:	244d0028 */ 	addiu	$t5,$v0,0x28
/*  f01f7cc:	afad0010 */ 	sw	$t5,0x10($sp)
/*  f01f7d0:	46080281 */ 	sub.s	$f10,$f0,$f8
/*  f01f7d4:	44063000 */ 	mfc1	$a2,$f6
/*  f01f7d8:	e7ac00e0 */ 	swc1	$f12,0xe0($sp)
/*  f01f7dc:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f01f7e0:	46025101 */ 	sub.s	$f4,$f10,$f2
/*  f01f7e4:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f01f7e8:	44072000 */ 	mfc1	$a3,$f4
/*  f01f7ec:	0c00a84f */ 	jal	func0002a13c
/*  f01f7f0:	00000000 */ 	nop
/*  f01f7f4:	10400005 */ 	beqz	$v0,.L0f01f80c
/*  f01f7f8:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
/*  f01f7fc:	3c0142b4 */ 	lui	$at,0x42b4
/*  f01f800:	44813000 */ 	mtc1	$at,$f6
/*  f01f804:	00000000 */ 	nop
/*  f01f808:	e6060028 */ 	swc1	$f6,0x28($s0)
.L0f01f80c:
/*  f01f80c:	8e0402d4 */ 	lw	$a0,0x2d4($s0)
/*  f01f810:	e7ac00e0 */ 	swc1	$f12,0xe0($sp)
/*  f01f814:	0fc32e41 */ 	jal	bmove0f0cb904
/*  f01f818:	24840108 */ 	addiu	$a0,$a0,0x108
/*  f01f81c:	8e0f02d4 */ 	lw	$t7,0x2d4($s0)
/*  f01f820:	3c028007 */ 	lui	$v0,%hi(var80075c00)
/*  f01f824:	24425c00 */ 	addiu	$v0,$v0,%lo(var80075c00)
/*  f01f828:	c44a0024 */ 	lwc1	$f10,0x24($v0)
/*  f01f82c:	c5e80108 */ 	lwc1	$f8,0x108($t7)
/*  f01f830:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f01f834:	3c013f00 */ 	lui	$at,0x3f00
/*  f01f838:	460a4102 */ 	mul.s	$f4,$f8,$f10
/*  f01f83c:	44810000 */ 	mtc1	$at,$f0
/*  f01f840:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
/*  f01f844:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f01f848:	44809000 */ 	mtc1	$zero,$f18
/*  f01f84c:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f01f850:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f01f854:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f01f858:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f01f85c:	460a2180 */ 	add.s	$f6,$f4,$f10
/*  f01f860:	e6260000 */ 	swc1	$f6,0x0($s1)
/*  f01f864:	8e1802d4 */ 	lw	$t8,0x2d4($s0)
/*  f01f868:	c4440024 */ 	lwc1	$f4,0x24($v0)
/*  f01f86c:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f01f870:	c7080110 */ 	lwc1	$f8,0x110($t8)
/*  f01f874:	46044282 */ 	mul.s	$f10,$f8,$f4
/*  f01f878:	00000000 */ 	nop
/*  f01f87c:	46065202 */ 	mul.s	$f8,$f10,$f6
/*  f01f880:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*  f01f884:	46004102 */ 	mul.s	$f4,$f8,$f0
/*  f01f888:	46045180 */ 	add.s	$f6,$f10,$f4
/*  f01f88c:	e6260008 */ 	swc1	$f6,0x8($s1)
/*  f01f890:	820a0007 */ 	lb	$t2,0x7($s0)
.L0f01f894:
/*  f01f894:	24010004 */ 	addiu	$at,$zero,0x4
/*  f01f898:	5541002e */ 	bnel	$t2,$at,.L0f01f954
/*  f01f89c:	c60202e8 */ 	lwc1	$f2,0x2e8($s0)
/*  f01f8a0:	c6020038 */ 	lwc1	$f2,0x38($s0)
/*  f01f8a4:	8fa90120 */ 	lw	$t1,0x120($sp)
/*  f01f8a8:	4602903c */ 	c.lt.s	$f18,$f2
/*  f01f8ac:	00000000 */ 	nop
/*  f01f8b0:	45020028 */ 	bc1fl	.L0f01f954
/*  f01f8b4:	c60202e8 */ 	lwc1	$f2,0x2e8($s0)
/*  f01f8b8:	8d2b0020 */ 	lw	$t3,0x20($t1)
/*  f01f8bc:	c604003c */ 	lwc1	$f4,0x3c($s0)
/*  f01f8c0:	c5680074 */ 	lwc1	$f8,0x74($t3)
/*  f01f8c4:	46041181 */ 	sub.s	$f6,$f2,$f4
/*  f01f8c8:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f01f8cc:	460c4282 */ 	mul.s	$f10,$f8,$f12
/*  f01f8d0:	00000000 */ 	nop
/*  f01f8d4:	46065202 */ 	mul.s	$f8,$f10,$f6
/*  f01f8d8:	c60a0040 */ 	lwc1	$f10,0x40($s0)
/*  f01f8dc:	46024003 */ 	div.s	$f0,$f8,$f2
/*  f01f8e0:	46005182 */ 	mul.s	$f6,$f10,$f0
/*  f01f8e4:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*  f01f8e8:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f01f8ec:	e6280000 */ 	swc1	$f8,0x0($s1)
/*  f01f8f0:	c6040048 */ 	lwc1	$f4,0x48($s0)
/*  f01f8f4:	46002182 */ 	mul.s	$f6,$f4,$f0
/*  f01f8f8:	46065200 */ 	add.s	$f8,$f10,$f6
/*  f01f8fc:	e6280008 */ 	swc1	$f8,0x8($s1)
/*  f01f900:	c60a0044 */ 	lwc1	$f10,0x44($s0)
/*  f01f904:	c7a400f0 */ 	lwc1	$f4,0xf0($sp)
/*  f01f908:	8fb90120 */ 	lw	$t9,0x120($sp)
/*  f01f90c:	46005182 */ 	mul.s	$f6,$f10,$f0
/*  f01f910:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f01f914:	e7a800f0 */ 	swc1	$f8,0xf0($sp)
/*  f01f918:	8f2c0020 */ 	lw	$t4,0x20($t9)
/*  f01f91c:	c60a003c */ 	lwc1	$f10,0x3c($s0)
/*  f01f920:	c5840074 */ 	lwc1	$f4,0x74($t4)
/*  f01f924:	46046182 */ 	mul.s	$f6,$f12,$f4
/*  f01f928:	c6040038 */ 	lwc1	$f4,0x38($s0)
/*  f01f92c:	46065200 */ 	add.s	$f8,$f10,$f6
/*  f01f930:	e608003c */ 	swc1	$f8,0x3c($s0)
/*  f01f934:	c60a003c */ 	lwc1	$f10,0x3c($s0)
/*  f01f938:	460a203c */ 	c.lt.s	$f4,$f10
/*  f01f93c:	00000000 */ 	nop
/*  f01f940:	4500002e */ 	bc1f	.L0f01f9fc
/*  f01f944:	00000000 */ 	nop
/*  f01f948:	1000002c */ 	b	.L0f01f9fc
/*  f01f94c:	e6120038 */ 	swc1	$f18,0x38($s0)
/*  f01f950:	c60202e8 */ 	lwc1	$f2,0x2e8($s0)
.L0f01f954:
/*  f01f954:	8fad0120 */ 	lw	$t5,0x120($sp)
/*  f01f958:	4602903c */ 	c.lt.s	$f18,$f2
/*  f01f95c:	00000000 */ 	nop
/*  f01f960:	45020027 */ 	bc1fl	.L0f01fa00
/*  f01f964:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01f968:	8dae0020 */ 	lw	$t6,0x20($t5)
/*  f01f96c:	c60402ec */ 	lwc1	$f4,0x2ec($s0)
/*  f01f970:	c5c60074 */ 	lwc1	$f6,0x74($t6)
/*  f01f974:	46041281 */ 	sub.s	$f10,$f2,$f4
/*  f01f978:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f01f97c:	460c3202 */ 	mul.s	$f8,$f6,$f12
/*  f01f980:	00000000 */ 	nop
/*  f01f984:	460a4182 */ 	mul.s	$f6,$f8,$f10
/*  f01f988:	c60802f0 */ 	lwc1	$f8,0x2f0($s0)
/*  f01f98c:	46023003 */ 	div.s	$f0,$f6,$f2
/*  f01f990:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f01f994:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*  f01f998:	460a2180 */ 	add.s	$f6,$f4,$f10
/*  f01f99c:	e6260000 */ 	swc1	$f6,0x0($s1)
/*  f01f9a0:	c60402f8 */ 	lwc1	$f4,0x2f8($s0)
/*  f01f9a4:	46002282 */ 	mul.s	$f10,$f4,$f0
/*  f01f9a8:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f01f9ac:	e6260008 */ 	swc1	$f6,0x8($s1)
/*  f01f9b0:	c60802f4 */ 	lwc1	$f8,0x2f4($s0)
/*  f01f9b4:	c7a400f0 */ 	lwc1	$f4,0xf0($sp)
/*  f01f9b8:	8faf0120 */ 	lw	$t7,0x120($sp)
/*  f01f9bc:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f01f9c0:	460a2180 */ 	add.s	$f6,$f4,$f10
/*  f01f9c4:	e7a600f0 */ 	swc1	$f6,0xf0($sp)
/*  f01f9c8:	8df80020 */ 	lw	$t8,0x20($t7)
/*  f01f9cc:	c60802ec */ 	lwc1	$f8,0x2ec($s0)
/*  f01f9d0:	c7040074 */ 	lwc1	$f4,0x74($t8)
/*  f01f9d4:	46046282 */ 	mul.s	$f10,$f12,$f4
/*  f01f9d8:	c60402e8 */ 	lwc1	$f4,0x2e8($s0)
/*  f01f9dc:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f01f9e0:	e60602ec */ 	swc1	$f6,0x2ec($s0)
/*  f01f9e4:	c60802ec */ 	lwc1	$f8,0x2ec($s0)
/*  f01f9e8:	4608203c */ 	c.lt.s	$f4,$f8
/*  f01f9ec:	00000000 */ 	nop
/*  f01f9f0:	45000002 */ 	bc1f	.L0f01f9fc
/*  f01f9f4:	00000000 */ 	nop
/*  f01f9f8:	e61202e8 */ 	swc1	$f18,0x2e8($s0)
.L0f01f9fc:
/*  f01f9fc:	c6000304 */ 	lwc1	$f0,0x304($s0)
.L0f01fa00:
/*  f01fa00:	c7a400dc */ 	lwc1	$f4,0xdc($sp)
/*  f01fa04:	46009032 */ 	c.eq.s	$f18,$f0
/*  f01fa08:	00000000 */ 	nop
/*  f01fa0c:	45000006 */ 	bc1f	.L0f01fa28
/*  f01fa10:	00000000 */ 	nop
/*  f01fa14:	c60a0308 */ 	lwc1	$f10,0x308($s0)
/*  f01fa18:	460a9032 */ 	c.eq.s	$f18,$f10
/*  f01fa1c:	00000000 */ 	nop
/*  f01fa20:	45030043 */ 	bc1tl	.L0f01fb30
/*  f01fa24:	c60400bc */ 	lwc1	$f4,0xbc($s0)
.L0f01fa28:
/*  f01fa28:	46040202 */ 	mul.s	$f8,$f0,$f4
/*  f01fa2c:	c6260000 */ 	lwc1	$f6,0x0($s1)
/*  f01fa30:	3c017f1b */ 	lui	$at,%hi(var7f1a86bc)
/*  f01fa34:	c43086bc */ 	lwc1	$f16,%lo(var7f1a86bc)($at)
/*  f01fa38:	46083280 */ 	add.s	$f10,$f6,$f8
/*  f01fa3c:	e62a0000 */ 	swc1	$f10,0x0($s1)
/*  f01fa40:	c6040308 */ 	lwc1	$f4,0x308($s0)
/*  f01fa44:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f01fa48:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*  f01fa4c:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f01fa50:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f01fa54:	e6240008 */ 	swc1	$f4,0x8($s1)
/*  f01fa58:	c6060304 */ 	lwc1	$f6,0x304($s0)
/*  f01fa5c:	c6080308 */ 	lwc1	$f8,0x308($s0)
/*  f01fa60:	46103282 */ 	mul.s	$f10,$f6,$f16
/*  f01fa64:	e60a0304 */ 	swc1	$f10,0x304($s0)
/*  f01fa68:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01fa6c:	46104102 */ 	mul.s	$f4,$f8,$f16
/*  f01fa70:	46009032 */ 	c.eq.s	$f18,$f0
/*  f01fa74:	00000000 */ 	nop
/*  f01fa78:	45000006 */ 	bc1f	.L0f01fa94
/*  f01fa7c:	e6040308 */ 	swc1	$f4,0x308($s0)
/*  f01fa80:	c6060308 */ 	lwc1	$f6,0x308($s0)
/*  f01fa84:	46069032 */ 	c.eq.s	$f18,$f6
/*  f01fa88:	00000000 */ 	nop
/*  f01fa8c:	45030028 */ 	bc1tl	.L0f01fb30
/*  f01fa90:	c60400bc */ 	lwc1	$f4,0xbc($s0)
.L0f01fa94:
/*  f01fa94:	c6020308 */ 	lwc1	$f2,0x308($s0)
/*  f01fa98:	46021282 */ 	mul.s	$f10,$f2,$f2
/*  f01fa9c:	00000000 */ 	nop
/*  f01faa0:	46000202 */ 	mul.s	$f8,$f0,$f0
/*  f01faa4:	0c012974 */ 	jal	sqrtf
/*  f01faa8:	46085300 */ 	add.s	$f12,$f10,$f8
/*  f01faac:	44809000 */ 	mtc1	$zero,$f18
/*  f01fab0:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f01fab4:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f01fab8:	4600903c */ 	c.lt.s	$f18,$f0
/*  f01fabc:	3c017f1b */ 	lui	$at,%hi(var7f1a86c4)
/*  f01fac0:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f01fac4:	45020018 */ 	bc1fl	.L0f01fb28
/*  f01fac8:	e6120304 */ 	swc1	$f18,0x304($s0)
/*  f01facc:	c42486c4 */ 	lwc1	$f4,%lo(var7f1a86c4)($at)
/*  f01fad0:	3c013f80 */ 	lui	$at,0x3f80
/*  f01fad4:	44814000 */ 	mtc1	$at,$f8
/*  f01fad8:	46062282 */ 	mul.s	$f10,$f4,$f6
/*  f01fadc:	46005303 */ 	div.s	$f12,$f10,$f0
/*  f01fae0:	460c403e */ 	c.le.s	$f8,$f12
/*  f01fae4:	00000000 */ 	nop
/*  f01fae8:	45020005 */ 	bc1fl	.L0f01fb00
/*  f01faec:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01faf0:	e6120304 */ 	swc1	$f18,0x304($s0)
/*  f01faf4:	1000000d */ 	b	.L0f01fb2c
/*  f01faf8:	e6120308 */ 	swc1	$f18,0x308($s0)
/*  f01fafc:	c6000304 */ 	lwc1	$f0,0x304($s0)
.L0f01fb00:
/*  f01fb00:	c6020308 */ 	lwc1	$f2,0x308($s0)
/*  f01fb04:	460c0102 */ 	mul.s	$f4,$f0,$f12
/*  f01fb08:	00000000 */ 	nop
/*  f01fb0c:	460c1282 */ 	mul.s	$f10,$f2,$f12
/*  f01fb10:	46040181 */ 	sub.s	$f6,$f0,$f4
/*  f01fb14:	460a1201 */ 	sub.s	$f8,$f2,$f10
/*  f01fb18:	e6060304 */ 	swc1	$f6,0x304($s0)
/*  f01fb1c:	10000003 */ 	b	.L0f01fb2c
/*  f01fb20:	e6080308 */ 	swc1	$f8,0x308($s0)
/*  f01fb24:	e6120304 */ 	swc1	$f18,0x304($s0)
.L0f01fb28:
/*  f01fb28:	e6120308 */ 	swc1	$f18,0x308($s0)
.L0f01fb2c:
/*  f01fb2c:	c60400bc */ 	lwc1	$f4,0xbc($s0)
.L0f01fb30:
/*  f01fb30:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f01fb34:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f01fb38:	24010003 */ 	addiu	$at,$zero,0x3
/*  f01fb3c:	46062282 */ 	mul.s	$f10,$f4,$f6
/*  f01fb40:	460a4100 */ 	add.s	$f4,$f8,$f10
/*  f01fb44:	e6240000 */ 	swc1	$f4,0x0($s1)
/*  f01fb48:	c7a800dc */ 	lwc1	$f8,0xdc($sp)
/*  f01fb4c:	c60600c4 */ 	lwc1	$f6,0xc4($s0)
/*  f01fb50:	c6240008 */ 	lwc1	$f4,0x8($s1)
/*  f01fb54:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f01fb58:	460a2180 */ 	add.s	$f6,$f4,$f10
/*  f01fb5c:	e6260008 */ 	swc1	$f6,0x8($s1)
/*  f01fb60:	8faa00f4 */ 	lw	$t2,0xf4($sp)
/*  f01fb64:	55410013 */ 	bnel	$t2,$at,.L0f01fbb4
/*  f01fb68:	820d0007 */ 	lb	$t5,0x7($s0)
/*  f01fb6c:	0fc0f011 */ 	jal	chrToEyespy
/*  f01fb70:	02002025 */ 	or	$a0,$s0,$zero
/*  f01fb74:	50400043 */ 	beqzl	$v0,.L0f01fc84
/*  f01fb78:	8fac0118 */ 	lw	$t4,0x118($sp)
/*  f01fb7c:	90490035 */ 	lbu	$t1,0x35($v0)
/*  f01fb80:	51200040 */ 	beqzl	$t1,.L0f01fc84
/*  f01fb84:	8fac0118 */ 	lw	$t4,0x118($sp)
/*  f01fb88:	8e0b001c */ 	lw	$t3,0x1c($s0)
/*  f01fb8c:	c5680008 */ 	lwc1	$f8,0x8($t3)
/*  f01fb90:	e6280000 */ 	swc1	$f8,0x0($s1)
/*  f01fb94:	8e19001c */ 	lw	$t9,0x1c($s0)
/*  f01fb98:	c724000c */ 	lwc1	$f4,0xc($t9)
/*  f01fb9c:	e6240004 */ 	swc1	$f4,0x4($s1)
/*  f01fba0:	8e0c001c */ 	lw	$t4,0x1c($s0)
/*  f01fba4:	c58a0010 */ 	lwc1	$f10,0x10($t4)
/*  f01fba8:	10000035 */ 	b	.L0f01fc80
/*  f01fbac:	e62a0008 */ 	swc1	$f10,0x8($s1)
/*  f01fbb0:	820d0007 */ 	lb	$t5,0x7($s0)
.L0f01fbb4:
/*  f01fbb4:	24010023 */ 	addiu	$at,$zero,0x23
/*  f01fbb8:	55a10013 */ 	bnel	$t5,$at,.L0f01fc08
/*  f01fbbc:	8e0a031c */ 	lw	$t2,0x31c($s0)
/*  f01fbc0:	920e002c */ 	lbu	$t6,0x2c($s0)
/*  f01fbc4:	24010001 */ 	addiu	$at,$zero,0x1
/*  f01fbc8:	55c1000f */ 	bnel	$t6,$at,.L0f01fc08
/*  f01fbcc:	8e0a031c */ 	lw	$t2,0x31c($s0)
/*  f01fbd0:	920f002d */ 	lbu	$t7,0x2d($s0)
/*  f01fbd4:	55e0000c */ 	bnezl	$t7,.L0f01fc08
/*  f01fbd8:	8e0a031c */ 	lw	$t2,0x31c($s0)
/*  f01fbdc:	8d180038 */ 	lw	$t8,0x38($t0)
/*  f01fbe0:	53000009 */ 	beqzl	$t8,.L0f01fc08
/*  f01fbe4:	8e0a031c */ 	lw	$t2,0x31c($s0)
/*  f01fbe8:	c6060040 */ 	lwc1	$f6,0x40($s0)
/*  f01fbec:	e6260000 */ 	swc1	$f6,0x0($s1)
/*  f01fbf0:	c6080044 */ 	lwc1	$f8,0x44($s0)
/*  f01fbf4:	e7a800f0 */ 	swc1	$f8,0xf0($sp)
/*  f01fbf8:	c6040048 */ 	lwc1	$f4,0x48($s0)
/*  f01fbfc:	10000020 */ 	b	.L0f01fc80
/*  f01fc00:	e6240008 */ 	swc1	$f4,0x8($s1)
/*  f01fc04:	8e0a031c */ 	lw	$t2,0x31c($s0)
.L0f01fc08:
/*  f01fc08:	8fa90124 */ 	lw	$t1,0x124($sp)
/*  f01fc0c:	5140001d */ 	beqzl	$t2,.L0f01fc84
/*  f01fc10:	8fac0118 */ 	lw	$t4,0x118($sp)
/*  f01fc14:	c5200000 */ 	lwc1	$f0,0x0($t1)
/*  f01fc18:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f01fc1c:	c6260008 */ 	lwc1	$f6,0x8($s1)
/*  f01fc20:	c5280008 */ 	lwc1	$f8,0x8($t1)
/*  f01fc24:	46005081 */ 	sub.s	$f2,$f10,$f0
/*  f01fc28:	e6200000 */ 	swc1	$f0,0x0($s1)
/*  f01fc2c:	8fab0124 */ 	lw	$t3,0x124($sp)
/*  f01fc30:	46083381 */ 	sub.s	$f14,$f6,$f8
/*  f01fc34:	46021282 */ 	mul.s	$f10,$f2,$f2
/*  f01fc38:	c5640008 */ 	lwc1	$f4,0x8($t3)
/*  f01fc3c:	460e7182 */ 	mul.s	$f6,$f14,$f14
/*  f01fc40:	e6240008 */ 	swc1	$f4,0x8($s1)
/*  f01fc44:	0c012974 */ 	jal	sqrtf
/*  f01fc48:	46065300 */ 	add.s	$f12,$f10,$f6
/*  f01fc4c:	3c0142c8 */ 	lui	$at,0x42c8
/*  f01fc50:	44816000 */ 	mtc1	$at,$f12
/*  f01fc54:	46000086 */ 	mov.s	$f2,$f0
/*  f01fc58:	c7a800f0 */ 	lwc1	$f8,0xf0($sp)
/*  f01fc5c:	4600603c */ 	c.lt.s	$f12,$f0
/*  f01fc60:	00000000 */ 	nop
/*  f01fc64:	45020003 */ 	bc1fl	.L0f01fc74
/*  f01fc68:	46024100 */ 	add.s	$f4,$f8,$f2
/*  f01fc6c:	46006086 */ 	mov.s	$f2,$f12
/*  f01fc70:	46024100 */ 	add.s	$f4,$f8,$f2
.L0f01fc74:
/*  f01fc74:	24190004 */ 	addiu	$t9,$zero,0x4
/*  f01fc78:	e7a400f0 */ 	swc1	$f4,0xf0($sp)
/*  f01fc7c:	a2190191 */ 	sb	$t9,0x191($s0)
.L0f01fc80:
/*  f01fc80:	8fac0118 */ 	lw	$t4,0x118($sp)
.L0f01fc84:
/*  f01fc84:	24010006 */ 	addiu	$at,$zero,0x6
/*  f01fc88:	02002025 */ 	or	$a0,$s0,$zero
/*  f01fc8c:	918d0000 */ 	lbu	$t5,0x0($t4)
/*  f01fc90:	02202825 */ 	or	$a1,$s1,$zero
/*  f01fc94:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f01fc98:	55a10019 */ 	bnel	$t5,$at,.L0f01fd00
/*  f01fc9c:	8e0a0018 */ 	lw	$t2,0x18($s0)
/*  f01fca0:	820e0007 */ 	lb	$t6,0x7($s0)
/*  f01fca4:	24010019 */ 	addiu	$at,$zero,0x19
/*  f01fca8:	55c10015 */ 	bnel	$t6,$at,.L0f01fd00
/*  f01fcac:	8e0a0018 */ 	lw	$t2,0x18($s0)
/*  f01fcb0:	c58a0008 */ 	lwc1	$f10,0x8($t4)
/*  f01fcb4:	27a500fc */ 	addiu	$a1,$sp,0xfc
/*  f01fcb8:	e62a0000 */ 	swc1	$f10,0x0($s1)
/*  f01fcbc:	8faf0118 */ 	lw	$t7,0x118($sp)
/*  f01fcc0:	c5e60010 */ 	lwc1	$f6,0x10($t7)
/*  f01fcc4:	e6260008 */ 	swc1	$f6,0x8($s1)
/*  f01fcc8:	8fa40118 */ 	lw	$a0,0x118($sp)
/*  f01fccc:	24840028 */ 	addiu	$a0,$a0,0x28
/*  f01fcd0:	0fc195e9 */ 	jal	roomsCopy
/*  f01fcd4:	afa40048 */ 	sw	$a0,0x48($sp)
/*  f01fcd8:	3c017f1b */ 	lui	$at,%hi(var7f1a86d4)
/*  f01fcdc:	c43086d4 */ 	lwc1	$f16,%lo(var7f1a86d4)($at)
/*  f01fce0:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f01fce4:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f01fce8:	a2000009 */ 	sb	$zero,0x9($s0)
/*  f01fcec:	8d180008 */ 	lw	$t8,0x8($t0)
/*  f01fcf0:	44809000 */ 	mtc1	$zero,$f18
/*  f01fcf4:	10000015 */ 	b	.L0f01fd4c
/*  f01fcf8:	ae1800d8 */ 	sw	$t8,0xd8($s0)
/*  f01fcfc:	8e0a0018 */ 	lw	$t2,0x18($s0)
.L0f01fd00:
/*  f01fd00:	8fab0124 */ 	lw	$t3,0x124($sp)
/*  f01fd04:	31494000 */ 	andi	$t1,$t2,0x4000
/*  f01fd08:	11200006 */ 	beqz	$t1,.L0f01fd24
/*  f01fd0c:	00000000 */ 	nop
/*  f01fd10:	c5680000 */ 	lwc1	$f8,0x0($t3)
/*  f01fd14:	e6280000 */ 	swc1	$f8,0x0($s1)
/*  f01fd18:	8fb90124 */ 	lw	$t9,0x124($sp)
/*  f01fd1c:	c7240008 */ 	lwc1	$f4,0x8($t9)
/*  f01fd20:	e6240008 */ 	swc1	$f4,0x8($s1)
.L0f01fd24:
/*  f01fd24:	0fc079fd */ 	jal	chrCalculatePushPos
/*  f01fd28:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f01fd2c:	8fad0118 */ 	lw	$t5,0x118($sp)
/*  f01fd30:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f01fd34:	3c017f1b */ 	lui	$at,%hi(var7f1a86d8)
/*  f01fd38:	25ae0028 */ 	addiu	$t6,$t5,0x28
/*  f01fd3c:	44809000 */ 	mtc1	$zero,$f18
/*  f01fd40:	afae0048 */ 	sw	$t6,0x48($sp)
/*  f01fd44:	c43086d8 */ 	lwc1	$f16,%lo(var7f1a86d8)($at)
/*  f01fd48:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
.L0f01fd4c:
/*  f01fd4c:	820c0007 */ 	lb	$t4,0x7($s0)
/*  f01fd50:	24010023 */ 	addiu	$at,$zero,0x23
/*  f01fd54:	55810021 */ 	bnel	$t4,$at,.L0f01fddc
/*  f01fd58:	8e0b031c */ 	lw	$t3,0x31c($s0)
/*  f01fd5c:	920f002c */ 	lbu	$t7,0x2c($s0)
/*  f01fd60:	24010001 */ 	addiu	$at,$zero,0x1
/*  f01fd64:	55e1001d */ 	bnel	$t7,$at,.L0f01fddc
/*  f01fd68:	8e0b031c */ 	lw	$t3,0x31c($s0)
/*  f01fd6c:	9218002d */ 	lbu	$t8,0x2d($s0)
/*  f01fd70:	5700001a */ 	bnezl	$t8,.L0f01fddc
/*  f01fd74:	8e0b031c */ 	lw	$t3,0x31c($s0)
/*  f01fd78:	8d0a0038 */ 	lw	$t2,0x38($t0)
/*  f01fd7c:	02002025 */ 	or	$a0,$s0,$zero
/*  f01fd80:	02202825 */ 	or	$a1,$s1,$zero
/*  f01fd84:	11400014 */ 	beqz	$t2,.L0f01fdd8
/*  f01fd88:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f01fd8c:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f01fd90:	afa90010 */ 	sw	$t1,0x10($sp)
/*  f01fd94:	0fc07c99 */ 	jal	func0f01f264
/*  f01fd98:	8fa700f0 */ 	lw	$a3,0xf0($sp)
/*  f01fd9c:	10400005 */ 	beqz	$v0,.L0f01fdb4
/*  f01fda0:	3c017f1b */ 	lui	$at,%hi(var7f1a86dc)
/*  f01fda4:	c60a00b4 */ 	lwc1	$f10,0xb4($s0)
/*  f01fda8:	c7a600f0 */ 	lwc1	$f6,0xf0($sp)
/*  f01fdac:	46065200 */ 	add.s	$f8,$f10,$f6
/*  f01fdb0:	e60800b4 */ 	swc1	$f8,0xb4($s0)
.L0f01fdb4:
/*  f01fdb4:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01fdb8:	c42486dc */ 	lwc1	$f4,%lo(var7f1a86dc)($at)
/*  f01fdbc:	e60000b8 */ 	swc1	$f0,0xb8($s0)
/*  f01fdc0:	46040282 */ 	mul.s	$f10,$f0,$f4
/*  f01fdc4:	e60a00b0 */ 	swc1	$f10,0xb0($s0)
/*  f01fdc8:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*  f01fdcc:	46003201 */ 	sub.s	$f8,$f6,$f0
/*  f01fdd0:	10000193 */ 	b	.L0f020420
/*  f01fdd4:	e6280004 */ 	swc1	$f8,0x4($s1)
.L0f01fdd8:
/*  f01fdd8:	8e0b031c */ 	lw	$t3,0x31c($s0)
.L0f01fddc:
/*  f01fddc:	02002025 */ 	or	$a0,$s0,$zero
/*  f01fde0:	8fad00f4 */ 	lw	$t5,0xf4($sp)
/*  f01fde4:	11600016 */ 	beqz	$t3,.L0f01fe40
/*  f01fde8:	24010003 */ 	addiu	$at,$zero,0x3
/*  f01fdec:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f01fdf0:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f01fdf4:	02202825 */ 	or	$a1,$s1,$zero
/*  f01fdf8:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f01fdfc:	0fc07c99 */ 	jal	func0f01f264
/*  f01fe00:	8fa700f0 */ 	lw	$a3,0xf0($sp)
/*  f01fe04:	10400005 */ 	beqz	$v0,.L0f01fe1c
/*  f01fe08:	3c017f1b */ 	lui	$at,%hi(var7f1a86e0)
/*  f01fe0c:	c60400b4 */ 	lwc1	$f4,0xb4($s0)
/*  f01fe10:	c7aa00f0 */ 	lwc1	$f10,0xf0($sp)
/*  f01fe14:	460a2180 */ 	add.s	$f6,$f4,$f10
/*  f01fe18:	e60600b4 */ 	swc1	$f6,0xb4($s0)
.L0f01fe1c:
/*  f01fe1c:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01fe20:	c42886e0 */ 	lwc1	$f8,%lo(var7f1a86e0)($at)
/*  f01fe24:	e60000b8 */ 	swc1	$f0,0xb8($s0)
/*  f01fe28:	46080102 */ 	mul.s	$f4,$f0,$f8
/*  f01fe2c:	e60400b0 */ 	swc1	$f4,0xb0($s0)
/*  f01fe30:	c62a0004 */ 	lwc1	$f10,0x4($s1)
/*  f01fe34:	46005181 */ 	sub.s	$f6,$f10,$f0
/*  f01fe38:	10000179 */ 	b	.L0f020420
/*  f01fe3c:	e6260004 */ 	swc1	$f6,0x4($s1)
.L0f01fe40:
/*  f01fe40:	15a10003 */ 	bne	$t5,$at,.L0f01fe50
/*  f01fe44:	8fae0118 */ 	lw	$t6,0x118($sp)
/*  f01fe48:	10000099 */ 	b	.L0f0200b0
/*  f01fe4c:	c60200b4 */ 	lwc1	$f2,0xb4($s0)
.L0f01fe50:
/*  f01fe50:	91cc0000 */ 	lbu	$t4,0x0($t6)
/*  f01fe54:	24010006 */ 	addiu	$at,$zero,0x6
/*  f01fe58:	c7a400f8 */ 	lwc1	$f4,0xf8($sp)
/*  f01fe5c:	55810012 */ 	bnel	$t4,$at,.L0f01fea8
/*  f01fe60:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*  f01fe64:	0fc4a25f */ 	jal	propGetPlayerNum
/*  f01fe68:	01c02025 */ 	or	$a0,$t6,$zero
/*  f01fe6c:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f01fe70:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f01fe74:	00027880 */ 	sll	$t7,$v0,0x2
/*  f01fe78:	010fc021 */ 	addu	$t8,$t0,$t7
/*  f01fe7c:	8f030064 */ 	lw	$v1,0x64($t8)
/*  f01fe80:	3c017f1b */ 	lui	$at,%hi(var7f1a86e4)
/*  f01fe84:	c43086e4 */ 	lwc1	$f16,%lo(var7f1a86e4)($at)
/*  f01fe88:	946a161a */ 	lhu	$t2,0x161a($v1)
/*  f01fe8c:	c4620074 */ 	lwc1	$f2,0x74($v1)
/*  f01fe90:	44809000 */ 	mtc1	$zero,$f18
/*  f01fe94:	a60a018a */ 	sh	$t2,0x18a($s0)
/*  f01fe98:	9069161e */ 	lbu	$t1,0x161e($v1)
/*  f01fe9c:	10000084 */ 	b	.L0f0200b0
/*  f01fea0:	a2090191 */ 	sb	$t1,0x191($s0)
/*  f01fea4:	c6280004 */ 	lwc1	$f8,0x4($s1)
.L0f01fea8:
/*  f01fea8:	3c01428a */ 	lui	$at,0x428a
/*  f01feac:	44810000 */ 	mtc1	$at,$f0
/*  f01feb0:	46044281 */ 	sub.s	$f10,$f8,$f4
/*  f01feb4:	27a60088 */ 	addiu	$a2,$sp,0x88
/*  f01feb8:	27a70078 */ 	addiu	$a3,$sp,0x78
/*  f01febc:	27ab00fc */ 	addiu	$t3,$sp,0xfc
/*  f01fec0:	4600503c */ 	c.lt.s	$f10,$f0
/*  f01fec4:	00000000 */ 	nop
/*  f01fec8:	45020013 */ 	bc1fl	.L0f01ff18
/*  f01fecc:	afb10098 */ 	sw	$s1,0x98($sp)
/*  f01fed0:	46002200 */ 	add.s	$f8,$f4,$f0
/*  f01fed4:	afa60098 */ 	sw	$a2,0x98($sp)
/*  f01fed8:	afa70094 */ 	sw	$a3,0x94($sp)
/*  f01fedc:	c6260000 */ 	lwc1	$f6,0x0($s1)
/*  f01fee0:	e7a8008c */ 	swc1	$f8,0x8c($sp)
/*  f01fee4:	02202025 */ 	or	$a0,$s1,$zero
/*  f01fee8:	e7a60088 */ 	swc1	$f6,0x88($sp)
/*  f01feec:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*  f01fef0:	27a500fc */ 	addiu	$a1,$sp,0xfc
/*  f01fef4:	0fc1979d */ 	jal	func0f065e74
/*  f01fef8:	e7aa0090 */ 	swc1	$f10,0x90($sp)
/*  f01fefc:	02002025 */ 	or	$a0,$s0,$zero
/*  f01ff00:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f01ff04:	0fc087ea */ 	jal	func0f021fa8
/*  f01ff08:	27a60078 */ 	addiu	$a2,$sp,0x78
/*  f01ff0c:	10000004 */ 	b	.L0f01ff20
/*  f01ff10:	8e050024 */ 	lw	$a1,0x24($s0)
/*  f01ff14:	afb10098 */ 	sw	$s1,0x98($sp)
.L0f01ff18:
/*  f01ff18:	afab0094 */ 	sw	$t3,0x94($sp)
/*  f01ff1c:	8e050024 */ 	lw	$a1,0x24($s0)
.L0f01ff20:
/*  f01ff20:	2607018a */ 	addiu	$a3,$s0,0x18a
/*  f01ff24:	26020191 */ 	addiu	$v0,$s0,0x191
/*  f01ff28:	27b900ea */ 	addiu	$t9,$sp,0xea
/*  f01ff2c:	260302b2 */ 	addiu	$v1,$s0,0x2b2
/*  f01ff30:	27ad00ec */ 	addiu	$t5,$sp,0xec
/*  f01ff34:	27ac0114 */ 	addiu	$t4,$sp,0x114
/*  f01ff38:	afac0020 */ 	sw	$t4,0x20($sp)
/*  f01ff3c:	afad001c */ 	sw	$t5,0x1c($sp)
/*  f01ff40:	afa30018 */ 	sw	$v1,0x18($sp)
/*  f01ff44:	afa30040 */ 	sw	$v1,0x40($sp)
/*  f01ff48:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f01ff4c:	afa20010 */ 	sw	$v0,0x10($sp)
/*  f01ff50:	afa20044 */ 	sw	$v0,0x44($sp)
/*  f01ff54:	afa7004c */ 	sw	$a3,0x4c($sp)
/*  f01ff58:	8fa40098 */ 	lw	$a0,0x98($sp)
/*  f01ff5c:	0c00a86c */ 	jal	cdFindGroundY
/*  f01ff60:	8fa60094 */ 	lw	$a2,0x94($sp)
/*  f01ff64:	8e0202d4 */ 	lw	$v0,0x2d4($s0)
/*  f01ff68:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f01ff6c:	3c017f1b */ 	lui	$at,%hi(var7f1a86f0)
/*  f01ff70:	44809000 */ 	mtc1	$zero,$f18
/*  f01ff74:	c43086f0 */ 	lwc1	$f16,%lo(var7f1a86f0)($at)
/*  f01ff78:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f01ff7c:	10400038 */ 	beqz	$v0,.L0f020060
/*  f01ff80:	46000086 */ 	mov.s	$f2,$f0
/*  f01ff84:	904e0078 */ 	lbu	$t6,0x78($v0)
/*  f01ff88:	3c017f1b */ 	lui	$at,%hi(var7f1a86f4)
/*  f01ff8c:	55c00035 */ 	bnezl	$t6,.L0f020064
/*  f01ff90:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f01ff94:	c42c86f4 */ 	lwc1	$f12,%lo(var7f1a86f4)($at)
/*  f01ff98:	460c003c */ 	c.lt.s	$f0,$f12
/*  f01ff9c:	00000000 */ 	nop
/*  f01ffa0:	45020030 */ 	bc1fl	.L0f020064
/*  f01ffa4:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f01ffa8:	8d0f0038 */ 	lw	$t7,0x38($t0)
/*  f01ffac:	29e10005 */ 	slti	$at,$t7,0x5
/*  f01ffb0:	5420002c */ 	bnezl	$at,.L0f020064
/*  f01ffb4:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f01ffb8:	8e18001c */ 	lw	$t8,0x1c($s0)
/*  f01ffbc:	240b000a */ 	addiu	$t3,$zero,0xa
/*  f01ffc0:	930a0001 */ 	lbu	$t2,0x1($t8)
/*  f01ffc4:	31490080 */ 	andi	$t1,$t2,0x80
/*  f01ffc8:	55200026 */ 	bnezl	$t1,.L0f020064
/*  f01ffcc:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f01ffd0:	a04b0078 */ 	sb	$t3,0x78($v0)
/*  f01ffd4:	8fb90118 */ 	lw	$t9,0x118($sp)
/*  f01ffd8:	27a500fc */ 	addiu	$a1,$sp,0xfc
/*  f01ffdc:	c7260008 */ 	lwc1	$f6,0x8($t9)
/*  f01ffe0:	e6260000 */ 	swc1	$f6,0x0($s1)
/*  f01ffe4:	8fad0118 */ 	lw	$t5,0x118($sp)
/*  f01ffe8:	c5a4000c */ 	lwc1	$f4,0xc($t5)
/*  f01ffec:	e6240004 */ 	swc1	$f4,0x4($s1)
/*  f01fff0:	8fac0118 */ 	lw	$t4,0x118($sp)
/*  f01fff4:	c5880010 */ 	lwc1	$f8,0x10($t4)
/*  f01fff8:	e6280008 */ 	swc1	$f8,0x8($s1)
/*  f01fffc:	0fc195e9 */ 	jal	roomsCopy
/*  f020000:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f020004:	44809000 */ 	mtc1	$zero,$f18
/*  f020008:	8fae0044 */ 	lw	$t6,0x44($sp)
/*  f02000c:	8fb80040 */ 	lw	$t8,0x40($sp)
/*  f020010:	e7b200dc */ 	swc1	$f18,0xdc($sp)
/*  f020014:	8e050024 */ 	lw	$a1,0x24($s0)
/*  f020018:	27af00ea */ 	addiu	$t7,$sp,0xea
/*  f02001c:	27aa00ec */ 	addiu	$t2,$sp,0xec
/*  f020020:	27a90114 */ 	addiu	$t1,$sp,0x114
/*  f020024:	afa90020 */ 	sw	$t1,0x20($sp)
/*  f020028:	afaa001c */ 	sw	$t2,0x1c($sp)
/*  f02002c:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f020030:	02202025 */ 	or	$a0,$s1,$zero
/*  f020034:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f020038:	8fa7004c */ 	lw	$a3,0x4c($sp)
/*  f02003c:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f020040:	0c00a86c */ 	jal	cdFindGroundY
/*  f020044:	afb80018 */ 	sw	$t8,0x18($sp)
/*  f020048:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f02004c:	3c017f1b */ 	lui	$at,%hi(var7f1a86fc)
/*  f020050:	44809000 */ 	mtc1	$zero,$f18
/*  f020054:	c43086fc */ 	lwc1	$f16,%lo(var7f1a86fc)($at)
/*  f020058:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f02005c:	46000086 */ 	mov.s	$f2,$f0
.L0f020060:
/*  f020060:	8fab00ec */ 	lw	$t3,0xec($sp)
.L0f020064:
/*  f020064:	3c017f1b */ 	lui	$at,%hi(var7f1a8700)
/*  f020068:	c42c8700 */ 	lwc1	$f12,%lo(var7f1a8700)($at)
/*  f02006c:	51600008 */ 	beqzl	$t3,.L0f020090
/*  f020070:	920f032d */ 	lbu	$t7,0x32d($s0)
/*  f020074:	920d032d */ 	lbu	$t5,0x32d($s0)
/*  f020078:	35ac0080 */ 	ori	$t4,$t5,0x80
/*  f02007c:	a20c032d */ 	sb	$t4,0x32d($s0)
/*  f020080:	8fae0114 */ 	lw	$t6,0x114($sp)
/*  f020084:	10000005 */ 	b	.L0f02009c
/*  f020088:	ae0e0364 */ 	sw	$t6,0x364($s0)
/*  f02008c:	920f032d */ 	lbu	$t7,0x32d($s0)
.L0f020090:
/*  f020090:	ae000364 */ 	sw	$zero,0x364($s0)
/*  f020094:	31f8ff7f */ 	andi	$t8,$t7,0xff7f
/*  f020098:	a218032d */ 	sb	$t8,0x32d($s0)
.L0f02009c:
/*  f02009c:	460c003c */ 	c.lt.s	$f0,$f12
/*  f0200a0:	00000000 */ 	nop
/*  f0200a4:	45020003 */ 	bc1fl	.L0f0200b4
/*  f0200a8:	8e0a0018 */ 	lw	$t2,0x18($s0)
/*  f0200ac:	46006086 */ 	mov.s	$f2,$f12
.L0f0200b0:
/*  f0200b0:	8e0a0018 */ 	lw	$t2,0x18($s0)
.L0f0200b4:
/*  f0200b4:	e60200b8 */ 	swc1	$f2,0xb8($s0)
/*  f0200b8:	c7aa00f0 */ 	lwc1	$f10,0xf0($sp)
/*  f0200bc:	31490001 */ 	andi	$t1,$t2,0x1
/*  f0200c0:	51200020 */ 	beqzl	$t1,.L0f020144
/*  f0200c4:	c60c00c0 */ 	lwc1	$f12,0xc0($s0)
/*  f0200c8:	c60600b8 */ 	lwc1	$f6,0xb8($s0)
/*  f0200cc:	c7a800f8 */ 	lwc1	$f8,0xf8($sp)
/*  f0200d0:	8fab0120 */ 	lw	$t3,0x120($sp)
/*  f0200d4:	46065100 */ 	add.s	$f4,$f10,$f6
/*  f0200d8:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*  f0200dc:	8d790008 */ 	lw	$t9,0x8($t3)
/*  f0200e0:	2401fffe */ 	addiu	$at,$zero,-2
/*  f0200e4:	46082281 */ 	sub.s	$f10,$f4,$f8
/*  f0200e8:	8f250000 */ 	lw	$a1,0x0($t9)
/*  f0200ec:	460a3100 */ 	add.s	$f4,$f6,$f10
/*  f0200f0:	94a20000 */ 	lhu	$v0,0x0($a1)
/*  f0200f4:	e6240004 */ 	swc1	$f4,0x4($s1)
/*  f0200f8:	8e0c0018 */ 	lw	$t4,0x18($s0)
/*  f0200fc:	c60200b8 */ 	lwc1	$f2,0xb8($s0)
/*  f020100:	304d00ff */ 	andi	$t5,$v0,0xff
/*  f020104:	01817024 */ 	and	$t6,$t4,$at
/*  f020108:	ae0e0018 */ 	sw	$t6,0x18($s0)
/*  f02010c:	3c017f1b */ 	lui	$at,%hi(var7f1a8704)
/*  f020110:	e60200b4 */ 	swc1	$f2,0xb4($s0)
/*  f020114:	c4288704 */ 	lwc1	$f8,%lo(var7f1a8704)($at)
/*  f020118:	24010001 */ 	addiu	$at,$zero,0x1
/*  f02011c:	46081182 */ 	mul.s	$f6,$f2,$f8
/*  f020120:	15a10005 */ 	bne	$t5,$at,.L0f020138
/*  f020124:	e60600b0 */ 	swc1	$f6,0xb0($s0)
/*  f020128:	0c006a87 */ 	jal	modelGetNodeRwData
/*  f02012c:	8fa40120 */ 	lw	$a0,0x120($sp)
/*  f020130:	c44a0028 */ 	lwc1	$f10,0x28($v0)
/*  f020134:	e44a0038 */ 	swc1	$f10,0x38($v0)
.L0f020138:
/*  f020138:	100000b6 */ 	b	.L0f020414
/*  f02013c:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020140:	c60c00c0 */ 	lwc1	$f12,0xc0($s0)
.L0f020144:
/*  f020144:	8faf0118 */ 	lw	$t7,0x118($sp)
/*  f020148:	27a400f0 */ 	addiu	$a0,$sp,0xf0
/*  f02014c:	460c9032 */ 	c.eq.s	$f18,$f12
/*  f020150:	27a50068 */ 	addiu	$a1,$sp,0x68
/*  f020154:	45020008 */ 	bc1fl	.L0f020178
/*  f020158:	91f80000 */ 	lbu	$t8,0x0($t7)
/*  f02015c:	c60200b8 */ 	lwc1	$f2,0xb8($s0)
/*  f020160:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020164:	4600103c */ 	c.lt.s	$f2,$f0
/*  f020168:	00000000 */ 	nop
/*  f02016c:	4502004a */ 	bc1fl	.L0f020298
/*  f020170:	4602003e */ 	c.le.s	$f0,$f2
/*  f020174:	91f80000 */ 	lbu	$t8,0x0($t7)
.L0f020178:
/*  f020178:	24010003 */ 	addiu	$at,$zero,0x3
/*  f02017c:	00001825 */ 	or	$v1,$zero,$zero
/*  f020180:	17010008 */ 	bne	$t8,$at,.L0f0201a4
/*  f020184:	3c017f1b */ 	lui	$at,%hi(var7f1a8708)
/*  f020188:	c4248708 */ 	lwc1	$f4,%lo(var7f1a8708)($at)
/*  f02018c:	c60800b4 */ 	lwc1	$f8,0xb4($s0)
/*  f020190:	4604403e */ 	c.le.s	$f8,$f4
/*  f020194:	00000000 */ 	nop
/*  f020198:	45020003 */ 	bc1fl	.L0f0201a8
/*  f02019c:	e7ac0068 */ 	swc1	$f12,0x68($sp)
/*  f0201a0:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f0201a4:
/*  f0201a4:	e7ac0068 */ 	swc1	$f12,0x68($sp)
.L0f0201a8:
/*  f0201a8:	8fa600dc */ 	lw	$a2,0xdc($sp)
/*  f0201ac:	0fc25979 */ 	jal	func0f0965e4
/*  f0201b0:	a3a30067 */ 	sb	$v1,0x67($sp)
/*  f0201b4:	02002025 */ 	or	$a0,$s0,$zero
/*  f0201b8:	02202825 */ 	or	$a1,$s1,$zero
/*  f0201bc:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f0201c0:	8fa700f0 */ 	lw	$a3,0xf0($sp)
/*  f0201c4:	0fc07c99 */ 	jal	func0f01f264
/*  f0201c8:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f0201cc:	44809000 */ 	mtc1	$zero,$f18
/*  f0201d0:	10400007 */ 	beqz	$v0,.L0f0201f0
/*  f0201d4:	93a30067 */ 	lbu	$v1,0x67($sp)
/*  f0201d8:	c60600b4 */ 	lwc1	$f6,0xb4($s0)
/*  f0201dc:	c7aa00f0 */ 	lwc1	$f10,0xf0($sp)
/*  f0201e0:	460a3100 */ 	add.s	$f4,$f6,$f10
/*  f0201e4:	e60400b4 */ 	swc1	$f4,0xb4($s0)
/*  f0201e8:	c7a80068 */ 	lwc1	$f8,0x68($sp)
/*  f0201ec:	e60800c0 */ 	swc1	$f8,0xc0($s0)
.L0f0201f0:
/*  f0201f0:	c60200b8 */ 	lwc1	$f2,0xb8($s0)
/*  f0201f4:	c60600b4 */ 	lwc1	$f6,0xb4($s0)
/*  f0201f8:	3c017f1b */ 	lui	$at,%hi(var7f1a870c)
/*  f0201fc:	4602303e */ 	c.le.s	$f6,$f2
/*  f020200:	00000000 */ 	nop
/*  f020204:	4500000b */ 	bc1f	.L0f020234
/*  f020208:	00000000 */ 	nop
/*  f02020c:	e60200b4 */ 	swc1	$f2,0xb4($s0)
/*  f020210:	c42a870c */ 	lwc1	$f10,%lo(var7f1a870c)($at)
/*  f020214:	e61200c0 */ 	swc1	$f18,0xc0($s0)
/*  f020218:	460a1102 */ 	mul.s	$f4,$f2,$f10
/*  f02021c:	e60400b0 */ 	swc1	$f4,0xb0($s0)
/*  f020220:	97aa00ea */ 	lhu	$t2,0xea($sp)
/*  f020224:	31494000 */ 	andi	$t1,$t2,0x4000
/*  f020228:	11200002 */ 	beqz	$t1,.L0f020234
/*  f02022c:	00000000 */ 	nop
/*  f020230:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f020234:
/*  f020234:	50600059 */ 	beqzl	$v1,.L0f02039c
/*  f020238:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f02023c:	8e0b02d4 */ 	lw	$t3,0x2d4($s0)
/*  f020240:	51600011 */ 	beqzl	$t3,.L0f020288
/*  f020244:	8e0d0014 */ 	lw	$t5,0x14($s0)
/*  f020248:	860200ec */ 	lh	$v0,0xec($s0)
/*  f02024c:	04400006 */ 	bltz	$v0,.L0f020268
/*  f020250:	00000000 */ 	nop
/*  f020254:	861900ee */ 	lh	$t9,0xee($s0)
/*  f020258:	1b200003 */ 	blez	$t9,.L0f020268
/*  f02025c:	00000000 */ 	nop
/*  f020260:	10000004 */ 	b	.L0f020274
/*  f020264:	00402825 */ 	or	$a1,$v0,$zero
.L0f020268:
/*  f020268:	0fc633fe */ 	jal	mpPlayerGetIndex
/*  f02026c:	02002025 */ 	or	$a0,$s0,$zero
/*  f020270:	00402825 */ 	or	$a1,$v0,$zero
.L0f020274:
/*  f020274:	0fc0d8d6 */ 	jal	chrDie
/*  f020278:	02002025 */ 	or	$a0,$s0,$zero
/*  f02027c:	10000047 */ 	b	.L0f02039c
/*  f020280:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020284:	8e0d0014 */ 	lw	$t5,0x14($s0)
.L0f020288:
/*  f020288:	35ac0020 */ 	ori	$t4,$t5,0x20
/*  f02028c:	10000042 */ 	b	.L0f020398
/*  f020290:	ae0c0014 */ 	sw	$t4,0x14($s0)
/*  f020294:	4602003e */ 	c.le.s	$f0,$f2
.L0f020298:
/*  f020298:	00000000 */ 	nop
/*  f02029c:	4502003f */ 	bc1fl	.L0f02039c
/*  f0202a0:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f0202a4:	8d0e0038 */ 	lw	$t6,0x38($t0)
/*  f0202a8:	00001025 */ 	or	$v0,$zero,$zero
/*  f0202ac:	19c00010 */ 	blez	$t6,.L0f0202f0
/*  f0202b0:	00000000 */ 	nop
/*  f0202b4:	c60800b0 */ 	lwc1	$f8,0xb0($s0)
.L0f0202b8:
/*  f0202b8:	c60400bc */ 	lwc1	$f4,0xbc($s0)
/*  f0202bc:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f0202c0:	46104182 */ 	mul.s	$f6,$f8,$f16
/*  f0202c4:	46023280 */ 	add.s	$f10,$f6,$f2
/*  f0202c8:	46102202 */ 	mul.s	$f8,$f4,$f16
/*  f0202cc:	c60600c4 */ 	lwc1	$f6,0xc4($s0)
/*  f0202d0:	e60a00b0 */ 	swc1	$f10,0xb0($s0)
/*  f0202d4:	46103282 */ 	mul.s	$f10,$f6,$f16
/*  f0202d8:	e60800bc */ 	swc1	$f8,0xbc($s0)
/*  f0202dc:	e60a00c4 */ 	swc1	$f10,0xc4($s0)
/*  f0202e0:	8d0f0038 */ 	lw	$t7,0x38($t0)
/*  f0202e4:	004f082a */ 	slt	$at,$v0,$t7
/*  f0202e8:	5420fff3 */ 	bnezl	$at,.L0f0202b8
/*  f0202ec:	c60800b0 */ 	lwc1	$f8,0xb0($s0)
.L0f0202f0:
/*  f0202f0:	3c017f1b */ 	lui	$at,%hi(var7f1a8710)
/*  f0202f4:	c4288710 */ 	lwc1	$f8,%lo(var7f1a8710)($at)
/*  f0202f8:	c60400b0 */ 	lwc1	$f4,0xb0($s0)
/*  f0202fc:	3c0141f0 */ 	lui	$at,0x41f0
/*  f020300:	44813000 */ 	mtc1	$at,$f6
/*  f020304:	46082002 */ 	mul.s	$f0,$f4,$f8
/*  f020308:	3c017f1b */ 	lui	$at,%hi(var7f1a8714)
/*  f02030c:	46061301 */ 	sub.s	$f12,$f2,$f6
/*  f020310:	460c003c */ 	c.lt.s	$f0,$f12
/*  f020314:	e60000b4 */ 	swc1	$f0,0xb4($s0)
/*  f020318:	45000005 */ 	bc1f	.L0f020330
/*  f02031c:	00000000 */ 	nop
/*  f020320:	e60c00b4 */ 	swc1	$f12,0xb4($s0)
/*  f020324:	c42a8714 */ 	lwc1	$f10,%lo(var7f1a8714)($at)
/*  f020328:	460a6102 */ 	mul.s	$f4,$f12,$f10
/*  f02032c:	e60400b0 */ 	swc1	$f4,0xb0($s0)
.L0f020330:
/*  f020330:	3c017f1b */ 	lui	$at,%hi(var7f1a8718)
/*  f020334:	c4288718 */ 	lwc1	$f8,%lo(var7f1a8718)($at)
/*  f020338:	c60000bc */ 	lwc1	$f0,0xbc($s0)
/*  f02033c:	3c017f1b */ 	lui	$at,%hi(var7f1a871c)
/*  f020340:	4608003c */ 	c.lt.s	$f0,$f8
/*  f020344:	00000000 */ 	nop
/*  f020348:	45020014 */ 	bc1fl	.L0f02039c
/*  f02034c:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020350:	c422871c */ 	lwc1	$f2,%lo(var7f1a871c)($at)
/*  f020354:	3c017f1b */ 	lui	$at,%hi(var7f1a8720)
/*  f020358:	4600103c */ 	c.lt.s	$f2,$f0
/*  f02035c:	00000000 */ 	nop
/*  f020360:	4502000e */ 	bc1fl	.L0f02039c
/*  f020364:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020368:	c60000c4 */ 	lwc1	$f0,0xc4($s0)
/*  f02036c:	c4268720 */ 	lwc1	$f6,%lo(var7f1a8720)($at)
/*  f020370:	4606003c */ 	c.lt.s	$f0,$f6
/*  f020374:	00000000 */ 	nop
/*  f020378:	45020008 */ 	bc1fl	.L0f02039c
/*  f02037c:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020380:	4600103c */ 	c.lt.s	$f2,$f0
/*  f020384:	00000000 */ 	nop
/*  f020388:	45020004 */ 	bc1fl	.L0f02039c
/*  f02038c:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f020390:	e61200c4 */ 	swc1	$f18,0xc4($s0)
/*  f020394:	e61200bc */ 	swc1	$f18,0xbc($s0)
.L0f020398:
/*  f020398:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
.L0f02039c:
/*  f02039c:	c7aa00f8 */ 	lwc1	$f10,0xf8($sp)
/*  f0203a0:	46005032 */ 	c.eq.s	$f10,$f0
/*  f0203a4:	00000000 */ 	nop
/*  f0203a8:	4503001b */ 	bc1tl	.L0f020418
/*  f0203ac:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*  f0203b0:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f0203b4:	27a400fc */ 	addiu	$a0,$sp,0xfc
/*  f0203b8:	27a500c0 */ 	addiu	$a1,$sp,0xc0
/*  f0203bc:	e7a400d0 */ 	swc1	$f4,0xd0($sp)
/*  f0203c0:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*  f0203c4:	e7a800d4 */ 	swc1	$f8,0xd4($sp)
/*  f0203c8:	c6260008 */ 	lwc1	$f6,0x8($s1)
/*  f0203cc:	0fc195e9 */ 	jal	roomsCopy
/*  f0203d0:	e7a600d8 */ 	swc1	$f6,0xd8($sp)
/*  f0203d4:	c60a00b4 */ 	lwc1	$f10,0xb4($s0)
/*  f0203d8:	c7a400f8 */ 	lwc1	$f4,0xf8($sp)
/*  f0203dc:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*  f0203e0:	27a400d0 */ 	addiu	$a0,$sp,0xd0
/*  f0203e4:	46045201 */ 	sub.s	$f8,$f10,$f4
/*  f0203e8:	27a500c0 */ 	addiu	$a1,$sp,0xc0
/*  f0203ec:	02203025 */ 	or	$a2,$s1,$zero
/*  f0203f0:	27a700fc */ 	addiu	$a3,$sp,0xfc
/*  f0203f4:	46083280 */ 	add.s	$f10,$f6,$f8
/*  f0203f8:	0fc1979d */ 	jal	func0f065e74
/*  f0203fc:	e62a0004 */ 	swc1	$f10,0x4($s1)
/*  f020400:	02002025 */ 	or	$a0,$s0,$zero
/*  f020404:	02202825 */ 	or	$a1,$s1,$zero
/*  f020408:	0fc087ea */ 	jal	func0f021fa8
/*  f02040c:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f020410:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
.L0f020414:
/*  f020414:	c6240004 */ 	lwc1	$f4,0x4($s1)
.L0f020418:
/*  f020418:	46002181 */ 	sub.s	$f6,$f4,$f0
/*  f02041c:	e6260004 */ 	swc1	$f6,0x4($s1)
.L0f020420:
/*  f020420:	c60800b4 */ 	lwc1	$f8,0xb4($s0)
/*  f020424:	8fb8012c */ 	lw	$t8,0x12c($sp)
/*  f020428:	8fa40118 */ 	lw	$a0,0x118($sp)
/*  f02042c:	24010023 */ 	addiu	$at,$zero,0x23
/*  f020430:	e7080000 */ 	swc1	$f8,0x0($t8)
/*  f020434:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f020438:	e48a0008 */ 	swc1	$f10,0x8($a0)
/*  f02043c:	c60600b4 */ 	lwc1	$f6,0xb4($s0)
/*  f020440:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*  f020444:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f020448:	e488000c */ 	swc1	$f8,0xc($a0)
/*  f02044c:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*  f020450:	e48a0010 */ 	swc1	$f10,0x10($a0)
/*  f020454:	820a0007 */ 	lb	$t2,0x7($s0)
/*  f020458:	1541000c */ 	bne	$t2,$at,.L0f02048c
/*  f02045c:	00000000 */ 	nop
/*  f020460:	c6020050 */ 	lwc1	$f2,0x50($s0)
/*  f020464:	c484000c */ 	lwc1	$f4,0xc($a0)
/*  f020468:	4602203c */ 	c.lt.s	$f4,$f2
/*  f02046c:	00000000 */ 	nop
/*  f020470:	45000006 */ 	bc1f	.L0f02048c
/*  f020474:	00000000 */ 	nop
/*  f020478:	e482000c */ 	swc1	$f2,0xc($a0)
/*  f02047c:	c6000050 */ 	lwc1	$f0,0x50($s0)
/*  f020480:	e60000b4 */ 	swc1	$f0,0xb4($s0)
/*  f020484:	8fa9012c */ 	lw	$t1,0x12c($sp)
/*  f020488:	e5200000 */ 	swc1	$f0,0x0($t1)
.L0f02048c:
/*  f02048c:	0fc19711 */ 	jal	propDeregisterRooms
/*  f020490:	00000000 */ 	nop
/*  f020494:	27a400fc */ 	addiu	$a0,$sp,0xfc
/*  f020498:	0fc195e9 */ 	jal	roomsCopy
/*  f02049c:	8fa50048 */ 	lw	$a1,0x48($sp)
/*  f0204a0:	8fa60118 */ 	lw	$a2,0x118($sp)
/*  f0204a4:	24010003 */ 	addiu	$at,$zero,0x3
/*  f0204a8:	90cb0000 */ 	lbu	$t3,0x0($a2)
/*  f0204ac:	15610016 */ 	bne	$t3,$at,.L0f020508
/*  f0204b0:	00000000 */ 	nop
/*  f0204b4:	84d90028 */ 	lh	$t9,0x28($a2)
/*  f0204b8:	2405ffff */ 	addiu	$a1,$zero,-1
/*  f0204bc:	00c01025 */ 	or	$v0,$a2,$zero
/*  f0204c0:	10b90011 */ 	beq	$a1,$t9,.L0f020508
/*  f0204c4:	00000000 */ 	nop
/*  f0204c8:	860402b2 */ 	lh	$a0,0x2b2($s0)
/*  f0204cc:	84c30028 */ 	lh	$v1,0x28($a2)
.L0f0204d0:
/*  f0204d0:	5483000a */ 	bnel	$a0,$v1,.L0f0204fc
/*  f0204d4:	8443002a */ 	lh	$v1,0x2a($v0)
/*  f0204d8:	0fc19711 */ 	jal	propDeregisterRooms
/*  f0204dc:	00c02025 */ 	or	$a0,$a2,$zero
/*  f0204e0:	8fac0118 */ 	lw	$t4,0x118($sp)
/*  f0204e4:	860d02b2 */ 	lh	$t5,0x2b2($s0)
/*  f0204e8:	2405ffff */ 	addiu	$a1,$zero,-1
/*  f0204ec:	a585002a */ 	sh	$a1,0x2a($t4)
/*  f0204f0:	10000005 */ 	b	.L0f020508
/*  f0204f4:	a58d0028 */ 	sh	$t5,0x28($t4)
/*  f0204f8:	8443002a */ 	lh	$v1,0x2a($v0)
.L0f0204fc:
/*  f0204fc:	24420002 */ 	addiu	$v0,$v0,0x2
/*  f020500:	14a3fff3 */ 	bne	$a1,$v1,.L0f0204d0
/*  f020504:	00000000 */ 	nop
.L0f020508:
/*  f020508:	0fc0882b */ 	jal	func0f0220ac
/*  f02050c:	02002025 */ 	or	$a0,$s0,$zero
/*  f020510:	8fa40118 */ 	lw	$a0,0x118($sp)
/*  f020514:	260500fc */ 	addiu	$a1,$s0,0xfc
/*  f020518:	0fc1a451 */ 	jal	func0f069144
/*  f02051c:	9606018a */ 	lhu	$a2,0x18a($s0)
/*  f020520:	8fbf0034 */ 	lw	$ra,0x34($sp)
/*  f020524:	8fb0002c */ 	lw	$s0,0x2c($sp)
/*  f020528:	8fb10030 */ 	lw	$s1,0x30($sp)
/*  f02052c:	27bd0120 */ 	addiu	$sp,$sp,0x120
/*  f020530:	03e00008 */ 	jr	$ra
/*  f020534:	24020001 */ 	addiu	$v0,$zero,0x1
);
#else
GLOBAL_ASM(
glabel func0f01f378
.late_rodata
glabel var7f1a86ac
.word 0xc9742400
glabel var7f1a86b0
.word 0x411ffffe
glabel var7f1a86b4
.word 0x3f8ccccd
glabel var7f1a86b8
.word 0x3f8ccccd
glabel var7f1a86bc
.word 0x3f666666
glabel var7f1a86c0
.word 0x3f666666
glabel var7f1a86c4
.word 0x3dcccccd
glabel var7f1a86c8
.word 0x3f666666
glabel var7f1a86cc
.word 0x3f666666
glabel var7f1a86d0
.word 0x3f666666
glabel var7f1a86d4
.word 0x3f666666
glabel var7f1a86d8
.word 0x3f666666
glabel var7f1a86dc
.word 0x411ffffe
glabel var7f1a86e0
.word 0x411ffffe
glabel var7f1a86e4
.word 0x3f666666
glabel var7f1a86e8
.word 0x3f666666
glabel var7f1a86ec
.word 0x3f666666
glabel var7f1a86f0
.word 0x3f666666
glabel var7f1a86f4
.word 0xc7c35000
glabel var7f1a8704
.word 0x411ffffe
glabel var7f1a8708
.word 0xc6ea6000
glabel var7f1a870c
.word 0x411ffffe
glabel var7f1a8710
.word 0x3dccccd0
glabel var7f1a8714
.word 0x411ffffe
glabel var7f1a8718
.word 0x3dcccccd
glabel var7f1a871c
.word 0xbdcccccd
glabel var7f1a8720
.word 0x3dcccccd
.text
/*  f01f140:	27bdff10 */ 	addiu	$sp,$sp,-240
/*  f01f144:	afbf0034 */ 	sw	$ra,0x34($sp)
/*  f01f148:	afb10030 */ 	sw	$s1,0x30($sp)
/*  f01f14c:	afb0002c */ 	sw	$s0,0x2c($sp)
/*  f01f150:	afa400f0 */ 	sw	$a0,0xf0($sp)
/*  f01f154:	afa500f4 */ 	sw	$a1,0xf4($sp)
/*  f01f158:	afa700fc */ 	sw	$a3,0xfc($sp)
/*  f01f15c:	8c900004 */ 	lw	$s0,0x4($a0)
/*  f01f160:	44809000 */ 	mtc1	$zero,$f18
/*  f01f164:	00c08825 */ 	or	$s1,$a2,$zero
/*  f01f168:	8e0f001c */ 	lw	$t7,0x1c($s0)
/*  f01f16c:	afaf00e8 */ 	sw	$t7,0xe8($sp)
/*  f01f170:	c60400b4 */ 	lwc1	$f4,0xb4($s0)
/*  f01f174:	12000004 */ 	beqz	$s0,.NB0f01f188
/*  f01f178:	e7a400c8 */ 	swc1	$f4,0xc8($sp)
/*  f01f17c:	921802fe */ 	lbu	$t8,0x2fe($s0)
/*  f01f180:	10000002 */ 	beqz	$zero,.NB0f01f18c
/*  f01f184:	afb800c4 */ 	sw	$t8,0xc4($sp)
.NB0f01f188:
/*  f01f188:	afa000c4 */ 	sw	$zero,0xc4($sp)
.NB0f01f18c:
/*  f01f18c:	8fa900f0 */ 	lw	$t1,0xf0($sp)
/*  f01f190:	e7b200c0 */ 	swc1	$f18,0xc0($sp)
/*  f01f194:	a7a000ba */ 	sh	$zero,0xba($sp)
/*  f01f198:	8d2a0020 */ 	lw	$t2,0x20($t1)
/*  f01f19c:	3c198006 */ 	lui	$t9,0x8006
/*  f01f1a0:	8f39151c */ 	lw	$t9,0x151c($t9)
/*  f01f1a4:	854b0000 */ 	lh	$t3,0x0($t2)
/*  f01f1a8:	c7aa00c8 */ 	lwc1	$f10,0xc8($sp)
/*  f01f1ac:	000b6080 */ 	sll	$t4,$t3,0x2
/*  f01f1b0:	018b6023 */ 	subu	$t4,$t4,$t3
/*  f01f1b4:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f01f1b8:	032c6821 */ 	addu	$t5,$t9,$t4
/*  f01f1bc:	91ae000b */ 	lbu	$t6,0xb($t5)
/*  f01f1c0:	31cf0002 */ 	andi	$t7,$t6,0x2
/*  f01f1c4:	51e0003a */ 	beqzl	$t7,.NB0f01f2b0
/*  f01f1c8:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*  f01f1cc:	8e180014 */ 	lw	$t8,0x14($s0)
/*  f01f1d0:	8fab00e8 */ 	lw	$t3,0xe8($sp)
/*  f01f1d4:	02203025 */ 	or	$a2,$s1,$zero
/*  f01f1d8:	00184b80 */ 	sll	$t1,$t8,0xe
/*  f01f1dc:	0521000a */ 	bgez	$t1,.NB0f01f208
/*  f01f1e0:	25640008 */ 	addiu	$a0,$t3,0x8
/*  f01f1e4:	8faa00e8 */ 	lw	$t2,0xe8($sp)
/*  f01f1e8:	02203025 */ 	or	$a2,$s1,$zero
/*  f01f1ec:	27a700cc */ 	addiu	$a3,$sp,0xcc
/*  f01f1f0:	25450028 */ 	addiu	$a1,$t2,0x28
/*  f01f1f4:	afa50044 */ 	sw	$a1,0x44($sp)
/*  f01f1f8:	0fc19440 */ 	jal	func0f065e98
/*  f01f1fc:	25440008 */ 	addiu	$a0,$t2,0x8
/*  f01f200:	10000006 */ 	beqz	$zero,.NB0f01f21c
/*  f01f204:	8e050024 */ 	lw	$a1,0x24($s0)
.NB0f01f208:
/*  f01f208:	25650028 */ 	addiu	$a1,$t3,0x28
/*  f01f20c:	afa50044 */ 	sw	$a1,0x44($sp)
/*  f01f210:	0fc19437 */ 	jal	func0f065e74
/*  f01f214:	27a700cc */ 	addiu	$a3,$sp,0xcc
/*  f01f218:	8e050024 */ 	lw	$a1,0x24($s0)
.NB0f01f21c:
/*  f01f21c:	26190191 */ 	addiu	$t9,$s0,0x191
/*  f01f220:	27ac00ba */ 	addiu	$t4,$sp,0xba
/*  f01f224:	260d02b2 */ 	addiu	$t5,$s0,0x2b2
/*  f01f228:	27ae00bc */ 	addiu	$t6,$sp,0xbc
/*  f01f22c:	27af00e4 */ 	addiu	$t7,$sp,0xe4
/*  f01f230:	afaf0020 */ 	sw	$t7,0x20($sp)
/*  f01f234:	afae001c */ 	sw	$t6,0x1c($sp)
/*  f01f238:	afad0018 */ 	sw	$t5,0x18($sp)
/*  f01f23c:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f01f240:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f01f244:	02202025 */ 	or	$a0,$s1,$zero
/*  f01f248:	27a600cc */ 	addiu	$a2,$sp,0xcc
/*  f01f24c:	0c00ad7e */ 	jal	cdFindGroundY
/*  f01f250:	2607018a */ 	addiu	$a3,$s0,0x18a
/*  f01f254:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01f258:	c4262348 */ 	lwc1	$f6,0x2348($at)
/*  f01f25c:	44809000 */ 	mtc1	$zero,$f18
/*  f01f260:	46000086 */ 	mov.s	$f2,$f0
/*  f01f264:	4606003c */ 	c.lt.s	$f0,$f6
/*  f01f268:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01f26c:	45020003 */ 	bc1fl	.NB0f01f27c
/*  f01f270:	e60200b8 */ 	swc1	$f2,0xb8($s0)
/*  f01f274:	46009086 */ 	mov.s	$f2,$f18
/*  f01f278:	e60200b8 */ 	swc1	$f2,0xb8($s0)
.NB0f01f27c:
/*  f01f27c:	e6120038 */ 	swc1	$f18,0x38($s0)
/*  f01f280:	e61200bc */ 	swc1	$f18,0xbc($s0)
/*  f01f284:	e61200c0 */ 	swc1	$f18,0xc0($s0)
/*  f01f288:	e61200c4 */ 	swc1	$f18,0xc4($s0)
/*  f01f28c:	e60200b4 */ 	swc1	$f2,0xb4($s0)
/*  f01f290:	c428234c */ 	lwc1	$f8,0x234c($at)
/*  f01f294:	46081282 */ 	mul.s	$f10,$f2,$f8
/*  f01f298:	e60a00b0 */ 	swc1	$f10,0xb0($s0)
/*  f01f29c:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*  f01f2a0:	46022181 */ 	sub.s	$f6,$f4,$f2
/*  f01f2a4:	10000349 */ 	beqz	$zero,.NB0f01ffcc
/*  f01f2a8:	e6260004 */ 	swc1	$f6,0x4($s1)
/*  f01f2ac:	c6280004 */ 	lwc1	$f8,0x4($s1)
.NB0f01f2b0:
/*  f01f2b0:	3c098006 */ 	lui	$t1,0x8006
/*  f01f2b4:	27a500b0 */ 	addiu	$a1,$sp,0xb0
/*  f01f2b8:	460a4100 */ 	add.s	$f4,$f8,$f10
/*  f01f2bc:	3c08800a */ 	lui	$t0,0x800a
/*  f01f2c0:	25294ea0 */ 	addiu	$t1,$t1,0x4ea0
/*  f01f2c4:	e6240004 */ 	swc1	$f4,0x4($s1)
/*  f01f2c8:	8e1802d4 */ 	lw	$t8,0x2d4($s0)
/*  f01f2cc:	53000017 */ 	beqzl	$t8,.NB0f01f32c
/*  f01f2d0:	82020007 */ 	lb	$v0,0x7($s0)
/*  f01f2d4:	8d210000 */ 	lw	$at,0x0($t1)
/*  f01f2d8:	2508e6c0 */ 	addiu	$t0,$t0,-6464
/*  f01f2dc:	8d190034 */ 	lw	$t9,0x34($t0)
/*  f01f2e0:	aca10000 */ 	sw	$at,0x0($a1)
/*  f01f2e4:	8d2b0004 */ 	lw	$t3,0x4($t1)
/*  f01f2e8:	1b200005 */ 	blez	$t9,.NB0f01f300
/*  f01f2ec:	acab0004 */ 	sw	$t3,0x4($a1)
/*  f01f2f0:	0fc630b7 */ 	jal	func0f1921f8
/*  f01f2f4:	02002025 */ 	or	$a0,$s0,$zero
/*  f01f2f8:	44809000 */ 	mtc1	$zero,$f18
/*  f01f2fc:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f01f300:
/*  f01f300:	8fac00f4 */ 	lw	$t4,0xf4($sp)
/*  f01f304:	c7a600b0 */ 	lwc1	$f6,0xb0($sp)
/*  f01f308:	c5880000 */ 	lwc1	$f8,0x0($t4)
/*  f01f30c:	46083280 */ 	add.s	$f10,$f6,$f8
/*  f01f310:	e62a0000 */ 	swc1	$f10,0x0($s1)
/*  f01f314:	8fad00f4 */ 	lw	$t5,0xf4($sp)
/*  f01f318:	c7a400b4 */ 	lwc1	$f4,0xb4($sp)
/*  f01f31c:	c5a60008 */ 	lwc1	$f6,0x8($t5)
/*  f01f320:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f01f324:	e6280008 */ 	swc1	$f8,0x8($s1)
/*  f01f328:	82020007 */ 	lb	$v0,0x7($s0)
.NB0f01f32c:
/*  f01f32c:	3c08800a */ 	lui	$t0,0x800a
/*  f01f330:	2401000e */ 	addiu	$at,$zero,0xe
/*  f01f334:	10410003 */ 	beq	$v0,$at,.NB0f01f344
/*  f01f338:	2508e6c0 */ 	addiu	$t0,$t0,-6464
/*  f01f33c:	2401000f */ 	addiu	$at,$zero,0xf
/*  f01f340:	1441001f */ 	bne	$v0,$at,.NB0f01f3c0
.NB0f01f344:
/*  f01f344:	3c014020 */ 	lui	$at,0x4020
/*  f01f348:	44812000 */ 	mtc1	$at,$f4
/*  f01f34c:	c60a0024 */ 	lwc1	$f10,0x24($s0)
/*  f01f350:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01f354:	c6080028 */ 	lwc1	$f8,0x28($s0)
/*  f01f358:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f01f35c:	3c013f80 */ 	lui	$at,0x3f80
/*  f01f360:	8e02001c */ 	lw	$v0,0x1c($s0)
/*  f01f364:	240f0040 */ 	addiu	$t7,$zero,0x40
/*  f01f368:	26180320 */ 	addiu	$t8,$s0,0x320
/*  f01f36c:	46080280 */ 	add.s	$f10,$f0,$f8
/*  f01f370:	c442000c */ 	lwc1	$f2,0xc($v0)
/*  f01f374:	44053000 */ 	mfc1	$a1,$f6
/*  f01f378:	44813000 */ 	mtc1	$at,$f6
/*  f01f37c:	46025101 */ 	sub.s	$f4,$f10,$f2
/*  f01f380:	244e0028 */ 	addiu	$t6,$v0,0x28
/*  f01f384:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f01f388:	46060200 */ 	add.s	$f8,$f0,$f6
/*  f01f38c:	44062000 */ 	mfc1	$a2,$f4
/*  f01f390:	afb80018 */ 	sw	$t8,0x18($sp)
/*  f01f394:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f01f398:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f01f39c:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f01f3a0:	44075000 */ 	mfc1	$a3,$f10
/*  f01f3a4:	0c00ad11 */ 	jal	func00029ffc
/*  f01f3a8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f3ac:	3c08800a */ 	lui	$t0,0x800a
/*  f01f3b0:	44809000 */ 	mtc1	$zero,$f18
/*  f01f3b4:	2508e6c0 */ 	addiu	$t0,$t0,-6464
/*  f01f3b8:	10000002 */ 	beqz	$zero,.NB0f01f3c4
/*  f01f3bc:	ae02031c */ 	sw	$v0,0x31c($s0)
.NB0f01f3c0:
/*  f01f3c0:	ae00031c */ 	sw	$zero,0x31c($s0)
.NB0f01f3c4:
/*  f01f3c4:	8e0a02d4 */ 	lw	$t2,0x2d4($s0)
/*  f01f3c8:	3c014339 */ 	lui	$at,0x4339
/*  f01f3cc:	51400074 */ 	beqzl	$t2,.NB0f01f5a0
/*  f01f3d0:	820b0007 */ 	lb	$t3,0x7($s0)
/*  f01f3d4:	44816000 */ 	mtc1	$at,$f12
/*  f01f3d8:	82020007 */ 	lb	$v0,0x7($s0)
/*  f01f3dc:	2401000f */ 	addiu	$at,$zero,0xf
/*  f01f3e0:	e60c0028 */ 	swc1	$f12,0x28($s0)
/*  f01f3e4:	5441000a */ 	bnel	$v0,$at,.NB0f01f410
/*  f01f3e8:	2401000f */ 	addiu	$at,$zero,0xf
/*  f01f3ec:	92090065 */ 	lbu	$t1,0x65($s0)
/*  f01f3f0:	3c014307 */ 	lui	$at,0x4307
/*  f01f3f4:	312b0080 */ 	andi	$t3,$t1,0x80
/*  f01f3f8:	51600005 */ 	beqzl	$t3,.NB0f01f410
/*  f01f3fc:	2401000f */ 	addiu	$at,$zero,0xf
/*  f01f400:	44812000 */ 	mtc1	$at,$f4
/*  f01f404:	10000046 */ 	beqz	$zero,.NB0f01f520
/*  f01f408:	e6040028 */ 	swc1	$f4,0x28($s0)
/*  f01f40c:	2401000f */ 	addiu	$at,$zero,0xf
.NB0f01f410:
/*  f01f410:	14410009 */ 	bne	$v0,$at,.NB0f01f438
/*  f01f414:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f418:	92190065 */ 	lbu	$t9,0x65($s0)
/*  f01f41c:	3c0142b4 */ 	lui	$at,0x42b4
/*  f01f420:	332c0040 */ 	andi	$t4,$t9,0x40
/*  f01f424:	11800004 */ 	beqz	$t4,.NB0f01f438
/*  f01f428:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f42c:	44813000 */ 	mtc1	$at,$f6
/*  f01f430:	1000003b */ 	beqz	$zero,.NB0f01f520
/*  f01f434:	e6060028 */ 	swc1	$f6,0x28($s0)
.NB0f01f438:
/*  f01f438:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01f43c:	c42a2350 */ 	lwc1	$f10,0x2350($at)
/*  f01f440:	c6080024 */ 	lwc1	$f8,0x24($s0)
/*  f01f444:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01f448:	3c014120 */ 	lui	$at,0x4120
/*  f01f44c:	460a4102 */ 	mul.s	$f4,$f8,$f10
/*  f01f450:	44815000 */ 	mtc1	$at,$f10
/*  f01f454:	8e02001c */ 	lw	$v0,0x1c($s0)
/*  f01f458:	240e1000 */ 	addiu	$t6,$zero,0x1000
/*  f01f45c:	460c0180 */ 	add.s	$f6,$f0,$f12
/*  f01f460:	c442000c */ 	lwc1	$f2,0xc($v0)
/*  f01f464:	44052000 */ 	mfc1	$a1,$f4
/*  f01f468:	460a0101 */ 	sub.s	$f4,$f0,$f10
/*  f01f46c:	244d0028 */ 	addiu	$t5,$v0,0x28
/*  f01f470:	afad0010 */ 	sw	$t5,0x10($sp)
/*  f01f474:	46023201 */ 	sub.s	$f8,$f6,$f2
/*  f01f478:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f01f47c:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f01f480:	46022181 */ 	sub.s	$f6,$f4,$f2
/*  f01f484:	44064000 */ 	mfc1	$a2,$f8
/*  f01f488:	44073000 */ 	mfc1	$a3,$f6
/*  f01f48c:	0c00ad61 */ 	jal	func0002a13c
/*  f01f490:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f494:	10400005 */ 	beqz	$v0,.NB0f01f4ac
/*  f01f498:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01f49c:	3c014307 */ 	lui	$at,0x4307
/*  f01f4a0:	44814000 */ 	mtc1	$at,$f8
/*  f01f4a4:	1000001e */ 	beqz	$zero,.NB0f01f520
/*  f01f4a8:	e6080028 */ 	swc1	$f8,0x28($s0)
.NB0f01f4ac:
/*  f01f4ac:	c60a0024 */ 	lwc1	$f10,0x24($s0)
/*  f01f4b0:	c4242354 */ 	lwc1	$f4,0x2354($at)
/*  f01f4b4:	3c014307 */ 	lui	$at,0x4307
/*  f01f4b8:	44814000 */ 	mtc1	$at,$f8
/*  f01f4bc:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f01f4c0:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01f4c4:	3c014120 */ 	lui	$at,0x4120
/*  f01f4c8:	8e02001c */ 	lw	$v0,0x1c($s0)
/*  f01f4cc:	24180800 */ 	addiu	$t8,$zero,0x800
/*  f01f4d0:	46080280 */ 	add.s	$f10,$f0,$f8
/*  f01f4d4:	c442000c */ 	lwc1	$f2,0xc($v0)
/*  f01f4d8:	44053000 */ 	mfc1	$a1,$f6
/*  f01f4dc:	44813000 */ 	mtc1	$at,$f6
/*  f01f4e0:	46025101 */ 	sub.s	$f4,$f10,$f2
/*  f01f4e4:	244f0028 */ 	addiu	$t7,$v0,0x28
/*  f01f4e8:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f01f4ec:	46060201 */ 	sub.s	$f8,$f0,$f6
/*  f01f4f0:	44062000 */ 	mfc1	$a2,$f4
/*  f01f4f4:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f01f4f8:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f01f4fc:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f01f500:	44075000 */ 	mfc1	$a3,$f10
/*  f01f504:	0c00ad61 */ 	jal	func0002a13c
/*  f01f508:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f50c:	10400004 */ 	beqz	$v0,.NB0f01f520
/*  f01f510:	3c0142b4 */ 	lui	$at,0x42b4
/*  f01f514:	44812000 */ 	mtc1	$at,$f4
/*  f01f518:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f51c:	e6040028 */ 	swc1	$f4,0x28($s0)
.NB0f01f520:
/*  f01f520:	8e0402d4 */ 	lw	$a0,0x2d4($s0)
/*  f01f524:	0fc3244d */ 	jal	bmove0f0cb904
/*  f01f528:	24840108 */ 	addiu	$a0,$a0,0x108
/*  f01f52c:	8e0a02d4 */ 	lw	$t2,0x2d4($s0)
/*  f01f530:	3c028007 */ 	lui	$v0,0x8007
/*  f01f534:	24427fa0 */ 	addiu	$v0,$v0,0x7fa0
/*  f01f538:	c4480024 */ 	lwc1	$f8,0x24($v0)
/*  f01f53c:	c5460108 */ 	lwc1	$f6,0x108($t2)
/*  f01f540:	3c08800a */ 	lui	$t0,0x800a
/*  f01f544:	2508e6c0 */ 	addiu	$t0,$t0,-6464
/*  f01f548:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f01f54c:	c504004c */ 	lwc1	$f4,0x4c($t0)
/*  f01f550:	3c013f00 */ 	lui	$at,0x3f00
/*  f01f554:	44810000 */ 	mtc1	$at,$f0
/*  f01f558:	44809000 */ 	mtc1	$zero,$f18
/*  f01f55c:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f01f560:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f01f564:	46003202 */ 	mul.s	$f8,$f6,$f0
/*  f01f568:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f01f56c:	e6240000 */ 	swc1	$f4,0x0($s1)
/*  f01f570:	8e0902d4 */ 	lw	$t1,0x2d4($s0)
/*  f01f574:	c44a0024 */ 	lwc1	$f10,0x24($v0)
/*  f01f578:	c504004c */ 	lwc1	$f4,0x4c($t0)
/*  f01f57c:	c5260110 */ 	lwc1	$f6,0x110($t1)
/*  f01f580:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f01f584:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f588:	46044182 */ 	mul.s	$f6,$f8,$f4
/*  f01f58c:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*  f01f590:	46003282 */ 	mul.s	$f10,$f6,$f0
/*  f01f594:	460a4100 */ 	add.s	$f4,$f8,$f10
/*  f01f598:	e6240008 */ 	swc1	$f4,0x8($s1)
/*  f01f59c:	820b0007 */ 	lb	$t3,0x7($s0)
.NB0f01f5a0:
/*  f01f5a0:	24010004 */ 	addiu	$at,$zero,0x4
/*  f01f5a4:	5561002f */ 	bnel	$t3,$at,.NB0f01f664
/*  f01f5a8:	c60202e8 */ 	lwc1	$f2,0x2e8($s0)
/*  f01f5ac:	c6020038 */ 	lwc1	$f2,0x38($s0)
/*  f01f5b0:	8fb900f0 */ 	lw	$t9,0xf0($sp)
/*  f01f5b4:	4602903c */ 	c.lt.s	$f18,$f2
/*  f01f5b8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f5bc:	45020029 */ 	bc1fl	.NB0f01f664
/*  f01f5c0:	c60202e8 */ 	lwc1	$f2,0x2e8($s0)
/*  f01f5c4:	8f2c0020 */ 	lw	$t4,0x20($t9)
/*  f01f5c8:	c5080044 */ 	lwc1	$f8,0x44($t0)
/*  f01f5cc:	c604003c */ 	lwc1	$f4,0x3c($s0)
/*  f01f5d0:	c5860074 */ 	lwc1	$f6,0x74($t4)
/*  f01f5d4:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f01f5d8:	46041181 */ 	sub.s	$f6,$f2,$f4
/*  f01f5dc:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f01f5e0:	46065202 */ 	mul.s	$f8,$f10,$f6
/*  f01f5e4:	c60a0040 */ 	lwc1	$f10,0x40($s0)
/*  f01f5e8:	46024003 */ 	div.s	$f0,$f8,$f2
/*  f01f5ec:	46005182 */ 	mul.s	$f6,$f10,$f0
/*  f01f5f0:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*  f01f5f4:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f01f5f8:	e6280000 */ 	swc1	$f8,0x0($s1)
/*  f01f5fc:	c6040048 */ 	lwc1	$f4,0x48($s0)
/*  f01f600:	46002182 */ 	mul.s	$f6,$f4,$f0
/*  f01f604:	46065200 */ 	add.s	$f8,$f10,$f6
/*  f01f608:	e6280008 */ 	swc1	$f8,0x8($s1)
/*  f01f60c:	c60a0044 */ 	lwc1	$f10,0x44($s0)
/*  f01f610:	c7a400c0 */ 	lwc1	$f4,0xc0($sp)
/*  f01f614:	8fad00f0 */ 	lw	$t5,0xf0($sp)
/*  f01f618:	46005182 */ 	mul.s	$f6,$f10,$f0
/*  f01f61c:	c50a0044 */ 	lwc1	$f10,0x44($t0)
/*  f01f620:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f01f624:	e7a800c0 */ 	swc1	$f8,0xc0($sp)
/*  f01f628:	8dae0020 */ 	lw	$t6,0x20($t5)
/*  f01f62c:	c608003c */ 	lwc1	$f8,0x3c($s0)
/*  f01f630:	c5c40074 */ 	lwc1	$f4,0x74($t6)
/*  f01f634:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f01f638:	c6040038 */ 	lwc1	$f4,0x38($s0)
/*  f01f63c:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f01f640:	e60a003c */ 	swc1	$f10,0x3c($s0)
/*  f01f644:	c608003c */ 	lwc1	$f8,0x3c($s0)
/*  f01f648:	4608203c */ 	c.lt.s	$f4,$f8
/*  f01f64c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f650:	45020030 */ 	bc1fl	.NB0f01f714
/*  f01f654:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01f658:	1000002d */ 	beqz	$zero,.NB0f01f710
/*  f01f65c:	e6120038 */ 	swc1	$f18,0x38($s0)
/*  f01f660:	c60202e8 */ 	lwc1	$f2,0x2e8($s0)
.NB0f01f664:
/*  f01f664:	8faf00f0 */ 	lw	$t7,0xf0($sp)
/*  f01f668:	4602903c */ 	c.lt.s	$f18,$f2
/*  f01f66c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f670:	45020028 */ 	bc1fl	.NB0f01f714
/*  f01f674:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01f678:	8df80020 */ 	lw	$t8,0x20($t7)
/*  f01f67c:	c50a0044 */ 	lwc1	$f10,0x44($t0)
/*  f01f680:	c60802ec */ 	lwc1	$f8,0x2ec($s0)
/*  f01f684:	c7060074 */ 	lwc1	$f6,0x74($t8)
/*  f01f688:	460a3102 */ 	mul.s	$f4,$f6,$f10
/*  f01f68c:	46081181 */ 	sub.s	$f6,$f2,$f8
/*  f01f690:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f01f694:	46062282 */ 	mul.s	$f10,$f4,$f6
/*  f01f698:	c60402f0 */ 	lwc1	$f4,0x2f0($s0)
/*  f01f69c:	46025003 */ 	div.s	$f0,$f10,$f2
/*  f01f6a0:	46002182 */ 	mul.s	$f6,$f4,$f0
/*  f01f6a4:	c6240008 */ 	lwc1	$f4,0x8($s1)
/*  f01f6a8:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f01f6ac:	e62a0000 */ 	swc1	$f10,0x0($s1)
/*  f01f6b0:	c60802f8 */ 	lwc1	$f8,0x2f8($s0)
/*  f01f6b4:	46004182 */ 	mul.s	$f6,$f8,$f0
/*  f01f6b8:	46062280 */ 	add.s	$f10,$f4,$f6
/*  f01f6bc:	e62a0008 */ 	swc1	$f10,0x8($s1)
/*  f01f6c0:	c60402f4 */ 	lwc1	$f4,0x2f4($s0)
/*  f01f6c4:	c7a800c0 */ 	lwc1	$f8,0xc0($sp)
/*  f01f6c8:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f01f6cc:	46002182 */ 	mul.s	$f6,$f4,$f0
/*  f01f6d0:	c5040044 */ 	lwc1	$f4,0x44($t0)
/*  f01f6d4:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f01f6d8:	e7aa00c0 */ 	swc1	$f10,0xc0($sp)
/*  f01f6dc:	8d490020 */ 	lw	$t1,0x20($t2)
/*  f01f6e0:	c60a02ec */ 	lwc1	$f10,0x2ec($s0)
/*  f01f6e4:	c5280074 */ 	lwc1	$f8,0x74($t1)
/*  f01f6e8:	46082182 */ 	mul.s	$f6,$f4,$f8
/*  f01f6ec:	c60802e8 */ 	lwc1	$f8,0x2e8($s0)
/*  f01f6f0:	46065100 */ 	add.s	$f4,$f10,$f6
/*  f01f6f4:	e60402ec */ 	swc1	$f4,0x2ec($s0)
/*  f01f6f8:	c60a02ec */ 	lwc1	$f10,0x2ec($s0)
/*  f01f6fc:	460a403c */ 	c.lt.s	$f8,$f10
/*  f01f700:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f704:	45020003 */ 	bc1fl	.NB0f01f714
/*  f01f708:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01f70c:	e61202e8 */ 	swc1	$f18,0x2e8($s0)
.NB0f01f710:
/*  f01f710:	c6000304 */ 	lwc1	$f0,0x304($s0)
.NB0f01f714:
/*  f01f714:	46009032 */ 	c.eq.s	$f18,$f0
/*  f01f718:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f71c:	45020007 */ 	bc1fl	.NB0f01f73c
/*  f01f720:	c508004c */ 	lwc1	$f8,0x4c($t0)
/*  f01f724:	c6060308 */ 	lwc1	$f6,0x308($s0)
/*  f01f728:	46069032 */ 	c.eq.s	$f18,$f6
/*  f01f72c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f730:	45030044 */ 	bc1tl	.NB0f01f844
/*  f01f734:	c60800bc */ 	lwc1	$f8,0xbc($s0)
/*  f01f738:	c508004c */ 	lwc1	$f8,0x4c($t0)
.NB0f01f73c:
/*  f01f73c:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f01f740:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01f744:	46080282 */ 	mul.s	$f10,$f0,$f8
/*  f01f748:	c4302358 */ 	lwc1	$f16,0x2358($at)
/*  f01f74c:	460a2180 */ 	add.s	$f6,$f4,$f10
/*  f01f750:	e6260000 */ 	swc1	$f6,0x0($s1)
/*  f01f754:	c6080308 */ 	lwc1	$f8,0x308($s0)
/*  f01f758:	c504004c */ 	lwc1	$f4,0x4c($t0)
/*  f01f75c:	c6260008 */ 	lwc1	$f6,0x8($s1)
/*  f01f760:	46044282 */ 	mul.s	$f10,$f8,$f4
/*  f01f764:	460a3200 */ 	add.s	$f8,$f6,$f10
/*  f01f768:	e6280008 */ 	swc1	$f8,0x8($s1)
/*  f01f76c:	c6040304 */ 	lwc1	$f4,0x304($s0)
/*  f01f770:	c60a0308 */ 	lwc1	$f10,0x308($s0)
/*  f01f774:	46102182 */ 	mul.s	$f6,$f4,$f16
/*  f01f778:	e6060304 */ 	swc1	$f6,0x304($s0)
/*  f01f77c:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01f780:	46105202 */ 	mul.s	$f8,$f10,$f16
/*  f01f784:	46009032 */ 	c.eq.s	$f18,$f0
/*  f01f788:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f78c:	45000006 */ 	bc1f	.NB0f01f7a8
/*  f01f790:	e6080308 */ 	swc1	$f8,0x308($s0)
/*  f01f794:	c6040308 */ 	lwc1	$f4,0x308($s0)
/*  f01f798:	46049032 */ 	c.eq.s	$f18,$f4
/*  f01f79c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f7a0:	45030028 */ 	bc1tl	.NB0f01f844
/*  f01f7a4:	c60800bc */ 	lwc1	$f8,0xbc($s0)
.NB0f01f7a8:
/*  f01f7a8:	c6020308 */ 	lwc1	$f2,0x308($s0)
/*  f01f7ac:	46021182 */ 	mul.s	$f6,$f2,$f2
/*  f01f7b0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f7b4:	46000282 */ 	mul.s	$f10,$f0,$f0
/*  f01f7b8:	0c012e84 */ 	jal	sqrtf
/*  f01f7bc:	460a3300 */ 	add.s	$f12,$f6,$f10
/*  f01f7c0:	44809000 */ 	mtc1	$zero,$f18
/*  f01f7c4:	3c08800a */ 	lui	$t0,0x800a
/*  f01f7c8:	2508e6c0 */ 	addiu	$t0,$t0,-6464
/*  f01f7cc:	4600903c */ 	c.lt.s	$f18,$f0
/*  f01f7d0:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01f7d4:	45020019 */ 	bc1fl	.NB0f01f83c
/*  f01f7d8:	e6120304 */ 	swc1	$f18,0x304($s0)
/*  f01f7dc:	c4282360 */ 	lwc1	$f8,0x2360($at)
/*  f01f7e0:	c504004c */ 	lwc1	$f4,0x4c($t0)
/*  f01f7e4:	3c013f80 */ 	lui	$at,0x3f80
/*  f01f7e8:	44815000 */ 	mtc1	$at,$f10
/*  f01f7ec:	46044182 */ 	mul.s	$f6,$f8,$f4
/*  f01f7f0:	46003303 */ 	div.s	$f12,$f6,$f0
/*  f01f7f4:	460c503e */ 	c.le.s	$f10,$f12
/*  f01f7f8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f7fc:	45020005 */ 	bc1fl	.NB0f01f814
/*  f01f800:	c6000304 */ 	lwc1	$f0,0x304($s0)
/*  f01f804:	e6120304 */ 	swc1	$f18,0x304($s0)
/*  f01f808:	1000000d */ 	beqz	$zero,.NB0f01f840
/*  f01f80c:	e6120308 */ 	swc1	$f18,0x308($s0)
/*  f01f810:	c6000304 */ 	lwc1	$f0,0x304($s0)
.NB0f01f814:
/*  f01f814:	c6020308 */ 	lwc1	$f2,0x308($s0)
/*  f01f818:	460c0202 */ 	mul.s	$f8,$f0,$f12
/*  f01f81c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01f820:	460c1182 */ 	mul.s	$f6,$f2,$f12
/*  f01f824:	46080101 */ 	sub.s	$f4,$f0,$f8
/*  f01f828:	46061281 */ 	sub.s	$f10,$f2,$f6
/*  f01f82c:	e6040304 */ 	swc1	$f4,0x304($s0)
/*  f01f830:	10000003 */ 	beqz	$zero,.NB0f01f840
/*  f01f834:	e60a0308 */ 	swc1	$f10,0x308($s0)
/*  f01f838:	e6120304 */ 	swc1	$f18,0x304($s0)
.NB0f01f83c:
/*  f01f83c:	e6120308 */ 	swc1	$f18,0x308($s0)
.NB0f01f840:
/*  f01f840:	c60800bc */ 	lwc1	$f8,0xbc($s0)
.NB0f01f844:
/*  f01f844:	c504004c */ 	lwc1	$f4,0x4c($t0)
/*  f01f848:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f01f84c:	24010003 */ 	addiu	$at,$zero,0x3
/*  f01f850:	46044182 */ 	mul.s	$f6,$f8,$f4
/*  f01f854:	46065200 */ 	add.s	$f8,$f10,$f6
/*  f01f858:	e6280000 */ 	swc1	$f8,0x0($s1)
/*  f01f85c:	c50a004c */ 	lwc1	$f10,0x4c($t0)
/*  f01f860:	c60400c4 */ 	lwc1	$f4,0xc4($s0)
/*  f01f864:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*  f01f868:	460a2182 */ 	mul.s	$f6,$f4,$f10
/*  f01f86c:	46064100 */ 	add.s	$f4,$f8,$f6
/*  f01f870:	e6240008 */ 	swc1	$f4,0x8($s1)
/*  f01f874:	8fab00c4 */ 	lw	$t3,0xc4($sp)
/*  f01f878:	55610013 */ 	bnel	$t3,$at,.NB0f01f8c8
/*  f01f87c:	820f0007 */ 	lb	$t7,0x7($s0)
/*  f01f880:	0fc0ee10 */ 	jal	chrToEyespy
/*  f01f884:	02002025 */ 	or	$a0,$s0,$zero
/*  f01f888:	5040003b */ 	beqzl	$v0,.NB0f01f978
/*  f01f88c:	8fae00e8 */ 	lw	$t6,0xe8($sp)
/*  f01f890:	90590035 */ 	lbu	$t9,0x35($v0)
/*  f01f894:	53200038 */ 	beqzl	$t9,.NB0f01f978
/*  f01f898:	8fae00e8 */ 	lw	$t6,0xe8($sp)
/*  f01f89c:	8e0c001c */ 	lw	$t4,0x1c($s0)
/*  f01f8a0:	c58a0008 */ 	lwc1	$f10,0x8($t4)
/*  f01f8a4:	e62a0000 */ 	swc1	$f10,0x0($s1)
/*  f01f8a8:	8e0d001c */ 	lw	$t5,0x1c($s0)
/*  f01f8ac:	c5a8000c */ 	lwc1	$f8,0xc($t5)
/*  f01f8b0:	e6280004 */ 	swc1	$f8,0x4($s1)
/*  f01f8b4:	8e0e001c */ 	lw	$t6,0x1c($s0)
/*  f01f8b8:	c5c60010 */ 	lwc1	$f6,0x10($t6)
/*  f01f8bc:	1000002d */ 	beqz	$zero,.NB0f01f974
/*  f01f8c0:	e6260008 */ 	swc1	$f6,0x8($s1)
/*  f01f8c4:	820f0007 */ 	lb	$t7,0x7($s0)
.NB0f01f8c8:
/*  f01f8c8:	24010023 */ 	addiu	$at,$zero,0x23
/*  f01f8cc:	55e10013 */ 	bnel	$t7,$at,.NB0f01f91c
/*  f01f8d0:	8e0b031c */ 	lw	$t3,0x31c($s0)
/*  f01f8d4:	9218002c */ 	lbu	$t8,0x2c($s0)
/*  f01f8d8:	24010001 */ 	addiu	$at,$zero,0x1
/*  f01f8dc:	5701000f */ 	bnel	$t8,$at,.NB0f01f91c
/*  f01f8e0:	8e0b031c */ 	lw	$t3,0x31c($s0)
/*  f01f8e4:	920a002d */ 	lbu	$t2,0x2d($s0)
/*  f01f8e8:	5540000c */ 	bnezl	$t2,.NB0f01f91c
/*  f01f8ec:	8e0b031c */ 	lw	$t3,0x31c($s0)
/*  f01f8f0:	8d090038 */ 	lw	$t1,0x38($t0)
/*  f01f8f4:	51200009 */ 	beqzl	$t1,.NB0f01f91c
/*  f01f8f8:	8e0b031c */ 	lw	$t3,0x31c($s0)
/*  f01f8fc:	c6040040 */ 	lwc1	$f4,0x40($s0)
/*  f01f900:	e6240000 */ 	swc1	$f4,0x0($s1)
/*  f01f904:	c60a0044 */ 	lwc1	$f10,0x44($s0)
/*  f01f908:	e7aa00c0 */ 	swc1	$f10,0xc0($sp)
/*  f01f90c:	c6080048 */ 	lwc1	$f8,0x48($s0)
/*  f01f910:	10000018 */ 	beqz	$zero,.NB0f01f974
/*  f01f914:	e6280008 */ 	swc1	$f8,0x8($s1)
/*  f01f918:	8e0b031c */ 	lw	$t3,0x31c($s0)
.NB0f01f91c:
/*  f01f91c:	8fb900f4 */ 	lw	$t9,0xf4($sp)
/*  f01f920:	51600015 */ 	beqzl	$t3,.NB0f01f978
/*  f01f924:	8fae00e8 */ 	lw	$t6,0xe8($sp)
/*  f01f928:	c7200000 */ 	lwc1	$f0,0x0($t9)
/*  f01f92c:	c6260000 */ 	lwc1	$f6,0x0($s1)
/*  f01f930:	c6240008 */ 	lwc1	$f4,0x8($s1)
/*  f01f934:	c72a0008 */ 	lwc1	$f10,0x8($t9)
/*  f01f938:	46003081 */ 	sub.s	$f2,$f6,$f0
/*  f01f93c:	e6200000 */ 	swc1	$f0,0x0($s1)
/*  f01f940:	8fac00f4 */ 	lw	$t4,0xf4($sp)
/*  f01f944:	460a2381 */ 	sub.s	$f14,$f4,$f10
/*  f01f948:	46021182 */ 	mul.s	$f6,$f2,$f2
/*  f01f94c:	c5880008 */ 	lwc1	$f8,0x8($t4)
/*  f01f950:	460e7102 */ 	mul.s	$f4,$f14,$f14
/*  f01f954:	e6280008 */ 	swc1	$f8,0x8($s1)
/*  f01f958:	0c012e84 */ 	jal	sqrtf
/*  f01f95c:	46043300 */ 	add.s	$f12,$f6,$f4
/*  f01f960:	c7aa00c0 */ 	lwc1	$f10,0xc0($sp)
/*  f01f964:	240d0004 */ 	addiu	$t5,$zero,0x4
/*  f01f968:	46005200 */ 	add.s	$f8,$f10,$f0
/*  f01f96c:	e7a800c0 */ 	swc1	$f8,0xc0($sp)
/*  f01f970:	a20d0191 */ 	sb	$t5,0x191($s0)
.NB0f01f974:
/*  f01f974:	8fae00e8 */ 	lw	$t6,0xe8($sp)
.NB0f01f978:
/*  f01f978:	24010006 */ 	addiu	$at,$zero,0x6
/*  f01f97c:	02002025 */ 	or	$a0,$s0,$zero
/*  f01f980:	91cf0000 */ 	lbu	$t7,0x0($t6)
/*  f01f984:	02202825 */ 	or	$a1,$s1,$zero
/*  f01f988:	27a600cc */ 	addiu	$a2,$sp,0xcc
/*  f01f98c:	55e10019 */ 	bnel	$t7,$at,.NB0f01f9f4
/*  f01f990:	8e0b0018 */ 	lw	$t3,0x18($s0)
/*  f01f994:	82180007 */ 	lb	$t8,0x7($s0)
/*  f01f998:	24010019 */ 	addiu	$at,$zero,0x19
/*  f01f99c:	57010015 */ 	bnel	$t8,$at,.NB0f01f9f4
/*  f01f9a0:	8e0b0018 */ 	lw	$t3,0x18($s0)
/*  f01f9a4:	c5c60008 */ 	lwc1	$f6,0x8($t6)
/*  f01f9a8:	27a500cc */ 	addiu	$a1,$sp,0xcc
/*  f01f9ac:	e6260000 */ 	swc1	$f6,0x0($s1)
/*  f01f9b0:	8faa00e8 */ 	lw	$t2,0xe8($sp)
/*  f01f9b4:	c5440010 */ 	lwc1	$f4,0x10($t2)
/*  f01f9b8:	e6240008 */ 	swc1	$f4,0x8($s1)
/*  f01f9bc:	8fa400e8 */ 	lw	$a0,0xe8($sp)
/*  f01f9c0:	24840028 */ 	addiu	$a0,$a0,0x28
/*  f01f9c4:	0fc19283 */ 	jal	roomsCopy
/*  f01f9c8:	afa40044 */ 	sw	$a0,0x44($sp)
/*  f01f9cc:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01f9d0:	c4302370 */ 	lwc1	$f16,0x2370($at)
/*  f01f9d4:	3c08800a */ 	lui	$t0,0x800a
/*  f01f9d8:	2508e6c0 */ 	addiu	$t0,$t0,-6464
/*  f01f9dc:	a2000009 */ 	sb	$zero,0x9($s0)
/*  f01f9e0:	8d090008 */ 	lw	$t1,0x8($t0)
/*  f01f9e4:	44809000 */ 	mtc1	$zero,$f18
/*  f01f9e8:	10000015 */ 	beqz	$zero,.NB0f01fa40
/*  f01f9ec:	ae0900d8 */ 	sw	$t1,0xd8($s0)
/*  f01f9f0:	8e0b0018 */ 	lw	$t3,0x18($s0)
.NB0f01f9f4:
/*  f01f9f4:	8fac00f4 */ 	lw	$t4,0xf4($sp)
/*  f01f9f8:	31794000 */ 	andi	$t9,$t3,0x4000
/*  f01f9fc:	13200006 */ 	beqz	$t9,.NB0f01fa18
/*  f01fa00:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fa04:	c58a0000 */ 	lwc1	$f10,0x0($t4)
/*  f01fa08:	e62a0000 */ 	swc1	$f10,0x0($s1)
/*  f01fa0c:	8fad00f4 */ 	lw	$t5,0xf4($sp)
/*  f01fa10:	c5a80008 */ 	lwc1	$f8,0x8($t5)
/*  f01fa14:	e6280008 */ 	swc1	$f8,0x8($s1)
.NB0f01fa18:
/*  f01fa18:	0fc07935 */ 	jal	chrCalculatePushPos
/*  f01fa1c:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f01fa20:	8faf00e8 */ 	lw	$t7,0xe8($sp)
/*  f01fa24:	3c08800a */ 	lui	$t0,0x800a
/*  f01fa28:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01fa2c:	25f80028 */ 	addiu	$t8,$t7,0x28
/*  f01fa30:	44809000 */ 	mtc1	$zero,$f18
/*  f01fa34:	afb80044 */ 	sw	$t8,0x44($sp)
/*  f01fa38:	c4302374 */ 	lwc1	$f16,0x2374($at)
/*  f01fa3c:	2508e6c0 */ 	addiu	$t0,$t0,-6464
.NB0f01fa40:
/*  f01fa40:	820e0007 */ 	lb	$t6,0x7($s0)
/*  f01fa44:	24010023 */ 	addiu	$at,$zero,0x23
/*  f01fa48:	55c10023 */ 	bnel	$t6,$at,.NB0f01fad8
/*  f01fa4c:	8e19031c */ 	lw	$t9,0x31c($s0)
/*  f01fa50:	920a002c */ 	lbu	$t2,0x2c($s0)
/*  f01fa54:	24010001 */ 	addiu	$at,$zero,0x1
/*  f01fa58:	5541001f */ 	bnel	$t2,$at,.NB0f01fad8
/*  f01fa5c:	8e19031c */ 	lw	$t9,0x31c($s0)
/*  f01fa60:	9209002d */ 	lbu	$t1,0x2d($s0)
/*  f01fa64:	5520001c */ 	bnezl	$t1,.NB0f01fad8
/*  f01fa68:	8e19031c */ 	lw	$t9,0x31c($s0)
/*  f01fa6c:	8d0b0038 */ 	lw	$t3,0x38($t0)
/*  f01fa70:	02002025 */ 	or	$a0,$s0,$zero
/*  f01fa74:	02202825 */ 	or	$a1,$s1,$zero
/*  f01fa78:	11600016 */ 	beqz	$t3,.NB0f01fad4
/*  f01fa7c:	27a600cc */ 	addiu	$a2,$sp,0xcc
/*  f01fa80:	0fc07c17 */ 	jal	func0f01f264
/*  f01fa84:	8fa700c0 */ 	lw	$a3,0xc0($sp)
/*  f01fa88:	10400009 */ 	beqz	$v0,.NB0f01fab0
/*  f01fa8c:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01fa90:	c60600b4 */ 	lwc1	$f6,0xb4($s0)
/*  f01fa94:	c7a400c0 */ 	lwc1	$f4,0xc0($sp)
/*  f01fa98:	46043280 */ 	add.s	$f10,$f6,$f4
/*  f01fa9c:	e60a00b4 */ 	swc1	$f10,0xb4($s0)
/*  f01faa0:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*  f01faa4:	c7a600c0 */ 	lwc1	$f6,0xc0($sp)
/*  f01faa8:	46064100 */ 	add.s	$f4,$f8,$f6
/*  f01faac:	e6240004 */ 	swc1	$f4,0x4($s1)
.NB0f01fab0:
/*  f01fab0:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01fab4:	c42a2378 */ 	lwc1	$f10,0x2378($at)
/*  f01fab8:	e60000b8 */ 	swc1	$f0,0xb8($s0)
/*  f01fabc:	460a0202 */ 	mul.s	$f8,$f0,$f10
/*  f01fac0:	e60800b0 */ 	swc1	$f8,0xb0($s0)
/*  f01fac4:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*  f01fac8:	46003101 */ 	sub.s	$f4,$f6,$f0
/*  f01facc:	1000013f */ 	beqz	$zero,.NB0f01ffcc
/*  f01fad0:	e6240004 */ 	swc1	$f4,0x4($s1)
.NB0f01fad4:
/*  f01fad4:	8e19031c */ 	lw	$t9,0x31c($s0)
.NB0f01fad8:
/*  f01fad8:	02002025 */ 	or	$a0,$s0,$zero
/*  f01fadc:	8fac00c4 */ 	lw	$t4,0xc4($sp)
/*  f01fae0:	13200018 */ 	beqz	$t9,.NB0f01fb44
/*  f01fae4:	24010003 */ 	addiu	$at,$zero,0x3
/*  f01fae8:	02202825 */ 	or	$a1,$s1,$zero
/*  f01faec:	27a600cc */ 	addiu	$a2,$sp,0xcc
/*  f01faf0:	0fc07c17 */ 	jal	func0f01f264
/*  f01faf4:	8fa700c0 */ 	lw	$a3,0xc0($sp)
/*  f01faf8:	10400009 */ 	beqz	$v0,.NB0f01fb20
/*  f01fafc:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01fb00:	c60a00b4 */ 	lwc1	$f10,0xb4($s0)
/*  f01fb04:	c7a800c0 */ 	lwc1	$f8,0xc0($sp)
/*  f01fb08:	46085180 */ 	add.s	$f6,$f10,$f8
/*  f01fb0c:	e60600b4 */ 	swc1	$f6,0xb4($s0)
/*  f01fb10:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*  f01fb14:	c7aa00c0 */ 	lwc1	$f10,0xc0($sp)
/*  f01fb18:	460a2200 */ 	add.s	$f8,$f4,$f10
/*  f01fb1c:	e6280004 */ 	swc1	$f8,0x4($s1)
.NB0f01fb20:
/*  f01fb20:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01fb24:	c426237c */ 	lwc1	$f6,0x237c($at)
/*  f01fb28:	e60000b8 */ 	swc1	$f0,0xb8($s0)
/*  f01fb2c:	46060102 */ 	mul.s	$f4,$f0,$f6
/*  f01fb30:	e60400b0 */ 	swc1	$f4,0xb0($s0)
/*  f01fb34:	c62a0004 */ 	lwc1	$f10,0x4($s1)
/*  f01fb38:	46005201 */ 	sub.s	$f8,$f10,$f0
/*  f01fb3c:	10000123 */ 	beqz	$zero,.NB0f01ffcc
/*  f01fb40:	e6280004 */ 	swc1	$f8,0x4($s1)
.NB0f01fb44:
/*  f01fb44:	15810003 */ 	bne	$t4,$at,.NB0f01fb54
/*  f01fb48:	8fad00e8 */ 	lw	$t5,0xe8($sp)
/*  f01fb4c:	1000005c */ 	beqz	$zero,.NB0f01fcc0
/*  f01fb50:	c60200b4 */ 	lwc1	$f2,0xb4($s0)
.NB0f01fb54:
/*  f01fb54:	91af0000 */ 	lbu	$t7,0x0($t5)
/*  f01fb58:	24010006 */ 	addiu	$at,$zero,0x6
/*  f01fb5c:	c7a400c8 */ 	lwc1	$f4,0xc8($sp)
/*  f01fb60:	55e10012 */ 	bnel	$t7,$at,.NB0f01fbac
/*  f01fb64:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*  f01fb68:	0fc48d6f */ 	jal	propGetPlayerNum
/*  f01fb6c:	01a02025 */ 	or	$a0,$t5,$zero
/*  f01fb70:	3c08800a */ 	lui	$t0,0x800a
/*  f01fb74:	2508e6c0 */ 	addiu	$t0,$t0,-6464
/*  f01fb78:	0002c080 */ 	sll	$t8,$v0,0x2
/*  f01fb7c:	01187021 */ 	addu	$t6,$t0,$t8
/*  f01fb80:	8dc30064 */ 	lw	$v1,0x64($t6)
/*  f01fb84:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01fb88:	c4302380 */ 	lwc1	$f16,0x2380($at)
/*  f01fb8c:	946a161a */ 	lhu	$t2,0x161a($v1)
/*  f01fb90:	c4620074 */ 	lwc1	$f2,0x74($v1)
/*  f01fb94:	44809000 */ 	mtc1	$zero,$f18
/*  f01fb98:	a60a018a */ 	sh	$t2,0x18a($s0)
/*  f01fb9c:	9069161e */ 	lbu	$t1,0x161e($v1)
/*  f01fba0:	10000047 */ 	beqz	$zero,.NB0f01fcc0
/*  f01fba4:	a2090191 */ 	sb	$t1,0x191($s0)
/*  f01fba8:	c6260004 */ 	lwc1	$f6,0x4($s1)
.NB0f01fbac:
/*  f01fbac:	3c01428a */ 	lui	$at,0x428a
/*  f01fbb0:	44810000 */ 	mtc1	$at,$f0
/*  f01fbb4:	46043281 */ 	sub.s	$f10,$f6,$f4
/*  f01fbb8:	27a60080 */ 	addiu	$a2,$sp,0x80
/*  f01fbbc:	27a70070 */ 	addiu	$a3,$sp,0x70
/*  f01fbc0:	27ab00cc */ 	addiu	$t3,$sp,0xcc
/*  f01fbc4:	4600503c */ 	c.lt.s	$f10,$f0
/*  f01fbc8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fbcc:	45020013 */ 	bc1fl	.NB0f01fc1c
/*  f01fbd0:	afb10090 */ 	sw	$s1,0x90($sp)
/*  f01fbd4:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f01fbd8:	afa60090 */ 	sw	$a2,0x90($sp)
/*  f01fbdc:	afa7008c */ 	sw	$a3,0x8c($sp)
/*  f01fbe0:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f01fbe4:	e7a60084 */ 	swc1	$f6,0x84($sp)
/*  f01fbe8:	02202025 */ 	or	$a0,$s1,$zero
/*  f01fbec:	e7a80080 */ 	swc1	$f8,0x80($sp)
/*  f01fbf0:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*  f01fbf4:	27a500cc */ 	addiu	$a1,$sp,0xcc
/*  f01fbf8:	0fc19437 */ 	jal	func0f065e74
/*  f01fbfc:	e7aa0088 */ 	swc1	$f10,0x88($sp)
/*  f01fc00:	02002025 */ 	or	$a0,$s0,$zero
/*  f01fc04:	27a50080 */ 	addiu	$a1,$sp,0x80
/*  f01fc08:	0fc086ba */ 	jal	func0f021fa8
/*  f01fc0c:	27a60070 */ 	addiu	$a2,$sp,0x70
/*  f01fc10:	10000004 */ 	beqz	$zero,.NB0f01fc24
/*  f01fc14:	8e050024 */ 	lw	$a1,0x24($s0)
/*  f01fc18:	afb10090 */ 	sw	$s1,0x90($sp)
.NB0f01fc1c:
/*  f01fc1c:	afab008c */ 	sw	$t3,0x8c($sp)
/*  f01fc20:	8e050024 */ 	lw	$a1,0x24($s0)
.NB0f01fc24:
/*  f01fc24:	26190191 */ 	addiu	$t9,$s0,0x191
/*  f01fc28:	27ac00ba */ 	addiu	$t4,$sp,0xba
/*  f01fc2c:	260f02b2 */ 	addiu	$t7,$s0,0x2b2
/*  f01fc30:	27ad00bc */ 	addiu	$t5,$sp,0xbc
/*  f01fc34:	27b800e4 */ 	addiu	$t8,$sp,0xe4
/*  f01fc38:	afb80020 */ 	sw	$t8,0x20($sp)
/*  f01fc3c:	afad001c */ 	sw	$t5,0x1c($sp)
/*  f01fc40:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f01fc44:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f01fc48:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f01fc4c:	8fa40090 */ 	lw	$a0,0x90($sp)
/*  f01fc50:	8fa6008c */ 	lw	$a2,0x8c($sp)
/*  f01fc54:	0c00ad7e */ 	jal	cdFindGroundY
/*  f01fc58:	2607018a */ 	addiu	$a3,$s0,0x18a
/*  f01fc5c:	8fae00bc */ 	lw	$t6,0xbc($sp)
/*  f01fc60:	3c08800a */ 	lui	$t0,0x800a
/*  f01fc64:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01fc68:	44809000 */ 	mtc1	$zero,$f18
/*  f01fc6c:	c430238c */ 	lwc1	$f16,0x238c($at)
/*  f01fc70:	2508e6c0 */ 	addiu	$t0,$t0,-6464
/*  f01fc74:	11c00007 */ 	beqz	$t6,.NB0f01fc94
/*  f01fc78:	46000086 */ 	mov.s	$f2,$f0
/*  f01fc7c:	9209032d */ 	lbu	$t1,0x32d($s0)
/*  f01fc80:	352b0080 */ 	ori	$t3,$t1,0x80
/*  f01fc84:	a20b032d */ 	sb	$t3,0x32d($s0)
/*  f01fc88:	8fb900e4 */ 	lw	$t9,0xe4($sp)
/*  f01fc8c:	10000005 */ 	beqz	$zero,.NB0f01fca4
/*  f01fc90:	ae190364 */ 	sw	$t9,0x364($s0)
.NB0f01fc94:
/*  f01fc94:	920c032d */ 	lbu	$t4,0x32d($s0)
/*  f01fc98:	ae000364 */ 	sw	$zero,0x364($s0)
/*  f01fc9c:	318fff7f */ 	andi	$t7,$t4,0xff7f
/*  f01fca0:	a20f032d */ 	sb	$t7,0x32d($s0)
.NB0f01fca4:
/*  f01fca4:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01fca8:	c42c2390 */ 	lwc1	$f12,0x2390($at)
/*  f01fcac:	460c003c */ 	c.lt.s	$f0,$f12
/*  f01fcb0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fcb4:	45020003 */ 	bc1fl	.NB0f01fcc4
/*  f01fcb8:	8e0d0018 */ 	lw	$t5,0x18($s0)
/*  f01fcbc:	46006086 */ 	mov.s	$f2,$f12
.NB0f01fcc0:
/*  f01fcc0:	8e0d0018 */ 	lw	$t5,0x18($s0)
.NB0f01fcc4:
/*  f01fcc4:	e60200b8 */ 	swc1	$f2,0xb8($s0)
/*  f01fcc8:	c7a800c0 */ 	lwc1	$f8,0xc0($sp)
/*  f01fccc:	31b80001 */ 	andi	$t8,$t5,0x1
/*  f01fcd0:	53000020 */ 	beqzl	$t8,.NB0f01fd54
/*  f01fcd4:	c60c00c0 */ 	lwc1	$f12,0xc0($s0)
/*  f01fcd8:	c60400b8 */ 	lwc1	$f4,0xb8($s0)
/*  f01fcdc:	c7aa00c8 */ 	lwc1	$f10,0xc8($sp)
/*  f01fce0:	8fae00f0 */ 	lw	$t6,0xf0($sp)
/*  f01fce4:	46044180 */ 	add.s	$f6,$f8,$f4
/*  f01fce8:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*  f01fcec:	8dca0008 */ 	lw	$t2,0x8($t6)
/*  f01fcf0:	2401fffe */ 	addiu	$at,$zero,-2
/*  f01fcf4:	460a3201 */ 	sub.s	$f8,$f6,$f10
/*  f01fcf8:	8d450000 */ 	lw	$a1,0x0($t2)
/*  f01fcfc:	46082180 */ 	add.s	$f6,$f4,$f8
/*  f01fd00:	94a20000 */ 	lhu	$v0,0x0($a1)
/*  f01fd04:	e6260004 */ 	swc1	$f6,0x4($s1)
/*  f01fd08:	8e0b0018 */ 	lw	$t3,0x18($s0)
/*  f01fd0c:	c60200b8 */ 	lwc1	$f2,0xb8($s0)
/*  f01fd10:	304900ff */ 	andi	$t1,$v0,0xff
/*  f01fd14:	0161c824 */ 	and	$t9,$t3,$at
/*  f01fd18:	ae190018 */ 	sw	$t9,0x18($s0)
/*  f01fd1c:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01fd20:	e60200b4 */ 	swc1	$f2,0xb4($s0)
/*  f01fd24:	c42a2394 */ 	lwc1	$f10,0x2394($at)
/*  f01fd28:	24010001 */ 	addiu	$at,$zero,0x1
/*  f01fd2c:	460a1102 */ 	mul.s	$f4,$f2,$f10
/*  f01fd30:	e60400b0 */ 	swc1	$f4,0xb0($s0)
/*  f01fd34:	1521009b */ 	bne	$t1,$at,.NB0f01ffa4
/*  f01fd38:	e7a200c8 */ 	swc1	$f2,0xc8($sp)
/*  f01fd3c:	0c006bab */ 	jal	modelGetNodeRwData
/*  f01fd40:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f01fd44:	c4480028 */ 	lwc1	$f8,0x28($v0)
/*  f01fd48:	10000096 */ 	beqz	$zero,.NB0f01ffa4
/*  f01fd4c:	e4480038 */ 	swc1	$f8,0x38($v0)
/*  f01fd50:	c60c00c0 */ 	lwc1	$f12,0xc0($s0)
.NB0f01fd54:
/*  f01fd54:	8fac00e8 */ 	lw	$t4,0xe8($sp)
/*  f01fd58:	27a400c0 */ 	addiu	$a0,$sp,0xc0
/*  f01fd5c:	460c9032 */ 	c.eq.s	$f18,$f12
/*  f01fd60:	27a50060 */ 	addiu	$a1,$sp,0x60
/*  f01fd64:	45020008 */ 	bc1fl	.NB0f01fd88
/*  f01fd68:	918f0000 */ 	lbu	$t7,0x0($t4)
/*  f01fd6c:	c60200b8 */ 	lwc1	$f2,0xb8($s0)
/*  f01fd70:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f01fd74:	4600103c */ 	c.lt.s	$f2,$f0
/*  f01fd78:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fd7c:	45020049 */ 	bc1fl	.NB0f01fea4
/*  f01fd80:	4602003e */ 	c.le.s	$f0,$f2
/*  f01fd84:	918f0000 */ 	lbu	$t7,0x0($t4)
.NB0f01fd88:
/*  f01fd88:	24010003 */ 	addiu	$at,$zero,0x3
/*  f01fd8c:	00001825 */ 	or	$v1,$zero,$zero
/*  f01fd90:	15e10008 */ 	bne	$t7,$at,.NB0f01fdb4
/*  f01fd94:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01fd98:	c4262398 */ 	lwc1	$f6,0x2398($at)
/*  f01fd9c:	c60a00b4 */ 	lwc1	$f10,0xb4($s0)
/*  f01fda0:	4606503e */ 	c.le.s	$f10,$f6
/*  f01fda4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fda8:	45020003 */ 	bc1fl	.NB0f01fdb8
/*  f01fdac:	e7ac0060 */ 	swc1	$f12,0x60($sp)
/*  f01fdb0:	24030001 */ 	addiu	$v1,$zero,0x1
.NB0f01fdb4:
/*  f01fdb4:	e7ac0060 */ 	swc1	$f12,0x60($sp)
.NB0f01fdb8:
/*  f01fdb8:	8d06004c */ 	lw	$a2,0x4c($t0)
/*  f01fdbc:	0fc2515d */ 	jal	func0f0965e4
/*  f01fdc0:	a3a3005f */ 	sb	$v1,0x5f($sp)
/*  f01fdc4:	02002025 */ 	or	$a0,$s0,$zero
/*  f01fdc8:	02202825 */ 	or	$a1,$s1,$zero
/*  f01fdcc:	27a600cc */ 	addiu	$a2,$sp,0xcc
/*  f01fdd0:	0fc07c17 */ 	jal	func0f01f264
/*  f01fdd4:	8fa700c0 */ 	lw	$a3,0xc0($sp)
/*  f01fdd8:	44809000 */ 	mtc1	$zero,$f18
/*  f01fddc:	10400007 */ 	beqz	$v0,.NB0f01fdfc
/*  f01fde0:	93a3005f */ 	lbu	$v1,0x5f($sp)
/*  f01fde4:	c60400b4 */ 	lwc1	$f4,0xb4($s0)
/*  f01fde8:	c7a800c0 */ 	lwc1	$f8,0xc0($sp)
/*  f01fdec:	46082180 */ 	add.s	$f6,$f4,$f8
/*  f01fdf0:	e60600b4 */ 	swc1	$f6,0xb4($s0)
/*  f01fdf4:	c7aa0060 */ 	lwc1	$f10,0x60($sp)
/*  f01fdf8:	e60a00c0 */ 	swc1	$f10,0xc0($s0)
.NB0f01fdfc:
/*  f01fdfc:	c60200b8 */ 	lwc1	$f2,0xb8($s0)
/*  f01fe00:	c60400b4 */ 	lwc1	$f4,0xb4($s0)
/*  f01fe04:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01fe08:	4602203e */ 	c.le.s	$f4,$f2
/*  f01fe0c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fe10:	4500000b */ 	bc1f	.NB0f01fe40
/*  f01fe14:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fe18:	e60200b4 */ 	swc1	$f2,0xb4($s0)
/*  f01fe1c:	c428239c */ 	lwc1	$f8,0x239c($at)
/*  f01fe20:	e61200c0 */ 	swc1	$f18,0xc0($s0)
/*  f01fe24:	46081182 */ 	mul.s	$f6,$f2,$f8
/*  f01fe28:	e60600b0 */ 	swc1	$f6,0xb0($s0)
/*  f01fe2c:	97ad00ba */ 	lhu	$t5,0xba($sp)
/*  f01fe30:	31b84000 */ 	andi	$t8,$t5,0x4000
/*  f01fe34:	13000002 */ 	beqz	$t8,.NB0f01fe40
/*  f01fe38:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fe3c:	24030001 */ 	addiu	$v1,$zero,0x1
.NB0f01fe40:
/*  f01fe40:	50600059 */ 	beqzl	$v1,.NB0f01ffa8
/*  f01fe44:	c60800b4 */ 	lwc1	$f8,0xb4($s0)
/*  f01fe48:	8e0e02d4 */ 	lw	$t6,0x2d4($s0)
/*  f01fe4c:	51c00011 */ 	beqzl	$t6,.NB0f01fe94
/*  f01fe50:	8e090014 */ 	lw	$t1,0x14($s0)
/*  f01fe54:	860200ec */ 	lh	$v0,0xec($s0)
/*  f01fe58:	04400006 */ 	bltz	$v0,.NB0f01fe74
/*  f01fe5c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fe60:	860a00ee */ 	lh	$t2,0xee($s0)
/*  f01fe64:	19400003 */ 	blez	$t2,.NB0f01fe74
/*  f01fe68:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fe6c:	10000004 */ 	beqz	$zero,.NB0f01fe80
/*  f01fe70:	00402825 */ 	or	$a1,$v0,$zero
.NB0f01fe74:
/*  f01fe74:	0fc61c7f */ 	jal	mpPlayerGetIndex
/*  f01fe78:	02002025 */ 	or	$a0,$s0,$zero
/*  f01fe7c:	00402825 */ 	or	$a1,$v0,$zero
.NB0f01fe80:
/*  f01fe80:	0fc0d732 */ 	jal	chrDie
/*  f01fe84:	02002025 */ 	or	$a0,$s0,$zero
/*  f01fe88:	10000047 */ 	beqz	$zero,.NB0f01ffa8
/*  f01fe8c:	c60800b4 */ 	lwc1	$f8,0xb4($s0)
/*  f01fe90:	8e090014 */ 	lw	$t1,0x14($s0)
.NB0f01fe94:
/*  f01fe94:	352b0020 */ 	ori	$t3,$t1,0x20
/*  f01fe98:	10000042 */ 	beqz	$zero,.NB0f01ffa4
/*  f01fe9c:	ae0b0014 */ 	sw	$t3,0x14($s0)
/*  f01fea0:	4602003e */ 	c.le.s	$f0,$f2
.NB0f01fea4:
/*  f01fea4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fea8:	4502003f */ 	bc1fl	.NB0f01ffa8
/*  f01feac:	c60800b4 */ 	lwc1	$f8,0xb4($s0)
/*  f01feb0:	8d190038 */ 	lw	$t9,0x38($t0)
/*  f01feb4:	00001025 */ 	or	$v0,$zero,$zero
/*  f01feb8:	1b200010 */ 	blez	$t9,.NB0f01fefc
/*  f01febc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01fec0:	c60a00b0 */ 	lwc1	$f10,0xb0($s0)
.NB0f01fec4:
/*  f01fec4:	c60600bc */ 	lwc1	$f6,0xbc($s0)
/*  f01fec8:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f01fecc:	46105102 */ 	mul.s	$f4,$f10,$f16
/*  f01fed0:	46022200 */ 	add.s	$f8,$f4,$f2
/*  f01fed4:	46103282 */ 	mul.s	$f10,$f6,$f16
/*  f01fed8:	c60400c4 */ 	lwc1	$f4,0xc4($s0)
/*  f01fedc:	e60800b0 */ 	swc1	$f8,0xb0($s0)
/*  f01fee0:	46102202 */ 	mul.s	$f8,$f4,$f16
/*  f01fee4:	e60a00bc */ 	swc1	$f10,0xbc($s0)
/*  f01fee8:	e60800c4 */ 	swc1	$f8,0xc4($s0)
/*  f01feec:	8d0c0038 */ 	lw	$t4,0x38($t0)
/*  f01fef0:	004c082a */ 	slt	$at,$v0,$t4
/*  f01fef4:	5420fff3 */ 	bnezl	$at,.NB0f01fec4
/*  f01fef8:	c60a00b0 */ 	lwc1	$f10,0xb0($s0)
.NB0f01fefc:
/*  f01fefc:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01ff00:	c42a23a0 */ 	lwc1	$f10,0x23a0($at)
/*  f01ff04:	c60600b0 */ 	lwc1	$f6,0xb0($s0)
/*  f01ff08:	3c0141f0 */ 	lui	$at,0x41f0
/*  f01ff0c:	44812000 */ 	mtc1	$at,$f4
/*  f01ff10:	460a3002 */ 	mul.s	$f0,$f6,$f10
/*  f01ff14:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01ff18:	46041301 */ 	sub.s	$f12,$f2,$f4
/*  f01ff1c:	460c003c */ 	c.lt.s	$f0,$f12
/*  f01ff20:	e60000b4 */ 	swc1	$f0,0xb4($s0)
/*  f01ff24:	45000005 */ 	bc1f	.NB0f01ff3c
/*  f01ff28:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01ff2c:	e60c00b4 */ 	swc1	$f12,0xb4($s0)
/*  f01ff30:	c42823a4 */ 	lwc1	$f8,0x23a4($at)
/*  f01ff34:	46086182 */ 	mul.s	$f6,$f12,$f8
/*  f01ff38:	e60600b0 */ 	swc1	$f6,0xb0($s0)
.NB0f01ff3c:
/*  f01ff3c:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01ff40:	c42a23a8 */ 	lwc1	$f10,0x23a8($at)
/*  f01ff44:	c60000bc */ 	lwc1	$f0,0xbc($s0)
/*  f01ff48:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01ff4c:	460a003c */ 	c.lt.s	$f0,$f10
/*  f01ff50:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01ff54:	45020014 */ 	bc1fl	.NB0f01ffa8
/*  f01ff58:	c60800b4 */ 	lwc1	$f8,0xb4($s0)
/*  f01ff5c:	c42223ac */ 	lwc1	$f2,0x23ac($at)
/*  f01ff60:	3c017f1a */ 	lui	$at,0x7f1a
/*  f01ff64:	4600103c */ 	c.lt.s	$f2,$f0
/*  f01ff68:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01ff6c:	4502000e */ 	bc1fl	.NB0f01ffa8
/*  f01ff70:	c60800b4 */ 	lwc1	$f8,0xb4($s0)
/*  f01ff74:	c60000c4 */ 	lwc1	$f0,0xc4($s0)
/*  f01ff78:	c42423b0 */ 	lwc1	$f4,0x23b0($at)
/*  f01ff7c:	4604003c */ 	c.lt.s	$f0,$f4
/*  f01ff80:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01ff84:	45020008 */ 	bc1fl	.NB0f01ffa8
/*  f01ff88:	c60800b4 */ 	lwc1	$f8,0xb4($s0)
/*  f01ff8c:	4600103c */ 	c.lt.s	$f2,$f0
/*  f01ff90:	00000000 */ 	sll	$zero,$zero,0x0
/*  f01ff94:	45020004 */ 	bc1fl	.NB0f01ffa8
/*  f01ff98:	c60800b4 */ 	lwc1	$f8,0xb4($s0)
/*  f01ff9c:	e61200c4 */ 	swc1	$f18,0xc4($s0)
/*  f01ffa0:	e61200bc */ 	swc1	$f18,0xbc($s0)
.NB0f01ffa4:
/*  f01ffa4:	c60800b4 */ 	lwc1	$f8,0xb4($s0)
.NB0f01ffa8:
/*  f01ffa8:	c7a600c8 */ 	lwc1	$f6,0xc8($sp)
/*  f01ffac:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*  f01ffb0:	46064281 */ 	sub.s	$f10,$f8,$f6
/*  f01ffb4:	460a2200 */ 	add.s	$f8,$f4,$f10
/*  f01ffb8:	e6280004 */ 	swc1	$f8,0x4($s1)
/*  f01ffbc:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*  f01ffc0:	c60400b4 */ 	lwc1	$f4,0xb4($s0)
/*  f01ffc4:	46043281 */ 	sub.s	$f10,$f6,$f4
/*  f01ffc8:	e62a0004 */ 	swc1	$f10,0x4($s1)
.NB0f01ffcc:
/*  f01ffcc:	c60800b4 */ 	lwc1	$f8,0xb4($s0)
/*  f01ffd0:	8faf00fc */ 	lw	$t7,0xfc($sp)
/*  f01ffd4:	24010023 */ 	addiu	$at,$zero,0x23
/*  f01ffd8:	e5e80000 */ 	swc1	$f8,0x0($t7)
/*  f01ffdc:	8fad00e8 */ 	lw	$t5,0xe8($sp)
/*  f01ffe0:	c6260000 */ 	lwc1	$f6,0x0($s1)
/*  f01ffe4:	e5a60008 */ 	swc1	$f6,0x8($t5)
/*  f01ffe8:	c60a00b4 */ 	lwc1	$f10,0xb4($s0)
/*  f01ffec:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*  f01fff0:	460a2200 */ 	add.s	$f8,$f4,$f10
/*  f01fff4:	e5a8000c */ 	swc1	$f8,0xc($t5)
/*  f01fff8:	c6260008 */ 	lwc1	$f6,0x8($s1)
/*  f01fffc:	e5a60010 */ 	swc1	$f6,0x10($t5)
/*  f020000:	82180007 */ 	lb	$t8,0x7($s0)
/*  f020004:	1701000c */ 	bne	$t8,$at,.NB0f020038
/*  f020008:	00000000 */ 	sll	$zero,$zero,0x0
/*  f02000c:	c6020050 */ 	lwc1	$f2,0x50($s0)
/*  f020010:	c5a4000c */ 	lwc1	$f4,0xc($t5)
/*  f020014:	4602203c */ 	c.lt.s	$f4,$f2
/*  f020018:	00000000 */ 	sll	$zero,$zero,0x0
/*  f02001c:	45000006 */ 	bc1f	.NB0f020038
/*  f020020:	00000000 */ 	sll	$zero,$zero,0x0
/*  f020024:	e5a2000c */ 	swc1	$f2,0xc($t5)
/*  f020028:	c6000050 */ 	lwc1	$f0,0x50($s0)
/*  f02002c:	e60000b4 */ 	swc1	$f0,0xb4($s0)
/*  f020030:	8fae00fc */ 	lw	$t6,0xfc($sp)
/*  f020034:	e5c00000 */ 	swc1	$f0,0x0($t6)
.NB0f020038:
/*  f020038:	0fc193ab */ 	jal	propDeregisterRooms
/*  f02003c:	8fa400e8 */ 	lw	$a0,0xe8($sp)
/*  f020040:	27a400cc */ 	addiu	$a0,$sp,0xcc
/*  f020044:	0fc19283 */ 	jal	roomsCopy
/*  f020048:	8fa50044 */ 	lw	$a1,0x44($sp)
/*  f02004c:	0fc086f9 */ 	jal	func0f0220ac
/*  f020050:	02002025 */ 	or	$a0,$s0,$zero
/*  f020054:	8fa400e8 */ 	lw	$a0,0xe8($sp)
/*  f020058:	260500fc */ 	addiu	$a1,$s0,0xfc
/*  f02005c:	0fc1a0f1 */ 	jal	func0f069144
/*  f020060:	9606018a */ 	lhu	$a2,0x18a($s0)
/*  f020064:	8fbf0034 */ 	lw	$ra,0x34($sp)
/*  f020068:	8fb0002c */ 	lw	$s0,0x2c($sp)
/*  f02006c:	8fb10030 */ 	lw	$s1,0x30($sp)
/*  f020070:	27bd00f0 */ 	addiu	$sp,$sp,0xf0
/*  f020074:	03e00008 */ 	jr	$ra
/*  f020078:	24020001 */ 	addiu	$v0,$zero,0x1
);
#endif

s32 getNumFreeChrSlots(void)
{
	s32 count = 0;
	s32 i;

	for (i = 0; i < g_NumChrSlots; i++) {
		if (g_ChrSlots[i].chrnum < 0) {
			count++;
		}
	}

	return count;
}

void chrSetMaxDamage(struct chrdata *chr, f32 maxdamage)
{
	chr->maxdamage = maxdamage;
}

f32 chrGetMaxDamage(struct chrdata *chr)
{
	return chr->maxdamage;
}

void chrAddHealth(struct chrdata *chr, f32 health)
{
	chr->damage -= health;
}

f32 chrGetArmor(struct chrdata *chr)
{
	if (chr->damage < 0) {
		return -chr->damage;
	}

	return 0;
}

s16 getNextUnusedChrnum(void)
{
	s32 chrnum;
	struct chrdata *chr;

	do {
		chrnum = ++g_NextChrnum;

		if (chrnum > 32767) {
			chrnum = g_NextChrnum = 5000;
		}

		chr = chrFindByLiteralId((s16)chrnum);
	} while (chr);

	return chrnum;
}

void chrInit(struct prop *prop, u8 *ailist)
{
	s32 i;
	struct chrdata *chr = NULL;

	for (i = 0; i < g_NumChrSlots; i++) {
		if (g_ChrSlots[i].chrnum < 0) {
			chr = &g_ChrSlots[i];
			break;
		}
	}

	prop->chr = chr;
	chr->chrnum = getNextUnusedChrnum();
	chrRegister(chr->chrnum, i);

	chr->headnum = 0;
	chr->bodynum = 0;
	chr->prop = prop;
	chr->model = NULL;
	chr->numarghs = 0;
	chr->lastwalk60 = 0;
	chr->invalidmove = 0;
	chr->lastmoveok60 = g_Vars.lvframe60;
	chr->visionrange = 250;

	if (cheatIsActive(CHEAT_PERFECTDARKNESS)) {
		chr->visionrange = 4;
	}

	chr->shotbondsum = 0;
	chr->damage = 0;
	chr->sumground = 0;
	chr->manground = 0;
	chr->ground = 0;
	chr->fallspeed.x = 0;
	chr->fallspeed.y = 0;
	chr->fallspeed.z = 0;
	chr->prevpos.x = 0;
	chr->prevpos.y = 0;
	chr->prevpos.z = 0;
	chr->hearingscale = 1;
	chr->maxdamage = 4;

	chr->lastseetarget60 = 0;
	chr->lastvisibletarget60 = 0;
	chr->lastheartarget60 = 0;
	chr->numclosearghs = 0;
	chr->shadecol[0] = chr->nextcol[0] = 0xff;
	chr->shadecol[1] = chr->nextcol[1] = 0xff;
	chr->shadecol[2] = chr->nextcol[2] = 0xff;
	chr->shadecol[3] = chr->nextcol[3] = 0xff;
	chr->floorcol = 0x0fff;
	chr->floortype = 0;
	chr->floorroom = -1;
	chr->fadealpha = 0xff;

	chr->chrflags = CHRCFLAG_00000001;
	chr->hidden = 0;
	chr->hidden2 = 0;
	chr->actiontype = ACT_INIT;
	chr->sleep = 0;

	chr->ailist = ailist;
	chr->aioffset = 0;
	chr->aireturnlist = -1;
	chr->aishotlist = -1;
	chr->aipunchdodgelist = -1;
	chr->aishootingatmelist = -1;
	chr->aidarkroomlist = -1;
	chr->aiplayerdeadlist = -1;

	chr->chrwidth = 20;
	chr->chrheight = 185;
	chr->morale = 0;
	chr->alertness = 0;
	chr->flags = 0;
	chr->random = 0;
	chr->timer60 = 0;
	chr->soundtimer = 0;
	chr->soundgap = 0;
	chr->talkgap = 0;
	chr->padpreset1 = -1;
	chr->proppreset1 = -1;
	chr->chrseeshot = -1;
	chr->chrseedie = -1;
	chr->chrpreset1 = -1;
	chr->chrdup = -1;
	chr->firecount[0] = 0;
	chr->firecount[1] = 0;

	chr->darkroomthing = 0;
	chr->playerdeadthing = 0;
	chr->unk32c_12 = 0;

	chr->grenadeprob = 0;
	chr->accuracyrating = 0;
	chr->speedrating = 0;
	chr->arghrating = 0;
	chr->dodgerating = 0;
	chr->unarmeddodgerating = 0;
	chr->maxdodgerating = 0;
	chr->flinchcnt = -1;
	chr->aimendcount = 0;
	chr->weapons_held[0] = NULL;
	chr->weapons_held[1] = NULL;
	chr->weapons_held[2] = NULL;
	chr->gunprop = NULL;
	chr->fireslots[0] = -1;
	chr->fireslots[1] = -1;

	chr->aimuplshoulder = 0;
	chr->aimuprshoulder = 0;
	chr->aimupback = 0;
	chr->aimsideback = 0;
	chr->aimendlshoulder = 0;
	chr->aimendrshoulder = 0;
	chr->aimendback = 0;
	chr->aimendsideback = 0;

	if (g_Vars.currentplayer->prop == NULL) {
		chr->target = -2;
	} else {
		chr->target = g_Vars.currentplayer->prop - g_Vars.props;
	}

	chr->path = -1;
	chr->team = TEAM_01;
	chrSetShield(chr, 0);
	chr->cmnum = 0;
	chr->cmnum2 = 0;
	chr->cmnum3 = 0;
	chr->cmnum4 = 0;
	chr->cmcount = random() % 300;
	chr->footstep = 0;
	chr->magicanim = -1;
	chr->cover = -1;
	chr->bdstart = 0;
	chr->oldframe = 0;
	chr->magicframe = 0;
	chr->magicspeed = PAL ? 1 : 0.25;

	i = 0;

	while (i != 60) {
		chr->bdlist[i++] = 0;
	}

	chr->talktimer = PALDOWN(3600);
	chr->cloakfadefrac = 0;
	chr->cloakfadefinished = false;
	chr->inlift = false;
	chr->targetlastseenp.x = 0;
	chr->targetlastseenp.y = 0;
	chr->targetlastseenp.z = 0;
	chr->myaction = MA_NONE;
	chr->orders = MA_NONE;
	chr->squadron = 0;
	chr->listening = 0;
	chr->convtalk = 0;
	chr->question = 0;
	chr->runfrompos.x = 0;
	chr->runfrompos.y = 0;
	chr->runfrompos.z = 0;
	chr->oldrooms[0] = -1;
	chr->aibot = NULL;
	chr->blurdrugamount = 0;
	chr->drugheadsway = 0;
	chr->drugheadcount = 0;
	chr->blurnumtimesdied = 0;
	chr->cloakpause = 0;
	chr->timeextra = 0;
	chr->elapseextra = 0;
	chr->extraspeed.x = 0;
	chr->extraspeed.y = 0;
	chr->extraspeed.z = 0;
	chr->hitpart = 0;
	chr->voicebox = 0;
	chr->pushspeed[0] = 0;
	chr->pushspeed[1] = 0;
	chr->gunroty[0] = 0;
	chr->gunrotx[0] = 0;
	chr->gunroty[1] = 0;
	chr->gunrotx[1] = 0;
	chr->unk348[0] = 0;
	chr->unk348[1] = 0;
	chr->onladder = 0;
	chr->laddernormal.x = 0;
	chr->laddernormal.y = 0;
	chr->laddernormal.z = 0;
	chr->liftaction = 0;
	chr->lift = NULL;
	chr->pouncebits = 0;
	chr->specialdie = 0;
	chr->roomtosearch = 0;
	chr->propsoundcount = 0;
	chr->patrolnextstep = -1;
	chr->p1p2 = g_Vars.bondplayernum;
	chr->lastattacker = NULL;
	chr->race = RACE_HUMAN;
	chr->aimtesttimer60 = random() % PALDOWN(30);
	chr->lastfootsample = 0;
	chr->poisoncounter = 0;
	chr->poisonprop = NULL;
	chr->lastshooter = -1;
	chr->timeshooter = 0;
	chr->noblood = false;
	chr->rtracked = false;

#if VERSION >= VERSION_NTSC_1_0
	chr->goposhitcount = 0;
#endif

	chrInitSplats(chr);
}

struct prop *func0f020b14(struct prop *prop, struct model *model,
		struct coord *pos, s16 *rooms, f32 faceangle, u8 *ailist)
{
	struct chrdata *chr;
	struct coord testpos;
	f32 ground;
	u32 nodetype;

	prop->type = PROPTYPE_CHR;

	if (prop->chr == NULL) {
		chrInit(prop, ailist);
	}

	chr = prop->chr;

	modelSetAnim70(model, func0f01f378);
	model->chr = chr;
	model->unk01 = 1;
	chr->model = model;
	chrSetLookAngle(chr, faceangle);
	modelSetAnimPlaySpeed(model, PALUPF(var80062968), 0);

	testpos.x = pos->x;
	testpos.y = pos->y + 100;
	testpos.z = pos->z;

	chr->ground = chr->manground = ground = cdFindGroundY(&testpos, chr->chrwidth, rooms, &chr->floorcol, &chr->floortype, NULL, &chr->floorroom, NULL, NULL);

	chr->sumground = ground * (PAL ? 8.4175090789795f : 9.999998f);

	prop->pos.x = testpos.x;
	prop->pos.y = ground + 100;
	prop->pos.z = testpos.z;

	propDeregisterRooms(prop);
	roomsCopy(rooms, prop->rooms);
	func0f0220ac(chr);
	modelSetRootPosition(model, &prop->pos);

	nodetype = chr->model->filedata->rootnode->type;

	if ((nodetype & 0xff) == MODELNODETYPE_CHRINFO) {
		union modelrwdata *rwdata = modelGetNodeRwData(chr->model, chr->model->filedata->rootnode);
		rwdata->chrinfo.ground = ground;
	}

	chr->prevpos.x = prop->pos.x;
	chr->prevpos.y = prop->pos.y;
	chr->prevpos.z = prop->pos.z;

	func0f069144(prop, chr->nextcol, chr->floorcol);

	return prop;
}

struct prop *propAllocateChr(struct model *model, struct coord *pos, s16 *rooms, f32 faceangle, u8 *ailist)
{
	struct prop *prop = propAllocate();

	if (prop) {
		prop = func0f020b14(prop, model, pos, rooms, faceangle, ailist);

		if (cheatIsActive(CHEAT_ENEMYSHIELDS)) {
			chrSetShield(prop->chr, 8);
		}
	}

	return prop;
}

/**
 * Appears to hide a chr. If removechr is true, deallocates the chr completely.
 */
void func0f020d44(struct prop *prop, bool removechr)
{
	struct chrdata *chr = prop->chr;
	struct model *model = chr->model;
	struct defaultobj *eyespyobj = NULL;
	struct prop *child;
	u32 stack[2];

	bgunFreeFireslotWrapper(chr->fireslots[0]);
	bgunFreeFireslotWrapper(chr->fireslots[1]);

	if (chr->proppreset1 >= 0) {
		struct prop *proppreset = &g_Vars.props[chr->proppreset1];
		struct defaultobj *chair = proppreset->obj;
		chair->hidden &= ~OBJHFLAG_OCCUPIEDCHAIR;
	}

	func0f14159c(prop);
	func0f0926bc(prop, 1, 0xffff);
	func0f0292bc(prop);
	func0f089a94(0, model);
	propDeregisterRooms(prop);

	if (g_Vars.stagenum == STAGE_CITRAINING) {
		eyespyobj = objFindByTagId(0x26);
	}

	child = prop->child;

	while (child) {
		struct defaultobj *obj = child->obj;
		struct prop *next = child->next;

		if ((obj->hidden & OBJHFLAG_HASTEXTOVERRIDE) == 0
				&& obj != eyespyobj
				&& (prop->type != PROPTYPE_PLAYER || (obj->flags3 & OBJFLAG3_00400000) == 0)) {
			objDetach(child);
			objRemove(obj, true);
		}

		child = next;
	}

	modelFree(model);
	chr->model = NULL;

	if (removechr) {
		chrDeregister(chr->chrnum);

		if (chr->cover != -1) {
			coverSetInUse(chr->cover, false);
			chr->cover = -1;
		}

		propClearReferences(prop - g_Vars.props);
		projectilesUnrefOwner(prop);

		if (g_Vars.normmplayerisrunning == false && g_MissionConfig.iscoop) {
			s32 i;

			for (i = 0; i < g_Vars.numaibuddies && i < 4; i++) {
				if (g_Vars.aibuddies[i] == prop) {
					g_Vars.aibuddies[i] = NULL;
				}
			}
		}

		chr->chrnum = -1;

		rebuildTeams();
		rebuildSquadrons();
	}
}

void propClearReferences(s32 propnum)
{
	s32 i;
	s32 j;
	struct prop *prop = &g_Vars.props[propnum];

	for (i = 0; i < g_NumChrSlots; i++) {
		if (g_ChrSlots[i].target == propnum) {
			if (propGetIndexByChrId(&g_ChrSlots[i], g_ChrSlots[i].chrpreset1) == propnum) {
				g_ChrSlots[i].chrpreset1 = -1;
			}

			g_ChrSlots[i].target = -1;
		}
	}

	for (i = 0; i < PLAYERCOUNT(); i++) {
		if (g_Vars.players[i]->lookingatprop.prop == prop) {
			g_Vars.players[i]->lookingatprop.prop = NULL;
		}

		for (j = 0; j != 4; j++) {
			if (g_Vars.players[i]->cmpfollowprops[j].prop == prop) {
				g_Vars.players[i]->cmpfollowprops[j].prop = NULL;
			}
		}
	}
}

void func0f0211a8(f32 arg0)
{
	s32 i;

	var80062968 = arg0;

	for (i = 0; i < g_NumChrSlots; i++) {
		if (g_ChrSlots[i].model) {
			modelSetAnimPlaySpeed(g_ChrSlots[i].model, PALUPF(var80062968), 600);
		}
	}
}

f32 func0f02124c(void)
{
	return var80062968;
}

void chrUpdateAimProperties(struct chrdata *chr)
{
	if (chr->aimendcount >= 2) {
		f32 mult = g_Vars.lvupdate240f / chr->aimendcount;

		if (mult > 1) {
			mult = 1;
		}

		chr->aimuplshoulder += (chr->aimendlshoulder - chr->aimuplshoulder) * mult;
		chr->aimuprshoulder += (chr->aimendrshoulder - chr->aimuprshoulder) * mult;
		chr->aimupback += (chr->aimendback - chr->aimupback) * mult;
		chr->aimsideback += (chr->aimendsideback - chr->aimsideback) * mult;

		chr->aimendcount -= g_Vars.lvupdate240_60;
	} else {
		chr->aimuplshoulder = chr->aimendlshoulder;
		chr->aimuprshoulder = chr->aimendrshoulder;
		chr->aimupback = chr->aimendback;
		chr->aimsideback = chr->aimendsideback;
	}
}

void chrFlinchBody(struct chrdata *chr)
{
	if (chr->actiontype != ACT_DEAD && chr->flinchcnt < 0) {
		chr->flinchcnt = 1;
		chr->hidden2 &= 0x0fff;
		chr->hidden2 |= (u16)(random() << 13);
	}
}

void chrFlinchHead(struct chrdata *chr, f32 arg1)
{
	s32 value;

	if (chr->flinchcnt < 0) {
		chr->flinchcnt = 1;
	} else if (chr->flinchcnt > 8) {
		chr->flinchcnt = 4;
	}

	chr->hidden2 &= 0x0fff;
	chr->hidden2 |= CHRH2FLAG_HEADSHOTTED;
	value = (arg1 + 0.3926365673542f) * 8.0f / M_BADTAU;

	if (value < 0) {
		value = 0;
	}

	if (value > 7) {
		value = 7;
	}

	chr->hidden2 |= value << 13;
}

f32 func0f02143c(struct chrdata *chr)
{
	f32 value = chr->flinchcnt;

	if (chr->hidden2 & CHRH2FLAG_HEADSHOTTED) {
		if (value < 4) {
			value = sinf(value * 1.5705462694168f / 4);
		} else {
			value = 1 - sinf((value - 4) * (PAL ? 0.07478791475296f : 0.060405626893044f));
		}
	} else {
		if (value < PALDOWN(10)) {
			value = sinf(value * 1.5705462694168f / PALDOWN(10));
		} else {
			value = 1 - sinf((value - PALDOWN(10)) * (PAL ? 0.098159141838551f : 0.078527316451073f));
		}
	}

	return value;
}

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0f02152c
.late_rodata
glabel var7f1a8740
.word 0x40c907a9
glabel var7f1a8744
.word 0x40c907a9
glabel var7f1a8748
.word 0x3fc90fdb
glabel var7f1a874c
.word 0x40c907a9
glabel var7f1a8750
.word 0x40c907a9
glabel var7f1a8754
.word 0x40c907a9
glabel var7f1a8758
.word 0x40c907a9
glabel var7f1a875c
.word 0x3f86051b
glabel var7f1a8760
.word 0xbf5f5dd8
glabel var7f1a8764
.word 0x3f5f5dd8
glabel var7f1a8768
.word 0x3f86051b
glabel var7f1a876c
.word 0xbf5f5dd8
glabel var7f1a8770
.word 0x40c907a9
glabel var7f1a8774
.word 0x40c907a9
glabel var7f1a8778
.word 0x40c907a9
glabel var7f1a877c
.word 0x40c907a9
glabel var7f1a8780
.word 0x3e86051b
glabel var7f1a8784
.word 0x40c907a9
glabel var7f1a8788
.word 0x3e86051b
glabel var7f1a878c
.word 0x3e32b17a
glabel var7f1a8790
.word 0x3e32b17a
glabel var7f1a8794
.word 0x40c907a9
glabel var7f1a8798
.word 0x40c907a9
glabel var7f1a879c
.word 0x40c907a9
.text
/*  f02152c:	3c013f80 */ 	lui	$at,0x3f80
/*  f021530:	44812000 */ 	mtc1	$at,$f4
/*  f021534:	27bdfea8 */ 	addiu	$sp,$sp,-344
/*  f021538:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f02153c:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f021540:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f021544:	afa5015c */ 	sw	$a1,0x15c($sp)
/*  f021548:	e7a40154 */ 	swc1	$f4,0x154($sp)
/*  f02154c:	8cce0020 */ 	lw	$t6,0x20($a2)
/*  f021550:	3c188008 */ 	lui	$t8,%hi(g_ModelTypeRobot)
/*  f021554:	00803825 */ 	or	$a3,$a0,$zero
/*  f021558:	8dcf0008 */ 	lw	$t7,0x8($t6)
/*  f02155c:	2718cefc */ 	addiu	$t8,$t8,%lo(g_ModelTypeRobot)
/*  f021560:	3c198008 */ 	lui	$t9,%hi(g_ModelTypeChr)
/*  f021564:	8de20004 */ 	lw	$v0,0x4($t7)
/*  f021568:	2739ce40 */ 	addiu	$t9,$t9,%lo(g_ModelTypeChr)
/*  f02156c:	24040007 */ 	addiu	$a0,$zero,0x7
/*  f021570:	1702006d */ 	bne	$t8,$v0,.L0f021728
/*  f021574:	00000000 */ 	nop
/*  f021578:	00c02025 */ 	or	$a0,$a2,$zero
/*  f02157c:	0fc0f917 */ 	jal	chrGetInverseTheta
/*  f021580:	afa70158 */ 	sw	$a3,0x158($sp)
/*  f021584:	8fa70158 */ 	lw	$a3,0x158($sp)
/*  f021588:	24010001 */ 	addiu	$at,$zero,0x1
/*  f02158c:	e7a000ac */ 	swc1	$f0,0xac($sp)
/*  f021590:	14e10006 */ 	bne	$a3,$at,.L0f0215ac
/*  f021594:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f021598:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f02159c:	c4c6030c */ 	lwc1	$f6,0x30c($a2)
/*  f0215a0:	c4ce0314 */ 	lwc1	$f14,0x314($a2)
/*  f0215a4:	10000008 */ 	b	.L0f0215c8
/*  f0215a8:	e7a600b4 */ 	swc1	$f6,0xb4($sp)
.L0f0215ac:
/*  f0215ac:	24010002 */ 	addiu	$at,$zero,0x2
/*  f0215b0:	14e10279 */ 	bne	$a3,$at,.L0f021f98
/*  f0215b4:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f0215b8:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f0215bc:	c4c80310 */ 	lwc1	$f8,0x310($a2)
/*  f0215c0:	c4ce0318 */ 	lwc1	$f14,0x318($a2)
/*  f0215c4:	e7a800b4 */ 	swc1	$f8,0xb4($sp)
.L0f0215c8:
/*  f0215c8:	0fc2d5de */ 	jal	currentPlayerGetUnk174c
/*  f0215cc:	e7ae00b0 */ 	swc1	$f14,0xb0($sp)
/*  f0215d0:	00402025 */ 	or	$a0,$v0,$zero
/*  f0215d4:	0c0056f8 */ 	jal	func00015be0
/*  f0215d8:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f0215dc:	8fa2015c */ 	lw	$v0,0x15c($sp)
/*  f0215e0:	c7ae00b0 */ 	lwc1	$f14,0xb0($sp)
/*  f0215e4:	44808000 */ 	mtc1	$zero,$f16
/*  f0215e8:	c44a0030 */ 	lwc1	$f10,0x30($v0)
/*  f0215ec:	27a500b8 */ 	addiu	$a1,$sp,0xb8
/*  f0215f0:	4610703c */ 	c.lt.s	$f14,$f16
/*  f0215f4:	e7aa0138 */ 	swc1	$f10,0x138($sp)
/*  f0215f8:	c4440034 */ 	lwc1	$f4,0x34($v0)
/*  f0215fc:	e7a4013c */ 	swc1	$f4,0x13c($sp)
/*  f021600:	c4460038 */ 	lwc1	$f6,0x38($v0)
/*  f021604:	e7a60140 */ 	swc1	$f6,0x140($sp)
/*  f021608:	e4500030 */ 	swc1	$f16,0x30($v0)
/*  f02160c:	e4500034 */ 	swc1	$f16,0x34($v0)
/*  f021610:	e4500038 */ 	swc1	$f16,0x38($v0)
/*  f021614:	c7a200b4 */ 	lwc1	$f2,0xb4($sp)
/*  f021618:	45000004 */ 	bc1f	.L0f02162c
/*  f02161c:	c7a800ac */ 	lwc1	$f8,0xac($sp)
/*  f021620:	3c017f1b */ 	lui	$at,%hi(var7f1a8740)
/*  f021624:	c4328740 */ 	lwc1	$f18,%lo(var7f1a8740)($at)
/*  f021628:	46127380 */ 	add.s	$f14,$f14,$f18
.L0f02162c:
/*  f02162c:	4610103c */ 	c.lt.s	$f2,$f16
/*  f021630:	3c017f1b */ 	lui	$at,%hi(var7f1a8744)
/*  f021634:	c4328744 */ 	lwc1	$f18,%lo(var7f1a8744)($at)
/*  f021638:	3c017f1b */ 	lui	$at,%hi(var7f1a8748)
/*  f02163c:	45000002 */ 	bc1f	.L0f021648
/*  f021640:	46089281 */ 	sub.s	$f10,$f18,$f8
/*  f021644:	46121080 */ 	add.s	$f2,$f2,$f18
.L0f021648:
/*  f021648:	c4248748 */ 	lwc1	$f4,%lo(var7f1a8748)($at)
/*  f02164c:	46045000 */ 	add.s	$f0,$f10,$f4
/*  f021650:	4600903e */ 	c.le.s	$f18,$f0
/*  f021654:	46000306 */ 	mov.s	$f12,$f0
/*  f021658:	45020003 */ 	bc1fl	.L0f021668
/*  f02165c:	e7a200b4 */ 	swc1	$f2,0xb4($sp)
/*  f021660:	46120301 */ 	sub.s	$f12,$f0,$f18
/*  f021664:	e7a200b4 */ 	swc1	$f2,0xb4($sp)
.L0f021668:
/*  f021668:	0c0058dd */ 	jal	func00016374
/*  f02166c:	e7ae00b0 */ 	swc1	$f14,0xb0($sp)
/*  f021670:	27a400b8 */ 	addiu	$a0,$sp,0xb8
/*  f021674:	0c0056f8 */ 	jal	func00015be0
/*  f021678:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f02167c:	c7ac00b0 */ 	lwc1	$f12,0xb0($sp)
/*  f021680:	0c0058ba */ 	jal	func000162e8
/*  f021684:	27a500f8 */ 	addiu	$a1,$sp,0xf8
/*  f021688:	27a400f8 */ 	addiu	$a0,$sp,0xf8
/*  f02168c:	0c0056f8 */ 	jal	func00015be0
/*  f021690:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021694:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f021698:	c7a800ac */ 	lwc1	$f8,0xac($sp)
/*  f02169c:	3c017f1b */ 	lui	$at,%hi(var7f1a8758)
/*  f0216a0:	c4328758 */ 	lwc1	$f18,%lo(var7f1a8758)($at)
/*  f0216a4:	46083000 */ 	add.s	$f0,$f6,$f8
/*  f0216a8:	4600903e */ 	c.le.s	$f18,$f0
/*  f0216ac:	46000306 */ 	mov.s	$f12,$f0
/*  f0216b0:	45000002 */ 	bc1f	.L0f0216bc
/*  f0216b4:	00000000 */ 	nop
/*  f0216b8:	46120301 */ 	sub.s	$f12,$f0,$f18
.L0f0216bc:
/*  f0216bc:	0c0058dd */ 	jal	func00016374
/*  f0216c0:	27a500b8 */ 	addiu	$a1,$sp,0xb8
/*  f0216c4:	27a400b8 */ 	addiu	$a0,$sp,0xb8
/*  f0216c8:	0c0056f8 */ 	jal	func00015be0
/*  f0216cc:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f0216d0:	3c013f80 */ 	lui	$at,0x3f80
/*  f0216d4:	44816000 */ 	mtc1	$at,$f12
/*  f0216d8:	00000000 */ 	nop
/*  f0216dc:	460c6032 */ 	c.eq.s	$f12,$f12
/*  f0216e0:	00000000 */ 	nop
/*  f0216e4:	45030004 */ 	bc1tl	.L0f0216f8
/*  f0216e8:	8fa2015c */ 	lw	$v0,0x15c($sp)
/*  f0216ec:	0c0057c1 */ 	jal	func00015f04
/*  f0216f0:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f0216f4:	8fa2015c */ 	lw	$v0,0x15c($sp)
.L0f0216f8:
/*  f0216f8:	c7aa0138 */ 	lwc1	$f10,0x138($sp)
/*  f0216fc:	e44a0030 */ 	swc1	$f10,0x30($v0)
/*  f021700:	c7a4013c */ 	lwc1	$f4,0x13c($sp)
/*  f021704:	e4440034 */ 	swc1	$f4,0x34($v0)
/*  f021708:	c7a60140 */ 	lwc1	$f6,0x140($sp)
/*  f02170c:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f021710:	e4460038 */ 	swc1	$f6,0x38($v0)
/*  f021714:	00402025 */ 	or	$a0,$v0,$zero
/*  f021718:	0c0056f8 */ 	jal	func00015be0
/*  f02171c:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021720:	1000021e */ 	b	.L0f021f9c
/*  f021724:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f021728:
/*  f021728:	17220006 */ 	bne	$t9,$v0,.L0f021744
/*  f02172c:	3c0b8008 */ 	lui	$t3,%hi(g_ModelTypeSkedar)
/*  f021730:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f021734:	24080003 */ 	addiu	$t0,$zero,0x3
/*  f021738:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f02173c:	1000000c */ 	b	.L0f021770
/*  f021740:	00004825 */ 	or	$t1,$zero,$zero
.L0f021744:
/*  f021744:	256bce98 */ 	addiu	$t3,$t3,%lo(g_ModelTypeSkedar)
/*  f021748:	15620006 */ 	bne	$t3,$v0,.L0f021764
/*  f02174c:	2405ffff */ 	addiu	$a1,$zero,-1
/*  f021750:	24050003 */ 	addiu	$a1,$zero,0x3
/*  f021754:	24080004 */ 	addiu	$t0,$zero,0x4
/*  f021758:	240a0002 */ 	addiu	$t2,$zero,0x2
/*  f02175c:	10000004 */ 	b	.L0f021770
/*  f021760:	24090001 */ 	addiu	$t1,$zero,0x1
.L0f021764:
/*  f021764:	2408ffff */ 	addiu	$t0,$zero,-1
/*  f021768:	240affff */ 	addiu	$t2,$zero,-1
/*  f02176c:	2409ffff */ 	addiu	$t1,$zero,-1
.L0f021770:
/*  f021770:	afa50150 */ 	sw	$a1,0x150($sp)
/*  f021774:	afa70158 */ 	sw	$a3,0x158($sp)
/*  f021778:	afa8014c */ 	sw	$t0,0x14c($sp)
/*  f02177c:	afa90144 */ 	sw	$t1,0x144($sp)
/*  f021780:	0fc41b99 */ 	jal	cheatIsActive
/*  f021784:	afaa0148 */ 	sw	$t2,0x148($sp)
/*  f021788:	8fa50150 */ 	lw	$a1,0x150($sp)
/*  f02178c:	8fa70158 */ 	lw	$a3,0x158($sp)
/*  f021790:	8fa8014c */ 	lw	$t0,0x14c($sp)
/*  f021794:	8fa90144 */ 	lw	$t1,0x144($sp)
/*  f021798:	10400016 */ 	beqz	$v0,.L0f0217f4
/*  f02179c:	8faa0148 */ 	lw	$t2,0x148($sp)
/*  f0217a0:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f0217a4:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f0217a8:	00001025 */ 	or	$v0,$zero,$zero
/*  f0217ac:	10c00003 */ 	beqz	$a2,.L0f0217bc
/*  f0217b0:	00000000 */ 	nop
/*  f0217b4:	10000001 */ 	b	.L0f0217bc
/*  f0217b8:	90c202fe */ 	lbu	$v0,0x2fe($a2)
.L0f0217bc:
/*  f0217bc:	1440000d */ 	bnez	$v0,.L0f0217f4
/*  f0217c0:	00000000 */ 	nop
/*  f0217c4:	14e90004 */ 	bne	$a3,$t1,.L0f0217d8
/*  f0217c8:	3c014080 */ 	lui	$at,0x4080
/*  f0217cc:	44814000 */ 	mtc1	$at,$f8
/*  f0217d0:	10000008 */ 	b	.L0f0217f4
/*  f0217d4:	e7a80154 */ 	swc1	$f8,0x154($sp)
.L0f0217d8:
/*  f0217d8:	10e50003 */ 	beq	$a3,$a1,.L0f0217e8
/*  f0217dc:	3c014020 */ 	lui	$at,0x4020
/*  f0217e0:	14e80004 */ 	bne	$a3,$t0,.L0f0217f4
/*  f0217e4:	00000000 */ 	nop
.L0f0217e8:
/*  f0217e8:	44815000 */ 	mtc1	$at,$f10
/*  f0217ec:	00000000 */ 	nop
/*  f0217f0:	e7aa0154 */ 	swc1	$f10,0x154($sp)
.L0f0217f4:
/*  f0217f4:	50e50008 */ 	beql	$a3,$a1,.L0f021818
/*  f0217f8:	44808000 */ 	mtc1	$zero,$f16
/*  f0217fc:	50e80006 */ 	beql	$a3,$t0,.L0f021818
/*  f021800:	44808000 */ 	mtc1	$zero,$f16
/*  f021804:	50ea0004 */ 	beql	$a3,$t2,.L0f021818
/*  f021808:	44808000 */ 	mtc1	$zero,$f16
/*  f02180c:	54e901e3 */ 	bnel	$a3,$t1,.L0f021f9c
/*  f021810:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f021814:	44808000 */ 	mtc1	$zero,$f16
.L0f021818:
/*  f021818:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f02181c:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f021820:	46008386 */ 	mov.s	$f14,$f16
/*  f021824:	46008306 */ 	mov.s	$f12,$f16
/*  f021828:	14e80003 */ 	bne	$a3,$t0,.L0f021838
/*  f02182c:	e7b0009c */ 	swc1	$f16,0x9c($sp)
/*  f021830:	10000088 */ 	b	.L0f021a54
/*  f021834:	c4ce0154 */ 	lwc1	$f14,0x154($a2)
.L0f021838:
/*  f021838:	14e50003 */ 	bne	$a3,$a1,.L0f021848
/*  f02183c:	00000000 */ 	nop
/*  f021840:	10000084 */ 	b	.L0f021a54
/*  f021844:	c4ce0150 */ 	lwc1	$f14,0x150($a2)
.L0f021848:
/*  f021848:	14ea003e */ 	bne	$a3,$t2,.L0f021944
/*  f02184c:	00000000 */ 	nop
/*  f021850:	94cc0192 */ 	lhu	$t4,0x192($a2)
/*  f021854:	c4ce0158 */ 	lwc1	$f14,0x158($a2)
/*  f021858:	3c017f1b */ 	lui	$at,%hi(var7f1a875c)
/*  f02185c:	318d0004 */ 	andi	$t5,$t4,0x4
/*  f021860:	51a00014 */ 	beqzl	$t5,.L0f0218b4
/*  f021864:	8cc202d4 */ 	lw	$v0,0x2d4($a2)
/*  f021868:	c420875c */ 	lwc1	$f0,%lo(var7f1a875c)($at)
/*  f02186c:	3c017f1b */ 	lui	$at,%hi(var7f1a8760)
/*  f021870:	460e003c */ 	c.lt.s	$f0,$f14
/*  f021874:	00000000 */ 	nop
/*  f021878:	45000003 */ 	bc1f	.L0f021888
/*  f02187c:	00000000 */ 	nop
/*  f021880:	1000000b */ 	b	.L0f0218b0
/*  f021884:	46007381 */ 	sub.s	$f14,$f14,$f0
.L0f021888:
/*  f021888:	c4208760 */ 	lwc1	$f0,%lo(var7f1a8760)($at)
/*  f02188c:	3c017f1b */ 	lui	$at,%hi(var7f1a8764)
/*  f021890:	4600703c */ 	c.lt.s	$f14,$f0
/*  f021894:	00000000 */ 	nop
/*  f021898:	45020005 */ 	bc1fl	.L0f0218b0
/*  f02189c:	46008386 */ 	mov.s	$f14,$f16
/*  f0218a0:	c4248764 */ 	lwc1	$f4,%lo(var7f1a8764)($at)
/*  f0218a4:	10000002 */ 	b	.L0f0218b0
/*  f0218a8:	46047380 */ 	add.s	$f14,$f14,$f4
/*  f0218ac:	46008386 */ 	mov.s	$f14,$f16
.L0f0218b0:
/*  f0218b0:	8cc202d4 */ 	lw	$v0,0x2d4($a2)
.L0f0218b4:
/*  f0218b4:	c4cc015c */ 	lwc1	$f12,0x15c($a2)
/*  f0218b8:	50400005 */ 	beqzl	$v0,.L0f0218d0
/*  f0218bc:	8cc4001c */ 	lw	$a0,0x1c($a2)
/*  f0218c0:	c44600a8 */ 	lwc1	$f6,0xa8($v0)
/*  f0218c4:	10000063 */ 	b	.L0f021a54
/*  f0218c8:	46066300 */ 	add.s	$f12,$f12,$f6
/*  f0218cc:	8cc4001c */ 	lw	$a0,0x1c($a2)
.L0f0218d0:
/*  f0218d0:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0218d4:	908e0000 */ 	lbu	$t6,0x0($a0)
/*  f0218d8:	55c1005f */ 	bnel	$t6,$at,.L0f021a58
/*  f0218dc:	80d90012 */ 	lb	$t9,0x12($a2)
/*  f0218e0:	afa50150 */ 	sw	$a1,0x150($sp)
/*  f0218e4:	afa70158 */ 	sw	$a3,0x158($sp)
/*  f0218e8:	afa8014c */ 	sw	$t0,0x14c($sp)
/*  f0218ec:	afa90144 */ 	sw	$t1,0x144($sp)
/*  f0218f0:	afaa0148 */ 	sw	$t2,0x148($sp)
/*  f0218f4:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f0218f8:	0fc4a25f */ 	jal	propGetPlayerNum
/*  f0218fc:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021900:	00027880 */ 	sll	$t7,$v0,0x2
/*  f021904:	3c18800a */ 	lui	$t8,%hi(g_Vars+0x64)
/*  f021908:	030fc021 */ 	addu	$t8,$t8,$t7
/*  f02190c:	8f18a024 */ 	lw	$t8,%lo(g_Vars+0x64)($t8)
/*  f021910:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021914:	44808000 */ 	mtc1	$zero,$f16
/*  f021918:	c70818f4 */ 	lwc1	$f8,0x18f4($t8)
/*  f02191c:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f021920:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f021924:	8fa50150 */ 	lw	$a1,0x150($sp)
/*  f021928:	8fa70158 */ 	lw	$a3,0x158($sp)
/*  f02192c:	8fa8014c */ 	lw	$t0,0x14c($sp)
/*  f021930:	8fa90144 */ 	lw	$t1,0x144($sp)
/*  f021934:	8faa0148 */ 	lw	$t2,0x148($sp)
/*  f021938:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f02193c:	10000045 */ 	b	.L0f021a54
/*  f021940:	46086300 */ 	add.s	$f12,$f12,$f8
.L0f021944:
/*  f021944:	54e90044 */ 	bnel	$a3,$t1,.L0f021a58
/*  f021948:	80d90012 */ 	lb	$t9,0x12($a2)
/*  f02194c:	94d90192 */ 	lhu	$t9,0x192($a2)
/*  f021950:	3c017f1b */ 	lui	$at,%hi(var7f1a8768)
/*  f021954:	3c18800a */ 	lui	$t8,%hi(g_Vars+0x2ac)
/*  f021958:	332b0004 */ 	andi	$t3,$t9,0x4
/*  f02195c:	51600012 */ 	beqzl	$t3,.L0f0219a8
/*  f021960:	8ccc0020 */ 	lw	$t4,0x20($a2)
/*  f021964:	c4208768 */ 	lwc1	$f0,%lo(var7f1a8768)($at)
/*  f021968:	c4ce0158 */ 	lwc1	$f14,0x158($a2)
/*  f02196c:	3c017f1b */ 	lui	$at,%hi(var7f1a876c)
/*  f021970:	460e003c */ 	c.lt.s	$f0,$f14
/*  f021974:	00000000 */ 	nop
/*  f021978:	45000003 */ 	bc1f	.L0f021988
/*  f02197c:	00000000 */ 	nop
/*  f021980:	10000010 */ 	b	.L0f0219c4
/*  f021984:	46000386 */ 	mov.s	$f14,$f0
.L0f021988:
/*  f021988:	c420876c */ 	lwc1	$f0,%lo(var7f1a876c)($at)
/*  f02198c:	4600703c */ 	c.lt.s	$f14,$f0
/*  f021990:	00000000 */ 	nop
/*  f021994:	4502000c */ 	bc1fl	.L0f0219c8
/*  f021998:	84cf02d8 */ 	lh	$t7,0x2d8($a2)
/*  f02199c:	10000009 */ 	b	.L0f0219c4
/*  f0219a0:	46000386 */ 	mov.s	$f14,$f0
/*  f0219a4:	8ccc0020 */ 	lw	$t4,0x20($a2)
.L0f0219a8:
/*  f0219a8:	8d8d0020 */ 	lw	$t5,0x20($t4)
/*  f0219ac:	81ae0008 */ 	lb	$t6,0x8($t5)
/*  f0219b0:	51c00004 */ 	beqzl	$t6,.L0f0219c4
/*  f0219b4:	c4ce0154 */ 	lwc1	$f14,0x154($a2)
/*  f0219b8:	10000002 */ 	b	.L0f0219c4
/*  f0219bc:	c4ce0150 */ 	lwc1	$f14,0x150($a2)
/*  f0219c0:	c4ce0154 */ 	lwc1	$f14,0x154($a2)
.L0f0219c4:
/*  f0219c4:	84cf02d8 */ 	lh	$t7,0x2d8($a2)
.L0f0219c8:
/*  f0219c8:	29e103e9 */ 	slti	$at,$t7,0x342
/*  f0219cc:	54200022 */ 	bnezl	$at,.L0f021a58
/*  f0219d0:	80d90012 */ 	lb	$t9,0x12($a2)
/*  f0219d4:	8f18a26c */ 	lw	$t8,%lo(g_Vars+0x2ac)($t8)
/*  f0219d8:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0219dc:	5301001e */ 	beql	$t8,$at,.L0f021a58
/*  f0219e0:	80d90012 */ 	lb	$t9,0x12($a2)
/*  f0219e4:	80c20007 */ 	lb	$v0,0x7($a2)
/*  f0219e8:	24010005 */ 	addiu	$at,$zero,0x5
/*  f0219ec:	10410019 */ 	beq	$v0,$at,.L0f021a54
/*  f0219f0:	24010004 */ 	addiu	$at,$zero,0x4
/*  f0219f4:	10410017 */ 	beq	$v0,$at,.L0f021a54
/*  f0219f8:	3c017f1b */ 	lui	$at,%hi(var7f1a8770)
/*  f0219fc:	c4328770 */ 	lwc1	$f18,%lo(var7f1a8770)($at)
/*  f021a00:	3c0143b4 */ 	lui	$at,0x43b4
/*  f021a04:	44815000 */ 	mtc1	$at,$f10
/*  f021a08:	c4c002dc */ 	lwc1	$f0,0x2dc($a2)
/*  f021a0c:	44804000 */ 	mtc1	$zero,$f8
/*  f021a10:	3c0141e0 */ 	lui	$at,0x41e0
/*  f021a14:	460a0103 */ 	div.s	$f4,$f0,$f10
/*  f021a18:	44815000 */ 	mtc1	$at,$f10
/*  f021a1c:	3c01437a */ 	lui	$at,0x437a
/*  f021a20:	4600403c */ 	c.lt.s	$f8,$f0
/*  f021a24:	46122182 */ 	mul.s	$f6,$f4,$f18
/*  f021a28:	45000003 */ 	bc1f	.L0f021a38
/*  f021a2c:	e7a6009c */ 	swc1	$f6,0x9c($sp)
/*  f021a30:	10000002 */ 	b	.L0f021a3c
/*  f021a34:	46000086 */ 	mov.s	$f2,$f0
.L0f021a38:
/*  f021a38:	46000087 */ 	neg.s	$f2,$f0
.L0f021a3c:
/*  f021a3c:	46025101 */ 	sub.s	$f4,$f10,$f2
/*  f021a40:	44813000 */ 	mtc1	$at,$f6
/*  f021a44:	00000000 */ 	nop
/*  f021a48:	46062203 */ 	div.s	$f8,$f4,$f6
/*  f021a4c:	46124282 */ 	mul.s	$f10,$f8,$f18
/*  f021a50:	460a7381 */ 	sub.s	$f14,$f14,$f10
.L0f021a54:
/*  f021a54:	80d90012 */ 	lb	$t9,0x12($a2)
.L0f021a58:
/*  f021a58:	072200c4 */ 	bltzl	$t9,.L0f021d6c
/*  f021a5c:	46107032 */ 	c.eq.s	$f14,$f16
/*  f021a60:	10c00003 */ 	beqz	$a2,.L0f021a70
/*  f021a64:	00001025 */ 	or	$v0,$zero,$zero
/*  f021a68:	10000001 */ 	b	.L0f021a70
/*  f021a6c:	90c202fe */ 	lbu	$v0,0x2fe($a2)
.L0f021a70:
/*  f021a70:	10400007 */ 	beqz	$v0,.L0f021a90
/*  f021a74:	24010001 */ 	addiu	$at,$zero,0x1
/*  f021a78:	10c00003 */ 	beqz	$a2,.L0f021a88
/*  f021a7c:	00001025 */ 	or	$v0,$zero,$zero
/*  f021a80:	10000001 */ 	b	.L0f021a88
/*  f021a84:	90c202fe */ 	lbu	$v0,0x2fe($a2)
.L0f021a88:
/*  f021a88:	544100b8 */ 	bnel	$v0,$at,.L0f021d6c
/*  f021a8c:	46107032 */ 	c.eq.s	$f14,$f16
.L0f021a90:
/*  f021a90:	10c00003 */ 	beqz	$a2,.L0f021aa0
/*  f021a94:	94c30192 */ 	lhu	$v1,0x192($a2)
/*  f021a98:	10000002 */ 	b	.L0f021aa4
/*  f021a9c:	90c202fe */ 	lbu	$v0,0x2fe($a2)
.L0f021aa0:
/*  f021aa0:	00001025 */ 	or	$v0,$zero,$zero
.L0f021aa4:
/*  f021aa4:	306b1000 */ 	andi	$t3,$v1,0x1000
/*  f021aa8:	1160005f */ 	beqz	$t3,.L0f021c28
/*  f021aac:	00000000 */ 	nop
/*  f021ab0:	14e900ad */ 	bne	$a3,$t1,.L0f021d68
/*  f021ab4:	00c02025 */ 	or	$a0,$a2,$zero
/*  f021ab8:	afa20028 */ 	sw	$v0,0x28($sp)
/*  f021abc:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f021ac0:	0fc0850f */ 	jal	func0f02143c
/*  f021ac4:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021ac8:	3c0c800a */ 	lui	$t4,%hi(var8009cd1c)
/*  f021acc:	8d8ccd1c */ 	lw	$t4,%lo(var8009cd1c)($t4)
/*  f021ad0:	8fa20028 */ 	lw	$v0,0x28($sp)
/*  f021ad4:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f021ad8:	95830192 */ 	lhu	$v1,0x192($t4)
/*  f021adc:	00452026 */ 	xor	$a0,$v0,$a1
/*  f021ae0:	44808000 */ 	mtc1	$zero,$f16
/*  f021ae4:	3c017f1b */ 	lui	$at,%hi(var7f1a8778)
/*  f021ae8:	2c840001 */ 	sltiu	$a0,$a0,0x1
/*  f021aec:	00036b43 */ 	sra	$t5,$v1,0xd
/*  f021af0:	c4328778 */ 	lwc1	$f18,%lo(var7f1a8778)($at)
/*  f021af4:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021af8:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021afc:	10800005 */ 	beqz	$a0,.L0f021b14
/*  f021b00:	31a30007 */ 	andi	$v1,$t5,0x7
/*  f021b04:	3c0141c8 */ 	lui	$at,0x41c8
/*  f021b08:	44811000 */ 	mtc1	$at,$f2
/*  f021b0c:	10000005 */ 	b	.L0f021b24
/*  f021b10:	306f0001 */ 	andi	$t7,$v1,0x1
.L0f021b14:
/*  f021b14:	3c014270 */ 	lui	$at,0x4270
/*  f021b18:	44811000 */ 	mtc1	$at,$f2
/*  f021b1c:	00000000 */ 	nop
/*  f021b20:	306f0001 */ 	andi	$t7,$v1,0x1
.L0f021b24:
/*  f021b24:	55e0000a */ 	bnezl	$t7,.L0f021b50
/*  f021b28:	28610005 */ 	slti	$at,$v1,0x5
/*  f021b2c:	10800005 */ 	beqz	$a0,.L0f021b44
/*  f021b30:	3c0142aa */ 	lui	$at,0x42aa
/*  f021b34:	3c014216 */ 	lui	$at,0x4216
/*  f021b38:	44811000 */ 	mtc1	$at,$f2
/*  f021b3c:	10000004 */ 	b	.L0f021b50
/*  f021b40:	28610005 */ 	slti	$at,$v1,0x5
.L0f021b44:
/*  f021b44:	44811000 */ 	mtc1	$at,$f2
/*  f021b48:	00000000 */ 	nop
/*  f021b4c:	28610005 */ 	slti	$at,$v1,0x5
.L0f021b50:
/*  f021b50:	1420000d */ 	bnez	$at,.L0f021b88
/*  f021b54:	28610008 */ 	slti	$at,$v1,0x8
/*  f021b58:	1020000b */ 	beqz	$at,.L0f021b88
/*  f021b5c:	00000000 */ 	nop
/*  f021b60:	46029102 */ 	mul.s	$f4,$f18,$f2
/*  f021b64:	3c0143b4 */ 	lui	$at,0x43b4
/*  f021b68:	44813000 */ 	mtc1	$at,$f6
/*  f021b6c:	00000000 */ 	nop
/*  f021b70:	46062203 */ 	div.s	$f8,$f4,$f6
/*  f021b74:	c7a4009c */ 	lwc1	$f4,0x9c($sp)
/*  f021b78:	46080282 */ 	mul.s	$f10,$f0,$f8
/*  f021b7c:	460a2181 */ 	sub.s	$f6,$f4,$f10
/*  f021b80:	1000000e */ 	b	.L0f021bbc
/*  f021b84:	e7a6009c */ 	swc1	$f6,0x9c($sp)
.L0f021b88:
/*  f021b88:	1860000c */ 	blez	$v1,.L0f021bbc
/*  f021b8c:	28610004 */ 	slti	$at,$v1,0x4
/*  f021b90:	5020000b */ 	beqzl	$at,.L0f021bc0
/*  f021b94:	24010007 */ 	addiu	$at,$zero,0x7
/*  f021b98:	46029202 */ 	mul.s	$f8,$f18,$f2
/*  f021b9c:	3c0143b4 */ 	lui	$at,0x43b4
/*  f021ba0:	44812000 */ 	mtc1	$at,$f4
/*  f021ba4:	00000000 */ 	nop
/*  f021ba8:	46044283 */ 	div.s	$f10,$f8,$f4
/*  f021bac:	c7a8009c */ 	lwc1	$f8,0x9c($sp)
/*  f021bb0:	460a0182 */ 	mul.s	$f6,$f0,$f10
/*  f021bb4:	46064100 */ 	add.s	$f4,$f8,$f6
/*  f021bb8:	e7a4009c */ 	swc1	$f4,0x9c($sp)
.L0f021bbc:
/*  f021bbc:	24010007 */ 	addiu	$at,$zero,0x7
.L0f021bc0:
/*  f021bc0:	10610005 */ 	beq	$v1,$at,.L0f021bd8
/*  f021bc4:	00000000 */ 	nop
/*  f021bc8:	10600003 */ 	beqz	$v1,.L0f021bd8
/*  f021bcc:	00000000 */ 	nop
/*  f021bd0:	14650009 */ 	bne	$v1,$a1,.L0f021bf8
/*  f021bd4:	28610003 */ 	slti	$at,$v1,0x3
.L0f021bd8:
/*  f021bd8:	46029282 */ 	mul.s	$f10,$f18,$f2
/*  f021bdc:	3c0143b4 */ 	lui	$at,0x43b4
/*  f021be0:	44814000 */ 	mtc1	$at,$f8
/*  f021be4:	00000000 */ 	nop
/*  f021be8:	46085183 */ 	div.s	$f6,$f10,$f8
/*  f021bec:	46060102 */ 	mul.s	$f4,$f0,$f6
/*  f021bf0:	1000005d */ 	b	.L0f021d68
/*  f021bf4:	46047380 */ 	add.s	$f14,$f14,$f4
.L0f021bf8:
/*  f021bf8:	1420005b */ 	bnez	$at,.L0f021d68
/*  f021bfc:	28610006 */ 	slti	$at,$v1,0x6
/*  f021c00:	5020005a */ 	beqzl	$at,.L0f021d6c
/*  f021c04:	46107032 */ 	c.eq.s	$f14,$f16
/*  f021c08:	46029282 */ 	mul.s	$f10,$f18,$f2
/*  f021c0c:	3c0143b4 */ 	lui	$at,0x43b4
/*  f021c10:	44814000 */ 	mtc1	$at,$f8
/*  f021c14:	00000000 */ 	nop
/*  f021c18:	46085183 */ 	div.s	$f6,$f10,$f8
/*  f021c1c:	46060102 */ 	mul.s	$f4,$f0,$f6
/*  f021c20:	10000051 */ 	b	.L0f021d68
/*  f021c24:	46047381 */ 	sub.s	$f14,$f14,$f4
.L0f021c28:
/*  f021c28:	10e80002 */ 	beq	$a3,$t0,.L0f021c34
/*  f021c2c:	00031343 */ 	sra	$v0,$v1,0xd
/*  f021c30:	14e50019 */ 	bne	$a3,$a1,.L0f021c98
.L0f021c34:
/*  f021c34:	30580007 */ 	andi	$t8,$v0,0x7
/*  f021c38:	afb80088 */ 	sw	$t8,0x88($sp)
/*  f021c3c:	00c02025 */ 	or	$a0,$a2,$zero
/*  f021c40:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f021c44:	0fc0850f */ 	jal	func0f02143c
/*  f021c48:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021c4c:	3c017f1b */ 	lui	$at,%hi(var7f1a8780)
/*  f021c50:	c42a8780 */ 	lwc1	$f10,%lo(var7f1a8780)($at)
/*  f021c54:	8fa20088 */ 	lw	$v0,0x88($sp)
/*  f021c58:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021c5c:	460a0082 */ 	mul.s	$f2,$f0,$f10
/*  f021c60:	44808000 */ 	mtc1	$zero,$f16
/*  f021c64:	28410003 */ 	slti	$at,$v0,0x3
/*  f021c68:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021c6c:	10200003 */ 	beqz	$at,.L0f021c7c
/*  f021c70:	46027381 */ 	sub.s	$f14,$f14,$f2
/*  f021c74:	1000003c */ 	b	.L0f021d68
/*  f021c78:	46026301 */ 	sub.s	$f12,$f12,$f2
.L0f021c7c:
/*  f021c7c:	28410003 */ 	slti	$at,$v0,0x3
/*  f021c80:	14200039 */ 	bnez	$at,.L0f021d68
/*  f021c84:	28410006 */ 	slti	$at,$v0,0x6
/*  f021c88:	50200038 */ 	beqzl	$at,.L0f021d6c
/*  f021c8c:	46107032 */ 	c.eq.s	$f14,$f16
/*  f021c90:	10000035 */ 	b	.L0f021d68
/*  f021c94:	46026300 */ 	add.s	$f12,$f12,$f2
.L0f021c98:
/*  f021c98:	14ea0033 */ 	bne	$a3,$t2,.L0f021d68
/*  f021c9c:	00c02025 */ 	or	$a0,$a2,$zero
/*  f021ca0:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f021ca4:	0fc0850f */ 	jal	func0f02143c
/*  f021ca8:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021cac:	3c19800a */ 	lui	$t9,%hi(var8009cd1c)
/*  f021cb0:	3c017f1b */ 	lui	$at,%hi(var7f1a8788)
/*  f021cb4:	8f39cd1c */ 	lw	$t9,%lo(var8009cd1c)($t9)
/*  f021cb8:	c4288788 */ 	lwc1	$f8,%lo(var7f1a8788)($at)
/*  f021cbc:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021cc0:	97220192 */ 	lhu	$v0,0x192($t9)
/*  f021cc4:	46080082 */ 	mul.s	$f2,$f0,$f8
/*  f021cc8:	44808000 */ 	mtc1	$zero,$f16
/*  f021ccc:	00025b43 */ 	sra	$t3,$v0,0xd
/*  f021cd0:	31620007 */ 	andi	$v0,$t3,0x7
/*  f021cd4:	28410003 */ 	slti	$at,$v0,0x3
/*  f021cd8:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f021cdc:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021ce0:	10200003 */ 	beqz	$at,.L0f021cf0
/*  f021ce4:	46027380 */ 	add.s	$f14,$f14,$f2
/*  f021ce8:	10000007 */ 	b	.L0f021d08
/*  f021cec:	46026300 */ 	add.s	$f12,$f12,$f2
.L0f021cf0:
/*  f021cf0:	28410003 */ 	slti	$at,$v0,0x3
/*  f021cf4:	14200004 */ 	bnez	$at,.L0f021d08
/*  f021cf8:	28410006 */ 	slti	$at,$v0,0x6
/*  f021cfc:	50200003 */ 	beqzl	$at,.L0f021d0c
/*  f021d00:	24010002 */ 	addiu	$at,$zero,0x2
/*  f021d04:	46026301 */ 	sub.s	$f12,$f12,$f2
.L0f021d08:
/*  f021d08:	24010002 */ 	addiu	$at,$zero,0x2
.L0f021d0c:
/*  f021d0c:	10410004 */ 	beq	$v0,$at,.L0f021d20
/*  f021d10:	24010005 */ 	addiu	$at,$zero,0x5
/*  f021d14:	10410002 */ 	beq	$v0,$at,.L0f021d20
/*  f021d18:	24010007 */ 	addiu	$at,$zero,0x7
/*  f021d1c:	14410007 */ 	bne	$v0,$at,.L0f021d3c
.L0f021d20:
/*  f021d20:	3c017f1b */ 	lui	$at,%hi(var7f1a878c)
/*  f021d24:	c424878c */ 	lwc1	$f4,%lo(var7f1a878c)($at)
/*  f021d28:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
/*  f021d2c:	46040282 */ 	mul.s	$f10,$f0,$f4
/*  f021d30:	460a3200 */ 	add.s	$f8,$f6,$f10
/*  f021d34:	1000000c */ 	b	.L0f021d68
/*  f021d38:	e7a8009c */ 	swc1	$f8,0x9c($sp)
.L0f021d3c:
/*  f021d3c:	10450004 */ 	beq	$v0,$a1,.L0f021d50
/*  f021d40:	24010004 */ 	addiu	$at,$zero,0x4
/*  f021d44:	10410002 */ 	beq	$v0,$at,.L0f021d50
/*  f021d48:	24010006 */ 	addiu	$at,$zero,0x6
/*  f021d4c:	14410006 */ 	bne	$v0,$at,.L0f021d68
.L0f021d50:
/*  f021d50:	3c017f1b */ 	lui	$at,%hi(var7f1a8790)
/*  f021d54:	c4268790 */ 	lwc1	$f6,%lo(var7f1a8790)($at)
/*  f021d58:	c7a4009c */ 	lwc1	$f4,0x9c($sp)
/*  f021d5c:	46060282 */ 	mul.s	$f10,$f0,$f6
/*  f021d60:	460a2201 */ 	sub.s	$f8,$f4,$f10
/*  f021d64:	e7a8009c */ 	swc1	$f8,0x9c($sp)
.L0f021d68:
/*  f021d68:	46107032 */ 	c.eq.s	$f14,$f16
.L0f021d6c:
/*  f021d6c:	3c04800a */ 	lui	$a0,%hi(var8009cd1c)
/*  f021d70:	45000010 */ 	bc1f	.L0f021db4
/*  f021d74:	00000000 */ 	nop
/*  f021d78:	46106032 */ 	c.eq.s	$f12,$f16
/*  f021d7c:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
/*  f021d80:	4500000c */ 	bc1f	.L0f021db4
/*  f021d84:	00000000 */ 	nop
/*  f021d88:	46103032 */ 	c.eq.s	$f6,$f16
/*  f021d8c:	c7a40154 */ 	lwc1	$f4,0x154($sp)
/*  f021d90:	3c013f80 */ 	lui	$at,0x3f80
/*  f021d94:	45000007 */ 	bc1f	.L0f021db4
/*  f021d98:	00000000 */ 	nop
/*  f021d9c:	44815000 */ 	mtc1	$at,$f10
/*  f021da0:	00000000 */ 	nop
/*  f021da4:	460a2032 */ 	c.eq.s	$f4,$f10
/*  f021da8:	00000000 */ 	nop
/*  f021dac:	4503007b */ 	bc1tl	.L0f021f9c
/*  f021db0:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f021db4:
/*  f021db4:	8c84cd1c */ 	lw	$a0,%lo(var8009cd1c)($a0)
/*  f021db8:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f021dbc:	0fc0f97c */ 	jal	chrGetAimAngle
/*  f021dc0:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021dc4:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021dc8:	44808000 */ 	mtc1	$zero,$f16
/*  f021dcc:	3c017f1b */ 	lui	$at,%hi(var7f1a8794)
/*  f021dd0:	c4328794 */ 	lwc1	$f18,%lo(var7f1a8794)($at)
/*  f021dd4:	4610703c */ 	c.lt.s	$f14,$f16
/*  f021dd8:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021ddc:	e7a0006c */ 	swc1	$f0,0x6c($sp)
/*  f021de0:	45020004 */ 	bc1fl	.L0f021df4
/*  f021de4:	460e9381 */ 	sub.s	$f14,$f18,$f14
/*  f021de8:	10000002 */ 	b	.L0f021df4
/*  f021dec:	46007387 */ 	neg.s	$f14,$f14
/*  f021df0:	460e9381 */ 	sub.s	$f14,$f18,$f14
.L0f021df4:
/*  f021df4:	4610603c */ 	c.lt.s	$f12,$f16
/*  f021df8:	00000000 */ 	nop
/*  f021dfc:	45020003 */ 	bc1fl	.L0f021e0c
/*  f021e00:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f021e04:	46126300 */ 	add.s	$f12,$f12,$f18
/*  f021e08:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
.L0f021e0c:
/*  f021e0c:	0fc2d5de */ 	jal	currentPlayerGetUnk174c
/*  f021e10:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021e14:	00402025 */ 	or	$a0,$v0,$zero
/*  f021e18:	0c0056f8 */ 	jal	func00015be0
/*  f021e1c:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021e20:	8fa2015c */ 	lw	$v0,0x15c($sp)
/*  f021e24:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021e28:	44808000 */ 	mtc1	$zero,$f16
/*  f021e2c:	c4480030 */ 	lwc1	$f8,0x30($v0)
/*  f021e30:	3c017f1b */ 	lui	$at,%hi(var7f1a879c)
/*  f021e34:	46107032 */ 	c.eq.s	$f14,$f16
/*  f021e38:	e7a80070 */ 	swc1	$f8,0x70($sp)
/*  f021e3c:	c4460034 */ 	lwc1	$f6,0x34($v0)
/*  f021e40:	c432879c */ 	lwc1	$f18,%lo(var7f1a879c)($at)
/*  f021e44:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021e48:	e7a60074 */ 	swc1	$f6,0x74($sp)
/*  f021e4c:	c4440038 */ 	lwc1	$f4,0x38($v0)
/*  f021e50:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f021e54:	e7a40078 */ 	swc1	$f4,0x78($sp)
/*  f021e58:	e4500030 */ 	swc1	$f16,0x30($v0)
/*  f021e5c:	e4500034 */ 	swc1	$f16,0x34($v0)
/*  f021e60:	45000006 */ 	bc1f	.L0f021e7c
/*  f021e64:	e4500038 */ 	swc1	$f16,0x38($v0)
/*  f021e68:	c7aa009c */ 	lwc1	$f10,0x9c($sp)
/*  f021e6c:	46105032 */ 	c.eq.s	$f10,$f16
/*  f021e70:	00000000 */ 	nop
/*  f021e74:	4501002e */ 	bc1t	.L0f021f30
/*  f021e78:	00000000 */ 	nop
.L0f021e7c:
/*  f021e7c:	c7a8006c */ 	lwc1	$f8,0x6c($sp)
/*  f021e80:	46086301 */ 	sub.s	$f12,$f12,$f8
/*  f021e84:	4610603c */ 	c.lt.s	$f12,$f16
/*  f021e88:	00000000 */ 	nop
/*  f021e8c:	45000002 */ 	bc1f	.L0f021e98
/*  f021e90:	00000000 */ 	nop
/*  f021e94:	46126300 */ 	add.s	$f12,$f12,$f18
.L0f021e98:
/*  f021e98:	0c0058dd */ 	jal	func00016374
/*  f021e9c:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021ea0:	27a4002c */ 	addiu	$a0,$sp,0x2c
/*  f021ea4:	0c0056f8 */ 	jal	func00015be0
/*  f021ea8:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021eac:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021eb0:	44808000 */ 	mtc1	$zero,$f16
/*  f021eb4:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f021eb8:	46107032 */ 	c.eq.s	$f14,$f16
/*  f021ebc:	00000000 */ 	nop
/*  f021ec0:	45030009 */ 	bc1tl	.L0f021ee8
/*  f021ec4:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
/*  f021ec8:	0c0058ba */ 	jal	func000162e8
/*  f021ecc:	46007306 */ 	mov.s	$f12,$f14
/*  f021ed0:	27a4002c */ 	addiu	$a0,$sp,0x2c
/*  f021ed4:	0c0056f8 */ 	jal	func00015be0
/*  f021ed8:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021edc:	44808000 */ 	mtc1	$zero,$f16
/*  f021ee0:	00000000 */ 	nop
/*  f021ee4:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
.L0f021ee8:
/*  f021ee8:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f021eec:	46103032 */ 	c.eq.s	$f6,$f16
/*  f021ef0:	00000000 */ 	nop
/*  f021ef4:	45030007 */ 	bc1tl	.L0f021f14
/*  f021ef8:	c7ac006c */ 	lwc1	$f12,0x6c($sp)
/*  f021efc:	0c005900 */ 	jal	func00016400
/*  f021f00:	46003306 */ 	mov.s	$f12,$f6
/*  f021f04:	27a4002c */ 	addiu	$a0,$sp,0x2c
/*  f021f08:	0c0056f8 */ 	jal	func00015be0
/*  f021f0c:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021f10:	c7ac006c */ 	lwc1	$f12,0x6c($sp)
.L0f021f14:
/*  f021f14:	0c0058dd */ 	jal	func00016374
/*  f021f18:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f021f1c:	27a4002c */ 	addiu	$a0,$sp,0x2c
/*  f021f20:	0c0056f8 */ 	jal	func00015be0
/*  f021f24:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021f28:	10000007 */ 	b	.L0f021f48
/*  f021f2c:	3c013f80 */ 	lui	$at,0x3f80
.L0f021f30:
/*  f021f30:	0c0058dd */ 	jal	func00016374
/*  f021f34:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f021f38:	27a4002c */ 	addiu	$a0,$sp,0x2c
/*  f021f3c:	0c0056f8 */ 	jal	func00015be0
/*  f021f40:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021f44:	3c013f80 */ 	lui	$at,0x3f80
.L0f021f48:
/*  f021f48:	44815000 */ 	mtc1	$at,$f10
/*  f021f4c:	c7a40154 */ 	lwc1	$f4,0x154($sp)
/*  f021f50:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021f54:	460a2032 */ 	c.eq.s	$f4,$f10
/*  f021f58:	00000000 */ 	nop
/*  f021f5c:	45030004 */ 	bc1tl	.L0f021f70
/*  f021f60:	c7a80070 */ 	lwc1	$f8,0x70($sp)
/*  f021f64:	0c0057c1 */ 	jal	func00015f04
/*  f021f68:	46002306 */ 	mov.s	$f12,$f4
/*  f021f6c:	c7a80070 */ 	lwc1	$f8,0x70($sp)
.L0f021f70:
/*  f021f70:	8fad015c */ 	lw	$t5,0x15c($sp)
/*  f021f74:	e5a80030 */ 	swc1	$f8,0x30($t5)
/*  f021f78:	c7a60074 */ 	lwc1	$f6,0x74($sp)
/*  f021f7c:	e5a60034 */ 	swc1	$f6,0x34($t5)
/*  f021f80:	c7aa0078 */ 	lwc1	$f10,0x78($sp)
/*  f021f84:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f021f88:	e5aa0038 */ 	swc1	$f10,0x38($t5)
/*  f021f8c:	00402025 */ 	or	$a0,$v0,$zero
/*  f021f90:	0c0056f8 */ 	jal	func00015be0
/*  f021f94:	8fa5015c */ 	lw	$a1,0x15c($sp)
.L0f021f98:
/*  f021f98:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f021f9c:
/*  f021f9c:	27bd0158 */ 	addiu	$sp,$sp,0x158
/*  f021fa0:	03e00008 */ 	jr	$ra
/*  f021fa4:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel func0f02152c
.late_rodata
glabel var7f1a8740
.word 0x40c907a9
glabel var7f1a8744
.word 0x40c907a9
glabel var7f1a8748
.word 0x3fc90fdb
glabel var7f1a874c
.word 0x40c907a9
glabel var7f1a8750
.word 0x40c907a9
glabel var7f1a8754
.word 0x40c907a9
glabel var7f1a8758
.word 0x40c907a9
glabel var7f1a875c
.word 0x3f86051b
glabel var7f1a8760
.word 0xbf5f5dd8
glabel var7f1a8764
.word 0x3f5f5dd8
glabel var7f1a8768
.word 0x3f86051b
glabel var7f1a876c
.word 0xbf5f5dd8
glabel var7f1a8770
.word 0x40c907a9
glabel var7f1a8774
.word 0x40c907a9
glabel var7f1a8778
.word 0x40c907a9
glabel var7f1a877c
.word 0x40c907a9
glabel var7f1a8780
.word 0x3e86051b
glabel var7f1a8784
.word 0x40c907a9
glabel var7f1a8788
.word 0x3e86051b
glabel var7f1a878c
.word 0x3e32b17a
glabel var7f1a8790
.word 0x3e32b17a
glabel var7f1a8794
.word 0x40c907a9
glabel var7f1a8798
.word 0x40c907a9
glabel var7f1a879c
.word 0x40c907a9
.text
/*  f02152c:	3c013f80 */ 	lui	$at,0x3f80
/*  f021530:	44812000 */ 	mtc1	$at,$f4
/*  f021534:	27bdfea8 */ 	addiu	$sp,$sp,-344
/*  f021538:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f02153c:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f021540:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f021544:	afa5015c */ 	sw	$a1,0x15c($sp)
/*  f021548:	e7a40154 */ 	swc1	$f4,0x154($sp)
/*  f02154c:	8cce0020 */ 	lw	$t6,0x20($a2)
/*  f021550:	3c188008 */ 	lui	$t8,%hi(g_ModelTypeRobot)
/*  f021554:	00803825 */ 	or	$a3,$a0,$zero
/*  f021558:	8dcf0008 */ 	lw	$t7,0x8($t6)
/*  f02155c:	2718cefc */ 	addiu	$t8,$t8,%lo(g_ModelTypeRobot)
/*  f021560:	3c198008 */ 	lui	$t9,%hi(g_ModelTypeChr)
/*  f021564:	8de20004 */ 	lw	$v0,0x4($t7)
/*  f021568:	2739ce40 */ 	addiu	$t9,$t9,%lo(g_ModelTypeChr)
/*  f02156c:	24040007 */ 	addiu	$a0,$zero,0x7
/*  f021570:	1702006d */ 	bne	$t8,$v0,.L0f021728
/*  f021574:	00000000 */ 	nop
/*  f021578:	00c02025 */ 	or	$a0,$a2,$zero
/*  f02157c:	0fc0f917 */ 	jal	chrGetInverseTheta
/*  f021580:	afa70158 */ 	sw	$a3,0x158($sp)
/*  f021584:	8fa70158 */ 	lw	$a3,0x158($sp)
/*  f021588:	24010001 */ 	addiu	$at,$zero,0x1
/*  f02158c:	e7a000ac */ 	swc1	$f0,0xac($sp)
/*  f021590:	14e10006 */ 	bne	$a3,$at,.L0f0215ac
/*  f021594:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f021598:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f02159c:	c4c6030c */ 	lwc1	$f6,0x30c($a2)
/*  f0215a0:	c4ce0314 */ 	lwc1	$f14,0x314($a2)
/*  f0215a4:	10000008 */ 	b	.L0f0215c8
/*  f0215a8:	e7a600b4 */ 	swc1	$f6,0xb4($sp)
.L0f0215ac:
/*  f0215ac:	24010002 */ 	addiu	$at,$zero,0x2
/*  f0215b0:	14e10279 */ 	bne	$a3,$at,.L0f021f98
/*  f0215b4:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f0215b8:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f0215bc:	c4c80310 */ 	lwc1	$f8,0x310($a2)
/*  f0215c0:	c4ce0318 */ 	lwc1	$f14,0x318($a2)
/*  f0215c4:	e7a800b4 */ 	swc1	$f8,0xb4($sp)
.L0f0215c8:
/*  f0215c8:	0fc2d5de */ 	jal	currentPlayerGetUnk174c
/*  f0215cc:	e7ae00b0 */ 	swc1	$f14,0xb0($sp)
/*  f0215d0:	00402025 */ 	or	$a0,$v0,$zero
/*  f0215d4:	0c0056f8 */ 	jal	func00015be0
/*  f0215d8:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f0215dc:	8fa2015c */ 	lw	$v0,0x15c($sp)
/*  f0215e0:	c7ae00b0 */ 	lwc1	$f14,0xb0($sp)
/*  f0215e4:	44808000 */ 	mtc1	$zero,$f16
/*  f0215e8:	c44a0030 */ 	lwc1	$f10,0x30($v0)
/*  f0215ec:	27a500b8 */ 	addiu	$a1,$sp,0xb8
/*  f0215f0:	4610703c */ 	c.lt.s	$f14,$f16
/*  f0215f4:	e7aa0138 */ 	swc1	$f10,0x138($sp)
/*  f0215f8:	c4440034 */ 	lwc1	$f4,0x34($v0)
/*  f0215fc:	e7a4013c */ 	swc1	$f4,0x13c($sp)
/*  f021600:	c4460038 */ 	lwc1	$f6,0x38($v0)
/*  f021604:	e7a60140 */ 	swc1	$f6,0x140($sp)
/*  f021608:	e4500030 */ 	swc1	$f16,0x30($v0)
/*  f02160c:	e4500034 */ 	swc1	$f16,0x34($v0)
/*  f021610:	e4500038 */ 	swc1	$f16,0x38($v0)
/*  f021614:	c7a200b4 */ 	lwc1	$f2,0xb4($sp)
/*  f021618:	45000004 */ 	bc1f	.L0f02162c
/*  f02161c:	c7a800ac */ 	lwc1	$f8,0xac($sp)
/*  f021620:	3c017f1b */ 	lui	$at,%hi(var7f1a8740)
/*  f021624:	c4328740 */ 	lwc1	$f18,%lo(var7f1a8740)($at)
/*  f021628:	46127380 */ 	add.s	$f14,$f14,$f18
.L0f02162c:
/*  f02162c:	4610103c */ 	c.lt.s	$f2,$f16
/*  f021630:	3c017f1b */ 	lui	$at,%hi(var7f1a8744)
/*  f021634:	c4328744 */ 	lwc1	$f18,%lo(var7f1a8744)($at)
/*  f021638:	3c017f1b */ 	lui	$at,%hi(var7f1a8748)
/*  f02163c:	45000002 */ 	bc1f	.L0f021648
/*  f021640:	46089281 */ 	sub.s	$f10,$f18,$f8
/*  f021644:	46121080 */ 	add.s	$f2,$f2,$f18
.L0f021648:
/*  f021648:	c4248748 */ 	lwc1	$f4,%lo(var7f1a8748)($at)
/*  f02164c:	46045000 */ 	add.s	$f0,$f10,$f4
/*  f021650:	4600903e */ 	c.le.s	$f18,$f0
/*  f021654:	46000306 */ 	mov.s	$f12,$f0
/*  f021658:	45020003 */ 	bc1fl	.L0f021668
/*  f02165c:	e7a200b4 */ 	swc1	$f2,0xb4($sp)
/*  f021660:	46120301 */ 	sub.s	$f12,$f0,$f18
/*  f021664:	e7a200b4 */ 	swc1	$f2,0xb4($sp)
.L0f021668:
/*  f021668:	0c0058dd */ 	jal	func00016374
/*  f02166c:	e7ae00b0 */ 	swc1	$f14,0xb0($sp)
/*  f021670:	27a400b8 */ 	addiu	$a0,$sp,0xb8
/*  f021674:	0c0056f8 */ 	jal	func00015be0
/*  f021678:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f02167c:	c7ac00b0 */ 	lwc1	$f12,0xb0($sp)
/*  f021680:	0c0058ba */ 	jal	func000162e8
/*  f021684:	27a500f8 */ 	addiu	$a1,$sp,0xf8
/*  f021688:	27a400f8 */ 	addiu	$a0,$sp,0xf8
/*  f02168c:	0c0056f8 */ 	jal	func00015be0
/*  f021690:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021694:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f021698:	c7a800ac */ 	lwc1	$f8,0xac($sp)
/*  f02169c:	3c017f1b */ 	lui	$at,%hi(var7f1a8758)
/*  f0216a0:	c4328758 */ 	lwc1	$f18,%lo(var7f1a8758)($at)
/*  f0216a4:	46083000 */ 	add.s	$f0,$f6,$f8
/*  f0216a8:	4600903e */ 	c.le.s	$f18,$f0
/*  f0216ac:	46000306 */ 	mov.s	$f12,$f0
/*  f0216b0:	45000002 */ 	bc1f	.L0f0216bc
/*  f0216b4:	00000000 */ 	nop
/*  f0216b8:	46120301 */ 	sub.s	$f12,$f0,$f18
.L0f0216bc:
/*  f0216bc:	0c0058dd */ 	jal	func00016374
/*  f0216c0:	27a500b8 */ 	addiu	$a1,$sp,0xb8
/*  f0216c4:	27a400b8 */ 	addiu	$a0,$sp,0xb8
/*  f0216c8:	0c0056f8 */ 	jal	func00015be0
/*  f0216cc:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f0216d0:	3c013f80 */ 	lui	$at,0x3f80
/*  f0216d4:	44816000 */ 	mtc1	$at,$f12
/*  f0216d8:	00000000 */ 	nop
/*  f0216dc:	460c6032 */ 	c.eq.s	$f12,$f12
/*  f0216e0:	00000000 */ 	nop
/*  f0216e4:	45030004 */ 	bc1tl	.L0f0216f8
/*  f0216e8:	8fa2015c */ 	lw	$v0,0x15c($sp)
/*  f0216ec:	0c0057c1 */ 	jal	func00015f04
/*  f0216f0:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f0216f4:	8fa2015c */ 	lw	$v0,0x15c($sp)
.L0f0216f8:
/*  f0216f8:	c7aa0138 */ 	lwc1	$f10,0x138($sp)
/*  f0216fc:	e44a0030 */ 	swc1	$f10,0x30($v0)
/*  f021700:	c7a4013c */ 	lwc1	$f4,0x13c($sp)
/*  f021704:	e4440034 */ 	swc1	$f4,0x34($v0)
/*  f021708:	c7a60140 */ 	lwc1	$f6,0x140($sp)
/*  f02170c:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f021710:	e4460038 */ 	swc1	$f6,0x38($v0)
/*  f021714:	00402025 */ 	or	$a0,$v0,$zero
/*  f021718:	0c0056f8 */ 	jal	func00015be0
/*  f02171c:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021720:	1000021e */ 	b	.L0f021f9c
/*  f021724:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f021728:
/*  f021728:	17220006 */ 	bne	$t9,$v0,.L0f021744
/*  f02172c:	3c0b8008 */ 	lui	$t3,%hi(g_ModelTypeSkedar)
/*  f021730:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f021734:	24080003 */ 	addiu	$t0,$zero,0x3
/*  f021738:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f02173c:	1000000c */ 	b	.L0f021770
/*  f021740:	00004825 */ 	or	$t1,$zero,$zero
.L0f021744:
/*  f021744:	256bce98 */ 	addiu	$t3,$t3,%lo(g_ModelTypeSkedar)
/*  f021748:	15620006 */ 	bne	$t3,$v0,.L0f021764
/*  f02174c:	2405ffff */ 	addiu	$a1,$zero,-1
/*  f021750:	24050003 */ 	addiu	$a1,$zero,0x3
/*  f021754:	24080004 */ 	addiu	$t0,$zero,0x4
/*  f021758:	240a0002 */ 	addiu	$t2,$zero,0x2
/*  f02175c:	10000004 */ 	b	.L0f021770
/*  f021760:	24090001 */ 	addiu	$t1,$zero,0x1
.L0f021764:
/*  f021764:	2408ffff */ 	addiu	$t0,$zero,-1
/*  f021768:	240affff */ 	addiu	$t2,$zero,-1
/*  f02176c:	2409ffff */ 	addiu	$t1,$zero,-1
.L0f021770:
/*  f021770:	afa50150 */ 	sw	$a1,0x150($sp)
/*  f021774:	afa70158 */ 	sw	$a3,0x158($sp)
/*  f021778:	afa8014c */ 	sw	$t0,0x14c($sp)
/*  f02177c:	afa90144 */ 	sw	$t1,0x144($sp)
/*  f021780:	0fc41b99 */ 	jal	cheatIsActive
/*  f021784:	afaa0148 */ 	sw	$t2,0x148($sp)
/*  f021788:	8fa50150 */ 	lw	$a1,0x150($sp)
/*  f02178c:	8fa70158 */ 	lw	$a3,0x158($sp)
/*  f021790:	8fa8014c */ 	lw	$t0,0x14c($sp)
/*  f021794:	8fa90144 */ 	lw	$t1,0x144($sp)
/*  f021798:	10400016 */ 	beqz	$v0,.L0f0217f4
/*  f02179c:	8faa0148 */ 	lw	$t2,0x148($sp)
/*  f0217a0:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f0217a4:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f0217a8:	00001025 */ 	or	$v0,$zero,$zero
/*  f0217ac:	10c00003 */ 	beqz	$a2,.L0f0217bc
/*  f0217b0:	00000000 */ 	nop
/*  f0217b4:	10000001 */ 	b	.L0f0217bc
/*  f0217b8:	90c202fe */ 	lbu	$v0,0x2fe($a2)
.L0f0217bc:
/*  f0217bc:	1440000d */ 	bnez	$v0,.L0f0217f4
/*  f0217c0:	00000000 */ 	nop
/*  f0217c4:	14e90004 */ 	bne	$a3,$t1,.L0f0217d8
/*  f0217c8:	3c014080 */ 	lui	$at,0x4080
/*  f0217cc:	44814000 */ 	mtc1	$at,$f8
/*  f0217d0:	10000008 */ 	b	.L0f0217f4
/*  f0217d4:	e7a80154 */ 	swc1	$f8,0x154($sp)
.L0f0217d8:
/*  f0217d8:	10e50003 */ 	beq	$a3,$a1,.L0f0217e8
/*  f0217dc:	3c014020 */ 	lui	$at,0x4020
/*  f0217e0:	14e80004 */ 	bne	$a3,$t0,.L0f0217f4
/*  f0217e4:	00000000 */ 	nop
.L0f0217e8:
/*  f0217e8:	44815000 */ 	mtc1	$at,$f10
/*  f0217ec:	00000000 */ 	nop
/*  f0217f0:	e7aa0154 */ 	swc1	$f10,0x154($sp)
.L0f0217f4:
/*  f0217f4:	50e50008 */ 	beql	$a3,$a1,.L0f021818
/*  f0217f8:	44808000 */ 	mtc1	$zero,$f16
/*  f0217fc:	50e80006 */ 	beql	$a3,$t0,.L0f021818
/*  f021800:	44808000 */ 	mtc1	$zero,$f16
/*  f021804:	50ea0004 */ 	beql	$a3,$t2,.L0f021818
/*  f021808:	44808000 */ 	mtc1	$zero,$f16
/*  f02180c:	54e901e3 */ 	bnel	$a3,$t1,.L0f021f9c
/*  f021810:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f021814:	44808000 */ 	mtc1	$zero,$f16
.L0f021818:
/*  f021818:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f02181c:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f021820:	46008386 */ 	mov.s	$f14,$f16
/*  f021824:	46008306 */ 	mov.s	$f12,$f16
/*  f021828:	14e80003 */ 	bne	$a3,$t0,.L0f021838
/*  f02182c:	e7b0009c */ 	swc1	$f16,0x9c($sp)
/*  f021830:	10000088 */ 	b	.L0f021a54
/*  f021834:	c4ce0154 */ 	lwc1	$f14,0x154($a2)
.L0f021838:
/*  f021838:	14e50003 */ 	bne	$a3,$a1,.L0f021848
/*  f02183c:	00000000 */ 	nop
/*  f021840:	10000084 */ 	b	.L0f021a54
/*  f021844:	c4ce0150 */ 	lwc1	$f14,0x150($a2)
.L0f021848:
/*  f021848:	14ea003e */ 	bne	$a3,$t2,.L0f021944
/*  f02184c:	00000000 */ 	nop
/*  f021850:	94cc0192 */ 	lhu	$t4,0x192($a2)
/*  f021854:	c4ce0158 */ 	lwc1	$f14,0x158($a2)
/*  f021858:	3c017f1b */ 	lui	$at,%hi(var7f1a875c)
/*  f02185c:	318d0004 */ 	andi	$t5,$t4,0x4
/*  f021860:	51a00014 */ 	beqzl	$t5,.L0f0218b4
/*  f021864:	8cc202d4 */ 	lw	$v0,0x2d4($a2)
/*  f021868:	c420875c */ 	lwc1	$f0,%lo(var7f1a875c)($at)
/*  f02186c:	3c017f1b */ 	lui	$at,%hi(var7f1a8760)
/*  f021870:	460e003c */ 	c.lt.s	$f0,$f14
/*  f021874:	00000000 */ 	nop
/*  f021878:	45000003 */ 	bc1f	.L0f021888
/*  f02187c:	00000000 */ 	nop
/*  f021880:	1000000b */ 	b	.L0f0218b0
/*  f021884:	46007381 */ 	sub.s	$f14,$f14,$f0
.L0f021888:
/*  f021888:	c4208760 */ 	lwc1	$f0,%lo(var7f1a8760)($at)
/*  f02188c:	3c017f1b */ 	lui	$at,%hi(var7f1a8764)
/*  f021890:	4600703c */ 	c.lt.s	$f14,$f0
/*  f021894:	00000000 */ 	nop
/*  f021898:	45020005 */ 	bc1fl	.L0f0218b0
/*  f02189c:	46008386 */ 	mov.s	$f14,$f16
/*  f0218a0:	c4248764 */ 	lwc1	$f4,%lo(var7f1a8764)($at)
/*  f0218a4:	10000002 */ 	b	.L0f0218b0
/*  f0218a8:	46047380 */ 	add.s	$f14,$f14,$f4
/*  f0218ac:	46008386 */ 	mov.s	$f14,$f16
.L0f0218b0:
/*  f0218b0:	8cc202d4 */ 	lw	$v0,0x2d4($a2)
.L0f0218b4:
/*  f0218b4:	c4cc015c */ 	lwc1	$f12,0x15c($a2)
/*  f0218b8:	50400005 */ 	beqzl	$v0,.L0f0218d0
/*  f0218bc:	8cc4001c */ 	lw	$a0,0x1c($a2)
/*  f0218c0:	c44600a8 */ 	lwc1	$f6,0xa8($v0)
/*  f0218c4:	10000063 */ 	b	.L0f021a54
/*  f0218c8:	46066300 */ 	add.s	$f12,$f12,$f6
/*  f0218cc:	8cc4001c */ 	lw	$a0,0x1c($a2)
.L0f0218d0:
/*  f0218d0:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0218d4:	908e0000 */ 	lbu	$t6,0x0($a0)
/*  f0218d8:	55c1005f */ 	bnel	$t6,$at,.L0f021a58
/*  f0218dc:	80d90012 */ 	lb	$t9,0x12($a2)
/*  f0218e0:	afa50150 */ 	sw	$a1,0x150($sp)
/*  f0218e4:	afa70158 */ 	sw	$a3,0x158($sp)
/*  f0218e8:	afa8014c */ 	sw	$t0,0x14c($sp)
/*  f0218ec:	afa90144 */ 	sw	$t1,0x144($sp)
/*  f0218f0:	afaa0148 */ 	sw	$t2,0x148($sp)
/*  f0218f4:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f0218f8:	0fc4a25f */ 	jal	propGetPlayerNum
/*  f0218fc:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021900:	00027880 */ 	sll	$t7,$v0,0x2
/*  f021904:	3c18800a */ 	lui	$t8,%hi(g_Vars+0x64)
/*  f021908:	030fc021 */ 	addu	$t8,$t8,$t7
/*  f02190c:	8f18a024 */ 	lw	$t8,%lo(g_Vars+0x64)($t8)
/*  f021910:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021914:	44808000 */ 	mtc1	$zero,$f16
/*  f021918:	c70818f4 */ 	lwc1	$f8,0x18f4($t8)
/*  f02191c:	3c06800a */ 	lui	$a2,%hi(var8009cd1c)
/*  f021920:	8cc6cd1c */ 	lw	$a2,%lo(var8009cd1c)($a2)
/*  f021924:	8fa50150 */ 	lw	$a1,0x150($sp)
/*  f021928:	8fa70158 */ 	lw	$a3,0x158($sp)
/*  f02192c:	8fa8014c */ 	lw	$t0,0x14c($sp)
/*  f021930:	8fa90144 */ 	lw	$t1,0x144($sp)
/*  f021934:	8faa0148 */ 	lw	$t2,0x148($sp)
/*  f021938:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f02193c:	10000045 */ 	b	.L0f021a54
/*  f021940:	46086300 */ 	add.s	$f12,$f12,$f8
.L0f021944:
/*  f021944:	54e90044 */ 	bnel	$a3,$t1,.L0f021a58
/*  f021948:	80d90012 */ 	lb	$t9,0x12($a2)
/*  f02194c:	94d90192 */ 	lhu	$t9,0x192($a2)
/*  f021950:	3c017f1b */ 	lui	$at,%hi(var7f1a8768)
/*  f021954:	3c18800a */ 	lui	$t8,%hi(g_Vars+0x2ac)
/*  f021958:	332b0004 */ 	andi	$t3,$t9,0x4
/*  f02195c:	51600012 */ 	beqzl	$t3,.L0f0219a8
/*  f021960:	8ccc0020 */ 	lw	$t4,0x20($a2)
/*  f021964:	c4208768 */ 	lwc1	$f0,%lo(var7f1a8768)($at)
/*  f021968:	c4ce0158 */ 	lwc1	$f14,0x158($a2)
/*  f02196c:	3c017f1b */ 	lui	$at,%hi(var7f1a876c)
/*  f021970:	460e003c */ 	c.lt.s	$f0,$f14
/*  f021974:	00000000 */ 	nop
/*  f021978:	45000003 */ 	bc1f	.L0f021988
/*  f02197c:	00000000 */ 	nop
/*  f021980:	10000010 */ 	b	.L0f0219c4
/*  f021984:	46000386 */ 	mov.s	$f14,$f0
.L0f021988:
/*  f021988:	c420876c */ 	lwc1	$f0,%lo(var7f1a876c)($at)
/*  f02198c:	4600703c */ 	c.lt.s	$f14,$f0
/*  f021990:	00000000 */ 	nop
/*  f021994:	4502000c */ 	bc1fl	.L0f0219c8
/*  f021998:	84cf02d8 */ 	lh	$t7,0x2d8($a2)
/*  f02199c:	10000009 */ 	b	.L0f0219c4
/*  f0219a0:	46000386 */ 	mov.s	$f14,$f0
/*  f0219a4:	8ccc0020 */ 	lw	$t4,0x20($a2)
.L0f0219a8:
/*  f0219a8:	8d8d0020 */ 	lw	$t5,0x20($t4)
/*  f0219ac:	81ae0008 */ 	lb	$t6,0x8($t5)
/*  f0219b0:	51c00004 */ 	beqzl	$t6,.L0f0219c4
/*  f0219b4:	c4ce0154 */ 	lwc1	$f14,0x154($a2)
/*  f0219b8:	10000002 */ 	b	.L0f0219c4
/*  f0219bc:	c4ce0150 */ 	lwc1	$f14,0x150($a2)
/*  f0219c0:	c4ce0154 */ 	lwc1	$f14,0x154($a2)
.L0f0219c4:
/*  f0219c4:	84cf02d8 */ 	lh	$t7,0x2d8($a2)
.L0f0219c8:
/*  f0219c8:	29e103e9 */ 	slti	$at,$t7,0x3e9
/*  f0219cc:	54200022 */ 	bnezl	$at,.L0f021a58
/*  f0219d0:	80d90012 */ 	lb	$t9,0x12($a2)
/*  f0219d4:	8f18a26c */ 	lw	$t8,%lo(g_Vars+0x2ac)($t8)
/*  f0219d8:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0219dc:	5301001e */ 	beql	$t8,$at,.L0f021a58
/*  f0219e0:	80d90012 */ 	lb	$t9,0x12($a2)
/*  f0219e4:	80c20007 */ 	lb	$v0,0x7($a2)
/*  f0219e8:	24010005 */ 	addiu	$at,$zero,0x5
/*  f0219ec:	10410019 */ 	beq	$v0,$at,.L0f021a54
/*  f0219f0:	24010004 */ 	addiu	$at,$zero,0x4
/*  f0219f4:	10410017 */ 	beq	$v0,$at,.L0f021a54
/*  f0219f8:	3c017f1b */ 	lui	$at,%hi(var7f1a8770)
/*  f0219fc:	c4328770 */ 	lwc1	$f18,%lo(var7f1a8770)($at)
/*  f021a00:	3c0143b4 */ 	lui	$at,0x43b4
/*  f021a04:	44815000 */ 	mtc1	$at,$f10
/*  f021a08:	c4c002dc */ 	lwc1	$f0,0x2dc($a2)
/*  f021a0c:	44804000 */ 	mtc1	$zero,$f8
/*  f021a10:	3c0141e0 */ 	lui	$at,0x41e0
/*  f021a14:	460a0103 */ 	div.s	$f4,$f0,$f10
/*  f021a18:	44815000 */ 	mtc1	$at,$f10
/*  f021a1c:	3c01437a */ 	lui	$at,0x437a
/*  f021a20:	4600403c */ 	c.lt.s	$f8,$f0
/*  f021a24:	46122182 */ 	mul.s	$f6,$f4,$f18
/*  f021a28:	45000003 */ 	bc1f	.L0f021a38
/*  f021a2c:	e7a6009c */ 	swc1	$f6,0x9c($sp)
/*  f021a30:	10000002 */ 	b	.L0f021a3c
/*  f021a34:	46000086 */ 	mov.s	$f2,$f0
.L0f021a38:
/*  f021a38:	46000087 */ 	neg.s	$f2,$f0
.L0f021a3c:
/*  f021a3c:	46025101 */ 	sub.s	$f4,$f10,$f2
/*  f021a40:	44813000 */ 	mtc1	$at,$f6
/*  f021a44:	00000000 */ 	nop
/*  f021a48:	46062203 */ 	div.s	$f8,$f4,$f6
/*  f021a4c:	46124282 */ 	mul.s	$f10,$f8,$f18
/*  f021a50:	460a7381 */ 	sub.s	$f14,$f14,$f10
.L0f021a54:
/*  f021a54:	80d90012 */ 	lb	$t9,0x12($a2)
.L0f021a58:
/*  f021a58:	072200c4 */ 	bltzl	$t9,.L0f021d6c
/*  f021a5c:	46107032 */ 	c.eq.s	$f14,$f16
/*  f021a60:	10c00003 */ 	beqz	$a2,.L0f021a70
/*  f021a64:	00001025 */ 	or	$v0,$zero,$zero
/*  f021a68:	10000001 */ 	b	.L0f021a70
/*  f021a6c:	90c202fe */ 	lbu	$v0,0x2fe($a2)
.L0f021a70:
/*  f021a70:	10400007 */ 	beqz	$v0,.L0f021a90
/*  f021a74:	24010001 */ 	addiu	$at,$zero,0x1
/*  f021a78:	10c00003 */ 	beqz	$a2,.L0f021a88
/*  f021a7c:	00001025 */ 	or	$v0,$zero,$zero
/*  f021a80:	10000001 */ 	b	.L0f021a88
/*  f021a84:	90c202fe */ 	lbu	$v0,0x2fe($a2)
.L0f021a88:
/*  f021a88:	544100b8 */ 	bnel	$v0,$at,.L0f021d6c
/*  f021a8c:	46107032 */ 	c.eq.s	$f14,$f16
.L0f021a90:
/*  f021a90:	10c00003 */ 	beqz	$a2,.L0f021aa0
/*  f021a94:	94c30192 */ 	lhu	$v1,0x192($a2)
/*  f021a98:	10000002 */ 	b	.L0f021aa4
/*  f021a9c:	90c202fe */ 	lbu	$v0,0x2fe($a2)
.L0f021aa0:
/*  f021aa0:	00001025 */ 	or	$v0,$zero,$zero
.L0f021aa4:
/*  f021aa4:	306b1000 */ 	andi	$t3,$v1,0x1000
/*  f021aa8:	1160005f */ 	beqz	$t3,.L0f021c28
/*  f021aac:	00000000 */ 	nop
/*  f021ab0:	14e900ad */ 	bne	$a3,$t1,.L0f021d68
/*  f021ab4:	00c02025 */ 	or	$a0,$a2,$zero
/*  f021ab8:	afa20028 */ 	sw	$v0,0x28($sp)
/*  f021abc:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f021ac0:	0fc0850f */ 	jal	func0f02143c
/*  f021ac4:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021ac8:	3c0c800a */ 	lui	$t4,%hi(var8009cd1c)
/*  f021acc:	8d8ccd1c */ 	lw	$t4,%lo(var8009cd1c)($t4)
/*  f021ad0:	8fa20028 */ 	lw	$v0,0x28($sp)
/*  f021ad4:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f021ad8:	95830192 */ 	lhu	$v1,0x192($t4)
/*  f021adc:	00452026 */ 	xor	$a0,$v0,$a1
/*  f021ae0:	44808000 */ 	mtc1	$zero,$f16
/*  f021ae4:	3c017f1b */ 	lui	$at,%hi(var7f1a8778)
/*  f021ae8:	2c840001 */ 	sltiu	$a0,$a0,0x1
/*  f021aec:	00036b43 */ 	sra	$t5,$v1,0xd
/*  f021af0:	c4328778 */ 	lwc1	$f18,%lo(var7f1a8778)($at)
/*  f021af4:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021af8:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021afc:	10800005 */ 	beqz	$a0,.L0f021b14
/*  f021b00:	31a30007 */ 	andi	$v1,$t5,0x7
/*  f021b04:	3c0141c8 */ 	lui	$at,0x41c8
/*  f021b08:	44811000 */ 	mtc1	$at,$f2
/*  f021b0c:	10000005 */ 	b	.L0f021b24
/*  f021b10:	306f0001 */ 	andi	$t7,$v1,0x1
.L0f021b14:
/*  f021b14:	3c014270 */ 	lui	$at,0x4270
/*  f021b18:	44811000 */ 	mtc1	$at,$f2
/*  f021b1c:	00000000 */ 	nop
/*  f021b20:	306f0001 */ 	andi	$t7,$v1,0x1
.L0f021b24:
/*  f021b24:	55e0000a */ 	bnezl	$t7,.L0f021b50
/*  f021b28:	28610005 */ 	slti	$at,$v1,0x5
/*  f021b2c:	10800005 */ 	beqz	$a0,.L0f021b44
/*  f021b30:	3c0142aa */ 	lui	$at,0x42aa
/*  f021b34:	3c014216 */ 	lui	$at,0x4216
/*  f021b38:	44811000 */ 	mtc1	$at,$f2
/*  f021b3c:	10000004 */ 	b	.L0f021b50
/*  f021b40:	28610005 */ 	slti	$at,$v1,0x5
.L0f021b44:
/*  f021b44:	44811000 */ 	mtc1	$at,$f2
/*  f021b48:	00000000 */ 	nop
/*  f021b4c:	28610005 */ 	slti	$at,$v1,0x5
.L0f021b50:
/*  f021b50:	1420000d */ 	bnez	$at,.L0f021b88
/*  f021b54:	28610008 */ 	slti	$at,$v1,0x8
/*  f021b58:	1020000b */ 	beqz	$at,.L0f021b88
/*  f021b5c:	00000000 */ 	nop
/*  f021b60:	46029102 */ 	mul.s	$f4,$f18,$f2
/*  f021b64:	3c0143b4 */ 	lui	$at,0x43b4
/*  f021b68:	44813000 */ 	mtc1	$at,$f6
/*  f021b6c:	00000000 */ 	nop
/*  f021b70:	46062203 */ 	div.s	$f8,$f4,$f6
/*  f021b74:	c7a4009c */ 	lwc1	$f4,0x9c($sp)
/*  f021b78:	46080282 */ 	mul.s	$f10,$f0,$f8
/*  f021b7c:	460a2181 */ 	sub.s	$f6,$f4,$f10
/*  f021b80:	1000000e */ 	b	.L0f021bbc
/*  f021b84:	e7a6009c */ 	swc1	$f6,0x9c($sp)
.L0f021b88:
/*  f021b88:	1860000c */ 	blez	$v1,.L0f021bbc
/*  f021b8c:	28610004 */ 	slti	$at,$v1,0x4
/*  f021b90:	5020000b */ 	beqzl	$at,.L0f021bc0
/*  f021b94:	24010007 */ 	addiu	$at,$zero,0x7
/*  f021b98:	46029202 */ 	mul.s	$f8,$f18,$f2
/*  f021b9c:	3c0143b4 */ 	lui	$at,0x43b4
/*  f021ba0:	44812000 */ 	mtc1	$at,$f4
/*  f021ba4:	00000000 */ 	nop
/*  f021ba8:	46044283 */ 	div.s	$f10,$f8,$f4
/*  f021bac:	c7a8009c */ 	lwc1	$f8,0x9c($sp)
/*  f021bb0:	460a0182 */ 	mul.s	$f6,$f0,$f10
/*  f021bb4:	46064100 */ 	add.s	$f4,$f8,$f6
/*  f021bb8:	e7a4009c */ 	swc1	$f4,0x9c($sp)
.L0f021bbc:
/*  f021bbc:	24010007 */ 	addiu	$at,$zero,0x7
.L0f021bc0:
/*  f021bc0:	10610005 */ 	beq	$v1,$at,.L0f021bd8
/*  f021bc4:	00000000 */ 	nop
/*  f021bc8:	10600003 */ 	beqz	$v1,.L0f021bd8
/*  f021bcc:	00000000 */ 	nop
/*  f021bd0:	14650009 */ 	bne	$v1,$a1,.L0f021bf8
/*  f021bd4:	28610003 */ 	slti	$at,$v1,0x3
.L0f021bd8:
/*  f021bd8:	46029282 */ 	mul.s	$f10,$f18,$f2
/*  f021bdc:	3c0143b4 */ 	lui	$at,0x43b4
/*  f021be0:	44814000 */ 	mtc1	$at,$f8
/*  f021be4:	00000000 */ 	nop
/*  f021be8:	46085183 */ 	div.s	$f6,$f10,$f8
/*  f021bec:	46060102 */ 	mul.s	$f4,$f0,$f6
/*  f021bf0:	1000005d */ 	b	.L0f021d68
/*  f021bf4:	46047380 */ 	add.s	$f14,$f14,$f4
.L0f021bf8:
/*  f021bf8:	1420005b */ 	bnez	$at,.L0f021d68
/*  f021bfc:	28610006 */ 	slti	$at,$v1,0x6
/*  f021c00:	5020005a */ 	beqzl	$at,.L0f021d6c
/*  f021c04:	46107032 */ 	c.eq.s	$f14,$f16
/*  f021c08:	46029282 */ 	mul.s	$f10,$f18,$f2
/*  f021c0c:	3c0143b4 */ 	lui	$at,0x43b4
/*  f021c10:	44814000 */ 	mtc1	$at,$f8
/*  f021c14:	00000000 */ 	nop
/*  f021c18:	46085183 */ 	div.s	$f6,$f10,$f8
/*  f021c1c:	46060102 */ 	mul.s	$f4,$f0,$f6
/*  f021c20:	10000051 */ 	b	.L0f021d68
/*  f021c24:	46047381 */ 	sub.s	$f14,$f14,$f4
.L0f021c28:
/*  f021c28:	10e80002 */ 	beq	$a3,$t0,.L0f021c34
/*  f021c2c:	00031343 */ 	sra	$v0,$v1,0xd
/*  f021c30:	14e50019 */ 	bne	$a3,$a1,.L0f021c98
.L0f021c34:
/*  f021c34:	30580007 */ 	andi	$t8,$v0,0x7
/*  f021c38:	afb80088 */ 	sw	$t8,0x88($sp)
/*  f021c3c:	00c02025 */ 	or	$a0,$a2,$zero
/*  f021c40:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f021c44:	0fc0850f */ 	jal	func0f02143c
/*  f021c48:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021c4c:	3c017f1b */ 	lui	$at,%hi(var7f1a8780)
/*  f021c50:	c42a8780 */ 	lwc1	$f10,%lo(var7f1a8780)($at)
/*  f021c54:	8fa20088 */ 	lw	$v0,0x88($sp)
/*  f021c58:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021c5c:	460a0082 */ 	mul.s	$f2,$f0,$f10
/*  f021c60:	44808000 */ 	mtc1	$zero,$f16
/*  f021c64:	28410003 */ 	slti	$at,$v0,0x3
/*  f021c68:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021c6c:	10200003 */ 	beqz	$at,.L0f021c7c
/*  f021c70:	46027381 */ 	sub.s	$f14,$f14,$f2
/*  f021c74:	1000003c */ 	b	.L0f021d68
/*  f021c78:	46026301 */ 	sub.s	$f12,$f12,$f2
.L0f021c7c:
/*  f021c7c:	28410003 */ 	slti	$at,$v0,0x3
/*  f021c80:	14200039 */ 	bnez	$at,.L0f021d68
/*  f021c84:	28410006 */ 	slti	$at,$v0,0x6
/*  f021c88:	50200038 */ 	beqzl	$at,.L0f021d6c
/*  f021c8c:	46107032 */ 	c.eq.s	$f14,$f16
/*  f021c90:	10000035 */ 	b	.L0f021d68
/*  f021c94:	46026300 */ 	add.s	$f12,$f12,$f2
.L0f021c98:
/*  f021c98:	14ea0033 */ 	bne	$a3,$t2,.L0f021d68
/*  f021c9c:	00c02025 */ 	or	$a0,$a2,$zero
/*  f021ca0:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f021ca4:	0fc0850f */ 	jal	func0f02143c
/*  f021ca8:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021cac:	3c19800a */ 	lui	$t9,%hi(var8009cd1c)
/*  f021cb0:	3c017f1b */ 	lui	$at,%hi(var7f1a8788)
/*  f021cb4:	8f39cd1c */ 	lw	$t9,%lo(var8009cd1c)($t9)
/*  f021cb8:	c4288788 */ 	lwc1	$f8,%lo(var7f1a8788)($at)
/*  f021cbc:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021cc0:	97220192 */ 	lhu	$v0,0x192($t9)
/*  f021cc4:	46080082 */ 	mul.s	$f2,$f0,$f8
/*  f021cc8:	44808000 */ 	mtc1	$zero,$f16
/*  f021ccc:	00025b43 */ 	sra	$t3,$v0,0xd
/*  f021cd0:	31620007 */ 	andi	$v0,$t3,0x7
/*  f021cd4:	28410003 */ 	slti	$at,$v0,0x3
/*  f021cd8:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f021cdc:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021ce0:	10200003 */ 	beqz	$at,.L0f021cf0
/*  f021ce4:	46027380 */ 	add.s	$f14,$f14,$f2
/*  f021ce8:	10000007 */ 	b	.L0f021d08
/*  f021cec:	46026300 */ 	add.s	$f12,$f12,$f2
.L0f021cf0:
/*  f021cf0:	28410003 */ 	slti	$at,$v0,0x3
/*  f021cf4:	14200004 */ 	bnez	$at,.L0f021d08
/*  f021cf8:	28410006 */ 	slti	$at,$v0,0x6
/*  f021cfc:	50200003 */ 	beqzl	$at,.L0f021d0c
/*  f021d00:	24010002 */ 	addiu	$at,$zero,0x2
/*  f021d04:	46026301 */ 	sub.s	$f12,$f12,$f2
.L0f021d08:
/*  f021d08:	24010002 */ 	addiu	$at,$zero,0x2
.L0f021d0c:
/*  f021d0c:	10410004 */ 	beq	$v0,$at,.L0f021d20
/*  f021d10:	24010005 */ 	addiu	$at,$zero,0x5
/*  f021d14:	10410002 */ 	beq	$v0,$at,.L0f021d20
/*  f021d18:	24010007 */ 	addiu	$at,$zero,0x7
/*  f021d1c:	14410007 */ 	bne	$v0,$at,.L0f021d3c
.L0f021d20:
/*  f021d20:	3c017f1b */ 	lui	$at,%hi(var7f1a878c)
/*  f021d24:	c424878c */ 	lwc1	$f4,%lo(var7f1a878c)($at)
/*  f021d28:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
/*  f021d2c:	46040282 */ 	mul.s	$f10,$f0,$f4
/*  f021d30:	460a3200 */ 	add.s	$f8,$f6,$f10
/*  f021d34:	1000000c */ 	b	.L0f021d68
/*  f021d38:	e7a8009c */ 	swc1	$f8,0x9c($sp)
.L0f021d3c:
/*  f021d3c:	10450004 */ 	beq	$v0,$a1,.L0f021d50
/*  f021d40:	24010004 */ 	addiu	$at,$zero,0x4
/*  f021d44:	10410002 */ 	beq	$v0,$at,.L0f021d50
/*  f021d48:	24010006 */ 	addiu	$at,$zero,0x6
/*  f021d4c:	14410006 */ 	bne	$v0,$at,.L0f021d68
.L0f021d50:
/*  f021d50:	3c017f1b */ 	lui	$at,%hi(var7f1a8790)
/*  f021d54:	c4268790 */ 	lwc1	$f6,%lo(var7f1a8790)($at)
/*  f021d58:	c7a4009c */ 	lwc1	$f4,0x9c($sp)
/*  f021d5c:	46060282 */ 	mul.s	$f10,$f0,$f6
/*  f021d60:	460a2201 */ 	sub.s	$f8,$f4,$f10
/*  f021d64:	e7a8009c */ 	swc1	$f8,0x9c($sp)
.L0f021d68:
/*  f021d68:	46107032 */ 	c.eq.s	$f14,$f16
.L0f021d6c:
/*  f021d6c:	3c04800a */ 	lui	$a0,%hi(var8009cd1c)
/*  f021d70:	45000010 */ 	bc1f	.L0f021db4
/*  f021d74:	00000000 */ 	nop
/*  f021d78:	46106032 */ 	c.eq.s	$f12,$f16
/*  f021d7c:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
/*  f021d80:	4500000c */ 	bc1f	.L0f021db4
/*  f021d84:	00000000 */ 	nop
/*  f021d88:	46103032 */ 	c.eq.s	$f6,$f16
/*  f021d8c:	c7a40154 */ 	lwc1	$f4,0x154($sp)
/*  f021d90:	3c013f80 */ 	lui	$at,0x3f80
/*  f021d94:	45000007 */ 	bc1f	.L0f021db4
/*  f021d98:	00000000 */ 	nop
/*  f021d9c:	44815000 */ 	mtc1	$at,$f10
/*  f021da0:	00000000 */ 	nop
/*  f021da4:	460a2032 */ 	c.eq.s	$f4,$f10
/*  f021da8:	00000000 */ 	nop
/*  f021dac:	4503007b */ 	bc1tl	.L0f021f9c
/*  f021db0:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f021db4:
/*  f021db4:	8c84cd1c */ 	lw	$a0,%lo(var8009cd1c)($a0)
/*  f021db8:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f021dbc:	0fc0f97c */ 	jal	chrGetAimAngle
/*  f021dc0:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021dc4:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021dc8:	44808000 */ 	mtc1	$zero,$f16
/*  f021dcc:	3c017f1b */ 	lui	$at,%hi(var7f1a8794)
/*  f021dd0:	c4328794 */ 	lwc1	$f18,%lo(var7f1a8794)($at)
/*  f021dd4:	4610703c */ 	c.lt.s	$f14,$f16
/*  f021dd8:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021ddc:	e7a0006c */ 	swc1	$f0,0x6c($sp)
/*  f021de0:	45020004 */ 	bc1fl	.L0f021df4
/*  f021de4:	460e9381 */ 	sub.s	$f14,$f18,$f14
/*  f021de8:	10000002 */ 	b	.L0f021df4
/*  f021dec:	46007387 */ 	neg.s	$f14,$f14
/*  f021df0:	460e9381 */ 	sub.s	$f14,$f18,$f14
.L0f021df4:
/*  f021df4:	4610603c */ 	c.lt.s	$f12,$f16
/*  f021df8:	00000000 */ 	nop
/*  f021dfc:	45020003 */ 	bc1fl	.L0f021e0c
/*  f021e00:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
/*  f021e04:	46126300 */ 	add.s	$f12,$f12,$f18
/*  f021e08:	e7ac00a0 */ 	swc1	$f12,0xa0($sp)
.L0f021e0c:
/*  f021e0c:	0fc2d5de */ 	jal	currentPlayerGetUnk174c
/*  f021e10:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021e14:	00402025 */ 	or	$a0,$v0,$zero
/*  f021e18:	0c0056f8 */ 	jal	func00015be0
/*  f021e1c:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021e20:	8fa2015c */ 	lw	$v0,0x15c($sp)
/*  f021e24:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021e28:	44808000 */ 	mtc1	$zero,$f16
/*  f021e2c:	c4480030 */ 	lwc1	$f8,0x30($v0)
/*  f021e30:	3c017f1b */ 	lui	$at,%hi(var7f1a879c)
/*  f021e34:	46107032 */ 	c.eq.s	$f14,$f16
/*  f021e38:	e7a80070 */ 	swc1	$f8,0x70($sp)
/*  f021e3c:	c4460034 */ 	lwc1	$f6,0x34($v0)
/*  f021e40:	c432879c */ 	lwc1	$f18,%lo(var7f1a879c)($at)
/*  f021e44:	c7ac00a0 */ 	lwc1	$f12,0xa0($sp)
/*  f021e48:	e7a60074 */ 	swc1	$f6,0x74($sp)
/*  f021e4c:	c4440038 */ 	lwc1	$f4,0x38($v0)
/*  f021e50:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f021e54:	e7a40078 */ 	swc1	$f4,0x78($sp)
/*  f021e58:	e4500030 */ 	swc1	$f16,0x30($v0)
/*  f021e5c:	e4500034 */ 	swc1	$f16,0x34($v0)
/*  f021e60:	45000006 */ 	bc1f	.L0f021e7c
/*  f021e64:	e4500038 */ 	swc1	$f16,0x38($v0)
/*  f021e68:	c7aa009c */ 	lwc1	$f10,0x9c($sp)
/*  f021e6c:	46105032 */ 	c.eq.s	$f10,$f16
/*  f021e70:	00000000 */ 	nop
/*  f021e74:	4501002e */ 	bc1t	.L0f021f30
/*  f021e78:	00000000 */ 	nop
.L0f021e7c:
/*  f021e7c:	c7a8006c */ 	lwc1	$f8,0x6c($sp)
/*  f021e80:	46086301 */ 	sub.s	$f12,$f12,$f8
/*  f021e84:	4610603c */ 	c.lt.s	$f12,$f16
/*  f021e88:	00000000 */ 	nop
/*  f021e8c:	45000002 */ 	bc1f	.L0f021e98
/*  f021e90:	00000000 */ 	nop
/*  f021e94:	46126300 */ 	add.s	$f12,$f12,$f18
.L0f021e98:
/*  f021e98:	0c0058dd */ 	jal	func00016374
/*  f021e9c:	e7ae00a4 */ 	swc1	$f14,0xa4($sp)
/*  f021ea0:	27a4002c */ 	addiu	$a0,$sp,0x2c
/*  f021ea4:	0c0056f8 */ 	jal	func00015be0
/*  f021ea8:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021eac:	c7ae00a4 */ 	lwc1	$f14,0xa4($sp)
/*  f021eb0:	44808000 */ 	mtc1	$zero,$f16
/*  f021eb4:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f021eb8:	46107032 */ 	c.eq.s	$f14,$f16
/*  f021ebc:	00000000 */ 	nop
/*  f021ec0:	45030009 */ 	bc1tl	.L0f021ee8
/*  f021ec4:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
/*  f021ec8:	0c0058ba */ 	jal	func000162e8
/*  f021ecc:	46007306 */ 	mov.s	$f12,$f14
/*  f021ed0:	27a4002c */ 	addiu	$a0,$sp,0x2c
/*  f021ed4:	0c0056f8 */ 	jal	func00015be0
/*  f021ed8:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021edc:	44808000 */ 	mtc1	$zero,$f16
/*  f021ee0:	00000000 */ 	nop
/*  f021ee4:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
.L0f021ee8:
/*  f021ee8:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f021eec:	46103032 */ 	c.eq.s	$f6,$f16
/*  f021ef0:	00000000 */ 	nop
/*  f021ef4:	45030007 */ 	bc1tl	.L0f021f14
/*  f021ef8:	c7ac006c */ 	lwc1	$f12,0x6c($sp)
/*  f021efc:	0c005900 */ 	jal	func00016400
/*  f021f00:	46003306 */ 	mov.s	$f12,$f6
/*  f021f04:	27a4002c */ 	addiu	$a0,$sp,0x2c
/*  f021f08:	0c0056f8 */ 	jal	func00015be0
/*  f021f0c:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021f10:	c7ac006c */ 	lwc1	$f12,0x6c($sp)
.L0f021f14:
/*  f021f14:	0c0058dd */ 	jal	func00016374
/*  f021f18:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f021f1c:	27a4002c */ 	addiu	$a0,$sp,0x2c
/*  f021f20:	0c0056f8 */ 	jal	func00015be0
/*  f021f24:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021f28:	10000007 */ 	b	.L0f021f48
/*  f021f2c:	3c013f80 */ 	lui	$at,0x3f80
.L0f021f30:
/*  f021f30:	0c0058dd */ 	jal	func00016374
/*  f021f34:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f021f38:	27a4002c */ 	addiu	$a0,$sp,0x2c
/*  f021f3c:	0c0056f8 */ 	jal	func00015be0
/*  f021f40:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021f44:	3c013f80 */ 	lui	$at,0x3f80
.L0f021f48:
/*  f021f48:	44815000 */ 	mtc1	$at,$f10
/*  f021f4c:	c7a40154 */ 	lwc1	$f4,0x154($sp)
/*  f021f50:	8fa5015c */ 	lw	$a1,0x15c($sp)
/*  f021f54:	460a2032 */ 	c.eq.s	$f4,$f10
/*  f021f58:	00000000 */ 	nop
/*  f021f5c:	45030004 */ 	bc1tl	.L0f021f70
/*  f021f60:	c7a80070 */ 	lwc1	$f8,0x70($sp)
/*  f021f64:	0c0057c1 */ 	jal	func00015f04
/*  f021f68:	46002306 */ 	mov.s	$f12,$f4
/*  f021f6c:	c7a80070 */ 	lwc1	$f8,0x70($sp)
.L0f021f70:
/*  f021f70:	8fad015c */ 	lw	$t5,0x15c($sp)
/*  f021f74:	e5a80030 */ 	swc1	$f8,0x30($t5)
/*  f021f78:	c7a60074 */ 	lwc1	$f6,0x74($sp)
/*  f021f7c:	e5a60034 */ 	swc1	$f6,0x34($t5)
/*  f021f80:	c7aa0078 */ 	lwc1	$f10,0x78($sp)
/*  f021f84:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f021f88:	e5aa0038 */ 	swc1	$f10,0x38($t5)
/*  f021f8c:	00402025 */ 	or	$a0,$v0,$zero
/*  f021f90:	0c0056f8 */ 	jal	func00015be0
/*  f021f94:	8fa5015c */ 	lw	$a1,0x15c($sp)
.L0f021f98:
/*  f021f98:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f021f9c:
/*  f021f9c:	27bd0158 */ 	addiu	$sp,$sp,0x158
/*  f021fa0:	03e00008 */ 	jr	$ra
/*  f021fa4:	00000000 */ 	nop
);
#endif

void func0f021fa8(struct chrdata *chr, struct coord *pos, s16 *rooms)
{
	struct coord lower;
	struct coord upper;
	f32 height = 110;

	if (
#if VERSION >= VERSION_NTSC_1_0
			chr && chr->race == RACE_EYESPY
#else
			chr->race == RACE_EYESPY
#endif
			) {
		struct eyespy *eyespy = chrToEyespy(chr);

		if (eyespy) {
			height = eyespy->height + 30.0f;
		} else {
			height = 230;
		}
	}

	lower.x = pos->x - 50.0f;
	lower.y = pos->y - height;
	lower.z = pos->z - 50.0f;

	upper.x = pos->x + 50.0f;
	upper.y = pos->y + height;
	upper.z = pos->z + 50.0f;

	func0f1650d0(&lower, &upper, rooms, 7, 1);
}

void func0f022084(struct chrdata *chr, s16 *room)
{
	func0f021fa8(chr, &chr->prop->pos, room);
}

void func0f0220ac(struct chrdata *chr)
{
	propDeregisterRooms(chr->prop);
	func0f022084(chr, chr->prop->rooms);
	propRegisterRooms(chr->prop);
}

void func0f0220ec(struct chrdata *chr, s32 arg1, s32 arg2)
{
	struct model *model = chr->model;

	if (g_Vars.tickmode == TICKMODE_CUTSCENE) {
		if (chr->prop->type == PROPTYPE_PLAYER) {
			chr->hidden &= ~CHRHFLAG_00000800;
		}

		if (model->anim
				&& (g_Anims[model->anim->animnum].flags & ANIMFLAG_02)
				&& arg1 > 0
				&& g_Vars.cutsceneskip60ths > 0) {
			arg1 += g_Vars.cutsceneskip60ths * 4;
		}
	}

	if (chr->chrflags & CHRCFLAG_20000000) {
		chr->chrflags &= ~CHRCFLAG_20000000;
	} else if (arg2) {
		if ((chr->hidden & CHRHFLAG_00000800) == 0) {
			modelGetRootPosition(model, &chr->prevpos);
			func0001ee18(model, arg1, 1);
			func0001b3bc(model);
		}
	} else {
		func0001ee18(model, arg1, 0);
	}
}

GLOBAL_ASM(
glabel func0f022214
.late_rodata
glabel var7f1a87a0
.word 0x3fa8dd79
glabel var7f1a87a4
.word 0x3fc907a9
glabel var7f1a87a8
.word 0x404907a9
.text
/*  f022214:	27bdfee8 */ 	addiu	$sp,$sp,-280
/*  f022218:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f02221c:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f022220:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f022224:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f022228:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f02222c:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f022230:	8cb00004 */ 	lw	$s0,0x4($a1)
/*  f022234:	00a09025 */ 	or	$s2,$a1,$zero
/*  f022238:	00c09825 */ 	or	$s3,$a2,$zero
/*  f02223c:	8e020040 */ 	lw	$v0,0x40($s0)
/*  f022240:	0080a025 */ 	or	$s4,$a0,$zero
/*  f022244:	8e030018 */ 	lw	$v1,0x18($s0)
/*  f022248:	304e0004 */ 	andi	$t6,$v0,0x4
/*  f02224c:	51c0000a */ 	beqzl	$t6,.L0f022278
/*  f022250:	8c640018 */ 	lw	$a0,0x18($v1)
/*  f022254:	92060002 */ 	lbu	$a2,0x2($s0)
/*  f022258:	02002025 */ 	or	$a0,$s0,$zero
/*  f02225c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f022260:	30cf0004 */ 	andi	$t7,$a2,0x4
/*  f022264:	0fc1ab4b */ 	jal	objRemove2
/*  f022268:	01e03025 */ 	or	$a2,$t7,$zero
/*  f02226c:	1000007e */ 	b	.L0f022468
/*  f022270:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f022274:	8c640018 */ 	lw	$a0,0x18($v1)
.L0f022278:
/*  f022278:	5080006c */ 	beqzl	$a0,.L0f02242c
/*  f02227c:	924a0001 */ 	lbu	$t2,0x1($s2)
/*  f022280:	8c65001c */ 	lw	$a1,0x1c($v1)
/*  f022284:	30580800 */ 	andi	$t8,$v0,0x800
/*  f022288:	50a00068 */ 	beqzl	$a1,.L0f02242c
/*  f02228c:	924a0001 */ 	lbu	$t2,0x1($s2)
/*  f022290:	57000066 */ 	bnezl	$t8,.L0f02242c
/*  f022294:	924a0001 */ 	lbu	$t2,0x1($s2)
/*  f022298:	8e19000c */ 	lw	$t9,0xc($s0)
/*  f02229c:	00003025 */ 	or	$a2,$zero,$zero
/*  f0222a0:	00194300 */ 	sll	$t0,$t9,0xc
/*  f0222a4:	05020061 */ 	bltzl	$t0,.L0f02242c
/*  f0222a8:	924a0001 */ 	lbu	$t2,0x1($s2)
/*  f0222ac:	0c006973 */ 	jal	func0001a5cc
/*  f0222b0:	afa30110 */ 	sw	$v1,0x110($sp)
/*  f0222b4:	3c0a8006 */ 	lui	$t2,%hi(var80062998)
/*  f0222b8:	254a2998 */ 	addiu	$t2,$t2,%lo(var80062998)
/*  f0222bc:	afa20104 */ 	sw	$v0,0x104($sp)
/*  f0222c0:	254d003c */ 	addiu	$t5,$t2,0x3c
/*  f0222c4:	27a900c4 */ 	addiu	$t1,$sp,0xc4
.L0f0222c8:
/*  f0222c8:	8d410000 */ 	lw	$at,0x0($t2)
/*  f0222cc:	254a000c */ 	addiu	$t2,$t2,0xc
/*  f0222d0:	2529000c */ 	addiu	$t1,$t1,0xc
/*  f0222d4:	ad21fff4 */ 	sw	$at,-0xc($t1)
/*  f0222d8:	8d41fff8 */ 	lw	$at,-0x8($t2)
/*  f0222dc:	ad21fff8 */ 	sw	$at,-0x8($t1)
/*  f0222e0:	8d41fffc */ 	lw	$at,-0x4($t2)
/*  f0222e4:	154dfff8 */ 	bne	$t2,$t5,.L0f0222c8
/*  f0222e8:	ad21fffc */ 	sw	$at,-0x4($t1)
/*  f0222ec:	8d410000 */ 	lw	$at,0x0($t2)
/*  f0222f0:	27b10080 */ 	addiu	$s1,$sp,0x80
/*  f0222f4:	ad210000 */ 	sw	$at,0x0($t1)
/*  f0222f8:	924e0001 */ 	lbu	$t6,0x1($s2)
/*  f0222fc:	24010001 */ 	addiu	$at,$zero,0x1
/*  f022300:	35cf0042 */ 	ori	$t7,$t6,0x42
/*  f022304:	a24f0001 */ 	sb	$t7,0x1($s2)
/*  f022308:	8e180040 */ 	lw	$t8,0x40($s0)
/*  f02230c:	8fa40104 */ 	lw	$a0,0x104($sp)
/*  f022310:	33190040 */ 	andi	$t9,$t8,0x40
/*  f022314:	13200007 */ 	beqz	$t9,.L0f022334
/*  f022318:	00000000 */ 	nop
/*  f02231c:	8e050048 */ 	lw	$a1,0x48($s0)
/*  f022320:	02203025 */ 	or	$a2,$s1,$zero
/*  f022324:	0c0056f9 */ 	jal	func00015be4
/*  f022328:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f02232c:	10000025 */ 	b	.L0f0223c4
/*  f022330:	afb100c4 */ 	sw	$s1,0xc4($sp)
.L0f022334:
/*  f022334:	12800003 */ 	beqz	$s4,.L0f022344
/*  f022338:	00001825 */ 	or	$v1,$zero,$zero
/*  f02233c:	10000001 */ 	b	.L0f022344
/*  f022340:	928302fe */ 	lbu	$v1,0x2fe($s4)
.L0f022344:
/*  f022344:	14610012 */ 	bne	$v1,$at,.L0f022390
/*  f022348:	27b10080 */ 	addiu	$s1,$sp,0x80
/*  f02234c:	3c017f1b */ 	lui	$at,%hi(var7f1a87a0)
/*  f022350:	c42c87a0 */ 	lwc1	$f12,%lo(var7f1a87a0)($at)
/*  f022354:	0c0058dd */ 	jal	func00016374
/*  f022358:	02202825 */ 	or	$a1,$s1,$zero
/*  f02235c:	27b00040 */ 	addiu	$s0,$sp,0x40
/*  f022360:	3c017f1b */ 	lui	$at,%hi(var7f1a87a4)
/*  f022364:	c42c87a4 */ 	lwc1	$f12,%lo(var7f1a87a4)($at)
/*  f022368:	0c005900 */ 	jal	func00016400
/*  f02236c:	02002825 */ 	or	$a1,$s0,$zero
/*  f022370:	02002025 */ 	or	$a0,$s0,$zero
/*  f022374:	0c00567f */ 	jal	func000159fc
/*  f022378:	02202825 */ 	or	$a1,$s1,$zero
/*  f02237c:	8fa40104 */ 	lw	$a0,0x104($sp)
/*  f022380:	0c00567f */ 	jal	func000159fc
/*  f022384:	02202825 */ 	or	$a1,$s1,$zero
/*  f022388:	1000000e */ 	b	.L0f0223c4
/*  f02238c:	afb100c4 */ 	sw	$s1,0xc4($sp)
.L0f022390:
/*  f022390:	8e880174 */ 	lw	$t0,0x174($s4)
/*  f022394:	27b10080 */ 	addiu	$s1,$sp,0x80
/*  f022398:	02202825 */ 	or	$a1,$s1,$zero
/*  f02239c:	16480008 */ 	bne	$s2,$t0,.L0f0223c0
/*  f0223a0:	3c017f1b */ 	lui	$at,%hi(var7f1a87a8)
/*  f0223a4:	0c005900 */ 	jal	func00016400
/*  f0223a8:	c42c87a8 */ 	lwc1	$f12,%lo(var7f1a87a8)($at)
/*  f0223ac:	8fa40104 */ 	lw	$a0,0x104($sp)
/*  f0223b0:	0c00567f */ 	jal	func000159fc
/*  f0223b4:	02202825 */ 	or	$a1,$s1,$zero
/*  f0223b8:	10000002 */ 	b	.L0f0223c4
/*  f0223bc:	afb100c4 */ 	sw	$s1,0xc4($sp)
.L0f0223c0:
/*  f0223c0:	afa200c4 */ 	sw	$v0,0xc4($sp)
.L0f0223c4:
/*  f0223c4:	8fac0110 */ 	lw	$t4,0x110($sp)
/*  f0223c8:	8d8b0008 */ 	lw	$t3,0x8($t4)
/*  f0223cc:	8564000e */ 	lh	$a0,0xe($t3)
/*  f0223d0:	00046980 */ 	sll	$t5,$a0,0x6
/*  f0223d4:	0fc59e7d */ 	jal	gfxAllocate
/*  f0223d8:	01a02025 */ 	or	$a0,$t5,$zero
/*  f0223dc:	afa200d4 */ 	sw	$v0,0xd4($sp)
/*  f0223e0:	27a400c4 */ 	addiu	$a0,$sp,0xc4
/*  f0223e4:	0c007399 */ 	jal	func0001ce64
/*  f0223e8:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f0223ec:	02402025 */ 	or	$a0,$s2,$zero
/*  f0223f0:	0fc1c18f */ 	jal	func0f07063c
/*  f0223f4:	02602825 */ 	or	$a1,$s3,$zero
/*  f0223f8:	8e51001c */ 	lw	$s1,0x1c($s2)
/*  f0223fc:	5220001a */ 	beqzl	$s1,.L0f022468
/*  f022400:	8fbf002c */ 	lw	$ra,0x2c($sp)
.L0f022404:
/*  f022404:	8e300020 */ 	lw	$s0,0x20($s1)
/*  f022408:	02802025 */ 	or	$a0,$s4,$zero
/*  f02240c:	02202825 */ 	or	$a1,$s1,$zero
/*  f022410:	0fc08885 */ 	jal	func0f022214
/*  f022414:	02603025 */ 	or	$a2,$s3,$zero
/*  f022418:	1600fffa */ 	bnez	$s0,.L0f022404
/*  f02241c:	02008825 */ 	or	$s1,$s0,$zero
/*  f022420:	10000011 */ 	b	.L0f022468
/*  f022424:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f022428:	924a0001 */ 	lbu	$t2,0x1($s2)
.L0f02242c:
/*  f02242c:	02402025 */ 	or	$a0,$s2,$zero
/*  f022430:	02602825 */ 	or	$a1,$s3,$zero
/*  f022434:	3149fffd */ 	andi	$t1,$t2,0xfffd
/*  f022438:	0fc1c18f */ 	jal	func0f07063c
/*  f02243c:	a2490001 */ 	sb	$t1,0x1($s2)
/*  f022440:	8e51001c */ 	lw	$s1,0x1c($s2)
/*  f022444:	52200008 */ 	beqzl	$s1,.L0f022468
/*  f022448:	8fbf002c */ 	lw	$ra,0x2c($sp)
.L0f02244c:
/*  f02244c:	8e300020 */ 	lw	$s0,0x20($s1)
/*  f022450:	02202025 */ 	or	$a0,$s1,$zero
/*  f022454:	0fc1c1be */ 	jal	func0f0706f8
/*  f022458:	02602825 */ 	or	$a1,$s3,$zero
/*  f02245c:	1600fffb */ 	bnez	$s0,.L0f02244c
/*  f022460:	02008825 */ 	or	$s1,$s0,$zero
/*  f022464:	8fbf002c */ 	lw	$ra,0x2c($sp)
.L0f022468:
/*  f022468:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f02246c:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f022470:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f022474:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f022478:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f02247c:	03e00008 */ 	jr	$ra
/*  f022480:	27bd0118 */ 	addiu	$sp,$sp,0x118
);

void chrCloak(struct chrdata *chr, bool value)
{
	if (!chrIsDead(chr)) {
		chr->hidden |= CHRHFLAG_CLOAKED;

		if (value) {
			func0f0939f8(0, chr->prop, SFX_CLOAK_ON, -1, -1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);
		}
	}
}

void chrUncloak(struct chrdata *chr, bool value)
{
	if (chr->hidden & CHRHFLAG_CLOAKED) {
		chr->hidden &= ~CHRHFLAG_CLOAKED;

		if (value) {
			func0f0939f8(0, chr->prop, SFX_CLOAK_OFF, -1, -1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);
		}

#if PIRACYCHECKS
		{
			u32 checksum = 0;
			u32 *i = (u32 *)&propobjHandlePickupByAibot;
			u32 *end = (u32 *)&func0f190be4;

			while (i < end) {
				checksum += ~*i;
				i++;
			}

			if (checksum != CHECKSUM_PLACEHOLDER) {
				((u32 *)&func0002a324)[-2] = 0;
			}
		}
#endif
	}
}

void chrUncloakTemporarily(struct chrdata *chr)
{
	chrUncloak(chr, true);
	chr->cloakpause = PALDOWN(120);
}

void chrUpdateCloak(struct chrdata *chr)
{
	s32 qty;
	s32 ammotype;
	u32 prevplayernum;
	f32 fVar14;
	s32 fadefrac;

	// Decrement cloakpause
	if (chr->cloakpause > 0) {
		chr->cloakpause -= g_Vars.lvupdate240_60;

		if (chr->cloakpause < 1) {
			chr->cloakpause = 0;
		}
	}

	// Handle ammo decrease and determine if cloak is still enabled
	if (chr->aibot) {
		if (chr->aibot->cloakdeviceenabled) {
			qty = chr->aibot->ammoheld[AMMOTYPE_CLOAK];

			if (qty > 0 && !chrIsDead(chr)) {
				if (chr->hidden & CHRHFLAG_CLOAKED) {
					qty -= g_Vars.lvupdate240_60;

					if (qty <= 0) {
						qty = 0;
					}

					chr->aibot->ammoheld[AMMOTYPE_CLOAK] = qty;
				}
			} else {
				chr->aibot->cloakdeviceenabled = false;
			}
		} else if (chr->aibot->rcp120cloakenabled) {
			if (chr->aibot->weaponnum == WEAPON_RCP120
					&& !chrIsDead(chr)
					&& aibotGetAmmoQuantityByWeapon(chr->aibot, WEAPON_RCP120, 0, 1) > 0) {
				if (chr->hidden & CHRHFLAG_CLOAKED) {
					chr->aibot->unk2c4 += (PAL ? g_Vars.lvupdate240freal : g_Vars.lvupdate240f) * 0.4f;

					if (chr->aibot->unk2c4 >= 1) {
						qty = chr->aibot->unk2c4;
						chr->aibot->unk2c4 -= qty;

						if (chr->aibot->loadedammo[0] > 0) {
							chr->aibot->loadedammo[0] -= qty;

							if (chr->aibot->loadedammo[0] <= 0) {
								chr->aibot->loadedammo[0] = 0;
							}
						} else {
							ammotype = weaponGetAmmoTypeByFunction(WEAPON_RCP120, 0);

							if (chr->aibot->ammoheld[ammotype] > 0) {
								chr->aibot->ammoheld[ammotype] -= qty;

								if (chr->aibot->ammoheld[ammotype] <= 0) {
									chr->aibot->ammoheld[ammotype] = 0;
								}
							}
						}
					}
				}
			} else {
				chr->aibot->rcp120cloakenabled = false;
			}
		}

		if (chr->aibot->cloakdeviceenabled || chr->aibot->rcp120cloakenabled) {
			if ((chr->hidden & CHRHFLAG_CLOAKED) == 0) {
				if (chr->cloakpause < 1) {
					chrCloak(chr, true);
				}
			}
		} else if (chr->hidden & CHRHFLAG_CLOAKED) {
			chrUncloak(chr, true);
		}
	} else if (chr->prop->type == PROPTYPE_PLAYER) {
		prevplayernum = g_Vars.currentplayernum;
		setCurrentPlayerNum(propGetPlayerNum(chr->prop));

		if (g_Vars.currentplayer->devicesactive & DEVICE_CLOAKDEVICE) {
			// Cloak is active - but may or may not be in effect due to recent shooting
			s32 qty = bgunGetAmmoCountWithCheck(AMMOTYPE_CLOAK);

			if (qty > 0) {
				if (chr->hidden & CHRHFLAG_CLOAKED) {
					// Cloak is effective
					qty -= g_Vars.lvupdate240_60;

					if (qty < 1) {
						qty = 0;
					}

					bgunSetAmmoQuantity(AMMOTYPE_CLOAK, qty);
				}
			} else {
				// Out of cloak ammo - turn off cloak
				g_Vars.currentplayer->devicesactive &= ~DEVICE_CLOAKDEVICE;
			}
		}

		// If cloak is enabled via cloaking device or via RCP120
		if ((g_Vars.currentplayer->devicesactive & DEVICE_CLOAKDEVICE)
				|| (g_Vars.currentplayer->gunctrl.weaponnum == WEAPON_RCP120
					&& (g_Vars.currentplayer->devicesactive & DEVICE_CLOAKRCP120))) {
			if ((chr->hidden & CHRHFLAG_CLOAKED) == 0 && chr->cloakpause < 1) {
				chrCloak(chr, true);
			}
		} else {
			if ((g_Vars.currentplayer->devicesactive & DEVICE_CLOAKDEVICE) == false
					&& (chr->hidden & CHRHFLAG_CLOAKED)) {
				chrUncloak(chr, true);
			}
		}

		setCurrentPlayerNum(prevplayernum);
	}

	// Update cloakfade
	if (chr->hidden & CHRHFLAG_CLOAKED) {
		if (chr->cloakfadefinished == false) {
			fadefrac = chr->cloakfadefrac + (g_Vars.lvupdate240 * 5) / 8;

			if (fadefrac >= 128) {
				chr->cloakfadefinished = true;
				chr->cloakfadefrac = 0;
			} else {
				chr->cloakfadefrac = fadefrac;
			}
		} else {
			s32 tmp = chr->cloakfadefrac + g_Vars.lvupdate240_60;
			chr->cloakfadefrac = tmp % 127;
		}
	} else {
		if (chr->cloakfadefinished == true) {
			chr->cloakfadefinished = false;

			fVar14 = 1.0f - cosf((chr->cloakfadefrac / 127.0f + chr->cloakfadefrac / 127.0f) * M_PI);
			chr->cloakfadefrac = (254 - (s32)(fVar14 * 20.0f * 0.5f)) / 2;
		}

		if (chr->cloakfadefrac > 0) {
			fadefrac = chr->cloakfadefrac - (g_Vars.lvupdate240 * 5) / 8;

			if (fadefrac < 0) {
				fadefrac = 0;
			}

			chr->cloakfadefrac = fadefrac;
		}
	}
}

s32 func0f022be4(struct chrdata *chr)
{
	s32 result = 255;

	if (chr->cloakfadefrac > 0 || chr->cloakfadefinished == true) {
		if (!chr->cloakfadefinished) {
			result = 255 - chr->cloakfadefrac * 2;
		} else {
			f32 fVar3 = (f32)cosf((chr->cloakfadefrac / 127.0f + chr->cloakfadefrac / 127.0f) * M_PI);
			result = (1.0f - fVar3) * 20.0f * 0.5f;
		}

		if (result == 0) {
			result = 1;
		}
	}

	return result;
}

void chrSetPoisoned(struct chrdata *chr, struct prop *poisonprop)
{
	if (chr->actiontype != ACT_DEAD
			&& chr->actiontype != ACT_DIE
			&& chr->prop->type == PROPTYPE_PLAYER) {
		// This was probably used in a debug print
		propGetPlayerNum(chr->prop);
	}

	if (g_Vars.normmplayerisrunning) {
		chr->poisonprop = poisonprop;
		chr->poisoncounter += PALDOWN(3360);
	} else if (chr->poisoncounter == 0) {
		chr->poisoncounter = PALDOWN(1680);
		chr->poisonprop = poisonprop;
	}
}

void chrTickPoisoned(struct chrdata *chr)
{
	if (chr->poisoncounter > 0) {
		struct coord coord = {0, 0, 0};

		struct gset gset = { WEAPON_COMBATKNIFE, 0, 0, FUNC_POISON };

		if (chr->actiontype == ACT_DEAD || chr->actiontype == ACT_DIE) {
			// Dying chr
			if (!g_Vars.normmplayerisrunning) {
				chr->poisoncounter = 0;
			} else {
				if (chr->poisoncounter > PALDOWN(3600)) {
					chr->poisoncounter = PALDOWN(3600);
				}

				if (g_MpSetup.options & MPOPTION_ONEHITKILLS) {
					chr->poisoncounter = 0;
				}
			}
		} else if (chr->prop->type == PROPTYPE_PLAYER
				&& g_Vars.players[propGetPlayerNum(chr->prop)]->bondhealth < 0.001f) {
			// Player who's alive but on almost zero health
			if (g_Vars.normmplayerisrunning) {
				if (chr->poisoncounter > PALDOWN(3600)) {
					chr->poisoncounter = PALDOWN(3600);
				}

				if (g_MpSetup.options & MPOPTION_ONEHITKILLS) {
					chr->poisoncounter = 0;
				}
			}
		} else {
			// Alive chr
			chr->poisoncounter -= g_Vars.lvupdate240;

			if (chr->poisoncounter <= 0) {
				if (!g_Vars.normmplayerisrunning) {
					chrDamageByMisc(chr, 100, &coord, &gset, chr->poisonprop);
					chrFlinchHead(chr, M_PI);
				}

				chr->poisoncounter = 0;
			} else if (chr->poisoncounter < PALDOWN(1680)) {
				chr->blurdrugamount += g_Vars.lvupdate240 * 10;
			}

			if (g_Vars.normmplayerisrunning) {
				if (chr->poisoncounter / PALDOWN(720) != (chr->poisoncounter + g_Vars.lvupdate240) / PALDOWN(720)) {
					chrDamageByMisc(chr, 1.3f, &coord, &gset, chr->poisonprop);
				}
			}
		}
	}
}

u32 var800629e8 = 0x3f800000;
u32 var800629ec = 0x00000000;
u32 var800629f0 = 0x00000000;
u32 var800629f4 = 0x00000000;
u32 var800629f8 = 0x00000000;
u32 var800629fc = 0x00000000;
u32 var80062a00 = 0x00000001;
u32 var80062a04 = 0x00000003;
u32 var80062a08 = 0x00000000;
u32 var80062a0c = 0x00000000;
u32 var80062a10 = 0x00000000;
u32 var80062a14 = 0x00000000;
u32 var80062a18 = 0x00000000;
u32 var80062a1c = 0x00000000;
u32 var80062a20 = 0x00000000;
u32 var80062a24 = 0x00000000;
u32 var80062a28 = 0x00000000;
u32 var80062a2c = 0x00000000;
u32 var80062a30 = 0x00000000;
u32 var80062a34 = 0x00000000;
u32 var80062a38 = 0x00000000;
u32 var80062a3c = 0x00000000;
u32 var80062a40 = 0x00000000;
u32 var80062a44 = 0x00000000;
u8 var80062a48[] = { 64, 10, 10 };

bool chrTickBeams(struct prop *prop)
{
	struct chrdata *chr = prop->chr;

	if (chr->fireslots[0] >= 0) {
		beamTick(&g_Fireslots[chr->fireslots[0]].beam);
	}

	if (chr->fireslots[1] >= 0) {
		beamTick(&g_Fireslots[chr->fireslots[1]].beam);
	}

	if (chr->aibot && chr->aibot->unk058 > 0) {
		if (chr->aibot->unk058 > g_Vars.lvupdate240_60) {
			chr->aibot->unk058 -= g_Vars.lvupdate240_60;
		} else {
			chr->aibot->unk058 = 0;
		}
	}

	return false;
}

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0f023098
.late_rodata
glabel var7f1a99d0pf
.word 0x40c907a9
glabel var7f1a99d4pf
.word 0x3e333333
glabel var7f1a99d8pf
.word 0x3e333333
glabel var7f1a99dcpf
.word 0x4a742400
glabel var7f1a99e0pf
.word 0x48ef4200
glabel var7f1a99e4pf
.word 0x4a742400
glabel var7f1a99e8pf
.word 0x48ef4200
glabel var7f1a99ecpf
.word 0x41aa6666
.text
/*  f0231d4:	27bdfdb0 */ 	addiu	$sp,$sp,-592
/*  f0231d8:	3c0f8006 */ 	lui	$t7,0x8006
/*  f0231dc:	25ef26dc */ 	addiu	$t7,$t7,0x26dc
/*  f0231e0:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f0231e4:	afb00020 */ 	sw	$s0,0x20($sp)
/*  f0231e8:	afa40250 */ 	sw	$a0,0x250($sp)
/*  f0231ec:	25e8003c */ 	addiu	$t0,$t7,0x3c
/*  f0231f0:	27ae0210 */ 	addiu	$t6,$sp,0x210
.PF0f0231f4:
/*  f0231f4:	8de10000 */ 	lw	$at,0x0($t7)
/*  f0231f8:	25ef000c */ 	addiu	$t7,$t7,0xc
/*  f0231fc:	25ce000c */ 	addiu	$t6,$t6,0xc
/*  f023200:	adc1fff4 */ 	sw	$at,-0xc($t6)
/*  f023204:	8de1fff8 */ 	lw	$at,-0x8($t7)
/*  f023208:	adc1fff8 */ 	sw	$at,-0x8($t6)
/*  f02320c:	8de1fffc */ 	lw	$at,-0x4($t7)
/*  f023210:	15e8fff8 */ 	bne	$t7,$t0,.PF0f0231f4
/*  f023214:	adc1fffc */ 	sw	$at,-0x4($t6)
/*  f023218:	8de10000 */ 	lw	$at,0x0($t7)
/*  f02321c:	3c0c800a */ 	lui	$t4,0x800a
/*  f023220:	240b0001 */ 	li	$t3,0x1
/*  f023224:	adc10000 */ 	sw	$at,0x0($t6)
/*  f023228:	8fa90250 */ 	lw	$t1,0x250($sp)
/*  f02322c:	8d8ca544 */ 	lw	$t4,-0x5abc($t4)
/*  f023230:	24080001 */ 	li	$t0,0x1
/*  f023234:	8d300004 */ 	lw	$s0,0x4($t1)
/*  f023238:	8e0a0020 */ 	lw	$t2,0x20($s0)
/*  f02323c:	afab0200 */ 	sw	$t3,0x200($sp)
/*  f023240:	afa001f0 */ 	sw	$zero,0x1f0($sp)
/*  f023244:	afac01fc */ 	sw	$t4,0x1fc($sp)
/*  f023248:	12000004 */ 	beqz	$s0,.PF0f02325c
/*  f02324c:	afaa0208 */ 	sw	$t2,0x208($sp)
/*  f023250:	920d02fe */ 	lbu	$t5,0x2fe($s0)
/*  f023254:	10000002 */ 	b	.PF0f023260
/*  f023258:	afad01ec */ 	sw	$t5,0x1ec($sp)
.PF0f02325c:
/*  f02325c:	afa001ec */ 	sw	$zero,0x1ec($sp)
.PF0f023260:
/*  f023260:	8fb90250 */ 	lw	$t9,0x250($sp)
/*  f023264:	3c0c800a */ 	lui	$t4,0x800a
/*  f023268:	93220001 */ 	lbu	$v0,0x1($t9)
/*  f02326c:	30580008 */ 	andi	$t8,$v0,0x8
/*  f023270:	13000003 */ 	beqz	$t8,.PF0f023280
/*  f023274:	304ffff7 */ 	andi	$t7,$v0,0xfff7
/*  f023278:	afa801f0 */ 	sw	$t0,0x1f0($sp)
/*  f02327c:	a32f0001 */ 	sb	$t7,0x1($t9)
.PF0f023280:
/*  f023280:	8fae01f0 */ 	lw	$t6,0x1f0($sp)
/*  f023284:	51c000b7 */ 	beqzl	$t6,.PF0f023564
/*  f023288:	8fab01ec */ 	lw	$t3,0x1ec($sp)
/*  f02328c:	92020291 */ 	lbu	$v0,0x291($s0)
/*  f023290:	18400007 */ 	blez	$v0,.PF0f0232b0
/*  f023294:	00000000 */ 	nop
/*  f023298:	8e090014 */ 	lw	$t1,0x14($s0)
/*  f02329c:	244bffff */ 	addiu	$t3,$v0,-1
/*  f0232a0:	312a0010 */ 	andi	$t2,$t1,0x10
/*  f0232a4:	15400002 */ 	bnez	$t2,.PF0f0232b0
/*  f0232a8:	00000000 */ 	nop
/*  f0232ac:	a20b0291 */ 	sb	$t3,0x291($s0)
.PF0f0232b0:
/*  f0232b0:	8d8ca9dc */ 	lw	$t4,-0x5624($t4)
/*  f0232b4:	51800006 */ 	beqzl	$t4,.PF0f0232d0
/*  f0232b8:	860d02d8 */ 	lh	$t5,0x2d8($s0)
/*  f0232bc:	44802000 */ 	mtc1	$zero,$f4
/*  f0232c0:	a20002e0 */ 	sb	$zero,0x2e0($s0)
/*  f0232c4:	10000057 */ 	b	.PF0f023424
/*  f0232c8:	e60402dc */ 	swc1	$f4,0x2dc($s0)
/*  f0232cc:	860d02d8 */ 	lh	$t5,0x2d8($s0)
.PF0f0232d0:
/*  f0232d0:	29a10342 */ 	slti	$at,$t5,0x342
/*  f0232d4:	54200022 */ 	bnezl	$at,.PF0f023360
/*  f0232d8:	c60002dc */ 	lwc1	$f0,0x2dc($s0)
/*  f0232dc:	82180007 */ 	lb	$t8,0x7($s0)
/*  f0232e0:	2401001f */ 	li	$at,0x1f
/*  f0232e4:	3c0f800a */ 	lui	$t7,0x800a
/*  f0232e8:	5301001d */ 	beql	$t8,$at,.PF0f023360
/*  f0232ec:	c60002dc */ 	lwc1	$f0,0x2dc($s0)
/*  f0232f0:	8defa544 */ 	lw	$t7,-0x5abc($t7)
/*  f0232f4:	920802e0 */ 	lbu	$t0,0x2e0($s0)
/*  f0232f8:	3c014f80 */ 	lui	$at,0x4f80
/*  f0232fc:	000fc843 */ 	sra	$t9,$t7,0x1
/*  f023300:	01197021 */ 	addu	$t6,$t0,$t9
/*  f023304:	31c900ff */ 	andi	$t1,$t6,0xff
/*  f023308:	44893000 */ 	mtc1	$t1,$f6
/*  f02330c:	a20e02e0 */ 	sb	$t6,0x2e0($s0)
/*  f023310:	05210004 */ 	bgez	$t1,.PF0f023324
/*  f023314:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f023318:	44815000 */ 	mtc1	$at,$f10
/*  f02331c:	00000000 */ 	nop
/*  f023320:	460a4200 */ 	add.s	$f8,$f8,$f10
.PF0f023324:
/*  f023324:	3c01437f */ 	lui	$at,0x437f
/*  f023328:	44819000 */ 	mtc1	$at,$f18
/*  f02332c:	3c017f1b */ 	lui	$at,0x7f1b
/*  f023330:	c42699d0 */ 	lwc1	$f6,-0x6630($at)
/*  f023334:	46124103 */ 	div.s	$f4,$f8,$f18
/*  f023338:	46062302 */ 	mul.s	$f12,$f4,$f6
/*  f02333c:	0c006858 */ 	jal	cosf
/*  f023340:	00000000 */ 	nop
/*  f023344:	3c0141a0 */ 	lui	$at,0x41a0
/*  f023348:	44815000 */ 	mtc1	$at,$f10
/*  f02334c:	00000000 */ 	nop
/*  f023350:	460a0202 */ 	mul.s	$f8,$f0,$f10
/*  f023354:	10000033 */ 	b	.PF0f023424
/*  f023358:	e60802dc */ 	swc1	$f8,0x2dc($s0)
/*  f02335c:	c60002dc */ 	lwc1	$f0,0x2dc($s0)
.PF0f023360:
/*  f023360:	44809000 */ 	mtc1	$zero,$f18
/*  f023364:	00000000 */ 	nop
/*  f023368:	46009032 */ 	c.eq.s	$f18,$f0
/*  f02336c:	00000000 */ 	nop
/*  f023370:	4501002c */ 	bc1t	.PF0f023424
/*  f023374:	00000000 */ 	nop
/*  f023378:	44802000 */ 	mtc1	$zero,$f4
/*  f02337c:	a20002e0 */ 	sb	$zero,0x2e0($s0)
/*  f023380:	3c017f1b */ 	lui	$at,0x7f1b
/*  f023384:	4600203c */ 	c.lt.s	$f4,$f0
/*  f023388:	00000000 */ 	nop
/*  f02338c:	45020011 */ 	bc1fl	.PF0f0233d4
/*  f023390:	44804000 */ 	mtc1	$zero,$f8
/*  f023394:	c42699d4 */ 	lwc1	$f6,-0x662c($at)
/*  f023398:	3c01800a */ 	lui	$at,0x800a
/*  f02339c:	c42aa55c */ 	lwc1	$f10,-0x5aa4($at)
/*  f0233a0:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f0233a4:	44803000 */ 	mtc1	$zero,$f6
/*  f0233a8:	46080481 */ 	sub.s	$f18,$f0,$f8
/*  f0233ac:	e61202dc */ 	swc1	$f18,0x2dc($s0)
/*  f0233b0:	c60402dc */ 	lwc1	$f4,0x2dc($s0)
/*  f0233b4:	4606203c */ 	c.lt.s	$f4,$f6
/*  f0233b8:	00000000 */ 	nop
/*  f0233bc:	45000019 */ 	bc1f	.PF0f023424
/*  f0233c0:	00000000 */ 	nop
/*  f0233c4:	44805000 */ 	mtc1	$zero,$f10
/*  f0233c8:	10000016 */ 	b	.PF0f023424
/*  f0233cc:	e60a02dc */ 	swc1	$f10,0x2dc($s0)
/*  f0233d0:	44804000 */ 	mtc1	$zero,$f8
.PF0f0233d4:
/*  f0233d4:	3c017f1b */ 	lui	$at,0x7f1b
/*  f0233d8:	4608003c */ 	c.lt.s	$f0,$f8
/*  f0233dc:	00000000 */ 	nop
/*  f0233e0:	45000010 */ 	bc1f	.PF0f023424
/*  f0233e4:	00000000 */ 	nop
/*  f0233e8:	c43299d8 */ 	lwc1	$f18,-0x6628($at)
/*  f0233ec:	3c01800a */ 	lui	$at,0x800a
/*  f0233f0:	c424a55c */ 	lwc1	$f4,-0x5aa4($at)
/*  f0233f4:	44804000 */ 	mtc1	$zero,$f8
/*  f0233f8:	46049182 */ 	mul.s	$f6,$f18,$f4
/*  f0233fc:	46060280 */ 	add.s	$f10,$f0,$f6
/*  f023400:	e60a02dc */ 	swc1	$f10,0x2dc($s0)
/*  f023404:	c61202dc */ 	lwc1	$f18,0x2dc($s0)
/*  f023408:	4612403c */ 	c.lt.s	$f8,$f18
/*  f02340c:	00000000 */ 	nop
/*  f023410:	45000004 */ 	bc1f	.PF0f023424
/*  f023414:	00000000 */ 	nop
/*  f023418:	44802000 */ 	mtc1	$zero,$f4
/*  f02341c:	00000000 */ 	nop
/*  f023420:	e60402dc */ 	swc1	$f4,0x2dc($s0)
.PF0f023424:
/*  f023424:	0fc089d8 */ 	jal	chrUpdateCloak
/*  f023428:	02002025 */ 	move	$a0,$s0
/*  f02342c:	0fc08ba7 */ 	jal	chrTickPoisoned
/*  f023430:	02002025 */ 	move	$a0,$s0
/*  f023434:	8e020018 */ 	lw	$v0,0x18($s0)
/*  f023438:	3c0c8006 */ 	lui	$t4,0x8006
/*  f02343c:	304a0400 */ 	andi	$t2,$v0,0x400
/*  f023440:	11400003 */ 	beqz	$t2,.PF0f023450
/*  f023444:	00025b40 */ 	sll	$t3,$v0,0xd
/*  f023448:	05630039 */ 	bgezl	$t3,.PF0f023530
/*  f02344c:	8e020014 */ 	lw	$v0,0x14($s0)
.PF0f023450:
/*  f023450:	8d8c264c */ 	lw	$t4,0x264c($t4)
/*  f023454:	3c048006 */ 	lui	$a0,0x8006
/*  f023458:	11800022 */ 	beqz	$t4,.PF0f0234e4
/*  f02345c:	00000000 */ 	nop
/*  f023460:	0c008c25 */ 	jal	func00023794
/*  f023464:	84842652 */ 	lh	$a0,0x2652($a0)
/*  f023468:	10400025 */ 	beqz	$v0,.PF0f023500
/*  f02346c:	00000000 */ 	nop
/*  f023470:	0c0073c3 */ 	jal	modelGetAnimNum
/*  f023474:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023478:	3c038006 */ 	lui	$v1,0x8006
/*  f02347c:	8c632650 */ 	lw	$v1,0x2650($v1)
/*  f023480:	5443000b */ 	bnel	$v0,$v1,.PF0f0234b0
/*  f023484:	44800000 */ 	mtc1	$zero,$f0
/*  f023488:	0c0073c3 */ 	jal	modelGetAnimNum
/*  f02348c:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023490:	00022400 */ 	sll	$a0,$v0,0x10
/*  f023494:	00046c03 */ 	sra	$t5,$a0,0x10
/*  f023498:	0c008c25 */ 	jal	func00023794
/*  f02349c:	01a02025 */ 	move	$a0,$t5
/*  f0234a0:	14400017 */ 	bnez	$v0,.PF0f023500
/*  f0234a4:	3c038006 */ 	lui	$v1,0x8006
/*  f0234a8:	8c632650 */ 	lw	$v1,0x2650($v1)
/*  f0234ac:	44800000 */ 	mtc1	$zero,$f0
.PF0f0234b0:
/*  f0234b0:	3c013f00 */ 	lui	$at,0x3f00
/*  f0234b4:	44813000 */ 	mtc1	$at,$f6
/*  f0234b8:	00032c00 */ 	sll	$a1,$v1,0x10
/*  f0234bc:	0005c403 */ 	sra	$t8,$a1,0x10
/*  f0234c0:	44070000 */ 	mfc1	$a3,$f0
/*  f0234c4:	03002825 */ 	move	$a1,$t8
/*  f0234c8:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0234cc:	00003025 */ 	move	$a2,$zero
/*  f0234d0:	e7a00014 */ 	swc1	$f0,0x14($sp)
/*  f0234d4:	0c0076a7 */ 	jal	modelSetAnimation
/*  f0234d8:	e7a60010 */ 	swc1	$f6,0x10($sp)
/*  f0234dc:	10000008 */ 	b	.PF0f023500
/*  f0234e0:	00000000 */ 	nop
.PF0f0234e4:
/*  f0234e4:	0fc11f8d */ 	jal	chrTick
/*  f0234e8:	02002025 */ 	move	$a0,$s0
/*  f0234ec:	8e0f0020 */ 	lw	$t7,0x20($s0)
/*  f0234f0:	15e00003 */ 	bnez	$t7,.PF0f023500
/*  f0234f4:	00000000 */ 	nop
/*  f0234f8:	1000044e */ 	b	.PF0f024634
/*  f0234fc:	24020001 */ 	li	$v0,0x1
.PF0f023500:
/*  f023500:	3c088006 */ 	lui	$t0,0x8006
/*  f023504:	8d082654 */ 	lw	$t0,0x2654($t0)
/*  f023508:	3c198006 */ 	lui	$t9,0x8006
/*  f02350c:	51000008 */ 	beqzl	$t0,.PF0f023530
/*  f023510:	8e020014 */ 	lw	$v0,0x14($s0)
/*  f023514:	8f392658 */ 	lw	$t9,0x2658($t9)
/*  f023518:	afa001fc */ 	sw	$zero,0x1fc($sp)
/*  f02351c:	240e0001 */ 	li	$t6,0x1
/*  f023520:	53200003 */ 	beqzl	$t9,.PF0f023530
/*  f023524:	8e020014 */ 	lw	$v0,0x14($s0)
/*  f023528:	afae01fc */ 	sw	$t6,0x1fc($sp)
/*  f02352c:	8e020014 */ 	lw	$v0,0x14($s0)
.PF0f023530:
/*  f023530:	30490020 */ 	andi	$t1,$v0,0x20
/*  f023534:	1120000a */ 	beqz	$t1,.PF0f023560
/*  f023538:	304a0001 */ 	andi	$t2,$v0,0x1
/*  f02353c:	11400003 */ 	beqz	$t2,.PF0f02354c
/*  f023540:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023544:	0fc1c248 */ 	jal	func0f070698
/*  f023548:	24050001 */ 	li	$a1,0x1
.PF0f02354c:
/*  f02354c:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023550:	0fc08399 */ 	jal	func0f020d44
/*  f023554:	24050001 */ 	li	$a1,0x1
/*  f023558:	10000436 */ 	b	.PF0f024634
/*  f02355c:	24020001 */ 	li	$v0,0x1
.PF0f023560:
/*  f023560:	8fab01ec */ 	lw	$t3,0x1ec($sp)
.PF0f023564:
/*  f023564:	24010003 */ 	li	$at,0x3
/*  f023568:	55610026 */ 	bnel	$t3,$at,.PF0f023604
/*  f02356c:	8e020018 */ 	lw	$v0,0x18($s0)
/*  f023570:	0fc0f072 */ 	jal	chrToEyespy
/*  f023574:	02002025 */ 	move	$a0,$s0
/*  f023578:	1040001f */ 	beqz	$v0,.PF0f0235f8
/*  f02357c:	00000000 */ 	nop
/*  f023580:	904c0035 */ 	lbu	$t4,0x35($v0)
/*  f023584:	3c0d800a */ 	lui	$t5,0x800a
/*  f023588:	1180001b */ 	beqz	$t4,.PF0f0235f8
/*  f02358c:	00000000 */ 	nop
/*  f023590:	8dada794 */ 	lw	$t5,-0x586c($t5)
/*  f023594:	8db80480 */ 	lw	$t8,0x480($t5)
/*  f023598:	14580006 */ 	bne	$v0,$t8,.PF0f0235b4
/*  f02359c:	00000000 */ 	nop
/*  f0235a0:	804f0037 */ 	lb	$t7,0x37($v0)
/*  f0235a4:	11e00003 */ 	beqz	$t7,.PF0f0235b4
/*  f0235a8:	00000000 */ 	nop
/*  f0235ac:	10000009 */ 	b	.PF0f0235d4
/*  f0235b0:	00003825 */ 	move	$a3,$zero
.PF0f0235b4:
/*  f0235b4:	0c006b44 */ 	jal	func0001af80
/*  f0235b8:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0235bc:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0235c0:	44060000 */ 	mfc1	$a2,$f0
/*  f0235c4:	24070001 */ 	li	$a3,0x1
/*  f0235c8:	0fc239f6 */ 	jal	func0f08e8ac
/*  f0235cc:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f0235d0:	00403825 */ 	move	$a3,$v0
.PF0f0235d4:
/*  f0235d4:	8fb901f0 */ 	lw	$t9,0x1f0($sp)
/*  f0235d8:	02002025 */ 	move	$a0,$s0
/*  f0235dc:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0235e0:	132001c9 */ 	beqz	$t9,.PF0f023d08
/*  f0235e4:	24060001 */ 	li	$a2,0x1
/*  f0235e8:	0fc0888a */ 	jal	func0f0220ec
/*  f0235ec:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f0235f0:	100001c5 */ 	b	.PF0f023d08
/*  f0235f4:	8fa70204 */ 	lw	$a3,0x204($sp)
.PF0f0235f8:
/*  f0235f8:	100001c3 */ 	b	.PF0f023d08
/*  f0235fc:	00003825 */ 	move	$a3,$zero
/*  f023600:	8e020018 */ 	lw	$v0,0x18($s0)
.PF0f023604:
/*  f023604:	304e0400 */ 	andi	$t6,$v0,0x400
/*  f023608:	11c00003 */ 	beqz	$t6,.PF0f023618
/*  f02360c:	00024a00 */ 	sll	$t1,$v0,0x8
/*  f023610:	100001bd */ 	b	.PF0f023d08
/*  f023614:	00003825 */ 	move	$a3,$zero
.PF0f023618:
/*  f023618:	05200017 */ 	bltz	$t1,.PF0f023678
/*  f02361c:	8faa0250 */ 	lw	$t2,0x250($sp)
/*  f023620:	914b0000 */ 	lbu	$t3,0x0($t2)
/*  f023624:	24010006 */ 	li	$at,0x6
/*  f023628:	55610068 */ 	bnel	$t3,$at,.PF0f0237cc
/*  f02362c:	82030007 */ 	lb	$v1,0x7($s0)
/*  f023630:	0fc4a513 */ 	jal	propGetPlayerNum
/*  f023634:	01402025 */ 	move	$a0,$t2
/*  f023638:	00026080 */ 	sll	$t4,$v0,0x2
/*  f02363c:	3c03800a */ 	lui	$v1,0x800a
/*  f023640:	006c1821 */ 	addu	$v1,$v1,$t4
/*  f023644:	3c0d800a */ 	lui	$t5,0x800a
/*  f023648:	8dada794 */ 	lw	$t5,-0x586c($t5)
/*  f02364c:	8c63a574 */ 	lw	$v1,-0x5a8c($v1)
/*  f023650:	546d005e */ 	bnel	$v1,$t5,.PF0f0237cc
/*  f023654:	82030007 */ 	lb	$v1,0x7($s0)
/*  f023658:	8c780000 */ 	lw	$t8,0x0($v1)
/*  f02365c:	24010001 */ 	li	$at,0x1
/*  f023660:	5701005a */ 	bnel	$t8,$at,.PF0f0237cc
/*  f023664:	82030007 */ 	lb	$v1,0x7($s0)
/*  f023668:	946f0010 */ 	lhu	$t7,0x10($v1)
/*  f02366c:	24010002 */ 	li	$at,0x2
/*  f023670:	51e10056 */ 	beql	$t7,$at,.PF0f0237cc
/*  f023674:	82030007 */ 	lb	$v1,0x7($s0)
.PF0f023678:
/*  f023678:	8fa801f0 */ 	lw	$t0,0x1f0($sp)
/*  f02367c:	00003825 */ 	move	$a3,$zero
/*  f023680:	8fb90208 */ 	lw	$t9,0x208($sp)
/*  f023684:	5100001b */ 	beqzl	$t0,.PF0f0236f4
/*  f023688:	8e030020 */ 	lw	$v1,0x20($s0)
/*  f02368c:	8f2e0020 */ 	lw	$t6,0x20($t9)
/*  f023690:	24010003 */ 	li	$at,0x3
/*  f023694:	02002025 */ 	move	$a0,$s0
/*  f023698:	a1c0000b */ 	sb	$zero,0xb($t6)
/*  f02369c:	82090007 */ 	lb	$t1,0x7($s0)
/*  f0236a0:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0236a4:	24060001 */ 	li	$a2,0x1
/*  f0236a8:	1521000e */ 	bne	$t1,$at,.PF0f0236e4
/*  f0236ac:	00000000 */ 	nop
/*  f0236b0:	8e0b002c */ 	lw	$t3,0x2c($s0)
/*  f0236b4:	1560000b */ 	bnez	$t3,.PF0f0236e4
/*  f0236b8:	00000000 */ 	nop
/*  f0236bc:	8e0a003c */ 	lw	$t2,0x3c($s0)
/*  f0236c0:	11400008 */ 	beqz	$t2,.PF0f0236e4
/*  f0236c4:	00000000 */ 	nop
/*  f0236c8:	02002025 */ 	move	$a0,$s0
/*  f0236cc:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0236d0:	00003025 */ 	move	$a2,$zero
/*  f0236d4:	0fc0888a */ 	jal	func0f0220ec
/*  f0236d8:	afa001a0 */ 	sw	$zero,0x1a0($sp)
/*  f0236dc:	10000004 */ 	b	.PF0f0236f0
/*  f0236e0:	8fa701a0 */ 	lw	$a3,0x1a0($sp)
.PF0f0236e4:
/*  f0236e4:	0fc0888a */ 	jal	func0f0220ec
/*  f0236e8:	afa701a0 */ 	sw	$a3,0x1a0($sp)
/*  f0236ec:	8fa701a0 */ 	lw	$a3,0x1a0($sp)
.PF0f0236f0:
/*  f0236f0:	8e030020 */ 	lw	$v1,0x20($s0)
.PF0f0236f4:
/*  f0236f4:	1060002c */ 	beqz	$v1,.PF0f0237a8
/*  f0236f8:	00000000 */ 	nop
/*  f0236fc:	8c620020 */ 	lw	$v0,0x20($v1)
/*  f023700:	10400029 */ 	beqz	$v0,.PF0f0237a8
/*  f023704:	00000000 */ 	nop
/*  f023708:	84440000 */ 	lh	$a0,0x0($v0)
/*  f02370c:	3c0c8006 */ 	lui	$t4,0x8006
/*  f023710:	8d8cecbc */ 	lw	$t4,-0x1344($t4)
/*  f023714:	00046880 */ 	sll	$t5,$a0,0x2
/*  f023718:	01a46823 */ 	subu	$t5,$t5,$a0
/*  f02371c:	000d6880 */ 	sll	$t5,$t5,0x2
/*  f023720:	018dc021 */ 	addu	$t8,$t4,$t5
/*  f023724:	930f000b */ 	lbu	$t7,0xb($t8)
/*  f023728:	31e80004 */ 	andi	$t0,$t7,0x4
/*  f02372c:	1100001e */ 	beqz	$t0,.PF0f0237a8
/*  f023730:	00000000 */ 	nop
/*  f023734:	0c008d8e */ 	jal	func00023d38
/*  f023738:	00000000 */ 	nop
/*  f02373c:	8e190020 */ 	lw	$t9,0x20($s0)
/*  f023740:	8f220020 */ 	lw	$v0,0x20($t9)
/*  f023744:	84440000 */ 	lh	$a0,0x0($v0)
/*  f023748:	0c008c53 */ 	jal	func0002384c
/*  f02374c:	84450014 */ 	lh	$a1,0x14($v0)
/*  f023750:	28440000 */ 	slti	$a0,$v0,0x0
/*  f023754:	54800014 */ 	bnezl	$a0,.PF0f0237a8
/*  f023758:	00803825 */ 	move	$a3,$a0
/*  f02375c:	8e0e0020 */ 	lw	$t6,0x20($s0)
/*  f023760:	8dc20020 */ 	lw	$v0,0x20($t6)
/*  f023764:	84440000 */ 	lh	$a0,0x0($v0)
/*  f023768:	0c008c53 */ 	jal	func0002384c
/*  f02376c:	84450016 */ 	lh	$a1,0x16($v0)
/*  f023770:	28440000 */ 	slti	$a0,$v0,0x0
/*  f023774:	5080000c */ 	beqzl	$a0,.PF0f0237a8
/*  f023778:	00803825 */ 	move	$a3,$a0
/*  f02377c:	8e090020 */ 	lw	$t1,0x20($s0)
/*  f023780:	44805000 */ 	mtc1	$zero,$f10
/*  f023784:	00002025 */ 	move	$a0,$zero
/*  f023788:	8d2b0020 */ 	lw	$t3,0x20($t1)
/*  f02378c:	c5680010 */ 	lwc1	$f8,0x10($t3)
/*  f023790:	46085032 */ 	c.eq.s	$f10,$f8
/*  f023794:	00000000 */ 	nop
/*  f023798:	45030003 */ 	bc1tl	.PF0f0237a8
/*  f02379c:	00803825 */ 	move	$a3,$a0
/*  f0237a0:	24040001 */ 	li	$a0,0x1
/*  f0237a4:	00803825 */ 	move	$a3,$a0
.PF0f0237a8:
/*  f0237a8:	10e00003 */ 	beqz	$a3,.PF0f0237b8
/*  f0237ac:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0237b0:	10000155 */ 	b	.PF0f023d08
/*  f0237b4:	00003825 */ 	move	$a3,$zero
.PF0f0237b8:
/*  f0237b8:	0fc23a44 */ 	jal	posIsInDrawDistance
/*  f0237bc:	24840008 */ 	addiu	$a0,$a0,0x8
/*  f0237c0:	10000151 */ 	b	.PF0f023d08
/*  f0237c4:	00403825 */ 	move	$a3,$v0
/*  f0237c8:	82030007 */ 	lb	$v1,0x7($s0)
.PF0f0237cc:
/*  f0237cc:	2401000e */ 	li	$at,0xe
/*  f0237d0:	10610002 */ 	beq	$v1,$at,.PF0f0237dc
/*  f0237d4:	2401000f */ 	li	$at,0xf
/*  f0237d8:	14610046 */ 	bne	$v1,$at,.PF0f0238f4
.PF0f0237dc:
/*  f0237dc:	2401000e */ 	li	$at,0xe
/*  f0237e0:	54610005 */ 	bnel	$v1,$at,.PF0f0237f8
/*  f0237e4:	2401000f */ 	li	$at,0xf
/*  f0237e8:	820a0038 */ 	lb	$t2,0x38($s0)
/*  f0237ec:	24010006 */ 	li	$at,0x6
/*  f0237f0:	11410007 */ 	beq	$t2,$at,.PF0f023810
/*  f0237f4:	2401000f */ 	li	$at,0xf
.PF0f0237f8:
/*  f0237f8:	14610018 */ 	bne	$v1,$at,.PF0f02385c
/*  f0237fc:	8fa801f0 */ 	lw	$t0,0x1f0($sp)
/*  f023800:	820c0068 */ 	lb	$t4,0x68($s0)
/*  f023804:	24010006 */ 	li	$at,0x6
/*  f023808:	15810014 */ 	bne	$t4,$at,.PF0f02385c
/*  f02380c:	00000000 */ 	nop
.PF0f023810:
/*  f023810:	0c006b44 */ 	jal	func0001af80
/*  f023814:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023818:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f02381c:	44060000 */ 	mfc1	$a2,$f0
/*  f023820:	24070001 */ 	li	$a3,0x1
/*  f023824:	0fc239f6 */ 	jal	func0f08e8ac
/*  f023828:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f02382c:	10400136 */ 	beqz	$v0,.PF0f023d08
/*  f023830:	00403825 */ 	move	$a3,$v0
/*  f023834:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023838:	260500c8 */ 	addiu	$a1,$s0,0xc8
/*  f02383c:	8c8f0020 */ 	lw	$t7,0x20($a0)
/*  f023840:	a1e0000b */ 	sb	$zero,0xb($t7)
/*  f023844:	0c006aa7 */ 	jal	modelGetRootPosition
/*  f023848:	afa20204 */ 	sw	$v0,0x204($sp)
/*  f02384c:	0c006c56 */ 	jal	func0001b3bc
/*  f023850:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023854:	1000012c */ 	b	.PF0f023d08
/*  f023858:	8fa70204 */ 	lw	$a3,0x204($sp)
.PF0f02385c:
/*  f02385c:	11000004 */ 	beqz	$t0,.PF0f023870
/*  f023860:	02002025 */ 	move	$a0,$s0
/*  f023864:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023868:	0fc0888a */ 	jal	func0f0220ec
/*  f02386c:	24060001 */ 	li	$a2,0x1
.PF0f023870:
/*  f023870:	0c006b44 */ 	jal	func0001af80
/*  f023874:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023878:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f02387c:	44060000 */ 	mfc1	$a2,$f0
/*  f023880:	24070001 */ 	li	$a3,0x1
/*  f023884:	0fc239f6 */ 	jal	func0f08e8ac
/*  f023888:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f02388c:	1040000e */ 	beqz	$v0,.PF0f0238c8
/*  f023890:	00403825 */ 	move	$a3,$v0
/*  f023894:	82030007 */ 	lb	$v1,0x7($s0)
/*  f023898:	2401000e */ 	li	$at,0xe
/*  f02389c:	3c0e800a */ 	lui	$t6,0x800a
/*  f0238a0:	54610005 */ 	bnel	$v1,$at,.PF0f0238b8
/*  f0238a4:	2401000f */ 	li	$at,0xf
/*  f0238a8:	8dcea518 */ 	lw	$t6,-0x5ae8($t6)
/*  f0238ac:	10000006 */ 	b	.PF0f0238c8
/*  f0238b0:	ae0e0078 */ 	sw	$t6,0x78($s0)
/*  f0238b4:	2401000f */ 	li	$at,0xf
.PF0f0238b8:
/*  f0238b8:	14610003 */ 	bne	$v1,$at,.PF0f0238c8
/*  f0238bc:	3c09800a */ 	lui	$t1,0x800a
/*  f0238c0:	8d29a518 */ 	lw	$t1,-0x5ae8($t1)
/*  f0238c4:	ae0900a8 */ 	sw	$t1,0xa8($s0)
.PF0f0238c8:
/*  f0238c8:	2c440001 */ 	sltiu	$a0,$v0,0x1
/*  f0238cc:	10800006 */ 	beqz	$a0,.PF0f0238e8
/*  f0238d0:	8fad0208 */ 	lw	$t5,0x208($sp)
/*  f0238d4:	8fab0250 */ 	lw	$t3,0x250($sp)
/*  f0238d8:	91640001 */ 	lbu	$a0,0x1($t3)
/*  f0238dc:	308a00c0 */ 	andi	$t2,$a0,0xc0
/*  f0238e0:	000a602b */ 	sltu	$t4,$zero,$t2
/*  f0238e4:	2d840001 */ 	sltiu	$a0,$t4,0x1
.PF0f0238e8:
/*  f0238e8:	8daf0020 */ 	lw	$t7,0x20($t5)
/*  f0238ec:	10000106 */ 	b	.PF0f023d08
/*  f0238f0:	a1e4000b */ 	sb	$a0,0xb($t7)
.PF0f0238f4:
/*  f0238f4:	24010003 */ 	li	$at,0x3
/*  f0238f8:	54610025 */ 	bnel	$v1,$at,.PF0f023990
/*  f0238fc:	24010001 */ 	li	$at,0x1
/*  f023900:	8e18002c */ 	lw	$t8,0x2c($s0)
/*  f023904:	57000022 */ 	bnezl	$t8,.PF0f023990
/*  f023908:	24010001 */ 	li	$at,0x1
/*  f02390c:	0c006b44 */ 	jal	func0001af80
/*  f023910:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023914:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023918:	44060000 */ 	mfc1	$a2,$f0
/*  f02391c:	24070001 */ 	li	$a3,0x1
/*  f023920:	0fc239f6 */ 	jal	func0f08e8ac
/*  f023924:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023928:	8fb901f0 */ 	lw	$t9,0x1f0($sp)
/*  f02392c:	00403825 */ 	move	$a3,$v0
/*  f023930:	8fae0208 */ 	lw	$t6,0x208($sp)
/*  f023934:	532000f5 */ 	beqzl	$t9,.PF0f023d0c
/*  f023938:	8faa01f0 */ 	lw	$t2,0x1f0($sp)
/*  f02393c:	8dc90020 */ 	lw	$t1,0x20($t6)
/*  f023940:	02002025 */ 	move	$a0,$s0
/*  f023944:	1040000b */ 	beqz	$v0,.PF0f023974
/*  f023948:	a120000b */ 	sb	$zero,0xb($t1)
/*  f02394c:	8e0b003c */ 	lw	$t3,0x3c($s0)
/*  f023950:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023954:	24060001 */ 	li	$a2,0x1
/*  f023958:	55600007 */ 	bnezl	$t3,.PF0f023978
/*  f02395c:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023960:	02002025 */ 	move	$a0,$s0
/*  f023964:	0fc0888a */ 	jal	func0f0220ec
/*  f023968:	afa20204 */ 	sw	$v0,0x204($sp)
/*  f02396c:	100000e6 */ 	b	.PF0f023d08
/*  f023970:	8fa70204 */ 	lw	$a3,0x204($sp)
.PF0f023974:
/*  f023974:	8fa501fc */ 	lw	$a1,0x1fc($sp)
.PF0f023978:
/*  f023978:	00003025 */ 	move	$a2,$zero
/*  f02397c:	0fc0888a */ 	jal	func0f0220ec
/*  f023980:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023984:	100000e0 */ 	b	.PF0f023d08
/*  f023988:	8fa70204 */ 	lw	$a3,0x204($sp)
/*  f02398c:	24010001 */ 	li	$at,0x1
.PF0f023990:
/*  f023990:	14610062 */ 	bne	$v1,$at,.PF0f023b1c
/*  f023994:	8faa0208 */ 	lw	$t2,0x208($sp)
/*  f023998:	8d4c0020 */ 	lw	$t4,0x20($t2)
/*  f02399c:	02002025 */ 	move	$a0,$s0
/*  f0239a0:	a180000b */ 	sb	$zero,0xb($t4)
/*  f0239a4:	8e0d0018 */ 	lw	$t5,0x18($s0)
/*  f0239a8:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0239ac:	31af0001 */ 	andi	$t7,$t5,0x1
/*  f0239b0:	11e0000c */ 	beqz	$t7,.PF0f0239e4
/*  f0239b4:	00000000 */ 	nop
/*  f0239b8:	0fc0888a */ 	jal	func0f0220ec
/*  f0239bc:	24060001 */ 	li	$a2,0x1
/*  f0239c0:	0c006b44 */ 	jal	func0001af80
/*  f0239c4:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0239c8:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0239cc:	44060000 */ 	mfc1	$a2,$f0
/*  f0239d0:	24070001 */ 	li	$a3,0x1
/*  f0239d4:	0fc239f6 */ 	jal	func0f08e8ac
/*  f0239d8:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f0239dc:	100000ca */ 	b	.PF0f023d08
/*  f0239e0:	00403825 */ 	move	$a3,$v0
.PF0f0239e4:
/*  f0239e4:	0c006b44 */ 	jal	func0001af80
/*  f0239e8:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0239ec:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0239f0:	44060000 */ 	mfc1	$a2,$f0
/*  f0239f4:	24070001 */ 	li	$a3,0x1
/*  f0239f8:	0fc239f6 */ 	jal	func0f08e8ac
/*  f0239fc:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023a00:	3c19800a */ 	lui	$t9,0x800a
/*  f023a04:	8f39a824 */ 	lw	$t9,-0x57dc($t9)
/*  f023a08:	00403825 */ 	move	$a3,$v0
/*  f023a0c:	8fae01f0 */ 	lw	$t6,0x1f0($sp)
/*  f023a10:	13200024 */ 	beqz	$t9,.PF0f023aa4
/*  f023a14:	00000000 */ 	nop
/*  f023a18:	11c000bb */ 	beqz	$t6,.PF0f023d08
/*  f023a1c:	3c09800a */ 	lui	$t1,0x800a
/*  f023a20:	8d29a7a8 */ 	lw	$t1,-0x5858($t1)
/*  f023a24:	3c0b800a */ 	lui	$t3,0x800a
/*  f023a28:	05210006 */ 	bgez	$t1,.PF0f023a44
/*  f023a2c:	00000000 */ 	nop
/*  f023a30:	8d6ba7ac */ 	lw	$t3,-0x5854($t3)
/*  f023a34:	02002025 */ 	move	$a0,$s0
/*  f023a38:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023a3c:	05600015 */ 	bltz	$t3,.PF0f023a94
/*  f023a40:	24060001 */ 	li	$a2,0x1
.PF0f023a44:
/*  f023a44:	10400008 */ 	beqz	$v0,.PF0f023a68
/*  f023a48:	8faa0208 */ 	lw	$t2,0x208($sp)
/*  f023a4c:	02002025 */ 	move	$a0,$s0
/*  f023a50:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023a54:	24060001 */ 	li	$a2,0x1
/*  f023a58:	0fc0888a */ 	jal	func0f0220ec
/*  f023a5c:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023a60:	100000a9 */ 	b	.PF0f023d08
/*  f023a64:	8fa70204 */ 	lw	$a3,0x204($sp)
.PF0f023a68:
/*  f023a68:	8d4c0020 */ 	lw	$t4,0x20($t2)
/*  f023a6c:	02002025 */ 	move	$a0,$s0
/*  f023a70:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023a74:	858d0002 */ 	lh	$t5,0x2($t4)
/*  f023a78:	00003025 */ 	move	$a2,$zero
/*  f023a7c:	51a000a3 */ 	beqzl	$t5,.PF0f023d0c
/*  f023a80:	8faa01f0 */ 	lw	$t2,0x1f0($sp)
/*  f023a84:	0fc0888a */ 	jal	func0f0220ec
/*  f023a88:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023a8c:	1000009e */ 	b	.PF0f023d08
/*  f023a90:	8fa70204 */ 	lw	$a3,0x204($sp)
.PF0f023a94:
/*  f023a94:	0fc0888a */ 	jal	func0f0220ec
/*  f023a98:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023a9c:	1000009a */ 	b	.PF0f023d08
/*  f023aa0:	8fa70204 */ 	lw	$a3,0x204($sp)
.PF0f023aa4:
/*  f023aa4:	10400012 */ 	beqz	$v0,.PF0f023af0
/*  f023aa8:	8fb80208 */ 	lw	$t8,0x208($sp)
/*  f023aac:	920f004c */ 	lbu	$t7,0x4c($s0)
/*  f023ab0:	24010001 */ 	li	$at,0x1
/*  f023ab4:	02002025 */ 	move	$a0,$s0
/*  f023ab8:	15e10008 */ 	bne	$t7,$at,.PF0f023adc
/*  f023abc:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023ac0:	02002025 */ 	move	$a0,$s0
/*  f023ac4:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023ac8:	00003025 */ 	move	$a2,$zero
/*  f023acc:	0fc0888a */ 	jal	func0f0220ec
/*  f023ad0:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023ad4:	1000008c */ 	b	.PF0f023d08
/*  f023ad8:	8fa70204 */ 	lw	$a3,0x204($sp)
.PF0f023adc:
/*  f023adc:	24060001 */ 	li	$a2,0x1
/*  f023ae0:	0fc0888a */ 	jal	func0f0220ec
/*  f023ae4:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023ae8:	10000087 */ 	b	.PF0f023d08
/*  f023aec:	8fa70204 */ 	lw	$a3,0x204($sp)
.PF0f023af0:
/*  f023af0:	8f080020 */ 	lw	$t0,0x20($t8)
/*  f023af4:	02002025 */ 	move	$a0,$s0
/*  f023af8:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023afc:	85190002 */ 	lh	$t9,0x2($t0)
/*  f023b00:	00003025 */ 	move	$a2,$zero
/*  f023b04:	53200081 */ 	beqzl	$t9,.PF0f023d0c
/*  f023b08:	8faa01f0 */ 	lw	$t2,0x1f0($sp)
/*  f023b0c:	0fc0888a */ 	jal	func0f0220ec
/*  f023b10:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023b14:	1000007c */ 	b	.PF0f023d08
/*  f023b18:	8fa70204 */ 	lw	$a3,0x204($sp)
.PF0f023b1c:
/*  f023b1c:	24010005 */ 	li	$at,0x5
/*  f023b20:	1461000a */ 	bne	$v1,$at,.PF0f023b4c
/*  f023b24:	8fa90250 */ 	lw	$t1,0x250($sp)
/*  f023b28:	0c006b44 */ 	jal	func0001af80
/*  f023b2c:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023b30:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023b34:	44060000 */ 	mfc1	$a2,$f0
/*  f023b38:	24070001 */ 	li	$a3,0x1
/*  f023b3c:	0fc239f6 */ 	jal	func0f08e8ac
/*  f023b40:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023b44:	10000070 */ 	b	.PF0f023d08
/*  f023b48:	00403825 */ 	move	$a3,$v0
.PF0f023b4c:
/*  f023b4c:	912b0000 */ 	lbu	$t3,0x0($t1)
/*  f023b50:	24010006 */ 	li	$at,0x6
/*  f023b54:	3c0a800a */ 	lui	$t2,0x800a
/*  f023b58:	55610025 */ 	bnel	$t3,$at,.PF0f023bf0
/*  f023b5c:	8fb901f0 */ 	lw	$t9,0x1f0($sp)
/*  f023b60:	8d4aa824 */ 	lw	$t2,-0x57dc($t2)
/*  f023b64:	55400012 */ 	bnezl	$t2,.PF0f023bb0
/*  f023b68:	8faf0208 */ 	lw	$t7,0x208($sp)
/*  f023b6c:	0fc4a513 */ 	jal	propGetPlayerNum
/*  f023b70:	01202025 */ 	move	$a0,$t1
/*  f023b74:	00026080 */ 	sll	$t4,$v0,0x2
/*  f023b78:	3c03800a */ 	lui	$v1,0x800a
/*  f023b7c:	006c1821 */ 	addu	$v1,$v1,$t4
/*  f023b80:	8c63a574 */ 	lw	$v1,-0x5a8c($v1)
/*  f023b84:	24010002 */ 	li	$at,0x2
/*  f023b88:	8c640000 */ 	lw	$a0,0x0($v1)
/*  f023b8c:	10810007 */ 	beq	$a0,$at,.PF0f023bac
/*  f023b90:	24010001 */ 	li	$at,0x1
/*  f023b94:	54810016 */ 	bnel	$a0,$at,.PF0f023bf0
/*  f023b98:	8fb901f0 */ 	lw	$t9,0x1f0($sp)
/*  f023b9c:	946d0010 */ 	lhu	$t5,0x10($v1)
/*  f023ba0:	24010002 */ 	li	$at,0x2
/*  f023ba4:	55a10012 */ 	bnel	$t5,$at,.PF0f023bf0
/*  f023ba8:	8fb901f0 */ 	lw	$t9,0x1f0($sp)
.PF0f023bac:
/*  f023bac:	8faf0208 */ 	lw	$t7,0x208($sp)
.PF0f023bb0:
/*  f023bb0:	02002025 */ 	move	$a0,$s0
/*  f023bb4:	24060001 */ 	li	$a2,0x1
/*  f023bb8:	8df80020 */ 	lw	$t8,0x20($t7)
/*  f023bbc:	a300000b */ 	sb	$zero,0xb($t8)
/*  f023bc0:	0fc0888a */ 	jal	func0f0220ec
/*  f023bc4:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023bc8:	0c006b44 */ 	jal	func0001af80
/*  f023bcc:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023bd0:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023bd4:	44060000 */ 	mfc1	$a2,$f0
/*  f023bd8:	24070001 */ 	li	$a3,0x1
/*  f023bdc:	0fc239f6 */ 	jal	func0f08e8ac
/*  f023be0:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023be4:	10000048 */ 	b	.PF0f023d08
/*  f023be8:	00403825 */ 	move	$a3,$v0
/*  f023bec:	8fb901f0 */ 	lw	$t9,0x1f0($sp)
.PF0f023bf0:
/*  f023bf0:	00003825 */ 	move	$a3,$zero
/*  f023bf4:	8fae0208 */ 	lw	$t6,0x208($sp)
/*  f023bf8:	5320000a */ 	beqzl	$t9,.PF0f023c24
/*  f023bfc:	8e030020 */ 	lw	$v1,0x20($s0)
/*  f023c00:	8dcb0020 */ 	lw	$t3,0x20($t6)
/*  f023c04:	02002025 */ 	move	$a0,$s0
/*  f023c08:	24060001 */ 	li	$a2,0x1
/*  f023c0c:	a160000b */ 	sb	$zero,0xb($t3)
/*  f023c10:	afa0019c */ 	sw	$zero,0x19c($sp)
/*  f023c14:	0fc0888a */ 	jal	func0f0220ec
/*  f023c18:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023c1c:	8fa7019c */ 	lw	$a3,0x19c($sp)
/*  f023c20:	8e030020 */ 	lw	$v1,0x20($s0)
.PF0f023c24:
/*  f023c24:	1060002c */ 	beqz	$v1,.PF0f023cd8
/*  f023c28:	00000000 */ 	nop
/*  f023c2c:	8c620020 */ 	lw	$v0,0x20($v1)
/*  f023c30:	10400029 */ 	beqz	$v0,.PF0f023cd8
/*  f023c34:	00000000 */ 	nop
/*  f023c38:	84440000 */ 	lh	$a0,0x0($v0)
/*  f023c3c:	3c0a8006 */ 	lui	$t2,0x8006
/*  f023c40:	8d4aecbc */ 	lw	$t2,-0x1344($t2)
/*  f023c44:	00044880 */ 	sll	$t1,$a0,0x2
/*  f023c48:	01244823 */ 	subu	$t1,$t1,$a0
/*  f023c4c:	00094880 */ 	sll	$t1,$t1,0x2
/*  f023c50:	01496021 */ 	addu	$t4,$t2,$t1
/*  f023c54:	918d000b */ 	lbu	$t5,0xb($t4)
/*  f023c58:	31af0004 */ 	andi	$t7,$t5,0x4
/*  f023c5c:	11e0001e */ 	beqz	$t7,.PF0f023cd8
/*  f023c60:	00000000 */ 	nop
/*  f023c64:	0c008d8e */ 	jal	func00023d38
/*  f023c68:	00000000 */ 	nop
/*  f023c6c:	8e180020 */ 	lw	$t8,0x20($s0)
/*  f023c70:	8f020020 */ 	lw	$v0,0x20($t8)
/*  f023c74:	84440000 */ 	lh	$a0,0x0($v0)
/*  f023c78:	0c008c53 */ 	jal	func0002384c
/*  f023c7c:	84450014 */ 	lh	$a1,0x14($v0)
/*  f023c80:	28440000 */ 	slti	$a0,$v0,0x0
/*  f023c84:	54800014 */ 	bnezl	$a0,.PF0f023cd8
/*  f023c88:	00803825 */ 	move	$a3,$a0
/*  f023c8c:	8e080020 */ 	lw	$t0,0x20($s0)
/*  f023c90:	8d020020 */ 	lw	$v0,0x20($t0)
/*  f023c94:	84440000 */ 	lh	$a0,0x0($v0)
/*  f023c98:	0c008c53 */ 	jal	func0002384c
/*  f023c9c:	84450016 */ 	lh	$a1,0x16($v0)
/*  f023ca0:	28440000 */ 	slti	$a0,$v0,0x0
/*  f023ca4:	5080000c */ 	beqzl	$a0,.PF0f023cd8
/*  f023ca8:	00803825 */ 	move	$a3,$a0
/*  f023cac:	8e190020 */ 	lw	$t9,0x20($s0)
/*  f023cb0:	44809000 */ 	mtc1	$zero,$f18
/*  f023cb4:	00002025 */ 	move	$a0,$zero
/*  f023cb8:	8f2e0020 */ 	lw	$t6,0x20($t9)
/*  f023cbc:	c5c40010 */ 	lwc1	$f4,0x10($t6)
/*  f023cc0:	46049032 */ 	c.eq.s	$f18,$f4
/*  f023cc4:	00000000 */ 	nop
/*  f023cc8:	45030003 */ 	bc1tl	.PF0f023cd8
/*  f023ccc:	00803825 */ 	move	$a3,$a0
/*  f023cd0:	24040001 */ 	li	$a0,0x1
/*  f023cd4:	00803825 */ 	move	$a3,$a0
.PF0f023cd8:
/*  f023cd8:	10e00003 */ 	beqz	$a3,.PF0f023ce8
/*  f023cdc:	00000000 */ 	nop
/*  f023ce0:	10000009 */ 	b	.PF0f023d08
/*  f023ce4:	00003825 */ 	move	$a3,$zero
.PF0f023ce8:
/*  f023ce8:	0c006b44 */ 	jal	func0001af80
/*  f023cec:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023cf0:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023cf4:	44060000 */ 	mfc1	$a2,$f0
/*  f023cf8:	24070001 */ 	li	$a3,0x1
/*  f023cfc:	0fc239f6 */ 	jal	func0f08e8ac
/*  f023d00:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023d04:	00403825 */ 	move	$a3,$v0
.PF0f023d08:
/*  f023d08:	8faa01f0 */ 	lw	$t2,0x1f0($sp)
.PF0f023d0c:
/*  f023d0c:	02002025 */ 	move	$a0,$s0
/*  f023d10:	51400016 */ 	beqzl	$t2,.PF0f023d6c
/*  f023d14:	8fab0250 */ 	lw	$t3,0x250($sp)
/*  f023d18:	82090007 */ 	lb	$t1,0x7($s0)
/*  f023d1c:	24010001 */ 	li	$at,0x1
/*  f023d20:	8fac0208 */ 	lw	$t4,0x208($sp)
/*  f023d24:	5521000b */ 	bnel	$t1,$at,.PF0f023d54
/*  f023d28:	96190192 */ 	lhu	$t9,0x192($s0)
/*  f023d2c:	8d8d0020 */ 	lw	$t5,0x20($t4)
/*  f023d30:	8fb80250 */ 	lw	$t8,0x250($sp)
/*  f023d34:	85af0002 */ 	lh	$t7,0x2($t5)
/*  f023d38:	55e00006 */ 	bnezl	$t7,.PF0f023d54
/*  f023d3c:	96190192 */ 	lhu	$t9,0x192($s0)
/*  f023d40:	93080000 */ 	lbu	$t0,0x0($t8)
/*  f023d44:	24010006 */ 	li	$at,0x6
/*  f023d48:	15010004 */ 	bne	$t0,$at,.PF0f023d5c
/*  f023d4c:	00000000 */ 	nop
/*  f023d50:	96190192 */ 	lhu	$t9,0x192($s0)
.PF0f023d54:
/*  f023d54:	372e0040 */ 	ori	$t6,$t9,0x40
/*  f023d58:	a60e0192 */ 	sh	$t6,0x192($s0)
.PF0f023d5c:
/*  f023d5c:	0fc084e5 */ 	jal	chrUpdateAimProperties
/*  f023d60:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023d64:	8fa70204 */ 	lw	$a3,0x204($sp)
/*  f023d68:	8fab0250 */ 	lw	$t3,0x250($sp)
.PF0f023d6c:
/*  f023d6c:	3c01c780 */ 	lui	$at,0xc780
/*  f023d70:	44815000 */ 	mtc1	$at,$f10
/*  f023d74:	c566000c */ 	lwc1	$f6,0xc($t3)
/*  f023d78:	3c0a800a */ 	lui	$t2,0x800a
/*  f023d7c:	460a303c */ 	c.lt.s	$f6,$f10
/*  f023d80:	00000000 */ 	nop
/*  f023d84:	45000002 */ 	bc1f	.PF0f023d90
/*  f023d88:	00000000 */ 	nop
/*  f023d8c:	00003825 */ 	move	$a3,$zero
.PF0f023d90:
/*  f023d90:	8d4aa828 */ 	lw	$t2,-0x57d8($t2)
/*  f023d94:	5540002d */ 	bnezl	$t2,.PF0f023e4c
/*  f023d98:	8fa90250 */ 	lw	$t1,0x250($sp)
/*  f023d9c:	50e0002b */ 	beqzl	$a3,.PF0f023e4c
/*  f023da0:	8fa90250 */ 	lw	$t1,0x250($sp)
/*  f023da4:	82030007 */ 	lb	$v1,0x7($s0)
/*  f023da8:	24010005 */ 	li	$at,0x5
/*  f023dac:	10610006 */ 	beq	$v1,$at,.PF0f023dc8
/*  f023db0:	2401001f */ 	li	$at,0x1f
/*  f023db4:	14610017 */ 	bne	$v1,$at,.PF0f023e14
/*  f023db8:	00000000 */ 	nop
/*  f023dbc:	8e090018 */ 	lw	$t1,0x18($s0)
/*  f023dc0:	00096140 */ 	sll	$t4,$t1,0x5
/*  f023dc4:	05800013 */ 	bltz	$t4,.PF0f023e14
.PF0f023dc8:
/*  f023dc8:	3c03800a */ 	lui	$v1,0x800a
/*  f023dcc:	2463d30c */ 	addiu	$v1,$v1,-11508
/*  f023dd0:	8c6d0000 */ 	lw	$t5,0x0($v1)
/*  f023dd4:	02002025 */ 	move	$a0,$s0
/*  f023dd8:	25a20001 */ 	addiu	$v0,$t5,0x1
/*  f023ddc:	2841000b */ 	slti	$at,$v0,0xb
/*  f023de0:	14200009 */ 	bnez	$at,.PF0f023e08
/*  f023de4:	ac620000 */ 	sw	$v0,0x0($v1)
/*  f023de8:	0fc091e3 */ 	jal	chrDropWeapons
/*  f023dec:	afa00204 */ 	sw	$zero,0x204($sp)
/*  f023df0:	8e180014 */ 	lw	$t8,0x14($s0)
/*  f023df4:	8fa70204 */ 	lw	$a3,0x204($sp)
/*  f023df8:	3c02800a */ 	lui	$v0,0x800a
/*  f023dfc:	37080020 */ 	ori	$t0,$t8,0x20
/*  f023e00:	ae080014 */ 	sw	$t0,0x14($s0)
/*  f023e04:	8c42d30c */ 	lw	$v0,-0x2cf4($v0)
.PF0f023e08:
/*  f023e08:	3c03800a */ 	lui	$v1,0x800a
/*  f023e0c:	10000008 */ 	b	.PF0f023e30
/*  f023e10:	2463d310 */ 	addiu	$v1,$v1,-11504
.PF0f023e14:
/*  f023e14:	3c03800a */ 	lui	$v1,0x800a
/*  f023e18:	2463d310 */ 	addiu	$v1,$v1,-11504
/*  f023e1c:	8c790000 */ 	lw	$t9,0x0($v1)
/*  f023e20:	3c02800a */ 	lui	$v0,0x800a
/*  f023e24:	272e0001 */ 	addiu	$t6,$t9,0x1
/*  f023e28:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f023e2c:	8c42d30c */ 	lw	$v0,-0x2cf4($v0)
.PF0f023e30:
/*  f023e30:	8c6b0000 */ 	lw	$t3,0x0($v1)
/*  f023e34:	01625021 */ 	addu	$t2,$t3,$v0
/*  f023e38:	2941001f */ 	slti	$at,$t2,0x1f
/*  f023e3c:	54200003 */ 	bnezl	$at,.PF0f023e4c
/*  f023e40:	8fa90250 */ 	lw	$t1,0x250($sp)
/*  f023e44:	00003825 */ 	move	$a3,$zero
/*  f023e48:	8fa90250 */ 	lw	$t1,0x250($sp)
.PF0f023e4c:
/*  f023e4c:	8faa0250 */ 	lw	$t2,0x250($sp)
/*  f023e50:	10e001be */ 	beqz	$a3,.PF0f02454c
/*  f023e54:	91220001 */ 	lbu	$v0,0x1($t1)
/*  f023e58:	344c0042 */ 	ori	$t4,$v0,0x42
/*  f023e5c:	a12c0001 */ 	sb	$t4,0x1($t1)
/*  f023e60:	8e0d0018 */ 	lw	$t5,0x18($s0)
/*  f023e64:	3c18800a */ 	lui	$t8,0x800a
/*  f023e68:	35af0008 */ 	ori	$t7,$t5,0x8
/*  f023e6c:	ae0f0018 */ 	sw	$t7,0x18($s0)
/*  f023e70:	8f18a7ac */ 	lw	$t8,-0x5854($t8)
/*  f023e74:	0700000a */ 	bltz	$t8,.PF0f023ea0
/*  f023e78:	3c08800a */ 	lui	$t0,0x800a
/*  f023e7c:	3c19800a */ 	lui	$t9,0x800a
/*  f023e80:	8f39a794 */ 	lw	$t9,-0x586c($t9)
/*  f023e84:	8d08a7b0 */ 	lw	$t0,-0x5850($t0)
/*  f023e88:	15190005 */ 	bne	$t0,$t9,.PF0f023ea0
/*  f023e8c:	00000000 */ 	nop
/*  f023e90:	8e0e0014 */ 	lw	$t6,0x14($s0)
/*  f023e94:	3c010080 */ 	lui	$at,0x80
/*  f023e98:	01c15825 */ 	or	$t3,$t6,$at
/*  f023e9c:	ae0b0014 */ 	sw	$t3,0x14($s0)
.PF0f023ea0:
/*  f023ea0:	0fc41dd5 */ 	jal	cheatIsActive
/*  f023ea4:	24040007 */ 	li	$a0,0x7
/*  f023ea8:	10400004 */ 	beqz	$v0,.PF0f023ebc
/*  f023eac:	3c013ea0 */ 	lui	$at,0x3ea0
/*  f023eb0:	44816000 */ 	mtc1	$at,$f12
/*  f023eb4:	0c0068a7 */ 	jal	modelSetDistanceScale
/*  f023eb8:	00000000 */ 	nop
.PF0f023ebc:
/*  f023ebc:	3c0a7f02 */ 	lui	$t2,0x7f02
/*  f023ec0:	254a1668 */ 	addiu	$t2,$t2,0x1668
/*  f023ec4:	3c018006 */ 	lui	$at,0x8006
/*  f023ec8:	ac2aec74 */ 	sw	$t2,-0x138c($at)
/*  f023ecc:	3c01800a */ 	lui	$at,0x800a
/*  f023ed0:	12000003 */ 	beqz	$s0,.PF0f023ee0
/*  f023ed4:	ac30d27c */ 	sw	$s0,-0x2d84($at)
/*  f023ed8:	10000002 */ 	b	.PF0f023ee4
/*  f023edc:	920402fe */ 	lbu	$a0,0x2fe($s0)
.PF0f023ee0:
/*  f023ee0:	00002025 */ 	move	$a0,$zero
.PF0f023ee4:
/*  f023ee4:	24010002 */ 	li	$at,0x2
/*  f023ee8:	14810021 */ 	bne	$a0,$at,.PF0f023f70
/*  f023eec:	3c0c800a */ 	lui	$t4,0x800a
/*  f023ef0:	8d8ca7bc */ 	lw	$t4,-0x5844($t4)
/*  f023ef4:	24010006 */ 	li	$at,0x6
/*  f023ef8:	5181001e */ 	beql	$t4,$at,.PF0f023f74
/*  f023efc:	8fad0250 */ 	lw	$t5,0x250($sp)
/*  f023f00:	0fc0f978 */ 	jal	chrGetInverseTheta
/*  f023f04:	02002025 */ 	move	$a0,$s0
/*  f023f08:	e7a0018c */ 	swc1	$f0,0x18c($sp)
/*  f023f0c:	0c00685b */ 	jal	sinf
/*  f023f10:	46000306 */ 	mov.s	$f12,$f0
/*  f023f14:	3c014198 */ 	lui	$at,0x4198
/*  f023f18:	44814000 */ 	mtc1	$at,$f8
/*  f023f1c:	44802000 */ 	mtc1	$zero,$f4
/*  f023f20:	c7ac018c */ 	lwc1	$f12,0x18c($sp)
/*  f023f24:	46080482 */ 	mul.s	$f18,$f0,$f8
/*  f023f28:	e7a40194 */ 	swc1	$f4,0x194($sp)
/*  f023f2c:	0c006858 */ 	jal	cosf
/*  f023f30:	e7b20190 */ 	swc1	$f18,0x190($sp)
/*  f023f34:	3c014198 */ 	lui	$at,0x4198
/*  f023f38:	44813000 */ 	mtc1	$at,$f6
/*  f023f3c:	27a40190 */ 	addiu	$a0,$sp,0x190
/*  f023f40:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f023f44:	46060282 */ 	mul.s	$f10,$f0,$f6
/*  f023f48:	0c00591b */ 	jal	func000166dc
/*  f023f4c:	e7aa0198 */ 	swc1	$f10,0x198($sp)
/*  f023f50:	0fc2d706 */ 	jal	currentPlayerGetMatrix1740
/*  f023f54:	00000000 */ 	nop
/*  f023f58:	00402025 */ 	move	$a0,$v0
/*  f023f5c:	0c0055e3 */ 	jal	func000159fc
/*  f023f60:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f023f64:	27a901a8 */ 	addiu	$t1,$sp,0x1a8
/*  f023f68:	1000004b */ 	b	.PF0f024098
/*  f023f6c:	afa90210 */ 	sw	$t1,0x210($sp)
.PF0f023f70:
/*  f023f70:	8fad0250 */ 	lw	$t5,0x250($sp)
.PF0f023f74:
/*  f023f74:	24010006 */ 	li	$at,0x6
/*  f023f78:	91af0000 */ 	lbu	$t7,0x0($t5)
/*  f023f7c:	15e10043 */ 	bne	$t7,$at,.PF0f02408c
/*  f023f80:	00000000 */ 	nop
/*  f023f84:	0fc4a513 */ 	jal	propGetPlayerNum
/*  f023f88:	01a02025 */ 	move	$a0,$t5
/*  f023f8c:	0002c080 */ 	sll	$t8,$v0,0x2
/*  f023f90:	3c03800a */ 	lui	$v1,0x800a
/*  f023f94:	00781821 */ 	addu	$v1,$v1,$t8
/*  f023f98:	8c63a574 */ 	lw	$v1,-0x5a8c($v1)
/*  f023f9c:	24010003 */ 	li	$at,0x3
/*  f023fa0:	02002025 */ 	move	$a0,$s0
/*  f023fa4:	8c6801b0 */ 	lw	$t0,0x1b0($v1)
/*  f023fa8:	15010034 */ 	bne	$t0,$at,.PF0f02407c
/*  f023fac:	00000000 */ 	nop
/*  f023fb0:	0fc0f978 */ 	jal	chrGetInverseTheta
/*  f023fb4:	afa30188 */ 	sw	$v1,0x188($sp)
/*  f023fb8:	8fa30188 */ 	lw	$v1,0x188($sp)
/*  f023fbc:	e7a00178 */ 	swc1	$f0,0x178($sp)
/*  f023fc0:	3c01447a */ 	lui	$at,0x447a
/*  f023fc4:	8c791a6c */ 	lw	$t9,0x1a6c($v1)
/*  f023fc8:	44819000 */ 	mtc1	$at,$f18
/*  f023fcc:	46000306 */ 	mov.s	$f12,$f0
/*  f023fd0:	8f220004 */ 	lw	$v0,0x4($t9)
/*  f023fd4:	c44800ac */ 	lwc1	$f8,0xac($v0)
/*  f023fd8:	afa20174 */ 	sw	$v0,0x174($sp)
/*  f023fdc:	46124102 */ 	mul.s	$f4,$f8,$f18
/*  f023fe0:	0c006858 */ 	jal	cosf
/*  f023fe4:	e7a40130 */ 	swc1	$f4,0x130($sp)
/*  f023fe8:	c7a60130 */ 	lwc1	$f6,0x130($sp)
/*  f023fec:	8fa20174 */ 	lw	$v0,0x174($sp)
/*  f023ff0:	44804000 */ 	mtc1	$zero,$f8
/*  f023ff4:	46060282 */ 	mul.s	$f10,$f0,$f6
/*  f023ff8:	3c014348 */ 	lui	$at,0x4348
/*  f023ffc:	44819000 */ 	mtc1	$at,$f18
/*  f024000:	e7aa017c */ 	swc1	$f10,0x17c($sp)
/*  f024004:	c44200ac */ 	lwc1	$f2,0xac($v0)
/*  f024008:	4602403c */ 	c.lt.s	$f8,$f2
/*  f02400c:	00000000 */ 	nop
/*  f024010:	45020004 */ 	bc1fl	.PF0f024024
/*  f024014:	46001007 */ 	neg.s	$f0,$f2
/*  f024018:	10000002 */ 	b	.PF0f024024
/*  f02401c:	46001006 */ 	mov.s	$f0,$f2
/*  f024020:	46001007 */ 	neg.s	$f0,$f2
.PF0f024024:
/*  f024024:	46120102 */ 	mul.s	$f4,$f0,$f18
/*  f024028:	3c0141c8 */ 	lui	$at,0x41c8
/*  f02402c:	44813000 */ 	mtc1	$at,$f6
/*  f024030:	c7ac0178 */ 	lwc1	$f12,0x178($sp)
/*  f024034:	46006307 */ 	neg.s	$f12,$f12
/*  f024038:	46062280 */ 	add.s	$f10,$f4,$f6
/*  f02403c:	0c00685b */ 	jal	sinf
/*  f024040:	e7aa0180 */ 	swc1	$f10,0x180($sp)
/*  f024044:	c7a80130 */ 	lwc1	$f8,0x130($sp)
/*  f024048:	27a4017c */ 	addiu	$a0,$sp,0x17c
/*  f02404c:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f024050:	46080482 */ 	mul.s	$f18,$f0,$f8
/*  f024054:	0c00591b */ 	jal	func000166dc
/*  f024058:	e7b20184 */ 	swc1	$f18,0x184($sp)
/*  f02405c:	0fc2d706 */ 	jal	currentPlayerGetMatrix1740
/*  f024060:	00000000 */ 	nop
/*  f024064:	00402025 */ 	move	$a0,$v0
/*  f024068:	0c0055e3 */ 	jal	func000159fc
/*  f02406c:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f024070:	27ae01a8 */ 	addiu	$t6,$sp,0x1a8
/*  f024074:	10000008 */ 	b	.PF0f024098
/*  f024078:	afae0210 */ 	sw	$t6,0x210($sp)
.PF0f02407c:
/*  f02407c:	0fc2d706 */ 	jal	currentPlayerGetMatrix1740
/*  f024080:	00000000 */ 	nop
/*  f024084:	10000004 */ 	b	.PF0f024098
/*  f024088:	afa20210 */ 	sw	$v0,0x210($sp)
.PF0f02408c:
/*  f02408c:	0fc2d706 */ 	jal	currentPlayerGetMatrix1740
/*  f024090:	00000000 */ 	nop
/*  f024094:	afa20210 */ 	sw	$v0,0x210($sp)
.PF0f024098:
/*  f024098:	8fab0208 */ 	lw	$t3,0x208($sp)
/*  f02409c:	8d6a0008 */ 	lw	$t2,0x8($t3)
/*  f0240a0:	8544000e */ 	lh	$a0,0xe($t2)
/*  f0240a4:	00046180 */ 	sll	$t4,$a0,0x6
/*  f0240a8:	0fc5a25d */ 	jal	gfxAllocate
/*  f0240ac:	01802025 */ 	move	$a0,$t4
/*  f0240b0:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
/*  f0240b4:	afa20220 */ 	sw	$v0,0x220($sp)
/*  f0240b8:	11200011 */ 	beqz	$t1,.PF0f024100
/*  f0240bc:	3c02800a */ 	lui	$v0,0x800a
/*  f0240c0:	8c42d27c */ 	lw	$v0,-0x2d84($v0)
/*  f0240c4:	3c0f800a */ 	lui	$t7,0x800a
/*  f0240c8:	80430012 */ 	lb	$v1,0x12($v0)
/*  f0240cc:	0460000c */ 	bltz	$v1,.PF0f024100
/*  f0240d0:	00000000 */ 	nop
/*  f0240d4:	8defa548 */ 	lw	$t7,-0x5ab8($t7)
/*  f0240d8:	2408ffff */ 	li	$t0,-1
/*  f0240dc:	006f6821 */ 	addu	$t5,$v1,$t7
/*  f0240e0:	a04d0012 */ 	sb	$t5,0x12($v0)
/*  f0240e4:	3c02800a */ 	lui	$v0,0x800a
/*  f0240e8:	8c42d27c */ 	lw	$v0,-0x2d84($v0)
/*  f0240ec:	80580012 */ 	lb	$t8,0x12($v0)
/*  f0240f0:	2b010018 */ 	slti	$at,$t8,0x18
/*  f0240f4:	14200002 */ 	bnez	$at,.PF0f024100
/*  f0240f8:	00000000 */ 	nop
/*  f0240fc:	a0480012 */ 	sb	$t0,0x12($v0)
.PF0f024100:
/*  f024100:	3c03800a */ 	lui	$v1,0x800a
/*  f024104:	8c63a794 */ 	lw	$v1,-0x586c($v1)
/*  f024108:	24631bb0 */ 	addiu	$v1,$v1,0x1bb0
/*  f02410c:	0fc2d736 */ 	jal	currentPlayerGetLodScaleZ
/*  f024110:	afa30124 */ 	sw	$v1,0x124($sp)
/*  f024114:	3c19800a */ 	lui	$t9,0x800a
/*  f024118:	8f39a828 */ 	lw	$t9,-0x57d8($t9)
/*  f02411c:	8fa30124 */ 	lw	$v1,0x124($sp)
/*  f024120:	46000406 */ 	mov.s	$f16,$f0
/*  f024124:	1320000c */ 	beqz	$t9,.PF0f024158
/*  f024128:	00003025 */ 	move	$a2,$zero
/*  f02412c:	3c0e800b */ 	lui	$t6,0x800b
/*  f024130:	8dced134 */ 	lw	$t6,-0x2ecc($t6)
/*  f024134:	3c017f1b */ 	lui	$at,0x7f1b
/*  f024138:	31cb00c0 */ 	andi	$t3,$t6,0xc0
/*  f02413c:	11600004 */ 	beqz	$t3,.PF0f024150
/*  f024140:	00000000 */ 	nop
/*  f024144:	3c017f1b */ 	lui	$at,0x7f1b
/*  f024148:	10000010 */ 	b	.PF0f02418c
/*  f02414c:	c42e99dc */ 	lwc1	$f14,-0x6624($at)
.PF0f024150:
/*  f024150:	1000000e */ 	b	.PF0f02418c
/*  f024154:	c42e99e0 */ 	lwc1	$f14,-0x6620($at)
.PF0f024158:
/*  f024158:	afa30124 */ 	sw	$v1,0x124($sp)
/*  f02415c:	afa60110 */ 	sw	$a2,0x110($sp)
/*  f024160:	0fc47e5c */ 	jal	debugGetSlowMotion
/*  f024164:	e7b00114 */ 	swc1	$f16,0x114($sp)
/*  f024168:	8fa30124 */ 	lw	$v1,0x124($sp)
/*  f02416c:	8fa60110 */ 	lw	$a2,0x110($sp)
/*  f024170:	10400004 */ 	beqz	$v0,.PF0f024184
/*  f024174:	c7b00114 */ 	lwc1	$f16,0x114($sp)
/*  f024178:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02417c:	10000003 */ 	b	.PF0f02418c
/*  f024180:	c42e99e4 */ 	lwc1	$f14,-0x661c($at)
.PF0f024184:
/*  f024184:	3c017f1b */ 	lui	$at,0x7f1b
/*  f024188:	c42e99e8 */ 	lwc1	$f14,-0x6618($at)
.PF0f02418c:
/*  f02418c:	8faa0208 */ 	lw	$t2,0x208($sp)
/*  f024190:	27a40210 */ 	addiu	$a0,$sp,0x210
/*  f024194:	8d420020 */ 	lw	$v0,0x20($t2)
/*  f024198:	50400057 */ 	beqzl	$v0,.PF0f0242f8
/*  f02419c:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f0241a0:	844c0000 */ 	lh	$t4,0x0($v0)
/*  f0241a4:	8fa90250 */ 	lw	$t1,0x250($sp)
/*  f0241a8:	51800053 */ 	beqzl	$t4,.PF0f0242f8
/*  f0241ac:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f0241b0:	c5240008 */ 	lwc1	$f4,0x8($t1)
/*  f0241b4:	c4660000 */ 	lwc1	$f6,0x0($v1)
/*  f0241b8:	c52a000c */ 	lwc1	$f10,0xc($t1)
/*  f0241bc:	c4680004 */ 	lwc1	$f8,0x4($v1)
/*  f0241c0:	46062001 */ 	sub.s	$f0,$f4,$f6
/*  f0241c4:	c4640008 */ 	lwc1	$f4,0x8($v1)
/*  f0241c8:	c5320010 */ 	lwc1	$f18,0x10($t1)
/*  f0241cc:	46085081 */ 	sub.s	$f2,$f10,$f8
/*  f0241d0:	46000182 */ 	mul.s	$f6,$f0,$f0
/*  f0241d4:	46049301 */ 	sub.s	$f12,$f18,$f4
/*  f0241d8:	46021282 */ 	mul.s	$f10,$f2,$f2
/*  f0241dc:	460a3200 */ 	add.s	$f8,$f6,$f10
/*  f0241e0:	460c6482 */ 	mul.s	$f18,$f12,$f12
/*  f0241e4:	46124100 */ 	add.s	$f4,$f8,$f18
/*  f0241e8:	46102182 */ 	mul.s	$f6,$f4,$f16
/*  f0241ec:	00000000 */ 	nop
/*  f0241f0:	46103282 */ 	mul.s	$f10,$f6,$f16
/*  f0241f4:	460a703c */ 	c.lt.s	$f14,$f10
/*  f0241f8:	00000000 */ 	nop
/*  f0241fc:	4500003d */ 	bc1f	.PF0f0242f4
/*  f024200:	00000000 */ 	nop
/*  f024204:	c4400010 */ 	lwc1	$f0,0x10($v0)
/*  f024208:	44801000 */ 	mtc1	$zero,$f2
/*  f02420c:	24060001 */ 	li	$a2,0x1
/*  f024210:	e7a0010c */ 	swc1	$f0,0x10c($sp)
/*  f024214:	844f0014 */ 	lh	$t7,0x14($v0)
/*  f024218:	46001032 */ 	c.eq.s	$f2,$f0
/*  f02421c:	afaf0108 */ 	sw	$t7,0x108($sp)
/*  f024220:	c4480034 */ 	lwc1	$f8,0x34($v0)
/*  f024224:	e7a80104 */ 	swc1	$f8,0x104($sp)
/*  f024228:	844d0038 */ 	lh	$t5,0x38($v0)
/*  f02422c:	45010014 */ 	bc1t	.PF0f024280
/*  f024230:	afad0100 */ 	sw	$t5,0x100($sp)
/*  f024234:	c452001c */ 	lwc1	$f18,0x1c($v0)
/*  f024238:	c4440074 */ 	lwc1	$f4,0x74($v0)
/*  f02423c:	3c013e80 */ 	lui	$at,0x3e80
/*  f024240:	44815000 */ 	mtc1	$at,$f10
/*  f024244:	46049182 */ 	mul.s	$f6,$f18,$f4
/*  f024248:	3c013f00 */ 	lui	$at,0x3f00
/*  f02424c:	4606503e */ 	c.le.s	$f10,$f6
/*  f024250:	00000000 */ 	nop
/*  f024254:	4502000b */ 	bc1fl	.PF0f024284
/*  f024258:	c4520054 */ 	lwc1	$f18,0x54($v0)
/*  f02425c:	44814000 */ 	mtc1	$at,$f8
/*  f024260:	00000000 */ 	nop
/*  f024264:	4600403c */ 	c.lt.s	$f8,$f0
/*  f024268:	00000000 */ 	nop
/*  f02426c:	45020004 */ 	bc1fl	.PF0f024280
/*  f024270:	e4420010 */ 	swc1	$f2,0x10($v0)
/*  f024274:	84580016 */ 	lh	$t8,0x16($v0)
/*  f024278:	a4580014 */ 	sh	$t8,0x14($v0)
/*  f02427c:	e4420010 */ 	swc1	$f2,0x10($v0)
.PF0f024280:
/*  f024280:	c4520054 */ 	lwc1	$f18,0x54($v0)
.PF0f024284:
/*  f024284:	46121032 */ 	c.eq.s	$f2,$f18
/*  f024288:	00000000 */ 	nop
/*  f02428c:	4503001a */ 	bc1tl	.PF0f0242f8
/*  f024290:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f024294:	c4440040 */ 	lwc1	$f4,0x40($v0)
/*  f024298:	c4460074 */ 	lwc1	$f6,0x74($v0)
/*  f02429c:	3c013e80 */ 	lui	$at,0x3e80
/*  f0242a0:	44814000 */ 	mtc1	$at,$f8
/*  f0242a4:	46062282 */ 	mul.s	$f10,$f4,$f6
/*  f0242a8:	460a403e */ 	c.le.s	$f8,$f10
/*  f0242ac:	00000000 */ 	nop
/*  f0242b0:	45020011 */ 	bc1fl	.PF0f0242f8
/*  f0242b4:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f0242b8:	c4400034 */ 	lwc1	$f0,0x34($v0)
/*  f0242bc:	3c013f00 */ 	lui	$at,0x3f00
/*  f0242c0:	46001032 */ 	c.eq.s	$f2,$f0
/*  f0242c4:	00000000 */ 	nop
/*  f0242c8:	4503000b */ 	bc1tl	.PF0f0242f8
/*  f0242cc:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f0242d0:	44819000 */ 	mtc1	$at,$f18
/*  f0242d4:	00000000 */ 	nop
/*  f0242d8:	4600903c */ 	c.lt.s	$f18,$f0
/*  f0242dc:	00000000 */ 	nop
/*  f0242e0:	45020004 */ 	bc1fl	.PF0f0242f4
/*  f0242e4:	e4420034 */ 	swc1	$f2,0x34($v0)
/*  f0242e8:	8448003a */ 	lh	$t0,0x3a($v0)
/*  f0242ec:	a4480038 */ 	sh	$t0,0x38($v0)
/*  f0242f0:	e4420034 */ 	swc1	$f2,0x34($v0)
.PF0f0242f4:
/*  f0242f4:	8fa50208 */ 	lw	$a1,0x208($sp)
.PF0f0242f8:
/*  f0242f8:	afa20128 */ 	sw	$v0,0x128($sp)
/*  f0242fc:	0c007323 */ 	jal	func0001cebc
/*  f024300:	afa60110 */ 	sw	$a2,0x110($sp)
/*  f024304:	8fa60110 */ 	lw	$a2,0x110($sp)
/*  f024308:	8fa20128 */ 	lw	$v0,0x128($sp)
/*  f02430c:	c7a4010c */ 	lwc1	$f4,0x10c($sp)
/*  f024310:	10c00008 */ 	beqz	$a2,.PF0f024334
/*  f024314:	3c018006 */ 	lui	$at,0x8006
/*  f024318:	e4440010 */ 	swc1	$f4,0x10($v0)
/*  f02431c:	8fb90108 */ 	lw	$t9,0x108($sp)
/*  f024320:	a4590014 */ 	sh	$t9,0x14($v0)
/*  f024324:	c7a60104 */ 	lwc1	$f6,0x104($sp)
/*  f024328:	e4460034 */ 	swc1	$f6,0x34($v0)
/*  f02432c:	8fae0100 */ 	lw	$t6,0x100($sp)
/*  f024330:	a44e0038 */ 	sh	$t6,0x38($v0)
.PF0f024334:
/*  f024334:	ac20ec74 */ 	sw	$zero,-0x138c($at)
/*  f024338:	3c018006 */ 	lui	$at,0x8006
/*  f02433c:	0c0068a7 */ 	jal	modelSetDistanceScale
/*  f024340:	c42c26c8 */ 	lwc1	$f12,0x26c8($at)
/*  f024344:	8fab01f0 */ 	lw	$t3,0x1f0($sp)
/*  f024348:	260400f8 */ 	addiu	$a0,$s0,0xf8
/*  f02434c:	11600003 */ 	beqz	$t3,.PF0f02435c
/*  f024350:	00000000 */ 	nop
/*  f024354:	0fc1a666 */ 	jal	colourTween
/*  f024358:	260500fc */ 	addiu	$a1,$s0,0xfc
.PF0f02435c:
/*  f02435c:	0c0069de */ 	jal	func0001a9e8
/*  f024360:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f024364:	8faa0250 */ 	lw	$t2,0x250($sp)
/*  f024368:	8d47001c */ 	lw	$a3,0x1c($t2)
/*  f02436c:	e5400014 */ 	swc1	$f0,0x14($t2)
/*  f024370:	50e0000b */ 	beqzl	$a3,.PF0f0243a0
/*  f024374:	8e030178 */ 	lw	$v1,0x178($s0)
/*  f024378:	8ce20020 */ 	lw	$v0,0x20($a3)
.PF0f02437c:
/*  f02437c:	02002025 */ 	move	$a0,$s0
/*  f024380:	00e02825 */ 	move	$a1,$a3
/*  f024384:	8fa601f0 */ 	lw	$a2,0x1f0($sp)
/*  f024388:	0fc088d4 */ 	jal	func0f022214
/*  f02438c:	afa201f4 */ 	sw	$v0,0x1f4($sp)
/*  f024390:	8fa701f4 */ 	lw	$a3,0x1f4($sp)
/*  f024394:	54e0fff9 */ 	bnezl	$a3,.PF0f02437c
/*  f024398:	8ce20020 */ 	lw	$v0,0x20($a3)
/*  f02439c:	8e030178 */ 	lw	$v1,0x178($s0)
.PF0f0243a0:
/*  f0243a0:	5060004d */ 	beqzl	$v1,.PF0f0244d8
/*  f0243a4:	8fa90208 */ 	lw	$t1,0x208($sp)
/*  f0243a8:	8c620004 */ 	lw	$v0,0x4($v1)
/*  f0243ac:	8c4c0018 */ 	lw	$t4,0x18($v0)
/*  f0243b0:	afac00f4 */ 	sw	$t4,0xf4($sp)
/*  f0243b4:	82040006 */ 	lb	$a0,0x6($s0)
/*  f0243b8:	2881002a */ 	slti	$at,$a0,0x2a
/*  f0243bc:	14200045 */ 	bnez	$at,.PF0f0244d4
/*  f0243c0:	2881002b */ 	slti	$at,$a0,0x2b
/*  f0243c4:	10200043 */ 	beqz	$at,.PF0f0244d4
/*  f0243c8:	3c0f8006 */ 	lui	$t7,0x8006
/*  f0243cc:	25ef271c */ 	addiu	$t7,$t7,0x271c
/*  f0243d0:	8de10000 */ 	lw	$at,0x0($t7)
/*  f0243d4:	27a900e8 */ 	addiu	$t1,$sp,0xe8
/*  f0243d8:	8df80004 */ 	lw	$t8,0x4($t7)
/*  f0243dc:	ad210000 */ 	sw	$at,0x0($t1)
/*  f0243e0:	8de10008 */ 	lw	$at,0x8($t7)
/*  f0243e4:	ad380004 */ 	sw	$t8,0x4($t1)
/*  f0243e8:	ad210008 */ 	sw	$at,0x8($t1)
/*  f0243ec:	0fc22f08 */ 	jal	hatGetType
/*  f0243f0:	8e040178 */ 	lw	$a0,0x178($s0)
/*  f0243f4:	afa20058 */ 	sw	$v0,0x58($sp)
/*  f0243f8:	82060006 */ 	lb	$a2,0x6($s0)
/*  f0243fc:	3c017f1b */ 	lui	$at,0x7f1b
/*  f024400:	c43299ec */ 	lwc1	$f18,-0x6614($at)
/*  f024404:	24c6ffd6 */ 	addiu	$a2,$a2,-42
/*  f024408:	000640c0 */ 	sll	$t0,$a2,0x3
/*  f02440c:	01064021 */ 	addu	$t0,$t0,$a2
/*  f024410:	0002c880 */ 	sll	$t9,$v0,0x2
/*  f024414:	00084100 */ 	sll	$t0,$t0,0x4
/*  f024418:	0322c823 */ 	subu	$t9,$t9,$v0
/*  f02441c:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f024420:	3c0b8008 */ 	lui	$t3,0x8008
/*  f024424:	01197021 */ 	addu	$t6,$t0,$t9
/*  f024428:	256bdfb4 */ 	addiu	$t3,$t3,-8268
/*  f02442c:	01cb1821 */ 	addu	$v1,$t6,$t3
/*  f024430:	c4700000 */ 	lwc1	$f16,0x0($v1)
/*  f024434:	c46e0004 */ 	lwc1	$f14,0x4($v1)
/*  f024438:	c46c0008 */ 	lwc1	$f12,0x8($v1)
/*  f02443c:	46128402 */ 	mul.s	$f16,$f16,$f18
/*  f024440:	c46a000c */ 	lwc1	$f10,0xc($v1)
/*  f024444:	c4680010 */ 	lwc1	$f8,0x10($v1)
/*  f024448:	46127382 */ 	mul.s	$f14,$f14,$f18
/*  f02444c:	c4660014 */ 	lwc1	$f6,0x14($v1)
/*  f024450:	e7aa00e4 */ 	swc1	$f10,0xe4($sp)
/*  f024454:	46126482 */ 	mul.s	$f18,$f12,$f18
/*  f024458:	e7b000e8 */ 	swc1	$f16,0xe8($sp)
/*  f02445c:	e7a800e0 */ 	swc1	$f8,0xe0($sp)
/*  f024460:	e7a600dc */ 	swc1	$f6,0xdc($sp)
/*  f024464:	e7ae00ec */ 	swc1	$f14,0xec($sp)
/*  f024468:	27a400e8 */ 	addiu	$a0,$sp,0xe8
/*  f02446c:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f024470:	0c00591b */ 	jal	func000166dc
/*  f024474:	e7b200f0 */ 	swc1	$f18,0xf0($sp)
/*  f024478:	c7ac00e4 */ 	lwc1	$f12,0xe4($sp)
/*  f02447c:	0c0056ed */ 	jal	func00015e24
/*  f024480:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f024484:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
/*  f024488:	0c005704 */ 	jal	func00015e80
/*  f02448c:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f024490:	c7ac00dc */ 	lwc1	$f12,0xdc($sp)
/*  f024494:	0c00571b */ 	jal	func00015edc
/*  f024498:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f02449c:	8faa00f4 */ 	lw	$t2,0xf4($sp)
/*  f0244a0:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f0244a4:	27a6005c */ 	addiu	$a2,$sp,0x5c
/*  f0244a8:	0c00565d */ 	jal	func00015be4
/*  f0244ac:	8d44000c */ 	lw	$a0,0xc($t2)
/*  f0244b0:	8fac00f4 */ 	lw	$t4,0xf4($sp)
/*  f0244b4:	27a4005c */ 	addiu	$a0,$sp,0x5c
/*  f0244b8:	0c0056aa */ 	jal	func00015d18
/*  f0244bc:	8d85000c */ 	lw	$a1,0xc($t4)
/*  f0244c0:	8fad0058 */ 	lw	$t5,0x58($sp)
/*  f0244c4:	24010002 */ 	li	$at,0x2
/*  f0244c8:	55a10003 */ 	bnel	$t5,$at,.PF0f0244d8
/*  f0244cc:	8fa90208 */ 	lw	$t1,0x208($sp)
/*  f0244d0:	afa00200 */ 	sw	$zero,0x200($sp)
.PF0f0244d4:
/*  f0244d4:	8fa90208 */ 	lw	$t1,0x208($sp)
.PF0f0244d8:
/*  f0244d8:	3c0f8008 */ 	lui	$t7,0x8008
/*  f0244dc:	25efd310 */ 	addiu	$t7,$t7,-11504
/*  f0244e0:	8d240008 */ 	lw	$a0,0x8($t1)
/*  f0244e4:	8c980004 */ 	lw	$t8,0x4($a0)
/*  f0244e8:	55f8003e */ 	bnel	$t7,$t8,.PF0f0245e4
/*  f0244ec:	8fac01f0 */ 	lw	$t4,0x1f0($sp)
/*  f0244f0:	0c0069ab */ 	jal	modelGetPart
/*  f0244f4:	24050004 */ 	li	$a1,0x4
/*  f0244f8:	10400039 */ 	beqz	$v0,.PF0f0245e0
/*  f0244fc:	00402825 */ 	move	$a1,$v0
/*  f024500:	94480000 */ 	lhu	$t0,0x0($v0)
/*  f024504:	24010017 */ 	li	$at,0x17
/*  f024508:	55010036 */ 	bnel	$t0,$at,.PF0f0245e4
/*  f02450c:	8fac01f0 */ 	lw	$t4,0x1f0($sp)
/*  f024510:	0c0069eb */ 	jal	modelGetNodeRwData
/*  f024514:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f024518:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02451c:	24050001 */ 	li	$a1,0x1
/*  f024520:	53200030 */ 	beqzl	$t9,.PF0f0245e4
/*  f024524:	8fac01f0 */ 	lw	$t4,0x1f0($sp)
/*  f024528:	0c0069ab */ 	jal	modelGetPart
/*  f02452c:	8c440000 */ 	lw	$a0,0x0($v0)
/*  f024530:	1040002b */ 	beqz	$v0,.PF0f0245e0
/*  f024534:	00402825 */ 	move	$a1,$v0
/*  f024538:	0c0069eb */ 	jal	modelGetNodeRwData
/*  f02453c:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f024540:	8fae0200 */ 	lw	$t6,0x200($sp)
/*  f024544:	10000026 */ 	b	.PF0f0245e0
/*  f024548:	ac4e0000 */ 	sw	$t6,0x0($v0)
.PF0f02454c:
/*  f02454c:	304bfffd */ 	andi	$t3,$v0,0xfffd
/*  f024550:	a14b0001 */ 	sb	$t3,0x1($t2)
/*  f024554:	3c0c800a */ 	lui	$t4,0x800a
/*  f024558:	8d8ca7ac */ 	lw	$t4,-0x5854($t4)
/*  f02455c:	3c0d800a */ 	lui	$t5,0x800a
/*  f024560:	3c09800a */ 	lui	$t1,0x800a
/*  f024564:	0582000b */ 	bltzl	$t4,.PF0f024594
/*  f024568:	8fa80250 */ 	lw	$t0,0x250($sp)
/*  f02456c:	8dada7b0 */ 	lw	$t5,-0x5850($t5)
/*  f024570:	8d29a794 */ 	lw	$t1,-0x586c($t1)
/*  f024574:	55a90007 */ 	bnel	$t5,$t1,.PF0f024594
/*  f024578:	8fa80250 */ 	lw	$t0,0x250($sp)
/*  f02457c:	8e0f0014 */ 	lw	$t7,0x14($s0)
/*  f024580:	3c01ff7f */ 	lui	$at,0xff7f
/*  f024584:	3421ffff */ 	ori	$at,$at,0xffff
/*  f024588:	01e1c024 */ 	and	$t8,$t7,$at
/*  f02458c:	ae180014 */ 	sw	$t8,0x14($s0)
/*  f024590:	8fa80250 */ 	lw	$t0,0x250($sp)
.PF0f024594:
/*  f024594:	8d07001c */ 	lw	$a3,0x1c($t0)
/*  f024598:	50e0000a */ 	beqzl	$a3,.PF0f0245c4
/*  f02459c:	921900fc */ 	lbu	$t9,0xfc($s0)
/*  f0245a0:	8ce20020 */ 	lw	$v0,0x20($a3)
.PF0f0245a4:
/*  f0245a4:	00e02025 */ 	move	$a0,$a3
/*  f0245a8:	8fa501f0 */ 	lw	$a1,0x1f0($sp)
/*  f0245ac:	0fc1c260 */ 	jal	func0f0706f8
/*  f0245b0:	afa201f4 */ 	sw	$v0,0x1f4($sp)
/*  f0245b4:	8fa701f4 */ 	lw	$a3,0x1f4($sp)
/*  f0245b8:	54e0fffa */ 	bnezl	$a3,.PF0f0245a4
/*  f0245bc:	8ce20020 */ 	lw	$v0,0x20($a3)
/*  f0245c0:	921900fc */ 	lbu	$t9,0xfc($s0)
.PF0f0245c4:
/*  f0245c4:	920e00fd */ 	lbu	$t6,0xfd($s0)
/*  f0245c8:	920b00fe */ 	lbu	$t3,0xfe($s0)
/*  f0245cc:	920a00ff */ 	lbu	$t2,0xff($s0)
/*  f0245d0:	a21900f8 */ 	sb	$t9,0xf8($s0)
/*  f0245d4:	a20e00f9 */ 	sb	$t6,0xf9($s0)
/*  f0245d8:	a20b00fa */ 	sb	$t3,0xfa($s0)
/*  f0245dc:	a20a00fb */ 	sb	$t2,0xfb($s0)
.PF0f0245e0:
/*  f0245e0:	8fac01f0 */ 	lw	$t4,0x1f0($sp)
.PF0f0245e4:
/*  f0245e4:	51800013 */ 	beqzl	$t4,.PF0f024634
/*  f0245e8:	00001025 */ 	move	$v0,$zero
/*  f0245ec:	8e0d0018 */ 	lw	$t5,0x18($s0)
/*  f0245f0:	31a90400 */ 	andi	$t1,$t5,0x400
/*  f0245f4:	5520000f */ 	bnezl	$t1,.PF0f024634
/*  f0245f8:	00001025 */ 	move	$v0,$zero
/*  f0245fc:	8e0f0014 */ 	lw	$t7,0x14($s0)
/*  f024600:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f024604:	31f80001 */ 	andi	$t8,$t7,0x1
/*  f024608:	13000007 */ 	beqz	$t8,.PF0f024628
/*  f02460c:	00000000 */ 	nop
/*  f024610:	0fc1c248 */ 	jal	func0f070698
/*  f024614:	00002825 */ 	move	$a1,$zero
/*  f024618:	8e080014 */ 	lw	$t0,0x14($s0)
/*  f02461c:	2401fffe */ 	li	$at,-2
/*  f024620:	0101c824 */ 	and	$t9,$t0,$at
/*  f024624:	ae190014 */ 	sw	$t9,0x14($s0)
.PF0f024628:
/*  f024628:	0fc10706 */ 	jal	func0f041a74
/*  f02462c:	02002025 */ 	move	$a0,$s0
/*  f024630:	00001025 */ 	move	$v0,$zero
.PF0f024634:
/*  f024634:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f024638:	8fb00020 */ 	lw	$s0,0x20($sp)
/*  f02463c:	27bd0250 */ 	addiu	$sp,$sp,0x250
/*  f024640:	03e00008 */ 	jr	$ra
/*  f024644:	00000000 */ 	nop
);
#elif VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func0f023098
.late_rodata
glabel var7f1a87bc
.word 0x40c907a9
glabel var7f1a87c0
.word 0x3d333333
glabel var7f1a87c4
.word 0x3d333333
glabel var7f1a87c8
.word 0x4a742400
glabel var7f1a87cc
.word 0x48ef4200
glabel var7f1a87d0
.word 0x4a742400
glabel var7f1a87d4
.word 0x48ef4200
glabel var7f1a87d8
.word 0x41aa6666
.text
/*  f023098:	27bdfdb0 */ 	addiu	$sp,$sp,-592
/*  f02309c:	3c0f8006 */ 	lui	$t7,%hi(var800629fc)
/*  f0230a0:	25ef29fc */ 	addiu	$t7,$t7,%lo(var800629fc)
/*  f0230a4:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f0230a8:	afb00020 */ 	sw	$s0,0x20($sp)
/*  f0230ac:	afa40250 */ 	sw	$a0,0x250($sp)
/*  f0230b0:	25e8003c */ 	addiu	$t0,$t7,0x3c
/*  f0230b4:	27ae0210 */ 	addiu	$t6,$sp,0x210
.L0f0230b8:
/*  f0230b8:	8de10000 */ 	lw	$at,0x0($t7)
/*  f0230bc:	25ef000c */ 	addiu	$t7,$t7,0xc
/*  f0230c0:	25ce000c */ 	addiu	$t6,$t6,0xc
/*  f0230c4:	adc1fff4 */ 	sw	$at,-0xc($t6)
/*  f0230c8:	8de1fff8 */ 	lw	$at,-0x8($t7)
/*  f0230cc:	adc1fff8 */ 	sw	$at,-0x8($t6)
/*  f0230d0:	8de1fffc */ 	lw	$at,-0x4($t7)
/*  f0230d4:	15e8fff8 */ 	bne	$t7,$t0,.L0f0230b8
/*  f0230d8:	adc1fffc */ 	sw	$at,-0x4($t6)
/*  f0230dc:	8de10000 */ 	lw	$at,0x0($t7)
/*  f0230e0:	3c0c800a */ 	lui	$t4,%hi(g_Vars+0x34)
/*  f0230e4:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f0230e8:	adc10000 */ 	sw	$at,0x0($t6)
/*  f0230ec:	8fa90250 */ 	lw	$t1,0x250($sp)
/*  f0230f0:	8d8c9ff4 */ 	lw	$t4,%lo(g_Vars+0x34)($t4)
/*  f0230f4:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f0230f8:	8d300004 */ 	lw	$s0,0x4($t1)
/*  f0230fc:	8e0a0020 */ 	lw	$t2,0x20($s0)
/*  f023100:	afab0200 */ 	sw	$t3,0x200($sp)
/*  f023104:	afa001f0 */ 	sw	$zero,0x1f0($sp)
/*  f023108:	afac01fc */ 	sw	$t4,0x1fc($sp)
/*  f02310c:	12000004 */ 	beqz	$s0,.L0f023120
/*  f023110:	afaa0208 */ 	sw	$t2,0x208($sp)
/*  f023114:	920d02fe */ 	lbu	$t5,0x2fe($s0)
/*  f023118:	10000002 */ 	b	.L0f023124
/*  f02311c:	afad01ec */ 	sw	$t5,0x1ec($sp)
.L0f023120:
/*  f023120:	afa001ec */ 	sw	$zero,0x1ec($sp)
.L0f023124:
/*  f023124:	8fb90250 */ 	lw	$t9,0x250($sp)
/*  f023128:	3c0c800a */ 	lui	$t4,%hi(g_Vars+0x4cc)
/*  f02312c:	93220001 */ 	lbu	$v0,0x1($t9)
/*  f023130:	30580008 */ 	andi	$t8,$v0,0x8
/*  f023134:	13000003 */ 	beqz	$t8,.L0f023144
/*  f023138:	304ffff7 */ 	andi	$t7,$v0,0xfff7
/*  f02313c:	afa801f0 */ 	sw	$t0,0x1f0($sp)
/*  f023140:	a32f0001 */ 	sb	$t7,0x1($t9)
.L0f023144:
/*  f023144:	8fae01f0 */ 	lw	$t6,0x1f0($sp)
/*  f023148:	51c000bd */ 	beqzl	$t6,.L0f023440
/*  f02314c:	8fad01ec */ 	lw	$t5,0x1ec($sp)
/*  f023150:	92020291 */ 	lbu	$v0,0x291($s0)
/*  f023154:	18400007 */ 	blez	$v0,.L0f023174
/*  f023158:	00000000 */ 	nop
/*  f02315c:	8e090014 */ 	lw	$t1,0x14($s0)
/*  f023160:	244bffff */ 	addiu	$t3,$v0,-1
/*  f023164:	312a0010 */ 	andi	$t2,$t1,0x10
/*  f023168:	15400002 */ 	bnez	$t2,.L0f023174
/*  f02316c:	00000000 */ 	nop
/*  f023170:	a20b0291 */ 	sb	$t3,0x291($s0)
.L0f023174:
/*  f023174:	8d8ca48c */ 	lw	$t4,%lo(g_Vars+0x4cc)($t4)
/*  f023178:	51800006 */ 	beqzl	$t4,.L0f023194
/*  f02317c:	860d02d8 */ 	lh	$t5,0x2d8($s0)
/*  f023180:	44802000 */ 	mtc1	$zero,$f4
/*  f023184:	a20002e0 */ 	sb	$zero,0x2e0($s0)
/*  f023188:	1000005d */ 	b	.L0f023300
/*  f02318c:	e60402dc */ 	swc1	$f4,0x2dc($s0)
/*  f023190:	860d02d8 */ 	lh	$t5,0x2d8($s0)
.L0f023194:
/*  f023194:	29a103e9 */ 	slti	$at,$t5,0x3e9
/*  f023198:	54200022 */ 	bnezl	$at,.L0f023224
/*  f02319c:	c60002dc */ 	lwc1	$f0,0x2dc($s0)
/*  f0231a0:	82180007 */ 	lb	$t8,0x7($s0)
/*  f0231a4:	2401001f */ 	addiu	$at,$zero,0x1f
/*  f0231a8:	3c0f800a */ 	lui	$t7,%hi(g_Vars+0x34)
/*  f0231ac:	5301001d */ 	beql	$t8,$at,.L0f023224
/*  f0231b0:	c60002dc */ 	lwc1	$f0,0x2dc($s0)
/*  f0231b4:	8def9ff4 */ 	lw	$t7,%lo(g_Vars+0x34)($t7)
/*  f0231b8:	920802e0 */ 	lbu	$t0,0x2e0($s0)
/*  f0231bc:	3c014f80 */ 	lui	$at,0x4f80
/*  f0231c0:	000fc843 */ 	sra	$t9,$t7,0x1
/*  f0231c4:	01197021 */ 	addu	$t6,$t0,$t9
/*  f0231c8:	31c900ff */ 	andi	$t1,$t6,0xff
/*  f0231cc:	44893000 */ 	mtc1	$t1,$f6
/*  f0231d0:	a20e02e0 */ 	sb	$t6,0x2e0($s0)
/*  f0231d4:	05210004 */ 	bgez	$t1,.L0f0231e8
/*  f0231d8:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f0231dc:	44815000 */ 	mtc1	$at,$f10
/*  f0231e0:	00000000 */ 	nop
/*  f0231e4:	460a4200 */ 	add.s	$f8,$f8,$f10
.L0f0231e8:
/*  f0231e8:	3c01437f */ 	lui	$at,0x437f
/*  f0231ec:	44819000 */ 	mtc1	$at,$f18
/*  f0231f0:	3c017f1b */ 	lui	$at,%hi(var7f1a87bc)
/*  f0231f4:	c42687bc */ 	lwc1	$f6,%lo(var7f1a87bc)($at)
/*  f0231f8:	46124103 */ 	div.s	$f4,$f8,$f18
/*  f0231fc:	46062302 */ 	mul.s	$f12,$f4,$f6
/*  f023200:	0c0068f4 */ 	jal	cosf
/*  f023204:	00000000 */ 	nop
/*  f023208:	3c0141a0 */ 	lui	$at,0x41a0
/*  f02320c:	44815000 */ 	mtc1	$at,$f10
/*  f023210:	00000000 */ 	nop
/*  f023214:	460a0202 */ 	mul.s	$f8,$f0,$f10
/*  f023218:	10000039 */ 	b	.L0f023300
/*  f02321c:	e60802dc */ 	swc1	$f8,0x2dc($s0)
/*  f023220:	c60002dc */ 	lwc1	$f0,0x2dc($s0)
.L0f023224:
/*  f023224:	44809000 */ 	mtc1	$zero,$f18
/*  f023228:	00000000 */ 	nop
/*  f02322c:	46009032 */ 	c.eq.s	$f18,$f0
/*  f023230:	00000000 */ 	nop
/*  f023234:	45010032 */ 	bc1t	.L0f023300
/*  f023238:	00000000 */ 	nop
/*  f02323c:	44802000 */ 	mtc1	$zero,$f4
/*  f023240:	a20002e0 */ 	sb	$zero,0x2e0($s0)
/*  f023244:	3c0a800a */ 	lui	$t2,%hi(g_Vars+0x34)
/*  f023248:	4600203c */ 	c.lt.s	$f4,$f0
/*  f02324c:	00000000 */ 	nop
/*  f023250:	45020014 */ 	bc1fl	.L0f0232a4
/*  f023254:	44809000 */ 	mtc1	$zero,$f18
/*  f023258:	8d4a9ff4 */ 	lw	$t2,%lo(g_Vars+0x34)($t2)
/*  f02325c:	3c017f1b */ 	lui	$at,%hi(var7f1a87c0)
/*  f023260:	c42687c0 */ 	lwc1	$f6,%lo(var7f1a87c0)($at)
/*  f023264:	448a5000 */ 	mtc1	$t2,$f10
/*  f023268:	00000000 */ 	nop
/*  f02326c:	46805220 */ 	cvt.s.w	$f8,$f10
/*  f023270:	46083482 */ 	mul.s	$f18,$f6,$f8
/*  f023274:	44803000 */ 	mtc1	$zero,$f6
/*  f023278:	46120101 */ 	sub.s	$f4,$f0,$f18
/*  f02327c:	e60402dc */ 	swc1	$f4,0x2dc($s0)
/*  f023280:	c60a02dc */ 	lwc1	$f10,0x2dc($s0)
/*  f023284:	4606503c */ 	c.lt.s	$f10,$f6
/*  f023288:	00000000 */ 	nop
/*  f02328c:	4500001c */ 	bc1f	.L0f023300
/*  f023290:	00000000 */ 	nop
/*  f023294:	44804000 */ 	mtc1	$zero,$f8
/*  f023298:	10000019 */ 	b	.L0f023300
/*  f02329c:	e60802dc */ 	swc1	$f8,0x2dc($s0)
/*  f0232a0:	44809000 */ 	mtc1	$zero,$f18
.L0f0232a4:
/*  f0232a4:	3c0b800a */ 	lui	$t3,%hi(g_Vars+0x34)
/*  f0232a8:	4612003c */ 	c.lt.s	$f0,$f18
/*  f0232ac:	00000000 */ 	nop
/*  f0232b0:	45000013 */ 	bc1f	.L0f023300
/*  f0232b4:	00000000 */ 	nop
/*  f0232b8:	8d6b9ff4 */ 	lw	$t3,%lo(g_Vars+0x34)($t3)
/*  f0232bc:	3c017f1b */ 	lui	$at,%hi(var7f1a87c4)
/*  f0232c0:	c42487c4 */ 	lwc1	$f4,%lo(var7f1a87c4)($at)
/*  f0232c4:	448b5000 */ 	mtc1	$t3,$f10
/*  f0232c8:	00000000 */ 	nop
/*  f0232cc:	468051a0 */ 	cvt.s.w	$f6,$f10
/*  f0232d0:	44805000 */ 	mtc1	$zero,$f10
/*  f0232d4:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f0232d8:	46080480 */ 	add.s	$f18,$f0,$f8
/*  f0232dc:	e61202dc */ 	swc1	$f18,0x2dc($s0)
/*  f0232e0:	c60402dc */ 	lwc1	$f4,0x2dc($s0)
/*  f0232e4:	4604503c */ 	c.lt.s	$f10,$f4
/*  f0232e8:	00000000 */ 	nop
/*  f0232ec:	45000004 */ 	bc1f	.L0f023300
/*  f0232f0:	00000000 */ 	nop
/*  f0232f4:	44803000 */ 	mtc1	$zero,$f6
/*  f0232f8:	00000000 */ 	nop
/*  f0232fc:	e60602dc */ 	swc1	$f6,0x2dc($s0)
.L0f023300:
/*  f023300:	0fc08989 */ 	jal	chrUpdateCloak
/*  f023304:	02002025 */ 	or	$a0,$s0,$zero
/*  f023308:	0fc08b58 */ 	jal	chrTickPoisoned
/*  f02330c:	02002025 */ 	or	$a0,$s0,$zero
/*  f023310:	8e020018 */ 	lw	$v0,0x18($s0)
/*  f023314:	3c188006 */ 	lui	$t8,%hi(var8006296c)
/*  f023318:	304c0400 */ 	andi	$t4,$v0,0x400
/*  f02331c:	11800003 */ 	beqz	$t4,.L0f02332c
/*  f023320:	00026b40 */ 	sll	$t5,$v0,0xd
/*  f023324:	05a30039 */ 	bgezl	$t5,.L0f02340c
/*  f023328:	8e020014 */ 	lw	$v0,0x14($s0)
.L0f02332c:
/*  f02332c:	8f18296c */ 	lw	$t8,%lo(var8006296c)($t8)
/*  f023330:	3c048006 */ 	lui	$a0,%hi(g_SelectedAnimNum+0x2)
/*  f023334:	13000022 */ 	beqz	$t8,.L0f0233c0
/*  f023338:	00000000 */ 	nop
/*  f02333c:	0c008de5 */ 	jal	func00023794
/*  f023340:	84842972 */ 	lh	$a0,%lo(g_SelectedAnimNum+0x2)($a0)
/*  f023344:	10400025 */ 	beqz	$v0,.L0f0233dc
/*  f023348:	00000000 */ 	nop
/*  f02334c:	0c00744f */ 	jal	modelGetAnimNum
/*  f023350:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023354:	3c038006 */ 	lui	$v1,%hi(g_SelectedAnimNum)
/*  f023358:	8c632970 */ 	lw	$v1,%lo(g_SelectedAnimNum)($v1)
/*  f02335c:	5443000b */ 	bnel	$v0,$v1,.L0f02338c
/*  f023360:	44800000 */ 	mtc1	$zero,$f0
/*  f023364:	0c00744f */ 	jal	modelGetAnimNum
/*  f023368:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f02336c:	00022400 */ 	sll	$a0,$v0,0x10
/*  f023370:	00047c03 */ 	sra	$t7,$a0,0x10
/*  f023374:	0c008de5 */ 	jal	func00023794
/*  f023378:	01e02025 */ 	or	$a0,$t7,$zero
/*  f02337c:	14400017 */ 	bnez	$v0,.L0f0233dc
/*  f023380:	3c038006 */ 	lui	$v1,%hi(g_SelectedAnimNum)
/*  f023384:	8c632970 */ 	lw	$v1,%lo(g_SelectedAnimNum)($v1)
/*  f023388:	44800000 */ 	mtc1	$zero,$f0
.L0f02338c:
/*  f02338c:	3c013f00 */ 	lui	$at,0x3f00
/*  f023390:	44814000 */ 	mtc1	$at,$f8
/*  f023394:	00032c00 */ 	sll	$a1,$v1,0x10
/*  f023398:	00054403 */ 	sra	$t0,$a1,0x10
/*  f02339c:	44070000 */ 	mfc1	$a3,$f0
/*  f0233a0:	01002825 */ 	or	$a1,$t0,$zero
/*  f0233a4:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0233a8:	00003025 */ 	or	$a2,$zero,$zero
/*  f0233ac:	e7a00014 */ 	swc1	$f0,0x14($sp)
/*  f0233b0:	0c007733 */ 	jal	modelSetAnimation
/*  f0233b4:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*  f0233b8:	10000008 */ 	b	.L0f0233dc
/*  f0233bc:	00000000 */ 	nop
.L0f0233c0:
/*  f0233c0:	0fc11f20 */ 	jal	chrTick
/*  f0233c4:	02002025 */ 	or	$a0,$s0,$zero
/*  f0233c8:	8e190020 */ 	lw	$t9,0x20($s0)
/*  f0233cc:	17200003 */ 	bnez	$t9,.L0f0233dc
/*  f0233d0:	00000000 */ 	nop
/*  f0233d4:	1000044e */ 	b	.L0f024510
/*  f0233d8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f0233dc:
/*  f0233dc:	3c0e8006 */ 	lui	$t6,%hi(var80062974)
/*  f0233e0:	8dce2974 */ 	lw	$t6,%lo(var80062974)($t6)
/*  f0233e4:	3c098006 */ 	lui	$t1,%hi(var80062978)
/*  f0233e8:	51c00008 */ 	beqzl	$t6,.L0f02340c
/*  f0233ec:	8e020014 */ 	lw	$v0,0x14($s0)
/*  f0233f0:	8d292978 */ 	lw	$t1,%lo(var80062978)($t1)
/*  f0233f4:	afa001fc */ 	sw	$zero,0x1fc($sp)
/*  f0233f8:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f0233fc:	51200003 */ 	beqzl	$t1,.L0f02340c
/*  f023400:	8e020014 */ 	lw	$v0,0x14($s0)
/*  f023404:	afaa01fc */ 	sw	$t2,0x1fc($sp)
/*  f023408:	8e020014 */ 	lw	$v0,0x14($s0)
.L0f02340c:
/*  f02340c:	304b0020 */ 	andi	$t3,$v0,0x20
/*  f023410:	1160000a */ 	beqz	$t3,.L0f02343c
/*  f023414:	304c0001 */ 	andi	$t4,$v0,0x1
/*  f023418:	11800003 */ 	beqz	$t4,.L0f023428
/*  f02341c:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023420:	0fc1c1a6 */ 	jal	func0f070698
/*  f023424:	24050001 */ 	addiu	$a1,$zero,0x1
.L0f023428:
/*  f023428:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f02342c:	0fc08351 */ 	jal	func0f020d44
/*  f023430:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f023434:	10000436 */ 	b	.L0f024510
/*  f023438:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f02343c:
/*  f02343c:	8fad01ec */ 	lw	$t5,0x1ec($sp)
.L0f023440:
/*  f023440:	24010003 */ 	addiu	$at,$zero,0x3
/*  f023444:	55a10026 */ 	bnel	$t5,$at,.L0f0234e0
/*  f023448:	8e020018 */ 	lw	$v0,0x18($s0)
/*  f02344c:	0fc0f011 */ 	jal	chrToEyespy
/*  f023450:	02002025 */ 	or	$a0,$s0,$zero
/*  f023454:	1040001f */ 	beqz	$v0,.L0f0234d4
/*  f023458:	00000000 */ 	nop
/*  f02345c:	90580035 */ 	lbu	$t8,0x35($v0)
/*  f023460:	3c0f800a */ 	lui	$t7,%hi(g_Vars+0x284)
/*  f023464:	1300001b */ 	beqz	$t8,.L0f0234d4
/*  f023468:	00000000 */ 	nop
/*  f02346c:	8defa244 */ 	lw	$t7,%lo(g_Vars+0x284)($t7)
/*  f023470:	8de80480 */ 	lw	$t0,0x480($t7)
/*  f023474:	14480006 */ 	bne	$v0,$t0,.L0f023490
/*  f023478:	00000000 */ 	nop
/*  f02347c:	80590037 */ 	lb	$t9,0x37($v0)
/*  f023480:	13200003 */ 	beqz	$t9,.L0f023490
/*  f023484:	00000000 */ 	nop
/*  f023488:	10000009 */ 	b	.L0f0234b0
/*  f02348c:	00003825 */ 	or	$a3,$zero,$zero
.L0f023490:
/*  f023490:	0c006be0 */ 	jal	func0001af80
/*  f023494:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023498:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f02349c:	44060000 */ 	mfc1	$a2,$f0
/*  f0234a0:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f0234a4:	0fc23a2b */ 	jal	func0f08e8ac
/*  f0234a8:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f0234ac:	00403825 */ 	or	$a3,$v0,$zero
.L0f0234b0:
/*  f0234b0:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
/*  f0234b4:	02002025 */ 	or	$a0,$s0,$zero
/*  f0234b8:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0234bc:	112001c9 */ 	beqz	$t1,.L0f023be4
/*  f0234c0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0234c4:	0fc0883b */ 	jal	func0f0220ec
/*  f0234c8:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f0234cc:	100001c5 */ 	b	.L0f023be4
/*  f0234d0:	8fa70204 */ 	lw	$a3,0x204($sp)
.L0f0234d4:
/*  f0234d4:	100001c3 */ 	b	.L0f023be4
/*  f0234d8:	00003825 */ 	or	$a3,$zero,$zero
/*  f0234dc:	8e020018 */ 	lw	$v0,0x18($s0)
.L0f0234e0:
/*  f0234e0:	304a0400 */ 	andi	$t2,$v0,0x400
/*  f0234e4:	11400003 */ 	beqz	$t2,.L0f0234f4
/*  f0234e8:	00025a00 */ 	sll	$t3,$v0,0x8
/*  f0234ec:	100001bd */ 	b	.L0f023be4
/*  f0234f0:	00003825 */ 	or	$a3,$zero,$zero
.L0f0234f4:
/*  f0234f4:	05600017 */ 	bltz	$t3,.L0f023554
/*  f0234f8:	8fac0250 */ 	lw	$t4,0x250($sp)
/*  f0234fc:	918d0000 */ 	lbu	$t5,0x0($t4)
/*  f023500:	24010006 */ 	addiu	$at,$zero,0x6
/*  f023504:	55a10068 */ 	bnel	$t5,$at,.L0f0236a8
/*  f023508:	82030007 */ 	lb	$v1,0x7($s0)
/*  f02350c:	0fc4a25f */ 	jal	propGetPlayerNum
/*  f023510:	01802025 */ 	or	$a0,$t4,$zero
/*  f023514:	0002c080 */ 	sll	$t8,$v0,0x2
/*  f023518:	3c03800a */ 	lui	$v1,%hi(g_Vars+0x64)
/*  f02351c:	00781821 */ 	addu	$v1,$v1,$t8
/*  f023520:	3c0f800a */ 	lui	$t7,%hi(g_Vars+0x284)
/*  f023524:	8defa244 */ 	lw	$t7,%lo(g_Vars+0x284)($t7)
/*  f023528:	8c63a024 */ 	lw	$v1,%lo(g_Vars+0x64)($v1)
/*  f02352c:	546f005e */ 	bnel	$v1,$t7,.L0f0236a8
/*  f023530:	82030007 */ 	lb	$v1,0x7($s0)
/*  f023534:	8c680000 */ 	lw	$t0,0x0($v1)
/*  f023538:	24010001 */ 	addiu	$at,$zero,0x1
/*  f02353c:	5501005a */ 	bnel	$t0,$at,.L0f0236a8
/*  f023540:	82030007 */ 	lb	$v1,0x7($s0)
/*  f023544:	94790010 */ 	lhu	$t9,0x10($v1)
/*  f023548:	24010002 */ 	addiu	$at,$zero,0x2
/*  f02354c:	53210056 */ 	beql	$t9,$at,.L0f0236a8
/*  f023550:	82030007 */ 	lb	$v1,0x7($s0)
.L0f023554:
/*  f023554:	8fae01f0 */ 	lw	$t6,0x1f0($sp)
/*  f023558:	00003825 */ 	or	$a3,$zero,$zero
/*  f02355c:	8fa90208 */ 	lw	$t1,0x208($sp)
/*  f023560:	51c0001b */ 	beqzl	$t6,.L0f0235d0
/*  f023564:	8e030020 */ 	lw	$v1,0x20($s0)
/*  f023568:	8d2a0020 */ 	lw	$t2,0x20($t1)
/*  f02356c:	24010003 */ 	addiu	$at,$zero,0x3
/*  f023570:	02002025 */ 	or	$a0,$s0,$zero
/*  f023574:	a140000b */ 	sb	$zero,0xb($t2)
/*  f023578:	820b0007 */ 	lb	$t3,0x7($s0)
/*  f02357c:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023580:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f023584:	1561000e */ 	bne	$t3,$at,.L0f0235c0
/*  f023588:	00000000 */ 	nop
/*  f02358c:	8e0d002c */ 	lw	$t5,0x2c($s0)
/*  f023590:	15a0000b */ 	bnez	$t5,.L0f0235c0
/*  f023594:	00000000 */ 	nop
/*  f023598:	8e0c003c */ 	lw	$t4,0x3c($s0)
/*  f02359c:	11800008 */ 	beqz	$t4,.L0f0235c0
/*  f0235a0:	00000000 */ 	nop
/*  f0235a4:	02002025 */ 	or	$a0,$s0,$zero
/*  f0235a8:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0235ac:	00003025 */ 	or	$a2,$zero,$zero
/*  f0235b0:	0fc0883b */ 	jal	func0f0220ec
/*  f0235b4:	afa001a0 */ 	sw	$zero,0x1a0($sp)
/*  f0235b8:	10000004 */ 	b	.L0f0235cc
/*  f0235bc:	8fa701a0 */ 	lw	$a3,0x1a0($sp)
.L0f0235c0:
/*  f0235c0:	0fc0883b */ 	jal	func0f0220ec
/*  f0235c4:	afa701a0 */ 	sw	$a3,0x1a0($sp)
/*  f0235c8:	8fa701a0 */ 	lw	$a3,0x1a0($sp)
.L0f0235cc:
/*  f0235cc:	8e030020 */ 	lw	$v1,0x20($s0)
.L0f0235d0:
/*  f0235d0:	1060002c */ 	beqz	$v1,.L0f023684
/*  f0235d4:	00000000 */ 	nop
/*  f0235d8:	8c620020 */ 	lw	$v0,0x20($v1)
/*  f0235dc:	10400029 */ 	beqz	$v0,.L0f023684
/*  f0235e0:	00000000 */ 	nop
/*  f0235e4:	84440000 */ 	lh	$a0,0x0($v0)
/*  f0235e8:	3c188006 */ 	lui	$t8,%hi(g_Anims)
/*  f0235ec:	8f18f00c */ 	lw	$t8,%lo(g_Anims)($t8)
/*  f0235f0:	00047880 */ 	sll	$t7,$a0,0x2
/*  f0235f4:	01e47823 */ 	subu	$t7,$t7,$a0
/*  f0235f8:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f0235fc:	030f4021 */ 	addu	$t0,$t8,$t7
/*  f023600:	9119000b */ 	lbu	$t9,0xb($t0)
/*  f023604:	332e0004 */ 	andi	$t6,$t9,0x4
/*  f023608:	11c0001e */ 	beqz	$t6,.L0f023684
/*  f02360c:	00000000 */ 	nop
/*  f023610:	0c008f4e */ 	jal	func00023d38
/*  f023614:	00000000 */ 	nop
/*  f023618:	8e090020 */ 	lw	$t1,0x20($s0)
/*  f02361c:	8d220020 */ 	lw	$v0,0x20($t1)
/*  f023620:	84440000 */ 	lh	$a0,0x0($v0)
/*  f023624:	0c008e13 */ 	jal	func0002384c
/*  f023628:	84450014 */ 	lh	$a1,0x14($v0)
/*  f02362c:	28440000 */ 	slti	$a0,$v0,0x0
/*  f023630:	54800014 */ 	bnezl	$a0,.L0f023684
/*  f023634:	00803825 */ 	or	$a3,$a0,$zero
/*  f023638:	8e0a0020 */ 	lw	$t2,0x20($s0)
/*  f02363c:	8d420020 */ 	lw	$v0,0x20($t2)
/*  f023640:	84440000 */ 	lh	$a0,0x0($v0)
/*  f023644:	0c008e13 */ 	jal	func0002384c
/*  f023648:	84450016 */ 	lh	$a1,0x16($v0)
/*  f02364c:	28440000 */ 	slti	$a0,$v0,0x0
/*  f023650:	5080000c */ 	beqzl	$a0,.L0f023684
/*  f023654:	00803825 */ 	or	$a3,$a0,$zero
/*  f023658:	8e0b0020 */ 	lw	$t3,0x20($s0)
/*  f02365c:	44809000 */ 	mtc1	$zero,$f18
/*  f023660:	00002025 */ 	or	$a0,$zero,$zero
/*  f023664:	8d6d0020 */ 	lw	$t5,0x20($t3)
/*  f023668:	c5aa0010 */ 	lwc1	$f10,0x10($t5)
/*  f02366c:	460a9032 */ 	c.eq.s	$f18,$f10
/*  f023670:	00000000 */ 	nop
/*  f023674:	45030003 */ 	bc1tl	.L0f023684
/*  f023678:	00803825 */ 	or	$a3,$a0,$zero
/*  f02367c:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f023680:	00803825 */ 	or	$a3,$a0,$zero
.L0f023684:
/*  f023684:	10e00003 */ 	beqz	$a3,.L0f023694
/*  f023688:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f02368c:	10000155 */ 	b	.L0f023be4
/*  f023690:	00003825 */ 	or	$a3,$zero,$zero
.L0f023694:
/*  f023694:	0fc23a79 */ 	jal	posIsInDrawDistance
/*  f023698:	24840008 */ 	addiu	$a0,$a0,8
/*  f02369c:	10000151 */ 	b	.L0f023be4
/*  f0236a0:	00403825 */ 	or	$a3,$v0,$zero
/*  f0236a4:	82030007 */ 	lb	$v1,0x7($s0)
.L0f0236a8:
/*  f0236a8:	2401000e */ 	addiu	$at,$zero,0xe
/*  f0236ac:	10610002 */ 	beq	$v1,$at,.L0f0236b8
/*  f0236b0:	2401000f */ 	addiu	$at,$zero,0xf
/*  f0236b4:	14610046 */ 	bne	$v1,$at,.L0f0237d0
.L0f0236b8:
/*  f0236b8:	2401000e */ 	addiu	$at,$zero,0xe
/*  f0236bc:	54610005 */ 	bnel	$v1,$at,.L0f0236d4
/*  f0236c0:	2401000f */ 	addiu	$at,$zero,0xf
/*  f0236c4:	820c0038 */ 	lb	$t4,0x38($s0)
/*  f0236c8:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0236cc:	11810007 */ 	beq	$t4,$at,.L0f0236ec
/*  f0236d0:	2401000f */ 	addiu	$at,$zero,0xf
.L0f0236d4:
/*  f0236d4:	14610018 */ 	bne	$v1,$at,.L0f023738
/*  f0236d8:	8fae01f0 */ 	lw	$t6,0x1f0($sp)
/*  f0236dc:	82180068 */ 	lb	$t8,0x68($s0)
/*  f0236e0:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0236e4:	17010014 */ 	bne	$t8,$at,.L0f023738
/*  f0236e8:	00000000 */ 	nop
.L0f0236ec:
/*  f0236ec:	0c006be0 */ 	jal	func0001af80
/*  f0236f0:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0236f4:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0236f8:	44060000 */ 	mfc1	$a2,$f0
/*  f0236fc:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f023700:	0fc23a2b */ 	jal	func0f08e8ac
/*  f023704:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023708:	10400136 */ 	beqz	$v0,.L0f023be4
/*  f02370c:	00403825 */ 	or	$a3,$v0,$zero
/*  f023710:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023714:	260500c8 */ 	addiu	$a1,$s0,0xc8
/*  f023718:	8c990020 */ 	lw	$t9,0x20($a0)
/*  f02371c:	a320000b */ 	sb	$zero,0xb($t9)
/*  f023720:	0c006b43 */ 	jal	modelGetRootPosition
/*  f023724:	afa20204 */ 	sw	$v0,0x204($sp)
/*  f023728:	0c006cef */ 	jal	func0001b3bc
/*  f02372c:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023730:	1000012c */ 	b	.L0f023be4
/*  f023734:	8fa70204 */ 	lw	$a3,0x204($sp)
.L0f023738:
/*  f023738:	11c00004 */ 	beqz	$t6,.L0f02374c
/*  f02373c:	02002025 */ 	or	$a0,$s0,$zero
/*  f023740:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023744:	0fc0883b */ 	jal	func0f0220ec
/*  f023748:	24060001 */ 	addiu	$a2,$zero,0x1
.L0f02374c:
/*  f02374c:	0c006be0 */ 	jal	func0001af80
/*  f023750:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023754:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023758:	44060000 */ 	mfc1	$a2,$f0
/*  f02375c:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f023760:	0fc23a2b */ 	jal	func0f08e8ac
/*  f023764:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023768:	1040000e */ 	beqz	$v0,.L0f0237a4
/*  f02376c:	00403825 */ 	or	$a3,$v0,$zero
/*  f023770:	82030007 */ 	lb	$v1,0x7($s0)
/*  f023774:	2401000e */ 	addiu	$at,$zero,0xe
/*  f023778:	3c0a800a */ 	lui	$t2,%hi(g_Vars+0x8)
/*  f02377c:	54610005 */ 	bnel	$v1,$at,.L0f023794
/*  f023780:	2401000f */ 	addiu	$at,$zero,0xf
/*  f023784:	8d4a9fc8 */ 	lw	$t2,%lo(g_Vars+0x8)($t2)
/*  f023788:	10000006 */ 	b	.L0f0237a4
/*  f02378c:	ae0a0078 */ 	sw	$t2,0x78($s0)
/*  f023790:	2401000f */ 	addiu	$at,$zero,0xf
.L0f023794:
/*  f023794:	14610003 */ 	bne	$v1,$at,.L0f0237a4
/*  f023798:	3c0b800a */ 	lui	$t3,%hi(g_Vars+0x8)
/*  f02379c:	8d6b9fc8 */ 	lw	$t3,%lo(g_Vars+0x8)($t3)
/*  f0237a0:	ae0b00a8 */ 	sw	$t3,0xa8($s0)
.L0f0237a4:
/*  f0237a4:	2c440001 */ 	sltiu	$a0,$v0,0x1
/*  f0237a8:	10800006 */ 	beqz	$a0,.L0f0237c4
/*  f0237ac:	8faf0208 */ 	lw	$t7,0x208($sp)
/*  f0237b0:	8fad0250 */ 	lw	$t5,0x250($sp)
/*  f0237b4:	91a40001 */ 	lbu	$a0,0x1($t5)
/*  f0237b8:	308c00c0 */ 	andi	$t4,$a0,0xc0
/*  f0237bc:	000cc02b */ 	sltu	$t8,$zero,$t4
/*  f0237c0:	2f040001 */ 	sltiu	$a0,$t8,0x1
.L0f0237c4:
/*  f0237c4:	8df90020 */ 	lw	$t9,0x20($t7)
/*  f0237c8:	10000106 */ 	b	.L0f023be4
/*  f0237cc:	a324000b */ 	sb	$a0,0xb($t9)
.L0f0237d0:
/*  f0237d0:	24010003 */ 	addiu	$at,$zero,0x3
/*  f0237d4:	54610025 */ 	bnel	$v1,$at,.L0f02386c
/*  f0237d8:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0237dc:	8e08002c */ 	lw	$t0,0x2c($s0)
/*  f0237e0:	55000022 */ 	bnezl	$t0,.L0f02386c
/*  f0237e4:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0237e8:	0c006be0 */ 	jal	func0001af80
/*  f0237ec:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0237f0:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0237f4:	44060000 */ 	mfc1	$a2,$f0
/*  f0237f8:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f0237fc:	0fc23a2b */ 	jal	func0f08e8ac
/*  f023800:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023804:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
/*  f023808:	00403825 */ 	or	$a3,$v0,$zero
/*  f02380c:	8faa0208 */ 	lw	$t2,0x208($sp)
/*  f023810:	512000f5 */ 	beqzl	$t1,.L0f023be8
/*  f023814:	8fac01f0 */ 	lw	$t4,0x1f0($sp)
/*  f023818:	8d4b0020 */ 	lw	$t3,0x20($t2)
/*  f02381c:	02002025 */ 	or	$a0,$s0,$zero
/*  f023820:	1040000b */ 	beqz	$v0,.L0f023850
/*  f023824:	a160000b */ 	sb	$zero,0xb($t3)
/*  f023828:	8e0d003c */ 	lw	$t5,0x3c($s0)
/*  f02382c:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023830:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f023834:	55a00007 */ 	bnezl	$t5,.L0f023854
/*  f023838:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f02383c:	02002025 */ 	or	$a0,$s0,$zero
/*  f023840:	0fc0883b */ 	jal	func0f0220ec
/*  f023844:	afa20204 */ 	sw	$v0,0x204($sp)
/*  f023848:	100000e6 */ 	b	.L0f023be4
/*  f02384c:	8fa70204 */ 	lw	$a3,0x204($sp)
.L0f023850:
/*  f023850:	8fa501fc */ 	lw	$a1,0x1fc($sp)
.L0f023854:
/*  f023854:	00003025 */ 	or	$a2,$zero,$zero
/*  f023858:	0fc0883b */ 	jal	func0f0220ec
/*  f02385c:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023860:	100000e0 */ 	b	.L0f023be4
/*  f023864:	8fa70204 */ 	lw	$a3,0x204($sp)
/*  f023868:	24010001 */ 	addiu	$at,$zero,0x1
.L0f02386c:
/*  f02386c:	14610062 */ 	bne	$v1,$at,.L0f0239f8
/*  f023870:	8fac0208 */ 	lw	$t4,0x208($sp)
/*  f023874:	8d980020 */ 	lw	$t8,0x20($t4)
/*  f023878:	02002025 */ 	or	$a0,$s0,$zero
/*  f02387c:	a300000b */ 	sb	$zero,0xb($t8)
/*  f023880:	8e0f0018 */ 	lw	$t7,0x18($s0)
/*  f023884:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023888:	31f90001 */ 	andi	$t9,$t7,0x1
/*  f02388c:	1320000c */ 	beqz	$t9,.L0f0238c0
/*  f023890:	00000000 */ 	nop
/*  f023894:	0fc0883b */ 	jal	func0f0220ec
/*  f023898:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f02389c:	0c006be0 */ 	jal	func0001af80
/*  f0238a0:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0238a4:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0238a8:	44060000 */ 	mfc1	$a2,$f0
/*  f0238ac:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f0238b0:	0fc23a2b */ 	jal	func0f08e8ac
/*  f0238b4:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f0238b8:	100000ca */ 	b	.L0f023be4
/*  f0238bc:	00403825 */ 	or	$a3,$v0,$zero
.L0f0238c0:
/*  f0238c0:	0c006be0 */ 	jal	func0001af80
/*  f0238c4:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0238c8:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0238cc:	44060000 */ 	mfc1	$a2,$f0
/*  f0238d0:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f0238d4:	0fc23a2b */ 	jal	func0f08e8ac
/*  f0238d8:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f0238dc:	3c09800a */ 	lui	$t1,%hi(g_Vars+0x314)
/*  f0238e0:	8d29a2d4 */ 	lw	$t1,%lo(g_Vars+0x314)($t1)
/*  f0238e4:	00403825 */ 	or	$a3,$v0,$zero
/*  f0238e8:	8faa01f0 */ 	lw	$t2,0x1f0($sp)
/*  f0238ec:	11200024 */ 	beqz	$t1,.L0f023980
/*  f0238f0:	00000000 */ 	nop
/*  f0238f4:	114000bb */ 	beqz	$t2,.L0f023be4
/*  f0238f8:	3c0b800a */ 	lui	$t3,%hi(g_Vars+0x298)
/*  f0238fc:	8d6ba258 */ 	lw	$t3,%lo(g_Vars+0x298)($t3)
/*  f023900:	3c0d800a */ 	lui	$t5,%hi(g_Vars+0x29c)
/*  f023904:	05610006 */ 	bgez	$t3,.L0f023920
/*  f023908:	00000000 */ 	nop
/*  f02390c:	8dada25c */ 	lw	$t5,%lo(g_Vars+0x29c)($t5)
/*  f023910:	02002025 */ 	or	$a0,$s0,$zero
/*  f023914:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023918:	05a00015 */ 	bltz	$t5,.L0f023970
/*  f02391c:	24060001 */ 	addiu	$a2,$zero,0x1
.L0f023920:
/*  f023920:	10400008 */ 	beqz	$v0,.L0f023944
/*  f023924:	8fac0208 */ 	lw	$t4,0x208($sp)
/*  f023928:	02002025 */ 	or	$a0,$s0,$zero
/*  f02392c:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023930:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f023934:	0fc0883b */ 	jal	func0f0220ec
/*  f023938:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f02393c:	100000a9 */ 	b	.L0f023be4
/*  f023940:	8fa70204 */ 	lw	$a3,0x204($sp)
.L0f023944:
/*  f023944:	8d980020 */ 	lw	$t8,0x20($t4)
/*  f023948:	02002025 */ 	or	$a0,$s0,$zero
/*  f02394c:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023950:	870f0002 */ 	lh	$t7,0x2($t8)
/*  f023954:	00003025 */ 	or	$a2,$zero,$zero
/*  f023958:	51e000a3 */ 	beqzl	$t7,.L0f023be8
/*  f02395c:	8fac01f0 */ 	lw	$t4,0x1f0($sp)
/*  f023960:	0fc0883b */ 	jal	func0f0220ec
/*  f023964:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023968:	1000009e */ 	b	.L0f023be4
/*  f02396c:	8fa70204 */ 	lw	$a3,0x204($sp)
.L0f023970:
/*  f023970:	0fc0883b */ 	jal	func0f0220ec
/*  f023974:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023978:	1000009a */ 	b	.L0f023be4
/*  f02397c:	8fa70204 */ 	lw	$a3,0x204($sp)
.L0f023980:
/*  f023980:	10400012 */ 	beqz	$v0,.L0f0239cc
/*  f023984:	8fa80208 */ 	lw	$t0,0x208($sp)
/*  f023988:	9219004c */ 	lbu	$t9,0x4c($s0)
/*  f02398c:	24010001 */ 	addiu	$at,$zero,0x1
/*  f023990:	02002025 */ 	or	$a0,$s0,$zero
/*  f023994:	17210008 */ 	bne	$t9,$at,.L0f0239b8
/*  f023998:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f02399c:	02002025 */ 	or	$a0,$s0,$zero
/*  f0239a0:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0239a4:	00003025 */ 	or	$a2,$zero,$zero
/*  f0239a8:	0fc0883b */ 	jal	func0f0220ec
/*  f0239ac:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f0239b0:	1000008c */ 	b	.L0f023be4
/*  f0239b4:	8fa70204 */ 	lw	$a3,0x204($sp)
.L0f0239b8:
/*  f0239b8:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0239bc:	0fc0883b */ 	jal	func0f0220ec
/*  f0239c0:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f0239c4:	10000087 */ 	b	.L0f023be4
/*  f0239c8:	8fa70204 */ 	lw	$a3,0x204($sp)
.L0f0239cc:
/*  f0239cc:	8d0e0020 */ 	lw	$t6,0x20($t0)
/*  f0239d0:	02002025 */ 	or	$a0,$s0,$zero
/*  f0239d4:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0239d8:	85c90002 */ 	lh	$t1,0x2($t6)
/*  f0239dc:	00003025 */ 	or	$a2,$zero,$zero
/*  f0239e0:	51200081 */ 	beqzl	$t1,.L0f023be8
/*  f0239e4:	8fac01f0 */ 	lw	$t4,0x1f0($sp)
/*  f0239e8:	0fc0883b */ 	jal	func0f0220ec
/*  f0239ec:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f0239f0:	1000007c */ 	b	.L0f023be4
/*  f0239f4:	8fa70204 */ 	lw	$a3,0x204($sp)
.L0f0239f8:
/*  f0239f8:	24010005 */ 	addiu	$at,$zero,0x5
/*  f0239fc:	1461000a */ 	bne	$v1,$at,.L0f023a28
/*  f023a00:	8fab0250 */ 	lw	$t3,0x250($sp)
/*  f023a04:	0c006be0 */ 	jal	func0001af80
/*  f023a08:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023a0c:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023a10:	44060000 */ 	mfc1	$a2,$f0
/*  f023a14:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f023a18:	0fc23a2b */ 	jal	func0f08e8ac
/*  f023a1c:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023a20:	10000070 */ 	b	.L0f023be4
/*  f023a24:	00403825 */ 	or	$a3,$v0,$zero
.L0f023a28:
/*  f023a28:	916d0000 */ 	lbu	$t5,0x0($t3)
/*  f023a2c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f023a30:	3c0c800a */ 	lui	$t4,%hi(g_Vars+0x314)
/*  f023a34:	55a10025 */ 	bnel	$t5,$at,.L0f023acc
/*  f023a38:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
/*  f023a3c:	8d8ca2d4 */ 	lw	$t4,%lo(g_Vars+0x314)($t4)
/*  f023a40:	55800012 */ 	bnezl	$t4,.L0f023a8c
/*  f023a44:	8fb90208 */ 	lw	$t9,0x208($sp)
/*  f023a48:	0fc4a25f */ 	jal	propGetPlayerNum
/*  f023a4c:	01602025 */ 	or	$a0,$t3,$zero
/*  f023a50:	0002c080 */ 	sll	$t8,$v0,0x2
/*  f023a54:	3c03800a */ 	lui	$v1,%hi(g_Vars+0x64)
/*  f023a58:	00781821 */ 	addu	$v1,$v1,$t8
/*  f023a5c:	8c63a024 */ 	lw	$v1,%lo(g_Vars+0x64)($v1)
/*  f023a60:	24010002 */ 	addiu	$at,$zero,0x2
/*  f023a64:	8c640000 */ 	lw	$a0,0x0($v1)
/*  f023a68:	10810007 */ 	beq	$a0,$at,.L0f023a88
/*  f023a6c:	24010001 */ 	addiu	$at,$zero,0x1
/*  f023a70:	54810016 */ 	bnel	$a0,$at,.L0f023acc
/*  f023a74:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
/*  f023a78:	946f0010 */ 	lhu	$t7,0x10($v1)
/*  f023a7c:	24010002 */ 	addiu	$at,$zero,0x2
/*  f023a80:	55e10012 */ 	bnel	$t7,$at,.L0f023acc
/*  f023a84:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
.L0f023a88:
/*  f023a88:	8fb90208 */ 	lw	$t9,0x208($sp)
.L0f023a8c:
/*  f023a8c:	02002025 */ 	or	$a0,$s0,$zero
/*  f023a90:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f023a94:	8f280020 */ 	lw	$t0,0x20($t9)
/*  f023a98:	a100000b */ 	sb	$zero,0xb($t0)
/*  f023a9c:	0fc0883b */ 	jal	func0f0220ec
/*  f023aa0:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023aa4:	0c006be0 */ 	jal	func0001af80
/*  f023aa8:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023aac:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023ab0:	44060000 */ 	mfc1	$a2,$f0
/*  f023ab4:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f023ab8:	0fc23a2b */ 	jal	func0f08e8ac
/*  f023abc:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023ac0:	10000048 */ 	b	.L0f023be4
/*  f023ac4:	00403825 */ 	or	$a3,$v0,$zero
/*  f023ac8:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
.L0f023acc:
/*  f023acc:	00003825 */ 	or	$a3,$zero,$zero
/*  f023ad0:	8faa0208 */ 	lw	$t2,0x208($sp)
/*  f023ad4:	5120000a */ 	beqzl	$t1,.L0f023b00
/*  f023ad8:	8e030020 */ 	lw	$v1,0x20($s0)
/*  f023adc:	8d4d0020 */ 	lw	$t5,0x20($t2)
/*  f023ae0:	02002025 */ 	or	$a0,$s0,$zero
/*  f023ae4:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f023ae8:	a1a0000b */ 	sb	$zero,0xb($t5)
/*  f023aec:	afa0019c */ 	sw	$zero,0x19c($sp)
/*  f023af0:	0fc0883b */ 	jal	func0f0220ec
/*  f023af4:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023af8:	8fa7019c */ 	lw	$a3,0x19c($sp)
/*  f023afc:	8e030020 */ 	lw	$v1,0x20($s0)
.L0f023b00:
/*  f023b00:	1060002c */ 	beqz	$v1,.L0f023bb4
/*  f023b04:	00000000 */ 	nop
/*  f023b08:	8c620020 */ 	lw	$v0,0x20($v1)
/*  f023b0c:	10400029 */ 	beqz	$v0,.L0f023bb4
/*  f023b10:	00000000 */ 	nop
/*  f023b14:	84440000 */ 	lh	$a0,0x0($v0)
/*  f023b18:	3c0c8006 */ 	lui	$t4,%hi(g_Anims)
/*  f023b1c:	8d8cf00c */ 	lw	$t4,%lo(g_Anims)($t4)
/*  f023b20:	00045880 */ 	sll	$t3,$a0,0x2
/*  f023b24:	01645823 */ 	subu	$t3,$t3,$a0
/*  f023b28:	000b5880 */ 	sll	$t3,$t3,0x2
/*  f023b2c:	018bc021 */ 	addu	$t8,$t4,$t3
/*  f023b30:	930f000b */ 	lbu	$t7,0xb($t8)
/*  f023b34:	31f90004 */ 	andi	$t9,$t7,0x4
/*  f023b38:	1320001e */ 	beqz	$t9,.L0f023bb4
/*  f023b3c:	00000000 */ 	nop
/*  f023b40:	0c008f4e */ 	jal	func00023d38
/*  f023b44:	00000000 */ 	nop
/*  f023b48:	8e080020 */ 	lw	$t0,0x20($s0)
/*  f023b4c:	8d020020 */ 	lw	$v0,0x20($t0)
/*  f023b50:	84440000 */ 	lh	$a0,0x0($v0)
/*  f023b54:	0c008e13 */ 	jal	func0002384c
/*  f023b58:	84450014 */ 	lh	$a1,0x14($v0)
/*  f023b5c:	28440000 */ 	slti	$a0,$v0,0x0
/*  f023b60:	54800014 */ 	bnezl	$a0,.L0f023bb4
/*  f023b64:	00803825 */ 	or	$a3,$a0,$zero
/*  f023b68:	8e0e0020 */ 	lw	$t6,0x20($s0)
/*  f023b6c:	8dc20020 */ 	lw	$v0,0x20($t6)
/*  f023b70:	84440000 */ 	lh	$a0,0x0($v0)
/*  f023b74:	0c008e13 */ 	jal	func0002384c
/*  f023b78:	84450016 */ 	lh	$a1,0x16($v0)
/*  f023b7c:	28440000 */ 	slti	$a0,$v0,0x0
/*  f023b80:	5080000c */ 	beqzl	$a0,.L0f023bb4
/*  f023b84:	00803825 */ 	or	$a3,$a0,$zero
/*  f023b88:	8e090020 */ 	lw	$t1,0x20($s0)
/*  f023b8c:	44802000 */ 	mtc1	$zero,$f4
/*  f023b90:	00002025 */ 	or	$a0,$zero,$zero
/*  f023b94:	8d2a0020 */ 	lw	$t2,0x20($t1)
/*  f023b98:	c5460010 */ 	lwc1	$f6,0x10($t2)
/*  f023b9c:	46062032 */ 	c.eq.s	$f4,$f6
/*  f023ba0:	00000000 */ 	nop
/*  f023ba4:	45030003 */ 	bc1tl	.L0f023bb4
/*  f023ba8:	00803825 */ 	or	$a3,$a0,$zero
/*  f023bac:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f023bb0:	00803825 */ 	or	$a3,$a0,$zero
.L0f023bb4:
/*  f023bb4:	10e00003 */ 	beqz	$a3,.L0f023bc4
/*  f023bb8:	00000000 */ 	nop
/*  f023bbc:	10000009 */ 	b	.L0f023be4
/*  f023bc0:	00003825 */ 	or	$a3,$zero,$zero
.L0f023bc4:
/*  f023bc4:	0c006be0 */ 	jal	func0001af80
/*  f023bc8:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023bcc:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023bd0:	44060000 */ 	mfc1	$a2,$f0
/*  f023bd4:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f023bd8:	0fc23a2b */ 	jal	func0f08e8ac
/*  f023bdc:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023be0:	00403825 */ 	or	$a3,$v0,$zero
.L0f023be4:
/*  f023be4:	8fac01f0 */ 	lw	$t4,0x1f0($sp)
.L0f023be8:
/*  f023be8:	02002025 */ 	or	$a0,$s0,$zero
/*  f023bec:	51800016 */ 	beqzl	$t4,.L0f023c48
/*  f023bf0:	8fad0250 */ 	lw	$t5,0x250($sp)
/*  f023bf4:	820b0007 */ 	lb	$t3,0x7($s0)
/*  f023bf8:	24010001 */ 	addiu	$at,$zero,0x1
/*  f023bfc:	8fb80208 */ 	lw	$t8,0x208($sp)
/*  f023c00:	5561000b */ 	bnel	$t3,$at,.L0f023c30
/*  f023c04:	96090192 */ 	lhu	$t1,0x192($s0)
/*  f023c08:	8f0f0020 */ 	lw	$t7,0x20($t8)
/*  f023c0c:	8fa80250 */ 	lw	$t0,0x250($sp)
/*  f023c10:	85f90002 */ 	lh	$t9,0x2($t7)
/*  f023c14:	57200006 */ 	bnezl	$t9,.L0f023c30
/*  f023c18:	96090192 */ 	lhu	$t1,0x192($s0)
/*  f023c1c:	910e0000 */ 	lbu	$t6,0x0($t0)
/*  f023c20:	24010006 */ 	addiu	$at,$zero,0x6
/*  f023c24:	15c10004 */ 	bne	$t6,$at,.L0f023c38
/*  f023c28:	00000000 */ 	nop
/*  f023c2c:	96090192 */ 	lhu	$t1,0x192($s0)
.L0f023c30:
/*  f023c30:	352a0040 */ 	ori	$t2,$t1,0x40
/*  f023c34:	a60a0192 */ 	sh	$t2,0x192($s0)
.L0f023c38:
/*  f023c38:	0fc08496 */ 	jal	chrUpdateAimProperties
/*  f023c3c:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023c40:	8fa70204 */ 	lw	$a3,0x204($sp)
/*  f023c44:	8fad0250 */ 	lw	$t5,0x250($sp)
.L0f023c48:
/*  f023c48:	3c01c780 */ 	lui	$at,0xc780
/*  f023c4c:	44819000 */ 	mtc1	$at,$f18
/*  f023c50:	c5a8000c */ 	lwc1	$f8,0xc($t5)
/*  f023c54:	3c0c800a */ 	lui	$t4,%hi(g_Vars+0x318)
/*  f023c58:	4612403c */ 	c.lt.s	$f8,$f18
/*  f023c5c:	00000000 */ 	nop
/*  f023c60:	45000002 */ 	bc1f	.L0f023c6c
/*  f023c64:	00000000 */ 	nop
/*  f023c68:	00003825 */ 	or	$a3,$zero,$zero
.L0f023c6c:
/*  f023c6c:	8d8ca2d8 */ 	lw	$t4,%lo(g_Vars+0x318)($t4)
/*  f023c70:	5580002d */ 	bnezl	$t4,.L0f023d28
/*  f023c74:	8fab0250 */ 	lw	$t3,0x250($sp)
/*  f023c78:	50e0002b */ 	beqzl	$a3,.L0f023d28
/*  f023c7c:	8fab0250 */ 	lw	$t3,0x250($sp)
/*  f023c80:	82030007 */ 	lb	$v1,0x7($s0)
/*  f023c84:	24010005 */ 	addiu	$at,$zero,0x5
/*  f023c88:	10610006 */ 	beq	$v1,$at,.L0f023ca4
/*  f023c8c:	2401001f */ 	addiu	$at,$zero,0x1f
/*  f023c90:	14610017 */ 	bne	$v1,$at,.L0f023cf0
/*  f023c94:	00000000 */ 	nop
/*  f023c98:	8e0b0018 */ 	lw	$t3,0x18($s0)
/*  f023c9c:	000bc140 */ 	sll	$t8,$t3,0x5
/*  f023ca0:	07000013 */ 	bltz	$t8,.L0f023cf0
.L0f023ca4:
/*  f023ca4:	3c03800a */ 	lui	$v1,%hi(var8009cdac)
/*  f023ca8:	2463cdac */ 	addiu	$v1,$v1,%lo(var8009cdac)
/*  f023cac:	8c6f0000 */ 	lw	$t7,0x0($v1)
/*  f023cb0:	02002025 */ 	or	$a0,$s0,$zero
/*  f023cb4:	25e20001 */ 	addiu	$v0,$t7,0x1
/*  f023cb8:	2841000b */ 	slti	$at,$v0,0xb
/*  f023cbc:	14200009 */ 	bnez	$at,.L0f023ce4
/*  f023cc0:	ac620000 */ 	sw	$v0,0x0($v1)
/*  f023cc4:	0fc0919a */ 	jal	chrDropWeapons
/*  f023cc8:	afa00204 */ 	sw	$zero,0x204($sp)
/*  f023ccc:	8e080014 */ 	lw	$t0,0x14($s0)
/*  f023cd0:	8fa70204 */ 	lw	$a3,0x204($sp)
/*  f023cd4:	3c02800a */ 	lui	$v0,%hi(var8009cdac)
/*  f023cd8:	350e0020 */ 	ori	$t6,$t0,0x20
/*  f023cdc:	ae0e0014 */ 	sw	$t6,0x14($s0)
/*  f023ce0:	8c42cdac */ 	lw	$v0,%lo(var8009cdac)($v0)
.L0f023ce4:
/*  f023ce4:	3c03800a */ 	lui	$v1,%hi(var8009cdb0)
/*  f023ce8:	10000008 */ 	b	.L0f023d0c
/*  f023cec:	2463cdb0 */ 	addiu	$v1,$v1,%lo(var8009cdb0)
.L0f023cf0:
/*  f023cf0:	3c03800a */ 	lui	$v1,%hi(var8009cdb0)
/*  f023cf4:	2463cdb0 */ 	addiu	$v1,$v1,%lo(var8009cdb0)
/*  f023cf8:	8c690000 */ 	lw	$t1,0x0($v1)
/*  f023cfc:	3c02800a */ 	lui	$v0,%hi(var8009cdac)
/*  f023d00:	252a0001 */ 	addiu	$t2,$t1,0x1
/*  f023d04:	ac6a0000 */ 	sw	$t2,0x0($v1)
/*  f023d08:	8c42cdac */ 	lw	$v0,%lo(var8009cdac)($v0)
.L0f023d0c:
/*  f023d0c:	8c6d0000 */ 	lw	$t5,0x0($v1)
/*  f023d10:	01a26021 */ 	addu	$t4,$t5,$v0
/*  f023d14:	2981001f */ 	slti	$at,$t4,0x1f
/*  f023d18:	54200003 */ 	bnezl	$at,.L0f023d28
/*  f023d1c:	8fab0250 */ 	lw	$t3,0x250($sp)
/*  f023d20:	00003825 */ 	or	$a3,$zero,$zero
/*  f023d24:	8fab0250 */ 	lw	$t3,0x250($sp)
.L0f023d28:
/*  f023d28:	8fac0250 */ 	lw	$t4,0x250($sp)
/*  f023d2c:	10e001be */ 	beqz	$a3,.L0f024428
/*  f023d30:	91620001 */ 	lbu	$v0,0x1($t3)
/*  f023d34:	34580042 */ 	ori	$t8,$v0,0x42
/*  f023d38:	a1780001 */ 	sb	$t8,0x1($t3)
/*  f023d3c:	8e0f0018 */ 	lw	$t7,0x18($s0)
/*  f023d40:	3c08800a */ 	lui	$t0,%hi(g_Vars+0x29c)
/*  f023d44:	35f90008 */ 	ori	$t9,$t7,0x8
/*  f023d48:	ae190018 */ 	sw	$t9,0x18($s0)
/*  f023d4c:	8d08a25c */ 	lw	$t0,%lo(g_Vars+0x29c)($t0)
/*  f023d50:	0500000a */ 	bltz	$t0,.L0f023d7c
/*  f023d54:	3c0e800a */ 	lui	$t6,%hi(g_Vars+0x2a0)
/*  f023d58:	3c09800a */ 	lui	$t1,%hi(g_Vars+0x284)
/*  f023d5c:	8d29a244 */ 	lw	$t1,%lo(g_Vars+0x284)($t1)
/*  f023d60:	8dcea260 */ 	lw	$t6,%lo(g_Vars+0x2a0)($t6)
/*  f023d64:	15c90005 */ 	bne	$t6,$t1,.L0f023d7c
/*  f023d68:	00000000 */ 	nop
/*  f023d6c:	8e0a0014 */ 	lw	$t2,0x14($s0)
/*  f023d70:	3c010080 */ 	lui	$at,0x80
/*  f023d74:	01416825 */ 	or	$t5,$t2,$at
/*  f023d78:	ae0d0014 */ 	sw	$t5,0x14($s0)
.L0f023d7c:
/*  f023d7c:	0fc41b99 */ 	jal	cheatIsActive
/*  f023d80:	24040007 */ 	addiu	$a0,$zero,0x7
/*  f023d84:	10400004 */ 	beqz	$v0,.L0f023d98
/*  f023d88:	3c013ea0 */ 	lui	$at,0x3ea0
/*  f023d8c:	44816000 */ 	mtc1	$at,$f12
/*  f023d90:	0c006943 */ 	jal	modelSetDistanceScale
/*  f023d94:	00000000 */ 	nop
.L0f023d98:
/*  f023d98:	3c0c7f02 */ 	lui	$t4,%hi(func0f02152c)
/*  f023d9c:	258c152c */ 	addiu	$t4,$t4,%lo(func0f02152c)
/*  f023da0:	3c018006 */ 	lui	$at,%hi(var8005efcc)
/*  f023da4:	ac2cefcc */ 	sw	$t4,%lo(var8005efcc)($at)
/*  f023da8:	3c01800a */ 	lui	$at,%hi(var8009cd1c)
/*  f023dac:	12000003 */ 	beqz	$s0,.L0f023dbc
/*  f023db0:	ac30cd1c */ 	sw	$s0,%lo(var8009cd1c)($at)
/*  f023db4:	10000002 */ 	b	.L0f023dc0
/*  f023db8:	920402fe */ 	lbu	$a0,0x2fe($s0)
.L0f023dbc:
/*  f023dbc:	00002025 */ 	or	$a0,$zero,$zero
.L0f023dc0:
/*  f023dc0:	24010002 */ 	addiu	$at,$zero,0x2
/*  f023dc4:	14810021 */ 	bne	$a0,$at,.L0f023e4c
/*  f023dc8:	3c18800a */ 	lui	$t8,%hi(g_Vars+0x2ac)
/*  f023dcc:	8f18a26c */ 	lw	$t8,%lo(g_Vars+0x2ac)($t8)
/*  f023dd0:	24010006 */ 	addiu	$at,$zero,0x6
/*  f023dd4:	5301001e */ 	beql	$t8,$at,.L0f023e50
/*  f023dd8:	8faf0250 */ 	lw	$t7,0x250($sp)
/*  f023ddc:	0fc0f917 */ 	jal	chrGetInverseTheta
/*  f023de0:	02002025 */ 	or	$a0,$s0,$zero
/*  f023de4:	e7a0018c */ 	swc1	$f0,0x18c($sp)
/*  f023de8:	0c0068f7 */ 	jal	sinf
/*  f023dec:	46000306 */ 	mov.s	$f12,$f0
/*  f023df0:	3c014198 */ 	lui	$at,0x4198
/*  f023df4:	44815000 */ 	mtc1	$at,$f10
/*  f023df8:	44803000 */ 	mtc1	$zero,$f6
/*  f023dfc:	c7ac018c */ 	lwc1	$f12,0x18c($sp)
/*  f023e00:	460a0102 */ 	mul.s	$f4,$f0,$f10
/*  f023e04:	e7a60194 */ 	swc1	$f6,0x194($sp)
/*  f023e08:	0c0068f4 */ 	jal	cosf
/*  f023e0c:	e7a40190 */ 	swc1	$f4,0x190($sp)
/*  f023e10:	3c014198 */ 	lui	$at,0x4198
/*  f023e14:	44814000 */ 	mtc1	$at,$f8
/*  f023e18:	27a40190 */ 	addiu	$a0,$sp,0x190
/*  f023e1c:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f023e20:	46080482 */ 	mul.s	$f18,$f0,$f8
/*  f023e24:	0c0059b7 */ 	jal	func000166dc
/*  f023e28:	e7b20198 */ 	swc1	$f18,0x198($sp)
/*  f023e2c:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f023e30:	00000000 */ 	nop
/*  f023e34:	00402025 */ 	or	$a0,$v0,$zero
/*  f023e38:	0c00567f */ 	jal	func000159fc
/*  f023e3c:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f023e40:	27ab01a8 */ 	addiu	$t3,$sp,0x1a8
/*  f023e44:	1000004b */ 	b	.L0f023f74
/*  f023e48:	afab0210 */ 	sw	$t3,0x210($sp)
.L0f023e4c:
/*  f023e4c:	8faf0250 */ 	lw	$t7,0x250($sp)
.L0f023e50:
/*  f023e50:	24010006 */ 	addiu	$at,$zero,0x6
/*  f023e54:	91f90000 */ 	lbu	$t9,0x0($t7)
/*  f023e58:	17210043 */ 	bne	$t9,$at,.L0f023f68
/*  f023e5c:	00000000 */ 	nop
/*  f023e60:	0fc4a25f */ 	jal	propGetPlayerNum
/*  f023e64:	01e02025 */ 	or	$a0,$t7,$zero
/*  f023e68:	00024080 */ 	sll	$t0,$v0,0x2
/*  f023e6c:	3c03800a */ 	lui	$v1,%hi(g_Vars+0x64)
/*  f023e70:	00681821 */ 	addu	$v1,$v1,$t0
/*  f023e74:	8c63a024 */ 	lw	$v1,%lo(g_Vars+0x64)($v1)
/*  f023e78:	24010003 */ 	addiu	$at,$zero,0x3
/*  f023e7c:	02002025 */ 	or	$a0,$s0,$zero
/*  f023e80:	8c6e01b0 */ 	lw	$t6,0x1b0($v1)
/*  f023e84:	15c10034 */ 	bne	$t6,$at,.L0f023f58
/*  f023e88:	00000000 */ 	nop
/*  f023e8c:	0fc0f917 */ 	jal	chrGetInverseTheta
/*  f023e90:	afa30188 */ 	sw	$v1,0x188($sp)
/*  f023e94:	8fa30188 */ 	lw	$v1,0x188($sp)
/*  f023e98:	e7a00178 */ 	swc1	$f0,0x178($sp)
/*  f023e9c:	3c01447a */ 	lui	$at,0x447a
/*  f023ea0:	8c691a6c */ 	lw	$t1,0x1a6c($v1)
/*  f023ea4:	44812000 */ 	mtc1	$at,$f4
/*  f023ea8:	46000306 */ 	mov.s	$f12,$f0
/*  f023eac:	8d220004 */ 	lw	$v0,0x4($t1)
/*  f023eb0:	c44a00ac */ 	lwc1	$f10,0xac($v0)
/*  f023eb4:	afa20174 */ 	sw	$v0,0x174($sp)
/*  f023eb8:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f023ebc:	0c0068f4 */ 	jal	cosf
/*  f023ec0:	e7a60130 */ 	swc1	$f6,0x130($sp)
/*  f023ec4:	c7a80130 */ 	lwc1	$f8,0x130($sp)
/*  f023ec8:	8fa20174 */ 	lw	$v0,0x174($sp)
/*  f023ecc:	44805000 */ 	mtc1	$zero,$f10
/*  f023ed0:	46080482 */ 	mul.s	$f18,$f0,$f8
/*  f023ed4:	3c014348 */ 	lui	$at,0x4348
/*  f023ed8:	44812000 */ 	mtc1	$at,$f4
/*  f023edc:	e7b2017c */ 	swc1	$f18,0x17c($sp)
/*  f023ee0:	c44200ac */ 	lwc1	$f2,0xac($v0)
/*  f023ee4:	4602503c */ 	c.lt.s	$f10,$f2
/*  f023ee8:	00000000 */ 	nop
/*  f023eec:	45020004 */ 	bc1fl	.L0f023f00
/*  f023ef0:	46001007 */ 	neg.s	$f0,$f2
/*  f023ef4:	10000002 */ 	b	.L0f023f00
/*  f023ef8:	46001006 */ 	mov.s	$f0,$f2
/*  f023efc:	46001007 */ 	neg.s	$f0,$f2
.L0f023f00:
/*  f023f00:	46040182 */ 	mul.s	$f6,$f0,$f4
/*  f023f04:	3c0141c8 */ 	lui	$at,0x41c8
/*  f023f08:	44814000 */ 	mtc1	$at,$f8
/*  f023f0c:	c7ac0178 */ 	lwc1	$f12,0x178($sp)
/*  f023f10:	46006307 */ 	neg.s	$f12,$f12
/*  f023f14:	46083480 */ 	add.s	$f18,$f6,$f8
/*  f023f18:	0c0068f7 */ 	jal	sinf
/*  f023f1c:	e7b20180 */ 	swc1	$f18,0x180($sp)
/*  f023f20:	c7aa0130 */ 	lwc1	$f10,0x130($sp)
/*  f023f24:	27a4017c */ 	addiu	$a0,$sp,0x17c
/*  f023f28:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f023f2c:	460a0102 */ 	mul.s	$f4,$f0,$f10
/*  f023f30:	0c0059b7 */ 	jal	func000166dc
/*  f023f34:	e7a40184 */ 	swc1	$f4,0x184($sp)
/*  f023f38:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f023f3c:	00000000 */ 	nop
/*  f023f40:	00402025 */ 	or	$a0,$v0,$zero
/*  f023f44:	0c00567f */ 	jal	func000159fc
/*  f023f48:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f023f4c:	27aa01a8 */ 	addiu	$t2,$sp,0x1a8
/*  f023f50:	10000008 */ 	b	.L0f023f74
/*  f023f54:	afaa0210 */ 	sw	$t2,0x210($sp)
.L0f023f58:
/*  f023f58:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f023f5c:	00000000 */ 	nop
/*  f023f60:	10000004 */ 	b	.L0f023f74
/*  f023f64:	afa20210 */ 	sw	$v0,0x210($sp)
.L0f023f68:
/*  f023f68:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f023f6c:	00000000 */ 	nop
/*  f023f70:	afa20210 */ 	sw	$v0,0x210($sp)
.L0f023f74:
/*  f023f74:	8fad0208 */ 	lw	$t5,0x208($sp)
/*  f023f78:	8dac0008 */ 	lw	$t4,0x8($t5)
/*  f023f7c:	8584000e */ 	lh	$a0,0xe($t4)
/*  f023f80:	0004c180 */ 	sll	$t8,$a0,0x6
/*  f023f84:	0fc59e7d */ 	jal	gfxAllocate
/*  f023f88:	03002025 */ 	or	$a0,$t8,$zero
/*  f023f8c:	8fab01f0 */ 	lw	$t3,0x1f0($sp)
/*  f023f90:	afa20220 */ 	sw	$v0,0x220($sp)
/*  f023f94:	11600011 */ 	beqz	$t3,.L0f023fdc
/*  f023f98:	3c02800a */ 	lui	$v0,%hi(var8009cd1c)
/*  f023f9c:	8c42cd1c */ 	lw	$v0,%lo(var8009cd1c)($v0)
/*  f023fa0:	3c19800a */ 	lui	$t9,%hi(g_Vars+0x38)
/*  f023fa4:	80430012 */ 	lb	$v1,0x12($v0)
/*  f023fa8:	0460000c */ 	bltz	$v1,.L0f023fdc
/*  f023fac:	00000000 */ 	nop
/*  f023fb0:	8f399ff8 */ 	lw	$t9,%lo(g_Vars+0x38)($t9)
/*  f023fb4:	240effff */ 	addiu	$t6,$zero,-1
/*  f023fb8:	00797821 */ 	addu	$t7,$v1,$t9
/*  f023fbc:	a04f0012 */ 	sb	$t7,0x12($v0)
/*  f023fc0:	3c02800a */ 	lui	$v0,%hi(var8009cd1c)
/*  f023fc4:	8c42cd1c */ 	lw	$v0,%lo(var8009cd1c)($v0)
/*  f023fc8:	80480012 */ 	lb	$t0,0x12($v0)
/*  f023fcc:	2901001e */ 	slti	$at,$t0,0x1e
/*  f023fd0:	14200002 */ 	bnez	$at,.L0f023fdc
/*  f023fd4:	00000000 */ 	nop
/*  f023fd8:	a04e0012 */ 	sb	$t6,0x12($v0)
.L0f023fdc:
/*  f023fdc:	3c03800a */ 	lui	$v1,%hi(g_Vars+0x284)
/*  f023fe0:	8c63a244 */ 	lw	$v1,%lo(g_Vars+0x284)($v1)
/*  f023fe4:	24631bb0 */ 	addiu	$v1,$v1,7088
/*  f023fe8:	0fc2d5ee */ 	jal	currentPlayerGetLodScaleZ
/*  f023fec:	afa30124 */ 	sw	$v1,0x124($sp)
/*  f023ff0:	3c09800a */ 	lui	$t1,%hi(g_Vars+0x318)
/*  f023ff4:	8d29a2d8 */ 	lw	$t1,%lo(g_Vars+0x318)($t1)
/*  f023ff8:	8fa30124 */ 	lw	$v1,0x124($sp)
/*  f023ffc:	46000406 */ 	mov.s	$f16,$f0
/*  f024000:	1120000c */ 	beqz	$t1,.L0f024034
/*  f024004:	00003025 */ 	or	$a2,$zero,$zero
/*  f024008:	3c0a800b */ 	lui	$t2,%hi(g_MpSetup+0xc)
/*  f02400c:	8d4acb94 */ 	lw	$t2,%lo(g_MpSetup+0xc)($t2)
/*  f024010:	3c017f1b */ 	lui	$at,%hi(var7f1a87c8)
/*  f024014:	314d00c0 */ 	andi	$t5,$t2,0xc0
/*  f024018:	11a00004 */ 	beqz	$t5,.L0f02402c
/*  f02401c:	00000000 */ 	nop
/*  f024020:	3c017f1b */ 	lui	$at,%hi(var7f1a87cc)
/*  f024024:	10000010 */ 	b	.L0f024068
/*  f024028:	c42e87c8 */ 	lwc1	$f14,%lo(var7f1a87c8)($at)
.L0f02402c:
/*  f02402c:	1000000e */ 	b	.L0f024068
/*  f024030:	c42e87cc */ 	lwc1	$f14,%lo(var7f1a87cc)($at)
.L0f024034:
/*  f024034:	afa30124 */ 	sw	$v1,0x124($sp)
/*  f024038:	afa60110 */ 	sw	$a2,0x110($sp)
/*  f02403c:	0fc47b9c */ 	jal	debugGetSlowMotion
/*  f024040:	e7b00114 */ 	swc1	$f16,0x114($sp)
/*  f024044:	8fa30124 */ 	lw	$v1,0x124($sp)
/*  f024048:	8fa60110 */ 	lw	$a2,0x110($sp)
/*  f02404c:	10400004 */ 	beqz	$v0,.L0f024060
/*  f024050:	c7b00114 */ 	lwc1	$f16,0x114($sp)
/*  f024054:	3c017f1b */ 	lui	$at,%hi(var7f1a87d0)
/*  f024058:	10000003 */ 	b	.L0f024068
/*  f02405c:	c42e87d0 */ 	lwc1	$f14,%lo(var7f1a87d0)($at)
.L0f024060:
/*  f024060:	3c017f1b */ 	lui	$at,%hi(var7f1a87d4)
/*  f024064:	c42e87d4 */ 	lwc1	$f14,%lo(var7f1a87d4)($at)
.L0f024068:
/*  f024068:	8fac0208 */ 	lw	$t4,0x208($sp)
/*  f02406c:	27a40210 */ 	addiu	$a0,$sp,0x210
/*  f024070:	8d820020 */ 	lw	$v0,0x20($t4)
/*  f024074:	50400057 */ 	beqzl	$v0,.L0f0241d4
/*  f024078:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f02407c:	84580000 */ 	lh	$t8,0x0($v0)
/*  f024080:	8fab0250 */ 	lw	$t3,0x250($sp)
/*  f024084:	53000053 */ 	beqzl	$t8,.L0f0241d4
/*  f024088:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f02408c:	c5660008 */ 	lwc1	$f6,0x8($t3)
/*  f024090:	c4680000 */ 	lwc1	$f8,0x0($v1)
/*  f024094:	c572000c */ 	lwc1	$f18,0xc($t3)
/*  f024098:	c46a0004 */ 	lwc1	$f10,0x4($v1)
/*  f02409c:	46083001 */ 	sub.s	$f0,$f6,$f8
/*  f0240a0:	c4660008 */ 	lwc1	$f6,0x8($v1)
/*  f0240a4:	c5640010 */ 	lwc1	$f4,0x10($t3)
/*  f0240a8:	460a9081 */ 	sub.s	$f2,$f18,$f10
/*  f0240ac:	46000202 */ 	mul.s	$f8,$f0,$f0
/*  f0240b0:	46062301 */ 	sub.s	$f12,$f4,$f6
/*  f0240b4:	46021482 */ 	mul.s	$f18,$f2,$f2
/*  f0240b8:	46124280 */ 	add.s	$f10,$f8,$f18
/*  f0240bc:	460c6102 */ 	mul.s	$f4,$f12,$f12
/*  f0240c0:	46045180 */ 	add.s	$f6,$f10,$f4
/*  f0240c4:	46103202 */ 	mul.s	$f8,$f6,$f16
/*  f0240c8:	00000000 */ 	nop
/*  f0240cc:	46104482 */ 	mul.s	$f18,$f8,$f16
/*  f0240d0:	4612703c */ 	c.lt.s	$f14,$f18
/*  f0240d4:	00000000 */ 	nop
/*  f0240d8:	4500003d */ 	bc1f	.L0f0241d0
/*  f0240dc:	00000000 */ 	nop
/*  f0240e0:	c4400010 */ 	lwc1	$f0,0x10($v0)
/*  f0240e4:	44801000 */ 	mtc1	$zero,$f2
/*  f0240e8:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0240ec:	e7a0010c */ 	swc1	$f0,0x10c($sp)
/*  f0240f0:	84590014 */ 	lh	$t9,0x14($v0)
/*  f0240f4:	46001032 */ 	c.eq.s	$f2,$f0
/*  f0240f8:	afb90108 */ 	sw	$t9,0x108($sp)
/*  f0240fc:	c44a0034 */ 	lwc1	$f10,0x34($v0)
/*  f024100:	e7aa0104 */ 	swc1	$f10,0x104($sp)
/*  f024104:	844f0038 */ 	lh	$t7,0x38($v0)
/*  f024108:	45010014 */ 	bc1t	.L0f02415c
/*  f02410c:	afaf0100 */ 	sw	$t7,0x100($sp)
/*  f024110:	c444001c */ 	lwc1	$f4,0x1c($v0)
/*  f024114:	c4460074 */ 	lwc1	$f6,0x74($v0)
/*  f024118:	3c013e80 */ 	lui	$at,0x3e80
/*  f02411c:	44819000 */ 	mtc1	$at,$f18
/*  f024120:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f024124:	3c013f00 */ 	lui	$at,0x3f00
/*  f024128:	4608903e */ 	c.le.s	$f18,$f8
/*  f02412c:	00000000 */ 	nop
/*  f024130:	4502000b */ 	bc1fl	.L0f024160
/*  f024134:	c4440054 */ 	lwc1	$f4,0x54($v0)
/*  f024138:	44815000 */ 	mtc1	$at,$f10
/*  f02413c:	00000000 */ 	nop
/*  f024140:	4600503c */ 	c.lt.s	$f10,$f0
/*  f024144:	00000000 */ 	nop
/*  f024148:	45020004 */ 	bc1fl	.L0f02415c
/*  f02414c:	e4420010 */ 	swc1	$f2,0x10($v0)
/*  f024150:	84480016 */ 	lh	$t0,0x16($v0)
/*  f024154:	a4480014 */ 	sh	$t0,0x14($v0)
/*  f024158:	e4420010 */ 	swc1	$f2,0x10($v0)
.L0f02415c:
/*  f02415c:	c4440054 */ 	lwc1	$f4,0x54($v0)
.L0f024160:
/*  f024160:	46041032 */ 	c.eq.s	$f2,$f4
/*  f024164:	00000000 */ 	nop
/*  f024168:	4503001a */ 	bc1tl	.L0f0241d4
/*  f02416c:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f024170:	c4460040 */ 	lwc1	$f6,0x40($v0)
/*  f024174:	c4480074 */ 	lwc1	$f8,0x74($v0)
/*  f024178:	3c013e80 */ 	lui	$at,0x3e80
/*  f02417c:	44815000 */ 	mtc1	$at,$f10
/*  f024180:	46083482 */ 	mul.s	$f18,$f6,$f8
/*  f024184:	4612503e */ 	c.le.s	$f10,$f18
/*  f024188:	00000000 */ 	nop
/*  f02418c:	45020011 */ 	bc1fl	.L0f0241d4
/*  f024190:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f024194:	c4400034 */ 	lwc1	$f0,0x34($v0)
/*  f024198:	3c013f00 */ 	lui	$at,0x3f00
/*  f02419c:	46001032 */ 	c.eq.s	$f2,$f0
/*  f0241a0:	00000000 */ 	nop
/*  f0241a4:	4503000b */ 	bc1tl	.L0f0241d4
/*  f0241a8:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f0241ac:	44812000 */ 	mtc1	$at,$f4
/*  f0241b0:	00000000 */ 	nop
/*  f0241b4:	4600203c */ 	c.lt.s	$f4,$f0
/*  f0241b8:	00000000 */ 	nop
/*  f0241bc:	45020004 */ 	bc1fl	.L0f0241d0
/*  f0241c0:	e4420034 */ 	swc1	$f2,0x34($v0)
/*  f0241c4:	844e003a */ 	lh	$t6,0x3a($v0)
/*  f0241c8:	a44e0038 */ 	sh	$t6,0x38($v0)
/*  f0241cc:	e4420034 */ 	swc1	$f2,0x34($v0)
.L0f0241d0:
/*  f0241d0:	8fa50208 */ 	lw	$a1,0x208($sp)
.L0f0241d4:
/*  f0241d4:	afa20128 */ 	sw	$v0,0x128($sp)
/*  f0241d8:	0c0073af */ 	jal	func0001cebc
/*  f0241dc:	afa60110 */ 	sw	$a2,0x110($sp)
/*  f0241e0:	8fa60110 */ 	lw	$a2,0x110($sp)
/*  f0241e4:	8fa20128 */ 	lw	$v0,0x128($sp)
/*  f0241e8:	c7a6010c */ 	lwc1	$f6,0x10c($sp)
/*  f0241ec:	10c00008 */ 	beqz	$a2,.L0f024210
/*  f0241f0:	3c018006 */ 	lui	$at,%hi(var8005efcc)
/*  f0241f4:	e4460010 */ 	swc1	$f6,0x10($v0)
/*  f0241f8:	8fa90108 */ 	lw	$t1,0x108($sp)
/*  f0241fc:	a4490014 */ 	sh	$t1,0x14($v0)
/*  f024200:	c7a80104 */ 	lwc1	$f8,0x104($sp)
/*  f024204:	e4480034 */ 	swc1	$f8,0x34($v0)
/*  f024208:	8faa0100 */ 	lw	$t2,0x100($sp)
/*  f02420c:	a44a0038 */ 	sh	$t2,0x38($v0)
.L0f024210:
/*  f024210:	ac20efcc */ 	sw	$zero,%lo(var8005efcc)($at)
/*  f024214:	3c018006 */ 	lui	$at,%hi(var800629e8)
/*  f024218:	0c006943 */ 	jal	modelSetDistanceScale
/*  f02421c:	c42c29e8 */ 	lwc1	$f12,%lo(var800629e8)($at)
/*  f024220:	8fad01f0 */ 	lw	$t5,0x1f0($sp)
/*  f024224:	260400f8 */ 	addiu	$a0,$s0,0xf8
/*  f024228:	11a00003 */ 	beqz	$t5,.L0f024238
/*  f02422c:	00000000 */ 	nop
/*  f024230:	0fc1a5c4 */ 	jal	colourTween
/*  f024234:	260500fc */ 	addiu	$a1,$s0,0xfc
.L0f024238:
/*  f024238:	0c006a7a */ 	jal	func0001a9e8
/*  f02423c:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f024240:	8fac0250 */ 	lw	$t4,0x250($sp)
/*  f024244:	8d87001c */ 	lw	$a3,0x1c($t4)
/*  f024248:	e5800014 */ 	swc1	$f0,0x14($t4)
/*  f02424c:	50e0000b */ 	beqzl	$a3,.L0f02427c
/*  f024250:	8e030178 */ 	lw	$v1,0x178($s0)
/*  f024254:	8ce20020 */ 	lw	$v0,0x20($a3)
.L0f024258:
/*  f024258:	02002025 */ 	or	$a0,$s0,$zero
/*  f02425c:	00e02825 */ 	or	$a1,$a3,$zero
/*  f024260:	8fa601f0 */ 	lw	$a2,0x1f0($sp)
/*  f024264:	0fc08885 */ 	jal	func0f022214
/*  f024268:	afa201f4 */ 	sw	$v0,0x1f4($sp)
/*  f02426c:	8fa701f4 */ 	lw	$a3,0x1f4($sp)
/*  f024270:	54e0fff9 */ 	bnezl	$a3,.L0f024258
/*  f024274:	8ce20020 */ 	lw	$v0,0x20($a3)
/*  f024278:	8e030178 */ 	lw	$v1,0x178($s0)
.L0f02427c:
/*  f02427c:	5060004d */ 	beqzl	$v1,.L0f0243b4
/*  f024280:	8fab0208 */ 	lw	$t3,0x208($sp)
/*  f024284:	8c620004 */ 	lw	$v0,0x4($v1)
/*  f024288:	8c580018 */ 	lw	$t8,0x18($v0)
/*  f02428c:	afb800f4 */ 	sw	$t8,0xf4($sp)
/*  f024290:	82040006 */ 	lb	$a0,0x6($s0)
/*  f024294:	2881002a */ 	slti	$at,$a0,0x2a
/*  f024298:	14200045 */ 	bnez	$at,.L0f0243b0
/*  f02429c:	2881002b */ 	slti	$at,$a0,0x2b
/*  f0242a0:	10200043 */ 	beqz	$at,.L0f0243b0
/*  f0242a4:	3c198006 */ 	lui	$t9,%hi(var80062a3c)
/*  f0242a8:	27392a3c */ 	addiu	$t9,$t9,%lo(var80062a3c)
/*  f0242ac:	8f210000 */ 	lw	$at,0x0($t9)
/*  f0242b0:	27ab00e8 */ 	addiu	$t3,$sp,0xe8
/*  f0242b4:	8f280004 */ 	lw	$t0,0x4($t9)
/*  f0242b8:	ad610000 */ 	sw	$at,0x0($t3)
/*  f0242bc:	8f210008 */ 	lw	$at,0x8($t9)
/*  f0242c0:	ad680004 */ 	sw	$t0,0x4($t3)
/*  f0242c4:	ad610008 */ 	sw	$at,0x8($t3)
/*  f0242c8:	0fc22f3d */ 	jal	hatGetType
/*  f0242cc:	8e040178 */ 	lw	$a0,0x178($s0)
/*  f0242d0:	afa20058 */ 	sw	$v0,0x58($sp)
/*  f0242d4:	82060006 */ 	lb	$a2,0x6($s0)
/*  f0242d8:	3c017f1b */ 	lui	$at,%hi(var7f1a87d8)
/*  f0242dc:	c43287d8 */ 	lwc1	$f18,%lo(var7f1a87d8)($at)
/*  f0242e0:	24c6ffd6 */ 	addiu	$a2,$a2,-42
/*  f0242e4:	000670c0 */ 	sll	$t6,$a2,0x3
/*  f0242e8:	01c67021 */ 	addu	$t6,$t6,$a2
/*  f0242ec:	00024880 */ 	sll	$t1,$v0,0x2
/*  f0242f0:	000e7100 */ 	sll	$t6,$t6,0x4
/*  f0242f4:	01224823 */ 	subu	$t1,$t1,$v0
/*  f0242f8:	000948c0 */ 	sll	$t1,$t1,0x3
/*  f0242fc:	3c0d8008 */ 	lui	$t5,%hi(var8007dae4)
/*  f024300:	01c95021 */ 	addu	$t2,$t6,$t1
/*  f024304:	25addae4 */ 	addiu	$t5,$t5,%lo(var8007dae4)
/*  f024308:	014d1821 */ 	addu	$v1,$t2,$t5
/*  f02430c:	c4700000 */ 	lwc1	$f16,0x0($v1)
/*  f024310:	c46e0004 */ 	lwc1	$f14,0x4($v1)
/*  f024314:	c46c0008 */ 	lwc1	$f12,0x8($v1)
/*  f024318:	46128402 */ 	mul.s	$f16,$f16,$f18
/*  f02431c:	c46a000c */ 	lwc1	$f10,0xc($v1)
/*  f024320:	c4680010 */ 	lwc1	$f8,0x10($v1)
/*  f024324:	46127382 */ 	mul.s	$f14,$f14,$f18
/*  f024328:	c4660014 */ 	lwc1	$f6,0x14($v1)
/*  f02432c:	e7aa00e4 */ 	swc1	$f10,0xe4($sp)
/*  f024330:	46126482 */ 	mul.s	$f18,$f12,$f18
/*  f024334:	e7b000e8 */ 	swc1	$f16,0xe8($sp)
/*  f024338:	e7a800e0 */ 	swc1	$f8,0xe0($sp)
/*  f02433c:	e7a600dc */ 	swc1	$f6,0xdc($sp)
/*  f024340:	e7ae00ec */ 	swc1	$f14,0xec($sp)
/*  f024344:	27a400e8 */ 	addiu	$a0,$sp,0xe8
/*  f024348:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f02434c:	0c0059b7 */ 	jal	func000166dc
/*  f024350:	e7b200f0 */ 	swc1	$f18,0xf0($sp)
/*  f024354:	c7ac00e4 */ 	lwc1	$f12,0xe4($sp)
/*  f024358:	0c005789 */ 	jal	func00015e24
/*  f02435c:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f024360:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
/*  f024364:	0c0057a0 */ 	jal	func00015e80
/*  f024368:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f02436c:	c7ac00dc */ 	lwc1	$f12,0xdc($sp)
/*  f024370:	0c0057b7 */ 	jal	func00015edc
/*  f024374:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f024378:	8fac00f4 */ 	lw	$t4,0xf4($sp)
/*  f02437c:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f024380:	27a6005c */ 	addiu	$a2,$sp,0x5c
/*  f024384:	0c0056f9 */ 	jal	func00015be4
/*  f024388:	8d84000c */ 	lw	$a0,0xc($t4)
/*  f02438c:	8fb800f4 */ 	lw	$t8,0xf4($sp)
/*  f024390:	27a4005c */ 	addiu	$a0,$sp,0x5c
/*  f024394:	0c005746 */ 	jal	func00015d18
/*  f024398:	8f05000c */ 	lw	$a1,0xc($t8)
/*  f02439c:	8faf0058 */ 	lw	$t7,0x58($sp)
/*  f0243a0:	24010002 */ 	addiu	$at,$zero,0x2
/*  f0243a4:	55e10003 */ 	bnel	$t7,$at,.L0f0243b4
/*  f0243a8:	8fab0208 */ 	lw	$t3,0x208($sp)
/*  f0243ac:	afa00200 */ 	sw	$zero,0x200($sp)
.L0f0243b0:
/*  f0243b0:	8fab0208 */ 	lw	$t3,0x208($sp)
.L0f0243b4:
/*  f0243b4:	3c198008 */ 	lui	$t9,%hi(g_ModelTypeChr)
/*  f0243b8:	2739ce40 */ 	addiu	$t9,$t9,%lo(g_ModelTypeChr)
/*  f0243bc:	8d640008 */ 	lw	$a0,0x8($t3)
/*  f0243c0:	8c880004 */ 	lw	$t0,0x4($a0)
/*  f0243c4:	5728003e */ 	bnel	$t9,$t0,.L0f0244c0
/*  f0243c8:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f0243cc:	0c006a47 */ 	jal	modelGetPart
/*  f0243d0:	24050004 */ 	addiu	$a1,$zero,0x4
/*  f0243d4:	10400039 */ 	beqz	$v0,.L0f0244bc
/*  f0243d8:	00402825 */ 	or	$a1,$v0,$zero
/*  f0243dc:	944e0000 */ 	lhu	$t6,0x0($v0)
/*  f0243e0:	24010017 */ 	addiu	$at,$zero,0x17
/*  f0243e4:	55c10036 */ 	bnel	$t6,$at,.L0f0244c0
/*  f0243e8:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f0243ec:	0c006a87 */ 	jal	modelGetNodeRwData
/*  f0243f0:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0243f4:	8c490000 */ 	lw	$t1,0x0($v0)
/*  f0243f8:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f0243fc:	51200030 */ 	beqzl	$t1,.L0f0244c0
/*  f024400:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f024404:	0c006a47 */ 	jal	modelGetPart
/*  f024408:	8c440000 */ 	lw	$a0,0x0($v0)
/*  f02440c:	1040002b */ 	beqz	$v0,.L0f0244bc
/*  f024410:	00402825 */ 	or	$a1,$v0,$zero
/*  f024414:	0c006a87 */ 	jal	modelGetNodeRwData
/*  f024418:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f02441c:	8faa0200 */ 	lw	$t2,0x200($sp)
/*  f024420:	10000026 */ 	b	.L0f0244bc
/*  f024424:	ac4a0000 */ 	sw	$t2,0x0($v0)
.L0f024428:
/*  f024428:	304dfffd */ 	andi	$t5,$v0,0xfffd
/*  f02442c:	a18d0001 */ 	sb	$t5,0x1($t4)
/*  f024430:	3c18800a */ 	lui	$t8,%hi(g_Vars+0x29c)
/*  f024434:	8f18a25c */ 	lw	$t8,%lo(g_Vars+0x29c)($t8)
/*  f024438:	3c0f800a */ 	lui	$t7,%hi(g_Vars+0x2a0)
/*  f02443c:	3c0b800a */ 	lui	$t3,%hi(g_Vars+0x284)
/*  f024440:	0702000b */ 	bltzl	$t8,.L0f024470
/*  f024444:	8fae0250 */ 	lw	$t6,0x250($sp)
/*  f024448:	8defa260 */ 	lw	$t7,%lo(g_Vars+0x2a0)($t7)
/*  f02444c:	8d6ba244 */ 	lw	$t3,%lo(g_Vars+0x284)($t3)
/*  f024450:	55eb0007 */ 	bnel	$t7,$t3,.L0f024470
/*  f024454:	8fae0250 */ 	lw	$t6,0x250($sp)
/*  f024458:	8e190014 */ 	lw	$t9,0x14($s0)
/*  f02445c:	3c01ff7f */ 	lui	$at,0xff7f
/*  f024460:	3421ffff */ 	ori	$at,$at,0xffff
/*  f024464:	03214024 */ 	and	$t0,$t9,$at
/*  f024468:	ae080014 */ 	sw	$t0,0x14($s0)
/*  f02446c:	8fae0250 */ 	lw	$t6,0x250($sp)
.L0f024470:
/*  f024470:	8dc7001c */ 	lw	$a3,0x1c($t6)
/*  f024474:	50e0000a */ 	beqzl	$a3,.L0f0244a0
/*  f024478:	920900fc */ 	lbu	$t1,0xfc($s0)
/*  f02447c:	8ce20020 */ 	lw	$v0,0x20($a3)
.L0f024480:
/*  f024480:	00e02025 */ 	or	$a0,$a3,$zero
/*  f024484:	8fa501f0 */ 	lw	$a1,0x1f0($sp)
/*  f024488:	0fc1c1be */ 	jal	func0f0706f8
/*  f02448c:	afa201f4 */ 	sw	$v0,0x1f4($sp)
/*  f024490:	8fa701f4 */ 	lw	$a3,0x1f4($sp)
/*  f024494:	54e0fffa */ 	bnezl	$a3,.L0f024480
/*  f024498:	8ce20020 */ 	lw	$v0,0x20($a3)
/*  f02449c:	920900fc */ 	lbu	$t1,0xfc($s0)
.L0f0244a0:
/*  f0244a0:	920a00fd */ 	lbu	$t2,0xfd($s0)
/*  f0244a4:	920d00fe */ 	lbu	$t5,0xfe($s0)
/*  f0244a8:	920c00ff */ 	lbu	$t4,0xff($s0)
/*  f0244ac:	a20900f8 */ 	sb	$t1,0xf8($s0)
/*  f0244b0:	a20a00f9 */ 	sb	$t2,0xf9($s0)
/*  f0244b4:	a20d00fa */ 	sb	$t5,0xfa($s0)
/*  f0244b8:	a20c00fb */ 	sb	$t4,0xfb($s0)
.L0f0244bc:
/*  f0244bc:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
.L0f0244c0:
/*  f0244c0:	53000013 */ 	beqzl	$t8,.L0f024510
/*  f0244c4:	00001025 */ 	or	$v0,$zero,$zero
/*  f0244c8:	8e0f0018 */ 	lw	$t7,0x18($s0)
/*  f0244cc:	31eb0400 */ 	andi	$t3,$t7,0x400
/*  f0244d0:	5560000f */ 	bnezl	$t3,.L0f024510
/*  f0244d4:	00001025 */ 	or	$v0,$zero,$zero
/*  f0244d8:	8e190014 */ 	lw	$t9,0x14($s0)
/*  f0244dc:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0244e0:	33280001 */ 	andi	$t0,$t9,0x1
/*  f0244e4:	11000007 */ 	beqz	$t0,.L0f024504
/*  f0244e8:	00000000 */ 	nop
/*  f0244ec:	0fc1c1a6 */ 	jal	func0f070698
/*  f0244f0:	00002825 */ 	or	$a1,$zero,$zero
/*  f0244f4:	8e0e0014 */ 	lw	$t6,0x14($s0)
/*  f0244f8:	2401fffe */ 	addiu	$at,$zero,-2
/*  f0244fc:	01c14824 */ 	and	$t1,$t6,$at
/*  f024500:	ae090014 */ 	sw	$t1,0x14($s0)
.L0f024504:
/*  f024504:	0fc1069d */ 	jal	func0f041a74
/*  f024508:	02002025 */ 	or	$a0,$s0,$zero
/*  f02450c:	00001025 */ 	or	$v0,$zero,$zero
.L0f024510:
/*  f024510:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f024514:	8fb00020 */ 	lw	$s0,0x20($sp)
/*  f024518:	27bd0250 */ 	addiu	$sp,$sp,0x250
/*  f02451c:	03e00008 */ 	jr	$ra
/*  f024520:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel func0f023098
.late_rodata
glabel var7f1a87bc
.word 0x40c907a9
glabel var7f1a87c0
.word 0x3d333333
glabel var7f1a87c4
.word 0x3d333333
glabel var7f1a87c8
.word 0x4a742400
glabel var7f1a87cc
.word 0x48ef4200
glabel var7f1a87d0
.word 0x4a742400
glabel var7f1a87d4
.word 0x48ef4200
glabel var7f1a87d8
.word 0x41aa6666
.text
/*  f022b84:	27bdfdb0 */ 	addiu	$sp,$sp,-592
/*  f022b88:	3c0f8006 */ 	lui	$t7,0x8006
/*  f022b8c:	25ef4f0c */ 	addiu	$t7,$t7,0x4f0c
/*  f022b90:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f022b94:	afb00020 */ 	sw	$s0,0x20($sp)
/*  f022b98:	afa40250 */ 	sw	$a0,0x250($sp)
/*  f022b9c:	25e8003c */ 	addiu	$t0,$t7,0x3c
/*  f022ba0:	27ae0210 */ 	addiu	$t6,$sp,0x210
.NB0f022ba4:
/*  f022ba4:	8de10000 */ 	lw	$at,0x0($t7)
/*  f022ba8:	25ef000c */ 	addiu	$t7,$t7,0xc
/*  f022bac:	25ce000c */ 	addiu	$t6,$t6,0xc
/*  f022bb0:	adc1fff4 */ 	sw	$at,-0xc($t6)
/*  f022bb4:	8de1fff8 */ 	lw	$at,-0x8($t7)
/*  f022bb8:	adc1fff8 */ 	sw	$at,-0x8($t6)
/*  f022bbc:	8de1fffc */ 	lw	$at,-0x4($t7)
/*  f022bc0:	15e8fff8 */ 	bne	$t7,$t0,.NB0f022ba4
/*  f022bc4:	adc1fffc */ 	sw	$at,-0x4($t6)
/*  f022bc8:	8de10000 */ 	lw	$at,0x0($t7)
/*  f022bcc:	3c0c800a */ 	lui	$t4,0x800a
/*  f022bd0:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f022bd4:	adc10000 */ 	sw	$at,0x0($t6)
/*  f022bd8:	8fa90250 */ 	lw	$t1,0x250($sp)
/*  f022bdc:	8d8ce6f4 */ 	lw	$t4,-0x190c($t4)
/*  f022be0:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f022be4:	8d300004 */ 	lw	$s0,0x4($t1)
/*  f022be8:	3c09800a */ 	lui	$t1,0x800a
/*  f022bec:	8e0a0020 */ 	lw	$t2,0x20($s0)
/*  f022bf0:	afab0200 */ 	sw	$t3,0x200($sp)
/*  f022bf4:	afa001f0 */ 	sw	$zero,0x1f0($sp)
/*  f022bf8:	afac01fc */ 	sw	$t4,0x1fc($sp)
/*  f022bfc:	12000004 */ 	beqz	$s0,.NB0f022c10
/*  f022c00:	afaa0208 */ 	sw	$t2,0x208($sp)
/*  f022c04:	920d02fe */ 	lbu	$t5,0x2fe($s0)
/*  f022c08:	10000002 */ 	beqz	$zero,.NB0f022c14
/*  f022c0c:	afad01ec */ 	sw	$t5,0x1ec($sp)
.NB0f022c10:
/*  f022c10:	afa001ec */ 	sw	$zero,0x1ec($sp)
.NB0f022c14:
/*  f022c14:	8fb90250 */ 	lw	$t9,0x250($sp)
/*  f022c18:	93220001 */ 	lbu	$v0,0x1($t9)
/*  f022c1c:	30580008 */ 	andi	$t8,$v0,0x8
/*  f022c20:	13000003 */ 	beqz	$t8,.NB0f022c30
/*  f022c24:	304ffff7 */ 	andi	$t7,$v0,0xfff7
/*  f022c28:	afa801f0 */ 	sw	$t0,0x1f0($sp)
/*  f022c2c:	a32f0001 */ 	sb	$t7,0x1($t9)
.NB0f022c30:
/*  f022c30:	8fae01f0 */ 	lw	$t6,0x1f0($sp)
/*  f022c34:	51c000b4 */ 	beqzl	$t6,.NB0f022f08
/*  f022c38:	8faa01ec */ 	lw	$t2,0x1ec($sp)
/*  f022c3c:	8d29eb8c */ 	lw	$t1,-0x1474($t1)
/*  f022c40:	51200006 */ 	beqzl	$t1,.NB0f022c5c
/*  f022c44:	860a02d8 */ 	lh	$t2,0x2d8($s0)
/*  f022c48:	44802000 */ 	mtc1	$zero,$f4
/*  f022c4c:	a20002e0 */ 	sb	$zero,0x2e0($s0)
/*  f022c50:	1000005d */ 	beqz	$zero,.NB0f022dc8
/*  f022c54:	e60402dc */ 	swc1	$f4,0x2dc($s0)
/*  f022c58:	860a02d8 */ 	lh	$t2,0x2d8($s0)
.NB0f022c5c:
/*  f022c5c:	294103e9 */ 	slti	$at,$t2,0x3e9
/*  f022c60:	54200022 */ 	bnezl	$at,.NB0f022cec
/*  f022c64:	c60002dc */ 	lwc1	$f0,0x2dc($s0)
/*  f022c68:	820b0007 */ 	lb	$t3,0x7($s0)
/*  f022c6c:	2401001f */ 	addiu	$at,$zero,0x1f
/*  f022c70:	3c0d800a */ 	lui	$t5,0x800a
/*  f022c74:	5161001d */ 	beql	$t3,$at,.NB0f022cec
/*  f022c78:	c60002dc */ 	lwc1	$f0,0x2dc($s0)
/*  f022c7c:	8dade6f4 */ 	lw	$t5,-0x190c($t5)
/*  f022c80:	920c02e0 */ 	lbu	$t4,0x2e0($s0)
/*  f022c84:	3c014f80 */ 	lui	$at,0x4f80
/*  f022c88:	000dc043 */ 	sra	$t8,$t5,0x1
/*  f022c8c:	01984021 */ 	addu	$t0,$t4,$t8
/*  f022c90:	310f00ff */ 	andi	$t7,$t0,0xff
/*  f022c94:	448f3000 */ 	mtc1	$t7,$f6
/*  f022c98:	a20802e0 */ 	sb	$t0,0x2e0($s0)
/*  f022c9c:	05e10004 */ 	bgez	$t7,.NB0f022cb0
/*  f022ca0:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f022ca4:	44815000 */ 	mtc1	$at,$f10
/*  f022ca8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022cac:	460a4200 */ 	add.s	$f8,$f8,$f10
.NB0f022cb0:
/*  f022cb0:	3c01437f */ 	lui	$at,0x437f
/*  f022cb4:	44819000 */ 	mtc1	$at,$f18
/*  f022cb8:	3c017f1a */ 	lui	$at,0x7f1a
/*  f022cbc:	c426244c */ 	lwc1	$f6,0x244c($at)
/*  f022cc0:	46124103 */ 	div.s	$f4,$f8,$f18
/*  f022cc4:	46062302 */ 	mul.s	$f12,$f4,$f6
/*  f022cc8:	0c006d52 */ 	jal	cosf
/*  f022ccc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022cd0:	3c0141a0 */ 	lui	$at,0x41a0
/*  f022cd4:	44815000 */ 	mtc1	$at,$f10
/*  f022cd8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022cdc:	460a0202 */ 	mul.s	$f8,$f0,$f10
/*  f022ce0:	10000039 */ 	beqz	$zero,.NB0f022dc8
/*  f022ce4:	e60802dc */ 	swc1	$f8,0x2dc($s0)
/*  f022ce8:	c60002dc */ 	lwc1	$f0,0x2dc($s0)
.NB0f022cec:
/*  f022cec:	44809000 */ 	mtc1	$zero,$f18
/*  f022cf0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022cf4:	46009032 */ 	c.eq.s	$f18,$f0
/*  f022cf8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022cfc:	45010032 */ 	bc1t	.NB0f022dc8
/*  f022d00:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022d04:	44802000 */ 	mtc1	$zero,$f4
/*  f022d08:	a20002e0 */ 	sb	$zero,0x2e0($s0)
/*  f022d0c:	3c19800a */ 	lui	$t9,0x800a
/*  f022d10:	4600203c */ 	c.lt.s	$f4,$f0
/*  f022d14:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022d18:	45020014 */ 	bc1fl	.NB0f022d6c
/*  f022d1c:	44809000 */ 	mtc1	$zero,$f18
/*  f022d20:	8f39e6f4 */ 	lw	$t9,-0x190c($t9)
/*  f022d24:	3c017f1a */ 	lui	$at,0x7f1a
/*  f022d28:	c4262450 */ 	lwc1	$f6,0x2450($at)
/*  f022d2c:	44995000 */ 	mtc1	$t9,$f10
/*  f022d30:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022d34:	46805220 */ 	cvt.s.w	$f8,$f10
/*  f022d38:	46083482 */ 	mul.s	$f18,$f6,$f8
/*  f022d3c:	44803000 */ 	mtc1	$zero,$f6
/*  f022d40:	46120101 */ 	sub.s	$f4,$f0,$f18
/*  f022d44:	e60402dc */ 	swc1	$f4,0x2dc($s0)
/*  f022d48:	c60a02dc */ 	lwc1	$f10,0x2dc($s0)
/*  f022d4c:	4606503c */ 	c.lt.s	$f10,$f6
/*  f022d50:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022d54:	4500001c */ 	bc1f	.NB0f022dc8
/*  f022d58:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022d5c:	44804000 */ 	mtc1	$zero,$f8
/*  f022d60:	10000019 */ 	beqz	$zero,.NB0f022dc8
/*  f022d64:	e60802dc */ 	swc1	$f8,0x2dc($s0)
/*  f022d68:	44809000 */ 	mtc1	$zero,$f18
.NB0f022d6c:
/*  f022d6c:	3c0e800a */ 	lui	$t6,0x800a
/*  f022d70:	4612003c */ 	c.lt.s	$f0,$f18
/*  f022d74:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022d78:	45000013 */ 	bc1f	.NB0f022dc8
/*  f022d7c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022d80:	8dcee6f4 */ 	lw	$t6,-0x190c($t6)
/*  f022d84:	3c017f1a */ 	lui	$at,0x7f1a
/*  f022d88:	c4242454 */ 	lwc1	$f4,0x2454($at)
/*  f022d8c:	448e5000 */ 	mtc1	$t6,$f10
/*  f022d90:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022d94:	468051a0 */ 	cvt.s.w	$f6,$f10
/*  f022d98:	44805000 */ 	mtc1	$zero,$f10
/*  f022d9c:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f022da0:	46080480 */ 	add.s	$f18,$f0,$f8
/*  f022da4:	e61202dc */ 	swc1	$f18,0x2dc($s0)
/*  f022da8:	c60402dc */ 	lwc1	$f4,0x2dc($s0)
/*  f022dac:	4604503c */ 	c.lt.s	$f10,$f4
/*  f022db0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022db4:	45000004 */ 	bc1f	.NB0f022dc8
/*  f022db8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022dbc:	44803000 */ 	mtc1	$zero,$f6
/*  f022dc0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022dc4:	e60602dc */ 	swc1	$f6,0x2dc($s0)
.NB0f022dc8:
/*  f022dc8:	0fc08844 */ 	jal	chrUpdateCloak
/*  f022dcc:	02002025 */ 	or	$a0,$s0,$zero
/*  f022dd0:	0fc08a13 */ 	jal	chrTickPoisoned
/*  f022dd4:	02002025 */ 	or	$a0,$s0,$zero
/*  f022dd8:	8e020018 */ 	lw	$v0,0x18($s0)
/*  f022ddc:	3c0b8006 */ 	lui	$t3,0x8006
/*  f022de0:	30490400 */ 	andi	$t1,$v0,0x400
/*  f022de4:	11200003 */ 	beqz	$t1,.NB0f022df4
/*  f022de8:	00025340 */ 	sll	$t2,$v0,0xd
/*  f022dec:	05430039 */ 	bgezl	$t2,.NB0f022ed4
/*  f022df0:	8e020014 */ 	lw	$v0,0x14($s0)
.NB0f022df4:
/*  f022df4:	8d6b4e7c */ 	lw	$t3,0x4e7c($t3)
/*  f022df8:	3c048006 */ 	lui	$a0,0x8006
/*  f022dfc:	11600022 */ 	beqz	$t3,.NB0f022e88
/*  f022e00:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022e04:	0c0092dd */ 	jal	func00023794
/*  f022e08:	84844e82 */ 	lh	$a0,0x4e82($a0)
/*  f022e0c:	10400025 */ 	beqz	$v0,.NB0f022ea4
/*  f022e10:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022e14:	0c00786f */ 	jal	modelGetAnimNum
/*  f022e18:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f022e1c:	3c038006 */ 	lui	$v1,0x8006
/*  f022e20:	8c634e80 */ 	lw	$v1,0x4e80($v1)
/*  f022e24:	5443000b */ 	bnel	$v0,$v1,.NB0f022e54
/*  f022e28:	44800000 */ 	mtc1	$zero,$f0
/*  f022e2c:	0c00786f */ 	jal	modelGetAnimNum
/*  f022e30:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f022e34:	00022400 */ 	sll	$a0,$v0,0x10
/*  f022e38:	00046c03 */ 	sra	$t5,$a0,0x10
/*  f022e3c:	0c0092dd */ 	jal	func00023794
/*  f022e40:	01a02025 */ 	or	$a0,$t5,$zero
/*  f022e44:	14400017 */ 	bnez	$v0,.NB0f022ea4
/*  f022e48:	3c038006 */ 	lui	$v1,0x8006
/*  f022e4c:	8c634e80 */ 	lw	$v1,0x4e80($v1)
/*  f022e50:	44800000 */ 	mtc1	$zero,$f0
.NB0f022e54:
/*  f022e54:	3c013f00 */ 	lui	$at,0x3f00
/*  f022e58:	44814000 */ 	mtc1	$at,$f8
/*  f022e5c:	00032c00 */ 	sll	$a1,$v1,0x10
/*  f022e60:	00056403 */ 	sra	$t4,$a1,0x10
/*  f022e64:	44070000 */ 	mfc1	$a3,$f0
/*  f022e68:	01802825 */ 	or	$a1,$t4,$zero
/*  f022e6c:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f022e70:	00003025 */ 	or	$a2,$zero,$zero
/*  f022e74:	e7a00014 */ 	swc1	$f0,0x14($sp)
/*  f022e78:	0c007b53 */ 	jal	modelSetAnimation
/*  f022e7c:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*  f022e80:	10000008 */ 	beqz	$zero,.NB0f022ea4
/*  f022e84:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f022e88:
/*  f022e88:	0fc11cec */ 	jal	chrTick
/*  f022e8c:	02002025 */ 	or	$a0,$s0,$zero
/*  f022e90:	8e180020 */ 	lw	$t8,0x20($s0)
/*  f022e94:	17000003 */ 	bnez	$t8,.NB0f022ea4
/*  f022e98:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022e9c:	10000423 */ 	beqz	$zero,.NB0f023f2c
/*  f022ea0:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f022ea4:
/*  f022ea4:	3c088006 */ 	lui	$t0,0x8006
/*  f022ea8:	8d084e84 */ 	lw	$t0,0x4e84($t0)
/*  f022eac:	3c0f8006 */ 	lui	$t7,0x8006
/*  f022eb0:	51000008 */ 	beqzl	$t0,.NB0f022ed4
/*  f022eb4:	8e020014 */ 	lw	$v0,0x14($s0)
/*  f022eb8:	8def4e88 */ 	lw	$t7,0x4e88($t7)
/*  f022ebc:	afa001fc */ 	sw	$zero,0x1fc($sp)
/*  f022ec0:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f022ec4:	51e00003 */ 	beqzl	$t7,.NB0f022ed4
/*  f022ec8:	8e020014 */ 	lw	$v0,0x14($s0)
/*  f022ecc:	afb901fc */ 	sw	$t9,0x1fc($sp)
/*  f022ed0:	8e020014 */ 	lw	$v0,0x14($s0)
.NB0f022ed4:
/*  f022ed4:	304e0020 */ 	andi	$t6,$v0,0x20
/*  f022ed8:	11c0000a */ 	beqz	$t6,.NB0f022f04
/*  f022edc:	30490001 */ 	andi	$t1,$v0,0x1
/*  f022ee0:	11200003 */ 	beqz	$t1,.NB0f022ef0
/*  f022ee4:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f022ee8:	0fc1bd25 */ 	jal	func0f070698
/*  f022eec:	24050001 */ 	addiu	$a1,$zero,0x1
.NB0f022ef0:
/*  f022ef0:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f022ef4:	0fc08221 */ 	jal	func0f020d44
/*  f022ef8:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f022efc:	1000040b */ 	beqz	$zero,.NB0f023f2c
/*  f022f00:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f022f04:
/*  f022f04:	8faa01ec */ 	lw	$t2,0x1ec($sp)
.NB0f022f08:
/*  f022f08:	24010003 */ 	addiu	$at,$zero,0x3
/*  f022f0c:	55410026 */ 	bnel	$t2,$at,.NB0f022fa8
/*  f022f10:	8e020018 */ 	lw	$v0,0x18($s0)
/*  f022f14:	0fc0ee10 */ 	jal	chrToEyespy
/*  f022f18:	02002025 */ 	or	$a0,$s0,$zero
/*  f022f1c:	1040001f */ 	beqz	$v0,.NB0f022f9c
/*  f022f20:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022f24:	904b0035 */ 	lbu	$t3,0x35($v0)
/*  f022f28:	3c0d800a */ 	lui	$t5,0x800a
/*  f022f2c:	1160001b */ 	beqz	$t3,.NB0f022f9c
/*  f022f30:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022f34:	8dade944 */ 	lw	$t5,-0x16bc($t5)
/*  f022f38:	8dac0480 */ 	lw	$t4,0x480($t5)
/*  f022f3c:	144c0006 */ 	bne	$v0,$t4,.NB0f022f58
/*  f022f40:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022f44:	80580037 */ 	lb	$t8,0x37($v0)
/*  f022f48:	13000003 */ 	beqz	$t8,.NB0f022f58
/*  f022f4c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f022f50:	10000009 */ 	beqz	$zero,.NB0f022f78
/*  f022f54:	00003825 */ 	or	$a3,$zero,$zero
.NB0f022f58:
/*  f022f58:	0c007000 */ 	jal	func0001af80
/*  f022f5c:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f022f60:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f022f64:	44060000 */ 	mfc1	$a2,$f0
/*  f022f68:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f022f6c:	0fc2341b */ 	jal	func0f08e8ac
/*  f022f70:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f022f74:	00403825 */ 	or	$a3,$v0,$zero
.NB0f022f78:
/*  f022f78:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
/*  f022f7c:	02002025 */ 	or	$a0,$s0,$zero
/*  f022f80:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f022f84:	11e001c9 */ 	beqz	$t7,.NB0f0236ac
/*  f022f88:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f022f8c:	0fc08709 */ 	jal	func0f0220ec
/*  f022f90:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f022f94:	100001c5 */ 	beqz	$zero,.NB0f0236ac
/*  f022f98:	8fa70204 */ 	lw	$a3,0x204($sp)
.NB0f022f9c:
/*  f022f9c:	100001c3 */ 	beqz	$zero,.NB0f0236ac
/*  f022fa0:	00003825 */ 	or	$a3,$zero,$zero
/*  f022fa4:	8e020018 */ 	lw	$v0,0x18($s0)
.NB0f022fa8:
/*  f022fa8:	30590400 */ 	andi	$t9,$v0,0x400
/*  f022fac:	13200003 */ 	beqz	$t9,.NB0f022fbc
/*  f022fb0:	00027200 */ 	sll	$t6,$v0,0x8
/*  f022fb4:	100001bd */ 	beqz	$zero,.NB0f0236ac
/*  f022fb8:	00003825 */ 	or	$a3,$zero,$zero
.NB0f022fbc:
/*  f022fbc:	05c00017 */ 	bltz	$t6,.NB0f02301c
/*  f022fc0:	8fa90250 */ 	lw	$t1,0x250($sp)
/*  f022fc4:	912a0000 */ 	lbu	$t2,0x0($t1)
/*  f022fc8:	24010006 */ 	addiu	$at,$zero,0x6
/*  f022fcc:	55410068 */ 	bnel	$t2,$at,.NB0f023170
/*  f022fd0:	82030007 */ 	lb	$v1,0x7($s0)
/*  f022fd4:	0fc48d6f */ 	jal	propGetPlayerNum
/*  f022fd8:	01202025 */ 	or	$a0,$t1,$zero
/*  f022fdc:	00025880 */ 	sll	$t3,$v0,0x2
/*  f022fe0:	3c03800a */ 	lui	$v1,0x800a
/*  f022fe4:	006b1821 */ 	addu	$v1,$v1,$t3
/*  f022fe8:	3c0d800a */ 	lui	$t5,0x800a
/*  f022fec:	8dade944 */ 	lw	$t5,-0x16bc($t5)
/*  f022ff0:	8c63e724 */ 	lw	$v1,-0x18dc($v1)
/*  f022ff4:	546d005e */ 	bnel	$v1,$t5,.NB0f023170
/*  f022ff8:	82030007 */ 	lb	$v1,0x7($s0)
/*  f022ffc:	8c6c0000 */ 	lw	$t4,0x0($v1)
/*  f023000:	24010001 */ 	addiu	$at,$zero,0x1
/*  f023004:	5581005a */ 	bnel	$t4,$at,.NB0f023170
/*  f023008:	82030007 */ 	lb	$v1,0x7($s0)
/*  f02300c:	94780010 */ 	lhu	$t8,0x10($v1)
/*  f023010:	24010002 */ 	addiu	$at,$zero,0x2
/*  f023014:	53010056 */ 	beql	$t8,$at,.NB0f023170
/*  f023018:	82030007 */ 	lb	$v1,0x7($s0)
.NB0f02301c:
/*  f02301c:	8fa801f0 */ 	lw	$t0,0x1f0($sp)
/*  f023020:	00003825 */ 	or	$a3,$zero,$zero
/*  f023024:	8faf0208 */ 	lw	$t7,0x208($sp)
/*  f023028:	5100001b */ 	beqzl	$t0,.NB0f023098
/*  f02302c:	8e030020 */ 	lw	$v1,0x20($s0)
/*  f023030:	8df90020 */ 	lw	$t9,0x20($t7)
/*  f023034:	24010003 */ 	addiu	$at,$zero,0x3
/*  f023038:	02002025 */ 	or	$a0,$s0,$zero
/*  f02303c:	a320000b */ 	sb	$zero,0xb($t9)
/*  f023040:	820e0007 */ 	lb	$t6,0x7($s0)
/*  f023044:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023048:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f02304c:	15c1000e */ 	bne	$t6,$at,.NB0f023088
/*  f023050:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023054:	8e0a002c */ 	lw	$t2,0x2c($s0)
/*  f023058:	1540000b */ 	bnez	$t2,.NB0f023088
/*  f02305c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023060:	8e09003c */ 	lw	$t1,0x3c($s0)
/*  f023064:	11200008 */ 	beqz	$t1,.NB0f023088
/*  f023068:	00000000 */ 	sll	$zero,$zero,0x0
/*  f02306c:	02002025 */ 	or	$a0,$s0,$zero
/*  f023070:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023074:	00003025 */ 	or	$a2,$zero,$zero
/*  f023078:	0fc08709 */ 	jal	func0f0220ec
/*  f02307c:	afa001a0 */ 	sw	$zero,0x1a0($sp)
/*  f023080:	10000004 */ 	beqz	$zero,.NB0f023094
/*  f023084:	8fa701a0 */ 	lw	$a3,0x1a0($sp)
.NB0f023088:
/*  f023088:	0fc08709 */ 	jal	func0f0220ec
/*  f02308c:	afa701a0 */ 	sw	$a3,0x1a0($sp)
/*  f023090:	8fa701a0 */ 	lw	$a3,0x1a0($sp)
.NB0f023094:
/*  f023094:	8e030020 */ 	lw	$v1,0x20($s0)
.NB0f023098:
/*  f023098:	1060002c */ 	beqz	$v1,.NB0f02314c
/*  f02309c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0230a0:	8c620020 */ 	lw	$v0,0x20($v1)
/*  f0230a4:	10400029 */ 	beqz	$v0,.NB0f02314c
/*  f0230a8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0230ac:	84440000 */ 	lh	$a0,0x0($v0)
/*  f0230b0:	3c0b8006 */ 	lui	$t3,0x8006
/*  f0230b4:	8d6b151c */ 	lw	$t3,0x151c($t3)
/*  f0230b8:	00046880 */ 	sll	$t5,$a0,0x2
/*  f0230bc:	01a46823 */ 	subu	$t5,$t5,$a0
/*  f0230c0:	000d6880 */ 	sll	$t5,$t5,0x2
/*  f0230c4:	016d6021 */ 	addu	$t4,$t3,$t5
/*  f0230c8:	9198000b */ 	lbu	$t8,0xb($t4)
/*  f0230cc:	33080004 */ 	andi	$t0,$t8,0x4
/*  f0230d0:	1100001e */ 	beqz	$t0,.NB0f02314c
/*  f0230d4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0230d8:	0c009446 */ 	jal	func00023d38
/*  f0230dc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0230e0:	8e0f0020 */ 	lw	$t7,0x20($s0)
/*  f0230e4:	8de20020 */ 	lw	$v0,0x20($t7)
/*  f0230e8:	84440000 */ 	lh	$a0,0x0($v0)
/*  f0230ec:	0c00930b */ 	jal	func0002384c
/*  f0230f0:	84450014 */ 	lh	$a1,0x14($v0)
/*  f0230f4:	28440000 */ 	slti	$a0,$v0,0x0
/*  f0230f8:	54800014 */ 	bnezl	$a0,.NB0f02314c
/*  f0230fc:	00803825 */ 	or	$a3,$a0,$zero
/*  f023100:	8e190020 */ 	lw	$t9,0x20($s0)
/*  f023104:	8f220020 */ 	lw	$v0,0x20($t9)
/*  f023108:	84440000 */ 	lh	$a0,0x0($v0)
/*  f02310c:	0c00930b */ 	jal	func0002384c
/*  f023110:	84450016 */ 	lh	$a1,0x16($v0)
/*  f023114:	28440000 */ 	slti	$a0,$v0,0x0
/*  f023118:	5080000c */ 	beqzl	$a0,.NB0f02314c
/*  f02311c:	00803825 */ 	or	$a3,$a0,$zero
/*  f023120:	8e0e0020 */ 	lw	$t6,0x20($s0)
/*  f023124:	44809000 */ 	mtc1	$zero,$f18
/*  f023128:	00002025 */ 	or	$a0,$zero,$zero
/*  f02312c:	8dca0020 */ 	lw	$t2,0x20($t6)
/*  f023130:	c54a0010 */ 	lwc1	$f10,0x10($t2)
/*  f023134:	460a9032 */ 	c.eq.s	$f18,$f10
/*  f023138:	00000000 */ 	sll	$zero,$zero,0x0
/*  f02313c:	45030003 */ 	bc1tl	.NB0f02314c
/*  f023140:	00803825 */ 	or	$a3,$a0,$zero
/*  f023144:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f023148:	00803825 */ 	or	$a3,$a0,$zero
.NB0f02314c:
/*  f02314c:	10e00003 */ 	beqz	$a3,.NB0f02315c
/*  f023150:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023154:	10000155 */ 	beqz	$zero,.NB0f0236ac
/*  f023158:	00003825 */ 	or	$a3,$zero,$zero
.NB0f02315c:
/*  f02315c:	0fc23469 */ 	jal	posIsInDrawDistance
/*  f023160:	24840008 */ 	addiu	$a0,$a0,0x8
/*  f023164:	10000151 */ 	beqz	$zero,.NB0f0236ac
/*  f023168:	00403825 */ 	or	$a3,$v0,$zero
/*  f02316c:	82030007 */ 	lb	$v1,0x7($s0)
.NB0f023170:
/*  f023170:	2401000e */ 	addiu	$at,$zero,0xe
/*  f023174:	10610002 */ 	beq	$v1,$at,.NB0f023180
/*  f023178:	2401000f */ 	addiu	$at,$zero,0xf
/*  f02317c:	14610046 */ 	bne	$v1,$at,.NB0f023298
.NB0f023180:
/*  f023180:	2401000e */ 	addiu	$at,$zero,0xe
/*  f023184:	54610005 */ 	bnel	$v1,$at,.NB0f02319c
/*  f023188:	2401000f */ 	addiu	$at,$zero,0xf
/*  f02318c:	82090038 */ 	lb	$t1,0x38($s0)
/*  f023190:	24010006 */ 	addiu	$at,$zero,0x6
/*  f023194:	11210007 */ 	beq	$t1,$at,.NB0f0231b4
/*  f023198:	2401000f */ 	addiu	$at,$zero,0xf
.NB0f02319c:
/*  f02319c:	14610018 */ 	bne	$v1,$at,.NB0f023200
/*  f0231a0:	8fa801f0 */ 	lw	$t0,0x1f0($sp)
/*  f0231a4:	820b0068 */ 	lb	$t3,0x68($s0)
/*  f0231a8:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0231ac:	15610014 */ 	bne	$t3,$at,.NB0f023200
/*  f0231b0:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f0231b4:
/*  f0231b4:	0c007000 */ 	jal	func0001af80
/*  f0231b8:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0231bc:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0231c0:	44060000 */ 	mfc1	$a2,$f0
/*  f0231c4:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f0231c8:	0fc2341b */ 	jal	func0f08e8ac
/*  f0231cc:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f0231d0:	10400136 */ 	beqz	$v0,.NB0f0236ac
/*  f0231d4:	00403825 */ 	or	$a3,$v0,$zero
/*  f0231d8:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0231dc:	260500c8 */ 	addiu	$a1,$s0,0xc8
/*  f0231e0:	8c980020 */ 	lw	$t8,0x20($a0)
/*  f0231e4:	a300000b */ 	sb	$zero,0xb($t8)
/*  f0231e8:	0c006f63 */ 	jal	modelGetRootPosition
/*  f0231ec:	afa20204 */ 	sw	$v0,0x204($sp)
/*  f0231f0:	0c00710f */ 	jal	func0001b3bc
/*  f0231f4:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0231f8:	1000012c */ 	beqz	$zero,.NB0f0236ac
/*  f0231fc:	8fa70204 */ 	lw	$a3,0x204($sp)
.NB0f023200:
/*  f023200:	11000004 */ 	beqz	$t0,.NB0f023214
/*  f023204:	02002025 */ 	or	$a0,$s0,$zero
/*  f023208:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f02320c:	0fc08709 */ 	jal	func0f0220ec
/*  f023210:	24060001 */ 	addiu	$a2,$zero,0x1
.NB0f023214:
/*  f023214:	0c007000 */ 	jal	func0001af80
/*  f023218:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f02321c:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023220:	44060000 */ 	mfc1	$a2,$f0
/*  f023224:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f023228:	0fc2341b */ 	jal	func0f08e8ac
/*  f02322c:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023230:	1040000e */ 	beqz	$v0,.NB0f02326c
/*  f023234:	00403825 */ 	or	$a3,$v0,$zero
/*  f023238:	82030007 */ 	lb	$v1,0x7($s0)
/*  f02323c:	2401000e */ 	addiu	$at,$zero,0xe
/*  f023240:	3c19800a */ 	lui	$t9,0x800a
/*  f023244:	54610005 */ 	bnel	$v1,$at,.NB0f02325c
/*  f023248:	2401000f */ 	addiu	$at,$zero,0xf
/*  f02324c:	8f39e6c8 */ 	lw	$t9,-0x1938($t9)
/*  f023250:	10000006 */ 	beqz	$zero,.NB0f02326c
/*  f023254:	ae190078 */ 	sw	$t9,0x78($s0)
/*  f023258:	2401000f */ 	addiu	$at,$zero,0xf
.NB0f02325c:
/*  f02325c:	14610003 */ 	bne	$v1,$at,.NB0f02326c
/*  f023260:	3c0e800a */ 	lui	$t6,0x800a
/*  f023264:	8dcee6c8 */ 	lw	$t6,-0x1938($t6)
/*  f023268:	ae0e00a8 */ 	sw	$t6,0xa8($s0)
.NB0f02326c:
/*  f02326c:	2c440001 */ 	sltiu	$a0,$v0,0x1
/*  f023270:	10800006 */ 	beqz	$a0,.NB0f02328c
/*  f023274:	8fad0208 */ 	lw	$t5,0x208($sp)
/*  f023278:	8faa0250 */ 	lw	$t2,0x250($sp)
/*  f02327c:	91440001 */ 	lbu	$a0,0x1($t2)
/*  f023280:	308900c0 */ 	andi	$t1,$a0,0xc0
/*  f023284:	0009582b */ 	sltu	$t3,$zero,$t1
/*  f023288:	2d640001 */ 	sltiu	$a0,$t3,0x1
.NB0f02328c:
/*  f02328c:	8db80020 */ 	lw	$t8,0x20($t5)
/*  f023290:	10000106 */ 	beqz	$zero,.NB0f0236ac
/*  f023294:	a304000b */ 	sb	$a0,0xb($t8)
.NB0f023298:
/*  f023298:	24010003 */ 	addiu	$at,$zero,0x3
/*  f02329c:	54610025 */ 	bnel	$v1,$at,.NB0f023334
/*  f0232a0:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0232a4:	8e0c002c */ 	lw	$t4,0x2c($s0)
/*  f0232a8:	55800022 */ 	bnezl	$t4,.NB0f023334
/*  f0232ac:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0232b0:	0c007000 */ 	jal	func0001af80
/*  f0232b4:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0232b8:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0232bc:	44060000 */ 	mfc1	$a2,$f0
/*  f0232c0:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f0232c4:	0fc2341b */ 	jal	func0f08e8ac
/*  f0232c8:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f0232cc:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
/*  f0232d0:	00403825 */ 	or	$a3,$v0,$zero
/*  f0232d4:	8fb90208 */ 	lw	$t9,0x208($sp)
/*  f0232d8:	51e000f5 */ 	beqzl	$t7,.NB0f0236b0
/*  f0232dc:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
/*  f0232e0:	8f2e0020 */ 	lw	$t6,0x20($t9)
/*  f0232e4:	02002025 */ 	or	$a0,$s0,$zero
/*  f0232e8:	1040000b */ 	beqz	$v0,.NB0f023318
/*  f0232ec:	a1c0000b */ 	sb	$zero,0xb($t6)
/*  f0232f0:	8e0a003c */ 	lw	$t2,0x3c($s0)
/*  f0232f4:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0232f8:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0232fc:	55400007 */ 	bnezl	$t2,.NB0f02331c
/*  f023300:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023304:	02002025 */ 	or	$a0,$s0,$zero
/*  f023308:	0fc08709 */ 	jal	func0f0220ec
/*  f02330c:	afa20204 */ 	sw	$v0,0x204($sp)
/*  f023310:	100000e6 */ 	beqz	$zero,.NB0f0236ac
/*  f023314:	8fa70204 */ 	lw	$a3,0x204($sp)
.NB0f023318:
/*  f023318:	8fa501fc */ 	lw	$a1,0x1fc($sp)
.NB0f02331c:
/*  f02331c:	00003025 */ 	or	$a2,$zero,$zero
/*  f023320:	0fc08709 */ 	jal	func0f0220ec
/*  f023324:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023328:	100000e0 */ 	beqz	$zero,.NB0f0236ac
/*  f02332c:	8fa70204 */ 	lw	$a3,0x204($sp)
/*  f023330:	24010001 */ 	addiu	$at,$zero,0x1
.NB0f023334:
/*  f023334:	14610062 */ 	bne	$v1,$at,.NB0f0234c0
/*  f023338:	8fa90208 */ 	lw	$t1,0x208($sp)
/*  f02333c:	8d2b0020 */ 	lw	$t3,0x20($t1)
/*  f023340:	02002025 */ 	or	$a0,$s0,$zero
/*  f023344:	a160000b */ 	sb	$zero,0xb($t3)
/*  f023348:	8e0d0018 */ 	lw	$t5,0x18($s0)
/*  f02334c:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023350:	31b80001 */ 	andi	$t8,$t5,0x1
/*  f023354:	1300000c */ 	beqz	$t8,.NB0f023388
/*  f023358:	00000000 */ 	sll	$zero,$zero,0x0
/*  f02335c:	0fc08709 */ 	jal	func0f0220ec
/*  f023360:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f023364:	0c007000 */ 	jal	func0001af80
/*  f023368:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f02336c:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023370:	44060000 */ 	mfc1	$a2,$f0
/*  f023374:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f023378:	0fc2341b */ 	jal	func0f08e8ac
/*  f02337c:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023380:	100000ca */ 	beqz	$zero,.NB0f0236ac
/*  f023384:	00403825 */ 	or	$a3,$v0,$zero
.NB0f023388:
/*  f023388:	0c007000 */ 	jal	func0001af80
/*  f02338c:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023390:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023394:	44060000 */ 	mfc1	$a2,$f0
/*  f023398:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f02339c:	0fc2341b */ 	jal	func0f08e8ac
/*  f0233a0:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f0233a4:	3c0f800a */ 	lui	$t7,0x800a
/*  f0233a8:	8defe9d4 */ 	lw	$t7,-0x162c($t7)
/*  f0233ac:	00403825 */ 	or	$a3,$v0,$zero
/*  f0233b0:	8fb901f0 */ 	lw	$t9,0x1f0($sp)
/*  f0233b4:	11e00024 */ 	beqz	$t7,.NB0f023448
/*  f0233b8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0233bc:	132000bb */ 	beqz	$t9,.NB0f0236ac
/*  f0233c0:	3c0e800a */ 	lui	$t6,0x800a
/*  f0233c4:	8dcee958 */ 	lw	$t6,-0x16a8($t6)
/*  f0233c8:	3c0a800a */ 	lui	$t2,0x800a
/*  f0233cc:	05c10006 */ 	bgez	$t6,.NB0f0233e8
/*  f0233d0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0233d4:	8d4ae95c */ 	lw	$t2,-0x16a4($t2)
/*  f0233d8:	02002025 */ 	or	$a0,$s0,$zero
/*  f0233dc:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0233e0:	05400015 */ 	bltz	$t2,.NB0f023438
/*  f0233e4:	24060001 */ 	addiu	$a2,$zero,0x1
.NB0f0233e8:
/*  f0233e8:	10400008 */ 	beqz	$v0,.NB0f02340c
/*  f0233ec:	8fa90208 */ 	lw	$t1,0x208($sp)
/*  f0233f0:	02002025 */ 	or	$a0,$s0,$zero
/*  f0233f4:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0233f8:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0233fc:	0fc08709 */ 	jal	func0f0220ec
/*  f023400:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023404:	100000a9 */ 	beqz	$zero,.NB0f0236ac
/*  f023408:	8fa70204 */ 	lw	$a3,0x204($sp)
.NB0f02340c:
/*  f02340c:	8d2b0020 */ 	lw	$t3,0x20($t1)
/*  f023410:	02002025 */ 	or	$a0,$s0,$zero
/*  f023414:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023418:	856d0002 */ 	lh	$t5,0x2($t3)
/*  f02341c:	00003025 */ 	or	$a2,$zero,$zero
/*  f023420:	51a000a3 */ 	beqzl	$t5,.NB0f0236b0
/*  f023424:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
/*  f023428:	0fc08709 */ 	jal	func0f0220ec
/*  f02342c:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023430:	1000009e */ 	beqz	$zero,.NB0f0236ac
/*  f023434:	8fa70204 */ 	lw	$a3,0x204($sp)
.NB0f023438:
/*  f023438:	0fc08709 */ 	jal	func0f0220ec
/*  f02343c:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023440:	1000009a */ 	beqz	$zero,.NB0f0236ac
/*  f023444:	8fa70204 */ 	lw	$a3,0x204($sp)
.NB0f023448:
/*  f023448:	10400012 */ 	beqz	$v0,.NB0f023494
/*  f02344c:	8fac0208 */ 	lw	$t4,0x208($sp)
/*  f023450:	9218004c */ 	lbu	$t8,0x4c($s0)
/*  f023454:	24010001 */ 	addiu	$at,$zero,0x1
/*  f023458:	02002025 */ 	or	$a0,$s0,$zero
/*  f02345c:	17010008 */ 	bne	$t8,$at,.NB0f023480
/*  f023460:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f023464:	02002025 */ 	or	$a0,$s0,$zero
/*  f023468:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f02346c:	00003025 */ 	or	$a2,$zero,$zero
/*  f023470:	0fc08709 */ 	jal	func0f0220ec
/*  f023474:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023478:	1000008c */ 	beqz	$zero,.NB0f0236ac
/*  f02347c:	8fa70204 */ 	lw	$a3,0x204($sp)
.NB0f023480:
/*  f023480:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f023484:	0fc08709 */ 	jal	func0f0220ec
/*  f023488:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f02348c:	10000087 */ 	beqz	$zero,.NB0f0236ac
/*  f023490:	8fa70204 */ 	lw	$a3,0x204($sp)
.NB0f023494:
/*  f023494:	8d880020 */ 	lw	$t0,0x20($t4)
/*  f023498:	02002025 */ 	or	$a0,$s0,$zero
/*  f02349c:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0234a0:	850f0002 */ 	lh	$t7,0x2($t0)
/*  f0234a4:	00003025 */ 	or	$a2,$zero,$zero
/*  f0234a8:	51e00081 */ 	beqzl	$t7,.NB0f0236b0
/*  f0234ac:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
/*  f0234b0:	0fc08709 */ 	jal	func0f0220ec
/*  f0234b4:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f0234b8:	1000007c */ 	beqz	$zero,.NB0f0236ac
/*  f0234bc:	8fa70204 */ 	lw	$a3,0x204($sp)
.NB0f0234c0:
/*  f0234c0:	24010005 */ 	addiu	$at,$zero,0x5
/*  f0234c4:	1461000a */ 	bne	$v1,$at,.NB0f0234f0
/*  f0234c8:	8fae0250 */ 	lw	$t6,0x250($sp)
/*  f0234cc:	0c007000 */ 	jal	func0001af80
/*  f0234d0:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f0234d4:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f0234d8:	44060000 */ 	mfc1	$a2,$f0
/*  f0234dc:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f0234e0:	0fc2341b */ 	jal	func0f08e8ac
/*  f0234e4:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f0234e8:	10000070 */ 	beqz	$zero,.NB0f0236ac
/*  f0234ec:	00403825 */ 	or	$a3,$v0,$zero
.NB0f0234f0:
/*  f0234f0:	91ca0000 */ 	lbu	$t2,0x0($t6)
/*  f0234f4:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0234f8:	3c09800a */ 	lui	$t1,0x800a
/*  f0234fc:	55410025 */ 	bnel	$t2,$at,.NB0f023594
/*  f023500:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
/*  f023504:	8d29e9d4 */ 	lw	$t1,-0x162c($t1)
/*  f023508:	55200012 */ 	bnezl	$t1,.NB0f023554
/*  f02350c:	8fb80208 */ 	lw	$t8,0x208($sp)
/*  f023510:	0fc48d6f */ 	jal	propGetPlayerNum
/*  f023514:	01c02025 */ 	or	$a0,$t6,$zero
/*  f023518:	00025880 */ 	sll	$t3,$v0,0x2
/*  f02351c:	3c03800a */ 	lui	$v1,0x800a
/*  f023520:	006b1821 */ 	addu	$v1,$v1,$t3
/*  f023524:	8c63e724 */ 	lw	$v1,-0x18dc($v1)
/*  f023528:	24010002 */ 	addiu	$at,$zero,0x2
/*  f02352c:	8c640000 */ 	lw	$a0,0x0($v1)
/*  f023530:	10810007 */ 	beq	$a0,$at,.NB0f023550
/*  f023534:	24010001 */ 	addiu	$at,$zero,0x1
/*  f023538:	54810016 */ 	bnel	$a0,$at,.NB0f023594
/*  f02353c:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
/*  f023540:	946d0010 */ 	lhu	$t5,0x10($v1)
/*  f023544:	24010002 */ 	addiu	$at,$zero,0x2
/*  f023548:	55a10012 */ 	bnel	$t5,$at,.NB0f023594
/*  f02354c:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
.NB0f023550:
/*  f023550:	8fb80208 */ 	lw	$t8,0x208($sp)
.NB0f023554:
/*  f023554:	02002025 */ 	or	$a0,$s0,$zero
/*  f023558:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f02355c:	8f0c0020 */ 	lw	$t4,0x20($t8)
/*  f023560:	a180000b */ 	sb	$zero,0xb($t4)
/*  f023564:	0fc08709 */ 	jal	func0f0220ec
/*  f023568:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f02356c:	0c007000 */ 	jal	func0001af80
/*  f023570:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023574:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023578:	44060000 */ 	mfc1	$a2,$f0
/*  f02357c:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f023580:	0fc2341b */ 	jal	func0f08e8ac
/*  f023584:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f023588:	10000048 */ 	beqz	$zero,.NB0f0236ac
/*  f02358c:	00403825 */ 	or	$a3,$v0,$zero
/*  f023590:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
.NB0f023594:
/*  f023594:	00003825 */ 	or	$a3,$zero,$zero
/*  f023598:	8fb90208 */ 	lw	$t9,0x208($sp)
/*  f02359c:	51e0000a */ 	beqzl	$t7,.NB0f0235c8
/*  f0235a0:	8e030020 */ 	lw	$v1,0x20($s0)
/*  f0235a4:	8f2a0020 */ 	lw	$t2,0x20($t9)
/*  f0235a8:	02002025 */ 	or	$a0,$s0,$zero
/*  f0235ac:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0235b0:	a140000b */ 	sb	$zero,0xb($t2)
/*  f0235b4:	afa0019c */ 	sw	$zero,0x19c($sp)
/*  f0235b8:	0fc08709 */ 	jal	func0f0220ec
/*  f0235bc:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f0235c0:	8fa7019c */ 	lw	$a3,0x19c($sp)
/*  f0235c4:	8e030020 */ 	lw	$v1,0x20($s0)
.NB0f0235c8:
/*  f0235c8:	1060002c */ 	beqz	$v1,.NB0f02367c
/*  f0235cc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0235d0:	8c620020 */ 	lw	$v0,0x20($v1)
/*  f0235d4:	10400029 */ 	beqz	$v0,.NB0f02367c
/*  f0235d8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0235dc:	84440000 */ 	lh	$a0,0x0($v0)
/*  f0235e0:	3c098006 */ 	lui	$t1,0x8006
/*  f0235e4:	8d29151c */ 	lw	$t1,0x151c($t1)
/*  f0235e8:	00047080 */ 	sll	$t6,$a0,0x2
/*  f0235ec:	01c47023 */ 	subu	$t6,$t6,$a0
/*  f0235f0:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f0235f4:	012e5821 */ 	addu	$t3,$t1,$t6
/*  f0235f8:	916d000b */ 	lbu	$t5,0xb($t3)
/*  f0235fc:	31b80004 */ 	andi	$t8,$t5,0x4
/*  f023600:	1300001e */ 	beqz	$t8,.NB0f02367c
/*  f023604:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023608:	0c009446 */ 	jal	func00023d38
/*  f02360c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023610:	8e0c0020 */ 	lw	$t4,0x20($s0)
/*  f023614:	8d820020 */ 	lw	$v0,0x20($t4)
/*  f023618:	84440000 */ 	lh	$a0,0x0($v0)
/*  f02361c:	0c00930b */ 	jal	func0002384c
/*  f023620:	84450014 */ 	lh	$a1,0x14($v0)
/*  f023624:	28440000 */ 	slti	$a0,$v0,0x0
/*  f023628:	54800014 */ 	bnezl	$a0,.NB0f02367c
/*  f02362c:	00803825 */ 	or	$a3,$a0,$zero
/*  f023630:	8e080020 */ 	lw	$t0,0x20($s0)
/*  f023634:	8d020020 */ 	lw	$v0,0x20($t0)
/*  f023638:	84440000 */ 	lh	$a0,0x0($v0)
/*  f02363c:	0c00930b */ 	jal	func0002384c
/*  f023640:	84450016 */ 	lh	$a1,0x16($v0)
/*  f023644:	28440000 */ 	slti	$a0,$v0,0x0
/*  f023648:	5080000c */ 	beqzl	$a0,.NB0f02367c
/*  f02364c:	00803825 */ 	or	$a3,$a0,$zero
/*  f023650:	8e0f0020 */ 	lw	$t7,0x20($s0)
/*  f023654:	44802000 */ 	mtc1	$zero,$f4
/*  f023658:	00002025 */ 	or	$a0,$zero,$zero
/*  f02365c:	8df90020 */ 	lw	$t9,0x20($t7)
/*  f023660:	c7260010 */ 	lwc1	$f6,0x10($t9)
/*  f023664:	46062032 */ 	c.eq.s	$f4,$f6
/*  f023668:	00000000 */ 	sll	$zero,$zero,0x0
/*  f02366c:	45030003 */ 	bc1tl	.NB0f02367c
/*  f023670:	00803825 */ 	or	$a3,$a0,$zero
/*  f023674:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f023678:	00803825 */ 	or	$a3,$a0,$zero
.NB0f02367c:
/*  f02367c:	10e00003 */ 	beqz	$a3,.NB0f02368c
/*  f023680:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023684:	10000009 */ 	beqz	$zero,.NB0f0236ac
/*  f023688:	00003825 */ 	or	$a3,$zero,$zero
.NB0f02368c:
/*  f02368c:	0c007000 */ 	jal	func0001af80
/*  f023690:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023694:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023698:	44060000 */ 	mfc1	$a2,$f0
/*  f02369c:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f0236a0:	0fc2341b */ 	jal	func0f08e8ac
/*  f0236a4:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f0236a8:	00403825 */ 	or	$a3,$v0,$zero
.NB0f0236ac:
/*  f0236ac:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
.NB0f0236b0:
/*  f0236b0:	02002025 */ 	or	$a0,$s0,$zero
/*  f0236b4:	51200016 */ 	beqzl	$t1,.NB0f023710
/*  f0236b8:	8faa0250 */ 	lw	$t2,0x250($sp)
/*  f0236bc:	820e0007 */ 	lb	$t6,0x7($s0)
/*  f0236c0:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0236c4:	8fab0208 */ 	lw	$t3,0x208($sp)
/*  f0236c8:	55c1000b */ 	bnel	$t6,$at,.NB0f0236f8
/*  f0236cc:	8e0f0014 */ 	lw	$t7,0x14($s0)
/*  f0236d0:	8d6d0020 */ 	lw	$t5,0x20($t3)
/*  f0236d4:	8fac0250 */ 	lw	$t4,0x250($sp)
/*  f0236d8:	85b80002 */ 	lh	$t8,0x2($t5)
/*  f0236dc:	57000006 */ 	bnezl	$t8,.NB0f0236f8
/*  f0236e0:	8e0f0014 */ 	lw	$t7,0x14($s0)
/*  f0236e4:	91880000 */ 	lbu	$t0,0x0($t4)
/*  f0236e8:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0236ec:	15010004 */ 	bne	$t0,$at,.NB0f023700
/*  f0236f0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0236f4:	8e0f0014 */ 	lw	$t7,0x14($s0)
.NB0f0236f8:
/*  f0236f8:	35f90200 */ 	ori	$t9,$t7,0x200
/*  f0236fc:	ae190014 */ 	sw	$t9,0x14($s0)
.NB0f023700:
/*  f023700:	0fc08366 */ 	jal	chrUpdateAimProperties
/*  f023704:	afa70204 */ 	sw	$a3,0x204($sp)
/*  f023708:	8fa70204 */ 	lw	$a3,0x204($sp)
/*  f02370c:	8faa0250 */ 	lw	$t2,0x250($sp)
.NB0f023710:
/*  f023710:	3c01c780 */ 	lui	$at,0xc780
/*  f023714:	44819000 */ 	mtc1	$at,$f18
/*  f023718:	c548000c */ 	lwc1	$f8,0xc($t2)
/*  f02371c:	8faa0250 */ 	lw	$t2,0x250($sp)
/*  f023720:	4612403c */ 	c.lt.s	$f8,$f18
/*  f023724:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023728:	45000002 */ 	bc1f	.NB0f023734
/*  f02372c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023730:	00003825 */ 	or	$a3,$zero,$zero
.NB0f023734:
/*  f023734:	50e001c3 */ 	beqzl	$a3,.NB0f023e44
/*  f023738:	914e0001 */ 	lbu	$t6,0x1($t2)
/*  f02373c:	0fc4667c */ 	jal	debug0f1199f0nb
/*  f023740:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023744:	8fa90250 */ 	lw	$t1,0x250($sp)
/*  f023748:	3c0c800a */ 	lui	$t4,0x800a
/*  f02374c:	912e0001 */ 	lbu	$t6,0x1($t1)
/*  f023750:	35cb0042 */ 	ori	$t3,$t6,0x42
/*  f023754:	a12b0001 */ 	sb	$t3,0x1($t1)
/*  f023758:	8e0d0018 */ 	lw	$t5,0x18($s0)
/*  f02375c:	35b80008 */ 	ori	$t8,$t5,0x8
/*  f023760:	ae180018 */ 	sw	$t8,0x18($s0)
/*  f023764:	8d8ce95c */ 	lw	$t4,-0x16a4($t4)
/*  f023768:	0580000a */ 	bltz	$t4,.NB0f023794
/*  f02376c:	3c08800a */ 	lui	$t0,0x800a
/*  f023770:	3c0f800a */ 	lui	$t7,0x800a
/*  f023774:	8defe944 */ 	lw	$t7,-0x16bc($t7)
/*  f023778:	8d08e960 */ 	lw	$t0,-0x16a0($t0)
/*  f02377c:	150f0005 */ 	bne	$t0,$t7,.NB0f023794
/*  f023780:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023784:	8e190014 */ 	lw	$t9,0x14($s0)
/*  f023788:	3c010080 */ 	lui	$at,0x80
/*  f02378c:	03215025 */ 	or	$t2,$t9,$at
/*  f023790:	ae0a0014 */ 	sw	$t2,0x14($s0)
.NB0f023794:
/*  f023794:	0fc40ab9 */ 	jal	cheatIsActive
/*  f023798:	24040007 */ 	addiu	$a0,$zero,0x7
/*  f02379c:	10400004 */ 	beqz	$v0,.NB0f0237b0
/*  f0237a0:	3c013ea0 */ 	lui	$at,0x3ea0
/*  f0237a4:	44816000 */ 	mtc1	$at,$f12
/*  f0237a8:	0c006d9f */ 	jal	modelSetDistanceScale
/*  f0237ac:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f0237b0:
/*  f0237b0:	3c0e7f02 */ 	lui	$t6,0x7f02
/*  f0237b4:	25ce106c */ 	addiu	$t6,$t6,0x106c
/*  f0237b8:	3c018006 */ 	lui	$at,0x8006
/*  f0237bc:	ac2e139c */ 	sw	$t6,0x139c($at)
/*  f0237c0:	3c01800a */ 	lui	$at,0x800a
/*  f0237c4:	12000003 */ 	beqz	$s0,.NB0f0237d4
/*  f0237c8:	ac30145c */ 	sw	$s0,0x145c($at)
/*  f0237cc:	10000002 */ 	beqz	$zero,.NB0f0237d8
/*  f0237d0:	920402fe */ 	lbu	$a0,0x2fe($s0)
.NB0f0237d4:
/*  f0237d4:	00002025 */ 	or	$a0,$zero,$zero
.NB0f0237d8:
/*  f0237d8:	24010002 */ 	addiu	$at,$zero,0x2
/*  f0237dc:	14810021 */ 	bne	$a0,$at,.NB0f023864
/*  f0237e0:	3c0b800a */ 	lui	$t3,0x800a
/*  f0237e4:	8d6be96c */ 	lw	$t3,-0x1694($t3)
/*  f0237e8:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0237ec:	5161001e */ 	beql	$t3,$at,.NB0f023868
/*  f0237f0:	8fad0250 */ 	lw	$t5,0x250($sp)
/*  f0237f4:	0fc0f714 */ 	jal	chrGetInverseTheta
/*  f0237f8:	02002025 */ 	or	$a0,$s0,$zero
/*  f0237fc:	e7a0018c */ 	swc1	$f0,0x18c($sp)
/*  f023800:	0c006d55 */ 	jal	sinf
/*  f023804:	46000306 */ 	mov.s	$f12,$f0
/*  f023808:	3c014198 */ 	lui	$at,0x4198
/*  f02380c:	44815000 */ 	mtc1	$at,$f10
/*  f023810:	44803000 */ 	mtc1	$zero,$f6
/*  f023814:	c7ac018c */ 	lwc1	$f12,0x18c($sp)
/*  f023818:	460a0102 */ 	mul.s	$f4,$f0,$f10
/*  f02381c:	e7a60194 */ 	swc1	$f6,0x194($sp)
/*  f023820:	0c006d52 */ 	jal	cosf
/*  f023824:	e7a40190 */ 	swc1	$f4,0x190($sp)
/*  f023828:	3c014198 */ 	lui	$at,0x4198
/*  f02382c:	44814000 */ 	mtc1	$at,$f8
/*  f023830:	27a40190 */ 	addiu	$a0,$sp,0x190
/*  f023834:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f023838:	46080482 */ 	mul.s	$f18,$f0,$f8
/*  f02383c:	0c005d9b */ 	jal	func000166dc
/*  f023840:	e7b20198 */ 	swc1	$f18,0x198($sp)
/*  f023844:	0fc2cd16 */ 	jal	currentPlayerGetMatrix1740
/*  f023848:	00000000 */ 	sll	$zero,$zero,0x0
/*  f02384c:	00402025 */ 	or	$a0,$v0,$zero
/*  f023850:	0c005a3b */ 	jal	func000159fc
/*  f023854:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f023858:	27a901a8 */ 	addiu	$t1,$sp,0x1a8
/*  f02385c:	1000004b */ 	beqz	$zero,.NB0f02398c
/*  f023860:	afa90210 */ 	sw	$t1,0x210($sp)
.NB0f023864:
/*  f023864:	8fad0250 */ 	lw	$t5,0x250($sp)
.NB0f023868:
/*  f023868:	24010006 */ 	addiu	$at,$zero,0x6
/*  f02386c:	91b80000 */ 	lbu	$t8,0x0($t5)
/*  f023870:	17010043 */ 	bne	$t8,$at,.NB0f023980
/*  f023874:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023878:	0fc48d6f */ 	jal	propGetPlayerNum
/*  f02387c:	01a02025 */ 	or	$a0,$t5,$zero
/*  f023880:	00026080 */ 	sll	$t4,$v0,0x2
/*  f023884:	3c03800a */ 	lui	$v1,0x800a
/*  f023888:	006c1821 */ 	addu	$v1,$v1,$t4
/*  f02388c:	8c63e724 */ 	lw	$v1,-0x18dc($v1)
/*  f023890:	24010003 */ 	addiu	$at,$zero,0x3
/*  f023894:	02002025 */ 	or	$a0,$s0,$zero
/*  f023898:	8c6801b0 */ 	lw	$t0,0x1b0($v1)
/*  f02389c:	15010034 */ 	bne	$t0,$at,.NB0f023970
/*  f0238a0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0238a4:	0fc0f714 */ 	jal	chrGetInverseTheta
/*  f0238a8:	afa30188 */ 	sw	$v1,0x188($sp)
/*  f0238ac:	8fa30188 */ 	lw	$v1,0x188($sp)
/*  f0238b0:	e7a00178 */ 	swc1	$f0,0x178($sp)
/*  f0238b4:	3c01447a */ 	lui	$at,0x447a
/*  f0238b8:	8c6f1a6c */ 	lw	$t7,0x1a6c($v1)
/*  f0238bc:	44812000 */ 	mtc1	$at,$f4
/*  f0238c0:	46000306 */ 	mov.s	$f12,$f0
/*  f0238c4:	8de20004 */ 	lw	$v0,0x4($t7)
/*  f0238c8:	c44a00ac */ 	lwc1	$f10,0xac($v0)
/*  f0238cc:	afa20174 */ 	sw	$v0,0x174($sp)
/*  f0238d0:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f0238d4:	0c006d52 */ 	jal	cosf
/*  f0238d8:	e7a60130 */ 	swc1	$f6,0x130($sp)
/*  f0238dc:	c7a80130 */ 	lwc1	$f8,0x130($sp)
/*  f0238e0:	8fa20174 */ 	lw	$v0,0x174($sp)
/*  f0238e4:	44805000 */ 	mtc1	$zero,$f10
/*  f0238e8:	46080482 */ 	mul.s	$f18,$f0,$f8
/*  f0238ec:	3c014348 */ 	lui	$at,0x4348
/*  f0238f0:	44812000 */ 	mtc1	$at,$f4
/*  f0238f4:	e7b2017c */ 	swc1	$f18,0x17c($sp)
/*  f0238f8:	c44200ac */ 	lwc1	$f2,0xac($v0)
/*  f0238fc:	4602503c */ 	c.lt.s	$f10,$f2
/*  f023900:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023904:	45020004 */ 	bc1fl	.NB0f023918
/*  f023908:	46001007 */ 	neg.s	$f0,$f2
/*  f02390c:	10000002 */ 	beqz	$zero,.NB0f023918
/*  f023910:	46001006 */ 	mov.s	$f0,$f2
/*  f023914:	46001007 */ 	neg.s	$f0,$f2
.NB0f023918:
/*  f023918:	46040182 */ 	mul.s	$f6,$f0,$f4
/*  f02391c:	3c0141c8 */ 	lui	$at,0x41c8
/*  f023920:	44814000 */ 	mtc1	$at,$f8
/*  f023924:	c7ac0178 */ 	lwc1	$f12,0x178($sp)
/*  f023928:	46006307 */ 	neg.s	$f12,$f12
/*  f02392c:	46083480 */ 	add.s	$f18,$f6,$f8
/*  f023930:	0c006d55 */ 	jal	sinf
/*  f023934:	e7b20180 */ 	swc1	$f18,0x180($sp)
/*  f023938:	c7aa0130 */ 	lwc1	$f10,0x130($sp)
/*  f02393c:	27a4017c */ 	addiu	$a0,$sp,0x17c
/*  f023940:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f023944:	460a0102 */ 	mul.s	$f4,$f0,$f10
/*  f023948:	0c005d9b */ 	jal	func000166dc
/*  f02394c:	e7a40184 */ 	swc1	$f4,0x184($sp)
/*  f023950:	0fc2cd16 */ 	jal	currentPlayerGetMatrix1740
/*  f023954:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023958:	00402025 */ 	or	$a0,$v0,$zero
/*  f02395c:	0c005a3b */ 	jal	func000159fc
/*  f023960:	27a501a8 */ 	addiu	$a1,$sp,0x1a8
/*  f023964:	27b901a8 */ 	addiu	$t9,$sp,0x1a8
/*  f023968:	10000008 */ 	beqz	$zero,.NB0f02398c
/*  f02396c:	afb90210 */ 	sw	$t9,0x210($sp)
.NB0f023970:
/*  f023970:	0fc2cd16 */ 	jal	currentPlayerGetMatrix1740
/*  f023974:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023978:	10000004 */ 	beqz	$zero,.NB0f02398c
/*  f02397c:	afa20210 */ 	sw	$v0,0x210($sp)
.NB0f023980:
/*  f023980:	0fc2cd16 */ 	jal	currentPlayerGetMatrix1740
/*  f023984:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023988:	afa20210 */ 	sw	$v0,0x210($sp)
.NB0f02398c:
/*  f02398c:	8faa0208 */ 	lw	$t2,0x208($sp)
/*  f023990:	8d4e0008 */ 	lw	$t6,0x8($t2)
/*  f023994:	85c4000e */ 	lh	$a0,0xe($t6)
/*  f023998:	00045980 */ 	sll	$t3,$a0,0x6
/*  f02399c:	0fc588cd */ 	jal	gfxAllocate
/*  f0239a0:	01602025 */ 	or	$a0,$t3,$zero
/*  f0239a4:	8fa901f0 */ 	lw	$t1,0x1f0($sp)
/*  f0239a8:	afa20220 */ 	sw	$v0,0x220($sp)
/*  f0239ac:	11200011 */ 	beqz	$t1,.NB0f0239f4
/*  f0239b0:	3c02800a */ 	lui	$v0,0x800a
/*  f0239b4:	8c42145c */ 	lw	$v0,0x145c($v0)
/*  f0239b8:	3c18800a */ 	lui	$t8,0x800a
/*  f0239bc:	80430012 */ 	lb	$v1,0x12($v0)
/*  f0239c0:	0460000c */ 	bltz	$v1,.NB0f0239f4
/*  f0239c4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0239c8:	8f18e6f8 */ 	lw	$t8,-0x1908($t8)
/*  f0239cc:	2408ffff */ 	addiu	$t0,$zero,-1
/*  f0239d0:	00786821 */ 	addu	$t5,$v1,$t8
/*  f0239d4:	a04d0012 */ 	sb	$t5,0x12($v0)
/*  f0239d8:	3c02800a */ 	lui	$v0,0x800a
/*  f0239dc:	8c42145c */ 	lw	$v0,0x145c($v0)
/*  f0239e0:	804c0012 */ 	lb	$t4,0x12($v0)
/*  f0239e4:	2981001e */ 	slti	$at,$t4,0x1e
/*  f0239e8:	14200002 */ 	bnez	$at,.NB0f0239f4
/*  f0239ec:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0239f0:	a0480012 */ 	sb	$t0,0x12($v0)
.NB0f0239f4:
/*  f0239f4:	3c03800a */ 	lui	$v1,0x800a
/*  f0239f8:	8c63e944 */ 	lw	$v1,-0x16bc($v1)
/*  f0239fc:	24631bb0 */ 	addiu	$v1,$v1,0x1bb0
/*  f023a00:	0fc2cd46 */ 	jal	currentPlayerGetLodScaleZ
/*  f023a04:	afa30124 */ 	sw	$v1,0x124($sp)
/*  f023a08:	3c0f800a */ 	lui	$t7,0x800a
/*  f023a0c:	8defe9d8 */ 	lw	$t7,-0x1628($t7)
/*  f023a10:	8fa30124 */ 	lw	$v1,0x124($sp)
/*  f023a14:	46000406 */ 	mov.s	$f16,$f0
/*  f023a18:	11e0000c */ 	beqz	$t7,.NB0f023a4c
/*  f023a1c:	00003025 */ 	or	$a2,$zero,$zero
/*  f023a20:	3c19800b */ 	lui	$t9,0x800b
/*  f023a24:	8f391444 */ 	lw	$t9,0x1444($t9)
/*  f023a28:	3c017f1a */ 	lui	$at,0x7f1a
/*  f023a2c:	332a00c0 */ 	andi	$t2,$t9,0xc0
/*  f023a30:	11400004 */ 	beqz	$t2,.NB0f023a44
/*  f023a34:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023a38:	3c017f1a */ 	lui	$at,0x7f1a
/*  f023a3c:	10000010 */ 	beqz	$zero,.NB0f023a80
/*  f023a40:	c42e2458 */ 	lwc1	$f14,0x2458($at)
.NB0f023a44:
/*  f023a44:	1000000e */ 	beqz	$zero,.NB0f023a80
/*  f023a48:	c42e245c */ 	lwc1	$f14,0x245c($at)
.NB0f023a4c:
/*  f023a4c:	afa30124 */ 	sw	$v1,0x124($sp)
/*  f023a50:	afa60110 */ 	sw	$a2,0x110($sp)
/*  f023a54:	0fc4668e */ 	jal	debugGetSlowMotion
/*  f023a58:	e7b00114 */ 	swc1	$f16,0x114($sp)
/*  f023a5c:	8fa30124 */ 	lw	$v1,0x124($sp)
/*  f023a60:	8fa60110 */ 	lw	$a2,0x110($sp)
/*  f023a64:	10400004 */ 	beqz	$v0,.NB0f023a78
/*  f023a68:	c7b00114 */ 	lwc1	$f16,0x114($sp)
/*  f023a6c:	3c017f1a */ 	lui	$at,0x7f1a
/*  f023a70:	10000003 */ 	beqz	$zero,.NB0f023a80
/*  f023a74:	c42e2460 */ 	lwc1	$f14,0x2460($at)
.NB0f023a78:
/*  f023a78:	3c017f1a */ 	lui	$at,0x7f1a
/*  f023a7c:	c42e2464 */ 	lwc1	$f14,0x2464($at)
.NB0f023a80:
/*  f023a80:	8fae0208 */ 	lw	$t6,0x208($sp)
/*  f023a84:	27a40210 */ 	addiu	$a0,$sp,0x210
/*  f023a88:	8dc20020 */ 	lw	$v0,0x20($t6)
/*  f023a8c:	50400057 */ 	beqzl	$v0,.NB0f023bec
/*  f023a90:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f023a94:	844b0000 */ 	lh	$t3,0x0($v0)
/*  f023a98:	8fa90250 */ 	lw	$t1,0x250($sp)
/*  f023a9c:	51600053 */ 	beqzl	$t3,.NB0f023bec
/*  f023aa0:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f023aa4:	c5260008 */ 	lwc1	$f6,0x8($t1)
/*  f023aa8:	c4680000 */ 	lwc1	$f8,0x0($v1)
/*  f023aac:	c532000c */ 	lwc1	$f18,0xc($t1)
/*  f023ab0:	c46a0004 */ 	lwc1	$f10,0x4($v1)
/*  f023ab4:	46083001 */ 	sub.s	$f0,$f6,$f8
/*  f023ab8:	c4660008 */ 	lwc1	$f6,0x8($v1)
/*  f023abc:	c5240010 */ 	lwc1	$f4,0x10($t1)
/*  f023ac0:	460a9081 */ 	sub.s	$f2,$f18,$f10
/*  f023ac4:	46000202 */ 	mul.s	$f8,$f0,$f0
/*  f023ac8:	46062301 */ 	sub.s	$f12,$f4,$f6
/*  f023acc:	46021482 */ 	mul.s	$f18,$f2,$f2
/*  f023ad0:	46124280 */ 	add.s	$f10,$f8,$f18
/*  f023ad4:	460c6102 */ 	mul.s	$f4,$f12,$f12
/*  f023ad8:	46045180 */ 	add.s	$f6,$f10,$f4
/*  f023adc:	46103202 */ 	mul.s	$f8,$f6,$f16
/*  f023ae0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023ae4:	46104482 */ 	mul.s	$f18,$f8,$f16
/*  f023ae8:	4612703c */ 	c.lt.s	$f14,$f18
/*  f023aec:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023af0:	4500003d */ 	bc1f	.NB0f023be8
/*  f023af4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023af8:	c4400010 */ 	lwc1	$f0,0x10($v0)
/*  f023afc:	44801000 */ 	mtc1	$zero,$f2
/*  f023b00:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f023b04:	e7a0010c */ 	swc1	$f0,0x10c($sp)
/*  f023b08:	84580014 */ 	lh	$t8,0x14($v0)
/*  f023b0c:	46001032 */ 	c.eq.s	$f2,$f0
/*  f023b10:	afb80108 */ 	sw	$t8,0x108($sp)
/*  f023b14:	c44a0034 */ 	lwc1	$f10,0x34($v0)
/*  f023b18:	e7aa0104 */ 	swc1	$f10,0x104($sp)
/*  f023b1c:	844d0038 */ 	lh	$t5,0x38($v0)
/*  f023b20:	45010014 */ 	bc1t	.NB0f023b74
/*  f023b24:	afad0100 */ 	sw	$t5,0x100($sp)
/*  f023b28:	c444001c */ 	lwc1	$f4,0x1c($v0)
/*  f023b2c:	c4460074 */ 	lwc1	$f6,0x74($v0)
/*  f023b30:	3c013e80 */ 	lui	$at,0x3e80
/*  f023b34:	44819000 */ 	mtc1	$at,$f18
/*  f023b38:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f023b3c:	3c013f00 */ 	lui	$at,0x3f00
/*  f023b40:	4608903e */ 	c.le.s	$f18,$f8
/*  f023b44:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023b48:	4502000b */ 	bc1fl	.NB0f023b78
/*  f023b4c:	c4440054 */ 	lwc1	$f4,0x54($v0)
/*  f023b50:	44815000 */ 	mtc1	$at,$f10
/*  f023b54:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023b58:	4600503c */ 	c.lt.s	$f10,$f0
/*  f023b5c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023b60:	45020004 */ 	bc1fl	.NB0f023b74
/*  f023b64:	e4420010 */ 	swc1	$f2,0x10($v0)
/*  f023b68:	844c0016 */ 	lh	$t4,0x16($v0)
/*  f023b6c:	a44c0014 */ 	sh	$t4,0x14($v0)
/*  f023b70:	e4420010 */ 	swc1	$f2,0x10($v0)
.NB0f023b74:
/*  f023b74:	c4440054 */ 	lwc1	$f4,0x54($v0)
.NB0f023b78:
/*  f023b78:	46041032 */ 	c.eq.s	$f2,$f4
/*  f023b7c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023b80:	4503001a */ 	bc1tl	.NB0f023bec
/*  f023b84:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f023b88:	c4460040 */ 	lwc1	$f6,0x40($v0)
/*  f023b8c:	c4480074 */ 	lwc1	$f8,0x74($v0)
/*  f023b90:	3c013e80 */ 	lui	$at,0x3e80
/*  f023b94:	44815000 */ 	mtc1	$at,$f10
/*  f023b98:	46083482 */ 	mul.s	$f18,$f6,$f8
/*  f023b9c:	4612503e */ 	c.le.s	$f10,$f18
/*  f023ba0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023ba4:	45020011 */ 	bc1fl	.NB0f023bec
/*  f023ba8:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f023bac:	c4400034 */ 	lwc1	$f0,0x34($v0)
/*  f023bb0:	3c013f00 */ 	lui	$at,0x3f00
/*  f023bb4:	46001032 */ 	c.eq.s	$f2,$f0
/*  f023bb8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023bbc:	4503000b */ 	bc1tl	.NB0f023bec
/*  f023bc0:	8fa50208 */ 	lw	$a1,0x208($sp)
/*  f023bc4:	44812000 */ 	mtc1	$at,$f4
/*  f023bc8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023bcc:	4600203c */ 	c.lt.s	$f4,$f0
/*  f023bd0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023bd4:	45020004 */ 	bc1fl	.NB0f023be8
/*  f023bd8:	e4420034 */ 	swc1	$f2,0x34($v0)
/*  f023bdc:	8448003a */ 	lh	$t0,0x3a($v0)
/*  f023be0:	a4480038 */ 	sh	$t0,0x38($v0)
/*  f023be4:	e4420034 */ 	swc1	$f2,0x34($v0)
.NB0f023be8:
/*  f023be8:	8fa50208 */ 	lw	$a1,0x208($sp)
.NB0f023bec:
/*  f023bec:	afa20128 */ 	sw	$v0,0x128($sp)
/*  f023bf0:	0c0077cf */ 	jal	func0001cebc
/*  f023bf4:	afa60110 */ 	sw	$a2,0x110($sp)
/*  f023bf8:	8fa60110 */ 	lw	$a2,0x110($sp)
/*  f023bfc:	8fa20128 */ 	lw	$v0,0x128($sp)
/*  f023c00:	c7a6010c */ 	lwc1	$f6,0x10c($sp)
/*  f023c04:	10c00008 */ 	beqz	$a2,.NB0f023c28
/*  f023c08:	3c018006 */ 	lui	$at,0x8006
/*  f023c0c:	e4460010 */ 	swc1	$f6,0x10($v0)
/*  f023c10:	8faf0108 */ 	lw	$t7,0x108($sp)
/*  f023c14:	a44f0014 */ 	sh	$t7,0x14($v0)
/*  f023c18:	c7a80104 */ 	lwc1	$f8,0x104($sp)
/*  f023c1c:	e4480034 */ 	swc1	$f8,0x34($v0)
/*  f023c20:	8fb90100 */ 	lw	$t9,0x100($sp)
/*  f023c24:	a4590038 */ 	sh	$t9,0x38($v0)
.NB0f023c28:
/*  f023c28:	ac20139c */ 	sw	$zero,0x139c($at)
/*  f023c2c:	3c018006 */ 	lui	$at,0x8006
/*  f023c30:	0c006d9f */ 	jal	modelSetDistanceScale
/*  f023c34:	c42c4ef8 */ 	lwc1	$f12,0x4ef8($at)
/*  f023c38:	8faa01f0 */ 	lw	$t2,0x1f0($sp)
/*  f023c3c:	260400f8 */ 	addiu	$a0,$s0,0xf8
/*  f023c40:	11400003 */ 	beqz	$t2,.NB0f023c50
/*  f023c44:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023c48:	0fc1a25f */ 	jal	colourTween
/*  f023c4c:	260500fc */ 	addiu	$a1,$s0,0xfc
.NB0f023c50:
/*  f023c50:	0c006ed6 */ 	jal	func0001a9e8
/*  f023c54:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023c58:	8fae0250 */ 	lw	$t6,0x250($sp)
/*  f023c5c:	8dc7001c */ 	lw	$a3,0x1c($t6)
/*  f023c60:	e5c00014 */ 	swc1	$f0,0x14($t6)
/*  f023c64:	50e0000b */ 	beqzl	$a3,.NB0f023c94
/*  f023c68:	8e030178 */ 	lw	$v1,0x178($s0)
/*  f023c6c:	8ce20020 */ 	lw	$v0,0x20($a3)
.NB0f023c70:
/*  f023c70:	02002025 */ 	or	$a0,$s0,$zero
/*  f023c74:	00e02825 */ 	or	$a1,$a3,$zero
/*  f023c78:	8fa601f0 */ 	lw	$a2,0x1f0($sp)
/*  f023c7c:	0fc08753 */ 	jal	func0f022214
/*  f023c80:	afa201f4 */ 	sw	$v0,0x1f4($sp)
/*  f023c84:	8fa701f4 */ 	lw	$a3,0x1f4($sp)
/*  f023c88:	54e0fff9 */ 	bnezl	$a3,.NB0f023c70
/*  f023c8c:	8ce20020 */ 	lw	$v0,0x20($a3)
/*  f023c90:	8e030178 */ 	lw	$v1,0x178($s0)
.NB0f023c94:
/*  f023c94:	5060004d */ 	beqzl	$v1,.NB0f023dcc
/*  f023c98:	8fa90208 */ 	lw	$t1,0x208($sp)
/*  f023c9c:	8c620004 */ 	lw	$v0,0x4($v1)
/*  f023ca0:	8c4b0018 */ 	lw	$t3,0x18($v0)
/*  f023ca4:	afab00f4 */ 	sw	$t3,0xf4($sp)
/*  f023ca8:	82040006 */ 	lb	$a0,0x6($s0)
/*  f023cac:	2881002a */ 	slti	$at,$a0,0x2a
/*  f023cb0:	14200045 */ 	bnez	$at,.NB0f023dc8
/*  f023cb4:	2881002b */ 	slti	$at,$a0,0x2b
/*  f023cb8:	10200043 */ 	beqz	$at,.NB0f023dc8
/*  f023cbc:	3c188006 */ 	lui	$t8,0x8006
/*  f023cc0:	27184f4c */ 	addiu	$t8,$t8,0x4f4c
/*  f023cc4:	8f010000 */ 	lw	$at,0x0($t8)
/*  f023cc8:	27a900e8 */ 	addiu	$t1,$sp,0xe8
/*  f023ccc:	8f0c0004 */ 	lw	$t4,0x4($t8)
/*  f023cd0:	ad210000 */ 	sw	$at,0x0($t1)
/*  f023cd4:	8f010008 */ 	lw	$at,0x8($t8)
/*  f023cd8:	ad2c0004 */ 	sw	$t4,0x4($t1)
/*  f023cdc:	ad210008 */ 	sw	$at,0x8($t1)
/*  f023ce0:	0fc22947 */ 	jal	hatGetType
/*  f023ce4:	8e040178 */ 	lw	$a0,0x178($s0)
/*  f023ce8:	afa20058 */ 	sw	$v0,0x58($sp)
/*  f023cec:	82060006 */ 	lb	$a2,0x6($s0)
/*  f023cf0:	3c017f1a */ 	lui	$at,0x7f1a
/*  f023cf4:	c4322468 */ 	lwc1	$f18,0x2468($at)
/*  f023cf8:	24c6ffd6 */ 	addiu	$a2,$a2,-42
/*  f023cfc:	000640c0 */ 	sll	$t0,$a2,0x3
/*  f023d00:	01064021 */ 	addu	$t0,$t0,$a2
/*  f023d04:	00027880 */ 	sll	$t7,$v0,0x2
/*  f023d08:	00084100 */ 	sll	$t0,$t0,0x4
/*  f023d0c:	01e27823 */ 	subu	$t7,$t7,$v0
/*  f023d10:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f023d14:	3c0a8008 */ 	lui	$t2,0x8008
/*  f023d18:	010fc821 */ 	addu	$t9,$t0,$t7
/*  f023d1c:	254a0344 */ 	addiu	$t2,$t2,0x344
/*  f023d20:	032a1821 */ 	addu	$v1,$t9,$t2
/*  f023d24:	c4700000 */ 	lwc1	$f16,0x0($v1)
/*  f023d28:	c46e0004 */ 	lwc1	$f14,0x4($v1)
/*  f023d2c:	c46c0008 */ 	lwc1	$f12,0x8($v1)
/*  f023d30:	46128402 */ 	mul.s	$f16,$f16,$f18
/*  f023d34:	c46a000c */ 	lwc1	$f10,0xc($v1)
/*  f023d38:	c4680010 */ 	lwc1	$f8,0x10($v1)
/*  f023d3c:	46127382 */ 	mul.s	$f14,$f14,$f18
/*  f023d40:	c4660014 */ 	lwc1	$f6,0x14($v1)
/*  f023d44:	e7aa00e4 */ 	swc1	$f10,0xe4($sp)
/*  f023d48:	46126482 */ 	mul.s	$f18,$f12,$f18
/*  f023d4c:	e7b000e8 */ 	swc1	$f16,0xe8($sp)
/*  f023d50:	e7a800e0 */ 	swc1	$f8,0xe0($sp)
/*  f023d54:	e7a600dc */ 	swc1	$f6,0xdc($sp)
/*  f023d58:	e7ae00ec */ 	swc1	$f14,0xec($sp)
/*  f023d5c:	27a400e8 */ 	addiu	$a0,$sp,0xe8
/*  f023d60:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f023d64:	0c005d9b */ 	jal	func000166dc
/*  f023d68:	e7b200f0 */ 	swc1	$f18,0xf0($sp)
/*  f023d6c:	c7ac00e4 */ 	lwc1	$f12,0xe4($sp)
/*  f023d70:	0c005b45 */ 	jal	func00015e24
/*  f023d74:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f023d78:	c7ac00e0 */ 	lwc1	$f12,0xe0($sp)
/*  f023d7c:	0c005b5c */ 	jal	func00015e80
/*  f023d80:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f023d84:	c7ac00dc */ 	lwc1	$f12,0xdc($sp)
/*  f023d88:	0c005b73 */ 	jal	func00015edc
/*  f023d8c:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f023d90:	8fae00f4 */ 	lw	$t6,0xf4($sp)
/*  f023d94:	27a5009c */ 	addiu	$a1,$sp,0x9c
/*  f023d98:	27a6005c */ 	addiu	$a2,$sp,0x5c
/*  f023d9c:	0c005ab5 */ 	jal	func00015be4
/*  f023da0:	8dc4000c */ 	lw	$a0,0xc($t6)
/*  f023da4:	8fab00f4 */ 	lw	$t3,0xf4($sp)
/*  f023da8:	27a4005c */ 	addiu	$a0,$sp,0x5c
/*  f023dac:	0c005b02 */ 	jal	func00015d18
/*  f023db0:	8d65000c */ 	lw	$a1,0xc($t3)
/*  f023db4:	8fad0058 */ 	lw	$t5,0x58($sp)
/*  f023db8:	24010002 */ 	addiu	$at,$zero,0x2
/*  f023dbc:	55a10003 */ 	bnel	$t5,$at,.NB0f023dcc
/*  f023dc0:	8fa90208 */ 	lw	$t1,0x208($sp)
/*  f023dc4:	afa00200 */ 	sw	$zero,0x200($sp)
.NB0f023dc8:
/*  f023dc8:	8fa90208 */ 	lw	$t1,0x208($sp)
.NB0f023dcc:
/*  f023dcc:	3c188008 */ 	lui	$t8,0x8008
/*  f023dd0:	2718f6a0 */ 	addiu	$t8,$t8,-2400
/*  f023dd4:	8d240008 */ 	lw	$a0,0x8($t1)
/*  f023dd8:	8c8c0004 */ 	lw	$t4,0x4($a0)
/*  f023ddc:	570c003f */ 	bnel	$t8,$t4,.NB0f023edc
/*  f023de0:	8fad01f0 */ 	lw	$t5,0x1f0($sp)
/*  f023de4:	0c006ea3 */ 	jal	modelGetPart
/*  f023de8:	24050004 */ 	addiu	$a1,$zero,0x4
/*  f023dec:	1040003a */ 	beqz	$v0,.NB0f023ed8
/*  f023df0:	00402825 */ 	or	$a1,$v0,$zero
/*  f023df4:	94480000 */ 	lhu	$t0,0x0($v0)
/*  f023df8:	24010017 */ 	addiu	$at,$zero,0x17
/*  f023dfc:	55010037 */ 	bnel	$t0,$at,.NB0f023edc
/*  f023e00:	8fad01f0 */ 	lw	$t5,0x1f0($sp)
/*  f023e04:	0c006bab */ 	jal	modelGetNodeRwData
/*  f023e08:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023e0c:	8c4f0000 */ 	lw	$t7,0x0($v0)
/*  f023e10:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f023e14:	51e00031 */ 	beqzl	$t7,.NB0f023edc
/*  f023e18:	8fad01f0 */ 	lw	$t5,0x1f0($sp)
/*  f023e1c:	0c006ea3 */ 	jal	modelGetPart
/*  f023e20:	8c440000 */ 	lw	$a0,0x0($v0)
/*  f023e24:	1040002c */ 	beqz	$v0,.NB0f023ed8
/*  f023e28:	00402825 */ 	or	$a1,$v0,$zero
/*  f023e2c:	0c006bab */ 	jal	modelGetNodeRwData
/*  f023e30:	8fa40208 */ 	lw	$a0,0x208($sp)
/*  f023e34:	8fb90200 */ 	lw	$t9,0x200($sp)
/*  f023e38:	10000027 */ 	beqz	$zero,.NB0f023ed8
/*  f023e3c:	ac590000 */ 	sw	$t9,0x0($v0)
/*  f023e40:	914e0001 */ 	lbu	$t6,0x1($t2)
.NB0f023e44:
/*  f023e44:	3c0d800a */ 	lui	$t5,0x800a
/*  f023e48:	3c09800a */ 	lui	$t1,0x800a
/*  f023e4c:	31cbfffd */ 	andi	$t3,$t6,0xfffd
/*  f023e50:	a14b0001 */ 	sb	$t3,0x1($t2)
/*  f023e54:	8dade95c */ 	lw	$t5,-0x16a4($t5)
/*  f023e58:	3c18800a */ 	lui	$t8,0x800a
/*  f023e5c:	05a2000b */ 	bltzl	$t5,.NB0f023e8c
/*  f023e60:	8faf0250 */ 	lw	$t7,0x250($sp)
/*  f023e64:	8d29e960 */ 	lw	$t1,-0x16a0($t1)
/*  f023e68:	8f18e944 */ 	lw	$t8,-0x16bc($t8)
/*  f023e6c:	55380007 */ 	bnel	$t1,$t8,.NB0f023e8c
/*  f023e70:	8faf0250 */ 	lw	$t7,0x250($sp)
/*  f023e74:	8e0c0014 */ 	lw	$t4,0x14($s0)
/*  f023e78:	3c01ff7f */ 	lui	$at,0xff7f
/*  f023e7c:	3421ffff */ 	ori	$at,$at,0xffff
/*  f023e80:	01814024 */ 	and	$t0,$t4,$at
/*  f023e84:	ae080014 */ 	sw	$t0,0x14($s0)
/*  f023e88:	8faf0250 */ 	lw	$t7,0x250($sp)
.NB0f023e8c:
/*  f023e8c:	8de7001c */ 	lw	$a3,0x1c($t7)
/*  f023e90:	50e0000a */ 	beqzl	$a3,.NB0f023ebc
/*  f023e94:	921900fc */ 	lbu	$t9,0xfc($s0)
/*  f023e98:	8ce20020 */ 	lw	$v0,0x20($a3)
.NB0f023e9c:
/*  f023e9c:	00e02025 */ 	or	$a0,$a3,$zero
/*  f023ea0:	8fa501f0 */ 	lw	$a1,0x1f0($sp)
/*  f023ea4:	0fc1bd3d */ 	jal	func0f0706f8
/*  f023ea8:	afa201f4 */ 	sw	$v0,0x1f4($sp)
/*  f023eac:	8fa701f4 */ 	lw	$a3,0x1f4($sp)
/*  f023eb0:	54e0fffa */ 	bnezl	$a3,.NB0f023e9c
/*  f023eb4:	8ce20020 */ 	lw	$v0,0x20($a3)
/*  f023eb8:	921900fc */ 	lbu	$t9,0xfc($s0)
.NB0f023ebc:
/*  f023ebc:	920e00fd */ 	lbu	$t6,0xfd($s0)
/*  f023ec0:	920b00fe */ 	lbu	$t3,0xfe($s0)
/*  f023ec4:	920a00ff */ 	lbu	$t2,0xff($s0)
/*  f023ec8:	a21900f8 */ 	sb	$t9,0xf8($s0)
/*  f023ecc:	a20e00f9 */ 	sb	$t6,0xf9($s0)
/*  f023ed0:	a20b00fa */ 	sb	$t3,0xfa($s0)
/*  f023ed4:	a20a00fb */ 	sb	$t2,0xfb($s0)
.NB0f023ed8:
/*  f023ed8:	8fad01f0 */ 	lw	$t5,0x1f0($sp)
.NB0f023edc:
/*  f023edc:	51a00013 */ 	beqzl	$t5,.NB0f023f2c
/*  f023ee0:	00001025 */ 	or	$v0,$zero,$zero
/*  f023ee4:	8e090018 */ 	lw	$t1,0x18($s0)
/*  f023ee8:	31380400 */ 	andi	$t8,$t1,0x400
/*  f023eec:	5700000f */ 	bnezl	$t8,.NB0f023f2c
/*  f023ef0:	00001025 */ 	or	$v0,$zero,$zero
/*  f023ef4:	8e0c0014 */ 	lw	$t4,0x14($s0)
/*  f023ef8:	8fa40250 */ 	lw	$a0,0x250($sp)
/*  f023efc:	31880001 */ 	andi	$t0,$t4,0x1
/*  f023f00:	11000007 */ 	beqz	$t0,.NB0f023f20
/*  f023f04:	00000000 */ 	sll	$zero,$zero,0x0
/*  f023f08:	0fc1bd25 */ 	jal	func0f070698
/*  f023f0c:	00002825 */ 	or	$a1,$zero,$zero
/*  f023f10:	8e0f0014 */ 	lw	$t7,0x14($s0)
/*  f023f14:	2401fffe */ 	addiu	$at,$zero,-2
/*  f023f18:	01e1c824 */ 	and	$t9,$t7,$at
/*  f023f1c:	ae190014 */ 	sw	$t9,0x14($s0)
.NB0f023f20:
/*  f023f20:	0fc1048f */ 	jal	func0f041a74
/*  f023f24:	02002025 */ 	or	$a0,$s0,$zero
/*  f023f28:	00001025 */ 	or	$v0,$zero,$zero
.NB0f023f2c:
/*  f023f2c:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f023f30:	8fb00020 */ 	lw	$s0,0x20($sp)
/*  f023f34:	27bd0250 */ 	addiu	$sp,$sp,0x250
/*  f023f38:	03e00008 */ 	jr	$ra
/*  f023f3c:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

void chrDropItems(struct chrdata *chr)
{
	struct prop *prop = chr->prop->child;

	while (prop) {
		if (prop != chr->weapons_held[2]
				&& prop != chr->weapons_held[1]
				&& prop != chr->weapons_held[0]
				&& (prop->obj->hidden & OBJHFLAG_00000040) == 0
				&& (prop->obj->flags & OBJFLAG_00002000) == 0) {
			propobjSetDropped(prop, DROPREASON_1);
		}

		prop = prop->next;
	}

	chr->hidden |= CHRHFLAG_00000001;
}

void chrSetHudpieceVisible(struct chrdata *chr, bool visible)
{
	struct modelfiledata *modelfiledata = chr->model->filedata;

	if (modelfiledata->type == &g_ModelTypeChr) {
		struct modelnode *headspotnode = modelGetPart(modelfiledata, MODELPART_CHR_HEADSPOT);

		if (headspotnode && headspotnode->type == MODELNODETYPE_HEADSPOT) {
			union modelrwdata *rwdata = modelGetNodeRwData(chr->model, headspotnode);

			if (rwdata->headspot.modelfiledata) {
				struct modelnode *hudpiecenode = modelGetPart(rwdata->headspot.modelfiledata, MODELPART_HEAD_HUDPIECE);

				if (hudpiecenode) {
					union modelrwdata *rwdata2 = modelGetNodeRwData(chr->model, hudpiecenode);
					rwdata2->toggle.visible = visible;
				}
			}
		}
	}
}

void chrDropWeapons(struct chrdata *chr)
{
	struct prop *prop = chr->prop->child;

	while (prop)  {
		// If prop is not hat
		if (prop != chr->weapons_held[2]) {
			struct defaultobj *obj = prop->obj;

			if ((obj->flags & OBJFLAG_00002000) == 0) {
				propobjSetDropped(prop, DROPREASON_6);
			}
		}

		prop = prop->next;
	}

	chr->hidden |= CHRHFLAG_00000001;
}

void func0f0246e4(u8 *arg0)
{
	var80062a48[0] = arg0[0];
	var80062a48[1] = arg0[1];
	var80062a48[2] = arg0[2];
}

void func0f024708(u8 *arg0)
{
	arg0[0] = var80062a48[0];
	arg0[1] = var80062a48[1];
	arg0[2] = var80062a48[2];
}

void func0f02472c(void)
{
	var80062964 = 0;
}

GLOBAL_ASM(
glabel func0f024738
/*  f024738:	27bdfd80 */ 	addiu	$sp,$sp,-640
/*  f02473c:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f024740:	3c138006 */ 	lui	$s3,%hi(var80062964)
/*  f024744:	26732964 */ 	addiu	$s3,$s3,%lo(var80062964)
/*  f024748:	8e6e0000 */ 	lw	$t6,0x0($s3)
/*  f02474c:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f024750:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f024754:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f024758:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f02475c:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f024760:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f024764:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f024768:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f02476c:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f024770:	afa40280 */ 	sw	$a0,0x280($sp)
/*  f024774:	afa0006c */ 	sw	$zero,0x6c($sp)
/*  f024778:	19c0000d */ 	blez	$t6,.L0f0247b0
/*  f02477c:	00001825 */ 	or	$v1,$zero,$zero
/*  f024780:	3c158006 */ 	lui	$s5,%hi(var80062960)
/*  f024784:	26b52960 */ 	addiu	$s5,$s5,%lo(var80062960)
/*  f024788:	00001025 */ 	or	$v0,$zero,$zero
/*  f02478c:	8eaf0000 */ 	lw	$t7,0x0($s5)
.L0f024790:
/*  f024790:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f024794:	01e2c021 */ 	addu	$t8,$t7,$v0
/*  f024798:	af000004 */ 	sw	$zero,0x4($t8)
/*  f02479c:	8e790000 */ 	lw	$t9,0x0($s3)
/*  f0247a0:	2442015c */ 	addiu	$v0,$v0,0x15c
/*  f0247a4:	0079082a */ 	slt	$at,$v1,$t9
/*  f0247a8:	5420fff9 */ 	bnezl	$at,.L0f024790
/*  f0247ac:	8eaf0000 */ 	lw	$t7,0x0($s5)
.L0f0247b0:
/*  f0247b0:	8fa80280 */ 	lw	$t0,0x280($sp)
/*  f0247b4:	27b0007c */ 	addiu	$s0,$sp,0x7c
/*  f0247b8:	3c158006 */ 	lui	$s5,%hi(var80062960)
/*  f0247bc:	8d04001c */ 	lw	$a0,0x1c($t0)
/*  f0247c0:	26b52960 */ 	addiu	$s5,$s5,%lo(var80062960)
/*  f0247c4:	02002825 */ 	or	$a1,$s0,$zero
/*  f0247c8:	24060100 */ 	addiu	$a2,$zero,0x100
/*  f0247cc:	0fc197e0 */ 	jal	roomGetProps
/*  f0247d0:	24840028 */ 	addiu	$a0,$a0,0x28
/*  f0247d4:	87a9007c */ 	lh	$t1,0x7c($sp)
/*  f0247d8:	0200a025 */ 	or	$s4,$s0,$zero
/*  f0247dc:	27aa007c */ 	addiu	$t2,$sp,0x7c
/*  f0247e0:	052000c0 */ 	bltz	$t1,.L0f024ae4
/*  f0247e4:	241e0001 */ 	addiu	$s8,$zero,0x1
/*  f0247e8:	3c16800a */ 	lui	$s6,%hi(g_Vars)
/*  f0247ec:	26d69fc0 */ 	addiu	$s6,$s6,%lo(g_Vars)
/*  f0247f0:	85420000 */ 	lh	$v0,0x0($t2)
/*  f0247f4:	2417015c */ 	addiu	$s7,$zero,0x15c
/*  f0247f8:	8ecc0338 */ 	lw	$t4,0x338($s6)
.L0f0247fc:
/*  f0247fc:	000258c0 */ 	sll	$t3,$v0,0x3
/*  f024800:	01625821 */ 	addu	$t3,$t3,$v0
/*  f024804:	000b58c0 */ 	sll	$t3,$t3,0x3
/*  f024808:	016c2821 */ 	addu	$a1,$t3,$t4
/*  f02480c:	90ad0000 */ 	lbu	$t5,0x0($a1)
/*  f024810:	24010002 */ 	addiu	$at,$zero,0x2
/*  f024814:	55a100b0 */ 	bnel	$t5,$at,.L0f024ad8
/*  f024818:	86820002 */ 	lh	$v0,0x2($s4)
/*  f02481c:	90ae0001 */ 	lbu	$t6,0x1($a1)
/*  f024820:	31cf0002 */ 	andi	$t7,$t6,0x2
/*  f024824:	51e000ac */ 	beqzl	$t7,.L0f024ad8
/*  f024828:	86820002 */ 	lh	$v0,0x2($s4)
/*  f02482c:	8ca20004 */ 	lw	$v0,0x4($a1)
/*  f024830:	3c188008 */ 	lui	$t8,%hi(g_ModelTypeWindowedDoor)
/*  f024834:	2718aed8 */ 	addiu	$t8,$t8,%lo(g_ModelTypeWindowedDoor)
/*  f024838:	8c590018 */ 	lw	$t9,0x18($v0)
/*  f02483c:	00409025 */ 	or	$s2,$v0,$zero
/*  f024840:	00401825 */ 	or	$v1,$v0,$zero
/*  f024844:	8f280008 */ 	lw	$t0,0x8($t9)
/*  f024848:	8d090004 */ 	lw	$t1,0x4($t0)
/*  f02484c:	530900a2 */ 	beql	$t8,$t1,.L0f024ad8
/*  f024850:	86820002 */ 	lh	$v0,0x2($s4)
/*  f024854:	94420072 */ 	lhu	$v0,0x72($v0)
/*  f024858:	24010006 */ 	addiu	$at,$zero,0x6
/*  f02485c:	1041009d */ 	beq	$v0,$at,.L0f024ad4
/*  f024860:	24010007 */ 	addiu	$at,$zero,0x7
/*  f024864:	1041009b */ 	beq	$v0,$at,.L0f024ad4
/*  f024868:	24010008 */ 	addiu	$at,$zero,0x8
/*  f02486c:	10410099 */ 	beq	$v0,$at,.L0f024ad4
/*  f024870:	24010009 */ 	addiu	$at,$zero,0x9
/*  f024874:	50410098 */ 	beql	$v0,$at,.L0f024ad8
/*  f024878:	86820002 */ 	lh	$v0,0x2($s4)
/*  f02487c:	8e4a0008 */ 	lw	$t2,0x8($s2)
/*  f024880:	3c010400 */ 	lui	$at,0x400
/*  f024884:	34210010 */ 	ori	$at,$at,0x10
/*  f024888:	01415824 */ 	and	$t3,$t2,$at
/*  f02488c:	55600092 */ 	bnezl	$t3,.L0f024ad8
/*  f024890:	86820002 */ 	lh	$v0,0x2($s4)
/*  f024894:	8e4c000c */ 	lw	$t4,0xc($s2)
/*  f024898:	000c6800 */ 	sll	$t5,$t4,0x0
/*  f02489c:	05a2008e */ 	bltzl	$t5,.L0f024ad8
/*  f0248a0:	86820002 */ 	lh	$v0,0x2($s4)
/*  f0248a4:	946e0070 */ 	lhu	$t6,0x70($v1)
/*  f0248a8:	31cf0080 */ 	andi	$t7,$t6,0x80
/*  f0248ac:	55e00008 */ 	bnezl	$t7,.L0f0248d0
/*  f0248b0:	8e640000 */ 	lw	$a0,0x0($s3)
/*  f0248b4:	44802000 */ 	mtc1	$zero,$f4
/*  f0248b8:	c466007c */ 	lwc1	$f6,0x7c($v1)
/*  f0248bc:	4606203c */ 	c.lt.s	$f4,$f6
/*  f0248c0:	00000000 */ 	nop
/*  f0248c4:	45030084 */ 	bc1tl	.L0f024ad8
/*  f0248c8:	86820002 */ 	lh	$v0,0x2($s4)
/*  f0248cc:	8e640000 */ 	lw	$a0,0x0($s3)
.L0f0248d0:
/*  f0248d0:	00001825 */ 	or	$v1,$zero,$zero
/*  f0248d4:	5880000a */ 	blezl	$a0,.L0f024900
/*  f0248d8:	0064082a */ 	slt	$at,$v1,$a0
/*  f0248dc:	8ea20000 */ 	lw	$v0,0x0($s5)
.L0f0248e0:
/*  f0248e0:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f0248e4:	50b90006 */ 	beql	$a1,$t9,.L0f024900
/*  f0248e8:	0064082a */ 	slt	$at,$v1,$a0
/*  f0248ec:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f0248f0:	0064082a */ 	slt	$at,$v1,$a0
/*  f0248f4:	1420fffa */ 	bnez	$at,.L0f0248e0
/*  f0248f8:	2442015c */ 	addiu	$v0,$v0,0x15c
/*  f0248fc:	0064082a */ 	slt	$at,$v1,$a0
.L0f024900:
/*  f024900:	50200008 */ 	beqzl	$at,.L0f024924
/*  f024904:	2881000f */ 	slti	$at,$a0,0xf
/*  f024908:	00770019 */ 	multu	$v1,$s7
/*  f02490c:	8eb80000 */ 	lw	$t8,0x0($s5)
/*  f024910:	00004012 */ 	mflo	$t0
/*  f024914:	01188021 */ 	addu	$s0,$t0,$t8
/*  f024918:	10000010 */ 	b	.L0f02495c
/*  f02491c:	8e0d000c */ 	lw	$t5,0xc($s0)
/*  f024920:	2881000f */ 	slti	$at,$a0,0xf
.L0f024924:
/*  f024924:	5020006c */ 	beqzl	$at,.L0f024ad8
/*  f024928:	86820002 */ 	lh	$v0,0x2($s4)
/*  f02492c:	00970019 */ 	multu	$a0,$s7
/*  f024930:	8eaa0000 */ 	lw	$t2,0x0($s5)
/*  f024934:	00004812 */ 	mflo	$t1
/*  f024938:	012a8021 */ 	addu	$s0,$t1,$t2
/*  f02493c:	ae050000 */ 	sw	$a1,0x0($s0)
/*  f024940:	ae00000c */ 	sw	$zero,0xc($s0)
/*  f024944:	ae000130 */ 	sw	$zero,0x130($s0)
/*  f024948:	ae000004 */ 	sw	$zero,0x4($s0)
/*  f02494c:	8e6b0000 */ 	lw	$t3,0x0($s3)
/*  f024950:	256c0001 */ 	addiu	$t4,$t3,0x1
/*  f024954:	ae6c0000 */ 	sw	$t4,0x0($s3)
/*  f024958:	8e0d000c */ 	lw	$t5,0xc($s0)
.L0f02495c:
/*  f02495c:	55a00034 */ 	bnezl	$t5,.L0f024a30
/*  f024960:	8fb90280 */ 	lw	$t9,0x280($sp)
/*  f024964:	0fc1a2bd */ 	jal	objFindBboxRodata
/*  f024968:	02402025 */ 	or	$a0,$s2,$zero
/*  f02496c:	8c410000 */ 	lw	$at,0x0($v0)
/*  f024970:	2611002c */ 	addiu	$s1,$s0,0x2c
/*  f024974:	02202825 */ 	or	$a1,$s1,$zero
/*  f024978:	ae010010 */ 	sw	$at,0x10($s0)
/*  f02497c:	8c4f0004 */ 	lw	$t7,0x4($v0)
/*  f024980:	2644001c */ 	addiu	$a0,$s2,0x1c
/*  f024984:	ae0f0014 */ 	sw	$t7,0x14($s0)
/*  f024988:	8c410008 */ 	lw	$at,0x8($v0)
/*  f02498c:	ae010018 */ 	sw	$at,0x18($s0)
/*  f024990:	8c4f000c */ 	lw	$t7,0xc($v0)
/*  f024994:	ae0f001c */ 	sw	$t7,0x1c($s0)
/*  f024998:	8c410010 */ 	lw	$at,0x10($v0)
/*  f02499c:	ae010020 */ 	sw	$at,0x20($s0)
/*  f0249a0:	8c4f0014 */ 	lw	$t7,0x14($v0)
/*  f0249a4:	ae0f0024 */ 	sw	$t7,0x24($s0)
/*  f0249a8:	8c410018 */ 	lw	$at,0x18($v0)
/*  f0249ac:	0c005755 */ 	jal	func00015d54
/*  f0249b0:	ae010028 */ 	sw	$at,0x28($s0)
/*  f0249b4:	8e440014 */ 	lw	$a0,0x14($s2)
/*  f0249b8:	02202825 */ 	or	$a1,$s1,$zero
/*  f0249bc:	0c005775 */ 	jal	func00015dd4
/*  f0249c0:	24840008 */ 	addiu	$a0,$a0,0x8
/*  f0249c4:	2612006c */ 	addiu	$s2,$s0,0x6c
/*  f0249c8:	02402825 */ 	or	$a1,$s2,$zero
/*  f0249cc:	0c005cbc */ 	jal	func000172f0
/*  f0249d0:	02202025 */ 	or	$a0,$s1,$zero
/*  f0249d4:	8ec20284 */ 	lw	$v0,0x284($s6)
/*  f0249d8:	c6080074 */ 	lwc1	$f8,0x74($s0)
/*  f0249dc:	c6120084 */ 	lwc1	$f18,0x84($s0)
/*  f0249e0:	c44a1bb0 */ 	lwc1	$f10,0x1bb0($v0)
/*  f0249e4:	c4441bb4 */ 	lwc1	$f4,0x1bb4($v0)
/*  f0249e8:	24421bb0 */ 	addiu	$v0,$v0,0x1bb0
/*  f0249ec:	460a4402 */ 	mul.s	$f16,$f8,$f10
/*  f0249f0:	c60a0094 */ 	lwc1	$f10,0x94($s0)
/*  f0249f4:	46049182 */ 	mul.s	$f6,$f18,$f4
/*  f0249f8:	c4520008 */ 	lwc1	$f18,0x8($v0)
/*  f0249fc:	46125102 */ 	mul.s	$f4,$f10,$f18
/*  f024a00:	46068200 */ 	add.s	$f8,$f16,$f6
/*  f024a04:	c60600a4 */ 	lwc1	$f6,0xa4($s0)
/*  f024a08:	46044400 */ 	add.s	$f16,$f8,$f4
/*  f024a0c:	46103280 */ 	add.s	$f10,$f6,$f16
/*  f024a10:	0fc2d5de */ 	jal	currentPlayerGetUnk174c
/*  f024a14:	e60a012c */ 	swc1	$f10,0x12c($s0)
/*  f024a18:	02402025 */ 	or	$a0,$s2,$zero
/*  f024a1c:	00402825 */ 	or	$a1,$v0,$zero
/*  f024a20:	0c0056f9 */ 	jal	func00015be4
/*  f024a24:	260600ac */ 	addiu	$a2,$s0,0xac
/*  f024a28:	ae1e000c */ 	sw	$s8,0xc($s0)
/*  f024a2c:	8fb90280 */ 	lw	$t9,0x280($sp)
.L0f024a30:
/*  f024a30:	27a50054 */ 	addiu	$a1,$sp,0x54
/*  f024a34:	0c006b43 */ 	jal	modelGetRootPosition
/*  f024a38:	8f240020 */ 	lw	$a0,0x20($t9)
/*  f024a3c:	c6120074 */ 	lwc1	$f18,0x74($s0)
/*  f024a40:	c7a80054 */ 	lwc1	$f8,0x54($sp)
/*  f024a44:	c6060084 */ 	lwc1	$f6,0x84($s0)
/*  f024a48:	c7b00058 */ 	lwc1	$f16,0x58($sp)
/*  f024a4c:	46089102 */ 	mul.s	$f4,$f18,$f8
/*  f024a50:	c6080094 */ 	lwc1	$f8,0x94($s0)
/*  f024a54:	c6000028 */ 	lwc1	$f0,0x28($s0)
/*  f024a58:	46103282 */ 	mul.s	$f10,$f6,$f16
/*  f024a5c:	c7a6005c */ 	lwc1	$f6,0x5c($sp)
/*  f024a60:	46064402 */ 	mul.s	$f16,$f8,$f6
/*  f024a64:	460a2480 */ 	add.s	$f18,$f4,$f10
/*  f024a68:	c60a00a4 */ 	lwc1	$f10,0xa4($s0)
/*  f024a6c:	46109100 */ 	add.s	$f4,$f18,$f16
/*  f024a70:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f024a74:	e6080008 */ 	swc1	$f8,0x8($s0)
/*  f024a78:	c6020008 */ 	lwc1	$f2,0x8($s0)
/*  f024a7c:	4602003c */ 	c.lt.s	$f0,$f2
/*  f024a80:	00000000 */ 	nop
/*  f024a84:	45020008 */ 	bc1fl	.L0f024aa8
/*  f024a88:	c6100024 */ 	lwc1	$f16,0x24($s0)
/*  f024a8c:	c606012c */ 	lwc1	$f6,0x12c($s0)
/*  f024a90:	c6120024 */ 	lwc1	$f18,0x24($s0)
/*  f024a94:	4612303c */ 	c.lt.s	$f6,$f18
/*  f024a98:	00000000 */ 	nop
/*  f024a9c:	4503000c */ 	bc1tl	.L0f024ad0
/*  f024aa0:	ae1e0004 */ 	sw	$s8,0x4($s0)
/*  f024aa4:	c6100024 */ 	lwc1	$f16,0x24($s0)
.L0f024aa8:
/*  f024aa8:	4610103c */ 	c.lt.s	$f2,$f16
/*  f024aac:	00000000 */ 	nop
/*  f024ab0:	45020009 */ 	bc1fl	.L0f024ad8
/*  f024ab4:	86820002 */ 	lh	$v0,0x2($s4)
/*  f024ab8:	c60a012c */ 	lwc1	$f10,0x12c($s0)
/*  f024abc:	460a003c */ 	c.lt.s	$f0,$f10
/*  f024ac0:	00000000 */ 	nop
/*  f024ac4:	45020004 */ 	bc1fl	.L0f024ad8
/*  f024ac8:	86820002 */ 	lh	$v0,0x2($s4)
/*  f024acc:	ae1e0004 */ 	sw	$s8,0x4($s0)
.L0f024ad0:
/*  f024ad0:	afbe006c */ 	sw	$s8,0x6c($sp)
.L0f024ad4:
/*  f024ad4:	86820002 */ 	lh	$v0,0x2($s4)
.L0f024ad8:
/*  f024ad8:	26940002 */ 	addiu	$s4,$s4,0x2
/*  f024adc:	0443ff47 */ 	bgezl	$v0,.L0f0247fc
/*  f024ae0:	8ecc0338 */ 	lw	$t4,0x338($s6)
.L0f024ae4:
/*  f024ae4:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f024ae8:	8fa2006c */ 	lw	$v0,0x6c($sp)
/*  f024aec:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f024af0:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f024af4:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f024af8:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f024afc:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f024b00:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f024b04:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f024b08:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f024b0c:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f024b10:	03e00008 */ 	jr	$ra
/*  f024b14:	27bd0280 */ 	addiu	$sp,$sp,0x280
);

GLOBAL_ASM(
glabel func0f024b18
.late_rodata
glabel var7f1a87dc
.word func0f024b18+0x2b8 # f024dd0
glabel var7f1a87e0
.word func0f024b18+0x2d4 # f024dec
glabel var7f1a87e4
.word func0f024b18+0x2f0 # f024e08
glabel var7f1a87e8
.word func0f024b18+0x30c # f024e24
glabel var7f1a87ec
.word func0f024b18+0x328 # f024e40
glabel var7f1a87f0
.word func0f024b18+0x344 # f024e5c
glabel var7f1a87f4
.word func0f024b18+0x360 # f024e78
glabel var7f1a87f8
.word func0f024b18+0x37c # f024e94
.text
/*  f024b18:	27bdfee8 */ 	addiu	$sp,$sp,-280
/*  f024b1c:	afbf0044 */ 	sw	$ra,0x44($sp)
/*  f024b20:	afbe0040 */ 	sw	$s8,0x40($sp)
/*  f024b24:	afb7003c */ 	sw	$s7,0x3c($sp)
/*  f024b28:	afb60038 */ 	sw	$s6,0x38($sp)
/*  f024b2c:	afb50034 */ 	sw	$s5,0x34($sp)
/*  f024b30:	afb40030 */ 	sw	$s4,0x30($sp)
/*  f024b34:	afb3002c */ 	sw	$s3,0x2c($sp)
/*  f024b38:	afb20028 */ 	sw	$s2,0x28($sp)
/*  f024b3c:	afb10024 */ 	sw	$s1,0x24($sp)
/*  f024b40:	afb00020 */ 	sw	$s0,0x20($sp)
/*  f024b44:	f7b40018 */ 	sdc1	$f20,0x18($sp)
/*  f024b48:	8c8e001c */ 	lw	$t6,0x1c($a0)
/*  f024b4c:	00801825 */ 	or	$v1,$a0,$zero
/*  f024b50:	51c0000d */ 	beqzl	$t6,.L0f024b88
/*  f024b54:	8c620004 */ 	lw	$v0,0x4($v1)
/*  f024b58:	8c8f0018 */ 	lw	$t7,0x18($a0)
/*  f024b5c:	51e0000a */ 	beqzl	$t7,.L0f024b88
/*  f024b60:	8c620004 */ 	lw	$v0,0x4($v1)
/*  f024b64:	8c620018 */ 	lw	$v0,0x18($v1)
/*  f024b68:	8c58001c */ 	lw	$t8,0x1c($v0)
.L0f024b6c:
/*  f024b6c:	00401825 */ 	or	$v1,$v0,$zero
/*  f024b70:	53000005 */ 	beqzl	$t8,.L0f024b88
/*  f024b74:	8c620004 */ 	lw	$v0,0x4($v1)
/*  f024b78:	8c420018 */ 	lw	$v0,0x18($v0)
/*  f024b7c:	5440fffb */ 	bnezl	$v0,.L0f024b6c
/*  f024b80:	8c58001c */ 	lw	$t8,0x1c($v0)
/*  f024b84:	8c620004 */ 	lw	$v0,0x4($v1)
.L0f024b88:
/*  f024b88:	5040012d */ 	beqzl	$v0,.L0f025040
/*  f024b8c:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f024b90:	10a00009 */ 	beqz	$a1,.L0f024bb8
/*  f024b94:	00a01025 */ 	or	$v0,$a1,$zero
/*  f024b98:	2403000a */ 	addiu	$v1,$zero,0xa
/*  f024b9c:	94590000 */ 	lhu	$t9,0x0($v0)
.L0f024ba0:
/*  f024ba0:	332800ff */ 	andi	$t0,$t9,0xff
/*  f024ba4:	10680004 */ 	beq	$v1,$t0,.L0f024bb8
/*  f024ba8:	00000000 */ 	nop
/*  f024bac:	8c420008 */ 	lw	$v0,0x8($v0)
/*  f024bb0:	5440fffb */ 	bnezl	$v0,.L0f024ba0
/*  f024bb4:	94590000 */ 	lhu	$t9,0x0($v0)
.L0f024bb8:
/*  f024bb8:	10400120 */ 	beqz	$v0,.L0f02503c
/*  f024bbc:	00003025 */ 	or	$a2,$zero,$zero
/*  f024bc0:	0c006973 */ 	jal	func0001a5cc
/*  f024bc4:	8c500004 */ 	lw	$s0,0x4($v0)
/*  f024bc8:	3c098006 */ 	lui	$t1,%hi(var80062964)
/*  f024bcc:	8d292964 */ 	lw	$t1,%lo(var80062964)($t1)
/*  f024bd0:	0040f025 */ 	or	$s8,$v0,$zero
/*  f024bd4:	00002025 */ 	or	$a0,$zero,$zero
/*  f024bd8:	19200118 */ 	blez	$t1,.L0f02503c
/*  f024bdc:	00001825 */ 	or	$v1,$zero,$zero
/*  f024be0:	4480a000 */ 	mtc1	$zero,$f20
/*  f024be4:	27b700b4 */ 	addiu	$s7,$sp,0xb4
/*  f024be8:	27b60064 */ 	addiu	$s6,$sp,0x64
/*  f024bec:	27b30070 */ 	addiu	$s3,$sp,0x70
.L0f024bf0:
/*  f024bf0:	3c028006 */ 	lui	$v0,%hi(var80062960)
/*  f024bf4:	8c422960 */ 	lw	$v0,%lo(var80062960)($v0)
/*  f024bf8:	afa30058 */ 	sw	$v1,0x58($sp)
/*  f024bfc:	afa400fc */ 	sw	$a0,0xfc($sp)
/*  f024c00:	00435021 */ 	addu	$t2,$v0,$v1
/*  f024c04:	8d4b0004 */ 	lw	$t3,0x4($t2)
/*  f024c08:	00628821 */ 	addu	$s1,$v1,$v0
/*  f024c0c:	0000a025 */ 	or	$s4,$zero,$zero
/*  f024c10:	11600102 */ 	beqz	$t3,.L0f02501c
/*  f024c14:	262400ac */ 	addiu	$a0,$s1,0xac
/*  f024c18:	afa000b0 */ 	sw	$zero,0xb0($sp)
/*  f024c1c:	8e2d0000 */ 	lw	$t5,0x0($s1)
/*  f024c20:	03c02825 */ 	or	$a1,$s8,$zero
/*  f024c24:	02e03025 */ 	or	$a2,$s7,$zero
/*  f024c28:	00009025 */ 	or	$s2,$zero,$zero
/*  f024c2c:	0c0056f9 */ 	jal	func00015be4
/*  f024c30:	8db50004 */ 	lw	$s5,0x4($t5)
/*  f024c34:	8e2e0130 */ 	lw	$t6,0x130($s1)
/*  f024c38:	55c0005e */ 	bnezl	$t6,.L0f024db4
/*  f024c3c:	2e410008 */ 	sltiu	$at,$s2,0x8
/*  f024c40:	96af0072 */ 	lhu	$t7,0x72($s5)
/*  f024c44:	24010004 */ 	addiu	$at,$zero,0x4
/*  f024c48:	55e10015 */ 	bnel	$t7,$at,.L0f024ca0
/*  f024c4c:	c6320018 */ 	lwc1	$f18,0x18($s1)
/*  f024c50:	c6240014 */ 	lwc1	$f4,0x14($s1)
/*  f024c54:	e7a400a0 */ 	swc1	$f4,0xa0($sp)
/*  f024c58:	c626001c */ 	lwc1	$f6,0x1c($s1)
/*  f024c5c:	e7a600a4 */ 	swc1	$f6,0xa4($sp)
/*  f024c60:	c6280024 */ 	lwc1	$f8,0x24($s1)
/*  f024c64:	e7a800a8 */ 	swc1	$f8,0xa8($sp)
/*  f024c68:	c62a0018 */ 	lwc1	$f10,0x18($s1)
/*  f024c6c:	e7aa0094 */ 	swc1	$f10,0x94($sp)
/*  f024c70:	c632001c */ 	lwc1	$f18,0x1c($s1)
/*  f024c74:	e7b20098 */ 	swc1	$f18,0x98($sp)
/*  f024c78:	c6240024 */ 	lwc1	$f4,0x24($s1)
/*  f024c7c:	e7a4009c */ 	swc1	$f4,0x9c($sp)
/*  f024c80:	c6260018 */ 	lwc1	$f6,0x18($s1)
/*  f024c84:	e7a60088 */ 	swc1	$f6,0x88($sp)
/*  f024c88:	c6280020 */ 	lwc1	$f8,0x20($s1)
/*  f024c8c:	e7a8008c */ 	swc1	$f8,0x8c($sp)
/*  f024c90:	c62a0024 */ 	lwc1	$f10,0x24($s1)
/*  f024c94:	10000013 */ 	b	.L0f024ce4
/*  f024c98:	e7aa0090 */ 	swc1	$f10,0x90($sp)
/*  f024c9c:	c6320018 */ 	lwc1	$f18,0x18($s1)
.L0f024ca0:
/*  f024ca0:	e7b200a0 */ 	swc1	$f18,0xa0($sp)
/*  f024ca4:	c6240020 */ 	lwc1	$f4,0x20($s1)
/*  f024ca8:	e7a400a4 */ 	swc1	$f4,0xa4($sp)
/*  f024cac:	c6260024 */ 	lwc1	$f6,0x24($s1)
/*  f024cb0:	e7a600a8 */ 	swc1	$f6,0xa8($sp)
/*  f024cb4:	c6280018 */ 	lwc1	$f8,0x18($s1)
/*  f024cb8:	e7a80094 */ 	swc1	$f8,0x94($sp)
/*  f024cbc:	c62a001c */ 	lwc1	$f10,0x1c($s1)
/*  f024cc0:	e7aa0098 */ 	swc1	$f10,0x98($sp)
/*  f024cc4:	c6320024 */ 	lwc1	$f18,0x24($s1)
/*  f024cc8:	e7b2009c */ 	swc1	$f18,0x9c($sp)
/*  f024ccc:	c6240014 */ 	lwc1	$f4,0x14($s1)
/*  f024cd0:	e7a40088 */ 	swc1	$f4,0x88($sp)
/*  f024cd4:	c626001c */ 	lwc1	$f6,0x1c($s1)
/*  f024cd8:	e7a6008c */ 	swc1	$f6,0x8c($sp)
/*  f024cdc:	c6280024 */ 	lwc1	$f8,0x24($s1)
/*  f024ce0:	e7a80090 */ 	swc1	$f8,0x90($sp)
.L0f024ce4:
/*  f024ce4:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f024ce8:	00000000 */ 	nop
/*  f024cec:	263500ec */ 	addiu	$s5,$s1,0xec
/*  f024cf0:	02a03025 */ 	or	$a2,$s5,$zero
/*  f024cf4:	00402025 */ 	or	$a0,$v0,$zero
/*  f024cf8:	0c0056f9 */ 	jal	func00015be4
/*  f024cfc:	2625002c */ 	addiu	$a1,$s1,0x2c
/*  f024d00:	02a02025 */ 	or	$a0,$s5,$zero
/*  f024d04:	27a500a0 */ 	addiu	$a1,$sp,0xa0
/*  f024d08:	0c0056da */ 	jal	func00015b68
/*  f024d0c:	02603025 */ 	or	$a2,$s3,$zero
/*  f024d10:	02602025 */ 	or	$a0,$s3,$zero
/*  f024d14:	0fc2d37b */ 	jal	func0f0b4dec
/*  f024d18:	26250134 */ 	addiu	$a1,$s1,0x134
/*  f024d1c:	02a02025 */ 	or	$a0,$s5,$zero
/*  f024d20:	27a50094 */ 	addiu	$a1,$sp,0x94
/*  f024d24:	0c0056da */ 	jal	func00015b68
/*  f024d28:	02603025 */ 	or	$a2,$s3,$zero
/*  f024d2c:	02602025 */ 	or	$a0,$s3,$zero
/*  f024d30:	0fc2d37b */ 	jal	func0f0b4dec
/*  f024d34:	2625013c */ 	addiu	$a1,$s1,0x13c
/*  f024d38:	02a02025 */ 	or	$a0,$s5,$zero
/*  f024d3c:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f024d40:	0c0056da */ 	jal	func00015b68
/*  f024d44:	02603025 */ 	or	$a2,$s3,$zero
/*  f024d48:	02602025 */ 	or	$a0,$s3,$zero
/*  f024d4c:	0fc2d37b */ 	jal	func0f0b4dec
/*  f024d50:	26250144 */ 	addiu	$a1,$s1,0x144
/*  f024d54:	c62e0134 */ 	lwc1	$f14,0x134($s1)
/*  f024d58:	c632013c */ 	lwc1	$f18,0x13c($s1)
/*  f024d5c:	c62c0138 */ 	lwc1	$f12,0x138($s1)
/*  f024d60:	c62a0140 */ 	lwc1	$f10,0x140($s1)
/*  f024d64:	460e9081 */ 	sub.s	$f2,$f18,$f14
/*  f024d68:	c6280148 */ 	lwc1	$f8,0x148($s1)
/*  f024d6c:	c6320144 */ 	lwc1	$f18,0x144($s1)
/*  f024d70:	460c5001 */ 	sub.s	$f0,$f10,$f12
/*  f024d74:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f024d78:	ae380130 */ 	sw	$t8,0x130($s1)
/*  f024d7c:	46001087 */ 	neg.s	$f2,$f2
/*  f024d80:	e620014c */ 	swc1	$f0,0x14c($s1)
/*  f024d84:	46026102 */ 	mul.s	$f4,$f12,$f2
/*  f024d88:	e6220150 */ 	swc1	$f2,0x150($s1)
/*  f024d8c:	460e0182 */ 	mul.s	$f6,$f0,$f14
/*  f024d90:	46062400 */ 	add.s	$f16,$f4,$f6
/*  f024d94:	46024282 */ 	mul.s	$f10,$f8,$f2
/*  f024d98:	00000000 */ 	nop
/*  f024d9c:	46120102 */ 	mul.s	$f4,$f0,$f18
/*  f024da0:	e6300154 */ 	swc1	$f16,0x154($s1)
/*  f024da4:	46045180 */ 	add.s	$f6,$f10,$f4
/*  f024da8:	46103201 */ 	sub.s	$f8,$f6,$f16
/*  f024dac:	e6280158 */ 	swc1	$f8,0x158($s1)
/*  f024db0:	2e410008 */ 	sltiu	$at,$s2,0x8
.L0f024db4:
/*  f024db4:	1020003d */ 	beqz	$at,.L0f024eac
/*  f024db8:	0012c880 */ 	sll	$t9,$s2,0x2
/*  f024dbc:	3c017f1b */ 	lui	$at,%hi(var7f1a87dc)
/*  f024dc0:	00390821 */ 	addu	$at,$at,$t9
/*  f024dc4:	8c3987dc */ 	lw	$t9,%lo(var7f1a87dc)($at)
/*  f024dc8:	03200008 */ 	jr	$t9
/*  f024dcc:	00000000 */ 	nop
/*  f024dd0:	c6120004 */ 	lwc1	$f18,0x4($s0)
/*  f024dd4:	e7b20064 */ 	swc1	$f18,0x64($sp)
/*  f024dd8:	c60a000c */ 	lwc1	$f10,0xc($s0)
/*  f024ddc:	e7aa0068 */ 	swc1	$f10,0x68($sp)
/*  f024de0:	c6040014 */ 	lwc1	$f4,0x14($s0)
/*  f024de4:	10000031 */ 	b	.L0f024eac
/*  f024de8:	e7a4006c */ 	swc1	$f4,0x6c($sp)
/*  f024dec:	c6060004 */ 	lwc1	$f6,0x4($s0)
/*  f024df0:	e7a60064 */ 	swc1	$f6,0x64($sp)
/*  f024df4:	c608000c */ 	lwc1	$f8,0xc($s0)
/*  f024df8:	e7a80068 */ 	swc1	$f8,0x68($sp)
/*  f024dfc:	c6120018 */ 	lwc1	$f18,0x18($s0)
/*  f024e00:	1000002a */ 	b	.L0f024eac
/*  f024e04:	e7b2006c */ 	swc1	$f18,0x6c($sp)
/*  f024e08:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f024e0c:	e7aa0064 */ 	swc1	$f10,0x64($sp)
/*  f024e10:	c6040010 */ 	lwc1	$f4,0x10($s0)
/*  f024e14:	e7a40068 */ 	swc1	$f4,0x68($sp)
/*  f024e18:	c6060014 */ 	lwc1	$f6,0x14($s0)
/*  f024e1c:	10000023 */ 	b	.L0f024eac
/*  f024e20:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*  f024e24:	c6080004 */ 	lwc1	$f8,0x4($s0)
/*  f024e28:	e7a80064 */ 	swc1	$f8,0x64($sp)
/*  f024e2c:	c6120010 */ 	lwc1	$f18,0x10($s0)
/*  f024e30:	e7b20068 */ 	swc1	$f18,0x68($sp)
/*  f024e34:	c60a0018 */ 	lwc1	$f10,0x18($s0)
/*  f024e38:	1000001c */ 	b	.L0f024eac
/*  f024e3c:	e7aa006c */ 	swc1	$f10,0x6c($sp)
/*  f024e40:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f024e44:	e7a40064 */ 	swc1	$f4,0x64($sp)
/*  f024e48:	c606000c */ 	lwc1	$f6,0xc($s0)
/*  f024e4c:	e7a60068 */ 	swc1	$f6,0x68($sp)
/*  f024e50:	c6080014 */ 	lwc1	$f8,0x14($s0)
/*  f024e54:	10000015 */ 	b	.L0f024eac
/*  f024e58:	e7a8006c */ 	swc1	$f8,0x6c($sp)
/*  f024e5c:	c6120008 */ 	lwc1	$f18,0x8($s0)
/*  f024e60:	e7b20064 */ 	swc1	$f18,0x64($sp)
/*  f024e64:	c60a000c */ 	lwc1	$f10,0xc($s0)
/*  f024e68:	e7aa0068 */ 	swc1	$f10,0x68($sp)
/*  f024e6c:	c6040018 */ 	lwc1	$f4,0x18($s0)
/*  f024e70:	1000000e */ 	b	.L0f024eac
/*  f024e74:	e7a4006c */ 	swc1	$f4,0x6c($sp)
/*  f024e78:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*  f024e7c:	e7a60064 */ 	swc1	$f6,0x64($sp)
/*  f024e80:	c6080010 */ 	lwc1	$f8,0x10($s0)
/*  f024e84:	e7a80068 */ 	swc1	$f8,0x68($sp)
/*  f024e88:	c6120014 */ 	lwc1	$f18,0x14($s0)
/*  f024e8c:	10000007 */ 	b	.L0f024eac
/*  f024e90:	e7b2006c */ 	swc1	$f18,0x6c($sp)
/*  f024e94:	c60a0008 */ 	lwc1	$f10,0x8($s0)
/*  f024e98:	e7aa0064 */ 	swc1	$f10,0x64($sp)
/*  f024e9c:	c6040010 */ 	lwc1	$f4,0x10($s0)
/*  f024ea0:	e7a40068 */ 	swc1	$f4,0x68($sp)
/*  f024ea4:	c6060018 */ 	lwc1	$f6,0x18($s0)
/*  f024ea8:	e7a6006c */ 	swc1	$f6,0x6c($sp)
.L0f024eac:
/*  f024eac:	03c02025 */ 	or	$a0,$s8,$zero
/*  f024eb0:	02c02825 */ 	or	$a1,$s6,$zero
/*  f024eb4:	0c0056da */ 	jal	func00015b68
/*  f024eb8:	02603025 */ 	or	$a2,$s3,$zero
/*  f024ebc:	02602025 */ 	or	$a0,$s3,$zero
/*  f024ec0:	0fc2d37b */ 	jal	func0f0b4dec
/*  f024ec4:	27a50080 */ 	addiu	$a1,$sp,0x80
/*  f024ec8:	c7a80084 */ 	lwc1	$f8,0x84($sp)
/*  f024ecc:	c6320150 */ 	lwc1	$f18,0x150($s1)
/*  f024ed0:	c624014c */ 	lwc1	$f4,0x14c($s1)
/*  f024ed4:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f024ed8:	46124282 */ 	mul.s	$f10,$f8,$f18
/*  f024edc:	c6220158 */ 	lwc1	$f2,0x158($s1)
/*  f024ee0:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f024ee4:	c6240154 */ 	lwc1	$f4,0x154($s1)
/*  f024ee8:	4602a03e */ 	c.le.s	$f20,$f2
/*  f024eec:	46085480 */ 	add.s	$f18,$f10,$f8
/*  f024ef0:	45000005 */ 	bc1f	.L0f024f08
/*  f024ef4:	46049001 */ 	sub.s	$f0,$f18,$f4
/*  f024ef8:	4614003c */ 	c.lt.s	$f0,$f20
/*  f024efc:	00000000 */ 	nop
/*  f024f00:	45030009 */ 	bc1tl	.L0f024f28
/*  f024f04:	24080001 */ 	addiu	$t0,$zero,0x1
.L0f024f08:
/*  f024f08:	4614103e */ 	c.le.s	$f2,$f20
/*  f024f0c:	00000000 */ 	nop
/*  f024f10:	45000007 */ 	bc1f	.L0f024f30
/*  f024f14:	00000000 */ 	nop
/*  f024f18:	4600a03c */ 	c.lt.s	$f20,$f0
/*  f024f1c:	00000000 */ 	nop
/*  f024f20:	45000003 */ 	bc1f	.L0f024f30
/*  f024f24:	24080001 */ 	addiu	$t0,$zero,0x1
.L0f024f28:
/*  f024f28:	10000036 */ 	b	.L0f025004
/*  f024f2c:	afa800b0 */ 	sw	$t0,0xb0($sp)
.L0f024f30:
/*  f024f30:	16800030 */ 	bnez	$s4,.L0f024ff4
/*  f024f34:	02e02025 */ 	or	$a0,$s7,$zero
/*  f024f38:	02c02825 */ 	or	$a1,$s6,$zero
/*  f024f3c:	0c0056da */ 	jal	func00015b68
/*  f024f40:	02603025 */ 	or	$a2,$s3,$zero
/*  f024f44:	c7a60070 */ 	lwc1	$f6,0x70($sp)
/*  f024f48:	c62a0014 */ 	lwc1	$f10,0x14($s1)
/*  f024f4c:	4606503e */ 	c.le.s	$f10,$f6
/*  f024f50:	00000000 */ 	nop
/*  f024f54:	45020028 */ 	bc1fl	.L0f024ff8
/*  f024f58:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f024f5c:	c6280018 */ 	lwc1	$f8,0x18($s1)
/*  f024f60:	c7b20074 */ 	lwc1	$f18,0x74($sp)
/*  f024f64:	4608303e */ 	c.le.s	$f6,$f8
/*  f024f68:	00000000 */ 	nop
/*  f024f6c:	45020022 */ 	bc1fl	.L0f024ff8
/*  f024f70:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f024f74:	c624001c */ 	lwc1	$f4,0x1c($s1)
/*  f024f78:	4612203e */ 	c.le.s	$f4,$f18
/*  f024f7c:	00000000 */ 	nop
/*  f024f80:	4502001d */ 	bc1fl	.L0f024ff8
/*  f024f84:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f024f88:	c62a0020 */ 	lwc1	$f10,0x20($s1)
/*  f024f8c:	460a903e */ 	c.le.s	$f18,$f10
/*  f024f90:	00000000 */ 	nop
/*  f024f94:	45020018 */ 	bc1fl	.L0f024ff8
/*  f024f98:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f024f9c:	c6200028 */ 	lwc1	$f0,0x28($s1)
/*  f024fa0:	c6220008 */ 	lwc1	$f2,0x8($s1)
/*  f024fa4:	c7a80078 */ 	lwc1	$f8,0x78($sp)
/*  f024fa8:	4602003c */ 	c.lt.s	$f0,$f2
/*  f024fac:	00000000 */ 	nop
/*  f024fb0:	45020006 */ 	bc1fl	.L0f024fcc
/*  f024fb4:	c6200024 */ 	lwc1	$f0,0x24($s1)
/*  f024fb8:	4600403c */ 	c.lt.s	$f8,$f0
/*  f024fbc:	00000000 */ 	nop
/*  f024fc0:	4503000c */ 	bc1tl	.L0f024ff4
/*  f024fc4:	24140001 */ 	addiu	$s4,$zero,0x1
/*  f024fc8:	c6200024 */ 	lwc1	$f0,0x24($s1)
.L0f024fcc:
/*  f024fcc:	c7a60078 */ 	lwc1	$f6,0x78($sp)
/*  f024fd0:	4600103c */ 	c.lt.s	$f2,$f0
/*  f024fd4:	00000000 */ 	nop
/*  f024fd8:	45020007 */ 	bc1fl	.L0f024ff8
/*  f024fdc:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f024fe0:	4606003c */ 	c.lt.s	$f0,$f6
/*  f024fe4:	00000000 */ 	nop
/*  f024fe8:	45020003 */ 	bc1fl	.L0f024ff8
/*  f024fec:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f024ff0:	24140001 */ 	addiu	$s4,$zero,0x1
.L0f024ff4:
/*  f024ff4:	26520001 */ 	addiu	$s2,$s2,0x1
.L0f024ff8:
/*  f024ff8:	24010008 */ 	addiu	$at,$zero,0x8
/*  f024ffc:	5641ff6d */ 	bnel	$s2,$at,.L0f024db4
/*  f025000:	2e410008 */ 	sltiu	$at,$s2,0x8
.L0f025004:
/*  f025004:	12800005 */ 	beqz	$s4,.L0f02501c
/*  f025008:	8fa900b0 */ 	lw	$t1,0xb0($sp)
/*  f02500c:	55200004 */ 	bnezl	$t1,.L0f025020
/*  f025010:	8fa400fc */ 	lw	$a0,0xfc($sp)
/*  f025014:	1000000a */ 	b	.L0f025040
/*  f025018:	00001025 */ 	or	$v0,$zero,$zero
.L0f02501c:
/*  f02501c:	8fa400fc */ 	lw	$a0,0xfc($sp)
.L0f025020:
/*  f025020:	3c0a8006 */ 	lui	$t2,%hi(var80062964)
/*  f025024:	8d4a2964 */ 	lw	$t2,%lo(var80062964)($t2)
/*  f025028:	8fa30058 */ 	lw	$v1,0x58($sp)
/*  f02502c:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f025030:	008a082a */ 	slt	$at,$a0,$t2
/*  f025034:	1420feee */ 	bnez	$at,.L0f024bf0
/*  f025038:	2463015c */ 	addiu	$v1,$v1,0x15c
.L0f02503c:
/*  f02503c:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f025040:
/*  f025040:	8fbf0044 */ 	lw	$ra,0x44($sp)
/*  f025044:	d7b40018 */ 	ldc1	$f20,0x18($sp)
/*  f025048:	8fb00020 */ 	lw	$s0,0x20($sp)
/*  f02504c:	8fb10024 */ 	lw	$s1,0x24($sp)
/*  f025050:	8fb20028 */ 	lw	$s2,0x28($sp)
/*  f025054:	8fb3002c */ 	lw	$s3,0x2c($sp)
/*  f025058:	8fb40030 */ 	lw	$s4,0x30($sp)
/*  f02505c:	8fb50034 */ 	lw	$s5,0x34($sp)
/*  f025060:	8fb60038 */ 	lw	$s6,0x38($sp)
/*  f025064:	8fb7003c */ 	lw	$s7,0x3c($sp)
/*  f025068:	8fbe0040 */ 	lw	$s8,0x40($sp)
/*  f02506c:	03e00008 */ 	jr	$ra
/*  f025070:	27bd0118 */ 	addiu	$sp,$sp,0x118
);

/**
 * Render an object that's attached to or held by a chr such as their weapon,
 * mines that are stuck to them, and knives/bolts which are embedded in them.
 *
 * This function is recursive. The chr's gun can have mines placed on it, and
 * mines can also have further mines placed on them.
 */
void chrRenderAttachedObject(struct prop *prop, struct modelrenderdata *renderdata, bool withalpha, struct chrdata *chr)
{
	if (prop->flags & PROPFLAG_ONSCREEN) {
		u32 stack;
		struct defaultobj *obj = prop->obj;
		struct model *model = obj->model;
		struct prop *child;

		modelRender(renderdata, model);

		// Note: OBJH2FLAG_RENDEROPAQUE << 1 is OBJH2FLAG_RENDERALPHA
		// so this is just checking if the appropriate flag is enabled
		if (obj->hidden2 & OBJH2FLAG_RENDEROPAQUE << withalpha) {
			renderdata->gdl = func0f140e20(renderdata->gdl, prop, withalpha);
		}

		child = prop->child;

		while (child) {
			chrRenderAttachedObject(child, renderdata, withalpha, chr);
			child = child->next;
		}

		if (withalpha) {
			func0f0c33f0(model->matrices, model->filedata->nummatrices);
		}
	}
}

void bodyGetBloodColour(s16 bodynum, u8 *colour1, u32 *colour2)
{
	switch (bodynum) {
	case BODY_ELVIS1:
	case BODY_THEKING:
	case BODY_ELVISWAISTCOAT:
		if (colour1) {
			colour1[0] = 10;
			colour1[1] = 0x40;
			colour1[2] = 10;
		}
		if (colour2) {
			colour2[0] = 0x103010ff;
			colour2[1] = 0x104010ff;
			colour2[2] = 0x005611a0;
		}
		return;
	case BODY_DRCAROLL:
	case BODY_EYESPY:
	case BODY_CHICROB:
		if (colour1) {
			colour1[0] = 10;
			colour1[1] = 10;
			colour1[2] = 10;
		}
		if (colour2) {
			colour2[0] = 0xb0b030a0;
			colour2[1] = 0xe0e030a0;
			colour2[2] = 0xe0e050a0;
		}
		return;
	case BODY_MRBLONDE:
	case BODY_SKEDAR:
	case BODY_MINISKEDAR:
	case BODY_SKEDARKING:
		if (colour1) {
			colour1[0] = 0x40;
			colour1[1] = 0x19;
			colour1[2] = 10;
		}
		if (colour2) {
			colour2[0] = 0x302010ff;
			colour2[1] = 0x402010ff;
			colour2[2] = 0x560011a0;
		}
		return;
	}

	if (colour1) {
		colour1[0] = 0x40;
		colour1[1] = 10;
		colour1[2] = 10;
	}

	if (colour2) {
		colour2[0] = 0x301010ff;
		colour2[1] = 0x401010ff;
		colour2[2] = 0x560011a0;
	}
}

Gfx *chrRender(struct prop *prop, Gfx *gdl, bool withalpha)
{
	struct chrdata *chr = prop->chr;
	struct model *model = chr->model;
	f32 sp108[4];
	s32 sp104;
	s32 sp100;
	s32 alpha;
	struct eyespy *eyespy;
	struct prop *child;
	f32 xrayalphafrac;
	u8 spec[4];
	u8 speb = 0;

	// Don't render the eyespy if we're the one controlling it
	if (CHRRACE(chr) == RACE_EYESPY) {
		eyespy = chrToEyespy(chr);

		if (eyespy) {
			if (!eyespy->initialised) {
				return gdl;
			}

			if (eyespy == g_Vars.currentplayer->eyespy && eyespy->active) {
				return gdl;
			}
		}
	}

	if (chr->chrflags & CHRCFLAG_UNPLAYABLE) {
		alpha = 0xff;
	} else {
		alpha = chr->fadealpha;
	}

	if (chr->aibot && chr->aibot->unk058 > 0) {
		alpha = (f32)alpha * (PALDOWN(120) - chr->aibot->unk058) * (PAL ? 0.01f : 0.0083333337679505f);
	}

	bodyGetBloodColour(chr->bodynum, spec, NULL);
	func0f0246e4(spec);
	alpha *= func0f08e6bc(prop, func0001af80(model));

	if (g_Vars.currentplayer->visionmode == VISIONMODE_XRAY) {
		f32 fadedist;
		f32 chrdist = sqrtf(ERASERSQDIST(prop->pos.f));

		if (chrdist > g_Vars.currentplayer->eraserpropdist) {
			return gdl;
		}

		alpha = 128;
		fadedist = g_Vars.currentplayer->eraserpropdist - 150;

		if (chrdist > fadedist) {
			alpha = (1.0f - (chrdist - fadedist) / 150.0f) * 128;
		}

		xrayalphafrac = chrdist / g_Vars.currentplayer->eraserpropdist;

		if (xrayalphafrac > 1.0f) {
			xrayalphafrac = 1.0f;
		}
	}

	if (g_Vars.currentplayer->isdead
			|| g_InCutscene
			|| !EYESPYINACTIVE()
			|| (g_Vars.currentplayer->devicesactive & ~g_Vars.currentplayer->devicesinhibit & DEVICE_IRSCANNER) == 0) {
		alpha = func0f022be4(chr) * alpha * 0.0039215688593686f;
	}

	if (alpha < 0xff) {
		if (!withalpha) {
			return gdl;
		}

		sp100 = 3;
	} else {
		if (!withalpha) {
			sp100 = 1;
		} else {
			sp100 = 2;
		}
	}

	sp104 = func0f1667f4(prop, sp108);

	if (chr->unk32c_18) {
		func0f069144(chr->prop, chr->nextcol, chr->floorcol);
		chr->unk32c_18 = false;
	}

	if (sp104 && alpha > 0) {
		struct modelrenderdata renderdata = {0, 1, 3};
		struct screenbox screenbox;
		s32 colour[4]; // rgba levels, but allowing > 256 temporarily
		u32 stack;

		if (withalpha && chr->cloakfadefrac > 0 && !chr->cloakfadefinished) {
			gdl = func0f02bdf8(gdl, chr->prop, chr->prop);
		}

		if (func0f08e5a8(prop->rooms, &screenbox) > 0 && (chr->chrflags & CHRCFLAG_UNPLAYABLE) == 0) {
			gdl = currentPlayerScissorWithinViewport(gdl, screenbox.xmin, screenbox.ymin, screenbox.xmax, screenbox.ymax);
		} else {
			gdl = currentPlayerScissorToViewport(gdl);
		}

		renderdata.flags = sp100;
		renderdata.zbufferenabled = true;
		renderdata.gdl = gdl;

		// Configure colours for IR scanner or default
		if (!g_Vars.currentplayer->isdead
				&& !g_InCutscene
				&& EYESPYINACTIVE()
				&& (g_Vars.currentplayer->devicesactive & ~g_Vars.currentplayer->devicesinhibit & DEVICE_IRSCANNER)) {
			colour[0] = 0xff;
			colour[1] = 0;
			colour[2] = 0;
			colour[3] = 0x80;
		} else {
			colour[0] = chr->shadecol[0];
			colour[1] = chr->shadecol[1];
			colour[2] = chr->shadecol[2];
			colour[3] = chr->shadecol[3];
		}

		if (g_Vars.normmplayerisrunning) {
			speb = func0f185e20(prop, colour);
		}

		if (!speb) {
			colour[3] = colour[3] - func0f068fc8(prop, true);

			if (colour[3] > 0xff) {
				colour[3] = 0xff;
			}

			if (colour[3] < 0) {
				colour[3] = 0;
			}
		}

		func0f069750(colour, sp104, sp108);

		// Configure colours for night vision if in use
		if (!g_Vars.currentplayer->isdead
				&& !g_InCutscene
				&& EYESPYINACTIVE()
				&& (g_Vars.currentplayer->devicesactive & ~g_Vars.currentplayer->devicesinhibit & DEVICE_NIGHTVISION)) {
			colour[0] = var8009caec[3];
			colour[1] = var8009caec[3];
			colour[2] = var8009caec[3];
			colour[3] = var8009caf0;
		}

		// Configure colours for xray if in use
		if (g_Vars.currentplayer->visionmode == VISIONMODE_XRAY) {
			colour[g_Vars.currentplayer->epcol_0] = xrayalphafrac * 255;
			colour[g_Vars.currentplayer->epcol_1] = (1 - xrayalphafrac) * 255;
			colour[g_Vars.currentplayer->epcol_2] = 0;
			colour[3] = 0xff;
		}

		renderdata.envcolour = var80062a48[0] << 24 | var80062a48[1] << 16 | var80062a48[2] << 8;
		renderdata.fogcolour = colour[0] << 24 | colour[1] << 16 | colour[2] << 8 | colour[3];

		if (alpha < 0xff) {
			renderdata.unk30 = 8;
			renderdata.envcolour |= (u8)alpha;
		} else {
			renderdata.unk30 = 7;
		}

		// Set Skedar eyes open or closed
		if (model->filedata->type == &g_ModelTypeSkedar) {
			struct modelnode *node1 = modelGetPart(model->filedata, MODELPART_SKEDAR_EYESOPEN);
			struct modelnode *node2 = modelGetPart(model->filedata, MODELPART_SKEDAR_EYESCLOSED);

			if (node1 && node2) {
				union modelrwdata *data1 = modelGetNodeRwData(model, node1);
				union modelrwdata *data2 = modelGetNodeRwData(model, node2);

				data2->toggle.visible = chr->actiontype == ACT_DIE || chr->actiontype == ACT_DEAD;
				data1->toggle.visible = !data2->toggle.visible;
			}
		}

		// Set Maian eyes open or closed
		if (chr->headnum == HEAD_THEKING
				|| chr->headnum == HEAD_ELVIS
				|| chr->headnum == HEAD_MAIAN_S
				|| chr->headnum == HEAD_ELVIS_GOGS) {
			if (model->filedata->type == &g_ModelTypeChr) {
				struct modelnode *headspotnode = modelGetPart(model->filedata, MODELPART_CHR_HEADSPOT);

				if (headspotnode && headspotnode->type == MODELNODETYPE_HEADSPOT) {
					union modelrwdata *headrwdata = modelGetNodeRwData(model, headspotnode);

					if (headrwdata->headspot.modelfiledata) {
						struct modelnode *node1 = modelGetPart(headrwdata->headspot.modelfiledata, MODELPART_HEAD_EYESOPEN);
						struct modelnode *node2 = modelGetPart(headrwdata->headspot.modelfiledata, MODELPART_HEAD_EYESCLOSED);

						if (node1 && node2) {
							union modelrwdata *data1 = modelGetNodeRwData(model, node1);
							union modelrwdata *data2 = modelGetNodeRwData(model, node2);

							data2->toggle.visible = chr->actiontype == ACT_DIE || chr->actiontype == ACT_DEAD;
							data1->toggle.visible = !data2->toggle.visible;
						}
					}
				}
			}
		}

		if (chr->race == RACE_DRCAROLL) {
			chrSetDrCarollImages(chr, chr->drcarollimage_left, chr->drcarollimage_right);
		}

		g_Vars.currentplayerstats->drawplayercount++;

		if (func0f024738(chr)) {
			var8005efc4 = func0f024b18;
		}

		// Render the chr's model
		modelRender(&renderdata, model);

		// Render attached props (eg. held guns and attached mines/knives/bolts)
		child = prop->child;

		while (child) {
			chrRenderAttachedObject(child, &renderdata, withalpha, chr);
			child = child->next;
		}

		gdl = renderdata.gdl;

		var8005efc4 = NULL;

		// Render shadow
		if (withalpha) {
			if (!chr->onladder && chr->actiontype != ACT_SKJUMP) {
				s32 shadowalpha = 0;

				if (chr->ground == 0) {
					shadowalpha = 1;
				}

				// @bug: The wrong variable is being used in the minimum bounds
				// check. However, the approach to this is also flawed. The RSP
				// can crash if drawing outside of its allowed range, which is
				// actually -32768.99 to 32767.99. And this range is relative
				// to the camera, not in world coordinates. This bad check
				// doesn't cause any crashes though, because even if a chr falls
				// out of the geometry they likely wouldn't be rendered due to
				// not being in an active room and also being out of the draw
				// distance.
				if (shadowalpha > -65536.0f && chr->ground < 65536.0f) {
					f32 gaptoground = prop->pos.y - chr->ground;
					f32 size; // unsure if radius or diameter

					if (gaptoground <= 400 && g_Vars.currentplayer->visionmode != VISIONMODE_XRAY) {
						if (chr->bodynum == BODY_SKEDAR || chr->bodynum == BODY_SKEDARKING) {
							size = 80;
						} else if (chr->bodynum == BODY_EYESPY) {
							size = 12;
						} else {
							size = 35;
						}

						if (chr->chrflags & CHRCFLAG_NOSHADOW) {
							shadowalpha = 0;
						} else if (sp104 == 1) {
							shadowalpha = (1.0f - sp108[3]) * ((alpha * 100) >> 8);
						} else {
							shadowalpha = (s32)(alpha * 100) >> 8;
						}

						if (gaptoground >= 150.0f) {
							shadowalpha = shadowalpha * (400 - gaptoground) * 0.004f;
						}

						if (cheatIsActive(CHEAT_SMALLCHARACTERS)) {
							size *= 0.4f;
						}

						gdl = gfxRenderRadialShadow(gdl, prop->pos.x, chr->ground, prop->pos.z, chrGetInverseTheta(chr), size, shadowalpha | ~0xff);
					}
				}
			}

			func0f0c33f0(model->matrices, model->filedata->nummatrices);

			if (!g_Vars.currentplayer->isdead
					&& !g_InCutscene
					&& EYESPYINACTIVE()
					&& (g_Vars.currentplayer->devicesactive & ~g_Vars.currentplayer->devicesinhibit & DEVICE_IRSCANNER)) {
				gdl = chrRenderShield(gdl, chr, 0x80);
			} else {
				gdl = chrRenderShield(gdl, chr, alpha);
			}
		}
	}

	return gdl;
}

struct var80062a8c *var80062a8c = NULL;

void chrEmitSparks(struct chrdata *chr, struct prop *prop, s32 hitpart, struct coord *coord, struct coord *coord2, struct chrdata *chr2)
{
	struct prop *chrprop = chr->prop;
	s32 race;

	if (chrIsUsingPaintball(chr2)) {
		sparksCreate(chrprop->rooms[0], chrprop, coord, coord2, 0, SPARKTYPE_19);
		return;
	}

	if (chrGetShield(chr) > 0.0f) {
		sparksCreate(chrprop->rooms[0], chrprop, coord, coord2, 0, SPARKTYPE_00);
		return;
	}

	if (prop->type == PROPTYPE_OBJ
			|| prop->type == PROPTYPE_WEAPON
			|| prop->type == PROPTYPE_DOOR
			|| hitpart == HITPART_GUN
			|| hitpart == HITPART_HAT) {
		sparksCreate(chrprop->rooms[0], chrprop, coord, coord2, 0, SPARKTYPE_00);
		return;
	}

	race = CHRRACE(chr);

	if (race == RACE_DRCAROLL || race == RACE_ROBOT || race == RACE_EYESPY) {
		sparksCreate(chrprop->rooms[0], chrprop, coord, coord2, 0, SPARKTYPE_01);
		return;
	}

	if (chr->noblood) {
		return;
	}

	if ((random() & 4) == 0) {
		struct coord coord3;
		coord3.x = coord2->x * 42.0f + coord->x;
		coord3.y = coord2->y * 42.0f + coord->y;
		coord3.z = coord2->z * 42.0f + coord->z;

		sparksCreate(chrprop->rooms[0], chrprop, &coord3, coord2, 0, SPARKTYPE_04);
	}

	sparksCreate(chrprop->rooms[0], chrprop, coord, coord2, 0, SPARKTYPE_02);
	sparksCreate(chrprop->rooms[0], chrprop, coord, coord2, 0, SPARKTYPE_03);
}

GLOBAL_ASM(
glabel func0f0260c4
/*  f0260c4:	27bdfed8 */ 	addiu	$sp,$sp,-296
/*  f0260c8:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f0260cc:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f0260d0:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f0260d4:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f0260d8:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f0260dc:	3c107fff */ 	lui	$s0,0x7fff
/*  f0260e0:	00e09025 */ 	or	$s2,$a3,$zero
/*  f0260e4:	00c09825 */ 	or	$s3,$a2,$zero
/*  f0260e8:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f0260ec:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f0260f0:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f0260f4:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f0260f8:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f0260fc:	afa40128 */ 	sw	$a0,0x128($sp)
/*  f026100:	afa5012c */ 	sw	$a1,0x12c($sp)
/*  f026104:	00008825 */ 	or	$s1,$zero,$zero
/*  f026108:	3610ffff */ 	ori	$s0,$s0,0xffff
/*  f02610c:	0c004b70 */ 	jal	random
/*  f026110:	afa00100 */ 	sw	$zero,0x100($sp)
/*  f026114:	24010032 */ 	addiu	$at,$zero,0x32
/*  f026118:	0041001b */ 	divu	$zero,$v0,$at
/*  f02611c:	00007010 */ 	mfhi	$t6
/*  f026120:	25cf0014 */ 	addiu	$t7,$t6,0x14
/*  f026124:	afaf00cc */ 	sw	$t7,0xcc($sp)
/*  f026128:	afa000c0 */ 	sw	$zero,0xc0($sp)
/*  f02612c:	0c0069d0 */ 	jal	func0001a740
/*  f026130:	02602025 */ 	or	$a0,$s3,$zero
/*  f026134:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f026138:	00402825 */ 	or	$a1,$v0,$zero
/*  f02613c:	0c006b57 */ 	jal	modelNodeGetModelRelativePosition
/*  f026140:	27a600f4 */ 	addiu	$a2,$sp,0xf4
/*  f026144:	c6440000 */ 	lwc1	$f4,0x0($s2)
/*  f026148:	c7a600f4 */ 	lwc1	$f6,0xf4($sp)
/*  f02614c:	c7b000f8 */ 	lwc1	$f16,0xf8($sp)
/*  f026150:	02602825 */ 	or	$a1,$s3,$zero
/*  f026154:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f026158:	c7a600fc */ 	lwc1	$f6,0xfc($sp)
/*  f02615c:	24160011 */ 	addiu	$s6,$zero,0x11
/*  f026160:	2415000a */ 	addiu	$s5,$zero,0xa
/*  f026164:	e7a800dc */ 	swc1	$f8,0xdc($sp)
/*  f026168:	c64a0004 */ 	lwc1	$f10,0x4($s2)
/*  f02616c:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f026170:	e7b200e0 */ 	swc1	$f18,0xe0($sp)
/*  f026174:	c6440008 */ 	lwc1	$f4,0x8($s2)
/*  f026178:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f02617c:	126000c7 */ 	beqz	$s3,.L0f02649c
/*  f026180:	e7a800e4 */ 	swc1	$f8,0xe4($sp)
/*  f026184:	94b40000 */ 	lhu	$s4,0x0($a1)
.L0f026188:
/*  f026188:	24010008 */ 	addiu	$at,$zero,0x8
/*  f02618c:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f026190:	329800ff */ 	andi	$t8,$s4,0xff
/*  f026194:	13010099 */ 	beq	$t8,$at,.L0f0263fc
/*  f026198:	0300a025 */ 	or	$s4,$t8,$zero
/*  f02619c:	24010012 */ 	addiu	$at,$zero,0x12
/*  f0261a0:	1301009b */ 	beq	$t8,$at,.L0f026410
/*  f0261a4:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f0261a8:	24010017 */ 	addiu	$at,$zero,0x17
/*  f0261ac:	1301009d */ 	beq	$t8,$at,.L0f026424
/*  f0261b0:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f0261b4:	24010018 */ 	addiu	$at,$zero,0x18
/*  f0261b8:	13010003 */ 	beq	$t8,$at,.L0f0261c8
/*  f0261bc:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f0261c0:	1000009c */ 	b	.L0f026434
/*  f0261c4:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f0261c8:
/*  f0261c8:	8cb20004 */ 	lw	$s2,0x4($a1)
/*  f0261cc:	0c006a87 */ 	jal	modelGetNodeRwData
/*  f0261d0:	afa50110 */ 	sw	$a1,0x110($sp)
/*  f0261d4:	8c440004 */ 	lw	$a0,0x4($v0)
/*  f0261d8:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f0261dc:	54800004 */ 	bnezl	$a0,.L0f0261f0
/*  f0261e0:	8e430000 */ 	lw	$v1,0x0($s2)
/*  f0261e4:	10000093 */ 	b	.L0f026434
/*  f0261e8:	8ca20014 */ 	lw	$v0,0x14($a1)
/*  f0261ec:	8e430000 */ 	lw	$v1,0x0($s2)
.L0f0261f0:
/*  f0261f0:	3c0100ff */ 	lui	$at,0xff
/*  f0261f4:	3421ffff */ 	ori	$at,$at,0xffff
/*  f0261f8:	14640005 */ 	bne	$v1,$a0,.L0f026210
/*  f0261fc:	0080f025 */ 	or	$s8,$a0,$zero
/*  f026200:	8e4a0008 */ 	lw	$t2,0x8($s2)
/*  f026204:	00615824 */ 	and	$t3,$v1,$at
/*  f026208:	10000001 */ 	b	.L0f026210
/*  f02620c:	014bf021 */ 	addu	$s8,$t2,$t3
.L0f026210:
/*  f026210:	8e420004 */ 	lw	$v0,0x4($s2)
/*  f026214:	3c0100ff */ 	lui	$at,0xff
/*  f026218:	50400008 */ 	beqzl	$v0,.L0f02623c
/*  f02621c:	afa00108 */ 	sw	$zero,0x108($sp)
/*  f026220:	8e4c0008 */ 	lw	$t4,0x8($s2)
/*  f026224:	3421ffff */ 	ori	$at,$at,0xffff
/*  f026228:	00416824 */ 	and	$t5,$v0,$at
/*  f02622c:	018d7021 */ 	addu	$t6,$t4,$t5
/*  f026230:	10000002 */ 	b	.L0f02623c
/*  f026234:	afae0108 */ 	sw	$t6,0x108($sp)
/*  f026238:	afa00108 */ 	sw	$zero,0x108($sp)
.L0f02623c:
/*  f02623c:	83c20000 */ 	lb	$v0,0x0($s8)
/*  f026240:	2401ffb8 */ 	addiu	$at,$zero,-72
/*  f026244:	8faf0108 */ 	lw	$t7,0x108($sp)
/*  f026248:	5441000a */ 	bnel	$v0,$at,.L0f026274
/*  f02624c:	24010004 */ 	addiu	$at,$zero,0x4
/*  f026250:	51e00005 */ 	beqzl	$t7,.L0f026268
/*  f026254:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f026258:	01e0f025 */ 	or	$s8,$t7,$zero
/*  f02625c:	1000fff7 */ 	b	.L0f02623c
/*  f026260:	afa00108 */ 	sw	$zero,0x108($sp)
/*  f026264:	8fa50110 */ 	lw	$a1,0x110($sp)
.L0f026268:
/*  f026268:	10000072 */ 	b	.L0f026434
/*  f02626c:	8ca20014 */ 	lw	$v0,0x14($a1)
/*  f026270:	24010004 */ 	addiu	$at,$zero,0x4
.L0f026274:
/*  f026274:	1441003e */ 	bne	$v0,$at,.L0f026370
/*  f026278:	8fac0100 */ 	lw	$t4,0x100($sp)
/*  f02627c:	8fc20004 */ 	lw	$v0,0x4($s8)
/*  f026280:	93c90001 */ 	lbu	$t1,0x1($s8)
/*  f026284:	3c0100ff */ 	lui	$at,0xff
/*  f026288:	8e4a000c */ 	lw	$t2,0xc($s2)
/*  f02628c:	3421ffff */ 	ori	$at,$at,0xffff
/*  f026290:	0041c824 */ 	and	$t9,$v0,$at
/*  f026294:	00095902 */ 	srl	$t3,$t1,0x4
/*  f026298:	25690001 */ 	addiu	$t1,$t3,0x1
/*  f02629c:	11800055 */ 	beqz	$t4,.L0f0263f4
/*  f0262a0:	01591821 */ 	addu	$v1,$t2,$t9
/*  f0262a4:	19200053 */ 	blez	$t1,.L0f0263f4
/*  f0262a8:	00003025 */ 	or	$a2,$zero,$zero
/*  f0262ac:	00601025 */ 	or	$v0,$v1,$zero
.L0f0262b0:
/*  f0262b0:	84470000 */ 	lh	$a3,0x0($v0)
/*  f0262b4:	8fad00d0 */ 	lw	$t5,0xd0($sp)
/*  f0262b8:	8fae00d4 */ 	lw	$t6,0xd4($sp)
/*  f0262bc:	844f0002 */ 	lh	$t7,0x2($v0)
/*  f0262c0:	01a71823 */ 	subu	$v1,$t5,$a3
/*  f0262c4:	00630019 */ 	multu	$v1,$v1
/*  f0262c8:	01cf2023 */ 	subu	$a0,$t6,$t7
/*  f0262cc:	8fb800d8 */ 	lw	$t8,0xd8($sp)
/*  f0262d0:	84590004 */ 	lh	$t9,0x4($v0)
/*  f0262d4:	24c60001 */ 	addiu	$a2,$a2,0x1
/*  f0262d8:	c7aa00e8 */ 	lwc1	$f10,0xe8($sp)
/*  f0262dc:	03192823 */ 	subu	$a1,$t8,$t9
/*  f0262e0:	00005012 */ 	mflo	$t2
/*  f0262e4:	00000000 */ 	nop
/*  f0262e8:	00000000 */ 	nop
/*  f0262ec:	00840019 */ 	multu	$a0,$a0
/*  f0262f0:	00005812 */ 	mflo	$t3
/*  f0262f4:	014b6021 */ 	addu	$t4,$t2,$t3
/*  f0262f8:	00000000 */ 	nop
/*  f0262fc:	00a50019 */ 	multu	$a1,$a1
/*  f026300:	00006812 */ 	mflo	$t5
/*  f026304:	018d4021 */ 	addu	$t0,$t4,$t5
/*  f026308:	0110082a */ 	slt	$at,$t0,$s0
/*  f02630c:	10200014 */ 	beqz	$at,.L0f026360
/*  f026310:	00000000 */ 	nop
/*  f026314:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f026318:	c7b200ec */ 	lwc1	$f18,0xec($sp)
/*  f02631c:	c7a600f0 */ 	lwc1	$f6,0xf0($sp)
/*  f026320:	01008025 */ 	or	$s0,$t0,$zero
/*  f026324:	440f8000 */ 	mfc1	$t7,$f16
/*  f026328:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f02632c:	8fb10110 */ 	lw	$s1,0x110($sp)
/*  f026330:	01e7c021 */ 	addu	$t8,$t7,$a3
/*  f026334:	afb80114 */ 	sw	$t8,0x114($sp)
/*  f026338:	844b0002 */ 	lh	$t3,0x2($v0)
/*  f02633c:	440a2000 */ 	mfc1	$t2,$f4
/*  f026340:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f026344:	014b6021 */ 	addu	$t4,$t2,$t3
/*  f026348:	afac0118 */ 	sw	$t4,0x118($sp)
/*  f02634c:	844f0004 */ 	lh	$t7,0x4($v0)
/*  f026350:	440e4000 */ 	mfc1	$t6,$f8
/*  f026354:	00000000 */ 	nop
/*  f026358:	01cfc021 */ 	addu	$t8,$t6,$t7
/*  f02635c:	afb8011c */ 	sw	$t8,0x11c($sp)
.L0f026360:
/*  f026360:	14c9ffd3 */ 	bne	$a2,$t1,.L0f0262b0
/*  f026364:	2442000c */ 	addiu	$v0,$v0,0xc
/*  f026368:	1000ffb4 */ 	b	.L0f02623c
/*  f02636c:	27de0008 */ 	addiu	$s8,$s8,0x8
.L0f026370:
/*  f026370:	24010001 */ 	addiu	$at,$zero,0x1
/*  f026374:	1441001f */ 	bne	$v0,$at,.L0f0263f4
/*  f026378:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f02637c:	8fc20004 */ 	lw	$v0,0x4($s8)
/*  f026380:	3c0100ff */ 	lui	$at,0xff
/*  f026384:	3421ffff */ 	ori	$at,$at,0xffff
/*  f026388:	0041c824 */ 	and	$t9,$v0,$at
/*  f02638c:	0c00698d */ 	jal	func0001a634
/*  f026390:	00192982 */ 	srl	$a1,$t9,0x6
/*  f026394:	afa20100 */ 	sw	$v0,0x100($sp)
/*  f026398:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f02639c:	00402825 */ 	or	$a1,$v0,$zero
/*  f0263a0:	0c006b57 */ 	jal	modelNodeGetModelRelativePosition
/*  f0263a4:	27a600e8 */ 	addiu	$a2,$sp,0xe8
/*  f0263a8:	c7aa00e8 */ 	lwc1	$f10,0xe8($sp)
/*  f0263ac:	c7b000dc */ 	lwc1	$f16,0xdc($sp)
/*  f0263b0:	c7a600ec */ 	lwc1	$f6,0xec($sp)
/*  f0263b4:	c7a800e0 */ 	lwc1	$f8,0xe0($sp)
/*  f0263b8:	46105480 */ 	add.s	$f18,$f10,$f16
/*  f0263bc:	46083280 */ 	add.s	$f10,$f6,$f8
/*  f0263c0:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f0263c4:	c7b200f0 */ 	lwc1	$f18,0xf0($sp)
/*  f0263c8:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f0263cc:	440b2000 */ 	mfc1	$t3,$f4
/*  f0263d0:	c7a400e4 */ 	lwc1	$f4,0xe4($sp)
/*  f0263d4:	440d8000 */ 	mfc1	$t5,$f16
/*  f0263d8:	46049180 */ 	add.s	$f6,$f18,$f4
/*  f0263dc:	afab00d0 */ 	sw	$t3,0xd0($sp)
/*  f0263e0:	afad00d4 */ 	sw	$t5,0xd4($sp)
/*  f0263e4:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f0263e8:	440f4000 */ 	mfc1	$t7,$f8
/*  f0263ec:	00000000 */ 	nop
/*  f0263f0:	afaf00d8 */ 	sw	$t7,0xd8($sp)
.L0f0263f4:
/*  f0263f4:	1000ff91 */ 	b	.L0f02623c
/*  f0263f8:	27de0008 */ 	addiu	$s8,$s8,0x8
.L0f0263fc:
/*  f0263fc:	0c0071e1 */ 	jal	func0001c784
/*  f026400:	afa50110 */ 	sw	$a1,0x110($sp)
/*  f026404:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f026408:	1000000a */ 	b	.L0f026434
/*  f02640c:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f026410:
/*  f026410:	0c0071f4 */ 	jal	func0001c7d0
/*  f026414:	afa50110 */ 	sw	$a1,0x110($sp)
/*  f026418:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f02641c:	10000005 */ 	b	.L0f026434
/*  f026420:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f026424:
/*  f026424:	0c007207 */ 	jal	modelAttachHead
/*  f026428:	afa50110 */ 	sw	$a1,0x110($sp)
/*  f02642c:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f026430:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f026434:
/*  f026434:	10400009 */ 	beqz	$v0,.L0f02645c
/*  f026438:	00000000 */ 	nop
/*  f02643c:	10b30005 */ 	beq	$a1,$s3,.L0f026454
/*  f026440:	00000000 */ 	nop
/*  f026444:	12950005 */ 	beq	$s4,$s5,.L0f02645c
/*  f026448:	00000000 */ 	nop
/*  f02644c:	12960003 */ 	beq	$s4,$s6,.L0f02645c
/*  f026450:	00000000 */ 	nop
.L0f026454:
/*  f026454:	1000000f */ 	b	.L0f026494
/*  f026458:	00402825 */ 	or	$a1,$v0,$zero
.L0f02645c:
/*  f02645c:	10a0000d */ 	beqz	$a1,.L0f026494
/*  f026460:	00000000 */ 	nop
.L0f026464:
/*  f026464:	54b30004 */ 	bnel	$a1,$s3,.L0f026478
/*  f026468:	8ca2000c */ 	lw	$v0,0xc($a1)
/*  f02646c:	10000009 */ 	b	.L0f026494
/*  f026470:	00002825 */ 	or	$a1,$zero,$zero
/*  f026474:	8ca2000c */ 	lw	$v0,0xc($a1)
.L0f026478:
/*  f026478:	50400004 */ 	beqzl	$v0,.L0f02648c
/*  f02647c:	8ca50008 */ 	lw	$a1,0x8($a1)
/*  f026480:	10000004 */ 	b	.L0f026494
/*  f026484:	00402825 */ 	or	$a1,$v0,$zero
/*  f026488:	8ca50008 */ 	lw	$a1,0x8($a1)
.L0f02648c:
/*  f02648c:	14a0fff5 */ 	bnez	$a1,.L0f026464
/*  f026490:	00000000 */ 	nop
.L0f026494:
/*  f026494:	54a0ff3c */ 	bnezl	$a1,.L0f026188
/*  f026498:	94b40000 */ 	lhu	$s4,0x0($a1)
.L0f02649c:
/*  f02649c:	122000fb */ 	beqz	$s1,.L0f02688c
/*  f0264a0:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f0264a4:	8c8b0008 */ 	lw	$t3,0x8($a0)
/*  f0264a8:	2417000c */ 	addiu	$s7,$zero,0xc
/*  f0264ac:	8d650000 */ 	lw	$a1,0x0($t3)
/*  f0264b0:	50a000f7 */ 	beqzl	$a1,.L0f026890
/*  f0264b4:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f0264b8:	94a20000 */ 	lhu	$v0,0x0($a1)
.L0f0264bc:
/*  f0264bc:	24010008 */ 	addiu	$at,$zero,0x8
/*  f0264c0:	304c00ff */ 	andi	$t4,$v0,0xff
/*  f0264c4:	118100ce */ 	beq	$t4,$at,.L0f026800
/*  f0264c8:	24010012 */ 	addiu	$at,$zero,0x12
/*  f0264cc:	118100d2 */ 	beq	$t4,$at,.L0f026818
/*  f0264d0:	24010017 */ 	addiu	$at,$zero,0x17
/*  f0264d4:	118100d6 */ 	beq	$t4,$at,.L0f026830
/*  f0264d8:	24010018 */ 	addiu	$at,$zero,0x18
/*  f0264dc:	51810004 */ 	beql	$t4,$at,.L0f0264f0
/*  f0264e0:	8cb20004 */ 	lw	$s2,0x4($a1)
/*  f0264e4:	100000d7 */ 	b	.L0f026844
/*  f0264e8:	8ca20014 */ 	lw	$v0,0x14($a1)
/*  f0264ec:	8cb20004 */ 	lw	$s2,0x4($a1)
.L0f0264f0:
/*  f0264f0:	0c006a87 */ 	jal	modelGetNodeRwData
/*  f0264f4:	afa50110 */ 	sw	$a1,0x110($sp)
/*  f0264f8:	8c440004 */ 	lw	$a0,0x4($v0)
/*  f0264fc:	00408025 */ 	or	$s0,$v0,$zero
/*  f026500:	54800006 */ 	bnezl	$a0,.L0f02651c
/*  f026504:	8e430000 */ 	lw	$v1,0x0($s2)
/*  f026508:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f02650c:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f026510:	100000cc */ 	b	.L0f026844
/*  f026514:	8ca20014 */ 	lw	$v0,0x14($a1)
/*  f026518:	8e430000 */ 	lw	$v1,0x0($s2)
.L0f02651c:
/*  f02651c:	3c0100ff */ 	lui	$at,0xff
/*  f026520:	3421ffff */ 	ori	$at,$at,0xffff
/*  f026524:	14640005 */ 	bne	$v1,$a0,.L0f02653c
/*  f026528:	0080f025 */ 	or	$s8,$a0,$zero
/*  f02652c:	8e4e0008 */ 	lw	$t6,0x8($s2)
/*  f026530:	00617824 */ 	and	$t7,$v1,$at
/*  f026534:	10000001 */ 	b	.L0f02653c
/*  f026538:	01cff021 */ 	addu	$s8,$t6,$t7
.L0f02653c:
/*  f02653c:	8e420004 */ 	lw	$v0,0x4($s2)
/*  f026540:	3c0100ff */ 	lui	$at,0xff
/*  f026544:	50400008 */ 	beqzl	$v0,.L0f026568
/*  f026548:	afa00108 */ 	sw	$zero,0x108($sp)
/*  f02654c:	8e580008 */ 	lw	$t8,0x8($s2)
/*  f026550:	3421ffff */ 	ori	$at,$at,0xffff
/*  f026554:	0041c824 */ 	and	$t9,$v0,$at
/*  f026558:	03195021 */ 	addu	$t2,$t8,$t9
/*  f02655c:	10000002 */ 	b	.L0f026568
/*  f026560:	afaa0108 */ 	sw	$t2,0x108($sp)
/*  f026564:	afa00108 */ 	sw	$zero,0x108($sp)
.L0f026568:
/*  f026568:	83c20000 */ 	lb	$v0,0x0($s8)
/*  f02656c:	2401ffb8 */ 	addiu	$at,$zero,-72
/*  f026570:	8fab0108 */ 	lw	$t3,0x108($sp)
/*  f026574:	5441000b */ 	bnel	$v0,$at,.L0f0265a4
/*  f026578:	24010004 */ 	addiu	$at,$zero,0x4
/*  f02657c:	51600005 */ 	beqzl	$t3,.L0f026594
/*  f026580:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f026584:	0160f025 */ 	or	$s8,$t3,$zero
/*  f026588:	1000fff7 */ 	b	.L0f026568
/*  f02658c:	afa00108 */ 	sw	$zero,0x108($sp)
/*  f026590:	8fa50110 */ 	lw	$a1,0x110($sp)
.L0f026594:
/*  f026594:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f026598:	100000aa */ 	b	.L0f026844
/*  f02659c:	8ca20014 */ 	lw	$v0,0x14($a1)
/*  f0265a0:	24010004 */ 	addiu	$at,$zero,0x4
.L0f0265a4:
/*  f0265a4:	1441007c */ 	bne	$v0,$at,.L0f026798
/*  f0265a8:	8fb80100 */ 	lw	$t8,0x100($sp)
/*  f0265ac:	8fd50004 */ 	lw	$s5,0x4($s8)
/*  f0265b0:	93d60001 */ 	lbu	$s6,0x1($s8)
/*  f0265b4:	3c0100ff */ 	lui	$at,0xff
/*  f0265b8:	8e4e000c */ 	lw	$t6,0xc($s2)
/*  f0265bc:	3421ffff */ 	ori	$at,$at,0xffff
/*  f0265c0:	02a16824 */ 	and	$t5,$s5,$at
/*  f0265c4:	00167902 */ 	srl	$t7,$s6,0x4
/*  f0265c8:	01a0a825 */ 	or	$s5,$t5,$zero
/*  f0265cc:	25f60001 */ 	addiu	$s6,$t7,0x1
/*  f0265d0:	13000089 */ 	beqz	$t8,.L0f0267f8
/*  f0265d4:	01cd1021 */ 	addu	$v0,$t6,$t5
/*  f0265d8:	1ac00087 */ 	blez	$s6,.L0f0267f8
/*  f0265dc:	00009825 */ 	or	$s3,$zero,$zero
/*  f0265e0:	0000a025 */ 	or	$s4,$zero,$zero
/*  f0265e4:	00408825 */ 	or	$s1,$v0,$zero
.L0f0265e8:
/*  f0265e8:	c7aa00e8 */ 	lwc1	$f10,0xe8($sp)
/*  f0265ec:	c7b200ec */ 	lwc1	$f18,0xec($sp)
/*  f0265f0:	c7a600f0 */ 	lwc1	$f6,0xf0($sp)
/*  f0265f4:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f0265f8:	862b0000 */ 	lh	$t3,0x0($s1)
/*  f0265fc:	862e0002 */ 	lh	$t6,0x2($s1)
/*  f026600:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f026604:	440a8000 */ 	mfc1	$t2,$f16
/*  f026608:	86390004 */ 	lh	$t9,0x4($s1)
/*  f02660c:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f026610:	014b1021 */ 	addu	$v0,$t2,$t3
/*  f026614:	8faa0114 */ 	lw	$t2,0x114($sp)
/*  f026618:	440d2000 */ 	mfc1	$t5,$f4
/*  f02661c:	44184000 */ 	mfc1	$t8,$f8
/*  f026620:	8fab0118 */ 	lw	$t3,0x118($sp)
/*  f026624:	01ae1821 */ 	addu	$v1,$t5,$t6
/*  f026628:	144a0055 */ 	bne	$v0,$t2,.L0f026780
/*  f02662c:	03192021 */ 	addu	$a0,$t8,$t9
/*  f026630:	146b0053 */ 	bne	$v1,$t3,.L0f026780
/*  f026634:	8fac011c */ 	lw	$t4,0x11c($sp)
/*  f026638:	548c0052 */ 	bnel	$a0,$t4,.L0f026784
/*  f02663c:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f026640:	864e0010 */ 	lh	$t6,0x10($s2)
/*  f026644:	8e4d000c */ 	lw	$t5,0xc($s2)
/*  f026648:	8e030008 */ 	lw	$v1,0x8($s0)
/*  f02664c:	01d70019 */ 	multu	$t6,$s7
/*  f026650:	00007812 */ 	mflo	$t7
/*  f026654:	01af2021 */ 	addu	$a0,$t5,$t7
/*  f026658:	24840007 */ 	addiu	$a0,$a0,0x7
/*  f02665c:	34980007 */ 	ori	$t8,$a0,0x7
/*  f026660:	3b190007 */ 	xori	$t9,$t8,0x7
/*  f026664:	17230031 */ 	bne	$t9,$v1,.L0f02672c
/*  f026668:	03202025 */ 	or	$a0,$t9,$zero
/*  f02666c:	96440016 */ 	lhu	$a0,0x16($s2)
/*  f026670:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f026674:	00003025 */ 	or	$a2,$zero,$zero
/*  f026678:	0fc4a557 */ 	jal	func0f12955c
/*  f02667c:	00003825 */ 	or	$a3,$zero,$zero
/*  f026680:	50400020 */ 	beqzl	$v0,.L0f026704
/*  f026684:	864d0010 */ 	lh	$t5,0x10($s2)
/*  f026688:	964a0016 */ 	lhu	$t2,0x16($s2)
/*  f02668c:	00001825 */ 	or	$v1,$zero,$zero
/*  f026690:	00002025 */ 	or	$a0,$zero,$zero
/*  f026694:	5940000e */ 	blezl	$t2,.L0f0266d0
/*  f026698:	ae020008 */ 	sw	$v0,0x8($s0)
/*  f02669c:	00402825 */ 	or	$a1,$v0,$zero
/*  f0266a0:	8e0b0008 */ 	lw	$t3,0x8($s0)
.L0f0266a4:
/*  f0266a4:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f0266a8:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f0266ac:	01646021 */ 	addu	$t4,$t3,$a0
/*  f0266b0:	8d810000 */ 	lw	$at,0x0($t4)
/*  f0266b4:	24840004 */ 	addiu	$a0,$a0,0x4
/*  f0266b8:	aca1fffc */ 	sw	$at,-0x4($a1)
/*  f0266bc:	964f0016 */ 	lhu	$t7,0x16($s2)
/*  f0266c0:	006f082a */ 	slt	$at,$v1,$t7
/*  f0266c4:	5420fff7 */ 	bnezl	$at,.L0f0266a4
/*  f0266c8:	8e0b0008 */ 	lw	$t3,0x8($s0)
/*  f0266cc:	ae020008 */ 	sw	$v0,0x8($s0)
.L0f0266d0:
/*  f0266d0:	86590010 */ 	lh	$t9,0x10($s2)
/*  f0266d4:	8e58000c */ 	lw	$t8,0xc($s2)
/*  f0266d8:	00401825 */ 	or	$v1,$v0,$zero
/*  f0266dc:	00195080 */ 	sll	$t2,$t9,0x2
/*  f0266e0:	01595023 */ 	subu	$t2,$t2,$t9
/*  f0266e4:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f0266e8:	030a2021 */ 	addu	$a0,$t8,$t2
/*  f0266ec:	24840007 */ 	addiu	$a0,$a0,0x7
/*  f0266f0:	348b0007 */ 	ori	$t3,$a0,0x7
/*  f0266f4:	396e0007 */ 	xori	$t6,$t3,0x7
/*  f0266f8:	1000000c */ 	b	.L0f02672c
/*  f0266fc:	01c02025 */ 	or	$a0,$t6,$zero
/*  f026700:	864d0010 */ 	lh	$t5,0x10($s2)
.L0f026704:
/*  f026704:	8e4c000c */ 	lw	$t4,0xc($s2)
/*  f026708:	8e030008 */ 	lw	$v1,0x8($s0)
/*  f02670c:	000d7880 */ 	sll	$t7,$t5,0x2
/*  f026710:	01ed7823 */ 	subu	$t7,$t7,$t5
/*  f026714:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f026718:	018f2021 */ 	addu	$a0,$t4,$t7
/*  f02671c:	24840007 */ 	addiu	$a0,$a0,0x7
/*  f026720:	34990007 */ 	ori	$t9,$a0,0x7
/*  f026724:	3b380007 */ 	xori	$t8,$t9,0x7
/*  f026728:	03002025 */ 	or	$a0,$t8,$zero
.L0f02672c:
/*  f02672c:	10830014 */ 	beq	$a0,$v1,.L0f026780
/*  f026730:	8fb900c0 */ 	lw	$t9,0xc0($sp)
/*  f026734:	02b7001b */ 	divu	$zero,$s5,$s7
/*  f026738:	00005812 */ 	mflo	$t3
/*  f02673c:	8e0a0000 */ 	lw	$t2,0x0($s0)
/*  f026740:	000b7080 */ 	sll	$t6,$t3,0x2
/*  f026744:	01cb7023 */ 	subu	$t6,$t6,$t3
/*  f026748:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f02674c:	014e6821 */ 	addu	$t5,$t2,$t6
/*  f026750:	01b46021 */ 	addu	$t4,$t5,$s4
/*  f026754:	91820007 */ 	lbu	$v0,0x7($t4)
/*  f026758:	8fb800cc */ 	lw	$t8,0xcc($sp)
/*  f02675c:	00792021 */ 	addu	$a0,$v1,$t9
/*  f026760:	00027883 */ 	sra	$t7,$v0,0x2
/*  f026764:	000f5880 */ 	sll	$t3,$t7,0x2
/*  f026768:	008b5021 */ 	addu	$t2,$a0,$t3
/*  f02676c:	01e01025 */ 	or	$v0,$t7,$zero
/*  f026770:	16e00002 */ 	bnez	$s7,.L0f02677c
/*  f026774:	00000000 */ 	nop
/*  f026778:	0007000d */ 	break	0x7
.L0f02677c:
/*  f02677c:	a1580003 */ 	sb	$t8,0x3($t2)
.L0f026780:
/*  f026780:	26730001 */ 	addiu	$s3,$s3,0x1
.L0f026784:
/*  f026784:	2694000c */ 	addiu	$s4,$s4,0xc
/*  f026788:	1676ff97 */ 	bne	$s3,$s6,.L0f0265e8
/*  f02678c:	2631000c */ 	addiu	$s1,$s1,0xc
/*  f026790:	1000ff75 */ 	b	.L0f026568
/*  f026794:	27de0008 */ 	addiu	$s8,$s8,0x8
.L0f026798:
/*  f026798:	24010001 */ 	addiu	$at,$zero,0x1
/*  f02679c:	1441000e */ 	bne	$v0,$at,.L0f0267d8
/*  f0267a0:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f0267a4:	8fc20004 */ 	lw	$v0,0x4($s8)
/*  f0267a8:	3c0100ff */ 	lui	$at,0xff
/*  f0267ac:	3421ffff */ 	ori	$at,$at,0xffff
/*  f0267b0:	00417024 */ 	and	$t6,$v0,$at
/*  f0267b4:	0c00698d */ 	jal	func0001a634
/*  f0267b8:	000e2982 */ 	srl	$a1,$t6,0x6
/*  f0267bc:	afa20100 */ 	sw	$v0,0x100($sp)
/*  f0267c0:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f0267c4:	00402825 */ 	or	$a1,$v0,$zero
/*  f0267c8:	0c006b57 */ 	jal	modelNodeGetModelRelativePosition
/*  f0267cc:	27a600e8 */ 	addiu	$a2,$sp,0xe8
/*  f0267d0:	1000ff65 */ 	b	.L0f026568
/*  f0267d4:	27de0008 */ 	addiu	$s8,$s8,0x8
.L0f0267d8:
/*  f0267d8:	24010007 */ 	addiu	$at,$zero,0x7
/*  f0267dc:	14410006 */ 	bne	$v0,$at,.L0f0267f8
/*  f0267e0:	00000000 */ 	nop
/*  f0267e4:	8fcd0004 */ 	lw	$t5,0x4($s8)
/*  f0267e8:	3c0100ff */ 	lui	$at,0xff
/*  f0267ec:	3421ffff */ 	ori	$at,$at,0xffff
/*  f0267f0:	01a16024 */ 	and	$t4,$t5,$at
/*  f0267f4:	afac00c0 */ 	sw	$t4,0xc0($sp)
.L0f0267f8:
/*  f0267f8:	1000ff5b */ 	b	.L0f026568
/*  f0267fc:	27de0008 */ 	addiu	$s8,$s8,0x8
.L0f026800:
/*  f026800:	0c0071e1 */ 	jal	func0001c784
/*  f026804:	afa50110 */ 	sw	$a1,0x110($sp)
/*  f026808:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f02680c:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f026810:	1000000c */ 	b	.L0f026844
/*  f026814:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f026818:
/*  f026818:	0c0071f4 */ 	jal	func0001c7d0
/*  f02681c:	afa50110 */ 	sw	$a1,0x110($sp)
/*  f026820:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f026824:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f026828:	10000006 */ 	b	.L0f026844
/*  f02682c:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f026830:
/*  f026830:	0c007207 */ 	jal	modelAttachHead
/*  f026834:	afa50110 */ 	sw	$a1,0x110($sp)
/*  f026838:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f02683c:	8fa40128 */ 	lw	$a0,0x128($sp)
/*  f026840:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f026844:
/*  f026844:	10400003 */ 	beqz	$v0,.L0f026854
/*  f026848:	00000000 */ 	nop
/*  f02684c:	1000000d */ 	b	.L0f026884
/*  f026850:	00402825 */ 	or	$a1,$v0,$zero
.L0f026854:
/*  f026854:	10a0000b */ 	beqz	$a1,.L0f026884
/*  f026858:	00000000 */ 	nop
.L0f02685c:
/*  f02685c:	50a00007 */ 	beqzl	$a1,.L0f02687c
/*  f026860:	8ca50008 */ 	lw	$a1,0x8($a1)
/*  f026864:	8ca2000c */ 	lw	$v0,0xc($a1)
/*  f026868:	50400004 */ 	beqzl	$v0,.L0f02687c
/*  f02686c:	8ca50008 */ 	lw	$a1,0x8($a1)
/*  f026870:	10000004 */ 	b	.L0f026884
/*  f026874:	00402825 */ 	or	$a1,$v0,$zero
/*  f026878:	8ca50008 */ 	lw	$a1,0x8($a1)
.L0f02687c:
/*  f02687c:	14a0fff7 */ 	bnez	$a1,.L0f02685c
/*  f026880:	00000000 */ 	nop
.L0f026884:
/*  f026884:	54a0ff0d */ 	bnezl	$a1,.L0f0264bc
/*  f026888:	94a20000 */ 	lhu	$v0,0x0($a1)
.L0f02688c:
/*  f02688c:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f026890:
/*  f026890:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f026894:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f026898:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f02689c:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f0268a0:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f0268a4:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f0268a8:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f0268ac:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f0268b0:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f0268b4:	03e00008 */ 	jr	$ra
/*  f0268b8:	27bd0128 */ 	addiu	$sp,$sp,0x128
);

GLOBAL_ASM(
glabel func0f0268bc
.late_rodata
glabel var7f1a8904
.word func0f0268bc+0x778 # f027034
glabel var7f1a8908
.word func0f0268bc+0x7bc # f027078
glabel var7f1a890c
.word func0f0268bc+0x424 # f026ce0
glabel var7f1a8910
.word func0f0268bc+0x7bc # f027078
glabel var7f1a8914
.word func0f0268bc+0x7bc # f027078
glabel var7f1a8918
.word func0f0268bc+0x7bc # f027078
glabel var7f1a891c
.word func0f0268bc+0x7bc # f027078
glabel var7f1a8920
.word func0f0268bc+0x7bc # f027078
glabel var7f1a8924
.word func0f0268bc+0x7bc # f027078
glabel var7f1a8928
.word func0f0268bc+0x7bc # f027078
glabel var7f1a892c
.word func0f0268bc+0x790 # f02704c
glabel var7f1a8930
.word func0f0268bc+0x7bc # f027078
glabel var7f1a8934
.word func0f0268bc+0x7bc # f027078
glabel var7f1a8938
.word func0f0268bc+0x7bc # f027078
glabel var7f1a893c
.word func0f0268bc+0x7bc # f027078
glabel var7f1a8940
.word func0f0268bc+0x7a8 # f027064
glabel var7f1a8944
.word func0f0268bc+0x484 # f026d40
.text
/*  f0268bc:	27bdfee0 */ 	addiu	$sp,$sp,-288
/*  f0268c0:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f0268c4:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f0268c8:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f0268cc:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f0268d0:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f0268d4:	3c107fff */ 	lui	$s0,0x7fff
/*  f0268d8:	00e09025 */ 	or	$s2,$a3,$zero
/*  f0268dc:	00c0a025 */ 	or	$s4,$a2,$zero
/*  f0268e0:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f0268e4:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f0268e8:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f0268ec:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f0268f0:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f0268f4:	afa40120 */ 	sw	$a0,0x120($sp)
/*  f0268f8:	afa50124 */ 	sw	$a1,0x124($sp)
/*  f0268fc:	00008825 */ 	or	$s1,$zero,$zero
/*  f026900:	3610ffff */ 	ori	$s0,$s0,0xffff
/*  f026904:	0c004b70 */ 	jal	random
/*  f026908:	afa000ec */ 	sw	$zero,0xec($sp)
/*  f02690c:	24010032 */ 	addiu	$at,$zero,0x32
/*  f026910:	0041001b */ 	divu	$zero,$v0,$at
/*  f026914:	00007010 */ 	mfhi	$t6
/*  f026918:	25cf0014 */ 	addiu	$t7,$t6,0x14
/*  f02691c:	afaf00b8 */ 	sw	$t7,0xb8($sp)
/*  f026920:	afa000ac */ 	sw	$zero,0xac($sp)
/*  f026924:	0c0069d0 */ 	jal	func0001a740
/*  f026928:	02802025 */ 	or	$a0,$s4,$zero
/*  f02692c:	8fa40120 */ 	lw	$a0,0x120($sp)
/*  f026930:	00402825 */ 	or	$a1,$v0,$zero
/*  f026934:	0c006b57 */ 	jal	modelNodeGetModelRelativePosition
/*  f026938:	27a600e0 */ 	addiu	$a2,$sp,0xe0
/*  f02693c:	c6440000 */ 	lwc1	$f4,0x0($s2)
/*  f026940:	c7a600e0 */ 	lwc1	$f6,0xe0($sp)
/*  f026944:	c7b000e4 */ 	lwc1	$f16,0xe4($sp)
/*  f026948:	02802825 */ 	or	$a1,$s4,$zero
/*  f02694c:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f026950:	c7a600e8 */ 	lwc1	$f6,0xe8($sp)
/*  f026954:	24170017 */ 	addiu	$s7,$zero,0x17
/*  f026958:	24160012 */ 	addiu	$s6,$zero,0x12
/*  f02695c:	e7a800c8 */ 	swc1	$f8,0xc8($sp)
/*  f026960:	c64a0004 */ 	lwc1	$f10,0x4($s2)
/*  f026964:	24150008 */ 	addiu	$s5,$zero,0x8
/*  f026968:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f02696c:	e7b200cc */ 	swc1	$f18,0xcc($sp)
/*  f026970:	c6440008 */ 	lwc1	$f4,0x8($s2)
/*  f026974:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f026978:	128000c4 */ 	beqz	$s4,.L0f026c8c
/*  f02697c:	e7a800d0 */ 	swc1	$f8,0xd0($sp)
/*  f026980:	94b30000 */ 	lhu	$s3,0x0($a1)
.L0f026984:
/*  f026984:	8fa40120 */ 	lw	$a0,0x120($sp)
/*  f026988:	327800ff */ 	andi	$t8,$s3,0xff
/*  f02698c:	13150097 */ 	beq	$t8,$s5,.L0f026bec
/*  f026990:	03009825 */ 	or	$s3,$t8,$zero
/*  f026994:	1316009a */ 	beq	$t8,$s6,.L0f026c00
/*  f026998:	8fa40120 */ 	lw	$a0,0x120($sp)
/*  f02699c:	1317009d */ 	beq	$t8,$s7,.L0f026c14
/*  f0269a0:	8fa40120 */ 	lw	$a0,0x120($sp)
/*  f0269a4:	24010018 */ 	addiu	$at,$zero,0x18
/*  f0269a8:	13010003 */ 	beq	$t8,$at,.L0f0269b8
/*  f0269ac:	8fa40120 */ 	lw	$a0,0x120($sp)
/*  f0269b0:	1000009c */ 	b	.L0f026c24
/*  f0269b4:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f0269b8:
/*  f0269b8:	8cb20004 */ 	lw	$s2,0x4($a1)
/*  f0269bc:	0c006a87 */ 	jal	modelGetNodeRwData
/*  f0269c0:	afa500fc */ 	sw	$a1,0xfc($sp)
/*  f0269c4:	8c440004 */ 	lw	$a0,0x4($v0)
/*  f0269c8:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f0269cc:	54800004 */ 	bnezl	$a0,.L0f0269e0
/*  f0269d0:	8e430000 */ 	lw	$v1,0x0($s2)
/*  f0269d4:	10000093 */ 	b	.L0f026c24
/*  f0269d8:	8ca20014 */ 	lw	$v0,0x14($a1)
/*  f0269dc:	8e430000 */ 	lw	$v1,0x0($s2)
.L0f0269e0:
/*  f0269e0:	3c0100ff */ 	lui	$at,0xff
/*  f0269e4:	3421ffff */ 	ori	$at,$at,0xffff
/*  f0269e8:	14640005 */ 	bne	$v1,$a0,.L0f026a00
/*  f0269ec:	0080f025 */ 	or	$s8,$a0,$zero
/*  f0269f0:	8e4a0008 */ 	lw	$t2,0x8($s2)
/*  f0269f4:	00615824 */ 	and	$t3,$v1,$at
/*  f0269f8:	10000001 */ 	b	.L0f026a00
/*  f0269fc:	014bf021 */ 	addu	$s8,$t2,$t3
.L0f026a00:
/*  f026a00:	8e420004 */ 	lw	$v0,0x4($s2)
/*  f026a04:	3c0100ff */ 	lui	$at,0xff
/*  f026a08:	50400008 */ 	beqzl	$v0,.L0f026a2c
/*  f026a0c:	afa000f4 */ 	sw	$zero,0xf4($sp)
/*  f026a10:	8e4c0008 */ 	lw	$t4,0x8($s2)
/*  f026a14:	3421ffff */ 	ori	$at,$at,0xffff
/*  f026a18:	00416824 */ 	and	$t5,$v0,$at
/*  f026a1c:	018d7021 */ 	addu	$t6,$t4,$t5
/*  f026a20:	10000002 */ 	b	.L0f026a2c
/*  f026a24:	afae00f4 */ 	sw	$t6,0xf4($sp)
/*  f026a28:	afa000f4 */ 	sw	$zero,0xf4($sp)
.L0f026a2c:
/*  f026a2c:	83c20000 */ 	lb	$v0,0x0($s8)
/*  f026a30:	2401ffb8 */ 	addiu	$at,$zero,-72
/*  f026a34:	8faf00f4 */ 	lw	$t7,0xf4($sp)
/*  f026a38:	5441000a */ 	bnel	$v0,$at,.L0f026a64
/*  f026a3c:	24010004 */ 	addiu	$at,$zero,0x4
/*  f026a40:	51e00005 */ 	beqzl	$t7,.L0f026a58
/*  f026a44:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f026a48:	01e0f025 */ 	or	$s8,$t7,$zero
/*  f026a4c:	1000fff7 */ 	b	.L0f026a2c
/*  f026a50:	afa000f4 */ 	sw	$zero,0xf4($sp)
/*  f026a54:	8fa500fc */ 	lw	$a1,0xfc($sp)
.L0f026a58:
/*  f026a58:	10000072 */ 	b	.L0f026c24
/*  f026a5c:	8ca20014 */ 	lw	$v0,0x14($a1)
/*  f026a60:	24010004 */ 	addiu	$at,$zero,0x4
.L0f026a64:
/*  f026a64:	1441003e */ 	bne	$v0,$at,.L0f026b60
/*  f026a68:	8fac00ec */ 	lw	$t4,0xec($sp)
/*  f026a6c:	8fc20004 */ 	lw	$v0,0x4($s8)
/*  f026a70:	93c90001 */ 	lbu	$t1,0x1($s8)
/*  f026a74:	3c0100ff */ 	lui	$at,0xff
/*  f026a78:	8e4a000c */ 	lw	$t2,0xc($s2)
/*  f026a7c:	3421ffff */ 	ori	$at,$at,0xffff
/*  f026a80:	0041c824 */ 	and	$t9,$v0,$at
/*  f026a84:	00095902 */ 	srl	$t3,$t1,0x4
/*  f026a88:	25690001 */ 	addiu	$t1,$t3,0x1
/*  f026a8c:	11800055 */ 	beqz	$t4,.L0f026be4
/*  f026a90:	01591821 */ 	addu	$v1,$t2,$t9
/*  f026a94:	19200053 */ 	blez	$t1,.L0f026be4
/*  f026a98:	00003025 */ 	or	$a2,$zero,$zero
/*  f026a9c:	00601025 */ 	or	$v0,$v1,$zero
.L0f026aa0:
/*  f026aa0:	84470000 */ 	lh	$a3,0x0($v0)
/*  f026aa4:	8fad00bc */ 	lw	$t5,0xbc($sp)
/*  f026aa8:	8fae00c0 */ 	lw	$t6,0xc0($sp)
/*  f026aac:	844f0002 */ 	lh	$t7,0x2($v0)
/*  f026ab0:	01a71823 */ 	subu	$v1,$t5,$a3
/*  f026ab4:	00630019 */ 	multu	$v1,$v1
/*  f026ab8:	01cf2023 */ 	subu	$a0,$t6,$t7
/*  f026abc:	8fb800c4 */ 	lw	$t8,0xc4($sp)
/*  f026ac0:	84590004 */ 	lh	$t9,0x4($v0)
/*  f026ac4:	24c60001 */ 	addiu	$a2,$a2,0x1
/*  f026ac8:	c7aa00d4 */ 	lwc1	$f10,0xd4($sp)
/*  f026acc:	03192823 */ 	subu	$a1,$t8,$t9
/*  f026ad0:	00005012 */ 	mflo	$t2
/*  f026ad4:	00000000 */ 	nop
/*  f026ad8:	00000000 */ 	nop
/*  f026adc:	00840019 */ 	multu	$a0,$a0
/*  f026ae0:	00005812 */ 	mflo	$t3
/*  f026ae4:	014b6021 */ 	addu	$t4,$t2,$t3
/*  f026ae8:	00000000 */ 	nop
/*  f026aec:	00a50019 */ 	multu	$a1,$a1
/*  f026af0:	00006812 */ 	mflo	$t5
/*  f026af4:	018d4021 */ 	addu	$t0,$t4,$t5
/*  f026af8:	0110082a */ 	slt	$at,$t0,$s0
/*  f026afc:	10200014 */ 	beqz	$at,.L0f026b50
/*  f026b00:	00000000 */ 	nop
/*  f026b04:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f026b08:	c7b200d8 */ 	lwc1	$f18,0xd8($sp)
/*  f026b0c:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f026b10:	01008025 */ 	or	$s0,$t0,$zero
/*  f026b14:	440f8000 */ 	mfc1	$t7,$f16
/*  f026b18:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f026b1c:	8fb100fc */ 	lw	$s1,0xfc($sp)
/*  f026b20:	01e7c021 */ 	addu	$t8,$t7,$a3
/*  f026b24:	afb80100 */ 	sw	$t8,0x100($sp)
/*  f026b28:	844b0002 */ 	lh	$t3,0x2($v0)
/*  f026b2c:	440a2000 */ 	mfc1	$t2,$f4
/*  f026b30:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f026b34:	014b6021 */ 	addu	$t4,$t2,$t3
/*  f026b38:	afac0104 */ 	sw	$t4,0x104($sp)
/*  f026b3c:	844f0004 */ 	lh	$t7,0x4($v0)
/*  f026b40:	440e4000 */ 	mfc1	$t6,$f8
/*  f026b44:	00000000 */ 	nop
/*  f026b48:	01cfc021 */ 	addu	$t8,$t6,$t7
/*  f026b4c:	afb80108 */ 	sw	$t8,0x108($sp)
.L0f026b50:
/*  f026b50:	14c9ffd3 */ 	bne	$a2,$t1,.L0f026aa0
/*  f026b54:	2442000c */ 	addiu	$v0,$v0,0xc
/*  f026b58:	1000ffb4 */ 	b	.L0f026a2c
/*  f026b5c:	27de0008 */ 	addiu	$s8,$s8,0x8
.L0f026b60:
/*  f026b60:	24010001 */ 	addiu	$at,$zero,0x1
/*  f026b64:	1441001f */ 	bne	$v0,$at,.L0f026be4
/*  f026b68:	8fa40120 */ 	lw	$a0,0x120($sp)
/*  f026b6c:	8fc20004 */ 	lw	$v0,0x4($s8)
/*  f026b70:	3c0100ff */ 	lui	$at,0xff
/*  f026b74:	3421ffff */ 	ori	$at,$at,0xffff
/*  f026b78:	0041c824 */ 	and	$t9,$v0,$at
/*  f026b7c:	0c00698d */ 	jal	func0001a634
/*  f026b80:	00192982 */ 	srl	$a1,$t9,0x6
/*  f026b84:	afa200ec */ 	sw	$v0,0xec($sp)
/*  f026b88:	8fa40120 */ 	lw	$a0,0x120($sp)
/*  f026b8c:	00402825 */ 	or	$a1,$v0,$zero
/*  f026b90:	0c006b57 */ 	jal	modelNodeGetModelRelativePosition
/*  f026b94:	27a600d4 */ 	addiu	$a2,$sp,0xd4
/*  f026b98:	c7aa00d4 */ 	lwc1	$f10,0xd4($sp)
/*  f026b9c:	c7b000c8 */ 	lwc1	$f16,0xc8($sp)
/*  f026ba0:	c7a600d8 */ 	lwc1	$f6,0xd8($sp)
/*  f026ba4:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f026ba8:	46105480 */ 	add.s	$f18,$f10,$f16
/*  f026bac:	46083280 */ 	add.s	$f10,$f6,$f8
/*  f026bb0:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f026bb4:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
/*  f026bb8:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f026bbc:	440b2000 */ 	mfc1	$t3,$f4
/*  f026bc0:	c7a400d0 */ 	lwc1	$f4,0xd0($sp)
/*  f026bc4:	440d8000 */ 	mfc1	$t5,$f16
/*  f026bc8:	46049180 */ 	add.s	$f6,$f18,$f4
/*  f026bcc:	afab00bc */ 	sw	$t3,0xbc($sp)
/*  f026bd0:	afad00c0 */ 	sw	$t5,0xc0($sp)
/*  f026bd4:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f026bd8:	440f4000 */ 	mfc1	$t7,$f8
/*  f026bdc:	00000000 */ 	nop
/*  f026be0:	afaf00c4 */ 	sw	$t7,0xc4($sp)
.L0f026be4:
/*  f026be4:	1000ff91 */ 	b	.L0f026a2c
/*  f026be8:	27de0008 */ 	addiu	$s8,$s8,0x8
.L0f026bec:
/*  f026bec:	0c0071e1 */ 	jal	func0001c784
/*  f026bf0:	afa500fc */ 	sw	$a1,0xfc($sp)
/*  f026bf4:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f026bf8:	1000000a */ 	b	.L0f026c24
/*  f026bfc:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f026c00:
/*  f026c00:	0c0071f4 */ 	jal	func0001c7d0
/*  f026c04:	afa500fc */ 	sw	$a1,0xfc($sp)
/*  f026c08:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f026c0c:	10000005 */ 	b	.L0f026c24
/*  f026c10:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f026c14:
/*  f026c14:	0c007207 */ 	jal	modelAttachHead
/*  f026c18:	afa500fc */ 	sw	$a1,0xfc($sp)
/*  f026c1c:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f026c20:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f026c24:
/*  f026c24:	10400009 */ 	beqz	$v0,.L0f026c4c
/*  f026c28:	00000000 */ 	nop
/*  f026c2c:	10b40005 */ 	beq	$a1,$s4,.L0f026c44
/*  f026c30:	2401000a */ 	addiu	$at,$zero,0xa
/*  f026c34:	12610005 */ 	beq	$s3,$at,.L0f026c4c
/*  f026c38:	24010011 */ 	addiu	$at,$zero,0x11
/*  f026c3c:	12610003 */ 	beq	$s3,$at,.L0f026c4c
/*  f026c40:	00000000 */ 	nop
.L0f026c44:
/*  f026c44:	1000000f */ 	b	.L0f026c84
/*  f026c48:	00402825 */ 	or	$a1,$v0,$zero
.L0f026c4c:
/*  f026c4c:	10a0000d */ 	beqz	$a1,.L0f026c84
/*  f026c50:	00000000 */ 	nop
.L0f026c54:
/*  f026c54:	54b40004 */ 	bnel	$a1,$s4,.L0f026c68
/*  f026c58:	8ca2000c */ 	lw	$v0,0xc($a1)
/*  f026c5c:	10000009 */ 	b	.L0f026c84
/*  f026c60:	00002825 */ 	or	$a1,$zero,$zero
/*  f026c64:	8ca2000c */ 	lw	$v0,0xc($a1)
.L0f026c68:
/*  f026c68:	50400004 */ 	beqzl	$v0,.L0f026c7c
/*  f026c6c:	8ca50008 */ 	lw	$a1,0x8($a1)
/*  f026c70:	10000004 */ 	b	.L0f026c84
/*  f026c74:	00402825 */ 	or	$a1,$v0,$zero
/*  f026c78:	8ca50008 */ 	lw	$a1,0x8($a1)
.L0f026c7c:
/*  f026c7c:	14a0fff5 */ 	bnez	$a1,.L0f026c54
/*  f026c80:	00000000 */ 	nop
.L0f026c84:
/*  f026c84:	54a0ff3f */ 	bnezl	$a1,.L0f026984
/*  f026c88:	94b30000 */ 	lhu	$s3,0x0($a1)
.L0f026c8c:
/*  f026c8c:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f026c90:	1220010c */ 	beqz	$s1,.L0f0270c4
/*  f026c94:	afab0118 */ 	sw	$t3,0x118($sp)
/*  f026c98:	8fa70120 */ 	lw	$a3,0x120($sp)
/*  f026c9c:	2417000c */ 	addiu	$s7,$zero,0xc
/*  f026ca0:	8cec0008 */ 	lw	$t4,0x8($a3)
/*  f026ca4:	8d850000 */ 	lw	$a1,0x0($t4)
/*  f026ca8:	50a00107 */ 	beqzl	$a1,.L0f0270c8
/*  f026cac:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f026cb0:	94b30000 */ 	lhu	$s3,0x0($a1)
.L0f026cb4:
/*  f026cb4:	afa500fc */ 	sw	$a1,0xfc($sp)
/*  f026cb8:	326d00ff */ 	andi	$t5,$s3,0xff
/*  f026cbc:	25aefff8 */ 	addiu	$t6,$t5,-8
/*  f026cc0:	2dc10011 */ 	sltiu	$at,$t6,0x11
/*  f026cc4:	102000ec */ 	beqz	$at,.L0f027078
/*  f026cc8:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f026ccc:	3c017f1b */ 	lui	$at,%hi(var7f1a8904)
/*  f026cd0:	002e0821 */ 	addu	$at,$at,$t6
/*  f026cd4:	8c2e8904 */ 	lw	$t6,%lo(var7f1a8904)($at)
/*  f026cd8:	01c00008 */ 	jr	$t6
/*  f026cdc:	00000000 */ 	nop
/*  f026ce0:	3c04800a */ 	lui	$a0,%hi(g_Vars+0x2c0)
/*  f026ce4:	8c84a280 */ 	lw	$a0,%lo(g_Vars+0x2c0)($a0)
/*  f026ce8:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f026cec:	50800012 */ 	beqzl	$a0,.L0f026d38
/*  f026cf0:	afaa0118 */ 	sw	$t2,0x118($sp)
/*  f026cf4:	1880000d */ 	blez	$a0,.L0f026d2c
/*  f026cf8:	00003025 */ 	or	$a2,$zero,$zero
/*  f026cfc:	3c0f800a */ 	lui	$t7,%hi(g_Vars)
/*  f026d00:	25e29fc0 */ 	addiu	$v0,$t7,%lo(g_Vars)
/*  f026d04:	0004c080 */ 	sll	$t8,$a0,0x2
/*  f026d08:	03021821 */ 	addu	$v1,$t8,$v0
/*  f026d0c:	8c5902c4 */ 	lw	$t9,0x2c4($v0)
.L0f026d10:
/*  f026d10:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f026d14:	0043082b */ 	sltu	$at,$v0,$v1
/*  f026d18:	14b90002 */ 	bne	$a1,$t9,.L0f026d24
/*  f026d1c:	00000000 */ 	nop
/*  f026d20:	24060001 */ 	addiu	$a2,$zero,0x1
.L0f026d24:
/*  f026d24:	5420fffa */ 	bnezl	$at,.L0f026d10
/*  f026d28:	8c5902c4 */ 	lw	$t9,0x2c4($v0)
.L0f026d2c:
/*  f026d2c:	10000002 */ 	b	.L0f026d38
/*  f026d30:	afa60118 */ 	sw	$a2,0x118($sp)
/*  f026d34:	afaa0118 */ 	sw	$t2,0x118($sp)
.L0f026d38:
/*  f026d38:	100000d0 */ 	b	.L0f02707c
/*  f026d3c:	8ca20014 */ 	lw	$v0,0x14($a1)
/*  f026d40:	8fab0118 */ 	lw	$t3,0x118($sp)
/*  f026d44:	afa500fc */ 	sw	$a1,0xfc($sp)
/*  f026d48:	00e02025 */ 	or	$a0,$a3,$zero
/*  f026d4c:	1160002a */ 	beqz	$t3,.L0f026df8
/*  f026d50:	00000000 */ 	nop
/*  f026d54:	8cb20004 */ 	lw	$s2,0x4($a1)
/*  f026d58:	0c006a87 */ 	jal	modelGetNodeRwData
/*  f026d5c:	afa500fc */ 	sw	$a1,0xfc($sp)
/*  f026d60:	8c440004 */ 	lw	$a0,0x4($v0)
/*  f026d64:	00408025 */ 	or	$s0,$v0,$zero
/*  f026d68:	54800005 */ 	bnezl	$a0,.L0f026d80
/*  f026d6c:	8e430000 */ 	lw	$v1,0x0($s2)
/*  f026d70:	8fa70120 */ 	lw	$a3,0x120($sp)
/*  f026d74:	100000c0 */ 	b	.L0f027078
/*  f026d78:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f026d7c:	8e430000 */ 	lw	$v1,0x0($s2)
.L0f026d80:
/*  f026d80:	3c0600ff */ 	lui	$a2,0xff
/*  f026d84:	34c6ffff */ 	ori	$a2,$a2,0xffff
/*  f026d88:	14640007 */ 	bne	$v1,$a0,.L0f026da8
/*  f026d8c:	0080f025 */ 	or	$s8,$a0,$zero
/*  f026d90:	3c0600ff */ 	lui	$a2,0xff
/*  f026d94:	8e4c0008 */ 	lw	$t4,0x8($s2)
/*  f026d98:	34c6ffff */ 	ori	$a2,$a2,0xffff
/*  f026d9c:	00666824 */ 	and	$t5,$v1,$a2
/*  f026da0:	10000001 */ 	b	.L0f026da8
/*  f026da4:	018df021 */ 	addu	$s8,$t4,$t5
.L0f026da8:
/*  f026da8:	8e420004 */ 	lw	$v0,0x4($s2)
/*  f026dac:	50400007 */ 	beqzl	$v0,.L0f026dcc
/*  f026db0:	afa000f4 */ 	sw	$zero,0xf4($sp)
/*  f026db4:	8e4e0008 */ 	lw	$t6,0x8($s2)
/*  f026db8:	0046c024 */ 	and	$t8,$v0,$a2
/*  f026dbc:	01d87821 */ 	addu	$t7,$t6,$t8
/*  f026dc0:	10000002 */ 	b	.L0f026dcc
/*  f026dc4:	afaf00f4 */ 	sw	$t7,0xf4($sp)
/*  f026dc8:	afa000f4 */ 	sw	$zero,0xf4($sp)
.L0f026dcc:
/*  f026dcc:	83c20000 */ 	lb	$v0,0x0($s8)
/*  f026dd0:	2401ffb8 */ 	addiu	$at,$zero,-72
/*  f026dd4:	8fb900f4 */ 	lw	$t9,0xf4($sp)
/*  f026dd8:	5441000a */ 	bnel	$v0,$at,.L0f026e04
/*  f026ddc:	24010004 */ 	addiu	$at,$zero,0x4
/*  f026de0:	53200005 */ 	beqzl	$t9,.L0f026df8
/*  f026de4:	8fa70120 */ 	lw	$a3,0x120($sp)
/*  f026de8:	0320f025 */ 	or	$s8,$t9,$zero
/*  f026dec:	1000fff7 */ 	b	.L0f026dcc
/*  f026df0:	afa000f4 */ 	sw	$zero,0xf4($sp)
/*  f026df4:	8fa70120 */ 	lw	$a3,0x120($sp)
.L0f026df8:
/*  f026df8:	1000009f */ 	b	.L0f027078
/*  f026dfc:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f026e00:	24010004 */ 	addiu	$at,$zero,0x4
.L0f026e04:
/*  f026e04:	14410072 */ 	bne	$v0,$at,.L0f026fd0
/*  f026e08:	8fad00ec */ 	lw	$t5,0xec($sp)
/*  f026e0c:	8fca0004 */ 	lw	$t2,0x4($s8)
/*  f026e10:	93d60001 */ 	lbu	$s6,0x1($s8)
/*  f026e14:	8e4b000c */ 	lw	$t3,0xc($s2)
/*  f026e18:	0146a824 */ 	and	$s5,$t2,$a2
/*  f026e1c:	00166102 */ 	srl	$t4,$s6,0x4
/*  f026e20:	25960001 */ 	addiu	$s6,$t4,0x1
/*  f026e24:	11a00081 */ 	beqz	$t5,.L0f02702c
/*  f026e28:	01751021 */ 	addu	$v0,$t3,$s5
/*  f026e2c:	1ac0007f */ 	blez	$s6,.L0f02702c
/*  f026e30:	00009825 */ 	or	$s3,$zero,$zero
/*  f026e34:	0000a025 */ 	or	$s4,$zero,$zero
/*  f026e38:	00408825 */ 	or	$s1,$v0,$zero
.L0f026e3c:
/*  f026e3c:	c7aa00d4 */ 	lwc1	$f10,0xd4($sp)
/*  f026e40:	862f0000 */ 	lh	$t7,0x0($s1)
/*  f026e44:	8fb90100 */ 	lw	$t9,0x100($sp)
/*  f026e48:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f026e4c:	c7b200d8 */ 	lwc1	$f18,0xd8($sp)
/*  f026e50:	44188000 */ 	mfc1	$t8,$f16
/*  f026e54:	00000000 */ 	nop
/*  f026e58:	030f1021 */ 	addu	$v0,$t8,$t7
/*  f026e5c:	54590055 */ 	bnel	$v0,$t9,.L0f026fb4
/*  f026e60:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f026e64:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f026e68:	862c0002 */ 	lh	$t4,0x2($s1)
/*  f026e6c:	8fad0104 */ 	lw	$t5,0x104($sp)
/*  f026e70:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f026e74:	440b2000 */ 	mfc1	$t3,$f4
/*  f026e78:	00000000 */ 	nop
/*  f026e7c:	016c1021 */ 	addu	$v0,$t3,$t4
/*  f026e80:	544d004c */ 	bnel	$v0,$t5,.L0f026fb4
/*  f026e84:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f026e88:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f026e8c:	862f0004 */ 	lh	$t7,0x4($s1)
/*  f026e90:	8fb90108 */ 	lw	$t9,0x108($sp)
/*  f026e94:	44184000 */ 	mfc1	$t8,$f8
/*  f026e98:	00000000 */ 	nop
/*  f026e9c:	030f1021 */ 	addu	$v0,$t8,$t7
/*  f026ea0:	54590044 */ 	bnel	$v0,$t9,.L0f026fb4
/*  f026ea4:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f026ea8:	864b0010 */ 	lh	$t3,0x10($s2)
/*  f026eac:	8e4a000c */ 	lw	$t2,0xc($s2)
/*  f026eb0:	8e190008 */ 	lw	$t9,0x8($s0)
/*  f026eb4:	01770019 */ 	multu	$t3,$s7
/*  f026eb8:	00006012 */ 	mflo	$t4
/*  f026ebc:	014c6821 */ 	addu	$t5,$t2,$t4
/*  f026ec0:	25ae0007 */ 	addiu	$t6,$t5,0x7
/*  f026ec4:	35d80007 */ 	ori	$t8,$t6,0x7
/*  f026ec8:	3b0f0007 */ 	xori	$t7,$t8,0x7
/*  f026ecc:	55f9001b */ 	bnel	$t7,$t9,.L0f026f3c
/*  f026ed0:	86590010 */ 	lh	$t9,0x10($s2)
/*  f026ed4:	96440016 */ 	lhu	$a0,0x16($s2)
/*  f026ed8:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f026edc:	00003025 */ 	or	$a2,$zero,$zero
/*  f026ee0:	0fc4a557 */ 	jal	func0f12955c
/*  f026ee4:	00003825 */ 	or	$a3,$zero,$zero
/*  f026ee8:	50400014 */ 	beqzl	$v0,.L0f026f3c
/*  f026eec:	86590010 */ 	lh	$t9,0x10($s2)
/*  f026ef0:	964b0016 */ 	lhu	$t3,0x16($s2)
/*  f026ef4:	00001825 */ 	or	$v1,$zero,$zero
/*  f026ef8:	00002025 */ 	or	$a0,$zero,$zero
/*  f026efc:	5960000e */ 	blezl	$t3,.L0f026f38
/*  f026f00:	ae020008 */ 	sw	$v0,0x8($s0)
/*  f026f04:	00402825 */ 	or	$a1,$v0,$zero
/*  f026f08:	8e0a0008 */ 	lw	$t2,0x8($s0)
.L0f026f0c:
/*  f026f0c:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f026f10:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f026f14:	01446021 */ 	addu	$t4,$t2,$a0
/*  f026f18:	8d810000 */ 	lw	$at,0x0($t4)
/*  f026f1c:	24840004 */ 	addiu	$a0,$a0,4
/*  f026f20:	aca1fffc */ 	sw	$at,-0x4($a1)
/*  f026f24:	96580016 */ 	lhu	$t8,0x16($s2)
/*  f026f28:	0078082a */ 	slt	$at,$v1,$t8
/*  f026f2c:	5420fff7 */ 	bnezl	$at,.L0f026f0c
/*  f026f30:	8e0a0008 */ 	lw	$t2,0x8($s0)
/*  f026f34:	ae020008 */ 	sw	$v0,0x8($s0)
.L0f026f38:
/*  f026f38:	86590010 */ 	lh	$t9,0x10($s2)
.L0f026f3c:
/*  f026f3c:	8e4f000c */ 	lw	$t7,0xc($s2)
/*  f026f40:	8e040008 */ 	lw	$a0,0x8($s0)
/*  f026f44:	03370019 */ 	multu	$t9,$s7
/*  f026f48:	00005812 */ 	mflo	$t3
/*  f026f4c:	01eb5021 */ 	addu	$t2,$t7,$t3
/*  f026f50:	254d0007 */ 	addiu	$t5,$t2,0x7
/*  f026f54:	35ac0007 */ 	ori	$t4,$t5,0x7
/*  f026f58:	398e0007 */ 	xori	$t6,$t4,0x7
/*  f026f5c:	11c40014 */ 	beq	$t6,$a0,.L0f026fb0
/*  f026f60:	8fac00ac */ 	lw	$t4,0xac($sp)
/*  f026f64:	02b7001b */ 	divu	$zero,$s5,$s7
/*  f026f68:	0000c812 */ 	mflo	$t9
/*  f026f6c:	8e180000 */ 	lw	$t8,0x0($s0)
/*  f026f70:	00197880 */ 	sll	$t7,$t9,0x2
/*  f026f74:	01f97823 */ 	subu	$t7,$t7,$t9
/*  f026f78:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f026f7c:	030f5821 */ 	addu	$t3,$t8,$t7
/*  f026f80:	01745021 */ 	addu	$t2,$t3,$s4
/*  f026f84:	91420007 */ 	lbu	$v0,0x7($t2)
/*  f026f88:	8fae00b8 */ 	lw	$t6,0xb8($sp)
/*  f026f8c:	008c1821 */ 	addu	$v1,$a0,$t4
/*  f026f90:	00026883 */ 	sra	$t5,$v0,0x2
/*  f026f94:	000dc880 */ 	sll	$t9,$t5,0x2
/*  f026f98:	0079c021 */ 	addu	$t8,$v1,$t9
/*  f026f9c:	01a01025 */ 	or	$v0,$t5,$zero
/*  f026fa0:	16e00002 */ 	bnez	$s7,.L0f026fac
/*  f026fa4:	00000000 */ 	nop
/*  f026fa8:	0007000d */ 	break	0x7
.L0f026fac:
/*  f026fac:	a30e0003 */ 	sb	$t6,0x3($t8)
.L0f026fb0:
/*  f026fb0:	26730001 */ 	addiu	$s3,$s3,0x1
.L0f026fb4:
/*  f026fb4:	2694000c */ 	addiu	$s4,$s4,0xc
/*  f026fb8:	1676ffa0 */ 	bne	$s3,$s6,.L0f026e3c
/*  f026fbc:	2631000c */ 	addiu	$s1,$s1,0xc
/*  f026fc0:	3c0600ff */ 	lui	$a2,0xff
/*  f026fc4:	34c6ffff */ 	ori	$a2,$a2,0xffff
/*  f026fc8:	1000ff80 */ 	b	.L0f026dcc
/*  f026fcc:	27de0008 */ 	addiu	$s8,$s8,0x8
.L0f026fd0:
/*  f026fd0:	24010001 */ 	addiu	$at,$zero,0x1
/*  f026fd4:	54410010 */ 	bnel	$v0,$at,.L0f027018
/*  f026fd8:	24010007 */ 	addiu	$at,$zero,0x7
/*  f026fdc:	8fcf0004 */ 	lw	$t7,0x4($s8)
/*  f026fe0:	8fa40120 */ 	lw	$a0,0x120($sp)
/*  f026fe4:	01e61024 */ 	and	$v0,$t7,$a2
/*  f026fe8:	0c00698d */ 	jal	func0001a634
/*  f026fec:	00022982 */ 	srl	$a1,$v0,0x6
/*  f026ff0:	afa200ec */ 	sw	$v0,0xec($sp)
/*  f026ff4:	8fa40120 */ 	lw	$a0,0x120($sp)
/*  f026ff8:	00402825 */ 	or	$a1,$v0,$zero
/*  f026ffc:	0c006b57 */ 	jal	modelNodeGetModelRelativePosition
/*  f027000:	27a600d4 */ 	addiu	$a2,$sp,0xd4
/*  f027004:	3c0600ff */ 	lui	$a2,0xff
/*  f027008:	34c6ffff */ 	ori	$a2,$a2,0xffff
/*  f02700c:	1000ff6f */ 	b	.L0f026dcc
/*  f027010:	27de0008 */ 	addiu	$s8,$s8,0x8
/*  f027014:	24010007 */ 	addiu	$at,$zero,0x7
.L0f027018:
/*  f027018:	14410004 */ 	bne	$v0,$at,.L0f02702c
/*  f02701c:	00000000 */ 	nop
/*  f027020:	8fcb0004 */ 	lw	$t3,0x4($s8)
/*  f027024:	01665024 */ 	and	$t2,$t3,$a2
/*  f027028:	afaa00ac */ 	sw	$t2,0xac($sp)
.L0f02702c:
/*  f02702c:	1000ff67 */ 	b	.L0f026dcc
/*  f027030:	27de0008 */ 	addiu	$s8,$s8,0x8
/*  f027034:	00e02025 */ 	or	$a0,$a3,$zero
/*  f027038:	0c0071e1 */ 	jal	func0001c784
/*  f02703c:	afa500fc */ 	sw	$a1,0xfc($sp)
/*  f027040:	8fa70120 */ 	lw	$a3,0x120($sp)
/*  f027044:	1000000c */ 	b	.L0f027078
/*  f027048:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f02704c:	00e02025 */ 	or	$a0,$a3,$zero
/*  f027050:	0c0071f4 */ 	jal	func0001c7d0
/*  f027054:	afa500fc */ 	sw	$a1,0xfc($sp)
/*  f027058:	8fa70120 */ 	lw	$a3,0x120($sp)
/*  f02705c:	10000006 */ 	b	.L0f027078
/*  f027060:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f027064:	00e02025 */ 	or	$a0,$a3,$zero
/*  f027068:	0c007207 */ 	jal	modelAttachHead
/*  f02706c:	afa500fc */ 	sw	$a1,0xfc($sp)
/*  f027070:	8fa70120 */ 	lw	$a3,0x120($sp)
/*  f027074:	8fa500fc */ 	lw	$a1,0xfc($sp)
.L0f027078:
/*  f027078:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f02707c:
/*  f02707c:	10400003 */ 	beqz	$v0,.L0f02708c
/*  f027080:	00000000 */ 	nop
/*  f027084:	1000000d */ 	b	.L0f0270bc
/*  f027088:	00402825 */ 	or	$a1,$v0,$zero
.L0f02708c:
/*  f02708c:	10a0000b */ 	beqz	$a1,.L0f0270bc
/*  f027090:	00000000 */ 	nop
.L0f027094:
/*  f027094:	50a00007 */ 	beqzl	$a1,.L0f0270b4
/*  f027098:	8ca50008 */ 	lw	$a1,0x8($a1)
/*  f02709c:	8ca2000c */ 	lw	$v0,0xc($a1)
/*  f0270a0:	50400004 */ 	beqzl	$v0,.L0f0270b4
/*  f0270a4:	8ca50008 */ 	lw	$a1,0x8($a1)
/*  f0270a8:	10000004 */ 	b	.L0f0270bc
/*  f0270ac:	00402825 */ 	or	$a1,$v0,$zero
/*  f0270b0:	8ca50008 */ 	lw	$a1,0x8($a1)
.L0f0270b4:
/*  f0270b4:	14a0fff7 */ 	bnez	$a1,.L0f027094
/*  f0270b8:	00000000 */ 	nop
.L0f0270bc:
/*  f0270bc:	54a0fefd */ 	bnezl	$a1,.L0f026cb4
/*  f0270c0:	94b30000 */ 	lhu	$s3,0x0($a1)
.L0f0270c4:
/*  f0270c4:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f0270c8:
/*  f0270c8:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f0270cc:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f0270d0:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f0270d4:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f0270d8:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f0270dc:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f0270e0:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f0270e4:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f0270e8:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f0270ec:	03e00008 */ 	jr	$ra
/*  f0270f0:	27bd0120 */ 	addiu	$sp,$sp,0x120
);

GLOBAL_ASM(
glabel func0f0270f4
/*  f0270f4:	27bdff58 */ 	addiu	$sp,$sp,-168
/*  f0270f8:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f0270fc:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f027100:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f027104:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f027108:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f02710c:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f027110:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f027114:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f027118:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f02711c:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f027120:	afa500ac */ 	sw	$a1,0xac($sp)
/*  f027124:	afa600b0 */ 	sw	$a2,0xb0($sp)
/*  f027128:	8c8e0020 */ 	lw	$t6,0x20($a0)
/*  f02712c:	00808025 */ 	or	$s0,$a0,$zero
/*  f027130:	afa00080 */ 	sw	$zero,0x80($sp)
/*  f027134:	0c004b70 */ 	jal	random
/*  f027138:	afae0094 */ 	sw	$t6,0x94($sp)
/*  f02713c:	3c0f800a */ 	lui	$t7,%hi(g_Vars+0x314)
/*  f027140:	8defa2d4 */ 	lw	$t7,%lo(g_Vars+0x314)($t7)
/*  f027144:	0040f025 */ 	or	$s8,$v0,$zero
/*  f027148:	55e001cb */ 	bnezl	$t7,.L0f027878
/*  f02714c:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f027150:	0fc0e6a5 */ 	jal	chrIsDead
/*  f027154:	02002025 */ 	or	$a0,$s0,$zero
/*  f027158:	104001c6 */ 	beqz	$v0,.L0f027874
/*  f02715c:	8fa40094 */ 	lw	$a0,0x94($sp)
/*  f027160:	8c980008 */ 	lw	$t8,0x8($a0)
/*  f027164:	24170003 */ 	addiu	$s7,$zero,0x3
/*  f027168:	24160005 */ 	addiu	$s6,$zero,0x5
/*  f02716c:	8f050000 */ 	lw	$a1,0x0($t8)
/*  f027170:	24120014 */ 	addiu	$s2,$zero,0x14
/*  f027174:	50a001c0 */ 	beqzl	$a1,.L0f027878
/*  f027178:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f02717c:	94a20000 */ 	lhu	$v0,0x0($a1)
.L0f027180:
/*  f027180:	24010008 */ 	addiu	$at,$zero,0x8
/*  f027184:	305900ff */ 	andi	$t9,$v0,0xff
/*  f027188:	13210199 */ 	beq	$t9,$at,.L0f0277f0
/*  f02718c:	24010012 */ 	addiu	$at,$zero,0x12
/*  f027190:	1321019d */ 	beq	$t9,$at,.L0f027808
/*  f027194:	24010017 */ 	addiu	$at,$zero,0x17
/*  f027198:	132101a1 */ 	beq	$t9,$at,.L0f027820
/*  f02719c:	24010018 */ 	addiu	$at,$zero,0x18
/*  f0271a0:	53210004 */ 	beql	$t9,$at,.L0f0271b4
/*  f0271a4:	8ca90004 */ 	lw	$t1,0x4($a1)
/*  f0271a8:	100001a2 */ 	b	.L0f027834
/*  f0271ac:	8ca20014 */ 	lw	$v0,0x14($a1)
/*  f0271b0:	8ca90004 */ 	lw	$t1,0x4($a1)
.L0f0271b4:
/*  f0271b4:	afa500a4 */ 	sw	$a1,0xa4($sp)
/*  f0271b8:	0c006a87 */ 	jal	modelGetNodeRwData
/*  f0271bc:	afa900a0 */ 	sw	$t1,0xa0($sp)
/*  f0271c0:	8c4a0004 */ 	lw	$t2,0x4($v0)
/*  f0271c4:	0040a025 */ 	or	$s4,$v0,$zero
/*  f0271c8:	8fa800a0 */ 	lw	$t0,0xa0($sp)
/*  f0271cc:	15400004 */ 	bnez	$t2,.L0f0271e0
/*  f0271d0:	8fa500a4 */ 	lw	$a1,0xa4($sp)
/*  f0271d4:	8ca20014 */ 	lw	$v0,0x14($a1)
/*  f0271d8:	10000196 */ 	b	.L0f027834
/*  f0271dc:	8fa40094 */ 	lw	$a0,0x94($sp)
.L0f0271e0:
/*  f0271e0:	8d03000c */ 	lw	$v1,0xc($t0)
/*  f0271e4:	8c440000 */ 	lw	$a0,0x0($v0)
/*  f0271e8:	5464017e */ 	bnel	$v1,$a0,.L0f0277e4
/*  f0271ec:	8fa500a4 */ 	lw	$a1,0xa4($sp)
/*  f0271f0:	14640022 */ 	bne	$v1,$a0,.L0f02727c
/*  f0271f4:	00002825 */ 	or	$a1,$zero,$zero
/*  f0271f8:	85040010 */ 	lh	$a0,0x10($t0)
/*  f0271fc:	00003025 */ 	or	$a2,$zero,$zero
/*  f027200:	0fc4a557 */ 	jal	func0f12955c
/*  f027204:	00003825 */ 	or	$a3,$zero,$zero
/*  f027208:	1040001c */ 	beqz	$v0,.L0f02727c
/*  f02720c:	8fa500a0 */ 	lw	$a1,0xa0($sp)
/*  f027210:	84ac0010 */ 	lh	$t4,0x10($a1)
/*  f027214:	00008825 */ 	or	$s1,$zero,$zero
/*  f027218:	00001825 */ 	or	$v1,$zero,$zero
/*  f02721c:	19800016 */ 	blez	$t4,.L0f027278
/*  f027220:	00402025 */ 	or	$a0,$v0,$zero
/*  f027224:	8e8d0000 */ 	lw	$t5,0x0($s4)
.L0f027228:
/*  f027228:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f02722c:	2484000c */ 	addiu	$a0,$a0,0xc
/*  f027230:	01a37021 */ 	addu	$t6,$t5,$v1
/*  f027234:	89c10000 */ 	lwl	$at,0x0($t6)
/*  f027238:	99c10003 */ 	lwr	$at,0x3($t6)
/*  f02723c:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f027240:	a881fff4 */ 	swl	$at,-0xc($a0)
/*  f027244:	b881fff7 */ 	swr	$at,-0x9($a0)
/*  f027248:	89d80004 */ 	lwl	$t8,0x4($t6)
/*  f02724c:	99d80007 */ 	lwr	$t8,0x7($t6)
/*  f027250:	a898fff8 */ 	swl	$t8,-0x8($a0)
/*  f027254:	b898fffb */ 	swr	$t8,-0x5($a0)
/*  f027258:	89c10008 */ 	lwl	$at,0x8($t6)
/*  f02725c:	99c1000b */ 	lwr	$at,0xb($t6)
/*  f027260:	a881fffc */ 	swl	$at,-0x4($a0)
/*  f027264:	b881ffff */ 	swr	$at,-0x1($a0)
/*  f027268:	84b90010 */ 	lh	$t9,0x10($a1)
/*  f02726c:	0239082a */ 	slt	$at,$s1,$t9
/*  f027270:	5420ffed */ 	bnezl	$at,.L0f027228
/*  f027274:	8e8d0000 */ 	lw	$t5,0x0($s4)
.L0f027278:
/*  f027278:	ae820000 */ 	sw	$v0,0x0($s4)
.L0f02727c:
/*  f02727c:	8fa800a0 */ 	lw	$t0,0xa0($sp)
/*  f027280:	8e980008 */ 	lw	$t8,0x8($s4)
/*  f027284:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f027288:	850a0010 */ 	lh	$t2,0x10($t0)
/*  f02728c:	8d09000c */ 	lw	$t1,0xc($t0)
/*  f027290:	00003025 */ 	or	$a2,$zero,$zero
/*  f027294:	000a5880 */ 	sll	$t3,$t2,0x2
/*  f027298:	016a5823 */ 	subu	$t3,$t3,$t2
/*  f02729c:	000b5880 */ 	sll	$t3,$t3,0x2
/*  f0272a0:	012b6021 */ 	addu	$t4,$t1,$t3
/*  f0272a4:	258d0007 */ 	addiu	$t5,$t4,0x7
/*  f0272a8:	35af0007 */ 	ori	$t7,$t5,0x7
/*  f0272ac:	39ee0007 */ 	xori	$t6,$t7,0x7
/*  f0272b0:	15d80016 */ 	bne	$t6,$t8,.L0f02730c
/*  f0272b4:	00003825 */ 	or	$a3,$zero,$zero
/*  f0272b8:	0fc4a557 */ 	jal	func0f12955c
/*  f0272bc:	95040016 */ 	lhu	$a0,0x16($t0)
/*  f0272c0:	10400012 */ 	beqz	$v0,.L0f02730c
/*  f0272c4:	8fa500a0 */ 	lw	$a1,0xa0($sp)
/*  f0272c8:	94b90016 */ 	lhu	$t9,0x16($a1)
/*  f0272cc:	00008825 */ 	or	$s1,$zero,$zero
/*  f0272d0:	00001825 */ 	or	$v1,$zero,$zero
/*  f0272d4:	1b20000c */ 	blez	$t9,.L0f027308
/*  f0272d8:	00402025 */ 	or	$a0,$v0,$zero
/*  f0272dc:	8e8a0008 */ 	lw	$t2,0x8($s4)
.L0f0272e0:
/*  f0272e0:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f0272e4:	24840004 */ 	addiu	$a0,$a0,0x4
/*  f0272e8:	01434821 */ 	addu	$t1,$t2,$v1
/*  f0272ec:	8d210000 */ 	lw	$at,0x0($t1)
/*  f0272f0:	24630004 */ 	addiu	$v1,$v1,0x4
/*  f0272f4:	ac81fffc */ 	sw	$at,-0x4($a0)
/*  f0272f8:	94ad0016 */ 	lhu	$t5,0x16($a1)
/*  f0272fc:	022d082a */ 	slt	$at,$s1,$t5
/*  f027300:	5420fff7 */ 	bnezl	$at,.L0f0272e0
/*  f027304:	8e8a0008 */ 	lw	$t2,0x8($s4)
.L0f027308:
/*  f027308:	ae820008 */ 	sw	$v0,0x8($s4)
.L0f02730c:
/*  f02730c:	8faf00a0 */ 	lw	$t7,0xa0($sp)
/*  f027310:	8e8e0000 */ 	lw	$t6,0x0($s4)
/*  f027314:	8de3000c */ 	lw	$v1,0xc($t7)
/*  f027318:	506e0132 */ 	beql	$v1,$t6,.L0f0277e4
/*  f02731c:	8fa500a4 */ 	lw	$a1,0xa4($sp)
/*  f027320:	85f80010 */ 	lh	$t8,0x10($t7)
/*  f027324:	8e8d0008 */ 	lw	$t5,0x8($s4)
/*  f027328:	0018c880 */ 	sll	$t9,$t8,0x2
/*  f02732c:	0338c823 */ 	subu	$t9,$t9,$t8
/*  f027330:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f027334:	00795021 */ 	addu	$t2,$v1,$t9
/*  f027338:	254b0007 */ 	addiu	$t3,$t2,0x7
/*  f02733c:	35690007 */ 	ori	$t1,$t3,0x7
/*  f027340:	392c0007 */ 	xori	$t4,$t1,0x7
/*  f027344:	118d0126 */ 	beq	$t4,$t5,.L0f0277e0
/*  f027348:	8fb900a0 */ 	lw	$t9,0xa0($sp)
/*  f02734c:	8de20000 */ 	lw	$v0,0x0($t7)
/*  f027350:	8e830004 */ 	lw	$v1,0x4($s4)
/*  f027354:	00008825 */ 	or	$s1,$zero,$zero
/*  f027358:	3c0100ff */ 	lui	$at,0xff
/*  f02735c:	14430006 */ 	bne	$v0,$v1,.L0f027378
/*  f027360:	0060a825 */ 	or	$s5,$v1,$zero
/*  f027364:	8dee0008 */ 	lw	$t6,0x8($t7)
/*  f027368:	3421ffff */ 	ori	$at,$at,0xffff
/*  f02736c:	0041c024 */ 	and	$t8,$v0,$at
/*  f027370:	10000001 */ 	b	.L0f027378
/*  f027374:	01d8a821 */ 	addu	$s5,$t6,$t8
.L0f027378:
/*  f027378:	8f220004 */ 	lw	$v0,0x4($t9)
/*  f02737c:	3c0100ff */ 	lui	$at,0xff
/*  f027380:	50400008 */ 	beqzl	$v0,.L0f0273a4
/*  f027384:	afa00084 */ 	sw	$zero,0x84($sp)
/*  f027388:	8f2a0008 */ 	lw	$t2,0x8($t9)
/*  f02738c:	3421ffff */ 	ori	$at,$at,0xffff
/*  f027390:	00415824 */ 	and	$t3,$v0,$at
/*  f027394:	014b4821 */ 	addu	$t1,$t2,$t3
/*  f027398:	10000002 */ 	b	.L0f0273a4
/*  f02739c:	afa90084 */ 	sw	$t1,0x84($sp)
/*  f0273a0:	afa00084 */ 	sw	$zero,0x84($sp)
.L0f0273a4:
/*  f0273a4:	82a20000 */ 	lb	$v0,0x0($s5)
/*  f0273a8:	2401ffb8 */ 	addiu	$at,$zero,-72
/*  f0273ac:	8fac0084 */ 	lw	$t4,0x84($sp)
/*  f0273b0:	54410006 */ 	bnel	$v0,$at,.L0f0273cc
/*  f0273b4:	24010004 */ 	addiu	$at,$zero,0x4
/*  f0273b8:	118000ee */ 	beqz	$t4,.L0f027774
/*  f0273bc:	0180a825 */ 	or	$s5,$t4,$zero
/*  f0273c0:	1000fff8 */ 	b	.L0f0273a4
/*  f0273c4:	afa00084 */ 	sw	$zero,0x84($sp)
/*  f0273c8:	24010004 */ 	addiu	$at,$zero,0x4
.L0f0273cc:
/*  f0273cc:	144100d9 */ 	bne	$v0,$at,.L0f027734
/*  f0273d0:	8fb80080 */ 	lw	$t8,0x80($sp)
/*  f0273d4:	8ea20004 */ 	lw	$v0,0x4($s5)
/*  f0273d8:	92b30001 */ 	lbu	$s3,0x1($s5)
/*  f0273dc:	3c0100ff */ 	lui	$at,0xff
/*  f0273e0:	8e8f0000 */ 	lw	$t7,0x0($s4)
/*  f0273e4:	3421ffff */ 	ori	$at,$at,0xffff
/*  f0273e8:	00416824 */ 	and	$t5,$v0,$at
/*  f0273ec:	00137102 */ 	srl	$t6,$s3,0x4
/*  f0273f0:	25d30001 */ 	addiu	$s3,$t6,0x1
/*  f0273f4:	130000dd */ 	beqz	$t8,.L0f02776c
/*  f0273f8:	01ed1821 */ 	addu	$v1,$t7,$t5
/*  f0273fc:	1a6000db */ 	blez	$s3,.L0f02776c
/*  f027400:	00608025 */ 	or	$s0,$v1,$zero
.L0f027404:
/*  f027404:	4459f800 */ 	cfc1	$t9,$31
/*  f027408:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f02740c:	44caf800 */ 	ctc1	$t2,$31
/*  f027410:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f027414:	3c014f00 */ 	lui	$at,0x4f00
/*  f027418:	460021a4 */ 	cvt.w.s	$f6,$f4
/*  f02741c:	444af800 */ 	cfc1	$t2,$31
/*  f027420:	00000000 */ 	nop
/*  f027424:	314a0078 */ 	andi	$t2,$t2,0x78
/*  f027428:	51400013 */ 	beqzl	$t2,.L0f027478
/*  f02742c:	440a3000 */ 	mfc1	$t2,$f6
/*  f027430:	44813000 */ 	mtc1	$at,$f6
/*  f027434:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f027438:	46062181 */ 	sub.s	$f6,$f4,$f6
/*  f02743c:	44caf800 */ 	ctc1	$t2,$31
/*  f027440:	00000000 */ 	nop
/*  f027444:	460031a4 */ 	cvt.w.s	$f6,$f6
/*  f027448:	444af800 */ 	cfc1	$t2,$31
/*  f02744c:	00000000 */ 	nop
/*  f027450:	314a0078 */ 	andi	$t2,$t2,0x78
/*  f027454:	15400005 */ 	bnez	$t2,.L0f02746c
/*  f027458:	00000000 */ 	nop
/*  f02745c:	440a3000 */ 	mfc1	$t2,$f6
/*  f027460:	3c018000 */ 	lui	$at,0x8000
/*  f027464:	10000007 */ 	b	.L0f027484
/*  f027468:	01415025 */ 	or	$t2,$t2,$at
.L0f02746c:
/*  f02746c:	10000005 */ 	b	.L0f027484
/*  f027470:	240affff */ 	addiu	$t2,$zero,-1
/*  f027474:	440a3000 */ 	mfc1	$t2,$f6
.L0f027478:
/*  f027478:	00000000 */ 	nop
/*  f02747c:	0540fffb */ 	bltz	$t2,.L0f02746c
/*  f027480:	00000000 */ 	nop
.L0f027484:
/*  f027484:	44d9f800 */ 	ctc1	$t9,$31
/*  f027488:	015e5821 */ 	addu	$t3,$t2,$s8
/*  f02748c:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f027490:	c7a80074 */ 	lwc1	$f8,0x74($sp)
/*  f027494:	4459f800 */ 	cfc1	$t9,$31
/*  f027498:	44caf800 */ 	ctc1	$t2,$31
/*  f02749c:	86090000 */ 	lh	$t1,0x0($s0)
/*  f0274a0:	860d0002 */ 	lh	$t5,0x2($s0)
/*  f0274a4:	460042a4 */ 	cvt.w.s	$f10,$f8
/*  f0274a8:	860e0004 */ 	lh	$t6,0x4($s0)
/*  f0274ac:	01696021 */ 	addu	$t4,$t3,$t1
/*  f0274b0:	018d7821 */ 	addu	$t7,$t4,$t5
/*  f0274b4:	444af800 */ 	cfc1	$t2,$31
/*  f0274b8:	3c014f00 */ 	lui	$at,0x4f00
/*  f0274bc:	01eec021 */ 	addu	$t8,$t7,$t6
/*  f0274c0:	314a0078 */ 	andi	$t2,$t2,0x78
/*  f0274c4:	51400013 */ 	beqzl	$t2,.L0f027514
/*  f0274c8:	440a5000 */ 	mfc1	$t2,$f10
/*  f0274cc:	44815000 */ 	mtc1	$at,$f10
/*  f0274d0:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f0274d4:	460a4281 */ 	sub.s	$f10,$f8,$f10
/*  f0274d8:	44caf800 */ 	ctc1	$t2,$31
/*  f0274dc:	00000000 */ 	nop
/*  f0274e0:	460052a4 */ 	cvt.w.s	$f10,$f10
/*  f0274e4:	444af800 */ 	cfc1	$t2,$31
/*  f0274e8:	00000000 */ 	nop
/*  f0274ec:	314a0078 */ 	andi	$t2,$t2,0x78
/*  f0274f0:	15400005 */ 	bnez	$t2,.L0f027508
/*  f0274f4:	00000000 */ 	nop
/*  f0274f8:	440a5000 */ 	mfc1	$t2,$f10
/*  f0274fc:	3c018000 */ 	lui	$at,0x8000
/*  f027500:	10000007 */ 	b	.L0f027520
/*  f027504:	01415025 */ 	or	$t2,$t2,$at
.L0f027508:
/*  f027508:	10000005 */ 	b	.L0f027520
/*  f02750c:	240affff */ 	addiu	$t2,$zero,-1
/*  f027510:	440a5000 */ 	mfc1	$t2,$f10
.L0f027514:
/*  f027514:	00000000 */ 	nop
/*  f027518:	0540fffb */ 	bltz	$t2,.L0f027508
/*  f02751c:	00000000 */ 	nop
.L0f027520:
/*  f027520:	44d9f800 */ 	ctc1	$t9,$31
/*  f027524:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f027528:	c7b00078 */ 	lwc1	$f16,0x78($sp)
/*  f02752c:	030a5821 */ 	addu	$t3,$t8,$t2
/*  f027530:	4449f800 */ 	cfc1	$t1,$31
/*  f027534:	44ccf800 */ 	ctc1	$t4,$31
/*  f027538:	3c014f00 */ 	lui	$at,0x4f00
/*  f02753c:	460084a4 */ 	cvt.w.s	$f18,$f16
/*  f027540:	444cf800 */ 	cfc1	$t4,$31
/*  f027544:	00000000 */ 	nop
/*  f027548:	318c0078 */ 	andi	$t4,$t4,0x78
/*  f02754c:	51800013 */ 	beqzl	$t4,.L0f02759c
/*  f027550:	440c9000 */ 	mfc1	$t4,$f18
/*  f027554:	44819000 */ 	mtc1	$at,$f18
/*  f027558:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f02755c:	46128481 */ 	sub.s	$f18,$f16,$f18
/*  f027560:	44ccf800 */ 	ctc1	$t4,$31
/*  f027564:	00000000 */ 	nop
/*  f027568:	460094a4 */ 	cvt.w.s	$f18,$f18
/*  f02756c:	444cf800 */ 	cfc1	$t4,$31
/*  f027570:	00000000 */ 	nop
/*  f027574:	318c0078 */ 	andi	$t4,$t4,0x78
/*  f027578:	15800005 */ 	bnez	$t4,.L0f027590
/*  f02757c:	00000000 */ 	nop
/*  f027580:	440c9000 */ 	mfc1	$t4,$f18
/*  f027584:	3c018000 */ 	lui	$at,0x8000
/*  f027588:	10000007 */ 	b	.L0f0275a8
/*  f02758c:	01816025 */ 	or	$t4,$t4,$at
.L0f027590:
/*  f027590:	10000005 */ 	b	.L0f0275a8
/*  f027594:	240cffff */ 	addiu	$t4,$zero,-1
/*  f027598:	440c9000 */ 	mfc1	$t4,$f18
.L0f02759c:
/*  f02759c:	00000000 */ 	nop
/*  f0275a0:	0580fffb */ 	bltz	$t4,.L0f027590
/*  f0275a4:	00000000 */ 	nop
.L0f0275a8:
/*  f0275a8:	44c9f800 */ 	ctc1	$t1,$31
/*  f0275ac:	0fc4a47e */ 	jal	func0f1291f8
/*  f0275b0:	016c2021 */ 	addu	$a0,$t3,$t4
/*  f0275b4:	86020000 */ 	lh	$v0,0x0($s0)
/*  f0275b8:	1840000e */ 	blez	$v0,.L0f0275f4
/*  f0275bc:	00000000 */ 	nop
/*  f0275c0:	0fc4a46c */ 	jal	func0f1291b0
/*  f0275c4:	00000000 */ 	nop
/*  f0275c8:	0052001b */ 	divu	$zero,$v0,$s2
/*  f0275cc:	860d0000 */ 	lh	$t5,0x0($s0)
/*  f0275d0:	00007810 */ 	mfhi	$t7
/*  f0275d4:	000f7400 */ 	sll	$t6,$t7,0x10
/*  f0275d8:	000ecc03 */ 	sra	$t9,$t6,0x10
/*  f0275dc:	16400002 */ 	bnez	$s2,.L0f0275e8
/*  f0275e0:	00000000 */ 	nop
/*  f0275e4:	0007000d */ 	break	0x7
.L0f0275e8:
/*  f0275e8:	01b9c023 */ 	subu	$t8,$t5,$t9
/*  f0275ec:	1000000f */ 	b	.L0f02762c
/*  f0275f0:	a6180000 */ 	sh	$t8,0x0($s0)
.L0f0275f4:
/*  f0275f4:	0443000e */ 	bgezl	$v0,.L0f027630
/*  f0275f8:	86020002 */ 	lh	$v0,0x2($s0)
/*  f0275fc:	0fc4a46c */ 	jal	func0f1291b0
/*  f027600:	00000000 */ 	nop
/*  f027604:	0052001b */ 	divu	$zero,$v0,$s2
/*  f027608:	860a0000 */ 	lh	$t2,0x0($s0)
/*  f02760c:	00004810 */ 	mfhi	$t1
/*  f027610:	00095c00 */ 	sll	$t3,$t1,0x10
/*  f027614:	000b6403 */ 	sra	$t4,$t3,0x10
/*  f027618:	014c7821 */ 	addu	$t7,$t2,$t4
/*  f02761c:	a60f0000 */ 	sh	$t7,0x0($s0)
/*  f027620:	16400002 */ 	bnez	$s2,.L0f02762c
/*  f027624:	00000000 */ 	nop
/*  f027628:	0007000d */ 	break	0x7
.L0f02762c:
/*  f02762c:	86020002 */ 	lh	$v0,0x2($s0)
.L0f027630:
/*  f027630:	1840000e */ 	blez	$v0,.L0f02766c
/*  f027634:	00000000 */ 	nop
/*  f027638:	0fc4a46c */ 	jal	func0f1291b0
/*  f02763c:	00000000 */ 	nop
/*  f027640:	0052001b */ 	divu	$zero,$v0,$s2
/*  f027644:	860e0002 */ 	lh	$t6,0x2($s0)
/*  f027648:	00006810 */ 	mfhi	$t5
/*  f02764c:	000dcc00 */ 	sll	$t9,$t5,0x10
/*  f027650:	0019c403 */ 	sra	$t8,$t9,0x10
/*  f027654:	16400002 */ 	bnez	$s2,.L0f027660
/*  f027658:	00000000 */ 	nop
/*  f02765c:	0007000d */ 	break	0x7
.L0f027660:
/*  f027660:	01d84823 */ 	subu	$t1,$t6,$t8
/*  f027664:	1000000f */ 	b	.L0f0276a4
/*  f027668:	a6090002 */ 	sh	$t1,0x2($s0)
.L0f02766c:
/*  f02766c:	0443000e */ 	bgezl	$v0,.L0f0276a8
/*  f027670:	86020004 */ 	lh	$v0,0x4($s0)
/*  f027674:	0fc4a46c */ 	jal	func0f1291b0
/*  f027678:	00000000 */ 	nop
/*  f02767c:	0052001b */ 	divu	$zero,$v0,$s2
/*  f027680:	860b0002 */ 	lh	$t3,0x2($s0)
/*  f027684:	00005010 */ 	mfhi	$t2
/*  f027688:	000a6400 */ 	sll	$t4,$t2,0x10
/*  f02768c:	000c7c03 */ 	sra	$t7,$t4,0x10
/*  f027690:	016f6821 */ 	addu	$t5,$t3,$t7
/*  f027694:	a60d0002 */ 	sh	$t5,0x2($s0)
/*  f027698:	16400002 */ 	bnez	$s2,.L0f0276a4
/*  f02769c:	00000000 */ 	nop
/*  f0276a0:	0007000d */ 	break	0x7
.L0f0276a4:
/*  f0276a4:	86020004 */ 	lh	$v0,0x4($s0)
.L0f0276a8:
/*  f0276a8:	1840000e */ 	blez	$v0,.L0f0276e4
/*  f0276ac:	00000000 */ 	nop
/*  f0276b0:	0fc4a46c */ 	jal	func0f1291b0
/*  f0276b4:	00000000 */ 	nop
/*  f0276b8:	0052001b */ 	divu	$zero,$v0,$s2
/*  f0276bc:	86190004 */ 	lh	$t9,0x4($s0)
/*  f0276c0:	00007010 */ 	mfhi	$t6
/*  f0276c4:	000ec400 */ 	sll	$t8,$t6,0x10
/*  f0276c8:	00184c03 */ 	sra	$t1,$t8,0x10
/*  f0276cc:	16400002 */ 	bnez	$s2,.L0f0276d8
/*  f0276d0:	00000000 */ 	nop
/*  f0276d4:	0007000d */ 	break	0x7
.L0f0276d8:
/*  f0276d8:	03295023 */ 	subu	$t2,$t9,$t1
/*  f0276dc:	1000000f */ 	b	.L0f02771c
/*  f0276e0:	a60a0004 */ 	sh	$t2,0x4($s0)
.L0f0276e4:
/*  f0276e4:	0443000e */ 	bgezl	$v0,.L0f027720
/*  f0276e8:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f0276ec:	0fc4a46c */ 	jal	func0f1291b0
/*  f0276f0:	00000000 */ 	nop
/*  f0276f4:	0052001b */ 	divu	$zero,$v0,$s2
/*  f0276f8:	860c0002 */ 	lh	$t4,0x2($s0)
/*  f0276fc:	00005810 */ 	mfhi	$t3
/*  f027700:	000b7c00 */ 	sll	$t7,$t3,0x10
/*  f027704:	000f6c03 */ 	sra	$t5,$t7,0x10
/*  f027708:	018d7021 */ 	addu	$t6,$t4,$t5
/*  f02770c:	a60e0002 */ 	sh	$t6,0x2($s0)
/*  f027710:	16400002 */ 	bnez	$s2,.L0f02771c
/*  f027714:	00000000 */ 	nop
/*  f027718:	0007000d */ 	break	0x7
.L0f02771c:
/*  f02771c:	26310001 */ 	addiu	$s1,$s1,0x1
.L0f027720:
/*  f027720:	1633ff38 */ 	bne	$s1,$s3,.L0f027404
/*  f027724:	2610000c */ 	addiu	$s0,$s0,0xc
/*  f027728:	00008825 */ 	or	$s1,$zero,$zero
/*  f02772c:	1000ff1d */ 	b	.L0f0273a4
/*  f027730:	26b50008 */ 	addiu	$s5,$s5,0x8
.L0f027734:
/*  f027734:	24010001 */ 	addiu	$at,$zero,0x1
/*  f027738:	1441000c */ 	bne	$v0,$at,.L0f02776c
/*  f02773c:	8fa40094 */ 	lw	$a0,0x94($sp)
/*  f027740:	8ea20004 */ 	lw	$v0,0x4($s5)
/*  f027744:	3c0100ff */ 	lui	$at,0xff
/*  f027748:	3421ffff */ 	ori	$at,$at,0xffff
/*  f02774c:	0041c024 */ 	and	$t8,$v0,$at
/*  f027750:	0c00698d */ 	jal	func0001a634
/*  f027754:	00182982 */ 	srl	$a1,$t8,0x6
/*  f027758:	afa20080 */ 	sw	$v0,0x80($sp)
/*  f02775c:	8fa40094 */ 	lw	$a0,0x94($sp)
/*  f027760:	00402825 */ 	or	$a1,$v0,$zero
/*  f027764:	0c006b57 */ 	jal	modelNodeGetModelRelativePosition
/*  f027768:	27a60074 */ 	addiu	$a2,$sp,0x74
.L0f02776c:
/*  f02776c:	1000ff0d */ 	b	.L0f0273a4
/*  f027770:	26b50008 */ 	addiu	$s5,$s5,0x8
.L0f027774:
/*  f027774:	8fb900a0 */ 	lw	$t9,0xa0($sp)
/*  f027778:	97290016 */ 	lhu	$t1,0x16($t9)
/*  f02777c:	19200018 */ 	blez	$t1,.L0f0277e0
/*  f027780:	00001825 */ 	or	$v1,$zero,$zero
.L0f027784:
/*  f027784:	8e8a0008 */ 	lw	$t2,0x8($s4)
/*  f027788:	00115880 */ 	sll	$t3,$s1,0x2
/*  f02778c:	014b7821 */ 	addu	$t7,$t2,$t3
/*  f027790:	01e32021 */ 	addu	$a0,$t7,$v1
/*  f027794:	90820000 */ 	lbu	$v0,0x0($a0)
/*  f027798:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f02779c:	00560019 */ 	multu	$v0,$s6
/*  f0277a0:	00001012 */ 	mflo	$v0
/*  f0277a4:	04410003 */ 	bgez	$v0,.L0f0277b4
/*  f0277a8:	00026103 */ 	sra	$t4,$v0,0x4
/*  f0277ac:	2441000f */ 	addiu	$at,$v0,0xf
/*  f0277b0:	00016103 */ 	sra	$t4,$at,0x4
.L0f0277b4:
/*  f0277b4:	05810002 */ 	bgez	$t4,.L0f0277c0
/*  f0277b8:	01801025 */ 	or	$v0,$t4,$zero
/*  f0277bc:	00001025 */ 	or	$v0,$zero,$zero
.L0f0277c0:
/*  f0277c0:	1477fff0 */ 	bne	$v1,$s7,.L0f027784
/*  f0277c4:	a0820000 */ 	sb	$v0,0x0($a0)
/*  f0277c8:	8fad00a0 */ 	lw	$t5,0xa0($sp)
/*  f0277cc:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f0277d0:	95ae0016 */ 	lhu	$t6,0x16($t5)
/*  f0277d4:	022e082a */ 	slt	$at,$s1,$t6
/*  f0277d8:	5420ffea */ 	bnezl	$at,.L0f027784
/*  f0277dc:	00001825 */ 	or	$v1,$zero,$zero
.L0f0277e0:
/*  f0277e0:	8fa500a4 */ 	lw	$a1,0xa4($sp)
.L0f0277e4:
/*  f0277e4:	8fa40094 */ 	lw	$a0,0x94($sp)
/*  f0277e8:	10000012 */ 	b	.L0f027834
/*  f0277ec:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f0277f0:
/*  f0277f0:	0c0071e1 */ 	jal	func0001c784
/*  f0277f4:	afa500a4 */ 	sw	$a1,0xa4($sp)
/*  f0277f8:	8fa500a4 */ 	lw	$a1,0xa4($sp)
/*  f0277fc:	8fa40094 */ 	lw	$a0,0x94($sp)
/*  f027800:	1000000c */ 	b	.L0f027834
/*  f027804:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f027808:
/*  f027808:	0c0071f4 */ 	jal	func0001c7d0
/*  f02780c:	afa500a4 */ 	sw	$a1,0xa4($sp)
/*  f027810:	8fa500a4 */ 	lw	$a1,0xa4($sp)
/*  f027814:	8fa40094 */ 	lw	$a0,0x94($sp)
/*  f027818:	10000006 */ 	b	.L0f027834
/*  f02781c:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f027820:
/*  f027820:	0c007207 */ 	jal	modelAttachHead
/*  f027824:	afa500a4 */ 	sw	$a1,0xa4($sp)
/*  f027828:	8fa500a4 */ 	lw	$a1,0xa4($sp)
/*  f02782c:	8fa40094 */ 	lw	$a0,0x94($sp)
/*  f027830:	8ca20014 */ 	lw	$v0,0x14($a1)
.L0f027834:
/*  f027834:	10400003 */ 	beqz	$v0,.L0f027844
/*  f027838:	00000000 */ 	nop
/*  f02783c:	1000000b */ 	b	.L0f02786c
/*  f027840:	00402825 */ 	or	$a1,$v0,$zero
.L0f027844:
/*  f027844:	10a00009 */ 	beqz	$a1,.L0f02786c
/*  f027848:	00000000 */ 	nop
/*  f02784c:	8ca2000c */ 	lw	$v0,0xc($a1)
.L0f027850:
/*  f027850:	50400004 */ 	beqzl	$v0,.L0f027864
/*  f027854:	8ca50008 */ 	lw	$a1,0x8($a1)
/*  f027858:	10000004 */ 	b	.L0f02786c
/*  f02785c:	00402825 */ 	or	$a1,$v0,$zero
/*  f027860:	8ca50008 */ 	lw	$a1,0x8($a1)
.L0f027864:
/*  f027864:	54a0fffa */ 	bnezl	$a1,.L0f027850
/*  f027868:	8ca2000c */ 	lw	$v0,0xc($a1)
.L0f02786c:
/*  f02786c:	54a0fe44 */ 	bnezl	$a1,.L0f027180
/*  f027870:	94a20000 */ 	lhu	$v0,0x0($a1)
.L0f027874:
/*  f027874:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f027878:
/*  f027878:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f02787c:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f027880:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f027884:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f027888:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f02788c:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f027890:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f027894:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f027898:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f02789c:	03e00008 */ 	jr	$ra
/*  f0278a0:	27bd00a8 */ 	addiu	$sp,$sp,0xa8
);

f32 func0f0278a4(struct chrdata *chr)
{
	s32 i;
	f32 result;
	f32 highest = 0;

	if (chr->model) {
		result = func0001af80(chr->model);

		for (i = 0; i < 2; i++) {
			if (chr->weapons_held[i]) {
				struct defaultobj *obj = chr->weapons_held[i]->obj;
				f32 value = func0001af80(obj->model) * chr->model->scale;

				if (value > highest) {
					highest = value;
				}
			}
		}

		result += highest;

		if (chrGetShield(chr) > 0) {
			result += 10;
		}
	} else {
		result = 100;
	}

	return result;
}

void func0f027994(struct prop *prop, struct shotdata *shotdata, bool arg2, bool arg3)
{
	struct coord spdc;
	struct coord spd0;
	struct chrdata *chr = prop->chr;

	if ((chr->chrflags & CHRCFLAG_HIDDEN) == 0 && (prop->flags & PROPFLAG_ONSCREEN)) {
		f32 fStack32 = func0f0278a4(chr);

		if (prop->z - fStack32 < shotdata->unk34) {
			struct model *model = chr->model;
			s32 spc0 = 0;
			struct modelnode *node = NULL;
			s32 spb8 = 0;
			struct hitthing sp88;
			s32 sp84 = 0;
			struct modelnode *sp80 = NULL;
			Mtxf *iVar5 = func0001a60c(model);
			struct prop *next;
			struct prop *child;
			s32 sp70;
			Mtxf *mtx;
			f32 sp68;

			if (func0f06b39c(&shotdata->unk00, &shotdata->unk0c, (struct coord *)iVar5->m[3], fStack32)) {
				spb8 = 1;
				spc0 = 1;
			}

			if (spc0) {
				if (chrGetShield(chr) > 0.0f) {
					var8005efc0 = 10.0f / model->scale;
				}

				child = prop->child;

				while (child) {
					next = child->next;
					func0f0859a0(child, shotdata);
					child = next;
				}

				if (arg3 || var8005efc0 > 0.0f) {
					spc0 = func000225d4(model, &shotdata->unk00, &shotdata->unk0c, &node);

					while (spc0 > 0) {
						if (func0f084594(model, node, &shotdata->unk00, &shotdata->unk0c, &sp88, &sp84, &sp80)) {
							func00015b68(&model->matrices[sp84], &sp88.unk00, &spdc);
							func00015b64(currentPlayerGetUnk174c(), &spdc);
							func00015b14(&model->matrices[sp84], &sp88.unk0c, &spd0);
							func00015b10(currentPlayerGetUnk174c(), &spd0);
							break;
						}

						spc0 = func000225d4(model, &shotdata->unk00, &shotdata->unk0c, &node);
					}
				} else {
					spc0 = func000225d4(model, &shotdata->unk00, &shotdata->unk0c, &node);

					if (spc0 > 0) {
						if (func0f06bea0(model, model->filedata->rootnode, model->filedata->rootnode, &shotdata->unk00,
									&shotdata->unk0c, &sp88.unk00, &sp70, &node, &spc0, &sp84, &sp80)) {
							func00015b68(currentPlayerGetUnk174c(), &sp88.unk00, &spdc);
							func00015b14(currentPlayerGetUnk174c(), &sp88.unk0c, &spd0);
						} else {
							spc0 = 0;
						}
					}
				}

				if (var8005efc0 > 0.0f) {
					var8005efc0 = 0.0f;
				}
			}

			if (spc0 > 0) {
				mtx = currentPlayerGetMatrix1740();
				sp68 = spdc.x * mtx->m[0][2] + spdc.y * mtx->m[1][2] + spdc.z * mtx->m[2][2] + mtx->m[3][2];
				sp68 = -sp68;

				if (sp68 < shotdata->unk34) {
					func0f061fa8(shotdata, prop, sp68, spc0, node, &sp88, sp84, sp80, model, 1, chrGetShield(chr) > 0.0f, &spdc, &spd0);
				}
			}

			if (spb8 && spc0 <= 0 && prop->z <= shotdata->unk34 && arg2) {
				if (chrGetTargetProp(chr) == g_Vars.currentplayer->prop) {
					chr->chrflags |= CHRCFLAG_NEAR_MISS;
				}

				chr->numclosearghs++;
			}
		}
	}
}

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func0f027e1c
/*  f027e1c:	27bdff08 */ 	addiu	$sp,$sp,-248
/*  f027e20:	afa400f8 */ 	sw	$a0,0xf8($sp)
/*  f027e24:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f027e28:	afb10038 */ 	sw	$s1,0x38($sp)
/*  f027e2c:	24840018 */ 	addiu	$a0,$a0,0x18
/*  f027e30:	00a08825 */ 	or	$s1,$a1,$zero
/*  f027e34:	afb00034 */ 	sw	$s0,0x34($sp)
/*  f027e38:	a3a0008f */ 	sb	$zero,0x8f($sp)
/*  f027e3c:	0fc2c41f */ 	jal	gsetGetWeaponFunction
/*  f027e40:	afa40048 */ 	sw	$a0,0x48($sp)
/*  f027e44:	50400009 */ 	beqzl	$v0,.L0f027e6c
/*  f027e48:	8e300004 */ 	lw	$s0,0x4($s1)
/*  f027e4c:	8c4e0000 */ 	lw	$t6,0x0($v0)
/*  f027e50:	24010003 */ 	addiu	$at,$zero,0x3
/*  f027e54:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f027e58:	31cf00ff */ 	andi	$t7,$t6,0xff
/*  f027e5c:	55e10003 */ 	bnel	$t7,$at,.L0f027e6c
/*  f027e60:	8e300004 */ 	lw	$s0,0x4($s1)
/*  f027e64:	a3b8008f */ 	sb	$t8,0x8f($sp)
/*  f027e68:	8e300004 */ 	lw	$s0,0x4($s1)
.L0f027e6c:
/*  f027e6c:	8e020018 */ 	lw	$v0,0x18($s0)
/*  f027e70:	50400006 */ 	beqzl	$v0,.L0f027e8c
/*  f027e74:	8e030004 */ 	lw	$v1,0x4($s0)
/*  f027e78:	00408025 */ 	or	$s0,$v0,$zero
.L0f027e7c:
/*  f027e7c:	8c420018 */ 	lw	$v0,0x18($v0)
/*  f027e80:	5440fffe */ 	bnezl	$v0,.L0f027e7c
/*  f027e84:	00408025 */ 	or	$s0,$v0,$zero
/*  f027e88:	8e030004 */ 	lw	$v1,0x4($s0)
.L0f027e8c:
/*  f027e8c:	8fa200f8 */ 	lw	$v0,0xf8($sp)
/*  f027e90:	8c790018 */ 	lw	$t9,0x18($v1)
/*  f027e94:	332a0400 */ 	andi	$t2,$t9,0x400
/*  f027e98:	55400179 */ 	bnezl	$t2,.L0f028480
/*  f027e9c:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f027ea0:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f027ea4:	c446000c */ 	lwc1	$f6,0xc($v0)
/*  f027ea8:	c44a0014 */ 	lwc1	$f10,0x14($v0)
/*  f027eac:	c4520000 */ 	lwc1	$f18,0x0($v0)
/*  f027eb0:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f027eb4:	460a4403 */ 	div.s	$f16,$f8,$f10
/*  f027eb8:	46109101 */ 	sub.s	$f4,$f18,$f16
/*  f027ebc:	e7a40098 */ 	swc1	$f4,0x98($sp)
/*  f027ec0:	c6260000 */ 	lwc1	$f6,0x0($s1)
/*  f027ec4:	c4480010 */ 	lwc1	$f8,0x10($v0)
/*  f027ec8:	c4520014 */ 	lwc1	$f18,0x14($v0)
/*  f027ecc:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*  f027ed0:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f027ed4:	46125403 */ 	div.s	$f16,$f10,$f18
/*  f027ed8:	46102181 */ 	sub.s	$f6,$f4,$f16
/*  f027edc:	e7a6009c */ 	swc1	$f6,0x9c($sp)
/*  f027ee0:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f027ee4:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f027ee8:	afa300f0 */ 	sw	$v1,0xf0($sp)
/*  f027eec:	460a4481 */ 	sub.s	$f18,$f8,$f10
/*  f027ef0:	0fc2d5de */ 	jal	currentPlayerGetUnk174c
/*  f027ef4:	e7b200a0 */ 	swc1	$f18,0xa0($sp)
/*  f027ef8:	00402025 */ 	or	$a0,$v0,$zero
/*  f027efc:	27a50098 */ 	addiu	$a1,$sp,0x98
/*  f027f00:	0c0056da */ 	jal	func00015b68
/*  f027f04:	27a600a4 */ 	addiu	$a2,$sp,0xa4
/*  f027f08:	0fc2a519 */ 	jal	bgunSetHitPos
/*  f027f0c:	27a400a4 */ 	addiu	$a0,$sp,0xa4
/*  f027f10:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f027f14:	8e250004 */ 	lw	$a1,0x4($s1)
/*  f027f18:	0fc29f66 */ 	jal	bgunPlayPropHitSound
/*  f027f1c:	2406ffff */ 	addiu	$a2,$zero,-1
/*  f027f20:	8fa200f8 */ 	lw	$v0,0xf8($sp)
/*  f027f24:	3c0b800a */ 	lui	$t3,%hi(g_Vars+0x284)
/*  f027f28:	8d6ba244 */ 	lw	$t3,%lo(g_Vars+0x284)($t3)
/*  f027f2c:	8e250004 */ 	lw	$a1,0x4($s1)
/*  f027f30:	8e260008 */ 	lw	$a2,0x8($s1)
/*  f027f34:	24420028 */ 	addiu	$v0,$v0,0x28
/*  f027f38:	afa20010 */ 	sw	$v0,0x10($sp)
/*  f027f3c:	8d6c00bc */ 	lw	$t4,0xbc($t3)
/*  f027f40:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f027f44:	27a700a4 */ 	addiu	$a3,$sp,0xa4
/*  f027f48:	8d8d0004 */ 	lw	$t5,0x4($t4)
/*  f027f4c:	afa20044 */ 	sw	$v0,0x44($sp)
/*  f027f50:	0fc097a9 */ 	jal	chrEmitSparks
/*  f027f54:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f027f58:	c6240010 */ 	lwc1	$f4,0x10($s1)
/*  f027f5c:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f027f60:	4600240d */ 	trunc.w.s	$f16,$f4
/*  f027f64:	440f8000 */ 	mfc1	$t7,$f16
/*  f027f68:	00000000 */ 	nop
/*  f027f6c:	a7af0090 */ 	sh	$t7,0x90($sp)
/*  f027f70:	c6260014 */ 	lwc1	$f6,0x14($s1)
/*  f027f74:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f027f78:	44194000 */ 	mfc1	$t9,$f8
/*  f027f7c:	00000000 */ 	nop
/*  f027f80:	a7b90092 */ 	sh	$t9,0x92($sp)
/*  f027f84:	c62a0018 */ 	lwc1	$f10,0x18($s1)
/*  f027f88:	4600548d */ 	trunc.w.s	$f18,$f10
/*  f027f8c:	440b9000 */ 	mfc1	$t3,$f18
/*  f027f90:	0fc0cfe8 */ 	jal	chrGetShield
/*  f027f94:	a7ab0094 */ 	sh	$t3,0x94($sp)
/*  f027f98:	e7a00084 */ 	swc1	$f0,0x84($sp)
/*  f027f9c:	0fc2c74a */ 	jal	gsetGetDamage
/*  f027fa0:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f027fa4:	3c0c800a */ 	lui	$t4,%hi(g_Vars+0x284)
/*  f027fa8:	8d8ca244 */ 	lw	$t4,%lo(g_Vars+0x284)($t4)
/*  f027fac:	44050000 */ 	mfc1	$a1,$f0
/*  f027fb0:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f027fb4:	8d8d00bc */ 	lw	$t5,0xbc($t4)
/*  f027fb8:	27ac0090 */ 	addiu	$t4,$sp,0x90
/*  f027fbc:	8fa60044 */ 	lw	$a2,0x44($sp)
/*  f027fc0:	afad0010 */ 	sw	$t5,0x10($sp)
/*  f027fc4:	8e2e0008 */ 	lw	$t6,0x8($s1)
/*  f027fc8:	8fa70048 */ 	lw	$a3,0x48($sp)
/*  f027fcc:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f027fd0:	8e2f0004 */ 	lw	$t7,0x4($s1)
/*  f027fd4:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f027fd8:	8e38000c */ 	lw	$t8,0xc($s1)
/*  f027fdc:	afb8001c */ 	sw	$t8,0x1c($sp)
/*  f027fe0:	8e390048 */ 	lw	$t9,0x48($s1)
/*  f027fe4:	afb90020 */ 	sw	$t9,0x20($sp)
/*  f027fe8:	862a0038 */ 	lh	$t2,0x38($s1)
/*  f027fec:	afac0028 */ 	sw	$t4,0x28($sp)
/*  f027ff0:	05410003 */ 	bgez	$t2,.L0f028000
/*  f027ff4:	000a5843 */ 	sra	$t3,$t2,0x1
/*  f027ff8:	25410001 */ 	addiu	$at,$t2,0x1
/*  f027ffc:	00015843 */ 	sra	$t3,$at,0x1
.L0f028000:
/*  f028000:	0fc0d077 */ 	jal	func0f0341dc
/*  f028004:	afab0024 */ 	sw	$t3,0x24($sp)
/*  f028008:	3c07800a */ 	lui	$a3,%hi(g_Vars)
/*  f02800c:	24e79fc0 */ 	addiu	$a3,$a3,%lo(g_Vars)
/*  f028010:	8ced029c */ 	lw	$t5,0x29c($a3)
/*  f028014:	05a2000b */ 	bltzl	$t5,.L0f028044
/*  f028018:	8cea0298 */ 	lw	$t2,0x298($a3)
/*  f02801c:	8cee02a8 */ 	lw	$t6,0x2a8($a3)
/*  f028020:	8cef0284 */ 	lw	$t7,0x284($a3)
/*  f028024:	8fa900f0 */ 	lw	$t1,0xf0($sp)
/*  f028028:	55cf0006 */ 	bnel	$t6,$t7,.L0f028044
/*  f02802c:	8cea0298 */ 	lw	$t2,0x298($a3)
/*  f028030:	8d380014 */ 	lw	$t8,0x14($t1)
/*  f028034:	0018c840 */ 	sll	$t9,$t8,0x1
/*  f028038:	07220111 */ 	bltzl	$t9,.L0f028480
/*  f02803c:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f028040:	8cea0298 */ 	lw	$t2,0x298($a3)
.L0f028044:
/*  f028044:	8fa900f0 */ 	lw	$t1,0xf0($sp)
/*  f028048:	3c0d800a */ 	lui	$t5,%hi(g_MissionConfig+0x3)
/*  f02804c:	05400008 */ 	bltz	$t2,.L0f028070
/*  f028050:	00000000 */ 	nop
/*  f028054:	8ceb0454 */ 	lw	$t3,0x454($a3)
/*  f028058:	15600005 */ 	bnez	$t3,.L0f028070
/*  f02805c:	00000000 */ 	nop
/*  f028060:	920c0000 */ 	lbu	$t4,0x0($s0)
/*  f028064:	24010006 */ 	addiu	$at,$zero,0x6
/*  f028068:	51810105 */ 	beql	$t4,$at,.L0f028480
/*  f02806c:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f028070:
/*  f028070:	81aedfeb */ 	lb	$t6,%lo(g_MissionConfig+0x3)($t5)
/*  f028074:	c7b00084 */ 	lwc1	$f16,0x84($sp)
/*  f028078:	05c30009 */ 	bgezl	$t6,.L0f0280a0
/*  f02807c:	44802000 */ 	mtc1	$zero,$f4
/*  f028080:	8cef0454 */ 	lw	$t7,0x454($a3)
/*  f028084:	55e00006 */ 	bnezl	$t7,.L0f0280a0
/*  f028088:	44802000 */ 	mtc1	$zero,$f4
/*  f02808c:	91380125 */ 	lbu	$t8,0x125($t1)
/*  f028090:	24010010 */ 	addiu	$at,$zero,0x10
/*  f028094:	530100fa */ 	beql	$t8,$at,.L0f028480
/*  f028098:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f02809c:	44802000 */ 	mtc1	$zero,$f4
.L0f0280a0:
/*  f0280a0:	00000000 */ 	nop
/*  f0280a4:	4604803e */ 	c.le.s	$f16,$f4
/*  f0280a8:	00000000 */ 	nop
/*  f0280ac:	450200f4 */ 	bc1fl	.L0f028480
/*  f0280b0:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f0280b4:	8e240004 */ 	lw	$a0,0x4($s1)
/*  f0280b8:	24010004 */ 	addiu	$at,$zero,0x4
/*  f0280bc:	90990000 */ 	lbu	$t9,0x0($a0)
/*  f0280c0:	57210070 */ 	bnel	$t9,$at,.L0f028284
/*  f0280c4:	8e2e0008 */ 	lw	$t6,0x8($s1)
/*  f0280c8:	8c900004 */ 	lw	$s0,0x4($a0)
/*  f0280cc:	2401001e */ 	addiu	$at,$zero,0x1e
/*  f0280d0:	9202005c */ 	lbu	$v0,0x5c($s0)
/*  f0280d4:	1041000d */ 	beq	$v0,$at,.L0f02810c
/*  f0280d8:	24010055 */ 	addiu	$at,$zero,0x55
/*  f0280dc:	1041000b */ 	beq	$v0,$at,.L0f02810c
/*  f0280e0:	24010053 */ 	addiu	$at,$zero,0x53
/*  f0280e4:	10410009 */ 	beq	$v0,$at,.L0f02810c
/*  f0280e8:	24010054 */ 	addiu	$at,$zero,0x54
/*  f0280ec:	10410007 */ 	beq	$v0,$at,.L0f02810c
/*  f0280f0:	24010020 */ 	addiu	$at,$zero,0x20
/*  f0280f4:	10410005 */ 	beq	$v0,$at,.L0f02810c
/*  f0280f8:	24010022 */ 	addiu	$at,$zero,0x22
/*  f0280fc:	10410003 */ 	beq	$v0,$at,.L0f02810c
/*  f028100:	24010021 */ 	addiu	$at,$zero,0x21
/*  f028104:	54410015 */ 	bnel	$v0,$at,.L0f02815c
/*  f028108:	8622003a */ 	lh	$v0,0x3a($s1)
.L0f02810c:
/*  f02810c:	0fc20a59 */ 	jal	propobjSetDropped
/*  f028110:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f028114:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f028118:	8d4b0014 */ 	lw	$t3,0x14($t2)
/*  f02811c:	356c0001 */ 	ori	$t4,$t3,0x1
/*  f028120:	ad4c0014 */ 	sw	$t4,0x14($t2)
/*  f028124:	0fc2c74a */ 	jal	gsetGetDamage
/*  f028128:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f02812c:	8fad00f8 */ 	lw	$t5,0xf8($sp)
/*  f028130:	3c0e800a */ 	lui	$t6,%hi(g_Vars+0x28c)
/*  f028134:	8dcea24c */ 	lw	$t6,%lo(g_Vars+0x28c)($t6)
/*  f028138:	44050000 */ 	mfc1	$a1,$f0
/*  f02813c:	91a70018 */ 	lbu	$a3,0x18($t5)
/*  f028140:	02002025 */ 	or	$a0,$s0,$zero
/*  f028144:	27a60098 */ 	addiu	$a2,$sp,0x98
/*  f028148:	0fc214ab */ 	jal	objDamage
/*  f02814c:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f028150:	100000cb */ 	b	.L0f028480
/*  f028154:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f028158:	8622003a */ 	lh	$v0,0x3a($s1)
.L0f02815c:
/*  f02815c:	04400003 */ 	bltz	$v0,.L0f02816c
/*  f028160:	28410daf */ 	slti	$at,$v0,0xdaf
/*  f028164:	14200003 */ 	bnez	$at,.L0f028174
/*  f028168:	3c0f800b */ 	lui	$t7,%hi(g_Textures)
.L0f02816c:
/*  f02816c:	10000007 */ 	b	.L0f02818c
/*  f028170:	00001825 */ 	or	$v1,$zero,$zero
.L0f028174:
/*  f028174:	8defabc0 */ 	lw	$t7,%lo(g_Textures)($t7)
/*  f028178:	0002c0c0 */ 	sll	$t8,$v0,0x3
/*  f02817c:	01f8c821 */ 	addu	$t9,$t7,$t8
/*  f028180:	93230000 */ 	lbu	$v1,0x0($t9)
/*  f028184:	306b000f */ 	andi	$t3,$v1,0xf
/*  f028188:	01601825 */ 	or	$v1,$t3,$zero
.L0f02818c:
/*  f02818c:	0460002b */ 	bltz	$v1,.L0f02823c
/*  f028190:	2861000f */ 	slti	$at,$v1,0xf
/*  f028194:	10200029 */ 	beqz	$at,.L0f02823c
/*  f028198:	00036080 */ 	sll	$t4,$v1,0x2
/*  f02819c:	3c088008 */ 	lui	$t0,%hi(g_SurfaceTypes)
/*  f0281a0:	010c4021 */ 	addu	$t0,$t0,$t4
/*  f0281a4:	8d084458 */ 	lw	$t0,%lo(g_SurfaceTypes)($t0)
/*  f0281a8:	850a000a */ 	lh	$t2,0xa($t0)
/*  f0281ac:	59400024 */ 	blezl	$t2,.L0f028240
/*  f0281b0:	8d2f02d4 */ 	lw	$t7,0x2d4($t1)
/*  f0281b4:	0c004b70 */ 	jal	random
/*  f0281b8:	afa8007c */ 	sw	$t0,0x7c($sp)
/*  f0281bc:	8fa8007c */ 	lw	$t0,0x7c($sp)
/*  f0281c0:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f0281c4:	3c0a800a */ 	lui	$t2,%hi(g_Vars+0x284)
/*  f0281c8:	850d000a */ 	lh	$t5,0xa($t0)
/*  f0281cc:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f0281d0:	8d0e0004 */ 	lw	$t6,0x4($t0)
/*  f0281d4:	004d001b */ 	divu	$zero,$v0,$t5
/*  f0281d8:	00001810 */ 	mfhi	$v1
/*  f0281dc:	01c37821 */ 	addu	$t7,$t6,$v1
/*  f0281e0:	91f80000 */ 	lbu	$t8,0x0($t7)
/*  f0281e4:	afb90018 */ 	sw	$t9,0x18($sp)
/*  f0281e8:	8d4aa244 */ 	lw	$t2,%lo(g_Vars+0x284)($t2)
/*  f0281ec:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f0281f0:	8e2b0004 */ 	lw	$t3,0x4($s1)
/*  f0281f4:	15a00002 */ 	bnez	$t5,.L0f028200
/*  f0281f8:	00000000 */ 	nop
/*  f0281fc:	0007000d */ 	break	0x7
.L0f028200:
/*  f028200:	afab001c */ 	sw	$t3,0x1c($sp)
/*  f028204:	8e2c0040 */ 	lw	$t4,0x40($s1)
/*  f028208:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f02820c:	8fa600f8 */ 	lw	$a2,0xf8($sp)
/*  f028210:	afac0020 */ 	sw	$t4,0x20($sp)
/*  f028214:	8d4d00bc */ 	lw	$t5,0xbc($t2)
/*  f028218:	26240010 */ 	addiu	$a0,$s1,0x10
/*  f02821c:	2625001c */ 	addiu	$a1,$s1,0x1c
/*  f028220:	8dae0004 */ 	lw	$t6,0x4($t5)
/*  f028224:	afa0002c */ 	sw	$zero,0x2c($sp)
/*  f028228:	00003825 */ 	or	$a3,$zero,$zero
/*  f02822c:	24c6001c */ 	addiu	$a2,$a2,0x1c
/*  f028230:	0fc4fcfd */ 	jal	func0f13f3f4
/*  f028234:	afae0028 */ 	sw	$t6,0x28($sp)
/*  f028238:	8fa900f0 */ 	lw	$t1,0xf0($sp)
.L0f02823c:
/*  f02823c:	8d2f02d4 */ 	lw	$t7,0x2d4($t1)
.L0f028240:
/*  f028240:	55e0008f */ 	bnezl	$t7,.L0f028480
/*  f028244:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f028248:	8d380114 */ 	lw	$t8,0x114($t1)
/*  f02824c:	0018c800 */ 	sll	$t9,$t8,0x0
/*  f028250:	0723008b */ 	bgezl	$t9,.L0f028480
/*  f028254:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f028258:	8e2b0004 */ 	lw	$t3,0x4($s1)
/*  f02825c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f028260:	ad2b0300 */ 	sw	$t3,0x300($t1)
/*  f028264:	0fc20a59 */ 	jal	propobjSetDropped
/*  f028268:	8e240004 */ 	lw	$a0,0x4($s1)
/*  f02826c:	8fac00f0 */ 	lw	$t4,0xf0($sp)
/*  f028270:	8d8a0014 */ 	lw	$t2,0x14($t4)
/*  f028274:	354d0001 */ 	ori	$t5,$t2,0x1
/*  f028278:	10000080 */ 	b	.L0f02847c
/*  f02827c:	ad8d0014 */ 	sw	$t5,0x14($t4)
/*  f028280:	8e2e0008 */ 	lw	$t6,0x8($s1)
.L0f028284:
/*  f028284:	2401006e */ 	addiu	$at,$zero,0x6e
/*  f028288:	00003025 */ 	or	$a2,$zero,$zero
/*  f02828c:	15c10035 */ 	bne	$t6,$at,.L0f028364
/*  f028290:	00000000 */ 	nop
/*  f028294:	8622003a */ 	lh	$v0,0x3a($s1)
/*  f028298:	3c038008 */ 	lui	$v1,%hi(g_SurfaceTypes)
/*  f02829c:	3c0f800b */ 	lui	$t7,%hi(g_Textures)
/*  f0282a0:	04410003 */ 	bgez	$v0,.L0f0282b0
/*  f0282a4:	00000000 */ 	nop
/*  f0282a8:	1000000a */ 	b	.L0f0282d4
/*  f0282ac:	8c634458 */ 	lw	$v1,%lo(g_SurfaceTypes)($v1)
.L0f0282b0:
/*  f0282b0:	8defabc0 */ 	lw	$t7,%lo(g_Textures)($t7)
/*  f0282b4:	0002c0c0 */ 	sll	$t8,$v0,0x3
/*  f0282b8:	3c038008 */ 	lui	$v1,%hi(g_SurfaceTypes)
/*  f0282bc:	01f8c821 */ 	addu	$t9,$t7,$t8
/*  f0282c0:	932b0000 */ 	lbu	$t3,0x0($t9)
/*  f0282c4:	316a000f */ 	andi	$t2,$t3,0xf
/*  f0282c8:	000a6880 */ 	sll	$t5,$t2,0x2
/*  f0282cc:	006d1821 */ 	addu	$v1,$v1,$t5
/*  f0282d0:	8c634458 */ 	lw	$v1,%lo(g_SurfaceTypes)($v1)
.L0f0282d4:
/*  f0282d4:	0c004b70 */ 	jal	random
/*  f0282d8:	afa30070 */ 	sw	$v1,0x70($sp)
/*  f0282dc:	8fa30070 */ 	lw	$v1,0x70($sp)
/*  f0282e0:	8fab00f0 */ 	lw	$t3,0xf0($sp)
/*  f0282e4:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f0282e8:	846c000a */ 	lh	$t4,0xa($v1)
/*  f0282ec:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f0282f0:	8c6e0004 */ 	lw	$t6,0x4($v1)
/*  f0282f4:	004c001b */ 	divu	$zero,$v0,$t4
/*  f0282f8:	00004010 */ 	mfhi	$t0
/*  f0282fc:	01c87821 */ 	addu	$t7,$t6,$t0
/*  f028300:	91f80000 */ 	lbu	$t8,0x0($t7)
/*  f028304:	afb90018 */ 	sw	$t9,0x18($sp)
/*  f028308:	15800002 */ 	bnez	$t4,.L0f028314
/*  f02830c:	00000000 */ 	nop
/*  f028310:	0007000d */ 	break	0x7
.L0f028314:
/*  f028314:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f028318:	8d6a0178 */ 	lw	$t2,0x178($t3)
/*  f02831c:	3c0c800a */ 	lui	$t4,%hi(g_Vars+0x284)
/*  f028320:	8d8ca244 */ 	lw	$t4,%lo(g_Vars+0x284)($t4)
/*  f028324:	afaa001c */ 	sw	$t2,0x1c($sp)
/*  f028328:	8e2d0040 */ 	lw	$t5,0x40($s1)
/*  f02832c:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f028330:	8fa600f8 */ 	lw	$a2,0xf8($sp)
/*  f028334:	afad0020 */ 	sw	$t5,0x20($sp)
/*  f028338:	8d8e00bc */ 	lw	$t6,0xbc($t4)
/*  f02833c:	26240010 */ 	addiu	$a0,$s1,0x10
/*  f028340:	2625001c */ 	addiu	$a1,$s1,0x1c
/*  f028344:	8dcf0004 */ 	lw	$t7,0x4($t6)
/*  f028348:	afa0002c */ 	sw	$zero,0x2c($sp)
/*  f02834c:	00003825 */ 	or	$a3,$zero,$zero
/*  f028350:	24c6001c */ 	addiu	$a2,$a2,0x1c
/*  f028354:	0fc4fcfd */ 	jal	func0f13f3f4
/*  f028358:	afaf0028 */ 	sw	$t7,0x28($sp)
/*  f02835c:	10000048 */ 	b	.L0f028480
/*  f028360:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f028364:
/*  f028364:	11200003 */ 	beqz	$t1,.L0f028374
/*  f028368:	00001825 */ 	or	$v1,$zero,$zero
/*  f02836c:	10000001 */ 	b	.L0f028374
/*  f028370:	912302fe */ 	lbu	$v1,0x2fe($t1)
.L0f028374:
/*  f028374:	8e240048 */ 	lw	$a0,0x48($s1)
/*  f028378:	8e25000c */ 	lw	$a1,0xc($s1)
/*  f02837c:	0c006973 */ 	jal	func0001a5cc
/*  f028380:	afa30068 */ 	sw	$v1,0x68($sp)
/*  f028384:	00402025 */ 	or	$a0,$v0,$zero
/*  f028388:	0c005c67 */ 	jal	func0001719c
/*  f02838c:	27a500b0 */ 	addiu	$a1,$sp,0xb0
/*  f028390:	27a400b0 */ 	addiu	$a0,$sp,0xb0
/*  f028394:	27a50098 */ 	addiu	$a1,$sp,0x98
/*  f028398:	0c0056da */ 	jal	func00015b68
/*  f02839c:	27a6005c */ 	addiu	$a2,$sp,0x5c
/*  f0283a0:	8fb800f0 */ 	lw	$t8,0xf0($sp)
/*  f0283a4:	8fa30068 */ 	lw	$v1,0x68($sp)
/*  f0283a8:	24010002 */ 	addiu	$at,$zero,0x2
/*  f0283ac:	8f19032c */ 	lw	$t9,0x32c($t8)
/*  f0283b0:	001954c0 */ 	sll	$t2,$t9,0x13
/*  f0283b4:	05420032 */ 	bltzl	$t2,.L0f028480
/*  f0283b8:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f0283bc:	1061002f */ 	beq	$v1,$at,.L0f02847c
/*  f0283c0:	24010004 */ 	addiu	$at,$zero,0x4
/*  f0283c4:	1061002d */ 	beq	$v1,$at,.L0f02847c
/*  f0283c8:	24010003 */ 	addiu	$at,$zero,0x3
/*  f0283cc:	1061002b */ 	beq	$v1,$at,.L0f02847c
/*  f0283d0:	93ad008f */ 	lbu	$t5,0x8f($sp)
/*  f0283d4:	15a00029 */ 	bnez	$t5,.L0f02847c
/*  f0283d8:	8fac00f8 */ 	lw	$t4,0xf8($sp)
/*  f0283dc:	918e0018 */ 	lbu	$t6,0x18($t4)
/*  f0283e0:	2401001c */ 	addiu	$at,$zero,0x1c
/*  f0283e4:	3c19800a */ 	lui	$t9,%hi(g_Vars+0x284)
/*  f0283e8:	51c10025 */ 	beql	$t6,$at,.L0f028480
/*  f0283ec:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f0283f0:	870f0010 */ 	lh	$t7,0x10($t8)
/*  f0283f4:	2401005b */ 	addiu	$at,$zero,0x5b
/*  f0283f8:	11e10003 */ 	beq	$t7,$at,.L0f028408
/*  f0283fc:	24010001 */ 	addiu	$at,$zero,0x1
/*  f028400:	54610004 */ 	bnel	$v1,$at,.L0f028414
/*  f028404:	00001825 */ 	or	$v1,$zero,$zero
.L0f028408:
/*  f028408:	10000002 */ 	b	.L0f028414
/*  f02840c:	24030001 */ 	addiu	$v1,$zero,0x1
/*  f028410:	00001825 */ 	or	$v1,$zero,$zero
.L0f028414:
/*  f028414:	8f39a244 */ 	lw	$t9,%lo(g_Vars+0x284)($t9)
/*  f028418:	8f2b00bc */ 	lw	$t3,0xbc($t9)
/*  f02841c:	8d640004 */ 	lw	$a0,0x4($t3)
/*  f028420:	0fc4f92a */ 	jal	chrIsUsingPaintball
/*  f028424:	a3a30057 */ 	sb	$v1,0x57($sp)
/*  f028428:	14400008 */ 	bnez	$v0,.L0f02844c
/*  f02842c:	93a30057 */ 	lbu	$v1,0x57($sp)
/*  f028430:	8e240048 */ 	lw	$a0,0x48($s1)
/*  f028434:	8e250008 */ 	lw	$a1,0x8($s1)
/*  f028438:	8e26000c */ 	lw	$a2,0xc($s1)
/*  f02843c:	a3a30057 */ 	sb	$v1,0x57($sp)
/*  f028440:	0fc09a2f */ 	jal	func0f0268bc
/*  f028444:	27a7005c */ 	addiu	$a3,$sp,0x5c
/*  f028448:	93a30057 */ 	lbu	$v1,0x57($sp)
.L0f02844c:
/*  f02844c:	3c0a800a */ 	lui	$t2,%hi(g_Vars+0x284)
/*  f028450:	8d4aa244 */ 	lw	$t2,%lo(g_Vars+0x284)($t2)
/*  f028454:	afa30010 */ 	sw	$v1,0x10($sp)
/*  f028458:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f02845c:	8d4d00bc */ 	lw	$t5,0xbc($t2)
/*  f028460:	02002025 */ 	or	$a0,$s0,$zero
/*  f028464:	8fa500f8 */ 	lw	$a1,0xf8($sp)
/*  f028468:	8dac0004 */ 	lw	$t4,0x4($t5)
/*  f02846c:	27a60098 */ 	addiu	$a2,$sp,0x98
/*  f028470:	27a700a4 */ 	addiu	$a3,$sp,0xa4
/*  f028474:	0fc52395 */ 	jal	func0f148e54
/*  f028478:	afac0018 */ 	sw	$t4,0x18($sp)
.L0f02847c:
/*  f02847c:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f028480:
/*  f028480:	8fb00034 */ 	lw	$s0,0x34($sp)
/*  f028484:	8fb10038 */ 	lw	$s1,0x38($sp)
/*  f028488:	03e00008 */ 	jr	$ra
/*  f02848c:	27bd00f8 */ 	addiu	$sp,$sp,0xf8
);
#else
GLOBAL_ASM(
glabel func0f027e1c
/*  f027838:	27bdff08 */ 	addiu	$sp,$sp,-248
/*  f02783c:	afa400f8 */ 	sw	$a0,0xf8($sp)
/*  f027840:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f027844:	afb10038 */ 	sw	$s1,0x38($sp)
/*  f027848:	24840018 */ 	addiu	$a0,$a0,0x18
/*  f02784c:	00a08825 */ 	or	$s1,$a1,$zero
/*  f027850:	afb00034 */ 	sw	$s0,0x34($sp)
/*  f027854:	a3a0008f */ 	sb	$zero,0x8f($sp)
/*  f027858:	0fc2bb77 */ 	jal	gsetGetWeaponFunction
/*  f02785c:	afa40048 */ 	sw	$a0,0x48($sp)
/*  f027860:	50400009 */ 	beqzl	$v0,.NB0f027888
/*  f027864:	8e300004 */ 	lw	$s0,0x4($s1)
/*  f027868:	8c4e0000 */ 	lw	$t6,0x0($v0)
/*  f02786c:	24010003 */ 	addiu	$at,$zero,0x3
/*  f027870:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f027874:	31cf00ff */ 	andi	$t7,$t6,0xff
/*  f027878:	55e10003 */ 	bnel	$t7,$at,.NB0f027888
/*  f02787c:	8e300004 */ 	lw	$s0,0x4($s1)
/*  f027880:	a3b8008f */ 	sb	$t8,0x8f($sp)
/*  f027884:	8e300004 */ 	lw	$s0,0x4($s1)
.NB0f027888:
/*  f027888:	8e020018 */ 	lw	$v0,0x18($s0)
/*  f02788c:	50400006 */ 	beqzl	$v0,.NB0f0278a8
/*  f027890:	8e030004 */ 	lw	$v1,0x4($s0)
/*  f027894:	00408025 */ 	or	$s0,$v0,$zero
.NB0f027898:
/*  f027898:	8c420018 */ 	lw	$v0,0x18($v0)
/*  f02789c:	5440fffe */ 	bnezl	$v0,.NB0f027898
/*  f0278a0:	00408025 */ 	or	$s0,$v0,$zero
/*  f0278a4:	8e030004 */ 	lw	$v1,0x4($s0)
.NB0f0278a8:
/*  f0278a8:	8fa200f8 */ 	lw	$v0,0xf8($sp)
/*  f0278ac:	8c790018 */ 	lw	$t9,0x18($v1)
/*  f0278b0:	33290400 */ 	andi	$t1,$t9,0x400
/*  f0278b4:	55200174 */ 	bnezl	$t1,.NB0f027e88
/*  f0278b8:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f0278bc:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f0278c0:	c446000c */ 	lwc1	$f6,0xc($v0)
/*  f0278c4:	c44a0014 */ 	lwc1	$f10,0x14($v0)
/*  f0278c8:	c4520000 */ 	lwc1	$f18,0x0($v0)
/*  f0278cc:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f0278d0:	460a4403 */ 	div.s	$f16,$f8,$f10
/*  f0278d4:	46109101 */ 	sub.s	$f4,$f18,$f16
/*  f0278d8:	e7a40098 */ 	swc1	$f4,0x98($sp)
/*  f0278dc:	c6260000 */ 	lwc1	$f6,0x0($s1)
/*  f0278e0:	c4480010 */ 	lwc1	$f8,0x10($v0)
/*  f0278e4:	c4520014 */ 	lwc1	$f18,0x14($v0)
/*  f0278e8:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*  f0278ec:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f0278f0:	46125403 */ 	div.s	$f16,$f10,$f18
/*  f0278f4:	46102181 */ 	sub.s	$f6,$f4,$f16
/*  f0278f8:	e7a6009c */ 	swc1	$f6,0x9c($sp)
/*  f0278fc:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f027900:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f027904:	afa300f0 */ 	sw	$v1,0xf0($sp)
/*  f027908:	460a4481 */ 	sub.s	$f18,$f8,$f10
/*  f02790c:	0fc2cd36 */ 	jal	currentPlayerGetUnk174c
/*  f027910:	e7b200a0 */ 	swc1	$f18,0xa0($sp)
/*  f027914:	00402025 */ 	or	$a0,$v0,$zero
/*  f027918:	27a50098 */ 	addiu	$a1,$sp,0x98
/*  f02791c:	0c005a96 */ 	jal	func00015b68
/*  f027920:	27a600a4 */ 	addiu	$a2,$sp,0xa4
/*  f027924:	0fc29c81 */ 	jal	bgunSetHitPos
/*  f027928:	27a400a4 */ 	addiu	$a0,$sp,0xa4
/*  f02792c:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f027930:	8e250004 */ 	lw	$a1,0x4($s1)
/*  f027934:	0fc296b1 */ 	jal	bgunPlayPropHitSound
/*  f027938:	2406ffff */ 	addiu	$a2,$zero,-1
/*  f02793c:	8fa200f8 */ 	lw	$v0,0xf8($sp)
/*  f027940:	3c0a800a */ 	lui	$t2,0x800a
/*  f027944:	8d4ae944 */ 	lw	$t2,-0x16bc($t2)
/*  f027948:	8e250004 */ 	lw	$a1,0x4($s1)
/*  f02794c:	8e260008 */ 	lw	$a2,0x8($s1)
/*  f027950:	24420028 */ 	addiu	$v0,$v0,0x28
/*  f027954:	afa20010 */ 	sw	$v0,0x10($sp)
/*  f027958:	8d4b00bc */ 	lw	$t3,0xbc($t2)
/*  f02795c:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f027960:	27a700a4 */ 	addiu	$a3,$sp,0xa4
/*  f027964:	8d6c0004 */ 	lw	$t4,0x4($t3)
/*  f027968:	afa20044 */ 	sw	$v0,0x44($sp)
/*  f02796c:	0fc09630 */ 	jal	chrEmitSparks
/*  f027970:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f027974:	c6240010 */ 	lwc1	$f4,0x10($s1)
/*  f027978:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f02797c:	4600240d */ 	trunc.w.s	$f16,$f4
/*  f027980:	440e8000 */ 	mfc1	$t6,$f16
/*  f027984:	00000000 */ 	sll	$zero,$zero,0x0
/*  f027988:	a7ae0090 */ 	sh	$t6,0x90($sp)
/*  f02798c:	c6260014 */ 	lwc1	$f6,0x14($s1)
/*  f027990:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f027994:	44184000 */ 	mfc1	$t8,$f8
/*  f027998:	00000000 */ 	sll	$zero,$zero,0x0
/*  f02799c:	a7b80092 */ 	sh	$t8,0x92($sp)
/*  f0279a0:	c62a0018 */ 	lwc1	$f10,0x18($s1)
/*  f0279a4:	4600548d */ 	trunc.w.s	$f18,$f10
/*  f0279a8:	44099000 */ 	mfc1	$t1,$f18
/*  f0279ac:	0fc0ce2a */ 	jal	chrGetShield
/*  f0279b0:	a7a90094 */ 	sh	$t1,0x94($sp)
/*  f0279b4:	e7a00084 */ 	swc1	$f0,0x84($sp)
/*  f0279b8:	0fc2bea2 */ 	jal	gsetGetDamage
/*  f0279bc:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f0279c0:	3c0a800a */ 	lui	$t2,0x800a
/*  f0279c4:	8d4ae944 */ 	lw	$t2,-0x16bc($t2)
/*  f0279c8:	44050000 */ 	mfc1	$a1,$f0
/*  f0279cc:	27a90090 */ 	addiu	$t1,$sp,0x90
/*  f0279d0:	8d4b00bc */ 	lw	$t3,0xbc($t2)
/*  f0279d4:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f0279d8:	8fa60044 */ 	lw	$a2,0x44($sp)
/*  f0279dc:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f0279e0:	8e2c0008 */ 	lw	$t4,0x8($s1)
/*  f0279e4:	8fa70048 */ 	lw	$a3,0x48($sp)
/*  f0279e8:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f0279ec:	8e2d0004 */ 	lw	$t5,0x4($s1)
/*  f0279f0:	afad0018 */ 	sw	$t5,0x18($sp)
/*  f0279f4:	8e2e000c */ 	lw	$t6,0xc($s1)
/*  f0279f8:	afae001c */ 	sw	$t6,0x1c($sp)
/*  f0279fc:	8e2f0048 */ 	lw	$t7,0x48($s1)
/*  f027a00:	afaf0020 */ 	sw	$t7,0x20($sp)
/*  f027a04:	86380038 */ 	lh	$t8,0x38($s1)
/*  f027a08:	afa90028 */ 	sw	$t1,0x28($sp)
/*  f027a0c:	07010003 */ 	bgez	$t8,.NB0f027a1c
/*  f027a10:	0018c843 */ 	sra	$t9,$t8,0x1
/*  f027a14:	27010001 */ 	addiu	$at,$t8,0x1
/*  f027a18:	0001c843 */ 	sra	$t9,$at,0x1
.NB0f027a1c:
/*  f027a1c:	0fc0ceb9 */ 	jal	func0f0341dc
/*  f027a20:	afb90024 */ 	sw	$t9,0x24($sp)
/*  f027a24:	3c07800a */ 	lui	$a3,0x800a
/*  f027a28:	24e7e6c0 */ 	addiu	$a3,$a3,-6464
/*  f027a2c:	8cea029c */ 	lw	$t2,0x29c($a3)
/*  f027a30:	0542000b */ 	bltzl	$t2,.NB0f027a60
/*  f027a34:	8cef0298 */ 	lw	$t7,0x298($a3)
/*  f027a38:	8ceb02a8 */ 	lw	$t3,0x2a8($a3)
/*  f027a3c:	8cec0284 */ 	lw	$t4,0x284($a3)
/*  f027a40:	8fa800f0 */ 	lw	$t0,0xf0($sp)
/*  f027a44:	556c0006 */ 	bnel	$t3,$t4,.NB0f027a60
/*  f027a48:	8cef0298 */ 	lw	$t7,0x298($a3)
/*  f027a4c:	8d0d0014 */ 	lw	$t5,0x14($t0)
/*  f027a50:	000d7040 */ 	sll	$t6,$t5,0x1
/*  f027a54:	05c2010c */ 	bltzl	$t6,.NB0f027e88
/*  f027a58:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f027a5c:	8cef0298 */ 	lw	$t7,0x298($a3)
.NB0f027a60:
/*  f027a60:	8fa800f0 */ 	lw	$t0,0xf0($sp)
/*  f027a64:	3c09800a */ 	lui	$t1,0x800a
/*  f027a68:	05e00008 */ 	bltz	$t7,.NB0f027a8c
/*  f027a6c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f027a70:	8cf80454 */ 	lw	$t8,0x454($a3)
/*  f027a74:	17000005 */ 	bnez	$t8,.NB0f027a8c
/*  f027a78:	00000000 */ 	sll	$zero,$zero,0x0
/*  f027a7c:	92190000 */ 	lbu	$t9,0x0($s0)
/*  f027a80:	24010006 */ 	addiu	$at,$zero,0x6
/*  f027a84:	53210100 */ 	beql	$t9,$at,.NB0f027e88
/*  f027a88:	8fbf003c */ 	lw	$ra,0x3c($sp)
.NB0f027a8c:
/*  f027a8c:	812a27ab */ 	lb	$t2,0x27ab($t1)
/*  f027a90:	c7b00084 */ 	lwc1	$f16,0x84($sp)
/*  f027a94:	05430009 */ 	bgezl	$t2,.NB0f027abc
/*  f027a98:	44802000 */ 	mtc1	$zero,$f4
/*  f027a9c:	8ceb0454 */ 	lw	$t3,0x454($a3)
/*  f027aa0:	55600006 */ 	bnezl	$t3,.NB0f027abc
/*  f027aa4:	44802000 */ 	mtc1	$zero,$f4
/*  f027aa8:	910c0125 */ 	lbu	$t4,0x125($t0)
/*  f027aac:	24010010 */ 	addiu	$at,$zero,0x10
/*  f027ab0:	518100f5 */ 	beql	$t4,$at,.NB0f027e88
/*  f027ab4:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f027ab8:	44802000 */ 	mtc1	$zero,$f4
.NB0f027abc:
/*  f027abc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f027ac0:	4604803e */ 	c.le.s	$f16,$f4
/*  f027ac4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f027ac8:	450200ef */ 	bc1fl	.NB0f027e88
/*  f027acc:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f027ad0:	8e240004 */ 	lw	$a0,0x4($s1)
/*  f027ad4:	24010004 */ 	addiu	$at,$zero,0x4
/*  f027ad8:	908d0000 */ 	lbu	$t5,0x0($a0)
/*  f027adc:	55a1006f */ 	bnel	$t5,$at,.NB0f027c9c
/*  f027ae0:	8e380008 */ 	lw	$t8,0x8($s1)
/*  f027ae4:	8c900004 */ 	lw	$s0,0x4($a0)
/*  f027ae8:	2401001e */ 	addiu	$at,$zero,0x1e
/*  f027aec:	9202005c */ 	lbu	$v0,0x5c($s0)
/*  f027af0:	1041000d */ 	beq	$v0,$at,.NB0f027b28
/*  f027af4:	24010054 */ 	addiu	$at,$zero,0x54
/*  f027af8:	1041000b */ 	beq	$v0,$at,.NB0f027b28
/*  f027afc:	24010052 */ 	addiu	$at,$zero,0x52
/*  f027b00:	10410009 */ 	beq	$v0,$at,.NB0f027b28
/*  f027b04:	24010053 */ 	addiu	$at,$zero,0x53
/*  f027b08:	10410007 */ 	beq	$v0,$at,.NB0f027b28
/*  f027b0c:	24010020 */ 	addiu	$at,$zero,0x20
/*  f027b10:	10410005 */ 	beq	$v0,$at,.NB0f027b28
/*  f027b14:	24010022 */ 	addiu	$at,$zero,0x22
/*  f027b18:	10410003 */ 	beq	$v0,$at,.NB0f027b28
/*  f027b1c:	24010021 */ 	addiu	$at,$zero,0x21
/*  f027b20:	54410015 */ 	bnel	$v0,$at,.NB0f027b78
/*  f027b24:	8622003a */ 	lh	$v0,0x3a($s1)
.NB0f027b28:
/*  f027b28:	0fc204f7 */ 	jal	propobjSetDropped
/*  f027b2c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f027b30:	8fae00f0 */ 	lw	$t6,0xf0($sp)
/*  f027b34:	8dcf0014 */ 	lw	$t7,0x14($t6)
/*  f027b38:	35f80001 */ 	ori	$t8,$t7,0x1
/*  f027b3c:	add80014 */ 	sw	$t8,0x14($t6)
/*  f027b40:	0fc2bea2 */ 	jal	gsetGetDamage
/*  f027b44:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f027b48:	8fb900f8 */ 	lw	$t9,0xf8($sp)
/*  f027b4c:	3c09800a */ 	lui	$t1,0x800a
/*  f027b50:	8d29e94c */ 	lw	$t1,-0x16b4($t1)
/*  f027b54:	44050000 */ 	mfc1	$a1,$f0
/*  f027b58:	93270018 */ 	lbu	$a3,0x18($t9)
/*  f027b5c:	02002025 */ 	or	$a0,$s0,$zero
/*  f027b60:	27a60098 */ 	addiu	$a2,$sp,0x98
/*  f027b64:	0fc20ecc */ 	jal	objDamage
/*  f027b68:	afa90010 */ 	sw	$t1,0x10($sp)
/*  f027b6c:	100000c6 */ 	beqz	$zero,.NB0f027e88
/*  f027b70:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f027b74:	8622003a */ 	lh	$v0,0x3a($s1)
.NB0f027b78:
/*  f027b78:	04400003 */ 	bltz	$v0,.NB0f027b88
/*  f027b7c:	28410daf */ 	slti	$at,$v0,0xdaf
/*  f027b80:	14200003 */ 	bnez	$at,.NB0f027b90
/*  f027b84:	3c0a800b */ 	lui	$t2,0x800b
.NB0f027b88:
/*  f027b88:	10000007 */ 	beqz	$zero,.NB0f027ba8
/*  f027b8c:	00001825 */ 	or	$v1,$zero,$zero
.NB0f027b90:
/*  f027b90:	8d4af470 */ 	lw	$t2,-0xb90($t2)
/*  f027b94:	000258c0 */ 	sll	$t3,$v0,0x3
/*  f027b98:	014b6021 */ 	addu	$t4,$t2,$t3
/*  f027b9c:	91830000 */ 	lbu	$v1,0x0($t4)
/*  f027ba0:	306d000f */ 	andi	$t5,$v1,0xf
/*  f027ba4:	01a01825 */ 	or	$v1,$t5,$zero
.NB0f027ba8:
/*  f027ba8:	0460002a */ 	bltz	$v1,.NB0f027c54
/*  f027bac:	2861000f */ 	slti	$at,$v1,0xf
/*  f027bb0:	10200028 */ 	beqz	$at,.NB0f027c54
/*  f027bb4:	00037880 */ 	sll	$t7,$v1,0x2
/*  f027bb8:	3c108008 */ 	lui	$s0,0x8008
/*  f027bbc:	020f8021 */ 	addu	$s0,$s0,$t7
/*  f027bc0:	8e106cd8 */ 	lw	$s0,0x6cd8($s0)
/*  f027bc4:	8618000a */ 	lh	$t8,0xa($s0)
/*  f027bc8:	5b000023 */ 	blezl	$t8,.NB0f027c58
/*  f027bcc:	8d1902d4 */ 	lw	$t9,0x2d4($t0)
/*  f027bd0:	0c004d84 */ 	jal	random
/*  f027bd4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f027bd8:	860e000a */ 	lh	$t6,0xa($s0)
/*  f027bdc:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f027be0:	8e190004 */ 	lw	$t9,0x4($s0)
/*  f027be4:	004e001b */ 	divu	$zero,$v0,$t6
/*  f027be8:	00001810 */ 	mfhi	$v1
/*  f027bec:	03234821 */ 	addu	$t1,$t9,$v1
/*  f027bf0:	912a0000 */ 	lbu	$t2,0x0($t1)
/*  f027bf4:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f027bf8:	afab0018 */ 	sw	$t3,0x18($sp)
/*  f027bfc:	afaa0014 */ 	sw	$t2,0x14($sp)
/*  f027c00:	8e2c0004 */ 	lw	$t4,0x4($s1)
/*  f027c04:	3c0f800a */ 	lui	$t7,0x800a
/*  f027c08:	8defe944 */ 	lw	$t7,-0x16bc($t7)
/*  f027c0c:	afac001c */ 	sw	$t4,0x1c($sp)
/*  f027c10:	8e2d0040 */ 	lw	$t5,0x40($s1)
/*  f027c14:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f027c18:	15c00002 */ 	bnez	$t6,.NB0f027c24
/*  f027c1c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f027c20:	0007000d */ 	break	0x7
.NB0f027c24:
/*  f027c24:	afad0020 */ 	sw	$t5,0x20($sp)
/*  f027c28:	8df800bc */ 	lw	$t8,0xbc($t7)
/*  f027c2c:	8fa600f8 */ 	lw	$a2,0xf8($sp)
/*  f027c30:	26240010 */ 	addiu	$a0,$s1,0x10
/*  f027c34:	8f0e0004 */ 	lw	$t6,0x4($t8)
/*  f027c38:	afa0002c */ 	sw	$zero,0x2c($sp)
/*  f027c3c:	2625001c */ 	addiu	$a1,$s1,0x1c
/*  f027c40:	00003825 */ 	or	$a3,$zero,$zero
/*  f027c44:	24c6001c */ 	addiu	$a2,$a2,0x1c
/*  f027c48:	0fc4e7bd */ 	jal	func0f13f3f4
/*  f027c4c:	afae0028 */ 	sw	$t6,0x28($sp)
/*  f027c50:	8fa800f0 */ 	lw	$t0,0xf0($sp)
.NB0f027c54:
/*  f027c54:	8d1902d4 */ 	lw	$t9,0x2d4($t0)
.NB0f027c58:
/*  f027c58:	5720008b */ 	bnezl	$t9,.NB0f027e88
/*  f027c5c:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f027c60:	8d090114 */ 	lw	$t1,0x114($t0)
/*  f027c64:	00095000 */ 	sll	$t2,$t1,0x0
/*  f027c68:	05430087 */ 	bgezl	$t2,.NB0f027e88
/*  f027c6c:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f027c70:	8e2b0004 */ 	lw	$t3,0x4($s1)
/*  f027c74:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f027c78:	ad0b0300 */ 	sw	$t3,0x300($t0)
/*  f027c7c:	0fc204f7 */ 	jal	propobjSetDropped
/*  f027c80:	8e240004 */ 	lw	$a0,0x4($s1)
/*  f027c84:	8fac00f0 */ 	lw	$t4,0xf0($sp)
/*  f027c88:	8d8d0014 */ 	lw	$t5,0x14($t4)
/*  f027c8c:	35af0001 */ 	ori	$t7,$t5,0x1
/*  f027c90:	1000007c */ 	beqz	$zero,.NB0f027e84
/*  f027c94:	ad8f0014 */ 	sw	$t7,0x14($t4)
/*  f027c98:	8e380008 */ 	lw	$t8,0x8($s1)
.NB0f027c9c:
/*  f027c9c:	2401006e */ 	addiu	$at,$zero,0x6e
/*  f027ca0:	00003025 */ 	or	$a2,$zero,$zero
/*  f027ca4:	17010034 */ 	bne	$t8,$at,.NB0f027d78
/*  f027ca8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f027cac:	8622003a */ 	lh	$v0,0x3a($s1)
/*  f027cb0:	3c108008 */ 	lui	$s0,0x8008
/*  f027cb4:	3c0e800b */ 	lui	$t6,0x800b
/*  f027cb8:	04410003 */ 	bgez	$v0,.NB0f027cc8
/*  f027cbc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f027cc0:	1000000a */ 	beqz	$zero,.NB0f027cec
/*  f027cc4:	8e106cd8 */ 	lw	$s0,0x6cd8($s0)
.NB0f027cc8:
/*  f027cc8:	8dcef470 */ 	lw	$t6,-0xb90($t6)
/*  f027ccc:	0002c8c0 */ 	sll	$t9,$v0,0x3
/*  f027cd0:	3c108008 */ 	lui	$s0,0x8008
/*  f027cd4:	01d94821 */ 	addu	$t1,$t6,$t9
/*  f027cd8:	912a0000 */ 	lbu	$t2,0x0($t1)
/*  f027cdc:	314b000f */ 	andi	$t3,$t2,0xf
/*  f027ce0:	000b6880 */ 	sll	$t5,$t3,0x2
/*  f027ce4:	020d8021 */ 	addu	$s0,$s0,$t5
/*  f027ce8:	8e106cd8 */ 	lw	$s0,0x6cd8($s0)
.NB0f027cec:
/*  f027cec:	0c004d84 */ 	jal	random
/*  f027cf0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f027cf4:	860f000a */ 	lh	$t7,0xa($s0)
/*  f027cf8:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f027cfc:	8e0c0004 */ 	lw	$t4,0x4($s0)
/*  f027d00:	004f001b */ 	divu	$zero,$v0,$t7
/*  f027d04:	00001810 */ 	mfhi	$v1
/*  f027d08:	0183c021 */ 	addu	$t8,$t4,$v1
/*  f027d0c:	930e0000 */ 	lbu	$t6,0x0($t8)
/*  f027d10:	8fa900f0 */ 	lw	$t1,0xf0($sp)
/*  f027d14:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f027d18:	afb90018 */ 	sw	$t9,0x18($sp)
/*  f027d1c:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f027d20:	8d2a0178 */ 	lw	$t2,0x178($t1)
/*  f027d24:	3c0d800a */ 	lui	$t5,0x800a
/*  f027d28:	8dade944 */ 	lw	$t5,-0x16bc($t5)
/*  f027d2c:	afaa001c */ 	sw	$t2,0x1c($sp)
/*  f027d30:	8e2b0040 */ 	lw	$t3,0x40($s1)
/*  f027d34:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f027d38:	15e00002 */ 	bnez	$t7,.NB0f027d44
/*  f027d3c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f027d40:	0007000d */ 	break	0x7
.NB0f027d44:
/*  f027d44:	afab0020 */ 	sw	$t3,0x20($sp)
/*  f027d48:	8daf00bc */ 	lw	$t7,0xbc($t5)
/*  f027d4c:	8fa600f8 */ 	lw	$a2,0xf8($sp)
/*  f027d50:	26240010 */ 	addiu	$a0,$s1,0x10
/*  f027d54:	8dec0004 */ 	lw	$t4,0x4($t7)
/*  f027d58:	afa0002c */ 	sw	$zero,0x2c($sp)
/*  f027d5c:	2625001c */ 	addiu	$a1,$s1,0x1c
/*  f027d60:	00003825 */ 	or	$a3,$zero,$zero
/*  f027d64:	24c6001c */ 	addiu	$a2,$a2,0x1c
/*  f027d68:	0fc4e7bd */ 	jal	func0f13f3f4
/*  f027d6c:	afac0028 */ 	sw	$t4,0x28($sp)
/*  f027d70:	10000045 */ 	beqz	$zero,.NB0f027e88
/*  f027d74:	8fbf003c */ 	lw	$ra,0x3c($sp)
.NB0f027d78:
/*  f027d78:	11000003 */ 	beqz	$t0,.NB0f027d88
/*  f027d7c:	00001825 */ 	or	$v1,$zero,$zero
/*  f027d80:	10000001 */ 	beqz	$zero,.NB0f027d88
/*  f027d84:	910302fe */ 	lbu	$v1,0x2fe($t0)
.NB0f027d88:
/*  f027d88:	8e240048 */ 	lw	$a0,0x48($s1)
/*  f027d8c:	8e25000c */ 	lw	$a1,0xc($s1)
/*  f027d90:	0c006dcf */ 	jal	func0001a5cc
/*  f027d94:	afa30068 */ 	sw	$v1,0x68($sp)
/*  f027d98:	00402025 */ 	or	$a0,$v0,$zero
/*  f027d9c:	0c006082 */ 	jal	func0001719c
/*  f027da0:	27a500b0 */ 	addiu	$a1,$sp,0xb0
/*  f027da4:	27a400b0 */ 	addiu	$a0,$sp,0xb0
/*  f027da8:	27a50098 */ 	addiu	$a1,$sp,0x98
/*  f027dac:	0c005a96 */ 	jal	func00015b68
/*  f027db0:	27a6005c */ 	addiu	$a2,$sp,0x5c
/*  f027db4:	3c18800a */ 	lui	$t8,0x800a
/*  f027db8:	8f18e944 */ 	lw	$t8,-0x16bc($t8)
/*  f027dbc:	8f0e00bc */ 	lw	$t6,0xbc($t8)
/*  f027dc0:	0fc4e3ea */ 	jal	chrIsUsingPaintball
/*  f027dc4:	8dc40004 */ 	lw	$a0,0x4($t6)
/*  f027dc8:	1440002e */ 	bnez	$v0,.NB0f027e84
/*  f027dcc:	8fa30068 */ 	lw	$v1,0x68($sp)
/*  f027dd0:	8fb900f0 */ 	lw	$t9,0xf0($sp)
/*  f027dd4:	24010002 */ 	addiu	$at,$zero,0x2
/*  f027dd8:	8f29032c */ 	lw	$t1,0x32c($t9)
/*  f027ddc:	00095cc0 */ 	sll	$t3,$t1,0x13
/*  f027de0:	05620029 */ 	bltzl	$t3,.NB0f027e88
/*  f027de4:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f027de8:	10610026 */ 	beq	$v1,$at,.NB0f027e84
/*  f027dec:	24010004 */ 	addiu	$at,$zero,0x4
/*  f027df0:	10610024 */ 	beq	$v1,$at,.NB0f027e84
/*  f027df4:	24010003 */ 	addiu	$at,$zero,0x3
/*  f027df8:	10610022 */ 	beq	$v1,$at,.NB0f027e84
/*  f027dfc:	93ad008f */ 	lbu	$t5,0x8f($sp)
/*  f027e00:	15a00020 */ 	bnez	$t5,.NB0f027e84
/*  f027e04:	8faf00f8 */ 	lw	$t7,0xf8($sp)
/*  f027e08:	91ec0018 */ 	lbu	$t4,0x18($t7)
/*  f027e0c:	2401001c */ 	addiu	$at,$zero,0x1c
/*  f027e10:	27a7005c */ 	addiu	$a3,$sp,0x5c
/*  f027e14:	5181001c */ 	beql	$t4,$at,.NB0f027e88
/*  f027e18:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f027e1c:	87380010 */ 	lh	$t8,0x10($t9)
/*  f027e20:	2401005b */ 	addiu	$at,$zero,0x5b
/*  f027e24:	13010003 */ 	beq	$t8,$at,.NB0f027e34
/*  f027e28:	24010001 */ 	addiu	$at,$zero,0x1
/*  f027e2c:	14610003 */ 	bne	$v1,$at,.NB0f027e3c
/*  f027e30:	00001025 */ 	or	$v0,$zero,$zero
.NB0f027e34:
/*  f027e34:	10000001 */ 	beqz	$zero,.NB0f027e3c
/*  f027e38:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f027e3c:
/*  f027e3c:	8e240048 */ 	lw	$a0,0x48($s1)
/*  f027e40:	8e250008 */ 	lw	$a1,0x8($s1)
/*  f027e44:	8e26000c */ 	lw	$a2,0xc($s1)
/*  f027e48:	0fc098b6 */ 	jal	func0f0268bc
/*  f027e4c:	a3a20057 */ 	sb	$v0,0x57($sp)
/*  f027e50:	93a20057 */ 	lbu	$v0,0x57($sp)
/*  f027e54:	3c0e800a */ 	lui	$t6,0x800a
/*  f027e58:	8dcee944 */ 	lw	$t6,-0x16bc($t6)
/*  f027e5c:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f027e60:	afa20010 */ 	sw	$v0,0x10($sp)
/*  f027e64:	8dc900bc */ 	lw	$t1,0xbc($t6)
/*  f027e68:	02002025 */ 	or	$a0,$s0,$zero
/*  f027e6c:	8fa500f8 */ 	lw	$a1,0xf8($sp)
/*  f027e70:	8d2a0004 */ 	lw	$t2,0x4($t1)
/*  f027e74:	27a60098 */ 	addiu	$a2,$sp,0x98
/*  f027e78:	27a700a4 */ 	addiu	$a3,$sp,0xa4
/*  f027e7c:	0fc50d89 */ 	jal	func0f148e54
/*  f027e80:	afaa0018 */ 	sw	$t2,0x18($sp)
.NB0f027e84:
/*  f027e84:	8fbf003c */ 	lw	$ra,0x3c($sp)
.NB0f027e88:
/*  f027e88:	8fb00034 */ 	lw	$s0,0x34($sp)
/*  f027e8c:	8fb10038 */ 	lw	$s1,0x38($sp)
/*  f027e90:	03e00008 */ 	jr	$ra
/*  f027e94:	27bd00f8 */ 	addiu	$sp,$sp,0xf8
);
#endif

void func0f028490(f32 arg1)
{
	// empty
}

void func0f028498(bool value)
{
	var8006296c = value;
	var8005efbc = value;
}

void func0f0284ac(s32 arg0)
{
	g_SelectedAnimNum -= arg0;

	if (g_SelectedAnimNum <= 0) {
		g_SelectedAnimNum = getNumAnimations() - 1;
	}
}

void func0f0284f4(s32 arg0)
{
	g_SelectedAnimNum += arg0;

	if (g_SelectedAnimNum >= getNumAnimations()) {
		g_SelectedAnimNum = 1;
	}
}

void func0f028544(void)
{
	var80062974 = !var80062974;
}

void func0f02855c(s32 arg0)
{
	var80062978 = arg0;

	func0000db30("selectanimnum", &g_SelectedAnimNum);
}

void chrsCheckForNoise(f32 noiseradius)
{
	s32 i;
	f32 add = 0.075f;

	for (i = 0; i < g_NumChrSlots; i++) {
		if (g_ChrSlots[i].model) {
			struct prop *prop = g_ChrSlots[i].prop;

			if (prop && prop->type == PROPTYPE_CHR &&
					chrGetTargetProp(&g_ChrSlots[i]) == g_Vars.currentplayer->prop) {

				f32 distance = chrGetDistanceToCurrentPlayer(&g_ChrSlots[i]);

				if (distance == 0) {
					distance = 2;
				} else {
					distance = (noiseradius * 100 * g_ChrSlots[i].hearingscale * (1.0f + add)) / distance;
				}

				if (distance > 1.0f) {
					chrRecordLastHearTargetTime(&g_ChrSlots[i]);
#if PIRACYCHECKS
					{
						s32 *i = (s32 *)&func00002078;
						s32 *end = (s32 *)&__scHandleRetrace;
						u32 checksum = 0;

						while (i < end) {
							checksum *= 2;
							checksum += *i;
							i++;
						}

						if (checksum != CHECKSUM_PLACEHOLDER) {
							g_HeadsAndBodies[BODY_SKEDARKING].filenum = 0;
						}
					}
#endif
				}
			}
		}
	}
}

struct chrdata *chrFindByLiteralId(s32 chrnum)
{
	s32 lower = 0;
	s32 upper = g_NumChrs;
	s32 i;

	while (upper >= lower) {
		i = (lower + upper) / 2;

		if (chrnum == g_Chrnums[i]) {
			return &g_ChrSlots[g_ChrIndexes[i]];
		}

		if (chrnum < g_Chrnums[i]) {
			upper = i - 1;
		} else {
			lower = i + 1;
		}
	}

	return NULL;
}

struct prop *chrGetEquippedWeaponProp(struct chrdata *chr, s32 hand)
{
	return chr->weapons_held[hand];
}

struct prop *chrGetEquippedWeaponPropWithCheck(struct chrdata *chr, s32 hand)
{
	struct prop *prop = chr->weapons_held[hand];

	if (prop) {
		struct weaponobj *weapon = prop->weapon;

		if (!weaponHasFlag(weapon->weaponnum, WEAPONFLAG_AICANUSE)) {
			prop = NULL;
		}
	}

	return prop;
}

struct prop *chrGetTargetProp(struct chrdata *chr)
{
	struct prop *ret;

	if (chr->target == -1) {
		ret = g_Vars.players[chr->p1p2]->prop;
	} else {
		ret = g_Vars.props + chr->target;
	}

	return ret;
}

bool chrUpdateGeometry(struct prop *prop, u8 **start, u8 **end)
{
	struct chrdata *chr = prop->chr;

	if (chr->actiontype != ACT_DEAD &&
			chr->actiontype != ACT_DRUGGEDKO &&
			(chr->chrflags & (CHRCFLAG_00010000 | CHRCFLAG_HIDDEN)) == 0 &&
			(chr->hidden & CHRHFLAG_00000100) == 0) {
		chr->geo.header.type = TILETYPE_03;

		if (chr->actiontype == ACT_DIE || chr->actiontype == ACT_DRUGGEDDROP) {
			chr->geo.header.flags = TILEFLAG_0010;
		} else {
			chr->geo.header.flags = TILEFLAG_0004 | TILEFLAG_0010;
		}

		chr->geo.ymin = chr->manground;
		chr->geo.ymax = chr->manground + chr->chrheight;

		if (chr->actiontype == ACT_SKJUMP) {
			if (chr->manground > chr->act_skjump.ground) {
				chr->geo.ymin = chr->act_skjump.ground;
			}
		}

		chr->geo.x = prop->pos.x;
		chr->geo.z = prop->pos.z;
		chr->geo.width = chr->chrwidth;

		if (g_Vars.unk00048c) {
			chr->geo.width = 15;
		}

		*start = (void *) &chr->geo;
		*end = *start + sizeof(struct tiletype3);

		return true;
	}

	*end = NULL;
	*start = NULL;

	return false;

}

void propChrGetBbox(struct prop *prop, f32 *width, f32 *ymax, f32 *ymin)
{
	struct chrdata *chr = prop->chr;

	*width = chr->chrwidth;
	*ymax = chr->manground + chr->chrheight;
	*ymin = chr->manground + 20;

	if (chr->actiontype == ACT_SKJUMP && chr->act_skjump.ground < chr->manground) {
		*ymin = chr->act_skjump.ground + 20;
	}
}

f32 chrGetGround(struct prop *prop)
{
	struct chrdata *chr = prop->chr;
	return chr->ground;
}

GLOBAL_ASM(
glabel func0f028a50
/*  f028a50:	27bdffd0 */ 	addiu	$sp,$sp,-48
/*  f028a54:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f028a58:	afa60038 */ 	sw	$a2,0x38($sp)
/*  f028a5c:	afa7003c */ 	sw	$a3,0x3c($sp)
/*  f028a60:	908e0001 */ 	lbu	$t6,0x1($a0)
/*  f028a64:	8c880004 */ 	lw	$t0,0x4($a0)
/*  f028a68:	31cf0002 */ 	andi	$t7,$t6,0x2
/*  f028a6c:	51e000b4 */ 	beqzl	$t7,.L0f028d40
/*  f028a70:	00001025 */ 	or	$v0,$zero,$zero
/*  f028a74:	81020007 */ 	lb	$v0,0x7($t0)
/*  f028a78:	24010004 */ 	addiu	$at,$zero,0x4
/*  f028a7c:	104100af */ 	beq	$v0,$at,.L0f028d3c
/*  f028a80:	2401001e */ 	addiu	$at,$zero,0x1e
/*  f028a84:	104100ad */ 	beq	$v0,$at,.L0f028d3c
/*  f028a88:	2401001f */ 	addiu	$at,$zero,0x1f
/*  f028a8c:	104100ab */ 	beq	$v0,$at,.L0f028d3c
/*  f028a90:	24010005 */ 	addiu	$at,$zero,0x5
/*  f028a94:	504100aa */ 	beql	$v0,$at,.L0f028d40
/*  f028a98:	00001025 */ 	or	$v0,$zero,$zero
/*  f028a9c:	8d180018 */ 	lw	$t8,0x18($t0)
/*  f028aa0:	33190800 */ 	andi	$t9,$t8,0x800
/*  f028aa4:	572000a6 */ 	bnezl	$t9,.L0f028d40
/*  f028aa8:	00001025 */ 	or	$v0,$zero,$zero
/*  f028aac:	8d090014 */ 	lw	$t1,0x14($t0)
/*  f028ab0:	3c06800a */ 	lui	$a2,%hi(g_Vars)
/*  f028ab4:	24c69fc0 */ 	addiu	$a2,$a2,%lo(g_Vars)
/*  f028ab8:	00095080 */ 	sll	$t2,$t1,0x2
/*  f028abc:	05430019 */ 	bgezl	$t2,.L0f028b24
/*  f028ac0:	908a0000 */ 	lbu	$t2,0x0($a0)
/*  f028ac4:	8cc30284 */ 	lw	$v1,0x284($a2)
/*  f028ac8:	3c0c8007 */ 	lui	$t4,%hi(g_InCutscene)
/*  f028acc:	8c6b00d8 */ 	lw	$t3,0xd8($v1)
/*  f028ad0:	5560009b */ 	bnezl	$t3,.L0f028d40
/*  f028ad4:	00001025 */ 	or	$v0,$zero,$zero
/*  f028ad8:	8d8c0764 */ 	lw	$t4,%lo(g_InCutscene)($t4)
/*  f028adc:	55800098 */ 	bnezl	$t4,.L0f028d40
/*  f028ae0:	00001025 */ 	or	$v0,$zero,$zero
/*  f028ae4:	8c620480 */ 	lw	$v0,0x480($v1)
/*  f028ae8:	50400007 */ 	beqzl	$v0,.L0f028b08
/*  f028aec:	8c6f1c54 */ 	lw	$t7,0x1c54($v1)
/*  f028af0:	50400093 */ 	beqzl	$v0,.L0f028d40
/*  f028af4:	00001025 */ 	or	$v0,$zero,$zero
/*  f028af8:	804d0037 */ 	lb	$t5,0x37($v0)
/*  f028afc:	55a00090 */ 	bnezl	$t5,.L0f028d40
/*  f028b00:	00001025 */ 	or	$v0,$zero,$zero
/*  f028b04:	8c6f1c54 */ 	lw	$t7,0x1c54($v1)
.L0f028b08:
/*  f028b08:	8c6e00c4 */ 	lw	$t6,0xc4($v1)
/*  f028b0c:	01e0c027 */ 	nor	$t8,$t7,$zero
/*  f028b10:	01d8c824 */ 	and	$t9,$t6,$t8
/*  f028b14:	33290008 */ 	andi	$t1,$t9,0x8
/*  f028b18:	51200089 */ 	beqzl	$t1,.L0f028d40
/*  f028b1c:	00001025 */ 	or	$v0,$zero,$zero
/*  f028b20:	908a0000 */ 	lbu	$t2,0x0($a0)
.L0f028b24:
/*  f028b24:	3c06800a */ 	lui	$a2,%hi(g_Vars)
/*  f028b28:	24010006 */ 	addiu	$at,$zero,0x6
/*  f028b2c:	15410010 */ 	bne	$t2,$at,.L0f028b70
/*  f028b30:	24c69fc0 */ 	addiu	$a2,$a2,%lo(g_Vars)
/*  f028b34:	afa40030 */ 	sw	$a0,0x30($sp)
/*  f028b38:	afa50034 */ 	sw	$a1,0x34($sp)
/*  f028b3c:	0fc4a25f */ 	jal	propGetPlayerNum
/*  f028b40:	afa8002c */ 	sw	$t0,0x2c($sp)
/*  f028b44:	3c06800a */ 	lui	$a2,%hi(g_Vars)
/*  f028b48:	24c69fc0 */ 	addiu	$a2,$a2,%lo(g_Vars)
/*  f028b4c:	00025880 */ 	sll	$t3,$v0,0x2
/*  f028b50:	00cb6021 */ 	addu	$t4,$a2,$t3
/*  f028b54:	8d8d0064 */ 	lw	$t5,0x64($t4)
/*  f028b58:	8fa40030 */ 	lw	$a0,0x30($sp)
/*  f028b5c:	8fa50034 */ 	lw	$a1,0x34($sp)
/*  f028b60:	8daf00d8 */ 	lw	$t7,0xd8($t5)
/*  f028b64:	8fa8002c */ 	lw	$t0,0x2c($sp)
/*  f028b68:	55e00075 */ 	bnezl	$t7,.L0f028d40
/*  f028b6c:	00001025 */ 	or	$v0,$zero,$zero
.L0f028b70:
/*  f028b70:	8cce0298 */ 	lw	$t6,0x298($a2)
/*  f028b74:	05c2000a */ 	bltzl	$t6,.L0f028ba0
/*  f028b78:	8d040020 */ 	lw	$a0,0x20($t0)
/*  f028b7c:	8cd802a0 */ 	lw	$t8,0x2a0($a2)
/*  f028b80:	8f1900bc */ 	lw	$t9,0xbc($t8)
/*  f028b84:	5099006e */ 	beql	$a0,$t9,.L0f028d40
/*  f028b88:	00001025 */ 	or	$v0,$zero,$zero
/*  f028b8c:	8cc902a4 */ 	lw	$t1,0x2a4($a2)
/*  f028b90:	8d2a00bc */ 	lw	$t2,0xbc($t1)
/*  f028b94:	508a006a */ 	beql	$a0,$t2,.L0f028d40
/*  f028b98:	00001025 */ 	or	$v0,$zero,$zero
/*  f028b9c:	8d040020 */ 	lw	$a0,0x20($t0)
.L0f028ba0:
/*  f028ba0:	3c078008 */ 	lui	$a3,%hi(g_ModelTypeChr)
/*  f028ba4:	24e7ce40 */ 	addiu	$a3,$a3,%lo(g_ModelTypeChr)
/*  f028ba8:	8c8b0008 */ 	lw	$t3,0x8($a0)
/*  f028bac:	3c0c8008 */ 	lui	$t4,%hi(g_ModelTypeSkedar)
/*  f028bb0:	44806000 */ 	mtc1	$zero,$f12
/*  f028bb4:	8d620004 */ 	lw	$v0,0x4($t3)
/*  f028bb8:	258cce98 */ 	addiu	$t4,$t4,%lo(g_ModelTypeSkedar)
/*  f028bbc:	14e2000c */ 	bne	$a3,$v0,.L0f028bf0
/*  f028bc0:	00000000 */ 	nop
/*  f028bc4:	8c86000c */ 	lw	$a2,0xc($a0)
/*  f028bc8:	3c013f00 */ 	lui	$at,0x3f00
/*  f028bcc:	44817000 */ 	mtc1	$at,$f14
/*  f028bd0:	24c30040 */ 	addiu	$v1,$a2,0x40
/*  f028bd4:	c4600038 */ 	lwc1	$f0,0x38($v1)
/*  f028bd8:	c4c40038 */ 	lwc1	$f4,0x38($a2)
/*  f028bdc:	46002181 */ 	sub.s	$f6,$f4,$f0
/*  f028be0:	460e3202 */ 	mul.s	$f8,$f6,$f14
/*  f028be4:	46004280 */ 	add.s	$f10,$f8,$f0
/*  f028be8:	1000001b */ 	b	.L0f028c58
/*  f028bec:	e4aa0008 */ 	swc1	$f10,0x8($a1)
.L0f028bf0:
/*  f028bf0:	15820008 */ 	bne	$t4,$v0,.L0f028c14
/*  f028bf4:	3c0d8008 */ 	lui	$t5,%hi(g_ModelTypeDrCaroll)
/*  f028bf8:	8c83000c */ 	lw	$v1,0xc($a0)
/*  f028bfc:	3c013f00 */ 	lui	$at,0x3f00
/*  f028c00:	44817000 */ 	mtc1	$at,$f14
/*  f028c04:	c4700038 */ 	lwc1	$f16,0x38($v1)
/*  f028c08:	e4b00008 */ 	swc1	$f16,0x8($a1)
/*  f028c0c:	10000012 */ 	b	.L0f028c58
/*  f028c10:	8fa60024 */ 	lw	$a2,0x24($sp)
.L0f028c14:
/*  f028c14:	25adcea8 */ 	addiu	$t5,$t5,%lo(g_ModelTypeDrCaroll)
/*  f028c18:	55a20009 */ 	bnel	$t5,$v0,.L0f028c40
/*  f028c1c:	8c8f000c */ 	lw	$t7,0xc($a0)
/*  f028c20:	8c83000c */ 	lw	$v1,0xc($a0)
/*  f028c24:	3c013f00 */ 	lui	$at,0x3f00
/*  f028c28:	44817000 */ 	mtc1	$at,$f14
/*  f028c2c:	c4720038 */ 	lwc1	$f18,0x38($v1)
/*  f028c30:	e4b20008 */ 	swc1	$f18,0x8($a1)
/*  f028c34:	10000008 */ 	b	.L0f028c58
/*  f028c38:	8fa60024 */ 	lw	$a2,0x24($sp)
/*  f028c3c:	8c8f000c */ 	lw	$t7,0xc($a0)
.L0f028c40:
/*  f028c40:	3c013f00 */ 	lui	$at,0x3f00
/*  f028c44:	44817000 */ 	mtc1	$at,$f14
/*  f028c48:	c5e40038 */ 	lwc1	$f4,0x38($t7)
/*  f028c4c:	e4a40008 */ 	swc1	$f4,0x8($a1)
/*  f028c50:	8fa30020 */ 	lw	$v1,0x20($sp)
/*  f028c54:	8fa60024 */ 	lw	$a2,0x24($sp)
.L0f028c58:
/*  f028c58:	c4a60008 */ 	lwc1	$f6,0x8($a1)
/*  f028c5c:	460c303c */ 	c.lt.s	$f6,$f12
/*  f028c60:	00000000 */ 	nop
/*  f028c64:	45020036 */ 	bc1fl	.L0f028d40
/*  f028c68:	00001025 */ 	or	$v0,$zero,$zero
/*  f028c6c:	8c8e0008 */ 	lw	$t6,0x8($a0)
/*  f028c70:	3c188008 */ 	lui	$t8,%hi(g_ModelTypeSkedar)
/*  f028c74:	2718ce98 */ 	addiu	$t8,$t8,%lo(g_ModelTypeSkedar)
/*  f028c78:	8dc20004 */ 	lw	$v0,0x4($t6)
/*  f028c7c:	14e2000e */ 	bne	$a3,$v0,.L0f028cb8
/*  f028c80:	00000000 */ 	nop
/*  f028c84:	c4600030 */ 	lwc1	$f0,0x30($v1)
/*  f028c88:	c4c80030 */ 	lwc1	$f8,0x30($a2)
/*  f028c8c:	46004281 */ 	sub.s	$f10,$f8,$f0
/*  f028c90:	460e5402 */ 	mul.s	$f16,$f10,$f14
/*  f028c94:	46008480 */ 	add.s	$f18,$f16,$f0
/*  f028c98:	e4b20000 */ 	swc1	$f18,0x0($a1)
/*  f028c9c:	c4c40034 */ 	lwc1	$f4,0x34($a2)
/*  f028ca0:	c4620034 */ 	lwc1	$f2,0x34($v1)
/*  f028ca4:	46022181 */ 	sub.s	$f6,$f4,$f2
/*  f028ca8:	460e3202 */ 	mul.s	$f8,$f6,$f14
/*  f028cac:	46024280 */ 	add.s	$f10,$f8,$f2
/*  f028cb0:	10000016 */ 	b	.L0f028d0c
/*  f028cb4:	e4aa0004 */ 	swc1	$f10,0x4($a1)
.L0f028cb8:
/*  f028cb8:	17020006 */ 	bne	$t8,$v0,.L0f028cd4
/*  f028cbc:	3c198008 */ 	lui	$t9,%hi(g_ModelTypeDrCaroll)
/*  f028cc0:	c4700030 */ 	lwc1	$f16,0x30($v1)
/*  f028cc4:	e4b00000 */ 	swc1	$f16,0x0($a1)
/*  f028cc8:	c4720034 */ 	lwc1	$f18,0x34($v1)
/*  f028ccc:	1000000f */ 	b	.L0f028d0c
/*  f028cd0:	e4b20004 */ 	swc1	$f18,0x4($a1)
.L0f028cd4:
/*  f028cd4:	2739cea8 */ 	addiu	$t9,$t9,%lo(g_ModelTypeDrCaroll)
/*  f028cd8:	57220007 */ 	bnel	$t9,$v0,.L0f028cf8
/*  f028cdc:	8c89000c */ 	lw	$t1,0xc($a0)
/*  f028ce0:	c4640030 */ 	lwc1	$f4,0x30($v1)
/*  f028ce4:	e4a40000 */ 	swc1	$f4,0x0($a1)
/*  f028ce8:	c4660034 */ 	lwc1	$f6,0x34($v1)
/*  f028cec:	10000007 */ 	b	.L0f028d0c
/*  f028cf0:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*  f028cf4:	8c89000c */ 	lw	$t1,0xc($a0)
.L0f028cf8:
/*  f028cf8:	c5280030 */ 	lwc1	$f8,0x30($t1)
/*  f028cfc:	e4a80000 */ 	swc1	$f8,0x0($a1)
/*  f028d00:	8c8a000c */ 	lw	$t2,0xc($a0)
/*  f028d04:	c54a0034 */ 	lwc1	$f10,0x34($t2)
/*  f028d08:	e4aa0004 */ 	swc1	$f10,0x4($a1)
.L0f028d0c:
/*  f028d0c:	8fab003c */ 	lw	$t3,0x3c($sp)
/*  f028d10:	e56c0004 */ 	swc1	$f12,0x4($t3)
/*  f028d14:	e56c0000 */ 	swc1	$f12,0x0($t3)
/*  f028d18:	8fa60038 */ 	lw	$a2,0x38($sp)
/*  f028d1c:	25670004 */ 	addiu	$a3,$t3,0x4
/*  f028d20:	e4cc0004 */ 	swc1	$f12,0x4($a2)
/*  f028d24:	e4cc0000 */ 	swc1	$f12,0x0($a2)
/*  f028d28:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f028d2c:	0fc19f62 */ 	jal	func0f067d88
/*  f028d30:	24c50004 */ 	addiu	$a1,$a2,0x4
/*  f028d34:	10000002 */ 	b	.L0f028d40
/*  f028d38:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f028d3c:
/*  f028d3c:	00001025 */ 	or	$v0,$zero,$zero
.L0f028d40:
/*  f028d40:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f028d44:	27bd0030 */ 	addiu	$sp,$sp,0x30
/*  f028d48:	03e00008 */ 	jr	$ra
/*  f028d4c:	00000000 */ 	nop
);

bool func0f028d50(struct prop *arg0, struct prop *arg1, struct modelnode *node, struct model *model, s32 *total)
{
	if (arg1 == arg0) {
		*total += func0001a524(node, 0);
		return true;
	}

	*total += model->filedata->nummatrices;

	if (arg0->child && func0f028d50(arg0->child, arg1, node, model, total) > 0) {
		return true;
	}

	if (arg0->next && func0f028d50(arg0->next, arg1, node, model, total) > 0) {
		return true;
	}

	return false;
}

s32 func0f028e18(struct prop *arg0, struct modelnode *node, struct model *model, struct prop *arg3)
{
	s32 result = 0;

	if (func0f028d50(arg3, arg0, node, model, &result)) {
		return result;
	}

	return -1;
}

GLOBAL_ASM(
glabel func0f028e6c
/*  f028e6c:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*  f028e70:	afb60038 */ 	sw	$s6,0x38($sp)
/*  f028e74:	afb50034 */ 	sw	$s5,0x34($sp)
/*  f028e78:	afb40030 */ 	sw	$s4,0x30($sp)
/*  f028e7c:	afb3002c */ 	sw	$s3,0x2c($sp)
/*  f028e80:	afb20028 */ 	sw	$s2,0x28($sp)
/*  f028e84:	afb10024 */ 	sw	$s1,0x24($sp)
/*  f028e88:	afb00020 */ 	sw	$s0,0x20($sp)
/*  f028e8c:	00a08025 */ 	or	$s0,$a1,$zero
/*  f028e90:	00808825 */ 	or	$s1,$a0,$zero
/*  f028e94:	00c09025 */ 	or	$s2,$a2,$zero
/*  f028e98:	00e09825 */ 	or	$s3,$a3,$zero
/*  f028e9c:	8fb40058 */ 	lw	$s4,0x58($sp)
/*  f028ea0:	24150003 */ 	addiu	$s5,$zero,0x3
/*  f028ea4:	24160006 */ 	addiu	$s6,$zero,0x6
/*  f028ea8:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f028eac:	00001825 */ 	or	$v1,$zero,$zero
.L0f028eb0:
/*  f028eb0:	92020000 */ 	lbu	$v0,0x0($s0)
/*  f028eb4:	02403025 */ 	or	$a2,$s2,$zero
/*  f028eb8:	02603825 */ 	or	$a3,$s3,$zero
/*  f028ebc:	52a20004 */ 	beql	$s5,$v0,.L0f028ed0
/*  f028ec0:	8e0e0004 */ 	lw	$t6,0x4($s0)
/*  f028ec4:	56c20005 */ 	bnel	$s6,$v0,.L0f028edc
/*  f028ec8:	8e0f0004 */ 	lw	$t7,0x4($s0)
/*  f028ecc:	8e0e0004 */ 	lw	$t6,0x4($s0)
.L0f028ed0:
/*  f028ed0:	10000003 */ 	b	.L0f028ee0
/*  f028ed4:	8dc40020 */ 	lw	$a0,0x20($t6)
/*  f028ed8:	8e0f0004 */ 	lw	$t7,0x4($s0)
.L0f028edc:
/*  f028edc:	8de40018 */ 	lw	$a0,0x18($t7)
.L0f028ee0:
/*  f028ee0:	8c980008 */ 	lw	$t8,0x8($a0)
/*  f028ee4:	8702000e */ 	lh	$v0,0xe($t8)
/*  f028ee8:	0222082a */ 	slt	$at,$s1,$v0
/*  f028eec:	54200011 */ 	bnezl	$at,.L0f028f34
/*  f028ef0:	ae500000 */ 	sw	$s0,0x0($s2)
/*  f028ef4:	8e05001c */ 	lw	$a1,0x1c($s0)
/*  f028ef8:	02228823 */ 	subu	$s1,$s1,$v0
/*  f028efc:	02202025 */ 	or	$a0,$s1,$zero
/*  f028f00:	50a00005 */ 	beqzl	$a1,.L0f028f18
/*  f028f04:	8e020020 */ 	lw	$v0,0x20($s0)
/*  f028f08:	0fc0a39b */ 	jal	func0f028e6c
/*  f028f0c:	afb40010 */ 	sw	$s4,0x10($sp)
/*  f028f10:	00401825 */ 	or	$v1,$v0,$zero
/*  f028f14:	8e020020 */ 	lw	$v0,0x20($s0)
.L0f028f18:
/*  f028f18:	1040000d */ 	beqz	$v0,.L0f028f50
/*  f028f1c:	00408025 */ 	or	$s0,$v0,$zero
/*  f028f20:	5460000c */ 	bnezl	$v1,.L0f028f54
/*  f028f24:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f028f28:	1000ffe1 */ 	b	.L0f028eb0
/*  f028f2c:	00001825 */ 	or	$v1,$zero,$zero
/*  f028f30:	ae500000 */ 	sw	$s0,0x0($s2)
.L0f028f34:
/*  f028f34:	afa40040 */ 	sw	$a0,0x40($sp)
/*  f028f38:	0c00698d */ 	jal	func0001a634
/*  f028f3c:	02202825 */ 	or	$a1,$s1,$zero
/*  f028f40:	8fa40040 */ 	lw	$a0,0x40($sp)
/*  f028f44:	ae620000 */ 	sw	$v0,0x0($s3)
/*  f028f48:	24030001 */ 	addiu	$v1,$zero,0x1
/*  f028f4c:	ae840000 */ 	sw	$a0,0x0($s4)
.L0f028f50:
/*  f028f50:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f028f54:
/*  f028f54:	8fb00020 */ 	lw	$s0,0x20($sp)
/*  f028f58:	8fb10024 */ 	lw	$s1,0x24($sp)
/*  f028f5c:	8fb20028 */ 	lw	$s2,0x28($sp)
/*  f028f60:	8fb3002c */ 	lw	$s3,0x2c($sp)
/*  f028f64:	8fb40030 */ 	lw	$s4,0x30($sp)
/*  f028f68:	8fb50034 */ 	lw	$s5,0x34($sp)
/*  f028f6c:	8fb60038 */ 	lw	$s6,0x38($sp)
/*  f028f70:	27bd0048 */ 	addiu	$sp,$sp,0x48
/*  f028f74:	03e00008 */ 	jr	$ra
/*  f028f78:	00601025 */ 	or	$v0,$v1,$zero
);

// Mismatch: Reordered instructions
//bool func0f028e6c(s32 arg0, struct prop *prop, struct prop **propptr, struct modelnode **nodeptr, struct model **modelptr)
//{
//	while (true) {
//		bool result = false;
//		struct model *model;
//		s32 stack;
//
//		if (prop->type == PROPTYPE_CHR || prop->type == PROPTYPE_PLAYER) {
//			model = prop->chr->model;
//		} else {
//			model = prop->obj->model;
//		}
//
//		if (1);
//
//		if (arg0 >= model->filedata->nummatrices) {
//			arg0 -= model->filedata->nummatrices;
//
//			if (prop->child) {
//				result = func0f028e6c(arg0, prop->child, propptr, nodeptr, modelptr);
//			}
//
//			if (prop->next && !result) {
//				prop = prop->next;
//				continue;
//			}
//		} else {
//			*propptr = prop;
//			*nodeptr = func0001a634(model, arg0);
//			*modelptr = model;
//			result = true;
//		}
//
//		return result;
//	}
//}

GLOBAL_ASM(
glabel func0f028f7c
/*  f028f7c:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*  f028f80:	3c0a8006 */ 	lui	$t2,%hi(var80062a8c)
/*  f028f84:	8d4a2a8c */ 	lw	$t2,%lo(var80062a8c)($t2)
/*  f028f88:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f028f8c:	00808025 */ 	or	$s0,$a0,$zero
/*  f028f90:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f028f94:	afa5002c */ 	sw	$a1,0x2c($sp)
/*  f028f98:	afa60030 */ 	sw	$a2,0x30($sp)
/*  f028f9c:	afa70034 */ 	sw	$a3,0x34($sp)
/*  f028fa0:	00005825 */ 	or	$t3,$zero,$zero
/*  f028fa4:	00004825 */ 	or	$t1,$zero,$zero
/*  f028fa8:	01404025 */ 	or	$t0,$t2,$zero
.L0f028fac:
/*  f028fac:	8d0e0000 */ 	lw	$t6,0x0($t0)
/*  f028fb0:	55c00004 */ 	bnezl	$t6,.L0f028fc4
/*  f028fb4:	2529005c */ 	addiu	$t1,$t1,0x5c
/*  f028fb8:	10000005 */ 	b	.L0f028fd0
/*  f028fbc:	012a5821 */ 	addu	$t3,$t1,$t2
/*  f028fc0:	2529005c */ 	addiu	$t1,$t1,0x5c
.L0f028fc4:
/*  f028fc4:	29210730 */ 	slti	$at,$t1,0x730
/*  f028fc8:	1420fff8 */ 	bnez	$at,.L0f028fac
/*  f028fcc:	2508005c */ 	addiu	$t0,$t0,0x5c
.L0f028fd0:
/*  f028fd0:	15600010 */ 	bnez	$t3,.L0f029014
/*  f028fd4:	00002825 */ 	or	$a1,$zero,$zero
/*  f028fd8:	3c03800a */ 	lui	$v1,%hi(g_Vars+0x8)
/*  f028fdc:	8c639fc8 */ 	lw	$v1,%lo(g_Vars+0x8)($v1)
/*  f028fe0:	00004825 */ 	or	$t1,$zero,$zero
/*  f028fe4:	01404025 */ 	or	$t0,$t2,$zero
/*  f028fe8:	24040730 */ 	addiu	$a0,$zero,0x730
.L0f028fec:
/*  f028fec:	8d02000c */ 	lw	$v0,0xc($t0)
/*  f028ff0:	0043082a */ 	slt	$at,$v0,$v1
/*  f028ff4:	50200004 */ 	beqzl	$at,.L0f029008
/*  f028ff8:	2529005c */ 	addiu	$t1,$t1,0x5c
/*  f028ffc:	012a2821 */ 	addu	$a1,$t1,$t2
/*  f029000:	00401825 */ 	or	$v1,$v0,$zero
/*  f029004:	2529005c */ 	addiu	$t1,$t1,0x5c
.L0f029008:
/*  f029008:	1524fff8 */ 	bne	$t1,$a0,.L0f028fec
/*  f02900c:	2508005c */ 	addiu	$t0,$t0,0x5c
/*  f029010:	00a05825 */ 	or	$t3,$a1,$zero
.L0f029014:
/*  f029014:	51600069 */ 	beqzl	$t3,.L0f0291bc
/*  f029018:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f02901c:	ad700000 */ 	sw	$s0,0x0($t3)
/*  f029020:	8faf0034 */ 	lw	$t7,0x34($sp)
/*  f029024:	3c0c800a */ 	lui	$t4,%hi(g_Vars+0x8)
/*  f029028:	00001025 */ 	or	$v0,$zero,$zero
/*  f02902c:	ad6f0004 */ 	sw	$t7,0x4($t3)
/*  f029030:	8fb80038 */ 	lw	$t8,0x38($sp)
/*  f029034:	01601825 */ 	or	$v1,$t3,$zero
/*  f029038:	2407ffff */ 	addiu	$a3,$zero,-1
/*  f02903c:	ad780008 */ 	sw	$t8,0x8($t3)
/*  f029040:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f029044:	a1790010 */ 	sb	$t9,0x10($t3)
/*  f029048:	8d8c9fc8 */ 	lw	$t4,%lo(g_Vars+0x8)($t4)
/*  f02904c:	ad6c000c */ 	sw	$t4,0xc($t3)
.L0f029050:
/*  f029050:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f029054:	28410020 */ 	slti	$at,$v0,0x20
/*  f029058:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f02905c:	1420fffc */ 	bnez	$at,.L0f029050
/*  f029060:	a0670017 */ 	sb	$a3,0x17($v1)
/*  f029064:	0c004b70 */ 	jal	random
/*  f029068:	afab0024 */ 	sw	$t3,0x24($sp)
/*  f02906c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f029070:	0041001b */ 	divu	$zero,$v0,$at
/*  f029074:	8fab0024 */ 	lw	$t3,0x24($sp)
/*  f029078:	00006810 */ 	mfhi	$t5
/*  f02907c:	8fa30040 */ 	lw	$v1,0x40($sp)
/*  f029080:	25ae0002 */ 	addiu	$t6,$t5,0x2
/*  f029084:	a16e0011 */ 	sb	$t6,0x11($t3)
/*  f029088:	c7a4002c */ 	lwc1	$f4,0x2c($sp)
/*  f02908c:	2407ffff */ 	addiu	$a3,$zero,-1
/*  f029090:	10600008 */ 	beqz	$v1,.L0f0290b4
/*  f029094:	e5640058 */ 	swc1	$f4,0x58($t3)
/*  f029098:	846f0000 */ 	lh	$t7,0x0($v1)
/*  f02909c:	a56f0012 */ 	sh	$t7,0x12($t3)
/*  f0290a0:	84780002 */ 	lh	$t8,0x2($v1)
/*  f0290a4:	a5780014 */ 	sh	$t8,0x14($t3)
/*  f0290a8:	84790004 */ 	lh	$t9,0x4($v1)
/*  f0290ac:	10000003 */ 	b	.L0f0290bc
/*  f0290b0:	a5790016 */ 	sh	$t9,0x16($t3)
.L0f0290b4:
/*  f0290b4:	240c7fff */ 	addiu	$t4,$zero,0x7fff
/*  f0290b8:	a56c0012 */ 	sh	$t4,0x12($t3)
.L0f0290bc:
/*  f0290bc:	8fad0034 */ 	lw	$t5,0x34($sp)
/*  f0290c0:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f0290c4:	00004825 */ 	or	$t1,$zero,$zero
/*  f0290c8:	11a00024 */ 	beqz	$t5,.L0f02915c
/*  f0290cc:	3c088006 */ 	lui	$t0,%hi(var80062a8c)
/*  f0290d0:	8d082a8c */ 	lw	$t0,%lo(var80062a8c)($t0)
/*  f0290d4:	24060020 */ 	addiu	$a2,$zero,0x20
/*  f0290d8:	2405fffe */ 	addiu	$a1,$zero,-2
.L0f0290dc:
/*  f0290dc:	8d0e0000 */ 	lw	$t6,0x0($t0)
/*  f0290e0:	2529005c */ 	addiu	$t1,$t1,0x5c
/*  f0290e4:	00001025 */ 	or	$v0,$zero,$zero
/*  f0290e8:	160e000c */ 	bne	$s0,$t6,.L0f02911c
/*  f0290ec:	01601825 */ 	or	$v1,$t3,$zero
.L0f0290f0:
/*  f0290f0:	80640018 */ 	lb	$a0,0x18($v1)
/*  f0290f4:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f0290f8:	10e40005 */ 	beq	$a3,$a0,.L0f029110
/*  f0290fc:	00000000 */ 	nop
/*  f029100:	10a40003 */ 	beq	$a1,$a0,.L0f029110
/*  f029104:	00000000 */ 	nop
/*  f029108:	10000003 */ 	b	.L0f029118
/*  f02910c:	00005025 */ 	or	$t2,$zero,$zero
.L0f029110:
/*  f029110:	1446fff7 */ 	bne	$v0,$a2,.L0f0290f0
/*  f029114:	24630001 */ 	addiu	$v1,$v1,0x1
.L0f029118:
/*  f029118:	11400003 */ 	beqz	$t2,.L0f029128
.L0f02911c:
/*  f02911c:	29210730 */ 	slti	$at,$t1,0x730
/*  f029120:	1420ffee */ 	bnez	$at,.L0f0290dc
/*  f029124:	2508005c */ 	addiu	$t0,$t0,92
.L0f029128:
/*  f029128:	1140000c */ 	beqz	$t2,.L0f02915c
/*  f02912c:	8fa40030 */ 	lw	$a0,0x30($sp)
/*  f029130:	8fa50034 */ 	lw	$a1,0x34($sp)
/*  f029134:	8fa60038 */ 	lw	$a2,0x38($sp)
/*  f029138:	02003825 */ 	or	$a3,$s0,$zero
/*  f02913c:	0fc0a386 */ 	jal	func0f028e18
/*  f029140:	afab0024 */ 	sw	$t3,0x24($sp)
/*  f029144:	28410020 */ 	slti	$at,$v0,0x20
/*  f029148:	10200004 */ 	beqz	$at,.L0f02915c
/*  f02914c:	8fab0024 */ 	lw	$t3,0x24($sp)
/*  f029150:	01621821 */ 	addu	$v1,$t3,$v0
/*  f029154:	a0600018 */ 	sb	$zero,0x18($v1)
/*  f029158:	a0600038 */ 	sb	$zero,0x38($v1)
.L0f02915c:
/*  f02915c:	92020000 */ 	lbu	$v0,0x0($s0)
/*  f029160:	24010003 */ 	addiu	$at,$zero,0x3
/*  f029164:	10410003 */ 	beq	$v0,$at,.L0f029174
/*  f029168:	24010006 */ 	addiu	$at,$zero,0x6
/*  f02916c:	54410007 */ 	bnel	$v0,$at,.L0f02918c
/*  f029170:	24010001 */ 	addiu	$at,$zero,0x1
.L0f029174:
/*  f029174:	8e020004 */ 	lw	$v0,0x4($s0)
/*  f029178:	944f0192 */ 	lhu	$t7,0x192($v0)
/*  f02917c:	35f80002 */ 	ori	$t8,$t7,0x2
/*  f029180:	1000000d */ 	b	.L0f0291b8
/*  f029184:	a4580192 */ 	sh	$t8,0x192($v0)
/*  f029188:	24010001 */ 	addiu	$at,$zero,0x1
.L0f02918c:
/*  f02918c:	10410005 */ 	beq	$v0,$at,.L0f0291a4
/*  f029190:	24010004 */ 	addiu	$at,$zero,0x4
/*  f029194:	10410003 */ 	beq	$v0,$at,.L0f0291a4
/*  f029198:	24010002 */ 	addiu	$at,$zero,0x2
/*  f02919c:	54410007 */ 	bnel	$v0,$at,.L0f0291bc
/*  f0291a0:	8fbf001c */ 	lw	$ra,0x1c($sp)
.L0f0291a4:
/*  f0291a4:	8e020004 */ 	lw	$v0,0x4($s0)
/*  f0291a8:	3c010002 */ 	lui	$at,0x2
/*  f0291ac:	8c590010 */ 	lw	$t9,0x10($v0)
/*  f0291b0:	03216025 */ 	or	$t4,$t9,$at
/*  f0291b4:	ac4c0010 */ 	sw	$t4,0x10($v0)
.L0f0291b8:
/*  f0291b8:	8fbf001c */ 	lw	$ra,0x1c($sp)
.L0f0291bc:
/*  f0291bc:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f0291c0:	3c018006 */ 	lui	$at,%hi(var80062a90)
/*  f0291c4:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f0291c8:	ac2d2a90 */ 	sw	$t5,%lo(var80062a90)($at)
/*  f0291cc:	03e00008 */ 	jr	$ra
/*  f0291d0:	27bd0028 */ 	addiu	$sp,$sp,0x28
);

// Mismatch: Goal uses a temp register for thing and handles the i/j loop
// differently.
//void func0f028f7c(struct prop *prop, f32 shield, struct prop *arg2, struct modelnode *node, struct model *model, s32 side, s16 *arg6)
//{
//	struct var80062a8c *thing = NULL;
//	s32 i;
//	s32 j;
//
//	for (i = 0; i < 20; i++) {
//		if (var80062a8c[i].prop == NULL) {
//			thing = &var80062a8c[i];
//			break;
//		}
//	}
//
//	if (thing == NULL) {
//		for (i = 0; i < 20; i++) {
//			if (var80062a8c[i].lvframe60 < g_Vars.lvframe60) {
//				thing = &var80062a8c[i];
//			}
//		}
//	}
//
//	if (thing) {
//		thing->prop = prop;
//		thing->node = node;
//		thing->model = model;
//		thing->side = side;
//		thing->lvframe60 = g_Vars.lvframe60;
//
//		for (i = 0; i < 32; i++) {
//			thing->unk018[i] = -1;
//		}
//
//		thing->unk011 = 2 + (random() % 6);
//		thing->shield = shield;
//
//		if (arg6) {
//			thing->unk012 = arg6[0];
//			thing->unk014 = arg6[1];
//			thing->unk016 = arg6[2];
//		} else {
//			thing->unk012 = 0x7fff;
//		}
//
//		if (node) {
//			bool pass = true;
//
//			for (i = 0; i < 20; i++) {
//				if (var80062a8c[i].prop == prop) {
//					for (j = 0; j < 32; j++) {
//						if (var80062a8c[i].unk018[j] != -1 && var80062a8c[i].unk018[j] != -2) {
//							pass = false;
//							break;
//						}
//					}
//
//					if (!pass) {
//						break;
//					}
//				}
//			}
//
//			if (pass) {
//				s32 index = func0f028e18(arg2, node, model, prop);
//
//				if (index < 32) {
//					thing->unk018[index] = 0;
//					thing->unk038[index] = 0;
//				}
//			}
//		}
//
//		if (prop->type == PROPTYPE_CHR || prop->type == PROPTYPE_PLAYER) {
//			prop->chr->hidden2 |= CHRH2FLAG_0002;
//		} else if (prop->type == PROPTYPE_OBJ || prop->type == PROPTYPE_WEAPON || prop->type == PROPTYPE_DOOR) {
//			prop->obj->flags3 |= OBJFLAG3_00020000;
//		}
//	}
//
//	var80062a90 = true;
//}

void func0f0291d4(struct var80062a8c *thing)
{
	s32 exists = false;
	s32 i;
	struct prop *prop = thing->prop;
	thing->prop = NULL;

	// Check if the var80062a8c array has any props in it
	var80062a90 = false;

	for (i = 0; i < 20; i++) {
		if (var80062a8c[i].prop) {
			var80062a90 = true;
			break;
		}
	}

	// Check if the passed prop exists in the array
	for (i = 0; i < 20; i++) {
		if (prop == var80062a8c[i].prop) {
			exists = true;
			break;
		}
	}

	if (!exists) {
		if (prop->type == PROPTYPE_CHR || prop->type == PROPTYPE_PLAYER) {
			struct chrdata *chr = prop->chr;
			chr->hidden2 &= ~CHRH2FLAG_0002;
		} else if (prop->type == PROPTYPE_OBJ
				|| prop->type == PROPTYPE_WEAPON
				|| prop->type == PROPTYPE_DOOR) {
			struct defaultobj *obj = prop->obj;
			obj->flags3 &= ~OBJFLAG3_00020000;
		}
	}
}

void func0f0292bc(struct prop *prop)
{
	s32 i;

	for (i = 0; i < 20; i++) {
		if (prop == var80062a8c[i].prop) {
			func0f0291d4(&var80062a8c[i]);
		}
	}
}

s32 func0f02932c(struct prop *prop, s32 arg1)
{
	s32 result = -1;
	struct modelnode *node2;
	struct prop *prop2;
	struct modelnode *node;
	struct model *model;

	if (func0f028e6c(arg1, prop, &prop2, &node, &model) && node) {
		node2 = func0001a784(node);

		if (node2) {
			result = func0f028e18(prop2, node2, model, prop);
		} else if (prop2->parent && model->attachedtomodel && model->attachedtonode) {
			result = func0f028e18(prop2->parent, model->attachedtonode, model->attachedtomodel, prop);
		}
	}

	return result;
}

GLOBAL_ASM(
glabel func0f0293ec
/*  f0293ec:	27bdffc0 */ 	addiu	$sp,$sp,-64
/*  f0293f0:	afa40040 */ 	sw	$a0,0x40($sp)
/*  f0293f4:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f0293f8:	afa50044 */ 	sw	$a1,0x44($sp)
/*  f0293fc:	2403ffff */ 	addiu	$v1,$zero,-1
/*  f029400:	00a02025 */ 	or	$a0,$a1,$zero
/*  f029404:	27ae002c */ 	addiu	$t6,$sp,0x2c
/*  f029408:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f02940c:	8fa50040 */ 	lw	$a1,0x40($sp)
/*  f029410:	afa3003c */ 	sw	$v1,0x3c($sp)
/*  f029414:	27a60034 */ 	addiu	$a2,$sp,0x34
/*  f029418:	0fc0a39b */ 	jal	func0f028e6c
/*  f02941c:	27a70030 */ 	addiu	$a3,$sp,0x30
/*  f029420:	10400025 */ 	beqz	$v0,.L0f0294b8
/*  f029424:	8fa3003c */ 	lw	$v1,0x3c($sp)
/*  f029428:	8fa40030 */ 	lw	$a0,0x30($sp)
/*  f02942c:	50800023 */ 	beqzl	$a0,.L0f0294bc
/*  f029430:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f029434:	0c0069f3 */ 	jal	func0001a7cc
/*  f029438:	afa3003c */ 	sw	$v1,0x3c($sp)
/*  f02943c:	8fa3003c */ 	lw	$v1,0x3c($sp)
/*  f029440:	10400007 */ 	beqz	$v0,.L0f029460
/*  f029444:	00402825 */ 	or	$a1,$v0,$zero
/*  f029448:	8fa40034 */ 	lw	$a0,0x34($sp)
/*  f02944c:	8fa6002c */ 	lw	$a2,0x2c($sp)
/*  f029450:	0fc0a386 */ 	jal	func0f028e18
/*  f029454:	8fa70040 */ 	lw	$a3,0x40($sp)
/*  f029458:	10000017 */ 	b	.L0f0294b8
/*  f02945c:	00401825 */ 	or	$v1,$v0,$zero
.L0f029460:
/*  f029460:	8faf0034 */ 	lw	$t7,0x34($sp)
/*  f029464:	8de4001c */ 	lw	$a0,0x1c($t7)
/*  f029468:	50800014 */ 	beqzl	$a0,.L0f0294bc
/*  f02946c:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f029470:	8c860018 */ 	lw	$a2,0x18($a0)
.L0f029474:
/*  f029474:	8fb8002c */ 	lw	$t8,0x2c($sp)
/*  f029478:	8fa80030 */ 	lw	$t0,0x30($sp)
/*  f02947c:	8cd90018 */ 	lw	$t9,0x18($a2)
/*  f029480:	5719000b */ 	bnel	$t8,$t9,.L0f0294b0
/*  f029484:	8c840020 */ 	lw	$a0,0x20($a0)
/*  f029488:	8cc9001c */ 	lw	$t1,0x1c($a2)
/*  f02948c:	55090008 */ 	bnel	$t0,$t1,.L0f0294b0
/*  f029490:	8c840020 */ 	lw	$a0,0x20($a0)
/*  f029494:	8cca0008 */ 	lw	$t2,0x8($a2)
/*  f029498:	8fa70040 */ 	lw	$a3,0x40($sp)
/*  f02949c:	0fc0a386 */ 	jal	func0f028e18
/*  f0294a0:	8d450000 */ 	lw	$a1,0x0($t2)
/*  f0294a4:	10000004 */ 	b	.L0f0294b8
/*  f0294a8:	00401825 */ 	or	$v1,$v0,$zero
/*  f0294ac:	8c840020 */ 	lw	$a0,0x20($a0)
.L0f0294b0:
/*  f0294b0:	5480fff0 */ 	bnezl	$a0,.L0f029474
/*  f0294b4:	8c860018 */ 	lw	$a2,0x18($a0)
.L0f0294b8:
/*  f0294b8:	8fbf001c */ 	lw	$ra,0x1c($sp)
.L0f0294bc:
/*  f0294bc:	27bd0040 */ 	addiu	$sp,$sp,0x40
/*  f0294c0:	00601025 */ 	or	$v0,$v1,$zero
/*  f0294c4:	03e00008 */ 	jr	$ra
/*  f0294c8:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel func0f0294cc
/*  f0294cc:	27bdffc0 */ 	addiu	$sp,$sp,-64
/*  f0294d0:	afa40040 */ 	sw	$a0,0x40($sp)
/*  f0294d4:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f0294d8:	afa50044 */ 	sw	$a1,0x44($sp)
/*  f0294dc:	240effff */ 	addiu	$t6,$zero,-1
/*  f0294e0:	00a02025 */ 	or	$a0,$a1,$zero
/*  f0294e4:	27af002c */ 	addiu	$t7,$sp,0x2c
/*  f0294e8:	afae003c */ 	sw	$t6,0x3c($sp)
/*  f0294ec:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f0294f0:	8fa50040 */ 	lw	$a1,0x40($sp)
/*  f0294f4:	27a60034 */ 	addiu	$a2,$sp,0x34
/*  f0294f8:	0fc0a39b */ 	jal	func0f028e6c
/*  f0294fc:	27a70030 */ 	addiu	$a3,$sp,0x30
/*  f029500:	10400038 */ 	beqz	$v0,.L0f0295e4
/*  f029504:	8fa40030 */ 	lw	$a0,0x30($sp)
/*  f029508:	50800037 */ 	beqzl	$a0,.L0f0295e8
/*  f02950c:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f029510:	0c006a17 */ 	jal	func0001a85c
/*  f029514:	00000000 */ 	nop
/*  f029518:	10400007 */ 	beqz	$v0,.L0f029538
/*  f02951c:	00402825 */ 	or	$a1,$v0,$zero
/*  f029520:	8fa40034 */ 	lw	$a0,0x34($sp)
/*  f029524:	8fa6002c */ 	lw	$a2,0x2c($sp)
/*  f029528:	0fc0a386 */ 	jal	func0f028e18
/*  f02952c:	8fa70040 */ 	lw	$a3,0x40($sp)
/*  f029530:	1000002c */ 	b	.L0f0295e4
/*  f029534:	afa2003c */ 	sw	$v0,0x3c($sp)
.L0f029538:
/*  f029538:	0c0069e1 */ 	jal	func0001a784
/*  f02953c:	8fa40030 */ 	lw	$a0,0x30($sp)
/*  f029540:	14400028 */ 	bnez	$v0,.L0f0295e4
/*  f029544:	8fb80034 */ 	lw	$t8,0x34($sp)
/*  f029548:	8f020018 */ 	lw	$v0,0x18($t8)
/*  f02954c:	50400026 */ 	beqzl	$v0,.L0f0295e8
/*  f029550:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f029554:	8c44001c */ 	lw	$a0,0x1c($v0)
/*  f029558:	10800009 */ 	beqz	$a0,.L0f029580
/*  f02955c:	00000000 */ 	nop
/*  f029560:	10980007 */ 	beq	$a0,$t8,.L0f029580
/*  f029564:	00000000 */ 	nop
/*  f029568:	8c840020 */ 	lw	$a0,0x20($a0)
.L0f02956c:
/*  f02956c:	8fb90034 */ 	lw	$t9,0x34($sp)
/*  f029570:	10800003 */ 	beqz	$a0,.L0f029580
/*  f029574:	00000000 */ 	nop
/*  f029578:	5499fffc */ 	bnel	$a0,$t9,.L0f02956c
/*  f02957c:	8c840020 */ 	lw	$a0,0x20($a0)
.L0f029580:
/*  f029580:	50800019 */ 	beqzl	$a0,.L0f0295e8
/*  f029584:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f029588:	8c840020 */ 	lw	$a0,0x20($a0)
/*  f02958c:	8fa8002c */ 	lw	$t0,0x2c($sp)
/*  f029590:	50800015 */ 	beqzl	$a0,.L0f0295e8
/*  f029594:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f029598:	8d020018 */ 	lw	$v0,0x18($t0)
/*  f02959c:	8c860018 */ 	lw	$a2,0x18($a0)
.L0f0295a0:
/*  f0295a0:	8faa002c */ 	lw	$t2,0x2c($sp)
/*  f0295a4:	8cc90018 */ 	lw	$t1,0x18($a2)
/*  f0295a8:	5449000c */ 	bnel	$v0,$t1,.L0f0295dc
/*  f0295ac:	8c840020 */ 	lw	$a0,0x20($a0)
/*  f0295b0:	8d4b001c */ 	lw	$t3,0x1c($t2)
/*  f0295b4:	8ccc001c */ 	lw	$t4,0x1c($a2)
/*  f0295b8:	556c0008 */ 	bnel	$t3,$t4,.L0f0295dc
/*  f0295bc:	8c840020 */ 	lw	$a0,0x20($a0)
/*  f0295c0:	8ccd0008 */ 	lw	$t5,0x8($a2)
/*  f0295c4:	8fa70040 */ 	lw	$a3,0x40($sp)
/*  f0295c8:	0fc0a386 */ 	jal	func0f028e18
/*  f0295cc:	8da50000 */ 	lw	$a1,0x0($t5)
/*  f0295d0:	10000004 */ 	b	.L0f0295e4
/*  f0295d4:	afa2003c */ 	sw	$v0,0x3c($sp)
/*  f0295d8:	8c840020 */ 	lw	$a0,0x20($a0)
.L0f0295dc:
/*  f0295dc:	5480fff0 */ 	bnezl	$a0,.L0f0295a0
/*  f0295e0:	8c860018 */ 	lw	$a2,0x18($a0)
.L0f0295e4:
/*  f0295e4:	8fbf001c */ 	lw	$ra,0x1c($sp)
.L0f0295e8:
/*  f0295e8:	8fa2003c */ 	lw	$v0,0x3c($sp)
/*  f0295ec:	27bd0040 */ 	addiu	$sp,$sp,0x40
/*  f0295f0:	03e00008 */ 	jr	$ra
/*  f0295f4:	00000000 */ 	nop
);

void func0f0295f8(f32 arg0, s32 *arg1, s32 *arg2, s32 *arg3)
{
	if (arg0 < 1.5f) {
		*arg1 = 57 - (s32)((1.5f - arg0) * 28.0f);
		*arg2 = 75 - (s32)((1.5f - arg0) * 20.0f);
		*arg3 = 0;
		return;
	}

	if (arg0 < 3.0f) {
		*arg1 = 102 - (s32)((3.0f - arg0) * 30.0f);
		*arg2 = 90 - (s32)((3.0f - arg0) * 10.0f);
		*arg3 = 0;
		return;
	}

	if (arg0 < 4.5f) {
		*arg1 = 174 - (s32)((4.5f - arg0) * 48.0f);
		*arg2 = 129 - (s32)((4.5f - arg0) * 26.0f);
		*arg3 = 0;
		return;
	}

	if (arg0 < 6.0f) {
		*arg1 = 162 - (s32)((6.0f - arg0) * -8.0f);
		*arg2 = 54 - (s32)((6.0f - arg0) * -50.0f);
		*arg3 = 0;
		return;
	}

	*arg1 = 162;
	*arg2 = 54;
	*arg3 = 0;
}

f32 propGetShieldThing(struct prop **propptr)
{
	struct prop *prop = *propptr;

	if (prop->type == PROPTYPE_CHR || prop->type == PROPTYPE_PLAYER) {
		return chrGetShield(prop->chr);
	}

	if (prop->type == PROPTYPE_OBJ
			|| prop->type == PROPTYPE_WEAPON
			|| prop->type == PROPTYPE_DOOR) {
		if (prop->obj->flags3 & OBJFLAG3_SHOWSHIELD) {
			return 4;
		}

		// If this function is returning the shield amount,
		// why would it return 8 for all objects here?
		return 8;
	}

	return 0;
}

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0f02983c
.late_rodata
glabel var7f1a9b60pf
.word 0x3c40c0c1
glabel var7f1a9b64pf
.word 0x3c40c0c1
glabel var7f1a9b68pf
.word 0x3bcddaca
glabel var7f1a9b6cpf
.word 0x3bcddaca
glabel var7f1a9b70pf
.word 0x3f169697
glabel var7f1a9b74pf
.word 0x3ea0a0a1
glabel var7f1a9b78pf
.word 0x3e70f0f1
glabel var7f1a9b7cpf
.word 0x3e20a0a1
glabel var7f1a9b80pf
.word 0x3cb0d9df
glabel var7f1a9b84pf
.word 0x40cccccd
glabel var7f1a9b88pf
.word 0x3b808081
glabel var7f1a9b8cpf
.word 0x407745d1
glabel var7f1a9b90pf
.word 0x3b808081
glabel var7f1a9b94pf
.word 0x4099999a
glabel var7f1a9b98pf
.word 0x3b808081
glabel var7f1a9b9cpf
.word 0x407745d1
glabel var7f1a9ba0pf
.word 0x3b808081
.text
/*  f029960:	27bdfe10 */ 	addiu	$sp,$sp,-496
/*  f029964:	afb50038 */ 	sw	$s5,0x38($sp)
/*  f029968:	3c0e8006 */ 	lui	$t6,0x8006
/*  f02996c:	8fb50200 */ 	lw	$s5,0x200($sp)
/*  f029970:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f029974:	afb40034 */ 	sw	$s4,0x34($sp)
/*  f029978:	afb30030 */ 	sw	$s3,0x30($sp)
/*  f02997c:	afb2002c */ 	sw	$s2,0x2c($sp)
/*  f029980:	afb10028 */ 	sw	$s1,0x28($sp)
/*  f029984:	afb00024 */ 	sw	$s0,0x24($sp)
/*  f029988:	afa401f0 */ 	sw	$a0,0x1f0($sp)
/*  f02998c:	afa501f4 */ 	sw	$a1,0x1f4($sp)
/*  f029990:	afa601f8 */ 	sw	$a2,0x1f8($sp)
/*  f029994:	afa701fc */ 	sw	$a3,0x1fc($sp)
/*  f029998:	25ce2774 */ 	addiu	$t6,$t6,0x2774
/*  f02999c:	8dc10000 */ 	lw	$at,0x0($t6)
/*  f0299a0:	27b201e0 */ 	addiu	$s2,$sp,0x1e0
/*  f0299a4:	8eb30004 */ 	lw	$s3,0x4($s5)
/*  f0299a8:	ae410000 */ 	sw	$at,0x0($s2)
/*  f0299ac:	8dd90004 */ 	lw	$t9,0x4($t6)
/*  f0299b0:	3c0f8006 */ 	lui	$t7,0x8006
/*  f0299b4:	25ef2780 */ 	addiu	$t7,$t7,0x2780
/*  f0299b8:	ae590004 */ 	sw	$t9,0x4($s2)
/*  f0299bc:	8dc10008 */ 	lw	$at,0x8($t6)
/*  f0299c0:	25f90060 */ 	addiu	$t9,$t7,0x60
/*  f0299c4:	27b80104 */ 	addiu	$t8,$sp,0x104
/*  f0299c8:	ae410008 */ 	sw	$at,0x8($s2)
.PF0f0299cc:
/*  f0299cc:	8de10000 */ 	lw	$at,0x0($t7)
/*  f0299d0:	25ef000c */ 	addiu	$t7,$t7,0xc
/*  f0299d4:	2718000c */ 	addiu	$t8,$t8,0xc
/*  f0299d8:	af01fff4 */ 	sw	$at,-0xc($t8)
/*  f0299dc:	8de1fff8 */ 	lw	$at,-0x8($t7)
/*  f0299e0:	af01fff8 */ 	sw	$at,-0x8($t8)
/*  f0299e4:	8de1fffc */ 	lw	$at,-0x4($t7)
/*  f0299e8:	15f9fff8 */ 	bne	$t7,$t9,.PF0f0299cc
/*  f0299ec:	af01fffc */ 	sw	$at,-0x4($t8)
/*  f0299f0:	8fae01f8 */ 	lw	$t6,0x1f8($sp)
/*  f0299f4:	24010003 */ 	li	$at,0x3
/*  f0299f8:	24110006 */ 	li	$s1,0x6
/*  f0299fc:	91c40000 */ 	lbu	$a0,0x0($t6)
/*  f029a00:	8fb901f8 */ 	lw	$t9,0x1f8($sp)
/*  f029a04:	50810004 */ 	beql	$a0,$at,.PF0f029a18
/*  f029a08:	8f300004 */ 	lw	$s0,0x4($t9)
/*  f029a0c:	56240014 */ 	bnel	$s1,$a0,.PF0f029a60
/*  f029a10:	8fb901f8 */ 	lw	$t9,0x1f8($sp)
/*  f029a14:	8f300004 */ 	lw	$s0,0x4($t9)
.PF0f029a18:
/*  f029a18:	3c014120 */ 	lui	$at,0x4120
/*  f029a1c:	44812000 */ 	mtc1	$at,$f4
/*  f029a20:	8e0f0020 */ 	lw	$t7,0x20($s0)
/*  f029a24:	24110006 */ 	li	$s1,0x6
/*  f029a28:	02002025 */ 	move	$a0,$s0
/*  f029a2c:	c5e60014 */ 	lwc1	$f6,0x14($t7)
/*  f029a30:	46062083 */ 	div.s	$f2,$f4,$f6
/*  f029a34:	0fc0d042 */ 	jal	chrGetShield
/*  f029a38:	e7a20170 */ 	swc1	$f2,0x170($sp)
/*  f029a3c:	921402e1 */ 	lbu	$s4,0x2e1($s0)
/*  f029a40:	960e0188 */ 	lhu	$t6,0x188($s0)
/*  f029a44:	c7a20170 */ 	lwc1	$f2,0x170($sp)
/*  f029a48:	0014c042 */ 	srl	$t8,$s4,0x1
/*  f029a4c:	46000386 */ 	mov.s	$f14,$f0
/*  f029a50:	0300a025 */ 	move	$s4,$t8
/*  f029a54:	10000011 */ 	b	.PF0f029a9c
/*  f029a58:	afae0164 */ 	sw	$t6,0x164($sp)
/*  f029a5c:	8fb901f8 */ 	lw	$t9,0x1f8($sp)
.PF0f029a60:
/*  f029a60:	44801000 */ 	mtc1	$zero,$f2
/*  f029a64:	24140040 */ 	li	$s4,0x40
/*  f029a68:	8f220004 */ 	lw	$v0,0x4($t9)
/*  f029a6c:	afa00164 */ 	sw	$zero,0x164($sp)
/*  f029a70:	3c014100 */ 	lui	$at,0x4100
/*  f029a74:	8c4f0010 */ 	lw	$t7,0x10($v0)
/*  f029a78:	31f81000 */ 	andi	$t8,$t7,0x1000
/*  f029a7c:	53000006 */ 	beqzl	$t8,.PF0f029a98
/*  f029a80:	44817000 */ 	mtc1	$at,$f14
/*  f029a84:	3c014080 */ 	lui	$at,0x4080
/*  f029a88:	44817000 */ 	mtc1	$at,$f14
/*  f029a8c:	10000004 */ 	b	.PF0f029aa0
/*  f029a90:	02a02025 */ 	move	$a0,$s5
/*  f029a94:	44817000 */ 	mtc1	$at,$f14
.PF0f029a98:
/*  f029a98:	00000000 */ 	nop
.PF0f029a9c:
/*  f029a9c:	02a02025 */ 	move	$a0,$s5
.PF0f029aa0:
/*  f029aa0:	00002825 */ 	move	$a1,$zero
/*  f029aa4:	e7a20170 */ 	swc1	$f2,0x170($sp)
/*  f029aa8:	0c0068ad */ 	jal	func0001a524
/*  f029aac:	e7ae016c */ 	swc1	$f14,0x16c($sp)
/*  f029ab0:	c7a20170 */ 	lwc1	$f2,0x170($sp)
/*  f029ab4:	c6680004 */ 	lwc1	$f8,0x4($s3)
/*  f029ab8:	c6720008 */ 	lwc1	$f18,0x8($s3)
/*  f029abc:	8fae01fc */ 	lw	$t6,0x1fc($sp)
/*  f029ac0:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f029ac4:	c668000c */ 	lwc1	$f8,0xc($s3)
/*  f029ac8:	8dd9000c */ 	lw	$t9,0xc($t6)
/*  f029acc:	46029100 */ 	add.s	$f4,$f18,$f2
/*  f029ad0:	c6720010 */ 	lwc1	$f18,0x10($s3)
/*  f029ad4:	8fb001f0 */ 	lw	$s0,0x1f0($sp)
/*  f029ad8:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f029adc:	00027980 */ 	sll	$t7,$v0,0x6
/*  f029ae0:	032f2021 */ 	addu	$a0,$t9,$t7
/*  f029ae4:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f029ae8:	44038000 */ 	mfc1	$v1,$f16
/*  f029aec:	3c190102 */ 	lui	$t9,0x102
/*  f029af0:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f029af4:	c6680014 */ 	lwc1	$f8,0x14($s3)
/*  f029af8:	44053000 */ 	mfc1	$a1,$f6
/*  f029afc:	46029100 */ 	add.s	$f4,$f18,$f2
/*  f029b00:	c6720018 */ 	lwc1	$f18,0x18($s3)
/*  f029b04:	260a0008 */ 	addiu	$t2,$s0,0x8
/*  f029b08:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f029b0c:	c7ae016c */ 	lwc1	$f14,0x16c($sp)
/*  f029b10:	afaa01f0 */ 	sw	$t2,0x1f0($sp)
/*  f029b14:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f029b18:	44068000 */ 	mfc1	$a2,$f16
/*  f029b1c:	37390040 */ 	ori	$t9,$t9,0x40
/*  f029b20:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f029b24:	44073000 */ 	mfc1	$a3,$f6
/*  f029b28:	a7a30180 */ 	sh	$v1,0x180($sp)
/*  f029b2c:	46029100 */ 	add.s	$f4,$f18,$f2
/*  f029b30:	a7a30186 */ 	sh	$v1,0x186($sp)
/*  f029b34:	a7a3018c */ 	sh	$v1,0x18c($sp)
/*  f029b38:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f029b3c:	a7a30192 */ 	sh	$v1,0x192($sp)
/*  f029b40:	a7a50198 */ 	sh	$a1,0x198($sp)
/*  f029b44:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f029b48:	44088000 */ 	mfc1	$t0,$f16
/*  f029b4c:	a7a5019e */ 	sh	$a1,0x19e($sp)
/*  f029b50:	a7a501a4 */ 	sh	$a1,0x1a4($sp)
/*  f029b54:	44093000 */ 	mfc1	$t1,$f6
/*  f029b58:	a7a501aa */ 	sh	$a1,0x1aa($sp)
/*  f029b5c:	a7a60182 */ 	sh	$a2,0x182($sp)
/*  f029b60:	a7a60188 */ 	sh	$a2,0x188($sp)
/*  f029b64:	a7a6019a */ 	sh	$a2,0x19a($sp)
/*  f029b68:	a7a601a0 */ 	sh	$a2,0x1a0($sp)
/*  f029b6c:	a7a7018e */ 	sh	$a3,0x18e($sp)
/*  f029b70:	a7a70194 */ 	sh	$a3,0x194($sp)
/*  f029b74:	a7a701a6 */ 	sh	$a3,0x1a6($sp)
/*  f029b78:	a7a701ac */ 	sh	$a3,0x1ac($sp)
/*  f029b7c:	a7a80184 */ 	sh	$t0,0x184($sp)
/*  f029b80:	a7a80190 */ 	sh	$t0,0x190($sp)
/*  f029b84:	a7a8019c */ 	sh	$t0,0x19c($sp)
/*  f029b88:	a7a801a8 */ 	sh	$t0,0x1a8($sp)
/*  f029b8c:	a7a9018a */ 	sh	$t1,0x18a($sp)
/*  f029b90:	a7a90196 */ 	sh	$t1,0x196($sp)
/*  f029b94:	a7a901a2 */ 	sh	$t1,0x1a2($sp)
/*  f029b98:	a7a901ae */ 	sh	$t1,0x1ae($sp)
/*  f029b9c:	ae190000 */ 	sw	$t9,0x0($s0)
/*  f029ba0:	afa301cc */ 	sw	$v1,0x1cc($sp)
/*  f029ba4:	afa501c8 */ 	sw	$a1,0x1c8($sp)
/*  f029ba8:	e7ae016c */ 	swc1	$f14,0x16c($sp)
/*  f029bac:	afa601c4 */ 	sw	$a2,0x1c4($sp)
/*  f029bb0:	afa701c0 */ 	sw	$a3,0x1c0($sp)
/*  f029bb4:	afa801bc */ 	sw	$t0,0x1bc($sp)
/*  f029bb8:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f029bbc:	afa901b8 */ 	sw	$t1,0x1b8($sp)
/*  f029bc0:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f029bc4:	c7ae016c */ 	lwc1	$f14,0x16c($sp)
/*  f029bc8:	2401fff9 */ 	li	$at,-7
/*  f029bcc:	15010082 */ 	bne	$t0,$at,.PF0f029dd8
/*  f029bd0:	ae020004 */ 	sw	$v0,0x4($s0)
/*  f029bd4:	0fc5a253 */ 	jal	gfxAllocateColours
/*  f029bd8:	24040001 */ 	li	$a0,0x1
/*  f029bdc:	8fb001f0 */ 	lw	$s0,0x1f0($sp)
/*  f029be0:	3c0e0700 */ 	lui	$t6,0x700
/*  f029be4:	35ce0004 */ 	ori	$t6,$t6,0x4
/*  f029be8:	26180008 */ 	addiu	$t8,$s0,0x8
/*  f029bec:	afb801f0 */ 	sw	$t8,0x1f0($sp)
/*  f029bf0:	ae0e0000 */ 	sw	$t6,0x0($s0)
/*  f029bf4:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f029bf8:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f029bfc:	00402025 */ 	move	$a0,$v0
/*  f029c00:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f029c04:	ae020004 */ 	sw	$v0,0x4($s0)
/*  f029c08:	240400ff */ 	li	$a0,0xff
/*  f029c0c:	2a810040 */ 	slti	$at,$s4,0x40
/*  f029c10:	a0640000 */ 	sb	$a0,0x0($v1)
/*  f029c14:	a0640001 */ 	sb	$a0,0x1($v1)
/*  f029c18:	1020000f */ 	beqz	$at,.PF0f029c58
/*  f029c1c:	a0640002 */ 	sb	$a0,0x2($v1)
/*  f029c20:	8fb90210 */ 	lw	$t9,0x210($sp)
/*  f029c24:	44944000 */ 	mtc1	$s4,$f8
/*  f029c28:	3c017f1b */ 	lui	$at,0x7f1b
/*  f029c2c:	44998000 */ 	mtc1	$t9,$f16
/*  f029c30:	468042a0 */ 	cvt.s.w	$f10,$f8
/*  f029c34:	c4269b60 */ 	lwc1	$f6,-0x64a0($at)
/*  f029c38:	468084a0 */ 	cvt.s.w	$f18,$f16
/*  f029c3c:	46125102 */ 	mul.s	$f4,$f10,$f18
/*  f029c40:	00000000 */ 	nop
/*  f029c44:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f029c48:	4600440d */ 	trunc.w.s	$f16,$f8
/*  f029c4c:	44188000 */ 	mfc1	$t8,$f16
/*  f029c50:	10000011 */ 	b	.PF0f029c98
/*  f029c54:	a0780003 */ 	sb	$t8,0x3($v1)
.PF0f029c58:
/*  f029c58:	8faf0210 */ 	lw	$t7,0x210($sp)
/*  f029c5c:	240e007f */ 	li	$t6,0x7f
/*  f029c60:	01d4c823 */ 	subu	$t9,$t6,$s4
/*  f029c64:	44995000 */ 	mtc1	$t9,$f10
/*  f029c68:	448f2000 */ 	mtc1	$t7,$f4
/*  f029c6c:	3c017f1b */ 	lui	$at,0x7f1b
/*  f029c70:	468054a0 */ 	cvt.s.w	$f18,$f10
/*  f029c74:	c4309b64 */ 	lwc1	$f16,-0x649c($at)
/*  f029c78:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f029c7c:	46069202 */ 	mul.s	$f8,$f18,$f6
/*  f029c80:	00000000 */ 	nop
/*  f029c84:	46104282 */ 	mul.s	$f10,$f8,$f16
/*  f029c88:	4600510d */ 	trunc.w.s	$f4,$f10
/*  f029c8c:	440e2000 */ 	mfc1	$t6,$f4
/*  f029c90:	00000000 */ 	nop
/*  f029c94:	a06e0003 */ 	sb	$t6,0x3($v1)
.PF0f029c98:
/*  f029c98:	0fc5a239 */ 	jal	gfxAllocateVertices
/*  f029c9c:	24040018 */ 	li	$a0,0x18
/*  f029ca0:	00408025 */ 	move	$s0,$v0
/*  f029ca4:	27a60104 */ 	addiu	$a2,$sp,0x104
/*  f029ca8:	24090004 */ 	li	$t1,0x4
/*  f029cac:	24070200 */ 	li	$a3,0x200
/*  f029cb0:	27a50180 */ 	addiu	$a1,$sp,0x180
.PF0f029cb4:
/*  f029cb4:	00002025 */ 	move	$a0,$zero
/*  f029cb8:	02001825 */ 	move	$v1,$s0
/*  f029cbc:	00c01025 */ 	move	$v0,$a2
.PF0f029cc0:
/*  f029cc0:	8e410000 */ 	lw	$at,0x0($s2)
/*  f029cc4:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f029cc8:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f029ccc:	a861fff4 */ 	swl	$at,-0xc($v1)
/*  f029cd0:	b861fff7 */ 	swr	$at,-0x9($v1)
/*  f029cd4:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f029cd8:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f029cdc:	a86ffff8 */ 	swl	$t7,-0x8($v1)
/*  f029ce0:	b86ffffb */ 	swr	$t7,-0x5($v1)
/*  f029ce4:	8e410008 */ 	lw	$at,0x8($s2)
/*  f029ce8:	a861fffc */ 	swl	$at,-0x4($v1)
/*  f029cec:	b861ffff */ 	swr	$at,-0x1($v1)
/*  f029cf0:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f029cf4:	03110019 */ 	multu	$t8,$s1
/*  f029cf8:	00007012 */ 	mflo	$t6
/*  f029cfc:	00aec821 */ 	addu	$t9,$a1,$t6
/*  f029d00:	872f0000 */ 	lh	$t7,0x0($t9)
/*  f029d04:	a46ffff4 */ 	sh	$t7,-0xc($v1)
/*  f029d08:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f029d0c:	03110019 */ 	multu	$t8,$s1
/*  f029d10:	00007012 */ 	mflo	$t6
/*  f029d14:	00aec821 */ 	addu	$t9,$a1,$t6
/*  f029d18:	872f0002 */ 	lh	$t7,0x2($t9)
/*  f029d1c:	a46ffff6 */ 	sh	$t7,-0xa($v1)
/*  f029d20:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f029d24:	03110019 */ 	multu	$t8,$s1
/*  f029d28:	00007012 */ 	mflo	$t6
/*  f029d2c:	00aec821 */ 	addu	$t9,$a1,$t6
/*  f029d30:	872f0004 */ 	lh	$t7,0x4($t9)
/*  f029d34:	a060fffb */ 	sb	$zero,-0x5($v1)
/*  f029d38:	1489ffe1 */ 	bne	$a0,$t1,.PF0f029cc0
/*  f029d3c:	a46ffff8 */ 	sh	$t7,-0x8($v1)
/*  f029d40:	a6000008 */ 	sh	$zero,0x8($s0)
/*  f029d44:	a600000a */ 	sh	$zero,0xa($s0)
/*  f029d48:	a6070014 */ 	sh	$a3,0x14($s0)
/*  f029d4c:	a6000016 */ 	sh	$zero,0x16($s0)
/*  f029d50:	a6070020 */ 	sh	$a3,0x20($s0)
/*  f029d54:	a6070022 */ 	sh	$a3,0x22($s0)
/*  f029d58:	a600002c */ 	sh	$zero,0x2c($s0)
/*  f029d5c:	a607002e */ 	sh	$a3,0x2e($s0)
/*  f029d60:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f029d64:	3c190430 */ 	lui	$t9,0x430
/*  f029d68:	37390030 */ 	ori	$t9,$t9,0x30
/*  f029d6c:	270e0008 */ 	addiu	$t6,$t8,0x8
/*  f029d70:	afae01f0 */ 	sw	$t6,0x1f0($sp)
/*  f029d74:	af190000 */ 	sw	$t9,0x0($t8)
/*  f029d78:	afa60054 */ 	sw	$a2,0x54($sp)
/*  f029d7c:	02002025 */ 	move	$a0,$s0
/*  f029d80:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f029d84:	afb800c8 */ 	sw	$t8,0xc8($sp)
/*  f029d88:	8fa800c8 */ 	lw	$t0,0xc8($sp)
/*  f029d8c:	8fa60054 */ 	lw	$a2,0x54($sp)
/*  f029d90:	3c0eb100 */ 	lui	$t6,0xb100
/*  f029d94:	ad020004 */ 	sw	$v0,0x4($t0)
/*  f029d98:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
/*  f029d9c:	35ce0032 */ 	ori	$t6,$t6,0x32
/*  f029da0:	24192010 */ 	li	$t9,0x2010
/*  f029da4:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f029da8:	afb801f0 */ 	sw	$t8,0x1f0($sp)
/*  f029dac:	adf90004 */ 	sw	$t9,0x4($t7)
/*  f029db0:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f029db4:	27af0164 */ 	addiu	$t7,$sp,0x164
/*  f029db8:	24c60010 */ 	addiu	$a2,$a2,0x10
/*  f029dbc:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f029dc0:	24070200 */ 	li	$a3,0x200
/*  f029dc4:	24090004 */ 	li	$t1,0x4
/*  f029dc8:	14cfffba */ 	bne	$a2,$t7,.PF0f029cb4
/*  f029dcc:	26100030 */ 	addiu	$s0,$s0,0x30
/*  f029dd0:	100006c0 */ 	b	.PF0f02b8d4
/*  f029dd4:	8fbf003c */ 	lw	$ra,0x3c($sp)
.PF0f029dd8:
/*  f029dd8:	3c05800b */ 	lui	$a1,0x800b
/*  f029ddc:	24180002 */ 	li	$t8,0x2
/*  f029de0:	240e0001 */ 	li	$t6,0x1
/*  f029de4:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f029de8:	afb80010 */ 	sw	$t8,0x10($sp)
/*  f029dec:	8ca5bb2c */ 	lw	$a1,-0x44d4($a1)
/*  f029df0:	27a401f0 */ 	addiu	$a0,$sp,0x1f0
/*  f029df4:	24060004 */ 	li	$a2,0x4
/*  f029df8:	24070001 */ 	li	$a3,0x1
/*  f029dfc:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f029e00:	0fc2cfb8 */ 	jal	func0f0b39c0
/*  f029e04:	e7ae016c */ 	swc1	$f14,0x16c($sp)
/*  f029e08:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f029e0c:	c7ae016c */ 	lwc1	$f14,0x16c($sp)
/*  f029e10:	27a50100 */ 	addiu	$a1,$sp,0x100
/*  f029e14:	05000004 */ 	bltz	$t0,.PF0f029e28
/*  f029e18:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f029e1c:	8fb901f4 */ 	lw	$t9,0x1f4($sp)
/*  f029e20:	1000001c */ 	b	.PF0f029e94
/*  f029e24:	c72c0058 */ 	lwc1	$f12,0x58($t9)
.PF0f029e28:
/*  f029e28:	2401fffe */ 	li	$at,-2
/*  f029e2c:	15010019 */ 	bne	$t0,$at,.PF0f029e94
/*  f029e30:	46007306 */ 	mov.s	$f12,$f14
/*  f029e34:	8faf01f4 */ 	lw	$t7,0x1f4($sp)
/*  f029e38:	8fb8020c */ 	lw	$t8,0x20c($sp)
/*  f029e3c:	81e20011 */ 	lb	$v0,0x11($t7)
/*  f029e40:	0058082a */ 	slt	$at,$v0,$t8
/*  f029e44:	50200005 */ 	beqzl	$at,.PF0f029e5c
/*  f029e48:	44823000 */ 	mtc1	$v0,$f6
/*  f029e4c:	44806000 */ 	mtc1	$zero,$f12
/*  f029e50:	10000010 */ 	b	.PF0f029e94
/*  f029e54:	00000000 */ 	nop
/*  f029e58:	44823000 */ 	mtc1	$v0,$f6
.PF0f029e5c:
/*  f029e5c:	8fae020c */ 	lw	$t6,0x20c($sp)
/*  f029e60:	3c014080 */ 	lui	$at,0x4080
/*  f029e64:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f029e68:	44819000 */ 	mtc1	$at,$f18
/*  f029e6c:	448e8000 */ 	mtc1	$t6,$f16
/*  f029e70:	3c013f80 */ 	lui	$at,0x3f80
/*  f029e74:	44813000 */ 	mtc1	$at,$f6
/*  f029e78:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f029e7c:	46089002 */ 	mul.s	$f0,$f18,$f8
/*  f029e80:	460a0101 */ 	sub.s	$f4,$f0,$f10
/*  f029e84:	46062480 */ 	add.s	$f18,$f4,$f6
/*  f029e88:	46009203 */ 	div.s	$f8,$f18,$f0
/*  f029e8c:	46087302 */ 	mul.s	$f12,$f14,$f8
/*  f029e90:	00000000 */ 	nop
.PF0f029e94:
/*  f029e94:	0fc0a5c7 */ 	jal	func0f0295f8
/*  f029e98:	27a700f8 */ 	addiu	$a3,$sp,0xf8
/*  f029e9c:	8fac0100 */ 	lw	$t4,0x100($sp)
/*  f029ea0:	8fad00fc */ 	lw	$t5,0xfc($sp)
/*  f029ea4:	8fbf00f8 */ 	lw	$ra,0xf8($sp)
/*  f029ea8:	2587ffec */ 	addiu	$a3,$t4,-20
/*  f029eac:	25a3ffec */ 	addiu	$v1,$t5,-20
/*  f029eb0:	27e4ffec */ 	addiu	$a0,$ra,-20
/*  f029eb4:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f029eb8:	00605025 */ 	move	$t2,$v1
/*  f029ebc:	04e10002 */ 	bgez	$a3,.PF0f029ec8
/*  f029ec0:	00805825 */ 	move	$t3,$a0
/*  f029ec4:	00003825 */ 	move	$a3,$zero
.PF0f029ec8:
/*  f029ec8:	04610002 */ 	bgez	$v1,.PF0f029ed4
/*  f029ecc:	2582ffc4 */ 	addiu	$v0,$t4,-60
/*  f029ed0:	00005025 */ 	move	$t2,$zero
.PF0f029ed4:
/*  f029ed4:	04810002 */ 	bgez	$a0,.PF0f029ee0
/*  f029ed8:	25a3ffc4 */ 	addiu	$v1,$t5,-60
/*  f029edc:	00005825 */ 	move	$t3,$zero
.PF0f029ee0:
/*  f029ee0:	27e4ffc4 */ 	addiu	$a0,$ra,-60
/*  f029ee4:	afa200e8 */ 	sw	$v0,0xe8($sp)
/*  f029ee8:	afa300e4 */ 	sw	$v1,0xe4($sp)
/*  f029eec:	04410002 */ 	bgez	$v0,.PF0f029ef8
/*  f029ef0:	afa400e0 */ 	sw	$a0,0xe0($sp)
/*  f029ef4:	afa000e8 */ 	sw	$zero,0xe8($sp)
.PF0f029ef8:
/*  f029ef8:	04610002 */ 	bgez	$v1,.PF0f029f04
/*  f029efc:	3c19800a */ 	lui	$t9,0x800a
/*  f029f00:	afa000e4 */ 	sw	$zero,0xe4($sp)
.PF0f029f04:
/*  f029f04:	04810002 */ 	bgez	$a0,.PF0f029f10
/*  f029f08:	00000000 */ 	nop
/*  f029f0c:	afa000e0 */ 	sw	$zero,0xe0($sp)
.PF0f029f10:
/*  f029f10:	8f39a568 */ 	lw	$t9,-0x5a98($t9)
/*  f029f14:	241003e8 */ 	li	$s0,0x3e8
/*  f029f18:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f029f1c:	0330001a */ 	div	$zero,$t9,$s0
/*  f029f20:	00007810 */ 	mfhi	$t7
/*  f029f24:	448f8000 */ 	mtc1	$t7,$f16
/*  f029f28:	16000002 */ 	bnez	$s0,.PF0f029f34
/*  f029f2c:	00000000 */ 	nop
/*  f029f30:	0007000d */ 	break	0x7
.PF0f029f34:
/*  f029f34:	2401ffff */ 	li	$at,-1
/*  f029f38:	16010004 */ 	bne	$s0,$at,.PF0f029f4c
/*  f029f3c:	3c018000 */ 	lui	$at,0x8000
/*  f029f40:	17210002 */ 	bne	$t9,$at,.PF0f029f4c
/*  f029f44:	00000000 */ 	nop
/*  f029f48:	0006000d */ 	break	0x6
.PF0f029f4c:
/*  f029f4c:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f029f50:	3c017f1b */ 	lui	$at,0x7f1b
/*  f029f54:	c4249b68 */ 	lwc1	$f4,-0x6498($at)
/*  f029f58:	afaa00f0 */ 	sw	$t2,0xf0($sp)
/*  f029f5c:	afab00ec */ 	sw	$t3,0xec($sp)
/*  f029f60:	46045302 */ 	mul.s	$f12,$f10,$f4
/*  f029f64:	0c00685b */ 	jal	sinf
/*  f029f68:	00000000 */ 	nop
/*  f029f6c:	3c0f800a */ 	lui	$t7,0x800a
/*  f029f70:	8defa568 */ 	lw	$t7,-0x5a98($t7)
/*  f029f74:	3c014200 */ 	lui	$at,0x4200
/*  f029f78:	44811000 */ 	mtc1	$at,$f2
/*  f029f7c:	01f0001a */ 	div	$zero,$t7,$s0
/*  f029f80:	3c013f80 */ 	lui	$at,0x3f80
/*  f029f84:	44813000 */ 	mtc1	$at,$f6
/*  f029f88:	3c013f00 */ 	lui	$at,0x3f00
/*  f029f8c:	44814000 */ 	mtc1	$at,$f8
/*  f029f90:	46060480 */ 	add.s	$f18,$f0,$f6
/*  f029f94:	0000c010 */ 	mfhi	$t8
/*  f029f98:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f029f9c:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f029fa0:	46089402 */ 	mul.s	$f16,$f18,$f8
/*  f029fa4:	44989000 */ 	mtc1	$t8,$f18
/*  f029fa8:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f029fac:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f029fb0:	46809220 */ 	cvt.s.w	$f8,$f18
/*  f029fb4:	46028282 */ 	mul.s	$f10,$f16,$f2
/*  f029fb8:	00000000 */ 	nop
/*  f029fbc:	46025102 */ 	mul.s	$f4,$f10,$f2
/*  f029fc0:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f029fc4:	44153000 */ 	mfc1	$s5,$f6
/*  f029fc8:	00000000 */ 	nop
/*  f029fcc:	00157400 */ 	sll	$t6,$s5,0x10
/*  f029fd0:	000ecc03 */ 	sra	$t9,$t6,0x10
/*  f029fd4:	0320a825 */ 	move	$s5,$t9
/*  f029fd8:	16000002 */ 	bnez	$s0,.PF0f029fe4
/*  f029fdc:	00000000 */ 	nop
/*  f029fe0:	0007000d */ 	break	0x7
.PF0f029fe4:
/*  f029fe4:	2401ffff */ 	li	$at,-1
/*  f029fe8:	16010004 */ 	bne	$s0,$at,.PF0f029ffc
/*  f029fec:	3c018000 */ 	lui	$at,0x8000
/*  f029ff0:	15e10002 */ 	bne	$t7,$at,.PF0f029ffc
/*  f029ff4:	00000000 */ 	nop
/*  f029ff8:	0006000d */ 	break	0x6
.PF0f029ffc:
/*  f029ffc:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02a000:	c4309b6c */ 	lwc1	$f16,-0x6494($at)
/*  f02a004:	46104302 */ 	mul.s	$f12,$f8,$f16
/*  f02a008:	0c006858 */ 	jal	cosf
/*  f02a00c:	00000000 */ 	nop
/*  f02a010:	3c014200 */ 	lui	$at,0x4200
/*  f02a014:	44811000 */ 	mtc1	$at,$f2
/*  f02a018:	3c013f80 */ 	lui	$at,0x3f80
/*  f02a01c:	44816000 */ 	mtc1	$at,$f12
/*  f02a020:	3c013f00 */ 	lui	$at,0x3f00
/*  f02a024:	44812000 */ 	mtc1	$at,$f4
/*  f02a028:	460c0280 */ 	add.s	$f10,$f0,$f12
/*  f02a02c:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f02a030:	26af0200 */ 	addiu	$t7,$s5,0x200
/*  f02a034:	2401fffd */ 	li	$at,-3
/*  f02a038:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f02a03c:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f02a040:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f02a044:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f02a048:	afaf0050 */ 	sw	$t7,0x50($sp)
/*  f02a04c:	a7af0176 */ 	sh	$t7,0x176($sp)
/*  f02a050:	24040001 */ 	li	$a0,0x1
/*  f02a054:	46023482 */ 	mul.s	$f18,$f6,$f2
/*  f02a058:	00000000 */ 	nop
/*  f02a05c:	46029202 */ 	mul.s	$f8,$f18,$f2
/*  f02a060:	4600440d */ 	trunc.w.s	$f16,$f8
/*  f02a064:	440e8000 */ 	mfc1	$t6,$f16
/*  f02a068:	00000000 */ 	nop
/*  f02a06c:	000e9c00 */ 	sll	$s3,$t6,0x10
/*  f02a070:	0013cc03 */ 	sra	$t9,$s3,0x10
/*  f02a074:	03209825 */ 	move	$s3,$t9
/*  f02a078:	25d40200 */ 	addiu	$s4,$t6,0x200
/*  f02a07c:	0014cc00 */ 	sll	$t9,$s4,0x10
/*  f02a080:	11010008 */ 	beq	$t0,$at,.PF0f02a0a4
/*  f02a084:	0019a403 */ 	sra	$s4,$t9,0x10
/*  f02a088:	2401fffc */ 	li	$at,-4
/*  f02a08c:	11010005 */ 	beq	$t0,$at,.PF0f02a0a4
/*  f02a090:	2401fffb */ 	li	$at,-5
/*  f02a094:	11010003 */ 	beq	$t0,$at,.PF0f02a0a4
/*  f02a098:	2401fffa */ 	li	$at,-6
/*  f02a09c:	5501016b */ 	bnel	$t0,$at,.PF0f02a64c
/*  f02a0a0:	2401fffe */ 	li	$at,-2
.PF0f02a0a4:
/*  f02a0a4:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f02a0a8:	afaa00f0 */ 	sw	$t2,0xf0($sp)
/*  f02a0ac:	0fc5a253 */ 	jal	gfxAllocateColours
/*  f02a0b0:	afab00ec */ 	sw	$t3,0xec($sp)
/*  f02a0b4:	8fb001f0 */ 	lw	$s0,0x1f0($sp)
/*  f02a0b8:	3c190700 */ 	lui	$t9,0x700
/*  f02a0bc:	37390004 */ 	ori	$t9,$t9,0x4
/*  f02a0c0:	260e0008 */ 	addiu	$t6,$s0,0x8
/*  f02a0c4:	afae01f0 */ 	sw	$t6,0x1f0($sp)
/*  f02a0c8:	ae190000 */ 	sw	$t9,0x0($s0)
/*  f02a0cc:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f02a0d0:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f02a0d4:	00402025 */ 	move	$a0,$v0
/*  f02a0d8:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f02a0dc:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02a0e0:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f02a0e4:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f02a0e8:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f02a0ec:	2401fffd */ 	li	$at,-3
/*  f02a0f0:	15010014 */ 	bne	$t0,$at,.PF0f02a144
/*  f02a0f4:	ae020004 */ 	sw	$v0,0x4($s0)
/*  f02a0f8:	a0670000 */ 	sb	$a3,0x0($v1)
/*  f02a0fc:	a06a0001 */ 	sb	$t2,0x1($v1)
/*  f02a100:	a06b0002 */ 	sb	$t3,0x2($v1)
/*  f02a104:	8faf0164 */ 	lw	$t7,0x164($sp)
/*  f02a108:	8fb80210 */ 	lw	$t8,0x210($sp)
/*  f02a10c:	29e1000a */ 	slti	$at,$t7,0xa
/*  f02a110:	1020000a */ 	beqz	$at,.PF0f02a13c
/*  f02a114:	00000000 */ 	nop
/*  f02a118:	44985000 */ 	mtc1	$t8,$f10
/*  f02a11c:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02a120:	c4269b70 */ 	lwc1	$f6,-0x6490($at)
/*  f02a124:	46805120 */ 	cvt.s.w	$f4,$f10
/*  f02a128:	46062482 */ 	mul.s	$f18,$f4,$f6
/*  f02a12c:	4600920d */ 	trunc.w.s	$f8,$f18
/*  f02a130:	44194000 */ 	mfc1	$t9,$f8
/*  f02a134:	10000031 */ 	b	.PF0f02a1fc
/*  f02a138:	a0790003 */ 	sb	$t9,0x3($v1)
.PF0f02a13c:
/*  f02a13c:	1000002f */ 	b	.PF0f02a1fc
/*  f02a140:	a0600003 */ 	sb	$zero,0x3($v1)
.PF0f02a144:
/*  f02a144:	8faf00e8 */ 	lw	$t7,0xe8($sp)
/*  f02a148:	a06f0000 */ 	sb	$t7,0x0($v1)
/*  f02a14c:	8fb800e4 */ 	lw	$t8,0xe4($sp)
/*  f02a150:	a0780001 */ 	sb	$t8,0x1($v1)
/*  f02a154:	8fae00e0 */ 	lw	$t6,0xe0($sp)
/*  f02a158:	a06e0002 */ 	sb	$t6,0x2($v1)
/*  f02a15c:	8fb90164 */ 	lw	$t9,0x164($sp)
/*  f02a160:	2b21000a */ 	slti	$at,$t9,0xa
/*  f02a164:	10200024 */ 	beqz	$at,.PF0f02a1f8
/*  f02a168:	2401fffc */ 	li	$at,-4
/*  f02a16c:	1501000a */ 	bne	$t0,$at,.PF0f02a198
/*  f02a170:	8faf0210 */ 	lw	$t7,0x210($sp)
/*  f02a174:	448f8000 */ 	mtc1	$t7,$f16
/*  f02a178:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02a17c:	c4249b74 */ 	lwc1	$f4,-0x648c($at)
/*  f02a180:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f02a184:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f02a188:	4600348d */ 	trunc.w.s	$f18,$f6
/*  f02a18c:	440e9000 */ 	mfc1	$t6,$f18
/*  f02a190:	1000001a */ 	b	.PF0f02a1fc
/*  f02a194:	a06e0003 */ 	sb	$t6,0x3($v1)
.PF0f02a198:
/*  f02a198:	2401fffb */ 	li	$at,-5
/*  f02a19c:	1501000a */ 	bne	$t0,$at,.PF0f02a1c8
/*  f02a1a0:	8fb90210 */ 	lw	$t9,0x210($sp)
/*  f02a1a4:	44994000 */ 	mtc1	$t9,$f8
/*  f02a1a8:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02a1ac:	c42a9b78 */ 	lwc1	$f10,-0x6488($at)
/*  f02a1b0:	46804420 */ 	cvt.s.w	$f16,$f8
/*  f02a1b4:	460a8102 */ 	mul.s	$f4,$f16,$f10
/*  f02a1b8:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f02a1bc:	44183000 */ 	mfc1	$t8,$f6
/*  f02a1c0:	1000000e */ 	b	.PF0f02a1fc
/*  f02a1c4:	a0780003 */ 	sb	$t8,0x3($v1)
.PF0f02a1c8:
/*  f02a1c8:	2401fffa */ 	li	$at,-6
/*  f02a1cc:	1501000b */ 	bne	$t0,$at,.PF0f02a1fc
/*  f02a1d0:	8fae0210 */ 	lw	$t6,0x210($sp)
/*  f02a1d4:	448e9000 */ 	mtc1	$t6,$f18
/*  f02a1d8:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02a1dc:	c4309b7c */ 	lwc1	$f16,-0x6484($at)
/*  f02a1e0:	46809220 */ 	cvt.s.w	$f8,$f18
/*  f02a1e4:	46104282 */ 	mul.s	$f10,$f8,$f16
/*  f02a1e8:	4600510d */ 	trunc.w.s	$f4,$f10
/*  f02a1ec:	440f2000 */ 	mfc1	$t7,$f4
/*  f02a1f0:	10000002 */ 	b	.PF0f02a1fc
/*  f02a1f4:	a06f0003 */ 	sb	$t7,0x3($v1)
.PF0f02a1f8:
/*  f02a1f8:	a0600003 */ 	sb	$zero,0x3($v1)
.PF0f02a1fc:
/*  f02a1fc:	24040018 */ 	li	$a0,0x18
/*  f02a200:	afa301d8 */ 	sw	$v1,0x1d8($sp)
/*  f02a204:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f02a208:	afaa00f0 */ 	sw	$t2,0xf0($sp)
/*  f02a20c:	0fc5a239 */ 	jal	gfxAllocateVertices
/*  f02a210:	afab00ec */ 	sw	$t3,0xec($sp)
/*  f02a214:	8fa501f8 */ 	lw	$a1,0x1f8($sp)
/*  f02a218:	24010001 */ 	li	$at,0x1
/*  f02a21c:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02a220:	90a40000 */ 	lbu	$a0,0x0($a1)
/*  f02a224:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f02a228:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f02a22c:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f02a230:	10810006 */ 	beq	$a0,$at,.PF0f02a24c
/*  f02a234:	00408025 */ 	move	$s0,$v0
/*  f02a238:	24090004 */ 	li	$t1,0x4
/*  f02a23c:	11240003 */ 	beq	$t1,$a0,.PF0f02a24c
/*  f02a240:	24010002 */ 	li	$at,0x2
/*  f02a244:	548100b0 */ 	bnel	$a0,$at,.PF0f02a508
/*  f02a248:	24080200 */ 	li	$t0,0x200
.PF0f02a24c:
/*  f02a24c:	8cb80004 */ 	lw	$t8,0x4($a1)
/*  f02a250:	24090004 */ 	li	$t1,0x4
/*  f02a254:	3c0f800a */ 	lui	$t7,0x800a
/*  f02a258:	8f0e0010 */ 	lw	$t6,0x10($t8)
/*  f02a25c:	31d91000 */ 	andi	$t9,$t6,0x1000
/*  f02a260:	532000a9 */ 	beqzl	$t9,.PF0f02a508
/*  f02a264:	24080200 */ 	li	$t0,0x200
/*  f02a268:	8defa568 */ 	lw	$t7,-0x5a98($t7)
/*  f02a26c:	24010123 */ 	li	$at,0x123
/*  f02a270:	afa301d8 */ 	sw	$v1,0x1d8($sp)
/*  f02a274:	01e1001a */ 	div	$zero,$t7,$at
/*  f02a278:	0000c010 */ 	mfhi	$t8
/*  f02a27c:	44983000 */ 	mtc1	$t8,$f6
/*  f02a280:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02a284:	c4289b80 */ 	lwc1	$f8,-0x6480($at)
/*  f02a288:	468034a0 */ 	cvt.s.w	$f18,$f6
/*  f02a28c:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f02a290:	afaa00f0 */ 	sw	$t2,0xf0($sp)
/*  f02a294:	afab00ec */ 	sw	$t3,0xec($sp)
/*  f02a298:	46089302 */ 	mul.s	$f12,$f18,$f8
/*  f02a29c:	0c00685b */ 	jal	sinf
/*  f02a2a0:	00000000 */ 	nop
/*  f02a2a4:	3c013f80 */ 	lui	$at,0x3f80
/*  f02a2a8:	44818000 */ 	mtc1	$at,$f16
/*  f02a2ac:	3c013f00 */ 	lui	$at,0x3f00
/*  f02a2b0:	44812000 */ 	mtc1	$at,$f4
/*  f02a2b4:	46100280 */ 	add.s	$f10,$f0,$f16
/*  f02a2b8:	3c0142f0 */ 	lui	$at,0x42f0
/*  f02a2bc:	44813000 */ 	mtc1	$at,$f6
/*  f02a2c0:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f02a2c4:	46045302 */ 	mul.s	$f12,$f10,$f4
/*  f02a2c8:	3c014248 */ 	lui	$at,0x4248
/*  f02a2cc:	44818000 */ 	mtc1	$at,$f16
/*  f02a2d0:	30ee00ff */ 	andi	$t6,$a3,0xff
/*  f02a2d4:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02a2d8:	448e5000 */ 	mtc1	$t6,$f10
/*  f02a2dc:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f02a2e0:	460c3482 */ 	mul.s	$f18,$f6,$f12
/*  f02a2e4:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f02a2e8:	24090004 */ 	li	$t1,0x4
/*  f02a2ec:	460c8082 */ 	mul.s	$f2,$f16,$f12
/*  f02a2f0:	3c014f80 */ 	lui	$at,0x4f80
/*  f02a2f4:	4600920d */ 	trunc.w.s	$f8,$f18
/*  f02a2f8:	46805120 */ 	cvt.s.w	$f4,$f10
/*  f02a2fc:	440f4000 */ 	mfc1	$t7,$f8
/*  f02a300:	00000000 */ 	nop
/*  f02a304:	25f80032 */ 	addiu	$t8,$t7,0x32
/*  f02a308:	05c10004 */ 	bgez	$t6,.PF0f02a31c
/*  f02a30c:	a0780003 */ 	sb	$t8,0x3($v1)
/*  f02a310:	44813000 */ 	mtc1	$at,$f6
/*  f02a314:	00000000 */ 	nop
/*  f02a318:	46062100 */ 	add.s	$f4,$f4,$f6
.PF0f02a31c:
/*  f02a31c:	46022480 */ 	add.s	$f18,$f4,$f2
/*  f02a320:	240f0001 */ 	li	$t7,0x1
/*  f02a324:	3c014f00 */ 	lui	$at,0x4f00
/*  f02a328:	315800ff */ 	andi	$t8,$t2,0xff
/*  f02a32c:	4459f800 */ 	cfc1	$t9,$31
/*  f02a330:	44cff800 */ 	ctc1	$t7,$31
/*  f02a334:	00000000 */ 	nop
/*  f02a338:	46009224 */ 	cvt.w.s	$f8,$f18
/*  f02a33c:	444ff800 */ 	cfc1	$t7,$31
/*  f02a340:	00000000 */ 	nop
/*  f02a344:	31ef0078 */ 	andi	$t7,$t7,0x78
/*  f02a348:	51e00013 */ 	beqzl	$t7,.PF0f02a398
/*  f02a34c:	440f4000 */ 	mfc1	$t7,$f8
/*  f02a350:	44814000 */ 	mtc1	$at,$f8
/*  f02a354:	240f0001 */ 	li	$t7,0x1
/*  f02a358:	46089201 */ 	sub.s	$f8,$f18,$f8
/*  f02a35c:	44cff800 */ 	ctc1	$t7,$31
/*  f02a360:	00000000 */ 	nop
/*  f02a364:	46004224 */ 	cvt.w.s	$f8,$f8
/*  f02a368:	444ff800 */ 	cfc1	$t7,$31
/*  f02a36c:	00000000 */ 	nop
/*  f02a370:	31ef0078 */ 	andi	$t7,$t7,0x78
/*  f02a374:	15e00005 */ 	bnez	$t7,.PF0f02a38c
/*  f02a378:	00000000 */ 	nop
/*  f02a37c:	440f4000 */ 	mfc1	$t7,$f8
/*  f02a380:	3c018000 */ 	lui	$at,0x8000
/*  f02a384:	10000007 */ 	b	.PF0f02a3a4
/*  f02a388:	01e17825 */ 	or	$t7,$t7,$at
.PF0f02a38c:
/*  f02a38c:	10000005 */ 	b	.PF0f02a3a4
/*  f02a390:	240fffff */ 	li	$t7,-1
/*  f02a394:	440f4000 */ 	mfc1	$t7,$f8
.PF0f02a398:
/*  f02a398:	00000000 */ 	nop
/*  f02a39c:	05e0fffb */ 	bltz	$t7,.PF0f02a38c
/*  f02a3a0:	00000000 */ 	nop
.PF0f02a3a4:
/*  f02a3a4:	44d9f800 */ 	ctc1	$t9,$31
/*  f02a3a8:	44988000 */ 	mtc1	$t8,$f16
/*  f02a3ac:	a06f0000 */ 	sb	$t7,0x0($v1)
/*  f02a3b0:	07010005 */ 	bgez	$t8,.PF0f02a3c8
/*  f02a3b4:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f02a3b8:	3c014f80 */ 	lui	$at,0x4f80
/*  f02a3bc:	44813000 */ 	mtc1	$at,$f6
/*  f02a3c0:	00000000 */ 	nop
/*  f02a3c4:	46065280 */ 	add.s	$f10,$f10,$f6
.PF0f02a3c8:
/*  f02a3c8:	46025100 */ 	add.s	$f4,$f10,$f2
/*  f02a3cc:	24190001 */ 	li	$t9,0x1
/*  f02a3d0:	3c014f00 */ 	lui	$at,0x4f00
/*  f02a3d4:	316f00ff */ 	andi	$t7,$t3,0xff
/*  f02a3d8:	444ef800 */ 	cfc1	$t6,$31
/*  f02a3dc:	44d9f800 */ 	ctc1	$t9,$31
/*  f02a3e0:	00000000 */ 	nop
/*  f02a3e4:	460024a4 */ 	cvt.w.s	$f18,$f4
/*  f02a3e8:	4459f800 */ 	cfc1	$t9,$31
/*  f02a3ec:	00000000 */ 	nop
/*  f02a3f0:	33390078 */ 	andi	$t9,$t9,0x78
/*  f02a3f4:	53200013 */ 	beqzl	$t9,.PF0f02a444
/*  f02a3f8:	44199000 */ 	mfc1	$t9,$f18
/*  f02a3fc:	44819000 */ 	mtc1	$at,$f18
/*  f02a400:	24190001 */ 	li	$t9,0x1
/*  f02a404:	46122481 */ 	sub.s	$f18,$f4,$f18
/*  f02a408:	44d9f800 */ 	ctc1	$t9,$31
/*  f02a40c:	00000000 */ 	nop
/*  f02a410:	460094a4 */ 	cvt.w.s	$f18,$f18
/*  f02a414:	4459f800 */ 	cfc1	$t9,$31
/*  f02a418:	00000000 */ 	nop
/*  f02a41c:	33390078 */ 	andi	$t9,$t9,0x78
/*  f02a420:	17200005 */ 	bnez	$t9,.PF0f02a438
/*  f02a424:	00000000 */ 	nop
/*  f02a428:	44199000 */ 	mfc1	$t9,$f18
/*  f02a42c:	3c018000 */ 	lui	$at,0x8000
/*  f02a430:	10000007 */ 	b	.PF0f02a450
/*  f02a434:	0321c825 */ 	or	$t9,$t9,$at
.PF0f02a438:
/*  f02a438:	10000005 */ 	b	.PF0f02a450
/*  f02a43c:	2419ffff */ 	li	$t9,-1
/*  f02a440:	44199000 */ 	mfc1	$t9,$f18
.PF0f02a444:
/*  f02a444:	00000000 */ 	nop
/*  f02a448:	0720fffb */ 	bltz	$t9,.PF0f02a438
/*  f02a44c:	00000000 */ 	nop
.PF0f02a450:
/*  f02a450:	44cef800 */ 	ctc1	$t6,$31
/*  f02a454:	448f4000 */ 	mtc1	$t7,$f8
/*  f02a458:	a0790001 */ 	sb	$t9,0x1($v1)
/*  f02a45c:	05e10005 */ 	bgez	$t7,.PF0f02a474
/*  f02a460:	46804420 */ 	cvt.s.w	$f16,$f8
/*  f02a464:	3c014f80 */ 	lui	$at,0x4f80
/*  f02a468:	44813000 */ 	mtc1	$at,$f6
/*  f02a46c:	00000000 */ 	nop
/*  f02a470:	46068400 */ 	add.s	$f16,$f16,$f6
.PF0f02a474:
/*  f02a474:	46028280 */ 	add.s	$f10,$f16,$f2
/*  f02a478:	240e0001 */ 	li	$t6,0x1
/*  f02a47c:	3c014f00 */ 	lui	$at,0x4f00
/*  f02a480:	4458f800 */ 	cfc1	$t8,$31
/*  f02a484:	44cef800 */ 	ctc1	$t6,$31
/*  f02a488:	00000000 */ 	nop
/*  f02a48c:	46005124 */ 	cvt.w.s	$f4,$f10
/*  f02a490:	444ef800 */ 	cfc1	$t6,$31
/*  f02a494:	00000000 */ 	nop
/*  f02a498:	31ce0078 */ 	andi	$t6,$t6,0x78
/*  f02a49c:	51c00013 */ 	beqzl	$t6,.PF0f02a4ec
/*  f02a4a0:	440e2000 */ 	mfc1	$t6,$f4
/*  f02a4a4:	44812000 */ 	mtc1	$at,$f4
/*  f02a4a8:	240e0001 */ 	li	$t6,0x1
/*  f02a4ac:	46045101 */ 	sub.s	$f4,$f10,$f4
/*  f02a4b0:	44cef800 */ 	ctc1	$t6,$31
/*  f02a4b4:	00000000 */ 	nop
/*  f02a4b8:	46002124 */ 	cvt.w.s	$f4,$f4
/*  f02a4bc:	444ef800 */ 	cfc1	$t6,$31
/*  f02a4c0:	00000000 */ 	nop
/*  f02a4c4:	31ce0078 */ 	andi	$t6,$t6,0x78
/*  f02a4c8:	15c00005 */ 	bnez	$t6,.PF0f02a4e0
/*  f02a4cc:	00000000 */ 	nop
/*  f02a4d0:	440e2000 */ 	mfc1	$t6,$f4
/*  f02a4d4:	3c018000 */ 	lui	$at,0x8000
/*  f02a4d8:	10000007 */ 	b	.PF0f02a4f8
/*  f02a4dc:	01c17025 */ 	or	$t6,$t6,$at
.PF0f02a4e0:
/*  f02a4e0:	10000005 */ 	b	.PF0f02a4f8
/*  f02a4e4:	240effff */ 	li	$t6,-1
/*  f02a4e8:	440e2000 */ 	mfc1	$t6,$f4
.PF0f02a4ec:
/*  f02a4ec:	00000000 */ 	nop
/*  f02a4f0:	05c0fffb */ 	bltz	$t6,.PF0f02a4e0
/*  f02a4f4:	00000000 */ 	nop
.PF0f02a4f8:
/*  f02a4f8:	44d8f800 */ 	ctc1	$t8,$31
/*  f02a4fc:	10000006 */ 	b	.PF0f02a518
/*  f02a500:	a06e0002 */ 	sb	$t6,0x2($v1)
/*  f02a504:	24080200 */ 	li	$t0,0x200
.PF0f02a508:
/*  f02a508:	0000a825 */ 	move	$s5,$zero
/*  f02a50c:	00009825 */ 	move	$s3,$zero
/*  f02a510:	a7a80176 */ 	sh	$t0,0x176($sp)
/*  f02a514:	24140200 */ 	li	$s4,0x200
.PF0f02a518:
/*  f02a518:	27a60104 */ 	addiu	$a2,$sp,0x104
/*  f02a51c:	27a50180 */ 	addiu	$a1,$sp,0x180
.PF0f02a520:
/*  f02a520:	87a80176 */ 	lh	$t0,0x176($sp)
/*  f02a524:	00002025 */ 	move	$a0,$zero
/*  f02a528:	02001825 */ 	move	$v1,$s0
/*  f02a52c:	00c01025 */ 	move	$v0,$a2
.PF0f02a530:
/*  f02a530:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02a534:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f02a538:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f02a53c:	a861fff4 */ 	swl	$at,-0xc($v1)
/*  f02a540:	b861fff7 */ 	swr	$at,-0x9($v1)
/*  f02a544:	8e580004 */ 	lw	$t8,0x4($s2)
/*  f02a548:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f02a54c:	a878fff8 */ 	swl	$t8,-0x8($v1)
/*  f02a550:	b878fffb */ 	swr	$t8,-0x5($v1)
/*  f02a554:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02a558:	a861fffc */ 	swl	$at,-0x4($v1)
/*  f02a55c:	b861ffff */ 	swr	$at,-0x1($v1)
/*  f02a560:	8c4efffc */ 	lw	$t6,-0x4($v0)
/*  f02a564:	01d10019 */ 	multu	$t6,$s1
/*  f02a568:	00007812 */ 	mflo	$t7
/*  f02a56c:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02a570:	87380000 */ 	lh	$t8,0x0($t9)
/*  f02a574:	a478fff4 */ 	sh	$t8,-0xc($v1)
/*  f02a578:	8c4efffc */ 	lw	$t6,-0x4($v0)
/*  f02a57c:	01d10019 */ 	multu	$t6,$s1
/*  f02a580:	00007812 */ 	mflo	$t7
/*  f02a584:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02a588:	87380002 */ 	lh	$t8,0x2($t9)
/*  f02a58c:	a478fff6 */ 	sh	$t8,-0xa($v1)
/*  f02a590:	8c4efffc */ 	lw	$t6,-0x4($v0)
/*  f02a594:	01d10019 */ 	multu	$t6,$s1
/*  f02a598:	00007812 */ 	mflo	$t7
/*  f02a59c:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02a5a0:	87380004 */ 	lh	$t8,0x4($t9)
/*  f02a5a4:	a060fffb */ 	sb	$zero,-0x5($v1)
/*  f02a5a8:	1489ffe1 */ 	bne	$a0,$t1,.PF0f02a530
/*  f02a5ac:	a478fff8 */ 	sh	$t8,-0x8($v1)
/*  f02a5b0:	a6150008 */ 	sh	$s5,0x8($s0)
/*  f02a5b4:	a613000a */ 	sh	$s3,0xa($s0)
/*  f02a5b8:	a6080014 */ 	sh	$t0,0x14($s0)
/*  f02a5bc:	a6130016 */ 	sh	$s3,0x16($s0)
/*  f02a5c0:	a6080020 */ 	sh	$t0,0x20($s0)
/*  f02a5c4:	a6140022 */ 	sh	$s4,0x22($s0)
/*  f02a5c8:	a615002c */ 	sh	$s5,0x2c($s0)
/*  f02a5cc:	a614002e */ 	sh	$s4,0x2e($s0)
/*  f02a5d0:	8fae01f0 */ 	lw	$t6,0x1f0($sp)
/*  f02a5d4:	3c190430 */ 	lui	$t9,0x430
/*  f02a5d8:	37390030 */ 	ori	$t9,$t9,0x30
/*  f02a5dc:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f02a5e0:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02a5e4:	add90000 */ 	sw	$t9,0x0($t6)
/*  f02a5e8:	a7a80176 */ 	sh	$t0,0x176($sp)
/*  f02a5ec:	afa60054 */ 	sw	$a2,0x54($sp)
/*  f02a5f0:	02002025 */ 	move	$a0,$s0
/*  f02a5f4:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f02a5f8:	afae00b4 */ 	sw	$t6,0xb4($sp)
/*  f02a5fc:	8fa700b4 */ 	lw	$a3,0xb4($sp)
/*  f02a600:	8fa60054 */ 	lw	$a2,0x54($sp)
/*  f02a604:	3c0fb100 */ 	lui	$t7,0xb100
/*  f02a608:	ace20004 */ 	sw	$v0,0x4($a3)
/*  f02a60c:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f02a610:	35ef0032 */ 	ori	$t7,$t7,0x32
/*  f02a614:	24192010 */ 	li	$t9,0x2010
/*  f02a618:	270e0008 */ 	addiu	$t6,$t8,0x8
/*  f02a61c:	afae01f0 */ 	sw	$t6,0x1f0($sp)
/*  f02a620:	af190004 */ 	sw	$t9,0x4($t8)
/*  f02a624:	af0f0000 */ 	sw	$t7,0x0($t8)
/*  f02a628:	27b80164 */ 	addiu	$t8,$sp,0x164
/*  f02a62c:	24c60010 */ 	addiu	$a2,$a2,0x10
/*  f02a630:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f02a634:	24090004 */ 	li	$t1,0x4
/*  f02a638:	14d8ffb9 */ 	bne	$a2,$t8,.PF0f02a520
/*  f02a63c:	26100030 */ 	addiu	$s0,$s0,0x30
/*  f02a640:	100004a4 */ 	b	.PF0f02b8d4
/*  f02a644:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f02a648:	2401fffe */ 	li	$at,-2
.PF0f02a64c:
/*  f02a64c:	150100d5 */ 	bne	$t0,$at,.PF0f02a9a4
/*  f02a650:	8fae01f4 */ 	lw	$t6,0x1f4($sp)
/*  f02a654:	8fa3020c */ 	lw	$v1,0x20c($sp)
/*  f02a658:	81c20011 */ 	lb	$v0,0x11($t6)
/*  f02a65c:	8faf0208 */ 	lw	$t7,0x208($sp)
/*  f02a660:	24040003 */ 	li	$a0,0x3
/*  f02a664:	0043082a */ 	slt	$at,$v0,$v1
/*  f02a668:	50200005 */ 	beqzl	$at,.PF0f02a680
/*  f02a66c:	448f3000 */ 	mtc1	$t7,$f6
/*  f02a670:	44806000 */ 	mtc1	$zero,$f12
/*  f02a674:	1000001f */ 	b	.PF0f02a6f4
/*  f02a678:	46006086 */ 	mov.s	$f2,$f12
/*  f02a67c:	448f3000 */ 	mtc1	$t7,$f6
.PF0f02a680:
/*  f02a680:	3c0141c8 */ 	lui	$at,0x41c8
/*  f02a684:	44814000 */ 	mtc1	$at,$f8
/*  f02a688:	46803420 */ 	cvt.s.w	$f16,$f6
/*  f02a68c:	44829000 */ 	mtc1	$v0,$f18
/*  f02a690:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02a694:	c4249b84 */ 	lwc1	$f4,-0x647c($at)
/*  f02a698:	3c014220 */ 	lui	$at,0x4220
/*  f02a69c:	46809020 */ 	cvt.s.w	$f0,$f18
/*  f02a6a0:	44813000 */ 	mtc1	$at,$f6
/*  f02a6a4:	8fb90210 */ 	lw	$t9,0x210($sp)
/*  f02a6a8:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02a6ac:	46104281 */ 	sub.s	$f10,$f8,$f16
/*  f02a6b0:	44838000 */ 	mtc1	$v1,$f16
/*  f02a6b4:	46045482 */ 	mul.s	$f18,$f10,$f4
/*  f02a6b8:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f02a6bc:	44998000 */ 	mtc1	$t9,$f16
/*  f02a6c0:	46069200 */ 	add.s	$f8,$f18,$f6
/*  f02a6c4:	460a0101 */ 	sub.s	$f4,$f0,$f10
/*  f02a6c8:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f02a6cc:	460c2480 */ 	add.s	$f18,$f4,$f12
/*  f02a6d0:	c4249b88 */ 	lwc1	$f4,-0x6478($at)
/*  f02a6d4:	44806000 */ 	mtc1	$zero,$f12
/*  f02a6d8:	46009183 */ 	div.s	$f6,$f18,$f0
/*  f02a6dc:	46064082 */ 	mul.s	$f2,$f8,$f6
/*  f02a6e0:	00000000 */ 	nop
/*  f02a6e4:	46045482 */ 	mul.s	$f18,$f10,$f4
/*  f02a6e8:	00000000 */ 	nop
/*  f02a6ec:	46121082 */ 	mul.s	$f2,$f2,$f18
/*  f02a6f0:	00000000 */ 	nop
.PF0f02a6f4:
/*  f02a6f4:	3c01437f */ 	lui	$at,0x437f
/*  f02a6f8:	44810000 */ 	mtc1	$at,$f0
/*  f02a6fc:	00000000 */ 	nop
/*  f02a700:	4602003c */ 	c.lt.s	$f0,$f2
/*  f02a704:	00000000 */ 	nop
/*  f02a708:	45020004 */ 	bc1fl	.PF0f02a71c
/*  f02a70c:	460c103c */ 	c.lt.s	$f2,$f12
/*  f02a710:	10000006 */ 	b	.PF0f02a72c
/*  f02a714:	46000086 */ 	mov.s	$f2,$f0
/*  f02a718:	460c103c */ 	c.lt.s	$f2,$f12
.PF0f02a71c:
/*  f02a71c:	00000000 */ 	nop
/*  f02a720:	45000002 */ 	bc1f	.PF0f02a72c
/*  f02a724:	00000000 */ 	nop
/*  f02a728:	46006086 */ 	mov.s	$f2,$f12
.PF0f02a72c:
/*  f02a72c:	0fc5a253 */ 	jal	gfxAllocateColours
/*  f02a730:	e7a200ac */ 	swc1	$f2,0xac($sp)
/*  f02a734:	8fb001f0 */ 	lw	$s0,0x1f0($sp)
/*  f02a738:	3c0f0708 */ 	lui	$t7,0x708
/*  f02a73c:	35ef000c */ 	ori	$t7,$t7,0xc
/*  f02a740:	260e0008 */ 	addiu	$t6,$s0,0x8
/*  f02a744:	afae01f0 */ 	sw	$t6,0x1f0($sp)
/*  f02a748:	ae0f0000 */ 	sw	$t7,0x0($s0)
/*  f02a74c:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f02a750:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f02a754:	00402025 */ 	move	$a0,$v0
/*  f02a758:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02a75c:	c7a200ac */ 	lwc1	$f2,0xac($sp)
/*  f02a760:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f02a764:	8fa600e4 */ 	lw	$a2,0xe4($sp)
/*  f02a768:	8fa700e0 */ 	lw	$a3,0xe0($sp)
/*  f02a76c:	ae020004 */ 	sw	$v0,0x4($s0)
/*  f02a770:	4600120d */ 	trunc.w.s	$f8,$f2
/*  f02a774:	2404001e */ 	li	$a0,0x1e
/*  f02a778:	a0600007 */ 	sb	$zero,0x7($v1)
/*  f02a77c:	a0650000 */ 	sb	$a1,0x0($v1)
/*  f02a780:	44184000 */ 	mfc1	$t8,$f8
/*  f02a784:	a0650004 */ 	sb	$a1,0x4($v1)
/*  f02a788:	a0660001 */ 	sb	$a2,0x1($v1)
/*  f02a78c:	a0660005 */ 	sb	$a2,0x5($v1)
/*  f02a790:	a0670002 */ 	sb	$a3,0x2($v1)
/*  f02a794:	a0670006 */ 	sb	$a3,0x6($v1)
/*  f02a798:	0fc5a239 */ 	jal	gfxAllocateVertices
/*  f02a79c:	a0780003 */ 	sb	$t8,0x3($v1)
/*  f02a7a0:	87ab0052 */ 	lh	$t3,0x52($sp)
/*  f02a7a4:	02747021 */ 	addu	$t6,$s3,$s4
/*  f02a7a8:	000e7843 */ 	sra	$t7,$t6,0x1
/*  f02a7ac:	02abc821 */ 	addu	$t9,$s5,$t3
/*  f02a7b0:	0019c043 */ 	sra	$t8,$t9,0x1
/*  f02a7b4:	00408025 */ 	move	$s0,$v0
/*  f02a7b8:	afb80040 */ 	sw	$t8,0x40($sp)
/*  f02a7bc:	afaf004c */ 	sw	$t7,0x4c($sp)
/*  f02a7c0:	27a60104 */ 	addiu	$a2,$sp,0x104
/*  f02a7c4:	240c0004 */ 	li	$t4,0x4
/*  f02a7c8:	24090004 */ 	li	$t1,0x4
/*  f02a7cc:	27a50180 */ 	addiu	$a1,$sp,0x180
.PF0f02a7d0:
/*  f02a7d0:	00002025 */ 	move	$a0,$zero
/*  f02a7d4:	02001825 */ 	move	$v1,$s0
/*  f02a7d8:	00c01025 */ 	move	$v0,$a2
.PF0f02a7dc:
/*  f02a7dc:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02a7e0:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f02a7e4:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f02a7e8:	a861fff4 */ 	swl	$at,-0xc($v1)
/*  f02a7ec:	b861fff7 */ 	swr	$at,-0x9($v1)
/*  f02a7f0:	8e590004 */ 	lw	$t9,0x4($s2)
/*  f02a7f4:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f02a7f8:	a879fff8 */ 	swl	$t9,-0x8($v1)
/*  f02a7fc:	b879fffb */ 	swr	$t9,-0x5($v1)
/*  f02a800:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02a804:	a861fffc */ 	swl	$at,-0x4($v1)
/*  f02a808:	b861ffff */ 	swr	$at,-0x1($v1)
/*  f02a80c:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f02a810:	03110019 */ 	multu	$t8,$s1
/*  f02a814:	00007812 */ 	mflo	$t7
/*  f02a818:	00af7021 */ 	addu	$t6,$a1,$t7
/*  f02a81c:	85d90000 */ 	lh	$t9,0x0($t6)
/*  f02a820:	a479fff4 */ 	sh	$t9,-0xc($v1)
/*  f02a824:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f02a828:	03110019 */ 	multu	$t8,$s1
/*  f02a82c:	00007812 */ 	mflo	$t7
/*  f02a830:	00af7021 */ 	addu	$t6,$a1,$t7
/*  f02a834:	85d90002 */ 	lh	$t9,0x2($t6)
/*  f02a838:	a479fff6 */ 	sh	$t9,-0xa($v1)
/*  f02a83c:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f02a840:	03110019 */ 	multu	$t8,$s1
/*  f02a844:	00007812 */ 	mflo	$t7
/*  f02a848:	00af7021 */ 	addu	$t6,$a1,$t7
/*  f02a84c:	85d90004 */ 	lh	$t9,0x4($t6)
/*  f02a850:	a060fffb */ 	sb	$zero,-0x5($v1)
/*  f02a854:	1489ffe1 */ 	bne	$a0,$t1,.PF0f02a7dc
/*  f02a858:	a479fff8 */ 	sh	$t9,-0x8($v1)
/*  f02a85c:	a6150008 */ 	sh	$s5,0x8($s0)
/*  f02a860:	a613000a */ 	sh	$s3,0xa($s0)
/*  f02a864:	a60b0014 */ 	sh	$t3,0x14($s0)
/*  f02a868:	a6130016 */ 	sh	$s3,0x16($s0)
/*  f02a86c:	a60b0020 */ 	sh	$t3,0x20($s0)
/*  f02a870:	a6140022 */ 	sh	$s4,0x22($s0)
/*  f02a874:	a615002c */ 	sh	$s5,0x2c($s0)
/*  f02a878:	a614002e */ 	sh	$s4,0x2e($s0)
/*  f02a87c:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02a880:	860e0024 */ 	lh	$t6,0x24($s0)
/*  f02a884:	86190000 */ 	lh	$t9,0x0($s0)
/*  f02a888:	aa010030 */ 	swl	$at,0x30($s0)
/*  f02a88c:	ba010033 */ 	swr	$at,0x33($s0)
/*  f02a890:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02a894:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a898:	86190018 */ 	lh	$t9,0x18($s0)
/*  f02a89c:	aa0f0034 */ 	swl	$t7,0x34($s0)
/*  f02a8a0:	ba0f0037 */ 	swr	$t7,0x37($s0)
/*  f02a8a4:	860f000c */ 	lh	$t7,0xc($s0)
/*  f02a8a8:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02a8ac:	02002025 */ 	move	$a0,$s0
/*  f02a8b0:	030f7021 */ 	addu	$t6,$t8,$t7
/*  f02a8b4:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a8b8:	86190002 */ 	lh	$t9,0x2($s0)
/*  f02a8bc:	860e0026 */ 	lh	$t6,0x26($s0)
/*  f02a8c0:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02a8c4:	a60f0030 */ 	sh	$t7,0x30($s0)
/*  f02a8c8:	860f000e */ 	lh	$t7,0xe($s0)
/*  f02a8cc:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a8d0:	8619001a */ 	lh	$t9,0x1a($s0)
/*  f02a8d4:	030f7021 */ 	addu	$t6,$t8,$t7
/*  f02a8d8:	aa010038 */ 	swl	$at,0x38($s0)
/*  f02a8dc:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a8e0:	86190004 */ 	lh	$t9,0x4($s0)
/*  f02a8e4:	860e0028 */ 	lh	$t6,0x28($s0)
/*  f02a8e8:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02a8ec:	a60f0032 */ 	sh	$t7,0x32($s0)
/*  f02a8f0:	860f0010 */ 	lh	$t7,0x10($s0)
/*  f02a8f4:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a8f8:	8619001c */ 	lh	$t9,0x1c($s0)
/*  f02a8fc:	030f7021 */ 	addu	$t6,$t8,$t7
/*  f02a900:	ba01003b */ 	swr	$at,0x3b($s0)
/*  f02a904:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a908:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02a90c:	a60f0034 */ 	sh	$t7,0x34($s0)
/*  f02a910:	8fae0040 */ 	lw	$t6,0x40($sp)
/*  f02a914:	a60e0038 */ 	sh	$t6,0x38($s0)
/*  f02a918:	8fb9004c */ 	lw	$t9,0x4c($sp)
/*  f02a91c:	a20c0037 */ 	sb	$t4,0x37($s0)
/*  f02a920:	3c0e0440 */ 	lui	$t6,0x440
/*  f02a924:	a619003a */ 	sh	$t9,0x3a($s0)
/*  f02a928:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f02a92c:	35ce003c */ 	ori	$t6,$t6,0x3c
/*  f02a930:	270f0008 */ 	addiu	$t7,$t8,0x8
/*  f02a934:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02a938:	af0e0000 */ 	sw	$t6,0x0($t8)
/*  f02a93c:	afab0044 */ 	sw	$t3,0x44($sp)
/*  f02a940:	afa60054 */ 	sw	$a2,0x54($sp)
/*  f02a944:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f02a948:	afb800a4 */ 	sw	$t8,0xa4($sp)
/*  f02a94c:	8fa700a4 */ 	lw	$a3,0xa4($sp)
/*  f02a950:	8fa60054 */ 	lw	$a2,0x54($sp)
/*  f02a954:	8fab0044 */ 	lw	$t3,0x44($sp)
/*  f02a958:	ace20004 */ 	sw	$v0,0x4($a3)
/*  f02a95c:	8fb901f0 */ 	lw	$t9,0x1f0($sp)
/*  f02a960:	3c0fb100 */ 	lui	$t7,0xb100
/*  f02a964:	3c0e0332 */ 	lui	$t6,0x332
/*  f02a968:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f02a96c:	afb801f0 */ 	sw	$t8,0x1f0($sp)
/*  f02a970:	35ce2110 */ 	ori	$t6,$t6,0x2110
/*  f02a974:	35ef4444 */ 	ori	$t7,$t7,0x4444
/*  f02a978:	af2f0000 */ 	sw	$t7,0x0($t9)
/*  f02a97c:	af2e0004 */ 	sw	$t6,0x4($t9)
/*  f02a980:	27b90164 */ 	addiu	$t9,$sp,0x164
/*  f02a984:	24c60010 */ 	addiu	$a2,$a2,0x10
/*  f02a988:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f02a98c:	24090004 */ 	li	$t1,0x4
/*  f02a990:	240c0004 */ 	li	$t4,0x4
/*  f02a994:	14d9ff8e */ 	bne	$a2,$t9,.PF0f02a7d0
/*  f02a998:	2610003c */ 	addiu	$s0,$s0,0x3c
/*  f02a99c:	100003cd */ 	b	.PF0f02b8d4
/*  f02a9a0:	8fbf003c */ 	lw	$ra,0x3c($sp)
.PF0f02a9a4:
/*  f02a9a4:	05010130 */ 	bgez	$t0,.PF0f02ae68
/*  f02a9a8:	8fae01f8 */ 	lw	$t6,0x1f8($sp)
/*  f02a9ac:	0fc5a239 */ 	jal	gfxAllocateVertices
/*  f02a9b0:	2404000c */ 	li	$a0,0xc
/*  f02a9b4:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f02a9b8:	2401ffff */ 	li	$at,-1
/*  f02a9bc:	00408025 */ 	move	$s0,$v0
/*  f02a9c0:	15010035 */ 	bne	$t0,$at,.PF0f02aa98
/*  f02a9c4:	8fb801f4 */ 	lw	$t8,0x1f4($sp)
/*  f02a9c8:	3c02800a */ 	lui	$v0,0x800a
/*  f02a9cc:	8c42a518 */ 	lw	$v0,-0x5ae8($v0)
/*  f02a9d0:	8f03000c */ 	lw	$v1,0xc($t8)
/*  f02a9d4:	00002825 */ 	move	$a1,$zero
/*  f02a9d8:	24040001 */ 	li	$a0,0x1
/*  f02a9dc:	00437823 */ 	subu	$t7,$v0,$v1
/*  f02a9e0:	29e10043 */ 	slti	$at,$t7,0x43
/*  f02a9e4:	10200016 */ 	beqz	$at,.PF0f02aa40
/*  f02a9e8:	00627023 */ 	subu	$t6,$v1,$v0
/*  f02a9ec:	25d90042 */ 	addiu	$t9,$t6,0x42
/*  f02a9f0:	44993000 */ 	mtc1	$t9,$f6
/*  f02a9f4:	8fb80210 */ 	lw	$t8,0x210($sp)
/*  f02a9f8:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02a9fc:	46803420 */ 	cvt.s.w	$f16,$f6
/*  f02aa00:	44982000 */ 	mtc1	$t8,$f4
/*  f02aa04:	c42a9b8c */ 	lwc1	$f10,-0x6474($at)
/*  f02aa08:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02aa0c:	c4289b90 */ 	lwc1	$f8,-0x6470($at)
/*  f02aa10:	468024a0 */ 	cvt.s.w	$f18,$f4
/*  f02aa14:	460a8002 */ 	mul.s	$f0,$f16,$f10
/*  f02aa18:	00000000 */ 	nop
/*  f02aa1c:	46089182 */ 	mul.s	$f6,$f18,$f8
/*  f02aa20:	00000000 */ 	nop
/*  f02aa24:	46060002 */ 	mul.s	$f0,$f0,$f6
/*  f02aa28:	4600040d */ 	trunc.w.s	$f16,$f0
/*  f02aa2c:	44058000 */ 	mfc1	$a1,$f16
/*  f02aa30:	00000000 */ 	nop
/*  f02aa34:	30ae00ff */ 	andi	$t6,$a1,0xff
/*  f02aa38:	10000001 */ 	b	.PF0f02aa40
/*  f02aa3c:	01c02825 */ 	move	$a1,$t6
.PF0f02aa40:
/*  f02aa40:	0fc5a253 */ 	jal	gfxAllocateColours
/*  f02aa44:	a3a5017f */ 	sb	$a1,0x17f($sp)
/*  f02aa48:	8fb101f0 */ 	lw	$s1,0x1f0($sp)
/*  f02aa4c:	3c0f0700 */ 	lui	$t7,0x700
/*  f02aa50:	35ef0004 */ 	ori	$t7,$t7,0x4
/*  f02aa54:	26380008 */ 	addiu	$t8,$s1,0x8
/*  f02aa58:	afb801f0 */ 	sw	$t8,0x1f0($sp)
/*  f02aa5c:	ae2f0000 */ 	sw	$t7,0x0($s1)
/*  f02aa60:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f02aa64:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f02aa68:	00402025 */ 	move	$a0,$v0
/*  f02aa6c:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02aa70:	93a5017f */ 	lbu	$a1,0x17f($sp)
/*  f02aa74:	ae220004 */ 	sw	$v0,0x4($s1)
/*  f02aa78:	8fae0100 */ 	lw	$t6,0x100($sp)
/*  f02aa7c:	a06e0000 */ 	sb	$t6,0x0($v1)
/*  f02aa80:	8fb900fc */ 	lw	$t9,0xfc($sp)
/*  f02aa84:	a0790001 */ 	sb	$t9,0x1($v1)
/*  f02aa88:	8fb800f8 */ 	lw	$t8,0xf8($sp)
/*  f02aa8c:	a0650003 */ 	sb	$a1,0x3($v1)
/*  f02aa90:	10000053 */ 	b	.PF0f02abe0
/*  f02aa94:	a0780002 */ 	sb	$t8,0x2($v1)
.PF0f02aa98:
/*  f02aa98:	2401fffe */ 	li	$at,-2
/*  f02aa9c:	15010050 */ 	bne	$t0,$at,.PF0f02abe0
/*  f02aaa0:	8faf01f4 */ 	lw	$t7,0x1f4($sp)
/*  f02aaa4:	8fa3020c */ 	lw	$v1,0x20c($sp)
/*  f02aaa8:	81e20011 */ 	lb	$v0,0x11($t7)
/*  f02aaac:	8fae0208 */ 	lw	$t6,0x208($sp)
/*  f02aab0:	24040001 */ 	li	$a0,0x1
/*  f02aab4:	0043082a */ 	slt	$at,$v0,$v1
/*  f02aab8:	50200005 */ 	beqzl	$at,.PF0f02aad0
/*  f02aabc:	448e9000 */ 	mtc1	$t6,$f18
/*  f02aac0:	44806000 */ 	mtc1	$zero,$f12
/*  f02aac4:	10000021 */ 	b	.PF0f02ab4c
/*  f02aac8:	46006086 */ 	mov.s	$f2,$f12
/*  f02aacc:	448e9000 */ 	mtc1	$t6,$f18
.PF0f02aad0:
/*  f02aad0:	3c0141c8 */ 	lui	$at,0x41c8
/*  f02aad4:	44812000 */ 	mtc1	$at,$f4
/*  f02aad8:	46809220 */ 	cvt.s.w	$f8,$f18
/*  f02aadc:	44825000 */ 	mtc1	$v0,$f10
/*  f02aae0:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02aae4:	c4309b94 */ 	lwc1	$f16,-0x646c($at)
/*  f02aae8:	3c014220 */ 	lui	$at,0x4220
/*  f02aaec:	46805020 */ 	cvt.s.w	$f0,$f10
/*  f02aaf0:	44819000 */ 	mtc1	$at,$f18
/*  f02aaf4:	3c013f80 */ 	lui	$at,0x3f80
/*  f02aaf8:	8fb90210 */ 	lw	$t9,0x210($sp)
/*  f02aafc:	44806000 */ 	mtc1	$zero,$f12
/*  f02ab00:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f02ab04:	44834000 */ 	mtc1	$v1,$f8
/*  f02ab08:	46103282 */ 	mul.s	$f10,$f6,$f16
/*  f02ab0c:	468041a0 */ 	cvt.s.w	$f6,$f8
/*  f02ab10:	46125100 */ 	add.s	$f4,$f10,$f18
/*  f02ab14:	44815000 */ 	mtc1	$at,$f10
/*  f02ab18:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02ab1c:	46060401 */ 	sub.s	$f16,$f0,$f6
/*  f02ab20:	44993000 */ 	mtc1	$t9,$f6
/*  f02ab24:	460a8480 */ 	add.s	$f18,$f16,$f10
/*  f02ab28:	c42a9b98 */ 	lwc1	$f10,-0x6468($at)
/*  f02ab2c:	46803420 */ 	cvt.s.w	$f16,$f6
/*  f02ab30:	46009203 */ 	div.s	$f8,$f18,$f0
/*  f02ab34:	46082082 */ 	mul.s	$f2,$f4,$f8
/*  f02ab38:	00000000 */ 	nop
/*  f02ab3c:	460a8482 */ 	mul.s	$f18,$f16,$f10
/*  f02ab40:	00000000 */ 	nop
/*  f02ab44:	46121082 */ 	mul.s	$f2,$f2,$f18
/*  f02ab48:	00000000 */ 	nop
.PF0f02ab4c:
/*  f02ab4c:	3c01437f */ 	lui	$at,0x437f
/*  f02ab50:	44810000 */ 	mtc1	$at,$f0
/*  f02ab54:	00000000 */ 	nop
/*  f02ab58:	4602003c */ 	c.lt.s	$f0,$f2
/*  f02ab5c:	00000000 */ 	nop
/*  f02ab60:	45020004 */ 	bc1fl	.PF0f02ab74
/*  f02ab64:	460c103c */ 	c.lt.s	$f2,$f12
/*  f02ab68:	10000006 */ 	b	.PF0f02ab84
/*  f02ab6c:	46000086 */ 	mov.s	$f2,$f0
/*  f02ab70:	460c103c */ 	c.lt.s	$f2,$f12
.PF0f02ab74:
/*  f02ab74:	00000000 */ 	nop
/*  f02ab78:	45000002 */ 	bc1f	.PF0f02ab84
/*  f02ab7c:	00000000 */ 	nop
/*  f02ab80:	46006086 */ 	mov.s	$f2,$f12
.PF0f02ab84:
/*  f02ab84:	0fc5a253 */ 	jal	gfxAllocateColours
/*  f02ab88:	e7a20094 */ 	swc1	$f2,0x94($sp)
/*  f02ab8c:	8fb101f0 */ 	lw	$s1,0x1f0($sp)
/*  f02ab90:	3c0e0700 */ 	lui	$t6,0x700
/*  f02ab94:	35ce0004 */ 	ori	$t6,$t6,0x4
/*  f02ab98:	262f0008 */ 	addiu	$t7,$s1,0x8
/*  f02ab9c:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02aba0:	ae2e0000 */ 	sw	$t6,0x0($s1)
/*  f02aba4:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f02aba8:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f02abac:	00402025 */ 	move	$a0,$v0
/*  f02abb0:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02abb4:	c7a20094 */ 	lwc1	$f2,0x94($sp)
/*  f02abb8:	ae220004 */ 	sw	$v0,0x4($s1)
/*  f02abbc:	8fb900e8 */ 	lw	$t9,0xe8($sp)
/*  f02abc0:	4600110d */ 	trunc.w.s	$f4,$f2
/*  f02abc4:	a0790000 */ 	sb	$t9,0x0($v1)
/*  f02abc8:	8fb800e4 */ 	lw	$t8,0xe4($sp)
/*  f02abcc:	44192000 */ 	mfc1	$t9,$f4
/*  f02abd0:	a0780001 */ 	sb	$t8,0x1($v1)
/*  f02abd4:	8faf00e0 */ 	lw	$t7,0xe0($sp)
/*  f02abd8:	a0790003 */ 	sb	$t9,0x3($v1)
/*  f02abdc:	a06f0002 */ 	sb	$t7,0x2($v1)
.PF0f02abe0:
/*  f02abe0:	02001825 */ 	move	$v1,$s0
/*  f02abe4:	27a20180 */ 	addiu	$v0,$sp,0x180
/*  f02abe8:	27a401b0 */ 	addiu	$a0,$sp,0x1b0
.PF0f02abec:
/*  f02abec:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02abf0:	24420006 */ 	addiu	$v0,$v0,0x6
/*  f02abf4:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f02abf8:	a861fff4 */ 	swl	$at,-0xc($v1)
/*  f02abfc:	b861fff7 */ 	swr	$at,-0x9($v1)
/*  f02ac00:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02ac04:	a86ffff8 */ 	swl	$t7,-0x8($v1)
/*  f02ac08:	b86ffffb */ 	swr	$t7,-0x5($v1)
/*  f02ac0c:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02ac10:	a861fffc */ 	swl	$at,-0x4($v1)
/*  f02ac14:	b861ffff */ 	swr	$at,-0x1($v1)
/*  f02ac18:	844efffa */ 	lh	$t6,-0x6($v0)
/*  f02ac1c:	0044082b */ 	sltu	$at,$v0,$a0
/*  f02ac20:	a46efff4 */ 	sh	$t6,-0xc($v1)
/*  f02ac24:	8459fffc */ 	lh	$t9,-0x4($v0)
/*  f02ac28:	a479fff6 */ 	sh	$t9,-0xa($v1)
/*  f02ac2c:	8458fffe */ 	lh	$t8,-0x2($v0)
/*  f02ac30:	a060fffb */ 	sb	$zero,-0x5($v1)
/*  f02ac34:	1420ffed */ 	bnez	$at,.PF0f02abec
/*  f02ac38:	a478fff8 */ 	sh	$t8,-0x8($v1)
/*  f02ac3c:	a6150008 */ 	sh	$s5,0x8($s0)
/*  f02ac40:	a613000a */ 	sh	$s3,0xa($s0)
/*  f02ac44:	87ab0052 */ 	lh	$t3,0x52($sp)
/*  f02ac48:	a6130016 */ 	sh	$s3,0x16($s0)
/*  f02ac4c:	a6140046 */ 	sh	$s4,0x46($s0)
/*  f02ac50:	a6150038 */ 	sh	$s5,0x38($s0)
/*  f02ac54:	a614003a */ 	sh	$s4,0x3a($s0)
/*  f02ac58:	a615002c */ 	sh	$s5,0x2c($s0)
/*  f02ac5c:	a613002e */ 	sh	$s3,0x2e($s0)
/*  f02ac60:	a6130022 */ 	sh	$s3,0x22($s0)
/*  f02ac64:	a6140052 */ 	sh	$s4,0x52($s0)
/*  f02ac68:	a615005c */ 	sh	$s5,0x5c($s0)
/*  f02ac6c:	a614005e */ 	sh	$s4,0x5e($s0)
/*  f02ac70:	a60b0014 */ 	sh	$t3,0x14($s0)
/*  f02ac74:	a60b0044 */ 	sh	$t3,0x44($s0)
/*  f02ac78:	a60b0020 */ 	sh	$t3,0x20($s0)
/*  f02ac7c:	a60b0050 */ 	sh	$t3,0x50($s0)
/*  f02ac80:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02ac84:	02002025 */ 	move	$a0,$s0
/*  f02ac88:	aa010060 */ 	swl	$at,0x60($s0)
/*  f02ac8c:	ba010063 */ 	swr	$at,0x63($s0)
/*  f02ac90:	8e4e0004 */ 	lw	$t6,0x4($s2)
/*  f02ac94:	aa0e0064 */ 	swl	$t6,0x64($s0)
/*  f02ac98:	ba0e0067 */ 	swr	$t6,0x67($s0)
/*  f02ac9c:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02aca0:	aa010068 */ 	swl	$at,0x68($s0)
/*  f02aca4:	ba01006b */ 	swr	$at,0x6b($s0)
/*  f02aca8:	87b9018c */ 	lh	$t9,0x18c($sp)
/*  f02acac:	a6190060 */ 	sh	$t9,0x60($s0)
/*  f02acb0:	87b8018e */ 	lh	$t8,0x18e($sp)
/*  f02acb4:	a6180062 */ 	sh	$t8,0x62($s0)
/*  f02acb8:	87af0190 */ 	lh	$t7,0x190($sp)
/*  f02acbc:	a2000067 */ 	sb	$zero,0x67($s0)
/*  f02acc0:	a60f0064 */ 	sh	$t7,0x64($s0)
/*  f02acc4:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02acc8:	aa01006c */ 	swl	$at,0x6c($s0)
/*  f02accc:	ba01006f */ 	swr	$at,0x6f($s0)
/*  f02acd0:	8e590004 */ 	lw	$t9,0x4($s2)
/*  f02acd4:	aa190070 */ 	swl	$t9,0x70($s0)
/*  f02acd8:	ba190073 */ 	swr	$t9,0x73($s0)
/*  f02acdc:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02ace0:	aa010074 */ 	swl	$at,0x74($s0)
/*  f02ace4:	ba010077 */ 	swr	$at,0x77($s0)
/*  f02ace8:	87b80192 */ 	lh	$t8,0x192($sp)
/*  f02acec:	a618006c */ 	sh	$t8,0x6c($s0)
/*  f02acf0:	87af0194 */ 	lh	$t7,0x194($sp)
/*  f02acf4:	a60f006e */ 	sh	$t7,0x6e($s0)
/*  f02acf8:	87ae0196 */ 	lh	$t6,0x196($sp)
/*  f02acfc:	a2000073 */ 	sb	$zero,0x73($s0)
/*  f02ad00:	a6150068 */ 	sh	$s5,0x68($s0)
/*  f02ad04:	a614006a */ 	sh	$s4,0x6a($s0)
/*  f02ad08:	a6140076 */ 	sh	$s4,0x76($s0)
/*  f02ad0c:	a60b0074 */ 	sh	$t3,0x74($s0)
/*  f02ad10:	a60e0070 */ 	sh	$t6,0x70($s0)
/*  f02ad14:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02ad18:	aa010078 */ 	swl	$at,0x78($s0)
/*  f02ad1c:	ba01007b */ 	swr	$at,0x7b($s0)
/*  f02ad20:	8e580004 */ 	lw	$t8,0x4($s2)
/*  f02ad24:	aa18007c */ 	swl	$t8,0x7c($s0)
/*  f02ad28:	ba18007f */ 	swr	$t8,0x7f($s0)
/*  f02ad2c:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02ad30:	aa010080 */ 	swl	$at,0x80($s0)
/*  f02ad34:	ba010083 */ 	swr	$at,0x83($s0)
/*  f02ad38:	87af01a4 */ 	lh	$t7,0x1a4($sp)
/*  f02ad3c:	a60f0078 */ 	sh	$t7,0x78($s0)
/*  f02ad40:	87ae01a6 */ 	lh	$t6,0x1a6($sp)
/*  f02ad44:	a60e007a */ 	sh	$t6,0x7a($s0)
/*  f02ad48:	87b901a8 */ 	lh	$t9,0x1a8($sp)
/*  f02ad4c:	a200007f */ 	sb	$zero,0x7f($s0)
/*  f02ad50:	a619007c */ 	sh	$t9,0x7c($s0)
/*  f02ad54:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02ad58:	aa010084 */ 	swl	$at,0x84($s0)
/*  f02ad5c:	ba010087 */ 	swr	$at,0x87($s0)
/*  f02ad60:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02ad64:	aa0f0088 */ 	swl	$t7,0x88($s0)
/*  f02ad68:	ba0f008b */ 	swr	$t7,0x8b($s0)
/*  f02ad6c:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02ad70:	aa01008c */ 	swl	$at,0x8c($s0)
/*  f02ad74:	ba01008f */ 	swr	$at,0x8f($s0)
/*  f02ad78:	87ae01aa */ 	lh	$t6,0x1aa($sp)
/*  f02ad7c:	a60e0084 */ 	sh	$t6,0x84($s0)
/*  f02ad80:	87b901ac */ 	lh	$t9,0x1ac($sp)
/*  f02ad84:	a6190086 */ 	sh	$t9,0x86($s0)
/*  f02ad88:	87b801ae */ 	lh	$t8,0x1ae($sp)
/*  f02ad8c:	a200008b */ 	sb	$zero,0x8b($s0)
/*  f02ad90:	a6150080 */ 	sh	$s5,0x80($s0)
/*  f02ad94:	a6130082 */ 	sh	$s3,0x82($s0)
/*  f02ad98:	a613008e */ 	sh	$s3,0x8e($s0)
/*  f02ad9c:	a60b008c */ 	sh	$t3,0x8c($s0)
/*  f02ada0:	a6180088 */ 	sh	$t8,0x88($s0)
/*  f02ada4:	8fb101f0 */ 	lw	$s1,0x1f0($sp)
/*  f02ada8:	3c1904b0 */ 	lui	$t9,0x4b0
/*  f02adac:	37390090 */ 	ori	$t9,$t9,0x90
/*  f02adb0:	262e0008 */ 	addiu	$t6,$s1,0x8
/*  f02adb4:	afae01f0 */ 	sw	$t6,0x1f0($sp)
/*  f02adb8:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f02adbc:	ae390000 */ 	sw	$t9,0x0($s1)
/*  f02adc0:	ae220004 */ 	sw	$v0,0x4($s1)
/*  f02adc4:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f02adc8:	3c0eb100 */ 	lui	$t6,0xb100
/*  f02adcc:	3c194b5b */ 	lui	$t9,0x4b5b
/*  f02add0:	270f0008 */ 	addiu	$t7,$t8,0x8
/*  f02add4:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02add8:	37399010 */ 	ori	$t9,$t9,0x9010
/*  f02addc:	35cea489 */ 	ori	$t6,$t6,0xa489
/*  f02ade0:	27a30124 */ 	addiu	$v1,$sp,0x124
/*  f02ade4:	27a60164 */ 	addiu	$a2,$sp,0x164
/*  f02ade8:	3c05b100 */ 	lui	$a1,0xb100
/*  f02adec:	af0e0000 */ 	sw	$t6,0x0($t8)
/*  f02adf0:	af190004 */ 	sw	$t9,0x4($t8)
.PF0f02adf4:
/*  f02adf4:	8fa201f0 */ 	lw	$v0,0x1f0($sp)
/*  f02adf8:	24630010 */ 	addiu	$v1,$v1,0x10
/*  f02adfc:	244f0008 */ 	addiu	$t7,$v0,0x8
/*  f02ae00:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02ae04:	8c6efff8 */ 	lw	$t6,-0x8($v1)
/*  f02ae08:	8c6ffffc */ 	lw	$t7,-0x4($v1)
/*  f02ae0c:	31d9000f */ 	andi	$t9,$t6,0xf
/*  f02ae10:	0325c025 */ 	or	$t8,$t9,$a1
/*  f02ae14:	31ee000f */ 	andi	$t6,$t7,0xf
/*  f02ae18:	000ec900 */ 	sll	$t9,$t6,0x4
/*  f02ae1c:	03197825 */ 	or	$t7,$t8,$t9
/*  f02ae20:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f02ae24:	8c78fff8 */ 	lw	$t8,-0x8($v1)
/*  f02ae28:	8c64fff0 */ 	lw	$a0,-0x10($v1)
/*  f02ae2c:	3319000f */ 	andi	$t9,$t8,0xf
/*  f02ae30:	308e000f */ 	andi	$t6,$a0,0xf
/*  f02ae34:	01c02025 */ 	move	$a0,$t6
/*  f02ae38:	00197b00 */ 	sll	$t7,$t9,0xc
/*  f02ae3c:	01cf7025 */ 	or	$t6,$t6,$t7
/*  f02ae40:	8c6ffff4 */ 	lw	$t7,-0xc($v1)
/*  f02ae44:	0004c200 */ 	sll	$t8,$a0,0x8
/*  f02ae48:	01d8c825 */ 	or	$t9,$t6,$t8
/*  f02ae4c:	31ee000f */ 	andi	$t6,$t7,0xf
/*  f02ae50:	000ec100 */ 	sll	$t8,$t6,0x4
/*  f02ae54:	03387825 */ 	or	$t7,$t9,$t8
/*  f02ae58:	1466ffe6 */ 	bne	$v1,$a2,.PF0f02adf4
/*  f02ae5c:	ac4f0004 */ 	sw	$t7,0x4($v0)
/*  f02ae60:	1000029c */ 	b	.PF0f02b8d4
/*  f02ae64:	8fbf003c */ 	lw	$ra,0x3c($sp)
.PF0f02ae68:
/*  f02ae68:	91c40000 */ 	lbu	$a0,0x0($t6)
/*  f02ae6c:	24010001 */ 	li	$at,0x1
/*  f02ae70:	10810005 */ 	beq	$a0,$at,.PF0f02ae88
/*  f02ae74:	24090004 */ 	li	$t1,0x4
/*  f02ae78:	11240003 */ 	beq	$t1,$a0,.PF0f02ae88
/*  f02ae7c:	24010002 */ 	li	$at,0x2
/*  f02ae80:	5481000b */ 	bnel	$a0,$at,.PF0f02aeb0
/*  f02ae84:	8fb901f4 */ 	lw	$t9,0x1f4($sp)
.PF0f02ae88:
/*  f02ae88:	8fb901f8 */ 	lw	$t9,0x1f8($sp)
/*  f02ae8c:	240500ff */ 	li	$a1,0xff
/*  f02ae90:	8f380004 */ 	lw	$t8,0x4($t9)
/*  f02ae94:	8f0f0010 */ 	lw	$t7,0x10($t8)
/*  f02ae98:	31ee1000 */ 	andi	$t6,$t7,0x1000
/*  f02ae9c:	51c00004 */ 	beqzl	$t6,.PF0f02aeb0
/*  f02aea0:	8fb901f4 */ 	lw	$t9,0x1f4($sp)
/*  f02aea4:	10000023 */ 	b	.PF0f02af34
/*  f02aea8:	240600ff */ 	li	$a2,0xff
/*  f02aeac:	8fb901f4 */ 	lw	$t9,0x1f4($sp)
.PF0f02aeb0:
/*  f02aeb0:	3c02800a */ 	lui	$v0,0x800a
/*  f02aeb4:	8c42a518 */ 	lw	$v0,-0x5ae8($v0)
/*  f02aeb8:	8f23000c */ 	lw	$v1,0xc($t9)
/*  f02aebc:	00002825 */ 	move	$a1,$zero
/*  f02aec0:	00003025 */ 	move	$a2,$zero
/*  f02aec4:	0043c023 */ 	subu	$t8,$v0,$v1
/*  f02aec8:	2b010043 */ 	slti	$at,$t8,0x43
/*  f02aecc:	10200019 */ 	beqz	$at,.PF0f02af34
/*  f02aed0:	00627823 */ 	subu	$t7,$v1,$v0
/*  f02aed4:	25ee0042 */ 	addiu	$t6,$t7,0x42
/*  f02aed8:	448e4000 */ 	mtc1	$t6,$f8
/*  f02aedc:	8fb90210 */ 	lw	$t9,0x210($sp)
/*  f02aee0:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02aee4:	468041a0 */ 	cvt.s.w	$f6,$f8
/*  f02aee8:	44995000 */ 	mtc1	$t9,$f10
/*  f02aeec:	c4309b9c */ 	lwc1	$f16,-0x6464($at)
/*  f02aef0:	3c017f1b */ 	lui	$at,0x7f1b
/*  f02aef4:	c4249ba0 */ 	lwc1	$f4,-0x6460($at)
/*  f02aef8:	468054a0 */ 	cvt.s.w	$f18,$f10
/*  f02aefc:	46103302 */ 	mul.s	$f12,$f6,$f16
/*  f02af00:	00000000 */ 	nop
/*  f02af04:	46049082 */ 	mul.s	$f2,$f18,$f4
/*  f02af08:	00000000 */ 	nop
/*  f02af0c:	46026002 */ 	mul.s	$f0,$f12,$f2
/*  f02af10:	4600020d */ 	trunc.w.s	$f8,$f0
/*  f02af14:	4600018d */ 	trunc.w.s	$f6,$f0
/*  f02af18:	44054000 */ 	mfc1	$a1,$f8
/*  f02af1c:	44063000 */ 	mfc1	$a2,$f6
/*  f02af20:	30af00ff */ 	andi	$t7,$a1,0xff
/*  f02af24:	01e02825 */ 	move	$a1,$t7
/*  f02af28:	30d900ff */ 	andi	$t9,$a2,0xff
/*  f02af2c:	10000001 */ 	b	.PF0f02af34
/*  f02af30:	03203025 */ 	move	$a2,$t9
.PF0f02af34:
/*  f02af34:	24040005 */ 	li	$a0,0x5
/*  f02af38:	a3a5017f */ 	sb	$a1,0x17f($sp)
/*  f02af3c:	a3a6017e */ 	sb	$a2,0x17e($sp)
/*  f02af40:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f02af44:	afaa00f0 */ 	sw	$t2,0xf0($sp)
/*  f02af48:	0fc5a253 */ 	jal	gfxAllocateColours
/*  f02af4c:	afab00ec */ 	sw	$t3,0xec($sp)
/*  f02af50:	8fb001f0 */ 	lw	$s0,0x1f0($sp)
/*  f02af54:	3c0e0710 */ 	lui	$t6,0x710
/*  f02af58:	35ce0014 */ 	ori	$t6,$t6,0x14
/*  f02af5c:	260f0008 */ 	addiu	$t7,$s0,0x8
/*  f02af60:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02af64:	ae0e0000 */ 	sw	$t6,0x0($s0)
/*  f02af68:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f02af6c:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f02af70:	00402025 */ 	move	$a0,$v0
/*  f02af74:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02af78:	93a5017f */ 	lbu	$a1,0x17f($sp)
/*  f02af7c:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f02af80:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f02af84:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f02af88:	93a6017e */ 	lbu	$a2,0x17e($sp)
/*  f02af8c:	ae020004 */ 	sw	$v0,0x4($s0)
/*  f02af90:	8fb90100 */ 	lw	$t9,0x100($sp)
/*  f02af94:	2404001e */ 	li	$a0,0x1e
/*  f02af98:	a0790000 */ 	sb	$t9,0x0($v1)
/*  f02af9c:	8fb800fc */ 	lw	$t8,0xfc($sp)
/*  f02afa0:	a0780001 */ 	sb	$t8,0x1($v1)
/*  f02afa4:	8faf00f8 */ 	lw	$t7,0xf8($sp)
/*  f02afa8:	a0650003 */ 	sb	$a1,0x3($v1)
/*  f02afac:	a0650007 */ 	sb	$a1,0x7($v1)
/*  f02afb0:	a065000b */ 	sb	$a1,0xb($v1)
/*  f02afb4:	a0670004 */ 	sb	$a3,0x4($v1)
/*  f02afb8:	a0670008 */ 	sb	$a3,0x8($v1)
/*  f02afbc:	a06a0005 */ 	sb	$t2,0x5($v1)
/*  f02afc0:	a06a0009 */ 	sb	$t2,0x9($v1)
/*  f02afc4:	a06b0006 */ 	sb	$t3,0x6($v1)
/*  f02afc8:	a06b000a */ 	sb	$t3,0xa($v1)
/*  f02afcc:	a06f0002 */ 	sb	$t7,0x2($v1)
/*  f02afd0:	8fae0100 */ 	lw	$t6,0x100($sp)
/*  f02afd4:	24e70046 */ 	addiu	$a3,$a3,0x46
/*  f02afd8:	254a0046 */ 	addiu	$t2,$t2,0x46
/*  f02afdc:	25d90064 */ 	addiu	$t9,$t6,0x64
/*  f02afe0:	2b210100 */ 	slti	$at,$t9,0x100
/*  f02afe4:	14200003 */ 	bnez	$at,.PF0f02aff4
/*  f02afe8:	afb90100 */ 	sw	$t9,0x100($sp)
/*  f02afec:	240c00ff */ 	li	$t4,0xff
/*  f02aff0:	afac0100 */ 	sw	$t4,0x100($sp)
.PF0f02aff4:
/*  f02aff4:	8fb80100 */ 	lw	$t8,0x100($sp)
/*  f02aff8:	256b0046 */ 	addiu	$t3,$t3,0x46
/*  f02affc:	a078000c */ 	sb	$t8,0xc($v1)
/*  f02b000:	8faf00fc */ 	lw	$t7,0xfc($sp)
/*  f02b004:	25ee0064 */ 	addiu	$t6,$t7,0x64
/*  f02b008:	29c10100 */ 	slti	$at,$t6,0x100
/*  f02b00c:	14200003 */ 	bnez	$at,.PF0f02b01c
/*  f02b010:	afae00fc */ 	sw	$t6,0xfc($sp)
/*  f02b014:	240d00ff */ 	li	$t5,0xff
/*  f02b018:	afad00fc */ 	sw	$t5,0xfc($sp)
.PF0f02b01c:
/*  f02b01c:	8fb900fc */ 	lw	$t9,0xfc($sp)
/*  f02b020:	a079000d */ 	sb	$t9,0xd($v1)
/*  f02b024:	8fb800f8 */ 	lw	$t8,0xf8($sp)
/*  f02b028:	270f0064 */ 	addiu	$t7,$t8,0x64
/*  f02b02c:	29e10100 */ 	slti	$at,$t7,0x100
/*  f02b030:	14200003 */ 	bnez	$at,.PF0f02b040
/*  f02b034:	afaf00f8 */ 	sw	$t7,0xf8($sp)
/*  f02b038:	241f00ff */ 	li	$ra,0xff
/*  f02b03c:	afbf00f8 */ 	sw	$ra,0xf8($sp)
.PF0f02b040:
/*  f02b040:	8fae00f8 */ 	lw	$t6,0xf8($sp)
/*  f02b044:	28e10100 */ 	slti	$at,$a3,0x100
/*  f02b048:	a066000f */ 	sb	$a2,0xf($v1)
/*  f02b04c:	14200002 */ 	bnez	$at,.PF0f02b058
/*  f02b050:	a06e000e */ 	sb	$t6,0xe($v1)
/*  f02b054:	240700ff */ 	li	$a3,0xff
.PF0f02b058:
/*  f02b058:	29410100 */ 	slti	$at,$t2,0x100
/*  f02b05c:	14200002 */ 	bnez	$at,.PF0f02b068
/*  f02b060:	a0670010 */ 	sb	$a3,0x10($v1)
/*  f02b064:	240a00ff */ 	li	$t2,0xff
.PF0f02b068:
/*  f02b068:	29610100 */ 	slti	$at,$t3,0x100
/*  f02b06c:	14200002 */ 	bnez	$at,.PF0f02b078
/*  f02b070:	a06a0011 */ 	sb	$t2,0x11($v1)
/*  f02b074:	240b00ff */ 	li	$t3,0xff
.PF0f02b078:
/*  f02b078:	a06b0012 */ 	sb	$t3,0x12($v1)
/*  f02b07c:	0fc5a239 */ 	jal	gfxAllocateVertices
/*  f02b080:	a0650013 */ 	sb	$a1,0x13($v1)
/*  f02b084:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f02b088:	27b80104 */ 	addiu	$t8,$sp,0x104
/*  f02b08c:	00408025 */ 	move	$s0,$v0
/*  f02b090:	0008c900 */ 	sll	$t9,$t0,0x4
/*  f02b094:	03382821 */ 	addu	$a1,$t9,$t8
/*  f02b098:	00a03825 */ 	move	$a3,$a1
/*  f02b09c:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f02b0a0:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f02b0a4:	00002025 */ 	move	$a0,$zero
/*  f02b0a8:	00401825 */ 	move	$v1,$v0
.PF0f02b0ac:
/*  f02b0ac:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b0b0:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f02b0b4:	24e70004 */ 	addiu	$a3,$a3,0x4
/*  f02b0b8:	a8610000 */ 	swl	$at,0x0($v1)
/*  f02b0bc:	b8610003 */ 	swr	$at,0x3($v1)
/*  f02b0c0:	8e590004 */ 	lw	$t9,0x4($s2)
/*  f02b0c4:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f02b0c8:	a879fff8 */ 	swl	$t9,-0x8($v1)
/*  f02b0cc:	b879fffb */ 	swr	$t9,-0x5($v1)
/*  f02b0d0:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b0d4:	a861fffc */ 	swl	$at,-0x4($v1)
/*  f02b0d8:	b861ffff */ 	swr	$at,-0x1($v1)
/*  f02b0dc:	8cf8fffc */ 	lw	$t8,-0x4($a3)
/*  f02b0e0:	28810004 */ 	slti	$at,$a0,0x4
/*  f02b0e4:	03110019 */ 	multu	$t8,$s1
/*  f02b0e8:	00007012 */ 	mflo	$t6
/*  f02b0ec:	00ae7821 */ 	addu	$t7,$a1,$t6
/*  f02b0f0:	85f90000 */ 	lh	$t9,0x0($t7)
/*  f02b0f4:	a479fff4 */ 	sh	$t9,-0xc($v1)
/*  f02b0f8:	8cf8fffc */ 	lw	$t8,-0x4($a3)
/*  f02b0fc:	03110019 */ 	multu	$t8,$s1
/*  f02b100:	00007012 */ 	mflo	$t6
/*  f02b104:	00ae7821 */ 	addu	$t7,$a1,$t6
/*  f02b108:	85f90002 */ 	lh	$t9,0x2($t7)
/*  f02b10c:	a479fff6 */ 	sh	$t9,-0xa($v1)
/*  f02b110:	8cf8fffc */ 	lw	$t8,-0x4($a3)
/*  f02b114:	03110019 */ 	multu	$t8,$s1
/*  f02b118:	00007012 */ 	mflo	$t6
/*  f02b11c:	00ae7821 */ 	addu	$t7,$a1,$t6
/*  f02b120:	85f90004 */ 	lh	$t9,0x4($t7)
/*  f02b124:	a060fffb */ 	sb	$zero,-0x5($v1)
/*  f02b128:	1420ffe0 */ 	bnez	$at,.PF0f02b0ac
/*  f02b12c:	a479fff8 */ 	sh	$t9,-0x8($v1)
/*  f02b130:	8fa401f4 */ 	lw	$a0,0x1f4($sp)
/*  f02b134:	a4550008 */ 	sh	$s5,0x8($v0)
/*  f02b138:	a453000a */ 	sh	$s3,0xa($v0)
/*  f02b13c:	87ab0052 */ 	lh	$t3,0x52($sp)
/*  f02b140:	a4530016 */ 	sh	$s3,0x16($v0)
/*  f02b144:	a4540022 */ 	sh	$s4,0x22($v0)
/*  f02b148:	a455002c */ 	sh	$s5,0x2c($v0)
/*  f02b14c:	a454002e */ 	sh	$s4,0x2e($v0)
/*  f02b150:	a44b0014 */ 	sh	$t3,0x14($v0)
/*  f02b154:	a44b0020 */ 	sh	$t3,0x20($v0)
/*  f02b158:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b15c:	a8410030 */ 	swl	$at,0x30($v0)
/*  f02b160:	b8410033 */ 	swr	$at,0x33($v0)
/*  f02b164:	8e4e0004 */ 	lw	$t6,0x4($s2)
/*  f02b168:	a84e0034 */ 	swl	$t6,0x34($v0)
/*  f02b16c:	b84e0037 */ 	swr	$t6,0x37($v0)
/*  f02b170:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b174:	a8410038 */ 	swl	$at,0x38($v0)
/*  f02b178:	b841003b */ 	swr	$at,0x3b($v0)
/*  f02b17c:	84830012 */ 	lh	$v1,0x12($a0)
/*  f02b180:	24017fff */ 	li	$at,0x7fff
/*  f02b184:	5461001e */ 	bnel	$v1,$at,.PF0f02b200
/*  f02b188:	a4430030 */ 	sh	$v1,0x30($v0)
/*  f02b18c:	844f0024 */ 	lh	$t7,0x24($v0)
/*  f02b190:	84590000 */ 	lh	$t9,0x0($v0)
/*  f02b194:	844e000c */ 	lh	$t6,0xc($v0)
/*  f02b198:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b19c:	84590018 */ 	lh	$t9,0x18($v0)
/*  f02b1a0:	030e7821 */ 	addu	$t7,$t8,$t6
/*  f02b1a4:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b1a8:	84590002 */ 	lh	$t9,0x2($v0)
/*  f02b1ac:	844f0026 */ 	lh	$t7,0x26($v0)
/*  f02b1b0:	00187083 */ 	sra	$t6,$t8,0x2
/*  f02b1b4:	a44e0030 */ 	sh	$t6,0x30($v0)
/*  f02b1b8:	844e000e */ 	lh	$t6,0xe($v0)
/*  f02b1bc:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b1c0:	8459001a */ 	lh	$t9,0x1a($v0)
/*  f02b1c4:	030e7821 */ 	addu	$t7,$t8,$t6
/*  f02b1c8:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b1cc:	84590004 */ 	lh	$t9,0x4($v0)
/*  f02b1d0:	844f0028 */ 	lh	$t7,0x28($v0)
/*  f02b1d4:	00187083 */ 	sra	$t6,$t8,0x2
/*  f02b1d8:	a44e0032 */ 	sh	$t6,0x32($v0)
/*  f02b1dc:	844e0010 */ 	lh	$t6,0x10($v0)
/*  f02b1e0:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b1e4:	8459001c */ 	lh	$t9,0x1c($v0)
/*  f02b1e8:	030e7821 */ 	addu	$t7,$t8,$t6
/*  f02b1ec:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b1f0:	00187083 */ 	sra	$t6,$t8,0x2
/*  f02b1f4:	10000006 */ 	b	.PF0f02b210
/*  f02b1f8:	a44e0034 */ 	sh	$t6,0x34($v0)
/*  f02b1fc:	a4430030 */ 	sh	$v1,0x30($v0)
.PF0f02b200:
/*  f02b200:	848f0014 */ 	lh	$t7,0x14($a0)
/*  f02b204:	a44f0032 */ 	sh	$t7,0x32($v0)
/*  f02b208:	84990016 */ 	lh	$t9,0x16($a0)
/*  f02b20c:	a4590034 */ 	sh	$t9,0x34($v0)
.PF0f02b210:
/*  f02b210:	02ab1821 */ 	addu	$v1,$s5,$t3
/*  f02b214:	02741021 */ 	addu	$v0,$s3,$s4
/*  f02b218:	2418000c */ 	li	$t8,0xc
/*  f02b21c:	00037043 */ 	sra	$t6,$v1,0x1
/*  f02b220:	00027843 */ 	sra	$t7,$v0,0x1
/*  f02b224:	a2180037 */ 	sb	$t8,0x37($s0)
/*  f02b228:	a60e0038 */ 	sh	$t6,0x38($s0)
/*  f02b22c:	a60f003a */ 	sh	$t7,0x3a($s0)
/*  f02b230:	8fb901f0 */ 	lw	$t9,0x1f0($sp)
/*  f02b234:	01c01825 */ 	move	$v1,$t6
/*  f02b238:	3c0e0440 */ 	lui	$t6,0x440
/*  f02b23c:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f02b240:	afb801f0 */ 	sw	$t8,0x1f0($sp)
/*  f02b244:	35ce003c */ 	ori	$t6,$t6,0x3c
/*  f02b248:	af2e0000 */ 	sw	$t6,0x0($t9)
/*  f02b24c:	afab0044 */ 	sw	$t3,0x44($sp)
/*  f02b250:	afa30040 */ 	sw	$v1,0x40($sp)
/*  f02b254:	afaf004c */ 	sw	$t7,0x4c($sp)
/*  f02b258:	02002025 */ 	move	$a0,$s0
/*  f02b25c:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f02b260:	afb90078 */ 	sw	$t9,0x78($sp)
/*  f02b264:	8fa60078 */ 	lw	$a2,0x78($sp)
/*  f02b268:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f02b26c:	8fab0044 */ 	lw	$t3,0x44($sp)
/*  f02b270:	acc20004 */ 	sw	$v0,0x4($a2)
/*  f02b274:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
/*  f02b278:	3c18b100 */ 	lui	$t8,0xb100
/*  f02b27c:	3c0e0332 */ 	lui	$t6,0x332
/*  f02b280:	25f90008 */ 	addiu	$t9,$t7,0x8
/*  f02b284:	afb901f0 */ 	sw	$t9,0x1f0($sp)
/*  f02b288:	35ce2110 */ 	ori	$t6,$t6,0x2110
/*  f02b28c:	37184444 */ 	ori	$t8,$t8,0x4444
/*  f02b290:	adf80000 */ 	sw	$t8,0x0($t7)
/*  f02b294:	adee0004 */ 	sw	$t6,0x4($t7)
/*  f02b298:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f02b29c:	24090004 */ 	li	$t1,0x4
/*  f02b2a0:	2610003c */ 	addiu	$s0,$s0,0x3c
/*  f02b2a4:	8fa70048 */ 	lw	$a3,0x48($sp)
/*  f02b2a8:	00002025 */ 	move	$a0,$zero
/*  f02b2ac:	241f0005 */ 	li	$ra,0x5
/*  f02b2b0:	240d0008 */ 	li	$t5,0x8
/*  f02b2b4:	240c0004 */ 	li	$t4,0x4
.PF0f02b2b8:
/*  f02b2b8:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b2bc:	248a0001 */ 	addiu	$t2,$a0,0x1
/*  f02b2c0:	aa010000 */ 	swl	$at,0x0($s0)
/*  f02b2c4:	ba010003 */ 	swr	$at,0x3($s0)
/*  f02b2c8:	8e590004 */ 	lw	$t9,0x4($s2)
/*  f02b2cc:	aa190004 */ 	swl	$t9,0x4($s0)
/*  f02b2d0:	ba190007 */ 	swr	$t9,0x7($s0)
/*  f02b2d4:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b2d8:	aa010008 */ 	swl	$at,0x8($s0)
/*  f02b2dc:	ba01000b */ 	swr	$at,0xb($s0)
/*  f02b2e0:	8fb80048 */ 	lw	$t8,0x48($sp)
/*  f02b2e4:	05410004 */ 	bgez	$t2,.PF0f02b2f8
/*  f02b2e8:	314e0003 */ 	andi	$t6,$t2,0x3
/*  f02b2ec:	11c00002 */ 	beqz	$t6,.PF0f02b2f8
/*  f02b2f0:	00000000 */ 	nop
/*  f02b2f4:	25cefffc */ 	addiu	$t6,$t6,-4
.PF0f02b2f8:
/*  f02b2f8:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f02b2fc:	030f1021 */ 	addu	$v0,$t8,$t7
/*  f02b300:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b304:	03310019 */ 	multu	$t9,$s1
/*  f02b308:	00007012 */ 	mflo	$t6
/*  f02b30c:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b310:	870f0000 */ 	lh	$t7,0x0($t8)
/*  f02b314:	a60f0000 */ 	sh	$t7,0x0($s0)
/*  f02b318:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b31c:	03310019 */ 	multu	$t9,$s1
/*  f02b320:	00007012 */ 	mflo	$t6
/*  f02b324:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b328:	870f0002 */ 	lh	$t7,0x2($t8)
/*  f02b32c:	a60f0002 */ 	sh	$t7,0x2($s0)
/*  f02b330:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b334:	03310019 */ 	multu	$t9,$s1
/*  f02b338:	00007012 */ 	mflo	$t6
/*  f02b33c:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b340:	870f0004 */ 	lh	$t7,0x4($t8)
/*  f02b344:	a20c0007 */ 	sb	$t4,0x7($s0)
/*  f02b348:	a60f0004 */ 	sh	$t7,0x4($s0)
/*  f02b34c:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b350:	aa01000c */ 	swl	$at,0xc($s0)
/*  f02b354:	ba01000f */ 	swr	$at,0xf($s0)
/*  f02b358:	8e4e0004 */ 	lw	$t6,0x4($s2)
/*  f02b35c:	aa0e0010 */ 	swl	$t6,0x10($s0)
/*  f02b360:	ba0e0013 */ 	swr	$t6,0x13($s0)
/*  f02b364:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b368:	aa010014 */ 	swl	$at,0x14($s0)
/*  f02b36c:	ba010017 */ 	swr	$at,0x17($s0)
/*  f02b370:	8cf80000 */ 	lw	$t8,0x0($a3)
/*  f02b374:	03110019 */ 	multu	$t8,$s1
/*  f02b378:	00007812 */ 	mflo	$t7
/*  f02b37c:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02b380:	872e0000 */ 	lh	$t6,0x0($t9)
/*  f02b384:	a60e000c */ 	sh	$t6,0xc($s0)
/*  f02b388:	8cf80000 */ 	lw	$t8,0x0($a3)
/*  f02b38c:	03110019 */ 	multu	$t8,$s1
/*  f02b390:	00007812 */ 	mflo	$t7
/*  f02b394:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02b398:	872e0002 */ 	lh	$t6,0x2($t9)
/*  f02b39c:	a60e000e */ 	sh	$t6,0xe($s0)
/*  f02b3a0:	8cf80000 */ 	lw	$t8,0x0($a3)
/*  f02b3a4:	03110019 */ 	multu	$t8,$s1
/*  f02b3a8:	00007812 */ 	mflo	$t7
/*  f02b3ac:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02b3b0:	872e0004 */ 	lh	$t6,0x4($t9)
/*  f02b3b4:	a20c0013 */ 	sb	$t4,0x13($s0)
/*  f02b3b8:	a60e0010 */ 	sh	$t6,0x10($s0)
/*  f02b3bc:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b3c0:	aa010018 */ 	swl	$at,0x18($s0)
/*  f02b3c4:	ba01001b */ 	swr	$at,0x1b($s0)
/*  f02b3c8:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02b3cc:	aa0f001c */ 	swl	$t7,0x1c($s0)
/*  f02b3d0:	ba0f001f */ 	swr	$t7,0x1f($s0)
/*  f02b3d4:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b3d8:	aa010020 */ 	swl	$at,0x20($s0)
/*  f02b3dc:	ba010023 */ 	swr	$at,0x23($s0)
/*  f02b3e0:	8cf90000 */ 	lw	$t9,0x0($a3)
/*  f02b3e4:	24010001 */ 	li	$at,0x1
/*  f02b3e8:	03310019 */ 	multu	$t9,$s1
/*  f02b3ec:	00007012 */ 	mflo	$t6
/*  f02b3f0:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b3f4:	870f0000 */ 	lh	$t7,0x0($t8)
/*  f02b3f8:	a60f0018 */ 	sh	$t7,0x18($s0)
/*  f02b3fc:	8cf90000 */ 	lw	$t9,0x0($a3)
/*  f02b400:	03310019 */ 	multu	$t9,$s1
/*  f02b404:	00007012 */ 	mflo	$t6
/*  f02b408:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b40c:	870f0002 */ 	lh	$t7,0x2($t8)
/*  f02b410:	a60f001a */ 	sh	$t7,0x1a($s0)
/*  f02b414:	8cf90000 */ 	lw	$t9,0x0($a3)
/*  f02b418:	03310019 */ 	multu	$t9,$s1
/*  f02b41c:	00007012 */ 	mflo	$t6
/*  f02b420:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b424:	870f0004 */ 	lh	$t7,0x4($t8)
/*  f02b428:	a20d001f */ 	sb	$t5,0x1f($s0)
/*  f02b42c:	15000004 */ 	bnez	$t0,.PF0f02b440
/*  f02b430:	a60f001c */ 	sh	$t7,0x1c($s0)
/*  f02b434:	8fb901c8 */ 	lw	$t9,0x1c8($sp)
/*  f02b438:	10000016 */ 	b	.PF0f02b494
/*  f02b43c:	a6190018 */ 	sh	$t9,0x18($s0)
.PF0f02b440:
/*  f02b440:	15010003 */ 	bne	$t0,$at,.PF0f02b450
/*  f02b444:	8fae01cc */ 	lw	$t6,0x1cc($sp)
/*  f02b448:	10000012 */ 	b	.PF0f02b494
/*  f02b44c:	a60e0018 */ 	sh	$t6,0x18($s0)
.PF0f02b450:
/*  f02b450:	24010002 */ 	li	$at,0x2
/*  f02b454:	15010003 */ 	bne	$t0,$at,.PF0f02b464
/*  f02b458:	8fb801c0 */ 	lw	$t8,0x1c0($sp)
/*  f02b45c:	1000000d */ 	b	.PF0f02b494
/*  f02b460:	a618001a */ 	sh	$t8,0x1a($s0)
.PF0f02b464:
/*  f02b464:	24010003 */ 	li	$at,0x3
/*  f02b468:	15010003 */ 	bne	$t0,$at,.PF0f02b478
/*  f02b46c:	8faf01c4 */ 	lw	$t7,0x1c4($sp)
/*  f02b470:	10000008 */ 	b	.PF0f02b494
/*  f02b474:	a60f001a */ 	sh	$t7,0x1a($s0)
.PF0f02b478:
/*  f02b478:	15090003 */ 	bne	$t0,$t1,.PF0f02b488
/*  f02b47c:	8fb901b8 */ 	lw	$t9,0x1b8($sp)
/*  f02b480:	10000004 */ 	b	.PF0f02b494
/*  f02b484:	a619001c */ 	sh	$t9,0x1c($s0)
.PF0f02b488:
/*  f02b488:	151f0002 */ 	bne	$t0,$ra,.PF0f02b494
/*  f02b48c:	8fae01bc */ 	lw	$t6,0x1bc($sp)
/*  f02b490:	a60e001c */ 	sh	$t6,0x1c($s0)
.PF0f02b494:
/*  f02b494:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b498:	aa010024 */ 	swl	$at,0x24($s0)
/*  f02b49c:	ba010027 */ 	swr	$at,0x27($s0)
/*  f02b4a0:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02b4a4:	aa0f0028 */ 	swl	$t7,0x28($s0)
/*  f02b4a8:	ba0f002b */ 	swr	$t7,0x2b($s0)
/*  f02b4ac:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b4b0:	aa01002c */ 	swl	$at,0x2c($s0)
/*  f02b4b4:	ba01002f */ 	swr	$at,0x2f($s0)
/*  f02b4b8:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b4bc:	24010001 */ 	li	$at,0x1
/*  f02b4c0:	03310019 */ 	multu	$t9,$s1
/*  f02b4c4:	00007012 */ 	mflo	$t6
/*  f02b4c8:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b4cc:	870f0000 */ 	lh	$t7,0x0($t8)
/*  f02b4d0:	a60f0024 */ 	sh	$t7,0x24($s0)
/*  f02b4d4:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b4d8:	03310019 */ 	multu	$t9,$s1
/*  f02b4dc:	00007012 */ 	mflo	$t6
/*  f02b4e0:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b4e4:	870f0002 */ 	lh	$t7,0x2($t8)
/*  f02b4e8:	a60f0026 */ 	sh	$t7,0x26($s0)
/*  f02b4ec:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b4f0:	03310019 */ 	multu	$t9,$s1
/*  f02b4f4:	00007012 */ 	mflo	$t6
/*  f02b4f8:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b4fc:	870f0004 */ 	lh	$t7,0x4($t8)
/*  f02b500:	a20d002b */ 	sb	$t5,0x2b($s0)
/*  f02b504:	15000004 */ 	bnez	$t0,.PF0f02b518
/*  f02b508:	a60f0028 */ 	sh	$t7,0x28($s0)
/*  f02b50c:	8fb901c8 */ 	lw	$t9,0x1c8($sp)
/*  f02b510:	10000016 */ 	b	.PF0f02b56c
/*  f02b514:	a6190024 */ 	sh	$t9,0x24($s0)
.PF0f02b518:
/*  f02b518:	15010003 */ 	bne	$t0,$at,.PF0f02b528
/*  f02b51c:	8fae01cc */ 	lw	$t6,0x1cc($sp)
/*  f02b520:	10000012 */ 	b	.PF0f02b56c
/*  f02b524:	a60e0024 */ 	sh	$t6,0x24($s0)
.PF0f02b528:
/*  f02b528:	24010002 */ 	li	$at,0x2
/*  f02b52c:	15010003 */ 	bne	$t0,$at,.PF0f02b53c
/*  f02b530:	8fb801c0 */ 	lw	$t8,0x1c0($sp)
/*  f02b534:	1000000d */ 	b	.PF0f02b56c
/*  f02b538:	a6180026 */ 	sh	$t8,0x26($s0)
.PF0f02b53c:
/*  f02b53c:	24010003 */ 	li	$at,0x3
/*  f02b540:	15010003 */ 	bne	$t0,$at,.PF0f02b550
/*  f02b544:	8faf01c4 */ 	lw	$t7,0x1c4($sp)
/*  f02b548:	10000008 */ 	b	.PF0f02b56c
/*  f02b54c:	a60f0026 */ 	sh	$t7,0x26($s0)
.PF0f02b550:
/*  f02b550:	15090003 */ 	bne	$t0,$t1,.PF0f02b560
/*  f02b554:	8fb901b8 */ 	lw	$t9,0x1b8($sp)
/*  f02b558:	10000004 */ 	b	.PF0f02b56c
/*  f02b55c:	a6190028 */ 	sh	$t9,0x28($s0)
.PF0f02b560:
/*  f02b560:	151f0002 */ 	bne	$t0,$ra,.PF0f02b56c
/*  f02b564:	8fae01bc */ 	lw	$t6,0x1bc($sp)
/*  f02b568:	a60e0028 */ 	sh	$t6,0x28($s0)
.PF0f02b56c:
/*  f02b56c:	a6150008 */ 	sh	$s5,0x8($s0)
/*  f02b570:	a613000a */ 	sh	$s3,0xa($s0)
/*  f02b574:	a60b0014 */ 	sh	$t3,0x14($s0)
/*  f02b578:	a6130016 */ 	sh	$s3,0x16($s0)
/*  f02b57c:	a60b0020 */ 	sh	$t3,0x20($s0)
/*  f02b580:	a6140022 */ 	sh	$s4,0x22($s0)
/*  f02b584:	a615002c */ 	sh	$s5,0x2c($s0)
/*  f02b588:	a614002e */ 	sh	$s4,0x2e($s0)
/*  f02b58c:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b590:	86190024 */ 	lh	$t9,0x24($s0)
/*  f02b594:	860e0000 */ 	lh	$t6,0x0($s0)
/*  f02b598:	aa010030 */ 	swl	$at,0x30($s0)
/*  f02b59c:	ba010033 */ 	swr	$at,0x33($s0)
/*  f02b5a0:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02b5a4:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b5a8:	860e0018 */ 	lh	$t6,0x18($s0)
/*  f02b5ac:	aa0f0034 */ 	swl	$t7,0x34($s0)
/*  f02b5b0:	ba0f0037 */ 	swr	$t7,0x37($s0)
/*  f02b5b4:	860f000c */ 	lh	$t7,0xc($s0)
/*  f02b5b8:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b5bc:	02002025 */ 	move	$a0,$s0
/*  f02b5c0:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b5c4:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b5c8:	860e0002 */ 	lh	$t6,0x2($s0)
/*  f02b5cc:	86190026 */ 	lh	$t9,0x26($s0)
/*  f02b5d0:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b5d4:	a60f0030 */ 	sh	$t7,0x30($s0)
/*  f02b5d8:	860f000e */ 	lh	$t7,0xe($s0)
/*  f02b5dc:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b5e0:	860e001a */ 	lh	$t6,0x1a($s0)
/*  f02b5e4:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b5e8:	aa010038 */ 	swl	$at,0x38($s0)
/*  f02b5ec:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b5f0:	860e0004 */ 	lh	$t6,0x4($s0)
/*  f02b5f4:	86190028 */ 	lh	$t9,0x28($s0)
/*  f02b5f8:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b5fc:	a60f0032 */ 	sh	$t7,0x32($s0)
/*  f02b600:	860f0010 */ 	lh	$t7,0x10($s0)
/*  f02b604:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b608:	860e001c */ 	lh	$t6,0x1c($s0)
/*  f02b60c:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b610:	ba01003b */ 	swr	$at,0x3b($s0)
/*  f02b614:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b618:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b61c:	24190010 */ 	li	$t9,0x10
/*  f02b620:	a60f0034 */ 	sh	$t7,0x34($s0)
/*  f02b624:	a2190037 */ 	sb	$t9,0x37($s0)
/*  f02b628:	8fae0040 */ 	lw	$t6,0x40($sp)
/*  f02b62c:	a60e0038 */ 	sh	$t6,0x38($s0)
/*  f02b630:	8fb8004c */ 	lw	$t8,0x4c($sp)
/*  f02b634:	3c0e0440 */ 	lui	$t6,0x440
/*  f02b638:	35ce003c */ 	ori	$t6,$t6,0x3c
/*  f02b63c:	a618003a */ 	sh	$t8,0x3a($s0)
/*  f02b640:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
/*  f02b644:	25f90008 */ 	addiu	$t9,$t7,0x8
/*  f02b648:	afb901f0 */ 	sw	$t9,0x1f0($sp)
/*  f02b64c:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f02b650:	afab0044 */ 	sw	$t3,0x44($sp)
/*  f02b654:	afaa0058 */ 	sw	$t2,0x58($sp)
/*  f02b658:	afa70054 */ 	sw	$a3,0x54($sp)
/*  f02b65c:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f02b660:	afaf0068 */ 	sw	$t7,0x68($sp)
/*  f02b664:	8fa60068 */ 	lw	$a2,0x68($sp)
/*  f02b668:	8fa70054 */ 	lw	$a3,0x54($sp)
/*  f02b66c:	8fa40058 */ 	lw	$a0,0x58($sp)
/*  f02b670:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f02b674:	8fab0044 */ 	lw	$t3,0x44($sp)
/*  f02b678:	acc20004 */ 	sw	$v0,0x4($a2)
/*  f02b67c:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f02b680:	3c19b100 */ 	lui	$t9,0xb100
/*  f02b684:	3c0e0332 */ 	lui	$t6,0x332
/*  f02b688:	270f0008 */ 	addiu	$t7,$t8,0x8
/*  f02b68c:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02b690:	35ce2110 */ 	ori	$t6,$t6,0x2110
/*  f02b694:	37394444 */ 	ori	$t9,$t9,0x4444
/*  f02b698:	28810004 */ 	slti	$at,$a0,0x4
/*  f02b69c:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f02b6a0:	24090004 */ 	li	$t1,0x4
/*  f02b6a4:	240c0004 */ 	li	$t4,0x4
/*  f02b6a8:	240d0008 */ 	li	$t5,0x8
/*  f02b6ac:	241f0005 */ 	li	$ra,0x5
/*  f02b6b0:	2610003c */ 	addiu	$s0,$s0,0x3c
/*  f02b6b4:	24e70004 */ 	addiu	$a3,$a3,0x4
/*  f02b6b8:	af190000 */ 	sw	$t9,0x0($t8)
/*  f02b6bc:	1420fefe */ 	bnez	$at,.PF0f02b2b8
/*  f02b6c0:	af0e0004 */ 	sw	$t6,0x4($t8)
/*  f02b6c4:	8fa20048 */ 	lw	$v0,0x48($sp)
/*  f02b6c8:	02001825 */ 	move	$v1,$s0
/*  f02b6cc:	00003025 */ 	move	$a2,$zero
/*  f02b6d0:	24040010 */ 	li	$a0,0x10
/*  f02b6d4:	2442000c */ 	addiu	$v0,$v0,0xc
.PF0f02b6d8:
/*  f02b6d8:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b6dc:	24c60004 */ 	addiu	$a2,$a2,0x4
/*  f02b6e0:	2442fffc */ 	addiu	$v0,$v0,-4
/*  f02b6e4:	a8610000 */ 	swl	$at,0x0($v1)
/*  f02b6e8:	b8610003 */ 	swr	$at,0x3($v1)
/*  f02b6ec:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02b6f0:	a86f0004 */ 	swl	$t7,0x4($v1)
/*  f02b6f4:	b86f0007 */ 	swr	$t7,0x7($v1)
/*  f02b6f8:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b6fc:	a8610008 */ 	swl	$at,0x8($v1)
/*  f02b700:	b861000b */ 	swr	$at,0xb($v1)
/*  f02b704:	8c590004 */ 	lw	$t9,0x4($v0)
/*  f02b708:	24010001 */ 	li	$at,0x1
/*  f02b70c:	03310019 */ 	multu	$t9,$s1
/*  f02b710:	00007012 */ 	mflo	$t6
/*  f02b714:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b718:	870f0000 */ 	lh	$t7,0x0($t8)
/*  f02b71c:	a46f0000 */ 	sh	$t7,0x0($v1)
/*  f02b720:	8c590004 */ 	lw	$t9,0x4($v0)
/*  f02b724:	03310019 */ 	multu	$t9,$s1
/*  f02b728:	00007012 */ 	mflo	$t6
/*  f02b72c:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b730:	870f0002 */ 	lh	$t7,0x2($t8)
/*  f02b734:	a46f0002 */ 	sh	$t7,0x2($v1)
/*  f02b738:	8c590004 */ 	lw	$t9,0x4($v0)
/*  f02b73c:	03310019 */ 	multu	$t9,$s1
/*  f02b740:	00007012 */ 	mflo	$t6
/*  f02b744:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b748:	870f0004 */ 	lh	$t7,0x4($t8)
/*  f02b74c:	a06d0007 */ 	sb	$t5,0x7($v1)
/*  f02b750:	15000004 */ 	bnez	$t0,.PF0f02b764
/*  f02b754:	a46f0004 */ 	sh	$t7,0x4($v1)
/*  f02b758:	8fb901c8 */ 	lw	$t9,0x1c8($sp)
/*  f02b75c:	10000016 */ 	b	.PF0f02b7b8
/*  f02b760:	a4790000 */ 	sh	$t9,0x0($v1)
.PF0f02b764:
/*  f02b764:	15010003 */ 	bne	$t0,$at,.PF0f02b774
/*  f02b768:	8fae01cc */ 	lw	$t6,0x1cc($sp)
/*  f02b76c:	10000012 */ 	b	.PF0f02b7b8
/*  f02b770:	a46e0000 */ 	sh	$t6,0x0($v1)
.PF0f02b774:
/*  f02b774:	24010002 */ 	li	$at,0x2
/*  f02b778:	15010003 */ 	bne	$t0,$at,.PF0f02b788
/*  f02b77c:	8fb801c0 */ 	lw	$t8,0x1c0($sp)
/*  f02b780:	1000000d */ 	b	.PF0f02b7b8
/*  f02b784:	a4780002 */ 	sh	$t8,0x2($v1)
.PF0f02b788:
/*  f02b788:	24010003 */ 	li	$at,0x3
/*  f02b78c:	15010003 */ 	bne	$t0,$at,.PF0f02b79c
/*  f02b790:	8faf01c4 */ 	lw	$t7,0x1c4($sp)
/*  f02b794:	10000008 */ 	b	.PF0f02b7b8
/*  f02b798:	a46f0002 */ 	sh	$t7,0x2($v1)
.PF0f02b79c:
/*  f02b79c:	15090003 */ 	bne	$t0,$t1,.PF0f02b7ac
/*  f02b7a0:	8fb901b8 */ 	lw	$t9,0x1b8($sp)
/*  f02b7a4:	10000004 */ 	b	.PF0f02b7b8
/*  f02b7a8:	a4790004 */ 	sh	$t9,0x4($v1)
.PF0f02b7ac:
/*  f02b7ac:	151f0002 */ 	bne	$t0,$ra,.PF0f02b7b8
/*  f02b7b0:	8fae01bc */ 	lw	$t6,0x1bc($sp)
/*  f02b7b4:	a46e0004 */ 	sh	$t6,0x4($v1)
.PF0f02b7b8:
/*  f02b7b8:	14c4ffc7 */ 	bne	$a2,$a0,.PF0f02b6d8
/*  f02b7bc:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f02b7c0:	a6150008 */ 	sh	$s5,0x8($s0)
/*  f02b7c4:	a613000a */ 	sh	$s3,0xa($s0)
/*  f02b7c8:	a60b0014 */ 	sh	$t3,0x14($s0)
/*  f02b7cc:	a6130016 */ 	sh	$s3,0x16($s0)
/*  f02b7d0:	a60b0020 */ 	sh	$t3,0x20($s0)
/*  f02b7d4:	a6140022 */ 	sh	$s4,0x22($s0)
/*  f02b7d8:	a615002c */ 	sh	$s5,0x2c($s0)
/*  f02b7dc:	a614002e */ 	sh	$s4,0x2e($s0)
/*  f02b7e0:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b7e4:	86190024 */ 	lh	$t9,0x24($s0)
/*  f02b7e8:	860e0000 */ 	lh	$t6,0x0($s0)
/*  f02b7ec:	aa010030 */ 	swl	$at,0x30($s0)
/*  f02b7f0:	ba010033 */ 	swr	$at,0x33($s0)
/*  f02b7f4:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02b7f8:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b7fc:	860e0018 */ 	lh	$t6,0x18($s0)
/*  f02b800:	aa0f0034 */ 	swl	$t7,0x34($s0)
/*  f02b804:	ba0f0037 */ 	swr	$t7,0x37($s0)
/*  f02b808:	860f000c */ 	lh	$t7,0xc($s0)
/*  f02b80c:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b810:	02002025 */ 	move	$a0,$s0
/*  f02b814:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b818:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b81c:	860e0002 */ 	lh	$t6,0x2($s0)
/*  f02b820:	86190026 */ 	lh	$t9,0x26($s0)
/*  f02b824:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b828:	a60f0030 */ 	sh	$t7,0x30($s0)
/*  f02b82c:	860f000e */ 	lh	$t7,0xe($s0)
/*  f02b830:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b834:	860e001a */ 	lh	$t6,0x1a($s0)
/*  f02b838:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b83c:	aa010038 */ 	swl	$at,0x38($s0)
/*  f02b840:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b844:	860e0004 */ 	lh	$t6,0x4($s0)
/*  f02b848:	86190028 */ 	lh	$t9,0x28($s0)
/*  f02b84c:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b850:	a60f0032 */ 	sh	$t7,0x32($s0)
/*  f02b854:	860f0010 */ 	lh	$t7,0x10($s0)
/*  f02b858:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b85c:	860e001c */ 	lh	$t6,0x1c($s0)
/*  f02b860:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b864:	ba01003b */ 	swr	$at,0x3b($s0)
/*  f02b868:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b86c:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b870:	24190010 */ 	li	$t9,0x10
/*  f02b874:	a60f0034 */ 	sh	$t7,0x34($s0)
/*  f02b878:	a2190037 */ 	sb	$t9,0x37($s0)
/*  f02b87c:	8fae0040 */ 	lw	$t6,0x40($sp)
/*  f02b880:	a60e0038 */ 	sh	$t6,0x38($s0)
/*  f02b884:	8fb8004c */ 	lw	$t8,0x4c($sp)
/*  f02b888:	3c0e0440 */ 	lui	$t6,0x440
/*  f02b88c:	35ce003c */ 	ori	$t6,$t6,0x3c
/*  f02b890:	a618003a */ 	sh	$t8,0x3a($s0)
/*  f02b894:	8fb101f0 */ 	lw	$s1,0x1f0($sp)
/*  f02b898:	26390008 */ 	addiu	$t9,$s1,0x8
/*  f02b89c:	afb901f0 */ 	sw	$t9,0x1f0($sp)
/*  f02b8a0:	0c012ab0 */ 	jal	osVirtualToPhysical
/*  f02b8a4:	ae2e0000 */ 	sw	$t6,0x0($s1)
/*  f02b8a8:	ae220004 */ 	sw	$v0,0x4($s1)
/*  f02b8ac:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f02b8b0:	3c19b100 */ 	lui	$t9,0xb100
/*  f02b8b4:	3c0e0332 */ 	lui	$t6,0x332
/*  f02b8b8:	270f0008 */ 	addiu	$t7,$t8,0x8
/*  f02b8bc:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02b8c0:	35ce2110 */ 	ori	$t6,$t6,0x2110
/*  f02b8c4:	37394444 */ 	ori	$t9,$t9,0x4444
/*  f02b8c8:	af190000 */ 	sw	$t9,0x0($t8)
/*  f02b8cc:	af0e0004 */ 	sw	$t6,0x4($t8)
/*  f02b8d0:	8fbf003c */ 	lw	$ra,0x3c($sp)
.PF0f02b8d4:
/*  f02b8d4:	8fa201f0 */ 	lw	$v0,0x1f0($sp)
/*  f02b8d8:	8fb00024 */ 	lw	$s0,0x24($sp)
/*  f02b8dc:	8fb10028 */ 	lw	$s1,0x28($sp)
/*  f02b8e0:	8fb2002c */ 	lw	$s2,0x2c($sp)
/*  f02b8e4:	8fb30030 */ 	lw	$s3,0x30($sp)
/*  f02b8e8:	8fb40034 */ 	lw	$s4,0x34($sp)
/*  f02b8ec:	8fb50038 */ 	lw	$s5,0x38($sp)
/*  f02b8f0:	03e00008 */ 	jr	$ra
/*  f02b8f4:	27bd01f0 */ 	addiu	$sp,$sp,0x1f0
);
#else
GLOBAL_ASM(
glabel func0f02983c
.late_rodata
glabel var7f1a894c
.word 0x3c40c0c1
glabel var7f1a8950
.word 0x3c40c0c1
glabel var7f1a8954
.word 0x3bab8ba8
glabel var7f1a8958
.word 0x3bab8ba8
glabel var7f1a895c
.word 0x3f169697
glabel var7f1a8960
.word 0x3ea0a0a1
glabel var7f1a8964
.word 0x3e70f0f1
glabel var7f1a8968
.word 0x3e20a0a1
glabel var7f1a896c
.word 0x3c9309fe
glabel var7f1a8970
.word 0x40aaaaab
glabel var7f1a8974
.word 0x3b808081
glabel var7f1a8978
.word 0x3b808081
glabel var7f1a897c
.word 0x3b808081
glabel var7f1a8980
.word 0x3b808081
.text
/*  f02983c:	27bdfe10 */ 	addiu	$sp,$sp,-496
/*  f029840:	afb50038 */ 	sw	$s5,0x38($sp)
/*  f029844:	3c0e8006 */ 	lui	$t6,%hi(var80062a94)
/*  f029848:	8fb50200 */ 	lw	$s5,0x200($sp)
/*  f02984c:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f029850:	afb40034 */ 	sw	$s4,0x34($sp)
/*  f029854:	afb30030 */ 	sw	$s3,0x30($sp)
/*  f029858:	afb2002c */ 	sw	$s2,0x2c($sp)
/*  f02985c:	afb10028 */ 	sw	$s1,0x28($sp)
/*  f029860:	afb00024 */ 	sw	$s0,0x24($sp)
/*  f029864:	afa401f0 */ 	sw	$a0,0x1f0($sp)
/*  f029868:	afa501f4 */ 	sw	$a1,0x1f4($sp)
/*  f02986c:	afa601f8 */ 	sw	$a2,0x1f8($sp)
/*  f029870:	afa701fc */ 	sw	$a3,0x1fc($sp)
/*  f029874:	25ce2a94 */ 	addiu	$t6,$t6,%lo(var80062a94)
/*  f029878:	8dc10000 */ 	lw	$at,0x0($t6)
/*  f02987c:	27b201e0 */ 	addiu	$s2,$sp,0x1e0
/*  f029880:	8eb30004 */ 	lw	$s3,0x4($s5)
/*  f029884:	ae410000 */ 	sw	$at,0x0($s2)
/*  f029888:	8dd90004 */ 	lw	$t9,0x4($t6)
/*  f02988c:	3c0f8006 */ 	lui	$t7,%hi(var80062aa0)
/*  f029890:	25ef2aa0 */ 	addiu	$t7,$t7,%lo(var80062aa0)
/*  f029894:	ae590004 */ 	sw	$t9,0x4($s2)
/*  f029898:	8dc10008 */ 	lw	$at,0x8($t6)
/*  f02989c:	25f90060 */ 	addiu	$t9,$t7,0x60
/*  f0298a0:	27b80104 */ 	addiu	$t8,$sp,0x104
/*  f0298a4:	ae410008 */ 	sw	$at,0x8($s2)
.L0f0298a8:
/*  f0298a8:	8de10000 */ 	lw	$at,0x0($t7)
/*  f0298ac:	25ef000c */ 	addiu	$t7,$t7,0xc
/*  f0298b0:	2718000c */ 	addiu	$t8,$t8,0xc
/*  f0298b4:	af01fff4 */ 	sw	$at,-0xc($t8)
/*  f0298b8:	8de1fff8 */ 	lw	$at,-0x8($t7)
/*  f0298bc:	af01fff8 */ 	sw	$at,-0x8($t8)
/*  f0298c0:	8de1fffc */ 	lw	$at,-0x4($t7)
/*  f0298c4:	15f9fff8 */ 	bne	$t7,$t9,.L0f0298a8
/*  f0298c8:	af01fffc */ 	sw	$at,-0x4($t8)
/*  f0298cc:	8fae01f8 */ 	lw	$t6,0x1f8($sp)
/*  f0298d0:	24010003 */ 	addiu	$at,$zero,0x3
/*  f0298d4:	24110006 */ 	addiu	$s1,$zero,0x6
/*  f0298d8:	91c40000 */ 	lbu	$a0,0x0($t6)
/*  f0298dc:	8fb901f8 */ 	lw	$t9,0x1f8($sp)
/*  f0298e0:	50810004 */ 	beql	$a0,$at,.L0f0298f4
/*  f0298e4:	8f300004 */ 	lw	$s0,0x4($t9)
/*  f0298e8:	56240014 */ 	bnel	$s1,$a0,.L0f02993c
/*  f0298ec:	8fb901f8 */ 	lw	$t9,0x1f8($sp)
/*  f0298f0:	8f300004 */ 	lw	$s0,0x4($t9)
.L0f0298f4:
/*  f0298f4:	3c014120 */ 	lui	$at,0x4120
/*  f0298f8:	44812000 */ 	mtc1	$at,$f4
/*  f0298fc:	8e0f0020 */ 	lw	$t7,0x20($s0)
/*  f029900:	24110006 */ 	addiu	$s1,$zero,0x6
/*  f029904:	02002025 */ 	or	$a0,$s0,$zero
/*  f029908:	c5e60014 */ 	lwc1	$f6,0x14($t7)
/*  f02990c:	46062083 */ 	div.s	$f2,$f4,$f6
/*  f029910:	0fc0cfe8 */ 	jal	chrGetShield
/*  f029914:	e7a20170 */ 	swc1	$f2,0x170($sp)
/*  f029918:	921402e1 */ 	lbu	$s4,0x2e1($s0)
/*  f02991c:	960e0188 */ 	lhu	$t6,0x188($s0)
/*  f029920:	c7a20170 */ 	lwc1	$f2,0x170($sp)
/*  f029924:	0014c042 */ 	srl	$t8,$s4,0x1
/*  f029928:	46000386 */ 	mov.s	$f14,$f0
/*  f02992c:	0300a025 */ 	or	$s4,$t8,$zero
/*  f029930:	10000011 */ 	b	.L0f029978
/*  f029934:	afae0164 */ 	sw	$t6,0x164($sp)
/*  f029938:	8fb901f8 */ 	lw	$t9,0x1f8($sp)
.L0f02993c:
/*  f02993c:	44801000 */ 	mtc1	$zero,$f2
/*  f029940:	24140040 */ 	addiu	$s4,$zero,0x40
/*  f029944:	8f220004 */ 	lw	$v0,0x4($t9)
/*  f029948:	afa00164 */ 	sw	$zero,0x164($sp)
/*  f02994c:	3c014100 */ 	lui	$at,0x4100
/*  f029950:	8c4f0010 */ 	lw	$t7,0x10($v0)
/*  f029954:	31f81000 */ 	andi	$t8,$t7,0x1000
/*  f029958:	53000006 */ 	beqzl	$t8,.L0f029974
/*  f02995c:	44817000 */ 	mtc1	$at,$f14
/*  f029960:	3c014080 */ 	lui	$at,0x4080
/*  f029964:	44817000 */ 	mtc1	$at,$f14
/*  f029968:	10000004 */ 	b	.L0f02997c
/*  f02996c:	02a02025 */ 	or	$a0,$s5,$zero
/*  f029970:	44817000 */ 	mtc1	$at,$f14
.L0f029974:
/*  f029974:	00000000 */ 	nop
.L0f029978:
/*  f029978:	02a02025 */ 	or	$a0,$s5,$zero
.L0f02997c:
/*  f02997c:	00002825 */ 	or	$a1,$zero,$zero
/*  f029980:	e7a20170 */ 	swc1	$f2,0x170($sp)
/*  f029984:	0c006949 */ 	jal	func0001a524
/*  f029988:	e7ae016c */ 	swc1	$f14,0x16c($sp)
/*  f02998c:	c7a20170 */ 	lwc1	$f2,0x170($sp)
/*  f029990:	c6680004 */ 	lwc1	$f8,0x4($s3)
/*  f029994:	c6720008 */ 	lwc1	$f18,0x8($s3)
/*  f029998:	8fae01fc */ 	lw	$t6,0x1fc($sp)
/*  f02999c:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f0299a0:	c668000c */ 	lwc1	$f8,0xc($s3)
/*  f0299a4:	8dd9000c */ 	lw	$t9,0xc($t6)
/*  f0299a8:	46029100 */ 	add.s	$f4,$f18,$f2
/*  f0299ac:	c6720010 */ 	lwc1	$f18,0x10($s3)
/*  f0299b0:	8fb001f0 */ 	lw	$s0,0x1f0($sp)
/*  f0299b4:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f0299b8:	00027980 */ 	sll	$t7,$v0,0x6
/*  f0299bc:	032f2021 */ 	addu	$a0,$t9,$t7
/*  f0299c0:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f0299c4:	44038000 */ 	mfc1	$v1,$f16
/*  f0299c8:	3c190102 */ 	lui	$t9,0x102
/*  f0299cc:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f0299d0:	c6680014 */ 	lwc1	$f8,0x14($s3)
/*  f0299d4:	44053000 */ 	mfc1	$a1,$f6
/*  f0299d8:	46029100 */ 	add.s	$f4,$f18,$f2
/*  f0299dc:	c6720018 */ 	lwc1	$f18,0x18($s3)
/*  f0299e0:	260a0008 */ 	addiu	$t2,$s0,0x8
/*  f0299e4:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f0299e8:	c7ae016c */ 	lwc1	$f14,0x16c($sp)
/*  f0299ec:	afaa01f0 */ 	sw	$t2,0x1f0($sp)
/*  f0299f0:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f0299f4:	44068000 */ 	mfc1	$a2,$f16
/*  f0299f8:	37390040 */ 	ori	$t9,$t9,0x40
/*  f0299fc:	46024281 */ 	sub.s	$f10,$f8,$f2
/*  f029a00:	44073000 */ 	mfc1	$a3,$f6
/*  f029a04:	a7a30180 */ 	sh	$v1,0x180($sp)
/*  f029a08:	46029100 */ 	add.s	$f4,$f18,$f2
/*  f029a0c:	a7a30186 */ 	sh	$v1,0x186($sp)
/*  f029a10:	a7a3018c */ 	sh	$v1,0x18c($sp)
/*  f029a14:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f029a18:	a7a30192 */ 	sh	$v1,0x192($sp)
/*  f029a1c:	a7a50198 */ 	sh	$a1,0x198($sp)
/*  f029a20:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f029a24:	44088000 */ 	mfc1	$t0,$f16
/*  f029a28:	a7a5019e */ 	sh	$a1,0x19e($sp)
/*  f029a2c:	a7a501a4 */ 	sh	$a1,0x1a4($sp)
/*  f029a30:	44093000 */ 	mfc1	$t1,$f6
/*  f029a34:	a7a501aa */ 	sh	$a1,0x1aa($sp)
/*  f029a38:	a7a60182 */ 	sh	$a2,0x182($sp)
/*  f029a3c:	a7a60188 */ 	sh	$a2,0x188($sp)
/*  f029a40:	a7a6019a */ 	sh	$a2,0x19a($sp)
/*  f029a44:	a7a601a0 */ 	sh	$a2,0x1a0($sp)
/*  f029a48:	a7a7018e */ 	sh	$a3,0x18e($sp)
/*  f029a4c:	a7a70194 */ 	sh	$a3,0x194($sp)
/*  f029a50:	a7a701a6 */ 	sh	$a3,0x1a6($sp)
/*  f029a54:	a7a701ac */ 	sh	$a3,0x1ac($sp)
/*  f029a58:	a7a80184 */ 	sh	$t0,0x184($sp)
/*  f029a5c:	a7a80190 */ 	sh	$t0,0x190($sp)
/*  f029a60:	a7a8019c */ 	sh	$t0,0x19c($sp)
/*  f029a64:	a7a801a8 */ 	sh	$t0,0x1a8($sp)
/*  f029a68:	a7a9018a */ 	sh	$t1,0x18a($sp)
/*  f029a6c:	a7a90196 */ 	sh	$t1,0x196($sp)
/*  f029a70:	a7a901a2 */ 	sh	$t1,0x1a2($sp)
/*  f029a74:	a7a901ae */ 	sh	$t1,0x1ae($sp)
/*  f029a78:	ae190000 */ 	sw	$t9,0x0($s0)
/*  f029a7c:	afa301cc */ 	sw	$v1,0x1cc($sp)
/*  f029a80:	afa501c8 */ 	sw	$a1,0x1c8($sp)
/*  f029a84:	e7ae016c */ 	swc1	$f14,0x16c($sp)
/*  f029a88:	afa601c4 */ 	sw	$a2,0x1c4($sp)
/*  f029a8c:	afa701c0 */ 	sw	$a3,0x1c0($sp)
/*  f029a90:	afa801bc */ 	sw	$t0,0x1bc($sp)
/*  f029a94:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f029a98:	afa901b8 */ 	sw	$t1,0x1b8($sp)
/*  f029a9c:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f029aa0:	c7ae016c */ 	lwc1	$f14,0x16c($sp)
/*  f029aa4:	2401fff9 */ 	addiu	$at,$zero,-7
/*  f029aa8:	15010082 */ 	bne	$t0,$at,.L0f029cb4
/*  f029aac:	ae020004 */ 	sw	$v0,0x4($s0)
/*  f029ab0:	0fc59e73 */ 	jal	gfxAllocateColours
/*  f029ab4:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f029ab8:	8fb001f0 */ 	lw	$s0,0x1f0($sp)
/*  f029abc:	3c0e0700 */ 	lui	$t6,0x700
/*  f029ac0:	35ce0004 */ 	ori	$t6,$t6,0x4
/*  f029ac4:	26180008 */ 	addiu	$t8,$s0,0x8
/*  f029ac8:	afb801f0 */ 	sw	$t8,0x1f0($sp)
/*  f029acc:	ae0e0000 */ 	sw	$t6,0x0($s0)
/*  f029ad0:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f029ad4:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f029ad8:	00402025 */ 	or	$a0,$v0,$zero
/*  f029adc:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f029ae0:	ae020004 */ 	sw	$v0,0x4($s0)
/*  f029ae4:	240400ff */ 	addiu	$a0,$zero,0xff
/*  f029ae8:	2a810040 */ 	slti	$at,$s4,0x40
/*  f029aec:	a0640000 */ 	sb	$a0,0x0($v1)
/*  f029af0:	a0640001 */ 	sb	$a0,0x1($v1)
/*  f029af4:	1020000f */ 	beqz	$at,.L0f029b34
/*  f029af8:	a0640002 */ 	sb	$a0,0x2($v1)
/*  f029afc:	8fb90210 */ 	lw	$t9,0x210($sp)
/*  f029b00:	44944000 */ 	mtc1	$s4,$f8
/*  f029b04:	3c017f1b */ 	lui	$at,%hi(var7f1a894c)
/*  f029b08:	44998000 */ 	mtc1	$t9,$f16
/*  f029b0c:	468042a0 */ 	cvt.s.w	$f10,$f8
/*  f029b10:	c426894c */ 	lwc1	$f6,%lo(var7f1a894c)($at)
/*  f029b14:	468084a0 */ 	cvt.s.w	$f18,$f16
/*  f029b18:	46125102 */ 	mul.s	$f4,$f10,$f18
/*  f029b1c:	00000000 */ 	nop
/*  f029b20:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f029b24:	4600440d */ 	trunc.w.s	$f16,$f8
/*  f029b28:	44188000 */ 	mfc1	$t8,$f16
/*  f029b2c:	10000011 */ 	b	.L0f029b74
/*  f029b30:	a0780003 */ 	sb	$t8,0x3($v1)
.L0f029b34:
/*  f029b34:	8faf0210 */ 	lw	$t7,0x210($sp)
/*  f029b38:	240e007f */ 	addiu	$t6,$zero,0x7f
/*  f029b3c:	01d4c823 */ 	subu	$t9,$t6,$s4
/*  f029b40:	44995000 */ 	mtc1	$t9,$f10
/*  f029b44:	448f2000 */ 	mtc1	$t7,$f4
/*  f029b48:	3c017f1b */ 	lui	$at,%hi(var7f1a8950)
/*  f029b4c:	468054a0 */ 	cvt.s.w	$f18,$f10
/*  f029b50:	c4308950 */ 	lwc1	$f16,%lo(var7f1a8950)($at)
/*  f029b54:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f029b58:	46069202 */ 	mul.s	$f8,$f18,$f6
/*  f029b5c:	00000000 */ 	nop
/*  f029b60:	46104282 */ 	mul.s	$f10,$f8,$f16
/*  f029b64:	4600510d */ 	trunc.w.s	$f4,$f10
/*  f029b68:	440e2000 */ 	mfc1	$t6,$f4
/*  f029b6c:	00000000 */ 	nop
/*  f029b70:	a06e0003 */ 	sb	$t6,0x3($v1)
.L0f029b74:
/*  f029b74:	0fc59e59 */ 	jal	gfxAllocateVertices
/*  f029b78:	24040018 */ 	addiu	$a0,$zero,0x18
/*  f029b7c:	00408025 */ 	or	$s0,$v0,$zero
/*  f029b80:	27a60104 */ 	addiu	$a2,$sp,0x104
/*  f029b84:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f029b88:	24070200 */ 	addiu	$a3,$zero,0x200
/*  f029b8c:	27a50180 */ 	addiu	$a1,$sp,0x180
.L0f029b90:
/*  f029b90:	00002025 */ 	or	$a0,$zero,$zero
/*  f029b94:	02001825 */ 	or	$v1,$s0,$zero
/*  f029b98:	00c01025 */ 	or	$v0,$a2,$zero
.L0f029b9c:
/*  f029b9c:	8e410000 */ 	lw	$at,0x0($s2)
/*  f029ba0:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f029ba4:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f029ba8:	a861fff4 */ 	swl	$at,-0xc($v1)
/*  f029bac:	b861fff7 */ 	swr	$at,-0x9($v1)
/*  f029bb0:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f029bb4:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f029bb8:	a86ffff8 */ 	swl	$t7,-0x8($v1)
/*  f029bbc:	b86ffffb */ 	swr	$t7,-0x5($v1)
/*  f029bc0:	8e410008 */ 	lw	$at,0x8($s2)
/*  f029bc4:	a861fffc */ 	swl	$at,-0x4($v1)
/*  f029bc8:	b861ffff */ 	swr	$at,-0x1($v1)
/*  f029bcc:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f029bd0:	03110019 */ 	multu	$t8,$s1
/*  f029bd4:	00007012 */ 	mflo	$t6
/*  f029bd8:	00aec821 */ 	addu	$t9,$a1,$t6
/*  f029bdc:	872f0000 */ 	lh	$t7,0x0($t9)
/*  f029be0:	a46ffff4 */ 	sh	$t7,-0xc($v1)
/*  f029be4:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f029be8:	03110019 */ 	multu	$t8,$s1
/*  f029bec:	00007012 */ 	mflo	$t6
/*  f029bf0:	00aec821 */ 	addu	$t9,$a1,$t6
/*  f029bf4:	872f0002 */ 	lh	$t7,0x2($t9)
/*  f029bf8:	a46ffff6 */ 	sh	$t7,-0xa($v1)
/*  f029bfc:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f029c00:	03110019 */ 	multu	$t8,$s1
/*  f029c04:	00007012 */ 	mflo	$t6
/*  f029c08:	00aec821 */ 	addu	$t9,$a1,$t6
/*  f029c0c:	872f0004 */ 	lh	$t7,0x4($t9)
/*  f029c10:	a060fffb */ 	sb	$zero,-0x5($v1)
/*  f029c14:	1489ffe1 */ 	bne	$a0,$t1,.L0f029b9c
/*  f029c18:	a46ffff8 */ 	sh	$t7,-0x8($v1)
/*  f029c1c:	a6000008 */ 	sh	$zero,0x8($s0)
/*  f029c20:	a600000a */ 	sh	$zero,0xa($s0)
/*  f029c24:	a6070014 */ 	sh	$a3,0x14($s0)
/*  f029c28:	a6000016 */ 	sh	$zero,0x16($s0)
/*  f029c2c:	a6070020 */ 	sh	$a3,0x20($s0)
/*  f029c30:	a6070022 */ 	sh	$a3,0x22($s0)
/*  f029c34:	a600002c */ 	sh	$zero,0x2c($s0)
/*  f029c38:	a607002e */ 	sh	$a3,0x2e($s0)
/*  f029c3c:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f029c40:	3c190430 */ 	lui	$t9,0x430
/*  f029c44:	37390030 */ 	ori	$t9,$t9,0x30
/*  f029c48:	270e0008 */ 	addiu	$t6,$t8,0x8
/*  f029c4c:	afae01f0 */ 	sw	$t6,0x1f0($sp)
/*  f029c50:	af190000 */ 	sw	$t9,0x0($t8)
/*  f029c54:	afa60054 */ 	sw	$a2,0x54($sp)
/*  f029c58:	02002025 */ 	or	$a0,$s0,$zero
/*  f029c5c:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f029c60:	afb800c8 */ 	sw	$t8,0xc8($sp)
/*  f029c64:	8fa800c8 */ 	lw	$t0,0xc8($sp)
/*  f029c68:	8fa60054 */ 	lw	$a2,0x54($sp)
/*  f029c6c:	3c0eb100 */ 	lui	$t6,0xb100
/*  f029c70:	ad020004 */ 	sw	$v0,0x4($t0)
/*  f029c74:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
/*  f029c78:	35ce0032 */ 	ori	$t6,$t6,0x32
/*  f029c7c:	24192010 */ 	addiu	$t9,$zero,0x2010
/*  f029c80:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f029c84:	afb801f0 */ 	sw	$t8,0x1f0($sp)
/*  f029c88:	adf90004 */ 	sw	$t9,0x4($t7)
/*  f029c8c:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f029c90:	27af0164 */ 	addiu	$t7,$sp,0x164
/*  f029c94:	24c60010 */ 	addiu	$a2,$a2,0x10
/*  f029c98:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f029c9c:	24070200 */ 	addiu	$a3,$zero,0x200
/*  f029ca0:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f029ca4:	14cfffba */ 	bne	$a2,$t7,.L0f029b90
/*  f029ca8:	26100030 */ 	addiu	$s0,$s0,0x30
/*  f029cac:	100006c0 */ 	b	.L0f02b7b0
/*  f029cb0:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f029cb4:
/*  f029cb4:	3c05800b */ 	lui	$a1,%hi(var800ab58c)
/*  f029cb8:	24180002 */ 	addiu	$t8,$zero,0x2
/*  f029cbc:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f029cc0:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f029cc4:	afb80010 */ 	sw	$t8,0x10($sp)
/*  f029cc8:	8ca5b58c */ 	lw	$a1,%lo(var800ab58c)($a1)
/*  f029ccc:	27a401f0 */ 	addiu	$a0,$sp,0x1f0
/*  f029cd0:	24060004 */ 	addiu	$a2,$zero,0x4
/*  f029cd4:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f029cd8:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f029cdc:	0fc2ce70 */ 	jal	func0f0b39c0
/*  f029ce0:	e7ae016c */ 	swc1	$f14,0x16c($sp)
/*  f029ce4:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f029ce8:	c7ae016c */ 	lwc1	$f14,0x16c($sp)
/*  f029cec:	27a50100 */ 	addiu	$a1,$sp,0x100
/*  f029cf0:	05000004 */ 	bltz	$t0,.L0f029d04
/*  f029cf4:	27a600fc */ 	addiu	$a2,$sp,0xfc
/*  f029cf8:	8fb901f4 */ 	lw	$t9,0x1f4($sp)
/*  f029cfc:	1000001c */ 	b	.L0f029d70
/*  f029d00:	c72c0058 */ 	lwc1	$f12,0x58($t9)
.L0f029d04:
/*  f029d04:	2401fffe */ 	addiu	$at,$zero,-2
/*  f029d08:	15010019 */ 	bne	$t0,$at,.L0f029d70
/*  f029d0c:	46007306 */ 	mov.s	$f12,$f14
/*  f029d10:	8faf01f4 */ 	lw	$t7,0x1f4($sp)
/*  f029d14:	8fb8020c */ 	lw	$t8,0x20c($sp)
/*  f029d18:	81e20011 */ 	lb	$v0,0x11($t7)
/*  f029d1c:	0058082a */ 	slt	$at,$v0,$t8
/*  f029d20:	50200005 */ 	beqzl	$at,.L0f029d38
/*  f029d24:	44823000 */ 	mtc1	$v0,$f6
/*  f029d28:	44806000 */ 	mtc1	$zero,$f12
/*  f029d2c:	10000010 */ 	b	.L0f029d70
/*  f029d30:	00000000 */ 	nop
/*  f029d34:	44823000 */ 	mtc1	$v0,$f6
.L0f029d38:
/*  f029d38:	8fae020c */ 	lw	$t6,0x20c($sp)
/*  f029d3c:	3c014080 */ 	lui	$at,0x4080
/*  f029d40:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f029d44:	44819000 */ 	mtc1	$at,$f18
/*  f029d48:	448e8000 */ 	mtc1	$t6,$f16
/*  f029d4c:	3c013f80 */ 	lui	$at,0x3f80
/*  f029d50:	44813000 */ 	mtc1	$at,$f6
/*  f029d54:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f029d58:	46089002 */ 	mul.s	$f0,$f18,$f8
/*  f029d5c:	460a0101 */ 	sub.s	$f4,$f0,$f10
/*  f029d60:	46062480 */ 	add.s	$f18,$f4,$f6
/*  f029d64:	46009203 */ 	div.s	$f8,$f18,$f0
/*  f029d68:	46087302 */ 	mul.s	$f12,$f14,$f8
/*  f029d6c:	00000000 */ 	nop
.L0f029d70:
/*  f029d70:	0fc0a57e */ 	jal	func0f0295f8
/*  f029d74:	27a700f8 */ 	addiu	$a3,$sp,0xf8
/*  f029d78:	8fac0100 */ 	lw	$t4,0x100($sp)
/*  f029d7c:	8fad00fc */ 	lw	$t5,0xfc($sp)
/*  f029d80:	8fbf00f8 */ 	lw	$ra,0xf8($sp)
/*  f029d84:	2587ffec */ 	addiu	$a3,$t4,-20
/*  f029d88:	25a3ffec */ 	addiu	$v1,$t5,-20
/*  f029d8c:	27e4ffec */ 	addiu	$a0,$ra,-20
/*  f029d90:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f029d94:	00605025 */ 	or	$t2,$v1,$zero
/*  f029d98:	04e10002 */ 	bgez	$a3,.L0f029da4
/*  f029d9c:	00805825 */ 	or	$t3,$a0,$zero
/*  f029da0:	00003825 */ 	or	$a3,$zero,$zero
.L0f029da4:
/*  f029da4:	04610002 */ 	bgez	$v1,.L0f029db0
/*  f029da8:	2582ffc4 */ 	addiu	$v0,$t4,-60
/*  f029dac:	00005025 */ 	or	$t2,$zero,$zero
.L0f029db0:
/*  f029db0:	04810002 */ 	bgez	$a0,.L0f029dbc
/*  f029db4:	25a3ffc4 */ 	addiu	$v1,$t5,-60
/*  f029db8:	00005825 */ 	or	$t3,$zero,$zero
.L0f029dbc:
/*  f029dbc:	27e4ffc4 */ 	addiu	$a0,$ra,-60
/*  f029dc0:	afa200e8 */ 	sw	$v0,0xe8($sp)
/*  f029dc4:	afa300e4 */ 	sw	$v1,0xe4($sp)
/*  f029dc8:	04410002 */ 	bgez	$v0,.L0f029dd4
/*  f029dcc:	afa400e0 */ 	sw	$a0,0xe0($sp)
/*  f029dd0:	afa000e8 */ 	sw	$zero,0xe8($sp)
.L0f029dd4:
/*  f029dd4:	04610002 */ 	bgez	$v1,.L0f029de0
/*  f029dd8:	3c19800a */ 	lui	$t9,%hi(g_Vars+0x58)
/*  f029ddc:	afa000e4 */ 	sw	$zero,0xe4($sp)
.L0f029de0:
/*  f029de0:	04810002 */ 	bgez	$a0,.L0f029dec
/*  f029de4:	00000000 */ 	nop
/*  f029de8:	afa000e0 */ 	sw	$zero,0xe0($sp)
.L0f029dec:
/*  f029dec:	8f39a018 */ 	lw	$t9,%lo(g_Vars+0x58)($t9)
/*  f029df0:	241004b0 */ 	addiu	$s0,$zero,0x4b0
/*  f029df4:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f029df8:	0330001a */ 	div	$zero,$t9,$s0
/*  f029dfc:	00007810 */ 	mfhi	$t7
/*  f029e00:	448f8000 */ 	mtc1	$t7,$f16
/*  f029e04:	16000002 */ 	bnez	$s0,.L0f029e10
/*  f029e08:	00000000 */ 	nop
/*  f029e0c:	0007000d */ 	break	0x7
.L0f029e10:
/*  f029e10:	2401ffff */ 	addiu	$at,$zero,-1
/*  f029e14:	16010004 */ 	bne	$s0,$at,.L0f029e28
/*  f029e18:	3c018000 */ 	lui	$at,0x8000
/*  f029e1c:	17210002 */ 	bne	$t9,$at,.L0f029e28
/*  f029e20:	00000000 */ 	nop
/*  f029e24:	0006000d */ 	break	0x6
.L0f029e28:
/*  f029e28:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f029e2c:	3c017f1b */ 	lui	$at,%hi(var7f1a8954)
/*  f029e30:	c4248954 */ 	lwc1	$f4,%lo(var7f1a8954)($at)
/*  f029e34:	afaa00f0 */ 	sw	$t2,0xf0($sp)
/*  f029e38:	afab00ec */ 	sw	$t3,0xec($sp)
/*  f029e3c:	46045302 */ 	mul.s	$f12,$f10,$f4
/*  f029e40:	0c0068f7 */ 	jal	sinf
/*  f029e44:	00000000 */ 	nop
/*  f029e48:	3c0f800a */ 	lui	$t7,%hi(g_Vars+0x58)
/*  f029e4c:	8defa018 */ 	lw	$t7,%lo(g_Vars+0x58)($t7)
/*  f029e50:	3c014200 */ 	lui	$at,0x4200
/*  f029e54:	44811000 */ 	mtc1	$at,$f2
/*  f029e58:	01f0001a */ 	div	$zero,$t7,$s0
/*  f029e5c:	3c013f80 */ 	lui	$at,0x3f80
/*  f029e60:	44813000 */ 	mtc1	$at,$f6
/*  f029e64:	3c013f00 */ 	lui	$at,0x3f00
/*  f029e68:	44814000 */ 	mtc1	$at,$f8
/*  f029e6c:	46060480 */ 	add.s	$f18,$f0,$f6
/*  f029e70:	0000c010 */ 	mfhi	$t8
/*  f029e74:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f029e78:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f029e7c:	46089402 */ 	mul.s	$f16,$f18,$f8
/*  f029e80:	44989000 */ 	mtc1	$t8,$f18
/*  f029e84:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f029e88:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f029e8c:	46809220 */ 	cvt.s.w	$f8,$f18
/*  f029e90:	46028282 */ 	mul.s	$f10,$f16,$f2
/*  f029e94:	00000000 */ 	nop
/*  f029e98:	46025102 */ 	mul.s	$f4,$f10,$f2
/*  f029e9c:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f029ea0:	44153000 */ 	mfc1	$s5,$f6
/*  f029ea4:	00000000 */ 	nop
/*  f029ea8:	00157400 */ 	sll	$t6,$s5,0x10
/*  f029eac:	000ecc03 */ 	sra	$t9,$t6,0x10
/*  f029eb0:	0320a825 */ 	or	$s5,$t9,$zero
/*  f029eb4:	16000002 */ 	bnez	$s0,.L0f029ec0
/*  f029eb8:	00000000 */ 	nop
/*  f029ebc:	0007000d */ 	break	0x7
.L0f029ec0:
/*  f029ec0:	2401ffff */ 	addiu	$at,$zero,-1
/*  f029ec4:	16010004 */ 	bne	$s0,$at,.L0f029ed8
/*  f029ec8:	3c018000 */ 	lui	$at,0x8000
/*  f029ecc:	15e10002 */ 	bne	$t7,$at,.L0f029ed8
/*  f029ed0:	00000000 */ 	nop
/*  f029ed4:	0006000d */ 	break	0x6
.L0f029ed8:
/*  f029ed8:	3c017f1b */ 	lui	$at,%hi(var7f1a8958)
/*  f029edc:	c4308958 */ 	lwc1	$f16,%lo(var7f1a8958)($at)
/*  f029ee0:	46104302 */ 	mul.s	$f12,$f8,$f16
/*  f029ee4:	0c0068f4 */ 	jal	cosf
/*  f029ee8:	00000000 */ 	nop
/*  f029eec:	3c014200 */ 	lui	$at,0x4200
/*  f029ef0:	44811000 */ 	mtc1	$at,$f2
/*  f029ef4:	3c013f80 */ 	lui	$at,0x3f80
/*  f029ef8:	44816000 */ 	mtc1	$at,$f12
/*  f029efc:	3c013f00 */ 	lui	$at,0x3f00
/*  f029f00:	44812000 */ 	mtc1	$at,$f4
/*  f029f04:	460c0280 */ 	add.s	$f10,$f0,$f12
/*  f029f08:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f029f0c:	26af0200 */ 	addiu	$t7,$s5,0x200
/*  f029f10:	2401fffd */ 	addiu	$at,$zero,-3
/*  f029f14:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f029f18:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f029f1c:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f029f20:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f029f24:	afaf0050 */ 	sw	$t7,0x50($sp)
/*  f029f28:	a7af0176 */ 	sh	$t7,0x176($sp)
/*  f029f2c:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f029f30:	46023482 */ 	mul.s	$f18,$f6,$f2
/*  f029f34:	00000000 */ 	nop
/*  f029f38:	46029202 */ 	mul.s	$f8,$f18,$f2
/*  f029f3c:	4600440d */ 	trunc.w.s	$f16,$f8
/*  f029f40:	440e8000 */ 	mfc1	$t6,$f16
/*  f029f44:	00000000 */ 	nop
/*  f029f48:	000e9c00 */ 	sll	$s3,$t6,0x10
/*  f029f4c:	0013cc03 */ 	sra	$t9,$s3,0x10
/*  f029f50:	03209825 */ 	or	$s3,$t9,$zero
/*  f029f54:	25d40200 */ 	addiu	$s4,$t6,0x200
/*  f029f58:	0014cc00 */ 	sll	$t9,$s4,0x10
/*  f029f5c:	11010008 */ 	beq	$t0,$at,.L0f029f80
/*  f029f60:	0019a403 */ 	sra	$s4,$t9,0x10
/*  f029f64:	2401fffc */ 	addiu	$at,$zero,-4
/*  f029f68:	11010005 */ 	beq	$t0,$at,.L0f029f80
/*  f029f6c:	2401fffb */ 	addiu	$at,$zero,-5
/*  f029f70:	11010003 */ 	beq	$t0,$at,.L0f029f80
/*  f029f74:	2401fffa */ 	addiu	$at,$zero,-6
/*  f029f78:	5501016b */ 	bnel	$t0,$at,.L0f02a528
/*  f029f7c:	2401fffe */ 	addiu	$at,$zero,-2
.L0f029f80:
/*  f029f80:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f029f84:	afaa00f0 */ 	sw	$t2,0xf0($sp)
/*  f029f88:	0fc59e73 */ 	jal	gfxAllocateColours
/*  f029f8c:	afab00ec */ 	sw	$t3,0xec($sp)
/*  f029f90:	8fb001f0 */ 	lw	$s0,0x1f0($sp)
/*  f029f94:	3c190700 */ 	lui	$t9,0x700
/*  f029f98:	37390004 */ 	ori	$t9,$t9,0x4
/*  f029f9c:	260e0008 */ 	addiu	$t6,$s0,0x8
/*  f029fa0:	afae01f0 */ 	sw	$t6,0x1f0($sp)
/*  f029fa4:	ae190000 */ 	sw	$t9,0x0($s0)
/*  f029fa8:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f029fac:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f029fb0:	00402025 */ 	or	$a0,$v0,$zero
/*  f029fb4:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f029fb8:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f029fbc:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f029fc0:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f029fc4:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f029fc8:	2401fffd */ 	addiu	$at,$zero,-3
/*  f029fcc:	15010014 */ 	bne	$t0,$at,.L0f02a020
/*  f029fd0:	ae020004 */ 	sw	$v0,0x4($s0)
/*  f029fd4:	a0670000 */ 	sb	$a3,0x0($v1)
/*  f029fd8:	a06a0001 */ 	sb	$t2,0x1($v1)
/*  f029fdc:	a06b0002 */ 	sb	$t3,0x2($v1)
/*  f029fe0:	8faf0164 */ 	lw	$t7,0x164($sp)
/*  f029fe4:	8fb80210 */ 	lw	$t8,0x210($sp)
/*  f029fe8:	29e1000a */ 	slti	$at,$t7,0xa
/*  f029fec:	1020000a */ 	beqz	$at,.L0f02a018
/*  f029ff0:	00000000 */ 	nop
/*  f029ff4:	44985000 */ 	mtc1	$t8,$f10
/*  f029ff8:	3c017f1b */ 	lui	$at,%hi(var7f1a895c)
/*  f029ffc:	c426895c */ 	lwc1	$f6,%lo(var7f1a895c)($at)
/*  f02a000:	46805120 */ 	cvt.s.w	$f4,$f10
/*  f02a004:	46062482 */ 	mul.s	$f18,$f4,$f6
/*  f02a008:	4600920d */ 	trunc.w.s	$f8,$f18
/*  f02a00c:	44194000 */ 	mfc1	$t9,$f8
/*  f02a010:	10000031 */ 	b	.L0f02a0d8
/*  f02a014:	a0790003 */ 	sb	$t9,0x3($v1)
.L0f02a018:
/*  f02a018:	1000002f */ 	b	.L0f02a0d8
/*  f02a01c:	a0600003 */ 	sb	$zero,0x3($v1)
.L0f02a020:
/*  f02a020:	8faf00e8 */ 	lw	$t7,0xe8($sp)
/*  f02a024:	a06f0000 */ 	sb	$t7,0x0($v1)
/*  f02a028:	8fb800e4 */ 	lw	$t8,0xe4($sp)
/*  f02a02c:	a0780001 */ 	sb	$t8,0x1($v1)
/*  f02a030:	8fae00e0 */ 	lw	$t6,0xe0($sp)
/*  f02a034:	a06e0002 */ 	sb	$t6,0x2($v1)
/*  f02a038:	8fb90164 */ 	lw	$t9,0x164($sp)
/*  f02a03c:	2b21000a */ 	slti	$at,$t9,0xa
/*  f02a040:	10200024 */ 	beqz	$at,.L0f02a0d4
/*  f02a044:	2401fffc */ 	addiu	$at,$zero,-4
/*  f02a048:	1501000a */ 	bne	$t0,$at,.L0f02a074
/*  f02a04c:	8faf0210 */ 	lw	$t7,0x210($sp)
/*  f02a050:	448f8000 */ 	mtc1	$t7,$f16
/*  f02a054:	3c017f1b */ 	lui	$at,%hi(var7f1a8960)
/*  f02a058:	c4248960 */ 	lwc1	$f4,%lo(var7f1a8960)($at)
/*  f02a05c:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f02a060:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f02a064:	4600348d */ 	trunc.w.s	$f18,$f6
/*  f02a068:	440e9000 */ 	mfc1	$t6,$f18
/*  f02a06c:	1000001a */ 	b	.L0f02a0d8
/*  f02a070:	a06e0003 */ 	sb	$t6,0x3($v1)
.L0f02a074:
/*  f02a074:	2401fffb */ 	addiu	$at,$zero,-5
/*  f02a078:	1501000a */ 	bne	$t0,$at,.L0f02a0a4
/*  f02a07c:	8fb90210 */ 	lw	$t9,0x210($sp)
/*  f02a080:	44994000 */ 	mtc1	$t9,$f8
/*  f02a084:	3c017f1b */ 	lui	$at,%hi(var7f1a8964)
/*  f02a088:	c42a8964 */ 	lwc1	$f10,%lo(var7f1a8964)($at)
/*  f02a08c:	46804420 */ 	cvt.s.w	$f16,$f8
/*  f02a090:	460a8102 */ 	mul.s	$f4,$f16,$f10
/*  f02a094:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f02a098:	44183000 */ 	mfc1	$t8,$f6
/*  f02a09c:	1000000e */ 	b	.L0f02a0d8
/*  f02a0a0:	a0780003 */ 	sb	$t8,0x3($v1)
.L0f02a0a4:
/*  f02a0a4:	2401fffa */ 	addiu	$at,$zero,-6
/*  f02a0a8:	1501000b */ 	bne	$t0,$at,.L0f02a0d8
/*  f02a0ac:	8fae0210 */ 	lw	$t6,0x210($sp)
/*  f02a0b0:	448e9000 */ 	mtc1	$t6,$f18
/*  f02a0b4:	3c017f1b */ 	lui	$at,%hi(var7f1a8968)
/*  f02a0b8:	c4308968 */ 	lwc1	$f16,%lo(var7f1a8968)($at)
/*  f02a0bc:	46809220 */ 	cvt.s.w	$f8,$f18
/*  f02a0c0:	46104282 */ 	mul.s	$f10,$f8,$f16
/*  f02a0c4:	4600510d */ 	trunc.w.s	$f4,$f10
/*  f02a0c8:	440f2000 */ 	mfc1	$t7,$f4
/*  f02a0cc:	10000002 */ 	b	.L0f02a0d8
/*  f02a0d0:	a06f0003 */ 	sb	$t7,0x3($v1)
.L0f02a0d4:
/*  f02a0d4:	a0600003 */ 	sb	$zero,0x3($v1)
.L0f02a0d8:
/*  f02a0d8:	24040018 */ 	addiu	$a0,$zero,0x18
/*  f02a0dc:	afa301d8 */ 	sw	$v1,0x1d8($sp)
/*  f02a0e0:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f02a0e4:	afaa00f0 */ 	sw	$t2,0xf0($sp)
/*  f02a0e8:	0fc59e59 */ 	jal	gfxAllocateVertices
/*  f02a0ec:	afab00ec */ 	sw	$t3,0xec($sp)
/*  f02a0f0:	8fa501f8 */ 	lw	$a1,0x1f8($sp)
/*  f02a0f4:	24010001 */ 	addiu	$at,$zero,0x1
/*  f02a0f8:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02a0fc:	90a40000 */ 	lbu	$a0,0x0($a1)
/*  f02a100:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f02a104:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f02a108:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f02a10c:	10810006 */ 	beq	$a0,$at,.L0f02a128
/*  f02a110:	00408025 */ 	or	$s0,$v0,$zero
/*  f02a114:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f02a118:	11240003 */ 	beq	$t1,$a0,.L0f02a128
/*  f02a11c:	24010002 */ 	addiu	$at,$zero,0x2
/*  f02a120:	548100b0 */ 	bnel	$a0,$at,.L0f02a3e4
/*  f02a124:	24080200 */ 	addiu	$t0,$zero,0x200
.L0f02a128:
/*  f02a128:	8cb80004 */ 	lw	$t8,0x4($a1)
/*  f02a12c:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f02a130:	3c0f800a */ 	lui	$t7,%hi(g_Vars+0x58)
/*  f02a134:	8f0e0010 */ 	lw	$t6,0x10($t8)
/*  f02a138:	31d91000 */ 	andi	$t9,$t6,0x1000
/*  f02a13c:	532000a9 */ 	beqzl	$t9,.L0f02a3e4
/*  f02a140:	24080200 */ 	addiu	$t0,$zero,0x200
/*  f02a144:	8defa018 */ 	lw	$t7,%lo(g_Vars+0x58)($t7)
/*  f02a148:	2401015e */ 	addiu	$at,$zero,0x15e
/*  f02a14c:	afa301d8 */ 	sw	$v1,0x1d8($sp)
/*  f02a150:	01e1001a */ 	div	$zero,$t7,$at
/*  f02a154:	0000c010 */ 	mfhi	$t8
/*  f02a158:	44983000 */ 	mtc1	$t8,$f6
/*  f02a15c:	3c017f1b */ 	lui	$at,%hi(var7f1a896c)
/*  f02a160:	c428896c */ 	lwc1	$f8,%lo(var7f1a896c)($at)
/*  f02a164:	468034a0 */ 	cvt.s.w	$f18,$f6
/*  f02a168:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f02a16c:	afaa00f0 */ 	sw	$t2,0xf0($sp)
/*  f02a170:	afab00ec */ 	sw	$t3,0xec($sp)
/*  f02a174:	46089302 */ 	mul.s	$f12,$f18,$f8
/*  f02a178:	0c0068f7 */ 	jal	sinf
/*  f02a17c:	00000000 */ 	nop
/*  f02a180:	3c013f80 */ 	lui	$at,0x3f80
/*  f02a184:	44818000 */ 	mtc1	$at,$f16
/*  f02a188:	3c013f00 */ 	lui	$at,0x3f00
/*  f02a18c:	44812000 */ 	mtc1	$at,$f4
/*  f02a190:	46100280 */ 	add.s	$f10,$f0,$f16
/*  f02a194:	3c0142f0 */ 	lui	$at,0x42f0
/*  f02a198:	44813000 */ 	mtc1	$at,$f6
/*  f02a19c:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f02a1a0:	46045302 */ 	mul.s	$f12,$f10,$f4
/*  f02a1a4:	3c014248 */ 	lui	$at,0x4248
/*  f02a1a8:	44818000 */ 	mtc1	$at,$f16
/*  f02a1ac:	30ee00ff */ 	andi	$t6,$a3,0xff
/*  f02a1b0:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02a1b4:	448e5000 */ 	mtc1	$t6,$f10
/*  f02a1b8:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f02a1bc:	460c3482 */ 	mul.s	$f18,$f6,$f12
/*  f02a1c0:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f02a1c4:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f02a1c8:	460c8082 */ 	mul.s	$f2,$f16,$f12
/*  f02a1cc:	3c014f80 */ 	lui	$at,0x4f80
/*  f02a1d0:	4600920d */ 	trunc.w.s	$f8,$f18
/*  f02a1d4:	46805120 */ 	cvt.s.w	$f4,$f10
/*  f02a1d8:	440f4000 */ 	mfc1	$t7,$f8
/*  f02a1dc:	00000000 */ 	nop
/*  f02a1e0:	25f80032 */ 	addiu	$t8,$t7,0x32
/*  f02a1e4:	05c10004 */ 	bgez	$t6,.L0f02a1f8
/*  f02a1e8:	a0780003 */ 	sb	$t8,0x3($v1)
/*  f02a1ec:	44813000 */ 	mtc1	$at,$f6
/*  f02a1f0:	00000000 */ 	nop
/*  f02a1f4:	46062100 */ 	add.s	$f4,$f4,$f6
.L0f02a1f8:
/*  f02a1f8:	46022480 */ 	add.s	$f18,$f4,$f2
/*  f02a1fc:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f02a200:	3c014f00 */ 	lui	$at,0x4f00
/*  f02a204:	315800ff */ 	andi	$t8,$t2,0xff
/*  f02a208:	4459f800 */ 	cfc1	$t9,$31
/*  f02a20c:	44cff800 */ 	ctc1	$t7,$31
/*  f02a210:	00000000 */ 	nop
/*  f02a214:	46009224 */ 	cvt.w.s	$f8,$f18
/*  f02a218:	444ff800 */ 	cfc1	$t7,$31
/*  f02a21c:	00000000 */ 	nop
/*  f02a220:	31ef0078 */ 	andi	$t7,$t7,0x78
/*  f02a224:	51e00013 */ 	beqzl	$t7,.L0f02a274
/*  f02a228:	440f4000 */ 	mfc1	$t7,$f8
/*  f02a22c:	44814000 */ 	mtc1	$at,$f8
/*  f02a230:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f02a234:	46089201 */ 	sub.s	$f8,$f18,$f8
/*  f02a238:	44cff800 */ 	ctc1	$t7,$31
/*  f02a23c:	00000000 */ 	nop
/*  f02a240:	46004224 */ 	cvt.w.s	$f8,$f8
/*  f02a244:	444ff800 */ 	cfc1	$t7,$31
/*  f02a248:	00000000 */ 	nop
/*  f02a24c:	31ef0078 */ 	andi	$t7,$t7,0x78
/*  f02a250:	15e00005 */ 	bnez	$t7,.L0f02a268
/*  f02a254:	00000000 */ 	nop
/*  f02a258:	440f4000 */ 	mfc1	$t7,$f8
/*  f02a25c:	3c018000 */ 	lui	$at,0x8000
/*  f02a260:	10000007 */ 	b	.L0f02a280
/*  f02a264:	01e17825 */ 	or	$t7,$t7,$at
.L0f02a268:
/*  f02a268:	10000005 */ 	b	.L0f02a280
/*  f02a26c:	240fffff */ 	addiu	$t7,$zero,-1
/*  f02a270:	440f4000 */ 	mfc1	$t7,$f8
.L0f02a274:
/*  f02a274:	00000000 */ 	nop
/*  f02a278:	05e0fffb */ 	bltz	$t7,.L0f02a268
/*  f02a27c:	00000000 */ 	nop
.L0f02a280:
/*  f02a280:	44d9f800 */ 	ctc1	$t9,$31
/*  f02a284:	44988000 */ 	mtc1	$t8,$f16
/*  f02a288:	a06f0000 */ 	sb	$t7,0x0($v1)
/*  f02a28c:	07010005 */ 	bgez	$t8,.L0f02a2a4
/*  f02a290:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f02a294:	3c014f80 */ 	lui	$at,0x4f80
/*  f02a298:	44813000 */ 	mtc1	$at,$f6
/*  f02a29c:	00000000 */ 	nop
/*  f02a2a0:	46065280 */ 	add.s	$f10,$f10,$f6
.L0f02a2a4:
/*  f02a2a4:	46025100 */ 	add.s	$f4,$f10,$f2
/*  f02a2a8:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f02a2ac:	3c014f00 */ 	lui	$at,0x4f00
/*  f02a2b0:	316f00ff */ 	andi	$t7,$t3,0xff
/*  f02a2b4:	444ef800 */ 	cfc1	$t6,$31
/*  f02a2b8:	44d9f800 */ 	ctc1	$t9,$31
/*  f02a2bc:	00000000 */ 	nop
/*  f02a2c0:	460024a4 */ 	cvt.w.s	$f18,$f4
/*  f02a2c4:	4459f800 */ 	cfc1	$t9,$31
/*  f02a2c8:	00000000 */ 	nop
/*  f02a2cc:	33390078 */ 	andi	$t9,$t9,0x78
/*  f02a2d0:	53200013 */ 	beqzl	$t9,.L0f02a320
/*  f02a2d4:	44199000 */ 	mfc1	$t9,$f18
/*  f02a2d8:	44819000 */ 	mtc1	$at,$f18
/*  f02a2dc:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f02a2e0:	46122481 */ 	sub.s	$f18,$f4,$f18
/*  f02a2e4:	44d9f800 */ 	ctc1	$t9,$31
/*  f02a2e8:	00000000 */ 	nop
/*  f02a2ec:	460094a4 */ 	cvt.w.s	$f18,$f18
/*  f02a2f0:	4459f800 */ 	cfc1	$t9,$31
/*  f02a2f4:	00000000 */ 	nop
/*  f02a2f8:	33390078 */ 	andi	$t9,$t9,0x78
/*  f02a2fc:	17200005 */ 	bnez	$t9,.L0f02a314
/*  f02a300:	00000000 */ 	nop
/*  f02a304:	44199000 */ 	mfc1	$t9,$f18
/*  f02a308:	3c018000 */ 	lui	$at,0x8000
/*  f02a30c:	10000007 */ 	b	.L0f02a32c
/*  f02a310:	0321c825 */ 	or	$t9,$t9,$at
.L0f02a314:
/*  f02a314:	10000005 */ 	b	.L0f02a32c
/*  f02a318:	2419ffff */ 	addiu	$t9,$zero,-1
/*  f02a31c:	44199000 */ 	mfc1	$t9,$f18
.L0f02a320:
/*  f02a320:	00000000 */ 	nop
/*  f02a324:	0720fffb */ 	bltz	$t9,.L0f02a314
/*  f02a328:	00000000 */ 	nop
.L0f02a32c:
/*  f02a32c:	44cef800 */ 	ctc1	$t6,$31
/*  f02a330:	448f4000 */ 	mtc1	$t7,$f8
/*  f02a334:	a0790001 */ 	sb	$t9,0x1($v1)
/*  f02a338:	05e10005 */ 	bgez	$t7,.L0f02a350
/*  f02a33c:	46804420 */ 	cvt.s.w	$f16,$f8
/*  f02a340:	3c014f80 */ 	lui	$at,0x4f80
/*  f02a344:	44813000 */ 	mtc1	$at,$f6
/*  f02a348:	00000000 */ 	nop
/*  f02a34c:	46068400 */ 	add.s	$f16,$f16,$f6
.L0f02a350:
/*  f02a350:	46028280 */ 	add.s	$f10,$f16,$f2
/*  f02a354:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f02a358:	3c014f00 */ 	lui	$at,0x4f00
/*  f02a35c:	4458f800 */ 	cfc1	$t8,$31
/*  f02a360:	44cef800 */ 	ctc1	$t6,$31
/*  f02a364:	00000000 */ 	nop
/*  f02a368:	46005124 */ 	cvt.w.s	$f4,$f10
/*  f02a36c:	444ef800 */ 	cfc1	$t6,$31
/*  f02a370:	00000000 */ 	nop
/*  f02a374:	31ce0078 */ 	andi	$t6,$t6,0x78
/*  f02a378:	51c00013 */ 	beqzl	$t6,.L0f02a3c8
/*  f02a37c:	440e2000 */ 	mfc1	$t6,$f4
/*  f02a380:	44812000 */ 	mtc1	$at,$f4
/*  f02a384:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f02a388:	46045101 */ 	sub.s	$f4,$f10,$f4
/*  f02a38c:	44cef800 */ 	ctc1	$t6,$31
/*  f02a390:	00000000 */ 	nop
/*  f02a394:	46002124 */ 	cvt.w.s	$f4,$f4
/*  f02a398:	444ef800 */ 	cfc1	$t6,$31
/*  f02a39c:	00000000 */ 	nop
/*  f02a3a0:	31ce0078 */ 	andi	$t6,$t6,0x78
/*  f02a3a4:	15c00005 */ 	bnez	$t6,.L0f02a3bc
/*  f02a3a8:	00000000 */ 	nop
/*  f02a3ac:	440e2000 */ 	mfc1	$t6,$f4
/*  f02a3b0:	3c018000 */ 	lui	$at,0x8000
/*  f02a3b4:	10000007 */ 	b	.L0f02a3d4
/*  f02a3b8:	01c17025 */ 	or	$t6,$t6,$at
.L0f02a3bc:
/*  f02a3bc:	10000005 */ 	b	.L0f02a3d4
/*  f02a3c0:	240effff */ 	addiu	$t6,$zero,-1
/*  f02a3c4:	440e2000 */ 	mfc1	$t6,$f4
.L0f02a3c8:
/*  f02a3c8:	00000000 */ 	nop
/*  f02a3cc:	05c0fffb */ 	bltz	$t6,.L0f02a3bc
/*  f02a3d0:	00000000 */ 	nop
.L0f02a3d4:
/*  f02a3d4:	44d8f800 */ 	ctc1	$t8,$31
/*  f02a3d8:	10000006 */ 	b	.L0f02a3f4
/*  f02a3dc:	a06e0002 */ 	sb	$t6,0x2($v1)
/*  f02a3e0:	24080200 */ 	addiu	$t0,$zero,0x200
.L0f02a3e4:
/*  f02a3e4:	0000a825 */ 	or	$s5,$zero,$zero
/*  f02a3e8:	00009825 */ 	or	$s3,$zero,$zero
/*  f02a3ec:	a7a80176 */ 	sh	$t0,0x176($sp)
/*  f02a3f0:	24140200 */ 	addiu	$s4,$zero,0x200
.L0f02a3f4:
/*  f02a3f4:	27a60104 */ 	addiu	$a2,$sp,0x104
/*  f02a3f8:	27a50180 */ 	addiu	$a1,$sp,0x180
.L0f02a3fc:
/*  f02a3fc:	87a80176 */ 	lh	$t0,0x176($sp)
/*  f02a400:	00002025 */ 	or	$a0,$zero,$zero
/*  f02a404:	02001825 */ 	or	$v1,$s0,$zero
/*  f02a408:	00c01025 */ 	or	$v0,$a2,$zero
.L0f02a40c:
/*  f02a40c:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02a410:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f02a414:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f02a418:	a861fff4 */ 	swl	$at,-0xc($v1)
/*  f02a41c:	b861fff7 */ 	swr	$at,-0x9($v1)
/*  f02a420:	8e580004 */ 	lw	$t8,0x4($s2)
/*  f02a424:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f02a428:	a878fff8 */ 	swl	$t8,-0x8($v1)
/*  f02a42c:	b878fffb */ 	swr	$t8,-0x5($v1)
/*  f02a430:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02a434:	a861fffc */ 	swl	$at,-0x4($v1)
/*  f02a438:	b861ffff */ 	swr	$at,-0x1($v1)
/*  f02a43c:	8c4efffc */ 	lw	$t6,-0x4($v0)
/*  f02a440:	01d10019 */ 	multu	$t6,$s1
/*  f02a444:	00007812 */ 	mflo	$t7
/*  f02a448:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02a44c:	87380000 */ 	lh	$t8,0x0($t9)
/*  f02a450:	a478fff4 */ 	sh	$t8,-0xc($v1)
/*  f02a454:	8c4efffc */ 	lw	$t6,-0x4($v0)
/*  f02a458:	01d10019 */ 	multu	$t6,$s1
/*  f02a45c:	00007812 */ 	mflo	$t7
/*  f02a460:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02a464:	87380002 */ 	lh	$t8,0x2($t9)
/*  f02a468:	a478fff6 */ 	sh	$t8,-0xa($v1)
/*  f02a46c:	8c4efffc */ 	lw	$t6,-0x4($v0)
/*  f02a470:	01d10019 */ 	multu	$t6,$s1
/*  f02a474:	00007812 */ 	mflo	$t7
/*  f02a478:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02a47c:	87380004 */ 	lh	$t8,0x4($t9)
/*  f02a480:	a060fffb */ 	sb	$zero,-0x5($v1)
/*  f02a484:	1489ffe1 */ 	bne	$a0,$t1,.L0f02a40c
/*  f02a488:	a478fff8 */ 	sh	$t8,-0x8($v1)
/*  f02a48c:	a6150008 */ 	sh	$s5,0x8($s0)
/*  f02a490:	a613000a */ 	sh	$s3,0xa($s0)
/*  f02a494:	a6080014 */ 	sh	$t0,0x14($s0)
/*  f02a498:	a6130016 */ 	sh	$s3,0x16($s0)
/*  f02a49c:	a6080020 */ 	sh	$t0,0x20($s0)
/*  f02a4a0:	a6140022 */ 	sh	$s4,0x22($s0)
/*  f02a4a4:	a615002c */ 	sh	$s5,0x2c($s0)
/*  f02a4a8:	a614002e */ 	sh	$s4,0x2e($s0)
/*  f02a4ac:	8fae01f0 */ 	lw	$t6,0x1f0($sp)
/*  f02a4b0:	3c190430 */ 	lui	$t9,0x430
/*  f02a4b4:	37390030 */ 	ori	$t9,$t9,0x30
/*  f02a4b8:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f02a4bc:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02a4c0:	add90000 */ 	sw	$t9,0x0($t6)
/*  f02a4c4:	a7a80176 */ 	sh	$t0,0x176($sp)
/*  f02a4c8:	afa60054 */ 	sw	$a2,0x54($sp)
/*  f02a4cc:	02002025 */ 	or	$a0,$s0,$zero
/*  f02a4d0:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f02a4d4:	afae00b4 */ 	sw	$t6,0xb4($sp)
/*  f02a4d8:	8fa700b4 */ 	lw	$a3,0xb4($sp)
/*  f02a4dc:	8fa60054 */ 	lw	$a2,0x54($sp)
/*  f02a4e0:	3c0fb100 */ 	lui	$t7,0xb100
/*  f02a4e4:	ace20004 */ 	sw	$v0,0x4($a3)
/*  f02a4e8:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f02a4ec:	35ef0032 */ 	ori	$t7,$t7,0x32
/*  f02a4f0:	24192010 */ 	addiu	$t9,$zero,0x2010
/*  f02a4f4:	270e0008 */ 	addiu	$t6,$t8,0x8
/*  f02a4f8:	afae01f0 */ 	sw	$t6,0x1f0($sp)
/*  f02a4fc:	af190004 */ 	sw	$t9,0x4($t8)
/*  f02a500:	af0f0000 */ 	sw	$t7,0x0($t8)
/*  f02a504:	27b80164 */ 	addiu	$t8,$sp,0x164
/*  f02a508:	24c60010 */ 	addiu	$a2,$a2,0x10
/*  f02a50c:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f02a510:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f02a514:	14d8ffb9 */ 	bne	$a2,$t8,.L0f02a3fc
/*  f02a518:	26100030 */ 	addiu	$s0,$s0,0x30
/*  f02a51c:	100004a4 */ 	b	.L0f02b7b0
/*  f02a520:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f02a524:	2401fffe */ 	addiu	$at,$zero,-2
.L0f02a528:
/*  f02a528:	150100d5 */ 	bne	$t0,$at,.L0f02a880
/*  f02a52c:	8fae01f4 */ 	lw	$t6,0x1f4($sp)
/*  f02a530:	8fa3020c */ 	lw	$v1,0x20c($sp)
/*  f02a534:	81c20011 */ 	lb	$v0,0x11($t6)
/*  f02a538:	8faf0208 */ 	lw	$t7,0x208($sp)
/*  f02a53c:	24040003 */ 	addiu	$a0,$zero,0x3
/*  f02a540:	0043082a */ 	slt	$at,$v0,$v1
/*  f02a544:	50200005 */ 	beqzl	$at,.L0f02a55c
/*  f02a548:	448f3000 */ 	mtc1	$t7,$f6
/*  f02a54c:	44806000 */ 	mtc1	$zero,$f12
/*  f02a550:	1000001f */ 	b	.L0f02a5d0
/*  f02a554:	46006086 */ 	mov.s	$f2,$f12
/*  f02a558:	448f3000 */ 	mtc1	$t7,$f6
.L0f02a55c:
/*  f02a55c:	3c0141f0 */ 	lui	$at,0x41f0
/*  f02a560:	44814000 */ 	mtc1	$at,$f8
/*  f02a564:	46803420 */ 	cvt.s.w	$f16,$f6
/*  f02a568:	44829000 */ 	mtc1	$v0,$f18
/*  f02a56c:	3c017f1b */ 	lui	$at,%hi(var7f1a8970)
/*  f02a570:	c4248970 */ 	lwc1	$f4,%lo(var7f1a8970)($at)
/*  f02a574:	3c014220 */ 	lui	$at,0x4220
/*  f02a578:	46809020 */ 	cvt.s.w	$f0,$f18
/*  f02a57c:	44813000 */ 	mtc1	$at,$f6
/*  f02a580:	8fb90210 */ 	lw	$t9,0x210($sp)
/*  f02a584:	3c017f1b */ 	lui	$at,%hi(var7f1a8974)
/*  f02a588:	46104281 */ 	sub.s	$f10,$f8,$f16
/*  f02a58c:	44838000 */ 	mtc1	$v1,$f16
/*  f02a590:	46045482 */ 	mul.s	$f18,$f10,$f4
/*  f02a594:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f02a598:	44998000 */ 	mtc1	$t9,$f16
/*  f02a59c:	46069200 */ 	add.s	$f8,$f18,$f6
/*  f02a5a0:	460a0101 */ 	sub.s	$f4,$f0,$f10
/*  f02a5a4:	468082a0 */ 	cvt.s.w	$f10,$f16
/*  f02a5a8:	460c2480 */ 	add.s	$f18,$f4,$f12
/*  f02a5ac:	c4248974 */ 	lwc1	$f4,%lo(var7f1a8974)($at)
/*  f02a5b0:	44806000 */ 	mtc1	$zero,$f12
/*  f02a5b4:	46009183 */ 	div.s	$f6,$f18,$f0
/*  f02a5b8:	46064082 */ 	mul.s	$f2,$f8,$f6
/*  f02a5bc:	00000000 */ 	nop
/*  f02a5c0:	46045482 */ 	mul.s	$f18,$f10,$f4
/*  f02a5c4:	00000000 */ 	nop
/*  f02a5c8:	46121082 */ 	mul.s	$f2,$f2,$f18
/*  f02a5cc:	00000000 */ 	nop
.L0f02a5d0:
/*  f02a5d0:	3c01437f */ 	lui	$at,0x437f
/*  f02a5d4:	44810000 */ 	mtc1	$at,$f0
/*  f02a5d8:	00000000 */ 	nop
/*  f02a5dc:	4602003c */ 	c.lt.s	$f0,$f2
/*  f02a5e0:	00000000 */ 	nop
/*  f02a5e4:	45020004 */ 	bc1fl	.L0f02a5f8
/*  f02a5e8:	460c103c */ 	c.lt.s	$f2,$f12
/*  f02a5ec:	10000006 */ 	b	.L0f02a608
/*  f02a5f0:	46000086 */ 	mov.s	$f2,$f0
/*  f02a5f4:	460c103c */ 	c.lt.s	$f2,$f12
.L0f02a5f8:
/*  f02a5f8:	00000000 */ 	nop
/*  f02a5fc:	45000002 */ 	bc1f	.L0f02a608
/*  f02a600:	00000000 */ 	nop
/*  f02a604:	46006086 */ 	mov.s	$f2,$f12
.L0f02a608:
/*  f02a608:	0fc59e73 */ 	jal	gfxAllocateColours
/*  f02a60c:	e7a200ac */ 	swc1	$f2,0xac($sp)
/*  f02a610:	8fb001f0 */ 	lw	$s0,0x1f0($sp)
/*  f02a614:	3c0f0708 */ 	lui	$t7,0x708
/*  f02a618:	35ef000c */ 	ori	$t7,$t7,0xc
/*  f02a61c:	260e0008 */ 	addiu	$t6,$s0,0x8
/*  f02a620:	afae01f0 */ 	sw	$t6,0x1f0($sp)
/*  f02a624:	ae0f0000 */ 	sw	$t7,0x0($s0)
/*  f02a628:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f02a62c:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f02a630:	00402025 */ 	or	$a0,$v0,$zero
/*  f02a634:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02a638:	c7a200ac */ 	lwc1	$f2,0xac($sp)
/*  f02a63c:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f02a640:	8fa600e4 */ 	lw	$a2,0xe4($sp)
/*  f02a644:	8fa700e0 */ 	lw	$a3,0xe0($sp)
/*  f02a648:	ae020004 */ 	sw	$v0,0x4($s0)
/*  f02a64c:	4600120d */ 	trunc.w.s	$f8,$f2
/*  f02a650:	2404001e */ 	addiu	$a0,$zero,0x1e
/*  f02a654:	a0600007 */ 	sb	$zero,0x7($v1)
/*  f02a658:	a0650000 */ 	sb	$a1,0x0($v1)
/*  f02a65c:	44184000 */ 	mfc1	$t8,$f8
/*  f02a660:	a0650004 */ 	sb	$a1,0x4($v1)
/*  f02a664:	a0660001 */ 	sb	$a2,0x1($v1)
/*  f02a668:	a0660005 */ 	sb	$a2,0x5($v1)
/*  f02a66c:	a0670002 */ 	sb	$a3,0x2($v1)
/*  f02a670:	a0670006 */ 	sb	$a3,0x6($v1)
/*  f02a674:	0fc59e59 */ 	jal	gfxAllocateVertices
/*  f02a678:	a0780003 */ 	sb	$t8,0x3($v1)
/*  f02a67c:	87ab0052 */ 	lh	$t3,0x52($sp)
/*  f02a680:	02747021 */ 	addu	$t6,$s3,$s4
/*  f02a684:	000e7843 */ 	sra	$t7,$t6,0x1
/*  f02a688:	02abc821 */ 	addu	$t9,$s5,$t3
/*  f02a68c:	0019c043 */ 	sra	$t8,$t9,0x1
/*  f02a690:	00408025 */ 	or	$s0,$v0,$zero
/*  f02a694:	afb80040 */ 	sw	$t8,0x40($sp)
/*  f02a698:	afaf004c */ 	sw	$t7,0x4c($sp)
/*  f02a69c:	27a60104 */ 	addiu	$a2,$sp,0x104
/*  f02a6a0:	240c0004 */ 	addiu	$t4,$zero,0x4
/*  f02a6a4:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f02a6a8:	27a50180 */ 	addiu	$a1,$sp,0x180
.L0f02a6ac:
/*  f02a6ac:	00002025 */ 	or	$a0,$zero,$zero
/*  f02a6b0:	02001825 */ 	or	$v1,$s0,$zero
/*  f02a6b4:	00c01025 */ 	or	$v0,$a2,$zero
.L0f02a6b8:
/*  f02a6b8:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02a6bc:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f02a6c0:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f02a6c4:	a861fff4 */ 	swl	$at,-0xc($v1)
/*  f02a6c8:	b861fff7 */ 	swr	$at,-0x9($v1)
/*  f02a6cc:	8e590004 */ 	lw	$t9,0x4($s2)
/*  f02a6d0:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f02a6d4:	a879fff8 */ 	swl	$t9,-0x8($v1)
/*  f02a6d8:	b879fffb */ 	swr	$t9,-0x5($v1)
/*  f02a6dc:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02a6e0:	a861fffc */ 	swl	$at,-0x4($v1)
/*  f02a6e4:	b861ffff */ 	swr	$at,-0x1($v1)
/*  f02a6e8:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f02a6ec:	03110019 */ 	multu	$t8,$s1
/*  f02a6f0:	00007812 */ 	mflo	$t7
/*  f02a6f4:	00af7021 */ 	addu	$t6,$a1,$t7
/*  f02a6f8:	85d90000 */ 	lh	$t9,0x0($t6)
/*  f02a6fc:	a479fff4 */ 	sh	$t9,-0xc($v1)
/*  f02a700:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f02a704:	03110019 */ 	multu	$t8,$s1
/*  f02a708:	00007812 */ 	mflo	$t7
/*  f02a70c:	00af7021 */ 	addu	$t6,$a1,$t7
/*  f02a710:	85d90002 */ 	lh	$t9,0x2($t6)
/*  f02a714:	a479fff6 */ 	sh	$t9,-0xa($v1)
/*  f02a718:	8c58fffc */ 	lw	$t8,-0x4($v0)
/*  f02a71c:	03110019 */ 	multu	$t8,$s1
/*  f02a720:	00007812 */ 	mflo	$t7
/*  f02a724:	00af7021 */ 	addu	$t6,$a1,$t7
/*  f02a728:	85d90004 */ 	lh	$t9,0x4($t6)
/*  f02a72c:	a060fffb */ 	sb	$zero,-0x5($v1)
/*  f02a730:	1489ffe1 */ 	bne	$a0,$t1,.L0f02a6b8
/*  f02a734:	a479fff8 */ 	sh	$t9,-0x8($v1)
/*  f02a738:	a6150008 */ 	sh	$s5,0x8($s0)
/*  f02a73c:	a613000a */ 	sh	$s3,0xa($s0)
/*  f02a740:	a60b0014 */ 	sh	$t3,0x14($s0)
/*  f02a744:	a6130016 */ 	sh	$s3,0x16($s0)
/*  f02a748:	a60b0020 */ 	sh	$t3,0x20($s0)
/*  f02a74c:	a6140022 */ 	sh	$s4,0x22($s0)
/*  f02a750:	a615002c */ 	sh	$s5,0x2c($s0)
/*  f02a754:	a614002e */ 	sh	$s4,0x2e($s0)
/*  f02a758:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02a75c:	860e0024 */ 	lh	$t6,0x24($s0)
/*  f02a760:	86190000 */ 	lh	$t9,0x0($s0)
/*  f02a764:	aa010030 */ 	swl	$at,0x30($s0)
/*  f02a768:	ba010033 */ 	swr	$at,0x33($s0)
/*  f02a76c:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02a770:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a774:	86190018 */ 	lh	$t9,0x18($s0)
/*  f02a778:	aa0f0034 */ 	swl	$t7,0x34($s0)
/*  f02a77c:	ba0f0037 */ 	swr	$t7,0x37($s0)
/*  f02a780:	860f000c */ 	lh	$t7,0xc($s0)
/*  f02a784:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02a788:	02002025 */ 	or	$a0,$s0,$zero
/*  f02a78c:	030f7021 */ 	addu	$t6,$t8,$t7
/*  f02a790:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a794:	86190002 */ 	lh	$t9,0x2($s0)
/*  f02a798:	860e0026 */ 	lh	$t6,0x26($s0)
/*  f02a79c:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02a7a0:	a60f0030 */ 	sh	$t7,0x30($s0)
/*  f02a7a4:	860f000e */ 	lh	$t7,0xe($s0)
/*  f02a7a8:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a7ac:	8619001a */ 	lh	$t9,0x1a($s0)
/*  f02a7b0:	030f7021 */ 	addu	$t6,$t8,$t7
/*  f02a7b4:	aa010038 */ 	swl	$at,0x38($s0)
/*  f02a7b8:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a7bc:	86190004 */ 	lh	$t9,0x4($s0)
/*  f02a7c0:	860e0028 */ 	lh	$t6,0x28($s0)
/*  f02a7c4:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02a7c8:	a60f0032 */ 	sh	$t7,0x32($s0)
/*  f02a7cc:	860f0010 */ 	lh	$t7,0x10($s0)
/*  f02a7d0:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a7d4:	8619001c */ 	lh	$t9,0x1c($s0)
/*  f02a7d8:	030f7021 */ 	addu	$t6,$t8,$t7
/*  f02a7dc:	ba01003b */ 	swr	$at,0x3b($s0)
/*  f02a7e0:	01d9c021 */ 	addu	$t8,$t6,$t9
/*  f02a7e4:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02a7e8:	a60f0034 */ 	sh	$t7,0x34($s0)
/*  f02a7ec:	8fae0040 */ 	lw	$t6,0x40($sp)
/*  f02a7f0:	a60e0038 */ 	sh	$t6,0x38($s0)
/*  f02a7f4:	8fb9004c */ 	lw	$t9,0x4c($sp)
/*  f02a7f8:	a20c0037 */ 	sb	$t4,0x37($s0)
/*  f02a7fc:	3c0e0440 */ 	lui	$t6,0x440
/*  f02a800:	a619003a */ 	sh	$t9,0x3a($s0)
/*  f02a804:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f02a808:	35ce003c */ 	ori	$t6,$t6,0x3c
/*  f02a80c:	270f0008 */ 	addiu	$t7,$t8,0x8
/*  f02a810:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02a814:	af0e0000 */ 	sw	$t6,0x0($t8)
/*  f02a818:	afab0044 */ 	sw	$t3,0x44($sp)
/*  f02a81c:	afa60054 */ 	sw	$a2,0x54($sp)
/*  f02a820:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f02a824:	afb800a4 */ 	sw	$t8,0xa4($sp)
/*  f02a828:	8fa700a4 */ 	lw	$a3,0xa4($sp)
/*  f02a82c:	8fa60054 */ 	lw	$a2,0x54($sp)
/*  f02a830:	8fab0044 */ 	lw	$t3,0x44($sp)
/*  f02a834:	ace20004 */ 	sw	$v0,0x4($a3)
/*  f02a838:	8fb901f0 */ 	lw	$t9,0x1f0($sp)
/*  f02a83c:	3c0fb100 */ 	lui	$t7,0xb100
/*  f02a840:	3c0e0332 */ 	lui	$t6,0x332
/*  f02a844:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f02a848:	afb801f0 */ 	sw	$t8,0x1f0($sp)
/*  f02a84c:	35ce2110 */ 	ori	$t6,$t6,0x2110
/*  f02a850:	35ef4444 */ 	ori	$t7,$t7,0x4444
/*  f02a854:	af2f0000 */ 	sw	$t7,0x0($t9)
/*  f02a858:	af2e0004 */ 	sw	$t6,0x4($t9)
/*  f02a85c:	27b90164 */ 	addiu	$t9,$sp,0x164
/*  f02a860:	24c60010 */ 	addiu	$a2,$a2,0x10
/*  f02a864:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f02a868:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f02a86c:	240c0004 */ 	addiu	$t4,$zero,0x4
/*  f02a870:	14d9ff8e */ 	bne	$a2,$t9,.L0f02a6ac
/*  f02a874:	2610003c */ 	addiu	$s0,$s0,0x3c
/*  f02a878:	100003cd */ 	b	.L0f02b7b0
/*  f02a87c:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f02a880:
/*  f02a880:	05010130 */ 	bgez	$t0,.L0f02ad44
/*  f02a884:	8fae01f8 */ 	lw	$t6,0x1f8($sp)
/*  f02a888:	0fc59e59 */ 	jal	gfxAllocateVertices
/*  f02a88c:	2404000c */ 	addiu	$a0,$zero,0xc
/*  f02a890:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f02a894:	2401ffff */ 	addiu	$at,$zero,-1
/*  f02a898:	00408025 */ 	or	$s0,$v0,$zero
/*  f02a89c:	15010035 */ 	bne	$t0,$at,.L0f02a974
/*  f02a8a0:	8fb801f4 */ 	lw	$t8,0x1f4($sp)
/*  f02a8a4:	3c02800a */ 	lui	$v0,%hi(g_Vars+0x8)
/*  f02a8a8:	8c429fc8 */ 	lw	$v0,%lo(g_Vars+0x8)($v0)
/*  f02a8ac:	8f03000c */ 	lw	$v1,0xc($t8)
/*  f02a8b0:	00002825 */ 	or	$a1,$zero,$zero
/*  f02a8b4:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f02a8b8:	00437823 */ 	subu	$t7,$v0,$v1
/*  f02a8bc:	29e10051 */ 	slti	$at,$t7,0x51
/*  f02a8c0:	10200016 */ 	beqz	$at,.L0f02a91c
/*  f02a8c4:	00627023 */ 	subu	$t6,$v1,$v0
/*  f02a8c8:	25d90050 */ 	addiu	$t9,$t6,0x50
/*  f02a8cc:	44993000 */ 	mtc1	$t9,$f6
/*  f02a8d0:	8fb80210 */ 	lw	$t8,0x210($sp)
/*  f02a8d4:	3c01404c */ 	lui	$at,0x404c
/*  f02a8d8:	46803420 */ 	cvt.s.w	$f16,$f6
/*  f02a8dc:	44982000 */ 	mtc1	$t8,$f4
/*  f02a8e0:	44815000 */ 	mtc1	$at,$f10
/*  f02a8e4:	3c017f1b */ 	lui	$at,%hi(var7f1a8978)
/*  f02a8e8:	c4288978 */ 	lwc1	$f8,%lo(var7f1a8978)($at)
/*  f02a8ec:	468024a0 */ 	cvt.s.w	$f18,$f4
/*  f02a8f0:	460a8002 */ 	mul.s	$f0,$f16,$f10
/*  f02a8f4:	00000000 */ 	nop
/*  f02a8f8:	46089182 */ 	mul.s	$f6,$f18,$f8
/*  f02a8fc:	00000000 */ 	nop
/*  f02a900:	46060002 */ 	mul.s	$f0,$f0,$f6
/*  f02a904:	4600040d */ 	trunc.w.s	$f16,$f0
/*  f02a908:	44058000 */ 	mfc1	$a1,$f16
/*  f02a90c:	00000000 */ 	nop
/*  f02a910:	30ae00ff */ 	andi	$t6,$a1,0xff
/*  f02a914:	10000001 */ 	b	.L0f02a91c
/*  f02a918:	01c02825 */ 	or	$a1,$t6,$zero
.L0f02a91c:
/*  f02a91c:	0fc59e73 */ 	jal	gfxAllocateColours
/*  f02a920:	a3a5017f */ 	sb	$a1,0x17f($sp)
/*  f02a924:	8fb101f0 */ 	lw	$s1,0x1f0($sp)
/*  f02a928:	3c0f0700 */ 	lui	$t7,0x700
/*  f02a92c:	35ef0004 */ 	ori	$t7,$t7,0x4
/*  f02a930:	26380008 */ 	addiu	$t8,$s1,0x8
/*  f02a934:	afb801f0 */ 	sw	$t8,0x1f0($sp)
/*  f02a938:	ae2f0000 */ 	sw	$t7,0x0($s1)
/*  f02a93c:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f02a940:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f02a944:	00402025 */ 	or	$a0,$v0,$zero
/*  f02a948:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02a94c:	93a5017f */ 	lbu	$a1,0x17f($sp)
/*  f02a950:	ae220004 */ 	sw	$v0,0x4($s1)
/*  f02a954:	8fae0100 */ 	lw	$t6,0x100($sp)
/*  f02a958:	a06e0000 */ 	sb	$t6,0x0($v1)
/*  f02a95c:	8fb900fc */ 	lw	$t9,0xfc($sp)
/*  f02a960:	a0790001 */ 	sb	$t9,0x1($v1)
/*  f02a964:	8fb800f8 */ 	lw	$t8,0xf8($sp)
/*  f02a968:	a0650003 */ 	sb	$a1,0x3($v1)
/*  f02a96c:	10000053 */ 	b	.L0f02aabc
/*  f02a970:	a0780002 */ 	sb	$t8,0x2($v1)
.L0f02a974:
/*  f02a974:	2401fffe */ 	addiu	$at,$zero,-2
/*  f02a978:	15010050 */ 	bne	$t0,$at,.L0f02aabc
/*  f02a97c:	8faf01f4 */ 	lw	$t7,0x1f4($sp)
/*  f02a980:	8fa3020c */ 	lw	$v1,0x20c($sp)
/*  f02a984:	81e20011 */ 	lb	$v0,0x11($t7)
/*  f02a988:	8fae0208 */ 	lw	$t6,0x208($sp)
/*  f02a98c:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f02a990:	0043082a */ 	slt	$at,$v0,$v1
/*  f02a994:	50200005 */ 	beqzl	$at,.L0f02a9ac
/*  f02a998:	448e9000 */ 	mtc1	$t6,$f18
/*  f02a99c:	44806000 */ 	mtc1	$zero,$f12
/*  f02a9a0:	10000021 */ 	b	.L0f02aa28
/*  f02a9a4:	46006086 */ 	mov.s	$f2,$f12
/*  f02a9a8:	448e9000 */ 	mtc1	$t6,$f18
.L0f02a9ac:
/*  f02a9ac:	3c0141f0 */ 	lui	$at,0x41f0
/*  f02a9b0:	44812000 */ 	mtc1	$at,$f4
/*  f02a9b4:	46809220 */ 	cvt.s.w	$f8,$f18
/*  f02a9b8:	44825000 */ 	mtc1	$v0,$f10
/*  f02a9bc:	3c014080 */ 	lui	$at,0x4080
/*  f02a9c0:	44818000 */ 	mtc1	$at,$f16
/*  f02a9c4:	3c014220 */ 	lui	$at,0x4220
/*  f02a9c8:	46805020 */ 	cvt.s.w	$f0,$f10
/*  f02a9cc:	44819000 */ 	mtc1	$at,$f18
/*  f02a9d0:	3c013f80 */ 	lui	$at,0x3f80
/*  f02a9d4:	8fb90210 */ 	lw	$t9,0x210($sp)
/*  f02a9d8:	44806000 */ 	mtc1	$zero,$f12
/*  f02a9dc:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f02a9e0:	44834000 */ 	mtc1	$v1,$f8
/*  f02a9e4:	46103282 */ 	mul.s	$f10,$f6,$f16
/*  f02a9e8:	468041a0 */ 	cvt.s.w	$f6,$f8
/*  f02a9ec:	46125100 */ 	add.s	$f4,$f10,$f18
/*  f02a9f0:	44815000 */ 	mtc1	$at,$f10
/*  f02a9f4:	3c017f1b */ 	lui	$at,%hi(var7f1a897c)
/*  f02a9f8:	46060401 */ 	sub.s	$f16,$f0,$f6
/*  f02a9fc:	44993000 */ 	mtc1	$t9,$f6
/*  f02aa00:	460a8480 */ 	add.s	$f18,$f16,$f10
/*  f02aa04:	c42a897c */ 	lwc1	$f10,%lo(var7f1a897c)($at)
/*  f02aa08:	46803420 */ 	cvt.s.w	$f16,$f6
/*  f02aa0c:	46009203 */ 	div.s	$f8,$f18,$f0
/*  f02aa10:	46082082 */ 	mul.s	$f2,$f4,$f8
/*  f02aa14:	00000000 */ 	nop
/*  f02aa18:	460a8482 */ 	mul.s	$f18,$f16,$f10
/*  f02aa1c:	00000000 */ 	nop
/*  f02aa20:	46121082 */ 	mul.s	$f2,$f2,$f18
/*  f02aa24:	00000000 */ 	nop
.L0f02aa28:
/*  f02aa28:	3c01437f */ 	lui	$at,0x437f
/*  f02aa2c:	44810000 */ 	mtc1	$at,$f0
/*  f02aa30:	00000000 */ 	nop
/*  f02aa34:	4602003c */ 	c.lt.s	$f0,$f2
/*  f02aa38:	00000000 */ 	nop
/*  f02aa3c:	45020004 */ 	bc1fl	.L0f02aa50
/*  f02aa40:	460c103c */ 	c.lt.s	$f2,$f12
/*  f02aa44:	10000006 */ 	b	.L0f02aa60
/*  f02aa48:	46000086 */ 	mov.s	$f2,$f0
/*  f02aa4c:	460c103c */ 	c.lt.s	$f2,$f12
.L0f02aa50:
/*  f02aa50:	00000000 */ 	nop
/*  f02aa54:	45000002 */ 	bc1f	.L0f02aa60
/*  f02aa58:	00000000 */ 	nop
/*  f02aa5c:	46006086 */ 	mov.s	$f2,$f12
.L0f02aa60:
/*  f02aa60:	0fc59e73 */ 	jal	gfxAllocateColours
/*  f02aa64:	e7a20094 */ 	swc1	$f2,0x94($sp)
/*  f02aa68:	8fb101f0 */ 	lw	$s1,0x1f0($sp)
/*  f02aa6c:	3c0e0700 */ 	lui	$t6,0x700
/*  f02aa70:	35ce0004 */ 	ori	$t6,$t6,0x4
/*  f02aa74:	262f0008 */ 	addiu	$t7,$s1,0x8
/*  f02aa78:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02aa7c:	ae2e0000 */ 	sw	$t6,0x0($s1)
/*  f02aa80:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f02aa84:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f02aa88:	00402025 */ 	or	$a0,$v0,$zero
/*  f02aa8c:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02aa90:	c7a20094 */ 	lwc1	$f2,0x94($sp)
/*  f02aa94:	ae220004 */ 	sw	$v0,0x4($s1)
/*  f02aa98:	8fb900e8 */ 	lw	$t9,0xe8($sp)
/*  f02aa9c:	4600110d */ 	trunc.w.s	$f4,$f2
/*  f02aaa0:	a0790000 */ 	sb	$t9,0x0($v1)
/*  f02aaa4:	8fb800e4 */ 	lw	$t8,0xe4($sp)
/*  f02aaa8:	44192000 */ 	mfc1	$t9,$f4
/*  f02aaac:	a0780001 */ 	sb	$t8,0x1($v1)
/*  f02aab0:	8faf00e0 */ 	lw	$t7,0xe0($sp)
/*  f02aab4:	a0790003 */ 	sb	$t9,0x3($v1)
/*  f02aab8:	a06f0002 */ 	sb	$t7,0x2($v1)
.L0f02aabc:
/*  f02aabc:	02001825 */ 	or	$v1,$s0,$zero
/*  f02aac0:	27a20180 */ 	addiu	$v0,$sp,0x180
/*  f02aac4:	27a401b0 */ 	addiu	$a0,$sp,0x1b0
.L0f02aac8:
/*  f02aac8:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02aacc:	24420006 */ 	addiu	$v0,$v0,0x6
/*  f02aad0:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f02aad4:	a861fff4 */ 	swl	$at,-0xc($v1)
/*  f02aad8:	b861fff7 */ 	swr	$at,-0x9($v1)
/*  f02aadc:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02aae0:	a86ffff8 */ 	swl	$t7,-0x8($v1)
/*  f02aae4:	b86ffffb */ 	swr	$t7,-0x5($v1)
/*  f02aae8:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02aaec:	a861fffc */ 	swl	$at,-0x4($v1)
/*  f02aaf0:	b861ffff */ 	swr	$at,-0x1($v1)
/*  f02aaf4:	844efffa */ 	lh	$t6,-0x6($v0)
/*  f02aaf8:	0044082b */ 	sltu	$at,$v0,$a0
/*  f02aafc:	a46efff4 */ 	sh	$t6,-0xc($v1)
/*  f02ab00:	8459fffc */ 	lh	$t9,-0x4($v0)
/*  f02ab04:	a479fff6 */ 	sh	$t9,-0xa($v1)
/*  f02ab08:	8458fffe */ 	lh	$t8,-0x2($v0)
/*  f02ab0c:	a060fffb */ 	sb	$zero,-0x5($v1)
/*  f02ab10:	1420ffed */ 	bnez	$at,.L0f02aac8
/*  f02ab14:	a478fff8 */ 	sh	$t8,-0x8($v1)
/*  f02ab18:	a6150008 */ 	sh	$s5,0x8($s0)
/*  f02ab1c:	a613000a */ 	sh	$s3,0xa($s0)
/*  f02ab20:	87ab0052 */ 	lh	$t3,0x52($sp)
/*  f02ab24:	a6130016 */ 	sh	$s3,0x16($s0)
/*  f02ab28:	a6140046 */ 	sh	$s4,0x46($s0)
/*  f02ab2c:	a6150038 */ 	sh	$s5,0x38($s0)
/*  f02ab30:	a614003a */ 	sh	$s4,0x3a($s0)
/*  f02ab34:	a615002c */ 	sh	$s5,0x2c($s0)
/*  f02ab38:	a613002e */ 	sh	$s3,0x2e($s0)
/*  f02ab3c:	a6130022 */ 	sh	$s3,0x22($s0)
/*  f02ab40:	a6140052 */ 	sh	$s4,0x52($s0)
/*  f02ab44:	a615005c */ 	sh	$s5,0x5c($s0)
/*  f02ab48:	a614005e */ 	sh	$s4,0x5e($s0)
/*  f02ab4c:	a60b0014 */ 	sh	$t3,0x14($s0)
/*  f02ab50:	a60b0044 */ 	sh	$t3,0x44($s0)
/*  f02ab54:	a60b0020 */ 	sh	$t3,0x20($s0)
/*  f02ab58:	a60b0050 */ 	sh	$t3,0x50($s0)
/*  f02ab5c:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02ab60:	02002025 */ 	or	$a0,$s0,$zero
/*  f02ab64:	aa010060 */ 	swl	$at,0x60($s0)
/*  f02ab68:	ba010063 */ 	swr	$at,0x63($s0)
/*  f02ab6c:	8e4e0004 */ 	lw	$t6,0x4($s2)
/*  f02ab70:	aa0e0064 */ 	swl	$t6,0x64($s0)
/*  f02ab74:	ba0e0067 */ 	swr	$t6,0x67($s0)
/*  f02ab78:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02ab7c:	aa010068 */ 	swl	$at,0x68($s0)
/*  f02ab80:	ba01006b */ 	swr	$at,0x6b($s0)
/*  f02ab84:	87b9018c */ 	lh	$t9,0x18c($sp)
/*  f02ab88:	a6190060 */ 	sh	$t9,0x60($s0)
/*  f02ab8c:	87b8018e */ 	lh	$t8,0x18e($sp)
/*  f02ab90:	a6180062 */ 	sh	$t8,0x62($s0)
/*  f02ab94:	87af0190 */ 	lh	$t7,0x190($sp)
/*  f02ab98:	a2000067 */ 	sb	$zero,0x67($s0)
/*  f02ab9c:	a60f0064 */ 	sh	$t7,0x64($s0)
/*  f02aba0:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02aba4:	aa01006c */ 	swl	$at,0x6c($s0)
/*  f02aba8:	ba01006f */ 	swr	$at,0x6f($s0)
/*  f02abac:	8e590004 */ 	lw	$t9,0x4($s2)
/*  f02abb0:	aa190070 */ 	swl	$t9,0x70($s0)
/*  f02abb4:	ba190073 */ 	swr	$t9,0x73($s0)
/*  f02abb8:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02abbc:	aa010074 */ 	swl	$at,0x74($s0)
/*  f02abc0:	ba010077 */ 	swr	$at,0x77($s0)
/*  f02abc4:	87b80192 */ 	lh	$t8,0x192($sp)
/*  f02abc8:	a618006c */ 	sh	$t8,0x6c($s0)
/*  f02abcc:	87af0194 */ 	lh	$t7,0x194($sp)
/*  f02abd0:	a60f006e */ 	sh	$t7,0x6e($s0)
/*  f02abd4:	87ae0196 */ 	lh	$t6,0x196($sp)
/*  f02abd8:	a2000073 */ 	sb	$zero,0x73($s0)
/*  f02abdc:	a6150068 */ 	sh	$s5,0x68($s0)
/*  f02abe0:	a614006a */ 	sh	$s4,0x6a($s0)
/*  f02abe4:	a6140076 */ 	sh	$s4,0x76($s0)
/*  f02abe8:	a60b0074 */ 	sh	$t3,0x74($s0)
/*  f02abec:	a60e0070 */ 	sh	$t6,0x70($s0)
/*  f02abf0:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02abf4:	aa010078 */ 	swl	$at,0x78($s0)
/*  f02abf8:	ba01007b */ 	swr	$at,0x7b($s0)
/*  f02abfc:	8e580004 */ 	lw	$t8,0x4($s2)
/*  f02ac00:	aa18007c */ 	swl	$t8,0x7c($s0)
/*  f02ac04:	ba18007f */ 	swr	$t8,0x7f($s0)
/*  f02ac08:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02ac0c:	aa010080 */ 	swl	$at,0x80($s0)
/*  f02ac10:	ba010083 */ 	swr	$at,0x83($s0)
/*  f02ac14:	87af01a4 */ 	lh	$t7,0x1a4($sp)
/*  f02ac18:	a60f0078 */ 	sh	$t7,0x78($s0)
/*  f02ac1c:	87ae01a6 */ 	lh	$t6,0x1a6($sp)
/*  f02ac20:	a60e007a */ 	sh	$t6,0x7a($s0)
/*  f02ac24:	87b901a8 */ 	lh	$t9,0x1a8($sp)
/*  f02ac28:	a200007f */ 	sb	$zero,0x7f($s0)
/*  f02ac2c:	a619007c */ 	sh	$t9,0x7c($s0)
/*  f02ac30:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02ac34:	aa010084 */ 	swl	$at,0x84($s0)
/*  f02ac38:	ba010087 */ 	swr	$at,0x87($s0)
/*  f02ac3c:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02ac40:	aa0f0088 */ 	swl	$t7,0x88($s0)
/*  f02ac44:	ba0f008b */ 	swr	$t7,0x8b($s0)
/*  f02ac48:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02ac4c:	aa01008c */ 	swl	$at,0x8c($s0)
/*  f02ac50:	ba01008f */ 	swr	$at,0x8f($s0)
/*  f02ac54:	87ae01aa */ 	lh	$t6,0x1aa($sp)
/*  f02ac58:	a60e0084 */ 	sh	$t6,0x84($s0)
/*  f02ac5c:	87b901ac */ 	lh	$t9,0x1ac($sp)
/*  f02ac60:	a6190086 */ 	sh	$t9,0x86($s0)
/*  f02ac64:	87b801ae */ 	lh	$t8,0x1ae($sp)
/*  f02ac68:	a200008b */ 	sb	$zero,0x8b($s0)
/*  f02ac6c:	a6150080 */ 	sh	$s5,0x80($s0)
/*  f02ac70:	a6130082 */ 	sh	$s3,0x82($s0)
/*  f02ac74:	a613008e */ 	sh	$s3,0x8e($s0)
/*  f02ac78:	a60b008c */ 	sh	$t3,0x8c($s0)
/*  f02ac7c:	a6180088 */ 	sh	$t8,0x88($s0)
/*  f02ac80:	8fb101f0 */ 	lw	$s1,0x1f0($sp)
/*  f02ac84:	3c1904b0 */ 	lui	$t9,0x4b0
/*  f02ac88:	37390090 */ 	ori	$t9,$t9,0x90
/*  f02ac8c:	262e0008 */ 	addiu	$t6,$s1,0x8
/*  f02ac90:	afae01f0 */ 	sw	$t6,0x1f0($sp)
/*  f02ac94:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f02ac98:	ae390000 */ 	sw	$t9,0x0($s1)
/*  f02ac9c:	ae220004 */ 	sw	$v0,0x4($s1)
/*  f02aca0:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f02aca4:	3c0eb100 */ 	lui	$t6,0xb100
/*  f02aca8:	3c194b5b */ 	lui	$t9,0x4b5b
/*  f02acac:	270f0008 */ 	addiu	$t7,$t8,0x8
/*  f02acb0:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02acb4:	37399010 */ 	ori	$t9,$t9,0x9010
/*  f02acb8:	35cea489 */ 	ori	$t6,$t6,0xa489
/*  f02acbc:	27a30124 */ 	addiu	$v1,$sp,0x124
/*  f02acc0:	27a60164 */ 	addiu	$a2,$sp,0x164
/*  f02acc4:	3c05b100 */ 	lui	$a1,0xb100
/*  f02acc8:	af0e0000 */ 	sw	$t6,0x0($t8)
/*  f02accc:	af190004 */ 	sw	$t9,0x4($t8)
.L0f02acd0:
/*  f02acd0:	8fa201f0 */ 	lw	$v0,0x1f0($sp)
/*  f02acd4:	24630010 */ 	addiu	$v1,$v1,0x10
/*  f02acd8:	244f0008 */ 	addiu	$t7,$v0,0x8
/*  f02acdc:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02ace0:	8c6efff8 */ 	lw	$t6,-0x8($v1)
/*  f02ace4:	8c6ffffc */ 	lw	$t7,-0x4($v1)
/*  f02ace8:	31d9000f */ 	andi	$t9,$t6,0xf
/*  f02acec:	0325c025 */ 	or	$t8,$t9,$a1
/*  f02acf0:	31ee000f */ 	andi	$t6,$t7,0xf
/*  f02acf4:	000ec900 */ 	sll	$t9,$t6,0x4
/*  f02acf8:	03197825 */ 	or	$t7,$t8,$t9
/*  f02acfc:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f02ad00:	8c78fff8 */ 	lw	$t8,-0x8($v1)
/*  f02ad04:	8c64fff0 */ 	lw	$a0,-0x10($v1)
/*  f02ad08:	3319000f */ 	andi	$t9,$t8,0xf
/*  f02ad0c:	308e000f */ 	andi	$t6,$a0,0xf
/*  f02ad10:	01c02025 */ 	or	$a0,$t6,$zero
/*  f02ad14:	00197b00 */ 	sll	$t7,$t9,0xc
/*  f02ad18:	01cf7025 */ 	or	$t6,$t6,$t7
/*  f02ad1c:	8c6ffff4 */ 	lw	$t7,-0xc($v1)
/*  f02ad20:	0004c200 */ 	sll	$t8,$a0,0x8
/*  f02ad24:	01d8c825 */ 	or	$t9,$t6,$t8
/*  f02ad28:	31ee000f */ 	andi	$t6,$t7,0xf
/*  f02ad2c:	000ec100 */ 	sll	$t8,$t6,0x4
/*  f02ad30:	03387825 */ 	or	$t7,$t9,$t8
/*  f02ad34:	1466ffe6 */ 	bne	$v1,$a2,.L0f02acd0
/*  f02ad38:	ac4f0004 */ 	sw	$t7,0x4($v0)
/*  f02ad3c:	1000029c */ 	b	.L0f02b7b0
/*  f02ad40:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f02ad44:
/*  f02ad44:	91c40000 */ 	lbu	$a0,0x0($t6)
/*  f02ad48:	24010001 */ 	addiu	$at,$zero,0x1
/*  f02ad4c:	10810005 */ 	beq	$a0,$at,.L0f02ad64
/*  f02ad50:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f02ad54:	11240003 */ 	beq	$t1,$a0,.L0f02ad64
/*  f02ad58:	24010002 */ 	addiu	$at,$zero,0x2
/*  f02ad5c:	5481000b */ 	bnel	$a0,$at,.L0f02ad8c
/*  f02ad60:	8fb901f4 */ 	lw	$t9,0x1f4($sp)
.L0f02ad64:
/*  f02ad64:	8fb901f8 */ 	lw	$t9,0x1f8($sp)
/*  f02ad68:	240500ff */ 	addiu	$a1,$zero,0xff
/*  f02ad6c:	8f380004 */ 	lw	$t8,0x4($t9)
/*  f02ad70:	8f0f0010 */ 	lw	$t7,0x10($t8)
/*  f02ad74:	31ee1000 */ 	andi	$t6,$t7,0x1000
/*  f02ad78:	51c00004 */ 	beqzl	$t6,.L0f02ad8c
/*  f02ad7c:	8fb901f4 */ 	lw	$t9,0x1f4($sp)
/*  f02ad80:	10000023 */ 	b	.L0f02ae10
/*  f02ad84:	240600ff */ 	addiu	$a2,$zero,0xff
/*  f02ad88:	8fb901f4 */ 	lw	$t9,0x1f4($sp)
.L0f02ad8c:
/*  f02ad8c:	3c02800a */ 	lui	$v0,%hi(g_Vars+0x8)
/*  f02ad90:	8c429fc8 */ 	lw	$v0,%lo(g_Vars+0x8)($v0)
/*  f02ad94:	8f23000c */ 	lw	$v1,0xc($t9)
/*  f02ad98:	00002825 */ 	or	$a1,$zero,$zero
/*  f02ad9c:	00003025 */ 	or	$a2,$zero,$zero
/*  f02ada0:	0043c023 */ 	subu	$t8,$v0,$v1
/*  f02ada4:	2b010051 */ 	slti	$at,$t8,0x51
/*  f02ada8:	10200019 */ 	beqz	$at,.L0f02ae10
/*  f02adac:	00627823 */ 	subu	$t7,$v1,$v0
/*  f02adb0:	25ee0050 */ 	addiu	$t6,$t7,0x50
/*  f02adb4:	448e4000 */ 	mtc1	$t6,$f8
/*  f02adb8:	8fb90210 */ 	lw	$t9,0x210($sp)
/*  f02adbc:	3c01404c */ 	lui	$at,0x404c
/*  f02adc0:	468041a0 */ 	cvt.s.w	$f6,$f8
/*  f02adc4:	44995000 */ 	mtc1	$t9,$f10
/*  f02adc8:	44818000 */ 	mtc1	$at,$f16
/*  f02adcc:	3c017f1b */ 	lui	$at,%hi(var7f1a8980)
/*  f02add0:	c4248980 */ 	lwc1	$f4,%lo(var7f1a8980)($at)
/*  f02add4:	468054a0 */ 	cvt.s.w	$f18,$f10
/*  f02add8:	46103302 */ 	mul.s	$f12,$f6,$f16
/*  f02addc:	00000000 */ 	nop
/*  f02ade0:	46049082 */ 	mul.s	$f2,$f18,$f4
/*  f02ade4:	00000000 */ 	nop
/*  f02ade8:	46026002 */ 	mul.s	$f0,$f12,$f2
/*  f02adec:	4600020d */ 	trunc.w.s	$f8,$f0
/*  f02adf0:	4600018d */ 	trunc.w.s	$f6,$f0
/*  f02adf4:	44054000 */ 	mfc1	$a1,$f8
/*  f02adf8:	44063000 */ 	mfc1	$a2,$f6
/*  f02adfc:	30af00ff */ 	andi	$t7,$a1,0xff
/*  f02ae00:	01e02825 */ 	or	$a1,$t7,$zero
/*  f02ae04:	30d900ff */ 	andi	$t9,$a2,0xff
/*  f02ae08:	10000001 */ 	b	.L0f02ae10
/*  f02ae0c:	03203025 */ 	or	$a2,$t9,$zero
.L0f02ae10:
/*  f02ae10:	24040005 */ 	addiu	$a0,$zero,0x5
/*  f02ae14:	a3a5017f */ 	sb	$a1,0x17f($sp)
/*  f02ae18:	a3a6017e */ 	sb	$a2,0x17e($sp)
/*  f02ae1c:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f02ae20:	afaa00f0 */ 	sw	$t2,0xf0($sp)
/*  f02ae24:	0fc59e73 */ 	jal	gfxAllocateColours
/*  f02ae28:	afab00ec */ 	sw	$t3,0xec($sp)
/*  f02ae2c:	8fb001f0 */ 	lw	$s0,0x1f0($sp)
/*  f02ae30:	3c0e0710 */ 	lui	$t6,0x710
/*  f02ae34:	35ce0014 */ 	ori	$t6,$t6,0x14
/*  f02ae38:	260f0008 */ 	addiu	$t7,$s0,0x8
/*  f02ae3c:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02ae40:	ae0e0000 */ 	sw	$t6,0x0($s0)
/*  f02ae44:	afa201d8 */ 	sw	$v0,0x1d8($sp)
/*  f02ae48:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f02ae4c:	00402025 */ 	or	$a0,$v0,$zero
/*  f02ae50:	8fa301d8 */ 	lw	$v1,0x1d8($sp)
/*  f02ae54:	93a5017f */ 	lbu	$a1,0x17f($sp)
/*  f02ae58:	8fa700f4 */ 	lw	$a3,0xf4($sp)
/*  f02ae5c:	8faa00f0 */ 	lw	$t2,0xf0($sp)
/*  f02ae60:	8fab00ec */ 	lw	$t3,0xec($sp)
/*  f02ae64:	93a6017e */ 	lbu	$a2,0x17e($sp)
/*  f02ae68:	ae020004 */ 	sw	$v0,0x4($s0)
/*  f02ae6c:	8fb90100 */ 	lw	$t9,0x100($sp)
/*  f02ae70:	2404001e */ 	addiu	$a0,$zero,0x1e
/*  f02ae74:	a0790000 */ 	sb	$t9,0x0($v1)
/*  f02ae78:	8fb800fc */ 	lw	$t8,0xfc($sp)
/*  f02ae7c:	a0780001 */ 	sb	$t8,0x1($v1)
/*  f02ae80:	8faf00f8 */ 	lw	$t7,0xf8($sp)
/*  f02ae84:	a0650003 */ 	sb	$a1,0x3($v1)
/*  f02ae88:	a0650007 */ 	sb	$a1,0x7($v1)
/*  f02ae8c:	a065000b */ 	sb	$a1,0xb($v1)
/*  f02ae90:	a0670004 */ 	sb	$a3,0x4($v1)
/*  f02ae94:	a0670008 */ 	sb	$a3,0x8($v1)
/*  f02ae98:	a06a0005 */ 	sb	$t2,0x5($v1)
/*  f02ae9c:	a06a0009 */ 	sb	$t2,0x9($v1)
/*  f02aea0:	a06b0006 */ 	sb	$t3,0x6($v1)
/*  f02aea4:	a06b000a */ 	sb	$t3,0xa($v1)
/*  f02aea8:	a06f0002 */ 	sb	$t7,0x2($v1)
/*  f02aeac:	8fae0100 */ 	lw	$t6,0x100($sp)
/*  f02aeb0:	24e70046 */ 	addiu	$a3,$a3,0x46
/*  f02aeb4:	254a0046 */ 	addiu	$t2,$t2,0x46
/*  f02aeb8:	25d90064 */ 	addiu	$t9,$t6,0x64
/*  f02aebc:	2b210100 */ 	slti	$at,$t9,0x100
/*  f02aec0:	14200003 */ 	bnez	$at,.L0f02aed0
/*  f02aec4:	afb90100 */ 	sw	$t9,0x100($sp)
/*  f02aec8:	240c00ff */ 	addiu	$t4,$zero,0xff
/*  f02aecc:	afac0100 */ 	sw	$t4,0x100($sp)
.L0f02aed0:
/*  f02aed0:	8fb80100 */ 	lw	$t8,0x100($sp)
/*  f02aed4:	256b0046 */ 	addiu	$t3,$t3,0x46
/*  f02aed8:	a078000c */ 	sb	$t8,0xc($v1)
/*  f02aedc:	8faf00fc */ 	lw	$t7,0xfc($sp)
/*  f02aee0:	25ee0064 */ 	addiu	$t6,$t7,0x64
/*  f02aee4:	29c10100 */ 	slti	$at,$t6,0x100
/*  f02aee8:	14200003 */ 	bnez	$at,.L0f02aef8
/*  f02aeec:	afae00fc */ 	sw	$t6,0xfc($sp)
/*  f02aef0:	240d00ff */ 	addiu	$t5,$zero,0xff
/*  f02aef4:	afad00fc */ 	sw	$t5,0xfc($sp)
.L0f02aef8:
/*  f02aef8:	8fb900fc */ 	lw	$t9,0xfc($sp)
/*  f02aefc:	a079000d */ 	sb	$t9,0xd($v1)
/*  f02af00:	8fb800f8 */ 	lw	$t8,0xf8($sp)
/*  f02af04:	270f0064 */ 	addiu	$t7,$t8,0x64
/*  f02af08:	29e10100 */ 	slti	$at,$t7,0x100
/*  f02af0c:	14200003 */ 	bnez	$at,.L0f02af1c
/*  f02af10:	afaf00f8 */ 	sw	$t7,0xf8($sp)
/*  f02af14:	241f00ff */ 	addiu	$ra,$zero,0xff
/*  f02af18:	afbf00f8 */ 	sw	$ra,0xf8($sp)
.L0f02af1c:
/*  f02af1c:	8fae00f8 */ 	lw	$t6,0xf8($sp)
/*  f02af20:	28e10100 */ 	slti	$at,$a3,0x100
/*  f02af24:	a066000f */ 	sb	$a2,0xf($v1)
/*  f02af28:	14200002 */ 	bnez	$at,.L0f02af34
/*  f02af2c:	a06e000e */ 	sb	$t6,0xe($v1)
/*  f02af30:	240700ff */ 	addiu	$a3,$zero,0xff
.L0f02af34:
/*  f02af34:	29410100 */ 	slti	$at,$t2,0x100
/*  f02af38:	14200002 */ 	bnez	$at,.L0f02af44
/*  f02af3c:	a0670010 */ 	sb	$a3,0x10($v1)
/*  f02af40:	240a00ff */ 	addiu	$t2,$zero,0xff
.L0f02af44:
/*  f02af44:	29610100 */ 	slti	$at,$t3,0x100
/*  f02af48:	14200002 */ 	bnez	$at,.L0f02af54
/*  f02af4c:	a06a0011 */ 	sb	$t2,0x11($v1)
/*  f02af50:	240b00ff */ 	addiu	$t3,$zero,0xff
.L0f02af54:
/*  f02af54:	a06b0012 */ 	sb	$t3,0x12($v1)
/*  f02af58:	0fc59e59 */ 	jal	gfxAllocateVertices
/*  f02af5c:	a0650013 */ 	sb	$a1,0x13($v1)
/*  f02af60:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f02af64:	27b80104 */ 	addiu	$t8,$sp,0x104
/*  f02af68:	00408025 */ 	or	$s0,$v0,$zero
/*  f02af6c:	0008c900 */ 	sll	$t9,$t0,0x4
/*  f02af70:	03382821 */ 	addu	$a1,$t9,$t8
/*  f02af74:	00a03825 */ 	or	$a3,$a1,$zero
/*  f02af78:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f02af7c:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f02af80:	00002025 */ 	or	$a0,$zero,$zero
/*  f02af84:	00401825 */ 	or	$v1,$v0,$zero
.L0f02af88:
/*  f02af88:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02af8c:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f02af90:	24e70004 */ 	addiu	$a3,$a3,0x4
/*  f02af94:	a8610000 */ 	swl	$at,0x0($v1)
/*  f02af98:	b8610003 */ 	swr	$at,0x3($v1)
/*  f02af9c:	8e590004 */ 	lw	$t9,0x4($s2)
/*  f02afa0:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f02afa4:	a879fff8 */ 	swl	$t9,-0x8($v1)
/*  f02afa8:	b879fffb */ 	swr	$t9,-0x5($v1)
/*  f02afac:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02afb0:	a861fffc */ 	swl	$at,-0x4($v1)
/*  f02afb4:	b861ffff */ 	swr	$at,-0x1($v1)
/*  f02afb8:	8cf8fffc */ 	lw	$t8,-0x4($a3)
/*  f02afbc:	28810004 */ 	slti	$at,$a0,0x4
/*  f02afc0:	03110019 */ 	multu	$t8,$s1
/*  f02afc4:	00007012 */ 	mflo	$t6
/*  f02afc8:	00ae7821 */ 	addu	$t7,$a1,$t6
/*  f02afcc:	85f90000 */ 	lh	$t9,0x0($t7)
/*  f02afd0:	a479fff4 */ 	sh	$t9,-0xc($v1)
/*  f02afd4:	8cf8fffc */ 	lw	$t8,-0x4($a3)
/*  f02afd8:	03110019 */ 	multu	$t8,$s1
/*  f02afdc:	00007012 */ 	mflo	$t6
/*  f02afe0:	00ae7821 */ 	addu	$t7,$a1,$t6
/*  f02afe4:	85f90002 */ 	lh	$t9,0x2($t7)
/*  f02afe8:	a479fff6 */ 	sh	$t9,-0xa($v1)
/*  f02afec:	8cf8fffc */ 	lw	$t8,-0x4($a3)
/*  f02aff0:	03110019 */ 	multu	$t8,$s1
/*  f02aff4:	00007012 */ 	mflo	$t6
/*  f02aff8:	00ae7821 */ 	addu	$t7,$a1,$t6
/*  f02affc:	85f90004 */ 	lh	$t9,0x4($t7)
/*  f02b000:	a060fffb */ 	sb	$zero,-0x5($v1)
/*  f02b004:	1420ffe0 */ 	bnez	$at,.L0f02af88
/*  f02b008:	a479fff8 */ 	sh	$t9,-0x8($v1)
/*  f02b00c:	8fa401f4 */ 	lw	$a0,0x1f4($sp)
/*  f02b010:	a4550008 */ 	sh	$s5,0x8($v0)
/*  f02b014:	a453000a */ 	sh	$s3,0xa($v0)
/*  f02b018:	87ab0052 */ 	lh	$t3,0x52($sp)
/*  f02b01c:	a4530016 */ 	sh	$s3,0x16($v0)
/*  f02b020:	a4540022 */ 	sh	$s4,0x22($v0)
/*  f02b024:	a455002c */ 	sh	$s5,0x2c($v0)
/*  f02b028:	a454002e */ 	sh	$s4,0x2e($v0)
/*  f02b02c:	a44b0014 */ 	sh	$t3,0x14($v0)
/*  f02b030:	a44b0020 */ 	sh	$t3,0x20($v0)
/*  f02b034:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b038:	a8410030 */ 	swl	$at,0x30($v0)
/*  f02b03c:	b8410033 */ 	swr	$at,0x33($v0)
/*  f02b040:	8e4e0004 */ 	lw	$t6,0x4($s2)
/*  f02b044:	a84e0034 */ 	swl	$t6,0x34($v0)
/*  f02b048:	b84e0037 */ 	swr	$t6,0x37($v0)
/*  f02b04c:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b050:	a8410038 */ 	swl	$at,0x38($v0)
/*  f02b054:	b841003b */ 	swr	$at,0x3b($v0)
/*  f02b058:	84830012 */ 	lh	$v1,0x12($a0)
/*  f02b05c:	24017fff */ 	addiu	$at,$zero,0x7fff
/*  f02b060:	5461001e */ 	bnel	$v1,$at,.L0f02b0dc
/*  f02b064:	a4430030 */ 	sh	$v1,0x30($v0)
/*  f02b068:	844f0024 */ 	lh	$t7,0x24($v0)
/*  f02b06c:	84590000 */ 	lh	$t9,0x0($v0)
/*  f02b070:	844e000c */ 	lh	$t6,0xc($v0)
/*  f02b074:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b078:	84590018 */ 	lh	$t9,0x18($v0)
/*  f02b07c:	030e7821 */ 	addu	$t7,$t8,$t6
/*  f02b080:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b084:	84590002 */ 	lh	$t9,0x2($v0)
/*  f02b088:	844f0026 */ 	lh	$t7,0x26($v0)
/*  f02b08c:	00187083 */ 	sra	$t6,$t8,0x2
/*  f02b090:	a44e0030 */ 	sh	$t6,0x30($v0)
/*  f02b094:	844e000e */ 	lh	$t6,0xe($v0)
/*  f02b098:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b09c:	8459001a */ 	lh	$t9,0x1a($v0)
/*  f02b0a0:	030e7821 */ 	addu	$t7,$t8,$t6
/*  f02b0a4:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b0a8:	84590004 */ 	lh	$t9,0x4($v0)
/*  f02b0ac:	844f0028 */ 	lh	$t7,0x28($v0)
/*  f02b0b0:	00187083 */ 	sra	$t6,$t8,0x2
/*  f02b0b4:	a44e0032 */ 	sh	$t6,0x32($v0)
/*  f02b0b8:	844e0010 */ 	lh	$t6,0x10($v0)
/*  f02b0bc:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b0c0:	8459001c */ 	lh	$t9,0x1c($v0)
/*  f02b0c4:	030e7821 */ 	addu	$t7,$t8,$t6
/*  f02b0c8:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02b0cc:	00187083 */ 	sra	$t6,$t8,0x2
/*  f02b0d0:	10000006 */ 	b	.L0f02b0ec
/*  f02b0d4:	a44e0034 */ 	sh	$t6,0x34($v0)
/*  f02b0d8:	a4430030 */ 	sh	$v1,0x30($v0)
.L0f02b0dc:
/*  f02b0dc:	848f0014 */ 	lh	$t7,0x14($a0)
/*  f02b0e0:	a44f0032 */ 	sh	$t7,0x32($v0)
/*  f02b0e4:	84990016 */ 	lh	$t9,0x16($a0)
/*  f02b0e8:	a4590034 */ 	sh	$t9,0x34($v0)
.L0f02b0ec:
/*  f02b0ec:	02ab1821 */ 	addu	$v1,$s5,$t3
/*  f02b0f0:	02741021 */ 	addu	$v0,$s3,$s4
/*  f02b0f4:	2418000c */ 	addiu	$t8,$zero,0xc
/*  f02b0f8:	00037043 */ 	sra	$t6,$v1,0x1
/*  f02b0fc:	00027843 */ 	sra	$t7,$v0,0x1
/*  f02b100:	a2180037 */ 	sb	$t8,0x37($s0)
/*  f02b104:	a60e0038 */ 	sh	$t6,0x38($s0)
/*  f02b108:	a60f003a */ 	sh	$t7,0x3a($s0)
/*  f02b10c:	8fb901f0 */ 	lw	$t9,0x1f0($sp)
/*  f02b110:	01c01825 */ 	or	$v1,$t6,$zero
/*  f02b114:	3c0e0440 */ 	lui	$t6,0x440
/*  f02b118:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f02b11c:	afb801f0 */ 	sw	$t8,0x1f0($sp)
/*  f02b120:	35ce003c */ 	ori	$t6,$t6,0x3c
/*  f02b124:	af2e0000 */ 	sw	$t6,0x0($t9)
/*  f02b128:	afab0044 */ 	sw	$t3,0x44($sp)
/*  f02b12c:	afa30040 */ 	sw	$v1,0x40($sp)
/*  f02b130:	afaf004c */ 	sw	$t7,0x4c($sp)
/*  f02b134:	02002025 */ 	or	$a0,$s0,$zero
/*  f02b138:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f02b13c:	afb90078 */ 	sw	$t9,0x78($sp)
/*  f02b140:	8fa60078 */ 	lw	$a2,0x78($sp)
/*  f02b144:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f02b148:	8fab0044 */ 	lw	$t3,0x44($sp)
/*  f02b14c:	acc20004 */ 	sw	$v0,0x4($a2)
/*  f02b150:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
/*  f02b154:	3c18b100 */ 	lui	$t8,0xb100
/*  f02b158:	3c0e0332 */ 	lui	$t6,0x332
/*  f02b15c:	25f90008 */ 	addiu	$t9,$t7,0x8
/*  f02b160:	afb901f0 */ 	sw	$t9,0x1f0($sp)
/*  f02b164:	35ce2110 */ 	ori	$t6,$t6,0x2110
/*  f02b168:	37184444 */ 	ori	$t8,$t8,0x4444
/*  f02b16c:	adf80000 */ 	sw	$t8,0x0($t7)
/*  f02b170:	adee0004 */ 	sw	$t6,0x4($t7)
/*  f02b174:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f02b178:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f02b17c:	2610003c */ 	addiu	$s0,$s0,0x3c
/*  f02b180:	8fa70048 */ 	lw	$a3,0x48($sp)
/*  f02b184:	00002025 */ 	or	$a0,$zero,$zero
/*  f02b188:	241f0005 */ 	addiu	$ra,$zero,0x5
/*  f02b18c:	240d0008 */ 	addiu	$t5,$zero,0x8
/*  f02b190:	240c0004 */ 	addiu	$t4,$zero,0x4
.L0f02b194:
/*  f02b194:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b198:	248a0001 */ 	addiu	$t2,$a0,0x1
/*  f02b19c:	aa010000 */ 	swl	$at,0x0($s0)
/*  f02b1a0:	ba010003 */ 	swr	$at,0x3($s0)
/*  f02b1a4:	8e590004 */ 	lw	$t9,0x4($s2)
/*  f02b1a8:	aa190004 */ 	swl	$t9,0x4($s0)
/*  f02b1ac:	ba190007 */ 	swr	$t9,0x7($s0)
/*  f02b1b0:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b1b4:	aa010008 */ 	swl	$at,0x8($s0)
/*  f02b1b8:	ba01000b */ 	swr	$at,0xb($s0)
/*  f02b1bc:	8fb80048 */ 	lw	$t8,0x48($sp)
/*  f02b1c0:	05410004 */ 	bgez	$t2,.L0f02b1d4
/*  f02b1c4:	314e0003 */ 	andi	$t6,$t2,0x3
/*  f02b1c8:	11c00002 */ 	beqz	$t6,.L0f02b1d4
/*  f02b1cc:	00000000 */ 	nop
/*  f02b1d0:	25cefffc */ 	addiu	$t6,$t6,-4
.L0f02b1d4:
/*  f02b1d4:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f02b1d8:	030f1021 */ 	addu	$v0,$t8,$t7
/*  f02b1dc:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b1e0:	03310019 */ 	multu	$t9,$s1
/*  f02b1e4:	00007012 */ 	mflo	$t6
/*  f02b1e8:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b1ec:	870f0000 */ 	lh	$t7,0x0($t8)
/*  f02b1f0:	a60f0000 */ 	sh	$t7,0x0($s0)
/*  f02b1f4:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b1f8:	03310019 */ 	multu	$t9,$s1
/*  f02b1fc:	00007012 */ 	mflo	$t6
/*  f02b200:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b204:	870f0002 */ 	lh	$t7,0x2($t8)
/*  f02b208:	a60f0002 */ 	sh	$t7,0x2($s0)
/*  f02b20c:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b210:	03310019 */ 	multu	$t9,$s1
/*  f02b214:	00007012 */ 	mflo	$t6
/*  f02b218:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b21c:	870f0004 */ 	lh	$t7,0x4($t8)
/*  f02b220:	a20c0007 */ 	sb	$t4,0x7($s0)
/*  f02b224:	a60f0004 */ 	sh	$t7,0x4($s0)
/*  f02b228:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b22c:	aa01000c */ 	swl	$at,0xc($s0)
/*  f02b230:	ba01000f */ 	swr	$at,0xf($s0)
/*  f02b234:	8e4e0004 */ 	lw	$t6,0x4($s2)
/*  f02b238:	aa0e0010 */ 	swl	$t6,0x10($s0)
/*  f02b23c:	ba0e0013 */ 	swr	$t6,0x13($s0)
/*  f02b240:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b244:	aa010014 */ 	swl	$at,0x14($s0)
/*  f02b248:	ba010017 */ 	swr	$at,0x17($s0)
/*  f02b24c:	8cf80000 */ 	lw	$t8,0x0($a3)
/*  f02b250:	03110019 */ 	multu	$t8,$s1
/*  f02b254:	00007812 */ 	mflo	$t7
/*  f02b258:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02b25c:	872e0000 */ 	lh	$t6,0x0($t9)
/*  f02b260:	a60e000c */ 	sh	$t6,0xc($s0)
/*  f02b264:	8cf80000 */ 	lw	$t8,0x0($a3)
/*  f02b268:	03110019 */ 	multu	$t8,$s1
/*  f02b26c:	00007812 */ 	mflo	$t7
/*  f02b270:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02b274:	872e0002 */ 	lh	$t6,0x2($t9)
/*  f02b278:	a60e000e */ 	sh	$t6,0xe($s0)
/*  f02b27c:	8cf80000 */ 	lw	$t8,0x0($a3)
/*  f02b280:	03110019 */ 	multu	$t8,$s1
/*  f02b284:	00007812 */ 	mflo	$t7
/*  f02b288:	00afc821 */ 	addu	$t9,$a1,$t7
/*  f02b28c:	872e0004 */ 	lh	$t6,0x4($t9)
/*  f02b290:	a20c0013 */ 	sb	$t4,0x13($s0)
/*  f02b294:	a60e0010 */ 	sh	$t6,0x10($s0)
/*  f02b298:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b29c:	aa010018 */ 	swl	$at,0x18($s0)
/*  f02b2a0:	ba01001b */ 	swr	$at,0x1b($s0)
/*  f02b2a4:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02b2a8:	aa0f001c */ 	swl	$t7,0x1c($s0)
/*  f02b2ac:	ba0f001f */ 	swr	$t7,0x1f($s0)
/*  f02b2b0:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b2b4:	aa010020 */ 	swl	$at,0x20($s0)
/*  f02b2b8:	ba010023 */ 	swr	$at,0x23($s0)
/*  f02b2bc:	8cf90000 */ 	lw	$t9,0x0($a3)
/*  f02b2c0:	24010001 */ 	addiu	$at,$zero,0x1
/*  f02b2c4:	03310019 */ 	multu	$t9,$s1
/*  f02b2c8:	00007012 */ 	mflo	$t6
/*  f02b2cc:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b2d0:	870f0000 */ 	lh	$t7,0x0($t8)
/*  f02b2d4:	a60f0018 */ 	sh	$t7,0x18($s0)
/*  f02b2d8:	8cf90000 */ 	lw	$t9,0x0($a3)
/*  f02b2dc:	03310019 */ 	multu	$t9,$s1
/*  f02b2e0:	00007012 */ 	mflo	$t6
/*  f02b2e4:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b2e8:	870f0002 */ 	lh	$t7,0x2($t8)
/*  f02b2ec:	a60f001a */ 	sh	$t7,0x1a($s0)
/*  f02b2f0:	8cf90000 */ 	lw	$t9,0x0($a3)
/*  f02b2f4:	03310019 */ 	multu	$t9,$s1
/*  f02b2f8:	00007012 */ 	mflo	$t6
/*  f02b2fc:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b300:	870f0004 */ 	lh	$t7,0x4($t8)
/*  f02b304:	a20d001f */ 	sb	$t5,0x1f($s0)
/*  f02b308:	15000004 */ 	bnez	$t0,.L0f02b31c
/*  f02b30c:	a60f001c */ 	sh	$t7,0x1c($s0)
/*  f02b310:	8fb901c8 */ 	lw	$t9,0x1c8($sp)
/*  f02b314:	10000016 */ 	b	.L0f02b370
/*  f02b318:	a6190018 */ 	sh	$t9,0x18($s0)
.L0f02b31c:
/*  f02b31c:	15010003 */ 	bne	$t0,$at,.L0f02b32c
/*  f02b320:	8fae01cc */ 	lw	$t6,0x1cc($sp)
/*  f02b324:	10000012 */ 	b	.L0f02b370
/*  f02b328:	a60e0018 */ 	sh	$t6,0x18($s0)
.L0f02b32c:
/*  f02b32c:	24010002 */ 	addiu	$at,$zero,0x2
/*  f02b330:	15010003 */ 	bne	$t0,$at,.L0f02b340
/*  f02b334:	8fb801c0 */ 	lw	$t8,0x1c0($sp)
/*  f02b338:	1000000d */ 	b	.L0f02b370
/*  f02b33c:	a618001a */ 	sh	$t8,0x1a($s0)
.L0f02b340:
/*  f02b340:	24010003 */ 	addiu	$at,$zero,0x3
/*  f02b344:	15010003 */ 	bne	$t0,$at,.L0f02b354
/*  f02b348:	8faf01c4 */ 	lw	$t7,0x1c4($sp)
/*  f02b34c:	10000008 */ 	b	.L0f02b370
/*  f02b350:	a60f001a */ 	sh	$t7,0x1a($s0)
.L0f02b354:
/*  f02b354:	15090003 */ 	bne	$t0,$t1,.L0f02b364
/*  f02b358:	8fb901b8 */ 	lw	$t9,0x1b8($sp)
/*  f02b35c:	10000004 */ 	b	.L0f02b370
/*  f02b360:	a619001c */ 	sh	$t9,0x1c($s0)
.L0f02b364:
/*  f02b364:	151f0002 */ 	bne	$t0,$ra,.L0f02b370
/*  f02b368:	8fae01bc */ 	lw	$t6,0x1bc($sp)
/*  f02b36c:	a60e001c */ 	sh	$t6,0x1c($s0)
.L0f02b370:
/*  f02b370:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b374:	aa010024 */ 	swl	$at,0x24($s0)
/*  f02b378:	ba010027 */ 	swr	$at,0x27($s0)
/*  f02b37c:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02b380:	aa0f0028 */ 	swl	$t7,0x28($s0)
/*  f02b384:	ba0f002b */ 	swr	$t7,0x2b($s0)
/*  f02b388:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b38c:	aa01002c */ 	swl	$at,0x2c($s0)
/*  f02b390:	ba01002f */ 	swr	$at,0x2f($s0)
/*  f02b394:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b398:	24010001 */ 	addiu	$at,$zero,0x1
/*  f02b39c:	03310019 */ 	multu	$t9,$s1
/*  f02b3a0:	00007012 */ 	mflo	$t6
/*  f02b3a4:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b3a8:	870f0000 */ 	lh	$t7,0x0($t8)
/*  f02b3ac:	a60f0024 */ 	sh	$t7,0x24($s0)
/*  f02b3b0:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b3b4:	03310019 */ 	multu	$t9,$s1
/*  f02b3b8:	00007012 */ 	mflo	$t6
/*  f02b3bc:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b3c0:	870f0002 */ 	lh	$t7,0x2($t8)
/*  f02b3c4:	a60f0026 */ 	sh	$t7,0x26($s0)
/*  f02b3c8:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f02b3cc:	03310019 */ 	multu	$t9,$s1
/*  f02b3d0:	00007012 */ 	mflo	$t6
/*  f02b3d4:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b3d8:	870f0004 */ 	lh	$t7,0x4($t8)
/*  f02b3dc:	a20d002b */ 	sb	$t5,0x2b($s0)
/*  f02b3e0:	15000004 */ 	bnez	$t0,.L0f02b3f4
/*  f02b3e4:	a60f0028 */ 	sh	$t7,0x28($s0)
/*  f02b3e8:	8fb901c8 */ 	lw	$t9,0x1c8($sp)
/*  f02b3ec:	10000016 */ 	b	.L0f02b448
/*  f02b3f0:	a6190024 */ 	sh	$t9,0x24($s0)
.L0f02b3f4:
/*  f02b3f4:	15010003 */ 	bne	$t0,$at,.L0f02b404
/*  f02b3f8:	8fae01cc */ 	lw	$t6,0x1cc($sp)
/*  f02b3fc:	10000012 */ 	b	.L0f02b448
/*  f02b400:	a60e0024 */ 	sh	$t6,0x24($s0)
.L0f02b404:
/*  f02b404:	24010002 */ 	addiu	$at,$zero,0x2
/*  f02b408:	15010003 */ 	bne	$t0,$at,.L0f02b418
/*  f02b40c:	8fb801c0 */ 	lw	$t8,0x1c0($sp)
/*  f02b410:	1000000d */ 	b	.L0f02b448
/*  f02b414:	a6180026 */ 	sh	$t8,0x26($s0)
.L0f02b418:
/*  f02b418:	24010003 */ 	addiu	$at,$zero,0x3
/*  f02b41c:	15010003 */ 	bne	$t0,$at,.L0f02b42c
/*  f02b420:	8faf01c4 */ 	lw	$t7,0x1c4($sp)
/*  f02b424:	10000008 */ 	b	.L0f02b448
/*  f02b428:	a60f0026 */ 	sh	$t7,0x26($s0)
.L0f02b42c:
/*  f02b42c:	15090003 */ 	bne	$t0,$t1,.L0f02b43c
/*  f02b430:	8fb901b8 */ 	lw	$t9,0x1b8($sp)
/*  f02b434:	10000004 */ 	b	.L0f02b448
/*  f02b438:	a6190028 */ 	sh	$t9,0x28($s0)
.L0f02b43c:
/*  f02b43c:	151f0002 */ 	bne	$t0,$ra,.L0f02b448
/*  f02b440:	8fae01bc */ 	lw	$t6,0x1bc($sp)
/*  f02b444:	a60e0028 */ 	sh	$t6,0x28($s0)
.L0f02b448:
/*  f02b448:	a6150008 */ 	sh	$s5,0x8($s0)
/*  f02b44c:	a613000a */ 	sh	$s3,0xa($s0)
/*  f02b450:	a60b0014 */ 	sh	$t3,0x14($s0)
/*  f02b454:	a6130016 */ 	sh	$s3,0x16($s0)
/*  f02b458:	a60b0020 */ 	sh	$t3,0x20($s0)
/*  f02b45c:	a6140022 */ 	sh	$s4,0x22($s0)
/*  f02b460:	a615002c */ 	sh	$s5,0x2c($s0)
/*  f02b464:	a614002e */ 	sh	$s4,0x2e($s0)
/*  f02b468:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b46c:	86190024 */ 	lh	$t9,0x24($s0)
/*  f02b470:	860e0000 */ 	lh	$t6,0x0($s0)
/*  f02b474:	aa010030 */ 	swl	$at,0x30($s0)
/*  f02b478:	ba010033 */ 	swr	$at,0x33($s0)
/*  f02b47c:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02b480:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b484:	860e0018 */ 	lh	$t6,0x18($s0)
/*  f02b488:	aa0f0034 */ 	swl	$t7,0x34($s0)
/*  f02b48c:	ba0f0037 */ 	swr	$t7,0x37($s0)
/*  f02b490:	860f000c */ 	lh	$t7,0xc($s0)
/*  f02b494:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b498:	02002025 */ 	or	$a0,$s0,$zero
/*  f02b49c:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b4a0:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b4a4:	860e0002 */ 	lh	$t6,0x2($s0)
/*  f02b4a8:	86190026 */ 	lh	$t9,0x26($s0)
/*  f02b4ac:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b4b0:	a60f0030 */ 	sh	$t7,0x30($s0)
/*  f02b4b4:	860f000e */ 	lh	$t7,0xe($s0)
/*  f02b4b8:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b4bc:	860e001a */ 	lh	$t6,0x1a($s0)
/*  f02b4c0:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b4c4:	aa010038 */ 	swl	$at,0x38($s0)
/*  f02b4c8:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b4cc:	860e0004 */ 	lh	$t6,0x4($s0)
/*  f02b4d0:	86190028 */ 	lh	$t9,0x28($s0)
/*  f02b4d4:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b4d8:	a60f0032 */ 	sh	$t7,0x32($s0)
/*  f02b4dc:	860f0010 */ 	lh	$t7,0x10($s0)
/*  f02b4e0:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b4e4:	860e001c */ 	lh	$t6,0x1c($s0)
/*  f02b4e8:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b4ec:	ba01003b */ 	swr	$at,0x3b($s0)
/*  f02b4f0:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b4f4:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b4f8:	24190010 */ 	addiu	$t9,$zero,0x10
/*  f02b4fc:	a60f0034 */ 	sh	$t7,0x34($s0)
/*  f02b500:	a2190037 */ 	sb	$t9,0x37($s0)
/*  f02b504:	8fae0040 */ 	lw	$t6,0x40($sp)
/*  f02b508:	a60e0038 */ 	sh	$t6,0x38($s0)
/*  f02b50c:	8fb8004c */ 	lw	$t8,0x4c($sp)
/*  f02b510:	3c0e0440 */ 	lui	$t6,0x440
/*  f02b514:	35ce003c */ 	ori	$t6,$t6,0x3c
/*  f02b518:	a618003a */ 	sh	$t8,0x3a($s0)
/*  f02b51c:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
/*  f02b520:	25f90008 */ 	addiu	$t9,$t7,0x8
/*  f02b524:	afb901f0 */ 	sw	$t9,0x1f0($sp)
/*  f02b528:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f02b52c:	afab0044 */ 	sw	$t3,0x44($sp)
/*  f02b530:	afaa0058 */ 	sw	$t2,0x58($sp)
/*  f02b534:	afa70054 */ 	sw	$a3,0x54($sp)
/*  f02b538:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f02b53c:	afaf0068 */ 	sw	$t7,0x68($sp)
/*  f02b540:	8fa60068 */ 	lw	$a2,0x68($sp)
/*  f02b544:	8fa70054 */ 	lw	$a3,0x54($sp)
/*  f02b548:	8fa40058 */ 	lw	$a0,0x58($sp)
/*  f02b54c:	8fa80204 */ 	lw	$t0,0x204($sp)
/*  f02b550:	8fab0044 */ 	lw	$t3,0x44($sp)
/*  f02b554:	acc20004 */ 	sw	$v0,0x4($a2)
/*  f02b558:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f02b55c:	3c19b100 */ 	lui	$t9,0xb100
/*  f02b560:	3c0e0332 */ 	lui	$t6,0x332
/*  f02b564:	270f0008 */ 	addiu	$t7,$t8,0x8
/*  f02b568:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02b56c:	35ce2110 */ 	ori	$t6,$t6,0x2110
/*  f02b570:	37394444 */ 	ori	$t9,$t9,0x4444
/*  f02b574:	28810004 */ 	slti	$at,$a0,0x4
/*  f02b578:	27a50180 */ 	addiu	$a1,$sp,0x180
/*  f02b57c:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f02b580:	240c0004 */ 	addiu	$t4,$zero,0x4
/*  f02b584:	240d0008 */ 	addiu	$t5,$zero,0x8
/*  f02b588:	241f0005 */ 	addiu	$ra,$zero,0x5
/*  f02b58c:	2610003c */ 	addiu	$s0,$s0,0x3c
/*  f02b590:	24e70004 */ 	addiu	$a3,$a3,0x4
/*  f02b594:	af190000 */ 	sw	$t9,0x0($t8)
/*  f02b598:	1420fefe */ 	bnez	$at,.L0f02b194
/*  f02b59c:	af0e0004 */ 	sw	$t6,0x4($t8)
/*  f02b5a0:	8fa20048 */ 	lw	$v0,0x48($sp)
/*  f02b5a4:	02001825 */ 	or	$v1,$s0,$zero
/*  f02b5a8:	00003025 */ 	or	$a2,$zero,$zero
/*  f02b5ac:	24040010 */ 	addiu	$a0,$zero,0x10
/*  f02b5b0:	2442000c */ 	addiu	$v0,$v0,12
.L0f02b5b4:
/*  f02b5b4:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b5b8:	24c60004 */ 	addiu	$a2,$a2,0x4
/*  f02b5bc:	2442fffc */ 	addiu	$v0,$v0,-4
/*  f02b5c0:	a8610000 */ 	swl	$at,0x0($v1)
/*  f02b5c4:	b8610003 */ 	swr	$at,0x3($v1)
/*  f02b5c8:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02b5cc:	a86f0004 */ 	swl	$t7,0x4($v1)
/*  f02b5d0:	b86f0007 */ 	swr	$t7,0x7($v1)
/*  f02b5d4:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b5d8:	a8610008 */ 	swl	$at,0x8($v1)
/*  f02b5dc:	b861000b */ 	swr	$at,0xb($v1)
/*  f02b5e0:	8c590004 */ 	lw	$t9,0x4($v0)
/*  f02b5e4:	24010001 */ 	addiu	$at,$zero,0x1
/*  f02b5e8:	03310019 */ 	multu	$t9,$s1
/*  f02b5ec:	00007012 */ 	mflo	$t6
/*  f02b5f0:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b5f4:	870f0000 */ 	lh	$t7,0x0($t8)
/*  f02b5f8:	a46f0000 */ 	sh	$t7,0x0($v1)
/*  f02b5fc:	8c590004 */ 	lw	$t9,0x4($v0)
/*  f02b600:	03310019 */ 	multu	$t9,$s1
/*  f02b604:	00007012 */ 	mflo	$t6
/*  f02b608:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b60c:	870f0002 */ 	lh	$t7,0x2($t8)
/*  f02b610:	a46f0002 */ 	sh	$t7,0x2($v1)
/*  f02b614:	8c590004 */ 	lw	$t9,0x4($v0)
/*  f02b618:	03310019 */ 	multu	$t9,$s1
/*  f02b61c:	00007012 */ 	mflo	$t6
/*  f02b620:	00aec021 */ 	addu	$t8,$a1,$t6
/*  f02b624:	870f0004 */ 	lh	$t7,0x4($t8)
/*  f02b628:	a06d0007 */ 	sb	$t5,0x7($v1)
/*  f02b62c:	15000004 */ 	bnez	$t0,.L0f02b640
/*  f02b630:	a46f0004 */ 	sh	$t7,0x4($v1)
/*  f02b634:	8fb901c8 */ 	lw	$t9,0x1c8($sp)
/*  f02b638:	10000016 */ 	b	.L0f02b694
/*  f02b63c:	a4790000 */ 	sh	$t9,0x0($v1)
.L0f02b640:
/*  f02b640:	15010003 */ 	bne	$t0,$at,.L0f02b650
/*  f02b644:	8fae01cc */ 	lw	$t6,0x1cc($sp)
/*  f02b648:	10000012 */ 	b	.L0f02b694
/*  f02b64c:	a46e0000 */ 	sh	$t6,0x0($v1)
.L0f02b650:
/*  f02b650:	24010002 */ 	addiu	$at,$zero,0x2
/*  f02b654:	15010003 */ 	bne	$t0,$at,.L0f02b664
/*  f02b658:	8fb801c0 */ 	lw	$t8,0x1c0($sp)
/*  f02b65c:	1000000d */ 	b	.L0f02b694
/*  f02b660:	a4780002 */ 	sh	$t8,0x2($v1)
.L0f02b664:
/*  f02b664:	24010003 */ 	addiu	$at,$zero,0x3
/*  f02b668:	15010003 */ 	bne	$t0,$at,.L0f02b678
/*  f02b66c:	8faf01c4 */ 	lw	$t7,0x1c4($sp)
/*  f02b670:	10000008 */ 	b	.L0f02b694
/*  f02b674:	a46f0002 */ 	sh	$t7,0x2($v1)
.L0f02b678:
/*  f02b678:	15090003 */ 	bne	$t0,$t1,.L0f02b688
/*  f02b67c:	8fb901b8 */ 	lw	$t9,0x1b8($sp)
/*  f02b680:	10000004 */ 	b	.L0f02b694
/*  f02b684:	a4790004 */ 	sh	$t9,0x4($v1)
.L0f02b688:
/*  f02b688:	151f0002 */ 	bne	$t0,$ra,.L0f02b694
/*  f02b68c:	8fae01bc */ 	lw	$t6,0x1bc($sp)
/*  f02b690:	a46e0004 */ 	sh	$t6,0x4($v1)
.L0f02b694:
/*  f02b694:	14c4ffc7 */ 	bne	$a2,$a0,.L0f02b5b4
/*  f02b698:	2463000c */ 	addiu	$v1,$v1,0xc
/*  f02b69c:	a6150008 */ 	sh	$s5,0x8($s0)
/*  f02b6a0:	a613000a */ 	sh	$s3,0xa($s0)
/*  f02b6a4:	a60b0014 */ 	sh	$t3,0x14($s0)
/*  f02b6a8:	a6130016 */ 	sh	$s3,0x16($s0)
/*  f02b6ac:	a60b0020 */ 	sh	$t3,0x20($s0)
/*  f02b6b0:	a6140022 */ 	sh	$s4,0x22($s0)
/*  f02b6b4:	a615002c */ 	sh	$s5,0x2c($s0)
/*  f02b6b8:	a614002e */ 	sh	$s4,0x2e($s0)
/*  f02b6bc:	8e410000 */ 	lw	$at,0x0($s2)
/*  f02b6c0:	86190024 */ 	lh	$t9,0x24($s0)
/*  f02b6c4:	860e0000 */ 	lh	$t6,0x0($s0)
/*  f02b6c8:	aa010030 */ 	swl	$at,0x30($s0)
/*  f02b6cc:	ba010033 */ 	swr	$at,0x33($s0)
/*  f02b6d0:	8e4f0004 */ 	lw	$t7,0x4($s2)
/*  f02b6d4:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b6d8:	860e0018 */ 	lh	$t6,0x18($s0)
/*  f02b6dc:	aa0f0034 */ 	swl	$t7,0x34($s0)
/*  f02b6e0:	ba0f0037 */ 	swr	$t7,0x37($s0)
/*  f02b6e4:	860f000c */ 	lh	$t7,0xc($s0)
/*  f02b6e8:	8e410008 */ 	lw	$at,0x8($s2)
/*  f02b6ec:	02002025 */ 	or	$a0,$s0,$zero
/*  f02b6f0:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b6f4:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b6f8:	860e0002 */ 	lh	$t6,0x2($s0)
/*  f02b6fc:	86190026 */ 	lh	$t9,0x26($s0)
/*  f02b700:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b704:	a60f0030 */ 	sh	$t7,0x30($s0)
/*  f02b708:	860f000e */ 	lh	$t7,0xe($s0)
/*  f02b70c:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b710:	860e001a */ 	lh	$t6,0x1a($s0)
/*  f02b714:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b718:	aa010038 */ 	swl	$at,0x38($s0)
/*  f02b71c:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b720:	860e0004 */ 	lh	$t6,0x4($s0)
/*  f02b724:	86190028 */ 	lh	$t9,0x28($s0)
/*  f02b728:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b72c:	a60f0032 */ 	sh	$t7,0x32($s0)
/*  f02b730:	860f0010 */ 	lh	$t7,0x10($s0)
/*  f02b734:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b738:	860e001c */ 	lh	$t6,0x1c($s0)
/*  f02b73c:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f02b740:	ba01003b */ 	swr	$at,0x3b($s0)
/*  f02b744:	032ec021 */ 	addu	$t8,$t9,$t6
/*  f02b748:	00187883 */ 	sra	$t7,$t8,0x2
/*  f02b74c:	24190010 */ 	addiu	$t9,$zero,0x10
/*  f02b750:	a60f0034 */ 	sh	$t7,0x34($s0)
/*  f02b754:	a2190037 */ 	sb	$t9,0x37($s0)
/*  f02b758:	8fae0040 */ 	lw	$t6,0x40($sp)
/*  f02b75c:	a60e0038 */ 	sh	$t6,0x38($s0)
/*  f02b760:	8fb8004c */ 	lw	$t8,0x4c($sp)
/*  f02b764:	3c0e0440 */ 	lui	$t6,0x440
/*  f02b768:	35ce003c */ 	ori	$t6,$t6,0x3c
/*  f02b76c:	a618003a */ 	sh	$t8,0x3a($s0)
/*  f02b770:	8fb101f0 */ 	lw	$s1,0x1f0($sp)
/*  f02b774:	26390008 */ 	addiu	$t9,$s1,0x8
/*  f02b778:	afb901f0 */ 	sw	$t9,0x1f0($sp)
/*  f02b77c:	0c012d20 */ 	jal	osVirtualToPhysical
/*  f02b780:	ae2e0000 */ 	sw	$t6,0x0($s1)
/*  f02b784:	ae220004 */ 	sw	$v0,0x4($s1)
/*  f02b788:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f02b78c:	3c19b100 */ 	lui	$t9,0xb100
/*  f02b790:	3c0e0332 */ 	lui	$t6,0x332
/*  f02b794:	270f0008 */ 	addiu	$t7,$t8,0x8
/*  f02b798:	afaf01f0 */ 	sw	$t7,0x1f0($sp)
/*  f02b79c:	35ce2110 */ 	ori	$t6,$t6,0x2110
/*  f02b7a0:	37394444 */ 	ori	$t9,$t9,0x4444
/*  f02b7a4:	af190000 */ 	sw	$t9,0x0($t8)
/*  f02b7a8:	af0e0004 */ 	sw	$t6,0x4($t8)
/*  f02b7ac:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f02b7b0:
/*  f02b7b0:	8fa201f0 */ 	lw	$v0,0x1f0($sp)
/*  f02b7b4:	8fb00024 */ 	lw	$s0,0x24($sp)
/*  f02b7b8:	8fb10028 */ 	lw	$s1,0x28($sp)
/*  f02b7bc:	8fb2002c */ 	lw	$s2,0x2c($sp)
/*  f02b7c0:	8fb30030 */ 	lw	$s3,0x30($sp)
/*  f02b7c4:	8fb40034 */ 	lw	$s4,0x34($sp)
/*  f02b7c8:	8fb50038 */ 	lw	$s5,0x38($sp)
/*  f02b7cc:	03e00008 */ 	jr	$ra
/*  f02b7d0:	27bd01f0 */ 	addiu	$sp,$sp,0x1f0
);
#endif

GLOBAL_ASM(
glabel func0f02b7d4
/*  f02b7d4:	27bdff90 */ 	addiu	$sp,$sp,-112
/*  f02b7d8:	afbf0054 */ 	sw	$ra,0x54($sp)
/*  f02b7dc:	afbe0050 */ 	sw	$s8,0x50($sp)
/*  f02b7e0:	afb7004c */ 	sw	$s7,0x4c($sp)
/*  f02b7e4:	afb60048 */ 	sw	$s6,0x48($sp)
/*  f02b7e8:	afb50044 */ 	sw	$s5,0x44($sp)
/*  f02b7ec:	afb40040 */ 	sw	$s4,0x40($sp)
/*  f02b7f0:	afb3003c */ 	sw	$s3,0x3c($sp)
/*  f02b7f4:	afb20038 */ 	sw	$s2,0x38($sp)
/*  f02b7f8:	afb10034 */ 	sw	$s1,0x34($sp)
/*  f02b7fc:	afb00030 */ 	sw	$s0,0x30($sp)
/*  f02b800:	afa60078 */ 	sw	$a2,0x78($sp)
/*  f02b804:	afa00058 */ 	sw	$zero,0x58($sp)
/*  f02b808:	90cf0001 */ 	lbu	$t7,0x1($a2)
/*  f02b80c:	0080a025 */ 	or	$s4,$a0,$zero
/*  f02b810:	00a0a825 */ 	or	$s5,$a1,$zero
/*  f02b814:	31f80002 */ 	andi	$t8,$t7,0x2
/*  f02b818:	1300016a */ 	beqz	$t8,.L0f02bdc4
/*  f02b81c:	00e0f025 */ 	or	$s8,$a3,$zero
/*  f02b820:	90c20000 */ 	lbu	$v0,0x0($a2)
/*  f02b824:	24010003 */ 	addiu	$at,$zero,0x3
/*  f02b828:	8fb90078 */ 	lw	$t9,0x78($sp)
/*  f02b82c:	10410003 */ 	beq	$v0,$at,.L0f02b83c
/*  f02b830:	24010006 */ 	addiu	$at,$zero,0x6
/*  f02b834:	14410004 */ 	bne	$v0,$at,.L0f02b848
/*  f02b838:	8fa90078 */ 	lw	$t1,0x78($sp)
.L0f02b83c:
/*  f02b83c:	8f220004 */ 	lw	$v0,0x4($t9)
/*  f02b840:	10000007 */ 	b	.L0f02b860
/*  f02b844:	8c570020 */ 	lw	$s7,0x20($v0)
.L0f02b848:
/*  f02b848:	8d2a0004 */ 	lw	$t2,0x4($t1)
/*  f02b84c:	24050067 */ 	addiu	$a1,$zero,0x67
/*  f02b850:	8d570018 */ 	lw	$s7,0x18($t2)
/*  f02b854:	0c006a47 */ 	jal	modelGetPart
/*  f02b858:	8ee40008 */ 	lw	$a0,0x8($s7)
/*  f02b85c:	afa20058 */ 	sw	$v0,0x58($sp)
.L0f02b860:
/*  f02b860:	8eeb0008 */ 	lw	$t3,0x8($s7)
/*  f02b864:	24160730 */ 	addiu	$s6,$zero,0x730
/*  f02b868:	8d730000 */ 	lw	$s3,0x0($t3)
/*  f02b86c:	5260013c */ 	beqzl	$s3,.L0f02bd60
/*  f02b870:	8fb80058 */ 	lw	$t8,0x58($sp)
/*  f02b874:	966c0000 */ 	lhu	$t4,0x0($s3)
.L0f02b878:
/*  f02b878:	2401000a */ 	addiu	$at,$zero,0xa
/*  f02b87c:	8faf0058 */ 	lw	$t7,0x58($sp)
/*  f02b880:	318d00ff */ 	andi	$t5,$t4,0xff
/*  f02b884:	55a10125 */ 	bnel	$t5,$at,.L0f02bd1c
/*  f02b888:	8e620014 */ 	lw	$v0,0x14($s3)
/*  f02b88c:	11e00002 */ 	beqz	$t7,.L0f02b898
/*  f02b890:	00008025 */ 	or	$s0,$zero,$zero
/*  f02b894:	15f30120 */ 	bne	$t7,$s3,.L0f02bd18
.L0f02b898:
/*  f02b898:	00008825 */ 	or	$s1,$zero,$zero
/*  f02b89c:	00009025 */ 	or	$s2,$zero,$zero
/*  f02b8a0:	8fa40078 */ 	lw	$a0,0x78($sp)
/*  f02b8a4:	02602825 */ 	or	$a1,$s3,$zero
/*  f02b8a8:	02e03025 */ 	or	$a2,$s7,$zero
/*  f02b8ac:	0fc0a386 */ 	jal	func0f028e18
/*  f02b8b0:	02a03825 */ 	or	$a3,$s5,$zero
/*  f02b8b4:	3c058006 */ 	lui	$a1,%hi(var80062a8c)
/*  f02b8b8:	00404025 */ 	or	$t0,$v0,$zero
/*  f02b8bc:	8ca52a8c */ 	lw	$a1,%lo(var80062a8c)($a1)
/*  f02b8c0:	00002025 */ 	or	$a0,$zero,$zero
.L0f02b8c4:
/*  f02b8c4:	8cb80000 */ 	lw	$t8,0x0($a1)
/*  f02b8c8:	2484005c */ 	addiu	$a0,$a0,0x5c
/*  f02b8cc:	00a01825 */ 	or	$v1,$a1,$zero
/*  f02b8d0:	16b80027 */ 	bne	$s5,$t8,.L0f02b970
/*  f02b8d4:	00000000 */ 	nop
/*  f02b8d8:	8c6e0008 */ 	lw	$t6,0x8($v1)
/*  f02b8dc:	11c0001c */ 	beqz	$t6,.L0f02b950
/*  f02b8e0:	00000000 */ 	nop
/*  f02b8e4:	8c790004 */ 	lw	$t9,0x4($v1)
/*  f02b8e8:	28410020 */ 	slti	$at,$v0,0x20
/*  f02b8ec:	1679000a */ 	bne	$s3,$t9,.L0f02b918
/*  f02b8f0:	00000000 */ 	nop
/*  f02b8f4:	12000006 */ 	beqz	$s0,.L0f02b910
/*  f02b8f8:	00000000 */ 	nop
/*  f02b8fc:	8e09000c */ 	lw	$t1,0xc($s0)
/*  f02b900:	8c6a000c */ 	lw	$t2,0xc($v1)
/*  f02b904:	012a082a */ 	slt	$at,$t1,$t2
/*  f02b908:	10200019 */ 	beqz	$at,.L0f02b970
/*  f02b90c:	00000000 */ 	nop
.L0f02b910:
/*  f02b910:	10000017 */ 	b	.L0f02b970
/*  f02b914:	00608025 */ 	or	$s0,$v1,$zero
.L0f02b918:
/*  f02b918:	10200015 */ 	beqz	$at,.L0f02b970
/*  f02b91c:	00625821 */ 	addu	$t3,$v1,$v0
/*  f02b920:	816c0018 */ 	lb	$t4,0x18($t3)
/*  f02b924:	05800012 */ 	bltz	$t4,.L0f02b970
/*  f02b928:	00000000 */ 	nop
/*  f02b92c:	12400006 */ 	beqz	$s2,.L0f02b948
/*  f02b930:	00000000 */ 	nop
/*  f02b934:	8e4d000c */ 	lw	$t5,0xc($s2)
/*  f02b938:	8c6f000c */ 	lw	$t7,0xc($v1)
/*  f02b93c:	01af082a */ 	slt	$at,$t5,$t7
/*  f02b940:	1020000b */ 	beqz	$at,.L0f02b970
/*  f02b944:	00000000 */ 	nop
.L0f02b948:
/*  f02b948:	10000009 */ 	b	.L0f02b970
/*  f02b94c:	00609025 */ 	or	$s2,$v1,$zero
.L0f02b950:
/*  f02b950:	52200007 */ 	beqzl	$s1,.L0f02b970
/*  f02b954:	00608825 */ 	or	$s1,$v1,$zero
/*  f02b958:	8e38000c */ 	lw	$t8,0xc($s1)
/*  f02b95c:	8c6e000c */ 	lw	$t6,0xc($v1)
/*  f02b960:	030e082a */ 	slt	$at,$t8,$t6
/*  f02b964:	10200002 */ 	beqz	$at,.L0f02b970
/*  f02b968:	00000000 */ 	nop
/*  f02b96c:	00608825 */ 	or	$s1,$v1,$zero
.L0f02b970:
/*  f02b970:	1496ffd4 */ 	bne	$a0,$s6,.L0f02b8c4
/*  f02b974:	24a5005c */ 	addiu	$a1,$a1,92
/*  f02b978:	12000011 */ 	beqz	$s0,.L0f02b9c0
/*  f02b97c:	02802025 */ 	or	$a0,$s4,$zero
/*  f02b980:	8e190004 */ 	lw	$t9,0x4($s0)
/*  f02b984:	8e070008 */ 	lw	$a3,0x8($s0)
/*  f02b988:	240affff */ 	addiu	$t2,$zero,-1
/*  f02b98c:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f02b990:	82090010 */ 	lb	$t1,0x10($s0)
/*  f02b994:	240bffff */ 	addiu	$t3,$zero,-1
/*  f02b998:	240c00ff */ 	addiu	$t4,$zero,0xff
/*  f02b99c:	afac0020 */ 	sw	$t4,0x20($sp)
/*  f02b9a0:	afab001c */ 	sw	$t3,0x1c($sp)
/*  f02b9a4:	afaa0018 */ 	sw	$t2,0x18($sp)
/*  f02b9a8:	02002825 */ 	or	$a1,$s0,$zero
/*  f02b9ac:	02a03025 */ 	or	$a2,$s5,$zero
/*  f02b9b0:	0fc0a60f */ 	jal	func0f02983c
/*  f02b9b4:	afa90014 */ 	sw	$t1,0x14($sp)
/*  f02b9b8:	100000d7 */ 	b	.L0f02bd18
/*  f02b9bc:	0040a025 */ 	or	$s4,$v0,$zero
.L0f02b9c0:
/*  f02b9c0:	12200010 */ 	beqz	$s1,.L0f02ba04
/*  f02b9c4:	02802025 */ 	or	$a0,$s4,$zero
/*  f02b9c8:	240dffff */ 	addiu	$t5,$zero,-1
/*  f02b9cc:	240fffff */ 	addiu	$t7,$zero,-1
/*  f02b9d0:	2418ffff */ 	addiu	$t8,$zero,-1
/*  f02b9d4:	240e00ff */ 	addiu	$t6,$zero,0xff
/*  f02b9d8:	afae0020 */ 	sw	$t6,0x20($sp)
/*  f02b9dc:	afb8001c */ 	sw	$t8,0x1c($sp)
/*  f02b9e0:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f02b9e4:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f02b9e8:	02202825 */ 	or	$a1,$s1,$zero
/*  f02b9ec:	02a03025 */ 	or	$a2,$s5,$zero
/*  f02b9f0:	02e03825 */ 	or	$a3,$s7,$zero
/*  f02b9f4:	0fc0a60f */ 	jal	func0f02983c
/*  f02b9f8:	afb30010 */ 	sw	$s3,0x10($sp)
/*  f02b9fc:	100000c6 */ 	b	.L0f02bd18
/*  f02ba00:	0040a025 */ 	or	$s4,$v0,$zero
.L0f02ba04:
/*  f02ba04:	12400012 */ 	beqz	$s2,.L0f02ba50
/*  f02ba08:	8fac0080 */ 	lw	$t4,0x80($sp)
/*  f02ba0c:	2419fffe */ 	addiu	$t9,$zero,-2
/*  f02ba10:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f02ba14:	afb30010 */ 	sw	$s3,0x10($sp)
/*  f02ba18:	02481021 */ 	addu	$v0,$s2,$t0
/*  f02ba1c:	80490018 */ 	lb	$t1,0x18($v0)
/*  f02ba20:	240b00ff */ 	addiu	$t3,$zero,0xff
/*  f02ba24:	02802025 */ 	or	$a0,$s4,$zero
/*  f02ba28:	afa90018 */ 	sw	$t1,0x18($sp)
/*  f02ba2c:	904a0038 */ 	lbu	$t2,0x38($v0)
/*  f02ba30:	afab0020 */ 	sw	$t3,0x20($sp)
/*  f02ba34:	02402825 */ 	or	$a1,$s2,$zero
/*  f02ba38:	02a03025 */ 	or	$a2,$s5,$zero
/*  f02ba3c:	02e03825 */ 	or	$a3,$s7,$zero
/*  f02ba40:	0fc0a60f */ 	jal	func0f02983c
/*  f02ba44:	afaa001c */ 	sw	$t2,0x1c($sp)
/*  f02ba48:	100000b3 */ 	b	.L0f02bd18
/*  f02ba4c:	0040a025 */ 	or	$s4,$v0,$zero
.L0f02ba50:
/*  f02ba50:	1180006f */ 	beqz	$t4,.L0f02bc10
/*  f02ba54:	8fb90084 */ 	lw	$t9,0x84($sp)
/*  f02ba58:	8fad0058 */ 	lw	$t5,0x58($sp)
/*  f02ba5c:	02801025 */ 	or	$v0,$s4,$zero
/*  f02ba60:	26940008 */ 	addiu	$s4,$s4,0x8
/*  f02ba64:	11a00002 */ 	beqz	$t5,.L0f02ba70
/*  f02ba68:	3c0fe700 */ 	lui	$t7,0xe700
/*  f02ba6c:	24080013 */ 	addiu	$t0,$zero,0x13
.L0f02ba70:
/*  f02ba70:	29010014 */ 	slti	$at,$t0,0x14
/*  f02ba74:	14200002 */ 	bnez	$at,.L0f02ba80
/*  f02ba78:	26840008 */ 	addiu	$a0,$s4,0x8
/*  f02ba7c:	00004025 */ 	or	$t0,$zero,$zero
.L0f02ba80:
/*  f02ba80:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f02ba84:	ac400004 */ 	sw	$zero,0x4($v0)
/*  f02ba88:	3c18ba00 */ 	lui	$t8,0xba00
/*  f02ba8c:	37180e02 */ 	ori	$t8,$t8,0xe02
/*  f02ba90:	ae980000 */ 	sw	$t8,0x0($s4)
/*  f02ba94:	ae800004 */ 	sw	$zero,0x4($s4)
/*  f02ba98:	3c0efd10 */ 	lui	$t6,0xfd10
/*  f02ba9c:	0008c880 */ 	sll	$t9,$t0,0x2
/*  f02baa0:	3c09800a */ 	lui	$t1,%hi(var8009ccc0)
/*  f02baa4:	01394821 */ 	addu	$t1,$t1,$t9
/*  f02baa8:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*  f02baac:	8d29ccc0 */ 	lw	$t1,%lo(var8009ccc0)($t1)
/*  f02bab0:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f02bab4:	3c0af510 */ 	lui	$t2,0xf510
/*  f02bab8:	3c0b0705 */ 	lui	$t3,0x705
/*  f02babc:	ac890004 */ 	sw	$t1,0x4($a0)
/*  f02bac0:	acaa0000 */ 	sw	$t2,0x0($a1)
/*  f02bac4:	356b0140 */ 	ori	$t3,$t3,0x140
/*  f02bac8:	acab0004 */ 	sw	$t3,0x4($a1)
/*  f02bacc:	24a60008 */ 	addiu	$a2,$a1,0x8
/*  f02bad0:	24c20008 */ 	addiu	$v0,$a2,0x8
/*  f02bad4:	3c0ce600 */ 	lui	$t4,0xe600
/*  f02bad8:	accc0000 */ 	sw	$t4,0x0($a2)
/*  f02badc:	acc00004 */ 	sw	$zero,0x4($a2)
/*  f02bae0:	3c0f070f */ 	lui	$t7,0x70f
/*  f02bae4:	3c0df300 */ 	lui	$t5,0xf300
/*  f02bae8:	ac4d0000 */ 	sw	$t5,0x0($v0)
/*  f02baec:	35eff200 */ 	ori	$t7,$t7,0xf200
/*  f02baf0:	24430008 */ 	addiu	$v1,$v0,0x8
/*  f02baf4:	ac4f0004 */ 	sw	$t7,0x4($v0)
/*  f02baf8:	24740008 */ 	addiu	$s4,$v1,0x8
/*  f02bafc:	3c0ef510 */ 	lui	$t6,0xf510
/*  f02bb00:	3c18e700 */ 	lui	$t8,0xe700
/*  f02bb04:	ac780000 */ 	sw	$t8,0x0($v1)
/*  f02bb08:	35ce0800 */ 	ori	$t6,$t6,0x800
/*  f02bb0c:	02802025 */ 	or	$a0,$s4,$zero
/*  f02bb10:	ac600004 */ 	sw	$zero,0x4($v1)
/*  f02bb14:	3c190005 */ 	lui	$t9,0x5
/*  f02bb18:	37390140 */ 	ori	$t9,$t9,0x140
/*  f02bb1c:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*  f02bb20:	26850008 */ 	addiu	$a1,$s4,0x8
/*  f02bb24:	ac990004 */ 	sw	$t9,0x4($a0)
/*  f02bb28:	3c0a0003 */ 	lui	$t2,0x3
/*  f02bb2c:	3c09f200 */ 	lui	$t1,0xf200
/*  f02bb30:	aca90000 */ 	sw	$t1,0x0($a1)
/*  f02bb34:	354ac03c */ 	ori	$t2,$t2,0xc03c
/*  f02bb38:	acaa0004 */ 	sw	$t2,0x4($a1)
/*  f02bb3c:	24a70008 */ 	addiu	$a3,$a1,0x8
/*  f02bb40:	3c0bba00 */ 	lui	$t3,0xba00
/*  f02bb44:	356b1402 */ 	ori	$t3,$t3,0x1402
/*  f02bb48:	aceb0000 */ 	sw	$t3,0x0($a3)
/*  f02bb4c:	24e20008 */ 	addiu	$v0,$a3,0x8
/*  f02bb50:	ace00004 */ 	sw	$zero,0x4($a3)
/*  f02bb54:	3c0d0050 */ 	lui	$t5,0x50
/*  f02bb58:	3c0cb900 */ 	lui	$t4,0xb900
/*  f02bb5c:	358c031d */ 	ori	$t4,$t4,0x31d
/*  f02bb60:	35ad49d8 */ 	ori	$t5,$t5,0x49d8
/*  f02bb64:	24430008 */ 	addiu	$v1,$v0,0x8
/*  f02bb68:	ac4d0004 */ 	sw	$t5,0x4($v0)
/*  f02bb6c:	ac4c0000 */ 	sw	$t4,0x0($v0)
/*  f02bb70:	3c0ffc12 */ 	lui	$t7,0xfc12
/*  f02bb74:	35ef7e24 */ 	ori	$t7,$t7,0x7e24
/*  f02bb78:	24640008 */ 	addiu	$a0,$v1,0x8
/*  f02bb7c:	2418f9fc */ 	addiu	$t8,$zero,-1540
/*  f02bb80:	3c0ebb00 */ 	lui	$t6,0xbb00
/*  f02bb84:	ac780004 */ 	sw	$t8,0x4($v1)
/*  f02bb88:	ac6f0000 */ 	sw	$t7,0x0($v1)
/*  f02bb8c:	35ce0001 */ 	ori	$t6,$t6,0x1
/*  f02bb90:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*  f02bb94:	24940008 */ 	addiu	$s4,$a0,0x8
/*  f02bb98:	2419ffff */ 	addiu	$t9,$zero,-1
/*  f02bb9c:	ac990004 */ 	sw	$t9,0x4($a0)
/*  f02bba0:	02802825 */ 	or	$a1,$s4,$zero
/*  f02bba4:	3c09ba00 */ 	lui	$t1,0xba00
/*  f02bba8:	35290c02 */ 	ori	$t1,$t1,0xc02
/*  f02bbac:	240a2000 */ 	addiu	$t2,$zero,0x2000
/*  f02bbb0:	acaa0004 */ 	sw	$t2,0x4($a1)
/*  f02bbb4:	aca90000 */ 	sw	$t1,0x0($a1)
/*  f02bbb8:	26880008 */ 	addiu	$t0,$s4,0x8
/*  f02bbbc:	3c0bba00 */ 	lui	$t3,0xba00
/*  f02bbc0:	356b0602 */ 	ori	$t3,$t3,0x602
/*  f02bbc4:	240c0040 */ 	addiu	$t4,$zero,0x40
/*  f02bbc8:	ad0c0004 */ 	sw	$t4,0x4($t0)
/*  f02bbcc:	ad0b0000 */ 	sw	$t3,0x0($t0)
/*  f02bbd0:	240e00ff */ 	addiu	$t6,$zero,0xff
/*  f02bbd4:	240fffff */ 	addiu	$t7,$zero,-1
/*  f02bbd8:	2418ffff */ 	addiu	$t8,$zero,-1
/*  f02bbdc:	240dfff9 */ 	addiu	$t5,$zero,-7
/*  f02bbe0:	25040008 */ 	addiu	$a0,$t0,0x8
/*  f02bbe4:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f02bbe8:	afb8001c */ 	sw	$t8,0x1c($sp)
/*  f02bbec:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f02bbf0:	afae0020 */ 	sw	$t6,0x20($sp)
/*  f02bbf4:	afb30010 */ 	sw	$s3,0x10($sp)
/*  f02bbf8:	00002825 */ 	or	$a1,$zero,$zero
/*  f02bbfc:	02e03825 */ 	or	$a3,$s7,$zero
/*  f02bc00:	0fc0a60f */ 	jal	func0f02983c
/*  f02bc04:	02a03025 */ 	or	$a2,$s5,$zero
/*  f02bc08:	10000043 */ 	b	.L0f02bd18
/*  f02bc0c:	0040a025 */ 	or	$s4,$v0,$zero
.L0f02bc10:
/*  f02bc10:	14590010 */ 	bne	$v0,$t9,.L0f02bc54
/*  f02bc14:	8fac0088 */ 	lw	$t4,0x88($sp)
/*  f02bc18:	2409fffd */ 	addiu	$t1,$zero,-3
/*  f02bc1c:	240affff */ 	addiu	$t2,$zero,-1
/*  f02bc20:	240bffff */ 	addiu	$t3,$zero,-1
/*  f02bc24:	afab001c */ 	sw	$t3,0x1c($sp)
/*  f02bc28:	afaa0018 */ 	sw	$t2,0x18($sp)
/*  f02bc2c:	afa90014 */ 	sw	$t1,0x14($sp)
/*  f02bc30:	02802025 */ 	or	$a0,$s4,$zero
/*  f02bc34:	00002825 */ 	or	$a1,$zero,$zero
/*  f02bc38:	02a03025 */ 	or	$a2,$s5,$zero
/*  f02bc3c:	02e03825 */ 	or	$a3,$s7,$zero
/*  f02bc40:	afb30010 */ 	sw	$s3,0x10($sp)
/*  f02bc44:	0fc0a60f */ 	jal	func0f02983c
/*  f02bc48:	afbe0020 */ 	sw	$s8,0x20($sp)
/*  f02bc4c:	10000032 */ 	b	.L0f02bd18
/*  f02bc50:	0040a025 */ 	or	$s4,$v0,$zero
.L0f02bc54:
/*  f02bc54:	144c0010 */ 	bne	$v0,$t4,.L0f02bc98
/*  f02bc58:	8fae008c */ 	lw	$t6,0x8c($sp)
/*  f02bc5c:	240dfffc */ 	addiu	$t5,$zero,-4
/*  f02bc60:	240fffff */ 	addiu	$t7,$zero,-1
/*  f02bc64:	2418ffff */ 	addiu	$t8,$zero,-1
/*  f02bc68:	afb8001c */ 	sw	$t8,0x1c($sp)
/*  f02bc6c:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f02bc70:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f02bc74:	02802025 */ 	or	$a0,$s4,$zero
/*  f02bc78:	00002825 */ 	or	$a1,$zero,$zero
/*  f02bc7c:	02a03025 */ 	or	$a2,$s5,$zero
/*  f02bc80:	02e03825 */ 	or	$a3,$s7,$zero
/*  f02bc84:	afb30010 */ 	sw	$s3,0x10($sp)
/*  f02bc88:	0fc0a60f */ 	jal	func0f02983c
/*  f02bc8c:	afbe0020 */ 	sw	$s8,0x20($sp)
/*  f02bc90:	10000021 */ 	b	.L0f02bd18
/*  f02bc94:	0040a025 */ 	or	$s4,$v0,$zero
.L0f02bc98:
/*  f02bc98:	144e0010 */ 	bne	$v0,$t6,.L0f02bcdc
/*  f02bc9c:	8fab0090 */ 	lw	$t3,0x90($sp)
/*  f02bca0:	2419fffb */ 	addiu	$t9,$zero,-5
/*  f02bca4:	2409ffff */ 	addiu	$t1,$zero,-1
/*  f02bca8:	240affff */ 	addiu	$t2,$zero,-1
/*  f02bcac:	afaa001c */ 	sw	$t2,0x1c($sp)
/*  f02bcb0:	afa90018 */ 	sw	$t1,0x18($sp)
/*  f02bcb4:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f02bcb8:	02802025 */ 	or	$a0,$s4,$zero
/*  f02bcbc:	00002825 */ 	or	$a1,$zero,$zero
/*  f02bcc0:	02a03025 */ 	or	$a2,$s5,$zero
/*  f02bcc4:	02e03825 */ 	or	$a3,$s7,$zero
/*  f02bcc8:	afb30010 */ 	sw	$s3,0x10($sp)
/*  f02bccc:	0fc0a60f */ 	jal	func0f02983c
/*  f02bcd0:	afbe0020 */ 	sw	$s8,0x20($sp)
/*  f02bcd4:	10000010 */ 	b	.L0f02bd18
/*  f02bcd8:	0040a025 */ 	or	$s4,$v0,$zero
.L0f02bcdc:
/*  f02bcdc:	144b000e */ 	bne	$v0,$t3,.L0f02bd18
/*  f02bce0:	02802025 */ 	or	$a0,$s4,$zero
/*  f02bce4:	240cfffa */ 	addiu	$t4,$zero,-6
/*  f02bce8:	240dffff */ 	addiu	$t5,$zero,-1
/*  f02bcec:	240fffff */ 	addiu	$t7,$zero,-1
/*  f02bcf0:	afaf001c */ 	sw	$t7,0x1c($sp)
/*  f02bcf4:	afad0018 */ 	sw	$t5,0x18($sp)
/*  f02bcf8:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f02bcfc:	00002825 */ 	or	$a1,$zero,$zero
/*  f02bd00:	02a03025 */ 	or	$a2,$s5,$zero
/*  f02bd04:	02e03825 */ 	or	$a3,$s7,$zero
/*  f02bd08:	afb30010 */ 	sw	$s3,0x10($sp)
/*  f02bd0c:	0fc0a60f */ 	jal	func0f02983c
/*  f02bd10:	afbe0020 */ 	sw	$s8,0x20($sp)
/*  f02bd14:	0040a025 */ 	or	$s4,$v0,$zero
.L0f02bd18:
/*  f02bd18:	8e620014 */ 	lw	$v0,0x14($s3)
.L0f02bd1c:
/*  f02bd1c:	10400003 */ 	beqz	$v0,.L0f02bd2c
/*  f02bd20:	00000000 */ 	nop
/*  f02bd24:	1000000b */ 	b	.L0f02bd54
/*  f02bd28:	00409825 */ 	or	$s3,$v0,$zero
.L0f02bd2c:
/*  f02bd2c:	12600009 */ 	beqz	$s3,.L0f02bd54
/*  f02bd30:	00000000 */ 	nop
/*  f02bd34:	8e62000c */ 	lw	$v0,0xc($s3)
.L0f02bd38:
/*  f02bd38:	50400004 */ 	beqzl	$v0,.L0f02bd4c
/*  f02bd3c:	8e730008 */ 	lw	$s3,0x8($s3)
/*  f02bd40:	10000004 */ 	b	.L0f02bd54
/*  f02bd44:	00409825 */ 	or	$s3,$v0,$zero
/*  f02bd48:	8e730008 */ 	lw	$s3,0x8($s3)
.L0f02bd4c:
/*  f02bd4c:	5660fffa */ 	bnezl	$s3,.L0f02bd38
/*  f02bd50:	8e62000c */ 	lw	$v0,0xc($s3)
.L0f02bd54:
/*  f02bd54:	5660fec8 */ 	bnezl	$s3,.L0f02b878
/*  f02bd58:	966c0000 */ 	lhu	$t4,0x0($s3)
/*  f02bd5c:	8fb80058 */ 	lw	$t8,0x58($sp)
.L0f02bd60:
/*  f02bd60:	8fae0078 */ 	lw	$t6,0x78($sp)
/*  f02bd64:	57000018 */ 	bnezl	$t8,.L0f02bdc8
/*  f02bd68:	8fbf0054 */ 	lw	$ra,0x54($sp)
/*  f02bd6c:	8dd0001c */ 	lw	$s0,0x1c($t6)
/*  f02bd70:	52000015 */ 	beqzl	$s0,.L0f02bdc8
/*  f02bd74:	8fbf0054 */ 	lw	$ra,0x54($sp)
/*  f02bd78:	8fb90080 */ 	lw	$t9,0x80($sp)
.L0f02bd7c:
/*  f02bd7c:	8fa90084 */ 	lw	$t1,0x84($sp)
/*  f02bd80:	8faa0088 */ 	lw	$t2,0x88($sp)
/*  f02bd84:	8fab008c */ 	lw	$t3,0x8c($sp)
/*  f02bd88:	8fac0090 */ 	lw	$t4,0x90($sp)
/*  f02bd8c:	02802025 */ 	or	$a0,$s4,$zero
/*  f02bd90:	02a02825 */ 	or	$a1,$s5,$zero
/*  f02bd94:	02003025 */ 	or	$a2,$s0,$zero
/*  f02bd98:	03c03825 */ 	or	$a3,$s8,$zero
/*  f02bd9c:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f02bda0:	afa90014 */ 	sw	$t1,0x14($sp)
/*  f02bda4:	afaa0018 */ 	sw	$t2,0x18($sp)
/*  f02bda8:	afab001c */ 	sw	$t3,0x1c($sp)
/*  f02bdac:	0fc0adf5 */ 	jal	func0f02b7d4
/*  f02bdb0:	afac0020 */ 	sw	$t4,0x20($sp)
/*  f02bdb4:	8e100020 */ 	lw	$s0,0x20($s0)
/*  f02bdb8:	0040a025 */ 	or	$s4,$v0,$zero
/*  f02bdbc:	5600ffef */ 	bnezl	$s0,.L0f02bd7c
/*  f02bdc0:	8fb90080 */ 	lw	$t9,0x80($sp)
.L0f02bdc4:
/*  f02bdc4:	8fbf0054 */ 	lw	$ra,0x54($sp)
.L0f02bdc8:
/*  f02bdc8:	02801025 */ 	or	$v0,$s4,$zero
/*  f02bdcc:	8fb40040 */ 	lw	$s4,0x40($sp)
/*  f02bdd0:	8fb00030 */ 	lw	$s0,0x30($sp)
/*  f02bdd4:	8fb10034 */ 	lw	$s1,0x34($sp)
/*  f02bdd8:	8fb20038 */ 	lw	$s2,0x38($sp)
/*  f02bddc:	8fb3003c */ 	lw	$s3,0x3c($sp)
/*  f02bde0:	8fb50044 */ 	lw	$s5,0x44($sp)
/*  f02bde4:	8fb60048 */ 	lw	$s6,0x48($sp)
/*  f02bde8:	8fb7004c */ 	lw	$s7,0x4c($sp)
/*  f02bdec:	8fbe0050 */ 	lw	$s8,0x50($sp)
/*  f02bdf0:	03e00008 */ 	jr	$ra
/*  f02bdf4:	27bd0070 */ 	addiu	$sp,$sp,0x70
);

GLOBAL_ASM(
glabel func0f02bdf8
/*  f02bdf8:	27bdfeb0 */ 	addiu	$sp,$sp,-336
/*  f02bdfc:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f02be00:	afb70038 */ 	sw	$s7,0x38($sp)
/*  f02be04:	afb60034 */ 	sw	$s6,0x34($sp)
/*  f02be08:	afb50030 */ 	sw	$s5,0x30($sp)
/*  f02be0c:	afb4002c */ 	sw	$s4,0x2c($sp)
/*  f02be10:	afb30028 */ 	sw	$s3,0x28($sp)
/*  f02be14:	afb20024 */ 	sw	$s2,0x24($sp)
/*  f02be18:	afb10020 */ 	sw	$s1,0x20($sp)
/*  f02be1c:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f02be20:	f7b40010 */ 	sdc1	$f20,0x10($sp)
/*  f02be24:	afa60158 */ 	sw	$a2,0x158($sp)
/*  f02be28:	90cf0001 */ 	lbu	$t7,0x1($a2)
/*  f02be2c:	00808825 */ 	or	$s1,$a0,$zero
/*  f02be30:	00a09025 */ 	or	$s2,$a1,$zero
/*  f02be34:	31f80002 */ 	andi	$t8,$t7,0x2
/*  f02be38:	1300021c */ 	beqz	$t8,.L0f02c6ac
/*  f02be3c:	0000b025 */ 	or	$s6,$zero,$zero
/*  f02be40:	90c20000 */ 	lbu	$v0,0x0($a2)
/*  f02be44:	24010003 */ 	addiu	$at,$zero,0x3
/*  f02be48:	8fb90158 */ 	lw	$t9,0x158($sp)
/*  f02be4c:	10410003 */ 	beq	$v0,$at,.L0f02be5c
/*  f02be50:	24010006 */ 	addiu	$at,$zero,0x6
/*  f02be54:	14410005 */ 	bne	$v0,$at,.L0f02be6c
/*  f02be58:	8fad0158 */ 	lw	$t5,0x158($sp)
.L0f02be5c:
/*  f02be5c:	8f2c0004 */ 	lw	$t4,0x4($t9)
/*  f02be60:	8d970020 */ 	lw	$s7,0x20($t4)
/*  f02be64:	10000008 */ 	b	.L0f02be88
/*  f02be68:	afb20154 */ 	sw	$s2,0x154($sp)
.L0f02be6c:
/*  f02be6c:	8daf0004 */ 	lw	$t7,0x4($t5)
/*  f02be70:	24050067 */ 	addiu	$a1,$zero,0x67
/*  f02be74:	8df70018 */ 	lw	$s7,0x18($t7)
/*  f02be78:	8ee40008 */ 	lw	$a0,0x8($s7)
/*  f02be7c:	0c006a47 */ 	jal	modelGetPart
/*  f02be80:	afb20154 */ 	sw	$s2,0x154($sp)
/*  f02be84:	0040b025 */ 	or	$s6,$v0,$zero
.L0f02be88:
/*  f02be88:	8fb80158 */ 	lw	$t8,0x158($sp)
/*  f02be8c:	8fb20154 */ 	lw	$s2,0x154($sp)
/*  f02be90:	02201025 */ 	or	$v0,$s1,$zero
/*  f02be94:	8f0e0018 */ 	lw	$t6,0x18($t8)
/*  f02be98:	3c19e700 */ 	lui	$t9,0xe700
/*  f02be9c:	3c0ced00 */ 	lui	$t4,0xed00
/*  f02bea0:	15c00083 */ 	bnez	$t6,.L0f02c0b0
/*  f02bea4:	3c0d0004 */ 	lui	$t5,0x4
/*  f02bea8:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02beac:	02201825 */ 	or	$v1,$s1,$zero
/*  f02beb0:	ac590000 */ 	sw	$t9,0x0($v0)
/*  f02beb4:	ac400004 */ 	sw	$zero,0x4($v0)
/*  f02beb8:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bebc:	35ad0040 */ 	ori	$t5,$t5,0x40
/*  f02bec0:	02202025 */ 	or	$a0,$s1,$zero
/*  f02bec4:	ac6d0004 */ 	sw	$t5,0x4($v1)
/*  f02bec8:	ac6c0000 */ 	sw	$t4,0x0($v1)
/*  f02becc:	3c0fba00 */ 	lui	$t7,0xba00
/*  f02bed0:	35ef1402 */ 	ori	$t7,$t7,0x1402
/*  f02bed4:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bed8:	3c180020 */ 	lui	$t8,0x20
/*  f02bedc:	ac980004 */ 	sw	$t8,0x4($a0)
/*  f02bee0:	ac8f0000 */ 	sw	$t7,0x0($a0)
/*  f02bee4:	02202825 */ 	or	$a1,$s1,$zero
/*  f02bee8:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02beec:	3c190500 */ 	lui	$t9,0x500
/*  f02bef0:	3c0ef510 */ 	lui	$t6,0xf510
/*  f02bef4:	acae0000 */ 	sw	$t6,0x0($a1)
/*  f02bef8:	acb90004 */ 	sw	$t9,0x4($a1)
/*  f02befc:	02203025 */ 	or	$a2,$s1,$zero
/*  f02bf00:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bf04:	3c0cf510 */ 	lui	$t4,0xf510
/*  f02bf08:	358c0080 */ 	ori	$t4,$t4,0x80
/*  f02bf0c:	3c0d0400 */ 	lui	$t5,0x400
/*  f02bf10:	02201025 */ 	or	$v0,$s1,$zero
/*  f02bf14:	accd0004 */ 	sw	$t5,0x4($a2)
/*  f02bf18:	accc0000 */ 	sw	$t4,0x0($a2)
/*  f02bf1c:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bf20:	3c0ff511 */ 	lui	$t7,0xf511
/*  f02bf24:	35ef4000 */ 	ori	$t7,$t7,0x4000
/*  f02bf28:	02201825 */ 	or	$v1,$s1,$zero
/*  f02bf2c:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f02bf30:	ac400004 */ 	sw	$zero,0x4($v0)
/*  f02bf34:	3c0e0100 */ 	lui	$t6,0x100
/*  f02bf38:	3c18f589 */ 	lui	$t8,0xf589
/*  f02bf3c:	37184080 */ 	ori	$t8,$t8,0x4080
/*  f02bf40:	35ce000f */ 	ori	$t6,$t6,0xf
/*  f02bf44:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bf48:	ac6e0004 */ 	sw	$t6,0x4($v1)
/*  f02bf4c:	ac780000 */ 	sw	$t8,0x0($v1)
/*  f02bf50:	02202025 */ 	or	$a0,$s1,$zero
/*  f02bf54:	3c19bb00 */ 	lui	$t9,0xbb00
/*  f02bf58:	2407ffff */ 	addiu	$a3,$zero,-1
/*  f02bf5c:	37390001 */ 	ori	$t9,$t9,0x1
/*  f02bf60:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bf64:	ac990000 */ 	sw	$t9,0x0($a0)
/*  f02bf68:	ac870004 */ 	sw	$a3,0x4($a0)
/*  f02bf6c:	02202825 */ 	or	$a1,$s1,$zero
/*  f02bf70:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bf74:	3c0cfb00 */ 	lui	$t4,0xfb00
/*  f02bf78:	acac0000 */ 	sw	$t4,0x0($a1)
/*  f02bf7c:	02203025 */ 	or	$a2,$s1,$zero
/*  f02bf80:	aca70004 */ 	sw	$a3,0x4($a1)
/*  f02bf84:	3c0dfa00 */ 	lui	$t5,0xfa00
/*  f02bf88:	accd0000 */ 	sw	$t5,0x0($a2)
/*  f02bf8c:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bf90:	acc70004 */ 	sw	$a3,0x4($a2)
/*  f02bf94:	02201025 */ 	or	$v0,$s1,$zero
/*  f02bf98:	3c0fb900 */ 	lui	$t7,0xb900
/*  f02bf9c:	afb20154 */ 	sw	$s2,0x154($sp)
/*  f02bfa0:	35ef031d */ 	ori	$t7,$t7,0x31d
/*  f02bfa4:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bfa8:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f02bfac:	02201825 */ 	or	$v1,$s1,$zero
/*  f02bfb0:	ac400004 */ 	sw	$zero,0x4($v0)
/*  f02bfb4:	3c18fcff */ 	lui	$t8,0xfcff
/*  f02bfb8:	3c0efffc */ 	lui	$t6,0xfffc
/*  f02bfbc:	35cef279 */ 	ori	$t6,$t6,0xf279
/*  f02bfc0:	3718ffff */ 	ori	$t8,$t8,0xffff
/*  f02bfc4:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bfc8:	ac780000 */ 	sw	$t8,0x0($v1)
/*  f02bfcc:	ac6e0004 */ 	sw	$t6,0x4($v1)
/*  f02bfd0:	02202025 */ 	or	$a0,$s1,$zero
/*  f02bfd4:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bfd8:	3c19ba00 */ 	lui	$t9,0xba00
/*  f02bfdc:	37390c02 */ 	ori	$t9,$t9,0xc02
/*  f02bfe0:	02202825 */ 	or	$a1,$s1,$zero
/*  f02bfe4:	ac990000 */ 	sw	$t9,0x0($a0)
/*  f02bfe8:	ac800004 */ 	sw	$zero,0x4($a0)
/*  f02bfec:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02bff0:	3c0cba00 */ 	lui	$t4,0xba00
/*  f02bff4:	358c1301 */ 	ori	$t4,$t4,0x1301
/*  f02bff8:	02203025 */ 	or	$a2,$s1,$zero
/*  f02bffc:	acac0000 */ 	sw	$t4,0x0($a1)
/*  f02c000:	aca00004 */ 	sw	$zero,0x4($a1)
/*  f02c004:	3c0dba00 */ 	lui	$t5,0xba00
/*  f02c008:	35ad0602 */ 	ori	$t5,$t5,0x602
/*  f02c00c:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c010:	240f00c0 */ 	addiu	$t7,$zero,0xc0
/*  f02c014:	accf0004 */ 	sw	$t7,0x4($a2)
/*  f02c018:	accd0000 */ 	sw	$t5,0x0($a2)
/*  f02c01c:	02201025 */ 	or	$v0,$s1,$zero
/*  f02c020:	3c18ba00 */ 	lui	$t8,0xba00
/*  f02c024:	37180402 */ 	ori	$t8,$t8,0x402
/*  f02c028:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c02c:	240e0030 */ 	addiu	$t6,$zero,0x30
/*  f02c030:	ac4e0004 */ 	sw	$t6,0x4($v0)
/*  f02c034:	ac580000 */ 	sw	$t8,0x0($v0)
/*  f02c038:	02201825 */ 	or	$v1,$s1,$zero
/*  f02c03c:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c040:	3c19ba00 */ 	lui	$t9,0xba00
/*  f02c044:	37391001 */ 	ori	$t9,$t9,0x1001
/*  f02c048:	02202025 */ 	or	$a0,$s1,$zero
/*  f02c04c:	ac790000 */ 	sw	$t9,0x0($v1)
/*  f02c050:	ac600004 */ 	sw	$zero,0x4($v1)
/*  f02c054:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c058:	3c0cba00 */ 	lui	$t4,0xba00
/*  f02c05c:	358c1102 */ 	ori	$t4,$t4,0x1102
/*  f02c060:	02202825 */ 	or	$a1,$s1,$zero
/*  f02c064:	ac8c0000 */ 	sw	$t4,0x0($a0)
/*  f02c068:	ac800004 */ 	sw	$zero,0x4($a0)
/*  f02c06c:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c070:	3c0dba00 */ 	lui	$t5,0xba00
/*  f02c074:	35ad0e02 */ 	ori	$t5,$t5,0xe02
/*  f02c078:	02203025 */ 	or	$a2,$s1,$zero
/*  f02c07c:	acad0000 */ 	sw	$t5,0x0($a1)
/*  f02c080:	aca00004 */ 	sw	$zero,0x4($a1)
/*  f02c084:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c088:	3c0fb900 */ 	lui	$t7,0xb900
/*  f02c08c:	35ef0002 */ 	ori	$t7,$t7,0x2
/*  f02c090:	02201025 */ 	or	$v0,$s1,$zero
/*  f02c094:	accf0000 */ 	sw	$t7,0x0($a2)
/*  f02c098:	acc00004 */ 	sw	$zero,0x4($a2)
/*  f02c09c:	3c18b600 */ 	lui	$t8,0xb600
/*  f02c0a0:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f02c0a4:	ac4e0004 */ 	sw	$t6,0x4($v0)
/*  f02c0a8:	ac580000 */ 	sw	$t8,0x0($v0)
/*  f02c0ac:	26310008 */ 	addiu	$s1,$s1,0x8
.L0f02c0b0:
/*  f02c0b0:	8ef90008 */ 	lw	$t9,0x8($s7)
/*  f02c0b4:	8fb20154 */ 	lw	$s2,0x154($sp)
/*  f02c0b8:	8f300000 */ 	lw	$s0,0x0($t9)
/*  f02c0bc:	1200010b */ 	beqz	$s0,.L0f02c4ec
/*  f02c0c0:	00000000 */ 	nop
/*  f02c0c4:	4480a000 */ 	mtc1	$zero,$f20
/*  f02c0c8:	afb20154 */ 	sw	$s2,0x154($sp)
/*  f02c0cc:	960c0000 */ 	lhu	$t4,0x0($s0)
.L0f02c0d0:
/*  f02c0d0:	2401000a */ 	addiu	$at,$zero,0xa
/*  f02c0d4:	318d00ff */ 	andi	$t5,$t4,0xff
/*  f02c0d8:	55a100f3 */ 	bnel	$t5,$at,.L0f02c4a8
/*  f02c0dc:	8e020014 */ 	lw	$v0,0x14($s0)
/*  f02c0e0:	12c00002 */ 	beqz	$s6,.L0f02c0ec
/*  f02c0e4:	8fa40158 */ 	lw	$a0,0x158($sp)
/*  f02c0e8:	161600ee */ 	bne	$s0,$s6,.L0f02c4a4
.L0f02c0ec:
/*  f02c0ec:	02002825 */ 	or	$a1,$s0,$zero
/*  f02c0f0:	02e03025 */ 	or	$a2,$s7,$zero
/*  f02c0f4:	0fc0a386 */ 	jal	func0f028e18
/*  f02c0f8:	8fa70154 */ 	lw	$a3,0x154($sp)
/*  f02c0fc:	12c00002 */ 	beqz	$s6,.L0f02c108
/*  f02c100:	0040a825 */ 	or	$s5,$v0,$zero
/*  f02c104:	24150013 */ 	addiu	$s5,$zero,0x13
.L0f02c108:
/*  f02c108:	2aa10014 */ 	slti	$at,$s5,0x14
/*  f02c10c:	502000e6 */ 	beqzl	$at,.L0f02c4a8
/*  f02c110:	8e020014 */ 	lw	$v0,0x14($s0)
/*  f02c114:	0c0069d0 */ 	jal	func0001a740
/*  f02c118:	02002025 */ 	or	$a0,$s0,$zero
/*  f02c11c:	02e02025 */ 	or	$a0,$s7,$zero
/*  f02c120:	00402825 */ 	or	$a1,$v0,$zero
/*  f02c124:	0c006973 */ 	jal	func0001a5cc
/*  f02c128:	00003025 */ 	or	$a2,$zero,$zero
/*  f02c12c:	c4440030 */ 	lwc1	$f4,0x30($v0)
/*  f02c130:	27a400d4 */ 	addiu	$a0,$sp,0xd4
/*  f02c134:	27a500cc */ 	addiu	$a1,$sp,0xcc
/*  f02c138:	e7a400d4 */ 	swc1	$f4,0xd4($sp)
/*  f02c13c:	c4460034 */ 	lwc1	$f6,0x34($v0)
/*  f02c140:	e7a600d8 */ 	swc1	$f6,0xd8($sp)
/*  f02c144:	c4480038 */ 	lwc1	$f8,0x38($v0)
/*  f02c148:	0fc2d35a */ 	jal	func0f0b4d68
/*  f02c14c:	e7a800dc */ 	swc1	$f8,0xdc($sp)
/*  f02c150:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*  f02c154:	4614503c */ 	c.lt.s	$f10,$f20
/*  f02c158:	00000000 */ 	nop
/*  f02c15c:	45000002 */ 	bc1f	.L0f02c168
/*  f02c160:	00000000 */ 	nop
/*  f02c164:	e7b400cc */ 	swc1	$f20,0xcc($sp)
.L0f02c168:
/*  f02c168:	0c002f02 */ 	jal	viGetWidth
/*  f02c16c:	00000000 */ 	nop
/*  f02c170:	44828000 */ 	mtc1	$v0,$f16
/*  f02c174:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
/*  f02c178:	468084a0 */ 	cvt.s.w	$f18,$f16
/*  f02c17c:	4604903c */ 	c.lt.s	$f18,$f4
/*  f02c180:	00000000 */ 	nop
/*  f02c184:	45020008 */ 	bc1fl	.L0f02c1a8
/*  f02c188:	c7a000d0 */ 	lwc1	$f0,0xd0($sp)
/*  f02c18c:	0c002f02 */ 	jal	viGetWidth
/*  f02c190:	00000000 */ 	nop
/*  f02c194:	44823000 */ 	mtc1	$v0,$f6
/*  f02c198:	00000000 */ 	nop
/*  f02c19c:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f02c1a0:	e7a800cc */ 	swc1	$f8,0xcc($sp)
/*  f02c1a4:	c7a000d0 */ 	lwc1	$f0,0xd0($sp)
.L0f02c1a8:
/*  f02c1a8:	4614003c */ 	c.lt.s	$f0,$f20
/*  f02c1ac:	00000000 */ 	nop
/*  f02c1b0:	45000002 */ 	bc1f	.L0f02c1bc
/*  f02c1b4:	00000000 */ 	nop
/*  f02c1b8:	e7b400d0 */ 	swc1	$f20,0xd0($sp)
.L0f02c1bc:
/*  f02c1bc:	0c002f06 */ 	jal	viGetHeight
/*  f02c1c0:	00000000 */ 	nop
/*  f02c1c4:	44825000 */ 	mtc1	$v0,$f10
/*  f02c1c8:	c7a000d0 */ 	lwc1	$f0,0xd0($sp)
/*  f02c1cc:	46805420 */ 	cvt.s.w	$f16,$f10
/*  f02c1d0:	4600803c */ 	c.lt.s	$f16,$f0
/*  f02c1d4:	00000000 */ 	nop
/*  f02c1d8:	45020007 */ 	bc1fl	.L0f02c1f8
/*  f02c1dc:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
/*  f02c1e0:	0c002f06 */ 	jal	viGetHeight
/*  f02c1e4:	00000000 */ 	nop
/*  f02c1e8:	44829000 */ 	mtc1	$v0,$f18
/*  f02c1ec:	00000000 */ 	nop
/*  f02c1f0:	46809020 */ 	cvt.s.w	$f0,$f18
/*  f02c1f4:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
.L0f02c1f8:
/*  f02c1f8:	4600020d */ 	trunc.w.s	$f8,$f0
/*  f02c1fc:	e7a000d0 */ 	swc1	$f0,0xd0($sp)
/*  f02c200:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f02c204:	44144000 */ 	mfc1	$s4,$f8
/*  f02c208:	44133000 */ 	mfc1	$s3,$f6
/*  f02c20c:	2694fff8 */ 	addiu	$s4,$s4,-8
/*  f02c210:	0c002f40 */ 	jal	viGetViewLeft
/*  f02c214:	2673fff8 */ 	addiu	$s3,$s3,-8
/*  f02c218:	0262082a */ 	slt	$at,$s3,$v0
/*  f02c21c:	10200004 */ 	beqz	$at,.L0f02c230
/*  f02c220:	00000000 */ 	nop
/*  f02c224:	0c002f40 */ 	jal	viGetViewLeft
/*  f02c228:	00000000 */ 	nop
/*  f02c22c:	00409825 */ 	or	$s3,$v0,$zero
.L0f02c230:
/*  f02c230:	0c002f40 */ 	jal	viGetViewLeft
/*  f02c234:	00000000 */ 	nop
/*  f02c238:	00029400 */ 	sll	$s2,$v0,0x10
/*  f02c23c:	00127403 */ 	sra	$t6,$s2,0x10
/*  f02c240:	0c002f22 */ 	jal	viGetViewWidth
/*  f02c244:	01c09025 */ 	or	$s2,$t6,$zero
/*  f02c248:	0052c821 */ 	addu	$t9,$v0,$s2
/*  f02c24c:	272cfff0 */ 	addiu	$t4,$t9,-16
/*  f02c250:	0193082a */ 	slt	$at,$t4,$s3
/*  f02c254:	10200009 */ 	beqz	$at,.L0f02c27c
/*  f02c258:	00000000 */ 	nop
/*  f02c25c:	0c002f40 */ 	jal	viGetViewLeft
/*  f02c260:	00000000 */ 	nop
/*  f02c264:	00029400 */ 	sll	$s2,$v0,0x10
/*  f02c268:	00126c03 */ 	sra	$t5,$s2,0x10
/*  f02c26c:	0c002f22 */ 	jal	viGetViewWidth
/*  f02c270:	01a09025 */ 	or	$s2,$t5,$zero
/*  f02c274:	00529821 */ 	addu	$s3,$v0,$s2
/*  f02c278:	2673fff0 */ 	addiu	$s3,$s3,-16
.L0f02c27c:
/*  f02c27c:	0c002f44 */ 	jal	viGetViewTop
/*  f02c280:	00000000 */ 	nop
/*  f02c284:	0282082a */ 	slt	$at,$s4,$v0
/*  f02c288:	10200004 */ 	beqz	$at,.L0f02c29c
/*  f02c28c:	00000000 */ 	nop
/*  f02c290:	0c002f44 */ 	jal	viGetViewTop
/*  f02c294:	00000000 */ 	nop
/*  f02c298:	0040a025 */ 	or	$s4,$v0,$zero
.L0f02c29c:
/*  f02c29c:	0c002f44 */ 	jal	viGetViewTop
/*  f02c2a0:	00000000 */ 	nop
/*  f02c2a4:	00029400 */ 	sll	$s2,$v0,0x10
/*  f02c2a8:	00127c03 */ 	sra	$t7,$s2,0x10
/*  f02c2ac:	0c002f26 */ 	jal	viGetViewHeight
/*  f02c2b0:	01e09025 */ 	or	$s2,$t7,$zero
/*  f02c2b4:	0052c021 */ 	addu	$t8,$v0,$s2
/*  f02c2b8:	270efff0 */ 	addiu	$t6,$t8,-16
/*  f02c2bc:	01d4082a */ 	slt	$at,$t6,$s4
/*  f02c2c0:	5020000a */ 	beqzl	$at,.L0f02c2ec
/*  f02c2c4:	3c0cff10 */ 	lui	$t4,0xff10
/*  f02c2c8:	0c002f44 */ 	jal	viGetViewTop
/*  f02c2cc:	00000000 */ 	nop
/*  f02c2d0:	00029400 */ 	sll	$s2,$v0,0x10
/*  f02c2d4:	0012cc03 */ 	sra	$t9,$s2,0x10
/*  f02c2d8:	0c002f26 */ 	jal	viGetViewHeight
/*  f02c2dc:	03209025 */ 	or	$s2,$t9,$zero
/*  f02c2e0:	0052a021 */ 	addu	$s4,$v0,$s2
/*  f02c2e4:	2694fff0 */ 	addiu	$s4,$s4,-16
/*  f02c2e8:	3c0cff10 */ 	lui	$t4,0xff10
.L0f02c2ec:
/*  f02c2ec:	358c000f */ 	ori	$t4,$t4,0xf
/*  f02c2f0:	02201025 */ 	or	$v0,$s1,$zero
/*  f02c2f4:	00156880 */ 	sll	$t5,$s5,0x2
/*  f02c2f8:	3c0f800a */ 	lui	$t7,%hi(var8009ccc0)
/*  f02c2fc:	01ed7821 */ 	addu	$t7,$t7,$t5
/*  f02c300:	ac4c0000 */ 	sw	$t4,0x0($v0)
/*  f02c304:	8defccc0 */ 	lw	$t7,%lo(var8009ccc0)($t7)
/*  f02c308:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c30c:	3c018000 */ 	lui	$at,0x8000
/*  f02c310:	02201825 */ 	or	$v1,$s1,$zero
/*  f02c314:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c318:	01e1c021 */ 	addu	$t8,$t7,$at
/*  f02c31c:	ac580004 */ 	sw	$t8,0x4($v0)
/*  f02c320:	3c0ee800 */ 	lui	$t6,0xe800
/*  f02c324:	02209025 */ 	or	$s2,$s1,$zero
/*  f02c328:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f02c32c:	ac600004 */ 	sw	$zero,0x4($v1)
/*  f02c330:	0c002f02 */ 	jal	viGetWidth
/*  f02c334:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c338:	2459ffff */ 	addiu	$t9,$v0,-1
/*  f02c33c:	332c0fff */ 	andi	$t4,$t9,0xfff
/*  f02c340:	3c01fd10 */ 	lui	$at,0xfd10
/*  f02c344:	01816825 */ 	or	$t5,$t4,$at
/*  f02c348:	0c002ac7 */ 	jal	viGetUnk28
/*  f02c34c:	ae4d0000 */ 	sw	$t5,0x0($s2)
/*  f02c350:	2663000f */ 	addiu	$v1,$s3,0xf
/*  f02c354:	00734823 */ 	subu	$t1,$v1,$s3
/*  f02c358:	00097840 */ 	sll	$t7,$t1,0x1
/*  f02c35c:	25e90009 */ 	addiu	$t1,$t7,0x9
/*  f02c360:	0009c0c3 */ 	sra	$t8,$t1,0x3
/*  f02c364:	330e01ff */ 	andi	$t6,$t8,0x1ff
/*  f02c368:	000eca40 */ 	sll	$t9,$t6,0x9
/*  f02c36c:	02202025 */ 	or	$a0,$s1,$zero
/*  f02c370:	3c01f510 */ 	lui	$at,0xf510
/*  f02c374:	03214825 */ 	or	$t1,$t9,$at
/*  f02c378:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c37c:	ae420004 */ 	sw	$v0,0x4($s2)
/*  f02c380:	3c0d0701 */ 	lui	$t5,0x701
/*  f02c384:	00133880 */ 	sll	$a3,$s3,0x2
/*  f02c388:	30f80fff */ 	andi	$t8,$a3,0xfff
/*  f02c38c:	35ad0040 */ 	ori	$t5,$t5,0x40
/*  f02c390:	02202825 */ 	or	$a1,$s1,$zero
/*  f02c394:	ac8d0004 */ 	sw	$t5,0x4($a0)
/*  f02c398:	00183b00 */ 	sll	$a3,$t8,0xc
/*  f02c39c:	ac890000 */ 	sw	$t1,0x0($a0)
/*  f02c3a0:	3c01f400 */ 	lui	$at,0xf400
/*  f02c3a4:	3c0fe600 */ 	lui	$t7,0xe600
/*  f02c3a8:	00144080 */ 	sll	$t0,$s4,0x2
/*  f02c3ac:	31190fff */ 	andi	$t9,$t0,0xfff
/*  f02c3b0:	acaf0000 */ 	sw	$t7,0x0($a1)
/*  f02c3b4:	00e16025 */ 	or	$t4,$a3,$at
/*  f02c3b8:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c3bc:	00035080 */ 	sll	$t2,$v1,0x2
/*  f02c3c0:	314f0fff */ 	andi	$t7,$t2,0xfff
/*  f02c3c4:	02203025 */ 	or	$a2,$s1,$zero
/*  f02c3c8:	01996825 */ 	or	$t5,$t4,$t9
/*  f02c3cc:	268b000f */ 	addiu	$t3,$s4,0xf
/*  f02c3d0:	000b7080 */ 	sll	$t6,$t3,0x2
/*  f02c3d4:	000f5300 */ 	sll	$t2,$t7,0xc
/*  f02c3d8:	3c010700 */ 	lui	$at,0x700
/*  f02c3dc:	aca00004 */ 	sw	$zero,0x4($a1)
/*  f02c3e0:	accd0000 */ 	sw	$t5,0x0($a2)
/*  f02c3e4:	01416025 */ 	or	$t4,$t2,$at
/*  f02c3e8:	31cb0fff */ 	andi	$t3,$t6,0xfff
/*  f02c3ec:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c3f0:	02201025 */ 	or	$v0,$s1,$zero
/*  f02c3f4:	018b6825 */ 	or	$t5,$t4,$t3
/*  f02c3f8:	accd0004 */ 	sw	$t5,0x4($a2)
/*  f02c3fc:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c400:	3c0fe700 */ 	lui	$t7,0xe700
/*  f02c404:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f02c408:	02201825 */ 	or	$v1,$s1,$zero
/*  f02c40c:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c410:	ac400004 */ 	sw	$zero,0x4($v0)
/*  f02c414:	3c01f200 */ 	lui	$at,0xf200
/*  f02c418:	3c180001 */ 	lui	$t8,0x1
/*  f02c41c:	37180040 */ 	ori	$t8,$t8,0x40
/*  f02c420:	00e17025 */ 	or	$t6,$a3,$at
/*  f02c424:	02202025 */ 	or	$a0,$s1,$zero
/*  f02c428:	03204025 */ 	or	$t0,$t9,$zero
/*  f02c42c:	01c8c825 */ 	or	$t9,$t6,$t0
/*  f02c430:	ac780004 */ 	sw	$t8,0x4($v1)
/*  f02c434:	ac690000 */ 	sw	$t1,0x0($v1)
/*  f02c438:	ac990000 */ 	sw	$t9,0x0($a0)
/*  f02c43c:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c440:	014b6025 */ 	or	$t4,$t2,$t3
/*  f02c444:	ac8c0004 */ 	sw	$t4,0x4($a0)
/*  f02c448:	02202825 */ 	or	$a1,$s1,$zero
/*  f02c44c:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c450:	3c0de700 */ 	lui	$t5,0xe700
/*  f02c454:	02201025 */ 	or	$v0,$s1,$zero
/*  f02c458:	acad0000 */ 	sw	$t5,0x0($a1)
/*  f02c45c:	aca00004 */ 	sw	$zero,0x4($a1)
/*  f02c460:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c464:	3c0fe403 */ 	lui	$t7,0xe403
/*  f02c468:	35efc03c */ 	ori	$t7,$t7,0xc03c
/*  f02c46c:	02201825 */ 	or	$v1,$s1,$zero
/*  f02c470:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c474:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f02c478:	ac400004 */ 	sw	$zero,0x4($v0)
/*  f02c47c:	02202025 */ 	or	$a0,$s1,$zero
/*  f02c480:	3c18b400 */ 	lui	$t8,0xb400
/*  f02c484:	ac780000 */ 	sw	$t8,0x0($v1)
/*  f02c488:	ac600004 */ 	sw	$zero,0x4($v1)
/*  f02c48c:	3c191000 */ 	lui	$t9,0x1000
/*  f02c490:	37390400 */ 	ori	$t9,$t9,0x400
/*  f02c494:	3c0eb300 */ 	lui	$t6,0xb300
/*  f02c498:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*  f02c49c:	ac990004 */ 	sw	$t9,0x4($a0)
/*  f02c4a0:	26310008 */ 	addiu	$s1,$s1,0x8
.L0f02c4a4:
/*  f02c4a4:	8e020014 */ 	lw	$v0,0x14($s0)
.L0f02c4a8:
/*  f02c4a8:	10400003 */ 	beqz	$v0,.L0f02c4b8
/*  f02c4ac:	00000000 */ 	nop
/*  f02c4b0:	1000000b */ 	b	.L0f02c4e0
/*  f02c4b4:	00408025 */ 	or	$s0,$v0,$zero
.L0f02c4b8:
/*  f02c4b8:	12000009 */ 	beqz	$s0,.L0f02c4e0
/*  f02c4bc:	00000000 */ 	nop
/*  f02c4c0:	8e02000c */ 	lw	$v0,0xc($s0)
.L0f02c4c4:
/*  f02c4c4:	50400004 */ 	beqzl	$v0,.L0f02c4d8
/*  f02c4c8:	8e100008 */ 	lw	$s0,0x8($s0)
/*  f02c4cc:	10000004 */ 	b	.L0f02c4e0
/*  f02c4d0:	00408025 */ 	or	$s0,$v0,$zero
/*  f02c4d4:	8e100008 */ 	lw	$s0,0x8($s0)
.L0f02c4d8:
/*  f02c4d8:	5600fffa */ 	bnezl	$s0,.L0f02c4c4
/*  f02c4dc:	8e02000c */ 	lw	$v0,0xc($s0)
.L0f02c4e0:
/*  f02c4e0:	5600fefb */ 	bnezl	$s0,.L0f02c0d0
/*  f02c4e4:	960c0000 */ 	lhu	$t4,0x0($s0)
/*  f02c4e8:	8fb20154 */ 	lw	$s2,0x154($sp)
.L0f02c4ec:
/*  f02c4ec:	16c0000d */ 	bnez	$s6,.L0f02c524
/*  f02c4f0:	8fac0158 */ 	lw	$t4,0x158($sp)
/*  f02c4f4:	8d90001c */ 	lw	$s0,0x1c($t4)
/*  f02c4f8:	5200000b */ 	beqzl	$s0,.L0f02c528
/*  f02c4fc:	8fad0158 */ 	lw	$t5,0x158($sp)
/*  f02c500:	afb20154 */ 	sw	$s2,0x154($sp)
/*  f02c504:	8fa50154 */ 	lw	$a1,0x154($sp)
.L0f02c508:
/*  f02c508:	02202025 */ 	or	$a0,$s1,$zero
/*  f02c50c:	0fc0af7e */ 	jal	func0f02bdf8
/*  f02c510:	02003025 */ 	or	$a2,$s0,$zero
/*  f02c514:	8e100020 */ 	lw	$s0,0x20($s0)
/*  f02c518:	00408825 */ 	or	$s1,$v0,$zero
/*  f02c51c:	5600fffa */ 	bnezl	$s0,.L0f02c508
/*  f02c520:	8fa50154 */ 	lw	$a1,0x154($sp)
.L0f02c524:
/*  f02c524:	8fad0158 */ 	lw	$t5,0x158($sp)
.L0f02c528:
/*  f02c528:	02201025 */ 	or	$v0,$s1,$zero
/*  f02c52c:	3c18e700 */ 	lui	$t8,0xe700
/*  f02c530:	8daf0018 */ 	lw	$t7,0x18($t5)
/*  f02c534:	3c0ee600 */ 	lui	$t6,0xe600
/*  f02c538:	3c19e800 */ 	lui	$t9,0xe800
/*  f02c53c:	55e0005c */ 	bnezl	$t7,.L0f02c6b0
/*  f02c540:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f02c544:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c548:	02201825 */ 	or	$v1,$s1,$zero
/*  f02c54c:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c550:	ac580000 */ 	sw	$t8,0x0($v0)
/*  f02c554:	ac400004 */ 	sw	$zero,0x4($v0)
/*  f02c558:	02202025 */ 	or	$a0,$s1,$zero
/*  f02c55c:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c560:	ac600004 */ 	sw	$zero,0x4($v1)
/*  f02c564:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f02c568:	02208025 */ 	or	$s0,$s1,$zero
/*  f02c56c:	ac800004 */ 	sw	$zero,0x4($a0)
/*  f02c570:	ac990000 */ 	sw	$t9,0x0($a0)
/*  f02c574:	0c002ef1 */ 	jal	viGetBufX
/*  f02c578:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c57c:	244cffff */ 	addiu	$t4,$v0,-1
/*  f02c580:	318d0fff */ 	andi	$t5,$t4,0xfff
/*  f02c584:	3c01ff10 */ 	lui	$at,0xff10
/*  f02c588:	01a17825 */ 	or	$t7,$t5,$at
/*  f02c58c:	0c002ac7 */ 	jal	viGetUnk28
/*  f02c590:	ae0f0000 */ 	sw	$t7,0x0($s0)
/*  f02c594:	3c018000 */ 	lui	$at,0x8000
/*  f02c598:	0041c021 */ 	addu	$t8,$v0,$at
/*  f02c59c:	ae180004 */ 	sw	$t8,0x4($s0)
/*  f02c5a0:	02209825 */ 	or	$s3,$s1,$zero
/*  f02c5a4:	3c0eed00 */ 	lui	$t6,0xed00
/*  f02c5a8:	ae6e0000 */ 	sw	$t6,0x0($s3)
/*  f02c5ac:	0c002f02 */ 	jal	viGetWidth
/*  f02c5b0:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c5b4:	00029400 */ 	sll	$s2,$v0,0x10
/*  f02c5b8:	0012cc03 */ 	sra	$t9,$s2,0x10
/*  f02c5bc:	0c002f06 */ 	jal	viGetHeight
/*  f02c5c0:	03209025 */ 	or	$s2,$t9,$zero
/*  f02c5c4:	44825000 */ 	mtc1	$v0,$f10
/*  f02c5c8:	44923000 */ 	mtc1	$s2,$f6
/*  f02c5cc:	3c014080 */ 	lui	$at,0x4080
/*  f02c5d0:	46805420 */ 	cvt.s.w	$f16,$f10
/*  f02c5d4:	44810000 */ 	mtc1	$at,$f0
/*  f02c5d8:	02201825 */ 	or	$v1,$s1,$zero
/*  f02c5dc:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c5e0:	3c18ba00 */ 	lui	$t8,0xba00
/*  f02c5e4:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f02c5e8:	46008482 */ 	mul.s	$f18,$f16,$f0
/*  f02c5ec:	37181402 */ 	ori	$t8,$t8,0x1402
/*  f02c5f0:	02202025 */ 	or	$a0,$s1,$zero
/*  f02c5f4:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c5f8:	02202825 */ 	or	$a1,$s1,$zero
/*  f02c5fc:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f02c600:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c604:	02203025 */ 	or	$a2,$s1,$zero
/*  f02c608:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c60c:	02203825 */ 	or	$a3,$s1,$zero
/*  f02c610:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c614:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f02c618:	02201025 */ 	or	$v0,$s1,$zero
/*  f02c61c:	26310008 */ 	addiu	$s1,$s1,0x8
/*  f02c620:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f02c624:	440d2000 */ 	mfc1	$t5,$f4
/*  f02c628:	440e8000 */ 	mfc1	$t6,$f16
/*  f02c62c:	31af0fff */ 	andi	$t7,$t5,0xfff
/*  f02c630:	31d90fff */ 	andi	$t9,$t6,0xfff
/*  f02c634:	00196300 */ 	sll	$t4,$t9,0xc
/*  f02c638:	01ec6825 */ 	or	$t5,$t7,$t4
/*  f02c63c:	ae6d0004 */ 	sw	$t5,0x4($s3)
/*  f02c640:	ac600004 */ 	sw	$zero,0x4($v1)
/*  f02c644:	ac780000 */ 	sw	$t8,0x0($v1)
/*  f02c648:	3c190055 */ 	lui	$t9,0x55
/*  f02c64c:	3c0eb900 */ 	lui	$t6,0xb900
/*  f02c650:	35ce031d */ 	ori	$t6,$t6,0x31d
/*  f02c654:	37392078 */ 	ori	$t9,$t9,0x2078
/*  f02c658:	ac990004 */ 	sw	$t9,0x4($a0)
/*  f02c65c:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*  f02c660:	3c0ffc12 */ 	lui	$t7,0xfc12
/*  f02c664:	35ef7e24 */ 	ori	$t7,$t7,0x7e24
/*  f02c668:	240cf9fc */ 	addiu	$t4,$zero,-1540
/*  f02c66c:	acac0004 */ 	sw	$t4,0x4($a1)
/*  f02c670:	acaf0000 */ 	sw	$t7,0x0($a1)
/*  f02c674:	3c0dba00 */ 	lui	$t5,0xba00
/*  f02c678:	35ad0c02 */ 	ori	$t5,$t5,0xc02
/*  f02c67c:	24182000 */ 	addiu	$t8,$zero,0x2000
/*  f02c680:	acd80004 */ 	sw	$t8,0x4($a2)
/*  f02c684:	accd0000 */ 	sw	$t5,0x0($a2)
/*  f02c688:	3c0eba00 */ 	lui	$t6,0xba00
/*  f02c68c:	35ce1301 */ 	ori	$t6,$t6,0x1301
/*  f02c690:	3c190008 */ 	lui	$t9,0x8
/*  f02c694:	acf90004 */ 	sw	$t9,0x4($a3)
/*  f02c698:	acee0000 */ 	sw	$t6,0x0($a3)
/*  f02c69c:	3c0fb700 */ 	lui	$t7,0xb700
/*  f02c6a0:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f02c6a4:	ac4c0004 */ 	sw	$t4,0x4($v0)
/*  f02c6a8:	ac4f0000 */ 	sw	$t7,0x0($v0)
.L0f02c6ac:
/*  f02c6ac:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f02c6b0:
/*  f02c6b0:	02201025 */ 	or	$v0,$s1,$zero
/*  f02c6b4:	8fb10020 */ 	lw	$s1,0x20($sp)
/*  f02c6b8:	d7b40010 */ 	ldc1	$f20,0x10($sp)
/*  f02c6bc:	8fb0001c */ 	lw	$s0,0x1c($sp)
/*  f02c6c0:	8fb20024 */ 	lw	$s2,0x24($sp)
/*  f02c6c4:	8fb30028 */ 	lw	$s3,0x28($sp)
/*  f02c6c8:	8fb4002c */ 	lw	$s4,0x2c($sp)
/*  f02c6cc:	8fb50030 */ 	lw	$s5,0x30($sp)
/*  f02c6d0:	8fb60034 */ 	lw	$s6,0x34($sp)
/*  f02c6d4:	8fb70038 */ 	lw	$s7,0x38($sp)
/*  f02c6d8:	03e00008 */ 	jr	$ra
/*  f02c6dc:	27bd0150 */ 	addiu	$sp,$sp,0x150
);

Gfx *chrRenderShield(Gfx *gdl, struct chrdata *chr, u32 alpha)
{
	if (chrGetShield(chr) > 0 && g_Vars.lvupdate240 > 0) {
		chr->cmcount++;

		if (chr->cmcount > 300) {
			chr->cmcount = 0;
		}
	}

	if ((chr->hidden2 & CHRH2FLAG_0002)
			|| (chrGetShield(chr) > 0 && chr->cmcount < 10)
			|| (chr->cloakfadefrac > 0 && !chr->cloakfadefinished)) {
		if (chrGetShield(chr) > 0 && g_Vars.lvupdate240 > 0) {
			s32 numiterations = (random() % 4) + 1;
			s32 newcmnum = chr->cmnum2;
			s32 candidate;
			s8 operation = 0;
			s8 again = true;
			s32 i;

			for (i = 0; i <= numiterations; ) {
				if (operation == 0) {
					candidate = func0f02932c(chr->prop, chr->cmnum);
					operation = 1;

					if (candidate >= 0) {
						if (candidate != chr->cmnum2) {
							newcmnum = candidate;
						}

						i++;
					} else {
						again = false;
					}
				} else if (operation == 1) {
					candidate = func0f0293ec(chr->prop, chr->cmnum);

					if (candidate >= 0) {
						operation = 2;

						if (candidate != chr->cmnum2) {
							newcmnum = candidate;
						}

						i++;
					} else {
						if (again) {
							operation = 0;
						} else {
							break;
						}
					}
				} else if (operation == 2) {
					candidate = func0f0294cc(chr->prop, candidate);

					if (candidate >= 0) {
						if (candidate != chr->cmnum2) {
							newcmnum = candidate;
						}

						i++;
					} else {
						operation = 0;
					}
				}
			}

			chr->cmnum4 = chr->cmnum3;
			chr->cmnum3 = chr->cmnum2;
			chr->cmnum2 = chr->cmnum;
			chr->cmnum = newcmnum;
		}

		gSPSetGeometryMode(gdl++, G_CULL_BACK);

		gdl = func0f02b7d4(gdl, chr->prop, chr->prop, alpha,
				chr->cloakfadefrac > 0 && !chr->cloakfadefinished,
				chr->cmnum, chr->cmnum2, chr->cmnum3, chr->cmnum4);

		gSPSetGeometryMode(gdl++, G_CULL_BACK);
	}

	return gdl;
}

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0f02c9b0
.late_rodata
glabel var7f1a8984
.word 0x3c783e10
.text
/*  f02c9b0:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*  f02c9b4:	3c0e8006 */ 	lui	$t6,%hi(var80062a90)
/*  f02c9b8:	8dce2a90 */ 	lw	$t6,%lo(var80062a90)($t6)
/*  f02c9bc:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f02c9c0:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f02c9c4:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f02c9c8:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f02c9cc:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f02c9d0:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f02c9d4:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f02c9d8:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f02c9dc:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f02c9e0:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f02c9e4:	11c000a7 */ 	beqz	$t6,.L0f02cc84
/*  f02c9e8:	afa00040 */ 	sw	$zero,0x40($sp)
/*  f02c9ec:	3c1e800a */ 	lui	$s8,%hi(g_Vars)
/*  f02c9f0:	3c118006 */ 	lui	$s1,%hi(var80062a8c)
/*  f02c9f4:	26312a8c */ 	addiu	$s1,$s1,%lo(var80062a8c)
/*  f02c9f8:	27de9fc0 */ 	addiu	$s8,$s8,%lo(g_Vars)
/*  f02c9fc:	00009825 */ 	or	$s3,$zero,$zero
/*  f02ca00:	0000a025 */ 	or	$s4,$zero,$zero
/*  f02ca04:	2416ffff */ 	addiu	$s6,$zero,-1
/*  f02ca08:	2415fffd */ 	addiu	$s5,$zero,-3
.L0f02ca0c:
/*  f02ca0c:	8e230000 */ 	lw	$v1,0x0($s1)
/*  f02ca10:	00741021 */ 	addu	$v0,$v1,$s4
/*  f02ca14:	8c4f0000 */ 	lw	$t7,0x0($v0)
/*  f02ca18:	51e00097 */ 	beqzl	$t7,.L0f02cc78
/*  f02ca1c:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f02ca20:	8fd90008 */ 	lw	$t9,0x8($s8)
/*  f02ca24:	8c58000c */ 	lw	$t8,0xc($v0)
/*  f02ca28:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f02ca2c:	2728ffb0 */ 	addiu	$t0,$t9,-66
/*  f02ca30:	0308082a */ 	slt	$at,$t8,$t0
/*  f02ca34:	1420000f */ 	bnez	$at,.L0f02ca74
/*  f02ca38:	02832021 */ 	addu	$a0,$s4,$v1
/*  f02ca3c:	0fc0a5e8 */ 	jal	propGetShieldThing
/*  f02ca40:	afa90040 */ 	sw	$t1,0x40($sp)
/*  f02ca44:	8e2a0000 */ 	lw	$t2,0x0($s1)
/*  f02ca48:	c7c60044 */ 	lwc1	$f6,0x44($s8)
/*  f02ca4c:	3c017f1b */ 	lui	$at,%hi(var7f1a8984)
/*  f02ca50:	01541021 */ 	addu	$v0,$t2,$s4
/*  f02ca54:	c4420058 */ 	lwc1	$f2,0x58($v0)
/*  f02ca58:	c42a8984 */ 	lwc1	$f10,%lo(var7f1a8984)($at)
/*  f02ca5c:	46020101 */ 	sub.s	$f4,$f0,$f2
/*  f02ca60:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f02ca64:	00000000 */ 	nop
/*  f02ca68:	460a4402 */ 	mul.s	$f16,$f8,$f10
/*  f02ca6c:	46101480 */ 	add.s	$f18,$f2,$f16
/*  f02ca70:	e4520058 */ 	swc1	$f18,0x58($v0)
.L0f02ca74:
/*  f02ca74:	00009025 */ 	or	$s2,$zero,$zero
/*  f02ca78:	00135880 */ 	sll	$t3,$s3,0x2
.L0f02ca7c:
/*  f02ca7c:	01735823 */ 	subu	$t3,$t3,$s3
/*  f02ca80:	8e230000 */ 	lw	$v1,0x0($s1)
/*  f02ca84:	000b58c0 */ 	sll	$t3,$t3,0x3
/*  f02ca88:	01735823 */ 	subu	$t3,$t3,$s3
/*  f02ca8c:	000b5880 */ 	sll	$t3,$t3,0x2
/*  f02ca90:	006b6021 */ 	addu	$t4,$v1,$t3
/*  f02ca94:	01926821 */ 	addu	$t5,$t4,$s2
/*  f02ca98:	81a20018 */ 	lb	$v0,0x18($t5)
/*  f02ca9c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f02caa0:	0442005a */ 	bltzl	$v0,.L0f02cc0c
/*  f02caa4:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f02caa8:	8fcf0038 */ 	lw	$t7,0x38($s8)
/*  f02caac:	afae0040 */ 	sw	$t6,0x40($sp)
/*  f02cab0:	1c400047 */ 	bgtz	$v0,.L0f02cbd0
/*  f02cab4:	004fb821 */ 	addu	$s7,$v0,$t7
/*  f02cab8:	1ae00045 */ 	blez	$s7,.L0f02cbd0
/*  f02cabc:	0074c821 */ 	addu	$t9,$v1,$s4
/*  f02cac0:	8f240000 */ 	lw	$a0,0x0($t9)
/*  f02cac4:	0fc0a4cb */ 	jal	func0f02932c
/*  f02cac8:	02402825 */ 	or	$a1,$s2,$zero
/*  f02cacc:	04400019 */ 	bltz	$v0,.L0f02cb34
/*  f02cad0:	28410020 */ 	slti	$at,$v0,0x20
/*  f02cad4:	10200017 */ 	beqz	$at,.L0f02cb34
/*  f02cad8:	00134080 */ 	sll	$t0,$s3,0x2
/*  f02cadc:	01134023 */ 	subu	$t0,$t0,$s3
/*  f02cae0:	8e380000 */ 	lw	$t8,0x0($s1)
/*  f02cae4:	000840c0 */ 	sll	$t0,$t0,0x3
/*  f02cae8:	01134023 */ 	subu	$t0,$t0,$s3
/*  f02caec:	00084080 */ 	sll	$t0,$t0,0x2
/*  f02caf0:	03084821 */ 	addu	$t1,$t8,$t0
/*  f02caf4:	01222021 */ 	addu	$a0,$t1,$v0
/*  f02caf8:	808a0018 */ 	lb	$t2,0x18($a0)
/*  f02cafc:	00136080 */ 	sll	$t4,$s3,0x2
/*  f02cb00:	01936023 */ 	subu	$t4,$t4,$s3
/*  f02cb04:	16ca000b */ 	bne	$s6,$t2,.L0f02cb34
/*  f02cb08:	000c60c0 */ 	sll	$t4,$t4,0x3
/*  f02cb0c:	a0950018 */ 	sb	$s5,0x18($a0)
/*  f02cb10:	8e2b0000 */ 	lw	$t3,0x0($s1)
/*  f02cb14:	01936023 */ 	subu	$t4,$t4,$s3
/*  f02cb18:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f02cb1c:	016c1821 */ 	addu	$v1,$t3,$t4
/*  f02cb20:	00726821 */ 	addu	$t5,$v1,$s2
/*  f02cb24:	91ae0038 */ 	lbu	$t6,0x38($t5)
/*  f02cb28:	0062c821 */ 	addu	$t9,$v1,$v0
/*  f02cb2c:	25cf0001 */ 	addiu	$t7,$t6,0x1
/*  f02cb30:	a32f0038 */ 	sb	$t7,0x38($t9)
.L0f02cb34:
/*  f02cb34:	8e380000 */ 	lw	$t8,0x0($s1)
/*  f02cb38:	02402825 */ 	or	$a1,$s2,$zero
/*  f02cb3c:	03144021 */ 	addu	$t0,$t8,$s4
/*  f02cb40:	0fc0a4fb */ 	jal	func0f0293ec
/*  f02cb44:	8d040000 */ 	lw	$a0,0x0($t0)
/*  f02cb48:	04400021 */ 	bltz	$v0,.L0f02cbd0
/*  f02cb4c:	00408025 */ 	or	$s0,$v0,$zero
.L0f02cb50:
/*  f02cb50:	28410020 */ 	slti	$at,$v0,0x20
/*  f02cb54:	10200017 */ 	beqz	$at,.L0f02cbb4
/*  f02cb58:	00135080 */ 	sll	$t2,$s3,0x2
/*  f02cb5c:	01535023 */ 	subu	$t2,$t2,$s3
/*  f02cb60:	8e290000 */ 	lw	$t1,0x0($s1)
/*  f02cb64:	000a50c0 */ 	sll	$t2,$t2,0x3
/*  f02cb68:	01535023 */ 	subu	$t2,$t2,$s3
/*  f02cb6c:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f02cb70:	012a5821 */ 	addu	$t3,$t1,$t2
/*  f02cb74:	01622021 */ 	addu	$a0,$t3,$v0
/*  f02cb78:	808c0018 */ 	lb	$t4,0x18($a0)
/*  f02cb7c:	00137080 */ 	sll	$t6,$s3,0x2
/*  f02cb80:	01d37023 */ 	subu	$t6,$t6,$s3
/*  f02cb84:	16cc000b */ 	bne	$s6,$t4,.L0f02cbb4
/*  f02cb88:	000e70c0 */ 	sll	$t6,$t6,0x3
/*  f02cb8c:	a0950018 */ 	sb	$s5,0x18($a0)
/*  f02cb90:	8e2d0000 */ 	lw	$t5,0x0($s1)
/*  f02cb94:	01d37023 */ 	subu	$t6,$t6,$s3
/*  f02cb98:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f02cb9c:	01ae1821 */ 	addu	$v1,$t5,$t6
/*  f02cba0:	00727821 */ 	addu	$t7,$v1,$s2
/*  f02cba4:	91f90038 */ 	lbu	$t9,0x38($t7)
/*  f02cba8:	00624021 */ 	addu	$t0,$v1,$v0
/*  f02cbac:	27380001 */ 	addiu	$t8,$t9,0x1
/*  f02cbb0:	a1180038 */ 	sb	$t8,0x38($t0)
.L0f02cbb4:
/*  f02cbb4:	8e290000 */ 	lw	$t1,0x0($s1)
/*  f02cbb8:	02002825 */ 	or	$a1,$s0,$zero
/*  f02cbbc:	01345021 */ 	addu	$t2,$t1,$s4
/*  f02cbc0:	0fc0a533 */ 	jal	func0f0294cc
/*  f02cbc4:	8d440000 */ 	lw	$a0,0x0($t2)
/*  f02cbc8:	0441ffe1 */ 	bgez	$v0,.L0f02cb50
/*  f02cbcc:	00408025 */ 	or	$s0,$v0,$zero
.L0f02cbd0:
/*  f02cbd0:	00136080 */ 	sll	$t4,$s3,0x2
/*  f02cbd4:	01936023 */ 	subu	$t4,$t4,$s3
/*  f02cbd8:	8e2b0000 */ 	lw	$t3,0x0($s1)
/*  f02cbdc:	000c60c0 */ 	sll	$t4,$t4,0x3
/*  f02cbe0:	01936023 */ 	subu	$t4,$t4,$s3
/*  f02cbe4:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f02cbe8:	2ae1001e */ 	slti	$at,$s7,0x19
/*  f02cbec:	016c6821 */ 	addu	$t5,$t3,$t4
/*  f02cbf0:	10200003 */ 	beqz	$at,.L0f02cc00
/*  f02cbf4:	01b21021 */ 	addu	$v0,$t5,$s2
/*  f02cbf8:	10000003 */ 	b	.L0f02cc08
/*  f02cbfc:	a0570018 */ 	sb	$s7,0x18($v0)
.L0f02cc00:
/*  f02cc00:	240efffe */ 	addiu	$t6,$zero,-2
/*  f02cc04:	a04e0018 */ 	sb	$t6,0x18($v0)
.L0f02cc08:
/*  f02cc08:	26520001 */ 	addiu	$s2,$s2,0x1
.L0f02cc0c:
/*  f02cc0c:	2a410020 */ 	slti	$at,$s2,0x20
/*  f02cc10:	5420ff9a */ 	bnezl	$at,.L0f02ca7c
/*  f02cc14:	00135880 */ 	sll	$t3,$s3,0x2
/*  f02cc18:	00009025 */ 	or	$s2,$zero,$zero
/*  f02cc1c:	0013c880 */ 	sll	$t9,$s3,0x2
.L0f02cc20:
/*  f02cc20:	0333c823 */ 	subu	$t9,$t9,$s3
/*  f02cc24:	8e2f0000 */ 	lw	$t7,0x0($s1)
/*  f02cc28:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f02cc2c:	0333c823 */ 	subu	$t9,$t9,$s3
/*  f02cc30:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f02cc34:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02cc38:	03121021 */ 	addu	$v0,$t8,$s2
/*  f02cc3c:	80480018 */ 	lb	$t0,0x18($v0)
/*  f02cc40:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f02cc44:	24010020 */ 	addiu	$at,$zero,0x20
/*  f02cc48:	16a80002 */ 	bne	$s5,$t0,.L0f02cc54
/*  f02cc4c:	00000000 */ 	nop
/*  f02cc50:	a0400018 */ 	sb	$zero,0x18($v0)
.L0f02cc54:
/*  f02cc54:	5641fff2 */ 	bnel	$s2,$at,.L0f02cc20
/*  f02cc58:	0013c880 */ 	sll	$t9,$s3,0x2
/*  f02cc5c:	8fa90040 */ 	lw	$t1,0x40($sp)
/*  f02cc60:	55200005 */ 	bnezl	$t1,.L0f02cc78
/*  f02cc64:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f02cc68:	8e2a0000 */ 	lw	$t2,0x0($s1)
/*  f02cc6c:	0fc0a475 */ 	jal	func0f0291d4
/*  f02cc70:	028a2021 */ 	addu	$a0,$s4,$t2
/*  f02cc74:	26730001 */ 	addiu	$s3,$s3,0x1
.L0f02cc78:
/*  f02cc78:	24010014 */ 	addiu	$at,$zero,0x14
/*  f02cc7c:	1661ff63 */ 	bne	$s3,$at,.L0f02ca0c
/*  f02cc80:	2694005c */ 	addiu	$s4,$s4,0x5c
.L0f02cc84:
/*  f02cc84:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f02cc88:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f02cc8c:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f02cc90:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f02cc94:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f02cc98:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f02cc9c:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f02cca0:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f02cca4:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f02cca8:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f02ccac:	03e00008 */ 	jr	$ra
/*  f02ccb0:	27bd0048 */ 	addiu	$sp,$sp,0x48
);
#else
GLOBAL_ASM(
glabel func0f02c9b0
.late_rodata
glabel var7f1a8984
.word 0x3c4ccccd
.text
/*  f02c9b0:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*  f02c9b4:	3c0e8006 */ 	lui	$t6,%hi(var80062a90)
/*  f02c9b8:	8dce2a90 */ 	lw	$t6,%lo(var80062a90)($t6)
/*  f02c9bc:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f02c9c0:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f02c9c4:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f02c9c8:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f02c9cc:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f02c9d0:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f02c9d4:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f02c9d8:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f02c9dc:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f02c9e0:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f02c9e4:	11c000a7 */ 	beqz	$t6,.L0f02cc84
/*  f02c9e8:	afa00040 */ 	sw	$zero,0x40($sp)
/*  f02c9ec:	3c1e800a */ 	lui	$s8,%hi(g_Vars)
/*  f02c9f0:	3c118006 */ 	lui	$s1,%hi(var80062a8c)
/*  f02c9f4:	26312a8c */ 	addiu	$s1,$s1,%lo(var80062a8c)
/*  f02c9f8:	27de9fc0 */ 	addiu	$s8,$s8,%lo(g_Vars)
/*  f02c9fc:	00009825 */ 	or	$s3,$zero,$zero
/*  f02ca00:	0000a025 */ 	or	$s4,$zero,$zero
/*  f02ca04:	2416ffff */ 	addiu	$s6,$zero,-1
/*  f02ca08:	2415fffd */ 	addiu	$s5,$zero,-3
.L0f02ca0c:
/*  f02ca0c:	8e230000 */ 	lw	$v1,0x0($s1)
/*  f02ca10:	00741021 */ 	addu	$v0,$v1,$s4
/*  f02ca14:	8c4f0000 */ 	lw	$t7,0x0($v0)
/*  f02ca18:	51e00097 */ 	beqzl	$t7,.L0f02cc78
/*  f02ca1c:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f02ca20:	8fd90008 */ 	lw	$t9,0x8($s8)
/*  f02ca24:	8c58000c */ 	lw	$t8,0xc($v0)
/*  f02ca28:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f02ca2c:	2728ffb0 */ 	addiu	$t0,$t9,-80
/*  f02ca30:	0308082a */ 	slt	$at,$t8,$t0
/*  f02ca34:	1420000f */ 	bnez	$at,.L0f02ca74
/*  f02ca38:	02832021 */ 	addu	$a0,$s4,$v1
/*  f02ca3c:	0fc0a5e8 */ 	jal	propGetShieldThing
/*  f02ca40:	afa90040 */ 	sw	$t1,0x40($sp)
/*  f02ca44:	8e2a0000 */ 	lw	$t2,0x0($s1)
/*  f02ca48:	c7c60044 */ 	lwc1	$f6,0x44($s8)
/*  f02ca4c:	3c017f1b */ 	lui	$at,%hi(var7f1a8984)
/*  f02ca50:	01541021 */ 	addu	$v0,$t2,$s4
/*  f02ca54:	c4420058 */ 	lwc1	$f2,0x58($v0)
/*  f02ca58:	c42a8984 */ 	lwc1	$f10,%lo(var7f1a8984)($at)
/*  f02ca5c:	46020101 */ 	sub.s	$f4,$f0,$f2
/*  f02ca60:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f02ca64:	00000000 */ 	nop
/*  f02ca68:	460a4402 */ 	mul.s	$f16,$f8,$f10
/*  f02ca6c:	46101480 */ 	add.s	$f18,$f2,$f16
/*  f02ca70:	e4520058 */ 	swc1	$f18,0x58($v0)
.L0f02ca74:
/*  f02ca74:	00009025 */ 	or	$s2,$zero,$zero
/*  f02ca78:	00135880 */ 	sll	$t3,$s3,0x2
.L0f02ca7c:
/*  f02ca7c:	01735823 */ 	subu	$t3,$t3,$s3
/*  f02ca80:	8e230000 */ 	lw	$v1,0x0($s1)
/*  f02ca84:	000b58c0 */ 	sll	$t3,$t3,0x3
/*  f02ca88:	01735823 */ 	subu	$t3,$t3,$s3
/*  f02ca8c:	000b5880 */ 	sll	$t3,$t3,0x2
/*  f02ca90:	006b6021 */ 	addu	$t4,$v1,$t3
/*  f02ca94:	01926821 */ 	addu	$t5,$t4,$s2
/*  f02ca98:	81a20018 */ 	lb	$v0,0x18($t5)
/*  f02ca9c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f02caa0:	0442005a */ 	bltzl	$v0,.L0f02cc0c
/*  f02caa4:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f02caa8:	8fcf0038 */ 	lw	$t7,0x38($s8)
/*  f02caac:	afae0040 */ 	sw	$t6,0x40($sp)
/*  f02cab0:	1c400047 */ 	bgtz	$v0,.L0f02cbd0
/*  f02cab4:	004fb821 */ 	addu	$s7,$v0,$t7
/*  f02cab8:	1ae00045 */ 	blez	$s7,.L0f02cbd0
/*  f02cabc:	0074c821 */ 	addu	$t9,$v1,$s4
/*  f02cac0:	8f240000 */ 	lw	$a0,0x0($t9)
/*  f02cac4:	0fc0a4cb */ 	jal	func0f02932c
/*  f02cac8:	02402825 */ 	or	$a1,$s2,$zero
/*  f02cacc:	04400019 */ 	bltz	$v0,.L0f02cb34
/*  f02cad0:	28410020 */ 	slti	$at,$v0,0x20
/*  f02cad4:	10200017 */ 	beqz	$at,.L0f02cb34
/*  f02cad8:	00134080 */ 	sll	$t0,$s3,0x2
/*  f02cadc:	01134023 */ 	subu	$t0,$t0,$s3
/*  f02cae0:	8e380000 */ 	lw	$t8,0x0($s1)
/*  f02cae4:	000840c0 */ 	sll	$t0,$t0,0x3
/*  f02cae8:	01134023 */ 	subu	$t0,$t0,$s3
/*  f02caec:	00084080 */ 	sll	$t0,$t0,0x2
/*  f02caf0:	03084821 */ 	addu	$t1,$t8,$t0
/*  f02caf4:	01222021 */ 	addu	$a0,$t1,$v0
/*  f02caf8:	808a0018 */ 	lb	$t2,0x18($a0)
/*  f02cafc:	00136080 */ 	sll	$t4,$s3,0x2
/*  f02cb00:	01936023 */ 	subu	$t4,$t4,$s3
/*  f02cb04:	16ca000b */ 	bne	$s6,$t2,.L0f02cb34
/*  f02cb08:	000c60c0 */ 	sll	$t4,$t4,0x3
/*  f02cb0c:	a0950018 */ 	sb	$s5,0x18($a0)
/*  f02cb10:	8e2b0000 */ 	lw	$t3,0x0($s1)
/*  f02cb14:	01936023 */ 	subu	$t4,$t4,$s3
/*  f02cb18:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f02cb1c:	016c1821 */ 	addu	$v1,$t3,$t4
/*  f02cb20:	00726821 */ 	addu	$t5,$v1,$s2
/*  f02cb24:	91ae0038 */ 	lbu	$t6,0x38($t5)
/*  f02cb28:	0062c821 */ 	addu	$t9,$v1,$v0
/*  f02cb2c:	25cf0001 */ 	addiu	$t7,$t6,0x1
/*  f02cb30:	a32f0038 */ 	sb	$t7,0x38($t9)
.L0f02cb34:
/*  f02cb34:	8e380000 */ 	lw	$t8,0x0($s1)
/*  f02cb38:	02402825 */ 	or	$a1,$s2,$zero
/*  f02cb3c:	03144021 */ 	addu	$t0,$t8,$s4
/*  f02cb40:	0fc0a4fb */ 	jal	func0f0293ec
/*  f02cb44:	8d040000 */ 	lw	$a0,0x0($t0)
/*  f02cb48:	04400021 */ 	bltz	$v0,.L0f02cbd0
/*  f02cb4c:	00408025 */ 	or	$s0,$v0,$zero
.L0f02cb50:
/*  f02cb50:	28410020 */ 	slti	$at,$v0,0x20
/*  f02cb54:	10200017 */ 	beqz	$at,.L0f02cbb4
/*  f02cb58:	00135080 */ 	sll	$t2,$s3,0x2
/*  f02cb5c:	01535023 */ 	subu	$t2,$t2,$s3
/*  f02cb60:	8e290000 */ 	lw	$t1,0x0($s1)
/*  f02cb64:	000a50c0 */ 	sll	$t2,$t2,0x3
/*  f02cb68:	01535023 */ 	subu	$t2,$t2,$s3
/*  f02cb6c:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f02cb70:	012a5821 */ 	addu	$t3,$t1,$t2
/*  f02cb74:	01622021 */ 	addu	$a0,$t3,$v0
/*  f02cb78:	808c0018 */ 	lb	$t4,0x18($a0)
/*  f02cb7c:	00137080 */ 	sll	$t6,$s3,0x2
/*  f02cb80:	01d37023 */ 	subu	$t6,$t6,$s3
/*  f02cb84:	16cc000b */ 	bne	$s6,$t4,.L0f02cbb4
/*  f02cb88:	000e70c0 */ 	sll	$t6,$t6,0x3
/*  f02cb8c:	a0950018 */ 	sb	$s5,0x18($a0)
/*  f02cb90:	8e2d0000 */ 	lw	$t5,0x0($s1)
/*  f02cb94:	01d37023 */ 	subu	$t6,$t6,$s3
/*  f02cb98:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f02cb9c:	01ae1821 */ 	addu	$v1,$t5,$t6
/*  f02cba0:	00727821 */ 	addu	$t7,$v1,$s2
/*  f02cba4:	91f90038 */ 	lbu	$t9,0x38($t7)
/*  f02cba8:	00624021 */ 	addu	$t0,$v1,$v0
/*  f02cbac:	27380001 */ 	addiu	$t8,$t9,0x1
/*  f02cbb0:	a1180038 */ 	sb	$t8,0x38($t0)
.L0f02cbb4:
/*  f02cbb4:	8e290000 */ 	lw	$t1,0x0($s1)
/*  f02cbb8:	02002825 */ 	or	$a1,$s0,$zero
/*  f02cbbc:	01345021 */ 	addu	$t2,$t1,$s4
/*  f02cbc0:	0fc0a533 */ 	jal	func0f0294cc
/*  f02cbc4:	8d440000 */ 	lw	$a0,0x0($t2)
/*  f02cbc8:	0441ffe1 */ 	bgez	$v0,.L0f02cb50
/*  f02cbcc:	00408025 */ 	or	$s0,$v0,$zero
.L0f02cbd0:
/*  f02cbd0:	00136080 */ 	sll	$t4,$s3,0x2
/*  f02cbd4:	01936023 */ 	subu	$t4,$t4,$s3
/*  f02cbd8:	8e2b0000 */ 	lw	$t3,0x0($s1)
/*  f02cbdc:	000c60c0 */ 	sll	$t4,$t4,0x3
/*  f02cbe0:	01936023 */ 	subu	$t4,$t4,$s3
/*  f02cbe4:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f02cbe8:	2ae1001e */ 	slti	$at,$s7,0x1e
/*  f02cbec:	016c6821 */ 	addu	$t5,$t3,$t4
/*  f02cbf0:	10200003 */ 	beqz	$at,.L0f02cc00
/*  f02cbf4:	01b21021 */ 	addu	$v0,$t5,$s2
/*  f02cbf8:	10000003 */ 	b	.L0f02cc08
/*  f02cbfc:	a0570018 */ 	sb	$s7,0x18($v0)
.L0f02cc00:
/*  f02cc00:	240efffe */ 	addiu	$t6,$zero,-2
/*  f02cc04:	a04e0018 */ 	sb	$t6,0x18($v0)
.L0f02cc08:
/*  f02cc08:	26520001 */ 	addiu	$s2,$s2,0x1
.L0f02cc0c:
/*  f02cc0c:	2a410020 */ 	slti	$at,$s2,0x20
/*  f02cc10:	5420ff9a */ 	bnezl	$at,.L0f02ca7c
/*  f02cc14:	00135880 */ 	sll	$t3,$s3,0x2
/*  f02cc18:	00009025 */ 	or	$s2,$zero,$zero
/*  f02cc1c:	0013c880 */ 	sll	$t9,$s3,0x2
.L0f02cc20:
/*  f02cc20:	0333c823 */ 	subu	$t9,$t9,$s3
/*  f02cc24:	8e2f0000 */ 	lw	$t7,0x0($s1)
/*  f02cc28:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f02cc2c:	0333c823 */ 	subu	$t9,$t9,$s3
/*  f02cc30:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f02cc34:	01f9c021 */ 	addu	$t8,$t7,$t9
/*  f02cc38:	03121021 */ 	addu	$v0,$t8,$s2
/*  f02cc3c:	80480018 */ 	lb	$t0,0x18($v0)
/*  f02cc40:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f02cc44:	24010020 */ 	addiu	$at,$zero,0x20
/*  f02cc48:	16a80002 */ 	bne	$s5,$t0,.L0f02cc54
/*  f02cc4c:	00000000 */ 	nop
/*  f02cc50:	a0400018 */ 	sb	$zero,0x18($v0)
.L0f02cc54:
/*  f02cc54:	5641fff2 */ 	bnel	$s2,$at,.L0f02cc20
/*  f02cc58:	0013c880 */ 	sll	$t9,$s3,0x2
/*  f02cc5c:	8fa90040 */ 	lw	$t1,0x40($sp)
/*  f02cc60:	55200005 */ 	bnezl	$t1,.L0f02cc78
/*  f02cc64:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f02cc68:	8e2a0000 */ 	lw	$t2,0x0($s1)
/*  f02cc6c:	0fc0a475 */ 	jal	func0f0291d4
/*  f02cc70:	028a2021 */ 	addu	$a0,$s4,$t2
/*  f02cc74:	26730001 */ 	addiu	$s3,$s3,0x1
.L0f02cc78:
/*  f02cc78:	24010014 */ 	addiu	$at,$zero,0x14
/*  f02cc7c:	1661ff63 */ 	bne	$s3,$at,.L0f02ca0c
/*  f02cc80:	2694005c */ 	addiu	$s4,$s4,0x5c
.L0f02cc84:
/*  f02cc84:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f02cc88:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f02cc8c:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f02cc90:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f02cc94:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f02cc98:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f02cc9c:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f02cca0:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f02cca4:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f02cca8:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f02ccac:	03e00008 */ 	jr	$ra
/*  f02ccb0:	27bd0048 */ 	addiu	$sp,$sp,0x48
);
#endif

void chrSetDrCarollImages(struct chrdata *drcaroll, s32 imageleft, s32 imageright)
{
	if (drcaroll && imageleft >= 0 && imageleft < 6 && imageright >= 0 && imageright < 6) {
		struct model *model = drcaroll->model;
		struct modelnode *nodes[2];
		union modelrwdata *rwdata;
		s32 i;
		s32 j;
		u32 stack;

		// Iterate model parts relating to images
		// Parts 0-5 are the left image
		// Parts 6-11 are the right image
		for (i = 0; i < 6; i++) {
			nodes[0] = modelGetPart(model->filedata, i);
			nodes[1] = modelGetPart(model->filedata, i + 6);

			for (j = 0; j < 2; j++) {
				if (nodes[j]) {
					rwdata = modelGetNodeRwData(model, nodes[j]);

					if (j == 0) {
						rwdata->toggle.visible = (imageleft == i) ? true : false;
					} else {
						rwdata->toggle.visible = (imageright == i) ? true : false;
					}
				}
			}
		}
	}
}

s32 var80062a90 = false;
u32 var80062a94 = 0x00000000;
u32 var80062a98 = 0x00000000;
u32 var80062a9c = 0x00000000;
u32 var80062aa0 = 0x00000000;
u32 var80062aa4 = 0x00000001;
u32 var80062aa8 = 0x00000003;
u32 var80062aac = 0x00000002;
u32 var80062ab0 = 0x00000007;
u32 var80062ab4 = 0x00000005;
u32 var80062ab8 = 0x00000004;
u32 var80062abc = 0x00000006;
u32 var80062ac0 = 0x00000005;
u32 var80062ac4 = 0x00000001;
u32 var80062ac8 = 0x00000000;
u32 var80062acc = 0x00000004;
u32 var80062ad0 = 0x00000002;
u32 var80062ad4 = 0x00000003;
u32 var80062ad8 = 0x00000007;
u32 var80062adc = 0x00000006;
u32 var80062ae0 = 0x00000000;
u32 var80062ae4 = 0x00000002;
u32 var80062ae8 = 0x00000006;
u32 var80062aec = 0x00000004;
u32 var80062af0 = 0x00000007;
u32 var80062af4 = 0x00000003;
u32 var80062af8 = 0x00000001;
u32 var80062afc = 0x00000005;
