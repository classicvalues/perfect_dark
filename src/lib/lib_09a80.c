#include <ultra64.h>
#include "constants.h"
#include "game/game_0b3350.h"
#include "game/game_0b4950.h"
#include "game/game_0b69d0.h"
#include "game/file.h"
#include "game/game_176080.h"
#include "game/options.h"
#include "bss.h"
#include "lib/lib_09660.h"
#include "lib/memory.h"
#include "lib/lib_159b0.h"
#include "lib/lib_30ce0.h"
#include "lib/lib_4b170.h"
#include "data.h"
#include "types.h"

u32 var80092830;
u32 var80092834;
u32 var80092838;
u32 var8009283c;
u32 var80092840;
u32 var80092844;
u32 var80092848;
u32 var8009284c;
u32 var80092850;
u32 var80092854;
u32 var80092858;
u32 var8009285c;
u32 var80092860;
u32 var80092864;
u32 var80092868;
u32 var8009286c;
u32 var80092870;
u32 var80092874;

const u32 var700526d0[] = {0x01400140};
const u32 var700526d4[] = {0x02800000};
const u32 var700526d8[] = {0x00dc00dc};

#if PAL
const u32 var700526dc[] = {0x01f80000};
#else
const u32 var700526dc[] = {0x01b80000};
#endif

struct rend_vidat var8005d530 = {
	NULL,
	320, 220,         // x and y
	60,               // fovy
	1.4545454978943f, // aspect
	30,               // znear
	10000,            // zfar
	320, 220,         // bufx and bufy
	320, 220,         // viewx and viewy
	0, 0,             // viewleft and viewtop
	true,             // usezbuf
	0,
};

struct rend_vidat var8005d55c = {
	NULL,
	320, 220,         // x and y
	60,               // fovy
	1.4545454978943f, // aspect
	30,               // znear
	10000,            // zfar
	320, 220,         // bufx and bufy
	320, 220,         // viewx and viewy
	0, 0,             // viewleft and viewtop
	true,             // usezbuf
	0,
};

u32 var8005d588 = 0x00000000;
u32 var8005d58c = 0x00000000;
struct rend_vidat *var8005d590 = &var8005d530;
struct rend_vidat *g_ViData = &var8005d530;
u32 var8005d598 = 0x00000001;
u32 var8005d59c = 0x00000000;
u32 var8005d5a0 = 0x00000000;
u32 var8005d5a4 = 0x00000000;
u32 var8005d5a8 = 0x00000000;
u32 var8005d5ac = 0x00000000;


void func00009a80(void)
{
	// empty
}

void func00009a88(void)
{
	// empty
}

void func00009a90(void)
{
	// empty
}

void func00009a98(void)
{
	// empty
}

void func00009aa0(u32 value)
{
	// empty
}

Gfx *debugRenderSomething(Gfx *gdl)
{
	return gdl;
}

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func00009ab0
/*     99a0:	2405002c */ 	li	$a1,0x2c
/*     99a4:	300f00ff */ 	andi	$t7,$zero,0xff
/*     99a8:	01e50019 */ 	multu	$t7,$a1
/*     99ac:	3c028009 */ 	lui	$v0,0x8009
/*     99b0:	3c038009 */ 	lui	$v1,0x8009
/*     99b4:	3c048006 */ 	lui	$a0,0x8006
/*     99b8:	2484d1d0 */ 	addiu	$a0,$a0,-11824
/*     99bc:	24632dc7 */ 	addiu	$v1,$v1,0x2dc7
/*     99c0:	24422dc6 */ 	addiu	$v0,$v0,0x2dc6
/*     99c4:	240e0001 */ 	li	$t6,0x1
/*     99c8:	a0400000 */ 	sb	$zero,0x0($v0)
/*     99cc:	a06e0000 */ 	sb	$t6,0x0($v1)
/*     99d0:	0000c012 */ 	mflo	$t8
/*     99d4:	0098c821 */ 	addu	$t9,$a0,$t8
/*     99d8:	3c018006 */ 	lui	$at,0x8006
/*     99dc:	ac39d230 */ 	sw	$t9,-0x2dd0($at)
/*     99e0:	90680000 */ 	lbu	$t0,0x0($v1)
/*     99e4:	3c0b8009 */ 	lui	$t3,0x8009
/*     99e8:	916b1040 */ 	lbu	$t3,0x1040($t3)
/*     99ec:	01050019 */ 	multu	$t0,$a1
/*     99f0:	3c018006 */ 	lui	$at,0x8006
/*     99f4:	240200dc */ 	li	$v0,0xdc
/*     99f8:	00004812 */ 	mflo	$t1
/*     99fc:	00895021 */ 	addu	$t2,$a0,$t1
/*     9a00:	ac2ad234 */ 	sw	$t2,-0x2dcc($at)
/*     9a04:	24010001 */ 	li	$at,0x1
/*     9a08:	1561000c */ 	bne	$t3,$at,.PF00009a3c
/*     9a0c:	00000000 */ 	nop
/*     9a10:	a4820006 */ 	sh	$v0,0x6($a0)
/*     9a14:	a482001a */ 	sh	$v0,0x1a($a0)
/*     9a18:	a482001e */ 	sh	$v0,0x1e($a0)
/*     9a1c:	a4820032 */ 	sh	$v0,0x32($a0)
/*     9a20:	a4820046 */ 	sh	$v0,0x46($a0)
/*     9a24:	a482004a */ 	sh	$v0,0x4a($a0)
/*     9a28:	3c018006 */ 	lui	$at,0x8006
/*     9a2c:	ac20d228 */ 	sw	$zero,-0x2dd8($at)
/*     9a30:	3c018006 */ 	lui	$at,0x8006
/*     9a34:	03e00008 */ 	jr	$ra
/*     9a38:	ac20d22c */ 	sw	$zero,-0x2dd4($at)
.PF00009a3c:
/*     9a3c:	3c018006 */ 	lui	$at,0x8006
/*     9a40:	ac20d228 */ 	sw	$zero,-0x2dd8($at)
/*     9a44:	3c018006 */ 	lui	$at,0x8006
/*     9a48:	240c000c */ 	li	$t4,0xc
/*     9a4c:	ac2cd22c */ 	sw	$t4,-0x2dd4($at)
/*     9a50:	03e00008 */ 	jr	$ra
/*     9a54:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel func00009ab0
/*     9ab0:	2405002c */ 	addiu	$a1,$zero,0x2c
/*     9ab4:	300f00ff */ 	andi	$t7,$zero,0xff
/*     9ab8:	01e50019 */ 	multu	$t7,$a1
/*     9abc:	3c028009 */ 	lui	$v0,%hi(var80092874+0x2)
/*     9ac0:	3c038009 */ 	lui	$v1,%hi(var80092874+0x3)
/*     9ac4:	3c048006 */ 	lui	$a0,%hi(var8005d530)
/*     9ac8:	2484d530 */ 	addiu	$a0,$a0,%lo(var8005d530)
/*     9acc:	24632877 */ 	addiu	$v1,$v1,%lo(var80092874+0x3)
/*     9ad0:	24422876 */ 	addiu	$v0,$v0,%lo(var80092874+0x2)
/*     9ad4:	240e0001 */ 	addiu	$t6,$zero,0x1
/*     9ad8:	a0400000 */ 	sb	$zero,0x0($v0)
/*     9adc:	a06e0000 */ 	sb	$t6,0x0($v1)
/*     9ae0:	0000c012 */ 	mflo	$t8
/*     9ae4:	0098c821 */ 	addu	$t9,$a0,$t8
/*     9ae8:	3c018006 */ 	lui	$at,%hi(var8005d590)
/*     9aec:	ac39d590 */ 	sw	$t9,%lo(var8005d590)($at)
/*     9af0:	90680000 */ 	lbu	$t0,0x0($v1)
/*     9af4:	3c018006 */ 	lui	$at,%hi(g_ViData)
/*     9af8:	3c0b8009 */ 	lui	$t3,%hi(g_Is4Mb)
/*     9afc:	01050019 */ 	multu	$t0,$a1
/*     9b00:	916b0af0 */ 	lbu	$t3,%lo(g_Is4Mb)($t3)
/*     9b04:	240200dc */ 	addiu	$v0,$zero,0xdc
/*     9b08:	00004812 */ 	mflo	$t1
/*     9b0c:	00895021 */ 	addu	$t2,$a0,$t1
/*     9b10:	ac2ad594 */ 	sw	$t2,%lo(g_ViData)($at)
/*     9b14:	3c018006 */ 	lui	$at,%hi(var8005d588)
/*     9b18:	ac20d588 */ 	sw	$zero,%lo(var8005d588)($at)
/*     9b1c:	3c018006 */ 	lui	$at,%hi(var8005d58c)
/*     9b20:	ac20d58c */ 	sw	$zero,%lo(var8005d58c)($at)
/*     9b24:	24010001 */ 	addiu	$at,$zero,0x1
/*     9b28:	15610007 */ 	bne	$t3,$at,.L00009b48
/*     9b2c:	00000000 */ 	nop
/*     9b30:	a4820006 */ 	sh	$v0,0x6($a0)
/*     9b34:	a482001a */ 	sh	$v0,0x1a($a0)
/*     9b38:	a482001e */ 	sh	$v0,0x1e($a0)
/*     9b3c:	a4820032 */ 	sh	$v0,0x32($a0)
/*     9b40:	a4820046 */ 	sh	$v0,0x46($a0)
/*     9b44:	a482004a */ 	sh	$v0,0x4a($a0)
.L00009b48:
/*     9b48:	03e00008 */ 	jr	$ra
/*     9b4c:	00000000 */ 	nop
);
#endif

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func00009b50
/*     9b50:	3c03800a */ 	lui	$v1,%hi(var8009cac0)
/*     9b54:	3c058006 */ 	lui	$a1,%hi(var8005d530)
/*     9b58:	3c078006 */ 	lui	$a3,%hi(var8005d588)
/*     9b5c:	24e7d588 */ 	addiu	$a3,$a3,%lo(var8005d588)
/*     9b60:	24a5d530 */ 	addiu	$a1,$a1,%lo(var8005d530)
/*     9b64:	2463cac0 */ 	addiu	$v1,$v1,%lo(var8009cac0)
/*     9b68:	24060030 */ 	addiu	$a2,$zero,0x30
/*     9b6c:	24020240 */ 	addiu	$v0,$zero,0x240
.L00009b70:
/*     9b70:	24a5002c */ 	addiu	$a1,$a1,0x2c
/*     9b74:	24630004 */ 	addiu	$v1,$v1,0x4
/*     9b78:	ac64fffc */ 	sw	$a0,-0x4($v1)
/*     9b7c:	a4a2ffd8 */ 	sh	$v0,-0x28($a1)
/*     9b80:	a4a2ffec */ 	sh	$v0,-0x14($a1)
/*     9b84:	a4a2fff0 */ 	sh	$v0,-0x10($a1)
/*     9b88:	a4a6ffda */ 	sh	$a2,-0x26($a1)
/*     9b8c:	a4a6ffee */ 	sh	$a2,-0x12($a1)
/*     9b90:	14a7fff7 */ 	bne	$a1,$a3,.L00009b70
/*     9b94:	a4a6fff2 */ 	sh	$a2,-0xe($a1)
/*     9b98:	3c0e8009 */ 	lui	$t6,%hi(var80092874+0x2)
/*     9b9c:	91ce2876 */ 	lbu	$t6,%lo(var80092874+0x2)($t6)
/*     9ba0:	3c02800a */ 	lui	$v0,%hi(var8009cac0)
/*     9ba4:	2442cac0 */ 	addiu	$v0,$v0,%lo(var8009cac0)
/*     9ba8:	000e7880 */ 	sll	$t7,$t6,0x2
/*     9bac:	004fc021 */ 	addu	$t8,$v0,$t7
/*     9bb0:	3c088006 */ 	lui	$t0,%hi(var8005d590)
/*     9bb4:	8d08d590 */ 	lw	$t0,%lo(var8005d590)($t0)
/*     9bb8:	8f190000 */ 	lw	$t9,0x0($t8)
/*     9bbc:	3c098009 */ 	lui	$t1,%hi(var80092874+0x3)
/*     9bc0:	3c0d8006 */ 	lui	$t5,%hi(g_ViData)
/*     9bc4:	ad190028 */ 	sw	$t9,0x28($t0)
/*     9bc8:	91292877 */ 	lbu	$t1,%lo(var80092874+0x3)($t1)
/*     9bcc:	8dadd594 */ 	lw	$t5,%lo(g_ViData)($t5)
/*     9bd0:	240e0001 */ 	addiu	$t6,$zero,0x1
/*     9bd4:	00095080 */ 	sll	$t2,$t1,0x2
/*     9bd8:	004a5821 */ 	addu	$t3,$v0,$t2
/*     9bdc:	8d6c0000 */ 	lw	$t4,0x0($t3)
/*     9be0:	3c018006 */ 	lui	$at,%hi(var8005d59c)
/*     9be4:	adac0028 */ 	sw	$t4,0x28($t5)
/*     9be8:	ac2ed59c */ 	sw	$t6,%lo(var8005d59c)($at)
/*     9bec:	3c01800a */ 	lui	$at,%hi(g_Vars+0x4e0)
/*     9bf0:	03e00008 */ 	jr	$ra
/*     9bf4:	a020a4a0 */ 	sb	$zero,%lo(g_Vars+0x4e0)($at)
);
#else
GLOBAL_ASM(
glabel func00009b50
/*     9cf0:	3c03800a */ 	lui	$v1,0x800a
/*     9cf4:	3c058006 */ 	lui	$a1,0x8006
/*     9cf8:	3c088006 */ 	lui	$t0,0x8006
/*     9cfc:	2508ed28 */ 	addiu	$t0,$t0,-4824
/*     9d00:	24a5ecd0 */ 	addiu	$a1,$a1,-4912
/*     9d04:	24631200 */ 	addiu	$v1,$v1,0x1200
/*     9d08:	24070030 */ 	addiu	$a3,$zero,0x30
/*     9d0c:	240601e0 */ 	addiu	$a2,$zero,0x1e0
/*     9d10:	24020240 */ 	addiu	$v0,$zero,0x240
.NB00009d14:
/*     9d14:	24a5002c */ 	addiu	$a1,$a1,0x2c
/*     9d18:	24630004 */ 	addiu	$v1,$v1,0x4
/*     9d1c:	ac64fffc */ 	sw	$a0,-0x4($v1)
/*     9d20:	a4a2ffd8 */ 	sh	$v0,-0x28($a1)
/*     9d24:	a4a2ffec */ 	sh	$v0,-0x14($a1)
/*     9d28:	a4a6fff0 */ 	sh	$a2,-0x10($a1)
/*     9d2c:	a4a7ffda */ 	sh	$a3,-0x26($a1)
/*     9d30:	a4a7ffee */ 	sh	$a3,-0x12($a1)
/*     9d34:	14a8fff7 */ 	bne	$a1,$t0,.NB00009d14
/*     9d38:	a4a7fff2 */ 	sh	$a3,-0xe($a1)
/*     9d3c:	3c0e8009 */ 	lui	$t6,0x8009
/*     9d40:	91ce4e66 */ 	lbu	$t6,0x4e66($t6)
/*     9d44:	3c02800a */ 	lui	$v0,0x800a
/*     9d48:	24421200 */ 	addiu	$v0,$v0,0x1200
/*     9d4c:	000e7880 */ 	sll	$t7,$t6,0x2
/*     9d50:	004fc021 */ 	addu	$t8,$v0,$t7
/*     9d54:	3c098006 */ 	lui	$t1,0x8006
/*     9d58:	8d29ed30 */ 	lw	$t1,-0x12d0($t1)
/*     9d5c:	8f190000 */ 	lw	$t9,0x0($t8)
/*     9d60:	3c0a8009 */ 	lui	$t2,0x8009
/*     9d64:	3c0e8006 */ 	lui	$t6,0x8006
/*     9d68:	ad390028 */ 	sw	$t9,0x28($t1)
/*     9d6c:	914a4e67 */ 	lbu	$t2,0x4e67($t2)
/*     9d70:	8dceed34 */ 	lw	$t6,-0x12cc($t6)
/*     9d74:	240f0001 */ 	addiu	$t7,$zero,0x1
/*     9d78:	000a5880 */ 	sll	$t3,$t2,0x2
/*     9d7c:	004b6021 */ 	addu	$t4,$v0,$t3
/*     9d80:	8d8d0000 */ 	lw	$t5,0x0($t4)
/*     9d84:	3c018006 */ 	lui	$at,0x8006
/*     9d88:	adcd0028 */ 	sw	$t5,0x28($t6)
/*     9d8c:	ac2fed3c */ 	sw	$t7,-0x12c4($at)
/*     9d90:	3c01800a */ 	lui	$at,0x800a
/*     9d94:	03e00008 */ 	jr	$ra
/*     9d98:	a020eba0 */ 	sb	$zero,-0x1460($at)
);
#endif

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func00009bf8
/*     9b00:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*     9b04:	3c028006 */ 	lui	$v0,0x8006
/*     9b08:	3c058006 */ 	lui	$a1,0x8006
/*     9b0c:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     9b10:	24a5d228 */ 	addiu	$a1,$a1,-11736
/*     9b14:	2442d1d0 */ 	addiu	$v0,$v0,-11824
/*     9b18:	240400dc */ 	li	$a0,0xdc
/*     9b1c:	24030140 */ 	li	$v1,0x140
.PF00009b20:
/*     9b20:	2442002c */ 	addiu	$v0,$v0,0x2c
/*     9b24:	a443ffd8 */ 	sh	$v1,-0x28($v0)
/*     9b28:	a443ffec */ 	sh	$v1,-0x14($v0)
/*     9b2c:	a443fff0 */ 	sh	$v1,-0x10($v0)
/*     9b30:	a444ffda */ 	sh	$a0,-0x26($v0)
/*     9b34:	a444ffee */ 	sh	$a0,-0x12($v0)
/*     9b38:	1445fff9 */ 	bne	$v0,$a1,.PF00009b20
/*     9b3c:	a444fff2 */ 	sh	$a0,-0xe($v0)
/*     9b40:	3c01800a */ 	lui	$at,0x800a
/*     9b44:	0fc2f254 */ 	jal	viResetDefaultModeIf4Mb
/*     9b48:	a020a9f0 */ 	sb	$zero,-0x5610($at)
/*     9b4c:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     9b50:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*     9b54:	03e00008 */ 	jr	$ra
/*     9b58:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel func00009bf8
/*     9bf8:	3c038006 */ 	lui	$v1,%hi(var8005d530)
/*     9bfc:	3c058006 */ 	lui	$a1,%hi(var8005d588)
/*     9c00:	24a5d588 */ 	addiu	$a1,$a1,%lo(var8005d588)
/*     9c04:	2463d530 */ 	addiu	$v1,$v1,%lo(var8005d530)
/*     9c08:	240400dc */ 	addiu	$a0,$zero,0xdc
/*     9c0c:	24020140 */ 	addiu	$v0,$zero,0x140
.L00009c10:
/*     9c10:	2463002c */ 	addiu	$v1,$v1,0x2c
/*     9c14:	a462ffd8 */ 	sh	$v0,-0x28($v1)
/*     9c18:	a462ffec */ 	sh	$v0,-0x14($v1)
/*     9c1c:	a462fff0 */ 	sh	$v0,-0x10($v1)
/*     9c20:	a464ffda */ 	sh	$a0,-0x26($v1)
/*     9c24:	a464ffee */ 	sh	$a0,-0x12($v1)
/*     9c28:	1465fff9 */ 	bne	$v1,$a1,.L00009c10
/*     9c2c:	a464fff2 */ 	sh	$a0,-0xe($v1)
/*     9c30:	3c01800a */ 	lui	$at,%hi(g_Vars+0x4e0)
/*     9c34:	03e00008 */ 	jr	$ra
/*     9c38:	a020a4a0 */ 	sb	$zero,%lo(g_Vars+0x4e0)($at)
);
#endif

#if PAL
GLOBAL_ASM(
glabel func00009c3c
/*     9c3c:	3c05800a */ 	lui	$a1,%hi(g_Vars)
/*     9c40:	24a59fc0 */ 	addiu	$a1,$a1,%lo(g_Vars)
/*     9c44:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*     9c48:	2401005a */ 	addiu	$at,$zero,0x5a
/*     9c4c:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     9c50:	10810003 */ 	beq	$a0,$at,.L00009c60
/*     9c54:	a0a004e0 */ 	sb	$zero,0x4e0($a1)
/*     9c58:	2401004e */ 	addiu	$at,$zero,0x4e
/*     9c5c:	14810015 */ 	bne	$a0,$at,.L00009cb4
.L00009c60:
/*     9c60:	3c0e8009 */ 	lui	$t6,%hi(g_Is4Mb)
/*     9c64:	91ce0af0 */ 	lbu	$t6,%lo(g_Is4Mb)($t6)
/*     9c68:	24010001 */ 	addiu	$at,$zero,0x1
/*     9c6c:	15c10006 */ 	bne	$t6,$at,.L00009c88
/*     9c70:	00000000 */ 	nop
/*     9c74:	0c002aac */ 	jal	func0000aab0
/*     9c78:	24040002 */ 	addiu	$a0,$zero,0x2
/*     9c7c:	3c060008 */ 	lui	$a2,0x8
/*     9c80:	10000060 */ 	b	.L00009e04
/*     9c84:	34c69800 */ 	ori	$a2,$a2,0x9800
.L00009c88:
/*     9c88:	0c002aac */ 	jal	func0000aab0
/*     9c8c:	24040002 */ 	addiu	$a0,$zero,0x2
/*     9c90:	3c0f7005 */ 	lui	$t7,%hi(var700526dc)
/*     9c94:	3c187005 */ 	lui	$t8,%hi(var700526d4)
/*     9c98:	871826d4 */ 	lh	$t8,%lo(var700526d4)($t8)
/*     9c9c:	85ef26dc */ 	lh	$t7,%lo(var700526dc)($t7)
/*     9ca0:	01f80019 */ 	multu	$t7,$t8
/*     9ca4:	00003012 */ 	mflo	$a2
/*     9ca8:	0006c840 */ 	sll	$t9,$a2,0x1
/*     9cac:	10000055 */ 	b	.L00009e04
/*     9cb0:	03203025 */ 	or	$a2,$t9,$zero
.L00009cb4:
/*     9cb4:	0c002aac */ 	jal	func0000aab0
/*     9cb8:	24040001 */ 	addiu	$a0,$zero,0x1
/*     9cbc:	3c028009 */ 	lui	$v0,%hi(g_Is4Mb)
/*     9cc0:	90420af0 */ 	lbu	$v0,%lo(g_Is4Mb)($v0)
/*     9cc4:	3c05800a */ 	lui	$a1,%hi(g_Vars)
/*     9cc8:	24010001 */ 	addiu	$at,$zero,0x1
/*     9ccc:	14410004 */ 	bne	$v0,$at,.L00009ce0
/*     9cd0:	24a59fc0 */ 	addiu	$a1,$a1,%lo(g_Vars)
/*     9cd4:	3c060002 */ 	lui	$a2,0x2
/*     9cd8:	10000003 */ 	b	.L00009ce8
/*     9cdc:	34c62600 */ 	ori	$a2,$a2,0x2600
.L00009ce0:
/*     9ce0:	3c060004 */ 	lui	$a2,0x4
/*     9ce4:	34c64c00 */ 	ori	$a2,$a2,0x4c00
.L00009ce8:
/*     9ce8:	24010001 */ 	addiu	$at,$zero,0x1
/*     9cec:	54410023 */ 	bnel	$v0,$at,.L00009d7c
/*     9cf0:	8cb90298 */ 	lw	$t9,0x298($a1)
/*     9cf4:	8ca9006c */ 	lw	$t1,0x6c($a1)
/*     9cf8:	24010002 */ 	addiu	$at,$zero,0x2
/*     9cfc:	00003825 */ 	or	$a3,$zero,$zero
/*     9d00:	11200003 */ 	beqz	$t1,.L00009d10
/*     9d04:	00002025 */ 	or	$a0,$zero,$zero
/*     9d08:	10000001 */ 	b	.L00009d10
/*     9d0c:	24070001 */ 	addiu	$a3,$zero,0x1
.L00009d10:
/*     9d10:	8caa0068 */ 	lw	$t2,0x68($a1)
/*     9d14:	00001825 */ 	or	$v1,$zero,$zero
/*     9d18:	00001025 */ 	or	$v0,$zero,$zero
/*     9d1c:	11400003 */ 	beqz	$t2,.L00009d2c
/*     9d20:	24180001 */ 	addiu	$t8,$zero,0x1
/*     9d24:	10000001 */ 	b	.L00009d2c
/*     9d28:	24040001 */ 	addiu	$a0,$zero,0x1
.L00009d2c:
/*     9d2c:	8cab0064 */ 	lw	$t3,0x64($a1)
/*     9d30:	11600003 */ 	beqz	$t3,.L00009d40
/*     9d34:	00000000 */ 	nop
/*     9d38:	10000001 */ 	b	.L00009d40
/*     9d3c:	24030001 */ 	addiu	$v1,$zero,0x1
.L00009d40:
/*     9d40:	8cac0070 */ 	lw	$t4,0x70($a1)
/*     9d44:	11800003 */ 	beqz	$t4,.L00009d54
/*     9d48:	00000000 */ 	nop
/*     9d4c:	10000001 */ 	b	.L00009d54
/*     9d50:	24020001 */ 	addiu	$v0,$zero,0x1
.L00009d54:
/*     9d54:	00436821 */ 	addu	$t5,$v0,$v1
/*     9d58:	01a47021 */ 	addu	$t6,$t5,$a0
/*     9d5c:	01c77821 */ 	addu	$t7,$t6,$a3
/*     9d60:	55e10006 */ 	bnel	$t7,$at,.L00009d7c
/*     9d64:	8cb90298 */ 	lw	$t9,0x298($a1)
/*     9d68:	3c060001 */ 	lui	$a2,0x1
/*     9d6c:	34c61300 */ 	ori	$a2,$a2,0x1300
/*     9d70:	10000024 */ 	b	.L00009e04
/*     9d74:	a0b804e0 */ 	sb	$t8,0x4e0($a1)
/*     9d78:	8cb90298 */ 	lw	$t9,0x298($a1)
.L00009d7c:
/*     9d7c:	24010002 */ 	addiu	$at,$zero,0x2
/*     9d80:	07230005 */ 	bgezl	$t9,.L00009d98
/*     9d84:	8caa006c */ 	lw	$t2,0x6c($a1)
/*     9d88:	8ca9029c */ 	lw	$t1,0x29c($a1)
/*     9d8c:	0522001e */ 	bltzl	$t1,.L00009e08
/*     9d90:	00062040 */ 	sll	$a0,$a2,0x1
/*     9d94:	8caa006c */ 	lw	$t2,0x6c($a1)
.L00009d98:
/*     9d98:	8ca20068 */ 	lw	$v0,0x68($a1)
/*     9d9c:	8ca30064 */ 	lw	$v1,0x64($a1)
/*     9da0:	11400003 */ 	beqz	$t2,.L00009db0
/*     9da4:	8ca80070 */ 	lw	$t0,0x70($a1)
/*     9da8:	10000002 */ 	b	.L00009db4
/*     9dac:	24070001 */ 	addiu	$a3,$zero,0x1
.L00009db0:
/*     9db0:	00003825 */ 	or	$a3,$zero,$zero
.L00009db4:
/*     9db4:	10400003 */ 	beqz	$v0,.L00009dc4
/*     9db8:	00002025 */ 	or	$a0,$zero,$zero
/*     9dbc:	10000001 */ 	b	.L00009dc4
/*     9dc0:	24040001 */ 	addiu	$a0,$zero,0x1
.L00009dc4:
/*     9dc4:	10600003 */ 	beqz	$v1,.L00009dd4
/*     9dc8:	00001025 */ 	or	$v0,$zero,$zero
/*     9dcc:	10000002 */ 	b	.L00009dd8
/*     9dd0:	24030001 */ 	addiu	$v1,$zero,0x1
.L00009dd4:
/*     9dd4:	00001825 */ 	or	$v1,$zero,$zero
.L00009dd8:
/*     9dd8:	11000003 */ 	beqz	$t0,.L00009de8
/*     9ddc:	00000000 */ 	nop
/*     9de0:	10000001 */ 	b	.L00009de8
/*     9de4:	24020001 */ 	addiu	$v0,$zero,0x1
.L00009de8:
/*     9de8:	00435821 */ 	addu	$t3,$v0,$v1
/*     9dec:	01646021 */ 	addu	$t4,$t3,$a0
/*     9df0:	01876821 */ 	addu	$t5,$t4,$a3
/*     9df4:	55a10004 */ 	bnel	$t5,$at,.L00009e08
/*     9df8:	00062040 */ 	sll	$a0,$a2,0x1
/*     9dfc:	3c060002 */ 	lui	$a2,0x2
/*     9e00:	34c62600 */ 	ori	$a2,$a2,0x9900
.L00009e04:
/*     9e04:	00062040 */ 	sll	$a0,$a2,0x1
.L00009e08:
/*     9e08:	24840040 */ 	addiu	$a0,$a0,0x40
/*     9e0c:	24050004 */ 	addiu	$a1,$zero,0x4
/*     9e10:	0c0048f2 */ 	jal	malloc
/*     9e14:	afa60018 */ 	sw	$a2,0x18($sp)
/*     9e18:	8fa60018 */ 	lw	$a2,0x18($sp)
/*     9e1c:	3c04800a */ 	lui	$a0,%hi(var8009cac0)
/*     9e20:	2445003f */ 	addiu	$a1,$v0,0x3f
/*     9e24:	2401ffc0 */ 	addiu	$at,$zero,-64
/*     9e28:	2484cac0 */ 	addiu	$a0,$a0,%lo(var8009cac0)
/*     9e2c:	00a17024 */ 	and	$t6,$a1,$at
/*     9e30:	00ce7821 */ 	addu	$t7,$a2,$t6
/*     9e34:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*     9e38:	ac8f0004 */ 	sw	$t7,0x4($a0)
/*     9e3c:	3c188009 */ 	lui	$t8,%hi(var80092874+0x2)
/*     9e40:	93182876 */ 	lbu	$t8,%lo(var80092874+0x2)($t8)
/*     9e44:	3c0b8006 */ 	lui	$t3,%hi(var8005d590)
/*     9e48:	8d6bd590 */ 	lw	$t3,%lo(var8005d590)($t3)
/*     9e4c:	0018c880 */ 	sll	$t9,$t8,0x2
/*     9e50:	00994821 */ 	addu	$t1,$a0,$t9
/*     9e54:	8d2a0000 */ 	lw	$t2,0x0($t1)
/*     9e58:	3c0c8009 */ 	lui	$t4,%hi(var80092874+0x3)
/*     9e5c:	3c188006 */ 	lui	$t8,%hi(g_ViData)
/*     9e60:	ad6a0028 */ 	sw	$t2,0x28($t3)
/*     9e64:	918c2877 */ 	lbu	$t4,%lo(var80092874+0x3)($t4)
/*     9e68:	8f18d594 */ 	lw	$t8,%lo(g_ViData)($t8)
/*     9e6c:	00001825 */ 	or	$v1,$zero,$zero
/*     9e70:	000c6880 */ 	sll	$t5,$t4,0x2
/*     9e74:	008d7021 */ 	addu	$t6,$a0,$t5
/*     9e78:	8dcf0000 */ 	lw	$t7,0x0($t6)
/*     9e7c:	24190001 */ 	addiu	$t9,$zero,0x1
/*     9e80:	af0f0028 */ 	sw	$t7,0x28($t8)
/*     9e84:	8c870000 */ 	lw	$a3,0x0($a0)
/*     9e88:	18c00009 */ 	blez	$a2,.L00009eb0
/*     9e8c:	8c880004 */ 	lw	$t0,0x4($a0)
/*     9e90:	00e01025 */ 	or	$v0,$a3,$zero
/*     9e94:	01002025 */ 	or	$a0,$t0,$zero
.L00009e98:
/*     9e98:	24630001 */ 	addiu	$v1,$v1,0x1
/*     9e9c:	a0400000 */ 	sb	$zero,0x0($v0)
/*     9ea0:	24420001 */ 	addiu	$v0,$v0,0x1
/*     9ea4:	24840001 */ 	addiu	$a0,$a0,0x1
/*     9ea8:	1466fffb */ 	bne	$v1,$a2,.L00009e98
/*     9eac:	a080ffff */ 	sb	$zero,-0x1($a0)
.L00009eb0:
/*     9eb0:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     9eb4:	3c018006 */ 	lui	$at,%hi(var8005d59c)
/*     9eb8:	ac39d59c */ 	sw	$t9,%lo(var8005d59c)($at)
/*     9ebc:	03e00008 */ 	jr	$ra
/*     9ec0:	27bd0020 */ 	addiu	$sp,$sp,0x20
);
#else
GLOBAL_ASM(
glabel func00009c3c
/*     9c3c:	3c05800a */ 	lui	$a1,%hi(g_Vars)
/*     9c40:	24a59fc0 */ 	addiu	$a1,$a1,%lo(g_Vars)
/*     9c44:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*     9c48:	2401005a */ 	addiu	$at,$zero,0x5a
/*     9c4c:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     9c50:	10810003 */ 	beq	$a0,$at,.L00009c60
/*     9c54:	a0a004e0 */ 	sb	$zero,0x4e0($a1)
/*     9c58:	2401004e */ 	addiu	$at,$zero,0x4e
/*     9c5c:	14810015 */ 	bne	$a0,$at,.L00009cb4
.L00009c60:
/*     9c60:	3c0e8009 */ 	lui	$t6,%hi(g_Is4Mb)
/*     9c64:	91ce0af0 */ 	lbu	$t6,%lo(g_Is4Mb)($t6)
/*     9c68:	24010001 */ 	addiu	$at,$zero,0x1
/*     9c6c:	15c10006 */ 	bne	$t6,$at,.L00009c88
/*     9c70:	00000000 */ 	nop
/*     9c74:	0c002aac */ 	jal	func0000aab0
/*     9c78:	24040002 */ 	addiu	$a0,$zero,0x2
/*     9c7c:	3c060008 */ 	lui	$a2,0x8
/*     9c80:	10000060 */ 	b	.L00009e04
/*     9c84:	34c69800 */ 	ori	$a2,$a2,0x9800
.L00009c88:
/*     9c88:	0c002aac */ 	jal	func0000aab0
/*     9c8c:	24040002 */ 	addiu	$a0,$zero,0x2
/*     9c90:	3c0f7005 */ 	lui	$t7,%hi(var700526dc)
/*     9c94:	3c187005 */ 	lui	$t8,%hi(var700526d4)
/*     9c98:	871826d4 */ 	lh	$t8,%lo(var700526d4)($t8)
/*     9c9c:	85ef26dc */ 	lh	$t7,%lo(var700526dc)($t7)
/*     9ca0:	01f80019 */ 	multu	$t7,$t8
/*     9ca4:	00003012 */ 	mflo	$a2
/*     9ca8:	0006c840 */ 	sll	$t9,$a2,0x1
/*     9cac:	10000055 */ 	b	.L00009e04
/*     9cb0:	03203025 */ 	or	$a2,$t9,$zero
.L00009cb4:
/*     9cb4:	0c002aac */ 	jal	func0000aab0
/*     9cb8:	24040001 */ 	addiu	$a0,$zero,0x1
/*     9cbc:	3c028009 */ 	lui	$v0,%hi(g_Is4Mb)
/*     9cc0:	90420af0 */ 	lbu	$v0,%lo(g_Is4Mb)($v0)
/*     9cc4:	3c05800a */ 	lui	$a1,%hi(g_Vars)
/*     9cc8:	24010001 */ 	addiu	$at,$zero,0x1
/*     9ccc:	14410004 */ 	bne	$v0,$at,.L00009ce0
/*     9cd0:	24a59fc0 */ 	addiu	$a1,$a1,%lo(g_Vars)
/*     9cd4:	3c060002 */ 	lui	$a2,0x2
/*     9cd8:	10000003 */ 	b	.L00009ce8
/*     9cdc:	34c62600 */ 	ori	$a2,$a2,0x2600
.L00009ce0:
/*     9ce0:	3c060004 */ 	lui	$a2,0x4
/*     9ce4:	34c64c00 */ 	ori	$a2,$a2,0x4c00
.L00009ce8:
/*     9ce8:	24010001 */ 	addiu	$at,$zero,0x1
/*     9cec:	54410023 */ 	bnel	$v0,$at,.L00009d7c
/*     9cf0:	8cb90298 */ 	lw	$t9,0x298($a1)
/*     9cf4:	8ca9006c */ 	lw	$t1,0x6c($a1)
/*     9cf8:	24010002 */ 	addiu	$at,$zero,0x2
/*     9cfc:	00003825 */ 	or	$a3,$zero,$zero
/*     9d00:	11200003 */ 	beqz	$t1,.L00009d10
/*     9d04:	00002025 */ 	or	$a0,$zero,$zero
/*     9d08:	10000001 */ 	b	.L00009d10
/*     9d0c:	24070001 */ 	addiu	$a3,$zero,0x1
.L00009d10:
/*     9d10:	8caa0068 */ 	lw	$t2,0x68($a1)
/*     9d14:	00001825 */ 	or	$v1,$zero,$zero
/*     9d18:	00001025 */ 	or	$v0,$zero,$zero
/*     9d1c:	11400003 */ 	beqz	$t2,.L00009d2c
/*     9d20:	24180001 */ 	addiu	$t8,$zero,0x1
/*     9d24:	10000001 */ 	b	.L00009d2c
/*     9d28:	24040001 */ 	addiu	$a0,$zero,0x1
.L00009d2c:
/*     9d2c:	8cab0064 */ 	lw	$t3,0x64($a1)
/*     9d30:	11600003 */ 	beqz	$t3,.L00009d40
/*     9d34:	00000000 */ 	nop
/*     9d38:	10000001 */ 	b	.L00009d40
/*     9d3c:	24030001 */ 	addiu	$v1,$zero,0x1
.L00009d40:
/*     9d40:	8cac0070 */ 	lw	$t4,0x70($a1)
/*     9d44:	11800003 */ 	beqz	$t4,.L00009d54
/*     9d48:	00000000 */ 	nop
/*     9d4c:	10000001 */ 	b	.L00009d54
/*     9d50:	24020001 */ 	addiu	$v0,$zero,0x1
.L00009d54:
/*     9d54:	00436821 */ 	addu	$t5,$v0,$v1
/*     9d58:	01a47021 */ 	addu	$t6,$t5,$a0
/*     9d5c:	01c77821 */ 	addu	$t7,$t6,$a3
/*     9d60:	55e10006 */ 	bnel	$t7,$at,.L00009d7c
/*     9d64:	8cb90298 */ 	lw	$t9,0x298($a1)
/*     9d68:	3c060001 */ 	lui	$a2,0x1
/*     9d6c:	34c61300 */ 	ori	$a2,$a2,0x1300
/*     9d70:	10000024 */ 	b	.L00009e04
/*     9d74:	a0b804e0 */ 	sb	$t8,0x4e0($a1)
/*     9d78:	8cb90298 */ 	lw	$t9,0x298($a1)
.L00009d7c:
/*     9d7c:	24010002 */ 	addiu	$at,$zero,0x2
/*     9d80:	07230005 */ 	bgezl	$t9,.L00009d98
/*     9d84:	8caa006c */ 	lw	$t2,0x6c($a1)
/*     9d88:	8ca9029c */ 	lw	$t1,0x29c($a1)
/*     9d8c:	0522001e */ 	bltzl	$t1,.L00009e08
/*     9d90:	00062040 */ 	sll	$a0,$a2,0x1
/*     9d94:	8caa006c */ 	lw	$t2,0x6c($a1)
.L00009d98:
/*     9d98:	8ca20068 */ 	lw	$v0,0x68($a1)
/*     9d9c:	8ca30064 */ 	lw	$v1,0x64($a1)
/*     9da0:	11400003 */ 	beqz	$t2,.L00009db0
/*     9da4:	8ca80070 */ 	lw	$t0,0x70($a1)
/*     9da8:	10000002 */ 	b	.L00009db4
/*     9dac:	24070001 */ 	addiu	$a3,$zero,0x1
.L00009db0:
/*     9db0:	00003825 */ 	or	$a3,$zero,$zero
.L00009db4:
/*     9db4:	10400003 */ 	beqz	$v0,.L00009dc4
/*     9db8:	00002025 */ 	or	$a0,$zero,$zero
/*     9dbc:	10000001 */ 	b	.L00009dc4
/*     9dc0:	24040001 */ 	addiu	$a0,$zero,0x1
.L00009dc4:
/*     9dc4:	10600003 */ 	beqz	$v1,.L00009dd4
/*     9dc8:	00001025 */ 	or	$v0,$zero,$zero
/*     9dcc:	10000002 */ 	b	.L00009dd8
/*     9dd0:	24030001 */ 	addiu	$v1,$zero,0x1
.L00009dd4:
/*     9dd4:	00001825 */ 	or	$v1,$zero,$zero
.L00009dd8:
/*     9dd8:	11000003 */ 	beqz	$t0,.L00009de8
/*     9ddc:	00000000 */ 	nop
/*     9de0:	10000001 */ 	b	.L00009de8
/*     9de4:	24020001 */ 	addiu	$v0,$zero,0x1
.L00009de8:
/*     9de8:	00435821 */ 	addu	$t3,$v0,$v1
/*     9dec:	01646021 */ 	addu	$t4,$t3,$a0
/*     9df0:	01876821 */ 	addu	$t5,$t4,$a3
/*     9df4:	55a10004 */ 	bnel	$t5,$at,.L00009e08
/*     9df8:	00062040 */ 	sll	$a0,$a2,0x1
/*     9dfc:	3c060002 */ 	lui	$a2,0x2
/*     9e00:	34c62600 */ 	ori	$a2,$a2,0x2600
.L00009e04:
/*     9e04:	00062040 */ 	sll	$a0,$a2,0x1
.L00009e08:
/*     9e08:	24840040 */ 	addiu	$a0,$a0,0x40
/*     9e0c:	24050004 */ 	addiu	$a1,$zero,0x4
/*     9e10:	0c0048f2 */ 	jal	malloc
/*     9e14:	afa60018 */ 	sw	$a2,0x18($sp)
/*     9e18:	8fa60018 */ 	lw	$a2,0x18($sp)
/*     9e1c:	3c04800a */ 	lui	$a0,%hi(var8009cac0)
/*     9e20:	2445003f */ 	addiu	$a1,$v0,0x3f
/*     9e24:	2401ffc0 */ 	addiu	$at,$zero,-64
/*     9e28:	2484cac0 */ 	addiu	$a0,$a0,%lo(var8009cac0)
/*     9e2c:	00a17024 */ 	and	$t6,$a1,$at
/*     9e30:	00ce7821 */ 	addu	$t7,$a2,$t6
/*     9e34:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*     9e38:	ac8f0004 */ 	sw	$t7,0x4($a0)
/*     9e3c:	3c188009 */ 	lui	$t8,%hi(var80092874+0x2)
/*     9e40:	93182876 */ 	lbu	$t8,%lo(var80092874+0x2)($t8)
/*     9e44:	3c0b8006 */ 	lui	$t3,%hi(var8005d590)
/*     9e48:	8d6bd590 */ 	lw	$t3,%lo(var8005d590)($t3)
/*     9e4c:	0018c880 */ 	sll	$t9,$t8,0x2
/*     9e50:	00994821 */ 	addu	$t1,$a0,$t9
/*     9e54:	8d2a0000 */ 	lw	$t2,0x0($t1)
/*     9e58:	3c0c8009 */ 	lui	$t4,%hi(var80092874+0x3)
/*     9e5c:	3c188006 */ 	lui	$t8,%hi(g_ViData)
/*     9e60:	ad6a0028 */ 	sw	$t2,0x28($t3)
/*     9e64:	918c2877 */ 	lbu	$t4,%lo(var80092874+0x3)($t4)
/*     9e68:	8f18d594 */ 	lw	$t8,%lo(g_ViData)($t8)
/*     9e6c:	00001825 */ 	or	$v1,$zero,$zero
/*     9e70:	000c6880 */ 	sll	$t5,$t4,0x2
/*     9e74:	008d7021 */ 	addu	$t6,$a0,$t5
/*     9e78:	8dcf0000 */ 	lw	$t7,0x0($t6)
/*     9e7c:	24190001 */ 	addiu	$t9,$zero,0x1
/*     9e80:	af0f0028 */ 	sw	$t7,0x28($t8)
/*     9e84:	8c870000 */ 	lw	$a3,0x0($a0)
/*     9e88:	18c00009 */ 	blez	$a2,.L00009eb0
/*     9e8c:	8c880004 */ 	lw	$t0,0x4($a0)
/*     9e90:	00e01025 */ 	or	$v0,$a3,$zero
/*     9e94:	01002025 */ 	or	$a0,$t0,$zero
.L00009e98:
/*     9e98:	24630001 */ 	addiu	$v1,$v1,0x1
/*     9e9c:	a0400000 */ 	sb	$zero,0x0($v0)
/*     9ea0:	24420001 */ 	addiu	$v0,$v0,0x1
/*     9ea4:	24840001 */ 	addiu	$a0,$a0,0x1
/*     9ea8:	1466fffb */ 	bne	$v1,$a2,.L00009e98
/*     9eac:	a080ffff */ 	sb	$zero,-0x1($a0)
.L00009eb0:
/*     9eb0:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     9eb4:	3c018006 */ 	lui	$at,%hi(var8005d59c)
/*     9eb8:	ac39d59c */ 	sw	$t9,%lo(var8005d59c)($at)
/*     9ebc:	03e00008 */ 	jr	$ra
/*     9ec0:	27bd0020 */ 	addiu	$sp,$sp,0x20
);
#endif

