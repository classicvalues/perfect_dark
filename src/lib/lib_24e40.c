#include <ultra64.h>
#include "constants.h"
#include "game/prop.h"
#include "game/game_1531a0.h"
#include "game/bg.h"
#include "game/game_1577f0.h"
#include "bss.h"
#include "lib/dma.h"
#include "lib/memory.h"
#include "lib/lib_16110.h"
#include "lib/lib_17ce0.h"
#include "lib/lib_233c0.h"
#include "lib/lib_24e40.h"
#include "lib/lib_2f490.h"
#include "lib/libc/ll.h"
#include "lib/lib_4b170.h"
#include "data.h"
#include "types.h"

union filedataptr g_TileFileData;
s32 g_TileNumRooms;
u32 *g_TileRooms;
s32 var8009a8ac;
f32 var8009a8b0;
u32 var8009a8b4;
struct coord var8009a8b8;
u32 var8009a8c4;
struct coord var8009a8c8;
struct prop *g_CdObstacle;
u32 var8009a8d8;
u32 var8009a8dc;
struct coord g_CdPos;
u32 var8009a8ec;
f32 var8009a8f0;
u32 var8009a8f4;
u32 var8009a8f8;
u32 var8009a8fc;
u32 var8009a900;
u32 var8009a904;
u32 var8009a908;
u32 var8009a90c;
u32 var8009a910;
u32 var8009a914;

u32 var8009a918;
u32 var8009a91c;
u32 var8009a920;
u32 var8009a924;
u32 var8009a928;
u32 var8009a92c;
u32 var8009a930;
u32 var8009a934;
u32 var8009a938;
u32 var8009a93c;
u32 var8009a940;
u32 var8009a944;
u32 var8009a948;
u32 var8009a94c;
u32 var8009a950;
u32 var8009a954;
u32 var8009a958;
u32 var8009a95c;
u32 var8009a960;

struct tile *var8009a964;
u32 var8009a968;
u32 var8009a96c;

u32 var8005f030 = 0x00000000;
u32 var8005f034 = 0x00000000;
u32 var8005f038 = 0x00000000;

f32 func00024e40(void)
{
	return var8009a8f0;
}

void func00024e4c(struct coord *a, struct coord *b, u32 line, char *file)
{
	a->x = var8009a8b8.x;
	a->y = var8009a8b8.y;
	a->z = var8009a8b8.z;

	b->x = var8009a8c8.x;
	b->y = var8009a8c8.y;
	b->z = var8009a8c8.z;
}

f32 func00024e98(void)
{
	return var8009a8b0;
}

s32 func00024ea4(void)
{
	return var8009a8ac;
}

struct prop *cdGetObstacle(void)
{
	return g_CdObstacle;
}

void cdGetPos(struct coord *pos, u32 line, char *file)
{
	pos->x = g_CdPos.x;
	pos->y = g_CdPos.y;
	pos->z = g_CdPos.z;
}

void func00024ee8(struct coord *arg0)
{
	func00025928(var8009a964, arg0);
}

u32 cdGetTileFlags(void)
{
	u32 flags = 0;

	switch (var8009a964->type) {
	case TILETYPE_00:
		flags = var8009a964->flags;
		break;
	case TILETYPE_01:
		flags = var8009a964->flags;
		break;
	case TILETYPE_02:
		flags = TILEFLAG_0004 | TILEFLAG_0008 | TILEFLAG_0010;
		break;
	case TILETYPE_03:
		flags = var8009a964->flags;
		break;
	}

	return flags;
}

void func00024f6c(void)
{
	var8009a8b4 = 0;
	var8009a8ac = 0;
	g_CdObstacle = NULL;
	var8009a8d8 = 0;
	var8009a8ec = 0;
	var8009a8f4 = 0;
	var8005f034 = 0;
	var8005f038 = 0;
}

void func00024fb0(struct coord *arg0, struct coord *arg1, struct prop *prop)
{
	var8009a8b8.x = arg0->x;
	var8009a8b8.y = arg0->y;
	var8009a8b8.z = arg0->z;

	var8009a8c8.x = arg1->x;
	var8009a8c8.y = arg1->y;
	var8009a8c8.z = arg1->z;

	var8009a8b4 = 1;
	var8009a8ac = 0;
	g_CdObstacle = prop;
	var8009a8d8 = 0;
	var8009a8ec = 0;
	var8009a8f4 = 0;
	var8005f034 = 0;
	var8005f038 = 0;
}

GLOBAL_ASM(
glabel func00025038
/*    25038:	44876000 */ 	mtc1	$a3,$f12
/*    2503c:	3c01800a */ 	lui	$at,%hi(var8009a8b0)
/*    25040:	3c02800a */ 	lui	$v0,%hi(var8009a8b8)
/*    25044:	e42ca8b0 */ 	swc1	$f12,%lo(var8009a8b0)($at)
/*    25048:	c4840000 */ 	lwc1	$f4,0x0($a0)
/*    2504c:	2442a8b8 */ 	addiu	$v0,$v0,%lo(var8009a8b8)
/*    25050:	3c03800a */ 	lui	$v1,%hi(var8009a8c8)
/*    25054:	e4440000 */ 	swc1	$f4,0x0($v0)
/*    25058:	c4860004 */ 	lwc1	$f6,0x4($a0)
/*    2505c:	2463a8c8 */ 	addiu	$v1,$v1,%lo(var8009a8c8)
/*    25060:	24070001 */ 	addiu	$a3,$zero,0x1
/*    25064:	e4460004 */ 	swc1	$f6,0x4($v0)
/*    25068:	c4880008 */ 	lwc1	$f8,0x8($a0)
/*    2506c:	3c01800a */ 	lui	$at,%hi(var8009a8b4)
/*    25070:	e4480008 */ 	swc1	$f8,0x8($v0)
/*    25074:	c4aa0000 */ 	lwc1	$f10,0x0($a1)
/*    25078:	e46a0000 */ 	swc1	$f10,0x0($v1)
/*    2507c:	c4b00004 */ 	lwc1	$f16,0x4($a1)
/*    25080:	e4700004 */ 	swc1	$f16,0x4($v1)
/*    25084:	c4b20008 */ 	lwc1	$f18,0x8($a1)
/*    25088:	e4720008 */ 	swc1	$f18,0x8($v1)
/*    2508c:	ac27a8b4 */ 	sw	$a3,%lo(var8009a8b4)($at)
/*    25090:	3c01800a */ 	lui	$at,%hi(var8009a8ac)
/*    25094:	ac27a8ac */ 	sw	$a3,%lo(var8009a8ac)($at)
/*    25098:	3c01800a */ 	lui	$at,%hi(g_CdObstacle)
/*    2509c:	ac26a8d4 */ 	sw	$a2,%lo(g_CdObstacle)($at)
/*    250a0:	3c01800a */ 	lui	$at,%hi(var8009a8d8)
/*    250a4:	ac20a8d8 */ 	sw	$zero,%lo(var8009a8d8)($at)
/*    250a8:	3c01800a */ 	lui	$at,%hi(var8009a8ec)
/*    250ac:	ac20a8ec */ 	sw	$zero,%lo(var8009a8ec)($at)
/*    250b0:	3c01800a */ 	lui	$at,%hi(var8009a8f4)
/*    250b4:	ac20a8f4 */ 	sw	$zero,%lo(var8009a8f4)($at)
/*    250b8:	3c018006 */ 	lui	$at,%hi(var8005f034)
/*    250bc:	ac20f034 */ 	sw	$zero,%lo(var8005f034)($at)
/*    250c0:	3c018006 */ 	lui	$at,%hi(var8005f038)
/*    250c4:	03e00008 */ 	jr	$ra
/*    250c8:	ac20f038 */ 	sw	$zero,%lo(var8005f038)($at)
);

void func000250cc(struct coord *arg0, struct coord *arg1, f32 width)
{
	f32 sp38[2];
	f32 sp34;
	f32 sp2c[2];
	f32 sp24[2];
	f32 sp1c[2];

	sp34 = width;

	sp38[0] = arg0->x;
	sp38[1] = arg0->z;

	sp1c[0] = arg1->x;
	sp1c[1] = arg1->z;

	sp2c[0] = var8009a8b8.x;
	sp2c[1] = var8009a8b8.z;

	sp24[0] = var8009a8c8.x;
	sp24[1] = var8009a8c8.z;

	var8009a8b0 = func0f1579cc(&sp34, sp2c, sp24, sp1c);
	var8009a8ac = 1;
}

void func00025168(struct prop *prop)
{
	var8009a8b4 = 0;
	var8009a8ac = 0;
	g_CdObstacle = prop;
	var8009a8d8 = 0;
	var8009a8ec = 0;
	var8009a8f4 = 0;
	var8005f034 = 0;
	var8005f038 = 0;
}

GLOBAL_ASM(
glabel func000251ac
/*    251ac:	c4840000 */ 	lwc1	$f4,0x0($a0)
/*    251b0:	3c02800a */ 	lui	$v0,%hi(var8009a8b8)
/*    251b4:	2442a8b8 */ 	addiu	$v0,$v0,%lo(var8009a8b8)
/*    251b8:	e4440000 */ 	swc1	$f4,0x0($v0)
/*    251bc:	c4860004 */ 	lwc1	$f6,0x4($a0)
/*    251c0:	3c03800a */ 	lui	$v1,%hi(var8009a8c8)
/*    251c4:	2463a8c8 */ 	addiu	$v1,$v1,%lo(var8009a8c8)
/*    251c8:	e4460004 */ 	swc1	$f6,0x4($v0)
/*    251cc:	c4880008 */ 	lwc1	$f8,0x8($a0)
/*    251d0:	3c08800a */ 	lui	$t0,%hi(g_CdPos)
/*    251d4:	2508a8e0 */ 	addiu	$t0,$t0,%lo(g_CdPos)
/*    251d8:	e4480008 */ 	swc1	$f8,0x8($v0)
/*    251dc:	c4aa0000 */ 	lwc1	$f10,0x0($a1)
/*    251e0:	24090001 */ 	addiu	$t1,$zero,0x1
/*    251e4:	3c01800a */ 	lui	$at,%hi(var8009a8b4)
/*    251e8:	e46a0000 */ 	swc1	$f10,0x0($v1)
/*    251ec:	c4b00004 */ 	lwc1	$f16,0x4($a1)
/*    251f0:	e4700004 */ 	swc1	$f16,0x4($v1)
/*    251f4:	c4b20008 */ 	lwc1	$f18,0x8($a1)
/*    251f8:	e4720008 */ 	swc1	$f18,0x8($v1)
/*    251fc:	c4c40000 */ 	lwc1	$f4,0x0($a2)
/*    25200:	e5040000 */ 	swc1	$f4,0x0($t0)
/*    25204:	c4c60004 */ 	lwc1	$f6,0x4($a2)
/*    25208:	e5060004 */ 	swc1	$f6,0x4($t0)
/*    2520c:	c4c80008 */ 	lwc1	$f8,0x8($a2)
/*    25210:	e5080008 */ 	swc1	$f8,0x8($t0)
/*    25214:	ac29a8b4 */ 	sw	$t1,%lo(var8009a8b4)($at)
/*    25218:	3c01800a */ 	lui	$at,%hi(var8009a8ac)
/*    2521c:	ac20a8ac */ 	sw	$zero,%lo(var8009a8ac)($at)
/*    25220:	3c01800a */ 	lui	$at,%hi(g_CdObstacle)
/*    25224:	ac27a8d4 */ 	sw	$a3,%lo(g_CdObstacle)($at)
/*    25228:	3c01800a */ 	lui	$at,%hi(var8009a8d8)
/*    2522c:	ac29a8d8 */ 	sw	$t1,%lo(var8009a8d8)($at)
/*    25230:	3c01800a */ 	lui	$at,%hi(var8009a8ec)
/*    25234:	ac20a8ec */ 	sw	$zero,%lo(var8009a8ec)($at)
/*    25238:	3c01800a */ 	lui	$at,%hi(var8009a8f4)
/*    2523c:	ac20a8f4 */ 	sw	$zero,%lo(var8009a8f4)($at)
/*    25240:	3c018006 */ 	lui	$at,%hi(var8005f034)
/*    25244:	ac20f034 */ 	sw	$zero,%lo(var8005f034)($at)
/*    25248:	3c018006 */ 	lui	$at,%hi(var8005f038)
/*    2524c:	03e00008 */ 	jr	$ra
/*    25250:	ac20f038 */ 	sw	$zero,%lo(var8005f038)($at)
);

void func00025254(struct coord *arg0, struct coord *arg1, struct coord *pos, struct prop *prop, f32 arg4, struct tile *tile)
{
	var8009a8b8.x = arg0->x;
	var8009a8b8.y = arg0->y;
	var8009a8b8.z = arg0->z;

	var8009a8c8.x = arg1->x;
	var8009a8c8.y = arg1->y;
	var8009a8c8.z = arg1->z;

	g_CdPos.x = pos->x;
	g_CdPos.y = pos->y;
	g_CdPos.z = pos->z;

	var8009a8b4 = 1;
	var8009a8ac = 0;
	g_CdObstacle = prop;
	var8009a8d8 = 1;
	var8009a8f0 = arg4;
	var8009a8ec = 1;
	var8009a8f4 = 0;
	var8005f034 = 0;
	var8009a964 = tile;
	var8005f038 = 1;
}

GLOBAL_ASM(
glabel func00025314
/*    25314:	c4840000 */ 	lwc1	$f4,0x0($a0)
/*    25318:	3c02800a */ 	lui	$v0,%hi(var8009a8f8)
/*    2531c:	2442a8f8 */ 	addiu	$v0,$v0,%lo(var8009a8f8)
/*    25320:	e4440000 */ 	swc1	$f4,0x0($v0)
/*    25324:	c4860004 */ 	lwc1	$f6,0x4($a0)
/*    25328:	3c03800a */ 	lui	$v1,%hi(var8009a908)
/*    2532c:	2463a908 */ 	addiu	$v1,$v1,%lo(var8009a908)
/*    25330:	e4460004 */ 	swc1	$f6,0x4($v0)
/*    25334:	c4880008 */ 	lwc1	$f8,0x8($a0)
/*    25338:	240e0001 */ 	addiu	$t6,$zero,0x1
/*    2533c:	3c01800a */ 	lui	$at,%hi(var8009a8f4)
/*    25340:	e4480008 */ 	swc1	$f8,0x8($v0)
/*    25344:	c4aa0000 */ 	lwc1	$f10,0x0($a1)
/*    25348:	e46a0000 */ 	swc1	$f10,0x0($v1)
/*    2534c:	c4b00004 */ 	lwc1	$f16,0x4($a1)
/*    25350:	e4700004 */ 	swc1	$f16,0x4($v1)
/*    25354:	c4b20008 */ 	lwc1	$f18,0x8($a1)
/*    25358:	e4720008 */ 	swc1	$f18,0x8($v1)
/*    2535c:	03e00008 */ 	jr	$ra
/*    25360:	ac2ea8f4 */ 	sw	$t6,%lo(var8009a8f4)($at)
);

GLOBAL_ASM(
glabel func00025364
/*    25364:	3c03800a */ 	lui	$v1,%hi(var8009a8f4)
/*    25368:	8c63a8f4 */ 	lw	$v1,%lo(var8009a8f4)($v1)
/*    2536c:	3c02800a */ 	lui	$v0,%hi(var8009a8f8)
/*    25370:	2442a8f8 */ 	addiu	$v0,$v0,%lo(var8009a8f8)
/*    25374:	10600011 */ 	beqz	$v1,.L000253bc
/*    25378:	00000000 */ 	nop
/*    2537c:	c4440000 */ 	lwc1	$f4,0x0($v0)
/*    25380:	3c06800a */ 	lui	$a2,%hi(var8009a908)
/*    25384:	24c6a908 */ 	addiu	$a2,$a2,%lo(var8009a908)
/*    25388:	e4840000 */ 	swc1	$f4,0x0($a0)
/*    2538c:	c4460004 */ 	lwc1	$f6,0x4($v0)
/*    25390:	3c03800a */ 	lui	$v1,%hi(var8009a8f4)
/*    25394:	e4860004 */ 	swc1	$f6,0x4($a0)
/*    25398:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*    2539c:	e4880008 */ 	swc1	$f8,0x8($a0)
/*    253a0:	c4ca0000 */ 	lwc1	$f10,0x0($a2)
/*    253a4:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*    253a8:	c4d00004 */ 	lwc1	$f16,0x4($a2)
/*    253ac:	e4b00004 */ 	swc1	$f16,0x4($a1)
/*    253b0:	c4d20008 */ 	lwc1	$f18,0x8($a2)
/*    253b4:	e4b20008 */ 	swc1	$f18,0x8($a1)
/*    253b8:	8c63a8f4 */ 	lw	$v1,%lo(var8009a8f4)($v1)
.L000253bc:
/*    253bc:	03e00008 */ 	jr	$ra
/*    253c0:	00601025 */ 	or	$v0,$v1,$zero
);

GLOBAL_ASM(
glabel func000253c4
/*    253c4:	3c0e800a */ 	lui	$t6,%hi(var8009a918)
/*    253c8:	25cea918 */ 	addiu	$t6,$t6,%lo(var8009a918)
/*    253cc:	00804025 */ 	or	$t0,$a0,$zero
/*    253d0:	24990048 */ 	addiu	$t9,$a0,0x48
.L000253d4:
/*    253d4:	8d010000 */ 	lw	$at,0x0($t0)
/*    253d8:	2508000c */ 	addiu	$t0,$t0,0xc
/*    253dc:	25ce000c */ 	addiu	$t6,$t6,0xc
/*    253e0:	adc1fff4 */ 	sw	$at,-0xc($t6)
/*    253e4:	8d01fff8 */ 	lw	$at,-0x8($t0)
/*    253e8:	adc1fff8 */ 	sw	$at,-0x8($t6)
/*    253ec:	8d01fffc */ 	lw	$at,-0x4($t0)
/*    253f0:	1519fff8 */ 	bne	$t0,$t9,.L000253d4
/*    253f4:	adc1fffc */ 	sw	$at,-0x4($t6)
/*    253f8:	8d010000 */ 	lw	$at,0x0($t0)
/*    253fc:	24090001 */ 	addiu	$t1,$zero,0x1
/*    25400:	adc10000 */ 	sw	$at,0x0($t6)
/*    25404:	3c018006 */ 	lui	$at,%hi(var8005f034)
/*    25408:	03e00008 */ 	jr	$ra
/*    2540c:	ac29f034 */ 	sw	$t1,%lo(var8005f034)($at)
);

GLOBAL_ASM(
glabel func00025410
/*    25410:	afa60008 */ 	sw	$a2,0x8($sp)
/*    25414:	c7a40008 */ 	lwc1	$f4,0x8($sp)
/*    25418:	afa7000c */ 	sw	$a3,0xc($sp)
/*    2541c:	c7a6000c */ 	lwc1	$f6,0xc($sp)
/*    25420:	46047082 */ 	mul.s	$f2,$f14,$f4
/*    25424:	00000000 */ 	nop
/*    25428:	46066002 */ 	mul.s	$f0,$f12,$f6
/*    2542c:	4600103c */ 	c.lt.s	$f2,$f0
/*    25430:	00000000 */ 	nop
/*    25434:	45000003 */ 	bc1f	.L00025444
/*    25438:	00000000 */ 	nop
/*    2543c:	03e00008 */ 	jr	$ra
/*    25440:	24020001 */ 	addiu	$v0,$zero,0x1
.L00025444:
/*    25444:	4602003c */ 	c.lt.s	$f0,$f2
/*    25448:	c7a80008 */ 	lwc1	$f8,0x8($sp)
/*    2544c:	45000003 */ 	bc1f	.L0002545c
/*    25450:	00000000 */ 	nop
/*    25454:	03e00008 */ 	jr	$ra
/*    25458:	2402ffff */ 	addiu	$v0,$zero,-1
.L0002545c:
/*    2545c:	46086282 */ 	mul.s	$f10,$f12,$f8
/*    25460:	44800000 */ 	mtc1	$zero,$f0
/*    25464:	c7b0000c */ 	lwc1	$f16,0xc($sp)
/*    25468:	4600503c */ 	c.lt.s	$f10,$f0
/*    2546c:	00000000 */ 	nop
/*    25470:	45010006 */ 	bc1t	.L0002548c
/*    25474:	00000000 */ 	nop
/*    25478:	46107482 */ 	mul.s	$f18,$f14,$f16
/*    2547c:	4600903c */ 	c.lt.s	$f18,$f0
/*    25480:	00000000 */ 	nop
/*    25484:	45000003 */ 	bc1f	.L00025494
/*    25488:	00000000 */ 	nop
.L0002548c:
/*    2548c:	03e00008 */ 	jr	$ra
/*    25490:	2402ffff */ 	addiu	$v0,$zero,-1
.L00025494:
/*    25494:	460c6102 */ 	mul.s	$f4,$f12,$f12
/*    25498:	c7aa0008 */ 	lwc1	$f10,0x8($sp)
/*    2549c:	c7b2000c */ 	lwc1	$f18,0xc($sp)
/*    254a0:	460e7182 */ 	mul.s	$f6,$f14,$f14
/*    254a4:	00001025 */ 	or	$v0,$zero,$zero
/*    254a8:	460a5402 */ 	mul.s	$f16,$f10,$f10
/*    254ac:	46062200 */ 	add.s	$f8,$f4,$f6
/*    254b0:	46129102 */ 	mul.s	$f4,$f18,$f18
/*    254b4:	46048180 */ 	add.s	$f6,$f16,$f4
/*    254b8:	4606403c */ 	c.lt.s	$f8,$f6
/*    254bc:	00000000 */ 	nop
/*    254c0:	45000003 */ 	bc1f	.L000254d0
/*    254c4:	00000000 */ 	nop
/*    254c8:	03e00008 */ 	jr	$ra
/*    254cc:	24020001 */ 	addiu	$v0,$zero,0x1
.L000254d0:
/*    254d0:	03e00008 */ 	jr	$ra
/*    254d4:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel func000254d8
/*    254d8:	27bdffa8 */ 	addiu	$sp,$sp,-88
/*    254dc:	afa60060 */ 	sw	$a2,0x60($sp)
/*    254e0:	afa70064 */ 	sw	$a3,0x64($sp)
/*    254e4:	afbf001c */ 	sw	$ra,0x1c($sp)
/*    254e8:	afb00018 */ 	sw	$s0,0x18($sp)
/*    254ec:	afa5005c */ 	sw	$a1,0x5c($sp)
/*    254f0:	afa0002c */ 	sw	$zero,0x2c($sp)
/*    254f4:	c4840000 */ 	lwc1	$f4,0x0($a0)
/*    254f8:	c7a60060 */ 	lwc1	$f6,0x60($sp)
/*    254fc:	c4880008 */ 	lwc1	$f8,0x8($a0)
/*    25500:	c7aa0064 */ 	lwc1	$f10,0x64($sp)
/*    25504:	c7b00068 */ 	lwc1	$f16,0x68($sp)
/*    25508:	c7b2006c */ 	lwc1	$f18,0x6c($sp)
/*    2550c:	46062001 */ 	sub.s	$f0,$f4,$f6
/*    25510:	00808025 */ 	or	$s0,$a0,$zero
/*    25514:	460a4081 */ 	sub.s	$f2,$f8,$f10
/*    25518:	44060000 */ 	mfc1	$a2,$f0
/*    2551c:	e7a00054 */ 	swc1	$f0,0x54($sp)
/*    25520:	46068301 */ 	sub.s	$f12,$f16,$f6
/*    25524:	44071000 */ 	mfc1	$a3,$f2
/*    25528:	e7a20050 */ 	swc1	$f2,0x50($sp)
/*    2552c:	460a9381 */ 	sub.s	$f14,$f18,$f10
/*    25530:	e7ac0028 */ 	swc1	$f12,0x28($sp)
/*    25534:	0c009504 */ 	jal	func00025410
/*    25538:	e7ae0024 */ 	swc1	$f14,0x24($sp)
/*    2553c:	8fa3005c */ 	lw	$v1,0x5c($sp)
/*    25540:	afa2003c */ 	sw	$v0,0x3c($sp)
/*    25544:	c7a80060 */ 	lwc1	$f8,0x60($sp)
/*    25548:	c7b20064 */ 	lwc1	$f18,0x64($sp)
/*    2554c:	c4660008 */ 	lwc1	$f6,0x8($v1)
/*    25550:	c4640000 */ 	lwc1	$f4,0x0($v1)
/*    25554:	c7ac0028 */ 	lwc1	$f12,0x28($sp)
/*    25558:	46123281 */ 	sub.s	$f10,$f6,$f18
/*    2555c:	c7ae0024 */ 	lwc1	$f14,0x24($sp)
/*    25560:	46082401 */ 	sub.s	$f16,$f4,$f8
/*    25564:	44075000 */ 	mfc1	$a3,$f10
/*    25568:	44068000 */ 	mfc1	$a2,$f16
/*    2556c:	0c009504 */ 	jal	func00025410
/*    25570:	00000000 */ 	nop
/*    25574:	8fae003c */ 	lw	$t6,0x3c($sp)
/*    25578:	8fa3005c */ 	lw	$v1,0x5c($sp)
/*    2557c:	01c20019 */ 	multu	$t6,$v0
/*    25580:	00007812 */ 	mflo	$t7
/*    25584:	5de00025 */ 	bgtzl	$t7,.L0002561c
/*    25588:	8fa20070 */ 	lw	$v0,0x70($sp)
/*    2558c:	c4640000 */ 	lwc1	$f4,0x0($v1)
/*    25590:	c6080000 */ 	lwc1	$f8,0x0($s0)
/*    25594:	c4700008 */ 	lwc1	$f16,0x8($v1)
/*    25598:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*    2559c:	46082301 */ 	sub.s	$f12,$f4,$f8
/*    255a0:	c7a40050 */ 	lwc1	$f4,0x50($sp)
/*    255a4:	c7b20054 */ 	lwc1	$f18,0x54($sp)
/*    255a8:	46068381 */ 	sub.s	$f14,$f16,$f6
/*    255ac:	e7ac004c */ 	swc1	$f12,0x4c($sp)
/*    255b0:	46002207 */ 	neg.s	$f8,$f4
/*    255b4:	46009287 */ 	neg.s	$f10,$f18
/*    255b8:	44074000 */ 	mfc1	$a3,$f8
/*    255bc:	44065000 */ 	mfc1	$a2,$f10
/*    255c0:	0c009504 */ 	jal	func00025410
/*    255c4:	e7ae0048 */ 	swc1	$f14,0x48($sp)
/*    255c8:	afa20034 */ 	sw	$v0,0x34($sp)
/*    255cc:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*    255d0:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*    255d4:	c7b00068 */ 	lwc1	$f16,0x68($sp)
/*    255d8:	c7aa006c */ 	lwc1	$f10,0x6c($sp)
/*    255dc:	c7ac004c */ 	lwc1	$f12,0x4c($sp)
/*    255e0:	46068481 */ 	sub.s	$f18,$f16,$f6
/*    255e4:	c7ae0048 */ 	lwc1	$f14,0x48($sp)
/*    255e8:	46045201 */ 	sub.s	$f8,$f10,$f4
/*    255ec:	44069000 */ 	mfc1	$a2,$f18
/*    255f0:	44074000 */ 	mfc1	$a3,$f8
/*    255f4:	0c009504 */ 	jal	func00025410
/*    255f8:	00000000 */ 	nop
/*    255fc:	8fb80034 */ 	lw	$t8,0x34($sp)
/*    25600:	24030001 */ 	addiu	$v1,$zero,0x1
/*    25604:	03020019 */ 	multu	$t8,$v0
/*    25608:	0000c812 */ 	mflo	$t9
/*    2560c:	5f200003 */ 	bgtzl	$t9,.L0002561c
/*    25610:	8fa20070 */ 	lw	$v0,0x70($sp)
/*    25614:	afa3002c */ 	sw	$v1,0x2c($sp)
/*    25618:	8fa20070 */ 	lw	$v0,0x70($sp)
.L0002561c:
/*    2561c:	8fa3002c */ 	lw	$v1,0x2c($sp)
/*    25620:	8c480000 */ 	lw	$t0,0x0($v0)
/*    25624:	51000007 */ 	beqzl	$t0,.L00025644
/*    25628:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*    2562c:	14600003 */ 	bnez	$v1,.L0002563c
/*    25630:	8fa9003c */ 	lw	$t1,0x3c($sp)
/*    25634:	5d200003 */ 	bgtzl	$t1,.L00025644
/*    25638:	8fbf001c */ 	lw	$ra,0x1c($sp)
.L0002563c:
/*    2563c:	ac400000 */ 	sw	$zero,0x0($v0)
/*    25640:	8fbf001c */ 	lw	$ra,0x1c($sp)
.L00025644:
/*    25644:	8fb00018 */ 	lw	$s0,0x18($sp)
/*    25648:	27bd0058 */ 	addiu	$sp,$sp,0x58
/*    2564c:	03e00008 */ 	jr	$ra
/*    25650:	00601025 */ 	or	$v0,$v1,$zero
);

f32 func00025654(f32 x1, f32 z1, f32 x2, f32 z2, f32 x3, f32 z3)
{
	u32 stack[8];
	f32 result;

	result = sqrtf((x2 - x1) * (x2 - x1) + (z2 - z1) * (z2 - z1));

	if (result == 0.0f) {
		return sqrtf((x3 - x2) * (x3 - x2) + (z3 - z2) * (z3 - z2));
	}

	return ((x3 - x1) * (z2 - z1) + -(x2 - x1) * (z3 - z1)) / result;
}

f32 func00025724(f32 x1, f32 z1, f32 x2, f32 z2)
{
	x2 -= x1;
	z2 -= z1;

	return sqrtf(x2 * x2 + z2 * z2);
}

bool func00025774(f32 x1, f32 z1, f32 x2, f32 z2, f32 x3, f32 z3)
{
	f32 f0;
	f32 f2;
	f32 f16;
	f32 f18;

	x3 -= x1;
	z3 -= z1;

	f0 = x2 - x1;
	f2 = z2 - z1;

	f16 = x3 * f0 + z3 * f2;
	f18 = f0 * f0 + f2 * f2;

	return (f18 < f16 && f16 < 0) || (f16 > 0 && f16 < f18);
}

void func00025848(f32 tilex, f32 tilez, f32 tilewidth, f32 posx, f32 posz, f32 *x1, f32 *z1, f32 *x2, f32 *z2)
{
	posx -= tilex;
	posz -= tilez;

	if (posx != 0 || posz != 0) {
		f32 dist = sqrtf(posx * posx + posz * posz);

		if (dist > 0) {
			dist = tilewidth / dist;
			posx *= dist;
			posz *= dist;
		}
	}

	*x1 = tilex + posx + posz;
	*z1 = tilez + posz - posx;
	*x2 = tilex + posx - posz;
	*z2 = tilez + posz + posx;
}

void func00025928(struct tile *tile, struct coord *arg1)
{
	if (tile->type == TILETYPE_00) {
		struct tiletype0 *tile0 = (struct tiletype0 *) tile;
		s32 sp38[3];
		s32 sp2c[3];
		s32 sp20[3];

		sp38[0] = tile0->vertices[1][0] - tile0->vertices[0][0];
		sp38[1] = tile0->vertices[1][1] - tile0->vertices[0][1];
		sp38[2] = tile0->vertices[1][2] - tile0->vertices[0][2];

		sp2c[0] = tile0->vertices[2][0] - tile0->vertices[0][0];
		sp2c[1] = tile0->vertices[2][1] - tile0->vertices[0][1];
		sp2c[2] = tile0->vertices[2][2] - tile0->vertices[0][2];

		sp20[0] = sp38[1] * sp2c[2] - sp38[2] * sp2c[1];
		sp20[1] = sp38[2] * sp2c[0] - sp38[0] * sp2c[2];
		sp20[2] = sp38[0] * sp2c[1] - sp38[1] * sp2c[0];

		arg1->x = sp20[0];
		arg1->y = sp20[1];
		arg1->z = sp20[2];
	} else if (tile->type == TILETYPE_01) {
		struct tiletype1 *tile1 = (struct tiletype1 *) tile;
		f32 sp10[3];
		f32 sp04[3];

		sp10[0] = tile1->vertices[1].x - tile1->vertices[0].x;
		sp10[1] = tile1->vertices[1].y - tile1->vertices[0].y;
		sp10[2] = tile1->vertices[1].z - tile1->vertices[0].z;

		sp04[0] = tile1->vertices[2].x - tile1->vertices[0].x;
		sp04[1] = tile1->vertices[2].y - tile1->vertices[0].y;
		sp04[2] = tile1->vertices[2].z - tile1->vertices[0].z;

		arg1->x = sp10[1] * sp04[2] - sp10[2] * sp04[1];
		arg1->y = sp10[2] * sp04[0] - sp10[0] * sp04[2];
		arg1->z = sp10[0] * sp04[1] - sp10[1] * sp04[0];
	} else if (tile->type == TILETYPE_02) {
		arg1->x = 0;
		arg1->y = 1;
		arg1->z = 0;
	} else if (tile->type == TILETYPE_03) {
		arg1->x = 0;
		arg1->y = 1;
		arg1->z = 0;
	}
}

void tileGetFloorCol(struct tile *tile, u16 *floorcol)
{
	if (tile == NULL) {
		*floorcol = 0xfff;
		return;
	}

	if (tile->type == TILETYPE_00) {
		struct tiletype0 *tile0 = (struct tiletype0 *) tile;
		*floorcol = tile0->floorcol;
		return;
	}

	if (tile->type == TILETYPE_01) {
		struct tiletype1 *tile1 = (struct tiletype1 *) tile;
		*floorcol = tile1->floorcol;
		return;
	}

	if (tile->type == TILETYPE_02) {
		*floorcol = 0xfff;
		return;
	}

	if (tile->type == TILETYPE_03) {
		*floorcol = 0xfff;
	}
}

void tileGetFloorType(struct tile *tile, u8 *floortype)
{
	bool water = false;

	if (tile && (tile->flags & TILEFLAG_UNDERWATER)) {
		water = true;
	}

	if (tile == NULL) {
		*floortype = 0xff;
		return;
	}

	if (water) {
		*floortype = FLOORTYPE_WATER;
		return;
	}

	if (tile->type == TILETYPE_00) {
		struct tiletype0 *tile0 = (struct tiletype0 *) tile;
		*floortype = tile0->floortype;
		return;
	}

	if (tile->type == TILETYPE_01) {
		struct tiletype1 *tile1 = (struct tiletype1 *) tile;
		*floortype = tile1->floortype;
		return;
	}

	if (tile->type == TILETYPE_02) {
		*floortype = 0xff;
		return;
	}

	if (tile->type == TILETYPE_03) {
		*floortype = 0xff;
	}
}

f32 cdFindGroundInTileType0AtVertex(struct tiletype0 *tile, f32 x, f32 z, s32 vertexindex)
{
	struct coord sp7c;
	struct coord sp70;
	s64 sp68;
	s64 sp60;
	s64 sp58;
	s64 tmp;
	f32 ground;
	s32 next;

	if (vertexindex == 0) {
		vertexindex = 1;
	}

	next = (vertexindex + 1) % tile->header.numvertices;

	if (next == 0) {
		next = 1;
	}

	sp7c.x = tile->vertices[vertexindex][0] - tile->vertices[0][0];
	sp7c.y = tile->vertices[vertexindex][1] - tile->vertices[0][1];
	sp7c.z = tile->vertices[vertexindex][2] - tile->vertices[0][2];

	sp70.x = tile->vertices[next][0] - tile->vertices[0][0];
	sp70.y = tile->vertices[next][1] - tile->vertices[0][1];
	sp70.z = tile->vertices[next][2] - tile->vertices[0][2];

	sp58 = sp7c.f[1] * sp70.f[2] - sp7c.f[2] * sp70.f[1];
	sp60 = sp7c.f[2] * sp70.f[0] - sp7c.f[0] * sp70.f[2];
	sp68 = sp7c.f[0] * sp70.f[1] - sp7c.f[1] * sp70.f[0];

	tmp = sp58 * tile->vertices[0][0]
		+ sp60 * tile->vertices[0][1]
		+ sp68 * tile->vertices[0][2];

	if (sp60 == 0) {
		return *(s16 *)(tile->ymax + (u32)tile);
	}

	ground = (tmp - (f64)x * sp58 - (f64)z * sp68) / sp60;

	if (ground > *(s16 *)(tile->ymax + (u32)tile)) {
		ground = *(s16 *)(tile->ymax + (u32)tile);
	} else if (ground < *(s16 *)(tile->ymin + (u32)tile)) {
		ground = *(s16 *)(tile->ymin + (u32)tile);
	}

	return ground;
}

#if VERSION < VERSION_NTSC_1_0
f32 cdFindGroundInTileType0AtVertex1(struct tiletype0 *tile, f32 x, f32 z)
{
	return cdFindGroundInTileType0AtVertex(tile, x, z, 1);
}
#endif

GLOBAL_ASM(
glabel cdFindGroundInTileType0
/*    25f90:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*    25f94:	f7b40010 */ 	sdc1	$f20,0x10($sp)
/*    25f98:	4485a000 */ 	mtc1	$a1,$f20
/*    25f9c:	afbf0024 */ 	sw	$ra,0x24($sp)
/*    25fa0:	f7b60018 */ 	sdc1	$f22,0x18($sp)
/*    25fa4:	90850001 */ 	lbu	$a1,0x1($a0)
/*    25fa8:	4486b000 */ 	mtc1	$a2,$f22
/*    25fac:	24070001 */ 	addiu	$a3,$zero,0x1
/*    25fb0:	28a10004 */ 	slti	$at,$a1,0x4
/*    25fb4:	1420003c */ 	bnez	$at,.L000260a8
/*    25fb8:	2403ffff */ 	addiu	$v1,$zero,-1
/*    25fbc:	28a10002 */ 	slti	$at,$a1,0x2
/*    25fc0:	14200039 */ 	bnez	$at,.L000260a8
/*    25fc4:	00077880 */ 	sll	$t7,$a3,0x2
/*    25fc8:	848e0012 */ 	lh	$t6,0x12($a0)
/*    25fcc:	8498000e */ 	lh	$t8,0xe($a0)
/*    25fd0:	01e77823 */ 	subu	$t7,$t7,$a3
/*    25fd4:	448e2000 */ 	mtc1	$t6,$f4
/*    25fd8:	44983000 */ 	mtc1	$t8,$f6
/*    25fdc:	000f7840 */ 	sll	$t7,$t7,0x1
/*    25fe0:	44807000 */ 	mtc1	$zero,$f14
/*    25fe4:	008f1021 */ 	addu	$v0,$a0,$t7
/*    25fe8:	46802420 */ 	cvt.s.w	$f16,$f4
/*    25fec:	468034a0 */ 	cvt.s.w	$f18,$f6
.L00025ff0:
/*    25ff0:	84590012 */ 	lh	$t9,0x12($v0)
/*    25ff4:	8448000e */ 	lh	$t0,0xe($v0)
/*    25ff8:	44994000 */ 	mtc1	$t9,$f8
/*    25ffc:	44885000 */ 	mtc1	$t0,$f10
/*    26000:	46804020 */ 	cvt.s.w	$f0,$f8
/*    26004:	468050a0 */ 	cvt.s.w	$f2,$f10
/*    26008:	46008101 */ 	sub.s	$f4,$f16,$f0
/*    2600c:	4602a181 */ 	sub.s	$f6,$f20,$f2
/*    26010:	4600b281 */ 	sub.s	$f10,$f22,$f0
/*    26014:	46062202 */ 	mul.s	$f8,$f4,$f6
/*    26018:	46029101 */ 	sub.s	$f4,$f18,$f2
/*    2601c:	46045182 */ 	mul.s	$f6,$f10,$f4
/*    26020:	46064301 */ 	sub.s	$f12,$f8,$f6
/*    26024:	460e6032 */ 	c.eq.s	$f12,$f14
/*    26028:	00000000 */ 	nop
/*    2602c:	4503001b */ 	bc1tl	.L0002609c
/*    26030:	24e70001 */ 	addiu	$a3,$a3,0x1
/*    26034:	04610008 */ 	bgez	$v1,.L00026058
/*    26038:	00000000 */ 	nop
/*    2603c:	460c703c */ 	c.lt.s	$f14,$f12
/*    26040:	00001825 */ 	or	$v1,$zero,$zero
/*    26044:	45020015 */ 	bc1fl	.L0002609c
/*    26048:	24e70001 */ 	addiu	$a3,$a3,0x1
/*    2604c:	24030001 */ 	addiu	$v1,$zero,0x1
/*    26050:	10000012 */ 	b	.L0002609c
/*    26054:	24e70001 */ 	addiu	$a3,$a3,0x1
.L00026058:
/*    26058:	10600007 */ 	beqz	$v1,.L00026078
/*    2605c:	00000000 */ 	nop
/*    26060:	460e603c */ 	c.lt.s	$f12,$f14
/*    26064:	00000000 */ 	nop
/*    26068:	45000003 */ 	bc1f	.L00026078
/*    2606c:	00000000 */ 	nop
/*    26070:	1000000d */ 	b	.L000260a8
/*    26074:	24e7ffff */ 	addiu	$a3,$a3,-1
.L00026078:
/*    26078:	54600008 */ 	bnezl	$v1,.L0002609c
/*    2607c:	24e70001 */ 	addiu	$a3,$a3,0x1
/*    26080:	460c703c */ 	c.lt.s	$f14,$f12
/*    26084:	00000000 */ 	nop
/*    26088:	45020004 */ 	bc1fl	.L0002609c
/*    2608c:	24e70001 */ 	addiu	$a3,$a3,0x1
/*    26090:	10000005 */ 	b	.L000260a8
/*    26094:	24e7ffff */ 	addiu	$a3,$a3,-1
/*    26098:	24e70001 */ 	addiu	$a3,$a3,0x1
.L0002609c:
/*    2609c:	00e5082a */ 	slt	$at,$a3,$a1
/*    260a0:	1420ffd3 */ 	bnez	$at,.L00025ff0
/*    260a4:	24420006 */ 	addiu	$v0,$v0,0x6
.L000260a8:
/*    260a8:	4405a000 */ 	mfc1	$a1,$f20
/*    260ac:	4406b000 */ 	mfc1	$a2,$f22
/*    260b0:	0c00971d */ 	jal	cdFindGroundInTileType0AtVertex
/*    260b4:	00000000 */ 	nop
/*    260b8:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*    260bc:	d7b40010 */ 	ldc1	$f20,0x10($sp)
/*    260c0:	d7b60018 */ 	ldc1	$f22,0x18($sp)
/*    260c4:	03e00008 */ 	jr	$ra
/*    260c8:	27bd0028 */ 	addiu	$sp,$sp,0x28
);

// Mismatch: regalloc, and operators for second mult are swapped
//f32 cdFindGroundInTileType0(struct tiletype0 *tile, f32 x, f32 z)
//{
//	s32 i = 1;
//	s32 ival = -1;
//	f32 tmpx;
//	f32 tmpz;
//	f32 fval;
//
//	if (tile->header.numvertices >= 4) {
//		while (i < tile->header.numvertices) { \
//			tmpz = tile->vertices[i][2];
//			tmpx = tile->vertices[i][0];
//
//			fval =
//				(tile->vertices[0][2] - tmpz) * (x - tmpx) -
//				(tile->vertices[0][0] - tmpx) * (z - tmpz);
//
//			if (fval != 0) {
//				if (ival < 0) {
//					ival = (fval > 0);
//				} else if (ival != 0 && fval < 0) {
//					i--;
//					break;
//				} else if (ival == 0 && fval > 0) {
//					i--;
//					break;
//				}
//			}
//
//			i++;
//		}
//	}
//
//	return cdFindGroundInTileType0AtVertex(tile, x, z, i);
//}

f32 cdFindGroundInTileType1(struct tiletype1 *tile, f32 x, f32 z)
{
	struct coord sp24;
	struct coord sp18;
	struct coord sp0c;
	f32 tmp;
	f32 ground;

	sp24.x = tile->vertices[1].x - tile->vertices[0].x;
	sp24.y = tile->vertices[1].y - tile->vertices[0].y;
	sp24.z = tile->vertices[1].z - tile->vertices[0].z;

	sp18.x = tile->vertices[2].x - tile->vertices[0].x;
	sp18.y = tile->vertices[2].y - tile->vertices[0].y;
	sp18.z = tile->vertices[2].z - tile->vertices[0].z;

	sp0c.x = sp24.f[1] * sp18.f[2] - sp24.f[2] * sp18.f[1];
	sp0c.y = sp24.f[2] * sp18.f[0] - sp24.f[0] * sp18.f[2];
	sp0c.z = sp24.f[0] * sp18.f[1] - sp24.f[1] * sp18.f[0];

	tmp = sp0c.f[0] * tile->vertices[0].f[0]
		+ sp0c.f[1] * tile->vertices[0].f[1]
		+ sp0c.f[2] * tile->vertices[0].f[2];

	if (sp0c.f[1] == 0) {
		return tile->vertices[tile->ymax].y;
	}

	ground = (tmp - (f64)x * (f64)sp0c.f[0] - (f64)z * (f64)sp0c.f[2]) / (f64)sp0c.f[1];

	if (ground > tile->vertices[tile->ymax].y) {
		ground = tile->vertices[tile->ymax].y;
	} else if (ground < tile->vertices[tile->ymin].y) {
		ground = tile->vertices[tile->ymin].y;
	}

	return ground;
}

bool cdIs2dPointInTileType0(struct tiletype0 *tile, f32 x, f32 z)
{
	s32 result = -1;
	s32 numvertices = tile->header.numvertices;
	s32 i;

	for (i = 0; i < numvertices; i++) {
		s32 next = (i + 1) % numvertices;

		f32 value = ((f32)tile->vertices[next][2] - (f32)tile->vertices[i][2]) * (x - tile->vertices[i][0])
			- ((f32)tile->vertices[next][0] - (f32)tile->vertices[i][0]) * (z - tile->vertices[i][2]);

		if (value != 0) {
			if (i == 0 || result < 0) {
				result = (value > 0);
			} else {
				if (result != 0 && value < 0) {
					return false;
				}

				if (result == 0 && value > 0) {
					return false;
				}
			}
		}
	}

	if (result < 0) {
		return false;
	}

	return true;
}

bool cdIs2dPointInTileType1(struct tiletype1 *tile, f32 x, f32 z)
{
	s32 result = -1;
	s32 numvertices = tile->header.numvertices;
	s32 i;

	for (i = 0; i < numvertices; i++) {
		s32 next = (i + 1) % numvertices;

		f32 value = (tile->vertices[next].z - tile->vertices[i].z) * (x - tile->vertices[i].x)
			- (tile->vertices[next].x - tile->vertices[i].x) * (z - tile->vertices[i].z);

		if (value != 0) {
			if (i == 0 || result < 0) {
				result = (value > 0);
			} else {
				if (result != 0 && value < 0) {
					return false;
				}

				if (result == 0 && value > 0) {
					return false;
				}
			}
		}
	}

	if (result < 0) {
		return false;
	}

	return true;
}

bool cdIs2dPointInTileType2(struct tiletype2 *tile, f32 x, f32 z)
{
	s32 result = -1;
	s32 numvertices = tile->header.numvertices;
	s32 i;

	for (i = 0; i < numvertices; i++) {
		s32 next = (i + 1) % numvertices;

		f32 value = (tile->vertices[next][1] - tile->vertices[i][1]) * (x - tile->vertices[i][0])
			- (tile->vertices[next][0] - tile->vertices[i][0]) * (z - tile->vertices[i][1]);

		if (value != 0) {
			if (i == 0 || result < 0) {
				result = (value > 0);
			} else {
				if (result != 0 && value < 0) {
					return false;
				}

				if (result == 0 && value > 0) {
					return false;
				}
			}
		}
	}

	if (result < 0) {
		return false;
	}

	return true;
}

bool cdIs2dPointInTileType3(struct tiletype3 *tile, f32 x, f32 z)
{
	f32 xdiff = x - tile->x;
	f32 zdiff = z - tile->z;

	return xdiff * xdiff + zdiff * zdiff <= tile->width * tile->width;
}

bool func000266a4(f32 x, f32 z, struct tile *tile)
{
	if (tile == NULL) {
		return false;
	}

	if (tile->type == TILETYPE_02) {
		return cdIs2dPointInTileType2((struct tiletype2 *) tile, x, z);
	}

	if (tile->type == TILETYPE_03) {
		return cdIs2dPointInTileType3((struct tiletype3 *) tile, x, z);
	}

	return false;
}

/**
 * For a lift or escalator step, find the props which are riding on it.
 */
void platformGetRidingProps(struct prop *platform, s16 *propnums, s32 maxlen)
{
	u8 *start;
	u8 *end;
	s16 roompropnums[257];
	struct prop *prop;
	s16 *roompropnumptr;
	struct tile *tile;
	s32 len = 0;

	if (propUpdateGeometry(platform, &start, &end)) {
		roomGetProps(platform->rooms, roompropnums, 256);
		roompropnumptr = roompropnums;

		while (*roompropnumptr >= 0) {
			prop = &g_Vars.props[*roompropnumptr];

			if (prop != platform) {
				tile = (struct tile *) start;

				while (tile < (struct tile *) end) {
					if (tile->type == TILETYPE_00) {
						struct tiletype0 *type0 = (struct tiletype0 *) tile;
						tile = (struct tile *)((u32)tile + sizeof(struct tiletype0) + sizeof(type0->vertices[0]) * (type0->header.numvertices - ARRAYCOUNT(type0->vertices)));
					} else if (tile->type == TILETYPE_01) {
						struct tiletype1 *type1 = (struct tiletype1 *) tile;
						struct coord *pos = &prop->pos;

						if ((tile->flags & (TILEFLAG_0001 | TILEFLAG_0002))
								&& pos->x >= type1->vertices[type1->xmin].x
								&& pos->x <= type1->vertices[type1->xmax].x
								&& pos->z >= type1->vertices[type1->zmin].z
								&& pos->z <= type1->vertices[type1->zmax].z
								&& pos->y >= type1->vertices[type1->ymin].y
								&& cdIs2dPointInTileType1(type1, pos->x, pos->z)
								&& pos->y >= cdFindGroundInTileType1(type1, pos->x, pos->z)) {
							break;
						}

						tile = (struct tile *)((u32)tile + sizeof(struct tiletype1) + sizeof(struct coord) * (type1->header.numvertices - ARRAYCOUNT(type1->vertices)));
					} else if (tile->type == TILETYPE_02) {
						tile = (struct tile *)((u32)tile + sizeof(struct tiletype2));
					} else if (tile->type == TILETYPE_03) {
						tile = (struct tile *)((u32)tile + sizeof(struct tiletype3));
					}
				}

				if (tile < (struct tile *) end) {
					if (len < maxlen - 2) {
						propnums[len] = *roompropnumptr;
						len++;
					} else {
						break;
					}
				}
			}

			roompropnumptr++;
		}
	}

	propnums[len] = -1;
}

#if VERSION < VERSION_NTSC_1_0
void cdSetPropYBounds(struct prop *prop, f32 ymax, f32 ymin)
{
	u8 *start;
	u8 *end;

	if (propUpdateGeometry(prop, &start, &end)) {
		struct tile *tile = (struct tile *) start;

		while (tile < (struct tile *) end) {
			if (tile->type == TILETYPE_00) {
				struct tiletype0 *type0 = (struct tiletype0 *) tile;
				tile = (struct tile *)((u32)tile + sizeof(struct tiletype0) + sizeof(type0->vertices[0]) * (type0->header.numvertices - ARRAYCOUNT(type0->vertices)));
			} else if (tile->type == TILETYPE_01) {
				struct tiletype1 *type1 = (struct tiletype1 *) tile;
				tile = (struct tile *)((u32)tile + sizeof(struct tiletype1) + sizeof(struct coord) * (type1->header.numvertices - ARRAYCOUNT(type1->vertices)));
			} else if (tile->type == TILETYPE_02) {
				struct tiletype2 *type2 = (struct tiletype2 *) tile;
				type2->ymax = ymax;
				type2->ymin = ymin;
				tile = (struct tile *)((u32)tile + sizeof(struct tiletype2));
			} else if (tile->type == TILETYPE_03) {
				struct tiletype3 *type3 = (struct tiletype3 *) tile;
				type3->ymax = ymax;
				type3->ymin = ymin;
				tile = (struct tile *)((u32)tile + sizeof(struct tiletype3));
			}
		}
	}
}
#endif

bool func00026a04(struct coord *pos, u8 *start, u8 *end, u16 flags, s32 room, struct tile **tileptr, s32 *roomptr, f32 *groundptr, bool arg8)
{
	bool result = false;
	struct tile *tile = (struct tile *) start;

	if (room);

	while (tile < (struct tile *) end) {
		if (tile->type == TILETYPE_00) {
			struct tiletype0 *type0 = (struct tiletype0 *) tile;

			if ((tile->flags & flags)
					&& pos->x >= *(s16 *)(type0->xmin + (u32)type0)
					&& pos->x <= *(s16 *)(type0->xmax + (u32)type0)
					&& pos->z >= *(s16 *)(type0->zmin + (u32)type0)
					&& pos->z <= *(s16 *)(type0->zmax + (u32)type0)) {
				if ((!arg8 && pos->y >= *(s16 *)(type0->ymin + (u32)type0))
						|| (arg8 && pos->y <= *(s16 *)(type0->ymax + (u32)type0))) {
					if (cdIs2dPointInTileType0(type0, pos->x, pos->z)) {
						f32 ground = cdFindGroundInTileType0(type0, pos->x, pos->z);

						if ((!arg8 && ground <= pos->y && ground > *groundptr)
								|| (arg8 && ground >= pos->y && ground < *groundptr)) {
							*groundptr = ground;
							*tileptr = tile;
							*roomptr = room;
							result = true;
						}
					}
				}
			}

			tile = (struct tile *)((u32)tile + sizeof(struct tiletype0) + sizeof(type0->vertices[0]) * (type0->header.numvertices - ARRAYCOUNT(type0->vertices)));
		} else if (tile->type == TILETYPE_01) {
			struct tiletype1 *type1 = (struct tiletype1 *) tile;

			if ((tile->flags & flags)
					&& pos->x >= type1->vertices[type1->xmin].x
					&& pos->x <= type1->vertices[type1->xmax].x
					&& pos->z >= type1->vertices[type1->zmin].z
					&& pos->z <= type1->vertices[type1->zmax].z) {
				if ((!arg8 && pos->y >= type1->vertices[type1->ymin].y)
						|| (arg8 && pos->y <= type1->vertices[type1->ymax].y)) {
					if (cdIs2dPointInTileType1(type1, pos->x, pos->z)) {
						f32 ground = cdFindGroundInTileType1(type1, pos->x, pos->z);

						if ((!arg8 && pos->y >= ground && ground > *groundptr)
								|| (arg8 && pos->y <= ground && ground < *groundptr)) {
							*groundptr = ground;
							*tileptr = tile;
							*roomptr = room;
							result = true;
						}
					}
				}
			}

			tile = (struct tile *)((u32)tile + sizeof(struct tiletype1) + sizeof(struct coord) * (type1->header.numvertices - ARRAYCOUNT(type1->vertices)));
		} else if (tile->type == TILETYPE_02) {
			tile = (struct tile *)((u32)tile + sizeof(struct tiletype2));
		} else if (tile->type == TILETYPE_03) {
			tile = (struct tile *)((u32)tile + sizeof(struct tiletype3));
		}
	}

	return result;
}

void func00026e7c(struct coord *pos, s16 *rooms, u16 arg2, struct tile **tileptr, s16 *arg4, f32 *arg5, struct prop **arg6, s32 arg7)
{
	s16 *roomptr;
	s32 roomnum;
	u8 *start;
	u8 *end;
	f32 sp274;
	struct tile *sp270 = NULL;
	s32 sp26c = 0;
	struct prop *sp268 = NULL;
	s16 *propnumptr;
	s16 propnums[256];

	if (arg7) {
		sp274 = 4294967296;
	} else {
		sp274 = -4294967296;
	}

	roomptr = rooms;
	roomnum = rooms[0];

	while (roomnum != -1) {
		if (roomnum < g_TileNumRooms) {
			start = g_TileFileData.u8 + g_TileRooms[roomnum];
			end = g_TileFileData.u8 + g_TileRooms[roomnum + 1];

			func00026a04(pos, start, end, arg2, roomnum, &sp270, &sp26c, &sp274, arg7);
		}

		roomptr++;
		roomnum = *roomptr;
	}

	roomGetProps(rooms, propnums, 256);
	propnumptr = propnums;

	while (*propnumptr >= 0) {
		struct prop *prop = &g_Vars.props[*propnumptr];

		if (propUpdateGeometry(prop, &start, &end)
				&& func00026a04(pos, start, end, arg2, prop->rooms[0], &sp270, &sp26c, &sp274, arg7)) {
			sp268 = prop;
		}

		propnumptr++;
	}

	*tileptr = sp270;
	*arg4 = sp26c;
	*arg5 = sp274;

	if (arg6 != NULL) {
		*arg6 = sp268;
	}
}

bool func0002709c(struct tiletype0 *tile, f32 x, f32 z, f32 width, struct prop *prop, struct collisionthing *thing)
{
	bool result = false;

	if (cdIs2dPointInTileType0(tile, x, z)) {
		thing->tile = &tile->header;
		thing->unk08 = 0;
		thing->prop = prop;
		result = true;
	} else {
		s32 numvertices = tile->header.numvertices;
		s32 i;

		for (i = 0; i < numvertices; i++) {
			s32 next = (i + 1) % numvertices;
			f32 value = func00025654(tile->vertices[i][0], tile->vertices[i][2], tile->vertices[next][0], tile->vertices[next][2], x, z);

			if (value < 0) {
				value = -value;
			}

			if (value <= width
					&& (func00025724(tile->vertices[i][0], tile->vertices[i][2], x, z) <= width
						|| func00025724(tile->vertices[next][0], tile->vertices[next][2], x, z) <= width
						|| func00025774(tile->vertices[i][0], tile->vertices[i][2], tile->vertices[next][0], tile->vertices[next][2], x, z))) {
				thing->tile = &tile->header;
				thing->unk08 = i;
				thing->prop = prop;
				result = true;
				break;
			}
		}
	}

	return result;
}

bool func000272f8(struct tiletype1 *tile, f32 x, f32 z, f32 width, struct prop *prop, struct collisionthing *thing)
{
	bool result = false;

	if (cdIs2dPointInTileType1(tile, x, z)) {
		thing->tile = &tile->header;
		thing->unk08 = 0;
		thing->prop = prop;
		result = true;
	} else {
		s32 numvertices = tile->header.numvertices;
		s32 i;

		for (i = 0; i < numvertices; i++) {
			s32 next = (i + 1) % numvertices;
			f32 value = func00025654(tile->vertices[i].x, tile->vertices[i].z, tile->vertices[next].x, tile->vertices[next].z, x, z);

			if (value < 0) {
				value = -value;
			}

			if (value <= width
					&& (func00025724(tile->vertices[i].x, tile->vertices[i].z, x, z) <= width
						|| func00025724(tile->vertices[next].x, tile->vertices[next].z, x, z) <= width
						|| func00025774(tile->vertices[i].x, tile->vertices[i].z, tile->vertices[next].x, tile->vertices[next].z, x, z))) {
				thing->tile = &tile->header;
				thing->unk08 = i;
				thing->prop = prop;
				result = true;
				break;
			}
		}
	}

	return result;
}

s32 func000274e0(struct tiletype2 *tile, f32 x, f32 z, f32 width, struct prop *prop, struct collisionthing *thing)
{
	bool result = false;

	if (cdIs2dPointInTileType2(tile, x, z)) {
		if (thing) {
			thing->tile = &tile->header;
			thing->unk08 = 0;
			thing->prop = prop;
		}

		result = true;
	} else {
		s32 numvertices = tile->header.numvertices;
		s32 i;

		for (i = 0; i < numvertices; i++) {
			s32 next = (i + 1) % numvertices;
			f32 value = func00025654(tile->vertices[i][0], tile->vertices[i][1],
					tile->vertices[next][0], tile->vertices[next][1],
					x, z);

			if (value < 0) {
				value = -value;
			}

			if (value <= width
					&& (func00025724(tile->vertices[i][0], tile->vertices[i][1], x, z) <= width
						|| func00025724(tile->vertices[next][0], tile->vertices[next][1], x, z) <= width
						|| func00025774(tile->vertices[i][0], tile->vertices[i][1], tile->vertices[next][0], tile->vertices[next][1], x, z))) {
				if (thing) {
					thing->tile = &tile->header;
					thing->unk08 = i;
					thing->prop = prop;
				}

				result = true;
				break;
			}
		}
	}

	return result;
}

bool func000276c8(struct tiletype3 *tile, f32 x, f32 z, f32 width, struct prop *prop, struct collisionthing *thing)
{
	bool result = false;

	f32 sumx = x - tile->x;
	f32 sumz = z - tile->z;
	f32 sumwidth = tile->width + width;

	if (sumx * sumx + sumz * sumz <= sumwidth * sumwidth) {
		result = true;

		if (thing) {
			thing->tile = &tile->header;
			thing->unk08 = 0;
			thing->prop = prop;
		}
	}

	return result;
}

void func00027738(struct coord *pos, f32 width, u8 *start, u8 *end, u16 flags,
		bool checkvertical, f32 arg6, f32 arg7, struct prop *prop,
		struct collisionthing *things, s32 maxthings, s32 *thingnum, s32 roomnum)
{
	struct tile *tile = (struct tile *) start;
	s32 result;

	while (tile < (struct tile *) end) {
		if (tile->type == TILETYPE_00) {
			struct tiletype0 *type0 = (struct tiletype0 *) tile;

			if ((tile->flags & flags)
					&& pos->x >= *(s16 *)(type0->xmin + (u32)type0) - width
					&& pos->x <= *(s16 *)(type0->xmax + (u32)type0) + width
					&& pos->z >= *(s16 *)(type0->zmin + (u32)type0) - width
					&& pos->z <= *(s16 *)(type0->zmax + (u32)type0) + width
					&& (!checkvertical || (pos->y + arg6 >= *(s16 *)(type0->ymin + (u32)type0)
							&& pos->y + arg7 <= *(s16 *)(type0->ymax + (u32)type0)))) {
				if (tile->flags & TILEFLAG_0080) {
					result = func00028200(type0, pos, width, pos->y + arg7, pos->y + arg6);
				} else {
					result = 1;
				}

				if (result != 0) {
					if (func0002709c(type0, pos->x, pos->z, width, prop, &things[*thingnum])) {
						things[*thingnum].roomnum = roomnum;
						*thingnum = *thingnum + 1;

						if (*thingnum >= maxthings) {
							break;
						}
					}
				}
			}

			tile = (struct tile *)((u32)tile + type0->header.numvertices * 6 + 0xe);
		} else if (tile->type == TILETYPE_01) {
			struct tiletype1 *type1 = (struct tiletype1 *) tile;
			s32 tmp = 0x40;

			if ((tile->flags & flags)
					&& pos->x >= *(f32 *)((u32)type1 + type1->xmin * 0xc + 0x10) - width
					&& pos->x <= *(f32 *)((u32)type1 + type1->xmax * 0xc + 0x10) + width
					&& pos->z >= *(f32 *)((u32)type1 + type1->zmin * 0xc + 0x18) - width
					&& pos->z <= *(f32 *)((u32)type1 + type1->zmax * 0xc + 0x18) + width
					&& (!checkvertical || (pos->y + arg6 >= *(f32*)((u32)type1 + type1->ymin * 0xc + 0x14)
							&& pos->y + arg7 <= *(f32 *)((u32)type1 + type1->ymax * 0xc + 0x14)))) {
				result = func000272f8(type1, pos->x, pos->z, width, prop, &things[*thingnum]);

				if (result != 0) {
					things[*thingnum].roomnum = roomnum;
					*thingnum = *thingnum + 1;

					if (*thingnum >= maxthings) {
						break;
					}
				}
			}

			tile = (struct tile *)((u32)tile + (type1->header.numvertices - tmp) * 0xc + 0x310);
		} else if (tile->type == TILETYPE_02) {
			struct tiletype2 *tile2 = (struct tiletype2 *) tile;

			if ((flags & (TILEFLAG_0004 | TILEFLAG_0008 | TILEFLAG_0010))
					&& (!checkvertical || (pos->y + arg6 >= tile2->ymin
							&& pos->y + arg7 <= tile2->ymax))) {
				result = func000274e0(tile2, pos->x, pos->z, width, prop, &things[*thingnum]);

				if (result) {
					things[*thingnum].roomnum = roomnum;
					*thingnum = *thingnum + 1;

					if (*thingnum >= maxthings) {
						break;
					}
				}
			}

			tile = (struct tile *)((u32)tile + 0x4c);
		} else if (tile->type == TILETYPE_03) {
			struct tiletype3 *tile3 = (struct tiletype3 *) tile;

			if ((flags & tile->flags)
					&& (!checkvertical || (pos->y + arg6 >= tile3->ymin
							&& pos->y + arg7 <= tile3->ymax))) {
				result = func000276c8(tile3, pos->x, pos->z, width, prop, &things[*thingnum]);

				if (result) {
					things[*thingnum].roomnum = roomnum;
					*thingnum = *thingnum + 1;

					if (*thingnum >= maxthings) {
						break;
					}
				}
			}

			tile = (struct tile *)((u32)tile + 0x18);
		}
	}
}

void func00027d1c(struct coord *pos, f32 width, s16 *rooms, u32 types, u16 arg4, u32 arg5, f32 arg6, f32 arg7, struct collisionthing *arg8, s32 arg9)
{
	s16 *roomptr;
	s32 roomnum;
	u8 *start;
	u8 *end;
	s32 sp294 = 0;
	s16 *propnumptr;
	s16 propnums[256];

	// Check BG
	if (types & CDTYPE_BG) {
		roomptr = rooms;
		roomnum = rooms[0];

		while (roomnum != -1) {
			if (roomnum < g_TileNumRooms) {
				start = g_TileFileData.u8 + g_TileRooms[roomnum];
				end = g_TileFileData.u8 + g_TileRooms[roomnum + 1];

				func00027738(pos, width, start, end, arg4, arg5, arg6, arg7, NULL, arg8, arg9, &sp294, roomnum);

				if (sp294 >= arg9) {
					goto end;
				}
			}

			roomptr++;
			roomnum = *roomptr;
		}
	}

	// Check props
	roomGetProps(rooms, propnums, 256);
	propnumptr = propnums;

	while (*propnumptr >= 0) {
		struct prop *prop = &g_Vars.props[*propnumptr];

		if (propIsOfCdType(prop, types) && propUpdateGeometry(prop, &start, &end)) {
			func00027738(pos, width, start, end, arg4, arg5, arg6, arg7, prop, arg8, arg9, &sp294, prop->rooms[0]);

			if (sp294 >= arg9) {
				break;
			}
		}

		propnumptr++;
	}

end:
	arg8[sp294].tile = NULL;
}

GLOBAL_ASM(
glabel func00027f78
/*    27f78:	27bdff98 */ 	addiu	$sp,$sp,-104
/*    27f7c:	afbf0064 */ 	sw	$ra,0x64($sp)
/*    27f80:	afbe0060 */ 	sw	$s8,0x60($sp)
/*    27f84:	afb7005c */ 	sw	$s7,0x5c($sp)
/*    27f88:	afb60058 */ 	sw	$s6,0x58($sp)
/*    27f8c:	afb50054 */ 	sw	$s5,0x54($sp)
/*    27f90:	afb40050 */ 	sw	$s4,0x50($sp)
/*    27f94:	afb3004c */ 	sw	$s3,0x4c($sp)
/*    27f98:	afb20048 */ 	sw	$s2,0x48($sp)
/*    27f9c:	afb10044 */ 	sw	$s1,0x44($sp)
/*    27fa0:	afb00040 */ 	sw	$s0,0x40($sp)
/*    27fa4:	f7ba0038 */ 	sdc1	$f26,0x38($sp)
/*    27fa8:	f7b80030 */ 	sdc1	$f24,0x30($sp)
/*    27fac:	f7b60028 */ 	sdc1	$f22,0x28($sp)
/*    27fb0:	f7b40020 */ 	sdc1	$f20,0x20($sp)
/*    27fb4:	90970001 */ 	lbu	$s7,0x1($a0)
/*    27fb8:	4485a000 */ 	mtc1	$a1,$f20
/*    27fbc:	4486b000 */ 	mtc1	$a2,$f22
/*    27fc0:	4487c000 */ 	mtc1	$a3,$f24
/*    27fc4:	0080f025 */ 	or	$s8,$a0,$zero
/*    27fc8:	1ae0007d */ 	blez	$s7,.L000281c0
/*    27fcc:	00009825 */ 	or	$s3,$zero,$zero
/*    27fd0:	4480d000 */ 	mtc1	$zero,$f26
/*    27fd4:	00808825 */ 	or	$s1,$a0,$zero
/*    27fd8:	24160014 */ 	addiu	$s6,$zero,0x14
/*    27fdc:	8fb5007c */ 	lw	$s5,0x7c($sp)
/*    27fe0:	8fb20084 */ 	lw	$s2,0x84($sp)
.L00027fe4:
/*    27fe4:	26740001 */ 	addiu	$s4,$s3,0x1
/*    27fe8:	0297001a */ 	div	$zero,$s4,$s7
/*    27fec:	00007010 */ 	mfhi	$t6
/*    27ff0:	000e7880 */ 	sll	$t7,$t6,0x2
/*    27ff4:	01ee7823 */ 	subu	$t7,$t7,$t6
/*    27ff8:	000f7840 */ 	sll	$t7,$t7,0x1
/*    27ffc:	03cf8021 */ 	addu	$s0,$s8,$t7
/*    28000:	8603000e */ 	lh	$v1,0xe($s0)
/*    28004:	8622000e */ 	lh	$v0,0xe($s1)
/*    28008:	16e00002 */ 	bnez	$s7,.L00028014
/*    2800c:	00000000 */ 	nop
/*    28010:	0007000d */ 	break	0x7
.L00028014:
/*    28014:	2401ffff */ 	addiu	$at,$zero,-1
/*    28018:	16e10004 */ 	bne	$s7,$at,.L0002802c
/*    2801c:	3c018000 */ 	lui	$at,0x8000
/*    28020:	16810002 */ 	bne	$s4,$at,.L0002802c
/*    28024:	00000000 */ 	nop
/*    28028:	0006000d */ 	break	0x6
.L0002802c:
/*    2802c:	54430006 */ 	bnel	$v0,$v1,.L00028048
/*    28030:	86090012 */ 	lh	$t1,0x12($s0)
/*    28034:	86380012 */ 	lh	$t8,0x12($s1)
/*    28038:	86190012 */ 	lh	$t9,0x12($s0)
/*    2803c:	5319005e */ 	beql	$t8,$t9,.L000281b8
/*    28040:	02809825 */ 	or	$s3,$s4,$zero
/*    28044:	86090012 */ 	lh	$t1,0x12($s0)
.L00028048:
/*    28048:	44834000 */ 	mtc1	$v1,$f8
/*    2804c:	86280012 */ 	lh	$t0,0x12($s1)
/*    28050:	44895000 */ 	mtc1	$t1,$f10
/*    28054:	46804220 */ 	cvt.s.w	$f8,$f8
/*    28058:	44822000 */ 	mtc1	$v0,$f4
/*    2805c:	44883000 */ 	mtc1	$t0,$f6
/*    28060:	e7b60014 */ 	swc1	$f22,0x14($sp)
/*    28064:	e7b40010 */ 	swc1	$f20,0x10($sp)
/*    28068:	468052a0 */ 	cvt.s.w	$f10,$f10
/*    2806c:	44064000 */ 	mfc1	$a2,$f8
/*    28070:	46802320 */ 	cvt.s.w	$f12,$f4
/*    28074:	44075000 */ 	mfc1	$a3,$f10
/*    28078:	0c009595 */ 	jal	func00025654
/*    2807c:	468033a0 */ 	cvt.s.w	$f14,$f6
/*    28080:	461a003c */ 	c.lt.s	$f0,$f26
/*    28084:	46000086 */ 	mov.s	$f2,$f0
/*    28088:	45020003 */ 	bc1fl	.L00028098
/*    2808c:	4618103e */ 	c.le.s	$f2,$f24
/*    28090:	46000087 */ 	neg.s	$f2,$f0
/*    28094:	4618103e */ 	c.le.s	$f2,$f24
.L00028098:
/*    28098:	00000000 */ 	nop
/*    2809c:	45020046 */ 	bc1fl	.L000281b8
/*    280a0:	02809825 */ 	or	$s3,$s4,$zero
/*    280a4:	862a000e */ 	lh	$t2,0xe($s1)
/*    280a8:	862b0012 */ 	lh	$t3,0x12($s1)
/*    280ac:	4406a000 */ 	mfc1	$a2,$f20
/*    280b0:	448a8000 */ 	mtc1	$t2,$f16
/*    280b4:	448b9000 */ 	mtc1	$t3,$f18
/*    280b8:	4407b000 */ 	mfc1	$a3,$f22
/*    280bc:	46808320 */ 	cvt.s.w	$f12,$f16
/*    280c0:	0c0095c9 */ 	jal	func00025724
/*    280c4:	468093a0 */ 	cvt.s.w	$f14,$f18
/*    280c8:	4618003e */ 	c.le.s	$f0,$f24
/*    280cc:	00000000 */ 	nop
/*    280d0:	45030022 */ 	bc1tl	.L0002815c
/*    280d4:	8e420000 */ 	lw	$v0,0x0($s2)
/*    280d8:	860c000e */ 	lh	$t4,0xe($s0)
/*    280dc:	860d0012 */ 	lh	$t5,0x12($s0)
/*    280e0:	4406a000 */ 	mfc1	$a2,$f20
/*    280e4:	448c2000 */ 	mtc1	$t4,$f4
/*    280e8:	448d3000 */ 	mtc1	$t5,$f6
/*    280ec:	4407b000 */ 	mfc1	$a3,$f22
/*    280f0:	46802320 */ 	cvt.s.w	$f12,$f4
/*    280f4:	0c0095c9 */ 	jal	func00025724
/*    280f8:	468033a0 */ 	cvt.s.w	$f14,$f6
/*    280fc:	4618003e */ 	c.le.s	$f0,$f24
/*    28100:	00000000 */ 	nop
/*    28104:	45030015 */ 	bc1tl	.L0002815c
/*    28108:	8e420000 */ 	lw	$v0,0x0($s2)
/*    2810c:	8618000e */ 	lh	$t8,0xe($s0)
/*    28110:	86190012 */ 	lh	$t9,0x12($s0)
/*    28114:	862e000e */ 	lh	$t6,0xe($s1)
/*    28118:	44988000 */ 	mtc1	$t8,$f16
/*    2811c:	44999000 */ 	mtc1	$t9,$f18
/*    28120:	862f0012 */ 	lh	$t7,0x12($s1)
/*    28124:	46808420 */ 	cvt.s.w	$f16,$f16
/*    28128:	448e4000 */ 	mtc1	$t6,$f8
/*    2812c:	448f5000 */ 	mtc1	$t7,$f10
/*    28130:	e7b60014 */ 	swc1	$f22,0x14($sp)
/*    28134:	e7b40010 */ 	swc1	$f20,0x10($sp)
/*    28138:	468094a0 */ 	cvt.s.w	$f18,$f18
/*    2813c:	44068000 */ 	mfc1	$a2,$f16
/*    28140:	46804320 */ 	cvt.s.w	$f12,$f8
/*    28144:	44079000 */ 	mfc1	$a3,$f18
/*    28148:	0c0095dd */ 	jal	func00025774
/*    2814c:	468053a0 */ 	cvt.s.w	$f14,$f10
/*    28150:	50400019 */ 	beqzl	$v0,.L000281b8
/*    28154:	02809825 */ 	or	$s3,$s4,$zero
/*    28158:	8e420000 */ 	lw	$v0,0x0($s2)
.L0002815c:
/*    2815c:	8fa80080 */ 	lw	$t0,0x80($sp)
/*    28160:	0048082a */ 	slt	$at,$v0,$t0
/*    28164:	50200017 */ 	beqzl	$at,.L000281c4
/*    28168:	8fbf0064 */ 	lw	$ra,0x64($sp)
/*    2816c:	00560019 */ 	multu	$v0,$s6
/*    28170:	00004812 */ 	mflo	$t1
/*    28174:	02a95021 */ 	addu	$t2,$s5,$t1
/*    28178:	ad5e0000 */ 	sw	$s8,0x0($t2)
/*    2817c:	8e4b0000 */ 	lw	$t3,0x0($s2)
/*    28180:	01760019 */ 	multu	$t3,$s6
/*    28184:	00006012 */ 	mflo	$t4
/*    28188:	02ac6821 */ 	addu	$t5,$s5,$t4
/*    2818c:	adb30008 */ 	sw	$s3,0x8($t5)
/*    28190:	8e4f0000 */ 	lw	$t7,0x0($s2)
/*    28194:	8fae0078 */ 	lw	$t6,0x78($sp)
/*    28198:	01f60019 */ 	multu	$t7,$s6
/*    2819c:	0000c012 */ 	mflo	$t8
/*    281a0:	02b8c821 */ 	addu	$t9,$s5,$t8
/*    281a4:	af2e000c */ 	sw	$t6,0xc($t9)
/*    281a8:	8e480000 */ 	lw	$t0,0x0($s2)
/*    281ac:	25090001 */ 	addiu	$t1,$t0,0x1
/*    281b0:	ae490000 */ 	sw	$t1,0x0($s2)
/*    281b4:	02809825 */ 	or	$s3,$s4,$zero
.L000281b8:
/*    281b8:	1697ff8a */ 	bne	$s4,$s7,.L00027fe4
/*    281bc:	26310006 */ 	addiu	$s1,$s1,0x6
.L000281c0:
/*    281c0:	8fbf0064 */ 	lw	$ra,0x64($sp)
.L000281c4:
/*    281c4:	d7b40020 */ 	ldc1	$f20,0x20($sp)
/*    281c8:	d7b60028 */ 	ldc1	$f22,0x28($sp)
/*    281cc:	d7b80030 */ 	ldc1	$f24,0x30($sp)
/*    281d0:	d7ba0038 */ 	ldc1	$f26,0x38($sp)
/*    281d4:	8fb00040 */ 	lw	$s0,0x40($sp)
/*    281d8:	8fb10044 */ 	lw	$s1,0x44($sp)
/*    281dc:	8fb20048 */ 	lw	$s2,0x48($sp)
/*    281e0:	8fb3004c */ 	lw	$s3,0x4c($sp)
/*    281e4:	8fb40050 */ 	lw	$s4,0x50($sp)
/*    281e8:	8fb50054 */ 	lw	$s5,0x54($sp)
/*    281ec:	8fb60058 */ 	lw	$s6,0x58($sp)
/*    281f0:	8fb7005c */ 	lw	$s7,0x5c($sp)
/*    281f4:	8fbe0060 */ 	lw	$s8,0x60($sp)
/*    281f8:	03e00008 */ 	jr	$ra
/*    281fc:	27bd0068 */ 	addiu	$sp,$sp,0x68
);

s32 func00028200(struct tiletype0 *tile, struct coord *pos, f32 width, f32 y1, f32 y2)
{
	s32 count;
	s32 i;
	s32 y1count;
	s32 y2count;
	s32 numverts;

	if (!g_Vars.enableslopes && (tile->header.flags & TILEFLAG_0100)) {
		return 0;
	}

	numverts = tile->header.numvertices;
	y2count = 0;
	y1count = 0;
	count = 0;

	for (i = 0; i < numverts; i++) {
		s32 next = i + 1;
		s32 last = numverts - 1;
		f32 posval;
		f32 thisvals[2];
		f32 nextvals[2];
		f32 somefloat;
		f32 somefloat2;
		s32 xdiff;
		s32 zdiff;

		if (i == last) {
			next = 0;
		}

		xdiff = tile->vertices[next][0] - tile->vertices[i][0];
		zdiff = tile->vertices[next][2] - tile->vertices[i][2];

		if (xdiff < 0) {
			xdiff = -xdiff;
		}

		if (zdiff < 0) {
			zdiff = -zdiff;
		}

		if (xdiff || zdiff) {
			thisvals[1] = tile->vertices[i][1];
			nextvals[1] = tile->vertices[next][1];

			if (zdiff < xdiff) {
				thisvals[0] = tile->vertices[i][0];
				nextvals[0] = tile->vertices[next][0];
				posval = pos->x;
			} else {
				thisvals[0] = tile->vertices[i][2];
				nextvals[0] = tile->vertices[next][2];
				posval = pos->z;
			}

			somefloat = (posval - thisvals[0]) / (nextvals[0] - thisvals[0]);

			if (somefloat <= 1.0f && somefloat >= 0.0f) {
				somefloat2 = thisvals[1] + (nextvals[1] - thisvals[1]) * somefloat;

				if (somefloat2 >= y2 - 1.0f) {
					y2count++;

					if (y1count != 0) {
						count++;
					}
				} else if (somefloat2 <= y1 + 1.0f) {
					y1count++;

					if (y2count != 0) {
						count++;
					}
				} else {
					count++;
				}
			}
		}
	}

	return count;
}

GLOBAL_ASM(
glabel func0002840c
/*    2840c:	27bdff98 */ 	addiu	$sp,$sp,-104
/*    28410:	afbf0064 */ 	sw	$ra,0x64($sp)
/*    28414:	afbe0060 */ 	sw	$s8,0x60($sp)
/*    28418:	afb7005c */ 	sw	$s7,0x5c($sp)
/*    2841c:	afb60058 */ 	sw	$s6,0x58($sp)
/*    28420:	afb50054 */ 	sw	$s5,0x54($sp)
/*    28424:	afb40050 */ 	sw	$s4,0x50($sp)
/*    28428:	afb3004c */ 	sw	$s3,0x4c($sp)
/*    2842c:	afb20048 */ 	sw	$s2,0x48($sp)
/*    28430:	afb10044 */ 	sw	$s1,0x44($sp)
/*    28434:	afb00040 */ 	sw	$s0,0x40($sp)
/*    28438:	f7ba0038 */ 	sdc1	$f26,0x38($sp)
/*    2843c:	f7b80030 */ 	sdc1	$f24,0x30($sp)
/*    28440:	f7b60028 */ 	sdc1	$f22,0x28($sp)
/*    28444:	f7b40020 */ 	sdc1	$f20,0x20($sp)
/*    28448:	90970001 */ 	lbu	$s7,0x1($a0)
/*    2844c:	4485a000 */ 	mtc1	$a1,$f20
/*    28450:	4486b000 */ 	mtc1	$a2,$f22
/*    28454:	4487c000 */ 	mtc1	$a3,$f24
/*    28458:	0080f025 */ 	or	$s8,$a0,$zero
/*    2845c:	1ae00066 */ 	blez	$s7,.L000285f8
/*    28460:	00009825 */ 	or	$s3,$zero,$zero
/*    28464:	4480d000 */ 	mtc1	$zero,$f26
/*    28468:	00808825 */ 	or	$s1,$a0,$zero
/*    2846c:	24160014 */ 	addiu	$s6,$zero,0x14
/*    28470:	8fb5007c */ 	lw	$s5,0x7c($sp)
/*    28474:	8fb20084 */ 	lw	$s2,0x84($sp)
.L00028478:
/*    28478:	26740001 */ 	addiu	$s4,$s3,0x1
/*    2847c:	0297001a */ 	div	$zero,$s4,$s7
/*    28480:	00007010 */ 	mfhi	$t6
/*    28484:	000e7880 */ 	sll	$t7,$t6,0x2
/*    28488:	01ee7823 */ 	subu	$t7,$t7,$t6
/*    2848c:	000f7880 */ 	sll	$t7,$t7,0x2
/*    28490:	03cf8021 */ 	addu	$s0,$s8,$t7
/*    28494:	c6000010 */ 	lwc1	$f0,0x10($s0)
/*    28498:	c62c0010 */ 	lwc1	$f12,0x10($s1)
/*    2849c:	16e00002 */ 	bnez	$s7,.L000284a8
/*    284a0:	00000000 */ 	nop
/*    284a4:	0007000d */ 	break	0x7
.L000284a8:
/*    284a8:	2401ffff */ 	addiu	$at,$zero,-1
/*    284ac:	16e10004 */ 	bne	$s7,$at,.L000284c0
/*    284b0:	3c018000 */ 	lui	$at,0x8000
/*    284b4:	16810002 */ 	bne	$s4,$at,.L000284c0
/*    284b8:	00000000 */ 	nop
/*    284bc:	0006000d */ 	break	0x6
.L000284c0:
/*    284c0:	46006032 */ 	c.eq.s	$f12,$f0
/*    284c4:	00000000 */ 	nop
/*    284c8:	45020008 */ 	bc1fl	.L000284ec
/*    284cc:	c62e0018 */ 	lwc1	$f14,0x18($s1)
/*    284d0:	c6240018 */ 	lwc1	$f4,0x18($s1)
/*    284d4:	c6060018 */ 	lwc1	$f6,0x18($s0)
/*    284d8:	46062032 */ 	c.eq.s	$f4,$f6
/*    284dc:	00000000 */ 	nop
/*    284e0:	45030043 */ 	bc1tl	.L000285f0
/*    284e4:	02809825 */ 	or	$s3,$s4,$zero
/*    284e8:	c62e0018 */ 	lwc1	$f14,0x18($s1)
.L000284ec:
/*    284ec:	44060000 */ 	mfc1	$a2,$f0
/*    284f0:	8e070018 */ 	lw	$a3,0x18($s0)
/*    284f4:	e7b60014 */ 	swc1	$f22,0x14($sp)
/*    284f8:	0c009595 */ 	jal	func00025654
/*    284fc:	e7b40010 */ 	swc1	$f20,0x10($sp)
/*    28500:	461a003c */ 	c.lt.s	$f0,$f26
/*    28504:	46000086 */ 	mov.s	$f2,$f0
/*    28508:	45020003 */ 	bc1fl	.L00028518
/*    2850c:	4618103e */ 	c.le.s	$f2,$f24
/*    28510:	46000087 */ 	neg.s	$f2,$f0
/*    28514:	4618103e */ 	c.le.s	$f2,$f24
.L00028518:
/*    28518:	00000000 */ 	nop
/*    2851c:	45020034 */ 	bc1fl	.L000285f0
/*    28520:	02809825 */ 	or	$s3,$s4,$zero
/*    28524:	4406a000 */ 	mfc1	$a2,$f20
/*    28528:	4407b000 */ 	mfc1	$a3,$f22
/*    2852c:	c62c0010 */ 	lwc1	$f12,0x10($s1)
/*    28530:	0c0095c9 */ 	jal	func00025724
/*    28534:	c62e0018 */ 	lwc1	$f14,0x18($s1)
/*    28538:	4618003e */ 	c.le.s	$f0,$f24
/*    2853c:	00000000 */ 	nop
/*    28540:	45030014 */ 	bc1tl	.L00028594
/*    28544:	8e420000 */ 	lw	$v0,0x0($s2)
/*    28548:	4406a000 */ 	mfc1	$a2,$f20
/*    2854c:	4407b000 */ 	mfc1	$a3,$f22
/*    28550:	c60c0010 */ 	lwc1	$f12,0x10($s0)
/*    28554:	0c0095c9 */ 	jal	func00025724
/*    28558:	c60e0018 */ 	lwc1	$f14,0x18($s0)
/*    2855c:	4618003e */ 	c.le.s	$f0,$f24
/*    28560:	00000000 */ 	nop
/*    28564:	4503000b */ 	bc1tl	.L00028594
/*    28568:	8e420000 */ 	lw	$v0,0x0($s2)
/*    2856c:	c62c0010 */ 	lwc1	$f12,0x10($s1)
/*    28570:	c62e0018 */ 	lwc1	$f14,0x18($s1)
/*    28574:	8e060010 */ 	lw	$a2,0x10($s0)
/*    28578:	8e070018 */ 	lw	$a3,0x18($s0)
/*    2857c:	e7b60014 */ 	swc1	$f22,0x14($sp)
/*    28580:	0c0095dd */ 	jal	func00025774
/*    28584:	e7b40010 */ 	swc1	$f20,0x10($sp)
/*    28588:	50400019 */ 	beqzl	$v0,.L000285f0
/*    2858c:	02809825 */ 	or	$s3,$s4,$zero
/*    28590:	8e420000 */ 	lw	$v0,0x0($s2)
.L00028594:
/*    28594:	8fb80080 */ 	lw	$t8,0x80($sp)
/*    28598:	0058082a */ 	slt	$at,$v0,$t8
/*    2859c:	50200017 */ 	beqzl	$at,.L000285fc
/*    285a0:	8fbf0064 */ 	lw	$ra,0x64($sp)
/*    285a4:	00560019 */ 	multu	$v0,$s6
/*    285a8:	0000c812 */ 	mflo	$t9
/*    285ac:	02b94021 */ 	addu	$t0,$s5,$t9
/*    285b0:	ad1e0000 */ 	sw	$s8,0x0($t0)
/*    285b4:	8e490000 */ 	lw	$t1,0x0($s2)
/*    285b8:	01360019 */ 	multu	$t1,$s6
/*    285bc:	00005012 */ 	mflo	$t2
/*    285c0:	02aa5821 */ 	addu	$t3,$s5,$t2
/*    285c4:	ad730008 */ 	sw	$s3,0x8($t3)
/*    285c8:	8e4d0000 */ 	lw	$t5,0x0($s2)
/*    285cc:	8fac0078 */ 	lw	$t4,0x78($sp)
/*    285d0:	01b60019 */ 	multu	$t5,$s6
/*    285d4:	00007012 */ 	mflo	$t6
/*    285d8:	02ae7821 */ 	addu	$t7,$s5,$t6
/*    285dc:	adec000c */ 	sw	$t4,0xc($t7)
/*    285e0:	8e580000 */ 	lw	$t8,0x0($s2)
/*    285e4:	27190001 */ 	addiu	$t9,$t8,0x1
/*    285e8:	ae590000 */ 	sw	$t9,0x0($s2)
/*    285ec:	02809825 */ 	or	$s3,$s4,$zero
.L000285f0:
/*    285f0:	1697ffa1 */ 	bne	$s4,$s7,.L00028478
/*    285f4:	2631000c */ 	addiu	$s1,$s1,0xc
.L000285f8:
/*    285f8:	8fbf0064 */ 	lw	$ra,0x64($sp)
.L000285fc:
/*    285fc:	d7b40020 */ 	ldc1	$f20,0x20($sp)
/*    28600:	d7b60028 */ 	ldc1	$f22,0x28($sp)
/*    28604:	d7b80030 */ 	ldc1	$f24,0x30($sp)
/*    28608:	d7ba0038 */ 	ldc1	$f26,0x38($sp)
/*    2860c:	8fb00040 */ 	lw	$s0,0x40($sp)
/*    28610:	8fb10044 */ 	lw	$s1,0x44($sp)
/*    28614:	8fb20048 */ 	lw	$s2,0x48($sp)
/*    28618:	8fb3004c */ 	lw	$s3,0x4c($sp)
/*    2861c:	8fb40050 */ 	lw	$s4,0x50($sp)
/*    28620:	8fb50054 */ 	lw	$s5,0x54($sp)
/*    28624:	8fb60058 */ 	lw	$s6,0x58($sp)
/*    28628:	8fb7005c */ 	lw	$s7,0x5c($sp)
/*    2862c:	8fbe0060 */ 	lw	$s8,0x60($sp)
/*    28630:	03e00008 */ 	jr	$ra
/*    28634:	27bd0068 */ 	addiu	$sp,$sp,0x68
);

GLOBAL_ASM(
glabel func00028638
/*    28638:	27bdff98 */ 	addiu	$sp,$sp,-104
/*    2863c:	afbf0064 */ 	sw	$ra,0x64($sp)
/*    28640:	afbe0060 */ 	sw	$s8,0x60($sp)
/*    28644:	afb7005c */ 	sw	$s7,0x5c($sp)
/*    28648:	afb60058 */ 	sw	$s6,0x58($sp)
/*    2864c:	afb50054 */ 	sw	$s5,0x54($sp)
/*    28650:	afb40050 */ 	sw	$s4,0x50($sp)
/*    28654:	afb3004c */ 	sw	$s3,0x4c($sp)
/*    28658:	afb20048 */ 	sw	$s2,0x48($sp)
/*    2865c:	afb10044 */ 	sw	$s1,0x44($sp)
/*    28660:	afb00040 */ 	sw	$s0,0x40($sp)
/*    28664:	f7ba0038 */ 	sdc1	$f26,0x38($sp)
/*    28668:	f7b80030 */ 	sdc1	$f24,0x30($sp)
/*    2866c:	f7b60028 */ 	sdc1	$f22,0x28($sp)
/*    28670:	f7b40020 */ 	sdc1	$f20,0x20($sp)
/*    28674:	90970001 */ 	lbu	$s7,0x1($a0)
/*    28678:	4485a000 */ 	mtc1	$a1,$f20
/*    2867c:	4486b000 */ 	mtc1	$a2,$f22
/*    28680:	4487c000 */ 	mtc1	$a3,$f24
/*    28684:	0080f025 */ 	or	$s8,$a0,$zero
/*    28688:	1ae00064 */ 	blez	$s7,.L0002881c
/*    2868c:	00009825 */ 	or	$s3,$zero,$zero
/*    28690:	4480d000 */ 	mtc1	$zero,$f26
/*    28694:	00808825 */ 	or	$s1,$a0,$zero
/*    28698:	24160014 */ 	addiu	$s6,$zero,0x14
/*    2869c:	8fb5007c */ 	lw	$s5,0x7c($sp)
/*    286a0:	8fb20084 */ 	lw	$s2,0x84($sp)
.L000286a4:
/*    286a4:	26740001 */ 	addiu	$s4,$s3,0x1
/*    286a8:	0297001a */ 	div	$zero,$s4,$s7
/*    286ac:	00007010 */ 	mfhi	$t6
/*    286b0:	000e78c0 */ 	sll	$t7,$t6,0x3
/*    286b4:	03cf8021 */ 	addu	$s0,$s8,$t7
/*    286b8:	c600000c */ 	lwc1	$f0,0xc($s0)
/*    286bc:	c62c000c */ 	lwc1	$f12,0xc($s1)
/*    286c0:	16e00002 */ 	bnez	$s7,.L000286cc
/*    286c4:	00000000 */ 	nop
/*    286c8:	0007000d */ 	break	0x7
.L000286cc:
/*    286cc:	2401ffff */ 	addiu	$at,$zero,-1
/*    286d0:	16e10004 */ 	bne	$s7,$at,.L000286e4
/*    286d4:	3c018000 */ 	lui	$at,0x8000
/*    286d8:	16810002 */ 	bne	$s4,$at,.L000286e4
/*    286dc:	00000000 */ 	nop
/*    286e0:	0006000d */ 	break	0x6
.L000286e4:
/*    286e4:	46006032 */ 	c.eq.s	$f12,$f0
/*    286e8:	00000000 */ 	nop
/*    286ec:	45020008 */ 	bc1fl	.L00028710
/*    286f0:	c62e0010 */ 	lwc1	$f14,0x10($s1)
/*    286f4:	c6240010 */ 	lwc1	$f4,0x10($s1)
/*    286f8:	c6060010 */ 	lwc1	$f6,0x10($s0)
/*    286fc:	46062032 */ 	c.eq.s	$f4,$f6
/*    28700:	00000000 */ 	nop
/*    28704:	45030043 */ 	bc1tl	.L00028814
/*    28708:	02809825 */ 	or	$s3,$s4,$zero
/*    2870c:	c62e0010 */ 	lwc1	$f14,0x10($s1)
.L00028710:
/*    28710:	44060000 */ 	mfc1	$a2,$f0
/*    28714:	8e070010 */ 	lw	$a3,0x10($s0)
/*    28718:	e7b60014 */ 	swc1	$f22,0x14($sp)
/*    2871c:	0c009595 */ 	jal	func00025654
/*    28720:	e7b40010 */ 	swc1	$f20,0x10($sp)
/*    28724:	461a003c */ 	c.lt.s	$f0,$f26
/*    28728:	46000086 */ 	mov.s	$f2,$f0
/*    2872c:	45020003 */ 	bc1fl	.L0002873c
/*    28730:	4618103e */ 	c.le.s	$f2,$f24
/*    28734:	46000087 */ 	neg.s	$f2,$f0
/*    28738:	4618103e */ 	c.le.s	$f2,$f24
.L0002873c:
/*    2873c:	00000000 */ 	nop
/*    28740:	45020034 */ 	bc1fl	.L00028814
/*    28744:	02809825 */ 	or	$s3,$s4,$zero
/*    28748:	4406a000 */ 	mfc1	$a2,$f20
/*    2874c:	4407b000 */ 	mfc1	$a3,$f22
/*    28750:	c62c000c */ 	lwc1	$f12,0xc($s1)
/*    28754:	0c0095c9 */ 	jal	func00025724
/*    28758:	c62e0010 */ 	lwc1	$f14,0x10($s1)
/*    2875c:	4618003e */ 	c.le.s	$f0,$f24
/*    28760:	00000000 */ 	nop
/*    28764:	45030014 */ 	bc1tl	.L000287b8
/*    28768:	8e420000 */ 	lw	$v0,0x0($s2)
/*    2876c:	4406a000 */ 	mfc1	$a2,$f20
/*    28770:	4407b000 */ 	mfc1	$a3,$f22
/*    28774:	c60c000c */ 	lwc1	$f12,0xc($s0)
/*    28778:	0c0095c9 */ 	jal	func00025724
/*    2877c:	c60e0010 */ 	lwc1	$f14,0x10($s0)
/*    28780:	4618003e */ 	c.le.s	$f0,$f24
/*    28784:	00000000 */ 	nop
/*    28788:	4503000b */ 	bc1tl	.L000287b8
/*    2878c:	8e420000 */ 	lw	$v0,0x0($s2)
/*    28790:	c62c000c */ 	lwc1	$f12,0xc($s1)
/*    28794:	c62e0010 */ 	lwc1	$f14,0x10($s1)
/*    28798:	8e06000c */ 	lw	$a2,0xc($s0)
/*    2879c:	8e070010 */ 	lw	$a3,0x10($s0)
/*    287a0:	e7b60014 */ 	swc1	$f22,0x14($sp)
/*    287a4:	0c0095dd */ 	jal	func00025774
/*    287a8:	e7b40010 */ 	swc1	$f20,0x10($sp)
/*    287ac:	50400019 */ 	beqzl	$v0,.L00028814
/*    287b0:	02809825 */ 	or	$s3,$s4,$zero
/*    287b4:	8e420000 */ 	lw	$v0,0x0($s2)
.L000287b8:
/*    287b8:	8fb80080 */ 	lw	$t8,0x80($sp)
/*    287bc:	0058082a */ 	slt	$at,$v0,$t8
/*    287c0:	50200017 */ 	beqzl	$at,.L00028820
/*    287c4:	8fbf0064 */ 	lw	$ra,0x64($sp)
/*    287c8:	00560019 */ 	multu	$v0,$s6
/*    287cc:	0000c812 */ 	mflo	$t9
/*    287d0:	02b94021 */ 	addu	$t0,$s5,$t9
/*    287d4:	ad1e0000 */ 	sw	$s8,0x0($t0)
/*    287d8:	8e490000 */ 	lw	$t1,0x0($s2)
/*    287dc:	01360019 */ 	multu	$t1,$s6
/*    287e0:	00005012 */ 	mflo	$t2
/*    287e4:	02aa5821 */ 	addu	$t3,$s5,$t2
/*    287e8:	ad730008 */ 	sw	$s3,0x8($t3)
/*    287ec:	8e4d0000 */ 	lw	$t5,0x0($s2)
/*    287f0:	8fac0078 */ 	lw	$t4,0x78($sp)
/*    287f4:	01b60019 */ 	multu	$t5,$s6
/*    287f8:	00007012 */ 	mflo	$t6
/*    287fc:	02ae7821 */ 	addu	$t7,$s5,$t6
/*    28800:	adec000c */ 	sw	$t4,0xc($t7)
/*    28804:	8e580000 */ 	lw	$t8,0x0($s2)
/*    28808:	27190001 */ 	addiu	$t9,$t8,0x1
/*    2880c:	ae590000 */ 	sw	$t9,0x0($s2)
/*    28810:	02809825 */ 	or	$s3,$s4,$zero
.L00028814:
/*    28814:	1697ffa3 */ 	bne	$s4,$s7,.L000286a4
/*    28818:	26310008 */ 	addiu	$s1,$s1,0x8
.L0002881c:
/*    2881c:	8fbf0064 */ 	lw	$ra,0x64($sp)
.L00028820:
/*    28820:	d7b40020 */ 	ldc1	$f20,0x20($sp)
/*    28824:	d7b60028 */ 	ldc1	$f22,0x28($sp)
/*    28828:	d7b80030 */ 	ldc1	$f24,0x30($sp)
/*    2882c:	d7ba0038 */ 	ldc1	$f26,0x38($sp)
/*    28830:	8fb00040 */ 	lw	$s0,0x40($sp)
/*    28834:	8fb10044 */ 	lw	$s1,0x44($sp)
/*    28838:	8fb20048 */ 	lw	$s2,0x48($sp)
/*    2883c:	8fb3004c */ 	lw	$s3,0x4c($sp)
/*    28840:	8fb40050 */ 	lw	$s4,0x50($sp)
/*    28844:	8fb50054 */ 	lw	$s5,0x54($sp)
/*    28848:	8fb60058 */ 	lw	$s6,0x58($sp)
/*    2884c:	8fb7005c */ 	lw	$s7,0x5c($sp)
/*    28850:	8fbe0060 */ 	lw	$s8,0x60($sp)
/*    28854:	03e00008 */ 	jr	$ra
/*    28858:	27bd0068 */ 	addiu	$sp,$sp,0x68
);

GLOBAL_ASM(
glabel func0002885c
/*    2885c:	afa7000c */ 	sw	$a3,0xc($sp)
/*    28860:	c7aa000c */ 	lwc1	$f10,0xc($sp)
/*    28864:	c4880014 */ 	lwc1	$f8,0x14($a0)
/*    28868:	44856000 */ 	mtc1	$a1,$f12
/*    2886c:	c484000c */ 	lwc1	$f4,0xc($a0)
/*    28870:	460a4400 */ 	add.s	$f16,$f8,$f10
/*    28874:	44867000 */ 	mtc1	$a2,$f14
/*    28878:	c4860010 */ 	lwc1	$f6,0x10($a0)
/*    2887c:	46046001 */ 	sub.s	$f0,$f12,$f4
/*    28880:	46108482 */ 	mul.s	$f18,$f16,$f16
/*    28884:	8fa2001c */ 	lw	$v0,0x1c($sp)
/*    28888:	46067081 */ 	sub.s	$f2,$f14,$f6
/*    2888c:	46000102 */ 	mul.s	$f4,$f0,$f0
/*    28890:	8fae0018 */ 	lw	$t6,0x18($sp)
/*    28894:	46021182 */ 	mul.s	$f6,$f2,$f2
/*    28898:	46062200 */ 	add.s	$f8,$f4,$f6
/*    2889c:	4612403e */ 	c.le.s	$f8,$f18
/*    288a0:	00000000 */ 	nop
/*    288a4:	45000019 */ 	bc1f	.L0002890c
/*    288a8:	00000000 */ 	nop
/*    288ac:	8c430000 */ 	lw	$v1,0x0($v0)
/*    288b0:	24060014 */ 	addiu	$a2,$zero,0x14
/*    288b4:	006e082a */ 	slt	$at,$v1,$t6
/*    288b8:	10200014 */ 	beqz	$at,.L0002890c
/*    288bc:	00000000 */ 	nop
/*    288c0:	00660019 */ 	multu	$v1,$a2
/*    288c4:	8fa50014 */ 	lw	$a1,0x14($sp)
/*    288c8:	00007812 */ 	mflo	$t7
/*    288cc:	00afc021 */ 	addu	$t8,$a1,$t7
/*    288d0:	af040000 */ 	sw	$a0,0x0($t8)
/*    288d4:	8c590000 */ 	lw	$t9,0x0($v0)
/*    288d8:	03260019 */ 	multu	$t9,$a2
/*    288dc:	00004012 */ 	mflo	$t0
/*    288e0:	00a84821 */ 	addu	$t1,$a1,$t0
/*    288e4:	ad200008 */ 	sw	$zero,0x8($t1)
/*    288e8:	8c4b0000 */ 	lw	$t3,0x0($v0)
/*    288ec:	8faa0010 */ 	lw	$t2,0x10($sp)
/*    288f0:	01660019 */ 	multu	$t3,$a2
/*    288f4:	00006012 */ 	mflo	$t4
/*    288f8:	00ac6821 */ 	addu	$t5,$a1,$t4
/*    288fc:	adaa000c */ 	sw	$t2,0xc($t5)
/*    28900:	8c4e0000 */ 	lw	$t6,0x0($v0)
/*    28904:	25cf0001 */ 	addiu	$t7,$t6,0x1
/*    28908:	ac4f0000 */ 	sw	$t7,0x0($v0)
.L0002890c:
/*    2890c:	03e00008 */ 	jr	$ra
/*    28910:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel func00028914
/*    28914:	27bdff88 */ 	addiu	$sp,$sp,-120
/*    28918:	f7b40028 */ 	sdc1	$f20,0x28($sp)
/*    2891c:	4487a000 */ 	mtc1	$a3,$f20
/*    28920:	afb10044 */ 	sw	$s1,0x44($sp)
/*    28924:	afb00040 */ 	sw	$s0,0x40($sp)
/*    28928:	0085082b */ 	sltu	$at,$a0,$a1
/*    2892c:	00c08825 */ 	or	$s1,$a2,$zero
/*    28930:	afbf0064 */ 	sw	$ra,0x64($sp)
/*    28934:	afbe0060 */ 	sw	$s8,0x60($sp)
/*    28938:	afb7005c */ 	sw	$s7,0x5c($sp)
/*    2893c:	afb60058 */ 	sw	$s6,0x58($sp)
/*    28940:	afb50054 */ 	sw	$s5,0x54($sp)
/*    28944:	afb40050 */ 	sw	$s4,0x50($sp)
/*    28948:	afb3004c */ 	sw	$s3,0x4c($sp)
/*    2894c:	afb20048 */ 	sw	$s2,0x48($sp)
/*    28950:	f7b80038 */ 	sdc1	$f24,0x38($sp)
/*    28954:	f7b60030 */ 	sdc1	$f22,0x30($sp)
/*    28958:	afa5007c */ 	sw	$a1,0x7c($sp)
/*    2895c:	10200115 */ 	beqz	$at,.L00028db4
/*    28960:	00808025 */ 	or	$s0,$a0,$zero
/*    28964:	c7b80094 */ 	lwc1	$f24,0x94($sp)
/*    28968:	c7b60090 */ 	lwc1	$f22,0x90($sp)
/*    2896c:	8fbe00a0 */ 	lw	$s8,0xa0($sp)
/*    28970:	8fb7009c */ 	lw	$s7,0x9c($sp)
/*    28974:	8fb60098 */ 	lw	$s6,0x98($sp)
/*    28978:	8fb5008c */ 	lw	$s5,0x8c($sp)
/*    2897c:	97b4008a */ 	lhu	$s4,0x8a($sp)
/*    28980:	2412000c */ 	addiu	$s2,$zero,0xc
/*    28984:	92020000 */ 	lbu	$v0,0x0($s0)
.L00028988:
/*    28988:	24010001 */ 	addiu	$at,$zero,0x1
/*    2898c:	1440006c */ 	bnez	$v0,.L00028b40
/*    28990:	00000000 */ 	nop
/*    28994:	96020002 */ 	lhu	$v0,0x2($s0)
/*    28998:	02009825 */ 	or	$s3,$s0,$zero
/*    2899c:	00547824 */ 	and	$t7,$v0,$s4
/*    289a0:	51e00061 */ 	beqzl	$t7,.L00028b28
/*    289a4:	92780001 */ 	lbu	$t8,0x1($s3)
/*    289a8:	92180006 */ 	lbu	$t8,0x6($s0)
/*    289ac:	c62c0000 */ 	lwc1	$f12,0x0($s1)
/*    289b0:	0310c821 */ 	addu	$t9,$t8,$s0
/*    289b4:	87280000 */ 	lh	$t0,0x0($t9)
/*    289b8:	44882000 */ 	mtc1	$t0,$f4
/*    289bc:	00000000 */ 	nop
/*    289c0:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    289c4:	46143201 */ 	sub.s	$f8,$f6,$f20
/*    289c8:	460c403e */ 	c.le.s	$f8,$f12
/*    289cc:	00000000 */ 	nop
/*    289d0:	45020055 */ 	bc1fl	.L00028b28
/*    289d4:	92780001 */ 	lbu	$t8,0x1($s3)
/*    289d8:	92090009 */ 	lbu	$t1,0x9($s0)
/*    289dc:	01305021 */ 	addu	$t2,$t1,$s0
/*    289e0:	854b0000 */ 	lh	$t3,0x0($t2)
/*    289e4:	448b5000 */ 	mtc1	$t3,$f10
/*    289e8:	00000000 */ 	nop
/*    289ec:	46805420 */ 	cvt.s.w	$f16,$f10
/*    289f0:	46148480 */ 	add.s	$f18,$f16,$f20
/*    289f4:	4612603e */ 	c.le.s	$f12,$f18
/*    289f8:	00000000 */ 	nop
/*    289fc:	4502004a */ 	bc1fl	.L00028b28
/*    28a00:	92780001 */ 	lbu	$t8,0x1($s3)
/*    28a04:	920c0008 */ 	lbu	$t4,0x8($s0)
/*    28a08:	c6220008 */ 	lwc1	$f2,0x8($s1)
/*    28a0c:	01906821 */ 	addu	$t5,$t4,$s0
/*    28a10:	85ae0000 */ 	lh	$t6,0x0($t5)
/*    28a14:	448e2000 */ 	mtc1	$t6,$f4
/*    28a18:	00000000 */ 	nop
/*    28a1c:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    28a20:	46143201 */ 	sub.s	$f8,$f6,$f20
/*    28a24:	4602403e */ 	c.le.s	$f8,$f2
/*    28a28:	00000000 */ 	nop
/*    28a2c:	4502003e */ 	bc1fl	.L00028b28
/*    28a30:	92780001 */ 	lbu	$t8,0x1($s3)
/*    28a34:	920f000b */ 	lbu	$t7,0xb($s0)
/*    28a38:	01f0c021 */ 	addu	$t8,$t7,$s0
/*    28a3c:	87190000 */ 	lh	$t9,0x0($t8)
/*    28a40:	44995000 */ 	mtc1	$t9,$f10
/*    28a44:	00000000 */ 	nop
/*    28a48:	46805420 */ 	cvt.s.w	$f16,$f10
/*    28a4c:	46148480 */ 	add.s	$f18,$f16,$f20
/*    28a50:	4612103e */ 	c.le.s	$f2,$f18
/*    28a54:	00000000 */ 	nop
/*    28a58:	45020033 */ 	bc1fl	.L00028b28
/*    28a5c:	92780001 */ 	lbu	$t8,0x1($s3)
/*    28a60:	12a00018 */ 	beqz	$s5,.L00028ac4
/*    28a64:	304e0080 */ 	andi	$t6,$v0,0x80
/*    28a68:	92080007 */ 	lbu	$t0,0x7($s0)
/*    28a6c:	c6200004 */ 	lwc1	$f0,0x4($s1)
/*    28a70:	01104821 */ 	addu	$t1,$t0,$s0
/*    28a74:	852a0000 */ 	lh	$t2,0x0($t1)
/*    28a78:	46160100 */ 	add.s	$f4,$f0,$f22
/*    28a7c:	448a3000 */ 	mtc1	$t2,$f6
/*    28a80:	00000000 */ 	nop
/*    28a84:	46803220 */ 	cvt.s.w	$f8,$f6
/*    28a88:	4604403e */ 	c.le.s	$f8,$f4
/*    28a8c:	00000000 */ 	nop
/*    28a90:	45020025 */ 	bc1fl	.L00028b28
/*    28a94:	92780001 */ 	lbu	$t8,0x1($s3)
/*    28a98:	920b000a */ 	lbu	$t3,0xa($s0)
/*    28a9c:	46180480 */ 	add.s	$f18,$f0,$f24
/*    28aa0:	01706021 */ 	addu	$t4,$t3,$s0
/*    28aa4:	858d0000 */ 	lh	$t5,0x0($t4)
/*    28aa8:	448d5000 */ 	mtc1	$t5,$f10
/*    28aac:	00000000 */ 	nop
/*    28ab0:	46805420 */ 	cvt.s.w	$f16,$f10
/*    28ab4:	4610903e */ 	c.le.s	$f18,$f16
/*    28ab8:	00000000 */ 	nop
/*    28abc:	4502001a */ 	bc1fl	.L00028b28
/*    28ac0:	92780001 */ 	lbu	$t8,0x1($s3)
.L00028ac4:
/*    28ac4:	11c0000c */ 	beqz	$t6,.L00028af8
/*    28ac8:	24030001 */ 	addiu	$v1,$zero,0x1
/*    28acc:	c6200004 */ 	lwc1	$f0,0x4($s1)
/*    28ad0:	4406a000 */ 	mfc1	$a2,$f20
/*    28ad4:	02002025 */ 	or	$a0,$s0,$zero
/*    28ad8:	46180180 */ 	add.s	$f6,$f0,$f24
/*    28adc:	02202825 */ 	or	$a1,$s1,$zero
/*    28ae0:	46160100 */ 	add.s	$f4,$f0,$f22
/*    28ae4:	44073000 */ 	mfc1	$a3,$f6
/*    28ae8:	0c00a080 */ 	jal	func00028200
/*    28aec:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*    28af0:	10000001 */ 	b	.L00028af8
/*    28af4:	00401825 */ 	or	$v1,$v0,$zero
.L00028af8:
/*    28af8:	1060000a */ 	beqz	$v1,.L00028b24
/*    28afc:	02002025 */ 	or	$a0,$s0,$zero
/*    28b00:	8e250000 */ 	lw	$a1,0x0($s1)
/*    28b04:	8e260008 */ 	lw	$a2,0x8($s1)
/*    28b08:	8faf00a4 */ 	lw	$t7,0xa4($sp)
/*    28b0c:	4407a000 */ 	mfc1	$a3,$f20
/*    28b10:	afbe0018 */ 	sw	$s8,0x18($sp)
/*    28b14:	afb70014 */ 	sw	$s7,0x14($sp)
/*    28b18:	afb60010 */ 	sw	$s6,0x10($sp)
/*    28b1c:	0c009fde */ 	jal	func00027f78
/*    28b20:	afaf001c */ 	sw	$t7,0x1c($sp)
.L00028b24:
/*    28b24:	92780001 */ 	lbu	$t8,0x1($s3)
.L00028b28:
/*    28b28:	0018c880 */ 	sll	$t9,$t8,0x2
/*    28b2c:	0338c823 */ 	subu	$t9,$t9,$t8
/*    28b30:	0019c840 */ 	sll	$t9,$t9,0x1
/*    28b34:	02198021 */ 	addu	$s0,$s0,$t9
/*    28b38:	1000009a */ 	b	.L00028da4
/*    28b3c:	2610000e */ 	addiu	$s0,$s0,0xe
.L00028b40:
/*    28b40:	5441005a */ 	bnel	$v0,$at,.L00028cac
/*    28b44:	24010002 */ 	addiu	$at,$zero,0x2
/*    28b48:	96080002 */ 	lhu	$t0,0x2($s0)
/*    28b4c:	02001025 */ 	or	$v0,$s0,$zero
/*    28b50:	01144824 */ 	and	$t1,$t0,$s4
/*    28b54:	5120004e */ 	beqzl	$t1,.L00028c90
/*    28b58:	90490001 */ 	lbu	$t1,0x1($v0)
/*    28b5c:	920a0006 */ 	lbu	$t2,0x6($s0)
/*    28b60:	c62c0000 */ 	lwc1	$f12,0x0($s1)
/*    28b64:	01520019 */ 	multu	$t2,$s2
/*    28b68:	00005812 */ 	mflo	$t3
/*    28b6c:	020b6021 */ 	addu	$t4,$s0,$t3
/*    28b70:	c5880010 */ 	lwc1	$f8,0x10($t4)
/*    28b74:	46144281 */ 	sub.s	$f10,$f8,$f20
/*    28b78:	460c503e */ 	c.le.s	$f10,$f12
/*    28b7c:	00000000 */ 	nop
/*    28b80:	45020043 */ 	bc1fl	.L00028c90
/*    28b84:	90490001 */ 	lbu	$t1,0x1($v0)
/*    28b88:	920d0009 */ 	lbu	$t5,0x9($s0)
/*    28b8c:	01b20019 */ 	multu	$t5,$s2
/*    28b90:	00007012 */ 	mflo	$t6
/*    28b94:	020e7821 */ 	addu	$t7,$s0,$t6
/*    28b98:	c5f00010 */ 	lwc1	$f16,0x10($t7)
/*    28b9c:	46148480 */ 	add.s	$f18,$f16,$f20
/*    28ba0:	4612603e */ 	c.le.s	$f12,$f18
/*    28ba4:	00000000 */ 	nop
/*    28ba8:	45020039 */ 	bc1fl	.L00028c90
/*    28bac:	90490001 */ 	lbu	$t1,0x1($v0)
/*    28bb0:	92180008 */ 	lbu	$t8,0x8($s0)
/*    28bb4:	c6220008 */ 	lwc1	$f2,0x8($s1)
/*    28bb8:	03120019 */ 	multu	$t8,$s2
/*    28bbc:	0000c812 */ 	mflo	$t9
/*    28bc0:	02194021 */ 	addu	$t0,$s0,$t9
/*    28bc4:	c5060018 */ 	lwc1	$f6,0x18($t0)
/*    28bc8:	46143101 */ 	sub.s	$f4,$f6,$f20
/*    28bcc:	4602203e */ 	c.le.s	$f4,$f2
/*    28bd0:	00000000 */ 	nop
/*    28bd4:	4502002e */ 	bc1fl	.L00028c90
/*    28bd8:	90490001 */ 	lbu	$t1,0x1($v0)
/*    28bdc:	9209000b */ 	lbu	$t1,0xb($s0)
/*    28be0:	01320019 */ 	multu	$t1,$s2
/*    28be4:	00005012 */ 	mflo	$t2
/*    28be8:	020a5821 */ 	addu	$t3,$s0,$t2
/*    28bec:	c5680018 */ 	lwc1	$f8,0x18($t3)
/*    28bf0:	46144280 */ 	add.s	$f10,$f8,$f20
/*    28bf4:	460a103e */ 	c.le.s	$f2,$f10
/*    28bf8:	00000000 */ 	nop
/*    28bfc:	45020024 */ 	bc1fl	.L00028c90
/*    28c00:	90490001 */ 	lbu	$t1,0x1($v0)
/*    28c04:	12a00016 */ 	beqz	$s5,.L00028c60
/*    28c08:	02002025 */ 	or	$a0,$s0,$zero
/*    28c0c:	920c0007 */ 	lbu	$t4,0x7($s0)
/*    28c10:	c6200004 */ 	lwc1	$f0,0x4($s1)
/*    28c14:	01920019 */ 	multu	$t4,$s2
/*    28c18:	46160400 */ 	add.s	$f16,$f0,$f22
/*    28c1c:	00006812 */ 	mflo	$t5
/*    28c20:	020d7021 */ 	addu	$t6,$s0,$t5
/*    28c24:	c5d20014 */ 	lwc1	$f18,0x14($t6)
/*    28c28:	4610903e */ 	c.le.s	$f18,$f16
/*    28c2c:	00000000 */ 	nop
/*    28c30:	45020017 */ 	bc1fl	.L00028c90
/*    28c34:	90490001 */ 	lbu	$t1,0x1($v0)
/*    28c38:	920f000a */ 	lbu	$t7,0xa($s0)
/*    28c3c:	46180100 */ 	add.s	$f4,$f0,$f24
/*    28c40:	01f20019 */ 	multu	$t7,$s2
/*    28c44:	0000c012 */ 	mflo	$t8
/*    28c48:	0218c821 */ 	addu	$t9,$s0,$t8
/*    28c4c:	c7260014 */ 	lwc1	$f6,0x14($t9)
/*    28c50:	4606203e */ 	c.le.s	$f4,$f6
/*    28c54:	00000000 */ 	nop
/*    28c58:	4502000d */ 	bc1fl	.L00028c90
/*    28c5c:	90490001 */ 	lbu	$t1,0x1($v0)
.L00028c60:
/*    28c60:	8fa800a4 */ 	lw	$t0,0xa4($sp)
/*    28c64:	44056000 */ 	mfc1	$a1,$f12
/*    28c68:	44061000 */ 	mfc1	$a2,$f2
/*    28c6c:	4407a000 */ 	mfc1	$a3,$f20
/*    28c70:	afb60010 */ 	sw	$s6,0x10($sp)
/*    28c74:	afb70014 */ 	sw	$s7,0x14($sp)
/*    28c78:	afbe0018 */ 	sw	$s8,0x18($sp)
/*    28c7c:	afa20068 */ 	sw	$v0,0x68($sp)
/*    28c80:	0c00a103 */ 	jal	func0002840c
/*    28c84:	afa8001c */ 	sw	$t0,0x1c($sp)
/*    28c88:	8fa20068 */ 	lw	$v0,0x68($sp)
/*    28c8c:	90490001 */ 	lbu	$t1,0x1($v0)
.L00028c90:
/*    28c90:	252affc0 */ 	addiu	$t2,$t1,-64
/*    28c94:	01520019 */ 	multu	$t2,$s2
/*    28c98:	00005812 */ 	mflo	$t3
/*    28c9c:	020b8021 */ 	addu	$s0,$s0,$t3
/*    28ca0:	10000040 */ 	b	.L00028da4
/*    28ca4:	26100310 */ 	addiu	$s0,$s0,0x310
/*    28ca8:	24010002 */ 	addiu	$at,$zero,0x2
.L00028cac:
/*    28cac:	1441001d */ 	bne	$v0,$at,.L00028d24
/*    28cb0:	328c001c */ 	andi	$t4,$s4,0x1c
/*    28cb4:	11800019 */ 	beqz	$t4,.L00028d1c
/*    28cb8:	00000000 */ 	nop
/*    28cbc:	12a0000e */ 	beqz	$s5,.L00028cf8
/*    28cc0:	02002025 */ 	or	$a0,$s0,$zero
/*    28cc4:	c6200004 */ 	lwc1	$f0,0x4($s1)
/*    28cc8:	c60a0008 */ 	lwc1	$f10,0x8($s0)
/*    28ccc:	46160200 */ 	add.s	$f8,$f0,$f22
/*    28cd0:	4608503e */ 	c.le.s	$f10,$f8
/*    28cd4:	00000000 */ 	nop
/*    28cd8:	45000010 */ 	bc1f	.L00028d1c
/*    28cdc:	00000000 */ 	nop
/*    28ce0:	46180480 */ 	add.s	$f18,$f0,$f24
/*    28ce4:	c6100004 */ 	lwc1	$f16,0x4($s0)
/*    28ce8:	4610903e */ 	c.le.s	$f18,$f16
/*    28cec:	00000000 */ 	nop
/*    28cf0:	4500000a */ 	bc1f	.L00028d1c
/*    28cf4:	00000000 */ 	nop
.L00028cf8:
/*    28cf8:	8e250000 */ 	lw	$a1,0x0($s1)
/*    28cfc:	8e260008 */ 	lw	$a2,0x8($s1)
/*    28d00:	8fad00a4 */ 	lw	$t5,0xa4($sp)
/*    28d04:	4407a000 */ 	mfc1	$a3,$f20
/*    28d08:	afbe0018 */ 	sw	$s8,0x18($sp)
/*    28d0c:	afb70014 */ 	sw	$s7,0x14($sp)
/*    28d10:	afb60010 */ 	sw	$s6,0x10($sp)
/*    28d14:	0c00a18e */ 	jal	func00028638
/*    28d18:	afad001c */ 	sw	$t5,0x1c($sp)
.L00028d1c:
/*    28d1c:	10000021 */ 	b	.L00028da4
/*    28d20:	2610004c */ 	addiu	$s0,$s0,0x4c
.L00028d24:
/*    28d24:	24010003 */ 	addiu	$at,$zero,0x3
/*    28d28:	5441001f */ 	bnel	$v0,$at,.L00028da8
/*    28d2c:	8fb9007c */ 	lw	$t9,0x7c($sp)
/*    28d30:	960e0002 */ 	lhu	$t6,0x2($s0)
/*    28d34:	028e7824 */ 	and	$t7,$s4,$t6
/*    28d38:	51e0001a */ 	beqzl	$t7,.L00028da4
/*    28d3c:	26100018 */ 	addiu	$s0,$s0,0x18
/*    28d40:	12a0000e */ 	beqz	$s5,.L00028d7c
/*    28d44:	02002025 */ 	or	$a0,$s0,$zero
/*    28d48:	c6200004 */ 	lwc1	$f0,0x4($s1)
/*    28d4c:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*    28d50:	46160180 */ 	add.s	$f6,$f0,$f22
/*    28d54:	4606203e */ 	c.le.s	$f4,$f6
/*    28d58:	00000000 */ 	nop
/*    28d5c:	45020011 */ 	bc1fl	.L00028da4
/*    28d60:	26100018 */ 	addiu	$s0,$s0,0x18
/*    28d64:	46180280 */ 	add.s	$f10,$f0,$f24
/*    28d68:	c6080004 */ 	lwc1	$f8,0x4($s0)
/*    28d6c:	4608503e */ 	c.le.s	$f10,$f8
/*    28d70:	00000000 */ 	nop
/*    28d74:	4502000b */ 	bc1fl	.L00028da4
/*    28d78:	26100018 */ 	addiu	$s0,$s0,0x18
.L00028d7c:
/*    28d7c:	8e250000 */ 	lw	$a1,0x0($s1)
/*    28d80:	8e260008 */ 	lw	$a2,0x8($s1)
/*    28d84:	8fb800a4 */ 	lw	$t8,0xa4($sp)
/*    28d88:	4407a000 */ 	mfc1	$a3,$f20
/*    28d8c:	afbe0018 */ 	sw	$s8,0x18($sp)
/*    28d90:	afb70014 */ 	sw	$s7,0x14($sp)
/*    28d94:	afb60010 */ 	sw	$s6,0x10($sp)
/*    28d98:	0c00a217 */ 	jal	func0002885c
/*    28d9c:	afb8001c */ 	sw	$t8,0x1c($sp)
/*    28da0:	26100018 */ 	addiu	$s0,$s0,0x18
.L00028da4:
/*    28da4:	8fb9007c */ 	lw	$t9,0x7c($sp)
.L00028da8:
/*    28da8:	0219082b */ 	sltu	$at,$s0,$t9
/*    28dac:	5420fef6 */ 	bnezl	$at,.L00028988
/*    28db0:	92020000 */ 	lbu	$v0,0x0($s0)
.L00028db4:
/*    28db4:	8fbf0064 */ 	lw	$ra,0x64($sp)
/*    28db8:	d7b40028 */ 	ldc1	$f20,0x28($sp)
/*    28dbc:	d7b60030 */ 	ldc1	$f22,0x30($sp)
/*    28dc0:	d7b80038 */ 	ldc1	$f24,0x38($sp)
/*    28dc4:	8fb00040 */ 	lw	$s0,0x40($sp)
/*    28dc8:	8fb10044 */ 	lw	$s1,0x44($sp)
/*    28dcc:	8fb20048 */ 	lw	$s2,0x48($sp)
/*    28dd0:	8fb3004c */ 	lw	$s3,0x4c($sp)
/*    28dd4:	8fb40050 */ 	lw	$s4,0x50($sp)
/*    28dd8:	8fb50054 */ 	lw	$s5,0x54($sp)
/*    28ddc:	8fb60058 */ 	lw	$s6,0x58($sp)
/*    28de0:	8fb7005c */ 	lw	$s7,0x5c($sp)
/*    28de4:	8fbe0060 */ 	lw	$s8,0x60($sp)
/*    28de8:	03e00008 */ 	jr	$ra
/*    28dec:	27bd0078 */ 	addiu	$sp,$sp,0x78
);

void func00028df0(struct coord *pos, f32 width, s16 *rooms, u32 types, u16 arg4, u32 arg5, f32 ymax, f32 ymin, struct collisionthing *arg8, s32 arg9)
{
	s16 *roomptr;
	s32 roomnum;
	u8 *start;
	u8 *end;
	s32 sp294 = 0;
	s16 *propnumptr;
	s16 propnums[256];

	// Check BG
	if (types & CDTYPE_BG) {
		roomptr = rooms;
		roomnum = rooms[0];

		while (roomnum != -1) {
			if (roomnum < g_TileNumRooms) {
				start = g_TileFileData.u8 + g_TileRooms[roomnum];
				end = g_TileFileData.u8 + g_TileRooms[roomnum + 1];

				func00028914(start, end, pos, width, arg4, arg5, ymax, ymin, NULL, arg8, arg9, &sp294);
			}

			roomptr++;
			roomnum = *roomptr;
		}
	}

	// Check props
	roomGetProps(rooms, propnums, 256);
	propnumptr = propnums;

	while (*propnumptr >= 0) {
		struct prop *prop = &g_Vars.props[*propnumptr];

		if (propIsOfCdType(prop, types) && propUpdateGeometry(prop, &start, &end)) {
			func00028914(start, end, pos, width, arg4, arg5, ymax, ymin, prop, arg8, arg9, &sp294);
		}

		propnumptr++;
	}

	arg8[sp294].tile = NULL;
}

GLOBAL_ASM(
glabel func0002901c
/*    2901c:	27bdfef8 */ 	addiu	$sp,$sp,-264
/*    29020:	afbf0064 */ 	sw	$ra,0x64($sp)
/*    29024:	afbe0060 */ 	sw	$s8,0x60($sp)
/*    29028:	afb7005c */ 	sw	$s7,0x5c($sp)
/*    2902c:	afb60058 */ 	sw	$s6,0x58($sp)
/*    29030:	afb50054 */ 	sw	$s5,0x54($sp)
/*    29034:	afb40050 */ 	sw	$s4,0x50($sp)
/*    29038:	afb3004c */ 	sw	$s3,0x4c($sp)
/*    2903c:	afb20048 */ 	sw	$s2,0x48($sp)
/*    29040:	afb10044 */ 	sw	$s1,0x44($sp)
/*    29044:	afb00040 */ 	sw	$s0,0x40($sp)
/*    29048:	f7b60038 */ 	sdc1	$f22,0x38($sp)
/*    2904c:	f7b40030 */ 	sdc1	$f20,0x30($sp)
/*    29050:	afa70114 */ 	sw	$a3,0x114($sp)
/*    29054:	8ce30000 */ 	lw	$v1,0x0($a3)
/*    29058:	4486b000 */ 	mtc1	$a2,$f22
/*    2905c:	4480a000 */ 	mtc1	$zero,$f20
/*    29060:	00a08825 */ 	or	$s1,$a1,$zero
/*    29064:	00809025 */ 	or	$s2,$a0,$zero
/*    29068:	2410ffff */ 	addiu	$s0,$zero,-1
/*    2906c:	00009825 */ 	or	$s3,$zero,$zero
/*    29070:	106000dc */ 	beqz	$v1,.L000293e4
/*    29074:	00e07025 */ 	or	$t6,$a3,$zero
/*    29078:	01c0a025 */ 	or	$s4,$t6,$zero
/*    2907c:	27be00e0 */ 	addiu	$s8,$sp,0xe0
/*    29080:	27b700e8 */ 	addiu	$s7,$sp,0xe8
/*    29084:	27b600f0 */ 	addiu	$s6,$sp,0xf0
/*    29088:	27b500f8 */ 	addiu	$s5,$sp,0xf8
/*    2908c:	90620000 */ 	lbu	$v0,0x0($v1)
.L00029090:
/*    29090:	54400042 */ 	bnezl	$v0,.L0002919c
/*    29094:	24010001 */ 	addiu	$at,$zero,0x1
/*    29098:	e7b600f8 */ 	swc1	$f22,0xf8($sp)
/*    2909c:	c6440000 */ 	lwc1	$f4,0x0($s2)
/*    290a0:	240b0006 */ 	addiu	$t3,$zero,0x6
/*    290a4:	02a02025 */ 	or	$a0,$s5,$zero
/*    290a8:	e7a400fc */ 	swc1	$f4,0xfc($sp)
/*    290ac:	c6460008 */ 	lwc1	$f6,0x8($s2)
/*    290b0:	02c02825 */ 	or	$a1,$s6,$zero
/*    290b4:	02e03025 */ 	or	$a2,$s7,$zero
/*    290b8:	e7a60100 */ 	swc1	$f6,0x100($sp)
/*    290bc:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*    290c0:	03c03825 */ 	or	$a3,$s8,$zero
/*    290c4:	e7a800e0 */ 	swc1	$f8,0xe0($sp)
/*    290c8:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*    290cc:	e7aa00e4 */ 	swc1	$f10,0xe4($sp)
/*    290d0:	8e820008 */ 	lw	$v0,0x8($s4)
/*    290d4:	90780001 */ 	lbu	$t8,0x1($v1)
/*    290d8:	244f0001 */ 	addiu	$t7,$v0,0x1
/*    290dc:	01f8001a */ 	div	$zero,$t7,$t8
/*    290e0:	00004010 */ 	mfhi	$t0
/*    290e4:	17000002 */ 	bnez	$t8,.L000290f0
/*    290e8:	00000000 */ 	nop
/*    290ec:	0007000d */ 	break	0x7
.L000290f0:
/*    290f0:	2401ffff */ 	addiu	$at,$zero,-1
/*    290f4:	17010004 */ 	bne	$t8,$at,.L00029108
/*    290f8:	3c018000 */ 	lui	$at,0x8000
/*    290fc:	15e10002 */ 	bne	$t7,$at,.L00029108
/*    29100:	00000000 */ 	nop
/*    29104:	0006000d */ 	break	0x6
.L00029108:
/*    29108:	004b0019 */ 	multu	$v0,$t3
/*    2910c:	0000c812 */ 	mflo	$t9
/*    29110:	00794821 */ 	addu	$t1,$v1,$t9
/*    29114:	852c000e */ 	lh	$t4,0xe($t1)
/*    29118:	010b0019 */ 	multu	$t0,$t3
/*    2911c:	448c8000 */ 	mtc1	$t4,$f16
/*    29120:	00000000 */ 	nop
/*    29124:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    29128:	00007012 */ 	mflo	$t6
/*    2912c:	e7b200f0 */ 	swc1	$f18,0xf0($sp)
/*    29130:	852d0012 */ 	lh	$t5,0x12($t1)
/*    29134:	006e5021 */ 	addu	$t2,$v1,$t6
/*    29138:	448d2000 */ 	mtc1	$t5,$f4
/*    2913c:	00000000 */ 	nop
/*    29140:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    29144:	e7a600f4 */ 	swc1	$f6,0xf4($sp)
/*    29148:	854f000e */ 	lh	$t7,0xe($t2)
/*    2914c:	448f4000 */ 	mtc1	$t7,$f8
/*    29150:	00000000 */ 	nop
/*    29154:	468042a0 */ 	cvt.s.w	$f10,$f8
/*    29158:	e7aa00e8 */ 	swc1	$f10,0xe8($sp)
/*    2915c:	85580012 */ 	lh	$t8,0x12($t2)
/*    29160:	44988000 */ 	mtc1	$t8,$f16
/*    29164:	00000000 */ 	nop
/*    29168:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    2916c:	0fc55e73 */ 	jal	func0f1579cc
/*    29170:	e7b200ec */ 	swc1	$f18,0xec($sp)
/*    29174:	06020006 */ 	bltzl	$s0,.L00029190
/*    29178:	46000506 */ 	mov.s	$f20,$f0
/*    2917c:	4614003c */ 	c.lt.s	$f0,$f20
/*    29180:	00000000 */ 	nop
/*    29184:	45020093 */ 	bc1fl	.L000293d4
/*    29188:	8e830014 */ 	lw	$v1,0x14($s4)
/*    2918c:	46000506 */ 	mov.s	$f20,$f0
.L00029190:
/*    29190:	1000008f */ 	b	.L000293d0
/*    29194:	02608025 */ 	or	$s0,$s3,$zero
/*    29198:	24010001 */ 	addiu	$at,$zero,0x1
.L0002919c:
/*    2919c:	54410036 */ 	bnel	$v0,$at,.L00029278
/*    291a0:	24010002 */ 	addiu	$at,$zero,0x2
/*    291a4:	e7b600f8 */ 	swc1	$f22,0xf8($sp)
/*    291a8:	c6440000 */ 	lwc1	$f4,0x0($s2)
/*    291ac:	240b000c */ 	addiu	$t3,$zero,0xc
/*    291b0:	02a02025 */ 	or	$a0,$s5,$zero
/*    291b4:	e7a400fc */ 	swc1	$f4,0xfc($sp)
/*    291b8:	c6460008 */ 	lwc1	$f6,0x8($s2)
/*    291bc:	02c02825 */ 	or	$a1,$s6,$zero
/*    291c0:	02e03025 */ 	or	$a2,$s7,$zero
/*    291c4:	e7a60100 */ 	swc1	$f6,0x100($sp)
/*    291c8:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*    291cc:	03c03825 */ 	or	$a3,$s8,$zero
/*    291d0:	e7a800e0 */ 	swc1	$f8,0xe0($sp)
/*    291d4:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*    291d8:	e7aa00e4 */ 	swc1	$f10,0xe4($sp)
/*    291dc:	8e820008 */ 	lw	$v0,0x8($s4)
/*    291e0:	906c0001 */ 	lbu	$t4,0x1($v1)
/*    291e4:	24590001 */ 	addiu	$t9,$v0,0x1
/*    291e8:	032c001a */ 	div	$zero,$t9,$t4
/*    291ec:	00004010 */ 	mfhi	$t0
/*    291f0:	15800002 */ 	bnez	$t4,.L000291fc
/*    291f4:	00000000 */ 	nop
/*    291f8:	0007000d */ 	break	0x7
.L000291fc:
/*    291fc:	2401ffff */ 	addiu	$at,$zero,-1
/*    29200:	15810004 */ 	bne	$t4,$at,.L00029214
/*    29204:	3c018000 */ 	lui	$at,0x8000
/*    29208:	17210002 */ 	bne	$t9,$at,.L00029214
/*    2920c:	00000000 */ 	nop
/*    29210:	0006000d */ 	break	0x6
.L00029214:
/*    29214:	004b0019 */ 	multu	$v0,$t3
/*    29218:	00006812 */ 	mflo	$t5
/*    2921c:	006d4821 */ 	addu	$t1,$v1,$t5
/*    29220:	c5300010 */ 	lwc1	$f16,0x10($t1)
/*    29224:	010b0019 */ 	multu	$t0,$t3
/*    29228:	e7b000f0 */ 	swc1	$f16,0xf0($sp)
/*    2922c:	c5320018 */ 	lwc1	$f18,0x18($t1)
/*    29230:	e7b200f4 */ 	swc1	$f18,0xf4($sp)
/*    29234:	00007012 */ 	mflo	$t6
/*    29238:	006e5021 */ 	addu	$t2,$v1,$t6
/*    2923c:	c5440010 */ 	lwc1	$f4,0x10($t2)
/*    29240:	e7a400e8 */ 	swc1	$f4,0xe8($sp)
/*    29244:	c5460018 */ 	lwc1	$f6,0x18($t2)
/*    29248:	0fc55e73 */ 	jal	func0f1579cc
/*    2924c:	e7a600ec */ 	swc1	$f6,0xec($sp)
/*    29250:	06020006 */ 	bltzl	$s0,.L0002926c
/*    29254:	46000506 */ 	mov.s	$f20,$f0
/*    29258:	4614003c */ 	c.lt.s	$f0,$f20
/*    2925c:	00000000 */ 	nop
/*    29260:	4502005c */ 	bc1fl	.L000293d4
/*    29264:	8e830014 */ 	lw	$v1,0x14($s4)
/*    29268:	46000506 */ 	mov.s	$f20,$f0
.L0002926c:
/*    2926c:	10000058 */ 	b	.L000293d0
/*    29270:	02608025 */ 	or	$s0,$s3,$zero
/*    29274:	24010002 */ 	addiu	$at,$zero,0x2
.L00029278:
/*    29278:	54410033 */ 	bnel	$v0,$at,.L00029348
/*    2927c:	24010003 */ 	addiu	$at,$zero,0x3
/*    29280:	e7b600f8 */ 	swc1	$f22,0xf8($sp)
/*    29284:	c6480000 */ 	lwc1	$f8,0x0($s2)
/*    29288:	02a02025 */ 	or	$a0,$s5,$zero
/*    2928c:	02c02825 */ 	or	$a1,$s6,$zero
/*    29290:	e7a800fc */ 	swc1	$f8,0xfc($sp)
/*    29294:	c64a0008 */ 	lwc1	$f10,0x8($s2)
/*    29298:	02e03025 */ 	or	$a2,$s7,$zero
/*    2929c:	03c03825 */ 	or	$a3,$s8,$zero
/*    292a0:	e7aa0100 */ 	swc1	$f10,0x100($sp)
/*    292a4:	c6300000 */ 	lwc1	$f16,0x0($s1)
/*    292a8:	e7b000e0 */ 	swc1	$f16,0xe0($sp)
/*    292ac:	c6320008 */ 	lwc1	$f18,0x8($s1)
/*    292b0:	e7b200e4 */ 	swc1	$f18,0xe4($sp)
/*    292b4:	90780001 */ 	lbu	$t8,0x1($v1)
/*    292b8:	8e820008 */ 	lw	$v0,0x8($s4)
/*    292bc:	244f0001 */ 	addiu	$t7,$v0,0x1
/*    292c0:	01f8001a */ 	div	$zero,$t7,$t8
/*    292c4:	0002c8c0 */ 	sll	$t9,$v0,0x3
/*    292c8:	00794821 */ 	addu	$t1,$v1,$t9
/*    292cc:	c524000c */ 	lwc1	$f4,0xc($t1)
/*    292d0:	00004010 */ 	mfhi	$t0
/*    292d4:	000860c0 */ 	sll	$t4,$t0,0x3
/*    292d8:	e7a400f0 */ 	swc1	$f4,0xf0($sp)
/*    292dc:	c5260010 */ 	lwc1	$f6,0x10($t1)
/*    292e0:	006c5021 */ 	addu	$t2,$v1,$t4
/*    292e4:	17000002 */ 	bnez	$t8,.L000292f0
/*    292e8:	00000000 */ 	nop
/*    292ec:	0007000d */ 	break	0x7
.L000292f0:
/*    292f0:	2401ffff */ 	addiu	$at,$zero,-1
/*    292f4:	17010004 */ 	bne	$t8,$at,.L00029308
/*    292f8:	3c018000 */ 	lui	$at,0x8000
/*    292fc:	15e10002 */ 	bne	$t7,$at,.L00029308
/*    29300:	00000000 */ 	nop
/*    29304:	0006000d */ 	break	0x6
.L00029308:
/*    29308:	e7a600f4 */ 	swc1	$f6,0xf4($sp)
/*    2930c:	c548000c */ 	lwc1	$f8,0xc($t2)
/*    29310:	e7a800e8 */ 	swc1	$f8,0xe8($sp)
/*    29314:	c54a0010 */ 	lwc1	$f10,0x10($t2)
/*    29318:	0fc55e73 */ 	jal	func0f1579cc
/*    2931c:	e7aa00ec */ 	swc1	$f10,0xec($sp)
/*    29320:	06020006 */ 	bltzl	$s0,.L0002933c
/*    29324:	46000506 */ 	mov.s	$f20,$f0
/*    29328:	4614003c */ 	c.lt.s	$f0,$f20
/*    2932c:	00000000 */ 	nop
/*    29330:	45020028 */ 	bc1fl	.L000293d4
/*    29334:	8e830014 */ 	lw	$v1,0x14($s4)
/*    29338:	46000506 */ 	mov.s	$f20,$f0
.L0002933c:
/*    2933c:	10000024 */ 	b	.L000293d0
/*    29340:	02608025 */ 	or	$s0,$s3,$zero
/*    29344:	24010003 */ 	addiu	$at,$zero,0x3
.L00029348:
/*    29348:	54410022 */ 	bnel	$v0,$at,.L000293d4
/*    2934c:	8e830014 */ 	lw	$v1,0x14($s4)
/*    29350:	c4700014 */ 	lwc1	$f16,0x14($v1)
/*    29354:	02a02025 */ 	or	$a0,$s5,$zero
/*    29358:	02c02825 */ 	or	$a1,$s6,$zero
/*    2935c:	46168480 */ 	add.s	$f18,$f16,$f22
/*    29360:	02e03025 */ 	or	$a2,$s7,$zero
/*    29364:	03c03825 */ 	or	$a3,$s8,$zero
/*    29368:	e7b200f8 */ 	swc1	$f18,0xf8($sp)
/*    2936c:	c6440000 */ 	lwc1	$f4,0x0($s2)
/*    29370:	e7a400fc */ 	swc1	$f4,0xfc($sp)
/*    29374:	c6460008 */ 	lwc1	$f6,0x8($s2)
/*    29378:	e7a60100 */ 	swc1	$f6,0x100($sp)
/*    2937c:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*    29380:	e7a800e0 */ 	swc1	$f8,0xe0($sp)
/*    29384:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*    29388:	e7aa00e4 */ 	swc1	$f10,0xe4($sp)
/*    2938c:	c470000c */ 	lwc1	$f16,0xc($v1)
/*    29390:	e7b000f0 */ 	swc1	$f16,0xf0($sp)
/*    29394:	c4720010 */ 	lwc1	$f18,0x10($v1)
/*    29398:	e7b200f4 */ 	swc1	$f18,0xf4($sp)
/*    2939c:	c464000c */ 	lwc1	$f4,0xc($v1)
/*    293a0:	e7a400e8 */ 	swc1	$f4,0xe8($sp)
/*    293a4:	c4660010 */ 	lwc1	$f6,0x10($v1)
/*    293a8:	0fc55e73 */ 	jal	func0f1579cc
/*    293ac:	e7a600ec */ 	swc1	$f6,0xec($sp)
/*    293b0:	06020006 */ 	bltzl	$s0,.L000293cc
/*    293b4:	46000506 */ 	mov.s	$f20,$f0
/*    293b8:	4614003c */ 	c.lt.s	$f0,$f20
/*    293bc:	00000000 */ 	nop
/*    293c0:	45020004 */ 	bc1fl	.L000293d4
/*    293c4:	8e830014 */ 	lw	$v1,0x14($s4)
/*    293c8:	46000506 */ 	mov.s	$f20,$f0
.L000293cc:
/*    293cc:	02608025 */ 	or	$s0,$s3,$zero
.L000293d0:
/*    293d0:	8e830014 */ 	lw	$v1,0x14($s4)
.L000293d4:
/*    293d4:	26730001 */ 	addiu	$s3,$s3,0x1
/*    293d8:	26940014 */ 	addiu	$s4,$s4,0x14
/*    293dc:	5460ff2c */ 	bnezl	$v1,.L00029090
/*    293e0:	90620000 */ 	lbu	$v0,0x0($v1)
.L000293e4:
/*    293e4:	8fad0114 */ 	lw	$t5,0x114($sp)
/*    293e8:	00107080 */ 	sll	$t6,$s0,0x2
/*    293ec:	01d07021 */ 	addu	$t6,$t6,$s0
/*    293f0:	000e7080 */ 	sll	$t6,$t6,0x2
/*    293f4:	01ae8821 */ 	addu	$s1,$t5,$t6
/*    293f8:	8e280000 */ 	lw	$t0,0x0($s1)
/*    293fc:	91020000 */ 	lbu	$v0,0x0($t0)
/*    29400:	54400037 */ 	bnezl	$v0,.L000294e0
/*    29404:	24010001 */ 	addiu	$at,$zero,0x1
/*    29408:	91180001 */ 	lbu	$t8,0x1($t0)
/*    2940c:	8e250008 */ 	lw	$a1,0x8($s1)
/*    29410:	01001025 */ 	or	$v0,$t0,$zero
/*    29414:	24af0001 */ 	addiu	$t7,$a1,0x1
/*    29418:	01f8001a */ 	div	$zero,$t7,$t8
/*    2941c:	0005c880 */ 	sll	$t9,$a1,0x2
/*    29420:	0325c823 */ 	subu	$t9,$t9,$a1
/*    29424:	0019c840 */ 	sll	$t9,$t9,0x1
/*    29428:	00591821 */ 	addu	$v1,$v0,$t9
/*    2942c:	846c000e */ 	lh	$t4,0xe($v1)
/*    29430:	00003010 */ 	mfhi	$a2
/*    29434:	448c4000 */ 	mtc1	$t4,$f8
/*    29438:	17000002 */ 	bnez	$t8,.L00029444
/*    2943c:	00000000 */ 	nop
/*    29440:	0007000d */ 	break	0x7
.L00029444:
/*    29444:	2401ffff */ 	addiu	$at,$zero,-1
/*    29448:	17010004 */ 	bne	$t8,$at,.L0002945c
/*    2944c:	3c018000 */ 	lui	$at,0x8000
/*    29450:	15e10002 */ 	bne	$t7,$at,.L0002945c
/*    29454:	00000000 */ 	nop
/*    29458:	0006000d */ 	break	0x6
.L0002945c:
/*    2945c:	468042a0 */ 	cvt.s.w	$f10,$f8
/*    29460:	00067880 */ 	sll	$t7,$a2,0x2
/*    29464:	01e67823 */ 	subu	$t7,$t7,$a2
/*    29468:	000f7840 */ 	sll	$t7,$t7,0x1
/*    2946c:	004f2021 */ 	addu	$a0,$v0,$t7
/*    29470:	e7aa00bc */ 	swc1	$f10,0xbc($sp)
/*    29474:	846d0010 */ 	lh	$t5,0x10($v1)
/*    29478:	448d8000 */ 	mtc1	$t5,$f16
/*    2947c:	00000000 */ 	nop
/*    29480:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    29484:	e7b200c0 */ 	swc1	$f18,0xc0($sp)
/*    29488:	846e0012 */ 	lh	$t6,0x12($v1)
/*    2948c:	448e2000 */ 	mtc1	$t6,$f4
/*    29490:	00000000 */ 	nop
/*    29494:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    29498:	e7a600c4 */ 	swc1	$f6,0xc4($sp)
/*    2949c:	8498000e */ 	lh	$t8,0xe($a0)
/*    294a0:	44984000 */ 	mtc1	$t8,$f8
/*    294a4:	00000000 */ 	nop
/*    294a8:	468042a0 */ 	cvt.s.w	$f10,$f8
/*    294ac:	e7aa00b0 */ 	swc1	$f10,0xb0($sp)
/*    294b0:	84990010 */ 	lh	$t9,0x10($a0)
/*    294b4:	44998000 */ 	mtc1	$t9,$f16
/*    294b8:	00000000 */ 	nop
/*    294bc:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    294c0:	e7b200b4 */ 	swc1	$f18,0xb4($sp)
/*    294c4:	848c0012 */ 	lh	$t4,0x12($a0)
/*    294c8:	448c2000 */ 	mtc1	$t4,$f4
/*    294cc:	00000000 */ 	nop
/*    294d0:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    294d4:	1000005f */ 	b	.L00029654
/*    294d8:	e7a600b8 */ 	swc1	$f6,0xb8($sp)
/*    294dc:	24010001 */ 	addiu	$at,$zero,0x1
.L000294e0:
/*    294e0:	54410025 */ 	bnel	$v0,$at,.L00029578
/*    294e4:	24010002 */ 	addiu	$at,$zero,0x2
/*    294e8:	8e250008 */ 	lw	$a1,0x8($s1)
/*    294ec:	910e0001 */ 	lbu	$t6,0x1($t0)
/*    294f0:	2407000c */ 	addiu	$a3,$zero,0xc
/*    294f4:	24ad0001 */ 	addiu	$t5,$a1,0x1
/*    294f8:	01ae001a */ 	div	$zero,$t5,$t6
/*    294fc:	00003010 */ 	mfhi	$a2
/*    29500:	01001025 */ 	or	$v0,$t0,$zero
/*    29504:	15c00002 */ 	bnez	$t6,.L00029510
/*    29508:	00000000 */ 	nop
/*    2950c:	0007000d */ 	break	0x7
.L00029510:
/*    29510:	2401ffff */ 	addiu	$at,$zero,-1
/*    29514:	15c10004 */ 	bne	$t6,$at,.L00029528
/*    29518:	3c018000 */ 	lui	$at,0x8000
/*    2951c:	15a10002 */ 	bne	$t5,$at,.L00029528
/*    29520:	00000000 */ 	nop
/*    29524:	0006000d */ 	break	0x6
.L00029528:
/*    29528:	00a70019 */ 	multu	$a1,$a3
/*    2952c:	00007812 */ 	mflo	$t7
/*    29530:	004f1821 */ 	addu	$v1,$v0,$t7
/*    29534:	c4680010 */ 	lwc1	$f8,0x10($v1)
/*    29538:	00c70019 */ 	multu	$a2,$a3
/*    2953c:	e7a800bc */ 	swc1	$f8,0xbc($sp)
/*    29540:	c46a0014 */ 	lwc1	$f10,0x14($v1)
/*    29544:	e7aa00c0 */ 	swc1	$f10,0xc0($sp)
/*    29548:	c4700018 */ 	lwc1	$f16,0x18($v1)
/*    2954c:	0000c012 */ 	mflo	$t8
/*    29550:	00582021 */ 	addu	$a0,$v0,$t8
/*    29554:	e7b000c4 */ 	swc1	$f16,0xc4($sp)
/*    29558:	c4920010 */ 	lwc1	$f18,0x10($a0)
/*    2955c:	e7b200b0 */ 	swc1	$f18,0xb0($sp)
/*    29560:	c4840014 */ 	lwc1	$f4,0x14($a0)
/*    29564:	e7a400b4 */ 	swc1	$f4,0xb4($sp)
/*    29568:	c4860018 */ 	lwc1	$f6,0x18($a0)
/*    2956c:	10000039 */ 	b	.L00029654
/*    29570:	e7a600b8 */ 	swc1	$f6,0xb8($sp)
/*    29574:	24010002 */ 	addiu	$at,$zero,0x2
.L00029578:
/*    29578:	54410022 */ 	bnel	$v0,$at,.L00029604
/*    2957c:	24010003 */ 	addiu	$at,$zero,0x3
/*    29580:	910c0001 */ 	lbu	$t4,0x1($t0)
/*    29584:	8e230008 */ 	lw	$v1,0x8($s1)
/*    29588:	01001025 */ 	or	$v0,$t0,$zero
/*    2958c:	24790001 */ 	addiu	$t9,$v1,0x1
/*    29590:	032c001a */ 	div	$zero,$t9,$t4
/*    29594:	000368c0 */ 	sll	$t5,$v1,0x3
/*    29598:	004d2021 */ 	addu	$a0,$v0,$t5
/*    2959c:	c488000c */ 	lwc1	$f8,0xc($a0)
/*    295a0:	00003010 */ 	mfhi	$a2
/*    295a4:	000670c0 */ 	sll	$t6,$a2,0x3
/*    295a8:	e7a800bc */ 	swc1	$f8,0xbc($sp)
/*    295ac:	c64a0004 */ 	lwc1	$f10,0x4($s2)
/*    295b0:	004e2821 */ 	addu	$a1,$v0,$t6
/*    295b4:	15800002 */ 	bnez	$t4,.L000295c0
/*    295b8:	00000000 */ 	nop
/*    295bc:	0007000d */ 	break	0x7
.L000295c0:
/*    295c0:	2401ffff */ 	addiu	$at,$zero,-1
/*    295c4:	15810004 */ 	bne	$t4,$at,.L000295d8
/*    295c8:	3c018000 */ 	lui	$at,0x8000
/*    295cc:	17210002 */ 	bne	$t9,$at,.L000295d8
/*    295d0:	00000000 */ 	nop
/*    295d4:	0006000d */ 	break	0x6
.L000295d8:
/*    295d8:	e7aa00c0 */ 	swc1	$f10,0xc0($sp)
/*    295dc:	c4900010 */ 	lwc1	$f16,0x10($a0)
/*    295e0:	e7b000c4 */ 	swc1	$f16,0xc4($sp)
/*    295e4:	c4b2000c */ 	lwc1	$f18,0xc($a1)
/*    295e8:	e7b200b0 */ 	swc1	$f18,0xb0($sp)
/*    295ec:	c6440004 */ 	lwc1	$f4,0x4($s2)
/*    295f0:	e7a400b4 */ 	swc1	$f4,0xb4($sp)
/*    295f4:	c4a60010 */ 	lwc1	$f6,0x10($a1)
/*    295f8:	10000016 */ 	b	.L00029654
/*    295fc:	e7a600b8 */ 	swc1	$f6,0xb8($sp)
/*    29600:	24010003 */ 	addiu	$at,$zero,0x3
.L00029604:
/*    29604:	14410013 */ 	bne	$v0,$at,.L00029654
/*    29608:	27af00bc */ 	addiu	$t7,$sp,0xbc
/*    2960c:	c6480008 */ 	lwc1	$f8,0x8($s2)
/*    29610:	c50c000c */ 	lwc1	$f12,0xc($t0)
/*    29614:	c50e0010 */ 	lwc1	$f14,0x10($t0)
/*    29618:	8d060014 */ 	lw	$a2,0x14($t0)
/*    2961c:	8e470000 */ 	lw	$a3,0x0($s2)
/*    29620:	27b800c4 */ 	addiu	$t8,$sp,0xc4
/*    29624:	27b900b0 */ 	addiu	$t9,$sp,0xb0
/*    29628:	27ac00b8 */ 	addiu	$t4,$sp,0xb8
/*    2962c:	afac0020 */ 	sw	$t4,0x20($sp)
/*    29630:	afb9001c */ 	sw	$t9,0x1c($sp)
/*    29634:	afb80018 */ 	sw	$t8,0x18($sp)
/*    29638:	afaf0014 */ 	sw	$t7,0x14($sp)
/*    2963c:	0c009612 */ 	jal	func00025848
/*    29640:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*    29644:	c64a0004 */ 	lwc1	$f10,0x4($s2)
/*    29648:	e7aa00c0 */ 	swc1	$f10,0xc0($sp)
/*    2964c:	c6500004 */ 	lwc1	$f16,0x4($s2)
/*    29650:	e7b000b4 */ 	swc1	$f16,0xb4($sp)
.L00029654:
/*    29654:	4407a000 */ 	mfc1	$a3,$f20
/*    29658:	27a400bc */ 	addiu	$a0,$sp,0xbc
/*    2965c:	27a500b0 */ 	addiu	$a1,$sp,0xb0
/*    29660:	0c00940e */ 	jal	func00025038
/*    29664:	8e26000c */ 	lw	$a2,0xc($s1)
/*    29668:	8fbf0064 */ 	lw	$ra,0x64($sp)
/*    2966c:	d7b40030 */ 	ldc1	$f20,0x30($sp)
/*    29670:	d7b60038 */ 	ldc1	$f22,0x38($sp)
/*    29674:	8fb00040 */ 	lw	$s0,0x40($sp)
/*    29678:	8fb10044 */ 	lw	$s1,0x44($sp)
/*    2967c:	8fb20048 */ 	lw	$s2,0x48($sp)
/*    29680:	8fb3004c */ 	lw	$s3,0x4c($sp)
/*    29684:	8fb40050 */ 	lw	$s4,0x50($sp)
/*    29688:	8fb50054 */ 	lw	$s5,0x54($sp)
/*    2968c:	8fb60058 */ 	lw	$s6,0x58($sp)
/*    29690:	8fb7005c */ 	lw	$s7,0x5c($sp)
/*    29694:	8fbe0060 */ 	lw	$s8,0x60($sp)
/*    29698:	03e00008 */ 	jr	$ra
/*    2969c:	27bd0108 */ 	addiu	$sp,$sp,0x108
);

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func000296a0
/*    296a0:	27bdfef0 */ 	addiu	$sp,$sp,-272
/*    296a4:	3c01cf80 */ 	lui	$at,0xcf80
/*    296a8:	44812000 */ 	mtc1	$at,$f4
/*    296ac:	afbf0074 */ 	sw	$ra,0x74($sp)
/*    296b0:	afbe0070 */ 	sw	$s8,0x70($sp)
/*    296b4:	afb7006c */ 	sw	$s7,0x6c($sp)
/*    296b8:	afb60068 */ 	sw	$s6,0x68($sp)
/*    296bc:	afb50064 */ 	sw	$s5,0x64($sp)
/*    296c0:	afb40060 */ 	sw	$s4,0x60($sp)
/*    296c4:	afb3005c */ 	sw	$s3,0x5c($sp)
/*    296c8:	afb20058 */ 	sw	$s2,0x58($sp)
/*    296cc:	afb10054 */ 	sw	$s1,0x54($sp)
/*    296d0:	afb00050 */ 	sw	$s0,0x50($sp)
/*    296d4:	f7be0048 */ 	sdc1	$f30,0x48($sp)
/*    296d8:	f7bc0040 */ 	sdc1	$f28,0x40($sp)
/*    296dc:	f7ba0038 */ 	sdc1	$f26,0x38($sp)
/*    296e0:	f7b80030 */ 	sdc1	$f24,0x30($sp)
/*    296e4:	f7b60028 */ 	sdc1	$f22,0x28($sp)
/*    296e8:	f7b40020 */ 	sdc1	$f20,0x20($sp)
/*    296ec:	afa60118 */ 	sw	$a2,0x118($sp)
/*    296f0:	afa7011c */ 	sw	$a3,0x11c($sp)
/*    296f4:	afa00100 */ 	sw	$zero,0x100($sp)
/*    296f8:	e7a40104 */ 	swc1	$f4,0x104($sp)
/*    296fc:	acc00000 */ 	sw	$zero,0x0($a2)
/*    29700:	8c8f0000 */ 	lw	$t7,0x0($a0)
/*    29704:	00a09025 */ 	or	$s2,$a1,$zero
/*    29708:	00809825 */ 	or	$s3,$a0,$zero
/*    2970c:	00008025 */ 	or	$s0,$zero,$zero
/*    29710:	00008825 */ 	or	$s1,$zero,$zero
/*    29714:	0000f025 */ 	or	$s8,$zero,$zero
/*    29718:	11e00024 */ 	beqz	$t7,.L000297ac
/*    2971c:	0080a825 */ 	or	$s5,$a0,$zero
/*    29720:	8ea70000 */ 	lw	$a3,0x0($s5)
/*    29724:	90e20000 */ 	lbu	$v0,0x0($a3)
.L00029728:
/*    29728:	24010001 */ 	addiu	$at,$zero,0x1
/*    2972c:	14400012 */ 	bnez	$v0,.L00029778
/*    29730:	00000000 */ 	nop
/*    29734:	94e20002 */ 	lhu	$v0,0x2($a3)
/*    29738:	00e02025 */ 	or	$a0,$a3,$zero
/*    2973c:	30584000 */ 	andi	$t8,$v0,0x4000
/*    29740:	13000003 */ 	beqz	$t8,.L00029750
/*    29744:	30590100 */ 	andi	$t9,$v0,0x100
/*    29748:	10000014 */ 	b	.L0002979c
/*    2974c:	aea00004 */ 	sw	$zero,0x4($s5)
.L00029750:
/*    29750:	53200003 */ 	beqzl	$t9,.L00029760
/*    29754:	8e450000 */ 	lw	$a1,0x0($s2)
/*    29758:	24110001 */ 	addiu	$s1,$zero,0x1
/*    2975c:	8e450000 */ 	lw	$a1,0x0($s2)
.L00029760:
/*    29760:	0c0098a2 */ 	jal	cdIs2dPointInTileType0
/*    29764:	8e460008 */ 	lw	$a2,0x8($s2)
/*    29768:	1040000c */ 	beqz	$v0,.L0002979c
/*    2976c:	aea20004 */ 	sw	$v0,0x4($s5)
/*    29770:	1000000a */ 	b	.L0002979c
/*    29774:	24100001 */ 	addiu	$s0,$zero,0x1
.L00029778:
/*    29778:	54410009 */ 	bnel	$v0,$at,.L000297a0
/*    2977c:	8ea70014 */ 	lw	$a3,0x14($s5)
/*    29780:	00e02025 */ 	or	$a0,$a3,$zero
/*    29784:	8e450000 */ 	lw	$a1,0x0($s2)
/*    29788:	0c0098f9 */ 	jal	cdIs2dPointInTileType1
/*    2978c:	8e460008 */ 	lw	$a2,0x8($s2)
/*    29790:	10400002 */ 	beqz	$v0,.L0002979c
/*    29794:	aea20004 */ 	sw	$v0,0x4($s5)
/*    29798:	24100001 */ 	addiu	$s0,$zero,0x1
.L0002979c:
/*    2979c:	8ea70014 */ 	lw	$a3,0x14($s5)
.L000297a0:
/*    297a0:	26b50014 */ 	addiu	$s5,$s5,0x14
/*    297a4:	54e0ffe0 */ 	bnezl	$a3,.L00029728
/*    297a8:	90e20000 */ 	lbu	$v0,0x0($a3)
.L000297ac:
/*    297ac:	52000068 */ 	beqzl	$s0,.L00029950
/*    297b0:	8fae0100 */ 	lw	$t6,0x100($sp)
/*    297b4:	8e620000 */ 	lw	$v0,0x0($s3)
/*    297b8:	0260a825 */ 	or	$s5,$s3,$zero
/*    297bc:	1040003c */ 	beqz	$v0,.L000298b0
/*    297c0:	00000000 */ 	nop
/*    297c4:	8ea80004 */ 	lw	$t0,0x4($s5)
.L000297c8:
/*    297c8:	51000034 */ 	beqzl	$t0,.L0002989c
/*    297cc:	8eaf0014 */ 	lw	$t7,0x14($s5)
/*    297d0:	8ea70000 */ 	lw	$a3,0x0($s5)
/*    297d4:	24010001 */ 	addiu	$at,$zero,0x1
/*    297d8:	90e20000 */ 	lbu	$v0,0x0($a3)
/*    297dc:	14400019 */ 	bnez	$v0,.L00029844
/*    297e0:	00000000 */ 	nop
/*    297e4:	94e90002 */ 	lhu	$t1,0x2($a3)
/*    297e8:	312a2000 */ 	andi	$t2,$t1,0x2000
/*    297ec:	5540002b */ 	bnezl	$t2,.L0002989c
/*    297f0:	8eaf0014 */ 	lw	$t7,0x14($s5)
/*    297f4:	00e02025 */ 	or	$a0,$a3,$zero
/*    297f8:	8e450000 */ 	lw	$a1,0x0($s2)
/*    297fc:	0c0097e4 */ 	jal	cdFindGroundInTileType0
/*    29800:	8e460008 */ 	lw	$a2,0x8($s2)
/*    29804:	c7a60104 */ 	lwc1	$f6,0x104($sp)
/*    29808:	4600303e */ 	c.le.s	$f6,$f0
/*    2980c:	00000000 */ 	nop
/*    29810:	45020022 */ 	bc1fl	.L0002989c
/*    29814:	8eaf0014 */ 	lw	$t7,0x14($s5)
/*    29818:	c6480004 */ 	lwc1	$f8,0x4($s2)
/*    2981c:	4608003c */ 	c.lt.s	$f0,$f8
/*    29820:	00000000 */ 	nop
/*    29824:	4502001d */ 	bc1fl	.L0002989c
/*    29828:	8eaf0014 */ 	lw	$t7,0x14($s5)
/*    2982c:	8fab0118 */ 	lw	$t3,0x118($sp)
/*    29830:	e7a00104 */ 	swc1	$f0,0x104($sp)
/*    29834:	240c0001 */ 	addiu	$t4,$zero,0x1
/*    29838:	ad750000 */ 	sw	$s5,0x0($t3)
/*    2983c:	10000016 */ 	b	.L00029898
/*    29840:	afac0100 */ 	sw	$t4,0x100($sp)
.L00029844:
/*    29844:	54410015 */ 	bnel	$v0,$at,.L0002989c
/*    29848:	8eaf0014 */ 	lw	$t7,0x14($s5)
/*    2984c:	00e02025 */ 	or	$a0,$a3,$zero
/*    29850:	8e450000 */ 	lw	$a1,0x0($s2)
/*    29854:	0c009833 */ 	jal	cdFindGroundInTileType1
/*    29858:	8e460008 */ 	lw	$a2,0x8($s2)
/*    2985c:	c7aa0104 */ 	lwc1	$f10,0x104($sp)
/*    29860:	4600503e */ 	c.le.s	$f10,$f0
/*    29864:	00000000 */ 	nop
/*    29868:	4502000c */ 	bc1fl	.L0002989c
/*    2986c:	8eaf0014 */ 	lw	$t7,0x14($s5)
/*    29870:	c6500004 */ 	lwc1	$f16,0x4($s2)
/*    29874:	4610003c */ 	c.lt.s	$f0,$f16
/*    29878:	00000000 */ 	nop
/*    2987c:	45020007 */ 	bc1fl	.L0002989c
/*    29880:	8eaf0014 */ 	lw	$t7,0x14($s5)
/*    29884:	8fad0118 */ 	lw	$t5,0x118($sp)
/*    29888:	e7a00104 */ 	swc1	$f0,0x104($sp)
/*    2988c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*    29890:	adb50000 */ 	sw	$s5,0x0($t5)
/*    29894:	afae0100 */ 	sw	$t6,0x100($sp)
.L00029898:
/*    29898:	8eaf0014 */ 	lw	$t7,0x14($s5)
.L0002989c:
/*    2989c:	26b50014 */ 	addiu	$s5,$s5,0x14
/*    298a0:	55e0ffc9 */ 	bnezl	$t7,.L000297c8
/*    298a4:	8ea80004 */ 	lw	$t0,0x4($s5)
/*    298a8:	0260a825 */ 	or	$s5,$s3,$zero
/*    298ac:	8e620000 */ 	lw	$v0,0x0($s3)
.L000298b0:
/*    298b0:	50400027 */ 	beqzl	$v0,.L00029950
/*    298b4:	8fae0100 */ 	lw	$t6,0x100($sp)
/*    298b8:	8eb80004 */ 	lw	$t8,0x4($s5)
.L000298bc:
/*    298bc:	53000020 */ 	beqzl	$t8,.L00029940
/*    298c0:	8ead0014 */ 	lw	$t5,0x14($s5)
/*    298c4:	8ea70000 */ 	lw	$a3,0x0($s5)
/*    298c8:	90f90000 */ 	lbu	$t9,0x0($a3)
/*    298cc:	5720001c */ 	bnezl	$t9,.L00029940
/*    298d0:	8ead0014 */ 	lw	$t5,0x14($s5)
/*    298d4:	94e80002 */ 	lhu	$t0,0x2($a3)
/*    298d8:	31092000 */ 	andi	$t1,$t0,0x2000
/*    298dc:	51200018 */ 	beqzl	$t1,.L00029940
/*    298e0:	8ead0014 */ 	lw	$t5,0x14($s5)
/*    298e4:	00e02025 */ 	or	$a0,$a3,$zero
/*    298e8:	8e450000 */ 	lw	$a1,0x0($s2)
/*    298ec:	0c0097e4 */ 	jal	cdFindGroundInTileType0
/*    298f0:	8e460008 */ 	lw	$a2,0x8($s2)
/*    298f4:	c7b20104 */ 	lwc1	$f18,0x104($sp)
/*    298f8:	4600903e */ 	c.le.s	$f18,$f0
/*    298fc:	00000000 */ 	nop
/*    29900:	4502000f */ 	bc1fl	.L00029940
/*    29904:	8ead0014 */ 	lw	$t5,0x14($s5)
/*    29908:	c6440004 */ 	lwc1	$f4,0x4($s2)
/*    2990c:	4604003c */ 	c.lt.s	$f0,$f4
/*    29910:	00000000 */ 	nop
/*    29914:	45030005 */ 	bc1tl	.L0002992c
/*    29918:	8fab0118 */ 	lw	$t3,0x118($sp)
/*    2991c:	8faa0100 */ 	lw	$t2,0x100($sp)
/*    29920:	55400007 */ 	bnezl	$t2,.L00029940
/*    29924:	8ead0014 */ 	lw	$t5,0x14($s5)
/*    29928:	8fab0118 */ 	lw	$t3,0x118($sp)
.L0002992c:
/*    2992c:	e7a00104 */ 	swc1	$f0,0x104($sp)
/*    29930:	240c0001 */ 	addiu	$t4,$zero,0x1
/*    29934:	ad750000 */ 	sw	$s5,0x0($t3)
/*    29938:	afac0100 */ 	sw	$t4,0x100($sp)
/*    2993c:	8ead0014 */ 	lw	$t5,0x14($s5)
.L00029940:
/*    29940:	26b50014 */ 	addiu	$s5,$s5,0x14
/*    29944:	55a0ffdd */ 	bnezl	$t5,.L000298bc
/*    29948:	8eb80004 */ 	lw	$t8,0x4($s5)
/*    2994c:	8fae0100 */ 	lw	$t6,0x100($sp)
.L00029950:
/*    29950:	3c014f80 */ 	lui	$at,0x4f80
/*    29954:	11c00003 */ 	beqz	$t6,.L00029964
/*    29958:	afae00f0 */ 	sw	$t6,0xf0($sp)
/*    2995c:	52200195 */ 	beqzl	$s1,.L00029fb4
/*    29960:	8fbf0074 */ 	lw	$ra,0x74($sp)
.L00029964:
/*    29964:	44813000 */ 	mtc1	$at,$f6
/*    29968:	0260a825 */ 	or	$s5,$s3,$zero
/*    2996c:	e7a600e4 */ 	swc1	$f6,0xe4($sp)
/*    29970:	8e6f0000 */ 	lw	$t7,0x0($s3)
/*    29974:	51e0018f */ 	beqzl	$t7,.L00029fb4
/*    29978:	8fbf0074 */ 	lw	$ra,0x74($sp)
/*    2997c:	8eb80004 */ 	lw	$t8,0x4($s5)
.L00029980:
/*    29980:	8fb900f0 */ 	lw	$t9,0xf0($sp)
/*    29984:	57000187 */ 	bnezl	$t8,.L00029fa4
/*    29988:	8ea80014 */ 	lw	$t0,0x14($s5)
/*    2998c:	13200008 */ 	beqz	$t9,.L000299b0
/*    29990:	8ea70000 */ 	lw	$a3,0x0($s5)
/*    29994:	90e80000 */ 	lbu	$t0,0x0($a3)
/*    29998:	55000182 */ 	bnezl	$t0,.L00029fa4
/*    2999c:	8ea80014 */ 	lw	$t0,0x14($s5)
/*    299a0:	94e90002 */ 	lhu	$t1,0x2($a3)
/*    299a4:	312a0100 */ 	andi	$t2,$t1,0x100
/*    299a8:	5140017e */ 	beqzl	$t2,.L00029fa4
/*    299ac:	8ea80014 */ 	lw	$t0,0x14($s5)
.L000299b0:
/*    299b0:	90e20000 */ 	lbu	$v0,0x0($a3)
/*    299b4:	544000d8 */ 	bnezl	$v0,.L00029d18
/*    299b8:	24010001 */ 	addiu	$at,$zero,0x1
/*    299bc:	94f70002 */ 	lhu	$s7,0x2($a3)
/*    299c0:	00e0a025 */ 	or	$s4,$a3,$zero
/*    299c4:	90e20001 */ 	lbu	$v0,0x1($a3)
/*    299c8:	32eb4000 */ 	andi	$t3,$s7,0x4000
/*    299cc:	000b602b */ 	sltu	$t4,$zero,$t3
/*    299d0:	11800004 */ 	beqz	$t4,.L000299e4
/*    299d4:	0180b825 */ 	or	$s7,$t4,$zero
/*    299d8:	8fad0100 */ 	lw	$t5,0x100($sp)
/*    299dc:	55a00171 */ 	bnezl	$t5,.L00029fa4
/*    299e0:	8ea80014 */ 	lw	$t0,0x14($s5)
.L000299e4:
/*    299e4:	1840016e */ 	blez	$v0,.L00029fa0
/*    299e8:	00008825 */ 	or	$s1,$zero,$zero
/*    299ec:	02809825 */ 	or	$s3,$s4,$zero
/*    299f0:	afa200bc */ 	sw	$v0,0xbc($sp)
/*    299f4:	8fa200bc */ 	lw	$v0,0xbc($sp)
.L000299f8:
/*    299f8:	26360001 */ 	addiu	$s6,$s1,0x1
/*    299fc:	866e000e */ 	lh	$t6,0xe($s3)
/*    29a00:	02c2001a */ 	div	$zero,$s6,$v0
/*    29a04:	0000c010 */ 	mfhi	$t8
/*    29a08:	0018c880 */ 	sll	$t9,$t8,0x2
/*    29a0c:	0338c823 */ 	subu	$t9,$t9,$t8
/*    29a10:	0019c840 */ 	sll	$t9,$t9,0x1
/*    29a14:	02998021 */ 	addu	$s0,$s4,$t9
/*    29a18:	8608000e */ 	lh	$t0,0xe($s0)
/*    29a1c:	86090012 */ 	lh	$t1,0x12($s0)
/*    29a20:	866f0012 */ 	lh	$t7,0x12($s3)
/*    29a24:	44888000 */ 	mtc1	$t0,$f16
/*    29a28:	44899000 */ 	mtc1	$t1,$f18
/*    29a2c:	448e4000 */ 	mtc1	$t6,$f8
/*    29a30:	448f5000 */ 	mtc1	$t7,$f10
/*    29a34:	468086a0 */ 	cvt.s.w	$f26,$f16
/*    29a38:	c6440000 */ 	lwc1	$f4,0x0($s2)
/*    29a3c:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*    29a40:	46809720 */ 	cvt.s.w	$f28,$f18
/*    29a44:	c6460008 */ 	lwc1	$f6,0x8($s2)
/*    29a48:	4406d000 */ 	mfc1	$a2,$f26
/*    29a4c:	e7a60014 */ 	swc1	$f6,0x14($sp)
/*    29a50:	468045a0 */ 	cvt.s.w	$f22,$f8
/*    29a54:	4407e000 */ 	mfc1	$a3,$f28
/*    29a58:	46805620 */ 	cvt.s.w	$f24,$f10
/*    29a5c:	14400002 */ 	bnez	$v0,.L00029a68
/*    29a60:	00000000 */ 	nop
/*    29a64:	0007000d */ 	break	0x7
.L00029a68:
/*    29a68:	2401ffff */ 	addiu	$at,$zero,-1
/*    29a6c:	14410004 */ 	bne	$v0,$at,.L00029a80
/*    29a70:	3c018000 */ 	lui	$at,0x8000
/*    29a74:	16c10002 */ 	bne	$s6,$at,.L00029a80
/*    29a78:	00000000 */ 	nop
/*    29a7c:	0006000d */ 	break	0x6
.L00029a80:
/*    29a80:	4600c386 */ 	mov.s	$f14,$f24
/*    29a84:	0c009595 */ 	jal	func00025654
/*    29a88:	4600b306 */ 	mov.s	$f12,$f22
/*    29a8c:	44804000 */ 	mtc1	$zero,$f8
/*    29a90:	e7a000d4 */ 	swc1	$f0,0xd4($sp)
/*    29a94:	46000786 */ 	mov.s	$f30,$f0
/*    29a98:	4608003c */ 	c.lt.s	$f0,$f8
/*    29a9c:	c7aa00e4 */ 	lwc1	$f10,0xe4($sp)
/*    29aa0:	45020003 */ 	bc1fl	.L00029ab0
/*    29aa4:	460af03c */ 	c.lt.s	$f30,$f10
/*    29aa8:	46000787 */ 	neg.s	$f30,$f0
/*    29aac:	460af03c */ 	c.lt.s	$f30,$f10
.L00029ab0:
/*    29ab0:	00000000 */ 	nop
/*    29ab4:	45030004 */ 	bc1tl	.L00029ac8
/*    29ab8:	c6500000 */ 	lwc1	$f16,0x0($s2)
/*    29abc:	53c0008f */ 	beqzl	$s8,.L00029cfc
/*    29ac0:	8fa900bc */ 	lw	$t1,0xbc($sp)
/*    29ac4:	c6500000 */ 	lwc1	$f16,0x0($s2)
.L00029ac8:
/*    29ac8:	4406d000 */ 	mfc1	$a2,$f26
/*    29acc:	4407e000 */ 	mfc1	$a3,$f28
/*    29ad0:	e7b00010 */ 	swc1	$f16,0x10($sp)
/*    29ad4:	c6520008 */ 	lwc1	$f18,0x8($s2)
/*    29ad8:	4600b306 */ 	mov.s	$f12,$f22
/*    29adc:	4600c386 */ 	mov.s	$f14,$f24
/*    29ae0:	0c0095dd */ 	jal	func00025774
/*    29ae4:	e7b20014 */ 	swc1	$f18,0x14($sp)
/*    29ae8:	5040002c */ 	beqzl	$v0,.L00029b9c
/*    29aec:	4600b306 */ 	mov.s	$f12,$f22
/*    29af0:	4616d001 */ 	sub.s	$f0,$f26,$f22
/*    29af4:	4618e501 */ 	sub.s	$f20,$f28,$f24
/*    29af8:	46000102 */ 	mul.s	$f4,$f0,$f0
/*    29afc:	e7a000b8 */ 	swc1	$f0,0xb8($sp)
/*    29b00:	4614a182 */ 	mul.s	$f6,$f20,$f20
/*    29b04:	0c012974 */ 	jal	sqrtf
/*    29b08:	46062300 */ 	add.s	$f12,$f4,$f6
/*    29b0c:	c7a800d4 */ 	lwc1	$f8,0xd4($sp)
/*    29b10:	4600a407 */ 	neg.s	$f16,$f20
/*    29b14:	c7a600b8 */ 	lwc1	$f6,0xb8($sp)
/*    29b18:	46004383 */ 	div.s	$f14,$f8,$f0
/*    29b1c:	c64a0000 */ 	lwc1	$f10,0x0($s2)
/*    29b20:	c6440008 */ 	lwc1	$f4,0x8($s2)
/*    29b24:	02802025 */ 	or	$a0,$s4,$zero
/*    29b28:	02203825 */ 	or	$a3,$s1,$zero
/*    29b2c:	46107482 */ 	mul.s	$f18,$f14,$f16
/*    29b30:	00000000 */ 	nop
/*    29b34:	46067202 */ 	mul.s	$f8,$f14,$f6
/*    29b38:	46125080 */ 	add.s	$f2,$f10,$f18
/*    29b3c:	46082300 */ 	add.s	$f12,$f4,$f8
/*    29b40:	44051000 */ 	mfc1	$a1,$f2
/*    29b44:	44066000 */ 	mfc1	$a2,$f12
/*    29b48:	0c00971d */ 	jal	cdFindGroundInTileType0AtVertex
/*    29b4c:	00000000 */ 	nop
/*    29b50:	c6500004 */ 	lwc1	$f16,0x4($s2)
/*    29b54:	4610003c */ 	c.lt.s	$f0,$f16
/*    29b58:	00000000 */ 	nop
/*    29b5c:	45030007 */ 	bc1tl	.L00029b7c
/*    29b60:	8fad0118 */ 	lw	$t5,0x118($sp)
/*    29b64:	8eaa0000 */ 	lw	$t2,0x0($s5)
/*    29b68:	954b0002 */ 	lhu	$t3,0x2($t2)
/*    29b6c:	316c2000 */ 	andi	$t4,$t3,0x2000
/*    29b70:	51800062 */ 	beqzl	$t4,.L00029cfc
/*    29b74:	8fa900bc */ 	lw	$t1,0xbc($sp)
/*    29b78:	8fad0118 */ 	lw	$t5,0x118($sp)
.L00029b7c:
/*    29b7c:	e7a00104 */ 	swc1	$f0,0x104($sp)
/*    29b80:	240e0001 */ 	addiu	$t6,$zero,0x1
/*    29b84:	adb50000 */ 	sw	$s5,0x0($t5)
/*    29b88:	e7be00e4 */ 	swc1	$f30,0xe4($sp)
/*    29b8c:	afae0100 */ 	sw	$t6,0x100($sp)
/*    29b90:	10000059 */ 	b	.L00029cf8
/*    29b94:	02e0f025 */ 	or	$s8,$s7,$zero
/*    29b98:	4600b306 */ 	mov.s	$f12,$f22
.L00029b9c:
/*    29b9c:	4600c386 */ 	mov.s	$f14,$f24
/*    29ba0:	8e460000 */ 	lw	$a2,0x0($s2)
/*    29ba4:	0c0095c9 */ 	jal	func00025724
/*    29ba8:	8e470008 */ 	lw	$a3,0x8($s2)
/*    29bac:	46000506 */ 	mov.s	$f20,$f0
/*    29bb0:	4600d306 */ 	mov.s	$f12,$f26
/*    29bb4:	4600e386 */ 	mov.s	$f14,$f28
/*    29bb8:	8e460000 */ 	lw	$a2,0x0($s2)
/*    29bbc:	0c0095c9 */ 	jal	func00025724
/*    29bc0:	8e470008 */ 	lw	$a3,0x8($s2)
/*    29bc4:	4600a03c */ 	c.lt.s	$f20,$f0
/*    29bc8:	46000586 */ 	mov.s	$f22,$f0
/*    29bcc:	45020027 */ 	bc1fl	.L00029c6c
/*    29bd0:	c7a800e4 */ 	lwc1	$f8,0xe4($sp)
/*    29bd4:	c7aa00e4 */ 	lwc1	$f10,0xe4($sp)
/*    29bd8:	460aa03c */ 	c.lt.s	$f20,$f10
/*    29bdc:	00000000 */ 	nop
/*    29be0:	45030004 */ 	bc1tl	.L00029bf4
/*    29be4:	866f000e */ 	lh	$t7,0xe($s3)
/*    29be8:	53c00044 */ 	beqzl	$s8,.L00029cfc
/*    29bec:	8fa900bc */ 	lw	$t1,0xbc($sp)
/*    29bf0:	866f000e */ 	lh	$t7,0xe($s3)
.L00029bf4:
/*    29bf4:	86780012 */ 	lh	$t8,0x12($s3)
/*    29bf8:	02802025 */ 	or	$a0,$s4,$zero
/*    29bfc:	448f9000 */ 	mtc1	$t7,$f18
/*    29c00:	44983000 */ 	mtc1	$t8,$f6
/*    29c04:	02203825 */ 	or	$a3,$s1,$zero
/*    29c08:	468090a0 */ 	cvt.s.w	$f2,$f18
/*    29c0c:	46803320 */ 	cvt.s.w	$f12,$f6
/*    29c10:	44051000 */ 	mfc1	$a1,$f2
/*    29c14:	44066000 */ 	mfc1	$a2,$f12
/*    29c18:	0c00971d */ 	jal	cdFindGroundInTileType0AtVertex
/*    29c1c:	00000000 */ 	nop
/*    29c20:	c6440004 */ 	lwc1	$f4,0x4($s2)
/*    29c24:	4604003c */ 	c.lt.s	$f0,$f4
/*    29c28:	00000000 */ 	nop
/*    29c2c:	45030007 */ 	bc1tl	.L00029c4c
/*    29c30:	8faa0118 */ 	lw	$t2,0x118($sp)
/*    29c34:	8eb90000 */ 	lw	$t9,0x0($s5)
/*    29c38:	97280002 */ 	lhu	$t0,0x2($t9)
/*    29c3c:	31092000 */ 	andi	$t1,$t0,0x2000
/*    29c40:	5120002e */ 	beqzl	$t1,.L00029cfc
/*    29c44:	8fa900bc */ 	lw	$t1,0xbc($sp)
/*    29c48:	8faa0118 */ 	lw	$t2,0x118($sp)
.L00029c4c:
/*    29c4c:	e7a00104 */ 	swc1	$f0,0x104($sp)
/*    29c50:	240b0001 */ 	addiu	$t3,$zero,0x1
/*    29c54:	ad550000 */ 	sw	$s5,0x0($t2)
/*    29c58:	e7b400e4 */ 	swc1	$f20,0xe4($sp)
/*    29c5c:	afab0100 */ 	sw	$t3,0x100($sp)
/*    29c60:	10000025 */ 	b	.L00029cf8
/*    29c64:	02e0f025 */ 	or	$s8,$s7,$zero
/*    29c68:	c7a800e4 */ 	lwc1	$f8,0xe4($sp)
.L00029c6c:
/*    29c6c:	4608003c */ 	c.lt.s	$f0,$f8
/*    29c70:	00000000 */ 	nop
/*    29c74:	45030004 */ 	bc1tl	.L00029c88
/*    29c78:	860c000e */ 	lh	$t4,0xe($s0)
/*    29c7c:	53c0001f */ 	beqzl	$s8,.L00029cfc
/*    29c80:	8fa900bc */ 	lw	$t1,0xbc($sp)
/*    29c84:	860c000e */ 	lh	$t4,0xe($s0)
.L00029c88:
/*    29c88:	860d0012 */ 	lh	$t5,0x12($s0)
/*    29c8c:	02802025 */ 	or	$a0,$s4,$zero
/*    29c90:	448c8000 */ 	mtc1	$t4,$f16
/*    29c94:	448d5000 */ 	mtc1	$t5,$f10
/*    29c98:	02203825 */ 	or	$a3,$s1,$zero
/*    29c9c:	468080a0 */ 	cvt.s.w	$f2,$f16
/*    29ca0:	46805320 */ 	cvt.s.w	$f12,$f10
/*    29ca4:	44051000 */ 	mfc1	$a1,$f2
/*    29ca8:	44066000 */ 	mfc1	$a2,$f12
/*    29cac:	0c00971d */ 	jal	cdFindGroundInTileType0AtVertex
/*    29cb0:	00000000 */ 	nop
/*    29cb4:	c6520004 */ 	lwc1	$f18,0x4($s2)
/*    29cb8:	4612003c */ 	c.lt.s	$f0,$f18
/*    29cbc:	00000000 */ 	nop
/*    29cc0:	45030007 */ 	bc1tl	.L00029ce0
/*    29cc4:	8fb90118 */ 	lw	$t9,0x118($sp)
/*    29cc8:	8eae0000 */ 	lw	$t6,0x0($s5)
/*    29ccc:	95cf0002 */ 	lhu	$t7,0x2($t6)
/*    29cd0:	31f82000 */ 	andi	$t8,$t7,0x2000
/*    29cd4:	53000009 */ 	beqzl	$t8,.L00029cfc
/*    29cd8:	8fa900bc */ 	lw	$t1,0xbc($sp)
/*    29cdc:	8fb90118 */ 	lw	$t9,0x118($sp)
.L00029ce0:
/*    29ce0:	e7a00104 */ 	swc1	$f0,0x104($sp)
/*    29ce4:	24080001 */ 	addiu	$t0,$zero,0x1
/*    29ce8:	af350000 */ 	sw	$s5,0x0($t9)
/*    29cec:	e7b600e4 */ 	swc1	$f22,0xe4($sp)
/*    29cf0:	afa80100 */ 	sw	$t0,0x100($sp)
/*    29cf4:	02e0f025 */ 	or	$s8,$s7,$zero
.L00029cf8:
/*    29cf8:	8fa900bc */ 	lw	$t1,0xbc($sp)
.L00029cfc:
/*    29cfc:	02c08825 */ 	or	$s1,$s6,$zero
/*    29d00:	26730006 */ 	addiu	$s3,$s3,0x6
/*    29d04:	56c9ff3c */ 	bnel	$s6,$t1,.L000299f8
/*    29d08:	8fa200bc */ 	lw	$v0,0xbc($sp)
/*    29d0c:	100000a5 */ 	b	.L00029fa4
/*    29d10:	8ea80014 */ 	lw	$t0,0x14($s5)
/*    29d14:	24010001 */ 	addiu	$at,$zero,0x1
.L00029d18:
/*    29d18:	544100a2 */ 	bnel	$v0,$at,.L00029fa4
/*    29d1c:	8ea80014 */ 	lw	$t0,0x14($s5)
/*    29d20:	90f60001 */ 	lbu	$s6,0x1($a3)
/*    29d24:	00e09825 */ 	or	$s3,$a3,$zero
/*    29d28:	00001025 */ 	or	$v0,$zero,$zero
/*    29d2c:	1ac0009c */ 	blez	$s6,.L00029fa0
/*    29d30:	00e08825 */ 	or	$s1,$a3,$zero
.L00029d34:
/*    29d34:	24540001 */ 	addiu	$s4,$v0,0x1
/*    29d38:	0296001a */ 	div	$zero,$s4,$s6
/*    29d3c:	00005010 */ 	mfhi	$t2
/*    29d40:	000a5880 */ 	sll	$t3,$t2,0x2
/*    29d44:	016a5823 */ 	subu	$t3,$t3,$t2
/*    29d48:	000b5880 */ 	sll	$t3,$t3,0x2
/*    29d4c:	026b8021 */ 	addu	$s0,$s3,$t3
/*    29d50:	c6460000 */ 	lwc1	$f6,0x0($s2)
/*    29d54:	c61a0010 */ 	lwc1	$f26,0x10($s0)
/*    29d58:	c61c0018 */ 	lwc1	$f28,0x18($s0)
/*    29d5c:	c6360010 */ 	lwc1	$f22,0x10($s1)
/*    29d60:	c6380018 */ 	lwc1	$f24,0x18($s1)
/*    29d64:	e7a60010 */ 	swc1	$f6,0x10($sp)
/*    29d68:	c6440008 */ 	lwc1	$f4,0x8($s2)
/*    29d6c:	16c00002 */ 	bnez	$s6,.L00029d78
/*    29d70:	00000000 */ 	nop
/*    29d74:	0007000d */ 	break	0x7
.L00029d78:
/*    29d78:	2401ffff */ 	addiu	$at,$zero,-1
/*    29d7c:	16c10004 */ 	bne	$s6,$at,.L00029d90
/*    29d80:	3c018000 */ 	lui	$at,0x8000
/*    29d84:	16810002 */ 	bne	$s4,$at,.L00029d90
/*    29d88:	00000000 */ 	nop
/*    29d8c:	0006000d */ 	break	0x6
.L00029d90:
/*    29d90:	4406d000 */ 	mfc1	$a2,$f26
/*    29d94:	4407e000 */ 	mfc1	$a3,$f28
/*    29d98:	4600b306 */ 	mov.s	$f12,$f22
/*    29d9c:	4600c386 */ 	mov.s	$f14,$f24
/*    29da0:	0c009595 */ 	jal	func00025654
/*    29da4:	e7a40014 */ 	swc1	$f4,0x14($sp)
/*    29da8:	44804000 */ 	mtc1	$zero,$f8
/*    29dac:	e7a00094 */ 	swc1	$f0,0x94($sp)
/*    29db0:	46000786 */ 	mov.s	$f30,$f0
/*    29db4:	4608003c */ 	c.lt.s	$f0,$f8
/*    29db8:	c7b000e4 */ 	lwc1	$f16,0xe4($sp)
/*    29dbc:	45020003 */ 	bc1fl	.L00029dcc
/*    29dc0:	4610f03c */ 	c.lt.s	$f30,$f16
/*    29dc4:	46000787 */ 	neg.s	$f30,$f0
/*    29dc8:	4610f03c */ 	c.lt.s	$f30,$f16
.L00029dcc:
/*    29dcc:	00000000 */ 	nop
/*    29dd0:	45020071 */ 	bc1fl	.L00029f98
/*    29dd4:	02801025 */ 	or	$v0,$s4,$zero
/*    29dd8:	c64a0000 */ 	lwc1	$f10,0x0($s2)
/*    29ddc:	4406d000 */ 	mfc1	$a2,$f26
/*    29de0:	4407e000 */ 	mfc1	$a3,$f28
/*    29de4:	e7aa0010 */ 	swc1	$f10,0x10($sp)
/*    29de8:	c6520008 */ 	lwc1	$f18,0x8($s2)
/*    29dec:	4600b306 */ 	mov.s	$f12,$f22
/*    29df0:	4600c386 */ 	mov.s	$f14,$f24
/*    29df4:	0c0095dd */ 	jal	func00025774
/*    29df8:	e7b20014 */ 	swc1	$f18,0x14($sp)
/*    29dfc:	50400026 */ 	beqzl	$v0,.L00029e98
/*    29e00:	4600b306 */ 	mov.s	$f12,$f22
/*    29e04:	4616d001 */ 	sub.s	$f0,$f26,$f22
/*    29e08:	4618e501 */ 	sub.s	$f20,$f28,$f24
/*    29e0c:	46000182 */ 	mul.s	$f6,$f0,$f0
/*    29e10:	e7a00078 */ 	swc1	$f0,0x78($sp)
/*    29e14:	4614a102 */ 	mul.s	$f4,$f20,$f20
/*    29e18:	0c012974 */ 	jal	sqrtf
/*    29e1c:	46043300 */ 	add.s	$f12,$f6,$f4
/*    29e20:	c7a80094 */ 	lwc1	$f8,0x94($sp)
/*    29e24:	4600a287 */ 	neg.s	$f10,$f20
/*    29e28:	c7a40078 */ 	lwc1	$f4,0x78($sp)
/*    29e2c:	46004383 */ 	div.s	$f14,$f8,$f0
/*    29e30:	c6500000 */ 	lwc1	$f16,0x0($s2)
/*    29e34:	c6460008 */ 	lwc1	$f6,0x8($s2)
/*    29e38:	02602025 */ 	or	$a0,$s3,$zero
/*    29e3c:	460a7482 */ 	mul.s	$f18,$f14,$f10
/*    29e40:	00000000 */ 	nop
/*    29e44:	46047202 */ 	mul.s	$f8,$f14,$f4
/*    29e48:	46128080 */ 	add.s	$f2,$f16,$f18
/*    29e4c:	46083300 */ 	add.s	$f12,$f6,$f8
/*    29e50:	44051000 */ 	mfc1	$a1,$f2
/*    29e54:	44066000 */ 	mfc1	$a2,$f12
/*    29e58:	0c009833 */ 	jal	cdFindGroundInTileType1
/*    29e5c:	00000000 */ 	nop
/*    29e60:	c64a0004 */ 	lwc1	$f10,0x4($s2)
/*    29e64:	460a003c */ 	c.lt.s	$f0,$f10
/*    29e68:	00000000 */ 	nop
/*    29e6c:	4502004a */ 	bc1fl	.L00029f98
/*    29e70:	02801025 */ 	or	$v0,$s4,$zero
/*    29e74:	8fac0118 */ 	lw	$t4,0x118($sp)
/*    29e78:	e7a00104 */ 	swc1	$f0,0x104($sp)
/*    29e7c:	240d0001 */ 	addiu	$t5,$zero,0x1
/*    29e80:	ad950000 */ 	sw	$s5,0x0($t4)
/*    29e84:	e7be00e4 */ 	swc1	$f30,0xe4($sp)
/*    29e88:	afad0100 */ 	sw	$t5,0x100($sp)
/*    29e8c:	10000041 */ 	b	.L00029f94
/*    29e90:	0000f025 */ 	or	$s8,$zero,$zero
/*    29e94:	4600b306 */ 	mov.s	$f12,$f22
.L00029e98:
/*    29e98:	4600c386 */ 	mov.s	$f14,$f24
/*    29e9c:	8e460000 */ 	lw	$a2,0x0($s2)
/*    29ea0:	0c0095c9 */ 	jal	func00025724
/*    29ea4:	8e470008 */ 	lw	$a3,0x8($s2)
/*    29ea8:	46000506 */ 	mov.s	$f20,$f0
/*    29eac:	4600d306 */ 	mov.s	$f12,$f26
/*    29eb0:	4600e386 */ 	mov.s	$f14,$f28
/*    29eb4:	8e460000 */ 	lw	$a2,0x0($s2)
/*    29eb8:	0c0095c9 */ 	jal	func00025724
/*    29ebc:	8e470008 */ 	lw	$a3,0x8($s2)
/*    29ec0:	4600a03c */ 	c.lt.s	$f20,$f0
/*    29ec4:	46000586 */ 	mov.s	$f22,$f0
/*    29ec8:	4502001b */ 	bc1fl	.L00029f38
/*    29ecc:	c7a400e4 */ 	lwc1	$f4,0xe4($sp)
/*    29ed0:	c7b000e4 */ 	lwc1	$f16,0xe4($sp)
/*    29ed4:	4610a03c */ 	c.lt.s	$f20,$f16
/*    29ed8:	00000000 */ 	nop
/*    29edc:	4502002e */ 	bc1fl	.L00029f98
/*    29ee0:	02801025 */ 	or	$v0,$s4,$zero
/*    29ee4:	c6220010 */ 	lwc1	$f2,0x10($s1)
/*    29ee8:	c62c0018 */ 	lwc1	$f12,0x18($s1)
/*    29eec:	02602025 */ 	or	$a0,$s3,$zero
/*    29ef0:	44051000 */ 	mfc1	$a1,$f2
/*    29ef4:	44066000 */ 	mfc1	$a2,$f12
/*    29ef8:	0c009833 */ 	jal	cdFindGroundInTileType1
/*    29efc:	00000000 */ 	nop
/*    29f00:	c6520004 */ 	lwc1	$f18,0x4($s2)
/*    29f04:	4612003c */ 	c.lt.s	$f0,$f18
/*    29f08:	00000000 */ 	nop
/*    29f0c:	45020022 */ 	bc1fl	.L00029f98
/*    29f10:	02801025 */ 	or	$v0,$s4,$zero
/*    29f14:	8fae0118 */ 	lw	$t6,0x118($sp)
/*    29f18:	e7a00104 */ 	swc1	$f0,0x104($sp)
/*    29f1c:	240f0001 */ 	addiu	$t7,$zero,0x1
/*    29f20:	add50000 */ 	sw	$s5,0x0($t6)
/*    29f24:	e7b400e4 */ 	swc1	$f20,0xe4($sp)
/*    29f28:	afaf0100 */ 	sw	$t7,0x100($sp)
/*    29f2c:	10000019 */ 	b	.L00029f94
/*    29f30:	0000f025 */ 	or	$s8,$zero,$zero
/*    29f34:	c7a400e4 */ 	lwc1	$f4,0xe4($sp)
.L00029f38:
/*    29f38:	4604003c */ 	c.lt.s	$f0,$f4
/*    29f3c:	00000000 */ 	nop
/*    29f40:	45020015 */ 	bc1fl	.L00029f98
/*    29f44:	02801025 */ 	or	$v0,$s4,$zero
/*    29f48:	c6020010 */ 	lwc1	$f2,0x10($s0)
/*    29f4c:	c60c0018 */ 	lwc1	$f12,0x18($s0)
/*    29f50:	02602025 */ 	or	$a0,$s3,$zero
/*    29f54:	44051000 */ 	mfc1	$a1,$f2
/*    29f58:	44066000 */ 	mfc1	$a2,$f12
/*    29f5c:	0c009833 */ 	jal	cdFindGroundInTileType1
/*    29f60:	00000000 */ 	nop
/*    29f64:	c6460004 */ 	lwc1	$f6,0x4($s2)
/*    29f68:	4606003c */ 	c.lt.s	$f0,$f6
/*    29f6c:	00000000 */ 	nop
/*    29f70:	45020009 */ 	bc1fl	.L00029f98
/*    29f74:	02801025 */ 	or	$v0,$s4,$zero
/*    29f78:	8fb80118 */ 	lw	$t8,0x118($sp)
/*    29f7c:	e7a00104 */ 	swc1	$f0,0x104($sp)
/*    29f80:	24190001 */ 	addiu	$t9,$zero,0x1
/*    29f84:	af150000 */ 	sw	$s5,0x0($t8)
/*    29f88:	e7b600e4 */ 	swc1	$f22,0xe4($sp)
/*    29f8c:	afb90100 */ 	sw	$t9,0x100($sp)
/*    29f90:	0000f025 */ 	or	$s8,$zero,$zero
.L00029f94:
/*    29f94:	02801025 */ 	or	$v0,$s4,$zero
.L00029f98:
/*    29f98:	1696ff66 */ 	bne	$s4,$s6,.L00029d34
/*    29f9c:	2631000c */ 	addiu	$s1,$s1,0xc
.L00029fa0:
/*    29fa0:	8ea80014 */ 	lw	$t0,0x14($s5)
.L00029fa4:
/*    29fa4:	26b50014 */ 	addiu	$s5,$s5,0x14
/*    29fa8:	5500fe75 */ 	bnezl	$t0,.L00029980
/*    29fac:	8eb80004 */ 	lw	$t8,0x4($s5)
/*    29fb0:	8fbf0074 */ 	lw	$ra,0x74($sp)
.L00029fb4:
/*    29fb4:	c7a00104 */ 	lwc1	$f0,0x104($sp)
/*    29fb8:	d7b40020 */ 	ldc1	$f20,0x20($sp)
/*    29fbc:	d7b60028 */ 	ldc1	$f22,0x28($sp)
/*    29fc0:	d7b80030 */ 	ldc1	$f24,0x30($sp)
/*    29fc4:	d7ba0038 */ 	ldc1	$f26,0x38($sp)
/*    29fc8:	d7bc0040 */ 	ldc1	$f28,0x40($sp)
/*    29fcc:	d7be0048 */ 	ldc1	$f30,0x48($sp)
/*    29fd0:	8fb00050 */ 	lw	$s0,0x50($sp)
/*    29fd4:	8fb10054 */ 	lw	$s1,0x54($sp)
/*    29fd8:	8fb20058 */ 	lw	$s2,0x58($sp)
/*    29fdc:	8fb3005c */ 	lw	$s3,0x5c($sp)
/*    29fe0:	8fb40060 */ 	lw	$s4,0x60($sp)
/*    29fe4:	8fb50064 */ 	lw	$s5,0x64($sp)
/*    29fe8:	8fb60068 */ 	lw	$s6,0x68($sp)
/*    29fec:	8fb7006c */ 	lw	$s7,0x6c($sp)
/*    29ff0:	8fbe0070 */ 	lw	$s8,0x70($sp)
/*    29ff4:	03e00008 */ 	jr	$ra
/*    29ff8:	27bd0110 */ 	addiu	$sp,$sp,0x110
);
#else
GLOBAL_ASM(
glabel func000296a0
/*    2ab9c:	27bdfef8 */ 	addiu	$sp,$sp,-264
/*    2aba0:	3c01cf80 */ 	lui	$at,0xcf80
/*    2aba4:	44812000 */ 	mtc1	$at,$f4
/*    2aba8:	afbf0074 */ 	sw	$ra,0x74($sp)
/*    2abac:	afbe0070 */ 	sw	$s8,0x70($sp)
/*    2abb0:	afb7006c */ 	sw	$s7,0x6c($sp)
/*    2abb4:	afb60068 */ 	sw	$s6,0x68($sp)
/*    2abb8:	afb50064 */ 	sw	$s5,0x64($sp)
/*    2abbc:	afb40060 */ 	sw	$s4,0x60($sp)
/*    2abc0:	afb3005c */ 	sw	$s3,0x5c($sp)
/*    2abc4:	afb20058 */ 	sw	$s2,0x58($sp)
/*    2abc8:	afb10054 */ 	sw	$s1,0x54($sp)
/*    2abcc:	afb00050 */ 	sw	$s0,0x50($sp)
/*    2abd0:	f7be0048 */ 	sdc1	$f30,0x48($sp)
/*    2abd4:	f7bc0040 */ 	sdc1	$f28,0x40($sp)
/*    2abd8:	f7ba0038 */ 	sdc1	$f26,0x38($sp)
/*    2abdc:	f7b80030 */ 	sdc1	$f24,0x30($sp)
/*    2abe0:	f7b60028 */ 	sdc1	$f22,0x28($sp)
/*    2abe4:	f7b40020 */ 	sdc1	$f20,0x20($sp)
/*    2abe8:	afa70114 */ 	sw	$a3,0x114($sp)
/*    2abec:	afa000f8 */ 	sw	$zero,0xf8($sp)
/*    2abf0:	e7a400fc */ 	swc1	$f4,0xfc($sp)
/*    2abf4:	acc00000 */ 	sw	$zero,0x0($a2)
/*    2abf8:	8c8e0000 */ 	lw	$t6,0x0($a0)
/*    2abfc:	00a09025 */ 	or	$s2,$a1,$zero
/*    2ac00:	00809825 */ 	or	$s3,$a0,$zero
/*    2ac04:	00c0f025 */ 	or	$s8,$a2,$zero
/*    2ac08:	00008025 */ 	or	$s0,$zero,$zero
/*    2ac0c:	00008825 */ 	or	$s1,$zero,$zero
/*    2ac10:	11c00025 */ 	beqz	$t6,.NB0002aca8
/*    2ac14:	0080b025 */ 	or	$s6,$a0,$zero
/*    2ac18:	8ec70000 */ 	lw	$a3,0x0($s6)
/*    2ac1c:	90e20000 */ 	lbu	$v0,0x0($a3)
.NB0002ac20:
/*    2ac20:	24010001 */ 	addiu	$at,$zero,0x1
/*    2ac24:	14400013 */ 	bnez	$v0,.NB0002ac74
/*    2ac28:	00000000 */ 	sll	$zero,$zero,0x0
/*    2ac2c:	94e20002 */ 	lhu	$v0,0x2($a3)
/*    2ac30:	00e02025 */ 	or	$a0,$a3,$zero
/*    2ac34:	304f4000 */ 	andi	$t7,$v0,0x4000
/*    2ac38:	51e00004 */ 	beqzl	$t7,.NB0002ac4c
/*    2ac3c:	30580100 */ 	andi	$t8,$v0,0x100
/*    2ac40:	10000015 */ 	beqz	$zero,.NB0002ac98
/*    2ac44:	aec00004 */ 	sw	$zero,0x4($s6)
/*    2ac48:	30580100 */ 	andi	$t8,$v0,0x100
.NB0002ac4c:
/*    2ac4c:	53000003 */ 	beqzl	$t8,.NB0002ac5c
/*    2ac50:	8e450000 */ 	lw	$a1,0x0($s2)
/*    2ac54:	24110001 */ 	addiu	$s1,$zero,0x1
/*    2ac58:	8e450000 */ 	lw	$a1,0x0($s2)
.NB0002ac5c:
/*    2ac5c:	0c009da6 */ 	jal	cdIs2dPointInTileType0
/*    2ac60:	8e460008 */ 	lw	$a2,0x8($s2)
/*    2ac64:	1040000c */ 	beqz	$v0,.NB0002ac98
/*    2ac68:	aec20004 */ 	sw	$v0,0x4($s6)
/*    2ac6c:	1000000a */ 	beqz	$zero,.NB0002ac98
/*    2ac70:	24100001 */ 	addiu	$s0,$zero,0x1
.NB0002ac74:
/*    2ac74:	54410009 */ 	bnel	$v0,$at,.NB0002ac9c
/*    2ac78:	8ec70014 */ 	lw	$a3,0x14($s6)
/*    2ac7c:	00e02025 */ 	or	$a0,$a3,$zero
/*    2ac80:	8e450000 */ 	lw	$a1,0x0($s2)
/*    2ac84:	0c009dfd */ 	jal	cdIs2dPointInTileType1
/*    2ac88:	8e460008 */ 	lw	$a2,0x8($s2)
/*    2ac8c:	10400002 */ 	beqz	$v0,.NB0002ac98
/*    2ac90:	aec20004 */ 	sw	$v0,0x4($s6)
/*    2ac94:	24100001 */ 	addiu	$s0,$zero,0x1
.NB0002ac98:
/*    2ac98:	8ec70014 */ 	lw	$a3,0x14($s6)
.NB0002ac9c:
/*    2ac9c:	26d60014 */ 	addiu	$s6,$s6,0x14
/*    2aca0:	54e0ffdf */ 	bnezl	$a3,.NB0002ac20
/*    2aca4:	90e20000 */ 	lbu	$v0,0x0($a3)
.NB0002aca8:
/*    2aca8:	52000065 */ 	beqzl	$s0,.NB0002ae40
/*    2acac:	8faa00f8 */ 	lw	$t2,0xf8($sp)
/*    2acb0:	8e620000 */ 	lw	$v0,0x0($s3)
/*    2acb4:	0260b025 */ 	or	$s6,$s3,$zero
/*    2acb8:	1040003a */ 	beqz	$v0,.NB0002ada4
/*    2acbc:	00000000 */ 	sll	$zero,$zero,0x0
/*    2acc0:	8ed90004 */ 	lw	$t9,0x4($s6)
.NB0002acc4:
/*    2acc4:	53200032 */ 	beqzl	$t9,.NB0002ad90
/*    2acc8:	8ecc0014 */ 	lw	$t4,0x14($s6)
/*    2accc:	8ec70000 */ 	lw	$a3,0x0($s6)
/*    2acd0:	24010001 */ 	addiu	$at,$zero,0x1
/*    2acd4:	90e20000 */ 	lbu	$v0,0x0($a3)
/*    2acd8:	14400018 */ 	bnez	$v0,.NB0002ad3c
/*    2acdc:	00000000 */ 	sll	$zero,$zero,0x0
/*    2ace0:	94e80002 */ 	lhu	$t0,0x2($a3)
/*    2ace4:	31092000 */ 	andi	$t1,$t0,0x2000
/*    2ace8:	55200029 */ 	bnezl	$t1,.NB0002ad90
/*    2acec:	8ecc0014 */ 	lw	$t4,0x14($s6)
/*    2acf0:	00e02025 */ 	or	$a0,$a3,$zero
/*    2acf4:	8e450000 */ 	lw	$a1,0x0($s2)
/*    2acf8:	0c009ce8 */ 	jal	cdFindGroundInTileType0
/*    2acfc:	8e460008 */ 	lw	$a2,0x8($s2)
/*    2ad00:	c7a600fc */ 	lwc1	$f6,0xfc($sp)
/*    2ad04:	4600303e */ 	c.le.s	$f6,$f0
/*    2ad08:	00000000 */ 	sll	$zero,$zero,0x0
/*    2ad0c:	45020020 */ 	bc1fl	.NB0002ad90
/*    2ad10:	8ecc0014 */ 	lw	$t4,0x14($s6)
/*    2ad14:	c6480004 */ 	lwc1	$f8,0x4($s2)
/*    2ad18:	240a0001 */ 	addiu	$t2,$zero,0x1
/*    2ad1c:	4608003c */ 	c.lt.s	$f0,$f8
/*    2ad20:	00000000 */ 	sll	$zero,$zero,0x0
/*    2ad24:	4502001a */ 	bc1fl	.NB0002ad90
/*    2ad28:	8ecc0014 */ 	lw	$t4,0x14($s6)
/*    2ad2c:	e7a000fc */ 	swc1	$f0,0xfc($sp)
/*    2ad30:	afd60000 */ 	sw	$s6,0x0($s8)
/*    2ad34:	10000015 */ 	beqz	$zero,.NB0002ad8c
/*    2ad38:	afaa00f8 */ 	sw	$t2,0xf8($sp)
.NB0002ad3c:
/*    2ad3c:	54410014 */ 	bnel	$v0,$at,.NB0002ad90
/*    2ad40:	8ecc0014 */ 	lw	$t4,0x14($s6)
/*    2ad44:	00e02025 */ 	or	$a0,$a3,$zero
/*    2ad48:	8e450000 */ 	lw	$a1,0x0($s2)
/*    2ad4c:	0c009d37 */ 	jal	cdFindGroundInTileType1
/*    2ad50:	8e460008 */ 	lw	$a2,0x8($s2)
/*    2ad54:	c7aa00fc */ 	lwc1	$f10,0xfc($sp)
/*    2ad58:	4600503e */ 	c.le.s	$f10,$f0
/*    2ad5c:	00000000 */ 	sll	$zero,$zero,0x0
/*    2ad60:	4502000b */ 	bc1fl	.NB0002ad90
/*    2ad64:	8ecc0014 */ 	lw	$t4,0x14($s6)
/*    2ad68:	c6500004 */ 	lwc1	$f16,0x4($s2)
/*    2ad6c:	240b0001 */ 	addiu	$t3,$zero,0x1
/*    2ad70:	4610003c */ 	c.lt.s	$f0,$f16
/*    2ad74:	00000000 */ 	sll	$zero,$zero,0x0
/*    2ad78:	45020005 */ 	bc1fl	.NB0002ad90
/*    2ad7c:	8ecc0014 */ 	lw	$t4,0x14($s6)
/*    2ad80:	e7a000fc */ 	swc1	$f0,0xfc($sp)
/*    2ad84:	afd60000 */ 	sw	$s6,0x0($s8)
/*    2ad88:	afab00f8 */ 	sw	$t3,0xf8($sp)
.NB0002ad8c:
/*    2ad8c:	8ecc0014 */ 	lw	$t4,0x14($s6)
.NB0002ad90:
/*    2ad90:	26d60014 */ 	addiu	$s6,$s6,0x14
/*    2ad94:	5580ffcb */ 	bnezl	$t4,.NB0002acc4
/*    2ad98:	8ed90004 */ 	lw	$t9,0x4($s6)
/*    2ad9c:	0260b025 */ 	or	$s6,$s3,$zero
/*    2ada0:	8e620000 */ 	lw	$v0,0x0($s3)
.NB0002ada4:
/*    2ada4:	50400026 */ 	beqzl	$v0,.NB0002ae40
/*    2ada8:	8faa00f8 */ 	lw	$t2,0xf8($sp)
/*    2adac:	8ecd0004 */ 	lw	$t5,0x4($s6)
.NB0002adb0:
/*    2adb0:	51a0001f */ 	beqzl	$t5,.NB0002ae30
/*    2adb4:	8ec90014 */ 	lw	$t1,0x14($s6)
/*    2adb8:	8ec70000 */ 	lw	$a3,0x0($s6)
/*    2adbc:	90ee0000 */ 	lbu	$t6,0x0($a3)
/*    2adc0:	55c0001b */ 	bnezl	$t6,.NB0002ae30
/*    2adc4:	8ec90014 */ 	lw	$t1,0x14($s6)
/*    2adc8:	94ef0002 */ 	lhu	$t7,0x2($a3)
/*    2adcc:	31f82000 */ 	andi	$t8,$t7,0x2000
/*    2add0:	53000017 */ 	beqzl	$t8,.NB0002ae30
/*    2add4:	8ec90014 */ 	lw	$t1,0x14($s6)
/*    2add8:	00e02025 */ 	or	$a0,$a3,$zero
/*    2addc:	8e450000 */ 	lw	$a1,0x0($s2)
/*    2ade0:	0c009ce8 */ 	jal	cdFindGroundInTileType0
/*    2ade4:	8e460008 */ 	lw	$a2,0x8($s2)
/*    2ade8:	c7b200fc */ 	lwc1	$f18,0xfc($sp)
/*    2adec:	4600903e */ 	c.le.s	$f18,$f0
/*    2adf0:	00000000 */ 	sll	$zero,$zero,0x0
/*    2adf4:	4502000e */ 	bc1fl	.NB0002ae30
/*    2adf8:	8ec90014 */ 	lw	$t1,0x14($s6)
/*    2adfc:	c6440004 */ 	lwc1	$f4,0x4($s2)
/*    2ae00:	4604003c */ 	c.lt.s	$f0,$f4
/*    2ae04:	00000000 */ 	sll	$zero,$zero,0x0
/*    2ae08:	45030005 */ 	bc1tl	.NB0002ae20
/*    2ae0c:	e7a000fc */ 	swc1	$f0,0xfc($sp)
/*    2ae10:	8fb900f8 */ 	lw	$t9,0xf8($sp)
/*    2ae14:	57200006 */ 	bnezl	$t9,.NB0002ae30
/*    2ae18:	8ec90014 */ 	lw	$t1,0x14($s6)
/*    2ae1c:	e7a000fc */ 	swc1	$f0,0xfc($sp)
.NB0002ae20:
/*    2ae20:	afd60000 */ 	sw	$s6,0x0($s8)
/*    2ae24:	24080001 */ 	addiu	$t0,$zero,0x1
/*    2ae28:	afa800f8 */ 	sw	$t0,0xf8($sp)
/*    2ae2c:	8ec90014 */ 	lw	$t1,0x14($s6)
.NB0002ae30:
/*    2ae30:	26d60014 */ 	addiu	$s6,$s6,0x14
/*    2ae34:	5520ffde */ 	bnezl	$t1,.NB0002adb0
/*    2ae38:	8ecd0004 */ 	lw	$t5,0x4($s6)
/*    2ae3c:	8faa00f8 */ 	lw	$t2,0xf8($sp)
.NB0002ae40:
/*    2ae40:	3c014f80 */ 	lui	$at,0x4f80
/*    2ae44:	51400004 */ 	beqzl	$t2,.NB0002ae58
/*    2ae48:	44813000 */ 	mtc1	$at,$f6
/*    2ae4c:	5220016b */ 	beqzl	$s1,.NB0002b3fc
/*    2ae50:	8fbf0074 */ 	lw	$ra,0x74($sp)
/*    2ae54:	44813000 */ 	mtc1	$at,$f6
.NB0002ae58:
/*    2ae58:	0260b025 */ 	or	$s6,$s3,$zero
/*    2ae5c:	e7a600e4 */ 	swc1	$f6,0xe4($sp)
/*    2ae60:	8e6b0000 */ 	lw	$t3,0x0($s3)
/*    2ae64:	51600165 */ 	beqzl	$t3,.NB0002b3fc
/*    2ae68:	8fbf0074 */ 	lw	$ra,0x74($sp)
/*    2ae6c:	8ecc0004 */ 	lw	$t4,0x4($s6)
.NB0002ae70:
/*    2ae70:	8fad00f8 */ 	lw	$t5,0xf8($sp)
/*    2ae74:	5580015d */ 	bnezl	$t4,.NB0002b3ec
/*    2ae78:	8ec80014 */ 	lw	$t0,0x14($s6)
/*    2ae7c:	11a00008 */ 	beqz	$t5,.NB0002aea0
/*    2ae80:	8ec70000 */ 	lw	$a3,0x0($s6)
/*    2ae84:	90ee0000 */ 	lbu	$t6,0x0($a3)
/*    2ae88:	55c00158 */ 	bnezl	$t6,.NB0002b3ec
/*    2ae8c:	8ec80014 */ 	lw	$t0,0x14($s6)
/*    2ae90:	94ef0002 */ 	lhu	$t7,0x2($a3)
/*    2ae94:	31f80100 */ 	andi	$t8,$t7,0x100
/*    2ae98:	53000154 */ 	beqzl	$t8,.NB0002b3ec
/*    2ae9c:	8ec80014 */ 	lw	$t0,0x14($s6)
.NB0002aea0:
/*    2aea0:	90e20000 */ 	lbu	$v0,0x0($a3)
/*    2aea4:	544000ba */ 	bnezl	$v0,.NB0002b190
/*    2aea8:	24010001 */ 	addiu	$at,$zero,0x1
/*    2aeac:	90f70001 */ 	lbu	$s7,0x1($a3)
/*    2aeb0:	00e0a025 */ 	or	$s4,$a3,$zero
/*    2aeb4:	00008825 */ 	or	$s1,$zero,$zero
/*    2aeb8:	1ae0014b */ 	blez	$s7,.NB0002b3e8
/*    2aebc:	00e09825 */ 	or	$s3,$a3,$zero
.NB0002aec0:
/*    2aec0:	26350001 */ 	addiu	$s5,$s1,0x1
/*    2aec4:	02b7001a */ 	div	$zero,$s5,$s7
/*    2aec8:	00004810 */ 	mfhi	$t1
/*    2aecc:	00095080 */ 	sll	$t2,$t1,0x2
/*    2aed0:	01495023 */ 	subu	$t2,$t2,$t1
/*    2aed4:	000a5040 */ 	sll	$t2,$t2,0x1
/*    2aed8:	028a8021 */ 	addu	$s0,$s4,$t2
/*    2aedc:	860b000e */ 	lh	$t3,0xe($s0)
/*    2aee0:	860c0012 */ 	lh	$t4,0x12($s0)
/*    2aee4:	8679000e */ 	lh	$t9,0xe($s3)
/*    2aee8:	86680012 */ 	lh	$t0,0x12($s3)
/*    2aeec:	448b8000 */ 	mtc1	$t3,$f16
/*    2aef0:	448c9000 */ 	mtc1	$t4,$f18
/*    2aef4:	44994000 */ 	mtc1	$t9,$f8
/*    2aef8:	44885000 */ 	mtc1	$t0,$f10
/*    2aefc:	468086a0 */ 	cvt.s.w	$f26,$f16
/*    2af00:	c6440000 */ 	lwc1	$f4,0x0($s2)
/*    2af04:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*    2af08:	46809720 */ 	cvt.s.w	$f28,$f18
/*    2af0c:	c6460008 */ 	lwc1	$f6,0x8($s2)
/*    2af10:	4406d000 */ 	mfc1	$a2,$f26
/*    2af14:	e7a60014 */ 	swc1	$f6,0x14($sp)
/*    2af18:	468045a0 */ 	cvt.s.w	$f22,$f8
/*    2af1c:	4407e000 */ 	mfc1	$a3,$f28
/*    2af20:	46805620 */ 	cvt.s.w	$f24,$f10
/*    2af24:	16e00002 */ 	bnez	$s7,.NB0002af30
/*    2af28:	00000000 */ 	sll	$zero,$zero,0x0
/*    2af2c:	0007000d */ 	break	0x7
.NB0002af30:
/*    2af30:	2401ffff */ 	addiu	$at,$zero,-1
/*    2af34:	16e10004 */ 	bne	$s7,$at,.NB0002af48
/*    2af38:	3c018000 */ 	lui	$at,0x8000
/*    2af3c:	16a10002 */ 	bne	$s5,$at,.NB0002af48
/*    2af40:	00000000 */ 	sll	$zero,$zero,0x0
/*    2af44:	0006000d */ 	break	0x6
.NB0002af48:
/*    2af48:	4600c386 */ 	mov.s	$f14,$f24
/*    2af4c:	0c009a8d */ 	jal	func00025654
/*    2af50:	4600b306 */ 	mov.s	$f12,$f22
/*    2af54:	44804000 */ 	mtc1	$zero,$f8
/*    2af58:	e7a000d4 */ 	swc1	$f0,0xd4($sp)
/*    2af5c:	46000786 */ 	mov.s	$f30,$f0
/*    2af60:	4608003c */ 	c.lt.s	$f0,$f8
/*    2af64:	c7aa00e4 */ 	lwc1	$f10,0xe4($sp)
/*    2af68:	45020003 */ 	bc1fl	.NB0002af78
/*    2af6c:	460af03c */ 	c.lt.s	$f30,$f10
/*    2af70:	46000787 */ 	neg.s	$f30,$f0
/*    2af74:	460af03c */ 	c.lt.s	$f30,$f10
.NB0002af78:
/*    2af78:	00000000 */ 	sll	$zero,$zero,0x0
/*    2af7c:	4502007f */ 	bc1fl	.NB0002b17c
/*    2af80:	02a08825 */ 	or	$s1,$s5,$zero
/*    2af84:	c6500000 */ 	lwc1	$f16,0x0($s2)
/*    2af88:	4406d000 */ 	mfc1	$a2,$f26
/*    2af8c:	4407e000 */ 	mfc1	$a3,$f28
/*    2af90:	e7b00010 */ 	swc1	$f16,0x10($sp)
/*    2af94:	c6520008 */ 	lwc1	$f18,0x8($s2)
/*    2af98:	4600b306 */ 	mov.s	$f12,$f22
/*    2af9c:	4600c386 */ 	mov.s	$f14,$f24
/*    2afa0:	0c009ad5 */ 	jal	func00025774
/*    2afa4:	e7b20014 */ 	swc1	$f18,0x14($sp)
/*    2afa8:	50400028 */ 	beqzl	$v0,.NB0002b04c
/*    2afac:	4600b306 */ 	mov.s	$f12,$f22
/*    2afb0:	4616d001 */ 	sub.s	$f0,$f26,$f22
/*    2afb4:	4618e501 */ 	sub.s	$f20,$f28,$f24
/*    2afb8:	46000102 */ 	mul.s	$f4,$f0,$f0
/*    2afbc:	e7a000b8 */ 	swc1	$f0,0xb8($sp)
/*    2afc0:	4614a182 */ 	mul.s	$f6,$f20,$f20
/*    2afc4:	0c012e84 */ 	jal	sqrtf
/*    2afc8:	46062300 */ 	add.s	$f12,$f4,$f6
/*    2afcc:	c7a800d4 */ 	lwc1	$f8,0xd4($sp)
/*    2afd0:	4600a407 */ 	neg.s	$f16,$f20
/*    2afd4:	c7a600b8 */ 	lwc1	$f6,0xb8($sp)
/*    2afd8:	46004383 */ 	div.s	$f14,$f8,$f0
/*    2afdc:	c64a0000 */ 	lwc1	$f10,0x0($s2)
/*    2afe0:	c6440008 */ 	lwc1	$f4,0x8($s2)
/*    2afe4:	02802025 */ 	or	$a0,$s4,$zero
/*    2afe8:	02203825 */ 	or	$a3,$s1,$zero
/*    2afec:	46107482 */ 	mul.s	$f18,$f14,$f16
/*    2aff0:	00000000 */ 	sll	$zero,$zero,0x0
/*    2aff4:	46067202 */ 	mul.s	$f8,$f14,$f6
/*    2aff8:	46125080 */ 	add.s	$f2,$f10,$f18
/*    2affc:	46082300 */ 	add.s	$f12,$f4,$f8
/*    2b000:	44051000 */ 	mfc1	$a1,$f2
/*    2b004:	44066000 */ 	mfc1	$a2,$f12
/*    2b008:	0c009c15 */ 	jal	cdFindGroundInTileType0AtVertex
/*    2b00c:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b010:	c6500004 */ 	lwc1	$f16,0x4($s2)
/*    2b014:	4610003c */ 	c.lt.s	$f0,$f16
/*    2b018:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b01c:	45030007 */ 	bc1tl	.NB0002b03c
/*    2b020:	e7a000fc */ 	swc1	$f0,0xfc($sp)
/*    2b024:	8ecd0000 */ 	lw	$t5,0x0($s6)
/*    2b028:	95ae0002 */ 	lhu	$t6,0x2($t5)
/*    2b02c:	31cf2000 */ 	andi	$t7,$t6,0x2000
/*    2b030:	51e00052 */ 	beqzl	$t7,.NB0002b17c
/*    2b034:	02a08825 */ 	or	$s1,$s5,$zero
/*    2b038:	e7a000fc */ 	swc1	$f0,0xfc($sp)
.NB0002b03c:
/*    2b03c:	afd60000 */ 	sw	$s6,0x0($s8)
/*    2b040:	1000004d */ 	beqz	$zero,.NB0002b178
/*    2b044:	e7be00e4 */ 	swc1	$f30,0xe4($sp)
/*    2b048:	4600b306 */ 	mov.s	$f12,$f22
.NB0002b04c:
/*    2b04c:	4600c386 */ 	mov.s	$f14,$f24
/*    2b050:	8e460000 */ 	lw	$a2,0x0($s2)
/*    2b054:	0c009ac1 */ 	jal	func00025724
/*    2b058:	8e470008 */ 	lw	$a3,0x8($s2)
/*    2b05c:	46000506 */ 	mov.s	$f20,$f0
/*    2b060:	4600d306 */ 	mov.s	$f12,$f26
/*    2b064:	4600e386 */ 	mov.s	$f14,$f28
/*    2b068:	8e460000 */ 	lw	$a2,0x0($s2)
/*    2b06c:	0c009ac1 */ 	jal	func00025724
/*    2b070:	8e470008 */ 	lw	$a3,0x8($s2)
/*    2b074:	4600a03c */ 	c.lt.s	$f20,$f0
/*    2b078:	46000586 */ 	mov.s	$f22,$f0
/*    2b07c:	45020021 */ 	bc1fl	.NB0002b104
/*    2b080:	c7a800e4 */ 	lwc1	$f8,0xe4($sp)
/*    2b084:	c7aa00e4 */ 	lwc1	$f10,0xe4($sp)
/*    2b088:	460aa03c */ 	c.lt.s	$f20,$f10
/*    2b08c:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b090:	4502003a */ 	bc1fl	.NB0002b17c
/*    2b094:	02a08825 */ 	or	$s1,$s5,$zero
/*    2b098:	8678000e */ 	lh	$t8,0xe($s3)
/*    2b09c:	86790012 */ 	lh	$t9,0x12($s3)
/*    2b0a0:	02802025 */ 	or	$a0,$s4,$zero
/*    2b0a4:	44989000 */ 	mtc1	$t8,$f18
/*    2b0a8:	44993000 */ 	mtc1	$t9,$f6
/*    2b0ac:	02203825 */ 	or	$a3,$s1,$zero
/*    2b0b0:	468090a0 */ 	cvt.s.w	$f2,$f18
/*    2b0b4:	46803320 */ 	cvt.s.w	$f12,$f6
/*    2b0b8:	44051000 */ 	mfc1	$a1,$f2
/*    2b0bc:	44066000 */ 	mfc1	$a2,$f12
/*    2b0c0:	0c009c15 */ 	jal	cdFindGroundInTileType0AtVertex
/*    2b0c4:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b0c8:	c6440004 */ 	lwc1	$f4,0x4($s2)
/*    2b0cc:	4604003c */ 	c.lt.s	$f0,$f4
/*    2b0d0:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b0d4:	45030007 */ 	bc1tl	.NB0002b0f4
/*    2b0d8:	e7a000fc */ 	swc1	$f0,0xfc($sp)
/*    2b0dc:	8ec80000 */ 	lw	$t0,0x0($s6)
/*    2b0e0:	95090002 */ 	lhu	$t1,0x2($t0)
/*    2b0e4:	312a2000 */ 	andi	$t2,$t1,0x2000
/*    2b0e8:	51400024 */ 	beqzl	$t2,.NB0002b17c
/*    2b0ec:	02a08825 */ 	or	$s1,$s5,$zero
/*    2b0f0:	e7a000fc */ 	swc1	$f0,0xfc($sp)
.NB0002b0f4:
/*    2b0f4:	afd60000 */ 	sw	$s6,0x0($s8)
/*    2b0f8:	1000001f */ 	beqz	$zero,.NB0002b178
/*    2b0fc:	e7b400e4 */ 	swc1	$f20,0xe4($sp)
/*    2b100:	c7a800e4 */ 	lwc1	$f8,0xe4($sp)
.NB0002b104:
/*    2b104:	4608003c */ 	c.lt.s	$f0,$f8
/*    2b108:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b10c:	4502001b */ 	bc1fl	.NB0002b17c
/*    2b110:	02a08825 */ 	or	$s1,$s5,$zero
/*    2b114:	860b000e */ 	lh	$t3,0xe($s0)
/*    2b118:	860c0012 */ 	lh	$t4,0x12($s0)
/*    2b11c:	02802025 */ 	or	$a0,$s4,$zero
/*    2b120:	448b8000 */ 	mtc1	$t3,$f16
/*    2b124:	448c5000 */ 	mtc1	$t4,$f10
/*    2b128:	02203825 */ 	or	$a3,$s1,$zero
/*    2b12c:	468080a0 */ 	cvt.s.w	$f2,$f16
/*    2b130:	46805320 */ 	cvt.s.w	$f12,$f10
/*    2b134:	44051000 */ 	mfc1	$a1,$f2
/*    2b138:	44066000 */ 	mfc1	$a2,$f12
/*    2b13c:	0c009c15 */ 	jal	cdFindGroundInTileType0AtVertex
/*    2b140:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b144:	c6520004 */ 	lwc1	$f18,0x4($s2)
/*    2b148:	4612003c */ 	c.lt.s	$f0,$f18
/*    2b14c:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b150:	45030007 */ 	bc1tl	.NB0002b170
/*    2b154:	e7a000fc */ 	swc1	$f0,0xfc($sp)
/*    2b158:	8ecd0000 */ 	lw	$t5,0x0($s6)
/*    2b15c:	95ae0002 */ 	lhu	$t6,0x2($t5)
/*    2b160:	31cf2000 */ 	andi	$t7,$t6,0x2000
/*    2b164:	51e00005 */ 	beqzl	$t7,.NB0002b17c
/*    2b168:	02a08825 */ 	or	$s1,$s5,$zero
/*    2b16c:	e7a000fc */ 	swc1	$f0,0xfc($sp)
.NB0002b170:
/*    2b170:	afd60000 */ 	sw	$s6,0x0($s8)
/*    2b174:	e7b600e4 */ 	swc1	$f22,0xe4($sp)
.NB0002b178:
/*    2b178:	02a08825 */ 	or	$s1,$s5,$zero
.NB0002b17c:
/*    2b17c:	16b7ff50 */ 	bne	$s5,$s7,.NB0002aec0
/*    2b180:	26730006 */ 	addiu	$s3,$s3,0x6
/*    2b184:	10000099 */ 	beqz	$zero,.NB0002b3ec
/*    2b188:	8ec80014 */ 	lw	$t0,0x14($s6)
/*    2b18c:	24010001 */ 	addiu	$at,$zero,0x1
.NB0002b190:
/*    2b190:	54410096 */ 	bnel	$v0,$at,.NB0002b3ec
/*    2b194:	8ec80014 */ 	lw	$t0,0x14($s6)
/*    2b198:	90f50001 */ 	lbu	$s5,0x1($a3)
/*    2b19c:	00e09825 */ 	or	$s3,$a3,$zero
/*    2b1a0:	00001025 */ 	or	$v0,$zero,$zero
/*    2b1a4:	1aa00090 */ 	blez	$s5,.NB0002b3e8
/*    2b1a8:	00e08825 */ 	or	$s1,$a3,$zero
.NB0002b1ac:
/*    2b1ac:	24540001 */ 	addiu	$s4,$v0,0x1
/*    2b1b0:	0295001a */ 	div	$zero,$s4,$s5
/*    2b1b4:	0000c010 */ 	mfhi	$t8
/*    2b1b8:	0018c880 */ 	sll	$t9,$t8,0x2
/*    2b1bc:	0338c823 */ 	subu	$t9,$t9,$t8
/*    2b1c0:	0019c880 */ 	sll	$t9,$t9,0x2
/*    2b1c4:	02798021 */ 	addu	$s0,$s3,$t9
/*    2b1c8:	c6460000 */ 	lwc1	$f6,0x0($s2)
/*    2b1cc:	c61a0010 */ 	lwc1	$f26,0x10($s0)
/*    2b1d0:	c61c0018 */ 	lwc1	$f28,0x18($s0)
/*    2b1d4:	c6360010 */ 	lwc1	$f22,0x10($s1)
/*    2b1d8:	c6380018 */ 	lwc1	$f24,0x18($s1)
/*    2b1dc:	e7a60010 */ 	swc1	$f6,0x10($sp)
/*    2b1e0:	c6440008 */ 	lwc1	$f4,0x8($s2)
/*    2b1e4:	16a00002 */ 	bnez	$s5,.NB0002b1f0
/*    2b1e8:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b1ec:	0007000d */ 	break	0x7
.NB0002b1f0:
/*    2b1f0:	2401ffff */ 	addiu	$at,$zero,-1
/*    2b1f4:	16a10004 */ 	bne	$s5,$at,.NB0002b208
/*    2b1f8:	3c018000 */ 	lui	$at,0x8000
/*    2b1fc:	16810002 */ 	bne	$s4,$at,.NB0002b208
/*    2b200:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b204:	0006000d */ 	break	0x6
.NB0002b208:
/*    2b208:	4406d000 */ 	mfc1	$a2,$f26
/*    2b20c:	4407e000 */ 	mfc1	$a3,$f28
/*    2b210:	4600b306 */ 	mov.s	$f12,$f22
/*    2b214:	4600c386 */ 	mov.s	$f14,$f24
/*    2b218:	0c009a8d */ 	jal	func00025654
/*    2b21c:	e7a40014 */ 	swc1	$f4,0x14($sp)
/*    2b220:	44804000 */ 	mtc1	$zero,$f8
/*    2b224:	e7a00098 */ 	swc1	$f0,0x98($sp)
/*    2b228:	46000786 */ 	mov.s	$f30,$f0
/*    2b22c:	4608003c */ 	c.lt.s	$f0,$f8
/*    2b230:	c7b000e4 */ 	lwc1	$f16,0xe4($sp)
/*    2b234:	45020003 */ 	bc1fl	.NB0002b244
/*    2b238:	4610f03c */ 	c.lt.s	$f30,$f16
/*    2b23c:	46000787 */ 	neg.s	$f30,$f0
/*    2b240:	4610f03c */ 	c.lt.s	$f30,$f16
.NB0002b244:
/*    2b244:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b248:	45020065 */ 	bc1fl	.NB0002b3e0
/*    2b24c:	02801025 */ 	or	$v0,$s4,$zero
/*    2b250:	c64a0000 */ 	lwc1	$f10,0x0($s2)
/*    2b254:	4406d000 */ 	mfc1	$a2,$f26
/*    2b258:	4407e000 */ 	mfc1	$a3,$f28
/*    2b25c:	e7aa0010 */ 	swc1	$f10,0x10($sp)
/*    2b260:	c6520008 */ 	lwc1	$f18,0x8($s2)
/*    2b264:	4600b306 */ 	mov.s	$f12,$f22
/*    2b268:	4600c386 */ 	mov.s	$f14,$f24
/*    2b26c:	0c009ad5 */ 	jal	func00025774
/*    2b270:	e7b20014 */ 	swc1	$f18,0x14($sp)
/*    2b274:	50400022 */ 	beqzl	$v0,.NB0002b300
/*    2b278:	4600b306 */ 	mov.s	$f12,$f22
/*    2b27c:	4616d001 */ 	sub.s	$f0,$f26,$f22
/*    2b280:	4618e501 */ 	sub.s	$f20,$f28,$f24
/*    2b284:	46000182 */ 	mul.s	$f6,$f0,$f0
/*    2b288:	e7a0007c */ 	swc1	$f0,0x7c($sp)
/*    2b28c:	4614a102 */ 	mul.s	$f4,$f20,$f20
/*    2b290:	0c012e84 */ 	jal	sqrtf
/*    2b294:	46043300 */ 	add.s	$f12,$f6,$f4
/*    2b298:	c7a80098 */ 	lwc1	$f8,0x98($sp)
/*    2b29c:	4600a287 */ 	neg.s	$f10,$f20
/*    2b2a0:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*    2b2a4:	46004383 */ 	div.s	$f14,$f8,$f0
/*    2b2a8:	c6500000 */ 	lwc1	$f16,0x0($s2)
/*    2b2ac:	c6460008 */ 	lwc1	$f6,0x8($s2)
/*    2b2b0:	02602025 */ 	or	$a0,$s3,$zero
/*    2b2b4:	460a7482 */ 	mul.s	$f18,$f14,$f10
/*    2b2b8:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b2bc:	46047202 */ 	mul.s	$f8,$f14,$f4
/*    2b2c0:	46128080 */ 	add.s	$f2,$f16,$f18
/*    2b2c4:	46083300 */ 	add.s	$f12,$f6,$f8
/*    2b2c8:	44051000 */ 	mfc1	$a1,$f2
/*    2b2cc:	44066000 */ 	mfc1	$a2,$f12
/*    2b2d0:	0c009d37 */ 	jal	cdFindGroundInTileType1
/*    2b2d4:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b2d8:	c64a0004 */ 	lwc1	$f10,0x4($s2)
/*    2b2dc:	460a003c */ 	c.lt.s	$f0,$f10
/*    2b2e0:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b2e4:	4502003e */ 	bc1fl	.NB0002b3e0
/*    2b2e8:	02801025 */ 	or	$v0,$s4,$zero
/*    2b2ec:	e7a000fc */ 	swc1	$f0,0xfc($sp)
/*    2b2f0:	afd60000 */ 	sw	$s6,0x0($s8)
/*    2b2f4:	10000039 */ 	beqz	$zero,.NB0002b3dc
/*    2b2f8:	e7be00e4 */ 	swc1	$f30,0xe4($sp)
/*    2b2fc:	4600b306 */ 	mov.s	$f12,$f22
.NB0002b300:
/*    2b300:	4600c386 */ 	mov.s	$f14,$f24
/*    2b304:	8e460000 */ 	lw	$a2,0x0($s2)
/*    2b308:	0c009ac1 */ 	jal	func00025724
/*    2b30c:	8e470008 */ 	lw	$a3,0x8($s2)
/*    2b310:	46000506 */ 	mov.s	$f20,$f0
/*    2b314:	4600d306 */ 	mov.s	$f12,$f26
/*    2b318:	4600e386 */ 	mov.s	$f14,$f28
/*    2b31c:	8e460000 */ 	lw	$a2,0x0($s2)
/*    2b320:	0c009ac1 */ 	jal	func00025724
/*    2b324:	8e470008 */ 	lw	$a3,0x8($s2)
/*    2b328:	4600a03c */ 	c.lt.s	$f20,$f0
/*    2b32c:	46000586 */ 	mov.s	$f22,$f0
/*    2b330:	45020017 */ 	bc1fl	.NB0002b390
/*    2b334:	c7a400e4 */ 	lwc1	$f4,0xe4($sp)
/*    2b338:	c7b000e4 */ 	lwc1	$f16,0xe4($sp)
/*    2b33c:	4610a03c */ 	c.lt.s	$f20,$f16
/*    2b340:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b344:	45020026 */ 	bc1fl	.NB0002b3e0
/*    2b348:	02801025 */ 	or	$v0,$s4,$zero
/*    2b34c:	c6220010 */ 	lwc1	$f2,0x10($s1)
/*    2b350:	c62c0018 */ 	lwc1	$f12,0x18($s1)
/*    2b354:	02602025 */ 	or	$a0,$s3,$zero
/*    2b358:	44051000 */ 	mfc1	$a1,$f2
/*    2b35c:	44066000 */ 	mfc1	$a2,$f12
/*    2b360:	0c009d37 */ 	jal	cdFindGroundInTileType1
/*    2b364:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b368:	c6520004 */ 	lwc1	$f18,0x4($s2)
/*    2b36c:	4612003c */ 	c.lt.s	$f0,$f18
/*    2b370:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b374:	4502001a */ 	bc1fl	.NB0002b3e0
/*    2b378:	02801025 */ 	or	$v0,$s4,$zero
/*    2b37c:	e7a000fc */ 	swc1	$f0,0xfc($sp)
/*    2b380:	afd60000 */ 	sw	$s6,0x0($s8)
/*    2b384:	10000015 */ 	beqz	$zero,.NB0002b3dc
/*    2b388:	e7b400e4 */ 	swc1	$f20,0xe4($sp)
/*    2b38c:	c7a400e4 */ 	lwc1	$f4,0xe4($sp)
.NB0002b390:
/*    2b390:	4604003c */ 	c.lt.s	$f0,$f4
/*    2b394:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b398:	45020011 */ 	bc1fl	.NB0002b3e0
/*    2b39c:	02801025 */ 	or	$v0,$s4,$zero
/*    2b3a0:	c6020010 */ 	lwc1	$f2,0x10($s0)
/*    2b3a4:	c60c0018 */ 	lwc1	$f12,0x18($s0)
/*    2b3a8:	02602025 */ 	or	$a0,$s3,$zero
/*    2b3ac:	44051000 */ 	mfc1	$a1,$f2
/*    2b3b0:	44066000 */ 	mfc1	$a2,$f12
/*    2b3b4:	0c009d37 */ 	jal	cdFindGroundInTileType1
/*    2b3b8:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b3bc:	c6460004 */ 	lwc1	$f6,0x4($s2)
/*    2b3c0:	4606003c */ 	c.lt.s	$f0,$f6
/*    2b3c4:	00000000 */ 	sll	$zero,$zero,0x0
/*    2b3c8:	45020005 */ 	bc1fl	.NB0002b3e0
/*    2b3cc:	02801025 */ 	or	$v0,$s4,$zero
/*    2b3d0:	e7a000fc */ 	swc1	$f0,0xfc($sp)
/*    2b3d4:	afd60000 */ 	sw	$s6,0x0($s8)
/*    2b3d8:	e7b600e4 */ 	swc1	$f22,0xe4($sp)
.NB0002b3dc:
/*    2b3dc:	02801025 */ 	or	$v0,$s4,$zero
.NB0002b3e0:
/*    2b3e0:	1695ff72 */ 	bne	$s4,$s5,.NB0002b1ac
/*    2b3e4:	2631000c */ 	addiu	$s1,$s1,0xc
.NB0002b3e8:
/*    2b3e8:	8ec80014 */ 	lw	$t0,0x14($s6)
.NB0002b3ec:
/*    2b3ec:	26d60014 */ 	addiu	$s6,$s6,0x14
/*    2b3f0:	5500fe9f */ 	bnezl	$t0,.NB0002ae70
/*    2b3f4:	8ecc0004 */ 	lw	$t4,0x4($s6)
/*    2b3f8:	8fbf0074 */ 	lw	$ra,0x74($sp)
.NB0002b3fc:
/*    2b3fc:	c7a000fc */ 	lwc1	$f0,0xfc($sp)
/*    2b400:	d7b40020 */ 	ldc1	$f20,0x20($sp)
/*    2b404:	d7b60028 */ 	ldc1	$f22,0x28($sp)
/*    2b408:	d7b80030 */ 	ldc1	$f24,0x30($sp)
/*    2b40c:	d7ba0038 */ 	ldc1	$f26,0x38($sp)
/*    2b410:	d7bc0040 */ 	ldc1	$f28,0x40($sp)
/*    2b414:	d7be0048 */ 	ldc1	$f30,0x48($sp)
/*    2b418:	8fb00050 */ 	lw	$s0,0x50($sp)
/*    2b41c:	8fb10054 */ 	lw	$s1,0x54($sp)
/*    2b420:	8fb20058 */ 	lw	$s2,0x58($sp)
/*    2b424:	8fb3005c */ 	lw	$s3,0x5c($sp)
/*    2b428:	8fb40060 */ 	lw	$s4,0x60($sp)
/*    2b42c:	8fb50064 */ 	lw	$s5,0x64($sp)
/*    2b430:	8fb60068 */ 	lw	$s6,0x68($sp)
/*    2b434:	8fb7006c */ 	lw	$s7,0x6c($sp)
/*    2b438:	8fbe0070 */ 	lw	$s8,0x70($sp)
/*    2b43c:	03e00008 */ 	jr	$ra
/*    2b440:	27bd0108 */ 	addiu	$sp,$sp,0x108
);
#endif

bool func00029ffc(struct coord *pos, f32 width, f32 foreheadheight, f32 inversefeettoeyesheight, s16 *rooms, u16 arg5, struct coord *laddernormal)
{
	u32 stack[5];
	struct collisionthing thing;

	func00027d1c(pos, width, rooms, CDTYPE_BG,
			arg5, 1, foreheadheight, inversefeettoeyesheight,
			&thing, 1);

	if (thing.tile) {
		struct tiletype0 *tile = (struct tiletype0 *) thing.tile;
		struct coord dist;

		func00025928(thing.tile, laddernormal);

		dist.x = pos->x - tile->vertices[0][0];
		dist.y = pos->y - tile->vertices[0][1];
		dist.z = pos->z - tile->vertices[0][2];

		if (dist.f[0] * laddernormal->f[0] + dist.f[1] * laddernormal->f[1] + dist.f[2] * laddernormal->f[2] < 0) {
			laddernormal->x = -laddernormal->x;
			laddernormal->y = -laddernormal->y;
			laddernormal->z = -laddernormal->z;
		}

		return true;
	}

	return false;
}

bool func0002a13c(struct coord *pos, f32 width, f32 arg2, f32 arg3, s16 *rooms, u16 arg5)
{
	u32 stack[5];
	struct collisionthing thing;

	func00027d1c(pos, width, rooms, CDTYPE_BG, arg5, 1, arg2, arg3, &thing, 1);

	if (thing.tile) {
		return true;
	}

	return false;
}

f32 cdFindGroundY(struct coord *pos, f32 width, s16 *rooms, u16 *floorcol,
		u8 *floortype, u16 *floorflags, s16 *floorroom, s32 *inlift, struct prop **lift)
{
	struct collisionthing cdthings[21];
	struct tilething *sp72 = NULL;
	f32 ground;
	struct tile *tile = NULL;

	func00027d1c(pos, width, rooms, CDTYPE_ALL, 3, 0, 0, 0, cdthings, 20);
	ground = func000296a0(cdthings, pos, &sp72, width);

	if (sp72) {
		tile = sp72->tile;
	}

	if (floorcol) {
		tileGetFloorCol(tile, floorcol);
	}

	if (floortype) {
		tileGetFloorType(tile, floortype);
	}

	if (floorflags && tile) {
		*floorflags = tile->flags;
	}

	if (floorroom) {
		if (sp72) {
			*floorroom = sp72->floorroom;
		} else {
			*floorroom = -1;
		}
	}

	if (inlift) {
		if (tile && tile->type == TILETYPE_01 && (tile->flags & TILEFLAG_0020)) {
			*inlift = true;
			*lift = sp72->lift;

			if (*lift && (*lift)->obj->modelnum == MODEL_ESCA_STEP && floortype) {
				*floortype = FLOORTYPE_METAL;
			}
		} else {
			*inlift = false;
			*lift = NULL;
		}
	}

	return ground;
}

/**
 * This function must come immediately after cdFindGroundY.
 *
 * A piracy check looks for this function, then backtracks two instructions to
 * nop the jr ra at the end of cdFindGroundY, causing it to flow into this
 * function and return 0.
 */
f32 func0002a324(void)
{
	return 0;
}

f32 cdFindGroundYSimple(struct coord *pos, f32 width, s16 *rooms, u16 *floorcol, u8 *floortype)
{
	return cdFindGroundY(pos, width, rooms, floorcol, floortype, NULL, NULL, NULL, NULL);
}

f32 func0002a36c(struct coord *coord, s16 *rooms, u16 *floorcol, u8 *floortype)
{
	struct tile *tile;
	s16 sp30[2];
	f32 sp2c;
	f32 result = -4294967296;

	func00026e7c(coord, rooms, 3, &tile, &sp30[1], &sp2c, NULL, 0);

	if (tile) {
		result = sp2c;
	}

	if (floorcol) {
		tileGetFloorCol(tile, floorcol);
	}

	if (floortype) {
		tileGetFloorType(tile, floortype);
	}

	return result;
}

s32 func0002a400(struct coord *pos, s16 *rooms)
{
	struct tile *tile;
	s16 sp32;
	f32 sp2c;

	func00026e7c(pos, rooms, 3, &tile, &sp32, &sp2c, 0, 0);

	return sp32;
}

#if VERSION >= VERSION_NTSC_1_0
s16 func0002a440(struct coord *pos, s16 *rooms, f32 *arg2, u16 *floorcolptr, u16 *flagsptr)
#else
s16 func0002a440(struct coord *pos, s16 *rooms, f32 *arg2, u16 *floorcolptr)
#endif
{
	struct tile *tile;
	s16 sp32;
	f32 sp2c;

	func00026e7c(pos, rooms, 3, &tile, &sp32, &sp2c, NULL, 0);

	if (tile != NULL) {
		*arg2 = sp2c;
	}

	if (floorcolptr != NULL) {
		tileGetFloorCol(tile, floorcolptr);
	}

#if VERSION >= VERSION_NTSC_1_0
	if (flagsptr != NULL && tile != NULL) {
		*flagsptr = tile->flags;
	}
#endif

	return sp32;
}

s16 func0002a4d0(struct coord *pos, s16 *rooms, f32 *arg2, u16 *floorcolptr, u16 *flagsptr)
{
	struct tile *tile;
	s16 sp32;
	f32 sp2c;

	func00026e7c(pos, rooms, 3, &tile, &sp32, &sp2c, NULL, 1);

	if (tile != NULL) {
		*arg2 = sp2c;
	}

	if (floorcolptr != NULL) {
		tileGetFloorCol(tile, floorcolptr);
	}

#if VERSION >= VERSION_NTSC_1_0
	if (flagsptr != NULL && tile != NULL) {
		*flagsptr = tile->flags;
	}
#endif

	return sp32;
}

s32 func0002a564(struct coord *pos, s16 *rooms, f32 *arg2, u16 *floorcol, struct coord *arg4, struct prop **propptr)
{
	struct tile *tile;
	s16 sp32;
	f32 sp2c;

	func00026e7c(pos, rooms, 3, &tile, &sp32, &sp2c, propptr, 0);

	if (tile) {
		*arg2 = sp2c;
		func00025928(tile, arg4);
	}

	if (floorcol) {
		tileGetFloorCol(tile, floorcol);
	}

	return sp32;
}

s32 func0002a5e4(struct coord *pos, s16 *rooms, f32 *arg2, u16 *floorcol, u16 *flagsptr, struct coord *arg5)
{
	struct tile *tile;
	s16 sp32;
	f32 sp2c;

	func00026e7c(pos, rooms, 3, &tile, &sp32, &sp2c, NULL, 1);

	if (tile) {
		*arg2 = sp2c;
		func00025928(tile, arg5);
	}

	if (floorcol) {
		tileGetFloorCol(tile, floorcol);
	}

	if (flagsptr != NULL && tile != NULL) {
		*flagsptr = tile->flags;
	}

	return sp32;
}

/**
 * Tests if a cylinder volume fits in the given position.
 */
s32 cdTestVolume(struct coord *pos, f32 width, s16 *rooms, s32 types, s32 arg4, f32 ymax, f32 ymin)
{
	struct collisionthing cdthings[2];
	bool result = true;

	func00027d1c(pos, width, rooms, types, 4, arg4, ymax, ymin, cdthings, 1);

	if (cdthings[0].tile) {
		result = false;
		func00025168(cdthings[0].prop);
	}

	return result;
}

GLOBAL_ASM(
glabel func0002a6fc
/*    2a6fc:	27bdff58 */ 	addiu	$sp,$sp,-168
/*    2a700:	44866000 */ 	mtc1	$a2,$f12
/*    2a704:	afb00030 */ 	sw	$s0,0x30($sp)
/*    2a708:	00808025 */ 	or	$s0,$a0,$zero
/*    2a70c:	8fb800bc */ 	lw	$t8,0xbc($sp)
/*    2a710:	c7a400c0 */ 	lwc1	$f4,0xc0($sp)
/*    2a714:	c7a600c4 */ 	lwc1	$f6,0xc4($sp)
/*    2a718:	afa500ac */ 	sw	$a1,0xac($sp)
/*    2a71c:	00a02025 */ 	or	$a0,$a1,$zero
/*    2a720:	afbf0034 */ 	sw	$ra,0x34($sp)
/*    2a724:	afa700b4 */ 	sw	$a3,0xb4($sp)
/*    2a728:	240e0001 */ 	addiu	$t6,$zero,0x1
/*    2a72c:	00e03025 */ 	or	$a2,$a3,$zero
/*    2a730:	27b90080 */ 	addiu	$t9,$sp,0x80
/*    2a734:	240f0004 */ 	addiu	$t7,$zero,0x4
/*    2a738:	24080001 */ 	addiu	$t0,$zero,0x1
/*    2a73c:	44056000 */ 	mfc1	$a1,$f12
/*    2a740:	afae007c */ 	sw	$t6,0x7c($sp)
/*    2a744:	afa80024 */ 	sw	$t0,0x24($sp)
/*    2a748:	afaf0010 */ 	sw	$t7,0x10($sp)
/*    2a74c:	afb90020 */ 	sw	$t9,0x20($sp)
/*    2a750:	8fa700b8 */ 	lw	$a3,0xb8($sp)
/*    2a754:	afb80014 */ 	sw	$t8,0x14($sp)
/*    2a758:	e7a40018 */ 	swc1	$f4,0x18($sp)
/*    2a75c:	0c009f47 */ 	jal	func00027d1c
/*    2a760:	e7a6001c */ 	swc1	$f6,0x1c($sp)
/*    2a764:	8fa90080 */ 	lw	$t1,0x80($sp)
/*    2a768:	5120009d */ 	beqzl	$t1,.L0002a9e0
/*    2a76c:	8fbf0034 */ 	lw	$ra,0x34($sp)
/*    2a770:	afa0007c */ 	sw	$zero,0x7c($sp)
/*    2a774:	91220000 */ 	lbu	$v0,0x0($t1)
/*    2a778:	54400037 */ 	bnezl	$v0,.L0002a858
/*    2a77c:	24010001 */ 	addiu	$at,$zero,0x1
/*    2a780:	8fa50088 */ 	lw	$a1,0x88($sp)
/*    2a784:	912b0001 */ 	lbu	$t3,0x1($t1)
/*    2a788:	24070006 */ 	addiu	$a3,$zero,0x6
/*    2a78c:	24aa0001 */ 	addiu	$t2,$a1,0x1
/*    2a790:	014b001a */ 	div	$zero,$t2,$t3
/*    2a794:	00003010 */ 	mfhi	$a2
/*    2a798:	01201025 */ 	or	$v0,$t1,$zero
/*    2a79c:	15600002 */ 	bnez	$t3,.L0002a7a8
/*    2a7a0:	00000000 */ 	nop
/*    2a7a4:	0007000d */ 	break	0x7
.L0002a7a8:
/*    2a7a8:	2401ffff */ 	addiu	$at,$zero,-1
/*    2a7ac:	15610004 */ 	bne	$t3,$at,.L0002a7c0
/*    2a7b0:	3c018000 */ 	lui	$at,0x8000
/*    2a7b4:	15410002 */ 	bne	$t2,$at,.L0002a7c0
/*    2a7b8:	00000000 */ 	nop
/*    2a7bc:	0006000d */ 	break	0x6
.L0002a7c0:
/*    2a7c0:	00a70019 */ 	multu	$a1,$a3
/*    2a7c4:	00006012 */ 	mflo	$t4
/*    2a7c8:	004c1821 */ 	addu	$v1,$v0,$t4
/*    2a7cc:	846d000e */ 	lh	$t5,0xe($v1)
/*    2a7d0:	00c70019 */ 	multu	$a2,$a3
/*    2a7d4:	448d4000 */ 	mtc1	$t5,$f8
/*    2a7d8:	00000000 */ 	nop
/*    2a7dc:	468042a0 */ 	cvt.s.w	$f10,$f8
/*    2a7e0:	0000c012 */ 	mflo	$t8
/*    2a7e4:	e7aa0070 */ 	swc1	$f10,0x70($sp)
/*    2a7e8:	846e0010 */ 	lh	$t6,0x10($v1)
/*    2a7ec:	00582021 */ 	addu	$a0,$v0,$t8
/*    2a7f0:	448e8000 */ 	mtc1	$t6,$f16
/*    2a7f4:	00000000 */ 	nop
/*    2a7f8:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    2a7fc:	e7b20074 */ 	swc1	$f18,0x74($sp)
/*    2a800:	846f0012 */ 	lh	$t7,0x12($v1)
/*    2a804:	448f2000 */ 	mtc1	$t7,$f4
/*    2a808:	00000000 */ 	nop
/*    2a80c:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    2a810:	e7a60078 */ 	swc1	$f6,0x78($sp)
/*    2a814:	8499000e */ 	lh	$t9,0xe($a0)
/*    2a818:	44994000 */ 	mtc1	$t9,$f8
/*    2a81c:	00000000 */ 	nop
/*    2a820:	468042a0 */ 	cvt.s.w	$f10,$f8
/*    2a824:	e7aa0064 */ 	swc1	$f10,0x64($sp)
/*    2a828:	84880010 */ 	lh	$t0,0x10($a0)
/*    2a82c:	44888000 */ 	mtc1	$t0,$f16
/*    2a830:	00000000 */ 	nop
/*    2a834:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    2a838:	e7b20068 */ 	swc1	$f18,0x68($sp)
/*    2a83c:	84890012 */ 	lh	$t1,0x12($a0)
/*    2a840:	44892000 */ 	mtc1	$t1,$f4
/*    2a844:	00000000 */ 	nop
/*    2a848:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    2a84c:	1000005f */ 	b	.L0002a9cc
/*    2a850:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*    2a854:	24010001 */ 	addiu	$at,$zero,0x1
.L0002a858:
/*    2a858:	54410025 */ 	bnel	$v0,$at,.L0002a8f0
/*    2a85c:	24010002 */ 	addiu	$at,$zero,0x2
/*    2a860:	8fa20080 */ 	lw	$v0,0x80($sp)
/*    2a864:	8fa50088 */ 	lw	$a1,0x88($sp)
/*    2a868:	2407000c */ 	addiu	$a3,$zero,0xc
/*    2a86c:	904b0001 */ 	lbu	$t3,0x1($v0)
/*    2a870:	24aa0001 */ 	addiu	$t2,$a1,0x1
/*    2a874:	014b001a */ 	div	$zero,$t2,$t3
/*    2a878:	00003010 */ 	mfhi	$a2
/*    2a87c:	15600002 */ 	bnez	$t3,.L0002a888
/*    2a880:	00000000 */ 	nop
/*    2a884:	0007000d */ 	break	0x7
.L0002a888:
/*    2a888:	2401ffff */ 	addiu	$at,$zero,-1
/*    2a88c:	15610004 */ 	bne	$t3,$at,.L0002a8a0
/*    2a890:	3c018000 */ 	lui	$at,0x8000
/*    2a894:	15410002 */ 	bne	$t2,$at,.L0002a8a0
/*    2a898:	00000000 */ 	nop
/*    2a89c:	0006000d */ 	break	0x6
.L0002a8a0:
/*    2a8a0:	00a70019 */ 	multu	$a1,$a3
/*    2a8a4:	00006012 */ 	mflo	$t4
/*    2a8a8:	004c1821 */ 	addu	$v1,$v0,$t4
/*    2a8ac:	c4680010 */ 	lwc1	$f8,0x10($v1)
/*    2a8b0:	00c70019 */ 	multu	$a2,$a3
/*    2a8b4:	e7a80070 */ 	swc1	$f8,0x70($sp)
/*    2a8b8:	c46a0014 */ 	lwc1	$f10,0x14($v1)
/*    2a8bc:	e7aa0074 */ 	swc1	$f10,0x74($sp)
/*    2a8c0:	c4700018 */ 	lwc1	$f16,0x18($v1)
/*    2a8c4:	00006812 */ 	mflo	$t5
/*    2a8c8:	004d2021 */ 	addu	$a0,$v0,$t5
/*    2a8cc:	e7b00078 */ 	swc1	$f16,0x78($sp)
/*    2a8d0:	c4920010 */ 	lwc1	$f18,0x10($a0)
/*    2a8d4:	e7b20064 */ 	swc1	$f18,0x64($sp)
/*    2a8d8:	c4840014 */ 	lwc1	$f4,0x14($a0)
/*    2a8dc:	e7a40068 */ 	swc1	$f4,0x68($sp)
/*    2a8e0:	c4860018 */ 	lwc1	$f6,0x18($a0)
/*    2a8e4:	10000039 */ 	b	.L0002a9cc
/*    2a8e8:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*    2a8ec:	24010002 */ 	addiu	$at,$zero,0x2
.L0002a8f0:
/*    2a8f0:	14410020 */ 	bne	$v0,$at,.L0002a974
/*    2a8f4:	8fa30088 */ 	lw	$v1,0x88($sp)
/*    2a8f8:	8fa20080 */ 	lw	$v0,0x80($sp)
/*    2a8fc:	246e0001 */ 	addiu	$t6,$v1,0x1
/*    2a900:	0003c0c0 */ 	sll	$t8,$v1,0x3
/*    2a904:	904f0001 */ 	lbu	$t7,0x1($v0)
/*    2a908:	00582021 */ 	addu	$a0,$v0,$t8
/*    2a90c:	c488000c */ 	lwc1	$f8,0xc($a0)
/*    2a910:	01cf001a */ 	div	$zero,$t6,$t7
/*    2a914:	e7a80070 */ 	swc1	$f8,0x70($sp)
/*    2a918:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*    2a91c:	00003010 */ 	mfhi	$a2
/*    2a920:	0006c8c0 */ 	sll	$t9,$a2,0x3
/*    2a924:	e7aa0074 */ 	swc1	$f10,0x74($sp)
/*    2a928:	c4900010 */ 	lwc1	$f16,0x10($a0)
/*    2a92c:	00592821 */ 	addu	$a1,$v0,$t9
/*    2a930:	15e00002 */ 	bnez	$t7,.L0002a93c
/*    2a934:	00000000 */ 	nop
/*    2a938:	0007000d */ 	break	0x7
.L0002a93c:
/*    2a93c:	2401ffff */ 	addiu	$at,$zero,-1
/*    2a940:	15e10004 */ 	bne	$t7,$at,.L0002a954
/*    2a944:	3c018000 */ 	lui	$at,0x8000
/*    2a948:	15c10002 */ 	bne	$t6,$at,.L0002a954
/*    2a94c:	00000000 */ 	nop
/*    2a950:	0006000d */ 	break	0x6
.L0002a954:
/*    2a954:	e7b00078 */ 	swc1	$f16,0x78($sp)
/*    2a958:	c4b2000c */ 	lwc1	$f18,0xc($a1)
/*    2a95c:	e7b20064 */ 	swc1	$f18,0x64($sp)
/*    2a960:	c6040004 */ 	lwc1	$f4,0x4($s0)
/*    2a964:	e7a40068 */ 	swc1	$f4,0x68($sp)
/*    2a968:	c4a60010 */ 	lwc1	$f6,0x10($a1)
/*    2a96c:	10000017 */ 	b	.L0002a9cc
/*    2a970:	e7a6006c */ 	swc1	$f6,0x6c($sp)
.L0002a974:
/*    2a974:	24010003 */ 	addiu	$at,$zero,0x3
/*    2a978:	14410014 */ 	bne	$v0,$at,.L0002a9cc
/*    2a97c:	27a80070 */ 	addiu	$t0,$sp,0x70
/*    2a980:	8fa20080 */ 	lw	$v0,0x80($sp)
/*    2a984:	c6080008 */ 	lwc1	$f8,0x8($s0)
/*    2a988:	8e070000 */ 	lw	$a3,0x0($s0)
/*    2a98c:	c44c000c */ 	lwc1	$f12,0xc($v0)
/*    2a990:	c44e0010 */ 	lwc1	$f14,0x10($v0)
/*    2a994:	8c460014 */ 	lw	$a2,0x14($v0)
/*    2a998:	27a90078 */ 	addiu	$t1,$sp,0x78
/*    2a99c:	27aa0064 */ 	addiu	$t2,$sp,0x64
/*    2a9a0:	27ab006c */ 	addiu	$t3,$sp,0x6c
/*    2a9a4:	afab0020 */ 	sw	$t3,0x20($sp)
/*    2a9a8:	afaa001c */ 	sw	$t2,0x1c($sp)
/*    2a9ac:	afa90018 */ 	sw	$t1,0x18($sp)
/*    2a9b0:	afa80014 */ 	sw	$t0,0x14($sp)
/*    2a9b4:	0c009612 */ 	jal	func00025848
/*    2a9b8:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*    2a9bc:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*    2a9c0:	e7aa0074 */ 	swc1	$f10,0x74($sp)
/*    2a9c4:	c6100004 */ 	lwc1	$f16,0x4($s0)
/*    2a9c8:	e7b00068 */ 	swc1	$f16,0x68($sp)
.L0002a9cc:
/*    2a9cc:	27a40070 */ 	addiu	$a0,$sp,0x70
/*    2a9d0:	27a50064 */ 	addiu	$a1,$sp,0x64
/*    2a9d4:	0c0093ec */ 	jal	func00024fb0
/*    2a9d8:	8fa6008c */ 	lw	$a2,0x8c($sp)
/*    2a9dc:	8fbf0034 */ 	lw	$ra,0x34($sp)
.L0002a9e0:
/*    2a9e0:	8fa2007c */ 	lw	$v0,0x7c($sp)
/*    2a9e4:	8fb00030 */ 	lw	$s0,0x30($sp)
/*    2a9e8:	03e00008 */ 	jr	$ra
/*    2a9ec:	27bd00a8 */ 	addiu	$sp,$sp,0xa8
);

// Mismatch: Goal copies tile from t1 to v0 in the type 0 block
//s32 func0002a6fc(struct coord *pos, struct coord *pos2, f32 width, s16 *rooms, s32 types, bool arg5, f32 arg6, f32 arg7)
//{
//	u32 stack[5];
//	struct collisionthing thing; // 80
//	s32 cdresult;
//	struct coord sp70;
//	struct coord sp64;
//
//	cdresult = CDRESULT_NOCOLLISION;
//
//	func00027d1c(pos2, width, rooms, types, 4, arg5, arg6, arg7, &thing, 1);
//
//	// 768
//	if (thing.tile != NULL) {
//		cdresult = CDRESULT_COLLISION;
//
//		// 778
//		if (thing.tile->type == TILETYPE_00) {
//			struct tiletype0 *type0 = (struct tiletype0 *) thing.tile;
//			s32 this = thing.unk08;
//			s32 next = (this + 1) % thing.tile->numvertices;
//
//			sp70.x = type0->vertices[this][0];
//			sp70.y = type0->vertices[this][1];
//			sp70.z = type0->vertices[this][2];
//
//			sp64.x = type0->vertices[next][0];
//			sp64.y = type0->vertices[next][1];
//			sp64.z = type0->vertices[next][2];
//		} else /*854*/ if (thing.tile->type == TILETYPE_01) {
//			struct tiletype1 *type1 = (struct tiletype1 *) thing.tile;
//			s32 this = thing.unk08;
//			s32 next = (this + 1) % thing.tile->numvertices;
//
//			sp70.x = type1->vertices[this].x;
//			sp70.y = type1->vertices[this].y;
//			sp70.z = type1->vertices[this].z;
//
//			sp64.x = type1->vertices[next].x;
//			sp64.y = type1->vertices[next].y;
//			sp64.z = type1->vertices[next].z;
//		} else if (thing.tile->type == TILETYPE_02) {
//			struct tiletype2 *type2 = (struct tiletype2 *) thing.tile;
//			s32 this = thing.unk08;
//			s32 next = (this + 1) % thing.tile->numvertices;
//
//			sp70.x = type2->vertices[this][0];
//			sp70.y = pos->y;
//			sp70.z = type2->vertices[this][1];
//
//			sp64.x = type2->vertices[next][0];
//			sp64.y = pos->y;
//			sp64.z = type2->vertices[next][1];
//		} else if (thing.tile->type == TILETYPE_03) {
//			struct tiletype3 *type3 = (struct tiletype3 *) thing.tile;
//
//			if (1);
//
//			func00025848(type3->x, type3->z, type3->width, pos->x, pos->z, &sp70.x, &sp70.z, &sp64.x, &sp64.z);
//
//			sp70.y = pos->y;
//			sp64.y = pos->y;
//		}
//
//		func00024fb0(&sp70, &sp64, thing.prop);
//	}
//
//	return cdresult;
//}

s32 cdTestAToB1(struct coord *origpos, struct coord *dstpos, f32 width, s16 *dstrooms, s32 types, s32 arg5, f32 ymax, f32 ymin)
{
	struct collisionthing things[21];
	struct coord dist;
	s32 result = CDRESULT_NOCOLLISION;

	func00028df0(dstpos, width, dstrooms, types, 4, arg5, ymax, ymin, things, 20);

	if (things[0].tile) {
		result = CDRESULT_COLLISION;

		dist.x = dstpos->x - origpos->x;
		dist.y = dstpos->y - origpos->y;
		dist.z = dstpos->z - origpos->z;

		func0002901c(origpos, &dist, width, things);
	}

	return result;
}

GLOBAL_ASM(
glabel func0002aac0
/*    2aac0:	27bdffa8 */ 	addiu	$sp,$sp,-88
/*    2aac4:	afbf0054 */ 	sw	$ra,0x54($sp)
/*    2aac8:	afbe0050 */ 	sw	$s8,0x50($sp)
/*    2aacc:	afb7004c */ 	sw	$s7,0x4c($sp)
/*    2aad0:	afb60048 */ 	sw	$s6,0x48($sp)
/*    2aad4:	afb50044 */ 	sw	$s5,0x44($sp)
/*    2aad8:	afb40040 */ 	sw	$s4,0x40($sp)
/*    2aadc:	afb3003c */ 	sw	$s3,0x3c($sp)
/*    2aae0:	afb20038 */ 	sw	$s2,0x38($sp)
/*    2aae4:	afb10034 */ 	sw	$s1,0x34($sp)
/*    2aae8:	afb00030 */ 	sw	$s0,0x30($sp)
/*    2aaec:	90f30001 */ 	lbu	$s3,0x1($a3)
/*    2aaf0:	0080a825 */ 	or	$s5,$a0,$zero
/*    2aaf4:	00a0b025 */ 	or	$s6,$a1,$zero
/*    2aaf8:	2a610003 */ 	slti	$at,$s3,0x3
/*    2aafc:	00c0b825 */ 	or	$s7,$a2,$zero
/*    2ab00:	14200018 */ 	bnez	$at,.L0002ab64
/*    2ab04:	24100002 */ 	addiu	$s0,$zero,0x2
/*    2ab08:	24e2000c */ 	addiu	$v0,$a3,0xc
/*    2ab0c:	24510008 */ 	addiu	$s1,$v0,0x8
/*    2ab10:	2452000e */ 	addiu	$s2,$v0,0xe
/*    2ab14:	24f4000e */ 	addiu	$s4,$a3,0xe
/*    2ab18:	8fbe0068 */ 	lw	$s8,0x68($sp)
.L0002ab1c:
/*    2ab1c:	8fae006c */ 	lw	$t6,0x6c($sp)
/*    2ab20:	02802025 */ 	or	$a0,$s4,$zero
/*    2ab24:	02202825 */ 	or	$a1,$s1,$zero
/*    2ab28:	02403025 */ 	or	$a2,$s2,$zero
/*    2ab2c:	00003825 */ 	or	$a3,$zero,$zero
/*    2ab30:	afb50010 */ 	sw	$s5,0x10($sp)
/*    2ab34:	afb60014 */ 	sw	$s6,0x14($sp)
/*    2ab38:	afb70018 */ 	sw	$s7,0x18($sp)
/*    2ab3c:	afbe001c */ 	sw	$s8,0x1c($sp)
/*    2ab40:	0c00bd24 */ 	jal	func0002f490
/*    2ab44:	afae0020 */ 	sw	$t6,0x20($sp)
/*    2ab48:	10400003 */ 	beqz	$v0,.L0002ab58
/*    2ab4c:	26100001 */ 	addiu	$s0,$s0,0x1
/*    2ab50:	10000005 */ 	b	.L0002ab68
/*    2ab54:	24020001 */ 	addiu	$v0,$zero,0x1
.L0002ab58:
/*    2ab58:	26310006 */ 	addiu	$s1,$s1,0x6
/*    2ab5c:	1613ffef */ 	bne	$s0,$s3,.L0002ab1c
/*    2ab60:	26520006 */ 	addiu	$s2,$s2,0x6
.L0002ab64:
/*    2ab64:	00001025 */ 	or	$v0,$zero,$zero
.L0002ab68:
/*    2ab68:	8fbf0054 */ 	lw	$ra,0x54($sp)
/*    2ab6c:	8fb00030 */ 	lw	$s0,0x30($sp)
/*    2ab70:	8fb10034 */ 	lw	$s1,0x34($sp)
/*    2ab74:	8fb20038 */ 	lw	$s2,0x38($sp)
/*    2ab78:	8fb3003c */ 	lw	$s3,0x3c($sp)
/*    2ab7c:	8fb40040 */ 	lw	$s4,0x40($sp)
/*    2ab80:	8fb50044 */ 	lw	$s5,0x44($sp)
/*    2ab84:	8fb60048 */ 	lw	$s6,0x48($sp)
/*    2ab88:	8fb7004c */ 	lw	$s7,0x4c($sp)
/*    2ab8c:	8fbe0050 */ 	lw	$s8,0x50($sp)
/*    2ab90:	03e00008 */ 	jr	$ra
/*    2ab94:	27bd0058 */ 	addiu	$sp,$sp,0x58
);

GLOBAL_ASM(
glabel func0002ab98
/*    2ab98:	27bdffa8 */ 	addiu	$sp,$sp,-88
/*    2ab9c:	afbf0054 */ 	sw	$ra,0x54($sp)
/*    2aba0:	afbe0050 */ 	sw	$s8,0x50($sp)
/*    2aba4:	afb7004c */ 	sw	$s7,0x4c($sp)
/*    2aba8:	afb60048 */ 	sw	$s6,0x48($sp)
/*    2abac:	afb50044 */ 	sw	$s5,0x44($sp)
/*    2abb0:	afb40040 */ 	sw	$s4,0x40($sp)
/*    2abb4:	afb3003c */ 	sw	$s3,0x3c($sp)
/*    2abb8:	afb20038 */ 	sw	$s2,0x38($sp)
/*    2abbc:	afb10034 */ 	sw	$s1,0x34($sp)
/*    2abc0:	afb00030 */ 	sw	$s0,0x30($sp)
/*    2abc4:	90f30001 */ 	lbu	$s3,0x1($a3)
/*    2abc8:	0080a825 */ 	or	$s5,$a0,$zero
/*    2abcc:	00a0b025 */ 	or	$s6,$a1,$zero
/*    2abd0:	2a610003 */ 	slti	$at,$s3,0x3
/*    2abd4:	00c0b825 */ 	or	$s7,$a2,$zero
/*    2abd8:	14200018 */ 	bnez	$at,.L0002ac3c
/*    2abdc:	24100002 */ 	addiu	$s0,$zero,0x2
/*    2abe0:	24e20018 */ 	addiu	$v0,$a3,0x18
/*    2abe4:	24510004 */ 	addiu	$s1,$v0,0x4
/*    2abe8:	24520010 */ 	addiu	$s2,$v0,0x10
/*    2abec:	24f40010 */ 	addiu	$s4,$a3,0x10
/*    2abf0:	8fbe0068 */ 	lw	$s8,0x68($sp)
.L0002abf4:
/*    2abf4:	8fae006c */ 	lw	$t6,0x6c($sp)
/*    2abf8:	02802025 */ 	or	$a0,$s4,$zero
/*    2abfc:	02202825 */ 	or	$a1,$s1,$zero
/*    2ac00:	02403025 */ 	or	$a2,$s2,$zero
/*    2ac04:	00003825 */ 	or	$a3,$zero,$zero
/*    2ac08:	afb50010 */ 	sw	$s5,0x10($sp)
/*    2ac0c:	afb60014 */ 	sw	$s6,0x14($sp)
/*    2ac10:	afb70018 */ 	sw	$s7,0x18($sp)
/*    2ac14:	afbe001c */ 	sw	$s8,0x1c($sp)
/*    2ac18:	0c00bd58 */ 	jal	func0002f560
/*    2ac1c:	afae0020 */ 	sw	$t6,0x20($sp)
/*    2ac20:	10400003 */ 	beqz	$v0,.L0002ac30
/*    2ac24:	26100001 */ 	addiu	$s0,$s0,0x1
/*    2ac28:	10000005 */ 	b	.L0002ac40
/*    2ac2c:	24020001 */ 	addiu	$v0,$zero,0x1
.L0002ac30:
/*    2ac30:	2631000c */ 	addiu	$s1,$s1,0xc
/*    2ac34:	1613ffef */ 	bne	$s0,$s3,.L0002abf4
/*    2ac38:	2652000c */ 	addiu	$s2,$s2,0xc
.L0002ac3c:
/*    2ac3c:	00001025 */ 	or	$v0,$zero,$zero
.L0002ac40:
/*    2ac40:	8fbf0054 */ 	lw	$ra,0x54($sp)
/*    2ac44:	8fb00030 */ 	lw	$s0,0x30($sp)
/*    2ac48:	8fb10034 */ 	lw	$s1,0x34($sp)
/*    2ac4c:	8fb20038 */ 	lw	$s2,0x38($sp)
/*    2ac50:	8fb3003c */ 	lw	$s3,0x3c($sp)
/*    2ac54:	8fb40040 */ 	lw	$s4,0x40($sp)
/*    2ac58:	8fb50044 */ 	lw	$s5,0x44($sp)
/*    2ac5c:	8fb60048 */ 	lw	$s6,0x48($sp)
/*    2ac60:	8fb7004c */ 	lw	$s7,0x4c($sp)
/*    2ac64:	8fbe0050 */ 	lw	$s8,0x50($sp)
/*    2ac68:	03e00008 */ 	jr	$ra
/*    2ac6c:	27bd0058 */ 	addiu	$sp,$sp,0x58
);

GLOBAL_ASM(
glabel func0002ac70
/*    2ac70:	27bdff20 */ 	addiu	$sp,$sp,-224
/*    2ac74:	afbf007c */ 	sw	$ra,0x7c($sp)
/*    2ac78:	afbe0078 */ 	sw	$s8,0x78($sp)
/*    2ac7c:	afb70074 */ 	sw	$s7,0x74($sp)
/*    2ac80:	afb60070 */ 	sw	$s6,0x70($sp)
/*    2ac84:	afb5006c */ 	sw	$s5,0x6c($sp)
/*    2ac88:	afb40068 */ 	sw	$s4,0x68($sp)
/*    2ac8c:	afb30064 */ 	sw	$s3,0x64($sp)
/*    2ac90:	afb20060 */ 	sw	$s2,0x60($sp)
/*    2ac94:	afb1005c */ 	sw	$s1,0x5c($sp)
/*    2ac98:	afb00058 */ 	sw	$s0,0x58($sp)
/*    2ac9c:	f7be0050 */ 	sdc1	$f30,0x50($sp)
/*    2aca0:	f7bc0048 */ 	sdc1	$f28,0x48($sp)
/*    2aca4:	f7ba0040 */ 	sdc1	$f26,0x40($sp)
/*    2aca8:	f7b80038 */ 	sdc1	$f24,0x38($sp)
/*    2acac:	f7b60030 */ 	sdc1	$f22,0x30($sp)
/*    2acb0:	f7b40028 */ 	sdc1	$f20,0x28($sp)
/*    2acb4:	afa600e8 */ 	sw	$a2,0xe8($sp)
/*    2acb8:	afa700ec */ 	sw	$a3,0xec($sp)
/*    2acbc:	afa000dc */ 	sw	$zero,0xdc($sp)
/*    2acc0:	90f70001 */ 	lbu	$s7,0x1($a3)
/*    2acc4:	240f0001 */ 	addiu	$t7,$zero,0x1
/*    2acc8:	afaf00c8 */ 	sw	$t7,0xc8($sp)
/*    2accc:	90f8000a */ 	lbu	$t8,0xa($a3)
/*    2acd0:	90e90007 */ 	lbu	$t1,0x7($a3)
/*    2acd4:	8fb600fc */ 	lw	$s6,0xfc($sp)
/*    2acd8:	0307c821 */ 	addu	$t9,$t8,$a3
/*    2acdc:	01275021 */ 	addu	$t2,$t1,$a3
/*    2ace0:	87280000 */ 	lh	$t0,0x0($t9)
/*    2ace4:	854b0000 */ 	lh	$t3,0x0($t2)
/*    2ace8:	3c013f80 */ 	lui	$at,0x3f80
/*    2acec:	44882000 */ 	mtc1	$t0,$f4
/*    2acf0:	448b3000 */ 	mtc1	$t3,$f6
/*    2acf4:	4481b000 */ 	mtc1	$at,$f22
/*    2acf8:	00a0a025 */ 	or	$s4,$a1,$zero
/*    2acfc:	0080a825 */ 	or	$s5,$a0,$zero
/*    2ad00:	00e07025 */ 	or	$t6,$a3,$zero
/*    2ad04:	468026a0 */ 	cvt.s.w	$f26,$f4
/*    2ad08:	12c0001b */ 	beqz	$s6,.L0002ad78
/*    2ad0c:	46803720 */ 	cvt.s.w	$f28,$f6
/*    2ad10:	c7be0100 */ 	lwc1	$f30,0x100($sp)
/*    2ad14:	c4820004 */ 	lwc1	$f2,0x4($a0)
/*    2ad18:	c7b00104 */ 	lwc1	$f16,0x104($sp)
/*    2ad1c:	461e1200 */ 	add.s	$f8,$f2,$f30
/*    2ad20:	4608e03e */ 	c.le.s	$f28,$f8
/*    2ad24:	00000000 */ 	nop
/*    2ad28:	45020008 */ 	bc1fl	.L0002ad4c
/*    2ad2c:	c7a40104 */ 	lwc1	$f4,0x104($sp)
/*    2ad30:	c68a0004 */ 	lwc1	$f10,0x4($s4)
/*    2ad34:	46105480 */ 	add.s	$f18,$f10,$f16
/*    2ad38:	461a903e */ 	c.le.s	$f18,$f26
/*    2ad3c:	00000000 */ 	nop
/*    2ad40:	4503000e */ 	bc1tl	.L0002ad7c
/*    2ad44:	c7be0100 */ 	lwc1	$f30,0x100($sp)
/*    2ad48:	c7a40104 */ 	lwc1	$f4,0x104($sp)
.L0002ad4c:
/*    2ad4c:	46041180 */ 	add.s	$f6,$f2,$f4
/*    2ad50:	461a303e */ 	c.le.s	$f6,$f26
/*    2ad54:	00000000 */ 	nop
/*    2ad58:	450200e1 */ 	bc1fl	.L0002b0e0
/*    2ad5c:	8fbf007c */ 	lw	$ra,0x7c($sp)
/*    2ad60:	c6880004 */ 	lwc1	$f8,0x4($s4)
/*    2ad64:	461e4280 */ 	add.s	$f10,$f8,$f30
/*    2ad68:	460ae03e */ 	c.le.s	$f28,$f10
/*    2ad6c:	00000000 */ 	nop
/*    2ad70:	450200db */ 	bc1fl	.L0002b0e0
/*    2ad74:	8fbf007c */ 	lw	$ra,0x7c($sp)
.L0002ad78:
/*    2ad78:	c7be0100 */ 	lwc1	$f30,0x100($sp)
.L0002ad7c:
/*    2ad7c:	1ae0006e */ 	blez	$s7,.L0002af38
/*    2ad80:	00009025 */ 	or	$s2,$zero,$zero
/*    2ad84:	8fb100ec */ 	lw	$s1,0xec($sp)
/*    2ad88:	c7b800bc */ 	lwc1	$f24,0xbc($sp)
/*    2ad8c:	c7b400b8 */ 	lwc1	$f20,0xb8($sp)
/*    2ad90:	27be00c8 */ 	addiu	$s8,$sp,0xc8
.L0002ad94:
/*    2ad94:	26530001 */ 	addiu	$s3,$s2,0x1
/*    2ad98:	0277001a */ 	div	$zero,$s3,$s7
/*    2ad9c:	0000c010 */ 	mfhi	$t8
/*    2ada0:	8faf00ec */ 	lw	$t7,0xec($sp)
/*    2ada4:	0018c880 */ 	sll	$t9,$t8,0x2
/*    2ada8:	0338c823 */ 	subu	$t9,$t9,$t8
/*    2adac:	0019c840 */ 	sll	$t9,$t9,0x1
/*    2adb0:	01f98021 */ 	addu	$s0,$t7,$t9
/*    2adb4:	8608000e */ 	lh	$t0,0xe($s0)
/*    2adb8:	862c000e */ 	lh	$t4,0xe($s1)
/*    2adbc:	862d0012 */ 	lh	$t5,0x12($s1)
/*    2adc0:	44882000 */ 	mtc1	$t0,$f4
/*    2adc4:	448c8000 */ 	mtc1	$t4,$f16
/*    2adc8:	448d9000 */ 	mtc1	$t5,$f18
/*    2adcc:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    2add0:	02a02025 */ 	or	$a0,$s5,$zero
/*    2add4:	02802825 */ 	or	$a1,$s4,$zero
/*    2add8:	46808420 */ 	cvt.s.w	$f16,$f16
/*    2addc:	e7a60010 */ 	swc1	$f6,0x10($sp)
/*    2ade0:	86090012 */ 	lh	$t1,0x12($s0)
/*    2ade4:	afbe0018 */ 	sw	$s8,0x18($sp)
/*    2ade8:	44894000 */ 	mtc1	$t1,$f8
/*    2adec:	468094a0 */ 	cvt.s.w	$f18,$f18
/*    2adf0:	44068000 */ 	mfc1	$a2,$f16
/*    2adf4:	468042a0 */ 	cvt.s.w	$f10,$f8
/*    2adf8:	44079000 */ 	mfc1	$a3,$f18
/*    2adfc:	16e00002 */ 	bnez	$s7,.L0002ae08
/*    2ae00:	00000000 */ 	nop
/*    2ae04:	0007000d */ 	break	0x7
.L0002ae08:
/*    2ae08:	2401ffff */ 	addiu	$at,$zero,-1
/*    2ae0c:	16e10004 */ 	bne	$s7,$at,.L0002ae20
/*    2ae10:	3c018000 */ 	lui	$at,0x8000
/*    2ae14:	16610002 */ 	bne	$s3,$at,.L0002ae20
/*    2ae18:	00000000 */ 	nop
/*    2ae1c:	0006000d */ 	break	0x6
.L0002ae20:
/*    2ae20:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*    2ae24:	0c009536 */ 	jal	func000254d8
/*    2ae28:	00000000 */ 	nop
/*    2ae2c:	5040003e */ 	beqzl	$v0,.L0002af28
/*    2ae30:	02609025 */ 	or	$s2,$s3,$zero
/*    2ae34:	c6b00000 */ 	lwc1	$f16,0x0($s5)
/*    2ae38:	27a400a8 */ 	addiu	$a0,$sp,0xa8
/*    2ae3c:	27a500a0 */ 	addiu	$a1,$sp,0xa0
/*    2ae40:	e7b000a8 */ 	swc1	$f16,0xa8($sp)
/*    2ae44:	c6b20008 */ 	lwc1	$f18,0x8($s5)
/*    2ae48:	27a60098 */ 	addiu	$a2,$sp,0x98
/*    2ae4c:	27a70090 */ 	addiu	$a3,$sp,0x90
/*    2ae50:	e7b200ac */ 	swc1	$f18,0xac($sp)
/*    2ae54:	c6840000 */ 	lwc1	$f4,0x0($s4)
/*    2ae58:	e7a400a0 */ 	swc1	$f4,0xa0($sp)
/*    2ae5c:	c6860008 */ 	lwc1	$f6,0x8($s4)
/*    2ae60:	e7a600a4 */ 	swc1	$f6,0xa4($sp)
/*    2ae64:	862e000e */ 	lh	$t6,0xe($s1)
/*    2ae68:	448e4000 */ 	mtc1	$t6,$f8
/*    2ae6c:	00000000 */ 	nop
/*    2ae70:	468042a0 */ 	cvt.s.w	$f10,$f8
/*    2ae74:	e7aa0098 */ 	swc1	$f10,0x98($sp)
/*    2ae78:	862a0012 */ 	lh	$t2,0x12($s1)
/*    2ae7c:	448a8000 */ 	mtc1	$t2,$f16
/*    2ae80:	00000000 */ 	nop
/*    2ae84:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    2ae88:	e7b2009c */ 	swc1	$f18,0x9c($sp)
/*    2ae8c:	860b000e */ 	lh	$t3,0xe($s0)
/*    2ae90:	448b2000 */ 	mtc1	$t3,$f4
/*    2ae94:	00000000 */ 	nop
/*    2ae98:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    2ae9c:	e7a60090 */ 	swc1	$f6,0x90($sp)
/*    2aea0:	860c0012 */ 	lh	$t4,0x12($s0)
/*    2aea4:	448c4000 */ 	mtc1	$t4,$f8
/*    2aea8:	00000000 */ 	nop
/*    2aeac:	468042a0 */ 	cvt.s.w	$f10,$f8
/*    2aeb0:	0fc55dfc */ 	jal	func0f1577f0
/*    2aeb4:	e7aa0094 */ 	swc1	$f10,0x94($sp)
/*    2aeb8:	4616003c */ 	c.lt.s	$f0,$f22
/*    2aebc:	00000000 */ 	nop
/*    2aec0:	45020019 */ 	bc1fl	.L0002af28
/*    2aec4:	02609025 */ 	or	$s2,$s3,$zero
/*    2aec8:	12c00009 */ 	beqz	$s6,.L0002aef0
/*    2aecc:	240d0001 */ 	addiu	$t5,$zero,0x1
/*    2aed0:	c6a20004 */ 	lwc1	$f2,0x4($s5)
/*    2aed4:	c6900004 */ 	lwc1	$f16,0x4($s4)
/*    2aed8:	c7a60104 */ 	lwc1	$f6,0x104($sp)
/*    2aedc:	46028481 */ 	sub.s	$f18,$f16,$f2
/*    2aee0:	46009102 */ 	mul.s	$f4,$f18,$f0
/*    2aee4:	46022500 */ 	add.s	$f20,$f4,$f2
/*    2aee8:	461ea600 */ 	add.s	$f24,$f20,$f30
/*    2aeec:	4606a500 */ 	add.s	$f20,$f20,$f6
.L0002aef0:
/*    2aef0:	52c0000a */ 	beqzl	$s6,.L0002af1c
/*    2aef4:	afad00dc */ 	sw	$t5,0xdc($sp)
/*    2aef8:	4614d03e */ 	c.le.s	$f26,$f20
/*    2aefc:	00000000 */ 	nop
/*    2af00:	45030009 */ 	bc1tl	.L0002af28
/*    2af04:	02609025 */ 	or	$s2,$s3,$zero
/*    2af08:	461cc03e */ 	c.le.s	$f24,$f28
/*    2af0c:	00000000 */ 	nop
/*    2af10:	45030005 */ 	bc1tl	.L0002af28
/*    2af14:	02609025 */ 	or	$s2,$s3,$zero
/*    2af18:	afad00dc */ 	sw	$t5,0xdc($sp)
.L0002af1c:
/*    2af1c:	46000586 */ 	mov.s	$f22,$f0
/*    2af20:	afb200c0 */ 	sw	$s2,0xc0($sp)
/*    2af24:	02609025 */ 	or	$s2,$s3,$zero
.L0002af28:
/*    2af28:	1677ff9a */ 	bne	$s3,$s7,.L0002ad94
/*    2af2c:	26310006 */ 	addiu	$s1,$s1,0x6
/*    2af30:	e7b800bc */ 	swc1	$f24,0xbc($sp)
/*    2af34:	e7b400b8 */ 	swc1	$f20,0xb8($sp)
.L0002af38:
/*    2af38:	8fb800dc */ 	lw	$t8,0xdc($sp)
/*    2af3c:	8faf00e8 */ 	lw	$t7,0xe8($sp)
/*    2af40:	8faa00dc */ 	lw	$t2,0xdc($sp)
/*    2af44:	13000048 */ 	beqz	$t8,.L0002b068
/*    2af48:	00000000 */ 	nop
/*    2af4c:	c5e80000 */ 	lwc1	$f8,0x0($t7)
/*    2af50:	c6b00000 */ 	lwc1	$f16,0x0($s5)
/*    2af54:	8fa200f0 */ 	lw	$v0,0xf0($sp)
/*    2af58:	46164282 */ 	mul.s	$f10,$f8,$f22
/*    2af5c:	8fa600f4 */ 	lw	$a2,0xf4($sp)
/*    2af60:	46105480 */ 	add.s	$f18,$f10,$f16
/*    2af64:	e4520000 */ 	swc1	$f18,0x0($v0)
/*    2af68:	8fb900e8 */ 	lw	$t9,0xe8($sp)
/*    2af6c:	c6a80004 */ 	lwc1	$f8,0x4($s5)
/*    2af70:	c7240004 */ 	lwc1	$f4,0x4($t9)
/*    2af74:	46162182 */ 	mul.s	$f6,$f4,$f22
/*    2af78:	46083280 */ 	add.s	$f10,$f6,$f8
/*    2af7c:	e44a0004 */ 	swc1	$f10,0x4($v0)
/*    2af80:	8fa800e8 */ 	lw	$t0,0xe8($sp)
/*    2af84:	c6a40008 */ 	lwc1	$f4,0x8($s5)
/*    2af88:	c5100008 */ 	lwc1	$f16,0x8($t0)
/*    2af8c:	46168482 */ 	mul.s	$f18,$f16,$f22
/*    2af90:	46049180 */ 	add.s	$f6,$f18,$f4
/*    2af94:	10c00051 */ 	beqz	$a2,.L0002b0dc
/*    2af98:	e4460008 */ 	swc1	$f6,0x8($v0)
/*    2af9c:	8fa300f8 */ 	lw	$v1,0xf8($sp)
/*    2afa0:	8fae00c0 */ 	lw	$t6,0xc0($sp)
/*    2afa4:	1060004d */ 	beqz	$v1,.L0002b0dc
/*    2afa8:	000e5080 */ 	sll	$t2,$t6,0x2
/*    2afac:	8fa900ec */ 	lw	$t1,0xec($sp)
/*    2afb0:	014e5023 */ 	subu	$t2,$t2,$t6
/*    2afb4:	000a5040 */ 	sll	$t2,$t2,0x1
/*    2afb8:	012a2021 */ 	addu	$a0,$t1,$t2
/*    2afbc:	848b000e */ 	lh	$t3,0xe($a0)
/*    2afc0:	448b4000 */ 	mtc1	$t3,$f8
/*    2afc4:	00000000 */ 	nop
/*    2afc8:	468042a0 */ 	cvt.s.w	$f10,$f8
/*    2afcc:	e4ca0000 */ 	swc1	$f10,0x0($a2)
/*    2afd0:	c4500004 */ 	lwc1	$f16,0x4($v0)
/*    2afd4:	e4d00004 */ 	swc1	$f16,0x4($a2)
/*    2afd8:	848c0012 */ 	lh	$t4,0x12($a0)
/*    2afdc:	448c9000 */ 	mtc1	$t4,$f18
/*    2afe0:	00000000 */ 	nop
/*    2afe4:	46809120 */ 	cvt.s.w	$f4,$f18
/*    2afe8:	e4c40008 */ 	swc1	$f4,0x8($a2)
/*    2afec:	8fb800c0 */ 	lw	$t8,0xc0($sp)
/*    2aff0:	8fad00ec */ 	lw	$t5,0xec($sp)
/*    2aff4:	270f0001 */ 	addiu	$t7,$t8,0x1
/*    2aff8:	01f7001a */ 	div	$zero,$t7,$s7
/*    2affc:	0000c810 */ 	mfhi	$t9
/*    2b000:	00194080 */ 	sll	$t0,$t9,0x2
/*    2b004:	01194023 */ 	subu	$t0,$t0,$t9
/*    2b008:	00084040 */ 	sll	$t0,$t0,0x1
/*    2b00c:	01a82821 */ 	addu	$a1,$t5,$t0
/*    2b010:	84ae000e */ 	lh	$t6,0xe($a1)
/*    2b014:	16e00002 */ 	bnez	$s7,.L0002b020
/*    2b018:	00000000 */ 	nop
/*    2b01c:	0007000d */ 	break	0x7
.L0002b020:
/*    2b020:	2401ffff */ 	addiu	$at,$zero,-1
/*    2b024:	16e10004 */ 	bne	$s7,$at,.L0002b038
/*    2b028:	3c018000 */ 	lui	$at,0x8000
/*    2b02c:	15e10002 */ 	bne	$t7,$at,.L0002b038
/*    2b030:	00000000 */ 	nop
/*    2b034:	0006000d */ 	break	0x6
.L0002b038:
/*    2b038:	448e3000 */ 	mtc1	$t6,$f6
/*    2b03c:	00000000 */ 	nop
/*    2b040:	46803220 */ 	cvt.s.w	$f8,$f6
/*    2b044:	e4680000 */ 	swc1	$f8,0x0($v1)
/*    2b048:	c44a0004 */ 	lwc1	$f10,0x4($v0)
/*    2b04c:	e46a0004 */ 	swc1	$f10,0x4($v1)
/*    2b050:	84a90012 */ 	lh	$t1,0x12($a1)
/*    2b054:	44898000 */ 	mtc1	$t1,$f16
/*    2b058:	00000000 */ 	nop
/*    2b05c:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    2b060:	1000001e */ 	b	.L0002b0dc
/*    2b064:	e4720008 */ 	swc1	$f18,0x8($v1)
.L0002b068:
/*    2b068:	1540001c */ 	bnez	$t2,.L0002b0dc
/*    2b06c:	8fab00c8 */ 	lw	$t3,0xc8($sp)
/*    2b070:	1160001a */ 	beqz	$t3,.L0002b0dc
/*    2b074:	8fa200f0 */ 	lw	$v0,0xf0($sp)
/*    2b078:	240c0001 */ 	addiu	$t4,$zero,0x1
/*    2b07c:	afac00dc */ 	sw	$t4,0xdc($sp)
/*    2b080:	c6a40000 */ 	lwc1	$f4,0x0($s5)
/*    2b084:	8fa600f4 */ 	lw	$a2,0xf4($sp)
/*    2b088:	e4440000 */ 	swc1	$f4,0x0($v0)
/*    2b08c:	c6a60004 */ 	lwc1	$f6,0x4($s5)
/*    2b090:	e4460004 */ 	swc1	$f6,0x4($v0)
/*    2b094:	c6a80008 */ 	lwc1	$f8,0x8($s5)
/*    2b098:	10c00010 */ 	beqz	$a2,.L0002b0dc
/*    2b09c:	e4480008 */ 	swc1	$f8,0x8($v0)
/*    2b0a0:	8fa300f8 */ 	lw	$v1,0xf8($sp)
/*    2b0a4:	5060000e */ 	beqzl	$v1,.L0002b0e0
/*    2b0a8:	8fbf007c */ 	lw	$ra,0x7c($sp)
/*    2b0ac:	c6aa0000 */ 	lwc1	$f10,0x0($s5)
/*    2b0b0:	e4ca0000 */ 	swc1	$f10,0x0($a2)
/*    2b0b4:	c6b00004 */ 	lwc1	$f16,0x4($s5)
/*    2b0b8:	e4d00004 */ 	swc1	$f16,0x4($a2)
/*    2b0bc:	c6b20008 */ 	lwc1	$f18,0x8($s5)
/*    2b0c0:	e4d20008 */ 	swc1	$f18,0x8($a2)
/*    2b0c4:	c6a40000 */ 	lwc1	$f4,0x0($s5)
/*    2b0c8:	e4640000 */ 	swc1	$f4,0x0($v1)
/*    2b0cc:	c6a60004 */ 	lwc1	$f6,0x4($s5)
/*    2b0d0:	e4660004 */ 	swc1	$f6,0x4($v1)
/*    2b0d4:	c6a80008 */ 	lwc1	$f8,0x8($s5)
/*    2b0d8:	e4680008 */ 	swc1	$f8,0x8($v1)
.L0002b0dc:
/*    2b0dc:	8fbf007c */ 	lw	$ra,0x7c($sp)
.L0002b0e0:
/*    2b0e0:	8fa200dc */ 	lw	$v0,0xdc($sp)
/*    2b0e4:	d7b40028 */ 	ldc1	$f20,0x28($sp)
/*    2b0e8:	d7b60030 */ 	ldc1	$f22,0x30($sp)
/*    2b0ec:	d7b80038 */ 	ldc1	$f24,0x38($sp)
/*    2b0f0:	d7ba0040 */ 	ldc1	$f26,0x40($sp)
/*    2b0f4:	d7bc0048 */ 	ldc1	$f28,0x48($sp)
/*    2b0f8:	d7be0050 */ 	ldc1	$f30,0x50($sp)
/*    2b0fc:	8fb00058 */ 	lw	$s0,0x58($sp)
/*    2b100:	8fb1005c */ 	lw	$s1,0x5c($sp)
/*    2b104:	8fb20060 */ 	lw	$s2,0x60($sp)
/*    2b108:	8fb30064 */ 	lw	$s3,0x64($sp)
/*    2b10c:	8fb40068 */ 	lw	$s4,0x68($sp)
/*    2b110:	8fb5006c */ 	lw	$s5,0x6c($sp)
/*    2b114:	8fb60070 */ 	lw	$s6,0x70($sp)
/*    2b118:	8fb70074 */ 	lw	$s7,0x74($sp)
/*    2b11c:	8fbe0078 */ 	lw	$s8,0x78($sp)
/*    2b120:	03e00008 */ 	jr	$ra
/*    2b124:	27bd00e0 */ 	addiu	$sp,$sp,0xe0
);

GLOBAL_ASM(
glabel func0002b128
/*    2b128:	27bdff20 */ 	addiu	$sp,$sp,-224
/*    2b12c:	afbf007c */ 	sw	$ra,0x7c($sp)
/*    2b130:	afbe0078 */ 	sw	$s8,0x78($sp)
/*    2b134:	afb70074 */ 	sw	$s7,0x74($sp)
/*    2b138:	afb60070 */ 	sw	$s6,0x70($sp)
/*    2b13c:	afb5006c */ 	sw	$s5,0x6c($sp)
/*    2b140:	afb40068 */ 	sw	$s4,0x68($sp)
/*    2b144:	afb30064 */ 	sw	$s3,0x64($sp)
/*    2b148:	afb20060 */ 	sw	$s2,0x60($sp)
/*    2b14c:	afb1005c */ 	sw	$s1,0x5c($sp)
/*    2b150:	afb00058 */ 	sw	$s0,0x58($sp)
/*    2b154:	f7be0050 */ 	sdc1	$f30,0x50($sp)
/*    2b158:	f7bc0048 */ 	sdc1	$f28,0x48($sp)
/*    2b15c:	f7ba0040 */ 	sdc1	$f26,0x40($sp)
/*    2b160:	f7b80038 */ 	sdc1	$f24,0x38($sp)
/*    2b164:	f7b60030 */ 	sdc1	$f22,0x30($sp)
/*    2b168:	f7b40028 */ 	sdc1	$f20,0x28($sp)
/*    2b16c:	afa600e8 */ 	sw	$a2,0xe8($sp)
/*    2b170:	afa700ec */ 	sw	$a3,0xec($sp)
/*    2b174:	afa000dc */ 	sw	$zero,0xdc($sp)
/*    2b178:	90f70001 */ 	lbu	$s7,0x1($a3)
/*    2b17c:	240f0001 */ 	addiu	$t7,$zero,0x1
/*    2b180:	afaf00c8 */ 	sw	$t7,0xc8($sp)
/*    2b184:	90f8000a */ 	lbu	$t8,0xa($a3)
/*    2b188:	2402000c */ 	addiu	$v0,$zero,0xc
/*    2b18c:	90e90007 */ 	lbu	$t1,0x7($a3)
/*    2b190:	03020019 */ 	multu	$t8,$v0
/*    2b194:	8fb600fc */ 	lw	$s6,0xfc($sp)
/*    2b198:	3c013f80 */ 	lui	$at,0x3f80
/*    2b19c:	4481b000 */ 	mtc1	$at,$f22
/*    2b1a0:	00a0a025 */ 	or	$s4,$a1,$zero
/*    2b1a4:	0080a825 */ 	or	$s5,$a0,$zero
/*    2b1a8:	00e07025 */ 	or	$t6,$a3,$zero
/*    2b1ac:	c7be0100 */ 	lwc1	$f30,0x100($sp)
/*    2b1b0:	00009025 */ 	or	$s2,$zero,$zero
/*    2b1b4:	0000c812 */ 	mflo	$t9
/*    2b1b8:	00f94021 */ 	addu	$t0,$a3,$t9
/*    2b1bc:	c51a0014 */ 	lwc1	$f26,0x14($t0)
/*    2b1c0:	01220019 */ 	multu	$t1,$v0
/*    2b1c4:	00005012 */ 	mflo	$t2
/*    2b1c8:	00ea5821 */ 	addu	$t3,$a3,$t2
/*    2b1cc:	12c0001a */ 	beqz	$s6,.L0002b238
/*    2b1d0:	c57c0014 */ 	lwc1	$f28,0x14($t3)
/*    2b1d4:	c4820004 */ 	lwc1	$f2,0x4($a0)
/*    2b1d8:	461e1100 */ 	add.s	$f4,$f2,$f30
/*    2b1dc:	4604e03e */ 	c.le.s	$f28,$f4
/*    2b1e0:	00000000 */ 	nop
/*    2b1e4:	45020009 */ 	bc1fl	.L0002b20c
/*    2b1e8:	c7b00104 */ 	lwc1	$f16,0x104($sp)
/*    2b1ec:	c6860004 */ 	lwc1	$f6,0x4($s4)
/*    2b1f0:	c7a80104 */ 	lwc1	$f8,0x104($sp)
/*    2b1f4:	46083280 */ 	add.s	$f10,$f6,$f8
/*    2b1f8:	461a503e */ 	c.le.s	$f10,$f26
/*    2b1fc:	00000000 */ 	nop
/*    2b200:	4501000d */ 	bc1t	.L0002b238
/*    2b204:	00000000 */ 	nop
/*    2b208:	c7b00104 */ 	lwc1	$f16,0x104($sp)
.L0002b20c:
/*    2b20c:	46101480 */ 	add.s	$f18,$f2,$f16
/*    2b210:	461a903e */ 	c.le.s	$f18,$f26
/*    2b214:	00000000 */ 	nop
/*    2b218:	450200bf */ 	bc1fl	.L0002b518
/*    2b21c:	8fbf007c */ 	lw	$ra,0x7c($sp)
/*    2b220:	c6840004 */ 	lwc1	$f4,0x4($s4)
/*    2b224:	461e2180 */ 	add.s	$f6,$f4,$f30
/*    2b228:	4606e03e */ 	c.le.s	$f28,$f6
/*    2b22c:	00000000 */ 	nop
/*    2b230:	450200b9 */ 	bc1fl	.L0002b518
/*    2b234:	8fbf007c */ 	lw	$ra,0x7c($sp)
.L0002b238:
/*    2b238:	1ae00059 */ 	blez	$s7,.L0002b3a0
/*    2b23c:	c7be0100 */ 	lwc1	$f30,0x100($sp)
/*    2b240:	8fb100ec */ 	lw	$s1,0xec($sp)
/*    2b244:	c7b800bc */ 	lwc1	$f24,0xbc($sp)
/*    2b248:	c7b400b8 */ 	lwc1	$f20,0xb8($sp)
/*    2b24c:	27be00c8 */ 	addiu	$s8,$sp,0xc8
.L0002b250:
/*    2b250:	26530001 */ 	addiu	$s3,$s2,0x1
/*    2b254:	0277001a */ 	div	$zero,$s3,$s7
/*    2b258:	00006810 */ 	mfhi	$t5
/*    2b25c:	8fac00ec */ 	lw	$t4,0xec($sp)
/*    2b260:	000d7880 */ 	sll	$t7,$t5,0x2
/*    2b264:	01ed7823 */ 	subu	$t7,$t7,$t5
/*    2b268:	000f7880 */ 	sll	$t7,$t7,0x2
/*    2b26c:	018f8021 */ 	addu	$s0,$t4,$t7
/*    2b270:	c6080010 */ 	lwc1	$f8,0x10($s0)
/*    2b274:	8e260010 */ 	lw	$a2,0x10($s1)
/*    2b278:	8e270018 */ 	lw	$a3,0x18($s1)
/*    2b27c:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*    2b280:	c60a0018 */ 	lwc1	$f10,0x18($s0)
/*    2b284:	afbe0018 */ 	sw	$s8,0x18($sp)
/*    2b288:	02a02025 */ 	or	$a0,$s5,$zero
/*    2b28c:	02802825 */ 	or	$a1,$s4,$zero
/*    2b290:	16e00002 */ 	bnez	$s7,.L0002b29c
/*    2b294:	00000000 */ 	nop
/*    2b298:	0007000d */ 	break	0x7
.L0002b29c:
/*    2b29c:	2401ffff */ 	addiu	$at,$zero,-1
/*    2b2a0:	16e10004 */ 	bne	$s7,$at,.L0002b2b4
/*    2b2a4:	3c018000 */ 	lui	$at,0x8000
/*    2b2a8:	16610002 */ 	bne	$s3,$at,.L0002b2b4
/*    2b2ac:	00000000 */ 	nop
/*    2b2b0:	0006000d */ 	break	0x6
.L0002b2b4:
/*    2b2b4:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*    2b2b8:	0c009536 */ 	jal	func000254d8
/*    2b2bc:	00000000 */ 	nop
/*    2b2c0:	50400033 */ 	beqzl	$v0,.L0002b390
/*    2b2c4:	02609025 */ 	or	$s2,$s3,$zero
/*    2b2c8:	c6b00000 */ 	lwc1	$f16,0x0($s5)
/*    2b2cc:	27a400a8 */ 	addiu	$a0,$sp,0xa8
/*    2b2d0:	27a500a0 */ 	addiu	$a1,$sp,0xa0
/*    2b2d4:	e7b000a8 */ 	swc1	$f16,0xa8($sp)
/*    2b2d8:	c6b20008 */ 	lwc1	$f18,0x8($s5)
/*    2b2dc:	27a60098 */ 	addiu	$a2,$sp,0x98
/*    2b2e0:	27a70090 */ 	addiu	$a3,$sp,0x90
/*    2b2e4:	e7b200ac */ 	swc1	$f18,0xac($sp)
/*    2b2e8:	c6840000 */ 	lwc1	$f4,0x0($s4)
/*    2b2ec:	e7a400a0 */ 	swc1	$f4,0xa0($sp)
/*    2b2f0:	c6860008 */ 	lwc1	$f6,0x8($s4)
/*    2b2f4:	e7a600a4 */ 	swc1	$f6,0xa4($sp)
/*    2b2f8:	c6280010 */ 	lwc1	$f8,0x10($s1)
/*    2b2fc:	e7a80098 */ 	swc1	$f8,0x98($sp)
/*    2b300:	c62a0018 */ 	lwc1	$f10,0x18($s1)
/*    2b304:	e7aa009c */ 	swc1	$f10,0x9c($sp)
/*    2b308:	c6100010 */ 	lwc1	$f16,0x10($s0)
/*    2b30c:	e7b00090 */ 	swc1	$f16,0x90($sp)
/*    2b310:	c6120018 */ 	lwc1	$f18,0x18($s0)
/*    2b314:	0fc55dfc */ 	jal	func0f1577f0
/*    2b318:	e7b20094 */ 	swc1	$f18,0x94($sp)
/*    2b31c:	4616003c */ 	c.lt.s	$f0,$f22
/*    2b320:	00000000 */ 	nop
/*    2b324:	4502001a */ 	bc1fl	.L0002b390
/*    2b328:	02609025 */ 	or	$s2,$s3,$zero
/*    2b32c:	12c00009 */ 	beqz	$s6,.L0002b354
/*    2b330:	00000000 */ 	nop
/*    2b334:	c6a20004 */ 	lwc1	$f2,0x4($s5)
/*    2b338:	c6840004 */ 	lwc1	$f4,0x4($s4)
/*    2b33c:	c7aa0104 */ 	lwc1	$f10,0x104($sp)
/*    2b340:	46022181 */ 	sub.s	$f6,$f4,$f2
/*    2b344:	46003202 */ 	mul.s	$f8,$f6,$f0
/*    2b348:	46024500 */ 	add.s	$f20,$f8,$f2
/*    2b34c:	461ea600 */ 	add.s	$f24,$f20,$f30
/*    2b350:	460aa500 */ 	add.s	$f20,$f20,$f10
.L0002b354:
/*    2b354:	52c0000a */ 	beqzl	$s6,.L0002b380
/*    2b358:	24180001 */ 	addiu	$t8,$zero,0x1
/*    2b35c:	4614d03e */ 	c.le.s	$f26,$f20
/*    2b360:	00000000 */ 	nop
/*    2b364:	4503000a */ 	bc1tl	.L0002b390
/*    2b368:	02609025 */ 	or	$s2,$s3,$zero
/*    2b36c:	461cc03e */ 	c.le.s	$f24,$f28
/*    2b370:	00000000 */ 	nop
/*    2b374:	45030006 */ 	bc1tl	.L0002b390
/*    2b378:	02609025 */ 	or	$s2,$s3,$zero
/*    2b37c:	24180001 */ 	addiu	$t8,$zero,0x1
.L0002b380:
/*    2b380:	afb800dc */ 	sw	$t8,0xdc($sp)
/*    2b384:	46000586 */ 	mov.s	$f22,$f0
/*    2b388:	afb200c0 */ 	sw	$s2,0xc0($sp)
/*    2b38c:	02609025 */ 	or	$s2,$s3,$zero
.L0002b390:
/*    2b390:	1677ffaf */ 	bne	$s3,$s7,.L0002b250
/*    2b394:	2631000c */ 	addiu	$s1,$s1,0xc
/*    2b398:	e7b800bc */ 	swc1	$f24,0xbc($sp)
/*    2b39c:	e7b400b8 */ 	swc1	$f20,0xb8($sp)
.L0002b3a0:
/*    2b3a0:	8fb900dc */ 	lw	$t9,0xdc($sp)
/*    2b3a4:	8fa800e8 */ 	lw	$t0,0xe8($sp)
/*    2b3a8:	8fa900dc */ 	lw	$t1,0xdc($sp)
/*    2b3ac:	1320003c */ 	beqz	$t9,.L0002b4a0
/*    2b3b0:	00000000 */ 	nop
/*    2b3b4:	c5100000 */ 	lwc1	$f16,0x0($t0)
/*    2b3b8:	c6a40000 */ 	lwc1	$f4,0x0($s5)
/*    2b3bc:	8fa200f0 */ 	lw	$v0,0xf0($sp)
/*    2b3c0:	46168482 */ 	mul.s	$f18,$f16,$f22
/*    2b3c4:	8fa600f4 */ 	lw	$a2,0xf4($sp)
/*    2b3c8:	46049180 */ 	add.s	$f6,$f18,$f4
/*    2b3cc:	e4460000 */ 	swc1	$f6,0x0($v0)
/*    2b3d0:	8fa900e8 */ 	lw	$t1,0xe8($sp)
/*    2b3d4:	c6b00004 */ 	lwc1	$f16,0x4($s5)
/*    2b3d8:	c5280004 */ 	lwc1	$f8,0x4($t1)
/*    2b3dc:	46164282 */ 	mul.s	$f10,$f8,$f22
/*    2b3e0:	46105480 */ 	add.s	$f18,$f10,$f16
/*    2b3e4:	e4520004 */ 	swc1	$f18,0x4($v0)
/*    2b3e8:	8fae00e8 */ 	lw	$t6,0xe8($sp)
/*    2b3ec:	c6a80008 */ 	lwc1	$f8,0x8($s5)
/*    2b3f0:	c5c40008 */ 	lwc1	$f4,0x8($t6)
/*    2b3f4:	46162182 */ 	mul.s	$f6,$f4,$f22
/*    2b3f8:	46083280 */ 	add.s	$f10,$f6,$f8
/*    2b3fc:	10c00045 */ 	beqz	$a2,.L0002b514
/*    2b400:	e44a0008 */ 	swc1	$f10,0x8($v0)
/*    2b404:	8fa300f8 */ 	lw	$v1,0xf8($sp)
/*    2b408:	8fab00c0 */ 	lw	$t3,0xc0($sp)
/*    2b40c:	10600041 */ 	beqz	$v1,.L0002b514
/*    2b410:	000b6880 */ 	sll	$t5,$t3,0x2
/*    2b414:	8faa00ec */ 	lw	$t2,0xec($sp)
/*    2b418:	01ab6823 */ 	subu	$t5,$t5,$t3
/*    2b41c:	000d6880 */ 	sll	$t5,$t5,0x2
/*    2b420:	014d2021 */ 	addu	$a0,$t2,$t5
/*    2b424:	c4900010 */ 	lwc1	$f16,0x10($a0)
/*    2b428:	e4d00000 */ 	swc1	$f16,0x0($a2)
/*    2b42c:	c4520004 */ 	lwc1	$f18,0x4($v0)
/*    2b430:	e4d20004 */ 	swc1	$f18,0x4($a2)
/*    2b434:	c4840018 */ 	lwc1	$f4,0x18($a0)
/*    2b438:	e4c40008 */ 	swc1	$f4,0x8($a2)
/*    2b43c:	8faf00c0 */ 	lw	$t7,0xc0($sp)
/*    2b440:	8fac00ec */ 	lw	$t4,0xec($sp)
/*    2b444:	25f80001 */ 	addiu	$t8,$t7,0x1
/*    2b448:	0317001a */ 	div	$zero,$t8,$s7
/*    2b44c:	0000c810 */ 	mfhi	$t9
/*    2b450:	00194080 */ 	sll	$t0,$t9,0x2
/*    2b454:	01194023 */ 	subu	$t0,$t0,$t9
/*    2b458:	00084080 */ 	sll	$t0,$t0,0x2
/*    2b45c:	01882821 */ 	addu	$a1,$t4,$t0
/*    2b460:	c4a60010 */ 	lwc1	$f6,0x10($a1)
/*    2b464:	16e00002 */ 	bnez	$s7,.L0002b470
/*    2b468:	00000000 */ 	nop
/*    2b46c:	0007000d */ 	break	0x7
.L0002b470:
/*    2b470:	2401ffff */ 	addiu	$at,$zero,-1
/*    2b474:	16e10004 */ 	bne	$s7,$at,.L0002b488
/*    2b478:	3c018000 */ 	lui	$at,0x8000
/*    2b47c:	17010002 */ 	bne	$t8,$at,.L0002b488
/*    2b480:	00000000 */ 	nop
/*    2b484:	0006000d */ 	break	0x6
.L0002b488:
/*    2b488:	e4660000 */ 	swc1	$f6,0x0($v1)
/*    2b48c:	c4480004 */ 	lwc1	$f8,0x4($v0)
/*    2b490:	e4680004 */ 	swc1	$f8,0x4($v1)
/*    2b494:	c4aa0018 */ 	lwc1	$f10,0x18($a1)
/*    2b498:	1000001e */ 	b	.L0002b514
/*    2b49c:	e46a0008 */ 	swc1	$f10,0x8($v1)
.L0002b4a0:
/*    2b4a0:	1520001c */ 	bnez	$t1,.L0002b514
/*    2b4a4:	8fae00c8 */ 	lw	$t6,0xc8($sp)
/*    2b4a8:	11c0001a */ 	beqz	$t6,.L0002b514
/*    2b4ac:	8fa200f0 */ 	lw	$v0,0xf0($sp)
/*    2b4b0:	240b0001 */ 	addiu	$t3,$zero,0x1
/*    2b4b4:	afab00dc */ 	sw	$t3,0xdc($sp)
/*    2b4b8:	c6b00000 */ 	lwc1	$f16,0x0($s5)
/*    2b4bc:	8fa600f4 */ 	lw	$a2,0xf4($sp)
/*    2b4c0:	e4500000 */ 	swc1	$f16,0x0($v0)
/*    2b4c4:	c6b20004 */ 	lwc1	$f18,0x4($s5)
/*    2b4c8:	e4520004 */ 	swc1	$f18,0x4($v0)
/*    2b4cc:	c6a40008 */ 	lwc1	$f4,0x8($s5)
/*    2b4d0:	10c00010 */ 	beqz	$a2,.L0002b514
/*    2b4d4:	e4440008 */ 	swc1	$f4,0x8($v0)
/*    2b4d8:	8fa300f8 */ 	lw	$v1,0xf8($sp)
/*    2b4dc:	5060000e */ 	beqzl	$v1,.L0002b518
/*    2b4e0:	8fbf007c */ 	lw	$ra,0x7c($sp)
/*    2b4e4:	c6a60000 */ 	lwc1	$f6,0x0($s5)
/*    2b4e8:	e4c60000 */ 	swc1	$f6,0x0($a2)
/*    2b4ec:	c6a80004 */ 	lwc1	$f8,0x4($s5)
/*    2b4f0:	e4c80004 */ 	swc1	$f8,0x4($a2)
/*    2b4f4:	c6aa0008 */ 	lwc1	$f10,0x8($s5)
/*    2b4f8:	e4ca0008 */ 	swc1	$f10,0x8($a2)
/*    2b4fc:	c6b00000 */ 	lwc1	$f16,0x0($s5)
/*    2b500:	e4700000 */ 	swc1	$f16,0x0($v1)
/*    2b504:	c6b20004 */ 	lwc1	$f18,0x4($s5)
/*    2b508:	e4720004 */ 	swc1	$f18,0x4($v1)
/*    2b50c:	c6a40008 */ 	lwc1	$f4,0x8($s5)
/*    2b510:	e4640008 */ 	swc1	$f4,0x8($v1)
.L0002b514:
/*    2b514:	8fbf007c */ 	lw	$ra,0x7c($sp)
.L0002b518:
/*    2b518:	8fa200dc */ 	lw	$v0,0xdc($sp)
/*    2b51c:	d7b40028 */ 	ldc1	$f20,0x28($sp)
/*    2b520:	d7b60030 */ 	ldc1	$f22,0x30($sp)
/*    2b524:	d7b80038 */ 	ldc1	$f24,0x38($sp)
/*    2b528:	d7ba0040 */ 	ldc1	$f26,0x40($sp)
/*    2b52c:	d7bc0048 */ 	ldc1	$f28,0x48($sp)
/*    2b530:	d7be0050 */ 	ldc1	$f30,0x50($sp)
/*    2b534:	8fb00058 */ 	lw	$s0,0x58($sp)
/*    2b538:	8fb1005c */ 	lw	$s1,0x5c($sp)
/*    2b53c:	8fb20060 */ 	lw	$s2,0x60($sp)
/*    2b540:	8fb30064 */ 	lw	$s3,0x64($sp)
/*    2b544:	8fb40068 */ 	lw	$s4,0x68($sp)
/*    2b548:	8fb5006c */ 	lw	$s5,0x6c($sp)
/*    2b54c:	8fb60070 */ 	lw	$s6,0x70($sp)
/*    2b550:	8fb70074 */ 	lw	$s7,0x74($sp)
/*    2b554:	8fbe0078 */ 	lw	$s8,0x78($sp)
/*    2b558:	03e00008 */ 	jr	$ra
/*    2b55c:	27bd00e0 */ 	addiu	$sp,$sp,0xe0
);

GLOBAL_ASM(
glabel func0002b560
/*    2b560:	27bdff30 */ 	addiu	$sp,$sp,-208
/*    2b564:	afb7006c */ 	sw	$s7,0x6c($sp)
/*    2b568:	8fb700ec */ 	lw	$s7,0xec($sp)
/*    2b56c:	f7b60030 */ 	sdc1	$f22,0x30($sp)
/*    2b570:	afbf0074 */ 	sw	$ra,0x74($sp)
/*    2b574:	afbe0070 */ 	sw	$s8,0x70($sp)
/*    2b578:	afb60068 */ 	sw	$s6,0x68($sp)
/*    2b57c:	afb50064 */ 	sw	$s5,0x64($sp)
/*    2b580:	afb40060 */ 	sw	$s4,0x60($sp)
/*    2b584:	afb3005c */ 	sw	$s3,0x5c($sp)
/*    2b588:	afb20058 */ 	sw	$s2,0x58($sp)
/*    2b58c:	afb10054 */ 	sw	$s1,0x54($sp)
/*    2b590:	afb00050 */ 	sw	$s0,0x50($sp)
/*    2b594:	f7bc0048 */ 	sdc1	$f28,0x48($sp)
/*    2b598:	f7ba0040 */ 	sdc1	$f26,0x40($sp)
/*    2b59c:	f7b80038 */ 	sdc1	$f24,0x38($sp)
/*    2b5a0:	f7b40028 */ 	sdc1	$f20,0x28($sp)
/*    2b5a4:	afa600d8 */ 	sw	$a2,0xd8($sp)
/*    2b5a8:	afa000cc */ 	sw	$zero,0xcc($sp)
/*    2b5ac:	3c013f80 */ 	lui	$at,0x3f80
/*    2b5b0:	90fe0001 */ 	lbu	$s8,0x1($a3)
/*    2b5b4:	240e0001 */ 	addiu	$t6,$zero,0x1
/*    2b5b8:	4481b000 */ 	mtc1	$at,$f22
/*    2b5bc:	00a0a025 */ 	or	$s4,$a1,$zero
/*    2b5c0:	0080a825 */ 	or	$s5,$a0,$zero
/*    2b5c4:	00e0b025 */ 	or	$s6,$a3,$zero
/*    2b5c8:	12e0001e */ 	beqz	$s7,.L0002b644
/*    2b5cc:	afae00b8 */ 	sw	$t6,0xb8($sp)
/*    2b5d0:	c7ba00f0 */ 	lwc1	$f26,0xf0($sp)
/*    2b5d4:	c4820004 */ 	lwc1	$f2,0x4($a0)
/*    2b5d8:	c6c00008 */ 	lwc1	$f0,0x8($s6)
/*    2b5dc:	c7bc00f4 */ 	lwc1	$f28,0xf4($sp)
/*    2b5e0:	461a1100 */ 	add.s	$f4,$f2,$f26
/*    2b5e4:	4604003e */ 	c.le.s	$f0,$f4
/*    2b5e8:	00000000 */ 	nop
/*    2b5ec:	45020009 */ 	bc1fl	.L0002b614
/*    2b5f0:	c7bc00f4 */ 	lwc1	$f28,0xf4($sp)
/*    2b5f4:	c6880004 */ 	lwc1	$f8,0x4($s4)
/*    2b5f8:	c6c60004 */ 	lwc1	$f6,0x4($s6)
/*    2b5fc:	461c4280 */ 	add.s	$f10,$f8,$f28
/*    2b600:	4606503e */ 	c.le.s	$f10,$f6
/*    2b604:	00000000 */ 	nop
/*    2b608:	4503000f */ 	bc1tl	.L0002b648
/*    2b60c:	c7ba00f0 */ 	lwc1	$f26,0xf0($sp)
/*    2b610:	c7bc00f4 */ 	lwc1	$f28,0xf4($sp)
.L0002b614:
/*    2b614:	c6d00004 */ 	lwc1	$f16,0x4($s6)
/*    2b618:	461c1480 */ 	add.s	$f18,$f2,$f28
/*    2b61c:	4610903e */ 	c.le.s	$f18,$f16
/*    2b620:	00000000 */ 	nop
/*    2b624:	450200ba */ 	bc1fl	.L0002b910
/*    2b628:	8fbf0074 */ 	lw	$ra,0x74($sp)
/*    2b62c:	c6840004 */ 	lwc1	$f4,0x4($s4)
/*    2b630:	461a2200 */ 	add.s	$f8,$f4,$f26
/*    2b634:	4608003e */ 	c.le.s	$f0,$f8
/*    2b638:	00000000 */ 	nop
/*    2b63c:	450200b4 */ 	bc1fl	.L0002b910
/*    2b640:	8fbf0074 */ 	lw	$ra,0x74($sp)
.L0002b644:
/*    2b644:	c7ba00f0 */ 	lwc1	$f26,0xf0($sp)
.L0002b648:
/*    2b648:	c7bc00f4 */ 	lwc1	$f28,0xf4($sp)
/*    2b64c:	1bc00057 */ 	blez	$s8,.L0002b7ac
/*    2b650:	00009025 */ 	or	$s2,$zero,$zero
/*    2b654:	02c08825 */ 	or	$s1,$s6,$zero
/*    2b658:	c7b800ac */ 	lwc1	$f24,0xac($sp)
/*    2b65c:	c7b400a8 */ 	lwc1	$f20,0xa8($sp)
.L0002b660:
/*    2b660:	26530001 */ 	addiu	$s3,$s2,0x1
/*    2b664:	027e001a */ 	div	$zero,$s3,$s8
/*    2b668:	00007810 */ 	mfhi	$t7
/*    2b66c:	000fc0c0 */ 	sll	$t8,$t7,0x3
/*    2b670:	02d88021 */ 	addu	$s0,$s6,$t8
/*    2b674:	c606000c */ 	lwc1	$f6,0xc($s0)
/*    2b678:	8e26000c */ 	lw	$a2,0xc($s1)
/*    2b67c:	8e270010 */ 	lw	$a3,0x10($s1)
/*    2b680:	e7a60010 */ 	swc1	$f6,0x10($sp)
/*    2b684:	c60a0010 */ 	lwc1	$f10,0x10($s0)
/*    2b688:	27b900b8 */ 	addiu	$t9,$sp,0xb8
/*    2b68c:	afb90018 */ 	sw	$t9,0x18($sp)
/*    2b690:	02a02025 */ 	or	$a0,$s5,$zero
/*    2b694:	02802825 */ 	or	$a1,$s4,$zero
/*    2b698:	17c00002 */ 	bnez	$s8,.L0002b6a4
/*    2b69c:	00000000 */ 	nop
/*    2b6a0:	0007000d */ 	break	0x7
.L0002b6a4:
/*    2b6a4:	2401ffff */ 	addiu	$at,$zero,-1
/*    2b6a8:	17c10004 */ 	bne	$s8,$at,.L0002b6bc
/*    2b6ac:	3c018000 */ 	lui	$at,0x8000
/*    2b6b0:	16610002 */ 	bne	$s3,$at,.L0002b6bc
/*    2b6b4:	00000000 */ 	nop
/*    2b6b8:	0006000d */ 	break	0x6
.L0002b6bc:
/*    2b6bc:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*    2b6c0:	0c009536 */ 	jal	func000254d8
/*    2b6c4:	00000000 */ 	nop
/*    2b6c8:	50400034 */ 	beqzl	$v0,.L0002b79c
/*    2b6cc:	02609025 */ 	or	$s2,$s3,$zero
/*    2b6d0:	c6b00000 */ 	lwc1	$f16,0x0($s5)
/*    2b6d4:	27a400a0 */ 	addiu	$a0,$sp,0xa0
/*    2b6d8:	27a50098 */ 	addiu	$a1,$sp,0x98
/*    2b6dc:	e7b000a0 */ 	swc1	$f16,0xa0($sp)
/*    2b6e0:	c6b20008 */ 	lwc1	$f18,0x8($s5)
/*    2b6e4:	27a60090 */ 	addiu	$a2,$sp,0x90
/*    2b6e8:	27a70088 */ 	addiu	$a3,$sp,0x88
/*    2b6ec:	e7b200a4 */ 	swc1	$f18,0xa4($sp)
/*    2b6f0:	c6840000 */ 	lwc1	$f4,0x0($s4)
/*    2b6f4:	e7a40098 */ 	swc1	$f4,0x98($sp)
/*    2b6f8:	c6880008 */ 	lwc1	$f8,0x8($s4)
/*    2b6fc:	e7a8009c */ 	swc1	$f8,0x9c($sp)
/*    2b700:	c626000c */ 	lwc1	$f6,0xc($s1)
/*    2b704:	e7a60090 */ 	swc1	$f6,0x90($sp)
/*    2b708:	c62a0010 */ 	lwc1	$f10,0x10($s1)
/*    2b70c:	e7aa0094 */ 	swc1	$f10,0x94($sp)
/*    2b710:	c610000c */ 	lwc1	$f16,0xc($s0)
/*    2b714:	e7b00088 */ 	swc1	$f16,0x88($sp)
/*    2b718:	c6120010 */ 	lwc1	$f18,0x10($s0)
/*    2b71c:	0fc55dfc */ 	jal	func0f1577f0
/*    2b720:	e7b2008c */ 	swc1	$f18,0x8c($sp)
/*    2b724:	4616003c */ 	c.lt.s	$f0,$f22
/*    2b728:	00000000 */ 	nop
/*    2b72c:	4502001b */ 	bc1fl	.L0002b79c
/*    2b730:	02609025 */ 	or	$s2,$s3,$zero
/*    2b734:	12e00008 */ 	beqz	$s7,.L0002b758
/*    2b738:	00000000 */ 	nop
/*    2b73c:	c6a20004 */ 	lwc1	$f2,0x4($s5)
/*    2b740:	c6840004 */ 	lwc1	$f4,0x4($s4)
/*    2b744:	46022201 */ 	sub.s	$f8,$f4,$f2
/*    2b748:	46004182 */ 	mul.s	$f6,$f8,$f0
/*    2b74c:	46023500 */ 	add.s	$f20,$f6,$f2
/*    2b750:	461aa600 */ 	add.s	$f24,$f20,$f26
/*    2b754:	461ca500 */ 	add.s	$f20,$f20,$f28
.L0002b758:
/*    2b758:	52e0000c */ 	beqzl	$s7,.L0002b78c
/*    2b75c:	24080001 */ 	addiu	$t0,$zero,0x1
/*    2b760:	c6ca0004 */ 	lwc1	$f10,0x4($s6)
/*    2b764:	4614503e */ 	c.le.s	$f10,$f20
/*    2b768:	00000000 */ 	nop
/*    2b76c:	4503000b */ 	bc1tl	.L0002b79c
/*    2b770:	02609025 */ 	or	$s2,$s3,$zero
/*    2b774:	c6d00008 */ 	lwc1	$f16,0x8($s6)
/*    2b778:	4610c03e */ 	c.le.s	$f24,$f16
/*    2b77c:	00000000 */ 	nop
/*    2b780:	45030006 */ 	bc1tl	.L0002b79c
/*    2b784:	02609025 */ 	or	$s2,$s3,$zero
/*    2b788:	24080001 */ 	addiu	$t0,$zero,0x1
.L0002b78c:
/*    2b78c:	afa800cc */ 	sw	$t0,0xcc($sp)
/*    2b790:	46000586 */ 	mov.s	$f22,$f0
/*    2b794:	afb200b0 */ 	sw	$s2,0xb0($sp)
/*    2b798:	02609025 */ 	or	$s2,$s3,$zero
.L0002b79c:
/*    2b79c:	167effb0 */ 	bne	$s3,$s8,.L0002b660
/*    2b7a0:	26310008 */ 	addiu	$s1,$s1,0x8
/*    2b7a4:	e7b800ac */ 	swc1	$f24,0xac($sp)
/*    2b7a8:	e7b400a8 */ 	swc1	$f20,0xa8($sp)
.L0002b7ac:
/*    2b7ac:	8fa900cc */ 	lw	$t1,0xcc($sp)
/*    2b7b0:	8faa00d8 */ 	lw	$t2,0xd8($sp)
/*    2b7b4:	51200037 */ 	beqzl	$t1,.L0002b894
/*    2b7b8:	8fa900cc */ 	lw	$t1,0xcc($sp)
/*    2b7bc:	c5520000 */ 	lwc1	$f18,0x0($t2)
/*    2b7c0:	c6a80000 */ 	lwc1	$f8,0x0($s5)
/*    2b7c4:	8fa200e0 */ 	lw	$v0,0xe0($sp)
/*    2b7c8:	46169102 */ 	mul.s	$f4,$f18,$f22
/*    2b7cc:	8fa600e4 */ 	lw	$a2,0xe4($sp)
/*    2b7d0:	46082180 */ 	add.s	$f6,$f4,$f8
/*    2b7d4:	e4460000 */ 	swc1	$f6,0x0($v0)
/*    2b7d8:	8fab00d8 */ 	lw	$t3,0xd8($sp)
/*    2b7dc:	c6b20004 */ 	lwc1	$f18,0x4($s5)
/*    2b7e0:	c56a0004 */ 	lwc1	$f10,0x4($t3)
/*    2b7e4:	46165402 */ 	mul.s	$f16,$f10,$f22
/*    2b7e8:	46128100 */ 	add.s	$f4,$f16,$f18
/*    2b7ec:	e4440004 */ 	swc1	$f4,0x4($v0)
/*    2b7f0:	8fac00d8 */ 	lw	$t4,0xd8($sp)
/*    2b7f4:	c6aa0008 */ 	lwc1	$f10,0x8($s5)
/*    2b7f8:	c5880008 */ 	lwc1	$f8,0x8($t4)
/*    2b7fc:	46164182 */ 	mul.s	$f6,$f8,$f22
/*    2b800:	460a3400 */ 	add.s	$f16,$f6,$f10
/*    2b804:	10c00041 */ 	beqz	$a2,.L0002b90c
/*    2b808:	e4500008 */ 	swc1	$f16,0x8($v0)
/*    2b80c:	8fa300e8 */ 	lw	$v1,0xe8($sp)
/*    2b810:	8fad00b0 */ 	lw	$t5,0xb0($sp)
/*    2b814:	1060003d */ 	beqz	$v1,.L0002b90c
/*    2b818:	000d70c0 */ 	sll	$t6,$t5,0x3
/*    2b81c:	02ce2021 */ 	addu	$a0,$s6,$t6
/*    2b820:	c492000c */ 	lwc1	$f18,0xc($a0)
/*    2b824:	e4d20000 */ 	swc1	$f18,0x0($a2)
/*    2b828:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*    2b82c:	e4c40004 */ 	swc1	$f4,0x4($a2)
/*    2b830:	c4880010 */ 	lwc1	$f8,0x10($a0)
/*    2b834:	e4c80008 */ 	swc1	$f8,0x8($a2)
/*    2b838:	8faf00b0 */ 	lw	$t7,0xb0($sp)
/*    2b83c:	25f80001 */ 	addiu	$t8,$t7,0x1
/*    2b840:	031e001a */ 	div	$zero,$t8,$s8
/*    2b844:	0000c810 */ 	mfhi	$t9
/*    2b848:	001940c0 */ 	sll	$t0,$t9,0x3
/*    2b84c:	02c82821 */ 	addu	$a1,$s6,$t0
/*    2b850:	c4a6000c */ 	lwc1	$f6,0xc($a1)
/*    2b854:	17c00002 */ 	bnez	$s8,.L0002b860
/*    2b858:	00000000 */ 	nop
/*    2b85c:	0007000d */ 	break	0x7
.L0002b860:
/*    2b860:	2401ffff */ 	addiu	$at,$zero,-1
/*    2b864:	17c10004 */ 	bne	$s8,$at,.L0002b878
/*    2b868:	3c018000 */ 	lui	$at,0x8000
/*    2b86c:	17010002 */ 	bne	$t8,$at,.L0002b878
/*    2b870:	00000000 */ 	nop
/*    2b874:	0006000d */ 	break	0x6
.L0002b878:
/*    2b878:	e4660000 */ 	swc1	$f6,0x0($v1)
/*    2b87c:	c44a0004 */ 	lwc1	$f10,0x4($v0)
/*    2b880:	e46a0004 */ 	swc1	$f10,0x4($v1)
/*    2b884:	c4b00010 */ 	lwc1	$f16,0x10($a1)
/*    2b888:	10000020 */ 	b	.L0002b90c
/*    2b88c:	e4700008 */ 	swc1	$f16,0x8($v1)
/*    2b890:	8fa900cc */ 	lw	$t1,0xcc($sp)
.L0002b894:
/*    2b894:	8faa00b8 */ 	lw	$t2,0xb8($sp)
/*    2b898:	5520001d */ 	bnezl	$t1,.L0002b910
/*    2b89c:	8fbf0074 */ 	lw	$ra,0x74($sp)
/*    2b8a0:	1140001a */ 	beqz	$t2,.L0002b90c
/*    2b8a4:	8fa200e0 */ 	lw	$v0,0xe0($sp)
/*    2b8a8:	240b0001 */ 	addiu	$t3,$zero,0x1
/*    2b8ac:	afab00cc */ 	sw	$t3,0xcc($sp)
/*    2b8b0:	c6b20000 */ 	lwc1	$f18,0x0($s5)
/*    2b8b4:	8fa600e4 */ 	lw	$a2,0xe4($sp)
/*    2b8b8:	e4520000 */ 	swc1	$f18,0x0($v0)
/*    2b8bc:	c6a40004 */ 	lwc1	$f4,0x4($s5)
/*    2b8c0:	e4440004 */ 	swc1	$f4,0x4($v0)
/*    2b8c4:	c6a80008 */ 	lwc1	$f8,0x8($s5)
/*    2b8c8:	10c00010 */ 	beqz	$a2,.L0002b90c
/*    2b8cc:	e4480008 */ 	swc1	$f8,0x8($v0)
/*    2b8d0:	8fa300e8 */ 	lw	$v1,0xe8($sp)
/*    2b8d4:	5060000e */ 	beqzl	$v1,.L0002b910
/*    2b8d8:	8fbf0074 */ 	lw	$ra,0x74($sp)
/*    2b8dc:	c6a60000 */ 	lwc1	$f6,0x0($s5)
/*    2b8e0:	e4c60000 */ 	swc1	$f6,0x0($a2)
/*    2b8e4:	c6aa0004 */ 	lwc1	$f10,0x4($s5)
/*    2b8e8:	e4ca0004 */ 	swc1	$f10,0x4($a2)
/*    2b8ec:	c6b00008 */ 	lwc1	$f16,0x8($s5)
/*    2b8f0:	e4d00008 */ 	swc1	$f16,0x8($a2)
/*    2b8f4:	c6b20000 */ 	lwc1	$f18,0x0($s5)
/*    2b8f8:	e4720000 */ 	swc1	$f18,0x0($v1)
/*    2b8fc:	c6a40004 */ 	lwc1	$f4,0x4($s5)
/*    2b900:	e4640004 */ 	swc1	$f4,0x4($v1)
/*    2b904:	c6a80008 */ 	lwc1	$f8,0x8($s5)
/*    2b908:	e4680008 */ 	swc1	$f8,0x8($v1)
.L0002b90c:
/*    2b90c:	8fbf0074 */ 	lw	$ra,0x74($sp)
.L0002b910:
/*    2b910:	8fa200cc */ 	lw	$v0,0xcc($sp)
/*    2b914:	d7b40028 */ 	ldc1	$f20,0x28($sp)
/*    2b918:	d7b60030 */ 	ldc1	$f22,0x30($sp)
/*    2b91c:	d7b80038 */ 	ldc1	$f24,0x38($sp)
/*    2b920:	d7ba0040 */ 	ldc1	$f26,0x40($sp)
/*    2b924:	d7bc0048 */ 	ldc1	$f28,0x48($sp)
/*    2b928:	8fb00050 */ 	lw	$s0,0x50($sp)
/*    2b92c:	8fb10054 */ 	lw	$s1,0x54($sp)
/*    2b930:	8fb20058 */ 	lw	$s2,0x58($sp)
/*    2b934:	8fb3005c */ 	lw	$s3,0x5c($sp)
/*    2b938:	8fb40060 */ 	lw	$s4,0x60($sp)
/*    2b93c:	8fb50064 */ 	lw	$s5,0x64($sp)
/*    2b940:	8fb60068 */ 	lw	$s6,0x68($sp)
/*    2b944:	8fb7006c */ 	lw	$s7,0x6c($sp)
/*    2b948:	8fbe0070 */ 	lw	$s8,0x70($sp)
/*    2b94c:	03e00008 */ 	jr	$ra
/*    2b950:	27bd00d0 */ 	addiu	$sp,$sp,0xd0
);

GLOBAL_ASM(
glabel func0002b954
/*    2b954:	27bdff80 */ 	addiu	$sp,$sp,-128
/*    2b958:	afbf0034 */ 	sw	$ra,0x34($sp)
/*    2b95c:	afb10030 */ 	sw	$s1,0x30($sp)
/*    2b960:	afb0002c */ 	sw	$s0,0x2c($sp)
/*    2b964:	afa60088 */ 	sw	$a2,0x88($sp)
/*    2b968:	afa7008c */ 	sw	$a3,0x8c($sp)
/*    2b96c:	afa0007c */ 	sw	$zero,0x7c($sp)
/*    2b970:	8faf009c */ 	lw	$t7,0x9c($sp)
/*    2b974:	c4e40014 */ 	lwc1	$f4,0x14($a3)
/*    2b978:	c4f0000c */ 	lwc1	$f16,0xc($a3)
/*    2b97c:	c4f20010 */ 	lwc1	$f18,0x10($a3)
/*    2b980:	00808025 */ 	or	$s0,$a0,$zero
/*    2b984:	00a08825 */ 	or	$s1,$a1,$zero
/*    2b988:	11e00020 */ 	beqz	$t7,.L0002ba0c
/*    2b98c:	e7a40068 */ 	swc1	$f4,0x68($sp)
/*    2b990:	c4800004 */ 	lwc1	$f0,0x4($a0)
/*    2b994:	c7a600a0 */ 	lwc1	$f6,0xa0($sp)
/*    2b998:	c4e20008 */ 	lwc1	$f2,0x8($a3)
/*    2b99c:	46060200 */ 	add.s	$f8,$f0,$f6
/*    2b9a0:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*    2b9a4:	4608103e */ 	c.le.s	$f2,$f8
/*    2b9a8:	00000000 */ 	nop
/*    2b9ac:	45020009 */ 	bc1fl	.L0002b9d4
/*    2b9b0:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*    2b9b4:	c4a40004 */ 	lwc1	$f4,0x4($a1)
/*    2b9b8:	c4ea0004 */ 	lwc1	$f10,0x4($a3)
/*    2b9bc:	46062200 */ 	add.s	$f8,$f4,$f6
/*    2b9c0:	460a403e */ 	c.le.s	$f8,$f10
/*    2b9c4:	00000000 */ 	nop
/*    2b9c8:	45030011 */ 	bc1tl	.L0002ba10
/*    2b9cc:	c60c0000 */ 	lwc1	$f12,0x0($s0)
/*    2b9d0:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
.L0002b9d4:
/*    2b9d4:	8fb8008c */ 	lw	$t8,0x8c($sp)
/*    2b9d8:	46060280 */ 	add.s	$f10,$f0,$f6
/*    2b9dc:	c7040004 */ 	lwc1	$f4,0x4($t8)
/*    2b9e0:	c7a600a0 */ 	lwc1	$f6,0xa0($sp)
/*    2b9e4:	4604503e */ 	c.le.s	$f10,$f4
/*    2b9e8:	00000000 */ 	nop
/*    2b9ec:	450200c0 */ 	bc1fl	.L0002bcf0
/*    2b9f0:	8fbf0034 */ 	lw	$ra,0x34($sp)
/*    2b9f4:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*    2b9f8:	46064100 */ 	add.s	$f4,$f8,$f6
/*    2b9fc:	4604103e */ 	c.le.s	$f2,$f4
/*    2ba00:	00000000 */ 	nop
/*    2ba04:	450200ba */ 	bc1fl	.L0002bcf0
/*    2ba08:	8fbf0034 */ 	lw	$ra,0x34($sp)
.L0002ba0c:
/*    2ba0c:	c60c0000 */ 	lwc1	$f12,0x0($s0)
.L0002ba10:
/*    2ba10:	c60e0008 */ 	lwc1	$f14,0x8($s0)
/*    2ba14:	8e260000 */ 	lw	$a2,0x0($s1)
/*    2ba18:	8e270008 */ 	lw	$a3,0x8($s1)
/*    2ba1c:	e7b2006c */ 	swc1	$f18,0x6c($sp)
/*    2ba20:	e7b00070 */ 	swc1	$f16,0x70($sp)
/*    2ba24:	e7b20014 */ 	swc1	$f18,0x14($sp)
/*    2ba28:	0c009595 */ 	jal	func00025654
/*    2ba2c:	e7b00010 */ 	swc1	$f16,0x10($sp)
/*    2ba30:	44805000 */ 	mtc1	$zero,$f10
/*    2ba34:	46000486 */ 	mov.s	$f18,$f0
/*    2ba38:	c7a80068 */ 	lwc1	$f8,0x68($sp)
/*    2ba3c:	460a003c */ 	c.lt.s	$f0,$f10
/*    2ba40:	8fa60070 */ 	lw	$a2,0x70($sp)
/*    2ba44:	8fa7006c */ 	lw	$a3,0x6c($sp)
/*    2ba48:	45020003 */ 	bc1fl	.L0002ba58
/*    2ba4c:	4608903c */ 	c.lt.s	$f18,$f8
/*    2ba50:	46000487 */ 	neg.s	$f18,$f0
/*    2ba54:	4608903c */ 	c.lt.s	$f18,$f8
.L0002ba58:
/*    2ba58:	00000000 */ 	nop
/*    2ba5c:	450200a4 */ 	bc1fl	.L0002bcf0
/*    2ba60:	8fbf0034 */ 	lw	$ra,0x34($sp)
/*    2ba64:	c60c0000 */ 	lwc1	$f12,0x0($s0)
/*    2ba68:	c60e0008 */ 	lwc1	$f14,0x8($s0)
/*    2ba6c:	0c0095c9 */ 	jal	func00025724
/*    2ba70:	e7b20074 */ 	swc1	$f18,0x74($sp)
/*    2ba74:	c7a60068 */ 	lwc1	$f6,0x68($sp)
/*    2ba78:	c7b20074 */ 	lwc1	$f18,0x74($sp)
/*    2ba7c:	8fa60070 */ 	lw	$a2,0x70($sp)
/*    2ba80:	4606003c */ 	c.lt.s	$f0,$f6
/*    2ba84:	8fa7006c */ 	lw	$a3,0x6c($sp)
/*    2ba88:	45030018 */ 	bc1tl	.L0002baec
/*    2ba8c:	c6260000 */ 	lwc1	$f6,0x0($s1)
/*    2ba90:	c62c0000 */ 	lwc1	$f12,0x0($s1)
/*    2ba94:	c62e0008 */ 	lwc1	$f14,0x8($s1)
/*    2ba98:	0c0095c9 */ 	jal	func00025724
/*    2ba9c:	e7b20074 */ 	swc1	$f18,0x74($sp)
/*    2baa0:	c7a40068 */ 	lwc1	$f4,0x68($sp)
/*    2baa4:	c7b20074 */ 	lwc1	$f18,0x74($sp)
/*    2baa8:	c7aa0070 */ 	lwc1	$f10,0x70($sp)
/*    2baac:	4604003c */ 	c.lt.s	$f0,$f4
/*    2bab0:	00000000 */ 	nop
/*    2bab4:	4503000d */ 	bc1tl	.L0002baec
/*    2bab8:	c6260000 */ 	lwc1	$f6,0x0($s1)
/*    2babc:	c7a8006c */ 	lwc1	$f8,0x6c($sp)
/*    2bac0:	c60c0000 */ 	lwc1	$f12,0x0($s0)
/*    2bac4:	c60e0008 */ 	lwc1	$f14,0x8($s0)
/*    2bac8:	8e260000 */ 	lw	$a2,0x0($s1)
/*    2bacc:	8e270008 */ 	lw	$a3,0x8($s1)
/*    2bad0:	e7b20074 */ 	swc1	$f18,0x74($sp)
/*    2bad4:	e7aa0010 */ 	swc1	$f10,0x10($sp)
/*    2bad8:	0c0095dd */ 	jal	func00025774
/*    2badc:	e7a80014 */ 	swc1	$f8,0x14($sp)
/*    2bae0:	10400082 */ 	beqz	$v0,.L0002bcec
/*    2bae4:	c7b20074 */ 	lwc1	$f18,0x74($sp)
/*    2bae8:	c6260000 */ 	lwc1	$f6,0x0($s1)
.L0002baec:
/*    2baec:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*    2baf0:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*    2baf4:	c6080008 */ 	lwc1	$f8,0x8($s0)
/*    2baf8:	46043001 */ 	sub.s	$f0,$f6,$f4
/*    2bafc:	e7b20074 */ 	swc1	$f18,0x74($sp)
/*    2bb00:	46085081 */ 	sub.s	$f2,$f10,$f8
/*    2bb04:	46000182 */ 	mul.s	$f6,$f0,$f0
/*    2bb08:	00000000 */ 	nop
/*    2bb0c:	46021102 */ 	mul.s	$f4,$f2,$f2
/*    2bb10:	0c012974 */ 	jal	sqrtf
/*    2bb14:	46043300 */ 	add.s	$f12,$f6,$f4
/*    2bb18:	44805000 */ 	mtc1	$zero,$f10
/*    2bb1c:	c7b20074 */ 	lwc1	$f18,0x74($sp)
/*    2bb20:	e7a00050 */ 	swc1	$f0,0x50($sp)
/*    2bb24:	4600503c */ 	c.lt.s	$f10,$f0
/*    2bb28:	c7a80070 */ 	lwc1	$f8,0x70($sp)
/*    2bb2c:	45020021 */ 	bc1fl	.L0002bbb4
/*    2bb30:	44801000 */ 	mtc1	$zero,$f2
/*    2bb34:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*    2bb38:	c7a4006c */ 	lwc1	$f4,0x6c($sp)
/*    2bb3c:	c60a0008 */ 	lwc1	$f10,0x8($s0)
/*    2bb40:	46064001 */ 	sub.s	$f0,$f8,$f6
/*    2bb44:	460a2081 */ 	sub.s	$f2,$f4,$f10
/*    2bb48:	46000202 */ 	mul.s	$f8,$f0,$f0
/*    2bb4c:	00000000 */ 	nop
/*    2bb50:	46021182 */ 	mul.s	$f6,$f2,$f2
/*    2bb54:	46064400 */ 	add.s	$f16,$f8,$f6
/*    2bb58:	46129382 */ 	mul.s	$f14,$f18,$f18
/*    2bb5c:	4610703e */ 	c.le.s	$f14,$f16
/*    2bb60:	00000000 */ 	nop
/*    2bb64:	4500000d */ 	bc1f	.L0002bb9c
/*    2bb68:	00000000 */ 	nop
/*    2bb6c:	460e8301 */ 	sub.s	$f12,$f16,$f14
/*    2bb70:	0c012974 */ 	jal	sqrtf
/*    2bb74:	e7ae003c */ 	swc1	$f14,0x3c($sp)
/*    2bb78:	c7a40068 */ 	lwc1	$f4,0x68($sp)
/*    2bb7c:	c7ae003c */ 	lwc1	$f14,0x3c($sp)
/*    2bb80:	e7a00044 */ 	swc1	$f0,0x44($sp)
/*    2bb84:	46042282 */ 	mul.s	$f10,$f4,$f4
/*    2bb88:	0c012974 */ 	jal	sqrtf
/*    2bb8c:	460e5301 */ 	sub.s	$f12,$f10,$f14
/*    2bb90:	c7a80044 */ 	lwc1	$f8,0x44($sp)
/*    2bb94:	10000003 */ 	b	.L0002bba4
/*    2bb98:	46004301 */ 	sub.s	$f12,$f8,$f0
.L0002bb9c:
/*    2bb9c:	44806000 */ 	mtc1	$zero,$f12
/*    2bba0:	00000000 */ 	nop
.L0002bba4:
/*    2bba4:	c7a60050 */ 	lwc1	$f6,0x50($sp)
/*    2bba8:	10000003 */ 	b	.L0002bbb8
/*    2bbac:	46066083 */ 	div.s	$f2,$f12,$f6
/*    2bbb0:	44801000 */ 	mtc1	$zero,$f2
.L0002bbb4:
/*    2bbb4:	00000000 */ 	nop
.L0002bbb8:
/*    2bbb8:	3c013f80 */ 	lui	$at,0x3f80
/*    2bbbc:	44812000 */ 	mtc1	$at,$f4
/*    2bbc0:	8fa2009c */ 	lw	$v0,0x9c($sp)
/*    2bbc4:	4604103c */ 	c.lt.s	$f2,$f4
/*    2bbc8:	00000000 */ 	nop
/*    2bbcc:	45020048 */ 	bc1fl	.L0002bcf0
/*    2bbd0:	8fbf0034 */ 	lw	$ra,0x34($sp)
/*    2bbd4:	1040000c */ 	beqz	$v0,.L0002bc08
/*    2bbd8:	00000000 */ 	nop
/*    2bbdc:	c6000004 */ 	lwc1	$f0,0x4($s0)
/*    2bbe0:	c62a0004 */ 	lwc1	$f10,0x4($s1)
/*    2bbe4:	c7a400a0 */ 	lwc1	$f4,0xa0($sp)
/*    2bbe8:	46005201 */ 	sub.s	$f8,$f10,$f0
/*    2bbec:	46024182 */ 	mul.s	$f6,$f8,$f2
/*    2bbf0:	c7a800a4 */ 	lwc1	$f8,0xa4($sp)
/*    2bbf4:	46003300 */ 	add.s	$f12,$f6,$f0
/*    2bbf8:	46046280 */ 	add.s	$f10,$f12,$f4
/*    2bbfc:	46086300 */ 	add.s	$f12,$f12,$f8
/*    2bc00:	e7aa004c */ 	swc1	$f10,0x4c($sp)
/*    2bc04:	e7ac0048 */ 	swc1	$f12,0x48($sp)
.L0002bc08:
/*    2bc08:	1040000d */ 	beqz	$v0,.L0002bc40
/*    2bc0c:	c7ac0048 */ 	lwc1	$f12,0x48($sp)
/*    2bc10:	8fa2008c */ 	lw	$v0,0x8c($sp)
/*    2bc14:	c7aa004c */ 	lwc1	$f10,0x4c($sp)
/*    2bc18:	c4460004 */ 	lwc1	$f6,0x4($v0)
/*    2bc1c:	460c303e */ 	c.le.s	$f6,$f12
/*    2bc20:	00000000 */ 	nop
/*    2bc24:	45030032 */ 	bc1tl	.L0002bcf0
/*    2bc28:	8fbf0034 */ 	lw	$ra,0x34($sp)
/*    2bc2c:	c4440008 */ 	lwc1	$f4,0x8($v0)
/*    2bc30:	4604503e */ 	c.le.s	$f10,$f4
/*    2bc34:	00000000 */ 	nop
/*    2bc38:	4503002d */ 	bc1tl	.L0002bcf0
/*    2bc3c:	8fbf0034 */ 	lw	$ra,0x34($sp)
.L0002bc40:
/*    2bc40:	8fa40088 */ 	lw	$a0,0x88($sp)
/*    2bc44:	24190001 */ 	addiu	$t9,$zero,0x1
/*    2bc48:	afb9007c */ 	sw	$t9,0x7c($sp)
/*    2bc4c:	c4880000 */ 	lwc1	$f8,0x0($a0)
/*    2bc50:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*    2bc54:	8fa20090 */ 	lw	$v0,0x90($sp)
/*    2bc58:	46024182 */ 	mul.s	$f6,$f8,$f2
/*    2bc5c:	8fa30094 */ 	lw	$v1,0x94($sp)
/*    2bc60:	46043280 */ 	add.s	$f10,$f6,$f4
/*    2bc64:	e44a0000 */ 	swc1	$f10,0x0($v0)
/*    2bc68:	c4880004 */ 	lwc1	$f8,0x4($a0)
/*    2bc6c:	c6040004 */ 	lwc1	$f4,0x4($s0)
/*    2bc70:	46024182 */ 	mul.s	$f6,$f8,$f2
/*    2bc74:	46043280 */ 	add.s	$f10,$f6,$f4
/*    2bc78:	e44a0004 */ 	swc1	$f10,0x4($v0)
/*    2bc7c:	c4880008 */ 	lwc1	$f8,0x8($a0)
/*    2bc80:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*    2bc84:	46024182 */ 	mul.s	$f6,$f8,$f2
/*    2bc88:	46043280 */ 	add.s	$f10,$f6,$f4
/*    2bc8c:	10600017 */ 	beqz	$v1,.L0002bcec
/*    2bc90:	e44a0008 */ 	swc1	$f10,0x8($v0)
/*    2bc94:	8fa40098 */ 	lw	$a0,0x98($sp)
/*    2bc98:	c7ac0070 */ 	lwc1	$f12,0x70($sp)
/*    2bc9c:	c7ae006c */ 	lwc1	$f14,0x6c($sp)
/*    2bca0:	10800012 */ 	beqz	$a0,.L0002bcec
/*    2bca4:	8fa60068 */ 	lw	$a2,0x68($sp)
/*    2bca8:	c6080008 */ 	lwc1	$f8,0x8($s0)
/*    2bcac:	8e070000 */ 	lw	$a3,0x0($s0)
/*    2bcb0:	24680008 */ 	addiu	$t0,$v1,0x8
/*    2bcb4:	24890008 */ 	addiu	$t1,$a0,0x8
/*    2bcb8:	afa90020 */ 	sw	$t1,0x20($sp)
/*    2bcbc:	afa80018 */ 	sw	$t0,0x18($sp)
/*    2bcc0:	afa4001c */ 	sw	$a0,0x1c($sp)
/*    2bcc4:	afa30014 */ 	sw	$v1,0x14($sp)
/*    2bcc8:	0c009612 */ 	jal	func00025848
/*    2bccc:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*    2bcd0:	8fa20090 */ 	lw	$v0,0x90($sp)
/*    2bcd4:	8fa30094 */ 	lw	$v1,0x94($sp)
/*    2bcd8:	8fa40098 */ 	lw	$a0,0x98($sp)
/*    2bcdc:	c4460004 */ 	lwc1	$f6,0x4($v0)
/*    2bce0:	e4660004 */ 	swc1	$f6,0x4($v1)
/*    2bce4:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*    2bce8:	e4840004 */ 	swc1	$f4,0x4($a0)
.L0002bcec:
/*    2bcec:	8fbf0034 */ 	lw	$ra,0x34($sp)
.L0002bcf0:
/*    2bcf0:	8fa2007c */ 	lw	$v0,0x7c($sp)
/*    2bcf4:	8fb0002c */ 	lw	$s0,0x2c($sp)
/*    2bcf8:	8fb10030 */ 	lw	$s1,0x30($sp)
/*    2bcfc:	03e00008 */ 	jr	$ra
/*    2bd00:	27bd0080 */ 	addiu	$sp,$sp,0x80
);

GLOBAL_ASM(
glabel func0002bd04
/*    2bd04:	27bdff10 */ 	addiu	$sp,$sp,-240
/*    2bd08:	afb20048 */ 	sw	$s2,0x48($sp)
/*    2bd0c:	afb10044 */ 	sw	$s1,0x44($sp)
/*    2bd10:	afb00040 */ 	sw	$s0,0x40($sp)
/*    2bd14:	0085082b */ 	sltu	$at,$a0,$a1
/*    2bd18:	00e08825 */ 	or	$s1,$a3,$zero
/*    2bd1c:	00c09025 */ 	or	$s2,$a2,$zero
/*    2bd20:	afbf005c */ 	sw	$ra,0x5c($sp)
/*    2bd24:	afb60058 */ 	sw	$s6,0x58($sp)
/*    2bd28:	afb50054 */ 	sw	$s5,0x54($sp)
/*    2bd2c:	afb40050 */ 	sw	$s4,0x50($sp)
/*    2bd30:	afb3004c */ 	sw	$s3,0x4c($sp)
/*    2bd34:	f7b60038 */ 	sdc1	$f22,0x38($sp)
/*    2bd38:	f7b40030 */ 	sdc1	$f20,0x30($sp)
/*    2bd3c:	afa500f4 */ 	sw	$a1,0xf4($sp)
/*    2bd40:	1020016c */ 	beqz	$at,.L0002c2f4
/*    2bd44:	00808025 */ 	or	$s0,$a0,$zero
/*    2bd48:	c7b60114 */ 	lwc1	$f22,0x114($sp)
/*    2bd4c:	c7b40110 */ 	lwc1	$f20,0x110($sp)
/*    2bd50:	8fb6010c */ 	lw	$s6,0x10c($sp)
/*    2bd54:	97b50106 */ 	lhu	$s5,0x106($sp)
/*    2bd58:	2414000c */ 	addiu	$s4,$zero,0xc
/*    2bd5c:	8fb30100 */ 	lw	$s3,0x100($sp)
/*    2bd60:	92020000 */ 	lbu	$v0,0x0($s0)
.L0002bd64:
/*    2bd64:	24010001 */ 	addiu	$at,$zero,0x1
/*    2bd68:	1440009d */ 	bnez	$v0,.L0002bfe0
/*    2bd6c:	00000000 */ 	nop
/*    2bd70:	afb000e8 */ 	sw	$s0,0xe8($sp)
/*    2bd74:	960f0002 */ 	lhu	$t7,0x2($s0)
/*    2bd78:	01f5c024 */ 	and	$t8,$t7,$s5
/*    2bd7c:	53000091 */ 	beqzl	$t8,.L0002bfc4
/*    2bd80:	8fa900e8 */ 	lw	$t1,0xe8($sp)
/*    2bd84:	92190006 */ 	lbu	$t9,0x6($s0)
/*    2bd88:	03304021 */ 	addu	$t0,$t9,$s0
/*    2bd8c:	85090000 */ 	lh	$t1,0x0($t0)
/*    2bd90:	44892000 */ 	mtc1	$t1,$f4
/*    2bd94:	00000000 */ 	nop
/*    2bd98:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    2bd9c:	e7a600dc */ 	swc1	$f6,0xdc($sp)
/*    2bda0:	c7aa00dc */ 	lwc1	$f10,0xdc($sp)
/*    2bda4:	c6480000 */ 	lwc1	$f8,0x0($s2)
/*    2bda8:	460a403c */ 	c.lt.s	$f8,$f10
/*    2bdac:	00000000 */ 	nop
/*    2bdb0:	45020007 */ 	bc1fl	.L0002bdd0
/*    2bdb4:	920a0009 */ 	lbu	$t2,0x9($s0)
/*    2bdb8:	c6300000 */ 	lwc1	$f16,0x0($s1)
/*    2bdbc:	460a803c */ 	c.lt.s	$f16,$f10
/*    2bdc0:	00000000 */ 	nop
/*    2bdc4:	4503007f */ 	bc1tl	.L0002bfc4
/*    2bdc8:	8fa900e8 */ 	lw	$t1,0xe8($sp)
/*    2bdcc:	920a0009 */ 	lbu	$t2,0x9($s0)
.L0002bdd0:
/*    2bdd0:	01505821 */ 	addu	$t3,$t2,$s0
/*    2bdd4:	856c0000 */ 	lh	$t4,0x0($t3)
/*    2bdd8:	448c9000 */ 	mtc1	$t4,$f18
/*    2bddc:	00000000 */ 	nop
/*    2bde0:	46809120 */ 	cvt.s.w	$f4,$f18
/*    2bde4:	e7a400d0 */ 	swc1	$f4,0xd0($sp)
/*    2bde8:	c6480000 */ 	lwc1	$f8,0x0($s2)
/*    2bdec:	c7a600d0 */ 	lwc1	$f6,0xd0($sp)
/*    2bdf0:	4608303c */ 	c.lt.s	$f6,$f8
/*    2bdf4:	00000000 */ 	nop
/*    2bdf8:	45020007 */ 	bc1fl	.L0002be18
/*    2bdfc:	920d0008 */ 	lbu	$t5,0x8($s0)
/*    2be00:	c6300000 */ 	lwc1	$f16,0x0($s1)
/*    2be04:	4610303c */ 	c.lt.s	$f6,$f16
/*    2be08:	00000000 */ 	nop
/*    2be0c:	4503006d */ 	bc1tl	.L0002bfc4
/*    2be10:	8fa900e8 */ 	lw	$t1,0xe8($sp)
/*    2be14:	920d0008 */ 	lbu	$t5,0x8($s0)
.L0002be18:
/*    2be18:	01b07021 */ 	addu	$t6,$t5,$s0
/*    2be1c:	85cf0000 */ 	lh	$t7,0x0($t6)
/*    2be20:	448f5000 */ 	mtc1	$t7,$f10
/*    2be24:	00000000 */ 	nop
/*    2be28:	468054a0 */ 	cvt.s.w	$f18,$f10
/*    2be2c:	e7b200e4 */ 	swc1	$f18,0xe4($sp)
/*    2be30:	c7a800e4 */ 	lwc1	$f8,0xe4($sp)
/*    2be34:	c6440008 */ 	lwc1	$f4,0x8($s2)
/*    2be38:	4608203c */ 	c.lt.s	$f4,$f8
/*    2be3c:	00000000 */ 	nop
/*    2be40:	45020007 */ 	bc1fl	.L0002be60
/*    2be44:	9218000b */ 	lbu	$t8,0xb($s0)
/*    2be48:	c6260008 */ 	lwc1	$f6,0x8($s1)
/*    2be4c:	4608303c */ 	c.lt.s	$f6,$f8
/*    2be50:	00000000 */ 	nop
/*    2be54:	4503005b */ 	bc1tl	.L0002bfc4
/*    2be58:	8fa900e8 */ 	lw	$t1,0xe8($sp)
/*    2be5c:	9218000b */ 	lbu	$t8,0xb($s0)
.L0002be60:
/*    2be60:	8fa90108 */ 	lw	$t1,0x108($sp)
/*    2be64:	0310c821 */ 	addu	$t9,$t8,$s0
/*    2be68:	87280000 */ 	lh	$t0,0x0($t9)
/*    2be6c:	44888000 */ 	mtc1	$t0,$f16
/*    2be70:	00000000 */ 	nop
/*    2be74:	468082a0 */ 	cvt.s.w	$f10,$f16
/*    2be78:	e7aa00d8 */ 	swc1	$f10,0xd8($sp)
/*    2be7c:	c6440008 */ 	lwc1	$f4,0x8($s2)
/*    2be80:	c7b200d8 */ 	lwc1	$f18,0xd8($sp)
/*    2be84:	4604903c */ 	c.lt.s	$f18,$f4
/*    2be88:	00000000 */ 	nop
/*    2be8c:	45000006 */ 	bc1f	.L0002bea8
/*    2be90:	00000000 */ 	nop
/*    2be94:	c6260008 */ 	lwc1	$f6,0x8($s1)
/*    2be98:	4606903c */ 	c.lt.s	$f18,$f6
/*    2be9c:	00000000 */ 	nop
/*    2bea0:	45030048 */ 	bc1tl	.L0002bfc4
/*    2bea4:	8fa900e8 */ 	lw	$t1,0xe8($sp)
.L0002bea8:
/*    2bea8:	11200036 */ 	beqz	$t1,.L0002bf84
/*    2beac:	02402025 */ 	or	$a0,$s2,$zero
/*    2beb0:	920a0007 */ 	lbu	$t2,0x7($s0)
/*    2beb4:	01505821 */ 	addu	$t3,$t2,$s0
/*    2beb8:	856c0000 */ 	lh	$t4,0x0($t3)
/*    2bebc:	448c4000 */ 	mtc1	$t4,$f8
/*    2bec0:	00000000 */ 	nop
/*    2bec4:	46804420 */ 	cvt.s.w	$f16,$f8
/*    2bec8:	e7b000e0 */ 	swc1	$f16,0xe0($sp)
/*    2becc:	920d000a */ 	lbu	$t5,0xa($s0)
/*    2bed0:	c7b200e0 */ 	lwc1	$f18,0xe0($sp)
/*    2bed4:	01b07021 */ 	addu	$t6,$t5,$s0
/*    2bed8:	85cf0000 */ 	lh	$t7,0x0($t6)
/*    2bedc:	448f5000 */ 	mtc1	$t7,$f10
/*    2bee0:	00000000 */ 	nop
/*    2bee4:	46805120 */ 	cvt.s.w	$f4,$f10
/*    2bee8:	e7a400d4 */ 	swc1	$f4,0xd4($sp)
/*    2beec:	c6400004 */ 	lwc1	$f0,0x4($s2)
/*    2bef0:	c7a800d4 */ 	lwc1	$f8,0xd4($sp)
/*    2bef4:	4612003c */ 	c.lt.s	$f0,$f18
/*    2bef8:	00000000 */ 	nop
/*    2befc:	45020007 */ 	bc1fl	.L0002bf1c
/*    2bf00:	4600403c */ 	c.lt.s	$f8,$f0
/*    2bf04:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*    2bf08:	4612303c */ 	c.lt.s	$f6,$f18
/*    2bf0c:	00000000 */ 	nop
/*    2bf10:	4503002c */ 	bc1tl	.L0002bfc4
/*    2bf14:	8fa900e8 */ 	lw	$t1,0xe8($sp)
/*    2bf18:	4600403c */ 	c.lt.s	$f8,$f0
.L0002bf1c:
/*    2bf1c:	02402025 */ 	or	$a0,$s2,$zero
/*    2bf20:	02602825 */ 	or	$a1,$s3,$zero
/*    2bf24:	27a600dc */ 	addiu	$a2,$sp,0xdc
/*    2bf28:	45000006 */ 	bc1f	.L0002bf44
/*    2bf2c:	00000000 */ 	nop
/*    2bf30:	c6300004 */ 	lwc1	$f16,0x4($s1)
/*    2bf34:	4610403c */ 	c.lt.s	$f8,$f16
/*    2bf38:	00000000 */ 	nop
/*    2bf3c:	45030021 */ 	bc1tl	.L0002bfc4
/*    2bf40:	8fa900e8 */ 	lw	$t1,0xe8($sp)
.L0002bf44:
/*    2bf44:	0fc57cac */ 	jal	func0f15f2b0
/*    2bf48:	27a700d0 */ 	addiu	$a3,$sp,0xd0
/*    2bf4c:	1040001c */ 	beqz	$v0,.L0002bfc0
/*    2bf50:	02402025 */ 	or	$a0,$s2,$zero
/*    2bf54:	27b800c4 */ 	addiu	$t8,$sp,0xc4
/*    2bf58:	27b900b8 */ 	addiu	$t9,$sp,0xb8
/*    2bf5c:	afb90014 */ 	sw	$t9,0x14($sp)
/*    2bf60:	afb80010 */ 	sw	$t8,0x10($sp)
/*    2bf64:	02202825 */ 	or	$a1,$s1,$zero
/*    2bf68:	02603025 */ 	or	$a2,$s3,$zero
/*    2bf6c:	0c00aab0 */ 	jal	func0002aac0
/*    2bf70:	02003825 */ 	or	$a3,$s0,$zero
/*    2bf74:	50400013 */ 	beqzl	$v0,.L0002bfc4
/*    2bf78:	8fa900e8 */ 	lw	$t1,0xe8($sp)
/*    2bf7c:	100000de */ 	b	.L0002c2f8
/*    2bf80:	00001025 */ 	or	$v0,$zero,$zero
.L0002bf84:
/*    2bf84:	27a800c4 */ 	addiu	$t0,$sp,0xc4
/*    2bf88:	afa80010 */ 	sw	$t0,0x10($sp)
/*    2bf8c:	02202825 */ 	or	$a1,$s1,$zero
/*    2bf90:	02603025 */ 	or	$a2,$s3,$zero
/*    2bf94:	02003825 */ 	or	$a3,$s0,$zero
/*    2bf98:	afa00014 */ 	sw	$zero,0x14($sp)
/*    2bf9c:	afa00018 */ 	sw	$zero,0x18($sp)
/*    2bfa0:	afb6001c */ 	sw	$s6,0x1c($sp)
/*    2bfa4:	e7b40020 */ 	swc1	$f20,0x20($sp)
/*    2bfa8:	0c00ab1c */ 	jal	func0002ac70
/*    2bfac:	e7b60024 */ 	swc1	$f22,0x24($sp)
/*    2bfb0:	50400004 */ 	beqzl	$v0,.L0002bfc4
/*    2bfb4:	8fa900e8 */ 	lw	$t1,0xe8($sp)
/*    2bfb8:	100000cf */ 	b	.L0002c2f8
/*    2bfbc:	00001025 */ 	or	$v0,$zero,$zero
.L0002bfc0:
/*    2bfc0:	8fa900e8 */ 	lw	$t1,0xe8($sp)
.L0002bfc4:
/*    2bfc4:	912a0001 */ 	lbu	$t2,0x1($t1)
/*    2bfc8:	000a5880 */ 	sll	$t3,$t2,0x2
/*    2bfcc:	016a5823 */ 	subu	$t3,$t3,$t2
/*    2bfd0:	000b5840 */ 	sll	$t3,$t3,0x1
/*    2bfd4:	020b8021 */ 	addu	$s0,$s0,$t3
/*    2bfd8:	100000c2 */ 	b	.L0002c2e4
/*    2bfdc:	2610000e */ 	addiu	$s0,$s0,0xe
.L0002bfe0:
/*    2bfe0:	54410094 */ 	bnel	$v0,$at,.L0002c234
/*    2bfe4:	24010002 */ 	addiu	$at,$zero,0x2
/*    2bfe8:	afb000b4 */ 	sw	$s0,0xb4($sp)
/*    2bfec:	960c0002 */ 	lhu	$t4,0x2($s0)
/*    2bff0:	01956824 */ 	and	$t5,$t4,$s5
/*    2bff4:	51a00087 */ 	beqzl	$t5,.L0002c214
/*    2bff8:	8fb800b4 */ 	lw	$t8,0xb4($sp)
/*    2bffc:	920e0006 */ 	lbu	$t6,0x6($s0)
/*    2c000:	01d40019 */ 	multu	$t6,$s4
/*    2c004:	00007812 */ 	mflo	$t7
/*    2c008:	020fc021 */ 	addu	$t8,$s0,$t7
/*    2c00c:	c70a0010 */ 	lwc1	$f10,0x10($t8)
/*    2c010:	e7aa00a8 */ 	swc1	$f10,0xa8($sp)
/*    2c014:	92190009 */ 	lbu	$t9,0x9($s0)
/*    2c018:	c7a800a8 */ 	lwc1	$f8,0xa8($sp)
/*    2c01c:	03340019 */ 	multu	$t9,$s4
/*    2c020:	00004012 */ 	mflo	$t0
/*    2c024:	02084821 */ 	addu	$t1,$s0,$t0
/*    2c028:	c5240010 */ 	lwc1	$f4,0x10($t1)
/*    2c02c:	e7a4009c */ 	swc1	$f4,0x9c($sp)
/*    2c030:	920a0008 */ 	lbu	$t2,0x8($s0)
/*    2c034:	c7aa009c */ 	lwc1	$f10,0x9c($sp)
/*    2c038:	01540019 */ 	multu	$t2,$s4
/*    2c03c:	00005812 */ 	mflo	$t3
/*    2c040:	020b6021 */ 	addu	$t4,$s0,$t3
/*    2c044:	c5860018 */ 	lwc1	$f6,0x18($t4)
/*    2c048:	e7a600b0 */ 	swc1	$f6,0xb0($sp)
/*    2c04c:	920d000b */ 	lbu	$t5,0xb($s0)
/*    2c050:	01b40019 */ 	multu	$t5,$s4
/*    2c054:	00007012 */ 	mflo	$t6
/*    2c058:	020e7821 */ 	addu	$t7,$s0,$t6
/*    2c05c:	c5f20018 */ 	lwc1	$f18,0x18($t7)
/*    2c060:	e7b200a4 */ 	swc1	$f18,0xa4($sp)
/*    2c064:	c6400000 */ 	lwc1	$f0,0x0($s2)
/*    2c068:	4608003c */ 	c.lt.s	$f0,$f8
/*    2c06c:	00000000 */ 	nop
/*    2c070:	45020007 */ 	bc1fl	.L0002c090
/*    2c074:	4600503c */ 	c.lt.s	$f10,$f0
/*    2c078:	c6300000 */ 	lwc1	$f16,0x0($s1)
/*    2c07c:	4608803c */ 	c.lt.s	$f16,$f8
/*    2c080:	00000000 */ 	nop
/*    2c084:	45030063 */ 	bc1tl	.L0002c214
/*    2c088:	8fb800b4 */ 	lw	$t8,0xb4($sp)
/*    2c08c:	4600503c */ 	c.lt.s	$f10,$f0
.L0002c090:
/*    2c090:	c7a600b0 */ 	lwc1	$f6,0xb0($sp)
/*    2c094:	45020007 */ 	bc1fl	.L0002c0b4
/*    2c098:	c6400008 */ 	lwc1	$f0,0x8($s2)
/*    2c09c:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*    2c0a0:	4604503c */ 	c.lt.s	$f10,$f4
/*    2c0a4:	00000000 */ 	nop
/*    2c0a8:	4503005a */ 	bc1tl	.L0002c214
/*    2c0ac:	8fb800b4 */ 	lw	$t8,0xb4($sp)
/*    2c0b0:	c6400008 */ 	lwc1	$f0,0x8($s2)
.L0002c0b4:
/*    2c0b4:	c7b000a4 */ 	lwc1	$f16,0xa4($sp)
/*    2c0b8:	4606003c */ 	c.lt.s	$f0,$f6
/*    2c0bc:	00000000 */ 	nop
/*    2c0c0:	45020007 */ 	bc1fl	.L0002c0e0
/*    2c0c4:	4600803c */ 	c.lt.s	$f16,$f0
/*    2c0c8:	c6320008 */ 	lwc1	$f18,0x8($s1)
/*    2c0cc:	4606903c */ 	c.lt.s	$f18,$f6
/*    2c0d0:	00000000 */ 	nop
/*    2c0d4:	4503004f */ 	bc1tl	.L0002c214
/*    2c0d8:	8fb800b4 */ 	lw	$t8,0xb4($sp)
/*    2c0dc:	4600803c */ 	c.lt.s	$f16,$f0
.L0002c0e0:
/*    2c0e0:	8fb80108 */ 	lw	$t8,0x108($sp)
/*    2c0e4:	45000006 */ 	bc1f	.L0002c100
/*    2c0e8:	00000000 */ 	nop
/*    2c0ec:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*    2c0f0:	4608803c */ 	c.lt.s	$f16,$f8
/*    2c0f4:	00000000 */ 	nop
/*    2c0f8:	45030046 */ 	bc1tl	.L0002c214
/*    2c0fc:	8fb800b4 */ 	lw	$t8,0xb4($sp)
.L0002c100:
/*    2c100:	13000034 */ 	beqz	$t8,.L0002c1d4
/*    2c104:	02402025 */ 	or	$a0,$s2,$zero
/*    2c108:	92190007 */ 	lbu	$t9,0x7($s0)
/*    2c10c:	03340019 */ 	multu	$t9,$s4
/*    2c110:	00004012 */ 	mflo	$t0
/*    2c114:	02084821 */ 	addu	$t1,$s0,$t0
/*    2c118:	c52a0014 */ 	lwc1	$f10,0x14($t1)
/*    2c11c:	e7aa00ac */ 	swc1	$f10,0xac($sp)
/*    2c120:	920a000a */ 	lbu	$t2,0xa($s0)
/*    2c124:	c7b200ac */ 	lwc1	$f18,0xac($sp)
/*    2c128:	01540019 */ 	multu	$t2,$s4
/*    2c12c:	00005812 */ 	mflo	$t3
/*    2c130:	020b6021 */ 	addu	$t4,$s0,$t3
/*    2c134:	c5840014 */ 	lwc1	$f4,0x14($t4)
/*    2c138:	e7a400a0 */ 	swc1	$f4,0xa0($sp)
/*    2c13c:	c6400004 */ 	lwc1	$f0,0x4($s2)
/*    2c140:	c7b000a0 */ 	lwc1	$f16,0xa0($sp)
/*    2c144:	4612003c */ 	c.lt.s	$f0,$f18
/*    2c148:	00000000 */ 	nop
/*    2c14c:	45020007 */ 	bc1fl	.L0002c16c
/*    2c150:	4600803c */ 	c.lt.s	$f16,$f0
/*    2c154:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*    2c158:	4612303c */ 	c.lt.s	$f6,$f18
/*    2c15c:	00000000 */ 	nop
/*    2c160:	4503002c */ 	bc1tl	.L0002c214
/*    2c164:	8fb800b4 */ 	lw	$t8,0xb4($sp)
/*    2c168:	4600803c */ 	c.lt.s	$f16,$f0
.L0002c16c:
/*    2c16c:	02402025 */ 	or	$a0,$s2,$zero
/*    2c170:	02602825 */ 	or	$a1,$s3,$zero
/*    2c174:	27a600a8 */ 	addiu	$a2,$sp,0xa8
/*    2c178:	45000006 */ 	bc1f	.L0002c194
/*    2c17c:	00000000 */ 	nop
/*    2c180:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*    2c184:	4608803c */ 	c.lt.s	$f16,$f8
/*    2c188:	00000000 */ 	nop
/*    2c18c:	45030021 */ 	bc1tl	.L0002c214
/*    2c190:	8fb800b4 */ 	lw	$t8,0xb4($sp)
.L0002c194:
/*    2c194:	0fc57cac */ 	jal	func0f15f2b0
/*    2c198:	27a7009c */ 	addiu	$a3,$sp,0x9c
/*    2c19c:	1040001c */ 	beqz	$v0,.L0002c210
/*    2c1a0:	02402025 */ 	or	$a0,$s2,$zero
/*    2c1a4:	27ad0090 */ 	addiu	$t5,$sp,0x90
/*    2c1a8:	27ae0084 */ 	addiu	$t6,$sp,0x84
/*    2c1ac:	afae0014 */ 	sw	$t6,0x14($sp)
/*    2c1b0:	afad0010 */ 	sw	$t5,0x10($sp)
/*    2c1b4:	02202825 */ 	or	$a1,$s1,$zero
/*    2c1b8:	02603025 */ 	or	$a2,$s3,$zero
/*    2c1bc:	0c00aae6 */ 	jal	func0002ab98
/*    2c1c0:	02003825 */ 	or	$a3,$s0,$zero
/*    2c1c4:	50400013 */ 	beqzl	$v0,.L0002c214
/*    2c1c8:	8fb800b4 */ 	lw	$t8,0xb4($sp)
/*    2c1cc:	1000004a */ 	b	.L0002c2f8
/*    2c1d0:	00001025 */ 	or	$v0,$zero,$zero
.L0002c1d4:
/*    2c1d4:	27af0090 */ 	addiu	$t7,$sp,0x90
/*    2c1d8:	afaf0010 */ 	sw	$t7,0x10($sp)
/*    2c1dc:	02202825 */ 	or	$a1,$s1,$zero
/*    2c1e0:	02603025 */ 	or	$a2,$s3,$zero
/*    2c1e4:	02003825 */ 	or	$a3,$s0,$zero
/*    2c1e8:	afa00014 */ 	sw	$zero,0x14($sp)
/*    2c1ec:	afa00018 */ 	sw	$zero,0x18($sp)
/*    2c1f0:	afb6001c */ 	sw	$s6,0x1c($sp)
/*    2c1f4:	e7b40020 */ 	swc1	$f20,0x20($sp)
/*    2c1f8:	0c00ac4a */ 	jal	func0002b128
/*    2c1fc:	e7b60024 */ 	swc1	$f22,0x24($sp)
/*    2c200:	50400004 */ 	beqzl	$v0,.L0002c214
/*    2c204:	8fb800b4 */ 	lw	$t8,0xb4($sp)
/*    2c208:	1000003b */ 	b	.L0002c2f8
/*    2c20c:	00001025 */ 	or	$v0,$zero,$zero
.L0002c210:
/*    2c210:	8fb800b4 */ 	lw	$t8,0xb4($sp)
.L0002c214:
/*    2c214:	93190001 */ 	lbu	$t9,0x1($t8)
/*    2c218:	2728ffc0 */ 	addiu	$t0,$t9,-64
/*    2c21c:	01140019 */ 	multu	$t0,$s4
/*    2c220:	00004812 */ 	mflo	$t1
/*    2c224:	02098021 */ 	addu	$s0,$s0,$t1
/*    2c228:	1000002e */ 	b	.L0002c2e4
/*    2c22c:	26100310 */ 	addiu	$s0,$s0,0x310
/*    2c230:	24010002 */ 	addiu	$at,$zero,0x2
.L0002c234:
/*    2c234:	14410014 */ 	bne	$v0,$at,.L0002c288
/*    2c238:	32aa001c */ 	andi	$t2,$s5,0x1c
/*    2c23c:	11400010 */ 	beqz	$t2,.L0002c280
/*    2c240:	02402025 */ 	or	$a0,$s2,$zero
/*    2c244:	27ab0078 */ 	addiu	$t3,$sp,0x78
/*    2c248:	afab0010 */ 	sw	$t3,0x10($sp)
/*    2c24c:	02202825 */ 	or	$a1,$s1,$zero
/*    2c250:	02603025 */ 	or	$a2,$s3,$zero
/*    2c254:	02003825 */ 	or	$a3,$s0,$zero
/*    2c258:	afa00014 */ 	sw	$zero,0x14($sp)
/*    2c25c:	afa00018 */ 	sw	$zero,0x18($sp)
/*    2c260:	afb6001c */ 	sw	$s6,0x1c($sp)
/*    2c264:	e7b40020 */ 	swc1	$f20,0x20($sp)
/*    2c268:	0c00ad58 */ 	jal	func0002b560
/*    2c26c:	e7b60024 */ 	swc1	$f22,0x24($sp)
/*    2c270:	10400003 */ 	beqz	$v0,.L0002c280
/*    2c274:	00000000 */ 	nop
/*    2c278:	1000001f */ 	b	.L0002c2f8
/*    2c27c:	00001025 */ 	or	$v0,$zero,$zero
.L0002c280:
/*    2c280:	10000018 */ 	b	.L0002c2e4
/*    2c284:	2610004c */ 	addiu	$s0,$s0,0x4c
.L0002c288:
/*    2c288:	24010003 */ 	addiu	$at,$zero,0x3
/*    2c28c:	54410016 */ 	bnel	$v0,$at,.L0002c2e8
/*    2c290:	8faf00f4 */ 	lw	$t7,0xf4($sp)
/*    2c294:	960c0002 */ 	lhu	$t4,0x2($s0)
/*    2c298:	02402025 */ 	or	$a0,$s2,$zero
/*    2c29c:	02202825 */ 	or	$a1,$s1,$zero
/*    2c2a0:	02ac6824 */ 	and	$t5,$s5,$t4
/*    2c2a4:	11a0000e */ 	beqz	$t5,.L0002c2e0
/*    2c2a8:	02603025 */ 	or	$a2,$s3,$zero
/*    2c2ac:	27ae0068 */ 	addiu	$t6,$sp,0x68
/*    2c2b0:	afae0010 */ 	sw	$t6,0x10($sp)
/*    2c2b4:	02003825 */ 	or	$a3,$s0,$zero
/*    2c2b8:	afa00014 */ 	sw	$zero,0x14($sp)
/*    2c2bc:	afa00018 */ 	sw	$zero,0x18($sp)
/*    2c2c0:	afb6001c */ 	sw	$s6,0x1c($sp)
/*    2c2c4:	e7b40020 */ 	swc1	$f20,0x20($sp)
/*    2c2c8:	0c00ae55 */ 	jal	func0002b954
/*    2c2cc:	e7b60024 */ 	swc1	$f22,0x24($sp)
/*    2c2d0:	50400004 */ 	beqzl	$v0,.L0002c2e4
/*    2c2d4:	26100018 */ 	addiu	$s0,$s0,0x18
/*    2c2d8:	10000007 */ 	b	.L0002c2f8
/*    2c2dc:	00001025 */ 	or	$v0,$zero,$zero
.L0002c2e0:
/*    2c2e0:	26100018 */ 	addiu	$s0,$s0,0x18
.L0002c2e4:
/*    2c2e4:	8faf00f4 */ 	lw	$t7,0xf4($sp)
.L0002c2e8:
/*    2c2e8:	020f082b */ 	sltu	$at,$s0,$t7
/*    2c2ec:	5420fe9d */ 	bnezl	$at,.L0002bd64
/*    2c2f0:	92020000 */ 	lbu	$v0,0x0($s0)
.L0002c2f4:
/*    2c2f4:	24020001 */ 	addiu	$v0,$zero,0x1
.L0002c2f8:
/*    2c2f8:	8fbf005c */ 	lw	$ra,0x5c($sp)
/*    2c2fc:	d7b40030 */ 	ldc1	$f20,0x30($sp)
/*    2c300:	d7b60038 */ 	ldc1	$f22,0x38($sp)
/*    2c304:	8fb00040 */ 	lw	$s0,0x40($sp)
/*    2c308:	8fb10044 */ 	lw	$s1,0x44($sp)
/*    2c30c:	8fb20048 */ 	lw	$s2,0x48($sp)
/*    2c310:	8fb3004c */ 	lw	$s3,0x4c($sp)
/*    2c314:	8fb40050 */ 	lw	$s4,0x50($sp)
/*    2c318:	8fb50054 */ 	lw	$s5,0x54($sp)
/*    2c31c:	8fb60058 */ 	lw	$s6,0x58($sp)
/*    2c320:	03e00008 */ 	jr	$ra
/*    2c324:	27bd00f0 */ 	addiu	$sp,$sp,0xf0
);

GLOBAL_ASM(
glabel func0002c328
/*    2c328:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*    2c32c:	f7b40010 */ 	sdc1	$f20,0x10($sp)
/*    2c330:	afbf0024 */ 	sw	$ra,0x24($sp)
/*    2c334:	f7b60018 */ 	sdc1	$f22,0x18($sp)
/*    2c338:	afa40048 */ 	sw	$a0,0x48($sp)
/*    2c33c:	4480a000 */ 	mtc1	$zero,$f20
/*    2c340:	c4c40000 */ 	lwc1	$f4,0x0($a2)
/*    2c344:	4600a406 */ 	mov.s	$f16,$f20
/*    2c348:	4604a032 */ 	c.eq.s	$f20,$f4
/*    2c34c:	4600a486 */ 	mov.s	$f18,$f20
/*    2c350:	45020008 */ 	bc1fl	.L0002c374
/*    2c354:	c4c80008 */ 	lwc1	$f8,0x8($a2)
/*    2c358:	c4c60008 */ 	lwc1	$f6,0x8($a2)
/*    2c35c:	3c013f80 */ 	lui	$at,0x3f80
/*    2c360:	4606a032 */ 	c.eq.s	$f20,$f6
/*    2c364:	00000000 */ 	nop
/*    2c368:	4503002a */ 	bc1tl	.L0002c414
/*    2c36c:	44814000 */ 	mtc1	$at,$f8
/*    2c370:	c4c80008 */ 	lwc1	$f8,0x8($a2)
.L0002c374:
/*    2c374:	e7b40040 */ 	swc1	$f20,0x40($sp)
/*    2c378:	e7a8003c */ 	swc1	$f8,0x3c($sp)
/*    2c37c:	c4ca0000 */ 	lwc1	$f10,0x0($a2)
/*    2c380:	e7b20028 */ 	swc1	$f18,0x28($sp)
/*    2c384:	e7b0002c */ 	swc1	$f16,0x2c($sp)
/*    2c388:	46005107 */ 	neg.s	$f4,$f10
/*    2c38c:	c7aa003c */ 	lwc1	$f10,0x3c($sp)
/*    2c390:	e7a40044 */ 	swc1	$f4,0x44($sp)
/*    2c394:	c7a60044 */ 	lwc1	$f6,0x44($sp)
/*    2c398:	afa70054 */ 	sw	$a3,0x54($sp)
/*    2c39c:	afa5004c */ 	sw	$a1,0x4c($sp)
/*    2c3a0:	46063202 */ 	mul.s	$f8,$f6,$f6
/*    2c3a4:	00000000 */ 	nop
/*    2c3a8:	460a5102 */ 	mul.s	$f4,$f10,$f10
/*    2c3ac:	0c012974 */ 	jal	sqrtf
/*    2c3b0:	46044300 */ 	add.s	$f12,$f8,$f4
/*    2c3b4:	4600a03c */ 	c.lt.s	$f20,$f0
/*    2c3b8:	8fa5004c */ 	lw	$a1,0x4c($sp)
/*    2c3bc:	8fa70054 */ 	lw	$a3,0x54($sp)
/*    2c3c0:	c7b0002c */ 	lwc1	$f16,0x2c($sp)
/*    2c3c4:	4500000c */ 	bc1f	.L0002c3f8
/*    2c3c8:	c7b20028 */ 	lwc1	$f18,0x28($sp)
/*    2c3cc:	3c013f80 */ 	lui	$at,0x3f80
/*    2c3d0:	44813000 */ 	mtc1	$at,$f6
/*    2c3d4:	c7aa003c */ 	lwc1	$f10,0x3c($sp)
/*    2c3d8:	c7a40044 */ 	lwc1	$f4,0x44($sp)
/*    2c3dc:	46003083 */ 	div.s	$f2,$f6,$f0
/*    2c3e0:	46025202 */ 	mul.s	$f8,$f10,$f2
/*    2c3e4:	00000000 */ 	nop
/*    2c3e8:	46022182 */ 	mul.s	$f6,$f4,$f2
/*    2c3ec:	e7a8003c */ 	swc1	$f8,0x3c($sp)
/*    2c3f0:	1000000b */ 	b	.L0002c420
/*    2c3f4:	e7a60044 */ 	swc1	$f6,0x44($sp)
.L0002c3f8:
/*    2c3f8:	3c013f80 */ 	lui	$at,0x3f80
/*    2c3fc:	44815000 */ 	mtc1	$at,$f10
/*    2c400:	e7b4003c */ 	swc1	$f20,0x3c($sp)
/*    2c404:	e7b40040 */ 	swc1	$f20,0x40($sp)
/*    2c408:	10000005 */ 	b	.L0002c420
/*    2c40c:	e7aa0044 */ 	swc1	$f10,0x44($sp)
/*    2c410:	44814000 */ 	mtc1	$at,$f8
.L0002c414:
/*    2c414:	e7b4003c */ 	swc1	$f20,0x3c($sp)
/*    2c418:	e7b40040 */ 	swc1	$f20,0x40($sp)
/*    2c41c:	e7a80044 */ 	swc1	$f8,0x44($sp)
.L0002c420:
/*    2c420:	8fae0048 */ 	lw	$t6,0x48($sp)
/*    2c424:	00001825 */ 	or	$v1,$zero,$zero
/*    2c428:	91c40001 */ 	lbu	$a0,0x1($t6)
/*    2c42c:	01c01025 */ 	or	$v0,$t6,$zero
/*    2c430:	58800020 */ 	blezl	$a0,.L0002c4b4
/*    2c434:	c7a4003c */ 	lwc1	$f4,0x3c($sp)
/*    2c438:	c4b40000 */ 	lwc1	$f20,0x0($a1)
/*    2c43c:	c4b60008 */ 	lwc1	$f22,0x8($a1)
.L0002c440:
/*    2c440:	84580012 */ 	lh	$t8,0x12($v0)
/*    2c444:	844f000e */ 	lh	$t7,0xe($v0)
/*    2c448:	24630001 */ 	addiu	$v1,$v1,0x1
/*    2c44c:	44985000 */ 	mtc1	$t8,$f10
/*    2c450:	448f2000 */ 	mtc1	$t7,$f4
/*    2c454:	46805220 */ 	cvt.s.w	$f8,$f10
/*    2c458:	c7aa003c */ 	lwc1	$f10,0x3c($sp)
/*    2c45c:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    2c460:	c7a40044 */ 	lwc1	$f4,0x44($sp)
/*    2c464:	46164301 */ 	sub.s	$f12,$f8,$f22
/*    2c468:	46143081 */ 	sub.s	$f2,$f6,$f20
/*    2c46c:	460c2182 */ 	mul.s	$f6,$f4,$f12
/*    2c470:	00000000 */ 	nop
/*    2c474:	460a1202 */ 	mul.s	$f8,$f2,$f10
/*    2c478:	46083000 */ 	add.s	$f0,$f6,$f8
/*    2c47c:	4600803c */ 	c.lt.s	$f16,$f0
/*    2c480:	00000000 */ 	nop
/*    2c484:	45000003 */ 	bc1f	.L0002c494
/*    2c488:	00000000 */ 	nop
/*    2c48c:	10000006 */ 	b	.L0002c4a8
/*    2c490:	46000406 */ 	mov.s	$f16,$f0
.L0002c494:
/*    2c494:	4612003c */ 	c.lt.s	$f0,$f18
/*    2c498:	00000000 */ 	nop
/*    2c49c:	45000002 */ 	bc1f	.L0002c4a8
/*    2c4a0:	00000000 */ 	nop
/*    2c4a4:	46000486 */ 	mov.s	$f18,$f0
.L0002c4a8:
/*    2c4a8:	1464ffe5 */ 	bne	$v1,$a0,.L0002c440
/*    2c4ac:	24420006 */ 	addiu	$v0,$v0,0x6
/*    2c4b0:	c7a4003c */ 	lwc1	$f4,0x3c($sp)
.L0002c4b4:
/*    2c4b4:	c4a60000 */ 	lwc1	$f6,0x0($a1)
/*    2c4b8:	8fa20058 */ 	lw	$v0,0x58($sp)
/*    2c4bc:	46102282 */ 	mul.s	$f10,$f4,$f16
/*    2c4c0:	46065200 */ 	add.s	$f8,$f10,$f6
/*    2c4c4:	e4e80000 */ 	swc1	$f8,0x0($a3)
/*    2c4c8:	c4a40004 */ 	lwc1	$f4,0x4($a1)
/*    2c4cc:	e4e40004 */ 	swc1	$f4,0x4($a3)
/*    2c4d0:	c7aa0044 */ 	lwc1	$f10,0x44($sp)
/*    2c4d4:	c4a80008 */ 	lwc1	$f8,0x8($a1)
/*    2c4d8:	46105182 */ 	mul.s	$f6,$f10,$f16
/*    2c4dc:	46083100 */ 	add.s	$f4,$f6,$f8
/*    2c4e0:	e4e40008 */ 	swc1	$f4,0x8($a3)
/*    2c4e4:	c7aa003c */ 	lwc1	$f10,0x3c($sp)
/*    2c4e8:	c4a80000 */ 	lwc1	$f8,0x0($a1)
/*    2c4ec:	46125182 */ 	mul.s	$f6,$f10,$f18
/*    2c4f0:	46083100 */ 	add.s	$f4,$f6,$f8
/*    2c4f4:	e4440000 */ 	swc1	$f4,0x0($v0)
/*    2c4f8:	c4aa0004 */ 	lwc1	$f10,0x4($a1)
/*    2c4fc:	e44a0004 */ 	swc1	$f10,0x4($v0)
/*    2c500:	c7a60044 */ 	lwc1	$f6,0x44($sp)
/*    2c504:	c4a40008 */ 	lwc1	$f4,0x8($a1)
/*    2c508:	46123202 */ 	mul.s	$f8,$f6,$f18
/*    2c50c:	46044280 */ 	add.s	$f10,$f8,$f4
/*    2c510:	e44a0008 */ 	swc1	$f10,0x8($v0)
/*    2c514:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*    2c518:	d7b60018 */ 	ldc1	$f22,0x18($sp)
/*    2c51c:	d7b40010 */ 	ldc1	$f20,0x10($sp)
/*    2c520:	03e00008 */ 	jr	$ra
/*    2c524:	27bd0048 */ 	addiu	$sp,$sp,0x48
);

GLOBAL_ASM(
glabel func0002c528
/*    2c528:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*    2c52c:	f7b40010 */ 	sdc1	$f20,0x10($sp)
/*    2c530:	afbf0024 */ 	sw	$ra,0x24($sp)
/*    2c534:	f7b60018 */ 	sdc1	$f22,0x18($sp)
/*    2c538:	afa40048 */ 	sw	$a0,0x48($sp)
/*    2c53c:	4480a000 */ 	mtc1	$zero,$f20
/*    2c540:	c4c40000 */ 	lwc1	$f4,0x0($a2)
/*    2c544:	4600a406 */ 	mov.s	$f16,$f20
/*    2c548:	4604a032 */ 	c.eq.s	$f20,$f4
/*    2c54c:	4600a486 */ 	mov.s	$f18,$f20
/*    2c550:	45020008 */ 	bc1fl	.L0002c574
/*    2c554:	c4c80008 */ 	lwc1	$f8,0x8($a2)
/*    2c558:	c4c60008 */ 	lwc1	$f6,0x8($a2)
/*    2c55c:	3c013f80 */ 	lui	$at,0x3f80
/*    2c560:	4606a032 */ 	c.eq.s	$f20,$f6
/*    2c564:	00000000 */ 	nop
/*    2c568:	4503002a */ 	bc1tl	.L0002c614
/*    2c56c:	44814000 */ 	mtc1	$at,$f8
/*    2c570:	c4c80008 */ 	lwc1	$f8,0x8($a2)
.L0002c574:
/*    2c574:	e7b40040 */ 	swc1	$f20,0x40($sp)
/*    2c578:	e7a8003c */ 	swc1	$f8,0x3c($sp)
/*    2c57c:	c4ca0000 */ 	lwc1	$f10,0x0($a2)
/*    2c580:	e7b20028 */ 	swc1	$f18,0x28($sp)
/*    2c584:	e7b0002c */ 	swc1	$f16,0x2c($sp)
/*    2c588:	46005107 */ 	neg.s	$f4,$f10
/*    2c58c:	c7aa003c */ 	lwc1	$f10,0x3c($sp)
/*    2c590:	e7a40044 */ 	swc1	$f4,0x44($sp)
/*    2c594:	c7a60044 */ 	lwc1	$f6,0x44($sp)
/*    2c598:	afa70054 */ 	sw	$a3,0x54($sp)
/*    2c59c:	afa5004c */ 	sw	$a1,0x4c($sp)
/*    2c5a0:	46063202 */ 	mul.s	$f8,$f6,$f6
/*    2c5a4:	00000000 */ 	nop
/*    2c5a8:	460a5102 */ 	mul.s	$f4,$f10,$f10
/*    2c5ac:	0c012974 */ 	jal	sqrtf
/*    2c5b0:	46044300 */ 	add.s	$f12,$f8,$f4
/*    2c5b4:	4600a03c */ 	c.lt.s	$f20,$f0
/*    2c5b8:	8fa5004c */ 	lw	$a1,0x4c($sp)
/*    2c5bc:	8fa70054 */ 	lw	$a3,0x54($sp)
/*    2c5c0:	c7b0002c */ 	lwc1	$f16,0x2c($sp)
/*    2c5c4:	4500000c */ 	bc1f	.L0002c5f8
/*    2c5c8:	c7b20028 */ 	lwc1	$f18,0x28($sp)
/*    2c5cc:	3c013f80 */ 	lui	$at,0x3f80
/*    2c5d0:	44813000 */ 	mtc1	$at,$f6
/*    2c5d4:	c7aa003c */ 	lwc1	$f10,0x3c($sp)
/*    2c5d8:	c7a40044 */ 	lwc1	$f4,0x44($sp)
/*    2c5dc:	46003083 */ 	div.s	$f2,$f6,$f0
/*    2c5e0:	46025202 */ 	mul.s	$f8,$f10,$f2
/*    2c5e4:	00000000 */ 	nop
/*    2c5e8:	46022182 */ 	mul.s	$f6,$f4,$f2
/*    2c5ec:	e7a8003c */ 	swc1	$f8,0x3c($sp)
/*    2c5f0:	1000000b */ 	b	.L0002c620
/*    2c5f4:	e7a60044 */ 	swc1	$f6,0x44($sp)
.L0002c5f8:
/*    2c5f8:	3c013f80 */ 	lui	$at,0x3f80
/*    2c5fc:	44815000 */ 	mtc1	$at,$f10
/*    2c600:	e7b4003c */ 	swc1	$f20,0x3c($sp)
/*    2c604:	e7b40040 */ 	swc1	$f20,0x40($sp)
/*    2c608:	10000005 */ 	b	.L0002c620
/*    2c60c:	e7aa0044 */ 	swc1	$f10,0x44($sp)
/*    2c610:	44814000 */ 	mtc1	$at,$f8
.L0002c614:
/*    2c614:	e7b4003c */ 	swc1	$f20,0x3c($sp)
/*    2c618:	e7b40040 */ 	swc1	$f20,0x40($sp)
/*    2c61c:	e7a80044 */ 	swc1	$f8,0x44($sp)
.L0002c620:
/*    2c620:	8fae0048 */ 	lw	$t6,0x48($sp)
/*    2c624:	00001825 */ 	or	$v1,$zero,$zero
/*    2c628:	91c40001 */ 	lbu	$a0,0x1($t6)
/*    2c62c:	01c01025 */ 	or	$v0,$t6,$zero
/*    2c630:	5880001b */ 	blezl	$a0,.L0002c6a0
/*    2c634:	c7aa003c */ 	lwc1	$f10,0x3c($sp)
/*    2c638:	c4b40000 */ 	lwc1	$f20,0x0($a1)
/*    2c63c:	c4b60008 */ 	lwc1	$f22,0x8($a1)
.L0002c640:
/*    2c640:	c4460018 */ 	lwc1	$f6,0x18($v0)
/*    2c644:	c4440010 */ 	lwc1	$f4,0x10($v0)
/*    2c648:	c7aa0044 */ 	lwc1	$f10,0x44($sp)
/*    2c64c:	46163301 */ 	sub.s	$f12,$f6,$f22
/*    2c650:	24630001 */ 	addiu	$v1,$v1,0x1
/*    2c654:	46142081 */ 	sub.s	$f2,$f4,$f20
/*    2c658:	460c5202 */ 	mul.s	$f8,$f10,$f12
/*    2c65c:	c7a4003c */ 	lwc1	$f4,0x3c($sp)
/*    2c660:	46041182 */ 	mul.s	$f6,$f2,$f4
/*    2c664:	46064000 */ 	add.s	$f0,$f8,$f6
/*    2c668:	4600803c */ 	c.lt.s	$f16,$f0
/*    2c66c:	00000000 */ 	nop
/*    2c670:	45020004 */ 	bc1fl	.L0002c684
/*    2c674:	4612003c */ 	c.lt.s	$f0,$f18
/*    2c678:	10000006 */ 	b	.L0002c694
/*    2c67c:	46000406 */ 	mov.s	$f16,$f0
/*    2c680:	4612003c */ 	c.lt.s	$f0,$f18
.L0002c684:
/*    2c684:	00000000 */ 	nop
/*    2c688:	45000002 */ 	bc1f	.L0002c694
/*    2c68c:	00000000 */ 	nop
/*    2c690:	46000486 */ 	mov.s	$f18,$f0
.L0002c694:
/*    2c694:	1464ffea */ 	bne	$v1,$a0,.L0002c640
/*    2c698:	2442000c */ 	addiu	$v0,$v0,0xc
/*    2c69c:	c7aa003c */ 	lwc1	$f10,0x3c($sp)
.L0002c6a0:
/*    2c6a0:	c4a80000 */ 	lwc1	$f8,0x0($a1)
/*    2c6a4:	8fa20058 */ 	lw	$v0,0x58($sp)
/*    2c6a8:	46105102 */ 	mul.s	$f4,$f10,$f16
/*    2c6ac:	46082180 */ 	add.s	$f6,$f4,$f8
/*    2c6b0:	e4e60000 */ 	swc1	$f6,0x0($a3)
/*    2c6b4:	c4aa0004 */ 	lwc1	$f10,0x4($a1)
/*    2c6b8:	e4ea0004 */ 	swc1	$f10,0x4($a3)
/*    2c6bc:	c7a40044 */ 	lwc1	$f4,0x44($sp)
/*    2c6c0:	c4a60008 */ 	lwc1	$f6,0x8($a1)
/*    2c6c4:	46102202 */ 	mul.s	$f8,$f4,$f16
/*    2c6c8:	46064280 */ 	add.s	$f10,$f8,$f6
/*    2c6cc:	e4ea0008 */ 	swc1	$f10,0x8($a3)
/*    2c6d0:	c7a4003c */ 	lwc1	$f4,0x3c($sp)
/*    2c6d4:	c4a60000 */ 	lwc1	$f6,0x0($a1)
/*    2c6d8:	46122202 */ 	mul.s	$f8,$f4,$f18
/*    2c6dc:	46064280 */ 	add.s	$f10,$f8,$f6
/*    2c6e0:	e44a0000 */ 	swc1	$f10,0x0($v0)
/*    2c6e4:	c4a40004 */ 	lwc1	$f4,0x4($a1)
/*    2c6e8:	e4440004 */ 	swc1	$f4,0x4($v0)
/*    2c6ec:	c7a80044 */ 	lwc1	$f8,0x44($sp)
/*    2c6f0:	c4aa0008 */ 	lwc1	$f10,0x8($a1)
/*    2c6f4:	46124182 */ 	mul.s	$f6,$f8,$f18
/*    2c6f8:	460a3100 */ 	add.s	$f4,$f6,$f10
/*    2c6fc:	e4440008 */ 	swc1	$f4,0x8($v0)
/*    2c700:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*    2c704:	d7b60018 */ 	ldc1	$f22,0x18($sp)
/*    2c708:	d7b40010 */ 	ldc1	$f20,0x10($sp)
/*    2c70c:	03e00008 */ 	jr	$ra
/*    2c710:	27bd0048 */ 	addiu	$sp,$sp,0x48
);

GLOBAL_ASM(
glabel func0002c714
/*    2c714:	27bdfe90 */ 	addiu	$sp,$sp,-368
/*    2c718:	afb3004c */ 	sw	$s3,0x4c($sp)
/*    2c71c:	afb10044 */ 	sw	$s1,0x44($sp)
/*    2c720:	afb00040 */ 	sw	$s0,0x40($sp)
/*    2c724:	0085082b */ 	sltu	$at,$a0,$a1
/*    2c728:	00c08825 */ 	or	$s1,$a2,$zero
/*    2c72c:	00e09825 */ 	or	$s3,$a3,$zero
/*    2c730:	afbf0064 */ 	sw	$ra,0x64($sp)
/*    2c734:	afbe0060 */ 	sw	$s8,0x60($sp)
/*    2c738:	afb7005c */ 	sw	$s7,0x5c($sp)
/*    2c73c:	afb60058 */ 	sw	$s6,0x58($sp)
/*    2c740:	afb50054 */ 	sw	$s5,0x54($sp)
/*    2c744:	afb40050 */ 	sw	$s4,0x50($sp)
/*    2c748:	afb20048 */ 	sw	$s2,0x48($sp)
/*    2c74c:	f7b60038 */ 	sdc1	$f22,0x38($sp)
/*    2c750:	f7b40030 */ 	sdc1	$f20,0x30($sp)
/*    2c754:	afa50174 */ 	sw	$a1,0x174($sp)
/*    2c758:	afa00154 */ 	sw	$zero,0x154($sp)
/*    2c75c:	1020026e */ 	beqz	$at,.L0002d118
/*    2c760:	00808025 */ 	or	$s0,$a0,$zero
/*    2c764:	c7b60190 */ 	lwc1	$f22,0x190($sp)
/*    2c768:	c7b40194 */ 	lwc1	$f20,0x194($sp)
/*    2c76c:	241e000c */ 	addiu	$s8,$zero,0xc
/*    2c770:	8fb70180 */ 	lw	$s7,0x180($sp)
/*    2c774:	8fb60198 */ 	lw	$s6,0x198($sp)
/*    2c778:	8fb501a4 */ 	lw	$s5,0x1a4($sp)
/*    2c77c:	8fb401a0 */ 	lw	$s4,0x1a0($sp)
/*    2c780:	8fb2019c */ 	lw	$s2,0x19c($sp)
/*    2c784:	92020000 */ 	lbu	$v0,0x0($s0)
.L0002c788:
/*    2c788:	24010001 */ 	addiu	$at,$zero,0x1
/*    2c78c:	144000fb */ 	bnez	$v0,.L0002cb7c
/*    2c790:	00000000 */ 	nop
/*    2c794:	afb00150 */ 	sw	$s0,0x150($sp)
/*    2c798:	960f0002 */ 	lhu	$t7,0x2($s0)
/*    2c79c:	24030001 */ 	addiu	$v1,$zero,0x1
/*    2c7a0:	31f80080 */ 	andi	$t8,$t7,0x80
/*    2c7a4:	1300000c */ 	beqz	$t8,.L0002c7d8
/*    2c7a8:	00000000 */ 	nop
/*    2c7ac:	c6200004 */ 	lwc1	$f0,0x4($s1)
/*    2c7b0:	02002025 */ 	or	$a0,$s0,$zero
/*    2c7b4:	02202825 */ 	or	$a1,$s1,$zero
/*    2c7b8:	46140100 */ 	add.s	$f4,$f0,$f20
/*    2c7bc:	24060000 */ 	addiu	$a2,$zero,0x0
/*    2c7c0:	46160180 */ 	add.s	$f6,$f0,$f22
/*    2c7c4:	44072000 */ 	mfc1	$a3,$f4
/*    2c7c8:	0c00a080 */ 	jal	func00028200
/*    2c7cc:	e7a60010 */ 	swc1	$f6,0x10($sp)
/*    2c7d0:	10000001 */ 	b	.L0002c7d8
/*    2c7d4:	00401825 */ 	or	$v1,$v0,$zero
.L0002c7d8:
/*    2c7d8:	106000e0 */ 	beqz	$v1,.L0002cb5c
/*    2c7dc:	97a80186 */ 	lhu	$t0,0x186($sp)
/*    2c7e0:	96190002 */ 	lhu	$t9,0x2($s0)
/*    2c7e4:	03284824 */ 	and	$t1,$t9,$t0
/*    2c7e8:	512000dd */ 	beqzl	$t1,.L0002cb60
/*    2c7ec:	8fa90150 */ 	lw	$t1,0x150($sp)
/*    2c7f0:	920a0006 */ 	lbu	$t2,0x6($s0)
/*    2c7f4:	01505821 */ 	addu	$t3,$t2,$s0
/*    2c7f8:	856c0000 */ 	lh	$t4,0x0($t3)
/*    2c7fc:	448c4000 */ 	mtc1	$t4,$f8
/*    2c800:	00000000 */ 	nop
/*    2c804:	468042a0 */ 	cvt.s.w	$f10,$f8
/*    2c808:	e7aa0144 */ 	swc1	$f10,0x144($sp)
/*    2c80c:	c7b20144 */ 	lwc1	$f18,0x144($sp)
/*    2c810:	c6300000 */ 	lwc1	$f16,0x0($s1)
/*    2c814:	4612803c */ 	c.lt.s	$f16,$f18
/*    2c818:	00000000 */ 	nop
/*    2c81c:	45020007 */ 	bc1fl	.L0002c83c
/*    2c820:	920d0009 */ 	lbu	$t5,0x9($s0)
/*    2c824:	c6640000 */ 	lwc1	$f4,0x0($s3)
/*    2c828:	4612203c */ 	c.lt.s	$f4,$f18
/*    2c82c:	00000000 */ 	nop
/*    2c830:	450300cb */ 	bc1tl	.L0002cb60
/*    2c834:	8fa90150 */ 	lw	$t1,0x150($sp)
/*    2c838:	920d0009 */ 	lbu	$t5,0x9($s0)
.L0002c83c:
/*    2c83c:	01b07021 */ 	addu	$t6,$t5,$s0
/*    2c840:	85cf0000 */ 	lh	$t7,0x0($t6)
/*    2c844:	448f3000 */ 	mtc1	$t7,$f6
/*    2c848:	00000000 */ 	nop
/*    2c84c:	46803220 */ 	cvt.s.w	$f8,$f6
/*    2c850:	e7a80138 */ 	swc1	$f8,0x138($sp)
/*    2c854:	c6300000 */ 	lwc1	$f16,0x0($s1)
/*    2c858:	c7aa0138 */ 	lwc1	$f10,0x138($sp)
/*    2c85c:	4610503c */ 	c.lt.s	$f10,$f16
/*    2c860:	00000000 */ 	nop
/*    2c864:	45020007 */ 	bc1fl	.L0002c884
/*    2c868:	92180008 */ 	lbu	$t8,0x8($s0)
/*    2c86c:	c6640000 */ 	lwc1	$f4,0x0($s3)
/*    2c870:	4604503c */ 	c.lt.s	$f10,$f4
/*    2c874:	00000000 */ 	nop
/*    2c878:	450300b9 */ 	bc1tl	.L0002cb60
/*    2c87c:	8fa90150 */ 	lw	$t1,0x150($sp)
/*    2c880:	92180008 */ 	lbu	$t8,0x8($s0)
.L0002c884:
/*    2c884:	0310c821 */ 	addu	$t9,$t8,$s0
/*    2c888:	87280000 */ 	lh	$t0,0x0($t9)
/*    2c88c:	44889000 */ 	mtc1	$t0,$f18
/*    2c890:	00000000 */ 	nop
/*    2c894:	468091a0 */ 	cvt.s.w	$f6,$f18
/*    2c898:	e7a6014c */ 	swc1	$f6,0x14c($sp)
/*    2c89c:	c7b0014c */ 	lwc1	$f16,0x14c($sp)
/*    2c8a0:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*    2c8a4:	4610403c */ 	c.lt.s	$f8,$f16
/*    2c8a8:	00000000 */ 	nop
/*    2c8ac:	45020007 */ 	bc1fl	.L0002c8cc
/*    2c8b0:	9209000b */ 	lbu	$t1,0xb($s0)
/*    2c8b4:	c66a0008 */ 	lwc1	$f10,0x8($s3)
/*    2c8b8:	4610503c */ 	c.lt.s	$f10,$f16
/*    2c8bc:	00000000 */ 	nop
/*    2c8c0:	450300a7 */ 	bc1tl	.L0002cb60
/*    2c8c4:	8fa90150 */ 	lw	$t1,0x150($sp)
/*    2c8c8:	9209000b */ 	lbu	$t1,0xb($s0)
.L0002c8cc:
/*    2c8cc:	8fac0188 */ 	lw	$t4,0x188($sp)
/*    2c8d0:	01305021 */ 	addu	$t2,$t1,$s0
/*    2c8d4:	854b0000 */ 	lh	$t3,0x0($t2)
/*    2c8d8:	448b2000 */ 	mtc1	$t3,$f4
/*    2c8dc:	00000000 */ 	nop
/*    2c8e0:	468024a0 */ 	cvt.s.w	$f18,$f4
/*    2c8e4:	e7b20140 */ 	swc1	$f18,0x140($sp)
/*    2c8e8:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*    2c8ec:	c7a60140 */ 	lwc1	$f6,0x140($sp)
/*    2c8f0:	4608303c */ 	c.lt.s	$f6,$f8
/*    2c8f4:	00000000 */ 	nop
/*    2c8f8:	45000006 */ 	bc1f	.L0002c914
/*    2c8fc:	00000000 */ 	nop
/*    2c900:	c66a0008 */ 	lwc1	$f10,0x8($s3)
/*    2c904:	460a303c */ 	c.lt.s	$f6,$f10
/*    2c908:	00000000 */ 	nop
/*    2c90c:	45030094 */ 	bc1tl	.L0002cb60
/*    2c910:	8fa90150 */ 	lw	$t1,0x150($sp)
.L0002c914:
/*    2c914:	11800058 */ 	beqz	$t4,.L0002ca78
/*    2c918:	02202025 */ 	or	$a0,$s1,$zero
/*    2c91c:	920d0007 */ 	lbu	$t5,0x7($s0)
/*    2c920:	01b07021 */ 	addu	$t6,$t5,$s0
/*    2c924:	85cf0000 */ 	lh	$t7,0x0($t6)
/*    2c928:	448f8000 */ 	mtc1	$t7,$f16
/*    2c92c:	00000000 */ 	nop
/*    2c930:	46808120 */ 	cvt.s.w	$f4,$f16
/*    2c934:	e7a40148 */ 	swc1	$f4,0x148($sp)
/*    2c938:	9218000a */ 	lbu	$t8,0xa($s0)
/*    2c93c:	c7a60148 */ 	lwc1	$f6,0x148($sp)
/*    2c940:	0310c821 */ 	addu	$t9,$t8,$s0
/*    2c944:	87280000 */ 	lh	$t0,0x0($t9)
/*    2c948:	44889000 */ 	mtc1	$t0,$f18
/*    2c94c:	00000000 */ 	nop
/*    2c950:	46809220 */ 	cvt.s.w	$f8,$f18
/*    2c954:	e7a8013c */ 	swc1	$f8,0x13c($sp)
/*    2c958:	c6200004 */ 	lwc1	$f0,0x4($s1)
/*    2c95c:	c7b0013c */ 	lwc1	$f16,0x13c($sp)
/*    2c960:	4606003c */ 	c.lt.s	$f0,$f6
/*    2c964:	00000000 */ 	nop
/*    2c968:	45020007 */ 	bc1fl	.L0002c988
/*    2c96c:	4600803c */ 	c.lt.s	$f16,$f0
/*    2c970:	c66a0004 */ 	lwc1	$f10,0x4($s3)
/*    2c974:	4606503c */ 	c.lt.s	$f10,$f6
/*    2c978:	00000000 */ 	nop
/*    2c97c:	45030078 */ 	bc1tl	.L0002cb60
/*    2c980:	8fa90150 */ 	lw	$t1,0x150($sp)
/*    2c984:	4600803c */ 	c.lt.s	$f16,$f0
.L0002c988:
/*    2c988:	02202025 */ 	or	$a0,$s1,$zero
/*    2c98c:	02e02825 */ 	or	$a1,$s7,$zero
/*    2c990:	27a60144 */ 	addiu	$a2,$sp,0x144
/*    2c994:	45000006 */ 	bc1f	.L0002c9b0
/*    2c998:	00000000 */ 	nop
/*    2c99c:	c6640004 */ 	lwc1	$f4,0x4($s3)
/*    2c9a0:	4604803c */ 	c.lt.s	$f16,$f4
/*    2c9a4:	00000000 */ 	nop
/*    2c9a8:	4503006d */ 	bc1tl	.L0002cb60
/*    2c9ac:	8fa90150 */ 	lw	$t1,0x150($sp)
.L0002c9b0:
/*    2c9b0:	0fc57cac */ 	jal	func0f15f2b0
/*    2c9b4:	27a70138 */ 	addiu	$a3,$sp,0x138
/*    2c9b8:	10400068 */ 	beqz	$v0,.L0002cb5c
/*    2c9bc:	02202025 */ 	or	$a0,$s1,$zero
/*    2c9c0:	27a9012c */ 	addiu	$t1,$sp,0x12c
/*    2c9c4:	27aa0120 */ 	addiu	$t2,$sp,0x120
/*    2c9c8:	afaa0014 */ 	sw	$t2,0x14($sp)
/*    2c9cc:	afa90010 */ 	sw	$t1,0x10($sp)
/*    2c9d0:	02602825 */ 	or	$a1,$s3,$zero
/*    2c9d4:	02e03025 */ 	or	$a2,$s7,$zero
/*    2c9d8:	0c00aab0 */ 	jal	func0002aac0
/*    2c9dc:	02003825 */ 	or	$a3,$s0,$zero
/*    2c9e0:	1040005e */ 	beqz	$v0,.L0002cb5c
/*    2c9e4:	c7b2012c */ 	lwc1	$f18,0x12c($sp)
/*    2c9e8:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*    2c9ec:	c7aa0130 */ 	lwc1	$f10,0x130($sp)
/*    2c9f0:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*    2c9f4:	46089001 */ 	sub.s	$f0,$f18,$f8
/*    2c9f8:	c7b00134 */ 	lwc1	$f16,0x134($sp)
/*    2c9fc:	c6240008 */ 	lwc1	$f4,0x8($s1)
/*    2ca00:	46065081 */ 	sub.s	$f2,$f10,$f6
/*    2ca04:	46000482 */ 	mul.s	$f18,$f0,$f0
/*    2ca08:	240b0001 */ 	addiu	$t3,$zero,0x1
/*    2ca0c:	46048301 */ 	sub.s	$f12,$f16,$f4
/*    2ca10:	46021202 */ 	mul.s	$f8,$f2,$f2
/*    2ca14:	c6d00000 */ 	lwc1	$f16,0x0($s6)
/*    2ca18:	460c6182 */ 	mul.s	$f6,$f12,$f12
/*    2ca1c:	46089280 */ 	add.s	$f10,$f18,$f8
/*    2ca20:	46065380 */ 	add.s	$f14,$f10,$f6
/*    2ca24:	4610703c */ 	c.lt.s	$f14,$f16
/*    2ca28:	00000000 */ 	nop
/*    2ca2c:	4502004c */ 	bc1fl	.L0002cb60
/*    2ca30:	8fa90150 */ 	lw	$t1,0x150($sp)
/*    2ca34:	afab0154 */ 	sw	$t3,0x154($sp)
/*    2ca38:	e6ce0000 */ 	swc1	$f14,0x0($s6)
/*    2ca3c:	c7a4012c */ 	lwc1	$f4,0x12c($sp)
/*    2ca40:	02002025 */ 	or	$a0,$s0,$zero
/*    2ca44:	27a5012c */ 	addiu	$a1,$sp,0x12c
/*    2ca48:	e6440000 */ 	swc1	$f4,0x0($s2)
/*    2ca4c:	c7b20130 */ 	lwc1	$f18,0x130($sp)
/*    2ca50:	27a60120 */ 	addiu	$a2,$sp,0x120
/*    2ca54:	02803825 */ 	or	$a3,$s4,$zero
/*    2ca58:	e6520004 */ 	swc1	$f18,0x4($s2)
/*    2ca5c:	c7a80134 */ 	lwc1	$f8,0x134($sp)
/*    2ca60:	e6480008 */ 	swc1	$f8,0x8($s2)
/*    2ca64:	0c00b0ca */ 	jal	func0002c328
/*    2ca68:	afb50010 */ 	sw	$s5,0x10($sp)
/*    2ca6c:	8fac01a8 */ 	lw	$t4,0x1a8($sp)
/*    2ca70:	1000003a */ 	b	.L0002cb5c
/*    2ca74:	ad900000 */ 	sw	$s0,0x0($t4)
.L0002ca78:
/*    2ca78:	8fb8018c */ 	lw	$t8,0x18c($sp)
/*    2ca7c:	27ad012c */ 	addiu	$t5,$sp,0x12c
/*    2ca80:	27ae0114 */ 	addiu	$t6,$sp,0x114
/*    2ca84:	27af0108 */ 	addiu	$t7,$sp,0x108
/*    2ca88:	afaf0018 */ 	sw	$t7,0x18($sp)
/*    2ca8c:	afae0014 */ 	sw	$t6,0x14($sp)
/*    2ca90:	afad0010 */ 	sw	$t5,0x10($sp)
/*    2ca94:	02602825 */ 	or	$a1,$s3,$zero
/*    2ca98:	02e03025 */ 	or	$a2,$s7,$zero
/*    2ca9c:	02003825 */ 	or	$a3,$s0,$zero
/*    2caa0:	e7b60020 */ 	swc1	$f22,0x20($sp)
/*    2caa4:	e7b40024 */ 	swc1	$f20,0x24($sp)
/*    2caa8:	0c00ab1c */ 	jal	func0002ac70
/*    2caac:	afb8001c */ 	sw	$t8,0x1c($sp)
/*    2cab0:	1040002a */ 	beqz	$v0,.L0002cb5c
/*    2cab4:	c7aa012c */ 	lwc1	$f10,0x12c($sp)
/*    2cab8:	c6260000 */ 	lwc1	$f6,0x0($s1)
/*    2cabc:	c7b00130 */ 	lwc1	$f16,0x130($sp)
/*    2cac0:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*    2cac4:	46065001 */ 	sub.s	$f0,$f10,$f6
/*    2cac8:	c7b20134 */ 	lwc1	$f18,0x134($sp)
/*    2cacc:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*    2cad0:	46048081 */ 	sub.s	$f2,$f16,$f4
/*    2cad4:	46000282 */ 	mul.s	$f10,$f0,$f0
/*    2cad8:	24190001 */ 	addiu	$t9,$zero,0x1
/*    2cadc:	46089301 */ 	sub.s	$f12,$f18,$f8
/*    2cae0:	46021182 */ 	mul.s	$f6,$f2,$f2
/*    2cae4:	c6d20000 */ 	lwc1	$f18,0x0($s6)
/*    2cae8:	460c6102 */ 	mul.s	$f4,$f12,$f12
/*    2caec:	46065400 */ 	add.s	$f16,$f10,$f6
/*    2caf0:	46048380 */ 	add.s	$f14,$f16,$f4
/*    2caf4:	4612703c */ 	c.lt.s	$f14,$f18
/*    2caf8:	00000000 */ 	nop
/*    2cafc:	45020018 */ 	bc1fl	.L0002cb60
/*    2cb00:	8fa90150 */ 	lw	$t1,0x150($sp)
/*    2cb04:	afb90154 */ 	sw	$t9,0x154($sp)
/*    2cb08:	e6ce0000 */ 	swc1	$f14,0x0($s6)
/*    2cb0c:	c7a8012c */ 	lwc1	$f8,0x12c($sp)
/*    2cb10:	e6480000 */ 	swc1	$f8,0x0($s2)
/*    2cb14:	c7aa0130 */ 	lwc1	$f10,0x130($sp)
/*    2cb18:	e64a0004 */ 	swc1	$f10,0x4($s2)
/*    2cb1c:	c7a60134 */ 	lwc1	$f6,0x134($sp)
/*    2cb20:	e6460008 */ 	swc1	$f6,0x8($s2)
/*    2cb24:	c7b00114 */ 	lwc1	$f16,0x114($sp)
/*    2cb28:	e6900000 */ 	swc1	$f16,0x0($s4)
/*    2cb2c:	c7a40118 */ 	lwc1	$f4,0x118($sp)
/*    2cb30:	e6840004 */ 	swc1	$f4,0x4($s4)
/*    2cb34:	c7b2011c */ 	lwc1	$f18,0x11c($sp)
/*    2cb38:	e6920008 */ 	swc1	$f18,0x8($s4)
/*    2cb3c:	c7a80108 */ 	lwc1	$f8,0x108($sp)
/*    2cb40:	e6a80000 */ 	swc1	$f8,0x0($s5)
/*    2cb44:	c7aa010c */ 	lwc1	$f10,0x10c($sp)
/*    2cb48:	e6aa0004 */ 	swc1	$f10,0x4($s5)
/*    2cb4c:	c7a60110 */ 	lwc1	$f6,0x110($sp)
/*    2cb50:	e6a60008 */ 	swc1	$f6,0x8($s5)
/*    2cb54:	8fa801a8 */ 	lw	$t0,0x1a8($sp)
/*    2cb58:	ad100000 */ 	sw	$s0,0x0($t0)
.L0002cb5c:
/*    2cb5c:	8fa90150 */ 	lw	$t1,0x150($sp)
.L0002cb60:
/*    2cb60:	912a0001 */ 	lbu	$t2,0x1($t1)
/*    2cb64:	000a5880 */ 	sll	$t3,$t2,0x2
/*    2cb68:	016a5823 */ 	subu	$t3,$t3,$t2
/*    2cb6c:	000b5840 */ 	sll	$t3,$t3,0x1
/*    2cb70:	020b8021 */ 	addu	$s0,$s0,$t3
/*    2cb74:	10000164 */ 	b	.L0002d108
/*    2cb78:	2610000e */ 	addiu	$s0,$s0,0xe
.L0002cb7c:
/*    2cb7c:	544100e1 */ 	bnel	$v0,$at,.L0002cf04
/*    2cb80:	24010002 */ 	addiu	$at,$zero,0x2
/*    2cb84:	afb00104 */ 	sw	$s0,0x104($sp)
/*    2cb88:	960c0002 */ 	lhu	$t4,0x2($s0)
/*    2cb8c:	97ad0186 */ 	lhu	$t5,0x186($sp)
/*    2cb90:	018d7024 */ 	and	$t6,$t4,$t5
/*    2cb94:	51c000d3 */ 	beqzl	$t6,.L0002cee4
/*    2cb98:	8fae0104 */ 	lw	$t6,0x104($sp)
/*    2cb9c:	920f0006 */ 	lbu	$t7,0x6($s0)
/*    2cba0:	01fe0019 */ 	multu	$t7,$s8
/*    2cba4:	0000c012 */ 	mflo	$t8
/*    2cba8:	0218c821 */ 	addu	$t9,$s0,$t8
/*    2cbac:	c7300010 */ 	lwc1	$f16,0x10($t9)
/*    2cbb0:	e7b000f8 */ 	swc1	$f16,0xf8($sp)
/*    2cbb4:	92080009 */ 	lbu	$t0,0x9($s0)
/*    2cbb8:	c7aa00f8 */ 	lwc1	$f10,0xf8($sp)
/*    2cbbc:	011e0019 */ 	multu	$t0,$s8
/*    2cbc0:	00004812 */ 	mflo	$t1
/*    2cbc4:	02095021 */ 	addu	$t2,$s0,$t1
/*    2cbc8:	c5440010 */ 	lwc1	$f4,0x10($t2)
/*    2cbcc:	e7a400ec */ 	swc1	$f4,0xec($sp)
/*    2cbd0:	920b0008 */ 	lbu	$t3,0x8($s0)
/*    2cbd4:	c7b000ec */ 	lwc1	$f16,0xec($sp)
/*    2cbd8:	017e0019 */ 	multu	$t3,$s8
/*    2cbdc:	00006012 */ 	mflo	$t4
/*    2cbe0:	020c6821 */ 	addu	$t5,$s0,$t4
/*    2cbe4:	c5b20018 */ 	lwc1	$f18,0x18($t5)
/*    2cbe8:	e7b20100 */ 	swc1	$f18,0x100($sp)
/*    2cbec:	920e000b */ 	lbu	$t6,0xb($s0)
/*    2cbf0:	01de0019 */ 	multu	$t6,$s8
/*    2cbf4:	00007812 */ 	mflo	$t7
/*    2cbf8:	020fc021 */ 	addu	$t8,$s0,$t7
/*    2cbfc:	c7080018 */ 	lwc1	$f8,0x18($t8)
/*    2cc00:	e7a800f4 */ 	swc1	$f8,0xf4($sp)
/*    2cc04:	c6200000 */ 	lwc1	$f0,0x0($s1)
/*    2cc08:	460a003c */ 	c.lt.s	$f0,$f10
/*    2cc0c:	00000000 */ 	nop
/*    2cc10:	45020007 */ 	bc1fl	.L0002cc30
/*    2cc14:	4600803c */ 	c.lt.s	$f16,$f0
/*    2cc18:	c6660000 */ 	lwc1	$f6,0x0($s3)
/*    2cc1c:	460a303c */ 	c.lt.s	$f6,$f10
/*    2cc20:	00000000 */ 	nop
/*    2cc24:	450300af */ 	bc1tl	.L0002cee4
/*    2cc28:	8fae0104 */ 	lw	$t6,0x104($sp)
/*    2cc2c:	4600803c */ 	c.lt.s	$f16,$f0
.L0002cc30:
/*    2cc30:	c7b20100 */ 	lwc1	$f18,0x100($sp)
/*    2cc34:	45020007 */ 	bc1fl	.L0002cc54
/*    2cc38:	c6200008 */ 	lwc1	$f0,0x8($s1)
/*    2cc3c:	c6640000 */ 	lwc1	$f4,0x0($s3)
/*    2cc40:	4604803c */ 	c.lt.s	$f16,$f4
/*    2cc44:	00000000 */ 	nop
/*    2cc48:	450300a6 */ 	bc1tl	.L0002cee4
/*    2cc4c:	8fae0104 */ 	lw	$t6,0x104($sp)
/*    2cc50:	c6200008 */ 	lwc1	$f0,0x8($s1)
.L0002cc54:
/*    2cc54:	c7a600f4 */ 	lwc1	$f6,0xf4($sp)
/*    2cc58:	4612003c */ 	c.lt.s	$f0,$f18
/*    2cc5c:	00000000 */ 	nop
/*    2cc60:	45020007 */ 	bc1fl	.L0002cc80
/*    2cc64:	4600303c */ 	c.lt.s	$f6,$f0
/*    2cc68:	c6680008 */ 	lwc1	$f8,0x8($s3)
/*    2cc6c:	4612403c */ 	c.lt.s	$f8,$f18
/*    2cc70:	00000000 */ 	nop
/*    2cc74:	4503009b */ 	bc1tl	.L0002cee4
/*    2cc78:	8fae0104 */ 	lw	$t6,0x104($sp)
/*    2cc7c:	4600303c */ 	c.lt.s	$f6,$f0
.L0002cc80:
/*    2cc80:	8fb90188 */ 	lw	$t9,0x188($sp)
/*    2cc84:	45000006 */ 	bc1f	.L0002cca0
/*    2cc88:	00000000 */ 	nop
/*    2cc8c:	c66a0008 */ 	lwc1	$f10,0x8($s3)
/*    2cc90:	460a303c */ 	c.lt.s	$f6,$f10
/*    2cc94:	00000000 */ 	nop
/*    2cc98:	45030092 */ 	bc1tl	.L0002cee4
/*    2cc9c:	8fae0104 */ 	lw	$t6,0x104($sp)
.L0002cca0:
/*    2cca0:	13200056 */ 	beqz	$t9,.L0002cdfc
/*    2cca4:	02202025 */ 	or	$a0,$s1,$zero
/*    2cca8:	92080007 */ 	lbu	$t0,0x7($s0)
/*    2ccac:	011e0019 */ 	multu	$t0,$s8
/*    2ccb0:	00004812 */ 	mflo	$t1
/*    2ccb4:	02095021 */ 	addu	$t2,$s0,$t1
/*    2ccb8:	c5500014 */ 	lwc1	$f16,0x14($t2)
/*    2ccbc:	e7b000fc */ 	swc1	$f16,0xfc($sp)
/*    2ccc0:	920b000a */ 	lbu	$t3,0xa($s0)
/*    2ccc4:	c7a800fc */ 	lwc1	$f8,0xfc($sp)
/*    2ccc8:	017e0019 */ 	multu	$t3,$s8
/*    2cccc:	00006012 */ 	mflo	$t4
/*    2ccd0:	020c6821 */ 	addu	$t5,$s0,$t4
/*    2ccd4:	c5a40014 */ 	lwc1	$f4,0x14($t5)
/*    2ccd8:	e7a400f0 */ 	swc1	$f4,0xf0($sp)
/*    2ccdc:	c6200004 */ 	lwc1	$f0,0x4($s1)
/*    2cce0:	c7a600f0 */ 	lwc1	$f6,0xf0($sp)
/*    2cce4:	4608003c */ 	c.lt.s	$f0,$f8
/*    2cce8:	00000000 */ 	nop
/*    2ccec:	45020007 */ 	bc1fl	.L0002cd0c
/*    2ccf0:	4600303c */ 	c.lt.s	$f6,$f0
/*    2ccf4:	c6720004 */ 	lwc1	$f18,0x4($s3)
/*    2ccf8:	4608903c */ 	c.lt.s	$f18,$f8
/*    2ccfc:	00000000 */ 	nop
/*    2cd00:	45030078 */ 	bc1tl	.L0002cee4
/*    2cd04:	8fae0104 */ 	lw	$t6,0x104($sp)
/*    2cd08:	4600303c */ 	c.lt.s	$f6,$f0
.L0002cd0c:
/*    2cd0c:	02202025 */ 	or	$a0,$s1,$zero
/*    2cd10:	02e02825 */ 	or	$a1,$s7,$zero
/*    2cd14:	27a600f8 */ 	addiu	$a2,$sp,0xf8
/*    2cd18:	45000006 */ 	bc1f	.L0002cd34
/*    2cd1c:	00000000 */ 	nop
/*    2cd20:	c66a0004 */ 	lwc1	$f10,0x4($s3)
/*    2cd24:	460a303c */ 	c.lt.s	$f6,$f10
/*    2cd28:	00000000 */ 	nop
/*    2cd2c:	4503006d */ 	bc1tl	.L0002cee4
/*    2cd30:	8fae0104 */ 	lw	$t6,0x104($sp)
.L0002cd34:
/*    2cd34:	0fc57cac */ 	jal	func0f15f2b0
/*    2cd38:	27a700ec */ 	addiu	$a3,$sp,0xec
/*    2cd3c:	10400068 */ 	beqz	$v0,.L0002cee0
/*    2cd40:	02202025 */ 	or	$a0,$s1,$zero
/*    2cd44:	27ae00e0 */ 	addiu	$t6,$sp,0xe0
/*    2cd48:	27af00d4 */ 	addiu	$t7,$sp,0xd4
/*    2cd4c:	afaf0014 */ 	sw	$t7,0x14($sp)
/*    2cd50:	afae0010 */ 	sw	$t6,0x10($sp)
/*    2cd54:	02602825 */ 	or	$a1,$s3,$zero
/*    2cd58:	02e03025 */ 	or	$a2,$s7,$zero
/*    2cd5c:	0c00aae6 */ 	jal	func0002ab98
/*    2cd60:	02003825 */ 	or	$a3,$s0,$zero
/*    2cd64:	1040005e */ 	beqz	$v0,.L0002cee0
/*    2cd68:	c7b000e0 */ 	lwc1	$f16,0xe0($sp)
/*    2cd6c:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*    2cd70:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
/*    2cd74:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*    2cd78:	46048001 */ 	sub.s	$f0,$f16,$f4
/*    2cd7c:	c7a600e8 */ 	lwc1	$f6,0xe8($sp)
/*    2cd80:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*    2cd84:	46089081 */ 	sub.s	$f2,$f18,$f8
/*    2cd88:	46000402 */ 	mul.s	$f16,$f0,$f0
/*    2cd8c:	24180001 */ 	addiu	$t8,$zero,0x1
/*    2cd90:	460a3301 */ 	sub.s	$f12,$f6,$f10
/*    2cd94:	46021102 */ 	mul.s	$f4,$f2,$f2
/*    2cd98:	c6c60000 */ 	lwc1	$f6,0x0($s6)
/*    2cd9c:	460c6202 */ 	mul.s	$f8,$f12,$f12
/*    2cda0:	46048480 */ 	add.s	$f18,$f16,$f4
/*    2cda4:	46089380 */ 	add.s	$f14,$f18,$f8
/*    2cda8:	4606703c */ 	c.lt.s	$f14,$f6
/*    2cdac:	00000000 */ 	nop
/*    2cdb0:	4502004c */ 	bc1fl	.L0002cee4
/*    2cdb4:	8fae0104 */ 	lw	$t6,0x104($sp)
/*    2cdb8:	afb80154 */ 	sw	$t8,0x154($sp)
/*    2cdbc:	e6ce0000 */ 	swc1	$f14,0x0($s6)
/*    2cdc0:	c7aa00e0 */ 	lwc1	$f10,0xe0($sp)
/*    2cdc4:	02002025 */ 	or	$a0,$s0,$zero
/*    2cdc8:	27a500e0 */ 	addiu	$a1,$sp,0xe0
/*    2cdcc:	e64a0000 */ 	swc1	$f10,0x0($s2)
/*    2cdd0:	c7b000e4 */ 	lwc1	$f16,0xe4($sp)
/*    2cdd4:	27a600d4 */ 	addiu	$a2,$sp,0xd4
/*    2cdd8:	02803825 */ 	or	$a3,$s4,$zero
/*    2cddc:	e6500004 */ 	swc1	$f16,0x4($s2)
/*    2cde0:	c7a400e8 */ 	lwc1	$f4,0xe8($sp)
/*    2cde4:	e6440008 */ 	swc1	$f4,0x8($s2)
/*    2cde8:	0c00b14a */ 	jal	func0002c528
/*    2cdec:	afb50010 */ 	sw	$s5,0x10($sp)
/*    2cdf0:	8fb901a8 */ 	lw	$t9,0x1a8($sp)
/*    2cdf4:	1000003a */ 	b	.L0002cee0
/*    2cdf8:	af300000 */ 	sw	$s0,0x0($t9)
.L0002cdfc:
/*    2cdfc:	8fab018c */ 	lw	$t3,0x18c($sp)
/*    2ce00:	27a800e0 */ 	addiu	$t0,$sp,0xe0
/*    2ce04:	27a900c8 */ 	addiu	$t1,$sp,0xc8
/*    2ce08:	27aa00bc */ 	addiu	$t2,$sp,0xbc
/*    2ce0c:	afaa0018 */ 	sw	$t2,0x18($sp)
/*    2ce10:	afa90014 */ 	sw	$t1,0x14($sp)
/*    2ce14:	afa80010 */ 	sw	$t0,0x10($sp)
/*    2ce18:	02602825 */ 	or	$a1,$s3,$zero
/*    2ce1c:	02e03025 */ 	or	$a2,$s7,$zero
/*    2ce20:	02003825 */ 	or	$a3,$s0,$zero
/*    2ce24:	e7b60020 */ 	swc1	$f22,0x20($sp)
/*    2ce28:	e7b40024 */ 	swc1	$f20,0x24($sp)
/*    2ce2c:	0c00ac4a */ 	jal	func0002b128
/*    2ce30:	afab001c */ 	sw	$t3,0x1c($sp)
/*    2ce34:	1040002a */ 	beqz	$v0,.L0002cee0
/*    2ce38:	c7b200e0 */ 	lwc1	$f18,0xe0($sp)
/*    2ce3c:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*    2ce40:	c7a600e4 */ 	lwc1	$f6,0xe4($sp)
/*    2ce44:	c62a0004 */ 	lwc1	$f10,0x4($s1)
/*    2ce48:	46089001 */ 	sub.s	$f0,$f18,$f8
/*    2ce4c:	c7b000e8 */ 	lwc1	$f16,0xe8($sp)
/*    2ce50:	c6240008 */ 	lwc1	$f4,0x8($s1)
/*    2ce54:	460a3081 */ 	sub.s	$f2,$f6,$f10
/*    2ce58:	46000482 */ 	mul.s	$f18,$f0,$f0
/*    2ce5c:	240c0001 */ 	addiu	$t4,$zero,0x1
/*    2ce60:	46048301 */ 	sub.s	$f12,$f16,$f4
/*    2ce64:	46021202 */ 	mul.s	$f8,$f2,$f2
/*    2ce68:	c6d00000 */ 	lwc1	$f16,0x0($s6)
/*    2ce6c:	460c6282 */ 	mul.s	$f10,$f12,$f12
/*    2ce70:	46089180 */ 	add.s	$f6,$f18,$f8
/*    2ce74:	460a3380 */ 	add.s	$f14,$f6,$f10
/*    2ce78:	4610703c */ 	c.lt.s	$f14,$f16
/*    2ce7c:	00000000 */ 	nop
/*    2ce80:	45020018 */ 	bc1fl	.L0002cee4
/*    2ce84:	8fae0104 */ 	lw	$t6,0x104($sp)
/*    2ce88:	afac0154 */ 	sw	$t4,0x154($sp)
/*    2ce8c:	e6ce0000 */ 	swc1	$f14,0x0($s6)
/*    2ce90:	c7a400e0 */ 	lwc1	$f4,0xe0($sp)
/*    2ce94:	e6440000 */ 	swc1	$f4,0x0($s2)
/*    2ce98:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
/*    2ce9c:	e6520004 */ 	swc1	$f18,0x4($s2)
/*    2cea0:	c7a800e8 */ 	lwc1	$f8,0xe8($sp)
/*    2cea4:	e6480008 */ 	swc1	$f8,0x8($s2)
/*    2cea8:	c7a600c8 */ 	lwc1	$f6,0xc8($sp)
/*    2ceac:	e6860000 */ 	swc1	$f6,0x0($s4)
/*    2ceb0:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*    2ceb4:	e68a0004 */ 	swc1	$f10,0x4($s4)
/*    2ceb8:	c7b000d0 */ 	lwc1	$f16,0xd0($sp)
/*    2cebc:	e6900008 */ 	swc1	$f16,0x8($s4)
/*    2cec0:	c7a400bc */ 	lwc1	$f4,0xbc($sp)
/*    2cec4:	e6a40000 */ 	swc1	$f4,0x0($s5)
/*    2cec8:	c7b200c0 */ 	lwc1	$f18,0xc0($sp)
/*    2cecc:	e6b20004 */ 	swc1	$f18,0x4($s5)
/*    2ced0:	c7a800c4 */ 	lwc1	$f8,0xc4($sp)
/*    2ced4:	e6a80008 */ 	swc1	$f8,0x8($s5)
/*    2ced8:	8fad01a8 */ 	lw	$t5,0x1a8($sp)
/*    2cedc:	adb00000 */ 	sw	$s0,0x0($t5)
.L0002cee0:
/*    2cee0:	8fae0104 */ 	lw	$t6,0x104($sp)
.L0002cee4:
/*    2cee4:	91cf0001 */ 	lbu	$t7,0x1($t6)
/*    2cee8:	25f8ffc0 */ 	addiu	$t8,$t7,-64
/*    2ceec:	031e0019 */ 	multu	$t8,$s8
/*    2cef0:	0000c812 */ 	mflo	$t9
/*    2cef4:	02198021 */ 	addu	$s0,$s0,$t9
/*    2cef8:	10000083 */ 	b	.L0002d108
/*    2cefc:	26100310 */ 	addiu	$s0,$s0,0x310
/*    2cf00:	24010002 */ 	addiu	$at,$zero,0x2
.L0002cf04:
/*    2cf04:	1441003f */ 	bne	$v0,$at,.L0002d004
/*    2cf08:	97a80186 */ 	lhu	$t0,0x186($sp)
/*    2cf0c:	3109001c */ 	andi	$t1,$t0,0x1c
/*    2cf10:	1120003a */ 	beqz	$t1,.L0002cffc
/*    2cf14:	02202025 */ 	or	$a0,$s1,$zero
/*    2cf18:	8fad018c */ 	lw	$t5,0x18c($sp)
/*    2cf1c:	27aa00b0 */ 	addiu	$t2,$sp,0xb0
/*    2cf20:	27ab00a4 */ 	addiu	$t3,$sp,0xa4
/*    2cf24:	27ac0098 */ 	addiu	$t4,$sp,0x98
/*    2cf28:	afac0018 */ 	sw	$t4,0x18($sp)
/*    2cf2c:	afab0014 */ 	sw	$t3,0x14($sp)
/*    2cf30:	afaa0010 */ 	sw	$t2,0x10($sp)
/*    2cf34:	02602825 */ 	or	$a1,$s3,$zero
/*    2cf38:	02e03025 */ 	or	$a2,$s7,$zero
/*    2cf3c:	02003825 */ 	or	$a3,$s0,$zero
/*    2cf40:	e7b60020 */ 	swc1	$f22,0x20($sp)
/*    2cf44:	e7b40024 */ 	swc1	$f20,0x24($sp)
/*    2cf48:	0c00ad58 */ 	jal	func0002b560
/*    2cf4c:	afad001c */ 	sw	$t5,0x1c($sp)
/*    2cf50:	1040002a */ 	beqz	$v0,.L0002cffc
/*    2cf54:	c7a600b0 */ 	lwc1	$f6,0xb0($sp)
/*    2cf58:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*    2cf5c:	c7b000b4 */ 	lwc1	$f16,0xb4($sp)
/*    2cf60:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*    2cf64:	460a3001 */ 	sub.s	$f0,$f6,$f10
/*    2cf68:	c7b200b8 */ 	lwc1	$f18,0xb8($sp)
/*    2cf6c:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*    2cf70:	46048081 */ 	sub.s	$f2,$f16,$f4
/*    2cf74:	46000182 */ 	mul.s	$f6,$f0,$f0
/*    2cf78:	240e0001 */ 	addiu	$t6,$zero,0x1
/*    2cf7c:	46089301 */ 	sub.s	$f12,$f18,$f8
/*    2cf80:	46021282 */ 	mul.s	$f10,$f2,$f2
/*    2cf84:	c6d20000 */ 	lwc1	$f18,0x0($s6)
/*    2cf88:	460c6102 */ 	mul.s	$f4,$f12,$f12
/*    2cf8c:	460a3400 */ 	add.s	$f16,$f6,$f10
/*    2cf90:	46048380 */ 	add.s	$f14,$f16,$f4
/*    2cf94:	4612703c */ 	c.lt.s	$f14,$f18
/*    2cf98:	00000000 */ 	nop
/*    2cf9c:	45000017 */ 	bc1f	.L0002cffc
/*    2cfa0:	00000000 */ 	nop
/*    2cfa4:	afae0154 */ 	sw	$t6,0x154($sp)
/*    2cfa8:	e6ce0000 */ 	swc1	$f14,0x0($s6)
/*    2cfac:	c7a800b0 */ 	lwc1	$f8,0xb0($sp)
/*    2cfb0:	e6480000 */ 	swc1	$f8,0x0($s2)
/*    2cfb4:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*    2cfb8:	e6460004 */ 	swc1	$f6,0x4($s2)
/*    2cfbc:	c7aa00b8 */ 	lwc1	$f10,0xb8($sp)
/*    2cfc0:	e64a0008 */ 	swc1	$f10,0x8($s2)
/*    2cfc4:	c7b000a4 */ 	lwc1	$f16,0xa4($sp)
/*    2cfc8:	e6900000 */ 	swc1	$f16,0x0($s4)
/*    2cfcc:	c7a400a8 */ 	lwc1	$f4,0xa8($sp)
/*    2cfd0:	e6840004 */ 	swc1	$f4,0x4($s4)
/*    2cfd4:	c7b200ac */ 	lwc1	$f18,0xac($sp)
/*    2cfd8:	e6920008 */ 	swc1	$f18,0x8($s4)
/*    2cfdc:	c7a80098 */ 	lwc1	$f8,0x98($sp)
/*    2cfe0:	e6a80000 */ 	swc1	$f8,0x0($s5)
/*    2cfe4:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
/*    2cfe8:	e6a60004 */ 	swc1	$f6,0x4($s5)
/*    2cfec:	c7aa00a0 */ 	lwc1	$f10,0xa0($sp)
/*    2cff0:	e6aa0008 */ 	swc1	$f10,0x8($s5)
/*    2cff4:	8faf01a8 */ 	lw	$t7,0x1a8($sp)
/*    2cff8:	adf00000 */ 	sw	$s0,0x0($t7)
.L0002cffc:
/*    2cffc:	10000042 */ 	b	.L0002d108
/*    2d000:	2610004c */ 	addiu	$s0,$s0,0x4c
.L0002d004:
/*    2d004:	24010003 */ 	addiu	$at,$zero,0x3
/*    2d008:	1441003f */ 	bne	$v0,$at,.L0002d108
/*    2d00c:	97b80186 */ 	lhu	$t8,0x186($sp)
/*    2d010:	96190002 */ 	lhu	$t9,0x2($s0)
/*    2d014:	02202025 */ 	or	$a0,$s1,$zero
/*    2d018:	02602825 */ 	or	$a1,$s3,$zero
/*    2d01c:	03194024 */ 	and	$t0,$t8,$t9
/*    2d020:	11000038 */ 	beqz	$t0,.L0002d104
/*    2d024:	02e03025 */ 	or	$a2,$s7,$zero
/*    2d028:	8fac018c */ 	lw	$t4,0x18c($sp)
/*    2d02c:	27a90088 */ 	addiu	$t1,$sp,0x88
/*    2d030:	27aa007c */ 	addiu	$t2,$sp,0x7c
/*    2d034:	27ab0070 */ 	addiu	$t3,$sp,0x70
/*    2d038:	afab0018 */ 	sw	$t3,0x18($sp)
/*    2d03c:	afaa0014 */ 	sw	$t2,0x14($sp)
/*    2d040:	afa90010 */ 	sw	$t1,0x10($sp)
/*    2d044:	02003825 */ 	or	$a3,$s0,$zero
/*    2d048:	e7b60020 */ 	swc1	$f22,0x20($sp)
/*    2d04c:	e7b40024 */ 	swc1	$f20,0x24($sp)
/*    2d050:	0c00ae55 */ 	jal	func0002b954
/*    2d054:	afac001c */ 	sw	$t4,0x1c($sp)
/*    2d058:	1040002a */ 	beqz	$v0,.L0002d104
/*    2d05c:	c7b00088 */ 	lwc1	$f16,0x88($sp)
/*    2d060:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*    2d064:	c7b2008c */ 	lwc1	$f18,0x8c($sp)
/*    2d068:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*    2d06c:	46048001 */ 	sub.s	$f0,$f16,$f4
/*    2d070:	c7a60090 */ 	lwc1	$f6,0x90($sp)
/*    2d074:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*    2d078:	46089081 */ 	sub.s	$f2,$f18,$f8
/*    2d07c:	46000402 */ 	mul.s	$f16,$f0,$f0
/*    2d080:	240d0001 */ 	addiu	$t5,$zero,0x1
/*    2d084:	460a3301 */ 	sub.s	$f12,$f6,$f10
/*    2d088:	46021102 */ 	mul.s	$f4,$f2,$f2
/*    2d08c:	c6c60000 */ 	lwc1	$f6,0x0($s6)
/*    2d090:	460c6202 */ 	mul.s	$f8,$f12,$f12
/*    2d094:	46048480 */ 	add.s	$f18,$f16,$f4
/*    2d098:	46089380 */ 	add.s	$f14,$f18,$f8
/*    2d09c:	4606703c */ 	c.lt.s	$f14,$f6
/*    2d0a0:	00000000 */ 	nop
/*    2d0a4:	45020018 */ 	bc1fl	.L0002d108
/*    2d0a8:	26100018 */ 	addiu	$s0,$s0,0x18
/*    2d0ac:	afad0154 */ 	sw	$t5,0x154($sp)
/*    2d0b0:	e6ce0000 */ 	swc1	$f14,0x0($s6)
/*    2d0b4:	c7aa0088 */ 	lwc1	$f10,0x88($sp)
/*    2d0b8:	e64a0000 */ 	swc1	$f10,0x0($s2)
/*    2d0bc:	c7b0008c */ 	lwc1	$f16,0x8c($sp)
/*    2d0c0:	e6500004 */ 	swc1	$f16,0x4($s2)
/*    2d0c4:	c7a40090 */ 	lwc1	$f4,0x90($sp)
/*    2d0c8:	e6440008 */ 	swc1	$f4,0x8($s2)
/*    2d0cc:	c7b2007c */ 	lwc1	$f18,0x7c($sp)
/*    2d0d0:	e6920000 */ 	swc1	$f18,0x0($s4)
/*    2d0d4:	c7a80080 */ 	lwc1	$f8,0x80($sp)
/*    2d0d8:	e6880004 */ 	swc1	$f8,0x4($s4)
/*    2d0dc:	c7a60084 */ 	lwc1	$f6,0x84($sp)
/*    2d0e0:	e6860008 */ 	swc1	$f6,0x8($s4)
/*    2d0e4:	c7aa0070 */ 	lwc1	$f10,0x70($sp)
/*    2d0e8:	e6aa0000 */ 	swc1	$f10,0x0($s5)
/*    2d0ec:	c7b00074 */ 	lwc1	$f16,0x74($sp)
/*    2d0f0:	e6b00004 */ 	swc1	$f16,0x4($s5)
/*    2d0f4:	c7a40078 */ 	lwc1	$f4,0x78($sp)
/*    2d0f8:	e6a40008 */ 	swc1	$f4,0x8($s5)
/*    2d0fc:	8fae01a8 */ 	lw	$t6,0x1a8($sp)
/*    2d100:	add00000 */ 	sw	$s0,0x0($t6)
.L0002d104:
/*    2d104:	26100018 */ 	addiu	$s0,$s0,0x18
.L0002d108:
/*    2d108:	8faf0174 */ 	lw	$t7,0x174($sp)
/*    2d10c:	020f082b */ 	sltu	$at,$s0,$t7
/*    2d110:	5420fd9d */ 	bnezl	$at,.L0002c788
/*    2d114:	92020000 */ 	lbu	$v0,0x0($s0)
.L0002d118:
/*    2d118:	8fa20154 */ 	lw	$v0,0x154($sp)
/*    2d11c:	8fbf0064 */ 	lw	$ra,0x64($sp)
/*    2d120:	d7b40030 */ 	ldc1	$f20,0x30($sp)
/*    2d124:	d7b60038 */ 	ldc1	$f22,0x38($sp)
/*    2d128:	8fb00040 */ 	lw	$s0,0x40($sp)
/*    2d12c:	8fb10044 */ 	lw	$s1,0x44($sp)
/*    2d130:	8fb20048 */ 	lw	$s2,0x48($sp)
/*    2d134:	8fb3004c */ 	lw	$s3,0x4c($sp)
/*    2d138:	8fb40050 */ 	lw	$s4,0x50($sp)
/*    2d13c:	8fb50054 */ 	lw	$s5,0x54($sp)
/*    2d140:	8fb60058 */ 	lw	$s6,0x58($sp)
/*    2d144:	8fb7005c */ 	lw	$s7,0x5c($sp)
/*    2d148:	8fbe0060 */ 	lw	$s8,0x60($sp)
/*    2d14c:	2c580001 */ 	sltiu	$t8,$v0,0x1
/*    2d150:	03001025 */ 	or	$v0,$t8,$zero
/*    2d154:	03e00008 */ 	jr	$ra
/*    2d158:	27bd0170 */ 	addiu	$sp,$sp,0x170
);

bool func0002d15c(struct coord *pos, struct coord *coord2, s16 *rooms, u32 types, u16 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8)
{
	s32 roomnum;
	s16 *roomptr;
	u8 *start;
	u8 *end;
	struct coord sp27c;
	s16 *propnumptr;
	s16 propnums[256];

	sp27c.x = coord2->x - pos->x;
	sp27c.y = coord2->y - pos->y;
	sp27c.z = coord2->z - pos->z;

	if (types & CDTYPE_BG) {
		roomptr = rooms;
		roomnum = rooms[0];

		while (roomnum != -1) {
			if (roomnum < g_TileNumRooms) {
				start = g_TileFileData.u8 + g_TileRooms[roomnum];
				end = g_TileFileData.u8 + g_TileRooms[roomnum + 1];

				if (func0002bd04(start, end, pos, coord2, &sp27c, arg4, arg5, arg6, arg7, arg8) == 0) {
					func00025168(NULL);
					return false;
				}
			}

			roomptr++;
			roomnum = *roomptr;
		}
	}

	roomGetProps(rooms, propnums, 256);

	propnumptr = propnums;

	while (*propnumptr >= 0) {
		struct prop *prop = &g_Vars.props[*propnumptr];

		if (propIsOfCdType(prop, types)
				&& propUpdateGeometry(prop, &start, &end)
				&& func0002bd04(start, end, pos, coord2, &sp27c, arg4, arg5, arg6, arg7, arg8) == 0) {
			func00025168(prop);
			return false;
		}

		propnumptr++;
	}

	return true;
}

GLOBAL_ASM(
glabel func0002d3b0
/*    2d3b0:	27bdfd20 */ 	addiu	$sp,$sp,-736
/*    2d3b4:	3c014f80 */ 	lui	$at,0x4f80
/*    2d3b8:	44812000 */ 	mtc1	$at,$f4
/*    2d3bc:	afbf007c */ 	sw	$ra,0x7c($sp)
/*    2d3c0:	afbe0078 */ 	sw	$s8,0x78($sp)
/*    2d3c4:	afb70074 */ 	sw	$s7,0x74($sp)
/*    2d3c8:	afb60070 */ 	sw	$s6,0x70($sp)
/*    2d3cc:	afb5006c */ 	sw	$s5,0x6c($sp)
/*    2d3d0:	afb40068 */ 	sw	$s4,0x68($sp)
/*    2d3d4:	afb30064 */ 	sw	$s3,0x64($sp)
/*    2d3d8:	afb20060 */ 	sw	$s2,0x60($sp)
/*    2d3dc:	afb1005c */ 	sw	$s1,0x5c($sp)
/*    2d3e0:	afb00058 */ 	sw	$s0,0x58($sp)
/*    2d3e4:	f7b60050 */ 	sdc1	$f22,0x50($sp)
/*    2d3e8:	f7b40048 */ 	sdc1	$f20,0x48($sp)
/*    2d3ec:	afa402e0 */ 	sw	$a0,0x2e0($sp)
/*    2d3f0:	afa502e4 */ 	sw	$a1,0x2e4($sp)
/*    2d3f4:	afa702ec */ 	sw	$a3,0x2ec($sp)
/*    2d3f8:	afa002c0 */ 	sw	$zero,0x2c0($sp)
/*    2d3fc:	e7a40298 */ 	swc1	$f4,0x298($sp)
/*    2d400:	c4880000 */ 	lwc1	$f8,0x0($a0)
/*    2d404:	c4a60000 */ 	lwc1	$f6,0x0($a1)
/*    2d408:	30f90020 */ 	andi	$t9,$a3,0x20
/*    2d40c:	00c0f025 */ 	or	$s8,$a2,$zero
/*    2d410:	46083281 */ 	sub.s	$f10,$f6,$f8
/*    2d414:	e7aa02c4 */ 	swc1	$f10,0x2c4($sp)
/*    2d418:	c4920004 */ 	lwc1	$f18,0x4($a0)
/*    2d41c:	c4b00004 */ 	lwc1	$f16,0x4($a1)
/*    2d420:	46128101 */ 	sub.s	$f4,$f16,$f18
/*    2d424:	e7a402c8 */ 	swc1	$f4,0x2c8($sp)
/*    2d428:	c4880008 */ 	lwc1	$f8,0x8($a0)
/*    2d42c:	c4a60008 */ 	lwc1	$f6,0x8($a1)
/*    2d430:	46083281 */ 	sub.s	$f10,$f6,$f8
/*    2d434:	13200043 */ 	beqz	$t9,.L0002d544
/*    2d438:	e7aa02cc */ 	swc1	$f10,0x2cc($sp)
/*    2d43c:	84c80000 */ 	lh	$t0,0x0($a2)
/*    2d440:	2411ffff */ 	addiu	$s1,$zero,-1
/*    2d444:	00c08025 */ 	or	$s0,$a2,$zero
/*    2d448:	1111003e */ 	beq	$t0,$s1,.L0002d544
/*    2d44c:	c7b60300 */ 	lwc1	$f22,0x300($sp)
/*    2d450:	3c17800a */ 	lui	$s7,%hi(g_TileFileData)
/*    2d454:	3c16800a */ 	lui	$s6,%hi(g_TileRooms)
/*    2d458:	3c15800a */ 	lui	$s5,%hi(g_TileNumRooms)
/*    2d45c:	26b5a8a4 */ 	addiu	$s5,$s5,%lo(g_TileNumRooms)
/*    2d460:	26d6a8a8 */ 	addiu	$s6,$s6,%lo(g_TileRooms)
/*    2d464:	26f7a8a0 */ 	addiu	$s7,$s7,%lo(g_TileFileData)
/*    2d468:	c7b402fc */ 	lwc1	$f20,0x2fc($sp)
/*    2d46c:	27b4029c */ 	addiu	$s4,$sp,0x29c
/*    2d470:	27b302a8 */ 	addiu	$s3,$sp,0x2a8
/*    2d474:	27b202b4 */ 	addiu	$s2,$sp,0x2b4
/*    2d478:	8ea90000 */ 	lw	$t1,0x0($s5)
.L0002d47c:
/*    2d47c:	00085080 */ 	sll	$t2,$t0,0x2
/*    2d480:	27b802c4 */ 	addiu	$t8,$sp,0x2c4
/*    2d484:	0109082a */ 	slt	$at,$t0,$t1
/*    2d488:	5020002b */ 	beqzl	$at,.L0002d538
/*    2d48c:	86080002 */ 	lh	$t0,0x2($s0)
/*    2d490:	8ecb0000 */ 	lw	$t3,0x0($s6)
/*    2d494:	8ee30000 */ 	lw	$v1,0x0($s7)
/*    2d498:	97b902f2 */ 	lhu	$t9,0x2f2($sp)
/*    2d49c:	014b1021 */ 	addu	$v0,$t2,$t3
/*    2d4a0:	8c4c0000 */ 	lw	$t4,0x0($v0)
/*    2d4a4:	8faa02f8 */ 	lw	$t2,0x2f8($sp)
/*    2d4a8:	8fa902f4 */ 	lw	$t1,0x2f4($sp)
/*    2d4ac:	01832021 */ 	addu	$a0,$t4,$v1
/*    2d4b0:	afa402d4 */ 	sw	$a0,0x2d4($sp)
/*    2d4b4:	8c4e0004 */ 	lw	$t6,0x4($v0)
/*    2d4b8:	27ac0294 */ 	addiu	$t4,$sp,0x294
/*    2d4bc:	27ab0298 */ 	addiu	$t3,$sp,0x298
/*    2d4c0:	01c32821 */ 	addu	$a1,$t6,$v1
/*    2d4c4:	afa502d0 */ 	sw	$a1,0x2d0($sp)
/*    2d4c8:	afab0028 */ 	sw	$t3,0x28($sp)
/*    2d4cc:	afac0038 */ 	sw	$t4,0x38($sp)
/*    2d4d0:	afa8003c */ 	sw	$t0,0x3c($sp)
/*    2d4d4:	afb40034 */ 	sw	$s4,0x34($sp)
/*    2d4d8:	afb30030 */ 	sw	$s3,0x30($sp)
/*    2d4dc:	afb2002c */ 	sw	$s2,0x2c($sp)
/*    2d4e0:	e7b60024 */ 	swc1	$f22,0x24($sp)
/*    2d4e4:	e7b40020 */ 	swc1	$f20,0x20($sp)
/*    2d4e8:	afb80010 */ 	sw	$t8,0x10($sp)
/*    2d4ec:	8fa602e0 */ 	lw	$a2,0x2e0($sp)
/*    2d4f0:	8fa702e4 */ 	lw	$a3,0x2e4($sp)
/*    2d4f4:	afb90014 */ 	sw	$t9,0x14($sp)
/*    2d4f8:	afaa001c */ 	sw	$t2,0x1c($sp)
/*    2d4fc:	0c00b1c5 */ 	jal	func0002c714
/*    2d500:	afa90018 */ 	sw	$t1,0x18($sp)
/*    2d504:	1440000b */ 	bnez	$v0,.L0002d534
/*    2d508:	240d0001 */ 	addiu	$t5,$zero,0x1
/*    2d50c:	c7b00298 */ 	lwc1	$f16,0x298($sp)
/*    2d510:	8fae0294 */ 	lw	$t6,0x294($sp)
/*    2d514:	afad02c0 */ 	sw	$t5,0x2c0($sp)
/*    2d518:	02602025 */ 	or	$a0,$s3,$zero
/*    2d51c:	02802825 */ 	or	$a1,$s4,$zero
/*    2d520:	02403025 */ 	or	$a2,$s2,$zero
/*    2d524:	00003825 */ 	or	$a3,$zero,$zero
/*    2d528:	e7b00010 */ 	swc1	$f16,0x10($sp)
/*    2d52c:	0c009495 */ 	jal	func00025254
/*    2d530:	afae0014 */ 	sw	$t6,0x14($sp)
.L0002d534:
/*    2d534:	86080002 */ 	lh	$t0,0x2($s0)
.L0002d538:
/*    2d538:	26100002 */ 	addiu	$s0,$s0,0x2
/*    2d53c:	5511ffcf */ 	bnel	$t0,$s1,.L0002d47c
/*    2d540:	8ea90000 */ 	lw	$t1,0x0($s5)
.L0002d544:
/*    2d544:	27b00090 */ 	addiu	$s0,$sp,0x90
/*    2d548:	27b202b4 */ 	addiu	$s2,$sp,0x2b4
/*    2d54c:	27b302a8 */ 	addiu	$s3,$sp,0x2a8
/*    2d550:	27b4029c */ 	addiu	$s4,$sp,0x29c
/*    2d554:	c7b402fc */ 	lwc1	$f20,0x2fc($sp)
/*    2d558:	c7b60300 */ 	lwc1	$f22,0x300($sp)
/*    2d55c:	02002825 */ 	or	$a1,$s0,$zero
/*    2d560:	03c02025 */ 	or	$a0,$s8,$zero
/*    2d564:	0fc197e0 */ 	jal	roomGetProps
/*    2d568:	24060100 */ 	addiu	$a2,$zero,0x100
/*    2d56c:	87af0090 */ 	lh	$t7,0x90($sp)
/*    2d570:	02008825 */ 	or	$s1,$s0,$zero
/*    2d574:	27b80090 */ 	addiu	$t8,$sp,0x90
/*    2d578:	05e0003b */ 	bltz	$t7,.L0002d668
/*    2d57c:	27be02d0 */ 	addiu	$s8,$sp,0x2d0
/*    2d580:	3c16800a */ 	lui	$s6,%hi(g_Vars)
/*    2d584:	26d69fc0 */ 	addiu	$s6,$s6,%lo(g_Vars)
/*    2d588:	87020000 */ 	lh	$v0,0x0($t8)
/*    2d58c:	27b702d4 */ 	addiu	$s7,$sp,0x2d4
/*    2d590:	24150048 */ 	addiu	$s5,$zero,0x48
.L0002d594:
/*    2d594:	00550019 */ 	multu	$v0,$s5
/*    2d598:	8ec90338 */ 	lw	$t1,0x338($s6)
/*    2d59c:	8fa502ec */ 	lw	$a1,0x2ec($sp)
/*    2d5a0:	0000c812 */ 	mflo	$t9
/*    2d5a4:	03298021 */ 	addu	$s0,$t9,$t1
/*    2d5a8:	0fc19553 */ 	jal	propIsOfCdType
/*    2d5ac:	02002025 */ 	or	$a0,$s0,$zero
/*    2d5b0:	10400029 */ 	beqz	$v0,.L0002d658
/*    2d5b4:	02002025 */ 	or	$a0,$s0,$zero
/*    2d5b8:	02e02825 */ 	or	$a1,$s7,$zero
/*    2d5bc:	0fc198a4 */ 	jal	propUpdateGeometry
/*    2d5c0:	03c03025 */ 	or	$a2,$s8,$zero
/*    2d5c4:	10400024 */ 	beqz	$v0,.L0002d658
/*    2d5c8:	8fa402d4 */ 	lw	$a0,0x2d4($sp)
/*    2d5cc:	97ab02f2 */ 	lhu	$t3,0x2f2($sp)
/*    2d5d0:	8fac02f4 */ 	lw	$t4,0x2f4($sp)
/*    2d5d4:	8fad02f8 */ 	lw	$t5,0x2f8($sp)
/*    2d5d8:	27aa02c4 */ 	addiu	$t2,$sp,0x2c4
/*    2d5dc:	27ae0298 */ 	addiu	$t6,$sp,0x298
/*    2d5e0:	27af0294 */ 	addiu	$t7,$sp,0x294
/*    2d5e4:	2418fc19 */ 	addiu	$t8,$zero,-999
/*    2d5e8:	afb8003c */ 	sw	$t8,0x3c($sp)
/*    2d5ec:	afaf0038 */ 	sw	$t7,0x38($sp)
/*    2d5f0:	afae0028 */ 	sw	$t6,0x28($sp)
/*    2d5f4:	afaa0010 */ 	sw	$t2,0x10($sp)
/*    2d5f8:	8fa502d0 */ 	lw	$a1,0x2d0($sp)
/*    2d5fc:	8fa602e0 */ 	lw	$a2,0x2e0($sp)
/*    2d600:	8fa702e4 */ 	lw	$a3,0x2e4($sp)
/*    2d604:	e7b40020 */ 	swc1	$f20,0x20($sp)
/*    2d608:	e7b60024 */ 	swc1	$f22,0x24($sp)
/*    2d60c:	afb2002c */ 	sw	$s2,0x2c($sp)
/*    2d610:	afb30030 */ 	sw	$s3,0x30($sp)
/*    2d614:	afb40034 */ 	sw	$s4,0x34($sp)
/*    2d618:	afab0014 */ 	sw	$t3,0x14($sp)
/*    2d61c:	afac0018 */ 	sw	$t4,0x18($sp)
/*    2d620:	0c00b1c5 */ 	jal	func0002c714
/*    2d624:	afad001c */ 	sw	$t5,0x1c($sp)
/*    2d628:	1440000b */ 	bnez	$v0,.L0002d658
/*    2d62c:	24190001 */ 	addiu	$t9,$zero,0x1
/*    2d630:	c7b20298 */ 	lwc1	$f18,0x298($sp)
/*    2d634:	8fa90294 */ 	lw	$t1,0x294($sp)
/*    2d638:	afb902c0 */ 	sw	$t9,0x2c0($sp)
/*    2d63c:	02602025 */ 	or	$a0,$s3,$zero
/*    2d640:	02802825 */ 	or	$a1,$s4,$zero
/*    2d644:	02403025 */ 	or	$a2,$s2,$zero
/*    2d648:	02003825 */ 	or	$a3,$s0,$zero
/*    2d64c:	e7b20010 */ 	swc1	$f18,0x10($sp)
/*    2d650:	0c009495 */ 	jal	func00025254
/*    2d654:	afa90014 */ 	sw	$t1,0x14($sp)
.L0002d658:
/*    2d658:	86220002 */ 	lh	$v0,0x2($s1)
/*    2d65c:	26310002 */ 	addiu	$s1,$s1,0x2
/*    2d660:	0441ffcc */ 	bgez	$v0,.L0002d594
/*    2d664:	00000000 */ 	nop
.L0002d668:
/*    2d668:	8fa202c0 */ 	lw	$v0,0x2c0($sp)
/*    2d66c:	8fbf007c */ 	lw	$ra,0x7c($sp)
/*    2d670:	d7b40048 */ 	ldc1	$f20,0x48($sp)
/*    2d674:	d7b60050 */ 	ldc1	$f22,0x50($sp)
/*    2d678:	8fb00058 */ 	lw	$s0,0x58($sp)
/*    2d67c:	8fb1005c */ 	lw	$s1,0x5c($sp)
/*    2d680:	8fb20060 */ 	lw	$s2,0x60($sp)
/*    2d684:	8fb30064 */ 	lw	$s3,0x64($sp)
/*    2d688:	8fb40068 */ 	lw	$s4,0x68($sp)
/*    2d68c:	8fb5006c */ 	lw	$s5,0x6c($sp)
/*    2d690:	8fb60070 */ 	lw	$s6,0x70($sp)
/*    2d694:	8fb70074 */ 	lw	$s7,0x74($sp)
/*    2d698:	8fbe0078 */ 	lw	$s8,0x78($sp)
/*    2d69c:	2c4a0001 */ 	sltiu	$t2,$v0,0x1
/*    2d6a0:	01401025 */ 	or	$v0,$t2,$zero
/*    2d6a4:	03e00008 */ 	jr	$ra
/*    2d6a8:	27bd02e0 */ 	addiu	$sp,$sp,0x2e0
);

// Mismatch: Calculation of g_TileRooms[roomnum] is different
// Other functions and the below use t3 as the offset, t2 as the base, then t2 + t3
// But goal for this function uses t2 as the offset, t3 as the base, then t2 + t3
//s32 func0002d3b0(struct coord *arg0, struct coord *arg1, s16 *rooms, s32 types, u16 arg4, s32 arg5, s32 arg6, f32 ymax, f32 ymin)
//{
//	s32 roomnum;
//	s16 *roomptr;
//	u8 *start;
//	u8 *end;
//	struct coord sp2c4;
//	bool sp2c0 = false;
//	u32 sp2b4[3];
//	struct coord sp2a8;
//	struct coord sp29c;
//	f32 sp298 = 4294967296;
//	struct tile *sp294;
//	s16 *propnumptr;
//	s16 propnums[256];
//
//	sp2c4.x = arg1->x - arg0->x;
//	sp2c4.y = arg1->y - arg0->y;
//	sp2c4.z = arg1->z - arg0->z;
//
//	if (types & CDTYPE_BG) {
//		roomptr = rooms;
//		roomnum = rooms[0];
//
//		while (roomnum != -1) {
//			if (roomnum < g_TileNumRooms) {
//				start = g_TileFileData.u8 + g_TileRooms[roomnum];
//				end = g_TileFileData.u8 + g_TileRooms[roomnum + 1];
//
//				if (!func0002c714(start, end, arg0, arg1, &sp2c4, arg4, arg5, arg6, ymax, ymin, &sp298, sp2b4, &sp2a8, &sp29c, &sp294, roomnum)) {
//					sp2c0 = true;
//					func00025254(&sp2a8, &sp29c, sp2b4, NULL, sp298, sp294);
//				}
//			}
//
//			roomptr++;
//			roomnum = *roomptr;
//		}
//	}
//
//	roomGetProps(rooms, propnums, 256);
//	propnumptr = propnums;
//
//	while (*propnumptr >= 0) {
//		struct prop *prop = &g_Vars.props[*propnumptr];
//
//		if (propIsOfCdType(prop, types)
//				&& propUpdateGeometry(prop, &start, &end)
//				&& !func0002c714(start, end, arg0, arg1, &sp2c4, arg4, arg5, arg6, ymax, ymin, &sp298, sp2b4, &sp2a8, &sp29c, &sp294, -999)) {
//			sp2c0 = true;
//			func00025254(&sp2a8, &sp29c, sp2b4, prop, sp298, sp294);
//		}
//
//		propnumptr++;
//	}
//
//	return !sp2c0;
//}

bool func0002d6ac(struct coord *pos, s16 *rooms, struct coord *targetpos, u32 types, u32 arg4, f32 arg5, f32 arg6)
{
	s16 sp44[21];
	s16 sp34[8];

	func00018148(pos, targetpos, rooms, sp34, sp44, 20);

	return func0002d15c(pos, targetpos, sp44, types, 4, 0, arg4, arg5, arg6);
}

s32 cdTestAToB2(struct coord *pos, s16 *rooms, struct coord *coord2, s16 *rooms2, u32 types, s32 arg5, f32 arg6, f32 arg7)
{
	s32 result;
	s16 sp44[20];
	s16 sp34[8];

	func0f065d1c(pos, rooms, coord2, sp34, sp44, 20);

	if (arrayIntersects(sp34, rooms2)) {
		result = func0002d15c(pos, coord2, sp44, types, 4, 0, arg5, arg6, arg7);
	} else {
		result = 0;
	}

	return result;
}

bool func0002d7c0(struct coord *pos, s16 *rooms, struct coord *arg2, u32 arg3, u32 arg4, f32 ymax, f32 ymin)
{
	s16 sp44[21];
	s16 sp34[8];

	func00018148(pos, arg2, rooms, sp34, sp44, 20);

	return func0002d3b0(pos, arg2, sp44, arg3, 4, 0, arg4, ymax, ymin);
}

s32 func0002d840(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, u32 types, s32 arg5, f32 ymax, f32 ymin)
{
	s16 rooms[21];

	func00018148(arg0, arg2, arg1, arg3, rooms, 20);

	return func0002d15c(arg0, arg2, rooms, types, 4, 0, arg5, ymax, ymin);
}

s32 func0002d8b8(struct coord *pos, s16 *rooms, struct coord *pos2, s16 *rooms2, s32 types, bool arg5, f32 ymax, f32 ymin)
{
	s16 sp44[21];
	s16 sp34[8];
	s32 result;

	func0f065d1c(pos, rooms, pos2, sp34, sp44, 20);

	result = func0002d3b0(pos, pos2, sp44, types, 4, 0, arg5, ymax, ymin);

	if (result != CDRESULT_COLLISION && !arrayIntersects(sp34, rooms2)) {
		func00024f6c();
		result = CDRESULT_ERROR;
	}

	return result;
}

s32 cdTestAToB3(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, f32 width, s32 types, s32 arg6, f32 ymax, f32 ymin)
{
	u32 stack[7];
	s16 sp5c[8];
	s16 sp4c[8];
	struct coord sp40;
	s32 result;

	func0f065d1c(arg0, arg1, arg2, sp4c, sp5c, 20);

	result = func0002d3b0(arg0, arg2, sp5c, types, 4, 0, arg6, ymax, ymin);

	if (result == CDRESULT_COLLISION) {
		sp40.x = arg2->x - arg0->x;
		sp40.y = arg2->y - arg0->y;
		sp40.z = arg2->z - arg0->z;

		func000250cc(arg0, &sp40, width);
	} else if (!arrayIntersects(sp4c, arg3)) {
		func00024f6c();
		result = -1;
	}

	return result;
}

void func0002da50(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, u32 types, s32 arg5, f32 ymax, f32 ymin)
{
	s16 rooms[21];

	func00018148(arg0, arg2, arg1, arg3, rooms, 20);
	func0002d3b0(arg0, arg2, rooms, types, 4, 0, arg5, ymax, ymin);
}

s32 func0002dac8(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, f32 width, u32 types, s32 arg6, f32 ymax, f32 ymin)
{
	s16 rooms[21];
	struct coord sp40;
	s32 result;

	func00018148(arg0, arg2, arg1, arg3, rooms, 20);

	result = func0002d3b0(arg0, arg2, rooms, types, 4, 0, arg6, ymax, ymin);

	if (result == 0) {
		sp40.x = arg2->x - arg0->x;
		sp40.y = arg2->y - arg0->y;
		sp40.z = arg2->z - arg0->z;

		func000250cc(arg0, &sp40, width);
	}

	return result;
}

bool func0002db98(struct coord *viewpos, s16 *rooms, struct coord *targetpos, u32 types, u16 arg4)
{
	s16 sp44[21];
	s16 sp34[8];

	func00018148(viewpos, targetpos, rooms, sp34, sp44, 20);

	return func0002d15c(viewpos, targetpos, sp44, types, arg4, 1, 1, 0, 0);
}

bool func0002dc18(struct coord *coord, s16 *rooms, struct coord *coord2, s32 arg3)
{
	return func0002db98(coord, rooms, coord2, arg3, 0x1c);
}

bool hasLineOfSight(struct coord *coord, s16 *rooms, struct coord *coord2, s16 *rooms2, s32 arg4, u16 arg5)
{
	bool result;
	s16 sp44[20];
	s16 sp34[8];

	func0f065d1c(coord, rooms, coord2, sp34, sp44, 20);

	if (arrayIntersects(sp34, rooms2)) {
		result = func0002d15c(coord, coord2, sp44, arg4, arg5, 1, 1, 0, 0);
	} else {
		result = false;
	}

	return result;
}

bool func0002dcd0(struct coord *arg0, s16 *rooms1, struct coord *arg2, s16 *rooms2, u32 arg4)
{
	return hasLineOfSight(arg0, rooms1, arg2, rooms2, arg4, 0x1c);
}

bool func0002dcfc(struct coord *pos, s16 *rooms, struct coord *pos2, s16 *rooms2, s16 *rooms3, u32 types, u16 arg6)
{
	bool result;
	s16 sp34[20];

	func0f065d1c(pos, rooms, pos2, rooms3, sp34, 20);

	if (arrayIntersects(rooms3, rooms2)) {
		result = func0002d15c(pos, pos2, sp34, types, arg6, 1, 1, 0, 0);
	} else {
		result = false;
	}

	return result;
}

s32 cdTestAToB4(struct coord *pos, s16 *rooms, struct coord *pos2, u32 types, u16 arg4)
{
	s16 sp44[21];
	s16 sp34[8];

	func00018148(pos, pos2, rooms, sp34, sp44, 20);

	return func0002d3b0(pos, pos2, sp44, types, arg4, 1, 1, 0, 0);
}

s32 func0002de10(struct coord *pos, s16 *rooms, struct coord *pos2, u32 types)
{
	return cdTestAToB4(pos, rooms, pos2, types, 0x1c);
}

s32 func0002de34(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, u32 types, u16 arg5)
{
	s16 rooms[21];

	func00018148(arg0, arg2, arg1, arg3, rooms, 20);

	return func0002d15c(arg0, arg2, rooms, types, arg5, 1, 1, 0, 0);
}

s32 func0002deac(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, u32 types)
{
	return func0002de34(arg0, arg1, arg2, arg3, types, 0x1c);
}

bool func0002ded8(struct coord *arg0, struct coord *arg1, struct prop *prop)
{
	u8 *start;
	u8 *end;
	struct coord sp7c;
	bool result = false;
	struct coord sp6c;
	struct coord sp60;
	struct coord sp54;
	f32 sp50 = 4294967296;
	struct tile *tile;

	sp7c.x = arg1->x - arg0->x;
	sp7c.y = arg1->y - arg0->y;
	sp7c.z = arg1->z - arg0->z;

	if (propUpdateGeometry(prop, &start, &end)) {
		if (!func0002c714(start, end, arg0, arg1, &sp7c, 0x1c, 1, 1, 0, 0, &sp50, &sp6c, &sp60, &sp54, &tile, -999)) {
			result = true;
			func00025254(&sp60, &sp54, &sp6c, prop, sp50, tile);
		}
	}

	return !result;
}

GLOBAL_ASM(
glabel func0002dffc
/*    2dffc:	27bdff78 */ 	addiu	$sp,$sp,-136
/*    2e000:	afbf003c */ 	sw	$ra,0x3c($sp)
/*    2e004:	afb50038 */ 	sw	$s5,0x38($sp)
/*    2e008:	afb40034 */ 	sw	$s4,0x34($sp)
/*    2e00c:	afb30030 */ 	sw	$s3,0x30($sp)
/*    2e010:	afb2002c */ 	sw	$s2,0x2c($sp)
/*    2e014:	afb10028 */ 	sw	$s1,0x28($sp)
/*    2e018:	afb00024 */ 	sw	$s0,0x24($sp)
/*    2e01c:	f7b60018 */ 	sdc1	$f22,0x18($sp)
/*    2e020:	f7b40010 */ 	sdc1	$f20,0x10($sp)
/*    2e024:	90900001 */ 	lbu	$s0,0x1($a0)
/*    2e028:	00809025 */ 	or	$s2,$a0,$zero
/*    2e02c:	00a0a825 */ 	or	$s5,$a1,$zero
/*    2e030:	90b10001 */ 	lbu	$s1,0x1($a1)
/*    2e034:	1a000084 */ 	blez	$s0,.L0002e248
/*    2e038:	00003025 */ 	or	$a2,$zero,$zero
/*    2e03c:	44802000 */ 	mtc1	$zero,$f4
/*    2e040:	00809825 */ 	or	$s3,$a0,$zero
/*    2e044:	d7b40040 */ 	ldc1	$f20,0x40($sp)
/*    2e048:	460025a1 */ 	cvt.d.s	$f22,$f4
.L0002e04c:
/*    2e04c:	24d40001 */ 	addiu	$s4,$a2,0x1
/*    2e050:	0290001a */ 	div	$zero,$s4,$s0
/*    2e054:	00002810 */ 	mfhi	$a1
/*    2e058:	000570c0 */ 	sll	$t6,$a1,0x3
/*    2e05c:	024e1021 */ 	addu	$v0,$s2,$t6
/*    2e060:	c4460010 */ 	lwc1	$f6,0x10($v0)
/*    2e064:	c6620010 */ 	lwc1	$f2,0x10($s3)
/*    2e068:	c44a000c */ 	lwc1	$f10,0xc($v0)
/*    2e06c:	46003221 */ 	cvt.d.s	$f8,$f6
/*    2e070:	46001021 */ 	cvt.d.s	$f0,$f2
/*    2e074:	c672000c */ 	lwc1	$f18,0xc($s3)
/*    2e078:	46204301 */ 	sub.d	$f12,$f8,$f0
/*    2e07c:	16000002 */ 	bnez	$s0,.L0002e088
/*    2e080:	00000000 */ 	nop
/*    2e084:	0007000d */ 	break	0x7
.L0002e088:
/*    2e088:	2401ffff */ 	addiu	$at,$zero,-1
/*    2e08c:	16010004 */ 	bne	$s0,$at,.L0002e0a0
/*    2e090:	3c018000 */ 	lui	$at,0x8000
/*    2e094:	16810002 */ 	bne	$s4,$at,.L0002e0a0
/*    2e098:	00000000 */ 	nop
/*    2e09c:	0006000d */ 	break	0x6
.L0002e0a0:
/*    2e0a0:	46366032 */ 	c.eq.d	$f12,$f22
/*    2e0a4:	24af0001 */ 	addiu	$t7,$a1,0x1
/*    2e0a8:	46005121 */ 	cvt.d.s	$f4,$f10
/*    2e0ac:	46009421 */ 	cvt.d.s	$f16,$f18
/*    2e0b0:	4500000d */ 	bc1f	.L0002e0e8
/*    2e0b4:	46248381 */ 	sub.d	$f14,$f16,$f4
/*    2e0b8:	46367032 */ 	c.eq.d	$f14,$f22
/*    2e0bc:	00000000 */ 	nop
/*    2e0c0:	45000009 */ 	bc1f	.L0002e0e8
/*    2e0c4:	00000000 */ 	nop
/*    2e0c8:	44059000 */ 	mfc1	$a1,$f18
/*    2e0cc:	44061000 */ 	mfc1	$a2,$f2
/*    2e0d0:	0c009948 */ 	jal	cdIs2dPointInTileType2
/*    2e0d4:	02a02025 */ 	or	$a0,$s5,$zero
/*    2e0d8:	50400058 */ 	beqzl	$v0,.L0002e23c
/*    2e0dc:	02803025 */ 	or	$a2,$s4,$zero
/*    2e0e0:	1000005a */ 	b	.L0002e24c
/*    2e0e4:	00001025 */ 	or	$v0,$zero,$zero
.L0002e0e8:
/*    2e0e8:	01f0001a */ 	div	$zero,$t7,$s0
/*    2e0ec:	462e0182 */ 	mul.d	$f6,$f0,$f14
/*    2e0f0:	00001010 */ 	mfhi	$v0
/*    2e0f4:	00401825 */ 	or	$v1,$v0,$zero
/*    2e0f8:	00002025 */ 	or	$a0,$zero,$zero
/*    2e0fc:	462c8202 */ 	mul.d	$f8,$f16,$f12
/*    2e100:	46283080 */ 	add.d	$f2,$f6,$f8
/*    2e104:	16000002 */ 	bnez	$s0,.L0002e110
/*    2e108:	00000000 */ 	nop
/*    2e10c:	0007000d */ 	break	0x7
.L0002e110:
/*    2e110:	2401ffff */ 	addiu	$at,$zero,-1
/*    2e114:	16010004 */ 	bne	$s0,$at,.L0002e128
/*    2e118:	3c018000 */ 	lui	$at,0x8000
/*    2e11c:	15e10002 */ 	bne	$t7,$at,.L0002e128
/*    2e120:	00000000 */ 	nop
/*    2e124:	0006000d */ 	break	0x6
.L0002e128:
/*    2e128:	10c2001d */ 	beq	$a2,$v0,.L0002e1a0
/*    2e12c:	00000000 */ 	nop
/*    2e130:	0003c0c0 */ 	sll	$t8,$v1,0x3
.L0002e134:
/*    2e134:	02581021 */ 	addu	$v0,$s2,$t8
/*    2e138:	c44a0010 */ 	lwc1	$f10,0x10($v0)
/*    2e13c:	c448000c */ 	lwc1	$f8,0xc($v0)
/*    2e140:	46005121 */ 	cvt.d.s	$f4,$f10
/*    2e144:	460042a1 */ 	cvt.d.s	$f10,$f8
/*    2e148:	462e2182 */ 	mul.d	$f6,$f4,$f14
/*    2e14c:	00000000 */ 	nop
/*    2e150:	462c5102 */ 	mul.d	$f4,$f10,$f12
/*    2e154:	46243500 */ 	add.d	$f20,$f6,$f4
/*    2e158:	4622a032 */ 	c.eq.d	$f20,$f2
/*    2e15c:	00000000 */ 	nop
/*    2e160:	4500000f */ 	bc1f	.L0002e1a0
/*    2e164:	00000000 */ 	nop
/*    2e168:	24790001 */ 	addiu	$t9,$v1,0x1
/*    2e16c:	0330001a */ 	div	$zero,$t9,$s0
/*    2e170:	00001810 */ 	mfhi	$v1
/*    2e174:	16000002 */ 	bnez	$s0,.L0002e180
/*    2e178:	00000000 */ 	nop
/*    2e17c:	0007000d */ 	break	0x7
.L0002e180:
/*    2e180:	2401ffff */ 	addiu	$at,$zero,-1
/*    2e184:	16010004 */ 	bne	$s0,$at,.L0002e198
/*    2e188:	3c018000 */ 	lui	$at,0x8000
/*    2e18c:	17210002 */ 	bne	$t9,$at,.L0002e198
/*    2e190:	00000000 */ 	nop
/*    2e194:	0006000d */ 	break	0x6
.L0002e198:
/*    2e198:	5466ffe6 */ 	bnel	$v1,$a2,.L0002e134
/*    2e19c:	0003c0c0 */ 	sll	$t8,$v1,0x3
.L0002e1a0:
/*    2e1a0:	1a200021 */ 	blez	$s1,.L0002e228
/*    2e1a4:	00000000 */ 	nop
/*    2e1a8:	02a01025 */ 	or	$v0,$s5,$zero
.L0002e1ac:
/*    2e1ac:	c4480010 */ 	lwc1	$f8,0x10($v0)
/*    2e1b0:	c444000c */ 	lwc1	$f4,0xc($v0)
/*    2e1b4:	4622a032 */ 	c.eq.d	$f20,$f2
/*    2e1b8:	460042a1 */ 	cvt.d.s	$f10,$f8
/*    2e1bc:	46002221 */ 	cvt.d.s	$f8,$f4
/*    2e1c0:	462e5182 */ 	mul.d	$f6,$f10,$f14
/*    2e1c4:	00000000 */ 	nop
/*    2e1c8:	462c4282 */ 	mul.d	$f10,$f8,$f12
/*    2e1cc:	45000003 */ 	bc1f	.L0002e1dc
/*    2e1d0:	462a3000 */ 	add.d	$f0,$f6,$f10
/*    2e1d4:	46201101 */ 	sub.d	$f4,$f2,$f0
/*    2e1d8:	46222500 */ 	add.d	$f20,$f4,$f2
.L0002e1dc:
/*    2e1dc:	4622003c */ 	c.lt.d	$f0,$f2
/*    2e1e0:	00000000 */ 	nop
/*    2e1e4:	45020006 */ 	bc1fl	.L0002e200
/*    2e1e8:	4620103c */ 	c.lt.d	$f2,$f0
/*    2e1ec:	4622a03c */ 	c.lt.d	$f20,$f2
/*    2e1f0:	00000000 */ 	nop
/*    2e1f4:	4501000c */ 	bc1t	.L0002e228
/*    2e1f8:	00000000 */ 	nop
/*    2e1fc:	4620103c */ 	c.lt.d	$f2,$f0
.L0002e200:
/*    2e200:	00000000 */ 	nop
/*    2e204:	45020006 */ 	bc1fl	.L0002e220
/*    2e208:	24840001 */ 	addiu	$a0,$a0,0x1
/*    2e20c:	4634103c */ 	c.lt.d	$f2,$f20
/*    2e210:	00000000 */ 	nop
/*    2e214:	45010004 */ 	bc1t	.L0002e228
/*    2e218:	00000000 */ 	nop
/*    2e21c:	24840001 */ 	addiu	$a0,$a0,0x1
.L0002e220:
/*    2e220:	1491ffe2 */ 	bne	$a0,$s1,.L0002e1ac
/*    2e224:	24420008 */ 	addiu	$v0,$v0,0x8
.L0002e228:
/*    2e228:	54910004 */ 	bnel	$a0,$s1,.L0002e23c
/*    2e22c:	02803025 */ 	or	$a2,$s4,$zero
/*    2e230:	10000006 */ 	b	.L0002e24c
/*    2e234:	24020001 */ 	addiu	$v0,$zero,0x1
/*    2e238:	02803025 */ 	or	$a2,$s4,$zero
.L0002e23c:
/*    2e23c:	1690ff83 */ 	bne	$s4,$s0,.L0002e04c
/*    2e240:	26730008 */ 	addiu	$s3,$s3,0x8
/*    2e244:	f7b40040 */ 	sdc1	$f20,0x40($sp)
.L0002e248:
/*    2e248:	00001025 */ 	or	$v0,$zero,$zero
.L0002e24c:
/*    2e24c:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*    2e250:	d7b40010 */ 	ldc1	$f20,0x10($sp)
/*    2e254:	d7b60018 */ 	ldc1	$f22,0x18($sp)
/*    2e258:	8fb00024 */ 	lw	$s0,0x24($sp)
/*    2e25c:	8fb10028 */ 	lw	$s1,0x28($sp)
/*    2e260:	8fb2002c */ 	lw	$s2,0x2c($sp)
/*    2e264:	8fb30030 */ 	lw	$s3,0x30($sp)
/*    2e268:	8fb40034 */ 	lw	$s4,0x34($sp)
/*    2e26c:	8fb50038 */ 	lw	$s5,0x38($sp)
/*    2e270:	03e00008 */ 	jr	$ra
/*    2e274:	27bd0088 */ 	addiu	$sp,$sp,0x88
);

// Mismatch: Float regalloc, likely related to the zero variable
//bool func0002dffc(struct tiletype2 *arg0, struct tiletype2 *arg1)
//{
//	u32 stack[4];
//	f32 zero = 0;
//	s32 numvertices0 = arg0->header.numvertices;
//	s32 numvertices1 = arg1->header.numvertices;
//	s32 i;
//
//	for (i = 0; i < numvertices0; i++) {
//		s32 next = (i + 1) % numvertices0;
//		f64 diff1;
//		f64 diff2;
//
//		diff1 = arg0->vertices[next][1] - (f64)arg0->vertices[i][1];
//		diff2 = arg0->vertices[i][0] - (f64)arg0->vertices[next][0];
//
//		if (diff1 == zero && diff2 == zero) {
//			if (cdIs2dPointInTileType2(arg1, arg0->vertices[i][0], arg0->vertices[i][1])) {
//				return false;
//			}
//		} else {
//			f64 sum1 = arg0->vertices[i][0] * diff1 + arg0->vertices[i][1] * diff2;
//			f64 sum2;
//			s32 j = (next + 1) % numvertices0;
//			s32 k;
//
//			while (j != i) {
//				sum2 = arg0->vertices[j][0] * diff1 + arg0->vertices[j][1] * diff2;
//
//				if (sum2 != sum1) {
//					break;
//				}
//
//				j = (j + 1) % numvertices0;
//			}
//
//			for (k = 0; k < numvertices1; k++) {
//				f64 sum3 = arg1->vertices[k][0] * diff1 + arg1->vertices[k][1] * diff2;
//
//				if (sum2 == sum1) {
//					sum2 = sum1 - sum3 + sum1;
//				}
//
//				if ((sum3 < sum1 && sum2 < sum1) || (sum3 > sum1 && sum2 > sum1)) {
//					break;
//				}
//			}
//
//			if (k == numvertices1) {
//				return true;
//			}
//		}
//	}
//
//	return false;
//}

s32 func0002e278(u8 *start, u8 *end, struct tiletype2 *ref, u16 flags)
{
	struct tile *tile = (struct tile *) start;

	while (tile < (struct tile *) end) {
		if (tile->type == TILETYPE_00) {
			struct tiletype0 *type0 = (struct tiletype0 *) tile;
			tile = (struct tile *)((u32)tile + type0->header.numvertices * 6 + 0xe);
		} else if (tile->type == TILETYPE_01) {
			struct tiletype1 *type1 = (struct tiletype1 *) tile;
			tile = (struct tile *)((u32)tile + type1->header.numvertices * 0xc + 0x10);
		} else if (tile->type == TILETYPE_02) {
			struct tiletype2 *tile2 = (struct tiletype2 *) tile;

			if ((flags & (TILEFLAG_0004 | TILEFLAG_0008 | TILEFLAG_0010))
					&& tile2->ymax >= ref->ymin
					&& tile2->ymin <= ref->ymax) {
				// Tiles are overlapping vertically
				s32 i;

				for (i = 0; i < ref->header.numvertices; i++) {
					if (cdIs2dPointInTileType2(tile2, ref->vertices[i][0], ref->vertices[i][1])) {
						return false;
					}
				}

				for (i = 0; i < tile2->header.numvertices; i++) {
					if (cdIs2dPointInTileType2(ref, tile2->vertices[i][0], tile2->vertices[i][1])) {
						return false;
					}
				}

				if (!func0002dffc(ref, tile2) && !func0002dffc(tile2, ref)) {
					return false;
				}
			}

			tile = (struct tile *)((u32)tile + 0x4c);
		} else if (tile->type == TILETYPE_03) {
			struct tiletype3 *tile3 = (struct tiletype3 *) tile;

			if ((flags & tile->flags)
					&& tile3->ymax >= ref->ymin
					&& tile3->ymin <= ref->ymax
					&& func000274e0(ref, tile3->x, tile3->z, tile3->width, NULL, NULL)) {
				return false;
			}

			tile = (struct tile *)((u32)tile + 0x18);
		}
	}

	return true;
}

s32 func0002e4c4(struct tiletype2 *geo, s16 *rooms, u32 types)
{
	s32 result = CDRESULT_NOCOLLISION;
	s32 roomnum;
	u8 *start;
	u8 *end;
	s16 *roomptr;
	s16 propnums[256];
	s16 *propnumptr;

	// Check BG
	if (types & CDTYPE_BG) {
		roomptr = rooms;
		roomnum = rooms[0];

		while (roomnum != -1) {
			if (roomnum < g_TileNumRooms) {
				start = g_TileFileData.u8 + g_TileRooms[roomnum];
				end = g_TileFileData.u8 + g_TileRooms[roomnum + 1];

				result = func0002e278(start, end, geo, TILEFLAG_0004);

				if (result == CDRESULT_COLLISION) {
					func00025168(NULL);
					break;
				}
			}

			roomptr++;
			roomnum = *roomptr;
		}
	}

	// Check props
	if (result != CDRESULT_COLLISION) {
		roomGetProps(rooms, propnums, 256);
		propnumptr = propnums;

		while (*propnumptr >= 0) {
			struct prop *prop = &g_Vars.props[*propnumptr];

			if (propIsOfCdType(prop, types) && propUpdateGeometry(prop, &start, &end)) {
				result = func0002e278(start, end, geo, TILEFLAG_0004);

				if (result == CDRESULT_COLLISION) {
					func00025168(prop);
					break;
				}
			}

			propnumptr++;
		}
	}

	return result;
}

GLOBAL_ASM(
glabel func0002e680
/*    2e680:	27bdff60 */ 	addiu	$sp,$sp,-160
/*    2e684:	afb40048 */ 	sw	$s4,0x48($sp)
/*    2e688:	afb1003c */ 	sw	$s1,0x3c($sp)
/*    2e68c:	afb00038 */ 	sw	$s0,0x38($sp)
/*    2e690:	00a08825 */ 	or	$s1,$a1,$zero
/*    2e694:	00c0a025 */ 	or	$s4,$a2,$zero
/*    2e698:	afbf005c */ 	sw	$ra,0x5c($sp)
/*    2e69c:	afbe0058 */ 	sw	$s8,0x58($sp)
/*    2e6a0:	afb70054 */ 	sw	$s7,0x54($sp)
/*    2e6a4:	afb60050 */ 	sw	$s6,0x50($sp)
/*    2e6a8:	afb5004c */ 	sw	$s5,0x4c($sp)
/*    2e6ac:	afb30044 */ 	sw	$s3,0x44($sp)
/*    2e6b0:	afb20040 */ 	sw	$s2,0x40($sp)
/*    2e6b4:	f7b40030 */ 	sdc1	$f20,0x30($sp)
/*    2e6b8:	afa400a0 */ 	sw	$a0,0xa0($sp)
/*    2e6bc:	afa700ac */ 	sw	$a3,0xac($sp)
/*    2e6c0:	afa0009c */ 	sw	$zero,0x9c($sp)
/*    2e6c4:	18a0004b */ 	blez	$a1,.L0002e7f4
/*    2e6c8:	00008025 */ 	or	$s0,$zero,$zero
/*    2e6cc:	4480a000 */ 	mtc1	$zero,$f20
/*    2e6d0:	27be0078 */ 	addiu	$s8,$sp,0x78
/*    2e6d4:	27b70084 */ 	addiu	$s7,$sp,0x84
/*    2e6d8:	27b6006c */ 	addiu	$s6,$sp,0x6c
/*    2e6dc:	2415000c */ 	addiu	$s5,$zero,0xc
.L0002e6e0:
/*    2e6e0:	3c0e8006 */ 	lui	$t6,%hi(var8005f030)
/*    2e6e4:	8dcef030 */ 	lw	$t6,%lo(var8005f030)($t6)
/*    2e6e8:	51c00013 */ 	beqzl	$t6,.L0002e738
/*    2e6ec:	26190001 */ 	addiu	$t9,$s0,0x1
/*    2e6f0:	02301023 */ 	subu	$v0,$s1,$s0
/*    2e6f4:	00517821 */ 	addu	$t7,$v0,$s1
/*    2e6f8:	25f8fffe */ 	addiu	$t8,$t7,-2
/*    2e6fc:	0311001a */ 	div	$zero,$t8,$s1
/*    2e700:	00001810 */ 	mfhi	$v1
/*    2e704:	2448ffff */ 	addiu	$t0,$v0,-1
/*    2e708:	16200002 */ 	bnez	$s1,.L0002e714
/*    2e70c:	00000000 */ 	nop
/*    2e710:	0007000d */ 	break	0x7
.L0002e714:
/*    2e714:	2401ffff */ 	addiu	$at,$zero,-1
/*    2e718:	16210004 */ 	bne	$s1,$at,.L0002e72c
/*    2e71c:	3c018000 */ 	lui	$at,0x8000
/*    2e720:	17010002 */ 	bne	$t8,$at,.L0002e72c
/*    2e724:	00000000 */ 	nop
/*    2e728:	0006000d */ 	break	0x6
.L0002e72c:
/*    2e72c:	1000000e */ 	b	.L0002e768
/*    2e730:	00000000 */ 	nop
/*    2e734:	26190001 */ 	addiu	$t9,$s0,0x1
.L0002e738:
/*    2e738:	0331001a */ 	div	$zero,$t9,$s1
/*    2e73c:	00001810 */ 	mfhi	$v1
/*    2e740:	02004025 */ 	or	$t0,$s0,$zero
/*    2e744:	16200002 */ 	bnez	$s1,.L0002e750
/*    2e748:	00000000 */ 	nop
/*    2e74c:	0007000d */ 	break	0x7
.L0002e750:
/*    2e750:	2401ffff */ 	addiu	$at,$zero,-1
/*    2e754:	16210004 */ 	bne	$s1,$at,.L0002e768
/*    2e758:	3c018000 */ 	lui	$at,0x8000
/*    2e75c:	17210002 */ 	bne	$t9,$at,.L0002e768
/*    2e760:	00000000 */ 	nop
/*    2e764:	0006000d */ 	break	0x6
.L0002e768:
/*    2e768:	01150019 */ 	multu	$t0,$s5
/*    2e76c:	8faa00ac */ 	lw	$t2,0xac($sp)
/*    2e770:	8fa700a0 */ 	lw	$a3,0xa0($sp)
/*    2e774:	afb60010 */ 	sw	$s6,0x10($sp)
/*    2e778:	afb70014 */ 	sw	$s7,0x14($sp)
/*    2e77c:	afbe0018 */ 	sw	$s8,0x18($sp)
/*    2e780:	afa0001c */ 	sw	$zero,0x1c($sp)
/*    2e784:	e7b40020 */ 	swc1	$f20,0x20($sp)
/*    2e788:	e7b40024 */ 	swc1	$f20,0x24($sp)
/*    2e78c:	00001012 */ 	mflo	$v0
/*    2e790:	02829021 */ 	addu	$s2,$s4,$v0
/*    2e794:	02402025 */ 	or	$a0,$s2,$zero
/*    2e798:	00750019 */ 	multu	$v1,$s5
/*    2e79c:	01423021 */ 	addu	$a2,$t2,$v0
/*    2e7a0:	00004812 */ 	mflo	$t1
/*    2e7a4:	02899821 */ 	addu	$s3,$s4,$t1
/*    2e7a8:	0c00ab1c */ 	jal	func0002ac70
/*    2e7ac:	02602825 */ 	or	$a1,$s3,$zero
/*    2e7b0:	1040000e */ 	beqz	$v0,.L0002e7ec
/*    2e7b4:	26100001 */ 	addiu	$s0,$s0,0x1
/*    2e7b8:	02e02025 */ 	or	$a0,$s7,$zero
/*    2e7bc:	03c02825 */ 	or	$a1,$s8,$zero
/*    2e7c0:	02c03025 */ 	or	$a2,$s6,$zero
/*    2e7c4:	0c00946b */ 	jal	func000251ac
/*    2e7c8:	8fa700b0 */ 	lw	$a3,0xb0($sp)
/*    2e7cc:	02402025 */ 	or	$a0,$s2,$zero
/*    2e7d0:	0c0094c5 */ 	jal	func00025314
/*    2e7d4:	02602825 */ 	or	$a1,$s3,$zero
/*    2e7d8:	0c0094f1 */ 	jal	func000253c4
/*    2e7dc:	8fa400b4 */ 	lw	$a0,0xb4($sp)
/*    2e7e0:	240b0001 */ 	addiu	$t3,$zero,0x1
/*    2e7e4:	10000003 */ 	b	.L0002e7f4
/*    2e7e8:	afab009c */ 	sw	$t3,0x9c($sp)
.L0002e7ec:
/*    2e7ec:	1611ffbc */ 	bne	$s0,$s1,.L0002e6e0
/*    2e7f0:	00000000 */ 	nop
.L0002e7f4:
/*    2e7f4:	8fbf005c */ 	lw	$ra,0x5c($sp)
/*    2e7f8:	8fa2009c */ 	lw	$v0,0x9c($sp)
/*    2e7fc:	d7b40030 */ 	ldc1	$f20,0x30($sp)
/*    2e800:	8fb00038 */ 	lw	$s0,0x38($sp)
/*    2e804:	8fb1003c */ 	lw	$s1,0x3c($sp)
/*    2e808:	8fb20040 */ 	lw	$s2,0x40($sp)
/*    2e80c:	8fb30044 */ 	lw	$s3,0x44($sp)
/*    2e810:	8fb40048 */ 	lw	$s4,0x48($sp)
/*    2e814:	8fb5004c */ 	lw	$s5,0x4c($sp)
/*    2e818:	8fb60050 */ 	lw	$s6,0x50($sp)
/*    2e81c:	8fb70054 */ 	lw	$s7,0x54($sp)
/*    2e820:	8fbe0058 */ 	lw	$s8,0x58($sp)
/*    2e824:	03e00008 */ 	jr	$ra
/*    2e828:	27bd00a0 */ 	addiu	$sp,$sp,0xa0
);

GLOBAL_ASM(
glabel func0002e82c
/*    2e82c:	27bdff60 */ 	addiu	$sp,$sp,-160
/*    2e830:	afb40048 */ 	sw	$s4,0x48($sp)
/*    2e834:	afb1003c */ 	sw	$s1,0x3c($sp)
/*    2e838:	afb00038 */ 	sw	$s0,0x38($sp)
/*    2e83c:	00a08825 */ 	or	$s1,$a1,$zero
/*    2e840:	00c0a025 */ 	or	$s4,$a2,$zero
/*    2e844:	afbf005c */ 	sw	$ra,0x5c($sp)
/*    2e848:	afbe0058 */ 	sw	$s8,0x58($sp)
/*    2e84c:	afb70054 */ 	sw	$s7,0x54($sp)
/*    2e850:	afb60050 */ 	sw	$s6,0x50($sp)
/*    2e854:	afb5004c */ 	sw	$s5,0x4c($sp)
/*    2e858:	afb30044 */ 	sw	$s3,0x44($sp)
/*    2e85c:	afb20040 */ 	sw	$s2,0x40($sp)
/*    2e860:	f7b40030 */ 	sdc1	$f20,0x30($sp)
/*    2e864:	afa400a0 */ 	sw	$a0,0xa0($sp)
/*    2e868:	afa700ac */ 	sw	$a3,0xac($sp)
/*    2e86c:	afa0009c */ 	sw	$zero,0x9c($sp)
/*    2e870:	18a0004b */ 	blez	$a1,.L0002e9a0
/*    2e874:	00008025 */ 	or	$s0,$zero,$zero
/*    2e878:	4480a000 */ 	mtc1	$zero,$f20
/*    2e87c:	27be0078 */ 	addiu	$s8,$sp,0x78
/*    2e880:	27b70084 */ 	addiu	$s7,$sp,0x84
/*    2e884:	27b6006c */ 	addiu	$s6,$sp,0x6c
/*    2e888:	2415000c */ 	addiu	$s5,$zero,0xc
.L0002e88c:
/*    2e88c:	3c0e8006 */ 	lui	$t6,%hi(var8005f030)
/*    2e890:	8dcef030 */ 	lw	$t6,%lo(var8005f030)($t6)
/*    2e894:	51c00013 */ 	beqzl	$t6,.L0002e8e4
/*    2e898:	26190001 */ 	addiu	$t9,$s0,0x1
/*    2e89c:	02301023 */ 	subu	$v0,$s1,$s0
/*    2e8a0:	00517821 */ 	addu	$t7,$v0,$s1
/*    2e8a4:	25f8fffe */ 	addiu	$t8,$t7,-2
/*    2e8a8:	0311001a */ 	div	$zero,$t8,$s1
/*    2e8ac:	00001810 */ 	mfhi	$v1
/*    2e8b0:	2448ffff */ 	addiu	$t0,$v0,-1
/*    2e8b4:	16200002 */ 	bnez	$s1,.L0002e8c0
/*    2e8b8:	00000000 */ 	nop
/*    2e8bc:	0007000d */ 	break	0x7
.L0002e8c0:
/*    2e8c0:	2401ffff */ 	addiu	$at,$zero,-1
/*    2e8c4:	16210004 */ 	bne	$s1,$at,.L0002e8d8
/*    2e8c8:	3c018000 */ 	lui	$at,0x8000
/*    2e8cc:	17010002 */ 	bne	$t8,$at,.L0002e8d8
/*    2e8d0:	00000000 */ 	nop
/*    2e8d4:	0006000d */ 	break	0x6
.L0002e8d8:
/*    2e8d8:	1000000e */ 	b	.L0002e914
/*    2e8dc:	00000000 */ 	nop
/*    2e8e0:	26190001 */ 	addiu	$t9,$s0,0x1
.L0002e8e4:
/*    2e8e4:	0331001a */ 	div	$zero,$t9,$s1
/*    2e8e8:	00001810 */ 	mfhi	$v1
/*    2e8ec:	02004025 */ 	or	$t0,$s0,$zero
/*    2e8f0:	16200002 */ 	bnez	$s1,.L0002e8fc
/*    2e8f4:	00000000 */ 	nop
/*    2e8f8:	0007000d */ 	break	0x7
.L0002e8fc:
/*    2e8fc:	2401ffff */ 	addiu	$at,$zero,-1
/*    2e900:	16210004 */ 	bne	$s1,$at,.L0002e914
/*    2e904:	3c018000 */ 	lui	$at,0x8000
/*    2e908:	17210002 */ 	bne	$t9,$at,.L0002e914
/*    2e90c:	00000000 */ 	nop
/*    2e910:	0006000d */ 	break	0x6
.L0002e914:
/*    2e914:	01150019 */ 	multu	$t0,$s5
/*    2e918:	8faa00ac */ 	lw	$t2,0xac($sp)
/*    2e91c:	8fa700a0 */ 	lw	$a3,0xa0($sp)
/*    2e920:	afb60010 */ 	sw	$s6,0x10($sp)
/*    2e924:	afb70014 */ 	sw	$s7,0x14($sp)
/*    2e928:	afbe0018 */ 	sw	$s8,0x18($sp)
/*    2e92c:	afa0001c */ 	sw	$zero,0x1c($sp)
/*    2e930:	e7b40020 */ 	swc1	$f20,0x20($sp)
/*    2e934:	e7b40024 */ 	swc1	$f20,0x24($sp)
/*    2e938:	00001012 */ 	mflo	$v0
/*    2e93c:	02829021 */ 	addu	$s2,$s4,$v0
/*    2e940:	02402025 */ 	or	$a0,$s2,$zero
/*    2e944:	00750019 */ 	multu	$v1,$s5
/*    2e948:	01423021 */ 	addu	$a2,$t2,$v0
/*    2e94c:	00004812 */ 	mflo	$t1
/*    2e950:	02899821 */ 	addu	$s3,$s4,$t1
/*    2e954:	0c00ac4a */ 	jal	func0002b128
/*    2e958:	02602825 */ 	or	$a1,$s3,$zero
/*    2e95c:	1040000e */ 	beqz	$v0,.L0002e998
/*    2e960:	26100001 */ 	addiu	$s0,$s0,0x1
/*    2e964:	02e02025 */ 	or	$a0,$s7,$zero
/*    2e968:	03c02825 */ 	or	$a1,$s8,$zero
/*    2e96c:	02c03025 */ 	or	$a2,$s6,$zero
/*    2e970:	0c00946b */ 	jal	func000251ac
/*    2e974:	8fa700b0 */ 	lw	$a3,0xb0($sp)
/*    2e978:	02402025 */ 	or	$a0,$s2,$zero
/*    2e97c:	0c0094c5 */ 	jal	func00025314
/*    2e980:	02602825 */ 	or	$a1,$s3,$zero
/*    2e984:	0c0094f1 */ 	jal	func000253c4
/*    2e988:	8fa400b4 */ 	lw	$a0,0xb4($sp)
/*    2e98c:	240b0001 */ 	addiu	$t3,$zero,0x1
/*    2e990:	10000003 */ 	b	.L0002e9a0
/*    2e994:	afab009c */ 	sw	$t3,0x9c($sp)
.L0002e998:
/*    2e998:	1611ffbc */ 	bne	$s0,$s1,.L0002e88c
/*    2e99c:	00000000 */ 	nop
.L0002e9a0:
/*    2e9a0:	8fbf005c */ 	lw	$ra,0x5c($sp)
/*    2e9a4:	8fa2009c */ 	lw	$v0,0x9c($sp)
/*    2e9a8:	d7b40030 */ 	ldc1	$f20,0x30($sp)
/*    2e9ac:	8fb00038 */ 	lw	$s0,0x38($sp)
/*    2e9b0:	8fb1003c */ 	lw	$s1,0x3c($sp)
/*    2e9b4:	8fb20040 */ 	lw	$s2,0x40($sp)
/*    2e9b8:	8fb30044 */ 	lw	$s3,0x44($sp)
/*    2e9bc:	8fb40048 */ 	lw	$s4,0x48($sp)
/*    2e9c0:	8fb5004c */ 	lw	$s5,0x4c($sp)
/*    2e9c4:	8fb60050 */ 	lw	$s6,0x50($sp)
/*    2e9c8:	8fb70054 */ 	lw	$s7,0x54($sp)
/*    2e9cc:	8fbe0058 */ 	lw	$s8,0x58($sp)
/*    2e9d0:	03e00008 */ 	jr	$ra
/*    2e9d4:	27bd00a0 */ 	addiu	$sp,$sp,0xa0
);

GLOBAL_ASM(
glabel func0002e9d8
/*    2e9d8:	27bdff60 */ 	addiu	$sp,$sp,-160
/*    2e9dc:	afb40048 */ 	sw	$s4,0x48($sp)
/*    2e9e0:	afb1003c */ 	sw	$s1,0x3c($sp)
/*    2e9e4:	afb00038 */ 	sw	$s0,0x38($sp)
/*    2e9e8:	00a08825 */ 	or	$s1,$a1,$zero
/*    2e9ec:	00c0a025 */ 	or	$s4,$a2,$zero
/*    2e9f0:	afbf005c */ 	sw	$ra,0x5c($sp)
/*    2e9f4:	afbe0058 */ 	sw	$s8,0x58($sp)
/*    2e9f8:	afb70054 */ 	sw	$s7,0x54($sp)
/*    2e9fc:	afb60050 */ 	sw	$s6,0x50($sp)
/*    2ea00:	afb5004c */ 	sw	$s5,0x4c($sp)
/*    2ea04:	afb30044 */ 	sw	$s3,0x44($sp)
/*    2ea08:	afb20040 */ 	sw	$s2,0x40($sp)
/*    2ea0c:	f7b40030 */ 	sdc1	$f20,0x30($sp)
/*    2ea10:	afa400a0 */ 	sw	$a0,0xa0($sp)
/*    2ea14:	afa700ac */ 	sw	$a3,0xac($sp)
/*    2ea18:	afa0009c */ 	sw	$zero,0x9c($sp)
/*    2ea1c:	18a0004b */ 	blez	$a1,.L0002eb4c
/*    2ea20:	00008025 */ 	or	$s0,$zero,$zero
/*    2ea24:	4480a000 */ 	mtc1	$zero,$f20
/*    2ea28:	27be0078 */ 	addiu	$s8,$sp,0x78
/*    2ea2c:	27b70084 */ 	addiu	$s7,$sp,0x84
/*    2ea30:	27b6006c */ 	addiu	$s6,$sp,0x6c
/*    2ea34:	2415000c */ 	addiu	$s5,$zero,0xc
.L0002ea38:
/*    2ea38:	3c0e8006 */ 	lui	$t6,%hi(var8005f030)
/*    2ea3c:	8dcef030 */ 	lw	$t6,%lo(var8005f030)($t6)
/*    2ea40:	51c00013 */ 	beqzl	$t6,.L0002ea90
/*    2ea44:	26190001 */ 	addiu	$t9,$s0,0x1
/*    2ea48:	02301023 */ 	subu	$v0,$s1,$s0
/*    2ea4c:	00517821 */ 	addu	$t7,$v0,$s1
/*    2ea50:	25f8fffe */ 	addiu	$t8,$t7,-2
/*    2ea54:	0311001a */ 	div	$zero,$t8,$s1
/*    2ea58:	00001810 */ 	mfhi	$v1
/*    2ea5c:	2448ffff */ 	addiu	$t0,$v0,-1
/*    2ea60:	16200002 */ 	bnez	$s1,.L0002ea6c
/*    2ea64:	00000000 */ 	nop
/*    2ea68:	0007000d */ 	break	0x7
.L0002ea6c:
/*    2ea6c:	2401ffff */ 	addiu	$at,$zero,-1
/*    2ea70:	16210004 */ 	bne	$s1,$at,.L0002ea84
/*    2ea74:	3c018000 */ 	lui	$at,0x8000
/*    2ea78:	17010002 */ 	bne	$t8,$at,.L0002ea84
/*    2ea7c:	00000000 */ 	nop
/*    2ea80:	0006000d */ 	break	0x6
.L0002ea84:
/*    2ea84:	1000000e */ 	b	.L0002eac0
/*    2ea88:	00000000 */ 	nop
/*    2ea8c:	26190001 */ 	addiu	$t9,$s0,0x1
.L0002ea90:
/*    2ea90:	0331001a */ 	div	$zero,$t9,$s1
/*    2ea94:	00001810 */ 	mfhi	$v1
/*    2ea98:	02004025 */ 	or	$t0,$s0,$zero
/*    2ea9c:	16200002 */ 	bnez	$s1,.L0002eaa8
/*    2eaa0:	00000000 */ 	nop
/*    2eaa4:	0007000d */ 	break	0x7
.L0002eaa8:
/*    2eaa8:	2401ffff */ 	addiu	$at,$zero,-1
/*    2eaac:	16210004 */ 	bne	$s1,$at,.L0002eac0
/*    2eab0:	3c018000 */ 	lui	$at,0x8000
/*    2eab4:	17210002 */ 	bne	$t9,$at,.L0002eac0
/*    2eab8:	00000000 */ 	nop
/*    2eabc:	0006000d */ 	break	0x6
.L0002eac0:
/*    2eac0:	01150019 */ 	multu	$t0,$s5
/*    2eac4:	8faa00ac */ 	lw	$t2,0xac($sp)
/*    2eac8:	8fa700a0 */ 	lw	$a3,0xa0($sp)
/*    2eacc:	afb60010 */ 	sw	$s6,0x10($sp)
/*    2ead0:	afb70014 */ 	sw	$s7,0x14($sp)
/*    2ead4:	afbe0018 */ 	sw	$s8,0x18($sp)
/*    2ead8:	afa0001c */ 	sw	$zero,0x1c($sp)
/*    2eadc:	e7b40020 */ 	swc1	$f20,0x20($sp)
/*    2eae0:	e7b40024 */ 	swc1	$f20,0x24($sp)
/*    2eae4:	00001012 */ 	mflo	$v0
/*    2eae8:	02829021 */ 	addu	$s2,$s4,$v0
/*    2eaec:	02402025 */ 	or	$a0,$s2,$zero
/*    2eaf0:	00750019 */ 	multu	$v1,$s5
/*    2eaf4:	01423021 */ 	addu	$a2,$t2,$v0
/*    2eaf8:	00004812 */ 	mflo	$t1
/*    2eafc:	02899821 */ 	addu	$s3,$s4,$t1
/*    2eb00:	0c00ad58 */ 	jal	func0002b560
/*    2eb04:	02602825 */ 	or	$a1,$s3,$zero
/*    2eb08:	1040000e */ 	beqz	$v0,.L0002eb44
/*    2eb0c:	26100001 */ 	addiu	$s0,$s0,0x1
/*    2eb10:	02e02025 */ 	or	$a0,$s7,$zero
/*    2eb14:	03c02825 */ 	or	$a1,$s8,$zero
/*    2eb18:	02c03025 */ 	or	$a2,$s6,$zero
/*    2eb1c:	0c00946b */ 	jal	func000251ac
/*    2eb20:	8fa700b0 */ 	lw	$a3,0xb0($sp)
/*    2eb24:	02402025 */ 	or	$a0,$s2,$zero
/*    2eb28:	0c0094c5 */ 	jal	func00025314
/*    2eb2c:	02602825 */ 	or	$a1,$s3,$zero
/*    2eb30:	0c0094f1 */ 	jal	func000253c4
/*    2eb34:	8fa400b4 */ 	lw	$a0,0xb4($sp)
/*    2eb38:	240b0001 */ 	addiu	$t3,$zero,0x1
/*    2eb3c:	10000003 */ 	b	.L0002eb4c
/*    2eb40:	afab009c */ 	sw	$t3,0x9c($sp)
.L0002eb44:
/*    2eb44:	1611ffbc */ 	bne	$s0,$s1,.L0002ea38
/*    2eb48:	00000000 */ 	nop
.L0002eb4c:
/*    2eb4c:	8fbf005c */ 	lw	$ra,0x5c($sp)
/*    2eb50:	8fa2009c */ 	lw	$v0,0x9c($sp)
/*    2eb54:	d7b40030 */ 	ldc1	$f20,0x30($sp)
/*    2eb58:	8fb00038 */ 	lw	$s0,0x38($sp)
/*    2eb5c:	8fb1003c */ 	lw	$s1,0x3c($sp)
/*    2eb60:	8fb20040 */ 	lw	$s2,0x40($sp)
/*    2eb64:	8fb30044 */ 	lw	$s3,0x44($sp)
/*    2eb68:	8fb40048 */ 	lw	$s4,0x48($sp)
/*    2eb6c:	8fb5004c */ 	lw	$s5,0x4c($sp)
/*    2eb70:	8fb60050 */ 	lw	$s6,0x50($sp)
/*    2eb74:	8fb70054 */ 	lw	$s7,0x54($sp)
/*    2eb78:	8fbe0058 */ 	lw	$s8,0x58($sp)
/*    2eb7c:	03e00008 */ 	jr	$ra
/*    2eb80:	27bd00a0 */ 	addiu	$sp,$sp,0xa0
);

GLOBAL_ASM(
glabel func0002eb84
/*    2eb84:	27bdff60 */ 	addiu	$sp,$sp,-160
/*    2eb88:	afb40048 */ 	sw	$s4,0x48($sp)
/*    2eb8c:	afb1003c */ 	sw	$s1,0x3c($sp)
/*    2eb90:	afb00038 */ 	sw	$s0,0x38($sp)
/*    2eb94:	00a08825 */ 	or	$s1,$a1,$zero
/*    2eb98:	00c0a025 */ 	or	$s4,$a2,$zero
/*    2eb9c:	afbf005c */ 	sw	$ra,0x5c($sp)
/*    2eba0:	afbe0058 */ 	sw	$s8,0x58($sp)
/*    2eba4:	afb70054 */ 	sw	$s7,0x54($sp)
/*    2eba8:	afb60050 */ 	sw	$s6,0x50($sp)
/*    2ebac:	afb5004c */ 	sw	$s5,0x4c($sp)
/*    2ebb0:	afb30044 */ 	sw	$s3,0x44($sp)
/*    2ebb4:	afb20040 */ 	sw	$s2,0x40($sp)
/*    2ebb8:	f7b40030 */ 	sdc1	$f20,0x30($sp)
/*    2ebbc:	afa400a0 */ 	sw	$a0,0xa0($sp)
/*    2ebc0:	afa700ac */ 	sw	$a3,0xac($sp)
/*    2ebc4:	afa0009c */ 	sw	$zero,0x9c($sp)
/*    2ebc8:	18a0004b */ 	blez	$a1,.L0002ecf8
/*    2ebcc:	00008025 */ 	or	$s0,$zero,$zero
/*    2ebd0:	4480a000 */ 	mtc1	$zero,$f20
/*    2ebd4:	27be0078 */ 	addiu	$s8,$sp,0x78
/*    2ebd8:	27b70084 */ 	addiu	$s7,$sp,0x84
/*    2ebdc:	27b6006c */ 	addiu	$s6,$sp,0x6c
/*    2ebe0:	2415000c */ 	addiu	$s5,$zero,0xc
.L0002ebe4:
/*    2ebe4:	3c0e8006 */ 	lui	$t6,%hi(var8005f030)
/*    2ebe8:	8dcef030 */ 	lw	$t6,%lo(var8005f030)($t6)
/*    2ebec:	51c00013 */ 	beqzl	$t6,.L0002ec3c
/*    2ebf0:	26190001 */ 	addiu	$t9,$s0,0x1
/*    2ebf4:	02301023 */ 	subu	$v0,$s1,$s0
/*    2ebf8:	00517821 */ 	addu	$t7,$v0,$s1
/*    2ebfc:	25f8fffe */ 	addiu	$t8,$t7,-2
/*    2ec00:	0311001a */ 	div	$zero,$t8,$s1
/*    2ec04:	00001810 */ 	mfhi	$v1
/*    2ec08:	2448ffff */ 	addiu	$t0,$v0,-1
/*    2ec0c:	16200002 */ 	bnez	$s1,.L0002ec18
/*    2ec10:	00000000 */ 	nop
/*    2ec14:	0007000d */ 	break	0x7
.L0002ec18:
/*    2ec18:	2401ffff */ 	addiu	$at,$zero,-1
/*    2ec1c:	16210004 */ 	bne	$s1,$at,.L0002ec30
/*    2ec20:	3c018000 */ 	lui	$at,0x8000
/*    2ec24:	17010002 */ 	bne	$t8,$at,.L0002ec30
/*    2ec28:	00000000 */ 	nop
/*    2ec2c:	0006000d */ 	break	0x6
.L0002ec30:
/*    2ec30:	1000000e */ 	b	.L0002ec6c
/*    2ec34:	00000000 */ 	nop
/*    2ec38:	26190001 */ 	addiu	$t9,$s0,0x1
.L0002ec3c:
/*    2ec3c:	0331001a */ 	div	$zero,$t9,$s1
/*    2ec40:	00001810 */ 	mfhi	$v1
/*    2ec44:	02004025 */ 	or	$t0,$s0,$zero
/*    2ec48:	16200002 */ 	bnez	$s1,.L0002ec54
/*    2ec4c:	00000000 */ 	nop
/*    2ec50:	0007000d */ 	break	0x7
.L0002ec54:
/*    2ec54:	2401ffff */ 	addiu	$at,$zero,-1
/*    2ec58:	16210004 */ 	bne	$s1,$at,.L0002ec6c
/*    2ec5c:	3c018000 */ 	lui	$at,0x8000
/*    2ec60:	17210002 */ 	bne	$t9,$at,.L0002ec6c
/*    2ec64:	00000000 */ 	nop
/*    2ec68:	0006000d */ 	break	0x6
.L0002ec6c:
/*    2ec6c:	01150019 */ 	multu	$t0,$s5
/*    2ec70:	8faa00ac */ 	lw	$t2,0xac($sp)
/*    2ec74:	8fa700a0 */ 	lw	$a3,0xa0($sp)
/*    2ec78:	afb60010 */ 	sw	$s6,0x10($sp)
/*    2ec7c:	afb70014 */ 	sw	$s7,0x14($sp)
/*    2ec80:	afbe0018 */ 	sw	$s8,0x18($sp)
/*    2ec84:	afa0001c */ 	sw	$zero,0x1c($sp)
/*    2ec88:	e7b40020 */ 	swc1	$f20,0x20($sp)
/*    2ec8c:	e7b40024 */ 	swc1	$f20,0x24($sp)
/*    2ec90:	00001012 */ 	mflo	$v0
/*    2ec94:	02829021 */ 	addu	$s2,$s4,$v0
/*    2ec98:	02402025 */ 	or	$a0,$s2,$zero
/*    2ec9c:	00750019 */ 	multu	$v1,$s5
/*    2eca0:	01423021 */ 	addu	$a2,$t2,$v0
/*    2eca4:	00004812 */ 	mflo	$t1
/*    2eca8:	02899821 */ 	addu	$s3,$s4,$t1
/*    2ecac:	0c00ae55 */ 	jal	func0002b954
/*    2ecb0:	02602825 */ 	or	$a1,$s3,$zero
/*    2ecb4:	1040000e */ 	beqz	$v0,.L0002ecf0
/*    2ecb8:	26100001 */ 	addiu	$s0,$s0,0x1
/*    2ecbc:	02e02025 */ 	or	$a0,$s7,$zero
/*    2ecc0:	03c02825 */ 	or	$a1,$s8,$zero
/*    2ecc4:	02c03025 */ 	or	$a2,$s6,$zero
/*    2ecc8:	0c00946b */ 	jal	func000251ac
/*    2eccc:	8fa700b0 */ 	lw	$a3,0xb0($sp)
/*    2ecd0:	02402025 */ 	or	$a0,$s2,$zero
/*    2ecd4:	0c0094c5 */ 	jal	func00025314
/*    2ecd8:	02602825 */ 	or	$a1,$s3,$zero
/*    2ecdc:	0c0094f1 */ 	jal	func000253c4
/*    2ece0:	8fa400b4 */ 	lw	$a0,0xb4($sp)
/*    2ece4:	240b0001 */ 	addiu	$t3,$zero,0x1
/*    2ece8:	10000003 */ 	b	.L0002ecf8
/*    2ecec:	afab009c */ 	sw	$t3,0x9c($sp)
.L0002ecf0:
/*    2ecf0:	1611ffbc */ 	bne	$s0,$s1,.L0002ebe4
/*    2ecf4:	00000000 */ 	nop
.L0002ecf8:
/*    2ecf8:	8fbf005c */ 	lw	$ra,0x5c($sp)
/*    2ecfc:	8fa2009c */ 	lw	$v0,0x9c($sp)
/*    2ed00:	d7b40030 */ 	ldc1	$f20,0x30($sp)
/*    2ed04:	8fb00038 */ 	lw	$s0,0x38($sp)
/*    2ed08:	8fb1003c */ 	lw	$s1,0x3c($sp)
/*    2ed0c:	8fb20040 */ 	lw	$s2,0x40($sp)
/*    2ed10:	8fb30044 */ 	lw	$s3,0x44($sp)
/*    2ed14:	8fb40048 */ 	lw	$s4,0x48($sp)
/*    2ed18:	8fb5004c */ 	lw	$s5,0x4c($sp)
/*    2ed1c:	8fb60050 */ 	lw	$s6,0x50($sp)
/*    2ed20:	8fb70054 */ 	lw	$s7,0x54($sp)
/*    2ed24:	8fbe0058 */ 	lw	$s8,0x58($sp)
/*    2ed28:	03e00008 */ 	jr	$ra
/*    2ed2c:	27bd00a0 */ 	addiu	$sp,$sp,0xa0
);

GLOBAL_ASM(
glabel func0002ed30
/*    2ed30:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*    2ed34:	afb40030 */ 	sw	$s4,0x30($sp)
/*    2ed38:	afb10024 */ 	sw	$s1,0x24($sp)
/*    2ed3c:	afb00020 */ 	sw	$s0,0x20($sp)
/*    2ed40:	0085082b */ 	sltu	$at,$a0,$a1
/*    2ed44:	00c08825 */ 	or	$s1,$a2,$zero
/*    2ed48:	00e0a025 */ 	or	$s4,$a3,$zero
/*    2ed4c:	afbf0044 */ 	sw	$ra,0x44($sp)
/*    2ed50:	afbe0040 */ 	sw	$s8,0x40($sp)
/*    2ed54:	afb7003c */ 	sw	$s7,0x3c($sp)
/*    2ed58:	afb60038 */ 	sw	$s6,0x38($sp)
/*    2ed5c:	afb50034 */ 	sw	$s5,0x34($sp)
/*    2ed60:	afb3002c */ 	sw	$s3,0x2c($sp)
/*    2ed64:	afb20028 */ 	sw	$s2,0x28($sp)
/*    2ed68:	afa5004c */ 	sw	$a1,0x4c($sp)
/*    2ed6c:	102000a2 */ 	beqz	$at,.L0002eff8
/*    2ed70:	00808025 */ 	or	$s0,$a0,$zero
/*    2ed74:	241e000c */ 	addiu	$s8,$zero,0xc
/*    2ed78:	8fb70064 */ 	lw	$s7,0x64($sp)
/*    2ed7c:	8fb6005c */ 	lw	$s6,0x5c($sp)
/*    2ed80:	8fb50058 */ 	lw	$s5,0x58($sp)
/*    2ed84:	97b30062 */ 	lhu	$s3,0x62($sp)
/*    2ed88:	92020000 */ 	lbu	$v0,0x0($s0)
.L0002ed8c:
/*    2ed8c:	24010001 */ 	addiu	$at,$zero,0x1
/*    2ed90:	1440002d */ 	bnez	$v0,.L0002ee48
/*    2ed94:	00000000 */ 	nop
/*    2ed98:	960f0002 */ 	lhu	$t7,0x2($s0)
/*    2ed9c:	02009025 */ 	or	$s2,$s0,$zero
/*    2eda0:	026fc024 */ 	and	$t8,$s3,$t7
/*    2eda4:	53000022 */ 	beqzl	$t8,.L0002ee30
/*    2eda8:	924d0001 */ 	lbu	$t5,0x1($s2)
/*    2edac:	9219000a */ 	lbu	$t9,0xa($s0)
/*    2edb0:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*    2edb4:	03304021 */ 	addu	$t0,$t9,$s0
/*    2edb8:	85090000 */ 	lh	$t1,0x0($t0)
/*    2edbc:	44892000 */ 	mtc1	$t1,$f4
/*    2edc0:	00000000 */ 	nop
/*    2edc4:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    2edc8:	4606403e */ 	c.le.s	$f8,$f6
/*    2edcc:	00000000 */ 	nop
/*    2edd0:	45020017 */ 	bc1fl	.L0002ee30
/*    2edd4:	924d0001 */ 	lbu	$t5,0x1($s2)
/*    2edd8:	920a0007 */ 	lbu	$t2,0x7($s0)
/*    2eddc:	c62a0004 */ 	lwc1	$f10,0x4($s1)
/*    2ede0:	02002025 */ 	or	$a0,$s0,$zero
/*    2ede4:	01505821 */ 	addu	$t3,$t2,$s0
/*    2ede8:	856c0000 */ 	lh	$t4,0x0($t3)
/*    2edec:	02802825 */ 	or	$a1,$s4,$zero
/*    2edf0:	02a03025 */ 	or	$a2,$s5,$zero
/*    2edf4:	448c8000 */ 	mtc1	$t4,$f16
/*    2edf8:	02c03825 */ 	or	$a3,$s6,$zero
/*    2edfc:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    2ee00:	460a903e */ 	c.le.s	$f18,$f10
/*    2ee04:	00000000 */ 	nop
/*    2ee08:	45020009 */ 	bc1fl	.L0002ee30
/*    2ee0c:	924d0001 */ 	lbu	$t5,0x1($s2)
/*    2ee10:	afb70010 */ 	sw	$s7,0x10($sp)
/*    2ee14:	0c00b9a0 */ 	jal	func0002e680
/*    2ee18:	afb10014 */ 	sw	$s1,0x14($sp)
/*    2ee1c:	50400004 */ 	beqzl	$v0,.L0002ee30
/*    2ee20:	924d0001 */ 	lbu	$t5,0x1($s2)
/*    2ee24:	10000075 */ 	b	.L0002effc
/*    2ee28:	00001025 */ 	or	$v0,$zero,$zero
/*    2ee2c:	924d0001 */ 	lbu	$t5,0x1($s2)
.L0002ee30:
/*    2ee30:	000d7080 */ 	sll	$t6,$t5,0x2
/*    2ee34:	01cd7023 */ 	subu	$t6,$t6,$t5
/*    2ee38:	000e7040 */ 	sll	$t6,$t6,0x1
/*    2ee3c:	020e8021 */ 	addu	$s0,$s0,$t6
/*    2ee40:	10000069 */ 	b	.L0002efe8
/*    2ee44:	2610000e */ 	addiu	$s0,$s0,0xe
.L0002ee48:
/*    2ee48:	5441002d */ 	bnel	$v0,$at,.L0002ef00
/*    2ee4c:	24010002 */ 	addiu	$at,$zero,0x2
/*    2ee50:	960f0002 */ 	lhu	$t7,0x2($s0)
/*    2ee54:	02009025 */ 	or	$s2,$s0,$zero
/*    2ee58:	026fc024 */ 	and	$t8,$s3,$t7
/*    2ee5c:	53000021 */ 	beqzl	$t8,.L0002eee4
/*    2ee60:	924d0001 */ 	lbu	$t5,0x1($s2)
/*    2ee64:	9219000a */ 	lbu	$t9,0xa($s0)
/*    2ee68:	c6260008 */ 	lwc1	$f6,0x8($s1)
/*    2ee6c:	033e0019 */ 	multu	$t9,$s8
/*    2ee70:	00004012 */ 	mflo	$t0
/*    2ee74:	02084821 */ 	addu	$t1,$s0,$t0
/*    2ee78:	c5240014 */ 	lwc1	$f4,0x14($t1)
/*    2ee7c:	4604303e */ 	c.le.s	$f6,$f4
/*    2ee80:	00000000 */ 	nop
/*    2ee84:	45020017 */ 	bc1fl	.L0002eee4
/*    2ee88:	924d0001 */ 	lbu	$t5,0x1($s2)
/*    2ee8c:	920a0007 */ 	lbu	$t2,0x7($s0)
/*    2ee90:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*    2ee94:	02002025 */ 	or	$a0,$s0,$zero
/*    2ee98:	015e0019 */ 	multu	$t2,$s8
/*    2ee9c:	02802825 */ 	or	$a1,$s4,$zero
/*    2eea0:	02a03025 */ 	or	$a2,$s5,$zero
/*    2eea4:	02c03825 */ 	or	$a3,$s6,$zero
/*    2eea8:	00005812 */ 	mflo	$t3
/*    2eeac:	020b6021 */ 	addu	$t4,$s0,$t3
/*    2eeb0:	c5900014 */ 	lwc1	$f16,0x14($t4)
/*    2eeb4:	4608803e */ 	c.le.s	$f16,$f8
/*    2eeb8:	00000000 */ 	nop
/*    2eebc:	45020009 */ 	bc1fl	.L0002eee4
/*    2eec0:	924d0001 */ 	lbu	$t5,0x1($s2)
/*    2eec4:	afb70010 */ 	sw	$s7,0x10($sp)
/*    2eec8:	0c00ba0b */ 	jal	func0002e82c
/*    2eecc:	afb10014 */ 	sw	$s1,0x14($sp)
/*    2eed0:	50400004 */ 	beqzl	$v0,.L0002eee4
/*    2eed4:	924d0001 */ 	lbu	$t5,0x1($s2)
/*    2eed8:	10000048 */ 	b	.L0002effc
/*    2eedc:	00001025 */ 	or	$v0,$zero,$zero
/*    2eee0:	924d0001 */ 	lbu	$t5,0x1($s2)
.L0002eee4:
/*    2eee4:	25aeffc0 */ 	addiu	$t6,$t5,-64
/*    2eee8:	01de0019 */ 	multu	$t6,$s8
/*    2eeec:	00007812 */ 	mflo	$t7
/*    2eef0:	020f8021 */ 	addu	$s0,$s0,$t7
/*    2eef4:	1000003c */ 	b	.L0002efe8
/*    2eef8:	26100310 */ 	addiu	$s0,$s0,0x310
/*    2eefc:	24010002 */ 	addiu	$at,$zero,0x2
.L0002ef00:
/*    2ef00:	1441001b */ 	bne	$v0,$at,.L0002ef70
/*    2ef04:	3278001c */ 	andi	$t8,$s3,0x1c
/*    2ef08:	13000017 */ 	beqz	$t8,.L0002ef68
/*    2ef0c:	00000000 */ 	nop
/*    2ef10:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*    2ef14:	c6320008 */ 	lwc1	$f18,0x8($s1)
/*    2ef18:	460a903e */ 	c.le.s	$f18,$f10
/*    2ef1c:	00000000 */ 	nop
/*    2ef20:	45000011 */ 	bc1f	.L0002ef68
/*    2ef24:	00000000 */ 	nop
/*    2ef28:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*    2ef2c:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*    2ef30:	02002025 */ 	or	$a0,$s0,$zero
/*    2ef34:	02802825 */ 	or	$a1,$s4,$zero
/*    2ef38:	4604303e */ 	c.le.s	$f6,$f4
/*    2ef3c:	02a03025 */ 	or	$a2,$s5,$zero
/*    2ef40:	02c03825 */ 	or	$a3,$s6,$zero
/*    2ef44:	45000008 */ 	bc1f	.L0002ef68
/*    2ef48:	00000000 */ 	nop
/*    2ef4c:	afb70010 */ 	sw	$s7,0x10($sp)
/*    2ef50:	0c00ba76 */ 	jal	func0002e9d8
/*    2ef54:	afb10014 */ 	sw	$s1,0x14($sp)
/*    2ef58:	10400003 */ 	beqz	$v0,.L0002ef68
/*    2ef5c:	00000000 */ 	nop
/*    2ef60:	10000026 */ 	b	.L0002effc
/*    2ef64:	00001025 */ 	or	$v0,$zero,$zero
.L0002ef68:
/*    2ef68:	1000001f */ 	b	.L0002efe8
/*    2ef6c:	2610004c */ 	addiu	$s0,$s0,0x4c
.L0002ef70:
/*    2ef70:	24010003 */ 	addiu	$at,$zero,0x3
/*    2ef74:	5441001d */ 	bnel	$v0,$at,.L0002efec
/*    2ef78:	8fa9004c */ 	lw	$t1,0x4c($sp)
/*    2ef7c:	96190002 */ 	lhu	$t9,0x2($s0)
/*    2ef80:	02794024 */ 	and	$t0,$s3,$t9
/*    2ef84:	51000018 */ 	beqzl	$t0,.L0002efe8
/*    2ef88:	26100018 */ 	addiu	$s0,$s0,0x18
/*    2ef8c:	c6080004 */ 	lwc1	$f8,0x4($s0)
/*    2ef90:	c6300008 */ 	lwc1	$f16,0x8($s1)
/*    2ef94:	4608803e */ 	c.le.s	$f16,$f8
/*    2ef98:	00000000 */ 	nop
/*    2ef9c:	45020012 */ 	bc1fl	.L0002efe8
/*    2efa0:	26100018 */ 	addiu	$s0,$s0,0x18
/*    2efa4:	c62a0004 */ 	lwc1	$f10,0x4($s1)
/*    2efa8:	c6120008 */ 	lwc1	$f18,0x8($s0)
/*    2efac:	02002025 */ 	or	$a0,$s0,$zero
/*    2efb0:	02802825 */ 	or	$a1,$s4,$zero
/*    2efb4:	460a903e */ 	c.le.s	$f18,$f10
/*    2efb8:	02a03025 */ 	or	$a2,$s5,$zero
/*    2efbc:	02c03825 */ 	or	$a3,$s6,$zero
/*    2efc0:	45020009 */ 	bc1fl	.L0002efe8
/*    2efc4:	26100018 */ 	addiu	$s0,$s0,0x18
/*    2efc8:	afb70010 */ 	sw	$s7,0x10($sp)
/*    2efcc:	0c00bae1 */ 	jal	func0002eb84
/*    2efd0:	afb10014 */ 	sw	$s1,0x14($sp)
/*    2efd4:	50400004 */ 	beqzl	$v0,.L0002efe8
/*    2efd8:	26100018 */ 	addiu	$s0,$s0,0x18
/*    2efdc:	10000007 */ 	b	.L0002effc
/*    2efe0:	00001025 */ 	or	$v0,$zero,$zero
/*    2efe4:	26100018 */ 	addiu	$s0,$s0,0x18
.L0002efe8:
/*    2efe8:	8fa9004c */ 	lw	$t1,0x4c($sp)
.L0002efec:
/*    2efec:	0209082b */ 	sltu	$at,$s0,$t1
/*    2eff0:	5420ff66 */ 	bnezl	$at,.L0002ed8c
/*    2eff4:	92020000 */ 	lbu	$v0,0x0($s0)
.L0002eff8:
/*    2eff8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0002effc:
/*    2effc:	8fbf0044 */ 	lw	$ra,0x44($sp)
/*    2f000:	8fb00020 */ 	lw	$s0,0x20($sp)
/*    2f004:	8fb10024 */ 	lw	$s1,0x24($sp)
/*    2f008:	8fb20028 */ 	lw	$s2,0x28($sp)
/*    2f00c:	8fb3002c */ 	lw	$s3,0x2c($sp)
/*    2f010:	8fb40030 */ 	lw	$s4,0x30($sp)
/*    2f014:	8fb50034 */ 	lw	$s5,0x34($sp)
/*    2f018:	8fb60038 */ 	lw	$s6,0x38($sp)
/*    2f01c:	8fb7003c */ 	lw	$s7,0x3c($sp)
/*    2f020:	8fbe0040 */ 	lw	$s8,0x40($sp)
/*    2f024:	03e00008 */ 	jr	$ra
/*    2f028:	27bd0048 */ 	addiu	$sp,$sp,0x48
);

GLOBAL_ASM(
glabel func0002f02c
/*    2f02c:	27bdfcb8 */ 	addiu	$sp,$sp,-840
/*    2f030:	afbf004c */ 	sw	$ra,0x4c($sp)
/*    2f034:	afbe0048 */ 	sw	$s8,0x48($sp)
/*    2f038:	afb70044 */ 	sw	$s7,0x44($sp)
/*    2f03c:	afb60040 */ 	sw	$s6,0x40($sp)
/*    2f040:	afb5003c */ 	sw	$s5,0x3c($sp)
/*    2f044:	afb40038 */ 	sw	$s4,0x38($sp)
/*    2f048:	afb30034 */ 	sw	$s3,0x34($sp)
/*    2f04c:	afb20030 */ 	sw	$s2,0x30($sp)
/*    2f050:	afb1002c */ 	sw	$s1,0x2c($sp)
/*    2f054:	afb00028 */ 	sw	$s0,0x28($sp)
/*    2f058:	afa5034c */ 	sw	$a1,0x34c($sp)
/*    2f05c:	afa60350 */ 	sw	$a2,0x350($sp)
/*    2f060:	90920001 */ 	lbu	$s2,0x1($a0)
/*    2f064:	0080b025 */ 	or	$s6,$a0,$zero
/*    2f068:	24090001 */ 	addiu	$t1,$zero,0x1
/*    2f06c:	1a40000e */ 	blez	$s2,.L0002f0a8
/*    2f070:	00003825 */ 	or	$a3,$zero,$zero
/*    2f074:	27a200cc */ 	addiu	$v0,$sp,0xcc
/*    2f078:	00801825 */ 	or	$v1,$a0,$zero
.L0002f07c:
/*    2f07c:	c464000c */ 	lwc1	$f4,0xc($v1)
/*    2f080:	24e70001 */ 	addiu	$a3,$a3,0x1
/*    2f084:	2442000c */ 	addiu	$v0,$v0,0xc
/*    2f088:	e444fff4 */ 	swc1	$f4,-0xc($v0)
/*    2f08c:	c6c60004 */ 	lwc1	$f6,0x4($s6)
/*    2f090:	24630008 */ 	addiu	$v1,$v1,0x8
/*    2f094:	e446fff8 */ 	swc1	$f6,-0x8($v0)
/*    2f098:	c4680008 */ 	lwc1	$f8,0x8($v1)
/*    2f09c:	14f2fff7 */ 	bne	$a3,$s2,.L0002f07c
/*    2f0a0:	e448fffc */ 	swc1	$f8,-0x4($v0)
/*    2f0a4:	00003825 */ 	or	$a3,$zero,$zero
.L0002f0a8:
/*    2f0a8:	1a400023 */ 	blez	$s2,.L0002f138
/*    2f0ac:	27a200cc */ 	addiu	$v0,$sp,0xcc
/*    2f0b0:	27a5006c */ 	addiu	$a1,$sp,0x6c
/*    2f0b4:	27b500cc */ 	addiu	$s5,$sp,0xcc
/*    2f0b8:	2406000c */ 	addiu	$a2,$zero,0xc
.L0002f0bc:
/*    2f0bc:	24e40001 */ 	addiu	$a0,$a3,0x1
/*    2f0c0:	0092001a */ 	div	$zero,$a0,$s2
/*    2f0c4:	00007010 */ 	mfhi	$t6
/*    2f0c8:	c4500000 */ 	lwc1	$f16,0x0($v0)
/*    2f0cc:	c4460004 */ 	lwc1	$f6,0x4($v0)
/*    2f0d0:	01c60019 */ 	multu	$t6,$a2
/*    2f0d4:	00803825 */ 	or	$a3,$a0,$zero
/*    2f0d8:	16400002 */ 	bnez	$s2,.L0002f0e4
/*    2f0dc:	00000000 */ 	nop
/*    2f0e0:	0007000d */ 	break	0x7
.L0002f0e4:
/*    2f0e4:	2401ffff */ 	addiu	$at,$zero,-1
/*    2f0e8:	16410004 */ 	bne	$s2,$at,.L0002f0fc
/*    2f0ec:	3c018000 */ 	lui	$at,0x8000
/*    2f0f0:	14810002 */ 	bne	$a0,$at,.L0002f0fc
/*    2f0f4:	00000000 */ 	nop
/*    2f0f8:	0006000d */ 	break	0x6
.L0002f0fc:
/*    2f0fc:	00007812 */ 	mflo	$t7
/*    2f100:	02af1821 */ 	addu	$v1,$s5,$t7
/*    2f104:	c46a0000 */ 	lwc1	$f10,0x0($v1)
/*    2f108:	c4640004 */ 	lwc1	$f4,0x4($v1)
/*    2f10c:	2442000c */ 	addiu	$v0,$v0,0xc
/*    2f110:	46105481 */ 	sub.s	$f18,$f10,$f16
/*    2f114:	c450fffc */ 	lwc1	$f16,-0x4($v0)
/*    2f118:	c46a0008 */ 	lwc1	$f10,0x8($v1)
/*    2f11c:	46062201 */ 	sub.s	$f8,$f4,$f6
/*    2f120:	e4b20000 */ 	swc1	$f18,0x0($a1)
/*    2f124:	24a5000c */ 	addiu	$a1,$a1,0xc
/*    2f128:	46105481 */ 	sub.s	$f18,$f10,$f16
/*    2f12c:	e4a8fff8 */ 	swc1	$f8,-0x8($a1)
/*    2f130:	1492ffe2 */ 	bne	$a0,$s2,.L0002f0bc
/*    2f134:	e4b2fffc */ 	swc1	$f18,-0x4($a1)
.L0002f138:
/*    2f138:	8fb80350 */ 	lw	$t8,0x350($sp)
/*    2f13c:	27b500cc */ 	addiu	$s5,$sp,0xcc
/*    2f140:	8fb0034c */ 	lw	$s0,0x34c($sp)
/*    2f144:	33190020 */ 	andi	$t9,$t8,0x20
/*    2f148:	13200027 */ 	beqz	$t9,.L0002f1e8
/*    2f14c:	00000000 */ 	nop
/*    2f150:	86080000 */ 	lh	$t0,0x0($s0)
/*    2f154:	241effff */ 	addiu	$s8,$zero,-1
/*    2f158:	27b7006c */ 	addiu	$s7,$sp,0x6c
/*    2f15c:	111e0022 */ 	beq	$t0,$s8,.L0002f1e8
/*    2f160:	3c14800a */ 	lui	$s4,%hi(g_TileFileData)
/*    2f164:	3c13800a */ 	lui	$s3,%hi(g_TileRooms)
/*    2f168:	3c11800a */ 	lui	$s1,%hi(g_TileNumRooms)
/*    2f16c:	2631a8a4 */ 	addiu	$s1,$s1,%lo(g_TileNumRooms)
/*    2f170:	2673a8a8 */ 	addiu	$s3,$s3,%lo(g_TileRooms)
/*    2f174:	2694a8a0 */ 	addiu	$s4,$s4,%lo(g_TileFileData)
/*    2f178:	8e2b0000 */ 	lw	$t3,0x0($s1)
.L0002f17c:
/*    2f17c:	00086880 */ 	sll	$t5,$t0,0x2
/*    2f180:	010b082a */ 	slt	$at,$t0,$t3
/*    2f184:	50200015 */ 	beqzl	$at,.L0002f1dc
/*    2f188:	86080002 */ 	lh	$t0,0x2($s0)
/*    2f18c:	8e6c0000 */ 	lw	$t4,0x0($s3)
/*    2f190:	8e830000 */ 	lw	$v1,0x0($s4)
/*    2f194:	240a0004 */ 	addiu	$t2,$zero,0x4
/*    2f198:	018d1021 */ 	addu	$v0,$t4,$t5
/*    2f19c:	8c4e0000 */ 	lw	$t6,0x0($v0)
/*    2f1a0:	02c03025 */ 	or	$a2,$s6,$zero
/*    2f1a4:	02403825 */ 	or	$a3,$s2,$zero
/*    2f1a8:	01c32021 */ 	addu	$a0,$t6,$v1
/*    2f1ac:	afa4033c */ 	sw	$a0,0x33c($sp)
/*    2f1b0:	8c580004 */ 	lw	$t8,0x4($v0)
/*    2f1b4:	afa0001c */ 	sw	$zero,0x1c($sp)
/*    2f1b8:	afaa0018 */ 	sw	$t2,0x18($sp)
/*    2f1bc:	03032821 */ 	addu	$a1,$t8,$v1
/*    2f1c0:	afa50338 */ 	sw	$a1,0x338($sp)
/*    2f1c4:	afb70014 */ 	sw	$s7,0x14($sp)
/*    2f1c8:	0c00bb4c */ 	jal	func0002ed30
/*    2f1cc:	afb50010 */ 	sw	$s5,0x10($sp)
/*    2f1d0:	10400005 */ 	beqz	$v0,.L0002f1e8
/*    2f1d4:	00404825 */ 	or	$t1,$v0,$zero
/*    2f1d8:	86080002 */ 	lh	$t0,0x2($s0)
.L0002f1dc:
/*    2f1dc:	26100002 */ 	addiu	$s0,$s0,0x2
/*    2f1e0:	551effe6 */ 	bnel	$t0,$s8,.L0002f17c
/*    2f1e4:	8e2b0000 */ 	lw	$t3,0x0($s1)
.L0002f1e8:
/*    2f1e8:	11200032 */ 	beqz	$t1,.L0002f2b4
/*    2f1ec:	27b7006c */ 	addiu	$s7,$sp,0x6c
/*    2f1f0:	27b00134 */ 	addiu	$s0,$sp,0x134
/*    2f1f4:	02002825 */ 	or	$a1,$s0,$zero
/*    2f1f8:	8fa4034c */ 	lw	$a0,0x34c($sp)
/*    2f1fc:	24060100 */ 	addiu	$a2,$zero,0x100
/*    2f200:	0fc197e0 */ 	jal	roomGetProps
/*    2f204:	afa9012c */ 	sw	$t1,0x12c($sp)
/*    2f208:	87ab0134 */ 	lh	$t3,0x134($sp)
/*    2f20c:	8fa9012c */ 	lw	$t1,0x12c($sp)
/*    2f210:	02008825 */ 	or	$s1,$s0,$zero
/*    2f214:	05600027 */ 	bltz	$t3,.L0002f2b4
/*    2f218:	27ac0134 */ 	addiu	$t4,$sp,0x134
/*    2f21c:	3c14800a */ 	lui	$s4,%hi(g_Vars)
/*    2f220:	26949fc0 */ 	addiu	$s4,$s4,%lo(g_Vars)
/*    2f224:	85820000 */ 	lh	$v0,0x0($t4)
/*    2f228:	27be033c */ 	addiu	$s8,$sp,0x33c
/*    2f22c:	24130048 */ 	addiu	$s3,$zero,0x48
.L0002f230:
/*    2f230:	00530019 */ 	multu	$v0,$s3
/*    2f234:	8e8e0338 */ 	lw	$t6,0x338($s4)
/*    2f238:	8fa50350 */ 	lw	$a1,0x350($sp)
/*    2f23c:	afa9012c */ 	sw	$t1,0x12c($sp)
/*    2f240:	00006812 */ 	mflo	$t5
/*    2f244:	01ae8021 */ 	addu	$s0,$t5,$t6
/*    2f248:	0fc19553 */ 	jal	propIsOfCdType
/*    2f24c:	02002025 */ 	or	$a0,$s0,$zero
/*    2f250:	10400014 */ 	beqz	$v0,.L0002f2a4
/*    2f254:	8fa9012c */ 	lw	$t1,0x12c($sp)
/*    2f258:	02002025 */ 	or	$a0,$s0,$zero
/*    2f25c:	03c02825 */ 	or	$a1,$s8,$zero
/*    2f260:	27a60338 */ 	addiu	$a2,$sp,0x338
/*    2f264:	0fc198a4 */ 	jal	propUpdateGeometry
/*    2f268:	afa9012c */ 	sw	$t1,0x12c($sp)
/*    2f26c:	1040000d */ 	beqz	$v0,.L0002f2a4
/*    2f270:	8fa9012c */ 	lw	$t1,0x12c($sp)
/*    2f274:	240f0004 */ 	addiu	$t7,$zero,0x4
/*    2f278:	afaf0018 */ 	sw	$t7,0x18($sp)
/*    2f27c:	8fa4033c */ 	lw	$a0,0x33c($sp)
/*    2f280:	8fa50338 */ 	lw	$a1,0x338($sp)
/*    2f284:	02c03025 */ 	or	$a2,$s6,$zero
/*    2f288:	02403825 */ 	or	$a3,$s2,$zero
/*    2f28c:	afb50010 */ 	sw	$s5,0x10($sp)
/*    2f290:	afb70014 */ 	sw	$s7,0x14($sp)
/*    2f294:	0c00bb4c */ 	jal	func0002ed30
/*    2f298:	afb0001c */ 	sw	$s0,0x1c($sp)
/*    2f29c:	10400005 */ 	beqz	$v0,.L0002f2b4
/*    2f2a0:	00404825 */ 	or	$t1,$v0,$zero
.L0002f2a4:
/*    2f2a4:	86220002 */ 	lh	$v0,0x2($s1)
/*    2f2a8:	26310002 */ 	addiu	$s1,$s1,0x2
/*    2f2ac:	0441ffe0 */ 	bgez	$v0,.L0002f230
/*    2f2b0:	00000000 */ 	nop
.L0002f2b4:
/*    2f2b4:	8fbf004c */ 	lw	$ra,0x4c($sp)
/*    2f2b8:	8fb00028 */ 	lw	$s0,0x28($sp)
/*    2f2bc:	8fb1002c */ 	lw	$s1,0x2c($sp)
/*    2f2c0:	8fb20030 */ 	lw	$s2,0x30($sp)
/*    2f2c4:	8fb30034 */ 	lw	$s3,0x34($sp)
/*    2f2c8:	8fb40038 */ 	lw	$s4,0x38($sp)
/*    2f2cc:	8fb5003c */ 	lw	$s5,0x3c($sp)
/*    2f2d0:	8fb60040 */ 	lw	$s6,0x40($sp)
/*    2f2d4:	8fb70044 */ 	lw	$s7,0x44($sp)
/*    2f2d8:	8fbe0048 */ 	lw	$s8,0x48($sp)
/*    2f2dc:	27bd0348 */ 	addiu	$sp,$sp,0x348
/*    2f2e0:	03e00008 */ 	jr	$ra
/*    2f2e4:	01201025 */ 	or	$v0,$t1,$zero
);

#if VERSION < VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func000306f0nb
/*    306f0:	27bdff78 */ 	addiu	$sp,$sp,-136
/*    306f4:	afb1000c */ 	sw	$s1,0xc($sp)
/*    306f8:	afb00008 */ 	sw	$s0,0x8($sp)
/*    306fc:	94ce0002 */ 	lhu	$t6,0x2($a2)
/*    30700:	00a08025 */ 	or	$s0,$a1,$zero
/*    30704:	00808825 */ 	or	$s1,$a0,$zero
/*    30708:	31cf0005 */ 	andi	$t7,$t6,0x5
/*    3070c:	51e00072 */ 	beqzl	$t7,.NB000308d8
/*    30710:	02201025 */ 	or	$v0,$s1,$zero
/*    30714:	90c20001 */ 	lbu	$v0,0x1($a2)
/*    30718:	27a40020 */ 	addiu	$a0,$sp,0x20
/*    3071c:	00c02825 */ 	or	$a1,$a2,$zero
/*    30720:	28410011 */ 	slti	$at,$v0,0x11
/*    30724:	14200002 */ 	bnez	$at,.NB00030730
/*    30728:	3c07800a */ 	lui	$a3,0x800a
/*    3072c:	24020010 */ 	addiu	$v0,$zero,0x10
.NB00030730:
/*    30730:	18400044 */ 	blez	$v0,.NB00030844
/*    30734:	00001825 */ 	or	$v1,$zero,$zero
/*    30738:	8ce7e944 */ 	lw	$a3,-0x16bc($a3)
/*    3073c:	24630001 */ 	addiu	$v1,$v1,0x1
/*    30740:	10620022 */ 	beq	$v1,$v0,.NB000307cc
/*    30744:	84b8000e */ 	lh	$t8,0xe($a1)
.NB00030748:
/*    30748:	44989000 */ 	mtc1	$t8,$f18
/*    3074c:	c4f00038 */ 	lwc1	$f16,0x38($a3)
/*    30750:	24630001 */ 	addiu	$v1,$v1,0x1
/*    30754:	468094a0 */ 	cvt.s.w	$f18,$f18
/*    30758:	24840006 */ 	addiu	$a0,$a0,0x6
/*    3075c:	24a50006 */ 	addiu	$a1,$a1,0x6
/*    30760:	46109401 */ 	sub.s	$f16,$f18,$f16
/*    30764:	4600840d */ 	trunc.w.s	$f16,$f16
/*    30768:	44088000 */ 	mfc1	$t0,$f16
/*    3076c:	00000000 */ 	sll	$zero,$zero,0x0
/*    30770:	a488fffa */ 	sh	$t0,-0x6($a0)
/*    30774:	84a9000a */ 	lh	$t1,0xa($a1)
/*    30778:	c4f0003c */ 	lwc1	$f16,0x3c($a3)
/*    3077c:	44899000 */ 	mtc1	$t1,$f18
/*    30780:	00000000 */ 	sll	$zero,$zero,0x0
/*    30784:	468094a0 */ 	cvt.s.w	$f18,$f18
/*    30788:	46109401 */ 	sub.s	$f16,$f18,$f16
/*    3078c:	4600840d */ 	trunc.w.s	$f16,$f16
/*    30790:	440b8000 */ 	mfc1	$t3,$f16
/*    30794:	00000000 */ 	sll	$zero,$zero,0x0
/*    30798:	a48bfffc */ 	sh	$t3,-0x4($a0)
/*    3079c:	84ac000c */ 	lh	$t4,0xc($a1)
/*    307a0:	c4f00040 */ 	lwc1	$f16,0x40($a3)
/*    307a4:	448c9000 */ 	mtc1	$t4,$f18
/*    307a8:	00000000 */ 	sll	$zero,$zero,0x0
/*    307ac:	468094a0 */ 	cvt.s.w	$f18,$f18
/*    307b0:	46109401 */ 	sub.s	$f16,$f18,$f16
/*    307b4:	4600840d */ 	trunc.w.s	$f16,$f16
/*    307b8:	440e8000 */ 	mfc1	$t6,$f16
/*    307bc:	00000000 */ 	sll	$zero,$zero,0x0
/*    307c0:	a48efffe */ 	sh	$t6,-0x2($a0)
/*    307c4:	1462ffe0 */ 	bne	$v1,$v0,.NB00030748
/*    307c8:	84b8000e */ 	lh	$t8,0xe($a1)
.NB000307cc:
/*    307cc:	44989000 */ 	mtc1	$t8,$f18
/*    307d0:	c4f00038 */ 	lwc1	$f16,0x38($a3)
/*    307d4:	24840006 */ 	addiu	$a0,$a0,0x6
/*    307d8:	468094a0 */ 	cvt.s.w	$f18,$f18
/*    307dc:	24a50006 */ 	addiu	$a1,$a1,0x6
/*    307e0:	46109401 */ 	sub.s	$f16,$f18,$f16
/*    307e4:	4600840d */ 	trunc.w.s	$f16,$f16
/*    307e8:	44088000 */ 	mfc1	$t0,$f16
/*    307ec:	00000000 */ 	sll	$zero,$zero,0x0
/*    307f0:	a488fffa */ 	sh	$t0,-0x6($a0)
/*    307f4:	84a9000a */ 	lh	$t1,0xa($a1)
/*    307f8:	c4f0003c */ 	lwc1	$f16,0x3c($a3)
/*    307fc:	44899000 */ 	mtc1	$t1,$f18
/*    30800:	00000000 */ 	sll	$zero,$zero,0x0
/*    30804:	468094a0 */ 	cvt.s.w	$f18,$f18
/*    30808:	46109401 */ 	sub.s	$f16,$f18,$f16
/*    3080c:	4600840d */ 	trunc.w.s	$f16,$f16
/*    30810:	440b8000 */ 	mfc1	$t3,$f16
/*    30814:	00000000 */ 	sll	$zero,$zero,0x0
/*    30818:	a48bfffc */ 	sh	$t3,-0x4($a0)
/*    3081c:	84ac000c */ 	lh	$t4,0xc($a1)
/*    30820:	c4f00040 */ 	lwc1	$f16,0x40($a3)
/*    30824:	448c9000 */ 	mtc1	$t4,$f18
/*    30828:	00000000 */ 	sll	$zero,$zero,0x0
/*    3082c:	468094a0 */ 	cvt.s.w	$f18,$f18
/*    30830:	46109401 */ 	sub.s	$f16,$f18,$f16
/*    30834:	4600840d */ 	trunc.w.s	$f16,$f16
/*    30838:	440e8000 */ 	mfc1	$t6,$f16
/*    3083c:	00000000 */ 	sll	$zero,$zero,0x0
/*    30840:	a48efffe */ 	sh	$t6,-0x2($a0)
.NB00030844:
/*    30844:	28410003 */ 	slti	$at,$v0,0x3
/*    30848:	14200022 */ 	bnez	$at,.NB000308d4
/*    3084c:	24030002 */ 	addiu	$v1,$zero,0x2
/*    30850:	24070006 */ 	addiu	$a3,$zero,0x6
/*    30854:	27a60020 */ 	addiu	$a2,$sp,0x20
.NB00030858:
/*    30858:	8e050000 */ 	lw	$a1,0x0($s0)
/*    3085c:	87af0020 */ 	lh	$t7,0x20($sp)
/*    30860:	58a00019 */ 	blezl	$a1,.NB000308c8
/*    30864:	24630001 */ 	addiu	$v1,$v1,0x1
/*    30868:	00670019 */ 	multu	$v1,$a3
/*    3086c:	a62f0000 */ 	sh	$t7,0x0($s1)
/*    30870:	87b80022 */ 	lh	$t8,0x22($sp)
/*    30874:	26310014 */ 	addiu	$s1,$s1,0x14
/*    30878:	a638ffee */ 	sh	$t8,-0x12($s1)
/*    3087c:	87b90024 */ 	lh	$t9,0x24($sp)
/*    30880:	a639fff0 */ 	sh	$t9,-0x10($s1)
/*    30884:	00004012 */ 	mflo	$t0
/*    30888:	00c82021 */ 	addu	$a0,$a2,$t0
/*    3088c:	8489fffa */ 	lh	$t1,-0x6($a0)
/*    30890:	a629fff2 */ 	sh	$t1,-0xe($s1)
/*    30894:	848afffc */ 	lh	$t2,-0x4($a0)
/*    30898:	a62afff4 */ 	sh	$t2,-0xc($s1)
/*    3089c:	848bfffe */ 	lh	$t3,-0x2($a0)
/*    308a0:	a62bfff6 */ 	sh	$t3,-0xa($s1)
/*    308a4:	848c0000 */ 	lh	$t4,0x0($a0)
/*    308a8:	a62cfff8 */ 	sh	$t4,-0x8($s1)
/*    308ac:	848d0002 */ 	lh	$t5,0x2($a0)
/*    308b0:	a62dfffa */ 	sh	$t5,-0x6($s1)
/*    308b4:	848e0004 */ 	lh	$t6,0x4($a0)
/*    308b8:	a220fffe */ 	sb	$zero,-0x2($s1)
/*    308bc:	a62efffc */ 	sh	$t6,-0x4($s1)
/*    308c0:	8e050000 */ 	lw	$a1,0x0($s0)
/*    308c4:	24630001 */ 	addiu	$v1,$v1,0x1
.NB000308c8:
/*    308c8:	24afffff */ 	addiu	$t7,$a1,-1
/*    308cc:	1462ffe2 */ 	bne	$v1,$v0,.NB00030858
/*    308d0:	ae0f0000 */ 	sw	$t7,0x0($s0)
.NB000308d4:
/*    308d4:	02201025 */ 	or	$v0,$s1,$zero
.NB000308d8:
/*    308d8:	8fb1000c */ 	lw	$s1,0xc($sp)
/*    308dc:	8fb00008 */ 	lw	$s0,0x8($sp)
/*    308e0:	03e00008 */ 	jr	$ra
/*    308e4:	27bd0088 */ 	addiu	$sp,$sp,0x88
);
#endif

#if VERSION < VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func000308e8nb
/*    308e8:	27bdff78 */ 	addiu	$sp,$sp,-136
/*    308ec:	afb1000c */ 	sw	$s1,0xc($sp)
/*    308f0:	afb00008 */ 	sw	$s0,0x8($sp)
/*    308f4:	94ce0002 */ 	lhu	$t6,0x2($a2)
/*    308f8:	00a08025 */ 	or	$s0,$a1,$zero
/*    308fc:	00808825 */ 	or	$s1,$a0,$zero
/*    30900:	31cf0005 */ 	andi	$t7,$t6,0x5
/*    30904:	51e00048 */ 	beqzl	$t7,.NB00030a28
/*    30908:	02201025 */ 	or	$v0,$s1,$zero
/*    3090c:	90c20001 */ 	lbu	$v0,0x1($a2)
/*    30910:	27a40020 */ 	addiu	$a0,$sp,0x20
/*    30914:	00c02825 */ 	or	$a1,$a2,$zero
/*    30918:	28410011 */ 	slti	$at,$v0,0x11
/*    3091c:	14200002 */ 	bnez	$at,.NB00030928
/*    30920:	3c07800a */ 	lui	$a3,0x800a
/*    30924:	24020010 */ 	addiu	$v0,$zero,0x10
.NB00030928:
/*    30928:	1840001a */ 	blez	$v0,.NB00030994
/*    3092c:	00001825 */ 	or	$v1,$zero,$zero
/*    30930:	8ce7e944 */ 	lw	$a3,-0x16bc($a3)
.NB00030934:
/*    30934:	c4a40010 */ 	lwc1	$f4,0x10($a1)
/*    30938:	c4e60038 */ 	lwc1	$f6,0x38($a3)
/*    3093c:	24630001 */ 	addiu	$v1,$v1,0x1
/*    30940:	24840006 */ 	addiu	$a0,$a0,0x6
/*    30944:	46062201 */ 	sub.s	$f8,$f4,$f6
/*    30948:	24a5000c */ 	addiu	$a1,$a1,0xc
/*    3094c:	4600428d */ 	trunc.w.s	$f10,$f8
/*    30950:	44195000 */ 	mfc1	$t9,$f10
/*    30954:	00000000 */ 	sll	$zero,$zero,0x0
/*    30958:	a499fffa */ 	sh	$t9,-0x6($a0)
/*    3095c:	c4f2003c */ 	lwc1	$f18,0x3c($a3)
/*    30960:	c4b00008 */ 	lwc1	$f16,0x8($a1)
/*    30964:	46128101 */ 	sub.s	$f4,$f16,$f18
/*    30968:	4600218d */ 	trunc.w.s	$f6,$f4
/*    3096c:	44093000 */ 	mfc1	$t1,$f6
/*    30970:	00000000 */ 	sll	$zero,$zero,0x0
/*    30974:	a489fffc */ 	sh	$t1,-0x4($a0)
/*    30978:	c4ea0040 */ 	lwc1	$f10,0x40($a3)
/*    3097c:	c4a8000c */ 	lwc1	$f8,0xc($a1)
/*    30980:	460a4401 */ 	sub.s	$f16,$f8,$f10
/*    30984:	4600848d */ 	trunc.w.s	$f18,$f16
/*    30988:	440b9000 */ 	mfc1	$t3,$f18
/*    3098c:	1462ffe9 */ 	bne	$v1,$v0,.NB00030934
/*    30990:	a48bfffe */ 	sh	$t3,-0x2($a0)
.NB00030994:
/*    30994:	28410003 */ 	slti	$at,$v0,0x3
/*    30998:	14200022 */ 	bnez	$at,.NB00030a24
/*    3099c:	24030002 */ 	addiu	$v1,$zero,0x2
/*    309a0:	24070006 */ 	addiu	$a3,$zero,0x6
/*    309a4:	27a60020 */ 	addiu	$a2,$sp,0x20
.NB000309a8:
/*    309a8:	8e050000 */ 	lw	$a1,0x0($s0)
/*    309ac:	87ac0020 */ 	lh	$t4,0x20($sp)
/*    309b0:	58a00019 */ 	blezl	$a1,.NB00030a18
/*    309b4:	24630001 */ 	addiu	$v1,$v1,0x1
/*    309b8:	00670019 */ 	multu	$v1,$a3
/*    309bc:	a62c0000 */ 	sh	$t4,0x0($s1)
/*    309c0:	87ad0022 */ 	lh	$t5,0x22($sp)
/*    309c4:	26310014 */ 	addiu	$s1,$s1,0x14
/*    309c8:	a62dffee */ 	sh	$t5,-0x12($s1)
/*    309cc:	87ae0024 */ 	lh	$t6,0x24($sp)
/*    309d0:	a62efff0 */ 	sh	$t6,-0x10($s1)
/*    309d4:	00007812 */ 	mflo	$t7
/*    309d8:	00cf2021 */ 	addu	$a0,$a2,$t7
/*    309dc:	8498fffa */ 	lh	$t8,-0x6($a0)
/*    309e0:	a638fff2 */ 	sh	$t8,-0xe($s1)
/*    309e4:	8499fffc */ 	lh	$t9,-0x4($a0)
/*    309e8:	a639fff4 */ 	sh	$t9,-0xc($s1)
/*    309ec:	8488fffe */ 	lh	$t0,-0x2($a0)
/*    309f0:	a628fff6 */ 	sh	$t0,-0xa($s1)
/*    309f4:	84890000 */ 	lh	$t1,0x0($a0)
/*    309f8:	a629fff8 */ 	sh	$t1,-0x8($s1)
/*    309fc:	848a0002 */ 	lh	$t2,0x2($a0)
/*    30a00:	a62afffa */ 	sh	$t2,-0x6($s1)
/*    30a04:	848b0004 */ 	lh	$t3,0x4($a0)
/*    30a08:	a220fffe */ 	sb	$zero,-0x2($s1)
/*    30a0c:	a62bfffc */ 	sh	$t3,-0x4($s1)
/*    30a10:	8e050000 */ 	lw	$a1,0x0($s0)
/*    30a14:	24630001 */ 	addiu	$v1,$v1,0x1
.NB00030a18:
/*    30a18:	24acffff */ 	addiu	$t4,$a1,-1
/*    30a1c:	1462ffe2 */ 	bne	$v1,$v0,.NB000309a8
/*    30a20:	ae0c0000 */ 	sw	$t4,0x0($s0)
.NB00030a24:
/*    30a24:	02201025 */ 	or	$v0,$s1,$zero
.NB00030a28:
/*    30a28:	8fb1000c */ 	lw	$s1,0xc($sp)
/*    30a2c:	8fb00008 */ 	lw	$s0,0x8($sp)
/*    30a30:	03e00008 */ 	jr	$ra
/*    30a34:	27bd0088 */ 	addiu	$sp,$sp,0x88
);
#endif

GLOBAL_ASM(
glabel func0002f2e8
/*    2f2e8:	afa50004 */ 	sw	$a1,0x4($sp)
/*    2f2ec:	afa60008 */ 	sw	$a2,0x8($sp)
/*    2f2f0:	afa7000c */ 	sw	$a3,0xc($sp)
/*    2f2f4:	03e00008 */ 	jr	$ra
/*    2f2f8:	00801025 */ 	or	$v0,$a0,$zero
);

GLOBAL_ASM(
glabel func0002f2fc
/*    2f2fc:	afa40000 */ 	sw	$a0,0x0($sp)
/*    2f300:	03e00008 */ 	jr	$ra
/*    2f304:	afa50004 */ 	sw	$a1,0x4($sp)
);

bool func0002f308(struct coord *viewpos, s16 *rooms, struct coord *targetpos, f32 distance, s32 arg4, u16 arg5)
{
	struct coord diff;
	f32 x;
	f32 z;
	struct coord vector;

	if (func0002db98(viewpos, rooms, targetpos, arg4, arg5)) {
		return true;
	}

	vector.x = targetpos->x - viewpos->x;
	vector.y = 0;
	vector.z = targetpos->z - viewpos->z;

	guNormalize(&vector.x, &vector.y, &vector.z);

	x = vector.f[0] * distance;
	z = vector.f[2] * distance;

	diff.x = targetpos->x - z;
	diff.y = targetpos->y;
	diff.z = targetpos->z + x;

	if (func0002db98(viewpos, rooms, &diff, arg4, arg5)) {
		return true;
	}

	diff.x = targetpos->x + z;
	diff.y = targetpos->y;
	diff.z = targetpos->z - x;

	if (func0002db98(viewpos, rooms, &diff, arg4, arg5)) {
		return true;
	}

	return false;
}

bool func0002f450(struct coord *viewpos, s16 *rooms, struct coord *targetpos, f32 distance, s32 arg4)
{
	return func0002f308(viewpos, rooms, targetpos, distance, arg4, 8);
}