void func00009ec4(s32 arg0)
{
	arg0 += 2;
	var8005ce90 = arg0;
}

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func00009ed4
/*     9ed4:	3c038006 */ 	lui	$v1,%hi(var8005ce9c)
/*     9ed8:	2463ce9c */ 	addiu	$v1,$v1,%lo(var8005ce9c)
/*     9edc:	8c620000 */ 	lw	$v0,0x0($v1)
/*     9ee0:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*     9ee4:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     9ee8:	10400006 */ 	beqz	$v0,.L00009f04
/*     9eec:	3c188006 */ 	lui	$t8,%hi(var8005ce98)
/*     9ef0:	244effff */ 	addiu	$t6,$v0,-1
/*     9ef4:	15c00003 */ 	bnez	$t6,.L00009f04
/*     9ef8:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*     9efc:	3c018006 */ 	lui	$at,%hi(var8005ce98)
/*     9f00:	ac20ce98 */ 	sw	$zero,%lo(var8005ce98)($at)
.L00009f04:
/*     9f04:	3c038006 */ 	lui	$v1,%hi(var8005ce94)
/*     9f08:	2463ce94 */ 	addiu	$v1,$v1,%lo(var8005ce94)
/*     9f0c:	8c620000 */ 	lw	$v0,0x0($v1)
/*     9f10:	8f18ce98 */ 	lw	$t8,%lo(var8005ce98)($t8)
/*     9f14:	24040001 */ 	addiu	$a0,$zero,0x1
/*     9f18:	0002c823 */ 	negu	$t9,$v0
/*     9f1c:	00580019 */ 	multu	$v0,$t8
/*     9f20:	ac790000 */ 	sw	$t9,0x0($v1)
/*     9f24:	00002812 */ 	mflo	$a1
/*     9f28:	afa50018 */ 	sw	$a1,0x18($sp)
/*     9f2c:	0c012194 */ 	jal	osSetIntMask
/*     9f30:	00000000 */ 	nop
/*     9f34:	3c078006 */ 	lui	$a3,%hi(var8005ce74)
/*     9f38:	3c038009 */ 	lui	$v1,%hi(var8008de0c)
/*     9f3c:	8c6dde0c */ 	lw	$t5,%lo(var8008de0c)($v1)
/*     9f40:	24e7ce74 */ 	addiu	$a3,$a3,%lo(var8005ce74)
/*     9f44:	8fa50018 */ 	lw	$a1,0x18($sp)
/*     9f48:	8cf90000 */ 	lw	$t9,0x0($a3)
/*     9f4c:	000d4c03 */ 	sra	$t1,$t5,0x10
/*     9f50:	3c068009 */ 	lui	$a2,%hi(var8008dd60+0x4)
/*     9f54:	01255821 */ 	addu	$t3,$t1,$a1
/*     9f58:	00194080 */ 	sll	$t0,$t9,0x2
/*     9f5c:	24c6dd64 */ 	addiu	$a2,$a2,%lo(var8008dd60+0x4)
/*     9f60:	00084823 */ 	negu	$t1,$t0
/*     9f64:	00c95021 */ 	addu	$t2,$a2,$t1
/*     9f68:	000b6400 */ 	sll	$t4,$t3,0x10
/*     9f6c:	8d4b0000 */ 	lw	$t3,0x0($t2)
/*     9f70:	01a57021 */ 	addu	$t6,$t5,$a1
/*     9f74:	31cfffff */ 	andi	$t7,$t6,0xffff
/*     9f78:	018fc025 */ 	or	$t8,$t4,$t7
/*     9f7c:	3c038009 */ 	lui	$v1,%hi(var8008de10)
/*     9f80:	ad780030 */ 	sw	$t8,0x30($t3)
/*     9f84:	8c68de10 */ 	lw	$t0,%lo(var8008de10)($v1)
/*     9f88:	8ceb0000 */ 	lw	$t3,0x0($a3)
/*     9f8c:	00402025 */ 	or	$a0,$v0,$zero
/*     9f90:	00087403 */ 	sra	$t6,$t0,0x10
/*     9f94:	01c57821 */ 	addu	$t7,$t6,$a1
/*     9f98:	000b6880 */ 	sll	$t5,$t3,0x2
/*     9f9c:	000d7023 */ 	negu	$t6,$t5
/*     9fa0:	00ce6021 */ 	addu	$t4,$a2,$t6
/*     9fa4:	000fcc00 */ 	sll	$t9,$t7,0x10
/*     9fa8:	01054821 */ 	addu	$t1,$t0,$a1
/*     9fac:	8d8f0000 */ 	lw	$t7,0x0($t4)
/*     9fb0:	312affff */ 	andi	$t2,$t1,0xffff
/*     9fb4:	032ac025 */ 	or	$t8,$t9,$t2
/*     9fb8:	0c012194 */ 	jal	osSetIntMask
/*     9fbc:	adf80044 */ 	sw	$t8,0x44($t7)
/*     9fc0:	3c088006 */ 	lui	$t0,%hi(var8005ce74)
/*     9fc4:	8d08ce74 */ 	lw	$t0,%lo(var8005ce74)($t0)
/*     9fc8:	3c048009 */ 	lui	$a0,%hi(var8008dd60+0x4)
/*     9fcc:	00084880 */ 	sll	$t1,$t0,0x2
/*     9fd0:	0009c823 */ 	negu	$t9,$t1
/*     9fd4:	00992021 */ 	addu	$a0,$a0,$t9
/*     9fd8:	0c012354 */ 	jal	osViSetMode
/*     9fdc:	8c84dd64 */ 	lw	$a0,%lo(var8008dd60+0x4)($a0)
/*     9fe0:	3c048006 */ 	lui	$a0,%hi(var8005ce90+0x3)
/*     9fe4:	0c012338 */ 	jal	osViBlack
/*     9fe8:	9084ce93 */ 	lbu	$a0,%lo(var8005ce90+0x3)($a0)
/*     9fec:	3c0a8006 */ 	lui	$t2,%hi(var8005ce74)
/*     9ff0:	8d4ace74 */ 	lw	$t2,%lo(var8005ce74)($t2)
/*     9ff4:	3c018006 */ 	lui	$at,%hi(var8005ce78+0x4)
/*     9ff8:	000a5880 */ 	sll	$t3,$t2,0x2
/*     9ffc:	000b6823 */ 	negu	$t5,$t3
/*     a000:	002d0821 */ 	addu	$at,$at,$t5
/*     a004:	0c012370 */ 	jal	osViSetXScale
/*     a008:	c42cce7c */ 	lwc1	$f12,%lo(var8005ce78+0x4)($at)
/*     a00c:	3c0e8006 */ 	lui	$t6,%hi(var8005ce74)
/*     a010:	8dcece74 */ 	lw	$t6,%lo(var8005ce74)($t6)
/*     a014:	3c018006 */ 	lui	$at,%hi(var8005ce80+0x4)
/*     a018:	000e6080 */ 	sll	$t4,$t6,0x2
/*     a01c:	000cc023 */ 	negu	$t8,$t4
/*     a020:	00380821 */ 	addu	$at,$at,$t8
/*     a024:	0c0123bc */ 	jal	osViSetYScale
/*     a028:	c42cce84 */ 	lwc1	$f12,%lo(var8005ce80+0x4)($at)
/*     a02c:	0c0123d4 */ 	jal	osViSetSpecialFeatures
/*     a030:	24040042 */ 	addiu	$a0,$zero,0x42
/*     a034:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     a038:	27bd0020 */ 	addiu	$sp,$sp,0x20
/*     a03c:	03e00008 */ 	jr	$ra
/*     a040:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel func00009ed4
/*     a078:	3c038006 */ 	lui	$v1,0x8006
/*     a07c:	2463e61c */ 	addiu	$v1,$v1,-6628
/*     a080:	8c620000 */ 	lw	$v0,0x0($v1)
/*     a084:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*     a088:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     a08c:	10400006 */ 	beqz	$v0,.NB0000a0a8
/*     a090:	3c088006 */ 	lui	$t0,0x8006
/*     a094:	244effff */ 	addiu	$t6,$v0,-1
/*     a098:	15c00003 */ 	bnez	$t6,.NB0000a0a8
/*     a09c:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*     a0a0:	3c018006 */ 	lui	$at,0x8006
/*     a0a4:	ac20e618 */ 	sw	$zero,-0x19e8($at)
.NB0000a0a8:
/*     a0a8:	2508e614 */ 	addiu	$t0,$t0,-6636
/*     a0ac:	3c188006 */ 	lui	$t8,0x8006
/*     a0b0:	8f18e618 */ 	lw	$t8,-0x19e8($t8)
/*     a0b4:	8d050000 */ 	lw	$a1,0x0($t0)
/*     a0b8:	3c028009 */ 	lui	$v0,0x8009
/*     a0bc:	3c078006 */ 	lui	$a3,0x8006
/*     a0c0:	00b80019 */ 	multu	$a1,$t8
/*     a0c4:	0005c823 */ 	negu	$t9,$a1
/*     a0c8:	ad190000 */ 	sw	$t9,0x0($t0)
/*     a0cc:	8c4e043c */ 	lw	$t6,0x43c($v0)
/*     a0d0:	24e7e5f4 */ 	addiu	$a3,$a3,-6668
/*     a0d4:	8ce90000 */ 	lw	$t1,0x0($a3)
/*     a0d8:	000e5403 */ 	sra	$t2,$t6,0x10
/*     a0dc:	3c068009 */ 	lui	$a2,0x8009
/*     a0e0:	24c60394 */ 	addiu	$a2,$a2,0x394
/*     a0e4:	3c028009 */ 	lui	$v0,0x8009
/*     a0e8:	00001812 */ 	mflo	$v1
/*     a0ec:	01436021 */ 	addu	$t4,$t2,$v1
/*     a0f0:	00095080 */ 	sll	$t2,$t1,0x2
/*     a0f4:	000a5823 */ 	negu	$t3,$t2
/*     a0f8:	000c6c00 */ 	sll	$t5,$t4,0x10
/*     a0fc:	00cb6021 */ 	addu	$t4,$a2,$t3
/*     a100:	01c37821 */ 	addu	$t7,$t6,$v1
/*     a104:	8d8e0000 */ 	lw	$t6,0x0($t4)
/*     a108:	31f8ffff */ 	andi	$t8,$t7,0xffff
/*     a10c:	01b8c825 */ 	or	$t9,$t5,$t8
/*     a110:	add90030 */ 	sw	$t9,0x30($t6)
/*     a114:	8c4b0440 */ 	lw	$t3,0x440($v0)
/*     a118:	8cef0000 */ 	lw	$t7,0x0($a3)
/*     a11c:	000b6c03 */ 	sra	$t5,$t3,0x10
/*     a120:	01a34821 */ 	addu	$t1,$t5,$v1
/*     a124:	000f6880 */ 	sll	$t5,$t7,0x2
/*     a128:	000dc023 */ 	negu	$t8,$t5
/*     a12c:	00095400 */ 	sll	$t2,$t1,0x10
/*     a130:	00d84821 */ 	addu	$t1,$a2,$t8
/*     a134:	01636021 */ 	addu	$t4,$t3,$v1
/*     a138:	8d2b0000 */ 	lw	$t3,0x0($t1)
/*     a13c:	3199ffff */ 	andi	$t9,$t4,0xffff
/*     a140:	01597025 */ 	or	$t6,$t2,$t9
/*     a144:	ad6e0044 */ 	sw	$t6,0x44($t3)
/*     a148:	8cec0000 */ 	lw	$t4,0x0($a3)
/*     a14c:	000c5080 */ 	sll	$t2,$t4,0x2
/*     a150:	000ac823 */ 	negu	$t9,$t2
/*     a154:	00d97821 */ 	addu	$t7,$a2,$t9
/*     a158:	0c012848 */ 	jal	osViSetMode
/*     a15c:	8de40000 */ 	lw	$a0,0x0($t7)
/*     a160:	3c048006 */ 	lui	$a0,0x8006
/*     a164:	0c01282c */ 	jal	osViBlack
/*     a168:	9084e613 */ 	lbu	$a0,-0x19ed($a0)
/*     a16c:	3c0d8006 */ 	lui	$t5,0x8006
/*     a170:	8dade5f4 */ 	lw	$t5,-0x1a0c($t5)
/*     a174:	3c018006 */ 	lui	$at,0x8006
/*     a178:	000dc080 */ 	sll	$t8,$t5,0x2
/*     a17c:	00184823 */ 	negu	$t1,$t8
/*     a180:	00290821 */ 	addu	$at,$at,$t1
/*     a184:	0c012864 */ 	jal	osViSetXScale
/*     a188:	c42ce5fc */ 	lwc1	$f12,-0x1a04($at)
/*     a18c:	3c0e8006 */ 	lui	$t6,0x8006
/*     a190:	8dcee5f4 */ 	lw	$t6,-0x1a0c($t6)
/*     a194:	3c018006 */ 	lui	$at,0x8006
/*     a198:	000e5880 */ 	sll	$t3,$t6,0x2
/*     a19c:	000b6023 */ 	negu	$t4,$t3
/*     a1a0:	002c0821 */ 	addu	$at,$at,$t4
/*     a1a4:	0c0128b0 */ 	jal	osViSetYScale
/*     a1a8:	c42ce604 */ 	lwc1	$f12,-0x19fc($at)
/*     a1ac:	0c0128c8 */ 	jal	osViSetSpecialFeatures
/*     a1b0:	24040042 */ 	addiu	$a0,$zero,0x42
/*     a1b4:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     a1b8:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*     a1bc:	03e00008 */ 	jr	$ra
/*     a1c0:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0000a044
/*     9f64:	3c098006 */ 	lui	$t1,0x8006
/*     9f68:	3c0e8006 */ 	lui	$t6,0x8006
/*     9f6c:	8dced230 */ 	lw	$t6,-0x2dd0($t6)
/*     9f70:	8d29d234 */ 	lw	$t1,-0x2dcc($t1)
/*     9f74:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*     9f78:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     9f7c:	91cf0000 */ 	lbu	$t7,0x0($t6)
/*     9f80:	91220000 */ 	lbu	$v0,0x0($t1)
/*     9f84:	504f0014 */ 	beql	$v0,$t7,.PF00009fd8
/*     9f88:	85380004 */ 	lh	$t8,0x4($t1)
/*     9f8c:	10400008 */ 	beqz	$v0,.PF00009fb0
/*     9f90:	00401825 */ 	move	$v1,$v0
/*     9f94:	241f0001 */ 	li	$ra,0x1
/*     9f98:	105f000e */ 	beq	$v0,$ra,.PF00009fd4
/*     9f9c:	24010002 */ 	li	$at,0x2
/*     9fa0:	5061000d */ 	beql	$v1,$at,.PF00009fd8
/*     9fa4:	85380004 */ 	lh	$t8,0x4($t1)
/*     9fa8:	1000000b */ 	b	.PF00009fd8
/*     9fac:	85380004 */ 	lh	$t8,0x4($t1)
.PF00009fb0:
/*     9fb0:	3c013f80 */ 	lui	$at,0x3f80
/*     9fb4:	44816000 */ 	mtc1	$at,$f12
/*     9fb8:	0c0121fc */ 	jal	osViSetYScale
/*     9fbc:	00000000 */ 	nop
/*     9fc0:	0c012178 */ 	jal	osViBlack
/*     9fc4:	24040001 */ 	li	$a0,0x1
/*     9fc8:	3c098006 */ 	lui	$t1,0x8006
/*     9fcc:	8d29d234 */ 	lw	$t1,-0x2dcc($t1)
/*     9fd0:	91220000 */ 	lbu	$v0,0x0($t1)
.PF00009fd4:
/*     9fd4:	85380004 */ 	lh	$t8,0x4($t1)
.PF00009fd8:
/*     9fd8:	85390018 */ 	lh	$t9,0x18($t1)
/*     9fdc:	852e0006 */ 	lh	$t6,0x6($t1)
/*     9fe0:	44982000 */ 	mtc1	$t8,$f4
/*     9fe4:	852f001a */ 	lh	$t7,0x1a($t1)
/*     9fe8:	44994000 */ 	mtc1	$t9,$f8
/*     9fec:	468021a0 */ 	cvt.s.w	$f6,$f4
/*     9ff0:	448e8000 */ 	mtc1	$t6,$f16
/*     9ff4:	448f2000 */ 	mtc1	$t7,$f4
/*     9ff8:	3c0d8009 */ 	lui	$t5,0x8009
/*     9ffc:	241f0001 */ 	li	$ra,0x1
/*     a000:	468042a0 */ 	cvt.s.w	$f10,$f8
/*     a004:	3c0c8006 */ 	lui	$t4,0x8006
/*     a008:	3c013f80 */ 	lui	$at,0x3f80
/*     a00c:	25ade35c */ 	addiu	$t5,$t5,-7332
/*     a010:	468084a0 */ 	cvt.s.w	$f18,$f16
/*     a014:	46802220 */ 	cvt.s.w	$f8,$f4
/*     a018:	460a3083 */ 	div.s	$f2,$f6,$f10
/*     a01c:	14400003 */ 	bnez	$v0,.PF0000a02c
/*     a020:	46089003 */ 	div.s	$f0,$f18,$f8
/*     a024:	44810000 */ 	mtc1	$at,$f0
/*     a028:	00000000 */ 	nop
.PF0000a02c:
/*     a02c:	8d8cd240 */ 	lw	$t4,-0x2dc0($t4)
/*     a030:	3c018006 */ 	lui	$at,0x8006
/*     a034:	000c5880 */ 	sll	$t3,$t4,0x2
/*     a038:	002b0821 */ 	addu	$at,$at,$t3
/*     a03c:	e422cb28 */ 	swc1	$f2,-0x34d8($at)
/*     a040:	3c018006 */ 	lui	$at,0x8006
/*     a044:	002b0821 */ 	addu	$at,$at,$t3
/*     a048:	e420cb30 */ 	swc1	$f0,-0x34d0($at)
/*     a04c:	91220000 */ 	lbu	$v0,0x0($t1)
/*     a050:	57e200a3 */ 	bnel	$ra,$v0,.PF0000a2e0
/*     a054:	24010002 */ 	li	$at,0x2
/*     a058:	3c0a8006 */ 	lui	$t2,0x8006
/*     a05c:	8d4ad238 */ 	lw	$t2,-0x2dc8($t2)
/*     a060:	3c1f8009 */ 	lui	$ra,0x8009
/*     a064:	000c7880 */ 	sll	$t7,$t4,0x2
/*     a068:	11400019 */ 	beqz	$t2,.PF0000a0d0
/*     a06c:	27ffe360 */ 	addiu	$ra,$ra,-7328
/*     a070:	000cc080 */ 	sll	$t8,$t4,0x2
/*     a074:	030cc021 */ 	addu	$t8,$t8,$t4
/*     a078:	3c198009 */ 	lui	$t9,0x8009
/*     a07c:	2739e210 */ 	addiu	$t9,$t9,-7664
/*     a080:	0018c100 */ 	sll	$t8,$t8,0x4
/*     a084:	03191021 */ 	addu	$v0,$t8,$t9
/*     a088:	3c0e8006 */ 	lui	$t6,0x8006
/*     a08c:	25cef8c0 */ 	addiu	$t6,$t6,-1856
/*     a090:	25d80048 */ 	addiu	$t8,$t6,0x48
/*     a094:	0040c825 */ 	move	$t9,$v0
.PF0000a098:
/*     a098:	8dc10000 */ 	lw	$at,0x0($t6)
/*     a09c:	25ce000c */ 	addiu	$t6,$t6,0xc
/*     a0a0:	2739000c */ 	addiu	$t9,$t9,0xc
/*     a0a4:	af21fff4 */ 	sw	$at,-0xc($t9)
/*     a0a8:	8dc1fff8 */ 	lw	$at,-0x8($t6)
/*     a0ac:	af21fff8 */ 	sw	$at,-0x8($t9)
/*     a0b0:	8dc1fffc */ 	lw	$at,-0x4($t6)
/*     a0b4:	15d8fff8 */ 	bne	$t6,$t8,.PF0000a098
/*     a0b8:	af21fffc */ 	sw	$at,-0x4($t9)
/*     a0bc:	8dc10000 */ 	lw	$at,0x0($t6)
/*     a0c0:	af210000 */ 	sw	$at,0x0($t9)
/*     a0c4:	8dd80004 */ 	lw	$t8,0x4($t6)
/*     a0c8:	10000017 */ 	b	.PF0000a128
/*     a0cc:	af380004 */ 	sw	$t8,0x4($t9)
.PF0000a0d0:
/*     a0d0:	01ec7821 */ 	addu	$t7,$t7,$t4
/*     a0d4:	3c188009 */ 	lui	$t8,0x8009
/*     a0d8:	2718e210 */ 	addiu	$t8,$t8,-7664
/*     a0dc:	000f7900 */ 	sll	$t7,$t7,0x4
/*     a0e0:	01f81021 */ 	addu	$v0,$t7,$t8
/*     a0e4:	3c0e8006 */ 	lui	$t6,0x8006
/*     a0e8:	25cefa00 */ 	addiu	$t6,$t6,-1536
/*     a0ec:	25cf0048 */ 	addiu	$t7,$t6,0x48
/*     a0f0:	0040c025 */ 	move	$t8,$v0
.PF0000a0f4:
/*     a0f4:	8dc10000 */ 	lw	$at,0x0($t6)
/*     a0f8:	25ce000c */ 	addiu	$t6,$t6,0xc
/*     a0fc:	2718000c */ 	addiu	$t8,$t8,0xc
/*     a100:	af01fff4 */ 	sw	$at,-0xc($t8)
/*     a104:	8dc1fff8 */ 	lw	$at,-0x8($t6)
/*     a108:	af01fff8 */ 	sw	$at,-0x8($t8)
/*     a10c:	8dc1fffc */ 	lw	$at,-0x4($t6)
/*     a110:	15cffff8 */ 	bne	$t6,$t7,.PF0000a0f4
/*     a114:	af01fffc */ 	sw	$at,-0x4($t8)
/*     a118:	8dc10000 */ 	lw	$at,0x0($t6)
/*     a11c:	af010000 */ 	sw	$at,0x0($t8)
/*     a120:	8dcf0004 */ 	lw	$t7,0x4($t6)
/*     a124:	af0f0004 */ 	sw	$t7,0x4($t8)
.PF0000a128:
/*     a128:	85390018 */ 	lh	$t9,0x18($t1)
/*     a12c:	24010280 */ 	li	$at,0x280
/*     a130:	24080400 */ 	li	$t0,0x400
/*     a134:	ac590008 */ 	sw	$t9,0x8($v0)
/*     a138:	852f0018 */ 	lh	$t7,0x18($t1)
/*     a13c:	8c44001c */ 	lw	$a0,0x1c($v0)
/*     a140:	3c078006 */ 	lui	$a3,0x8006
/*     a144:	000f7280 */ 	sll	$t6,$t7,0xa
/*     a148:	01c1001a */ 	div	$zero,$t6,$at
/*     a14c:	0000c012 */ 	mflo	$t8
/*     a150:	ac580020 */ 	sw	$t8,0x20($v0)
/*     a154:	85390018 */ 	lh	$t9,0x18($t1)
/*     a158:	3406ffff */ 	li	$a2,0xffff
/*     a15c:	00197840 */ 	sll	$t7,$t9,0x1
/*     a160:	ac4f0028 */ 	sw	$t7,0x28($v0)
/*     a164:	852e0018 */ 	lh	$t6,0x18($t1)
/*     a168:	ac48002c */ 	sw	$t0,0x2c($v0)
/*     a16c:	ac480040 */ 	sw	$t0,0x40($v0)
/*     a170:	000ec040 */ 	sll	$t8,$t6,0x1
/*     a174:	ac58003c */ 	sw	$t8,0x3c($v0)
/*     a178:	8ce7d228 */ 	lw	$a3,-0x2dd8($a3)
/*     a17c:	0004cc03 */ 	sra	$t9,$a0,0x10
/*     a180:	332fffff */ 	andi	$t7,$t9,0xffff
/*     a184:	01e77021 */ 	addu	$t6,$t7,$a3
/*     a188:	01c6001a */ 	div	$zero,$t6,$a2
/*     a18c:	14c00002 */ 	bnez	$a2,.PF0000a198
/*     a190:	00000000 */ 	nop
/*     a194:	0007000d */ 	break	0x7
.PF0000a198:
/*     a198:	2401ffff */ 	li	$at,-1
/*     a19c:	14c10004 */ 	bne	$a2,$at,.PF0000a1b0
/*     a1a0:	3c018000 */ 	lui	$at,0x8000
/*     a1a4:	15c10002 */ 	bne	$t6,$at,.PF0000a1b0
/*     a1a8:	00000000 */ 	nop
/*     a1ac:	0006000d */ 	break	0x6
.PF0000a1b0:
/*     a1b0:	308fffff */ 	andi	$t7,$a0,0xffff
/*     a1b4:	0000c010 */ 	mfhi	$t8
/*     a1b8:	01e77021 */ 	addu	$t6,$t7,$a3
/*     a1bc:	0018cc00 */ 	sll	$t9,$t8,0x10
/*     a1c0:	01c6001a */ 	div	$zero,$t6,$a2
/*     a1c4:	14c00002 */ 	bnez	$a2,.PF0000a1d0
/*     a1c8:	00000000 */ 	nop
/*     a1cc:	0007000d */ 	break	0x7
.PF0000a1d0:
/*     a1d0:	2401ffff */ 	li	$at,-1
/*     a1d4:	14c10004 */ 	bne	$a2,$at,.PF0000a1e8
/*     a1d8:	3c018000 */ 	lui	$at,0x8000
/*     a1dc:	15c10002 */ 	bne	$t6,$at,.PF0000a1e8
/*     a1e0:	00000000 */ 	nop
/*     a1e4:	0006000d */ 	break	0x6
.PF0000a1e8:
/*     a1e8:	0000c010 */ 	mfhi	$t8
/*     a1ec:	03381825 */ 	or	$v1,$t9,$t8
/*     a1f0:	ac43001c */ 	sw	$v1,0x1c($v0)
/*     a1f4:	3c018009 */ 	lui	$at,0x8009
/*     a1f8:	ac23e358 */ 	sw	$v1,-0x1ca8($at)
/*     a1fc:	8525001a */ 	lh	$a1,0x1a($t1)
/*     a200:	24180140 */ 	li	$t8,0x140
/*     a204:	3c048006 */ 	lui	$a0,0x8006
/*     a208:	00057a80 */ 	sll	$t7,$a1,0xa
/*     a20c:	000f7282 */ 	srl	$t6,$t7,0xa
/*     a210:	29c1012d */ 	slti	$at,$t6,0x12d
/*     a214:	14200002 */ 	bnez	$at,.PF0000a220
/*     a218:	01c02825 */ 	move	$a1,$t6
/*     a21c:	000e2843 */ 	sra	$a1,$t6,0x1
.PF0000a220:
/*     a220:	03053823 */ 	subu	$a3,$t8,$a1
/*     a224:	24ef0002 */ 	addiu	$t7,$a3,0x2
/*     a228:	24b9fffe */ 	addiu	$t9,$a1,-2
/*     a22c:	0019c040 */ 	sll	$t8,$t9,0x1
/*     a230:	000f7400 */ 	sll	$t6,$t7,0x10
/*     a234:	00f87821 */ 	addu	$t7,$a3,$t8
/*     a238:	25f90002 */ 	addiu	$t9,$t7,0x2
/*     a23c:	8c84d22c */ 	lw	$a0,-0x2dd4($a0)
/*     a240:	01d94025 */ 	or	$t0,$t6,$t9
/*     a244:	0008c403 */ 	sra	$t8,$t0,0x10
/*     a248:	330fffff */ 	andi	$t7,$t8,0xffff
/*     a24c:	01e47021 */ 	addu	$t6,$t7,$a0
/*     a250:	01c6001a */ 	div	$zero,$t6,$a2
/*     a254:	14c00002 */ 	bnez	$a2,.PF0000a260
/*     a258:	00000000 */ 	nop
/*     a25c:	0007000d */ 	break	0x7
.PF0000a260:
/*     a260:	2401ffff */ 	li	$at,-1
/*     a264:	14c10004 */ 	bne	$a2,$at,.PF0000a278
/*     a268:	3c018000 */ 	lui	$at,0x8000
/*     a26c:	15c10002 */ 	bne	$t6,$at,.PF0000a278
/*     a270:	00000000 */ 	nop
/*     a274:	0006000d */ 	break	0x6
.PF0000a278:
/*     a278:	310fffff */ 	andi	$t7,$t0,0xffff
/*     a27c:	01e47021 */ 	addu	$t6,$t7,$a0
/*     a280:	0000c810 */ 	mfhi	$t9
/*     a284:	0019c400 */ 	sll	$t8,$t9,0x10
/*     a288:	240f0001 */ 	li	$t7,0x1
/*     a28c:	01c6001a */ 	div	$zero,$t6,$a2
/*     a290:	14c00002 */ 	bnez	$a2,.PF0000a29c
/*     a294:	00000000 */ 	nop
/*     a298:	0007000d */ 	break	0x7
.PF0000a29c:
/*     a29c:	2401ffff */ 	li	$at,-1
/*     a2a0:	14c10004 */ 	bne	$a2,$at,.PF0000a2b4
/*     a2a4:	3c018000 */ 	lui	$at,0x8000
/*     a2a8:	15c10002 */ 	bne	$t6,$at,.PF0000a2b4
/*     a2ac:	00000000 */ 	nop
/*     a2b0:	0006000d */ 	break	0x6
.PF0000a2b4:
/*     a2b4:	0000c810 */ 	mfhi	$t9
/*     a2b8:	03191825 */ 	or	$v1,$t8,$t9
/*     a2bc:	3c018006 */ 	lui	$at,0x8006
/*     a2c0:	ac430030 */ 	sw	$v1,0x30($v0)
/*     a2c4:	ada30000 */ 	sw	$v1,0x0($t5)
/*     a2c8:	ac430044 */ 	sw	$v1,0x44($v0)
/*     a2cc:	afe30000 */ 	sw	$v1,0x0($ra)
/*     a2d0:	002b0821 */ 	addu	$at,$at,$t3
/*     a2d4:	100000dd */ 	b	.PF0000a64c
/*     a2d8:	ac2fcb38 */ 	sw	$t7,-0x34c8($at)
/*     a2dc:	24010002 */ 	li	$at,0x2
.PF0000a2e0:
/*     a2e0:	144100d5 */ 	bne	$v0,$at,.PF0000a638
/*     a2e4:	000c7080 */ 	sll	$t6,$t4,0x2
/*     a2e8:	01cc7021 */ 	addu	$t6,$t6,$t4
/*     a2ec:	3c188009 */ 	lui	$t8,0x8009
/*     a2f0:	2718e210 */ 	addiu	$t8,$t8,-7664
/*     a2f4:	000e7100 */ 	sll	$t6,$t6,0x4
/*     a2f8:	01d81021 */ 	addu	$v0,$t6,$t8
/*     a2fc:	3c198006 */ 	lui	$t9,0x8006
/*     a300:	3c0d8009 */ 	lui	$t5,0x8009
/*     a304:	2739fb90 */ 	addiu	$t9,$t9,-1136
/*     a308:	25ade35c */ 	addiu	$t5,$t5,-7332
/*     a30c:	3406ffff */ 	li	$a2,0xffff
/*     a310:	24080800 */ 	li	$t0,0x800
/*     a314:	272e0048 */ 	addiu	$t6,$t9,0x48
/*     a318:	0040c025 */ 	move	$t8,$v0
.PF0000a31c:
/*     a31c:	8f210000 */ 	lw	$at,0x0($t9)
/*     a320:	2739000c */ 	addiu	$t9,$t9,0xc
/*     a324:	2718000c */ 	addiu	$t8,$t8,0xc
/*     a328:	af01fff4 */ 	sw	$at,-0xc($t8)
/*     a32c:	8f21fff8 */ 	lw	$at,-0x8($t9)
/*     a330:	af01fff8 */ 	sw	$at,-0x8($t8)
/*     a334:	8f21fffc */ 	lw	$at,-0x4($t9)
/*     a338:	172efff8 */ 	bne	$t9,$t6,.PF0000a31c
/*     a33c:	af01fffc */ 	sw	$at,-0x4($t8)
/*     a340:	8f210000 */ 	lw	$at,0x0($t9)
/*     a344:	3c078006 */ 	lui	$a3,0x8006
/*     a348:	3c048006 */ 	lui	$a0,0x8006
/*     a34c:	af010000 */ 	sw	$at,0x0($t8)
/*     a350:	8f2e0004 */ 	lw	$t6,0x4($t9)
/*     a354:	24010280 */ 	li	$at,0x280
/*     a358:	3c1f8009 */ 	lui	$ra,0x8009
/*     a35c:	af0e0004 */ 	sw	$t6,0x4($t8)
/*     a360:	852f0018 */ 	lh	$t7,0x18($t1)
/*     a364:	8c45001c */ 	lw	$a1,0x1c($v0)
/*     a368:	27ffe360 */ 	addiu	$ra,$ra,-7328
/*     a36c:	ac4f0008 */ 	sw	$t7,0x8($v0)
/*     a370:	852e0018 */ 	lh	$t6,0x18($t1)
/*     a374:	ac48002c */ 	sw	$t0,0x2c($v0)
/*     a378:	ac480040 */ 	sw	$t0,0x40($v0)
/*     a37c:	000eca80 */ 	sll	$t9,$t6,0xa
/*     a380:	0321001a */ 	div	$zero,$t9,$at
/*     a384:	0000c012 */ 	mflo	$t8
/*     a388:	ac580020 */ 	sw	$t8,0x20($v0)
/*     a38c:	852f0018 */ 	lh	$t7,0x18($t1)
/*     a390:	3c0a8006 */ 	lui	$t2,0x8006
/*     a394:	000f7040 */ 	sll	$t6,$t7,0x1
/*     a398:	ac4e0028 */ 	sw	$t6,0x28($v0)
/*     a39c:	85390018 */ 	lh	$t9,0x18($t1)
/*     a3a0:	00057c03 */ 	sra	$t7,$a1,0x10
/*     a3a4:	31eeffff */ 	andi	$t6,$t7,0xffff
/*     a3a8:	0019c080 */ 	sll	$t8,$t9,0x2
/*     a3ac:	ac58003c */ 	sw	$t8,0x3c($v0)
/*     a3b0:	8ce7d228 */ 	lw	$a3,-0x2dd8($a3)
/*     a3b4:	01c7c821 */ 	addu	$t9,$t6,$a3
/*     a3b8:	0326001a */ 	div	$zero,$t9,$a2
/*     a3bc:	14c00002 */ 	bnez	$a2,.PF0000a3c8
/*     a3c0:	00000000 */ 	nop
/*     a3c4:	0007000d */ 	break	0x7
.PF0000a3c8:
/*     a3c8:	2401ffff */ 	li	$at,-1
/*     a3cc:	14c10004 */ 	bne	$a2,$at,.PF0000a3e0
/*     a3d0:	3c018000 */ 	lui	$at,0x8000
/*     a3d4:	17210002 */ 	bne	$t9,$at,.PF0000a3e0
/*     a3d8:	00000000 */ 	nop
/*     a3dc:	0006000d */ 	break	0x6
.PF0000a3e0:
/*     a3e0:	30aeffff */ 	andi	$t6,$a1,0xffff
/*     a3e4:	0000c010 */ 	mfhi	$t8
/*     a3e8:	01c7c821 */ 	addu	$t9,$t6,$a3
/*     a3ec:	00187c00 */ 	sll	$t7,$t8,0x10
/*     a3f0:	0326001a */ 	div	$zero,$t9,$a2
/*     a3f4:	14c00002 */ 	bnez	$a2,.PF0000a400
/*     a3f8:	00000000 */ 	nop
/*     a3fc:	0007000d */ 	break	0x7
.PF0000a400:
/*     a400:	2401ffff */ 	li	$at,-1
/*     a404:	14c10004 */ 	bne	$a2,$at,.PF0000a418
/*     a408:	3c018000 */ 	lui	$at,0x8000
/*     a40c:	17210002 */ 	bne	$t9,$at,.PF0000a418
/*     a410:	00000000 */ 	nop
/*     a414:	0006000d */ 	break	0x6
.PF0000a418:
/*     a418:	0000c010 */ 	mfhi	$t8
/*     a41c:	01f81825 */ 	or	$v1,$t7,$t8
/*     a420:	ac43001c */ 	sw	$v1,0x1c($v0)
/*     a424:	3c018009 */ 	lui	$at,0x8009
/*     a428:	ac23e358 */ 	sw	$v1,-0x1ca8($at)
/*     a42c:	8c450030 */ 	lw	$a1,0x30($v0)
/*     a430:	8c84d22c */ 	lw	$a0,-0x2dd4($a0)
/*     a434:	00057403 */ 	sra	$t6,$a1,0x10
/*     a438:	31d9ffff */ 	andi	$t9,$t6,0xffff
/*     a43c:	03247821 */ 	addu	$t7,$t9,$a0
/*     a440:	01e6001a */ 	div	$zero,$t7,$a2
/*     a444:	14c00002 */ 	bnez	$a2,.PF0000a450
/*     a448:	00000000 */ 	nop
/*     a44c:	0007000d */ 	break	0x7
.PF0000a450:
/*     a450:	2401ffff */ 	li	$at,-1
/*     a454:	14c10004 */ 	bne	$a2,$at,.PF0000a468
/*     a458:	3c018000 */ 	lui	$at,0x8000
/*     a45c:	15e10002 */ 	bne	$t7,$at,.PF0000a468
/*     a460:	00000000 */ 	nop
/*     a464:	0006000d */ 	break	0x6
.PF0000a468:
/*     a468:	30b9ffff */ 	andi	$t9,$a1,0xffff
/*     a46c:	03247821 */ 	addu	$t7,$t9,$a0
/*     a470:	0000c010 */ 	mfhi	$t8
/*     a474:	8c450044 */ 	lw	$a1,0x44($v0)
/*     a478:	00187400 */ 	sll	$t6,$t8,0x10
/*     a47c:	01e6001a */ 	div	$zero,$t7,$a2
/*     a480:	14c00002 */ 	bnez	$a2,.PF0000a48c
/*     a484:	00000000 */ 	nop
/*     a488:	0007000d */ 	break	0x7
.PF0000a48c:
/*     a48c:	2401ffff */ 	li	$at,-1
/*     a490:	14c10004 */ 	bne	$a2,$at,.PF0000a4a4
/*     a494:	3c018000 */ 	lui	$at,0x8000
/*     a498:	15e10002 */ 	bne	$t7,$at,.PF0000a4a4
/*     a49c:	00000000 */ 	nop
/*     a4a0:	0006000d */ 	break	0x6
.PF0000a4a4:
/*     a4a4:	0000c010 */ 	mfhi	$t8
/*     a4a8:	0005cc03 */ 	sra	$t9,$a1,0x10
/*     a4ac:	01d81825 */ 	or	$v1,$t6,$t8
/*     a4b0:	332fffff */ 	andi	$t7,$t9,0xffff
/*     a4b4:	01e47021 */ 	addu	$t6,$t7,$a0
/*     a4b8:	01c6001a */ 	div	$zero,$t6,$a2
/*     a4bc:	30afffff */ 	andi	$t7,$a1,0xffff
/*     a4c0:	0000c010 */ 	mfhi	$t8
/*     a4c4:	0018cc00 */ 	sll	$t9,$t8,0x10
/*     a4c8:	ac430030 */ 	sw	$v1,0x30($v0)
/*     a4cc:	ada30000 */ 	sw	$v1,0x0($t5)
/*     a4d0:	14c00002 */ 	bnez	$a2,.PF0000a4dc
/*     a4d4:	00000000 */ 	nop
/*     a4d8:	0007000d */ 	break	0x7
.PF0000a4dc:
/*     a4dc:	2401ffff */ 	li	$at,-1
/*     a4e0:	14c10004 */ 	bne	$a2,$at,.PF0000a4f4
/*     a4e4:	3c018000 */ 	lui	$at,0x8000
/*     a4e8:	15c10002 */ 	bne	$t6,$at,.PF0000a4f4
/*     a4ec:	00000000 */ 	nop
/*     a4f0:	0006000d */ 	break	0x6
.PF0000a4f4:
/*     a4f4:	01e47021 */ 	addu	$t6,$t7,$a0
/*     a4f8:	01c6001a */ 	div	$zero,$t6,$a2
/*     a4fc:	0000c010 */ 	mfhi	$t8
/*     a500:	03381825 */ 	or	$v1,$t9,$t8
/*     a504:	ac430044 */ 	sw	$v1,0x44($v0)
/*     a508:	afe30000 */ 	sw	$v1,0x0($ra)
/*     a50c:	3c0f8006 */ 	lui	$t7,0x8006
/*     a510:	8defd9b8 */ 	lw	$t7,-0x2648($t7)
/*     a514:	14c00002 */ 	bnez	$a2,.PF0000a520
/*     a518:	00000000 */ 	nop
/*     a51c:	0007000d */ 	break	0x7
.PF0000a520:
/*     a520:	2401ffff */ 	li	$at,-1
/*     a524:	14c10004 */ 	bne	$a2,$at,.PF0000a538
/*     a528:	3c018000 */ 	lui	$at,0x8000
/*     a52c:	15c10002 */ 	bne	$t6,$at,.PF0000a538
/*     a530:	00000000 */ 	nop
/*     a534:	0006000d */ 	break	0x6
.PF0000a538:
/*     a538:	248e01fa */ 	addiu	$t6,$a0,0x1fa
/*     a53c:	11e00038 */ 	beqz	$t7,.PF0000a620
/*     a540:	00000000 */ 	nop
/*     a544:	01c6001a */ 	div	$zero,$t6,$a2
/*     a548:	0000c810 */ 	mfhi	$t9
/*     a54c:	248f0086 */ 	addiu	$t7,$a0,0x86
/*     a550:	14c00002 */ 	bnez	$a2,.PF0000a55c
/*     a554:	00000000 */ 	nop
/*     a558:	0007000d */ 	break	0x7
.PF0000a55c:
/*     a55c:	2401ffff */ 	li	$at,-1
/*     a560:	14c10004 */ 	bne	$a2,$at,.PF0000a574
/*     a564:	3c018000 */ 	lui	$at,0x8000
/*     a568:	15c10002 */ 	bne	$t6,$at,.PF0000a574
/*     a56c:	00000000 */ 	nop
/*     a570:	0006000d */ 	break	0x6
.PF0000a574:
/*     a574:	01e6001a */ 	div	$zero,$t7,$a2
/*     a578:	00007010 */ 	mfhi	$t6
/*     a57c:	0019c400 */ 	sll	$t8,$t9,0x10
/*     a580:	249901fc */ 	addiu	$t9,$a0,0x1fc
/*     a584:	0326001a */ 	div	$zero,$t9,$a2
/*     a588:	030e1825 */ 	or	$v1,$t8,$t6
/*     a58c:	248e0084 */ 	addiu	$t6,$a0,0x84
/*     a590:	14c00002 */ 	bnez	$a2,.PF0000a59c
/*     a594:	00000000 */ 	nop
/*     a598:	0007000d */ 	break	0x7
.PF0000a59c:
/*     a59c:	2401ffff */ 	li	$at,-1
/*     a5a0:	14c10004 */ 	bne	$a2,$at,.PF0000a5b4
/*     a5a4:	3c018000 */ 	lui	$at,0x8000
/*     a5a8:	15e10002 */ 	bne	$t7,$at,.PF0000a5b4
/*     a5ac:	00000000 */ 	nop
/*     a5b0:	0006000d */ 	break	0x6
.PF0000a5b4:
/*     a5b4:	00007810 */ 	mfhi	$t7
/*     a5b8:	ac430030 */ 	sw	$v1,0x30($v0)
/*     a5bc:	ada30000 */ 	sw	$v1,0x0($t5)
/*     a5c0:	01c6001a */ 	div	$zero,$t6,$a2
/*     a5c4:	14c00002 */ 	bnez	$a2,.PF0000a5d0
/*     a5c8:	00000000 */ 	nop
/*     a5cc:	0007000d */ 	break	0x7
.PF0000a5d0:
/*     a5d0:	2401ffff */ 	li	$at,-1
/*     a5d4:	14c10004 */ 	bne	$a2,$at,.PF0000a5e8
/*     a5d8:	3c018000 */ 	lui	$at,0x8000
/*     a5dc:	17210002 */ 	bne	$t9,$at,.PF0000a5e8
/*     a5e0:	00000000 */ 	nop
/*     a5e4:	0006000d */ 	break	0x6
.PF0000a5e8:
/*     a5e8:	0000c810 */ 	mfhi	$t9
/*     a5ec:	000fc400 */ 	sll	$t8,$t7,0x10
/*     a5f0:	03191825 */ 	or	$v1,$t8,$t9
/*     a5f4:	ac430044 */ 	sw	$v1,0x44($v0)
/*     a5f8:	afe30000 */ 	sw	$v1,0x0($ra)
/*     a5fc:	14c00002 */ 	bnez	$a2,.PF0000a608
/*     a600:	00000000 */ 	nop
/*     a604:	0007000d */ 	break	0x7
.PF0000a608:
/*     a608:	2401ffff */ 	li	$at,-1
/*     a60c:	14c10004 */ 	bne	$a2,$at,.PF0000a620
/*     a610:	3c018000 */ 	lui	$at,0x8000
/*     a614:	15c10002 */ 	bne	$t6,$at,.PF0000a620
/*     a618:	00000000 */ 	nop
/*     a61c:	0006000d */ 	break	0x6
.PF0000a620:
/*     a620:	3c018006 */ 	lui	$at,0x8006
/*     a624:	002b0821 */ 	addu	$at,$at,$t3
/*     a628:	240f0001 */ 	li	$t7,0x1
/*     a62c:	ac2fcb38 */ 	sw	$t7,-0x34c8($at)
/*     a630:	10000006 */ 	b	.PF0000a64c
/*     a634:	8d4ad238 */ 	lw	$t2,-0x2dc8($t2)
.PF0000a638:
/*     a638:	3c018006 */ 	lui	$at,0x8006
/*     a63c:	002b0821 */ 	addu	$at,$at,$t3
/*     a640:	3c0a8006 */ 	lui	$t2,0x8006
/*     a644:	8d4ad238 */ 	lw	$t2,-0x2dc8($t2)
/*     a648:	ac20cb38 */ 	sw	$zero,-0x34c8($at)
.PF0000a64c:
/*     a64c:	258c0001 */ 	addiu	$t4,$t4,0x1
/*     a650:	05810004 */ 	bgez	$t4,.PF0000a664
/*     a654:	318e0001 */ 	andi	$t6,$t4,0x1
/*     a658:	11c00002 */ 	beqz	$t6,.PF0000a664
/*     a65c:	00000000 */ 	nop
/*     a660:	25cefffe */ 	addiu	$t6,$t6,-2
.PF0000a664:
/*     a664:	3c018006 */ 	lui	$at,0x8006
/*     a668:	11400006 */ 	beqz	$t2,.PF0000a684
/*     a66c:	ac2ed240 */ 	sw	$t6,-0x2dc0($at)
/*     a670:	3c198006 */ 	lui	$t9,0x8006
/*     a674:	8f39edb8 */ 	lw	$t9,-0x1248($t9)
/*     a678:	8d380028 */ 	lw	$t8,0x28($t1)
/*     a67c:	10000006 */ 	b	.PF0000a698
/*     a680:	af380058 */ 	sw	$t8,0x58($t9)
.PF0000a684:
/*     a684:	3c0f800a */ 	lui	$t7,0x800a
/*     a688:	3c0e8006 */ 	lui	$t6,0x8006
/*     a68c:	8dceedb8 */ 	lw	$t6,-0x1248($t6)
/*     a690:	8defd020 */ 	lw	$t7,-0x2fe0($t7)
/*     a694:	adcf0058 */ 	sw	$t7,0x58($t6)
.PF0000a698:
/*     a698:	3c028009 */ 	lui	$v0,0x8009
/*     a69c:	24422dc6 */ 	addiu	$v0,$v0,0x2dc6
/*     a6a0:	90580000 */ 	lbu	$t8,0x0($v0)
/*     a6a4:	3c048006 */ 	lui	$a0,0x8006
/*     a6a8:	8c84d234 */ 	lw	$a0,-0x2dcc($a0)
/*     a6ac:	27190001 */ 	addiu	$t9,$t8,0x1
/*     a6b0:	3c038009 */ 	lui	$v1,0x8009
/*     a6b4:	2408002c */ 	li	$t0,0x2c
/*     a6b8:	24632dc7 */ 	addiu	$v1,$v1,0x2dc7
/*     a6bc:	906e0000 */ 	lbu	$t6,0x0($v1)
/*     a6c0:	3c078006 */ 	lui	$a3,0x8006
/*     a6c4:	24e7d1d0 */ 	addiu	$a3,$a3,-11824
/*     a6c8:	07210004 */ 	bgez	$t9,.PF0000a6dc
/*     a6cc:	332f0001 */ 	andi	$t7,$t9,0x1
/*     a6d0:	11e00002 */ 	beqz	$t7,.PF0000a6dc
/*     a6d4:	00000000 */ 	nop
/*     a6d8:	25effffe */ 	addiu	$t7,$t7,-2
.PF0000a6dc:
/*     a6dc:	a04f0000 */ 	sb	$t7,0x0($v0)
/*     a6e0:	904f0000 */ 	lbu	$t7,0x0($v0)
/*     a6e4:	25d80001 */ 	addiu	$t8,$t6,0x1
/*     a6e8:	07010004 */ 	bgez	$t8,.PF0000a6fc
/*     a6ec:	33190001 */ 	andi	$t9,$t8,0x1
/*     a6f0:	13200002 */ 	beqz	$t9,.PF0000a6fc
/*     a6f4:	00000000 */ 	nop
/*     a6f8:	2739fffe */ 	addiu	$t9,$t9,-2
.PF0000a6fc:
/*     a6fc:	01e80019 */ 	multu	$t7,$t0
/*     a700:	a0790000 */ 	sb	$t9,0x0($v1)
/*     a704:	3c018006 */ 	lui	$at,0x8006
/*     a708:	3c058006 */ 	lui	$a1,0x8006
/*     a70c:	2406002c */ 	li	$a2,0x2c
/*     a710:	00007012 */ 	mflo	$t6
/*     a714:	00eec021 */ 	addu	$t8,$a3,$t6
/*     a718:	ac38d230 */ 	sw	$t8,-0x2dd0($at)
/*     a71c:	90790000 */ 	lbu	$t9,0x0($v1)
/*     a720:	3c018006 */ 	lui	$at,0x8006
/*     a724:	03280019 */ 	multu	$t9,$t0
/*     a728:	00007812 */ 	mflo	$t7
/*     a72c:	00ef7021 */ 	addu	$t6,$a3,$t7
/*     a730:	ac2ed234 */ 	sw	$t6,-0x2dcc($at)
/*     a734:	0c0129ec */ 	jal	bcopy
/*     a738:	8ca5d234 */ 	lw	$a1,-0x2dcc($a1)
/*     a73c:	3c038009 */ 	lui	$v1,0x8009
/*     a740:	24632dc7 */ 	addiu	$v1,$v1,0x2dc7
/*     a744:	90780000 */ 	lbu	$t8,0x0($v1)
/*     a748:	3c0f800a */ 	lui	$t7,0x800a
/*     a74c:	3c0e8006 */ 	lui	$t6,0x8006
/*     a750:	0018c880 */ 	sll	$t9,$t8,0x2
/*     a754:	01f97821 */ 	addu	$t7,$t7,$t9
/*     a758:	8defd020 */ 	lw	$t7,-0x2fe0($t7)
/*     a75c:	8dced234 */ 	lw	$t6,-0x2dcc($t6)
/*     a760:	3c028006 */ 	lui	$v0,0x8006
/*     a764:	2442d23c */ 	addiu	$v0,$v0,-11716
/*     a768:	adcf0028 */ 	sw	$t7,0x28($t6)
/*     a76c:	8c580000 */ 	lw	$t8,0x0($v0)
/*     a770:	53000005 */ 	beqzl	$t8,.PF0000a788
/*     a774:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     a778:	ac400000 */ 	sw	$zero,0x0($v0)
/*     a77c:	0c002779 */ 	jal	func00009ec4
/*     a780:	00002025 */ 	move	$a0,$zero
/*     a784:	8fbf0014 */ 	lw	$ra,0x14($sp)
.PF0000a788:
/*     a788:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*     a78c:	03e00008 */ 	jr	$ra
/*     a790:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel func0000a044
/*     a044:	3c098006 */ 	lui	$t1,%hi(g_ViData)
/*     a048:	3c0e8006 */ 	lui	$t6,%hi(var8005d590)
/*     a04c:	8dced590 */ 	lw	$t6,%lo(var8005d590)($t6)
/*     a050:	8d29d594 */ 	lw	$t1,%lo(g_ViData)($t1)
/*     a054:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*     a058:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     a05c:	91cf0000 */ 	lbu	$t7,0x0($t6)
/*     a060:	91230000 */ 	lbu	$v1,0x0($t1)
/*     a064:	506f0014 */ 	beql	$v1,$t7,.L0000a0b8
/*     a068:	85380004 */ 	lh	$t8,0x4($t1)
/*     a06c:	10600008 */ 	beqz	$v1,.L0000a090
/*     a070:	00601025 */ 	or	$v0,$v1,$zero
/*     a074:	241f0001 */ 	addiu	$ra,$zero,0x1
/*     a078:	107f000e */ 	beq	$v1,$ra,.L0000a0b4
/*     a07c:	24040002 */ 	addiu	$a0,$zero,0x2
/*     a080:	5044000d */ 	beql	$v0,$a0,.L0000a0b8
/*     a084:	85380004 */ 	lh	$t8,0x4($t1)
/*     a088:	1000000b */ 	b	.L0000a0b8
/*     a08c:	85380004 */ 	lh	$t8,0x4($t1)
.L0000a090:
/*     a090:	3c013f80 */ 	lui	$at,0x3f80
/*     a094:	44816000 */ 	mtc1	$at,$f12
/*     a098:	0c0123bc */ 	jal	osViSetYScale
/*     a09c:	00000000 */ 	nop
/*     a0a0:	0c012338 */ 	jal	osViBlack
/*     a0a4:	24040001 */ 	addiu	$a0,$zero,0x1
/*     a0a8:	3c098006 */ 	lui	$t1,%hi(g_ViData)
/*     a0ac:	8d29d594 */ 	lw	$t1,%lo(g_ViData)($t1)
/*     a0b0:	91230000 */ 	lbu	$v1,0x0($t1)
.L0000a0b4:
/*     a0b4:	85380004 */ 	lh	$t8,0x4($t1)
.L0000a0b8:
/*     a0b8:	85390018 */ 	lh	$t9,0x18($t1)
/*     a0bc:	852e0006 */ 	lh	$t6,0x6($t1)
/*     a0c0:	44982000 */ 	mtc1	$t8,$f4
/*     a0c4:	852f001a */ 	lh	$t7,0x1a($t1)
/*     a0c8:	44994000 */ 	mtc1	$t9,$f8
/*     a0cc:	468021a0 */ 	cvt.s.w	$f6,$f4
/*     a0d0:	448e8000 */ 	mtc1	$t6,$f16
/*     a0d4:	448f2000 */ 	mtc1	$t7,$f4
/*     a0d8:	24040002 */ 	addiu	$a0,$zero,0x2
/*     a0dc:	241f0001 */ 	addiu	$ra,$zero,0x1
/*     a0e0:	468042a0 */ 	cvt.s.w	$f10,$f8
/*     a0e4:	3c0b8006 */ 	lui	$t3,%hi(var8005d5a0)
/*     a0e8:	3c013f80 */ 	lui	$at,0x3f80
/*     a0ec:	468084a0 */ 	cvt.s.w	$f18,$f16
/*     a0f0:	46802220 */ 	cvt.s.w	$f8,$f4
/*     a0f4:	460a3083 */ 	div.s	$f2,$f6,$f10
/*     a0f8:	14600003 */ 	bnez	$v1,.L0000a108
/*     a0fc:	46089003 */ 	div.s	$f0,$f18,$f8
/*     a100:	44810000 */ 	mtc1	$at,$f0
/*     a104:	00000000 */ 	nop
.L0000a108:
/*     a108:	8d6bd5a0 */ 	lw	$t3,%lo(var8005d5a0)($t3)
/*     a10c:	3c018006 */ 	lui	$at,%hi(var8005ce78)
/*     a110:	000b6080 */ 	sll	$t4,$t3,0x2
/*     a114:	002c0821 */ 	addu	$at,$at,$t4
/*     a118:	e422ce78 */ 	swc1	$f2,%lo(var8005ce78)($at)
/*     a11c:	3c018006 */ 	lui	$at,%hi(var8005ce80)
/*     a120:	002c0821 */ 	addu	$at,$at,$t4
/*     a124:	e420ce80 */ 	swc1	$f0,%lo(var8005ce80)($at)
/*     a128:	91230000 */ 	lbu	$v1,0x0($t1)
/*     a12c:	17e30101 */ 	bne	$ra,$v1,.L0000a534
/*     a130:	00000000 */ 	nop
/*     a134:	3c0a8006 */ 	lui	$t2,%hi(var8005d598)
/*     a138:	8d4ad598 */ 	lw	$t2,%lo(var8005d598)($t2)
/*     a13c:	3c188000 */ 	lui	$t8,0x8000
/*     a140:	11400033 */ 	beqz	$t2,.L0000a210
/*     a144:	00000000 */ 	nop
/*     a148:	8f180300 */ 	lw	$t8,0x300($t8)
/*     a14c:	3c198009 */ 	lui	$t9,%hi(var8008dcc0)
/*     a150:	2739dcc0 */ 	addiu	$t9,$t9,%lo(var8008dcc0)
/*     a154:	14980019 */ 	bne	$a0,$t8,.L0000a1bc
/*     a158:	3c0f8006 */ 	lui	$t7,%hi(osViModeTable+0xa0)
/*     a15c:	000bc880 */ 	sll	$t9,$t3,0x2
/*     a160:	032bc821 */ 	addu	$t9,$t9,$t3
/*     a164:	3c0e8009 */ 	lui	$t6,%hi(var8008dcc0)
/*     a168:	25cedcc0 */ 	addiu	$t6,$t6,%lo(var8008dcc0)
/*     a16c:	0019c900 */ 	sll	$t9,$t9,0x4
/*     a170:	032e2021 */ 	addu	$a0,$t9,$t6
/*     a174:	3c0f8006 */ 	lui	$t7,%hi(osViModeTable+0x960)
/*     a178:	25ef0070 */ 	addiu	$t7,$t7,%lo(osViModeTable+0x960)
/*     a17c:	25f90048 */ 	addiu	$t9,$t7,0x48
/*     a180:	00807025 */ 	or	$t6,$a0,$zero
.L0000a184:
/*     a184:	8de10000 */ 	lw	$at,0x0($t7)
/*     a188:	25ef000c */ 	addiu	$t7,$t7,12
/*     a18c:	25ce000c */ 	addiu	$t6,$t6,12
/*     a190:	adc1fff4 */ 	sw	$at,-0xc($t6)
/*     a194:	8de1fff8 */ 	lw	$at,-0x8($t7)
/*     a198:	adc1fff8 */ 	sw	$at,-0x8($t6)
/*     a19c:	8de1fffc */ 	lw	$at,-0x4($t7)
/*     a1a0:	15f9fff8 */ 	bne	$t7,$t9,.L0000a184
/*     a1a4:	adc1fffc */ 	sw	$at,-0x4($t6)
/*     a1a8:	8de10000 */ 	lw	$at,0x0($t7)
/*     a1ac:	adc10000 */ 	sw	$at,0x0($t6)
/*     a1b0:	8df90004 */ 	lw	$t9,0x4($t7)
/*     a1b4:	10000048 */ 	b	.L0000a2d8
/*     a1b8:	add90004 */ 	sw	$t9,0x4($t6)
.L0000a1bc:
/*     a1bc:	000bc080 */ 	sll	$t8,$t3,0x2
/*     a1c0:	030bc021 */ 	addu	$t8,$t8,$t3
/*     a1c4:	0018c100 */ 	sll	$t8,$t8,0x4
/*     a1c8:	03192021 */ 	addu	$a0,$t8,$t9
/*     a1cc:	25eff7b0 */ 	addiu	$t7,$t7,%lo(osViModeTable+0xa0)
/*     a1d0:	25f80048 */ 	addiu	$t8,$t7,0x48
/*     a1d4:	0080c825 */ 	or	$t9,$a0,$zero
.L0000a1d8:
/*     a1d8:	8de10000 */ 	lw	$at,0x0($t7)
/*     a1dc:	25ef000c */ 	addiu	$t7,$t7,0xc
/*     a1e0:	2739000c */ 	addiu	$t9,$t9,0xc
/*     a1e4:	af21fff4 */ 	sw	$at,-0xc($t9)
/*     a1e8:	8de1fff8 */ 	lw	$at,-0x8($t7)
/*     a1ec:	af21fff8 */ 	sw	$at,-0x8($t9)
/*     a1f0:	8de1fffc */ 	lw	$at,-0x4($t7)
/*     a1f4:	15f8fff8 */ 	bne	$t7,$t8,.L0000a1d8
/*     a1f8:	af21fffc */ 	sw	$at,-0x4($t9)
/*     a1fc:	8de10000 */ 	lw	$at,0x0($t7)
/*     a200:	af210000 */ 	sw	$at,0x0($t9)
/*     a204:	8df80004 */ 	lw	$t8,0x4($t7)
/*     a208:	10000033 */ 	b	.L0000a2d8
/*     a20c:	af380004 */ 	sw	$t8,0x4($t9)
.L0000a210:
/*     a210:	3c0e8000 */ 	lui	$t6,0x8000
/*     a214:	8dce0300 */ 	lw	$t6,0x300($t6)
/*     a218:	148e0018 */ 	bne	$a0,$t6,.L0000a27c
/*     a21c:	000bc080 */ 	sll	$t8,$t3,0x2
/*     a220:	030bc021 */ 	addu	$t8,$t8,$t3
/*     a224:	3c0f8009 */ 	lui	$t7,%hi(var8008dcc0)
/*     a228:	25efdcc0 */ 	addiu	$t7,$t7,%lo(var8008dcc0)
/*     a22c:	0018c100 */ 	sll	$t8,$t8,0x4
/*     a230:	030f2021 */ 	addu	$a0,$t8,$t7
/*     a234:	3c198006 */ 	lui	$t9,%hi(osViModeTable+0xaa0)
/*     a238:	273901b0 */ 	addiu	$t9,$t9,%lo(osViModeTable+0xaa0)
/*     a23c:	27380048 */ 	addiu	$t8,$t9,0x48
/*     a240:	00807825 */ 	or	$t7,$a0,$zero
.L0000a244:
/*     a244:	8f210000 */ 	lw	$at,0x0($t9)
/*     a248:	2739000c */ 	addiu	$t9,$t9,0xc
/*     a24c:	25ef000c */ 	addiu	$t7,$t7,0xc
/*     a250:	ade1fff4 */ 	sw	$at,-0xc($t7)
/*     a254:	8f21fff8 */ 	lw	$at,-0x8($t9)
/*     a258:	ade1fff8 */ 	sw	$at,-0x8($t7)
/*     a25c:	8f21fffc */ 	lw	$at,-0x4($t9)
/*     a260:	1738fff8 */ 	bne	$t9,$t8,.L0000a244
/*     a264:	ade1fffc */ 	sw	$at,-0x4($t7)
/*     a268:	8f210000 */ 	lw	$at,0x0($t9)
/*     a26c:	ade10000 */ 	sw	$at,0x0($t7)
/*     a270:	8f380004 */ 	lw	$t8,0x4($t9)
/*     a274:	10000018 */ 	b	.L0000a2d8
/*     a278:	adf80004 */ 	sw	$t8,0x4($t7)
.L0000a27c:
/*     a27c:	000b7080 */ 	sll	$t6,$t3,0x2
/*     a280:	01cb7021 */ 	addu	$t6,$t6,$t3
/*     a284:	3c188009 */ 	lui	$t8,%hi(var8008dcc0)
/*     a288:	2718dcc0 */ 	addiu	$t8,$t8,%lo(var8008dcc0)
/*     a28c:	000e7100 */ 	sll	$t6,$t6,0x4
/*     a290:	01d82021 */ 	addu	$a0,$t6,$t8
/*     a294:	3c198006 */ 	lui	$t9,%hi(osViModeTable+0x1e0)
/*     a298:	2739f8f0 */ 	addiu	$t9,$t9,%lo(osViModeTable+0x1e0)
/*     a29c:	272e0048 */ 	addiu	$t6,$t9,0x48
/*     a2a0:	0080c025 */ 	or	$t8,$a0,$zero
.L0000a2a4:
/*     a2a4:	8f210000 */ 	lw	$at,0x0($t9)
/*     a2a8:	2739000c */ 	addiu	$t9,$t9,0xc
/*     a2ac:	2718000c */ 	addiu	$t8,$t8,0xc
/*     a2b0:	af01fff4 */ 	sw	$at,-0xc($t8)
/*     a2b4:	8f21fff8 */ 	lw	$at,-0x8($t9)
/*     a2b8:	af01fff8 */ 	sw	$at,-0x8($t8)
/*     a2bc:	8f21fffc */ 	lw	$at,-0x4($t9)
/*     a2c0:	172efff8 */ 	bne	$t9,$t6,.L0000a2a4
/*     a2c4:	af01fffc */ 	sw	$at,-0x4($t8)
/*     a2c8:	8f210000 */ 	lw	$at,0x0($t9)
/*     a2cc:	af010000 */ 	sw	$at,0x0($t8)
/*     a2d0:	8f2e0004 */ 	lw	$t6,0x4($t9)
/*     a2d4:	af0e0004 */ 	sw	$t6,0x4($t8)
.L0000a2d8:
/*     a2d8:	852f0018 */ 	lh	$t7,0x18($t1)
/*     a2dc:	24010280 */ 	addiu	$at,$zero,0x280
/*     a2e0:	3c0d8009 */ 	lui	$t5,%hi(var8008de0c)
/*     a2e4:	ac8f0008 */ 	sw	$t7,0x8($a0)
/*     a2e8:	852e0018 */ 	lh	$t6,0x18($t1)
/*     a2ec:	3406ffff */ 	dli	$a2,0xffff
/*     a2f0:	25adde0c */ 	addiu	$t5,$t5,%lo(var8008de0c)
/*     a2f4:	000eca80 */ 	sll	$t9,$t6,0xa
/*     a2f8:	0321001a */ 	div	$zero,$t9,$at
/*     a2fc:	0000c012 */ 	mflo	$t8
/*     a300:	ac980020 */ 	sw	$t8,0x20($a0)
/*     a304:	852f0018 */ 	lh	$t7,0x18($t1)
/*     a308:	000f7040 */ 	sll	$t6,$t7,0x1
/*     a30c:	ac8e0028 */ 	sw	$t6,0x28($a0)
/*     a310:	85390018 */ 	lh	$t9,0x18($t1)
/*     a314:	3c0f8009 */ 	lui	$t7,%hi(g_Is4Mb)
/*     a318:	0019c040 */ 	sll	$t8,$t9,0x1
/*     a31c:	ac98003c */ 	sw	$t8,0x3c($a0)
/*     a320:	91ef0af0 */ 	lbu	$t7,%lo(g_Is4Mb)($t7)
/*     a324:	17ef0004 */ 	bne	$ra,$t7,.L0000a338
/*     a328:	24020400 */ 	addiu	$v0,$zero,0x400
/*     a32c:	ac82002c */ 	sw	$v0,0x2c($a0)
/*     a330:	1000001e */ 	b	.L0000a3ac
/*     a334:	ac820040 */ 	sw	$v0,0x40($a0)
.L0000a338:
/*     a338:	852e001a */ 	lh	$t6,0x1a($t1)
/*     a33c:	240201b8 */ 	addiu	$v0,$zero,0x1b8
/*     a340:	000ecac0 */ 	sll	$t9,$t6,0xb
/*     a344:	0322001a */ 	div	$zero,$t9,$v0
/*     a348:	0000c012 */ 	mflo	$t8
/*     a34c:	ac98002c */ 	sw	$t8,0x2c($a0)
/*     a350:	852f001a */ 	lh	$t7,0x1a($t1)
/*     a354:	14400002 */ 	bnez	$v0,.L0000a360
/*     a358:	00000000 */ 	nop
/*     a35c:	0007000d */ 	break	0x7
.L0000a360:
/*     a360:	2401ffff */ 	addiu	$at,$zero,-1
/*     a364:	14410004 */ 	bne	$v0,$at,.L0000a378
/*     a368:	3c018000 */ 	lui	$at,0x8000
/*     a36c:	17210002 */ 	bne	$t9,$at,.L0000a378
/*     a370:	00000000 */ 	nop
/*     a374:	0006000d */ 	break	0x6
.L0000a378:
/*     a378:	000f72c0 */ 	sll	$t6,$t7,0xb
/*     a37c:	01c2001a */ 	div	$zero,$t6,$v0
/*     a380:	0000c812 */ 	mflo	$t9
/*     a384:	ac990040 */ 	sw	$t9,0x40($a0)
/*     a388:	14400002 */ 	bnez	$v0,.L0000a394
/*     a38c:	00000000 */ 	nop
/*     a390:	0007000d */ 	break	0x7
.L0000a394:
/*     a394:	2401ffff */ 	addiu	$at,$zero,-1
/*     a398:	14410004 */ 	bne	$v0,$at,.L0000a3ac
/*     a39c:	3c018000 */ 	lui	$at,0x8000
/*     a3a0:	15c10002 */ 	bne	$t6,$at,.L0000a3ac
/*     a3a4:	00000000 */ 	nop
/*     a3a8:	0006000d */ 	break	0x6
.L0000a3ac:
/*     a3ac:	8c85001c */ 	lw	$a1,0x1c($a0)
/*     a3b0:	3c078006 */ 	lui	$a3,%hi(var8005d588)
/*     a3b4:	8ce7d588 */ 	lw	$a3,%lo(var8005d588)($a3)
/*     a3b8:	0005c403 */ 	sra	$t8,$a1,0x10
/*     a3bc:	330fffff */ 	andi	$t7,$t8,0xffff
/*     a3c0:	01e77021 */ 	addu	$t6,$t7,$a3
/*     a3c4:	01c6001a */ 	div	$zero,$t6,$a2
/*     a3c8:	14c00002 */ 	bnez	$a2,.L0000a3d4
/*     a3cc:	00000000 */ 	nop
/*     a3d0:	0007000d */ 	break	0x7
.L0000a3d4:
/*     a3d4:	2401ffff */ 	addiu	$at,$zero,-1
/*     a3d8:	14c10004 */ 	bne	$a2,$at,.L0000a3ec
/*     a3dc:	3c018000 */ 	lui	$at,0x8000
/*     a3e0:	15c10002 */ 	bne	$t6,$at,.L0000a3ec
/*     a3e4:	00000000 */ 	nop
/*     a3e8:	0006000d */ 	break	0x6
.L0000a3ec:
/*     a3ec:	30afffff */ 	andi	$t7,$a1,0xffff
/*     a3f0:	01e77021 */ 	addu	$t6,$t7,$a3
/*     a3f4:	0000c810 */ 	mfhi	$t9
/*     a3f8:	0019c400 */ 	sll	$t8,$t9,0x10
/*     a3fc:	3c1f8009 */ 	lui	$ra,%hi(var8008de10)
/*     a400:	01c6001a */ 	div	$zero,$t6,$a2
/*     a404:	14c00002 */ 	bnez	$a2,.L0000a410
/*     a408:	00000000 */ 	nop
/*     a40c:	0007000d */ 	break	0x7
.L0000a410:
/*     a410:	2401ffff */ 	addiu	$at,$zero,-1
/*     a414:	14c10004 */ 	bne	$a2,$at,.L0000a428
/*     a418:	3c018000 */ 	lui	$at,0x8000
/*     a41c:	15c10002 */ 	bne	$t6,$at,.L0000a428
/*     a420:	00000000 */ 	nop
/*     a424:	0006000d */ 	break	0x6
.L0000a428:
/*     a428:	0000c810 */ 	mfhi	$t9
/*     a42c:	03191025 */ 	or	$v0,$t8,$t9
/*     a430:	ac82001c */ 	sw	$v0,0x1c($a0)
/*     a434:	3c018009 */ 	lui	$at,%hi(var8008de08)
/*     a438:	ac22de08 */ 	sw	$v0,%lo(var8008de08)($at)
/*     a43c:	8523001a */ 	lh	$v1,0x1a($t1)
/*     a440:	8c8e002c */ 	lw	$t6,0x2c($a0)
/*     a444:	27ffde10 */ 	addiu	$ra,$ra,%lo(var8008de10)
/*     a448:	00037a80 */ 	sll	$t7,$v1,0xa
/*     a44c:	01ee001b */ 	divu	$zero,$t7,$t6
/*     a450:	00001812 */ 	mflo	$v1
/*     a454:	2861012d */ 	slti	$at,$v1,0x12d
/*     a458:	15c00002 */ 	bnez	$t6,.L0000a464
/*     a45c:	00000000 */ 	nop
/*     a460:	0007000d */ 	break	0x7
.L0000a464:
/*     a464:	24190115 */ 	addiu	$t9,$zero,0x115
/*     a468:	14200003 */ 	bnez	$at,.L0000a478
/*     a46c:	3c058006 */ 	lui	$a1,%hi(var8005d58c)
/*     a470:	0003c043 */ 	sra	$t8,$v1,0x1
/*     a474:	03001825 */ 	or	$v1,$t8,$zero
.L0000a478:
/*     a478:	03233823 */ 	subu	$a3,$t9,$v1
/*     a47c:	24ef0002 */ 	addiu	$t7,$a3,0x2
/*     a480:	2478fffe */ 	addiu	$t8,$v1,-2
/*     a484:	0018c840 */ 	sll	$t9,$t8,0x1
/*     a488:	000f7400 */ 	sll	$t6,$t7,0x10
/*     a48c:	00f97821 */ 	addu	$t7,$a3,$t9
/*     a490:	25f80002 */ 	addiu	$t8,$t7,0x2
/*     a494:	8ca5d58c */ 	lw	$a1,%lo(var8005d58c)($a1)
/*     a498:	01d84025 */ 	or	$t0,$t6,$t8
/*     a49c:	0008cc03 */ 	sra	$t9,$t0,0x10
/*     a4a0:	332fffff */ 	andi	$t7,$t9,0xffff
/*     a4a4:	01e57021 */ 	addu	$t6,$t7,$a1
/*     a4a8:	01c6001a */ 	div	$zero,$t6,$a2
/*     a4ac:	14c00002 */ 	bnez	$a2,.L0000a4b8
/*     a4b0:	00000000 */ 	nop
/*     a4b4:	0007000d */ 	break	0x7
.L0000a4b8:
/*     a4b8:	2401ffff */ 	addiu	$at,$zero,-1
/*     a4bc:	14c10004 */ 	bne	$a2,$at,.L0000a4d0
/*     a4c0:	3c018000 */ 	lui	$at,0x8000
/*     a4c4:	15c10002 */ 	bne	$t6,$at,.L0000a4d0
/*     a4c8:	00000000 */ 	nop
/*     a4cc:	0006000d */ 	break	0x6
.L0000a4d0:
/*     a4d0:	310fffff */ 	andi	$t7,$t0,0xffff
/*     a4d4:	01e57021 */ 	addu	$t6,$t7,$a1
/*     a4d8:	0000c010 */ 	mfhi	$t8
/*     a4dc:	0018cc00 */ 	sll	$t9,$t8,0x10
/*     a4e0:	240f0001 */ 	addiu	$t7,$zero,0x1
/*     a4e4:	01c6001a */ 	div	$zero,$t6,$a2
/*     a4e8:	14c00002 */ 	bnez	$a2,.L0000a4f4
/*     a4ec:	00000000 */ 	nop
/*     a4f0:	0007000d */ 	break	0x7
.L0000a4f4:
/*     a4f4:	2401ffff */ 	addiu	$at,$zero,-1
/*     a4f8:	14c10004 */ 	bne	$a2,$at,.L0000a50c
/*     a4fc:	3c018000 */ 	lui	$at,0x8000
/*     a500:	15c10002 */ 	bne	$t6,$at,.L0000a50c
/*     a504:	00000000 */ 	nop
/*     a508:	0006000d */ 	break	0x6
.L0000a50c:
/*     a50c:	0000c010 */ 	mfhi	$t8
/*     a510:	03381025 */ 	or	$v0,$t9,$t8
/*     a514:	3c018006 */ 	lui	$at,%hi(var8005ce88)
/*     a518:	ac820030 */ 	sw	$v0,0x30($a0)
/*     a51c:	ada20000 */ 	sw	$v0,0x0($t5)
/*     a520:	ac820044 */ 	sw	$v0,0x44($a0)
/*     a524:	afe20000 */ 	sw	$v0,0x0($ra)
/*     a528:	002c0821 */ 	addu	$at,$at,$t4
/*     a52c:	100000f6 */ 	b	.L0000a908
/*     a530:	ac2fce88 */ 	sw	$t7,%lo(var8005ce88)($at)
.L0000a534:
/*     a534:	148300ef */ 	bne	$a0,$v1,.L0000a8f4
/*     a538:	3c0e8000 */ 	lui	$t6,0x8000
/*     a53c:	8dce0300 */ 	lw	$t6,0x300($t6)
/*     a540:	3406ffff */ 	dli	$a2,0xffff
/*     a544:	24080800 */ 	addiu	$t0,$zero,0x800
/*     a548:	148e0019 */ 	bne	$a0,$t6,.L0000a5b0
/*     a54c:	3c0d8009 */ 	lui	$t5,%hi(var8008de0c)
/*     a550:	000bc880 */ 	sll	$t9,$t3,0x2
/*     a554:	032bc821 */ 	addu	$t9,$t9,$t3
/*     a558:	3c188009 */ 	lui	$t8,%hi(var8008dcc0)
/*     a55c:	2718dcc0 */ 	addiu	$t8,$t8,%lo(var8008dcc0)
/*     a560:	0019c900 */ 	sll	$t9,$t9,0x4
/*     a564:	03382021 */ 	addu	$a0,$t9,$t8
/*     a568:	3c0f8006 */ 	lui	$t7,%hi(osViModeTable+0xc30)
/*     a56c:	25ef0340 */ 	addiu	$t7,$t7,%lo(osViModeTable+0xc30)
/*     a570:	25f90048 */ 	addiu	$t9,$t7,0x48
/*     a574:	0080c025 */ 	or	$t8,$a0,$zero
.L0000a578:
/*     a578:	8de10000 */ 	lw	$at,0x0($t7)
/*     a57c:	25ef000c */ 	addiu	$t7,$t7,12
/*     a580:	2718000c */ 	addiu	$t8,$t8,0xc
/*     a584:	af01fff4 */ 	sw	$at,-0xc($t8)
/*     a588:	8de1fff8 */ 	lw	$at,-0x8($t7)
/*     a58c:	af01fff8 */ 	sw	$at,-0x8($t8)
/*     a590:	8de1fffc */ 	lw	$at,-0x4($t7)
/*     a594:	15f9fff8 */ 	bne	$t7,$t9,.L0000a578
/*     a598:	af01fffc */ 	sw	$at,-0x4($t8)
/*     a59c:	8de10000 */ 	lw	$at,0x0($t7)
/*     a5a0:	af010000 */ 	sw	$at,0x0($t8)
/*     a5a4:	8df90004 */ 	lw	$t9,0x4($t7)
/*     a5a8:	10000018 */ 	b	.L0000a60c
/*     a5ac:	af190004 */ 	sw	$t9,0x4($t8)
.L0000a5b0:
/*     a5b0:	000b7080 */ 	sll	$t6,$t3,0x2
/*     a5b4:	01cb7021 */ 	addu	$t6,$t6,$t3
/*     a5b8:	3c198009 */ 	lui	$t9,%hi(var8008dcc0)
/*     a5bc:	2739dcc0 */ 	addiu	$t9,$t9,%lo(var8008dcc0)
/*     a5c0:	000e7100 */ 	sll	$t6,$t6,0x4
/*     a5c4:	01d92021 */ 	addu	$a0,$t6,$t9
/*     a5c8:	3c0f8006 */ 	lui	$t7,%hi(osViModeTable+0x370)
/*     a5cc:	25effa80 */ 	addiu	$t7,$t7,%lo(osViModeTable+0x370)
/*     a5d0:	25ee0048 */ 	addiu	$t6,$t7,0x48
/*     a5d4:	0080c825 */ 	or	$t9,$a0,$zero
.L0000a5d8:
/*     a5d8:	8de10000 */ 	lw	$at,0x0($t7)
/*     a5dc:	25ef000c */ 	addiu	$t7,$t7,0xc
/*     a5e0:	2739000c */ 	addiu	$t9,$t9,0xc
/*     a5e4:	af21fff4 */ 	sw	$at,-0xc($t9)
/*     a5e8:	8de1fff8 */ 	lw	$at,-0x8($t7)
/*     a5ec:	af21fff8 */ 	sw	$at,-0x8($t9)
/*     a5f0:	8de1fffc */ 	lw	$at,-0x4($t7)
/*     a5f4:	15eefff8 */ 	bne	$t7,$t6,.L0000a5d8
/*     a5f8:	af21fffc */ 	sw	$at,-0x4($t9)
/*     a5fc:	8de10000 */ 	lw	$at,0x0($t7)
/*     a600:	af210000 */ 	sw	$at,0x0($t9)
/*     a604:	8dee0004 */ 	lw	$t6,0x4($t7)
/*     a608:	af2e0004 */ 	sw	$t6,0x4($t9)
.L0000a60c:
/*     a60c:	85380018 */ 	lh	$t8,0x18($t1)
/*     a610:	24010280 */ 	addiu	$at,$zero,0x280
/*     a614:	8c83001c */ 	lw	$v1,0x1c($a0)
/*     a618:	ac980008 */ 	sw	$t8,0x8($a0)
/*     a61c:	852e0018 */ 	lh	$t6,0x18($t1)
/*     a620:	ac88002c */ 	sw	$t0,0x2c($a0)
/*     a624:	ac880040 */ 	sw	$t0,0x40($a0)
/*     a628:	000e7a80 */ 	sll	$t7,$t6,0xa
/*     a62c:	01e1001a */ 	div	$zero,$t7,$at
/*     a630:	0000c812 */ 	mflo	$t9
/*     a634:	ac990020 */ 	sw	$t9,0x20($a0)
/*     a638:	85380018 */ 	lh	$t8,0x18($t1)
/*     a63c:	3c078006 */ 	lui	$a3,%hi(var8005d588)
/*     a640:	3c058006 */ 	lui	$a1,%hi(var8005d58c)
/*     a644:	00187040 */ 	sll	$t6,$t8,0x1
/*     a648:	ac8e0028 */ 	sw	$t6,0x28($a0)
/*     a64c:	852f0018 */ 	lh	$t7,0x18($t1)
/*     a650:	0003c403 */ 	sra	$t8,$v1,0x10
/*     a654:	330effff */ 	andi	$t6,$t8,0xffff
/*     a658:	000fc880 */ 	sll	$t9,$t7,0x2
/*     a65c:	ac99003c */ 	sw	$t9,0x3c($a0)
/*     a660:	8ce7d588 */ 	lw	$a3,%lo(var8005d588)($a3)
/*     a664:	25adde0c */ 	addiu	$t5,$t5,%lo(var8008de0c)
/*     a668:	3c1f8009 */ 	lui	$ra,%hi(var8008de10)
/*     a66c:	01c77821 */ 	addu	$t7,$t6,$a3
/*     a670:	01e6001a */ 	div	$zero,$t7,$a2
/*     a674:	14c00002 */ 	bnez	$a2,.L0000a680
/*     a678:	00000000 */ 	nop
/*     a67c:	0007000d */ 	break	0x7
.L0000a680:
/*     a680:	2401ffff */ 	addiu	$at,$zero,-1
/*     a684:	14c10004 */ 	bne	$a2,$at,.L0000a698
/*     a688:	3c018000 */ 	lui	$at,0x8000
/*     a68c:	15e10002 */ 	bne	$t7,$at,.L0000a698
/*     a690:	00000000 */ 	nop
/*     a694:	0006000d */ 	break	0x6
.L0000a698:
/*     a698:	306effff */ 	andi	$t6,$v1,0xffff
/*     a69c:	0000c810 */ 	mfhi	$t9
/*     a6a0:	01c77821 */ 	addu	$t7,$t6,$a3
/*     a6a4:	0019c400 */ 	sll	$t8,$t9,0x10
/*     a6a8:	01e6001a */ 	div	$zero,$t7,$a2
/*     a6ac:	14c00002 */ 	bnez	$a2,.L0000a6b8
/*     a6b0:	00000000 */ 	nop
/*     a6b4:	0007000d */ 	break	0x7
.L0000a6b8:
/*     a6b8:	2401ffff */ 	addiu	$at,$zero,-1
/*     a6bc:	14c10004 */ 	bne	$a2,$at,.L0000a6d0
/*     a6c0:	3c018000 */ 	lui	$at,0x8000
/*     a6c4:	15e10002 */ 	bne	$t7,$at,.L0000a6d0
/*     a6c8:	00000000 */ 	nop
/*     a6cc:	0006000d */ 	break	0x6
.L0000a6d0:
/*     a6d0:	0000c810 */ 	mfhi	$t9
/*     a6d4:	03191025 */ 	or	$v0,$t8,$t9
/*     a6d8:	ac82001c */ 	sw	$v0,0x1c($a0)
/*     a6dc:	3c018009 */ 	lui	$at,%hi(var8008de08)
/*     a6e0:	ac22de08 */ 	sw	$v0,%lo(var8008de08)($at)
/*     a6e4:	8c830030 */ 	lw	$v1,0x30($a0)
/*     a6e8:	8ca5d58c */ 	lw	$a1,%lo(var8005d58c)($a1)
/*     a6ec:	27ffde10 */ 	addiu	$ra,$ra,%lo(var8008de10)
/*     a6f0:	00037403 */ 	sra	$t6,$v1,0x10
/*     a6f4:	31cfffff */ 	andi	$t7,$t6,0xffff
/*     a6f8:	01e5c021 */ 	addu	$t8,$t7,$a1
/*     a6fc:	0306001a */ 	div	$zero,$t8,$a2
/*     a700:	14c00002 */ 	bnez	$a2,.L0000a70c
/*     a704:	00000000 */ 	nop
/*     a708:	0007000d */ 	break	0x7
.L0000a70c:
/*     a70c:	2401ffff */ 	addiu	$at,$zero,-1
/*     a710:	14c10004 */ 	bne	$a2,$at,.L0000a724
/*     a714:	3c018000 */ 	lui	$at,0x8000
/*     a718:	17010002 */ 	bne	$t8,$at,.L0000a724
/*     a71c:	00000000 */ 	nop
/*     a720:	0006000d */ 	break	0x6
.L0000a724:
/*     a724:	306fffff */ 	andi	$t7,$v1,0xffff
/*     a728:	01e5c021 */ 	addu	$t8,$t7,$a1
/*     a72c:	0000c810 */ 	mfhi	$t9
/*     a730:	8c830044 */ 	lw	$v1,0x44($a0)
/*     a734:	00197400 */ 	sll	$t6,$t9,0x10
/*     a738:	0306001a */ 	div	$zero,$t8,$a2
/*     a73c:	14c00002 */ 	bnez	$a2,.L0000a748
/*     a740:	00000000 */ 	nop
/*     a744:	0007000d */ 	break	0x7
.L0000a748:
/*     a748:	2401ffff */ 	addiu	$at,$zero,-1
/*     a74c:	14c10004 */ 	bne	$a2,$at,.L0000a760
/*     a750:	3c018000 */ 	lui	$at,0x8000
/*     a754:	17010002 */ 	bne	$t8,$at,.L0000a760
/*     a758:	00000000 */ 	nop
/*     a75c:	0006000d */ 	break	0x6
.L0000a760:
/*     a760:	0000c810 */ 	mfhi	$t9
/*     a764:	00037c03 */ 	sra	$t7,$v1,0x10
/*     a768:	01d91025 */ 	or	$v0,$t6,$t9
/*     a76c:	31f8ffff */ 	andi	$t8,$t7,0xffff
/*     a770:	03057021 */ 	addu	$t6,$t8,$a1
/*     a774:	01c6001a */ 	div	$zero,$t6,$a2
/*     a778:	3078ffff */ 	andi	$t8,$v1,0xffff
/*     a77c:	0000c810 */ 	mfhi	$t9
/*     a780:	00197c00 */ 	sll	$t7,$t9,0x10
/*     a784:	ac820030 */ 	sw	$v0,0x30($a0)
/*     a788:	ada20000 */ 	sw	$v0,0x0($t5)
/*     a78c:	14c00002 */ 	bnez	$a2,.L0000a798
/*     a790:	00000000 */ 	nop
/*     a794:	0007000d */ 	break	0x7
.L0000a798:
/*     a798:	2401ffff */ 	addiu	$at,$zero,-1
/*     a79c:	14c10004 */ 	bne	$a2,$at,.L0000a7b0
/*     a7a0:	3c018000 */ 	lui	$at,0x8000
/*     a7a4:	15c10002 */ 	bne	$t6,$at,.L0000a7b0
/*     a7a8:	00000000 */ 	nop
/*     a7ac:	0006000d */ 	break	0x6
.L0000a7b0:
/*     a7b0:	03057021 */ 	addu	$t6,$t8,$a1
/*     a7b4:	01c6001a */ 	div	$zero,$t6,$a2
/*     a7b8:	0000c810 */ 	mfhi	$t9
/*     a7bc:	01f91025 */ 	or	$v0,$t7,$t9
/*     a7c0:	ac820044 */ 	sw	$v0,0x44($a0)
/*     a7c4:	afe20000 */ 	sw	$v0,0x0($ra)
/*     a7c8:	3c188006 */ 	lui	$t8,%hi(var8005dd18)
/*     a7cc:	8f18dd18 */ 	lw	$t8,%lo(var8005dd18)($t8)
/*     a7d0:	14c00002 */ 	bnez	$a2,.L0000a7dc
/*     a7d4:	00000000 */ 	nop
/*     a7d8:	0007000d */ 	break	0x7
.L0000a7dc:
/*     a7dc:	2401ffff */ 	addiu	$at,$zero,-1
/*     a7e0:	14c10004 */ 	bne	$a2,$at,.L0000a7f4
/*     a7e4:	3c018000 */ 	lui	$at,0x8000
/*     a7e8:	15c10002 */ 	bne	$t6,$at,.L0000a7f4
/*     a7ec:	00000000 */ 	nop
/*     a7f0:	0006000d */ 	break	0x6
.L0000a7f4:
/*     a7f4:	3c0a8006 */ 	lui	$t2,%hi(var8005d598)
/*     a7f8:	13000038 */ 	beqz	$t8,.L0000a8dc
/*     a7fc:	24ae01af */ 	addiu	$t6,$a1,0x1af
/*     a800:	01c6001a */ 	div	$zero,$t6,$a2
/*     a804:	00007810 */ 	mfhi	$t7
/*     a808:	24b8007b */ 	addiu	$t8,$a1,0x7b
/*     a80c:	14c00002 */ 	bnez	$a2,.L0000a818
/*     a810:	00000000 */ 	nop
/*     a814:	0007000d */ 	break	0x7
.L0000a818:
/*     a818:	2401ffff */ 	addiu	$at,$zero,-1
/*     a81c:	14c10004 */ 	bne	$a2,$at,.L0000a830
/*     a820:	3c018000 */ 	lui	$at,0x8000
/*     a824:	15c10002 */ 	bne	$t6,$at,.L0000a830
/*     a828:	00000000 */ 	nop
/*     a82c:	0006000d */ 	break	0x6
.L0000a830:
/*     a830:	0306001a */ 	div	$zero,$t8,$a2
/*     a834:	00007010 */ 	mfhi	$t6
/*     a838:	000fcc00 */ 	sll	$t9,$t7,0x10
/*     a83c:	24af01b1 */ 	addiu	$t7,$a1,0x1b1
/*     a840:	01e6001a */ 	div	$zero,$t7,$a2
/*     a844:	032e1025 */ 	or	$v0,$t9,$t6
/*     a848:	24ae0079 */ 	addiu	$t6,$a1,0x79
/*     a84c:	14c00002 */ 	bnez	$a2,.L0000a858
/*     a850:	00000000 */ 	nop
/*     a854:	0007000d */ 	break	0x7
.L0000a858:
/*     a858:	2401ffff */ 	addiu	$at,$zero,-1
/*     a85c:	14c10004 */ 	bne	$a2,$at,.L0000a870
/*     a860:	3c018000 */ 	lui	$at,0x8000
/*     a864:	17010002 */ 	bne	$t8,$at,.L0000a870
/*     a868:	00000000 */ 	nop
/*     a86c:	0006000d */ 	break	0x6
.L0000a870:
/*     a870:	0000c010 */ 	mfhi	$t8
/*     a874:	ac820030 */ 	sw	$v0,0x30($a0)
/*     a878:	ada20000 */ 	sw	$v0,0x0($t5)
/*     a87c:	01c6001a */ 	div	$zero,$t6,$a2
/*     a880:	14c00002 */ 	bnez	$a2,.L0000a88c
/*     a884:	00000000 */ 	nop
/*     a888:	0007000d */ 	break	0x7
.L0000a88c:
/*     a88c:	2401ffff */ 	addiu	$at,$zero,-1
/*     a890:	14c10004 */ 	bne	$a2,$at,.L0000a8a4
/*     a894:	3c018000 */ 	lui	$at,0x8000
/*     a898:	15e10002 */ 	bne	$t7,$at,.L0000a8a4
/*     a89c:	00000000 */ 	nop
/*     a8a0:	0006000d */ 	break	0x6
.L0000a8a4:
/*     a8a4:	00007810 */ 	mfhi	$t7
/*     a8a8:	0018cc00 */ 	sll	$t9,$t8,0x10
/*     a8ac:	032f1025 */ 	or	$v0,$t9,$t7
/*     a8b0:	ac820044 */ 	sw	$v0,0x44($a0)
/*     a8b4:	afe20000 */ 	sw	$v0,0x0($ra)
/*     a8b8:	14c00002 */ 	bnez	$a2,.L0000a8c4
/*     a8bc:	00000000 */ 	nop
/*     a8c0:	0007000d */ 	break	0x7
.L0000a8c4:
/*     a8c4:	2401ffff */ 	addiu	$at,$zero,-1
/*     a8c8:	14c10004 */ 	bne	$a2,$at,.L0000a8dc
/*     a8cc:	3c018000 */ 	lui	$at,0x8000
/*     a8d0:	15c10002 */ 	bne	$t6,$at,.L0000a8dc
/*     a8d4:	00000000 */ 	nop
/*     a8d8:	0006000d */ 	break	0x6
.L0000a8dc:
/*     a8dc:	3c018006 */ 	lui	$at,%hi(var8005ce88)
/*     a8e0:	002c0821 */ 	addu	$at,$at,$t4
/*     a8e4:	24180001 */ 	addiu	$t8,$zero,0x1
/*     a8e8:	ac38ce88 */ 	sw	$t8,%lo(var8005ce88)($at)
/*     a8ec:	10000006 */ 	b	.L0000a908
/*     a8f0:	8d4ad598 */ 	lw	$t2,%lo(var8005d598)($t2)
.L0000a8f4:
/*     a8f4:	3c018006 */ 	lui	$at,%hi(var8005ce88)
/*     a8f8:	002c0821 */ 	addu	$at,$at,$t4
/*     a8fc:	3c0a8006 */ 	lui	$t2,%hi(var8005d598)
/*     a900:	8d4ad598 */ 	lw	$t2,%lo(var8005d598)($t2)
/*     a904:	ac20ce88 */ 	sw	$zero,%lo(var8005ce88)($at)
.L0000a908:
/*     a908:	256b0001 */ 	addiu	$t3,$t3,0x1
/*     a90c:	05610004 */ 	bgez	$t3,.L0000a920
/*     a910:	316e0001 */ 	andi	$t6,$t3,0x1
/*     a914:	11c00002 */ 	beqz	$t6,.L0000a920
/*     a918:	00000000 */ 	nop
/*     a91c:	25cefffe */ 	addiu	$t6,$t6,-2
.L0000a920:
/*     a920:	3c018006 */ 	lui	$at,%hi(var8005d5a0)
/*     a924:	11400006 */ 	beqz	$t2,.L0000a940
/*     a928:	ac2ed5a0 */ 	sw	$t6,%lo(var8005d5a0)($at)
/*     a92c:	3c0f8006 */ 	lui	$t7,%hi(g_RdpCurTask)
/*     a930:	8deff108 */ 	lw	$t7,%lo(g_RdpCurTask)($t7)
/*     a934:	8d390028 */ 	lw	$t9,0x28($t1)
/*     a938:	10000006 */ 	b	.L0000a954
/*     a93c:	adf90058 */ 	sw	$t9,0x58($t7)
.L0000a940:
/*     a940:	3c18800a */ 	lui	$t8,%hi(var8009cac0)
/*     a944:	3c0e8006 */ 	lui	$t6,%hi(g_RdpCurTask)
/*     a948:	8dcef108 */ 	lw	$t6,%lo(g_RdpCurTask)($t6)
/*     a94c:	8f18cac0 */ 	lw	$t8,%lo(var8009cac0)($t8)
/*     a950:	add80058 */ 	sw	$t8,0x58($t6)
.L0000a954:
/*     a954:	3c028009 */ 	lui	$v0,%hi(var80092874+0x2)
/*     a958:	24422876 */ 	addiu	$v0,$v0,%lo(var80092874+0x2)
/*     a95c:	90590000 */ 	lbu	$t9,0x0($v0)
/*     a960:	3c048006 */ 	lui	$a0,%hi(g_ViData)
/*     a964:	8c84d594 */ 	lw	$a0,%lo(g_ViData)($a0)
/*     a968:	272f0001 */ 	addiu	$t7,$t9,0x1
/*     a96c:	3c038009 */ 	lui	$v1,%hi(var80092874+0x3)
/*     a970:	2408002c */ 	addiu	$t0,$zero,0x2c
/*     a974:	24632877 */ 	addiu	$v1,$v1,%lo(var80092874+0x3)
/*     a978:	906e0000 */ 	lbu	$t6,0x0($v1)
/*     a97c:	3c078006 */ 	lui	$a3,%hi(var8005d530)
/*     a980:	24e7d530 */ 	addiu	$a3,$a3,%lo(var8005d530)
/*     a984:	05e10004 */ 	bgez	$t7,.L0000a998
/*     a988:	31f80001 */ 	andi	$t8,$t7,0x1
/*     a98c:	13000002 */ 	beqz	$t8,.L0000a998
/*     a990:	00000000 */ 	nop
/*     a994:	2718fffe */ 	addiu	$t8,$t8,-2
.L0000a998:
/*     a998:	a0580000 */ 	sb	$t8,0x0($v0)
/*     a99c:	90580000 */ 	lbu	$t8,0x0($v0)
/*     a9a0:	25d90001 */ 	addiu	$t9,$t6,0x1
/*     a9a4:	07210004 */ 	bgez	$t9,.L0000a9b8
/*     a9a8:	332f0001 */ 	andi	$t7,$t9,0x1
/*     a9ac:	11e00002 */ 	beqz	$t7,.L0000a9b8
/*     a9b0:	00000000 */ 	nop
/*     a9b4:	25effffe */ 	addiu	$t7,$t7,-2
.L0000a9b8:
/*     a9b8:	03080019 */ 	multu	$t8,$t0
/*     a9bc:	a06f0000 */ 	sb	$t7,0x0($v1)
/*     a9c0:	3c018006 */ 	lui	$at,%hi(var8005d590)
/*     a9c4:	3c058006 */ 	lui	$a1,%hi(g_ViData)
/*     a9c8:	2406002c */ 	addiu	$a2,$zero,0x2c
/*     a9cc:	00007012 */ 	mflo	$t6
/*     a9d0:	00eec821 */ 	addu	$t9,$a3,$t6
/*     a9d4:	ac39d590 */ 	sw	$t9,%lo(var8005d590)($at)
/*     a9d8:	906f0000 */ 	lbu	$t7,0x0($v1)
/*     a9dc:	3c018006 */ 	lui	$at,%hi(g_ViData)
/*     a9e0:	01e80019 */ 	multu	$t7,$t0
/*     a9e4:	0000c012 */ 	mflo	$t8
/*     a9e8:	00f87021 */ 	addu	$t6,$a3,$t8
/*     a9ec:	ac2ed594 */ 	sw	$t6,%lo(g_ViData)($at)
/*     a9f0:	0c012c5c */ 	jal	bcopy
/*     a9f4:	8ca5d594 */ 	lw	$a1,%lo(g_ViData)($a1)
/*     a9f8:	3c038009 */ 	lui	$v1,%hi(var80092874+0x3)
/*     a9fc:	24632877 */ 	addiu	$v1,$v1,%lo(var80092874+0x3)
/*     aa00:	90790000 */ 	lbu	$t9,0x0($v1)
/*     aa04:	3c18800a */ 	lui	$t8,%hi(var8009cac0)
/*     aa08:	3c0e8006 */ 	lui	$t6,%hi(g_ViData)
/*     aa0c:	00197880 */ 	sll	$t7,$t9,0x2
/*     aa10:	030fc021 */ 	addu	$t8,$t8,$t7
/*     aa14:	8f18cac0 */ 	lw	$t8,%lo(var8009cac0)($t8)
/*     aa18:	8dced594 */ 	lw	$t6,%lo(g_ViData)($t6)
/*     aa1c:	3c028006 */ 	lui	$v0,%hi(var8005d59c)
/*     aa20:	2442d59c */ 	addiu	$v0,$v0,%lo(var8005d59c)
/*     aa24:	add80028 */ 	sw	$t8,0x28($t6)
/*     aa28:	8c590000 */ 	lw	$t9,0x0($v0)
/*     aa2c:	53200005 */ 	beqzl	$t9,.L0000aa44
/*     aa30:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     aa34:	ac400000 */ 	sw	$zero,0x0($v0)
/*     aa38:	0c0027b1 */ 	jal	func00009ec4
/*     aa3c:	00002025 */ 	or	$a0,$zero,$zero
/*     aa40:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0000aa44:
/*     aa44:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*     aa48:	03e00008 */ 	jr	$ra
/*     aa4c:	00000000 */ 	nop
);
#endif

GLOBAL_ASM(
glabel func0000aa50
/*     aa50:	3c014160 */ 	lui	$at,0x4160
/*     aa54:	44810000 */ 	mtc1	$at,$f0
/*     aa58:	00000000 */ 	nop
/*     aa5c:	460c003c */ 	c.lt.s	$f0,$f12
/*     aa60:	00000000 */ 	nop
/*     aa64:	45020003 */ 	bc1fl	.L0000aa74
/*     aa68:	44800000 */ 	mtc1	$zero,$f0
/*     aa6c:	46000306 */ 	mov.s	$f12,$f0
/*     aa70:	44800000 */ 	mtc1	$zero,$f0
.L0000aa74:
/*     aa74:	00000000 */ 	nop
/*     aa78:	4600603c */ 	c.lt.s	$f12,$f0
/*     aa7c:	00000000 */ 	nop
/*     aa80:	45020003 */ 	bc1fl	.L0000aa90
/*     aa84:	4600610d */ 	trunc.w.s	$f4,$f12
/*     aa88:	46000306 */ 	mov.s	$f12,$f0
/*     aa8c:	4600610d */ 	trunc.w.s	$f4,$f12
.L0000aa90:
/*     aa90:	3c018006 */ 	lui	$at,%hi(var8005ce98)
/*     aa94:	2418000a */ 	addiu	$t8,$zero,0xa
/*     aa98:	440f2000 */ 	mfc1	$t7,$f4
/*     aa9c:	00000000 */ 	nop
/*     aaa0:	ac2fce98 */ 	sw	$t7,%lo(var8005ce98)($at)
/*     aaa4:	3c018006 */ 	lui	$at,%hi(var8005ce9c)
/*     aaa8:	03e00008 */ 	jr	$ra
/*     aaac:	ac38ce9c */ 	sw	$t8,%lo(var8005ce9c)($at)
);

GLOBAL_ASM(
glabel func0000aab0
/*     aab0:	3c058006 */ 	lui	$a1,%hi(g_ViData)
/*     aab4:	24a5d594 */ 	addiu	$a1,$a1,%lo(g_ViData)
/*     aab8:	8cae0000 */ 	lw	$t6,0x0($a1)
/*     aabc:	00041840 */ 	sll	$v1,$a0,0x1
/*     aac0:	3c027005 */ 	lui	$v0,%hi(var700526d0)
/*     aac4:	a1c40000 */ 	sb	$a0,0x0($t6)
/*     aac8:	00431021 */ 	addu	$v0,$v0,$v1
/*     aacc:	844226d0 */ 	lh	$v0,%lo(var700526d0)($v0)
/*     aad0:	8caf0000 */ 	lw	$t7,0x0($a1)
/*     aad4:	a5e20018 */ 	sh	$v0,0x18($t7)
/*     aad8:	8cb80000 */ 	lw	$t8,0x0($a1)
/*     aadc:	a7020004 */ 	sh	$v0,0x4($t8)
/*     aae0:	3c027005 */ 	lui	$v0,%hi(var700526d8)
/*     aae4:	00431021 */ 	addu	$v0,$v0,$v1
/*     aae8:	844226d8 */ 	lh	$v0,%lo(var700526d8)($v0)
/*     aaec:	8cb90000 */ 	lw	$t9,0x0($a1)
/*     aaf0:	a722001a */ 	sh	$v0,0x1a($t9)
/*     aaf4:	8ca80000 */ 	lw	$t0,0x0($a1)
/*     aaf8:	03e00008 */ 	jr	$ra
/*     aafc:	a5020006 */ 	sh	$v0,0x6($t0)
);

GLOBAL_ASM(
glabel func0000ab00
/*     ab00:	240e0001 */ 	addiu	$t6,$zero,0x1
/*     ab04:	3c018006 */ 	lui	$at,%hi(var8005d598)
/*     ab08:	03e00008 */ 	jr	$ra
/*     ab0c:	ac2ed598 */ 	sw	$t6,%lo(var8005d598)($at)
);

GLOBAL_ASM(
glabel func0000ab10
/*     ab10:	3c018006 */ 	lui	$at,%hi(var8005d598)
/*     ab14:	03e00008 */ 	jr	$ra
/*     ab18:	ac20d598 */ 	sw	$zero,%lo(var8005d598)($at)
);

void *viGetUnk28(void)
{
	return g_ViData->unk28;
}

void *vi2GetUnk28(void)
{
	return var8005d590->unk28;
}

void viSetUnk28(void *arg0)
{
	g_ViData->unk28 = arg0;
}

GLOBAL_ASM(
glabel func0000ab4c
/*     ab4c:	3c0f8009 */ 	lui	$t7,%hi(var80092874+0x3)
/*     ab50:	91ef2877 */ 	lbu	$t7,%lo(var80092874+0x3)($t7)
/*     ab54:	3c0e800a */ 	lui	$t6,%hi(g_Vars+0x284)
/*     ab58:	8dcea244 */ 	lw	$t6,%lo(g_Vars+0x284)($t6)
/*     ab5c:	000fc100 */ 	sll	$t8,$t7,0x4
/*     ab60:	01d81021 */ 	addu	$v0,$t6,$t8
/*     ab64:	03e00008 */ 	jr	$ra
/*     ab68:	24420610 */ 	addiu	$v0,$v0,0x610
);

GLOBAL_ASM(
glabel func0000ab6c
/*     ab6c:	3c028009 */ 	lui	$v0,%hi(var80092874)
/*     ab70:	03e00008 */ 	jr	$ra
/*     ab74:	94422874 */ 	lhu	$v0,%lo(var80092874)($v0)
);

GLOBAL_ASM(
glabel func0000ab78
/*     ab78:	3c028006 */ 	lui	$v0,%hi(g_ViData)
/*     ab7c:	8c42d594 */ 	lw	$v0,%lo(g_ViData)($v0)
/*     ab80:	27bdfeb0 */ 	addiu	$sp,$sp,-336
/*     ab84:	afbf002c */ 	sw	$ra,0x2c($sp)
/*     ab88:	afb00028 */ 	sw	$s0,0x28($sp)
/*     ab8c:	c4440010 */ 	lwc1	$f4,0x10($v0)
/*     ab90:	8c47000c */ 	lw	$a3,0xc($v0)
/*     ab94:	8c460008 */ 	lw	$a2,0x8($v0)
/*     ab98:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*     ab9c:	c4400014 */ 	lwc1	$f0,0x14($v0)
/*     aba0:	3c013f80 */ 	lui	$at,0x3f80
/*     aba4:	44814000 */ 	mtc1	$at,$f8
/*     aba8:	46000180 */ 	add.s	$f6,$f0,$f0
/*     abac:	00808025 */ 	or	$s0,$a0,$zero
/*     abb0:	27a40110 */ 	addiu	$a0,$sp,0x110
/*     abb4:	27a50046 */ 	addiu	$a1,$sp,0x46
/*     abb8:	e7a60014 */ 	swc1	$f6,0x14($sp)
/*     abbc:	0c001210 */ 	jal	guPerspectiveF
/*     abc0:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*     abc4:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*     abc8:	00000000 */ 	nop
/*     abcc:	00402025 */ 	or	$a0,$v0,$zero
/*     abd0:	0c005746 */ 	jal	func00015d18
/*     abd4:	27a50090 */ 	addiu	$a1,$sp,0x90
/*     abd8:	44800000 */ 	mtc1	$zero,$f0
/*     abdc:	27a40110 */ 	addiu	$a0,$sp,0x110
/*     abe0:	27a50090 */ 	addiu	$a1,$sp,0x90
/*     abe4:	27a600d0 */ 	addiu	$a2,$sp,0xd0
/*     abe8:	e7a000c0 */ 	swc1	$f0,0xc0($sp)
/*     abec:	e7a000c4 */ 	swc1	$f0,0xc4($sp)
/*     abf0:	0c005680 */ 	jal	func00015a00
/*     abf4:	e7a000c8 */ 	swc1	$f0,0xc8($sp)
/*     abf8:	0fc59e66 */ 	jal	gfxAllocateMatrix
/*     abfc:	00000000 */ 	nop
/*     ac00:	afa2004c */ 	sw	$v0,0x4c($sp)
/*     ac04:	27a400d0 */ 	addiu	$a0,$sp,0xd0
/*     ac08:	0c0128d8 */ 	jal	guMtxF2L
/*     ac0c:	00402825 */ 	or	$a1,$v0,$zero
/*     ac10:	0c00566c */ 	jal	func000159b0
/*     ac14:	27a40050 */ 	addiu	$a0,$sp,0x50
/*     ac18:	0fc59e66 */ 	jal	gfxAllocateMatrix
/*     ac1c:	00000000 */ 	nop
/*     ac20:	afa20048 */ 	sw	$v0,0x48($sp)
/*     ac24:	27a40050 */ 	addiu	$a0,$sp,0x50
/*     ac28:	0c0128d8 */ 	jal	guMtxF2L
/*     ac2c:	00402825 */ 	or	$a1,$v0,$zero
/*     ac30:	3c0e0103 */ 	lui	$t6,0x103
/*     ac34:	35ce0040 */ 	ori	$t6,$t6,0x40
/*     ac38:	02001825 */ 	or	$v1,$s0,$zero
/*     ac3c:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*     ac40:	8faf004c */ 	lw	$t7,0x4c($sp)
/*     ac44:	3c068000 */ 	lui	$a2,0x8000
/*     ac48:	26100008 */ 	addiu	$s0,$s0,0x8
/*     ac4c:	3c190102 */ 	lui	$t9,0x102
/*     ac50:	01e6c021 */ 	addu	$t8,$t7,$a2
/*     ac54:	ac780004 */ 	sw	$t8,0x4($v1)
/*     ac58:	37390040 */ 	ori	$t9,$t9,0x40
/*     ac5c:	02002025 */ 	or	$a0,$s0,$zero
/*     ac60:	ac990000 */ 	sw	$t9,0x0($a0)
/*     ac64:	8fa80048 */ 	lw	$t0,0x48($sp)
/*     ac68:	26100008 */ 	addiu	$s0,$s0,0x8
/*     ac6c:	3c0abc00 */ 	lui	$t2,0xbc00
/*     ac70:	01064821 */ 	addu	$t1,$t0,$a2
/*     ac74:	ac890004 */ 	sw	$t1,0x4($a0)
/*     ac78:	354a000e */ 	ori	$t2,$t2,0xe
/*     ac7c:	02002825 */ 	or	$a1,$s0,$zero
/*     ac80:	acaa0000 */ 	sw	$t2,0x0($a1)
/*     ac84:	97ab0046 */ 	lhu	$t3,0x46($sp)
/*     ac88:	26020008 */ 	addiu	$v0,$s0,0x8
/*     ac8c:	acab0004 */ 	sw	$t3,0x4($a1)
/*     ac90:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*     ac94:	8fb00028 */ 	lw	$s0,0x28($sp)
/*     ac98:	27bd0150 */ 	addiu	$sp,$sp,0x150
/*     ac9c:	03e00008 */ 	jr	$ra
/*     aca0:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel func0000aca4
/*     aca4:	27bdff78 */ 	addiu	$sp,$sp,-136
/*     aca8:	afbf002c */ 	sw	$ra,0x2c($sp)
/*     acac:	afb00028 */ 	sw	$s0,0x28($sp)
/*     acb0:	00808025 */ 	or	$s0,$a0,$zero
/*     acb4:	afa5008c */ 	sw	$a1,0x8c($sp)
/*     acb8:	0fc59e66 */ 	jal	gfxAllocateMatrix
/*     acbc:	afa60090 */ 	sw	$a2,0x90($sp)
/*     acc0:	3c038006 */ 	lui	$v1,%hi(g_ViData)
/*     acc4:	8c63d594 */ 	lw	$v1,%lo(g_ViData)($v1)
/*     acc8:	afa20040 */ 	sw	$v0,0x40($sp)
/*     accc:	3c013f80 */ 	lui	$at,0x3f80
/*     acd0:	44814000 */ 	mtc1	$at,$f8
/*     acd4:	c7a4008c */ 	lwc1	$f4,0x8c($sp)
/*     acd8:	c7a60090 */ 	lwc1	$f6,0x90($sp)
/*     acdc:	8c67000c */ 	lw	$a3,0xc($v1)
/*     ace0:	8c660008 */ 	lw	$a2,0x8($v1)
/*     ace4:	27a40044 */ 	addiu	$a0,$sp,0x44
/*     ace8:	27a50086 */ 	addiu	$a1,$sp,0x86
/*     acec:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*     acf0:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*     acf4:	0c001210 */ 	jal	guPerspectiveF
/*     acf8:	e7a60014 */ 	swc1	$f6,0x14($sp)
/*     acfc:	27a40044 */ 	addiu	$a0,$sp,0x44
/*     ad00:	0c0128d8 */ 	jal	guMtxF2L
/*     ad04:	8fa50040 */ 	lw	$a1,0x40($sp)
/*     ad08:	3c0e0103 */ 	lui	$t6,0x103
/*     ad0c:	35ce0040 */ 	ori	$t6,$t6,0x40
/*     ad10:	02001825 */ 	or	$v1,$s0,$zero
/*     ad14:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*     ad18:	8faf0040 */ 	lw	$t7,0x40($sp)
/*     ad1c:	3c018000 */ 	lui	$at,0x8000
/*     ad20:	26100008 */ 	addiu	$s0,$s0,0x8
/*     ad24:	3c19bc00 */ 	lui	$t9,0xbc00
/*     ad28:	01e1c021 */ 	addu	$t8,$t7,$at
/*     ad2c:	ac780004 */ 	sw	$t8,0x4($v1)
/*     ad30:	3739000e */ 	ori	$t9,$t9,0xe
/*     ad34:	02002025 */ 	or	$a0,$s0,$zero
/*     ad38:	ac990000 */ 	sw	$t9,0x0($a0)
/*     ad3c:	97a80086 */ 	lhu	$t0,0x86($sp)
/*     ad40:	26020008 */ 	addiu	$v0,$s0,0x8
/*     ad44:	ac880004 */ 	sw	$t0,0x4($a0)
/*     ad48:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*     ad4c:	8fb00028 */ 	lw	$s0,0x28($sp)
/*     ad50:	27bd0088 */ 	addiu	$sp,$sp,0x88
/*     ad54:	03e00008 */ 	jr	$ra
/*     ad58:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel func0000ad5c
/*     ad5c:	3c088006 */ 	lui	$t0,%hi(g_ViData)
/*     ad60:	2508d594 */ 	addiu	$t0,$t0,%lo(g_ViData)
/*     ad64:	8d0e0000 */ 	lw	$t6,0x0($t0)
/*     ad68:	27bdffd0 */ 	addiu	$sp,$sp,-48
/*     ad6c:	3c028009 */ 	lui	$v0,%hi(var80092874+0x3)
/*     ad70:	24422877 */ 	addiu	$v0,$v0,%lo(var80092874+0x3)
/*     ad74:	90590000 */ 	lbu	$t9,0x0($v0)
/*     ad78:	afbf002c */ 	sw	$ra,0x2c($sp)
/*     ad7c:	afb00028 */ 	sw	$s0,0x28($sp)
/*     ad80:	85cf001c */ 	lh	$t7,0x1c($t6)
/*     ad84:	00194900 */ 	sll	$t1,$t9,0x4
/*     ad88:	00a95021 */ 	addu	$t2,$a1,$t1
/*     ad8c:	000fc040 */ 	sll	$t8,$t7,0x1
/*     ad90:	a5580000 */ 	sh	$t8,0x0($t2)
/*     ad94:	8d030000 */ 	lw	$v1,0x0($t0)
/*     ad98:	90590000 */ 	lbu	$t9,0x0($v0)
/*     ad9c:	3c018000 */ 	lui	$at,0x8000
/*     ada0:	846b001c */ 	lh	$t3,0x1c($v1)
/*     ada4:	846d0020 */ 	lh	$t5,0x20($v1)
/*     ada8:	00194900 */ 	sll	$t1,$t9,0x4
/*     adac:	000b6040 */ 	sll	$t4,$t3,0x1
/*     adb0:	000d7080 */ 	sll	$t6,$t5,0x2
/*     adb4:	018e7821 */ 	addu	$t7,$t4,$t6
/*     adb8:	00a9c021 */ 	addu	$t8,$a1,$t1
/*     adbc:	a70f0008 */ 	sh	$t7,0x8($t8)
/*     adc0:	8d0a0000 */ 	lw	$t2,0x0($t0)
/*     adc4:	904c0000 */ 	lbu	$t4,0x0($v0)
/*     adc8:	24900008 */ 	addiu	$s0,$a0,0x8
/*     adcc:	854b001e */ 	lh	$t3,0x1e($t2)
/*     add0:	000c7100 */ 	sll	$t6,$t4,0x4
/*     add4:	00aec821 */ 	addu	$t9,$a1,$t6
/*     add8:	000b6840 */ 	sll	$t5,$t3,0x1
/*     addc:	a72d0002 */ 	sh	$t5,0x2($t9)
/*     ade0:	8d030000 */ 	lw	$v1,0x0($t0)
/*     ade4:	904c0000 */ 	lbu	$t4,0x0($v0)
/*     ade8:	3c190380 */ 	lui	$t9,0x380
/*     adec:	8469001e */ 	lh	$t1,0x1e($v1)
/*     adf0:	84780022 */ 	lh	$t8,0x22($v1)
/*     adf4:	000c7100 */ 	sll	$t6,$t4,0x4
/*     adf8:	00097840 */ 	sll	$t7,$t1,0x1
/*     adfc:	00185080 */ 	sll	$t2,$t8,0x2
/*     ae00:	01ea5821 */ 	addu	$t3,$t7,$t2
/*     ae04:	00ae6821 */ 	addu	$t5,$a1,$t6
/*     ae08:	a5ab000a */ 	sh	$t3,0xa($t5)
/*     ae0c:	37390010 */ 	ori	$t9,$t9,0x10
/*     ae10:	ac990000 */ 	sw	$t9,0x0($a0)
/*     ae14:	90490000 */ 	lbu	$t1,0x0($v0)
/*     ae18:	0009c100 */ 	sll	$t8,$t1,0x4
/*     ae1c:	03057821 */ 	addu	$t7,$t8,$a1
/*     ae20:	01e15021 */ 	addu	$t2,$t7,$at
/*     ae24:	0fc59e66 */ 	jal	gfxAllocateMatrix
/*     ae28:	ac8a0004 */ 	sw	$t2,0x4($a0)
/*     ae2c:	3c088006 */ 	lui	$t0,%hi(g_ViData)
/*     ae30:	3c018009 */ 	lui	$at,%hi(var80092870)
/*     ae34:	ac222870 */ 	sw	$v0,%lo(var80092870)($at)
/*     ae38:	2508d594 */ 	addiu	$t0,$t0,%lo(g_ViData)
/*     ae3c:	8d030000 */ 	lw	$v1,0x0($t0)
/*     ae40:	3c013f80 */ 	lui	$at,0x3f80
/*     ae44:	44814000 */ 	mtc1	$at,$f8
/*     ae48:	c4640010 */ 	lwc1	$f4,0x10($v1)
/*     ae4c:	8c660008 */ 	lw	$a2,0x8($v1)
/*     ae50:	8c67000c */ 	lw	$a3,0xc($v1)
/*     ae54:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*     ae58:	c4660014 */ 	lwc1	$f6,0x14($v1)
/*     ae5c:	3c048009 */ 	lui	$a0,%hi(var80092830)
/*     ae60:	3c058009 */ 	lui	$a1,%hi(var80092874)
/*     ae64:	24a52874 */ 	addiu	$a1,$a1,%lo(var80092874)
/*     ae68:	24842830 */ 	addiu	$a0,$a0,%lo(var80092830)
/*     ae6c:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*     ae70:	0c001210 */ 	jal	guPerspectiveF
/*     ae74:	e7a60014 */ 	swc1	$f6,0x14($sp)
/*     ae78:	3c048009 */ 	lui	$a0,%hi(var80092830)
/*     ae7c:	3c058009 */ 	lui	$a1,%hi(var80092870)
/*     ae80:	8ca52870 */ 	lw	$a1,%lo(var80092870)($a1)
/*     ae84:	0c0128d8 */ 	jal	guMtxF2L
/*     ae88:	24842830 */ 	addiu	$a0,$a0,%lo(var80092830)
/*     ae8c:	3c0c0103 */ 	lui	$t4,0x103
/*     ae90:	3c058009 */ 	lui	$a1,%hi(var80092870)
/*     ae94:	358c0040 */ 	ori	$t4,$t4,0x40
/*     ae98:	02001025 */ 	or	$v0,$s0,$zero
/*     ae9c:	24a52870 */ 	addiu	$a1,$a1,%lo(var80092870)
/*     aea0:	ac4c0000 */ 	sw	$t4,0x0($v0)
/*     aea4:	8cae0000 */ 	lw	$t6,0x0($a1)
/*     aea8:	3c018000 */ 	lui	$at,0x8000
/*     aeac:	26100008 */ 	addiu	$s0,$s0,0x8
/*     aeb0:	3c0dbc00 */ 	lui	$t5,0xbc00
/*     aeb4:	01c15821 */ 	addu	$t3,$t6,$at
/*     aeb8:	ac4b0004 */ 	sw	$t3,0x4($v0)
/*     aebc:	35ad000e */ 	ori	$t5,$t5,0xe
/*     aec0:	02001825 */ 	or	$v1,$s0,$zero
/*     aec4:	ac6d0000 */ 	sw	$t5,0x0($v1)
/*     aec8:	3c198009 */ 	lui	$t9,%hi(var80092874)
/*     aecc:	97392874 */ 	lhu	$t9,%lo(var80092874)($t9)
/*     aed0:	26100008 */ 	addiu	$s0,$s0,0x8
/*     aed4:	ac790004 */ 	sw	$t9,0x4($v1)
/*     aed8:	0fc2d3f6 */ 	jal	currentPlayerSetUnk1750
/*     aedc:	8ca40000 */ 	lw	$a0,0x0($a1)
/*     aee0:	3c048009 */ 	lui	$a0,%hi(var80092830)
/*     aee4:	0fc2d5c2 */ 	jal	currentPlayerSetUnk1754
/*     aee8:	24842830 */ 	addiu	$a0,$a0,%lo(var80092830)
/*     aeec:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*     aef0:	02001025 */ 	or	$v0,$s0,$zero
/*     aef4:	8fb00028 */ 	lw	$s0,0x28($sp)
/*     aef8:	03e00008 */ 	jr	$ra
/*     aefc:	27bd0030 */ 	addiu	$sp,$sp,0x30
);

GLOBAL_ASM(
glabel func0000af00
/*     af00:	3c088006 */ 	lui	$t0,%hi(g_ViData)
/*     af04:	2508d594 */ 	addiu	$t0,$t0,%lo(g_ViData)
/*     af08:	8d0e0000 */ 	lw	$t6,0x0($t0)
/*     af0c:	27bdffd0 */ 	addiu	$sp,$sp,-48
/*     af10:	3c028009 */ 	lui	$v0,%hi(var80092874+0x3)
/*     af14:	24422877 */ 	addiu	$v0,$v0,%lo(var80092874+0x3)
/*     af18:	90590000 */ 	lbu	$t9,0x0($v0)
/*     af1c:	afbf002c */ 	sw	$ra,0x2c($sp)
/*     af20:	afb00028 */ 	sw	$s0,0x28($sp)
/*     af24:	85cf001c */ 	lh	$t7,0x1c($t6)
/*     af28:	00194900 */ 	sll	$t1,$t9,0x4
/*     af2c:	00a95021 */ 	addu	$t2,$a1,$t1
/*     af30:	000fc040 */ 	sll	$t8,$t7,0x1
/*     af34:	a5580000 */ 	sh	$t8,0x0($t2)
/*     af38:	8d030000 */ 	lw	$v1,0x0($t0)
/*     af3c:	90590000 */ 	lbu	$t9,0x0($v0)
/*     af40:	240701ff */ 	addiu	$a3,$zero,0x1ff
/*     af44:	846b001c */ 	lh	$t3,0x1c($v1)
/*     af48:	846d0020 */ 	lh	$t5,0x20($v1)
/*     af4c:	00194900 */ 	sll	$t1,$t9,0x4
/*     af50:	000b6040 */ 	sll	$t4,$t3,0x1
/*     af54:	000d7080 */ 	sll	$t6,$t5,0x2
/*     af58:	018e7821 */ 	addu	$t7,$t4,$t6
/*     af5c:	00a9c021 */ 	addu	$t8,$a1,$t1
/*     af60:	a70f0008 */ 	sh	$t7,0x8($t8)
/*     af64:	8d0a0000 */ 	lw	$t2,0x0($t0)
/*     af68:	904c0000 */ 	lbu	$t4,0x0($v0)
/*     af6c:	3c018000 */ 	lui	$at,0x8000
/*     af70:	854b001e */ 	lh	$t3,0x1e($t2)
/*     af74:	000c7100 */ 	sll	$t6,$t4,0x4
/*     af78:	00aec821 */ 	addu	$t9,$a1,$t6
/*     af7c:	000b6840 */ 	sll	$t5,$t3,0x1
/*     af80:	a72d0002 */ 	sh	$t5,0x2($t9)
/*     af84:	8d030000 */ 	lw	$v1,0x0($t0)
/*     af88:	904c0000 */ 	lbu	$t4,0x0($v0)
/*     af8c:	24900008 */ 	addiu	$s0,$a0,0x8
/*     af90:	8469001e */ 	lh	$t1,0x1e($v1)
/*     af94:	84780022 */ 	lh	$t8,0x22($v1)
/*     af98:	000c7100 */ 	sll	$t6,$t4,0x4
/*     af9c:	00097840 */ 	sll	$t7,$t1,0x1
/*     afa0:	00185080 */ 	sll	$t2,$t8,0x2
/*     afa4:	01ea5821 */ 	addu	$t3,$t7,$t2
/*     afa8:	00ae6821 */ 	addu	$t5,$a1,$t6
/*     afac:	a5ab000a */ 	sh	$t3,0xa($t5)
/*     afb0:	90590000 */ 	lbu	$t9,0x0($v0)
/*     afb4:	00194900 */ 	sll	$t1,$t9,0x4
/*     afb8:	00a9c021 */ 	addu	$t8,$a1,$t1
/*     afbc:	a7070004 */ 	sh	$a3,0x4($t8)
/*     afc0:	904f0000 */ 	lbu	$t7,0x0($v0)
/*     afc4:	000f5100 */ 	sll	$t2,$t7,0x4
/*     afc8:	00aa6021 */ 	addu	$t4,$a1,$t2
/*     afcc:	a587000c */ 	sh	$a3,0xc($t4)
/*     afd0:	904e0000 */ 	lbu	$t6,0x0($v0)
/*     afd4:	3c0f0380 */ 	lui	$t7,0x380
/*     afd8:	35ef0010 */ 	ori	$t7,$t7,0x10
/*     afdc:	000e5900 */ 	sll	$t3,$t6,0x4
/*     afe0:	00ab6821 */ 	addu	$t5,$a1,$t3
/*     afe4:	a5a00006 */ 	sh	$zero,0x6($t5)
/*     afe8:	90590000 */ 	lbu	$t9,0x0($v0)
/*     afec:	00194900 */ 	sll	$t1,$t9,0x4
/*     aff0:	00a9c021 */ 	addu	$t8,$a1,$t1
/*     aff4:	a700000e */ 	sh	$zero,0xe($t8)
/*     aff8:	ac8f0000 */ 	sw	$t7,0x0($a0)
/*     affc:	904a0000 */ 	lbu	$t2,0x0($v0)
/*     b000:	000a6100 */ 	sll	$t4,$t2,0x4
/*     b004:	01857021 */ 	addu	$t6,$t4,$a1
/*     b008:	01c15821 */ 	addu	$t3,$t6,$at
/*     b00c:	0fc59e66 */ 	jal	gfxAllocateMatrix
/*     b010:	ac8b0004 */ 	sw	$t3,0x4($a0)
/*     b014:	3c088006 */ 	lui	$t0,%hi(g_ViData)
/*     b018:	3c018009 */ 	lui	$at,%hi(var80092870)
/*     b01c:	ac222870 */ 	sw	$v0,%lo(var80092870)($at)
/*     b020:	2508d594 */ 	addiu	$t0,$t0,%lo(g_ViData)
/*     b024:	8d030000 */ 	lw	$v1,0x0($t0)
/*     b028:	3c013f80 */ 	lui	$at,0x3f80
/*     b02c:	44814000 */ 	mtc1	$at,$f8
/*     b030:	c4640010 */ 	lwc1	$f4,0x10($v1)
/*     b034:	8c660008 */ 	lw	$a2,0x8($v1)
/*     b038:	8c67000c */ 	lw	$a3,0xc($v1)
/*     b03c:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*     b040:	c4660014 */ 	lwc1	$f6,0x14($v1)
/*     b044:	3c048009 */ 	lui	$a0,%hi(var80092830)
/*     b048:	3c058009 */ 	lui	$a1,%hi(var80092874)
/*     b04c:	24a52874 */ 	addiu	$a1,$a1,%lo(var80092874)
/*     b050:	24842830 */ 	addiu	$a0,$a0,%lo(var80092830)
/*     b054:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*     b058:	0c001210 */ 	jal	guPerspectiveF
/*     b05c:	e7a60014 */ 	swc1	$f6,0x14($sp)
/*     b060:	3c048009 */ 	lui	$a0,%hi(var80092830)
/*     b064:	3c058009 */ 	lui	$a1,%hi(var80092870)
/*     b068:	8ca52870 */ 	lw	$a1,%lo(var80092870)($a1)
/*     b06c:	0c0128d8 */ 	jal	guMtxF2L
/*     b070:	24842830 */ 	addiu	$a0,$a0,%lo(var80092830)
/*     b074:	3c0d0103 */ 	lui	$t5,0x103
/*     b078:	3c058009 */ 	lui	$a1,%hi(var80092870)
/*     b07c:	35ad0040 */ 	ori	$t5,$t5,0x40
/*     b080:	02001025 */ 	or	$v0,$s0,$zero
/*     b084:	24a52870 */ 	addiu	$a1,$a1,%lo(var80092870)
/*     b088:	ac4d0000 */ 	sw	$t5,0x0($v0)
/*     b08c:	8cb90000 */ 	lw	$t9,0x0($a1)
/*     b090:	3c018000 */ 	lui	$at,0x8000
/*     b094:	26100008 */ 	addiu	$s0,$s0,0x8
/*     b098:	3c18bc00 */ 	lui	$t8,0xbc00
/*     b09c:	03214821 */ 	addu	$t1,$t9,$at
/*     b0a0:	ac490004 */ 	sw	$t1,0x4($v0)
/*     b0a4:	3718000e */ 	ori	$t8,$t8,0xe
/*     b0a8:	02001825 */ 	or	$v1,$s0,$zero
/*     b0ac:	ac780000 */ 	sw	$t8,0x0($v1)
/*     b0b0:	3c0f8009 */ 	lui	$t7,%hi(var80092874)
/*     b0b4:	95ef2874 */ 	lhu	$t7,%lo(var80092874)($t7)
/*     b0b8:	26100008 */ 	addiu	$s0,$s0,0x8
/*     b0bc:	ac6f0004 */ 	sw	$t7,0x4($v1)
/*     b0c0:	0fc2d3f6 */ 	jal	currentPlayerSetUnk1750
/*     b0c4:	8ca40000 */ 	lw	$a0,0x0($a1)
/*     b0c8:	3c048009 */ 	lui	$a0,%hi(var80092830)
/*     b0cc:	0fc2d5c2 */ 	jal	currentPlayerSetUnk1754
/*     b0d0:	24842830 */ 	addiu	$a0,$a0,%lo(var80092830)
/*     b0d4:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*     b0d8:	02001025 */ 	or	$v0,$s0,$zero
/*     b0dc:	8fb00028 */ 	lw	$s0,0x28($sp)
/*     b0e0:	03e00008 */ 	jr	$ra
/*     b0e4:	27bd0030 */ 	addiu	$sp,$sp,0x30
);

GLOBAL_ASM(
glabel func0000b0e8
/*     b0e8:	27bdff80 */ 	addiu	$sp,$sp,-128
/*     b0ec:	afbf002c */ 	sw	$ra,0x2c($sp)
/*     b0f0:	afb00028 */ 	sw	$s0,0x28($sp)
/*     b0f4:	00808025 */ 	or	$s0,$a0,$zero
/*     b0f8:	afa50084 */ 	sw	$a1,0x84($sp)
/*     b0fc:	0fc59e66 */ 	jal	gfxAllocateMatrix
/*     b100:	afa60088 */ 	sw	$a2,0x88($sp)
/*     b104:	3c038006 */ 	lui	$v1,%hi(g_ViData)
/*     b108:	8c63d594 */ 	lw	$v1,%lo(g_ViData)($v1)
/*     b10c:	afa2003c */ 	sw	$v0,0x3c($sp)
/*     b110:	3c013f80 */ 	lui	$at,0x3f80
/*     b114:	c4640010 */ 	lwc1	$f4,0x10($v1)
/*     b118:	44814000 */ 	mtc1	$at,$f8
/*     b11c:	3c058009 */ 	lui	$a1,%hi(var80092874)
/*     b120:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*     b124:	c4660014 */ 	lwc1	$f6,0x14($v1)
/*     b128:	24a52874 */ 	addiu	$a1,$a1,%lo(var80092874)
/*     b12c:	27a40040 */ 	addiu	$a0,$sp,0x40
/*     b130:	8fa60084 */ 	lw	$a2,0x84($sp)
/*     b134:	8fa70088 */ 	lw	$a3,0x88($sp)
/*     b138:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*     b13c:	0c001210 */ 	jal	guPerspectiveF
/*     b140:	e7a60014 */ 	swc1	$f6,0x14($sp)
/*     b144:	27a40040 */ 	addiu	$a0,$sp,0x40
/*     b148:	0c0128d8 */ 	jal	guMtxF2L
/*     b14c:	8fa5003c */ 	lw	$a1,0x3c($sp)
/*     b150:	3c0e0103 */ 	lui	$t6,0x103
/*     b154:	35ce0040 */ 	ori	$t6,$t6,0x40
/*     b158:	02001825 */ 	or	$v1,$s0,$zero
/*     b15c:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*     b160:	8faf003c */ 	lw	$t7,0x3c($sp)
/*     b164:	3c018000 */ 	lui	$at,0x8000
/*     b168:	26100008 */ 	addiu	$s0,$s0,0x8
/*     b16c:	3c19bc00 */ 	lui	$t9,0xbc00
/*     b170:	01e1c021 */ 	addu	$t8,$t7,$at
/*     b174:	ac780004 */ 	sw	$t8,0x4($v1)
/*     b178:	3739000e */ 	ori	$t9,$t9,0xe
/*     b17c:	02002025 */ 	or	$a0,$s0,$zero
/*     b180:	ac990000 */ 	sw	$t9,0x0($a0)
/*     b184:	3c088009 */ 	lui	$t0,%hi(var80092874)
/*     b188:	95082874 */ 	lhu	$t0,%lo(var80092874)($t0)
/*     b18c:	26020008 */ 	addiu	$v0,$s0,0x8
/*     b190:	ac880004 */ 	sw	$t0,0x4($a0)
/*     b194:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*     b198:	8fb00028 */ 	lw	$s0,0x28($sp)
/*     b19c:	27bd0080 */ 	addiu	$sp,$sp,0x80
/*     b1a0:	03e00008 */ 	jr	$ra
/*     b1a4:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel func0000b1a8
/*     b1a8:	3c05800a */ 	lui	$a1,%hi(g_Vars+0x284)
/*     b1ac:	8ca5a244 */ 	lw	$a1,%lo(g_Vars+0x284)($a1)
/*     b1b0:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*     b1b4:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     b1b8:	0c002b57 */ 	jal	func0000ad5c
/*     b1bc:	24a50610 */ 	addiu	$a1,$a1,1552
/*     b1c0:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     b1c4:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*     b1c8:	03e00008 */ 	jr	$ra
/*     b1cc:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel func0000b1d0
/*     b1d0:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*     b1d4:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     b1d8:	0c002c6a */ 	jal	func0000b1a8
/*     b1dc:	00000000 */ 	nop
/*     b1e0:	3c0e8006 */ 	lui	$t6,%hi(var8005d598)
/*     b1e4:	8dced598 */ 	lw	$t6,%lo(var8005d598)($t6)
/*     b1e8:	3c058006 */ 	lui	$a1,%hi(g_ViData)
/*     b1ec:	24a5d594 */ 	addiu	$a1,$a1,%lo(g_ViData)
/*     b1f0:	51c00012 */ 	beqzl	$t6,.L0000b23c
/*     b1f4:	8cad0000 */ 	lw	$t5,0x0($a1)
/*     b1f8:	3c058006 */ 	lui	$a1,%hi(g_ViData)
/*     b1fc:	24a5d594 */ 	addiu	$a1,$a1,%lo(g_ViData)
/*     b200:	8caf0000 */ 	lw	$t7,0x0($a1)
/*     b204:	3c01ff10 */ 	lui	$at,0xff10
/*     b208:	24440008 */ 	addiu	$a0,$v0,0x8
/*     b20c:	85f80018 */ 	lh	$t8,0x18($t7)
/*     b210:	2719ffff */ 	addiu	$t9,$t8,-1
/*     b214:	33280fff */ 	andi	$t0,$t9,0xfff
/*     b218:	01014825 */ 	or	$t1,$t0,$at
/*     b21c:	ac490000 */ 	sw	$t1,0x0($v0)
/*     b220:	8caa0000 */ 	lw	$t2,0x0($a1)
/*     b224:	3c018000 */ 	lui	$at,0x8000
/*     b228:	8d4b0028 */ 	lw	$t3,0x28($t2)
/*     b22c:	01616021 */ 	addu	$t4,$t3,$at
/*     b230:	1000000e */ 	b	.L0000b26c
/*     b234:	ac4c0004 */ 	sw	$t4,0x4($v0)
/*     b238:	8cad0000 */ 	lw	$t5,0x0($a1)
.L0000b23c:
/*     b23c:	3c01ff18 */ 	lui	$at,0xff18
/*     b240:	3c08800a */ 	lui	$t0,%hi(var8009cac0)
/*     b244:	85ae0018 */ 	lh	$t6,0x18($t5)
/*     b248:	24440008 */ 	addiu	$a0,$v0,0x8
/*     b24c:	25cfffff */ 	addiu	$t7,$t6,-1
/*     b250:	31f80fff */ 	andi	$t8,$t7,0xfff
/*     b254:	0301c825 */ 	or	$t9,$t8,$at
/*     b258:	ac590000 */ 	sw	$t9,0x0($v0)
/*     b25c:	8d08cac0 */ 	lw	$t0,%lo(var8009cac0)($t0)
/*     b260:	3c018000 */ 	lui	$at,0x8000
/*     b264:	01014821 */ 	addu	$t1,$t0,$at
/*     b268:	ac490004 */ 	sw	$t1,0x4($v0)
.L0000b26c:
/*     b26c:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     b270:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*     b274:	00801025 */ 	or	$v0,$a0,$zero
/*     b278:	03e00008 */ 	jr	$ra
/*     b27c:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel func0000b280
/*     b280:	3c0e8006 */ 	lui	$t6,%hi(g_ViData)
/*     b284:	8dced594 */ 	lw	$t6,%lo(g_ViData)($t6)
/*     b288:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*     b28c:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     b290:	8dcf0024 */ 	lw	$t7,0x24($t6)
/*     b294:	51e00007 */ 	beqzl	$t7,.L0000b2b4
/*     b298:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     b29c:	0fc5d8ab */ 	jal	func0f1762ac
/*     b2a0:	00000000 */ 	nop
/*     b2a4:	0fc5d8fd */ 	jal	func0f1763f4
/*     b2a8:	00402025 */ 	or	$a0,$v0,$zero
/*     b2ac:	00402025 */ 	or	$a0,$v0,$zero
/*     b2b0:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0000b2b4:
/*     b2b4:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*     b2b8:	00801025 */ 	or	$v0,$a0,$zero
/*     b2bc:	03e00008 */ 	jr	$ra
/*     b2c0:	00000000 */ 	nop
);

Gfx *func0000b2c4(Gfx *gdl)
{
	gDPSetCycleType(gdl++, G_CYC_FILL);
	gDPFillRectangle(gdl++, 0, 0, g_ViData->bufx - 1, g_ViData->bufy - 1);
	gDPPipeSync(gdl++);

	return gdl;
}

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func0000b330
/*     b330:	27bdff58 */ 	addiu	$sp,$sp,-168
/*     b334:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     b338:	3c0eba00 */ 	lui	$t6,0xba00
/*     b33c:	35ce1402 */ 	ori	$t6,$t6,0x1402
/*     b340:	24830008 */ 	addiu	$v1,$a0,0x8
/*     b344:	3c0f0030 */ 	lui	$t7,0x30
/*     b348:	ac8f0004 */ 	sw	$t7,0x4($a0)
/*     b34c:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*     b350:	3c18ed00 */ 	lui	$t8,0xed00
/*     b354:	ac780000 */ 	sw	$t8,0x0($v1)
/*     b358:	24660008 */ 	addiu	$a2,$v1,0x8
/*     b35c:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b360:	0c002f02 */ 	jal	viGetWidth
/*     b364:	afa300a0 */ 	sw	$v1,0xa0($sp)
/*     b368:	0c002f06 */ 	jal	viGetHeight
/*     b36c:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b370:	44822000 */ 	mtc1	$v0,$f4
/*     b374:	87af0056 */ 	lh	$t7,0x56($sp)
/*     b378:	3c014080 */ 	lui	$at,0x4080
/*     b37c:	468021a0 */ 	cvt.s.w	$f6,$f4
/*     b380:	448f8000 */ 	mtc1	$t7,$f16
/*     b384:	44810000 */ 	mtc1	$at,$f0
/*     b388:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b38c:	3c0b800a */ 	lui	$t3,%hi(g_Vars)
/*     b390:	468084a0 */ 	cvt.s.w	$f18,$f16
/*     b394:	46003202 */ 	mul.s	$f8,$f6,$f0
/*     b398:	00c01825 */ 	or	$v1,$a2,$zero
/*     b39c:	256b9fc0 */ 	addiu	$t3,$t3,%lo(g_Vars)
/*     b3a0:	24010001 */ 	addiu	$at,$zero,0x1
/*     b3a4:	00002825 */ 	or	$a1,$zero,$zero
/*     b3a8:	46009102 */ 	mul.s	$f4,$f18,$f0
/*     b3ac:	00002025 */ 	or	$a0,$zero,$zero
/*     b3b0:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b3b4:	4600428d */ 	trunc.w.s	$f10,$f8
/*     b3b8:	4600218d */ 	trunc.w.s	$f6,$f4
/*     b3bc:	440d5000 */ 	mfc1	$t5,$f10
/*     b3c0:	44193000 */ 	mfc1	$t9,$f6
/*     b3c4:	31ae0fff */ 	andi	$t6,$t5,0xfff
/*     b3c8:	332d0fff */ 	andi	$t5,$t9,0xfff
/*     b3cc:	8fb900a0 */ 	lw	$t9,0xa0($sp)
/*     b3d0:	000d7b00 */ 	sll	$t7,$t5,0xc
/*     b3d4:	01cfc025 */ 	or	$t8,$t6,$t7
/*     b3d8:	3c0e0001 */ 	lui	$t6,0x1
/*     b3dc:	af380004 */ 	sw	$t8,0x4($t9)
/*     b3e0:	35ce0001 */ 	ori	$t6,$t6,0x1
/*     b3e4:	3c0df700 */ 	lui	$t5,0xf700
/*     b3e8:	ac6d0000 */ 	sw	$t5,0x0($v1)
/*     b3ec:	ac6e0004 */ 	sw	$t6,0x4($v1)
/*     b3f0:	8d6f006c */ 	lw	$t7,0x6c($t3)
/*     b3f4:	00001825 */ 	or	$v1,$zero,$zero
/*     b3f8:	11e00003 */ 	beqz	$t7,.L0000b408
/*     b3fc:	00000000 */ 	nop
/*     b400:	10000001 */ 	b	.L0000b408
/*     b404:	24050001 */ 	addiu	$a1,$zero,0x1
.L0000b408:
/*     b408:	8d780068 */ 	lw	$t8,0x68($t3)
/*     b40c:	00001025 */ 	or	$v0,$zero,$zero
/*     b410:	13000003 */ 	beqz	$t8,.L0000b420
/*     b414:	00000000 */ 	nop
/*     b418:	10000001 */ 	b	.L0000b420
/*     b41c:	24040001 */ 	addiu	$a0,$zero,0x1
.L0000b420:
/*     b420:	8d790064 */ 	lw	$t9,0x64($t3)
/*     b424:	13200003 */ 	beqz	$t9,.L0000b434
/*     b428:	00000000 */ 	nop
/*     b42c:	10000001 */ 	b	.L0000b434
/*     b430:	24030001 */ 	addiu	$v1,$zero,0x1
.L0000b434:
/*     b434:	8d6d0070 */ 	lw	$t5,0x70($t3)
/*     b438:	11a00003 */ 	beqz	$t5,.L0000b448
/*     b43c:	00000000 */ 	nop
/*     b440:	10000001 */ 	b	.L0000b448
/*     b444:	24020001 */ 	addiu	$v0,$zero,0x1
.L0000b448:
/*     b448:	00437021 */ 	addu	$t6,$v0,$v1
/*     b44c:	01c47821 */ 	addu	$t7,$t6,$a0
/*     b450:	01e5c021 */ 	addu	$t8,$t7,$a1
/*     b454:	13010010 */ 	beq	$t8,$at,.L0000b498
/*     b458:	00000000 */ 	nop
/*     b45c:	8d790298 */ 	lw	$t9,0x298($t3)
/*     b460:	07210004 */ 	bgez	$t9,.L0000b474
/*     b464:	00000000 */ 	nop
/*     b468:	8d6d029c */ 	lw	$t5,0x29c($t3)
/*     b46c:	05a20057 */ 	bltzl	$t5,.L0000b5cc
/*     b470:	8d6d0290 */ 	lw	$t5,0x290($t3)
.L0000b474:
/*     b474:	0fc2f130 */ 	jal	func0f0bc4c0
/*     b478:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b47c:	3c0b800a */ 	lui	$t3,%hi(g_Vars)
/*     b480:	256b9fc0 */ 	addiu	$t3,$t3,%lo(g_Vars)
/*     b484:	10400050 */ 	beqz	$v0,.L0000b5c8
/*     b488:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b48c:	8d6e028c */ 	lw	$t6,0x28c($t3)
/*     b490:	55c0004e */ 	bnezl	$t6,.L0000b5cc
/*     b494:	8d6d0290 */ 	lw	$t5,0x290($t3)
.L0000b498:
/*     b498:	0c002f44 */ 	jal	viGetViewTop
/*     b49c:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b4a0:	1840001a */ 	blez	$v0,.L0000b50c
/*     b4a4:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b4a8:	afa60098 */ 	sw	$a2,0x98($sp)
/*     b4ac:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b4b0:	0c002f02 */ 	jal	viGetWidth
/*     b4b4:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b4b8:	0c002f44 */ 	jal	viGetViewTop
/*     b4bc:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b4c0:	87ae0056 */ 	lh	$t6,0x56($sp)
/*     b4c4:	244fffff */ 	addiu	$t7,$v0,-1
/*     b4c8:	31f803ff */ 	andi	$t8,$t7,0x3ff
/*     b4cc:	0018c880 */ 	sll	$t9,$t8,0x2
/*     b4d0:	8fa40098 */ 	lw	$a0,0x98($sp)
/*     b4d4:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b4d8:	3c01f600 */ 	lui	$at,0xf600
/*     b4dc:	25cfffff */ 	addiu	$t7,$t6,-1
/*     b4e0:	31f803ff */ 	andi	$t8,$t7,0x3ff
/*     b4e4:	03216825 */ 	or	$t5,$t9,$at
/*     b4e8:	0018cb80 */ 	sll	$t9,$t8,0xe
/*     b4ec:	01b97025 */ 	or	$t6,$t5,$t9
/*     b4f0:	00c01825 */ 	or	$v1,$a2,$zero
/*     b4f4:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*     b4f8:	ac800004 */ 	sw	$zero,0x4($a0)
/*     b4fc:	3c0fe700 */ 	lui	$t7,0xe700
/*     b500:	ac6f0000 */ 	sw	$t7,0x0($v1)
/*     b504:	ac600004 */ 	sw	$zero,0x4($v1)
/*     b508:	24c60008 */ 	addiu	$a2,$a2,0x8
.L0000b50c:
/*     b50c:	0c002f26 */ 	jal	viGetViewHeight
/*     b510:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b514:	0c002f44 */ 	jal	viGetViewTop
/*     b518:	a7a20042 */ 	sh	$v0,0x42($sp)
/*     b51c:	0c002f06 */ 	jal	viGetHeight
/*     b520:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b524:	87b80056 */ 	lh	$t8,0x56($sp)
/*     b528:	87ad0042 */ 	lh	$t5,0x42($sp)
/*     b52c:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b530:	030dc821 */ 	addu	$t9,$t8,$t5
/*     b534:	0322082a */ 	slt	$at,$t9,$v0
/*     b538:	50200195 */ 	beqzl	$at,.L0000bb90
/*     b53c:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     b540:	afa60090 */ 	sw	$a2,0x90($sp)
/*     b544:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b548:	0c002f02 */ 	jal	viGetWidth
/*     b54c:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b550:	0c002f06 */ 	jal	viGetHeight
/*     b554:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b558:	87b90056 */ 	lh	$t9,0x56($sp)
/*     b55c:	244effff */ 	addiu	$t6,$v0,-1
/*     b560:	31cf03ff */ 	andi	$t7,$t6,0x3ff
/*     b564:	000fc080 */ 	sll	$t8,$t7,0x2
/*     b568:	272effff */ 	addiu	$t6,$t9,-1
/*     b56c:	31cf03ff */ 	andi	$t7,$t6,0x3ff
/*     b570:	3c01f600 */ 	lui	$at,0xf600
/*     b574:	03016825 */ 	or	$t5,$t8,$at
/*     b578:	8fae0090 */ 	lw	$t6,0x90($sp)
/*     b57c:	000fc380 */ 	sll	$t8,$t7,0xe
/*     b580:	01b8c825 */ 	or	$t9,$t5,$t8
/*     b584:	0c002f44 */ 	jal	viGetViewTop
/*     b588:	add90000 */ 	sw	$t9,0x0($t6)
/*     b58c:	0c002f26 */ 	jal	viGetViewHeight
/*     b590:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b594:	87af0056 */ 	lh	$t7,0x56($sp)
/*     b598:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b59c:	8fae0090 */ 	lw	$t6,0x90($sp)
/*     b5a0:	004f6821 */ 	addu	$t5,$v0,$t7
/*     b5a4:	31b803ff */ 	andi	$t8,$t5,0x3ff
/*     b5a8:	0018c880 */ 	sll	$t9,$t8,0x2
/*     b5ac:	00c01825 */ 	or	$v1,$a2,$zero
/*     b5b0:	3c0fe700 */ 	lui	$t7,0xe700
/*     b5b4:	add90004 */ 	sw	$t9,0x4($t6)
/*     b5b8:	ac600004 */ 	sw	$zero,0x4($v1)
/*     b5bc:	ac6f0000 */ 	sw	$t7,0x0($v1)
/*     b5c0:	10000172 */ 	b	.L0000bb8c
/*     b5c4:	24c60008 */ 	addiu	$a2,$a2,0x8
.L0000b5c8:
/*     b5c8:	8d6d0290 */ 	lw	$t5,0x290($t3)
.L0000b5cc:
/*     b5cc:	00006025 */ 	or	$t4,$zero,$zero
/*     b5d0:	24010002 */ 	addiu	$at,$zero,0x2
/*     b5d4:	55a0016e */ 	bnezl	$t5,.L0000bb90
/*     b5d8:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     b5dc:	8d69006c */ 	lw	$t1,0x6c($t3)
/*     b5e0:	afa00080 */ 	sw	$zero,0x80($sp)
/*     b5e4:	8d670068 */ 	lw	$a3,0x68($t3)
/*     b5e8:	8d680064 */ 	lw	$t0,0x64($t3)
/*     b5ec:	11200003 */ 	beqz	$t1,.L0000b5fc
/*     b5f0:	8d6a0070 */ 	lw	$t2,0x70($t3)
/*     b5f4:	10000002 */ 	b	.L0000b600
/*     b5f8:	24050001 */ 	addiu	$a1,$zero,0x1
.L0000b5fc:
/*     b5fc:	00002825 */ 	or	$a1,$zero,$zero
.L0000b600:
/*     b600:	50e00004 */ 	beqzl	$a3,.L0000b614
/*     b604:	00002025 */ 	or	$a0,$zero,$zero
/*     b608:	10000002 */ 	b	.L0000b614
/*     b60c:	24040001 */ 	addiu	$a0,$zero,0x1
/*     b610:	00002025 */ 	or	$a0,$zero,$zero
.L0000b614:
/*     b614:	51000004 */ 	beqzl	$t0,.L0000b628
/*     b618:	00001825 */ 	or	$v1,$zero,$zero
/*     b61c:	10000002 */ 	b	.L0000b628
/*     b620:	24030001 */ 	addiu	$v1,$zero,0x1
/*     b624:	00001825 */ 	or	$v1,$zero,$zero
.L0000b628:
/*     b628:	51400004 */ 	beqzl	$t2,.L0000b63c
/*     b62c:	00001025 */ 	or	$v0,$zero,$zero
/*     b630:	10000002 */ 	b	.L0000b63c
/*     b634:	24020001 */ 	addiu	$v0,$zero,0x1
/*     b638:	00001025 */ 	or	$v0,$zero,$zero
.L0000b63c:
/*     b63c:	0043c021 */ 	addu	$t8,$v0,$v1
/*     b640:	0304c821 */ 	addu	$t9,$t8,$a0
/*     b644:	03257021 */ 	addu	$t6,$t9,$a1
/*     b648:	15c10004 */ 	bne	$t6,$at,.L0000b65c
/*     b64c:	240f0001 */ 	addiu	$t7,$zero,0x1
/*     b650:	240c0001 */ 	addiu	$t4,$zero,0x1
/*     b654:	10000019 */ 	b	.L0000b6bc
/*     b658:	afaf0080 */ 	sw	$t7,0x80($sp)
.L0000b65c:
/*     b65c:	11200003 */ 	beqz	$t1,.L0000b66c
/*     b660:	00002825 */ 	or	$a1,$zero,$zero
/*     b664:	10000001 */ 	b	.L0000b66c
/*     b668:	24050001 */ 	addiu	$a1,$zero,0x1
.L0000b66c:
/*     b66c:	10e00003 */ 	beqz	$a3,.L0000b67c
/*     b670:	00002025 */ 	or	$a0,$zero,$zero
/*     b674:	10000001 */ 	b	.L0000b67c
/*     b678:	24040001 */ 	addiu	$a0,$zero,0x1
.L0000b67c:
/*     b67c:	11000003 */ 	beqz	$t0,.L0000b68c
/*     b680:	00001825 */ 	or	$v1,$zero,$zero
/*     b684:	10000001 */ 	b	.L0000b68c
/*     b688:	24030001 */ 	addiu	$v1,$zero,0x1
.L0000b68c:
/*     b68c:	11400003 */ 	beqz	$t2,.L0000b69c
/*     b690:	00001025 */ 	or	$v0,$zero,$zero
/*     b694:	10000001 */ 	b	.L0000b69c
/*     b698:	24020001 */ 	addiu	$v0,$zero,0x1
.L0000b69c:
/*     b69c:	00436821 */ 	addu	$t5,$v0,$v1
/*     b6a0:	01a4c021 */ 	addu	$t8,$t5,$a0
/*     b6a4:	0305c821 */ 	addu	$t9,$t8,$a1
/*     b6a8:	2b210003 */ 	slti	$at,$t9,0x3
/*     b6ac:	14200003 */ 	bnez	$at,.L0000b6bc
/*     b6b0:	240e0002 */ 	addiu	$t6,$zero,0x2
/*     b6b4:	240c0002 */ 	addiu	$t4,$zero,0x2
/*     b6b8:	afae0080 */ 	sw	$t6,0x80($sp)
.L0000b6bc:
/*     b6bc:	3c0f800a */ 	lui	$t7,%hi(g_Vars+0x64)
/*     b6c0:	8defa024 */ 	lw	$t7,%lo(g_Vars+0x64)($t7)
/*     b6c4:	85ed0636 */ 	lh	$t5,0x636($t7)
/*     b6c8:	19a0001c */ 	blez	$t5,.L0000b73c
/*     b6cc:	00c02025 */ 	or	$a0,$a2,$zero
/*     b6d0:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b6d4:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b6d8:	afa4007c */ 	sw	$a0,0x7c($sp)
/*     b6dc:	0c002f02 */ 	jal	viGetWidth
/*     b6e0:	afac0084 */ 	sw	$t4,0x84($sp)
/*     b6e4:	3c18800a */ 	lui	$t8,%hi(g_Vars+0x64)
/*     b6e8:	8f18a024 */ 	lw	$t8,%lo(g_Vars+0x64)($t8)
/*     b6ec:	8fa4007c */ 	lw	$a0,0x7c($sp)
/*     b6f0:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b6f4:	87190636 */ 	lh	$t9,0x636($t8)
/*     b6f8:	3c01f600 */ 	lui	$at,0xf600
/*     b6fc:	8fac0084 */ 	lw	$t4,0x84($sp)
/*     b700:	272effff */ 	addiu	$t6,$t9,-1
/*     b704:	31cf03ff */ 	andi	$t7,$t6,0x3ff
/*     b708:	000f6880 */ 	sll	$t5,$t7,0x2
/*     b70c:	2459ffff */ 	addiu	$t9,$v0,-1
/*     b710:	332e03ff */ 	andi	$t6,$t9,0x3ff
/*     b714:	000e7b80 */ 	sll	$t7,$t6,0xe
/*     b718:	01a1c025 */ 	or	$t8,$t5,$at
/*     b71c:	030f6825 */ 	or	$t5,$t8,$t7
/*     b720:	00c01825 */ 	or	$v1,$a2,$zero
/*     b724:	ac8d0000 */ 	sw	$t5,0x0($a0)
/*     b728:	ac800004 */ 	sw	$zero,0x4($a0)
/*     b72c:	3c19e700 */ 	lui	$t9,0xe700
/*     b730:	ac790000 */ 	sw	$t9,0x0($v1)
/*     b734:	ac600004 */ 	sw	$zero,0x4($v1)
/*     b738:	24c60008 */ 	addiu	$a2,$a2,0x8
.L0000b73c:
/*     b73c:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b740:	0c002f06 */ 	jal	viGetHeight
/*     b744:	afac0084 */ 	sw	$t4,0x84($sp)
/*     b748:	8fac0084 */ 	lw	$t4,0x84($sp)
/*     b74c:	3c0b800a */ 	lui	$t3,%hi(g_Vars)
/*     b750:	256b9fc0 */ 	addiu	$t3,$t3,%lo(g_Vars)
/*     b754:	000c7080 */ 	sll	$t6,$t4,0x2
/*     b758:	016e2821 */ 	addu	$a1,$t3,$t6
/*     b75c:	8ca30064 */ 	lw	$v1,0x64($a1)
/*     b760:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b764:	84780636 */ 	lh	$t8,0x636($v1)
/*     b768:	846f0632 */ 	lh	$t7,0x632($v1)
/*     b76c:	030f6821 */ 	addu	$t5,$t8,$t7
/*     b770:	01a2082a */ 	slt	$at,$t5,$v0
/*     b774:	50200023 */ 	beqzl	$at,.L0000b804
/*     b778:	00c02025 */ 	or	$a0,$a2,$zero
/*     b77c:	afa60074 */ 	sw	$a2,0x74($sp)
/*     b780:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b784:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b788:	0c002f02 */ 	jal	viGetWidth
/*     b78c:	afa5002c */ 	sw	$a1,0x2c($sp)
/*     b790:	0c002f06 */ 	jal	viGetHeight
/*     b794:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b798:	87ad0056 */ 	lh	$t5,0x56($sp)
/*     b79c:	2459ffff */ 	addiu	$t9,$v0,-1
/*     b7a0:	332e03ff */ 	andi	$t6,$t9,0x3ff
/*     b7a4:	000ec080 */ 	sll	$t8,$t6,0x2
/*     b7a8:	3c01f600 */ 	lui	$at,0xf600
/*     b7ac:	25b9ffff */ 	addiu	$t9,$t5,-1
/*     b7b0:	8fa70074 */ 	lw	$a3,0x74($sp)
/*     b7b4:	332e03ff */ 	andi	$t6,$t9,0x3ff
/*     b7b8:	03017825 */ 	or	$t7,$t8,$at
/*     b7bc:	8fa5002c */ 	lw	$a1,0x2c($sp)
/*     b7c0:	000ec380 */ 	sll	$t8,$t6,0xe
/*     b7c4:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b7c8:	01f86825 */ 	or	$t5,$t7,$t8
/*     b7cc:	aced0000 */ 	sw	$t5,0x0($a3)
/*     b7d0:	8ca30064 */ 	lw	$v1,0x64($a1)
/*     b7d4:	00c02025 */ 	or	$a0,$a2,$zero
/*     b7d8:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b7dc:	84790632 */ 	lh	$t9,0x632($v1)
/*     b7e0:	846e0636 */ 	lh	$t6,0x636($v1)
/*     b7e4:	032e7821 */ 	addu	$t7,$t9,$t6
/*     b7e8:	31f803ff */ 	andi	$t8,$t7,0x3ff
/*     b7ec:	00186880 */ 	sll	$t5,$t8,0x2
/*     b7f0:	aced0004 */ 	sw	$t5,0x4($a3)
/*     b7f4:	3c19e700 */ 	lui	$t9,0xe700
/*     b7f8:	ac990000 */ 	sw	$t9,0x0($a0)
/*     b7fc:	ac800004 */ 	sw	$zero,0x4($a0)
/*     b800:	00c02025 */ 	or	$a0,$a2,$zero
.L0000b804:
/*     b804:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b808:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b80c:	0c002f02 */ 	jal	viGetWidth
/*     b810:	afa4006c */ 	sw	$a0,0x6c($sp)
/*     b814:	8fae0080 */ 	lw	$t6,0x80($sp)
/*     b818:	3c0b800a */ 	lui	$t3,%hi(g_Vars)
/*     b81c:	256b9fc0 */ 	addiu	$t3,$t3,%lo(g_Vars)
/*     b820:	000e7880 */ 	sll	$t7,$t6,0x2
/*     b824:	016f6021 */ 	addu	$t4,$t3,$t7
/*     b828:	8d980064 */ 	lw	$t8,0x64($t4)
/*     b82c:	8fa4006c */ 	lw	$a0,0x6c($sp)
/*     b830:	3c01f600 */ 	lui	$at,0xf600
/*     b834:	870d0636 */ 	lh	$t5,0x636($t8)
/*     b838:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b83c:	00002825 */ 	or	$a1,$zero,$zero
/*     b840:	25b9ffff */ 	addiu	$t9,$t5,-1
/*     b844:	332e03ff */ 	andi	$t6,$t9,0x3ff
/*     b848:	000e7880 */ 	sll	$t7,$t6,0x2
/*     b84c:	244dffff */ 	addiu	$t5,$v0,-1
/*     b850:	31b903ff */ 	andi	$t9,$t5,0x3ff
/*     b854:	00197380 */ 	sll	$t6,$t9,0xe
/*     b858:	01e1c025 */ 	or	$t8,$t7,$at
/*     b85c:	030e7825 */ 	or	$t7,$t8,$t6
/*     b860:	ac8f0000 */ 	sw	$t7,0x0($a0)
/*     b864:	8d8d0064 */ 	lw	$t5,0x64($t4)
/*     b868:	00c01825 */ 	or	$v1,$a2,$zero
/*     b86c:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b870:	85b90636 */ 	lh	$t9,0x636($t5)
/*     b874:	3c0de700 */ 	lui	$t5,0xe700
/*     b878:	2738ffff */ 	addiu	$t8,$t9,-1
/*     b87c:	330e03ff */ 	andi	$t6,$t8,0x3ff
/*     b880:	000e7880 */ 	sll	$t7,$t6,0x2
/*     b884:	ac8f0004 */ 	sw	$t7,0x4($a0)
/*     b888:	ac600004 */ 	sw	$zero,0x4($v1)
/*     b88c:	ac6d0000 */ 	sw	$t5,0x0($v1)
/*     b890:	8d69006c */ 	lw	$t1,0x6c($t3)
/*     b894:	11200003 */ 	beqz	$t1,.L0000b8a4
/*     b898:	00000000 */ 	nop
/*     b89c:	10000001 */ 	b	.L0000b8a4
/*     b8a0:	24050001 */ 	addiu	$a1,$zero,0x1
.L0000b8a4:
/*     b8a4:	8d670068 */ 	lw	$a3,0x68($t3)
/*     b8a8:	00002025 */ 	or	$a0,$zero,$zero
/*     b8ac:	00001825 */ 	or	$v1,$zero,$zero
/*     b8b0:	10e00003 */ 	beqz	$a3,.L0000b8c0
/*     b8b4:	00000000 */ 	nop
/*     b8b8:	10000001 */ 	b	.L0000b8c0
/*     b8bc:	24040001 */ 	addiu	$a0,$zero,0x1
.L0000b8c0:
/*     b8c0:	8d680064 */ 	lw	$t0,0x64($t3)
/*     b8c4:	00001025 */ 	or	$v0,$zero,$zero
/*     b8c8:	11000003 */ 	beqz	$t0,.L0000b8d8
/*     b8cc:	00000000 */ 	nop
/*     b8d0:	10000001 */ 	b	.L0000b8d8
/*     b8d4:	24030001 */ 	addiu	$v1,$zero,0x1
.L0000b8d8:
/*     b8d8:	8d6a0070 */ 	lw	$t2,0x70($t3)
/*     b8dc:	11400003 */ 	beqz	$t2,.L0000b8ec
/*     b8e0:	00000000 */ 	nop
/*     b8e4:	10000001 */ 	b	.L0000b8ec
/*     b8e8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0000b8ec:
/*     b8ec:	0043c821 */ 	addu	$t9,$v0,$v1
/*     b8f0:	0324c021 */ 	addu	$t8,$t9,$a0
/*     b8f4:	03057021 */ 	addu	$t6,$t8,$a1
/*     b8f8:	29c10003 */ 	slti	$at,$t6,0x3
/*     b8fc:	50200024 */ 	beqzl	$at,.L0000b990
/*     b900:	8d6e006c */ 	lw	$t6,0x6c($t3)
/*     b904:	11200003 */ 	beqz	$t1,.L0000b914
/*     b908:	24010002 */ 	addiu	$at,$zero,0x2
/*     b90c:	10000002 */ 	b	.L0000b918
/*     b910:	24050001 */ 	addiu	$a1,$zero,0x1
.L0000b914:
/*     b914:	00002825 */ 	or	$a1,$zero,$zero
.L0000b918:
/*     b918:	10e00003 */ 	beqz	$a3,.L0000b928
/*     b91c:	00001825 */ 	or	$v1,$zero,$zero
/*     b920:	10000001 */ 	b	.L0000b928
/*     b924:	24030001 */ 	addiu	$v1,$zero,0x1
.L0000b928:
/*     b928:	11000003 */ 	beqz	$t0,.L0000b938
/*     b92c:	00002025 */ 	or	$a0,$zero,$zero
/*     b930:	10000001 */ 	b	.L0000b938
/*     b934:	24040001 */ 	addiu	$a0,$zero,0x1
.L0000b938:
/*     b938:	11400003 */ 	beqz	$t2,.L0000b948
/*     b93c:	00001025 */ 	or	$v0,$zero,$zero
/*     b940:	10000001 */ 	b	.L0000b948
/*     b944:	24020001 */ 	addiu	$v0,$zero,0x1
.L0000b948:
/*     b948:	00447821 */ 	addu	$t7,$v0,$a0
/*     b94c:	01e36821 */ 	addu	$t5,$t7,$v1
/*     b950:	01a5c821 */ 	addu	$t9,$t5,$a1
/*     b954:	5721004e */ 	bnel	$t9,$at,.L0000ba90
/*     b958:	8d6f006c */ 	lw	$t7,0x6c($t3)
/*     b95c:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b960:	0fc54bcd */ 	jal	optionsGetScreenSplit
/*     b964:	afac001c */ 	sw	$t4,0x1c($sp)
/*     b968:	3c0b800a */ 	lui	$t3,%hi(g_Vars)
/*     b96c:	24010001 */ 	addiu	$at,$zero,0x1
/*     b970:	256b9fc0 */ 	addiu	$t3,$t3,%lo(g_Vars)
/*     b974:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b978:	10410004 */ 	beq	$v0,$at,.L0000b98c
/*     b97c:	8fac001c */ 	lw	$t4,0x1c($sp)
/*     b980:	917804e0 */ 	lbu	$t8,0x4e0($t3)
/*     b984:	53000042 */ 	beqzl	$t8,.L0000ba90
/*     b988:	8d6f006c */ 	lw	$t7,0x6c($t3)
.L0000b98c:
/*     b98c:	8d6e006c */ 	lw	$t6,0x6c($t3)
.L0000b990:
/*     b990:	8d670068 */ 	lw	$a3,0x68($t3)
/*     b994:	8d680064 */ 	lw	$t0,0x64($t3)
/*     b998:	11c00003 */ 	beqz	$t6,.L0000b9a8
/*     b99c:	8d6a0070 */ 	lw	$t2,0x70($t3)
/*     b9a0:	10000002 */ 	b	.L0000b9ac
/*     b9a4:	24050001 */ 	addiu	$a1,$zero,0x1
.L0000b9a8:
/*     b9a8:	00002825 */ 	or	$a1,$zero,$zero
.L0000b9ac:
/*     b9ac:	10e00003 */ 	beqz	$a3,.L0000b9bc
/*     b9b0:	24010002 */ 	addiu	$at,$zero,0x2
/*     b9b4:	10000002 */ 	b	.L0000b9c0
/*     b9b8:	24040001 */ 	addiu	$a0,$zero,0x1
.L0000b9bc:
/*     b9bc:	00002025 */ 	or	$a0,$zero,$zero
.L0000b9c0:
/*     b9c0:	11000003 */ 	beqz	$t0,.L0000b9d0
/*     b9c4:	00001825 */ 	or	$v1,$zero,$zero
/*     b9c8:	10000001 */ 	b	.L0000b9d0
/*     b9cc:	24030001 */ 	addiu	$v1,$zero,0x1
.L0000b9d0:
/*     b9d0:	11400003 */ 	beqz	$t2,.L0000b9e0
/*     b9d4:	00001025 */ 	or	$v0,$zero,$zero
/*     b9d8:	10000001 */ 	b	.L0000b9e0
/*     b9dc:	24020001 */ 	addiu	$v0,$zero,0x1
.L0000b9e0:
/*     b9e0:	00437821 */ 	addu	$t7,$v0,$v1
/*     b9e4:	01e46821 */ 	addu	$t5,$t7,$a0
/*     b9e8:	01a5c821 */ 	addu	$t9,$t5,$a1
/*     b9ec:	17210004 */ 	bne	$t9,$at,.L0000ba00
/*     b9f0:	00c02825 */ 	or	$a1,$a2,$zero
/*     b9f4:	3c0c800a */ 	lui	$t4,%hi(g_Vars)
/*     b9f8:	258c9fc0 */ 	addiu	$t4,$t4,%lo(g_Vars)
/*     b9fc:	afa00080 */ 	sw	$zero,0x80($sp)
.L0000ba00:
/*     ba00:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     ba04:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     ba08:	afa50064 */ 	sw	$a1,0x64($sp)
/*     ba0c:	0c002f06 */ 	jal	viGetHeight
/*     ba10:	afac001c */ 	sw	$t4,0x1c($sp)
/*     ba14:	8fac001c */ 	lw	$t4,0x1c($sp)
/*     ba18:	8fa50064 */ 	lw	$a1,0x64($sp)
/*     ba1c:	3c01f600 */ 	lui	$at,0xf600
/*     ba20:	8d830064 */ 	lw	$v1,0x64($t4)
/*     ba24:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     ba28:	3c0b800a */ 	lui	$t3,%hi(g_Vars)
/*     ba2c:	84780634 */ 	lh	$t8,0x634($v1)
/*     ba30:	846e0630 */ 	lh	$t6,0x630($v1)
/*     ba34:	00c02025 */ 	or	$a0,$a2,$zero
/*     ba38:	256b9fc0 */ 	addiu	$t3,$t3,%lo(g_Vars)
/*     ba3c:	030e7821 */ 	addu	$t7,$t8,$t6
/*     ba40:	31ed03ff */ 	andi	$t5,$t7,0x3ff
/*     ba44:	2458ffff */ 	addiu	$t8,$v0,-1
/*     ba48:	330e03ff */ 	andi	$t6,$t8,0x3ff
/*     ba4c:	000e7880 */ 	sll	$t7,$t6,0x2
/*     ba50:	000dcb80 */ 	sll	$t9,$t5,0xe
/*     ba54:	01e16825 */ 	or	$t5,$t7,$at
/*     ba58:	01b9c025 */ 	or	$t8,$t5,$t9
/*     ba5c:	acb80000 */ 	sw	$t8,0x0($a1)
/*     ba60:	8d830064 */ 	lw	$v1,0x64($t4)
/*     ba64:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     ba68:	846e0630 */ 	lh	$t6,0x630($v1)
/*     ba6c:	846f0634 */ 	lh	$t7,0x634($v1)
/*     ba70:	01cf6821 */ 	addu	$t5,$t6,$t7
/*     ba74:	31b903ff */ 	andi	$t9,$t5,0x3ff
/*     ba78:	0019c380 */ 	sll	$t8,$t9,0xe
/*     ba7c:	acb80004 */ 	sw	$t8,0x4($a1)
/*     ba80:	3c0ee700 */ 	lui	$t6,0xe700
/*     ba84:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*     ba88:	ac800004 */ 	sw	$zero,0x4($a0)
/*     ba8c:	8d6f006c */ 	lw	$t7,0x6c($t3)
.L0000ba90:
/*     ba90:	8d670068 */ 	lw	$a3,0x68($t3)
/*     ba94:	8d680064 */ 	lw	$t0,0x64($t3)
/*     ba98:	11e00003 */ 	beqz	$t7,.L0000baa8
/*     ba9c:	8d6a0070 */ 	lw	$t2,0x70($t3)
/*     baa0:	10000002 */ 	b	.L0000baac
/*     baa4:	24050001 */ 	addiu	$a1,$zero,0x1
.L0000baa8:
/*     baa8:	00002825 */ 	or	$a1,$zero,$zero
.L0000baac:
/*     baac:	10e00003 */ 	beqz	$a3,.L0000babc
/*     bab0:	24010003 */ 	addiu	$at,$zero,0x3
/*     bab4:	10000002 */ 	b	.L0000bac0
/*     bab8:	24040001 */ 	addiu	$a0,$zero,0x1
.L0000babc:
/*     babc:	00002025 */ 	or	$a0,$zero,$zero
.L0000bac0:
/*     bac0:	11000003 */ 	beqz	$t0,.L0000bad0
/*     bac4:	00001825 */ 	or	$v1,$zero,$zero
/*     bac8:	10000001 */ 	b	.L0000bad0
/*     bacc:	24030001 */ 	addiu	$v1,$zero,0x1
.L0000bad0:
/*     bad0:	11400003 */ 	beqz	$t2,.L0000bae0
/*     bad4:	00001025 */ 	or	$v0,$zero,$zero
/*     bad8:	10000001 */ 	b	.L0000bae0
/*     badc:	24020001 */ 	addiu	$v0,$zero,0x1
.L0000bae0:
/*     bae0:	00436821 */ 	addu	$t5,$v0,$v1
/*     bae4:	01a4c821 */ 	addu	$t9,$t5,$a0
/*     bae8:	0325c021 */ 	addu	$t8,$t9,$a1
/*     baec:	57010028 */ 	bnel	$t8,$at,.L0000bb90
/*     baf0:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     baf4:	afa6005c */ 	sw	$a2,0x5c($sp)
/*     baf8:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     bafc:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     bb00:	0c002f02 */ 	jal	viGetWidth
/*     bb04:	afac001c */ 	sw	$t4,0x1c($sp)
/*     bb08:	0c002f06 */ 	jal	viGetHeight
/*     bb0c:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     bb10:	87b80056 */ 	lh	$t8,0x56($sp)
/*     bb14:	244effff */ 	addiu	$t6,$v0,-1
/*     bb18:	31cf03ff */ 	andi	$t7,$t6,0x3ff
/*     bb1c:	000f6880 */ 	sll	$t5,$t7,0x2
/*     bb20:	3c01f600 */ 	lui	$at,0xf600
/*     bb24:	270effff */ 	addiu	$t6,$t8,-1
/*     bb28:	8fa5005c */ 	lw	$a1,0x5c($sp)
/*     bb2c:	31cf03ff */ 	andi	$t7,$t6,0x3ff
/*     bb30:	01a1c825 */ 	or	$t9,$t5,$at
/*     bb34:	8fac001c */ 	lw	$t4,0x1c($sp)
/*     bb38:	000f6b80 */ 	sll	$t5,$t7,0xe
/*     bb3c:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     bb40:	032dc025 */ 	or	$t8,$t9,$t5
/*     bb44:	acb80000 */ 	sw	$t8,0x0($a1)
/*     bb48:	8d830064 */ 	lw	$v1,0x64($t4)
/*     bb4c:	00c02025 */ 	or	$a0,$a2,$zero
/*     bb50:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     bb54:	846e0634 */ 	lh	$t6,0x634($v1)
/*     bb58:	846f0630 */ 	lh	$t7,0x630($v1)
/*     bb5c:	01cfc821 */ 	addu	$t9,$t6,$t7
/*     bb60:	846f0636 */ 	lh	$t7,0x636($v1)
/*     bb64:	272d0001 */ 	addiu	$t5,$t9,0x1
/*     bb68:	31b803ff */ 	andi	$t8,$t5,0x3ff
/*     bb6c:	31f903ff */ 	andi	$t9,$t7,0x3ff
/*     bb70:	00196880 */ 	sll	$t5,$t9,0x2
/*     bb74:	00187380 */ 	sll	$t6,$t8,0xe
/*     bb78:	01aec025 */ 	or	$t8,$t5,$t6
/*     bb7c:	acb80004 */ 	sw	$t8,0x4($a1)
/*     bb80:	3c0fe700 */ 	lui	$t7,0xe700
/*     bb84:	ac8f0000 */ 	sw	$t7,0x0($a0)
/*     bb88:	ac800004 */ 	sw	$zero,0x4($a0)
.L0000bb8c:
/*     bb8c:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0000bb90:
/*     bb90:	27bd00a8 */ 	addiu	$sp,$sp,0xa8
/*     bb94:	00c01025 */ 	or	$v0,$a2,$zero
/*     bb98:	03e00008 */ 	jr	$ra
/*     bb9c:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel func0000b330
/*     b4b0:	27bdff58 */ 	addiu	$sp,$sp,-168
/*     b4b4:	afbf0014 */ 	sw	$ra,0x14($sp)
/*     b4b8:	3c0eba00 */ 	lui	$t6,0xba00
/*     b4bc:	35ce1402 */ 	ori	$t6,$t6,0x1402
/*     b4c0:	24830008 */ 	addiu	$v1,$a0,0x8
/*     b4c4:	3c0f0030 */ 	lui	$t7,0x30
/*     b4c8:	ac8f0004 */ 	sw	$t7,0x4($a0)
/*     b4cc:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*     b4d0:	3c18ed00 */ 	lui	$t8,0xed00
/*     b4d4:	ac780000 */ 	sw	$t8,0x0($v1)
/*     b4d8:	24660008 */ 	addiu	$a2,$v1,0x8
/*     b4dc:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b4e0:	0c002f77 */ 	jal	viGetWidth
/*     b4e4:	afa300a0 */ 	sw	$v1,0xa0($sp)
/*     b4e8:	0c002f7b */ 	jal	viGetHeight
/*     b4ec:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b4f0:	44822000 */ 	mtc1	$v0,$f4
/*     b4f4:	87af0056 */ 	lh	$t7,0x56($sp)
/*     b4f8:	3c014080 */ 	lui	$at,0x4080
/*     b4fc:	468021a0 */ 	cvt.s.w	$f6,$f4
/*     b500:	448f8000 */ 	mtc1	$t7,$f16
/*     b504:	44810000 */ 	mtc1	$at,$f0
/*     b508:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b50c:	3c0b800a */ 	lui	$t3,0x800a
/*     b510:	468084a0 */ 	cvt.s.w	$f18,$f16
/*     b514:	46003202 */ 	mul.s	$f8,$f6,$f0
/*     b518:	00c01825 */ 	or	$v1,$a2,$zero
/*     b51c:	256be6c0 */ 	addiu	$t3,$t3,-6464
/*     b520:	24010001 */ 	addiu	$at,$zero,0x1
/*     b524:	00002825 */ 	or	$a1,$zero,$zero
/*     b528:	46009102 */ 	mul.s	$f4,$f18,$f0
/*     b52c:	00002025 */ 	or	$a0,$zero,$zero
/*     b530:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b534:	4600428d */ 	trunc.w.s	$f10,$f8
/*     b538:	4600218d */ 	trunc.w.s	$f6,$f4
/*     b53c:	440d5000 */ 	mfc1	$t5,$f10
/*     b540:	44193000 */ 	mfc1	$t9,$f6
/*     b544:	31ae0fff */ 	andi	$t6,$t5,0xfff
/*     b548:	332d0fff */ 	andi	$t5,$t9,0xfff
/*     b54c:	8fb900a0 */ 	lw	$t9,0xa0($sp)
/*     b550:	000d7b00 */ 	sll	$t7,$t5,0xc
/*     b554:	01cfc025 */ 	or	$t8,$t6,$t7
/*     b558:	3c0e0001 */ 	lui	$t6,0x1
/*     b55c:	af380004 */ 	sw	$t8,0x4($t9)
/*     b560:	35ce0001 */ 	ori	$t6,$t6,0x1
/*     b564:	3c0df700 */ 	lui	$t5,0xf700
/*     b568:	ac6d0000 */ 	sw	$t5,0x0($v1)
/*     b56c:	ac6e0004 */ 	sw	$t6,0x4($v1)
/*     b570:	8d6f006c */ 	lw	$t7,0x6c($t3)
/*     b574:	00001825 */ 	or	$v1,$zero,$zero
/*     b578:	11e00003 */ 	beqz	$t7,.NB0000b588
/*     b57c:	00000000 */ 	sll	$zero,$zero,0x0
/*     b580:	10000001 */ 	beqz	$zero,.NB0000b588
/*     b584:	24050001 */ 	addiu	$a1,$zero,0x1
.NB0000b588:
/*     b588:	8d780068 */ 	lw	$t8,0x68($t3)
/*     b58c:	00001025 */ 	or	$v0,$zero,$zero
/*     b590:	13000003 */ 	beqz	$t8,.NB0000b5a0
/*     b594:	00000000 */ 	sll	$zero,$zero,0x0
/*     b598:	10000001 */ 	beqz	$zero,.NB0000b5a0
/*     b59c:	24040001 */ 	addiu	$a0,$zero,0x1
.NB0000b5a0:
/*     b5a0:	8d790064 */ 	lw	$t9,0x64($t3)
/*     b5a4:	13200003 */ 	beqz	$t9,.NB0000b5b4
/*     b5a8:	00000000 */ 	sll	$zero,$zero,0x0
/*     b5ac:	10000001 */ 	beqz	$zero,.NB0000b5b4
/*     b5b0:	24030001 */ 	addiu	$v1,$zero,0x1
.NB0000b5b4:
/*     b5b4:	8d6d0070 */ 	lw	$t5,0x70($t3)
/*     b5b8:	11a00003 */ 	beqz	$t5,.NB0000b5c8
/*     b5bc:	00000000 */ 	sll	$zero,$zero,0x0
/*     b5c0:	10000001 */ 	beqz	$zero,.NB0000b5c8
/*     b5c4:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0000b5c8:
/*     b5c8:	00437021 */ 	addu	$t6,$v0,$v1
/*     b5cc:	01c47821 */ 	addu	$t7,$t6,$a0
/*     b5d0:	01e5c021 */ 	addu	$t8,$t7,$a1
/*     b5d4:	13010019 */ 	beq	$t8,$at,.NB0000b63c
/*     b5d8:	00000000 */ 	sll	$zero,$zero,0x0
/*     b5dc:	8d790298 */ 	lw	$t9,0x298($t3)
/*     b5e0:	3c0e8007 */ 	lui	$t6,0x8007
/*     b5e4:	07210004 */ 	bgez	$t9,.NB0000b5f8
/*     b5e8:	00000000 */ 	sll	$zero,$zero,0x0
/*     b5ec:	8d6d029c */ 	lw	$t5,0x29c($t3)
/*     b5f0:	05a2005f */ 	bltzl	$t5,.NB0000b770
/*     b5f4:	8d6f0290 */ 	lw	$t7,0x290($t3)
.NB0000b5f8:
/*     b5f8:	8dce2e24 */ 	lw	$t6,0x2e24($t6)
/*     b5fc:	3c0f8006 */ 	lui	$t7,0x8006
/*     b600:	11c00004 */ 	beqz	$t6,.NB0000b614
/*     b604:	00000000 */ 	sll	$zero,$zero,0x0
/*     b608:	8deff2f0 */ 	lw	$t7,-0xd10($t7)
/*     b60c:	51e00009 */ 	beqzl	$t7,.NB0000b634
/*     b610:	8d78028c */ 	lw	$t8,0x28c($t3)
.NB0000b614:
/*     b614:	0fc3e4d2 */ 	jal	menuGetRoot
/*     b618:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b61c:	3c0b800a */ 	lui	$t3,0x800a
/*     b620:	24010009 */ 	addiu	$at,$zero,0x9
/*     b624:	256be6c0 */ 	addiu	$t3,$t3,-6464
/*     b628:	14410050 */ 	bne	$v0,$at,.NB0000b76c
/*     b62c:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b630:	8d78028c */ 	lw	$t8,0x28c($t3)
.NB0000b634:
/*     b634:	5700004e */ 	bnezl	$t8,.NB0000b770
/*     b638:	8d6f0290 */ 	lw	$t7,0x290($t3)
.NB0000b63c:
/*     b63c:	0c002fb9 */ 	jal	viGetViewTop
/*     b640:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b644:	1840001a */ 	blez	$v0,.NB0000b6b0
/*     b648:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b64c:	afa60098 */ 	sw	$a2,0x98($sp)
/*     b650:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b654:	0c002f77 */ 	jal	viGetWidth
/*     b658:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b65c:	0c002fb9 */ 	jal	viGetViewTop
/*     b660:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b664:	87b80056 */ 	lh	$t8,0x56($sp)
/*     b668:	2459ffff */ 	addiu	$t9,$v0,-1
/*     b66c:	332d03ff */ 	andi	$t5,$t9,0x3ff
/*     b670:	000d7080 */ 	sll	$t6,$t5,0x2
/*     b674:	8fa40098 */ 	lw	$a0,0x98($sp)
/*     b678:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b67c:	3c01f600 */ 	lui	$at,0xf600
/*     b680:	2719ffff */ 	addiu	$t9,$t8,-1
/*     b684:	332d03ff */ 	andi	$t5,$t9,0x3ff
/*     b688:	01c17825 */ 	or	$t7,$t6,$at
/*     b68c:	000d7380 */ 	sll	$t6,$t5,0xe
/*     b690:	01eec025 */ 	or	$t8,$t7,$t6
/*     b694:	00c01825 */ 	or	$v1,$a2,$zero
/*     b698:	ac980000 */ 	sw	$t8,0x0($a0)
/*     b69c:	ac800004 */ 	sw	$zero,0x4($a0)
/*     b6a0:	3c19e700 */ 	lui	$t9,0xe700
/*     b6a4:	ac790000 */ 	sw	$t9,0x0($v1)
/*     b6a8:	ac600004 */ 	sw	$zero,0x4($v1)
/*     b6ac:	24c60008 */ 	addiu	$a2,$a2,0x8
.NB0000b6b0:
/*     b6b0:	0c002f9b */ 	jal	viGetViewHeight
/*     b6b4:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b6b8:	0c002fb9 */ 	jal	viGetViewTop
/*     b6bc:	a7a20042 */ 	sh	$v0,0x42($sp)
/*     b6c0:	0c002f7b */ 	jal	viGetHeight
/*     b6c4:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b6c8:	87ad0056 */ 	lh	$t5,0x56($sp)
/*     b6cc:	87af0042 */ 	lh	$t7,0x42($sp)
/*     b6d0:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b6d4:	01af7021 */ 	addu	$t6,$t5,$t7
/*     b6d8:	01c2082a */ 	slt	$at,$t6,$v0
/*     b6dc:	50200195 */ 	beqzl	$at,.NB0000bd34
/*     b6e0:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     b6e4:	afa60090 */ 	sw	$a2,0x90($sp)
/*     b6e8:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b6ec:	0c002f77 */ 	jal	viGetWidth
/*     b6f0:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b6f4:	0c002f7b */ 	jal	viGetHeight
/*     b6f8:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b6fc:	87ae0056 */ 	lh	$t6,0x56($sp)
/*     b700:	2458ffff */ 	addiu	$t8,$v0,-1
/*     b704:	331903ff */ 	andi	$t9,$t8,0x3ff
/*     b708:	00196880 */ 	sll	$t5,$t9,0x2
/*     b70c:	25d8ffff */ 	addiu	$t8,$t6,-1
/*     b710:	331903ff */ 	andi	$t9,$t8,0x3ff
/*     b714:	3c01f600 */ 	lui	$at,0xf600
/*     b718:	01a17825 */ 	or	$t7,$t5,$at
/*     b71c:	8fb80090 */ 	lw	$t8,0x90($sp)
/*     b720:	00196b80 */ 	sll	$t5,$t9,0xe
/*     b724:	01ed7025 */ 	or	$t6,$t7,$t5
/*     b728:	0c002fb9 */ 	jal	viGetViewTop
/*     b72c:	af0e0000 */ 	sw	$t6,0x0($t8)
/*     b730:	0c002f9b */ 	jal	viGetViewHeight
/*     b734:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b738:	87b90056 */ 	lh	$t9,0x56($sp)
/*     b73c:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b740:	8fb80090 */ 	lw	$t8,0x90($sp)
/*     b744:	00597821 */ 	addu	$t7,$v0,$t9
/*     b748:	31ed03ff */ 	andi	$t5,$t7,0x3ff
/*     b74c:	000d7080 */ 	sll	$t6,$t5,0x2
/*     b750:	00c01825 */ 	or	$v1,$a2,$zero
/*     b754:	3c19e700 */ 	lui	$t9,0xe700
/*     b758:	af0e0004 */ 	sw	$t6,0x4($t8)
/*     b75c:	ac600004 */ 	sw	$zero,0x4($v1)
/*     b760:	ac790000 */ 	sw	$t9,0x0($v1)
/*     b764:	10000172 */ 	beqz	$zero,.NB0000bd30
/*     b768:	24c60008 */ 	addiu	$a2,$a2,0x8
.NB0000b76c:
/*     b76c:	8d6f0290 */ 	lw	$t7,0x290($t3)
.NB0000b770:
/*     b770:	00006025 */ 	or	$t4,$zero,$zero
/*     b774:	24010002 */ 	addiu	$at,$zero,0x2
/*     b778:	55e0016e */ 	bnezl	$t7,.NB0000bd34
/*     b77c:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     b780:	8d69006c */ 	lw	$t1,0x6c($t3)
/*     b784:	afa00080 */ 	sw	$zero,0x80($sp)
/*     b788:	8d670068 */ 	lw	$a3,0x68($t3)
/*     b78c:	8d680064 */ 	lw	$t0,0x64($t3)
/*     b790:	11200003 */ 	beqz	$t1,.NB0000b7a0
/*     b794:	8d6a0070 */ 	lw	$t2,0x70($t3)
/*     b798:	10000002 */ 	beqz	$zero,.NB0000b7a4
/*     b79c:	24050001 */ 	addiu	$a1,$zero,0x1
.NB0000b7a0:
/*     b7a0:	00002825 */ 	or	$a1,$zero,$zero
.NB0000b7a4:
/*     b7a4:	50e00004 */ 	beqzl	$a3,.NB0000b7b8
/*     b7a8:	00002025 */ 	or	$a0,$zero,$zero
/*     b7ac:	10000002 */ 	beqz	$zero,.NB0000b7b8
/*     b7b0:	24040001 */ 	addiu	$a0,$zero,0x1
/*     b7b4:	00002025 */ 	or	$a0,$zero,$zero
.NB0000b7b8:
/*     b7b8:	51000004 */ 	beqzl	$t0,.NB0000b7cc
/*     b7bc:	00001825 */ 	or	$v1,$zero,$zero
/*     b7c0:	10000002 */ 	beqz	$zero,.NB0000b7cc
/*     b7c4:	24030001 */ 	addiu	$v1,$zero,0x1
/*     b7c8:	00001825 */ 	or	$v1,$zero,$zero
.NB0000b7cc:
/*     b7cc:	51400004 */ 	beqzl	$t2,.NB0000b7e0
/*     b7d0:	00001025 */ 	or	$v0,$zero,$zero
/*     b7d4:	10000002 */ 	beqz	$zero,.NB0000b7e0
/*     b7d8:	24020001 */ 	addiu	$v0,$zero,0x1
/*     b7dc:	00001025 */ 	or	$v0,$zero,$zero
.NB0000b7e0:
/*     b7e0:	00436821 */ 	addu	$t5,$v0,$v1
/*     b7e4:	01a47021 */ 	addu	$t6,$t5,$a0
/*     b7e8:	01c5c021 */ 	addu	$t8,$t6,$a1
/*     b7ec:	17010004 */ 	bne	$t8,$at,.NB0000b800
/*     b7f0:	24190001 */ 	addiu	$t9,$zero,0x1
/*     b7f4:	240c0001 */ 	addiu	$t4,$zero,0x1
/*     b7f8:	10000019 */ 	beqz	$zero,.NB0000b860
/*     b7fc:	afb90080 */ 	sw	$t9,0x80($sp)
.NB0000b800:
/*     b800:	11200003 */ 	beqz	$t1,.NB0000b810
/*     b804:	00002825 */ 	or	$a1,$zero,$zero
/*     b808:	10000001 */ 	beqz	$zero,.NB0000b810
/*     b80c:	24050001 */ 	addiu	$a1,$zero,0x1
.NB0000b810:
/*     b810:	10e00003 */ 	beqz	$a3,.NB0000b820
/*     b814:	00002025 */ 	or	$a0,$zero,$zero
/*     b818:	10000001 */ 	beqz	$zero,.NB0000b820
/*     b81c:	24040001 */ 	addiu	$a0,$zero,0x1
.NB0000b820:
/*     b820:	11000003 */ 	beqz	$t0,.NB0000b830
/*     b824:	00001825 */ 	or	$v1,$zero,$zero
/*     b828:	10000001 */ 	beqz	$zero,.NB0000b830
/*     b82c:	24030001 */ 	addiu	$v1,$zero,0x1
.NB0000b830:
/*     b830:	11400003 */ 	beqz	$t2,.NB0000b840
/*     b834:	00001025 */ 	or	$v0,$zero,$zero
/*     b838:	10000001 */ 	beqz	$zero,.NB0000b840
/*     b83c:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0000b840:
/*     b840:	00437821 */ 	addu	$t7,$v0,$v1
/*     b844:	01e46821 */ 	addu	$t5,$t7,$a0
/*     b848:	01a57021 */ 	addu	$t6,$t5,$a1
/*     b84c:	29c10003 */ 	slti	$at,$t6,0x3
/*     b850:	14200003 */ 	bnez	$at,.NB0000b860
/*     b854:	24180002 */ 	addiu	$t8,$zero,0x2
/*     b858:	240c0002 */ 	addiu	$t4,$zero,0x2
/*     b85c:	afb80080 */ 	sw	$t8,0x80($sp)
.NB0000b860:
/*     b860:	3c19800a */ 	lui	$t9,0x800a
/*     b864:	8f39e724 */ 	lw	$t9,-0x18dc($t9)
/*     b868:	872f0636 */ 	lh	$t7,0x636($t9)
/*     b86c:	19e0001c */ 	blez	$t7,.NB0000b8e0
/*     b870:	00c02025 */ 	or	$a0,$a2,$zero
/*     b874:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b878:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b87c:	afa4007c */ 	sw	$a0,0x7c($sp)
/*     b880:	0c002f77 */ 	jal	viGetWidth
/*     b884:	afac0084 */ 	sw	$t4,0x84($sp)
/*     b888:	3c0d800a */ 	lui	$t5,0x800a
/*     b88c:	8dade724 */ 	lw	$t5,-0x18dc($t5)
/*     b890:	8fa4007c */ 	lw	$a0,0x7c($sp)
/*     b894:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b898:	85ae0636 */ 	lh	$t6,0x636($t5)
/*     b89c:	3c01f600 */ 	lui	$at,0xf600
/*     b8a0:	8fac0084 */ 	lw	$t4,0x84($sp)
/*     b8a4:	25d8ffff */ 	addiu	$t8,$t6,-1
/*     b8a8:	331903ff */ 	andi	$t9,$t8,0x3ff
/*     b8ac:	00197880 */ 	sll	$t7,$t9,0x2
/*     b8b0:	244effff */ 	addiu	$t6,$v0,-1
/*     b8b4:	31d803ff */ 	andi	$t8,$t6,0x3ff
/*     b8b8:	0018cb80 */ 	sll	$t9,$t8,0xe
/*     b8bc:	01e16825 */ 	or	$t5,$t7,$at
/*     b8c0:	01b97825 */ 	or	$t7,$t5,$t9
/*     b8c4:	00c01825 */ 	or	$v1,$a2,$zero
/*     b8c8:	ac8f0000 */ 	sw	$t7,0x0($a0)
/*     b8cc:	ac800004 */ 	sw	$zero,0x4($a0)
/*     b8d0:	3c0ee700 */ 	lui	$t6,0xe700
/*     b8d4:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*     b8d8:	ac600004 */ 	sw	$zero,0x4($v1)
/*     b8dc:	24c60008 */ 	addiu	$a2,$a2,0x8
.NB0000b8e0:
/*     b8e0:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b8e4:	0c002f7b */ 	jal	viGetHeight
/*     b8e8:	afac0084 */ 	sw	$t4,0x84($sp)
/*     b8ec:	8fac0084 */ 	lw	$t4,0x84($sp)
/*     b8f0:	3c0b800a */ 	lui	$t3,0x800a
/*     b8f4:	256be6c0 */ 	addiu	$t3,$t3,-6464
/*     b8f8:	000cc080 */ 	sll	$t8,$t4,0x2
/*     b8fc:	01782821 */ 	addu	$a1,$t3,$t8
/*     b900:	8ca30064 */ 	lw	$v1,0x64($a1)
/*     b904:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b908:	846d0636 */ 	lh	$t5,0x636($v1)
/*     b90c:	84790632 */ 	lh	$t9,0x632($v1)
/*     b910:	01b97821 */ 	addu	$t7,$t5,$t9
/*     b914:	01e2082a */ 	slt	$at,$t7,$v0
/*     b918:	50200023 */ 	beqzl	$at,.NB0000b9a8
/*     b91c:	00c02025 */ 	or	$a0,$a2,$zero
/*     b920:	afa60074 */ 	sw	$a2,0x74($sp)
/*     b924:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b928:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b92c:	0c002f77 */ 	jal	viGetWidth
/*     b930:	afa5002c */ 	sw	$a1,0x2c($sp)
/*     b934:	0c002f7b */ 	jal	viGetHeight
/*     b938:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     b93c:	87af0056 */ 	lh	$t7,0x56($sp)
/*     b940:	244effff */ 	addiu	$t6,$v0,-1
/*     b944:	31d803ff */ 	andi	$t8,$t6,0x3ff
/*     b948:	00186880 */ 	sll	$t5,$t8,0x2
/*     b94c:	3c01f600 */ 	lui	$at,0xf600
/*     b950:	25eeffff */ 	addiu	$t6,$t7,-1
/*     b954:	8fa70074 */ 	lw	$a3,0x74($sp)
/*     b958:	31d803ff */ 	andi	$t8,$t6,0x3ff
/*     b95c:	01a1c825 */ 	or	$t9,$t5,$at
/*     b960:	8fa5002c */ 	lw	$a1,0x2c($sp)
/*     b964:	00186b80 */ 	sll	$t5,$t8,0xe
/*     b968:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b96c:	032d7825 */ 	or	$t7,$t9,$t5
/*     b970:	acef0000 */ 	sw	$t7,0x0($a3)
/*     b974:	8ca30064 */ 	lw	$v1,0x64($a1)
/*     b978:	00c02025 */ 	or	$a0,$a2,$zero
/*     b97c:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b980:	846e0632 */ 	lh	$t6,0x632($v1)
/*     b984:	84780636 */ 	lh	$t8,0x636($v1)
/*     b988:	01d8c821 */ 	addu	$t9,$t6,$t8
/*     b98c:	332d03ff */ 	andi	$t5,$t9,0x3ff
/*     b990:	000d7880 */ 	sll	$t7,$t5,0x2
/*     b994:	acef0004 */ 	sw	$t7,0x4($a3)
/*     b998:	3c0ee700 */ 	lui	$t6,0xe700
/*     b99c:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*     b9a0:	ac800004 */ 	sw	$zero,0x4($a0)
/*     b9a4:	00c02025 */ 	or	$a0,$a2,$zero
.NB0000b9a8:
/*     b9a8:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     b9ac:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     b9b0:	0c002f77 */ 	jal	viGetWidth
/*     b9b4:	afa4006c */ 	sw	$a0,0x6c($sp)
/*     b9b8:	8fb80080 */ 	lw	$t8,0x80($sp)
/*     b9bc:	3c0b800a */ 	lui	$t3,0x800a
/*     b9c0:	256be6c0 */ 	addiu	$t3,$t3,-6464
/*     b9c4:	0018c880 */ 	sll	$t9,$t8,0x2
/*     b9c8:	01796021 */ 	addu	$t4,$t3,$t9
/*     b9cc:	8d8d0064 */ 	lw	$t5,0x64($t4)
/*     b9d0:	8fa4006c */ 	lw	$a0,0x6c($sp)
/*     b9d4:	3c01f600 */ 	lui	$at,0xf600
/*     b9d8:	85af0636 */ 	lh	$t7,0x636($t5)
/*     b9dc:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     b9e0:	00002825 */ 	or	$a1,$zero,$zero
/*     b9e4:	25eeffff */ 	addiu	$t6,$t7,-1
/*     b9e8:	31d803ff */ 	andi	$t8,$t6,0x3ff
/*     b9ec:	0018c880 */ 	sll	$t9,$t8,0x2
/*     b9f0:	244fffff */ 	addiu	$t7,$v0,-1
/*     b9f4:	31ee03ff */ 	andi	$t6,$t7,0x3ff
/*     b9f8:	000ec380 */ 	sll	$t8,$t6,0xe
/*     b9fc:	03216825 */ 	or	$t5,$t9,$at
/*     ba00:	01b8c825 */ 	or	$t9,$t5,$t8
/*     ba04:	ac990000 */ 	sw	$t9,0x0($a0)
/*     ba08:	8d8f0064 */ 	lw	$t7,0x64($t4)
/*     ba0c:	00c01825 */ 	or	$v1,$a2,$zero
/*     ba10:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     ba14:	85ee0636 */ 	lh	$t6,0x636($t7)
/*     ba18:	3c0fe700 */ 	lui	$t7,0xe700
/*     ba1c:	25cdffff */ 	addiu	$t5,$t6,-1
/*     ba20:	31b803ff */ 	andi	$t8,$t5,0x3ff
/*     ba24:	0018c880 */ 	sll	$t9,$t8,0x2
/*     ba28:	ac990004 */ 	sw	$t9,0x4($a0)
/*     ba2c:	ac600004 */ 	sw	$zero,0x4($v1)
/*     ba30:	ac6f0000 */ 	sw	$t7,0x0($v1)
/*     ba34:	8d69006c */ 	lw	$t1,0x6c($t3)
/*     ba38:	11200003 */ 	beqz	$t1,.NB0000ba48
/*     ba3c:	00000000 */ 	sll	$zero,$zero,0x0
/*     ba40:	10000001 */ 	beqz	$zero,.NB0000ba48
/*     ba44:	24050001 */ 	addiu	$a1,$zero,0x1
.NB0000ba48:
/*     ba48:	8d670068 */ 	lw	$a3,0x68($t3)
/*     ba4c:	00002025 */ 	or	$a0,$zero,$zero
/*     ba50:	00001825 */ 	or	$v1,$zero,$zero
/*     ba54:	10e00003 */ 	beqz	$a3,.NB0000ba64
/*     ba58:	00000000 */ 	sll	$zero,$zero,0x0
/*     ba5c:	10000001 */ 	beqz	$zero,.NB0000ba64
/*     ba60:	24040001 */ 	addiu	$a0,$zero,0x1
.NB0000ba64:
/*     ba64:	8d680064 */ 	lw	$t0,0x64($t3)
/*     ba68:	00001025 */ 	or	$v0,$zero,$zero
/*     ba6c:	11000003 */ 	beqz	$t0,.NB0000ba7c
/*     ba70:	00000000 */ 	sll	$zero,$zero,0x0
/*     ba74:	10000001 */ 	beqz	$zero,.NB0000ba7c
/*     ba78:	24030001 */ 	addiu	$v1,$zero,0x1
.NB0000ba7c:
/*     ba7c:	8d6a0070 */ 	lw	$t2,0x70($t3)
/*     ba80:	11400003 */ 	beqz	$t2,.NB0000ba90
/*     ba84:	00000000 */ 	sll	$zero,$zero,0x0
/*     ba88:	10000001 */ 	beqz	$zero,.NB0000ba90
/*     ba8c:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0000ba90:
/*     ba90:	00437021 */ 	addu	$t6,$v0,$v1
/*     ba94:	01c46821 */ 	addu	$t5,$t6,$a0
/*     ba98:	01a5c021 */ 	addu	$t8,$t5,$a1
/*     ba9c:	2b010003 */ 	slti	$at,$t8,0x3
/*     baa0:	50200024 */ 	beqzl	$at,.NB0000bb34
/*     baa4:	8d78006c */ 	lw	$t8,0x6c($t3)
/*     baa8:	11200003 */ 	beqz	$t1,.NB0000bab8
/*     baac:	24010002 */ 	addiu	$at,$zero,0x2
/*     bab0:	10000002 */ 	beqz	$zero,.NB0000babc
/*     bab4:	24050001 */ 	addiu	$a1,$zero,0x1
.NB0000bab8:
/*     bab8:	00002825 */ 	or	$a1,$zero,$zero
.NB0000babc:
/*     babc:	10e00003 */ 	beqz	$a3,.NB0000bacc
/*     bac0:	00001825 */ 	or	$v1,$zero,$zero
/*     bac4:	10000001 */ 	beqz	$zero,.NB0000bacc
/*     bac8:	24030001 */ 	addiu	$v1,$zero,0x1
.NB0000bacc:
/*     bacc:	11000003 */ 	beqz	$t0,.NB0000badc
/*     bad0:	00002025 */ 	or	$a0,$zero,$zero
/*     bad4:	10000001 */ 	beqz	$zero,.NB0000badc
/*     bad8:	24040001 */ 	addiu	$a0,$zero,0x1
.NB0000badc:
/*     badc:	11400003 */ 	beqz	$t2,.NB0000baec
/*     bae0:	00001025 */ 	or	$v0,$zero,$zero
/*     bae4:	10000001 */ 	beqz	$zero,.NB0000baec
/*     bae8:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0000baec:
/*     baec:	0044c821 */ 	addu	$t9,$v0,$a0
/*     baf0:	03237821 */ 	addu	$t7,$t9,$v1
/*     baf4:	01e57021 */ 	addu	$t6,$t7,$a1
/*     baf8:	55c1004e */ 	bnel	$t6,$at,.NB0000bc34
/*     bafc:	8d79006c */ 	lw	$t9,0x6c($t3)
/*     bb00:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     bb04:	0fc53588 */ 	jal	optionsGetScreenSplit
/*     bb08:	afac001c */ 	sw	$t4,0x1c($sp)
/*     bb0c:	3c0b800a */ 	lui	$t3,0x800a
/*     bb10:	24010001 */ 	addiu	$at,$zero,0x1
/*     bb14:	256be6c0 */ 	addiu	$t3,$t3,-6464
/*     bb18:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     bb1c:	10410004 */ 	beq	$v0,$at,.NB0000bb30
/*     bb20:	8fac001c */ 	lw	$t4,0x1c($sp)
/*     bb24:	916d04e0 */ 	lbu	$t5,0x4e0($t3)
/*     bb28:	51a00042 */ 	beqzl	$t5,.NB0000bc34
/*     bb2c:	8d79006c */ 	lw	$t9,0x6c($t3)
.NB0000bb30:
/*     bb30:	8d78006c */ 	lw	$t8,0x6c($t3)
.NB0000bb34:
/*     bb34:	8d670068 */ 	lw	$a3,0x68($t3)
/*     bb38:	8d680064 */ 	lw	$t0,0x64($t3)
/*     bb3c:	13000003 */ 	beqz	$t8,.NB0000bb4c
/*     bb40:	8d6a0070 */ 	lw	$t2,0x70($t3)
/*     bb44:	10000002 */ 	beqz	$zero,.NB0000bb50
/*     bb48:	24050001 */ 	addiu	$a1,$zero,0x1
.NB0000bb4c:
/*     bb4c:	00002825 */ 	or	$a1,$zero,$zero
.NB0000bb50:
/*     bb50:	10e00003 */ 	beqz	$a3,.NB0000bb60
/*     bb54:	24010002 */ 	addiu	$at,$zero,0x2
/*     bb58:	10000002 */ 	beqz	$zero,.NB0000bb64
/*     bb5c:	24040001 */ 	addiu	$a0,$zero,0x1
.NB0000bb60:
/*     bb60:	00002025 */ 	or	$a0,$zero,$zero
.NB0000bb64:
/*     bb64:	11000003 */ 	beqz	$t0,.NB0000bb74
/*     bb68:	00001825 */ 	or	$v1,$zero,$zero
/*     bb6c:	10000001 */ 	beqz	$zero,.NB0000bb74
/*     bb70:	24030001 */ 	addiu	$v1,$zero,0x1
.NB0000bb74:
/*     bb74:	11400003 */ 	beqz	$t2,.NB0000bb84
/*     bb78:	00001025 */ 	or	$v0,$zero,$zero
/*     bb7c:	10000001 */ 	beqz	$zero,.NB0000bb84
/*     bb80:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0000bb84:
/*     bb84:	0043c821 */ 	addu	$t9,$v0,$v1
/*     bb88:	03247821 */ 	addu	$t7,$t9,$a0
/*     bb8c:	01e57021 */ 	addu	$t6,$t7,$a1
/*     bb90:	15c10004 */ 	bne	$t6,$at,.NB0000bba4
/*     bb94:	00c02825 */ 	or	$a1,$a2,$zero
/*     bb98:	3c0c800a */ 	lui	$t4,0x800a
/*     bb9c:	258ce6c0 */ 	addiu	$t4,$t4,-6464
/*     bba0:	afa00080 */ 	sw	$zero,0x80($sp)
.NB0000bba4:
/*     bba4:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     bba8:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     bbac:	afa50064 */ 	sw	$a1,0x64($sp)
/*     bbb0:	0c002f7b */ 	jal	viGetHeight
/*     bbb4:	afac001c */ 	sw	$t4,0x1c($sp)
/*     bbb8:	8fac001c */ 	lw	$t4,0x1c($sp)
/*     bbbc:	8fa50064 */ 	lw	$a1,0x64($sp)
/*     bbc0:	3c01f600 */ 	lui	$at,0xf600
/*     bbc4:	8d830064 */ 	lw	$v1,0x64($t4)
/*     bbc8:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     bbcc:	3c0b800a */ 	lui	$t3,0x800a
/*     bbd0:	846d0634 */ 	lh	$t5,0x634($v1)
/*     bbd4:	84780630 */ 	lh	$t8,0x630($v1)
/*     bbd8:	00c02025 */ 	or	$a0,$a2,$zero
/*     bbdc:	256be6c0 */ 	addiu	$t3,$t3,-6464
/*     bbe0:	01b8c821 */ 	addu	$t9,$t5,$t8
/*     bbe4:	332f03ff */ 	andi	$t7,$t9,0x3ff
/*     bbe8:	244dffff */ 	addiu	$t5,$v0,-1
/*     bbec:	31b803ff */ 	andi	$t8,$t5,0x3ff
/*     bbf0:	0018c880 */ 	sll	$t9,$t8,0x2
/*     bbf4:	000f7380 */ 	sll	$t6,$t7,0xe
/*     bbf8:	03217825 */ 	or	$t7,$t9,$at
/*     bbfc:	01ee6825 */ 	or	$t5,$t7,$t6
/*     bc00:	acad0000 */ 	sw	$t5,0x0($a1)
/*     bc04:	8d830064 */ 	lw	$v1,0x64($t4)
/*     bc08:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     bc0c:	84780630 */ 	lh	$t8,0x630($v1)
/*     bc10:	84790634 */ 	lh	$t9,0x634($v1)
/*     bc14:	03197821 */ 	addu	$t7,$t8,$t9
/*     bc18:	31ee03ff */ 	andi	$t6,$t7,0x3ff
/*     bc1c:	000e6b80 */ 	sll	$t5,$t6,0xe
/*     bc20:	acad0004 */ 	sw	$t5,0x4($a1)
/*     bc24:	3c18e700 */ 	lui	$t8,0xe700
/*     bc28:	ac980000 */ 	sw	$t8,0x0($a0)
/*     bc2c:	ac800004 */ 	sw	$zero,0x4($a0)
/*     bc30:	8d79006c */ 	lw	$t9,0x6c($t3)
.NB0000bc34:
/*     bc34:	8d670068 */ 	lw	$a3,0x68($t3)
/*     bc38:	8d680064 */ 	lw	$t0,0x64($t3)
/*     bc3c:	13200003 */ 	beqz	$t9,.NB0000bc4c
/*     bc40:	8d6a0070 */ 	lw	$t2,0x70($t3)
/*     bc44:	10000002 */ 	beqz	$zero,.NB0000bc50
/*     bc48:	24050001 */ 	addiu	$a1,$zero,0x1
.NB0000bc4c:
/*     bc4c:	00002825 */ 	or	$a1,$zero,$zero
.NB0000bc50:
/*     bc50:	10e00003 */ 	beqz	$a3,.NB0000bc60
/*     bc54:	24010003 */ 	addiu	$at,$zero,0x3
/*     bc58:	10000002 */ 	beqz	$zero,.NB0000bc64
/*     bc5c:	24040001 */ 	addiu	$a0,$zero,0x1
.NB0000bc60:
/*     bc60:	00002025 */ 	or	$a0,$zero,$zero
.NB0000bc64:
/*     bc64:	11000003 */ 	beqz	$t0,.NB0000bc74
/*     bc68:	00001825 */ 	or	$v1,$zero,$zero
/*     bc6c:	10000001 */ 	beqz	$zero,.NB0000bc74
/*     bc70:	24030001 */ 	addiu	$v1,$zero,0x1
.NB0000bc74:
/*     bc74:	11400003 */ 	beqz	$t2,.NB0000bc84
/*     bc78:	00001025 */ 	or	$v0,$zero,$zero
/*     bc7c:	10000001 */ 	beqz	$zero,.NB0000bc84
/*     bc80:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0000bc84:
/*     bc84:	00437821 */ 	addu	$t7,$v0,$v1
/*     bc88:	01e47021 */ 	addu	$t6,$t7,$a0
/*     bc8c:	01c56821 */ 	addu	$t5,$t6,$a1
/*     bc90:	55a10028 */ 	bnel	$t5,$at,.NB0000bd34
/*     bc94:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*     bc98:	afa6005c */ 	sw	$a2,0x5c($sp)
/*     bc9c:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     bca0:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*     bca4:	0c002f77 */ 	jal	viGetWidth
/*     bca8:	afac001c */ 	sw	$t4,0x1c($sp)
/*     bcac:	0c002f7b */ 	jal	viGetHeight
/*     bcb0:	a7a20056 */ 	sh	$v0,0x56($sp)
/*     bcb4:	87ad0056 */ 	lh	$t5,0x56($sp)
/*     bcb8:	2458ffff */ 	addiu	$t8,$v0,-1
/*     bcbc:	331903ff */ 	andi	$t9,$t8,0x3ff
/*     bcc0:	00197880 */ 	sll	$t7,$t9,0x2
/*     bcc4:	3c01f600 */ 	lui	$at,0xf600
/*     bcc8:	25b8ffff */ 	addiu	$t8,$t5,-1
/*     bccc:	8fa5005c */ 	lw	$a1,0x5c($sp)
/*     bcd0:	331903ff */ 	andi	$t9,$t8,0x3ff
/*     bcd4:	01e17025 */ 	or	$t6,$t7,$at
/*     bcd8:	8fac001c */ 	lw	$t4,0x1c($sp)
/*     bcdc:	00197b80 */ 	sll	$t7,$t9,0xe
/*     bce0:	8fa600a8 */ 	lw	$a2,0xa8($sp)
/*     bce4:	01cf6825 */ 	or	$t5,$t6,$t7
/*     bce8:	acad0000 */ 	sw	$t5,0x0($a1)
/*     bcec:	8d830064 */ 	lw	$v1,0x64($t4)
/*     bcf0:	00c02025 */ 	or	$a0,$a2,$zero
/*     bcf4:	24c60008 */ 	addiu	$a2,$a2,0x8
/*     bcf8:	84780634 */ 	lh	$t8,0x634($v1)
/*     bcfc:	84790630 */ 	lh	$t9,0x630($v1)
/*     bd00:	03197021 */ 	addu	$t6,$t8,$t9
/*     bd04:	84790636 */ 	lh	$t9,0x636($v1)
/*     bd08:	25cf0001 */ 	addiu	$t7,$t6,0x1
/*     bd0c:	31ed03ff */ 	andi	$t5,$t7,0x3ff
/*     bd10:	332e03ff */ 	andi	$t6,$t9,0x3ff
/*     bd14:	000e7880 */ 	sll	$t7,$t6,0x2
/*     bd18:	000dc380 */ 	sll	$t8,$t5,0xe
/*     bd1c:	01f86825 */ 	or	$t5,$t7,$t8
/*     bd20:	acad0004 */ 	sw	$t5,0x4($a1)
/*     bd24:	3c19e700 */ 	lui	$t9,0xe700
/*     bd28:	ac990000 */ 	sw	$t9,0x0($a0)
/*     bd2c:	ac800004 */ 	sw	$zero,0x4($a0)
.NB0000bd30:
/*     bd30:	8fbf0014 */ 	lw	$ra,0x14($sp)
.NB0000bd34:
/*     bd34:	27bd00a8 */ 	addiu	$sp,$sp,0xa8
/*     bd38:	00c01025 */ 	or	$v0,$a2,$zero
/*     bd3c:	03e00008 */ 	jr	$ra
/*     bd40:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

#if VERSION < VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func0000bd44nb
/*     bd44:	3c018006 */ 	lui	$at,0x8006
/*     bd48:	03e00008 */ 	jr	$ra
/*     bd4c:	ac24ed2c */ 	sw	$a0,-0x12d4($at)
);

GLOBAL_ASM(
glabel func0000bd50nb
/*     bd50:	3c028006 */ 	lui	$v0,0x8006
/*     bd54:	03e00008 */ 	jr	$ra
/*     bd58:	8c42ed2c */ 	lw	$v0,-0x12d4($v0)
);

GLOBAL_ASM(
glabel func0000bd5cnb
/*     bd5c:	3c018006 */ 	lui	$at,0x8006
/*     bd60:	03e00008 */ 	jr	$ra
/*     bd64:	ac24ed28 */ 	sw	$a0,-0x12d8($at)
);

GLOBAL_ASM(
glabel func0000bd68nb
/*     bd68:	3c028006 */ 	lui	$v0,0x8006
/*     bd6c:	03e00008 */ 	jr	$ra
/*     bd70:	8c42ed28 */ 	lw	$v0,-0x12d8($v0)
);
#endif

void viSetBuf(s16 x, s16 y)
{
	g_ViData->bufx = x;
	g_ViData->bufy = y;
}

s16 viGetBufX(void)
{
	return g_ViData->bufx;
}

s16 viGetBufY(void)
{
	return g_ViData->bufy;
}

void viSetXY(s16 x, s16 y)
{
	g_ViData->x = x;
	g_ViData->y = y;
}

s16 viGetWidth(void)
{
	return g_ViData->x;
}

s16 viGetHeight(void)
{
	return g_ViData->y;
}

void viSetViewSize(s16 x, s16 y)
{
	g_ViData->viewx = x;
	g_ViData->viewy = y;

	currentPlayerSetScreenSize(g_ViData->viewx, g_ViData->viewy);
	currentPlayerSetCameraScale();
}

s16 viGetViewWidth(void)
{
	return g_ViData->viewx;
}

s16 viGetViewHeight(void)
{
	return g_ViData->viewy;
}

void viSetViewPosition(s16 left, s16 top)
{
	g_ViData->viewleft = left;
	g_ViData->viewtop = top;

	currentPlayerSetScreenPosition(g_ViData->viewleft, g_ViData->viewtop);
}

s16 viGetViewLeft(void)
{
	return g_ViData->viewleft;
}

s16 viGetViewTop(void)
{
	return g_ViData->viewtop;
}

void viSetUseZBuf(bool use)
{
	g_ViData->usezbuf = use;
}

void viSetFovY(f32 fovy)
{
	g_ViData->fovy = fovy;

	currentPlayerSetPerspective(g_ViData->znear, g_ViData->fovy, g_ViData->aspect);
	currentPlayerSetCameraScale();
}

void viSetAspect(f32 aspect)
{
	g_ViData->aspect = aspect;

	currentPlayerSetPerspective(g_ViData->znear, g_ViData->fovy, g_ViData->aspect);
	currentPlayerSetCameraScale();
}

f32 viGetAspect(void)
{
	return g_ViData->aspect;
}

void viSetFovAspectAndSize(f32 fovy, f32 aspect, s16 width, s16 height)
{
	g_ViData->fovy = fovy;
	g_ViData->aspect = aspect;
	g_ViData->viewx = width;
	g_ViData->viewy = height;

	currentPlayerSetScreenSize(g_ViData->viewx, g_ViData->viewy);
	currentPlayerSetPerspective(g_ViData->znear, g_ViData->fovy, g_ViData->aspect);
	currentPlayerSetCameraScale();
}

f32 viGetFovY(void)
{
	return g_ViData->fovy;
}

void viSetZRange(f32 near, f32 far)
{
	g_ViData->znear = near;
	g_ViData->zfar = far;

	currentPlayerSetPerspective(g_ViData->znear, g_ViData->fovy, g_ViData->aspect);
	currentPlayerSetCameraScale();
}

void viGetZRange(struct zrange *zrange)
{
	zrange->near = g_ViData->znear;
	zrange->far = g_ViData->zfar;
}

GLOBAL_ASM(
glabel func0000bf04
/*     bf04:	3c0e8006 */ 	lui	$t6,%hi(var8005d598)
/*     bf08:	8dced598 */ 	lw	$t6,%lo(var8005d598)($t6)
/*     bf0c:	00801025 */ 	or	$v0,$a0,$zero
/*     bf10:	3c18f700 */ 	lui	$t8,0xf700
/*     bf14:	11c00013 */ 	beqz	$t6,.L0000bf64
/*     bf18:	00054600 */ 	sll	$t0,$a1,0x18
/*     bf1c:	0005c200 */ 	sll	$t8,$a1,0x8
/*     bf20:	000640c0 */ 	sll	$t0,$a2,0x3
/*     bf24:	310907c0 */ 	andi	$t1,$t0,0x7c0
/*     bf28:	3319f800 */ 	andi	$t9,$t8,0xf800
/*     bf2c:	00075883 */ 	sra	$t3,$a3,0x2
/*     bf30:	316c003e */ 	andi	$t4,$t3,0x3e
/*     bf34:	03295025 */ 	or	$t2,$t9,$t1
/*     bf38:	014c1825 */ 	or	$v1,$t2,$t4
/*     bf3c:	346d0001 */ 	ori	$t5,$v1,0x1
/*     bf40:	00801025 */ 	or	$v0,$a0,$zero
/*     bf44:	3c0ff700 */ 	lui	$t7,0xf700
/*     bf48:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*     bf4c:	000d7400 */ 	sll	$t6,$t5,0x10
/*     bf50:	01cd7825 */ 	or	$t7,$t6,$t5
/*     bf54:	ac4f0004 */ 	sw	$t7,0x4($v0)
/*     bf58:	24840008 */ 	addiu	$a0,$a0,0x8
/*     bf5c:	03e00008 */ 	jr	$ra
/*     bf60:	00801025 */ 	or	$v0,$a0,$zero
.L0000bf64:
/*     bf64:	0006cc00 */ 	sll	$t9,$a2,0x10
/*     bf68:	01194825 */ 	or	$t1,$t0,$t9
/*     bf6c:	00075a00 */ 	sll	$t3,$a3,0x8
/*     bf70:	012b5025 */ 	or	$t2,$t1,$t3
/*     bf74:	354c00ff */ 	ori	$t4,$t2,0xff
/*     bf78:	ac4c0004 */ 	sw	$t4,0x4($v0)
/*     bf7c:	24840008 */ 	addiu	$a0,$a0,0x8
/*     bf80:	ac580000 */ 	sw	$t8,0x0($v0)
/*     bf84:	03e00008 */ 	jr	$ra
/*     bf88:	00801025 */ 	or	$v0,$a0,$zero
);

void func0000bf8c(void)
{
	// empty
}

void func0000bf94(void)
{
	// empty
}

void func0000bf9c(void)
{
	// empty
}

void func0000bfa4(void)
{
	// empty
}
