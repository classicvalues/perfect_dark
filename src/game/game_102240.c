#include <ultra64.h>
#include "constants.h"
#include "game/cheats.h"
#include "game/game_00c490.h"
#include "game/title.h"
#include "game/game_01b0a0.h"
#include "game/game_01bea0.h"
#include "game/game_095320.h"
#include "game/bondgun.h"
#include "game/game_0b0fd0.h"
#include "game/game_0b3350.h"
#include "game/game_0b69d0.h"
#include "game/game_0f09f0.h"
#include "game/game_102240.h"
#include "game/game_107fb0.h"
#include "game/inventory/inventory.h"
#include "game/game_1531a0.h"
#include "game/lv.h"
#include "game/mplayer/ingame.h"
#include "game/game_19aa80.h"
#include "game/training/training.h"
#include "game/gamefile.h"
#include "game/lang.h"
#include "game/mplayer/mplayer.h"
#include "game/options.h"
#include "bss.h"
#include "lib/lib_09a80.h"
#include "lib/main.h"
#include "lib/snd.h"
#include "data.h"
#include "types.h"

u8 g_InventoryWeapon;

struct menudialog g_2PMissionControlStyleMenuDialog;
struct menudialog g_CiControlPlayer2MenuDialog;
struct menudialog g_CinemaMenuDialog;

char *menuTextCurrentStageName(struct menuitem *item)
{
	sprintf(g_StringPointer, "%s\n", langGet(g_StageNames[g_MissionConfig.stageindex].name3));
	return g_StringPointer;
}

char *soloMenuTextDifficulty(struct menuitem *item)
{
#if VERSION >= VERSION_NTSC_1_0
	if (g_MissionConfig.pdmode) {
		return langGet(L_MPWEAPONS_221);
	}
#endif

	switch (g_MissionConfig.difficulty) {
	case DIFF_SA:
		return langGet(L_OPTIONS_252);
	case DIFF_PA:
		return langGet(L_OPTIONS_253);
	case DIFF_A:
	default:
		return langGet(L_OPTIONS_251);
	}
}

u16 g_ControlStyleOptions[] = {
	L_OPTIONS_239, // "1.1"
	L_OPTIONS_240, // "1.2"
	L_OPTIONS_241, // "1.3"
	L_OPTIONS_242, // "1.4"
	L_OPTIONS_243, // "2.1"
	L_OPTIONS_244, // "2.2"
	L_OPTIONS_245, // "2.3"
	L_OPTIONS_246, // "2.4"
};

s32 menuhandlerControlStyleImpl(s32 operation, struct menuitem *item, union handlerdata *data, s32 mpindex)
{
	u16 categories[] = {
		L_OPTIONS_237, // "Single"
		L_OPTIONS_238, // "Double"
	};

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpindex = g_Vars.currentplayerstats->mpindex;
	}

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		data->list.value = 8;
		break;
	case MENUOP_GETOPTGROUPCOUNT:
		data->list.value = 2;
		break;
	case MENUOP_GETOPTIONTEXT:
		return (s32) langGet(g_ControlStyleOptions[data->list.value]);
	case MENUOP_GETOPTGROUPTEXT:
		return (s32) langGet(categories[data->list.value]);
	case MENUOP_GETGROUPSTARTINDEX:
		data->list.groupstartindex = data->list.value == 0 ? 0 : 4;
		break;
	case MENUOP_SET:
		optionsSetControlMode(mpindex, data->list.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
		break;
	case MENUOP_GETOPTIONVALUE:
		data->list.value = optionsGetControlMode(mpindex);
		g_Menus[g_MpPlayerNum].data.main.mpindex = mpindex;
		break;
	case MENUOP_LISTITEMFOCUS:
		if (g_MenuData.root == MENUROOT_MAINMENU) {
			g_Menus[g_MpPlayerNum].data.main.controlmode = data->list.value;
		}
		break;
	}

	return 0;
}

s32 menuhandler001024dc(s32 operation, struct menuitem *item, union handlerdata *data)
{
	return menuhandlerControlStyleImpl(operation, item, data, 4);
}

s32 menuhandler001024fc(s32 operation, struct menuitem *item, union handlerdata *data)
{
	return menuhandlerControlStyleImpl(operation, item, data, 5);
}

s32 menuhandlerReversePitch(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 mpchrnum;

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpchrnum = g_Vars.currentplayerstats->mpindex;
	} else {
		mpchrnum = item->param3;
	}

	switch (operation) {
	case MENUOP_GET:
		return !optionsGetForwardPitch(mpchrnum);
	case MENUOP_SET:
		optionsSetForwardPitch(mpchrnum, data->checkbox.value == 0);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerAimControl(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 playernum = (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0)
		? g_Vars.currentplayerstats->mpindex : item->param3;

#if PAL
	s32 index = 0;

	u16 options[2][2] = {
		{ L_OPTIONS_201,   L_OPTIONS_202   }, // "Hold", "Toggle"
		{ L_MPWEAPONS_276, L_MPWEAPONS_277 }, // "Hold", "Toggle"
	};

	if (optionsGetScreenSplit() == SCREENSPLIT_VERTICAL && PLAYERCOUNT() >= 2) {
		index = 1;
	}
#else
	u16 options[] = {
		L_OPTIONS_201, // "Hold"
		L_OPTIONS_202, // "Toggle"
	};
#endif

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		data->dropdown.value = 2;
		break;
	case MENUOP_GETOPTIONTEXT:
#if PAL
		return (s32) langGet(options[index][data->dropdown.value]);
#else
		return (s32) langGet(options[data->dropdown.value]);
#endif
	case MENUOP_SET:
		optionsSetAimControl(playernum, data->dropdown.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
		break;
	case MENUOP_GETOPTIONVALUE:
		data->dropdown.value = optionsGetAimControl(playernum);
	}

	return 0;
}

s32 menuhandlerSoundMode(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u16 options[] = {
		L_OPTIONS_232, // "Mono"
		L_OPTIONS_233, // "Stereo"
		L_OPTIONS_234, // "Headphone"
		L_OPTIONS_235, // "Surround"
	};

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		data->dropdown.value = 4;
		break;
	case MENUOP_GETOPTIONTEXT:
		return (s32) langGet(options[data->dropdown.value]);
	case MENUOP_SET:
		sndSetSoundMode(data->dropdown.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
		break;
	case MENUOP_GETOPTIONVALUE:
		data->dropdown.value = g_SoundMode;
	}

	return 0;
}

s32 menuhandlerScreenSize(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u16 options[] = {
		L_OPTIONS_220, // "Full"
		L_OPTIONS_221, // "Wide"
		L_OPTIONS_222, // "Cinema"
	};

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		data->dropdown.value = 3;
		break;
	case MENUOP_GETOPTIONTEXT:
		return (s32) langGet(options[data->dropdown.value]);
	case MENUOP_SET:
		optionsSetScreenSize(data->dropdown.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
		break;
	case MENUOP_GETOPTIONVALUE:
		data->dropdown.value = optionsGetEffectiveScreenSize();
	}

	return 0;
}

s32 menuhandlerScreenRatio(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u16 options[] = {
		L_OPTIONS_223, // "Normal"
		L_OPTIONS_224, // "16:9"
	};

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		data->dropdown.value = 2;
		break;
	case MENUOP_GETOPTIONTEXT:
		return (s32) langGet(options[data->dropdown.value]);
	case MENUOP_SET:
		optionsSetScreenRatio(data->dropdown.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
		break;
	case MENUOP_GETOPTIONVALUE:
		data->dropdown.value = optionsGetScreenRatio();
	}

	return 0;
}

#if VERSION >= VERSION_PAL_FINAL
u16 var80071ce0pf[] = { 0x5507, 0x5508, 0x5509, 0x550a, 0x550b };

GLOBAL_ASM(
glabel func0f1030e4pf
/*  f1030e4:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*  f1030e8:	3c0e8007 */ 	lui	$t6,0x8007
/*  f1030ec:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f1030f0:	afa5002c */ 	sw	$a1,0x2c($sp)
/*  f1030f4:	25ce1ce0 */ 	addiu	$t6,$t6,0x1ce0
/*  f1030f8:	8dc10000 */ 	lw	$at,0x0($t6)
/*  f1030fc:	27a2001c */ 	addiu	$v0,$sp,0x1c
/*  f103100:	24080005 */ 	li	$t0,0x5
/*  f103104:	ac410000 */ 	sw	$at,0x0($v0)
/*  f103108:	8dd90004 */ 	lw	$t9,0x4($t6)
/*  f10310c:	ac590004 */ 	sw	$t9,0x4($v0)
/*  f103110:	95c10008 */ 	lhu	$at,0x8($t6)
/*  f103114:	a4410008 */ 	sh	$at,0x8($v0)
/*  f103118:	24010001 */ 	li	$at,0x1
/*  f10311c:	10810009 */ 	beq	$a0,$at,.PF0f103144
/*  f103120:	24010003 */ 	li	$at,0x3
/*  f103124:	10810009 */ 	beq	$a0,$at,.PF0f10314c
/*  f103128:	24010006 */ 	li	$at,0x6
/*  f10312c:	1081000e */ 	beq	$a0,$at,.PF0f103168
/*  f103130:	24010007 */ 	li	$at,0x7
/*  f103134:	10810018 */ 	beq	$a0,$at,.PF0f103198
/*  f103138:	3c02800a */ 	lui	$v0,0x800a
/*  f10313c:	1000001d */ 	b	.PF0f1031b4
/*  f103140:	00001025 */ 	move	$v0,$zero
.PF0f103144:
/*  f103144:	1000001a */ 	b	.PF0f1031b0
/*  f103148:	acc80000 */ 	sw	$t0,0x0($a2)
.PF0f10314c:
/*  f10314c:	8cc90000 */ 	lw	$t1,0x0($a2)
/*  f103150:	00095040 */ 	sll	$t2,$t1,0x1
/*  f103154:	004a5821 */ 	addu	$t3,$v0,$t2
/*  f103158:	0fc5bdaa */ 	jal	langGet
/*  f10315c:	95640000 */ 	lhu	$a0,0x0($t3)
/*  f103160:	10000015 */ 	b	.PF0f1031b8
/*  f103164:	8fbf0014 */ 	lw	$ra,0x14($sp)
.PF0f103168:
/*  f103168:	8ccc0000 */ 	lw	$t4,0x0($a2)
/*  f10316c:	3c02800a */ 	lui	$v0,0x800a
/*  f103170:	2442a510 */ 	addiu	$v0,$v0,-23280
/*  f103174:	a44c0482 */ 	sh	$t4,0x482($v0)
/*  f103178:	0fc5bdd7 */ 	jal	func0f16f75c
/*  f10317c:	3184ffff */ 	andi	$a0,$t4,0xffff
/*  f103180:	3c02800a */ 	lui	$v0,0x800a
/*  f103184:	2442a510 */ 	addiu	$v0,$v0,-23280
/*  f103188:	8c4d0458 */ 	lw	$t5,0x458($v0)
/*  f10318c:	35b80005 */ 	ori	$t8,$t5,0x5
/*  f103190:	10000007 */ 	b	.PF0f1031b0
/*  f103194:	ac580458 */ 	sw	$t8,0x458($v0)
.PF0f103198:
/*  f103198:	2442a510 */ 	addiu	$v0,$v0,-23280
/*  f10319c:	944f0482 */ 	lhu	$t7,0x482($v0)
/*  f1031a0:	2de10005 */ 	sltiu	$at,$t7,0x5
/*  f1031a4:	14200002 */ 	bnez	$at,.PF0f1031b0
/*  f1031a8:	accf0000 */ 	sw	$t7,0x0($a2)
/*  f1031ac:	acc00000 */ 	sw	$zero,0x0($a2)
.PF0f1031b0:
/*  f1031b0:	00001025 */ 	move	$v0,$zero
.PF0f1031b4:
/*  f1031b4:	8fbf0014 */ 	lw	$ra,0x14($sp)
.PF0f1031b8:
/*  f1031b8:	27bd0028 */ 	addiu	$sp,$sp,0x28
/*  f1031bc:	03e00008 */ 	jr	$ra
/*  f1031c0:	00000000 */ 	nop
);
#endif

s32 menuhandlerScreenSplit(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u16 options[] = {
		L_OPTIONS_225, // "Horizontal"
		L_OPTIONS_226, // "Vertical"
	};

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		data->dropdown.value = 2;
		break;
	case MENUOP_GETOPTIONTEXT:
		return (s32) langGet(options[data->dropdown.value]);
	case MENUOP_SET:
		if (data->dropdown.value != (u32)optionsGetScreenSplit()) {
			optionsSetScreenSplit(data->dropdown.value);

			g_Vars.modifiedfiles |= MODFILE_SOLO;

			if (PLAYERCOUNT() > 1) {
				u32 prevplayernum = g_MpPlayerNum;
				g_MpPlayerNum = 0;
				func0f0f8120();
				g_MpPlayerNum = 1;
				func0f0f8120();
				g_MpPlayerNum = prevplayernum;
			}
		}
		break;
	case MENUOP_GETOPTIONVALUE:
		data->dropdown.value = optionsGetScreenSplit();
		break;
	}

	return 0;
}

s32 menuhandlerLookAhead(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 mpchrnum;

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpchrnum = g_Vars.currentplayerstats->mpindex;
	} else {
		mpchrnum = item->param3;
	}

	switch (operation) {
	case MENUOP_GET:
		return optionsGetLookAhead(mpchrnum);
	case MENUOP_SET:
		optionsSetLookAhead(mpchrnum, data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerHeadRoll(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 mpchrnum;

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpchrnum = g_Vars.currentplayerstats->mpindex;
	} else {
		mpchrnum = item->param3;
	}

	switch (operation) {
	case MENUOP_GET:
		return optionsGetHeadRoll(mpchrnum);
	case MENUOP_SET:
		optionsSetHeadRoll(mpchrnum, data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerInGameSubtitles(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return optionsGetInGameSubtitles();
	case MENUOP_SET:
		optionsSetInGameSubtitles(data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerCutsceneSubtitles(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return optionsGetCutsceneSubtitles();
	case MENUOP_SET:
		optionsSetCutsceneSubtitles(data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerAlternativeTitle(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_CHECKHIDDEN:
		if (g_Vars.stagenum != STAGE_CITRAINING || (u8)g_SoloCompleted == false) {
			return true;
		}
		break;
	case MENUOP_GET:
		return g_AltTitle;
	case MENUOP_SET:
		g_AltTitle = data->checkbox.value;
		g_Vars.modifiedfiles |= MODFILE_GLOBAL;
	}

	return 0;
}

s32 menuhandlerHiRes(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_CHECKHIDDEN:
		if (IS4MB()) {
			return true;
		}
		if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
			if (PLAYERCOUNT() >= 2) {
				return true;
			}
		}
		break;
	case MENUOP_GET:
		return g_HiResEnabled == true;
	case MENUOP_SET:
		optionsSetHiRes(data->checkbox.value ? 1 : 0);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerAmmoOnScreen(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 mpchrnum;

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpchrnum = g_Vars.currentplayerstats->mpindex;
	} else {
		mpchrnum = item->param3;
	}

	switch (operation) {
	case MENUOP_GET:
		return optionsGetAmmoOnScreen(mpchrnum);
	case MENUOP_SET:
		optionsSetAmmoOnScreen(mpchrnum, data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerShowGunFunction(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 mpchrnum;

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpchrnum = g_Vars.currentplayerstats->mpindex;
	} else {
		mpchrnum = item->param3;
	}

	switch (operation) {
	case MENUOP_CHECKDISABLED:
		if (optionsGetAmmoOnScreen(mpchrnum) == 0) {
			return true;
		}
		break;
	case MENUOP_GET:
		return optionsGetShowGunFunction(mpchrnum);
	case MENUOP_SET:
		optionsSetShowGunFunction(mpchrnum, data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerShowMissionTime(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 mpchrnum;

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpchrnum = g_Vars.currentplayerstats->mpindex;
	} else {
		mpchrnum = item->param3;
	}

	switch (operation) {
	case MENUOP_GET:
		return optionsGetShowMissionTime(mpchrnum);
	case MENUOP_SET:
		optionsSetShowMissionTime(mpchrnum, data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerAlwaysShowTarget(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 mpchrnum;

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpchrnum = g_Vars.currentplayerstats->mpindex;
	} else {
		mpchrnum = item->param3;
	}

	switch (operation) {
	case MENUOP_CHECKDISABLED:
		if (optionsGetSightOnScreen(mpchrnum) == 0) {
			return true;
		}
		break;
	case MENUOP_GET:
		return optionsGetAlwaysShowTarget(mpchrnum);
	case MENUOP_SET:
		optionsSetAlwaysShowTarget(mpchrnum, data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerShowZoomRange(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 mpchrnum;

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpchrnum = g_Vars.currentplayerstats->mpindex;
	} else {
		mpchrnum = item->param3;
	}

	switch (operation) {
	case MENUOP_CHECKDISABLED:
		if (optionsGetSightOnScreen(mpchrnum) == 0) {
			return true;
		}
		break;
	case MENUOP_GET:
		return optionsGetShowZoomRange(mpchrnum);
	case MENUOP_SET:
		optionsSetShowZoomRange(mpchrnum, data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerPaintball(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 mpchrnum;

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpchrnum = g_Vars.currentplayerstats->mpindex;
	} else {
		mpchrnum = item->param3;
	}

	switch (operation) {
	case MENUOP_GET:
		return optionsGetPaintball(mpchrnum);
	case MENUOP_SET:
		optionsSetPaintball(mpchrnum, data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerSightOnScreen(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 mpchrnum;

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpchrnum = g_Vars.currentplayerstats->mpindex;
	} else {
		mpchrnum = item->param3;
	}

	switch (operation) {
	case MENUOP_GET:
		return optionsGetSightOnScreen(mpchrnum);
	case MENUOP_SET:
		optionsSetSightOnScreen(mpchrnum, data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerAutoAim(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u32 mpchrnum;

	if (g_Vars.coopplayernum >= 0 || g_Vars.antiplayernum >= 0) {
		mpchrnum = g_Vars.currentplayerstats->mpindex;
	} else {
		mpchrnum = item->param3;
	}

	switch (operation) {
	case MENUOP_GET:
		return optionsGetAutoAim(mpchrnum);
	case MENUOP_SET:
		optionsSetAutoAim(mpchrnum, data->checkbox.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerMusicVolume(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = optionsGetMusicVolume();
		break;
	case MENUOP_SET:
		optionsSetMusicVolume(data->slider.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerSfxVolume(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = VOLUME(g_SfxVolume);
		break;
	case MENUOP_SET:
		sndSetSfxVolume(data->slider.value);
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menudialogBriefing(s32 operation, struct menudialog *dialog, union handlerdata *data)
{
	if (operation == MENUOP_TICK) {
		if (g_Menus[g_MpPlayerNum].curframe
				&& g_Menus[g_MpPlayerNum].curframe->dialog == dialog) {
			struct menuinputs *inputs = data->dialog2.inputs;

			if (inputs->start) {
				menuhandlerAcceptMission(MENUOP_SET, NULL, data);
			}

			inputs->start = false;
		}
	}

	return 0;
}

struct menuitem g_PreAndPostMissionBriefingMenuItems[] = {
	{ MENUITEMTYPE_SCROLLABLE, DESCRIPTION_BRIEFING, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_END,        0,                    0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_PreAndPostMissionBriefingMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_247, // "Briefing"
	g_PreAndPostMissionBriefingMenuItems,
	menudialogBriefing,
	0x00000008,
	NULL,
};

s32 menuhandlerAcceptMission(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		func0f01bea0();

		if (g_Vars.stagenum == g_MissionConfig.stagenum) {
			g_Vars.restartlevel = true;
		}

		titleSetNextStage(g_MissionConfig.stagenum);

		if (g_MissionConfig.iscoop) {
			if (g_Vars.numaibuddies == 0) {
				// Coop with human buddy
				g_Vars.bondplayernum = 0;
				g_Vars.coopplayernum = 1;
				g_Vars.antiplayernum = -1;
				setNumPlayers(2);
			} else {
				// Coop with AI buddies
				g_Vars.bondplayernum = 0;
				g_Vars.coopplayernum = -1;
				g_Vars.antiplayernum = -1;
				setNumPlayers(1);
			}
		} else if (g_MissionConfig.isanti) {
			if (g_Vars.pendingantiplayernum == 1) {
				g_Vars.bondplayernum = 0;
				g_Vars.antiplayernum = 1;
			} else {
				g_Vars.bondplayernum = 1;
				g_Vars.antiplayernum = 0;
			}

			g_Vars.coopplayernum = -1;
			setNumPlayers(2);
		} else {
			// Solo
			g_Vars.bondplayernum = 0;
			g_Vars.coopplayernum = -1;
			g_Vars.antiplayernum = -1;
			setNumPlayers(1);
		}

		lvSetDifficulty(g_MissionConfig.difficulty);
		titleSetNextMode(TITLEMODE_SKIP);
		mainSetStageNum(g_MissionConfig.stagenum);

#if VERSION >= VERSION_NTSC_1_0
		func00009ec4(1);
#endif
	}

	return 0;
}

char *soloMenuTitleStageOverview(struct menudialog *dialog)
{
	if (dialog != g_Menus[g_MpPlayerNum].curframe->dialog) {
		return langGet(L_OPTIONS_273); // "Overview"
	}

	sprintf(g_StringPointer, "%s: %s\n",
			langGet(g_StageNames[g_MissionConfig.stageindex].name3),
			langGet(L_OPTIONS_273));

	return g_StringPointer;
}

s32 menudialog00103608(s32 operation, struct menudialog *dialog, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_OPEN:
		g_Menus[g_MpPlayerNum].unk850 = 0;

		func0f00e980(g_MissionConfig.stagenum,
				g_Menus[g_MpPlayerNum].unk844,
				g_Menus[g_MpPlayerNum].unk848, &g_Briefing);
		break;
	case MENUOP_CLOSE:
		langClearBank(g_Briefing.langbank);
		break;
	}

	return 0;
}

struct menuitem g_AcceptMissionMenuItems[] = {
	{ MENUITEMTYPE_OBJECTIVES,  1, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_OPTIONS_274, 0x00000000, menuhandlerAcceptMission }, // "Accept"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_275, 0x00000000, NULL }, // "Decline"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_AcceptMissionMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(u32)&soloMenuTitleStageOverview,
	g_AcceptMissionMenuItems,
	menudialog00103608,
	0x0000000c,
	&g_PreAndPostMissionBriefingMenuDialog,
};

f32 func0f1036ac(u8 value, s32 prop)
{
	if (prop == PDMODEPROP_REACTION) {
		return value / 255.0f;
	}

	return mpHandicapToDamageScale(value);
}

s32 menuhandlerPdModeSetting(s32 operation, struct menuitem *item, union handlerdata *data)
{
	u8 *property;
	f32 fvalue;

	switch (item->param) {
	case PDMODEPROP_REACTION: property = &g_MissionConfig.pdmodereaction; break;
	case PDMODEPROP_HEALTH:   property = &g_MissionConfig.pdmodehealth;   break;
	case PDMODEPROP_DAMAGE:   property = &g_MissionConfig.pdmodedamage;   break;
	case PDMODEPROP_ACCURACY: property = &g_MissionConfig.pdmodeaccuracy; break;
	default: return 0;
	}

	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = *property;
		break;
	case MENUOP_SET:
		*property = (u16)data->slider.value;
		break;
	case MENUOP_GETSLIDERLABEL:
		fvalue = func0f1036ac(*property, item->param);
		if (item->param == 0) {
			fvalue = fvalue * 4 + 1.0f;
		}
		sprintf(data->slider.label, "%s%s%.00f%%\n", "", "", fvalue * 100.0f);
		break;
	}

	return 0;
}

s32 menuhandlerAcceptPdModeSettings(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		g_MissionConfig.pdmode = true;
		g_MissionConfig.pdmodehealthf = func0f1036ac(g_MissionConfig.pdmodehealth, PDMODEPROP_HEALTH);
		g_MissionConfig.pdmodedamagef = func0f1036ac(g_MissionConfig.pdmodedamage, PDMODEPROP_DAMAGE);
		g_MissionConfig.pdmodeaccuracyf = func0f1036ac(g_MissionConfig.pdmodeaccuracy, PDMODEPROP_ACCURACY);
		g_MissionConfig.difficulty = DIFF_PA;
		lvSetDifficulty(g_MissionConfig.difficulty);
		menuPopDialog();
		menuPopDialog();
		menuPushDialog(&g_AcceptMissionMenuDialog);
	}

	return 0;
}

struct menuitem g_PdModeSettingsMenuItems[] = {
	{ MENUITEMTYPE_LABEL,       0, 0x00000012, L_MPWEAPONS_222, 0x00000000, NULL }, // "Choose Settings:"
	{ MENUITEMTYPE_SLIDER,      1, 0x00100000, L_MPWEAPONS_224, 0x000000ff, menuhandlerPdModeSetting }, // "Enemy Health"
	{ MENUITEMTYPE_SLIDER,      2, 0x00100000, L_MPWEAPONS_225, 0x000000ff, menuhandlerPdModeSetting }, // "Enemy Damage"
	{ MENUITEMTYPE_SLIDER,      3, 0x00100000, L_MPWEAPONS_226, 0x000000ff, menuhandlerPdModeSetting }, // "Enemy Accuracy"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x000000b4, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_MPWEAPONS_227, 0x00000000, menuhandlerAcceptPdModeSettings }, // "OK"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_MPWEAPONS_228, 0x00000000, NULL }, // "Cancel"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_PdModeSettingsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_MPWEAPONS_221, // "Perfect Dark"
	g_PdModeSettingsMenuItems,
	NULL,
	0x00000004,
	NULL,
};

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel isStageDifficultyUnlocked
/*  f1038ec:	28810011 */ 	slti	$at,$a0,0x11
/*  f1038f0:	14200024 */ 	bnez	$at,.L0f103984
/*  f1038f4:	00a03025 */ 	or	$a2,$a1,$zero
/*  f1038f8:	3c05800a */ 	lui	$a1,%hi(g_SoloSaveFile)
/*  f1038fc:	00001025 */ 	or	$v0,$zero,$zero
/*  f103900:	24a52200 */ 	addiu	$a1,$a1,%lo(g_SoloSaveFile)
/*  f103904:	00001825 */ 	or	$v1,$zero,$zero
.L0f103908:
/*  f103908:	94ae0080 */ 	lhu	$t6,0x80($a1)
/*  f10390c:	51c00003 */ 	beqzl	$t6,.L0f10391c
/*  f103910:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f103914:	00601025 */ 	or	$v0,$v1,$zero
/*  f103918:	24630001 */ 	addiu	$v1,$v1,0x1
.L0f10391c:
/*  f10391c:	28610003 */ 	slti	$at,$v1,0x3
/*  f103920:	1420fff9 */ 	bnez	$at,.L0f103908
/*  f103924:	24a50002 */ 	addiu	$a1,$a1,0x2
/*  f103928:	0046082a */ 	slt	$at,$v0,$a2
/*  f10392c:	14200003 */ 	bnez	$at,.L0f10393c
/*  f103930:	00000000 */ 	nop
/*  f103934:	03e00008 */ 	jr	$ra
/*  f103938:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f10393c:
/*  f10393c:	18c0000f */ 	blez	$a2,.L0f10397c
/*  f103940:	00001825 */ 	or	$v1,$zero,$zero
/*  f103944:	00047880 */ 	sll	$t7,$a0,0x2
/*  f103948:	01e47823 */ 	subu	$t7,$t7,$a0
/*  f10394c:	3c18800a */ 	lui	$t8,%hi(g_SoloSaveFile)
/*  f103950:	27182200 */ 	addiu	$t8,$t8,%lo(g_SoloSaveFile)
/*  f103954:	000f7840 */ 	sll	$t7,$t7,0x1
/*  f103958:	01f81021 */ 	addu	$v0,$t7,$t8
.L0f10395c:
/*  f10395c:	94590020 */ 	lhu	$t9,0x20($v0)
/*  f103960:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f103964:	17200003 */ 	bnez	$t9,.L0f103974
/*  f103968:	00000000 */ 	nop
/*  f10396c:	03e00008 */ 	jr	$ra
/*  f103970:	00001025 */ 	or	$v0,$zero,$zero
.L0f103974:
/*  f103974:	1466fff9 */ 	bne	$v1,$a2,.L0f10395c
/*  f103978:	24420002 */ 	addiu	$v0,$v0,0x2
.L0f10397c:
/*  f10397c:	03e00008 */ 	jr	$ra
/*  f103980:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f103984:
/*  f103984:	28810011 */ 	slti	$at,$a0,0x11
/*  f103988:	102000d6 */ 	beqz	$at,.L0f103ce4
/*  f10398c:	28c10003 */ 	slti	$at,$a2,0x3
/*  f103990:	102000d4 */ 	beqz	$at,.L0f103ce4
/*  f103994:	00046080 */ 	sll	$t4,$a0,0x2
/*  f103998:	01846023 */ 	subu	$t4,$t4,$a0
/*  f10399c:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f1039a0:	3c058007 */ 	lui	$a1,%hi(g_StageNames)
/*  f1039a4:	00ac2821 */ 	addu	$a1,$a1,$t4
/*  f1039a8:	8ca51e6c */ 	lw	$a1,%lo(g_StageNames)($a1)
/*  f1039ac:	24010030 */ 	addiu	$at,$zero,0x30
/*  f1039b0:	54a10004 */ 	bnel	$a1,$at,.L0f1039c4
/*  f1039b4:	28c10003 */ 	slti	$at,$a2,0x3
/*  f1039b8:	03e00008 */ 	jr	$ra
/*  f1039bc:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f1039c0:	28c10003 */ 	slti	$at,$a2,0x3
.L0f1039c4:
/*  f1039c4:	10200026 */ 	beqz	$at,.L0f103a60
/*  f1039c8:	00c01825 */ 	or	$v1,$a2,$zero
/*  f1039cc:	00046880 */ 	sll	$t5,$a0,0x2
/*  f1039d0:	01a46823 */ 	subu	$t5,$t5,$a0
/*  f1039d4:	000d6840 */ 	sll	$t5,$t5,0x1
/*  f1039d8:	00037040 */ 	sll	$t6,$v1,0x1
/*  f1039dc:	3c18800a */ 	lui	$t8,%hi(g_SoloSaveFile)
/*  f1039e0:	27182200 */ 	addiu	$t8,$t8,%lo(g_SoloSaveFile)
/*  f1039e4:	01ae7821 */ 	addu	$t7,$t5,$t6
/*  f1039e8:	3c0a800a */ 	lui	$t2,%hi(g_SoloSaveFile)
/*  f1039ec:	3c09800a */ 	lui	$t1,%hi(g_MissionConfig)
/*  f1039f0:	2529dfe8 */ 	addiu	$t1,$t1,%lo(g_MissionConfig)
/*  f1039f4:	254a2200 */ 	addiu	$t2,$t2,%lo(g_SoloSaveFile)
/*  f1039f8:	01f81021 */ 	addu	$v0,$t7,$t8
/*  f1039fc:	240b0003 */ 	addiu	$t3,$zero,0x3
.L0f103a00:
/*  f103a00:	94590020 */ 	lhu	$t9,0x20($v0)
/*  f103a04:	53200004 */ 	beqzl	$t9,.L0f103a18
/*  f103a08:	812d0003 */ 	lb	$t5,0x3($t1)
/*  f103a0c:	03e00008 */ 	jr	$ra
/*  f103a10:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f103a14:	812d0003 */ 	lb	$t5,0x3($t1)
.L0f103a18:
/*  f103a18:	0003c880 */ 	sll	$t9,$v1,0x2
/*  f103a1c:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f103a20:	05a00005 */ 	bltz	$t5,.L0f103a38
/*  f103a24:	01596021 */ 	addu	$t4,$t2,$t9
/*  f103a28:	8d2e0000 */ 	lw	$t6,0x0($t1)
/*  f103a2c:	000ec640 */ 	sll	$t8,$t6,0x19
/*  f103a30:	07010009 */ 	bgez	$t8,.L0f103a58
/*  f103a34:	00000000 */ 	nop
.L0f103a38:
/*  f103a38:	8d8d00a0 */ 	lw	$t5,0xa0($t4)
/*  f103a3c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f103a40:	008e7804 */ 	sllv	$t7,$t6,$a0
/*  f103a44:	01afc024 */ 	and	$t8,$t5,$t7
/*  f103a48:	13000003 */ 	beqz	$t8,.L0f103a58
/*  f103a4c:	00000000 */ 	nop
/*  f103a50:	03e00008 */ 	jr	$ra
/*  f103a54:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f103a58:
/*  f103a58:	146bffe9 */ 	bne	$v1,$t3,.L0f103a00
/*  f103a5c:	24420002 */ 	addiu	$v0,$v0,0x2
.L0f103a60:
/*  f103a60:	3c09800a */ 	lui	$t1,%hi(g_MissionConfig)
/*  f103a64:	3c0a800a */ 	lui	$t2,%hi(g_SoloSaveFile)
/*  f103a68:	254a2200 */ 	addiu	$t2,$t2,%lo(g_SoloSaveFile)
/*  f103a6c:	2529dfe8 */ 	addiu	$t1,$t1,%lo(g_MissionConfig)
/*  f103a70:	18800052 */ 	blez	$a0,.L0f103bbc
/*  f103a74:	240b0003 */ 	addiu	$t3,$zero,0x3
/*  f103a78:	2401002a */ 	addiu	$at,$zero,0x2a
/*  f103a7c:	10a10024 */ 	beq	$a1,$at,.L0f103b10
/*  f103a80:	28c10003 */ 	slti	$at,$a2,0x3
/*  f103a84:	1020004d */ 	beqz	$at,.L0f103bbc
/*  f103a88:	00c01825 */ 	or	$v1,$a2,$zero
/*  f103a8c:	0004c880 */ 	sll	$t9,$a0,0x2
/*  f103a90:	0324c823 */ 	subu	$t9,$t9,$a0
/*  f103a94:	0019c840 */ 	sll	$t9,$t9,0x1
/*  f103a98:	01596021 */ 	addu	$t4,$t2,$t9
/*  f103a9c:	00037040 */ 	sll	$t6,$v1,0x1
/*  f103aa0:	018e1021 */ 	addu	$v0,$t4,$t6
.L0f103aa4:
/*  f103aa4:	944d001a */ 	lhu	$t5,0x1a($v0)
/*  f103aa8:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f103aac:	51a00004 */ 	beqzl	$t5,.L0f103ac0
/*  f103ab0:	81380003 */ 	lb	$t8,0x3($t1)
/*  f103ab4:	03e00008 */ 	jr	$ra
/*  f103ab8:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f103abc:	81380003 */ 	lb	$t8,0x3($t1)
.L0f103ac0:
/*  f103ac0:	00036880 */ 	sll	$t5,$v1,0x2
/*  f103ac4:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f103ac8:	07000005 */ 	bltz	$t8,.L0f103ae0
/*  f103acc:	014d7821 */ 	addu	$t7,$t2,$t5
/*  f103ad0:	8d390000 */ 	lw	$t9,0x0($t1)
/*  f103ad4:	00197640 */ 	sll	$t6,$t9,0x19
/*  f103ad8:	05c10009 */ 	bgez	$t6,.L0f103b00
/*  f103adc:	00000000 */ 	nop
.L0f103ae0:
/*  f103ae0:	8df800a0 */ 	lw	$t8,0xa0($t7)
/*  f103ae4:	2499001f */ 	addiu	$t9,$a0,0x1f
/*  f103ae8:	032c7004 */ 	sllv	$t6,$t4,$t9
/*  f103aec:	030e6824 */ 	and	$t5,$t8,$t6
/*  f103af0:	11a00003 */ 	beqz	$t5,.L0f103b00
/*  f103af4:	00000000 */ 	nop
/*  f103af8:	03e00008 */ 	jr	$ra
/*  f103afc:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f103b00:
/*  f103b00:	146bffe8 */ 	bne	$v1,$t3,.L0f103aa4
/*  f103b04:	24420002 */ 	addiu	$v0,$v0,0x2
/*  f103b08:	1000002c */ 	b	.L0f103bbc
/*  f103b0c:	00000000 */ 	nop
.L0f103b10:
/*  f103b10:	18800025 */ 	blez	$a0,.L0f103ba8
/*  f103b14:	00003825 */ 	or	$a3,$zero,$zero
/*  f103b18:	28c10003 */ 	slti	$at,$a2,0x3
.L0f103b1c:
/*  f103b1c:	1020001c */ 	beqz	$at,.L0f103b90
/*  f103b20:	00c01825 */ 	or	$v1,$a2,$zero
/*  f103b24:	00077880 */ 	sll	$t7,$a3,0x2
/*  f103b28:	01e77823 */ 	subu	$t7,$t7,$a3
/*  f103b2c:	000f7840 */ 	sll	$t7,$t7,0x1
/*  f103b30:	014f6021 */ 	addu	$t4,$t2,$t7
/*  f103b34:	0003c840 */ 	sll	$t9,$v1,0x1
/*  f103b38:	01994021 */ 	addu	$t0,$t4,$t9
.L0f103b3c:
/*  f103b3c:	95180020 */ 	lhu	$t8,0x20($t0)
/*  f103b40:	57000014 */ 	bnezl	$t8,.L0f103b94
/*  f103b44:	28610003 */ 	slti	$at,$v1,0x3
/*  f103b48:	812d0003 */ 	lb	$t5,0x3($t1)
/*  f103b4c:	0003c080 */ 	sll	$t8,$v1,0x2
/*  f103b50:	01587021 */ 	addu	$t6,$t2,$t8
/*  f103b54:	05a20006 */ 	bltzl	$t5,.L0f103b70
/*  f103b58:	8dcd00a0 */ 	lw	$t5,0xa0($t6)
/*  f103b5c:	8d2f0000 */ 	lw	$t7,0x0($t1)
/*  f103b60:	000fce40 */ 	sll	$t9,$t7,0x19
/*  f103b64:	07230008 */ 	bgezl	$t9,.L0f103b88
/*  f103b68:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f103b6c:	8dcd00a0 */ 	lw	$t5,0xa0($t6)
.L0f103b70:
/*  f103b70:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f103b74:	00ef6004 */ 	sllv	$t4,$t7,$a3
/*  f103b78:	01acc824 */ 	and	$t9,$t5,$t4
/*  f103b7c:	57200005 */ 	bnezl	$t9,.L0f103b94
/*  f103b80:	28610003 */ 	slti	$at,$v1,0x3
/*  f103b84:	24630001 */ 	addiu	$v1,$v1,0x1
.L0f103b88:
/*  f103b88:	146bffec */ 	bne	$v1,$t3,.L0f103b3c
/*  f103b8c:	25080002 */ 	addiu	$t0,$t0,0x2
.L0f103b90:
/*  f103b90:	28610003 */ 	slti	$at,$v1,0x3
.L0f103b94:
/*  f103b94:	50200005 */ 	beqzl	$at,.L0f103bac
/*  f103b98:	00e4082a */ 	slt	$at,$a3,$a0
/*  f103b9c:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f103ba0:	54e4ffde */ 	bnel	$a3,$a0,.L0f103b1c
/*  f103ba4:	28c10003 */ 	slti	$at,$a2,0x3
.L0f103ba8:
/*  f103ba8:	00e4082a */ 	slt	$at,$a3,$a0
.L0f103bac:
/*  f103bac:	14200003 */ 	bnez	$at,.L0f103bbc
/*  f103bb0:	00000000 */ 	nop
/*  f103bb4:	03e00008 */ 	jr	$ra
/*  f103bb8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f103bbc:
/*  f103bbc:	18c00049 */ 	blez	$a2,.L0f103ce4
/*  f103bc0:	2401002a */ 	addiu	$at,$zero,0x2a
/*  f103bc4:	10a10047 */ 	beq	$a1,$at,.L0f103ce4
/*  f103bc8:	00003825 */ 	or	$a3,$zero,$zero
/*  f103bcc:	3c05800a */ 	lui	$a1,%hi(g_SoloSaveFile)
/*  f103bd0:	24a52200 */ 	addiu	$a1,$a1,%lo(g_SoloSaveFile)
.L0f103bd4:
/*  f103bd4:	00001825 */ 	or	$v1,$zero,$zero
/*  f103bd8:	00001025 */ 	or	$v0,$zero,$zero
/*  f103bdc:	00a04025 */ 	or	$t0,$a1,$zero
.L0f103be0:
/*  f103be0:	95180020 */ 	lhu	$t8,0x20($t0)
/*  f103be4:	25080002 */ 	addiu	$t0,$t0,0x2
/*  f103be8:	57000013 */ 	bnezl	$t8,.L0f103c38
/*  f103bec:	28410006 */ 	slti	$at,$v0,0x6
/*  f103bf0:	812f0003 */ 	lb	$t7,0x3($t1)
/*  f103bf4:	0003c080 */ 	sll	$t8,$v1,0x2
/*  f103bf8:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f103bfc:	05e00005 */ 	bltz	$t7,.L0f103c14
/*  f103c00:	01587021 */ 	addu	$t6,$t2,$t8
/*  f103c04:	8d2d0000 */ 	lw	$t5,0x0($t1)
/*  f103c08:	000dce40 */ 	sll	$t9,$t5,0x19
/*  f103c0c:	07230007 */ 	bgezl	$t9,.L0f103c2c
/*  f103c10:	28610003 */ 	slti	$at,$v1,0x3
.L0f103c14:
/*  f103c14:	8dcf00a0 */ 	lw	$t7,0xa0($t6)
/*  f103c18:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f103c1c:	00ed6004 */ 	sllv	$t4,$t5,$a3
/*  f103c20:	01ecc824 */ 	and	$t9,$t7,$t4
/*  f103c24:	17200003 */ 	bnez	$t9,.L0f103c34
/*  f103c28:	28610003 */ 	slti	$at,$v1,0x3
.L0f103c2c:
/*  f103c2c:	1420ffec */ 	bnez	$at,.L0f103be0
/*  f103c30:	24420002 */ 	addiu	$v0,$v0,0x2
.L0f103c34:
/*  f103c34:	28410006 */ 	slti	$at,$v0,0x6
.L0f103c38:
/*  f103c38:	10200004 */ 	beqz	$at,.L0f103c4c
/*  f103c3c:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f103c40:	28e10011 */ 	slti	$at,$a3,0x11
/*  f103c44:	1420ffe3 */ 	bnez	$at,.L0f103bd4
/*  f103c48:	24a50006 */ 	addiu	$a1,$a1,0x6
.L0f103c4c:
/*  f103c4c:	3c18800a */ 	lui	$t8,%hi(g_SoloSaveFile+0x66)
/*  f103c50:	27182266 */ 	addiu	$t8,$t8,%lo(g_SoloSaveFile+0x66)
/*  f103c54:	00b8082b */ 	sltu	$at,$a1,$t8
/*  f103c58:	14200022 */ 	bnez	$at,.L0f103ce4
/*  f103c5c:	24c2ffff */ 	addiu	$v0,$a2,-1
/*  f103c60:	28410003 */ 	slti	$at,$v0,0x3
/*  f103c64:	1020001f */ 	beqz	$at,.L0f103ce4
/*  f103c68:	00401825 */ 	or	$v1,$v0,$zero
/*  f103c6c:	00047080 */ 	sll	$t6,$a0,0x2
/*  f103c70:	01c47023 */ 	subu	$t6,$t6,$a0
/*  f103c74:	000e7040 */ 	sll	$t6,$t6,0x1
/*  f103c78:	014e6821 */ 	addu	$t5,$t2,$t6
/*  f103c7c:	00027840 */ 	sll	$t7,$v0,0x1
/*  f103c80:	01af1021 */ 	addu	$v0,$t5,$t7
.L0f103c84:
/*  f103c84:	944c0020 */ 	lhu	$t4,0x20($v0)
/*  f103c88:	51800004 */ 	beqzl	$t4,.L0f103c9c
/*  f103c8c:	81380003 */ 	lb	$t8,0x3($t1)
/*  f103c90:	03e00008 */ 	jr	$ra
/*  f103c94:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f103c98:	81380003 */ 	lb	$t8,0x3($t1)
.L0f103c9c:
/*  f103c9c:	00036080 */ 	sll	$t4,$v1,0x2
/*  f103ca0:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f103ca4:	07000005 */ 	bltz	$t8,.L0f103cbc
/*  f103ca8:	014cc821 */ 	addu	$t9,$t2,$t4
/*  f103cac:	8d2e0000 */ 	lw	$t6,0x0($t1)
/*  f103cb0:	000e7e40 */ 	sll	$t7,$t6,0x19
/*  f103cb4:	05e10009 */ 	bgez	$t7,.L0f103cdc
/*  f103cb8:	00000000 */ 	nop
.L0f103cbc:
/*  f103cbc:	8f3800a0 */ 	lw	$t8,0xa0($t9)
/*  f103cc0:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f103cc4:	008e6804 */ 	sllv	$t5,$t6,$a0
/*  f103cc8:	030d7824 */ 	and	$t7,$t8,$t5
/*  f103ccc:	11e00003 */ 	beqz	$t7,.L0f103cdc
/*  f103cd0:	00000000 */ 	nop
/*  f103cd4:	03e00008 */ 	jr	$ra
/*  f103cd8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f103cdc:
/*  f103cdc:	146bffe9 */ 	bne	$v1,$t3,.L0f103c84
/*  f103ce0:	24420002 */ 	addiu	$v0,$v0,0x2
.L0f103ce4:
/*  f103ce4:	00001025 */ 	or	$v0,$zero,$zero
/*  f103ce8:	03e00008 */ 	jr	$ra
/*  f103cec:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel isStageDifficultyUnlocked
/*  f0ff778:	28810011 */ 	slti	$at,$a0,0x11
/*  f0ff77c:	54200014 */ 	bnezl	$at,.NB0f0ff7d0
/*  f0ff780:	28810011 */ 	slti	$at,$a0,0x11
/*  f0ff784:	18a0000f */ 	blez	$a1,.NB0f0ff7c4
/*  f0ff788:	00001025 */ 	or	$v0,$zero,$zero
/*  f0ff78c:	00047080 */ 	sll	$t6,$a0,0x2
/*  f0ff790:	01c47023 */ 	subu	$t6,$t6,$a0
/*  f0ff794:	3c0f800a */ 	lui	$t7,0x800a
/*  f0ff798:	25ef66f0 */ 	addiu	$t7,$t7,0x66f0
/*  f0ff79c:	000e7040 */ 	sll	$t6,$t6,0x1
/*  f0ff7a0:	01cf1821 */ 	addu	$v1,$t6,$t7
.NB0f0ff7a4:
/*  f0ff7a4:	94780020 */ 	lhu	$t8,0x20($v1)
/*  f0ff7a8:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f0ff7ac:	17000003 */ 	bnez	$t8,.NB0f0ff7bc
/*  f0ff7b0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0ff7b4:	03e00008 */ 	jr	$ra
/*  f0ff7b8:	00001025 */ 	or	$v0,$zero,$zero
.NB0f0ff7bc:
/*  f0ff7bc:	1445fff9 */ 	bne	$v0,$a1,.NB0f0ff7a4
/*  f0ff7c0:	24630002 */ 	addiu	$v1,$v1,0x2
.NB0f0ff7c4:
/*  f0ff7c4:	03e00008 */ 	jr	$ra
/*  f0ff7c8:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f0ff7cc:	28810011 */ 	slti	$at,$a0,0x11
.NB0f0ff7d0:
/*  f0ff7d0:	102000d6 */ 	beqz	$at,.NB0f0ffb2c
/*  f0ff7d4:	28a10003 */ 	slti	$at,$a1,0x3
/*  f0ff7d8:	102000d4 */ 	beqz	$at,.NB0f0ffb2c
/*  f0ff7dc:	0004c880 */ 	sll	$t9,$a0,0x2
/*  f0ff7e0:	0324c823 */ 	subu	$t9,$t9,$a0
/*  f0ff7e4:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f0ff7e8:	3c068007 */ 	lui	$a2,0x8007
/*  f0ff7ec:	00d93021 */ 	addu	$a2,$a2,$t9
/*  f0ff7f0:	8cc643fc */ 	lw	$a2,0x43fc($a2)
/*  f0ff7f4:	24010030 */ 	addiu	$at,$zero,0x30
/*  f0ff7f8:	54c10004 */ 	bnel	$a2,$at,.NB0f0ff80c
/*  f0ff7fc:	28a10003 */ 	slti	$at,$a1,0x3
/*  f0ff800:	03e00008 */ 	jr	$ra
/*  f0ff804:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f0ff808:	28a10003 */ 	slti	$at,$a1,0x3
.NB0f0ff80c:
/*  f0ff80c:	10200026 */ 	beqz	$at,.NB0f0ff8a8
/*  f0ff810:	00a01025 */ 	or	$v0,$a1,$zero
/*  f0ff814:	00046080 */ 	sll	$t4,$a0,0x2
/*  f0ff818:	01846023 */ 	subu	$t4,$t4,$a0
/*  f0ff81c:	000c6040 */ 	sll	$t4,$t4,0x1
/*  f0ff820:	00026840 */ 	sll	$t5,$v0,0x1
/*  f0ff824:	3c0f800a */ 	lui	$t7,0x800a
/*  f0ff828:	25ef66f0 */ 	addiu	$t7,$t7,0x66f0
/*  f0ff82c:	018d7021 */ 	addu	$t6,$t4,$t5
/*  f0ff830:	3c0a800a */ 	lui	$t2,0x800a
/*  f0ff834:	3c09800a */ 	lui	$t1,0x800a
/*  f0ff838:	252927a8 */ 	addiu	$t1,$t1,0x27a8
/*  f0ff83c:	254a66f0 */ 	addiu	$t2,$t2,0x66f0
/*  f0ff840:	01cf1821 */ 	addu	$v1,$t6,$t7
/*  f0ff844:	240b0003 */ 	addiu	$t3,$zero,0x3
.NB0f0ff848:
/*  f0ff848:	94780020 */ 	lhu	$t8,0x20($v1)
/*  f0ff84c:	53000004 */ 	beqzl	$t8,.NB0f0ff860
/*  f0ff850:	812c0003 */ 	lb	$t4,0x3($t1)
/*  f0ff854:	03e00008 */ 	jr	$ra
/*  f0ff858:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f0ff85c:	812c0003 */ 	lb	$t4,0x3($t1)
.NB0f0ff860:
/*  f0ff860:	0002c080 */ 	sll	$t8,$v0,0x2
/*  f0ff864:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f0ff868:	05800005 */ 	bltz	$t4,.NB0f0ff880
/*  f0ff86c:	0158c821 */ 	addu	$t9,$t2,$t8
/*  f0ff870:	8d2d0000 */ 	lw	$t5,0x0($t1)
/*  f0ff874:	000d7e40 */ 	sll	$t7,$t5,0x19
/*  f0ff878:	05e10009 */ 	bgez	$t7,.NB0f0ff8a0
/*  f0ff87c:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f0ff880:
/*  f0ff880:	8f2c00a0 */ 	lw	$t4,0xa0($t9)
/*  f0ff884:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f0ff888:	008d7004 */ 	sllv	$t6,$t5,$a0
/*  f0ff88c:	018e7824 */ 	and	$t7,$t4,$t6
/*  f0ff890:	11e00003 */ 	beqz	$t7,.NB0f0ff8a0
/*  f0ff894:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0ff898:	03e00008 */ 	jr	$ra
/*  f0ff89c:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f0ff8a0:
/*  f0ff8a0:	144bffe9 */ 	bne	$v0,$t3,.NB0f0ff848
/*  f0ff8a4:	24630002 */ 	addiu	$v1,$v1,0x2
.NB0f0ff8a8:
/*  f0ff8a8:	3c09800a */ 	lui	$t1,0x800a
/*  f0ff8ac:	3c0a800a */ 	lui	$t2,0x800a
/*  f0ff8b0:	254a66f0 */ 	addiu	$t2,$t2,0x66f0
/*  f0ff8b4:	252927a8 */ 	addiu	$t1,$t1,0x27a8
/*  f0ff8b8:	18800052 */ 	blez	$a0,.NB0f0ffa04
/*  f0ff8bc:	240b0003 */ 	addiu	$t3,$zero,0x3
/*  f0ff8c0:	2401002a */ 	addiu	$at,$zero,0x2a
/*  f0ff8c4:	10c10024 */ 	beq	$a2,$at,.NB0f0ff958
/*  f0ff8c8:	28a10003 */ 	slti	$at,$a1,0x3
/*  f0ff8cc:	1020004d */ 	beqz	$at,.NB0f0ffa04
/*  f0ff8d0:	00a01025 */ 	or	$v0,$a1,$zero
/*  f0ff8d4:	0004c080 */ 	sll	$t8,$a0,0x2
/*  f0ff8d8:	0304c023 */ 	subu	$t8,$t8,$a0
/*  f0ff8dc:	0018c040 */ 	sll	$t8,$t8,0x1
/*  f0ff8e0:	0158c821 */ 	addu	$t9,$t2,$t8
/*  f0ff8e4:	00026840 */ 	sll	$t5,$v0,0x1
/*  f0ff8e8:	032d1821 */ 	addu	$v1,$t9,$t5
.NB0f0ff8ec:
/*  f0ff8ec:	946c001a */ 	lhu	$t4,0x1a($v1)
/*  f0ff8f0:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f0ff8f4:	51800004 */ 	beqzl	$t4,.NB0f0ff908
/*  f0ff8f8:	812f0003 */ 	lb	$t7,0x3($t1)
/*  f0ff8fc:	03e00008 */ 	jr	$ra
/*  f0ff900:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f0ff904:	812f0003 */ 	lb	$t7,0x3($t1)
.NB0f0ff908:
/*  f0ff908:	00026080 */ 	sll	$t4,$v0,0x2
/*  f0ff90c:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f0ff910:	05e00005 */ 	bltz	$t7,.NB0f0ff928
/*  f0ff914:	014c7021 */ 	addu	$t6,$t2,$t4
/*  f0ff918:	8d380000 */ 	lw	$t8,0x0($t1)
/*  f0ff91c:	00186e40 */ 	sll	$t5,$t8,0x19
/*  f0ff920:	05a10009 */ 	bgez	$t5,.NB0f0ff948
/*  f0ff924:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f0ff928:
/*  f0ff928:	8dcf00a0 */ 	lw	$t7,0xa0($t6)
/*  f0ff92c:	2498001f */ 	addiu	$t8,$a0,0x1f
/*  f0ff930:	03196804 */ 	sllv	$t5,$t9,$t8
/*  f0ff934:	01ed6024 */ 	and	$t4,$t7,$t5
/*  f0ff938:	11800003 */ 	beqz	$t4,.NB0f0ff948
/*  f0ff93c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0ff940:	03e00008 */ 	jr	$ra
/*  f0ff944:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f0ff948:
/*  f0ff948:	144bffe8 */ 	bne	$v0,$t3,.NB0f0ff8ec
/*  f0ff94c:	24630002 */ 	addiu	$v1,$v1,0x2
/*  f0ff950:	1000002c */ 	beqz	$zero,.NB0f0ffa04
/*  f0ff954:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f0ff958:
/*  f0ff958:	18800025 */ 	blez	$a0,.NB0f0ff9f0
/*  f0ff95c:	00003825 */ 	or	$a3,$zero,$zero
/*  f0ff960:	28a10003 */ 	slti	$at,$a1,0x3
.NB0f0ff964:
/*  f0ff964:	1020001c */ 	beqz	$at,.NB0f0ff9d8
/*  f0ff968:	00a01025 */ 	or	$v0,$a1,$zero
/*  f0ff96c:	00077080 */ 	sll	$t6,$a3,0x2
/*  f0ff970:	01c77023 */ 	subu	$t6,$t6,$a3
/*  f0ff974:	000e7040 */ 	sll	$t6,$t6,0x1
/*  f0ff978:	014ec821 */ 	addu	$t9,$t2,$t6
/*  f0ff97c:	0002c040 */ 	sll	$t8,$v0,0x1
/*  f0ff980:	03384021 */ 	addu	$t0,$t9,$t8
.NB0f0ff984:
/*  f0ff984:	950f0020 */ 	lhu	$t7,0x20($t0)
/*  f0ff988:	55e00014 */ 	bnezl	$t7,.NB0f0ff9dc
/*  f0ff98c:	28410003 */ 	slti	$at,$v0,0x3
/*  f0ff990:	812c0003 */ 	lb	$t4,0x3($t1)
/*  f0ff994:	00027880 */ 	sll	$t7,$v0,0x2
/*  f0ff998:	014f6821 */ 	addu	$t5,$t2,$t7
/*  f0ff99c:	05820006 */ 	bltzl	$t4,.NB0f0ff9b8
/*  f0ff9a0:	8dac00a0 */ 	lw	$t4,0xa0($t5)
/*  f0ff9a4:	8d2e0000 */ 	lw	$t6,0x0($t1)
/*  f0ff9a8:	000ec640 */ 	sll	$t8,$t6,0x19
/*  f0ff9ac:	07030008 */ 	bgezl	$t8,.NB0f0ff9d0
/*  f0ff9b0:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f0ff9b4:	8dac00a0 */ 	lw	$t4,0xa0($t5)
.NB0f0ff9b8:
/*  f0ff9b8:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f0ff9bc:	00eec804 */ 	sllv	$t9,$t6,$a3
/*  f0ff9c0:	0199c024 */ 	and	$t8,$t4,$t9
/*  f0ff9c4:	57000005 */ 	bnezl	$t8,.NB0f0ff9dc
/*  f0ff9c8:	28410003 */ 	slti	$at,$v0,0x3
/*  f0ff9cc:	24420001 */ 	addiu	$v0,$v0,0x1
.NB0f0ff9d0:
/*  f0ff9d0:	144bffec */ 	bne	$v0,$t3,.NB0f0ff984
/*  f0ff9d4:	25080002 */ 	addiu	$t0,$t0,0x2
.NB0f0ff9d8:
/*  f0ff9d8:	28410003 */ 	slti	$at,$v0,0x3
.NB0f0ff9dc:
/*  f0ff9dc:	50200005 */ 	beqzl	$at,.NB0f0ff9f4
/*  f0ff9e0:	00e4082a */ 	slt	$at,$a3,$a0
/*  f0ff9e4:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f0ff9e8:	54e4ffde */ 	bnel	$a3,$a0,.NB0f0ff964
/*  f0ff9ec:	28a10003 */ 	slti	$at,$a1,0x3
.NB0f0ff9f0:
/*  f0ff9f0:	00e4082a */ 	slt	$at,$a3,$a0
.NB0f0ff9f4:
/*  f0ff9f4:	14200003 */ 	bnez	$at,.NB0f0ffa04
/*  f0ff9f8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0ff9fc:	03e00008 */ 	jr	$ra
/*  f0ffa00:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f0ffa04:
/*  f0ffa04:	18a00049 */ 	blez	$a1,.NB0f0ffb2c
/*  f0ffa08:	2401002a */ 	addiu	$at,$zero,0x2a
/*  f0ffa0c:	10c10047 */ 	beq	$a2,$at,.NB0f0ffb2c
/*  f0ffa10:	00003825 */ 	or	$a3,$zero,$zero
/*  f0ffa14:	3c06800a */ 	lui	$a2,0x800a
/*  f0ffa18:	24c666f0 */ 	addiu	$a2,$a2,0x66f0
.NB0f0ffa1c:
/*  f0ffa1c:	00001025 */ 	or	$v0,$zero,$zero
/*  f0ffa20:	00001825 */ 	or	$v1,$zero,$zero
/*  f0ffa24:	00c04025 */ 	or	$t0,$a2,$zero
.NB0f0ffa28:
/*  f0ffa28:	950f0020 */ 	lhu	$t7,0x20($t0)
/*  f0ffa2c:	25080002 */ 	addiu	$t0,$t0,0x2
/*  f0ffa30:	55e00013 */ 	bnezl	$t7,.NB0f0ffa80
/*  f0ffa34:	28610006 */ 	slti	$at,$v1,0x6
/*  f0ffa38:	812e0003 */ 	lb	$t6,0x3($t1)
/*  f0ffa3c:	00027880 */ 	sll	$t7,$v0,0x2
/*  f0ffa40:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f0ffa44:	05c00005 */ 	bltz	$t6,.NB0f0ffa5c
/*  f0ffa48:	014f6821 */ 	addu	$t5,$t2,$t7
/*  f0ffa4c:	8d2c0000 */ 	lw	$t4,0x0($t1)
/*  f0ffa50:	000cc640 */ 	sll	$t8,$t4,0x19
/*  f0ffa54:	07030007 */ 	bgezl	$t8,.NB0f0ffa74
/*  f0ffa58:	28410003 */ 	slti	$at,$v0,0x3
.NB0f0ffa5c:
/*  f0ffa5c:	8dae00a0 */ 	lw	$t6,0xa0($t5)
/*  f0ffa60:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f0ffa64:	00ecc804 */ 	sllv	$t9,$t4,$a3
/*  f0ffa68:	01d9c024 */ 	and	$t8,$t6,$t9
/*  f0ffa6c:	17000003 */ 	bnez	$t8,.NB0f0ffa7c
/*  f0ffa70:	28410003 */ 	slti	$at,$v0,0x3
.NB0f0ffa74:
/*  f0ffa74:	1420ffec */ 	bnez	$at,.NB0f0ffa28
/*  f0ffa78:	24630002 */ 	addiu	$v1,$v1,0x2
.NB0f0ffa7c:
/*  f0ffa7c:	28610006 */ 	slti	$at,$v1,0x6
.NB0f0ffa80:
/*  f0ffa80:	10200004 */ 	beqz	$at,.NB0f0ffa94
/*  f0ffa84:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f0ffa88:	28e10011 */ 	slti	$at,$a3,0x11
/*  f0ffa8c:	1420ffe3 */ 	bnez	$at,.NB0f0ffa1c
/*  f0ffa90:	24c60006 */ 	addiu	$a2,$a2,0x6
.NB0f0ffa94:
/*  f0ffa94:	3c0f800a */ 	lui	$t7,0x800a
/*  f0ffa98:	25ef6756 */ 	addiu	$t7,$t7,0x6756
/*  f0ffa9c:	00cf082b */ 	sltu	$at,$a2,$t7
/*  f0ffaa0:	14200022 */ 	bnez	$at,.NB0f0ffb2c
/*  f0ffaa4:	24a3ffff */ 	addiu	$v1,$a1,-1
/*  f0ffaa8:	28610003 */ 	slti	$at,$v1,0x3
/*  f0ffaac:	1020001f */ 	beqz	$at,.NB0f0ffb2c
/*  f0ffab0:	00601025 */ 	or	$v0,$v1,$zero
/*  f0ffab4:	00046880 */ 	sll	$t5,$a0,0x2
/*  f0ffab8:	01a46823 */ 	subu	$t5,$t5,$a0
/*  f0ffabc:	000d6840 */ 	sll	$t5,$t5,0x1
/*  f0ffac0:	014d6021 */ 	addu	$t4,$t2,$t5
/*  f0ffac4:	00037040 */ 	sll	$t6,$v1,0x1
/*  f0ffac8:	018e1821 */ 	addu	$v1,$t4,$t6
.NB0f0ffacc:
/*  f0ffacc:	94790020 */ 	lhu	$t9,0x20($v1)
/*  f0ffad0:	53200004 */ 	beqzl	$t9,.NB0f0ffae4
/*  f0ffad4:	812f0003 */ 	lb	$t7,0x3($t1)
/*  f0ffad8:	03e00008 */ 	jr	$ra
/*  f0ffadc:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f0ffae0:	812f0003 */ 	lb	$t7,0x3($t1)
.NB0f0ffae4:
/*  f0ffae4:	0002c880 */ 	sll	$t9,$v0,0x2
/*  f0ffae8:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f0ffaec:	05e00005 */ 	bltz	$t7,.NB0f0ffb04
/*  f0ffaf0:	0159c021 */ 	addu	$t8,$t2,$t9
/*  f0ffaf4:	8d2d0000 */ 	lw	$t5,0x0($t1)
/*  f0ffaf8:	000d7640 */ 	sll	$t6,$t5,0x19
/*  f0ffafc:	05c10009 */ 	bgez	$t6,.NB0f0ffb24
/*  f0ffb00:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f0ffb04:
/*  f0ffb04:	8f0f00a0 */ 	lw	$t7,0xa0($t8)
/*  f0ffb08:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f0ffb0c:	008d6004 */ 	sllv	$t4,$t5,$a0
/*  f0ffb10:	01ec7024 */ 	and	$t6,$t7,$t4
/*  f0ffb14:	11c00003 */ 	beqz	$t6,.NB0f0ffb24
/*  f0ffb18:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0ffb1c:	03e00008 */ 	jr	$ra
/*  f0ffb20:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f0ffb24:
/*  f0ffb24:	144bffe9 */ 	bne	$v0,$t3,.NB0f0ffacc
/*  f0ffb28:	24630002 */ 	addiu	$v1,$v1,0x2
.NB0f0ffb2c:
/*  f0ffb2c:	00001025 */ 	or	$v0,$zero,$zero
/*  f0ffb30:	03e00008 */ 	jr	$ra
/*  f0ffb34:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

s32 menuhandlerSoloDifficulty(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_CHECKPREFOCUSED:
#if VERSION >= VERSION_NTSC_1_0
		if (isStageDifficultyUnlocked(g_MissionConfig.stageindex, item->param)) {
			if (item->param3 == 0) {
				return true;
			}
			if (item->param <= (u32)g_SoloSaveFile.autodifficulty) {
				return true;
			}
		}
#else
		if (item->param3 == 0) {
			return true;
		}
		if (item->param <= (u32)g_SoloSaveFile.autodifficulty) {
			return true;
		}
#endif
		break;
	case MENUOP_SET:
		g_MissionConfig.pdmode = false;
		g_MissionConfig.difficulty = item->param;
		lvSetDifficulty(g_MissionConfig.difficulty);
		menuPopDialog();
		menuPushDialog(&g_AcceptMissionMenuDialog);
		break;
	case MENUOP_CHECKDISABLED:
		if (!isStageDifficultyUnlocked(g_MissionConfig.stageindex, item->param)) {
			return true;
		}
	}

	return 0;
}

s32 menuhandlerPdMode(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_SET:
		menuPushDialog(&g_PdModeSettingsMenuDialog);
		break;
	case MENUOP_CHECKHIDDEN:
		if (g_SoloSaveFile.besttimes[SOLOSTAGEINDEX_SKEDARRUINS][DIFF_PA] == 0) {
			return true;
		}
	}

	return 0;
}

char *soloMenuTextBestTime(struct menuitem *item)
{
	u16 time = g_SoloSaveFile.besttimes[g_MissionConfig.stageindex][item->param];
	s32 hours = time / 3600;

	if (time == 0) {
		return "--:--\n";
	}

	if (time >= 0xfff) { // 1 hour, 8 minutes, 15 seconds
		return "==:==\n";
	}

	if (hours == 0) {
		s32 mins = time / 60;
		sprintf(g_StringPointer, "%dm:%02ds", mins % 60, time % 60);
	} else {
		s32 mins = time / 60;
		sprintf(g_StringPointer, "%dh:%02dm:%02ds", hours, mins % 60, time % 60);
	}

	return g_StringPointer;
}

struct menuitem g_SoloMissionDifficultyMenuItems[] = {
	{ MENUITEMTYPE_LABEL,       0, 0x00000012, L_OPTIONS_249, L_OPTIONS_250, NULL }, // "Difficulty"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_OPTIONS_251, (u32)&soloMenuTextBestTime, menuhandlerSoloDifficulty }, // "Agent"
	{ MENUITEMTYPE_SELECTABLE,  1, 0x00000000, L_OPTIONS_252, (u32)&soloMenuTextBestTime, menuhandlerSoloDifficulty }, // "Special Agent"
	{ MENUITEMTYPE_SELECTABLE,  2, 0x00000000, L_OPTIONS_253, (u32)&soloMenuTextBestTime, menuhandlerSoloDifficulty }, // "Perfect Agent"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_MPWEAPONS_221, 0x00000000, menuhandlerPdMode }, // "Perfect Dark"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_254, 0x00000000, NULL }, // "Cancel"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_SoloMissionDifficultyMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_248, // "Select Difficulty"
	g_SoloMissionDifficultyMenuItems,
	NULL,
	0x00000004,
	NULL,
};

const u32 var7f1b2d40[] = {0x57055706};
const u32 var7f1b2d44[] = {0x57075708};
const u32 var7f1b2d48[] = {0x57090000};

s32 menuhandlerBuddyOptionsContinue(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		menuPopDialog();
		menuPushDialog(&g_AcceptMissionMenuDialog);
	}

	if (operation == MENUOP_CHECKPREFOCUSED) {
		return true;
	}

	return 0;
}

#if VERSION >= VERSION_NTSC_1_0
s32 getMaxAiBuddies(void)
{
	s32 extra = 0;
	s32 max = 1 - g_MissionConfig.difficulty;
	s32 d;

	for (d = 0; d != 3; d++) {
		if ((g_SoloSaveFile.coopcompletions[d] | 0xfffe0000) == 0xffffffff) {
			extra = d + 1;
		}
	}

	max += extra;

	if (max > 4) {
		max = 4;
	}

	if (max < 1) {
		max = 1;
	}

	return max;
}
#endif

s32 menudialogCoopAntiOptions(s32 operation, struct menudialog *dialog, union handlerdata *data)
{
#if VERSION >= VERSION_NTSC_1_0
	if (operation == MENUOP_OPEN) {
		s32 max = getMaxAiBuddies();

		if (g_Vars.numaibuddies > max) {
			g_Vars.numaibuddies = max;
		}
	}
#endif

	if (operation == MENUOP_TICK) {
		if (g_Menus[g_MpPlayerNum].curframe &&
				g_Menus[g_MpPlayerNum].curframe->dialog == dialog) {
			struct menuinputs *inputs = data->dialog2.inputs;

			if (inputs->start) {
				menuhandlerBuddyOptionsContinue(MENUOP_SET, NULL, NULL);
			}

			inputs->start = false;
		}
	}

	return 0;
}

s32 menuhandlerCoopRadar(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return g_Vars.coopradaron;
	case MENUOP_SET:
		g_Vars.coopradaron = data->checkbox.value ? 1 : 0;
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerCoopFriendlyFire(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return g_Vars.coopfriendlyfire;
	case MENUOP_SET:
		g_Vars.coopfriendlyfire = data->checkbox.value ? 1 : 0;
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel menuhandlerCoopBuddy
/*  f10429c:	27bdffc0 */ 	addiu	$sp,$sp,-64
/*  f1042a0:	3c0f7f1b */ 	lui	$t7,%hi(var7f1b2d40)
/*  f1042a4:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f1042a8:	afa50044 */ 	sw	$a1,0x44($sp)
/*  f1042ac:	afa60048 */ 	sw	$a2,0x48($sp)
/*  f1042b0:	25ef2d40 */ 	addiu	$t7,$t7,%lo(var7f1b2d40)
/*  f1042b4:	8de10000 */ 	lw	$at,0x0($t7)
/*  f1042b8:	27ae0034 */ 	addiu	$t6,$sp,0x34
/*  f1042bc:	8de80004 */ 	lw	$t0,0x4($t7)
/*  f1042c0:	adc10000 */ 	sw	$at,0x0($t6)
/*  f1042c4:	95e10008 */ 	lhu	$at,0x8($t7)
/*  f1042c8:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f1042cc:	adc80004 */ 	sw	$t0,0x4($t6)
/*  f1042d0:	1085000c */ 	beq	$a0,$a1,.L0f104304
/*  f1042d4:	a5c10008 */ 	sh	$at,0x8($t6)
/*  f1042d8:	24010003 */ 	addiu	$at,$zero,0x3
/*  f1042dc:	10810017 */ 	beq	$a0,$at,.L0f10433c
/*  f1042e0:	24030001 */ 	addiu	$v1,$zero,0x1
/*  f1042e4:	24010006 */ 	addiu	$at,$zero,0x6
/*  f1042e8:	10810024 */ 	beq	$a0,$at,.L0f10437c
/*  f1042ec:	24030001 */ 	addiu	$v1,$zero,0x1
/*  f1042f0:	24010007 */ 	addiu	$at,$zero,0x7
/*  f1042f4:	10810031 */ 	beq	$a0,$at,.L0f1043bc
/*  f1042f8:	00000000 */ 	nop
/*  f1042fc:	10000044 */ 	b	.L0f104410
/*  f104300:	00001025 */ 	or	$v0,$zero,$zero
.L0f104304:
/*  f104304:	0fc41023 */ 	jal	getMaxAiBuddies
/*  f104308:	00000000 */ 	nop
/*  f10430c:	afa20030 */ 	sw	$v0,0x30($sp)
/*  f104310:	0c005013 */ 	jal	joyGetConnectedControllers
/*  f104314:	afa0002c */ 	sw	$zero,0x2c($sp)
/*  f104318:	30490002 */ 	andi	$t1,$v0,0x2
/*  f10431c:	11200002 */ 	beqz	$t1,.L0f104328
/*  f104320:	8fa3002c */ 	lw	$v1,0x2c($sp)
/*  f104324:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f104328:
/*  f104328:	8faa0030 */ 	lw	$t2,0x30($sp)
/*  f10432c:	8fac0048 */ 	lw	$t4,0x48($sp)
/*  f104330:	006a5821 */ 	addu	$t3,$v1,$t2
/*  f104334:	10000035 */ 	b	.L0f10440c
/*  f104338:	ad8b0000 */ 	sw	$t3,0x0($t4)
.L0f10433c:
/*  f10433c:	0c005013 */ 	jal	joyGetConnectedControllers
/*  f104340:	afa30028 */ 	sw	$v1,0x28($sp)
/*  f104344:	304d0002 */ 	andi	$t5,$v0,0x2
/*  f104348:	11a00002 */ 	beqz	$t5,.L0f104354
/*  f10434c:	8fa30028 */ 	lw	$v1,0x28($sp)
/*  f104350:	00001825 */ 	or	$v1,$zero,$zero
.L0f104354:
/*  f104354:	8fb90048 */ 	lw	$t9,0x48($sp)
/*  f104358:	00037840 */ 	sll	$t7,$v1,0x1
/*  f10435c:	8f380000 */ 	lw	$t8,0x0($t9)
/*  f104360:	00187040 */ 	sll	$t6,$t8,0x1
/*  f104364:	01cf4021 */ 	addu	$t0,$t6,$t7
/*  f104368:	03a82021 */ 	addu	$a0,$sp,$t0
/*  f10436c:	0fc5b9f1 */ 	jal	langGet
/*  f104370:	94840034 */ 	lhu	$a0,0x34($a0)
/*  f104374:	10000027 */ 	b	.L0f104414
/*  f104378:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f10437c:
/*  f10437c:	0c005013 */ 	jal	joyGetConnectedControllers
/*  f104380:	afa30024 */ 	sw	$v1,0x24($sp)
/*  f104384:	30490002 */ 	andi	$t1,$v0,0x2
/*  f104388:	11200002 */ 	beqz	$t1,.L0f104394
/*  f10438c:	8fa30024 */ 	lw	$v1,0x24($sp)
/*  f104390:	00001825 */ 	or	$v1,$zero,$zero
.L0f104394:
/*  f104394:	8faa0048 */ 	lw	$t2,0x48($sp)
/*  f104398:	3c02800a */ 	lui	$v0,%hi(g_Vars)
/*  f10439c:	24429fc0 */ 	addiu	$v0,$v0,%lo(g_Vars)
/*  f1043a0:	8c4d0458 */ 	lw	$t5,0x458($v0)
/*  f1043a4:	8d4b0000 */ 	lw	$t3,0x0($t2)
/*  f1043a8:	35b90001 */ 	ori	$t9,$t5,0x1
/*  f1043ac:	01636021 */ 	addu	$t4,$t3,$v1
/*  f1043b0:	ac4c0474 */ 	sw	$t4,0x474($v0)
/*  f1043b4:	10000015 */ 	b	.L0f10440c
/*  f1043b8:	ac590458 */ 	sw	$t9,0x458($v0)
.L0f1043bc:
/*  f1043bc:	0c005013 */ 	jal	joyGetConnectedControllers
/*  f1043c0:	afa50020 */ 	sw	$a1,0x20($sp)
/*  f1043c4:	30580002 */ 	andi	$t8,$v0,0x2
/*  f1043c8:	8fa30020 */ 	lw	$v1,0x20($sp)
/*  f1043cc:	13000002 */ 	beqz	$t8,.L0f1043d8
/*  f1043d0:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f1043d4:	00001825 */ 	or	$v1,$zero,$zero
.L0f1043d8:
/*  f1043d8:	14650006 */ 	bne	$v1,$a1,.L0f1043f4
/*  f1043dc:	3c02800a */ 	lui	$v0,%hi(g_Vars)
/*  f1043e0:	24429fc0 */ 	addiu	$v0,$v0,%lo(g_Vars)
/*  f1043e4:	8c4e0474 */ 	lw	$t6,0x474($v0)
/*  f1043e8:	15c00002 */ 	bnez	$t6,.L0f1043f4
/*  f1043ec:	00000000 */ 	nop
/*  f1043f0:	ac450474 */ 	sw	$a1,0x474($v0)
.L0f1043f4:
/*  f1043f4:	3c02800a */ 	lui	$v0,%hi(g_Vars)
/*  f1043f8:	24429fc0 */ 	addiu	$v0,$v0,%lo(g_Vars)
/*  f1043fc:	8c4f0474 */ 	lw	$t7,0x474($v0)
/*  f104400:	8fa90048 */ 	lw	$t1,0x48($sp)
/*  f104404:	01e34023 */ 	subu	$t0,$t7,$v1
/*  f104408:	ad280000 */ 	sw	$t0,0x0($t1)
.L0f10440c:
/*  f10440c:	00001025 */ 	or	$v0,$zero,$zero
.L0f104410:
/*  f104410:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f104414:
/*  f104414:	27bd0040 */ 	addiu	$sp,$sp,0x40
/*  f104418:	03e00008 */ 	jr	$ra
/*  f10441c:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel menuhandlerCoopBuddy
/*  f100014:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*  f100018:	3c0f7f1b */ 	lui	$t7,0x7f1b
/*  f10001c:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f100020:	afa40048 */ 	sw	$a0,0x48($sp)
/*  f100024:	afa5004c */ 	sw	$a1,0x4c($sp)
/*  f100028:	afa60050 */ 	sw	$a2,0x50($sp)
/*  f10002c:	25efd040 */ 	addiu	$t7,$t7,-12224
/*  f100030:	8de10000 */ 	lw	$at,0x0($t7)
/*  f100034:	27ae003c */ 	addiu	$t6,$sp,0x3c
/*  f100038:	8dea0004 */ 	lw	$t2,0x4($t7)
/*  f10003c:	adc10000 */ 	sw	$at,0x0($t6)
/*  f100040:	95e10008 */ 	lhu	$at,0x8($t7)
/*  f100044:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f100048:	00802825 */ 	or	$a1,$a0,$zero
/*  f10004c:	adca0004 */ 	sw	$t2,0x4($t6)
/*  f100050:	1089000c */ 	beq	$a0,$t1,.NB0f100084
/*  f100054:	a5c10008 */ 	sh	$at,0x8($t6)
/*  f100058:	24040003 */ 	addiu	$a0,$zero,0x3
/*  f10005c:	10a40037 */ 	beq	$a1,$a0,.NB0f10013c
/*  f100060:	24030001 */ 	addiu	$v1,$zero,0x1
/*  f100064:	24010006 */ 	addiu	$at,$zero,0x6
/*  f100068:	10a10044 */ 	beq	$a1,$at,.NB0f10017c
/*  f10006c:	24030001 */ 	addiu	$v1,$zero,0x1
/*  f100070:	24010007 */ 	addiu	$at,$zero,0x7
/*  f100074:	10a10051 */ 	beq	$a1,$at,.NB0f1001bc
/*  f100078:	00000000 */ 	sll	$zero,$zero,0x0
/*  f10007c:	10000064 */ 	beqz	$zero,.NB0f100210
/*  f100080:	00001025 */ 	or	$v0,$zero,$zero
.NB0f100084:
/*  f100084:	3c0b800a */ 	lui	$t3,0x800a
/*  f100088:	8d6b27a8 */ 	lw	$t3,0x27a8($t3)
/*  f10008c:	afa0002c */ 	sw	$zero,0x2c($sp)
/*  f100090:	afa00038 */ 	sw	$zero,0x38($sp)
/*  f100094:	000b6642 */ 	srl	$t4,$t3,0x19
/*  f100098:	012c4023 */ 	subu	$t0,$t1,$t4
/*  f10009c:	0c0053a4 */ 	jal	joyGetConnectedControllers
/*  f1000a0:	afa80030 */ 	sw	$t0,0x30($sp)
/*  f1000a4:	304d0002 */ 	andi	$t5,$v0,0x2
/*  f1000a8:	8fa70038 */ 	lw	$a3,0x38($sp)
/*  f1000ac:	11a00003 */ 	beqz	$t5,.NB0f1000bc
/*  f1000b0:	8fa80030 */ 	lw	$t0,0x30($sp)
/*  f1000b4:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f1000b8:	afb9002c */ 	sw	$t9,0x2c($sp)
.NB0f1000bc:
/*  f1000bc:	3c03800a */ 	lui	$v1,0x800a
/*  f1000c0:	246366f0 */ 	addiu	$v1,$v1,0x66f0
/*  f1000c4:	00001025 */ 	or	$v0,$zero,$zero
/*  f1000c8:	3c06fffe */ 	lui	$a2,0xfffe
/*  f1000cc:	2405ffff */ 	addiu	$a1,$zero,-1
/*  f1000d0:	24040003 */ 	addiu	$a0,$zero,0x3
.NB0f1000d4:
/*  f1000d4:	8c7800a0 */ 	lw	$t8,0xa0($v1)
/*  f1000d8:	03067025 */ 	or	$t6,$t8,$a2
/*  f1000dc:	54ae0003 */ 	bnel	$a1,$t6,.NB0f1000ec
/*  f1000e0:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f1000e4:	24470001 */ 	addiu	$a3,$v0,0x1
/*  f1000e8:	24420001 */ 	addiu	$v0,$v0,0x1
.NB0f1000ec:
/*  f1000ec:	1444fff9 */ 	bne	$v0,$a0,.NB0f1000d4
/*  f1000f0:	24630004 */ 	addiu	$v1,$v1,0x4
/*  f1000f4:	01074021 */ 	addu	$t0,$t0,$a3
/*  f1000f8:	29010005 */ 	slti	$at,$t0,0x5
/*  f1000fc:	14200002 */ 	bnez	$at,.NB0f100108
/*  f100100:	00000000 */ 	sll	$zero,$zero,0x0
/*  f100104:	24080004 */ 	addiu	$t0,$zero,0x4
.NB0f100108:
/*  f100108:	1d000002 */ 	bgtz	$t0,.NB0f100114
/*  f10010c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f100110:	24080001 */ 	addiu	$t0,$zero,0x1
.NB0f100114:
/*  f100114:	0fc466d8 */ 	jal	debug0f119b60nb
/*  f100118:	afa80030 */ 	sw	$t0,0x30($sp)
/*  f10011c:	10400002 */ 	beqz	$v0,.NB0f100128
/*  f100120:	8fa80030 */ 	lw	$t0,0x30($sp)
/*  f100124:	24080004 */ 	addiu	$t0,$zero,0x4
.NB0f100128:
/*  f100128:	8faf002c */ 	lw	$t7,0x2c($sp)
/*  f10012c:	8fab0050 */ 	lw	$t3,0x50($sp)
/*  f100130:	01e85021 */ 	addu	$t2,$t7,$t0
/*  f100134:	10000035 */ 	beqz	$zero,.NB0f10020c
/*  f100138:	ad6a0000 */ 	sw	$t2,0x0($t3)
.NB0f10013c:
/*  f10013c:	0c0053a4 */ 	jal	joyGetConnectedControllers
/*  f100140:	afa30028 */ 	sw	$v1,0x28($sp)
/*  f100144:	304c0002 */ 	andi	$t4,$v0,0x2
/*  f100148:	11800002 */ 	beqz	$t4,.NB0f100154
/*  f10014c:	8fa30028 */ 	lw	$v1,0x28($sp)
/*  f100150:	00001825 */ 	or	$v1,$zero,$zero
.NB0f100154:
/*  f100154:	8fad0050 */ 	lw	$t5,0x50($sp)
/*  f100158:	00037040 */ 	sll	$t6,$v1,0x1
/*  f10015c:	8db90000 */ 	lw	$t9,0x0($t5)
/*  f100160:	0019c040 */ 	sll	$t8,$t9,0x1
/*  f100164:	030e7821 */ 	addu	$t7,$t8,$t6
/*  f100168:	03af2021 */ 	addu	$a0,$sp,$t7
/*  f10016c:	0fc5a4dd */ 	jal	langGet
/*  f100170:	9484003c */ 	lhu	$a0,0x3c($a0)
/*  f100174:	10000027 */ 	beqz	$zero,.NB0f100214
/*  f100178:	8fbf0014 */ 	lw	$ra,0x14($sp)
.NB0f10017c:
/*  f10017c:	0c0053a4 */ 	jal	joyGetConnectedControllers
/*  f100180:	afa30024 */ 	sw	$v1,0x24($sp)
/*  f100184:	304a0002 */ 	andi	$t2,$v0,0x2
/*  f100188:	11400002 */ 	beqz	$t2,.NB0f100194
/*  f10018c:	8fa30024 */ 	lw	$v1,0x24($sp)
/*  f100190:	00001825 */ 	or	$v1,$zero,$zero
.NB0f100194:
/*  f100194:	8fab0050 */ 	lw	$t3,0x50($sp)
/*  f100198:	3c02800a */ 	lui	$v0,0x800a
/*  f10019c:	2442e6c0 */ 	addiu	$v0,$v0,-6464
/*  f1001a0:	8c590458 */ 	lw	$t9,0x458($v0)
/*  f1001a4:	8d6c0000 */ 	lw	$t4,0x0($t3)
/*  f1001a8:	37380001 */ 	ori	$t8,$t9,0x1
/*  f1001ac:	01836821 */ 	addu	$t5,$t4,$v1
/*  f1001b0:	ac4d0474 */ 	sw	$t5,0x474($v0)
/*  f1001b4:	10000015 */ 	beqz	$zero,.NB0f10020c
/*  f1001b8:	ac580458 */ 	sw	$t8,0x458($v0)
.NB0f1001bc:
/*  f1001bc:	0c0053a4 */ 	jal	joyGetConnectedControllers
/*  f1001c0:	afa90020 */ 	sw	$t1,0x20($sp)
/*  f1001c4:	304e0002 */ 	andi	$t6,$v0,0x2
/*  f1001c8:	8fa30020 */ 	lw	$v1,0x20($sp)
/*  f1001cc:	11c00002 */ 	beqz	$t6,.NB0f1001d8
/*  f1001d0:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f1001d4:	00001825 */ 	or	$v1,$zero,$zero
.NB0f1001d8:
/*  f1001d8:	14690006 */ 	bne	$v1,$t1,.NB0f1001f4
/*  f1001dc:	3c02800a */ 	lui	$v0,0x800a
/*  f1001e0:	2442e6c0 */ 	addiu	$v0,$v0,-6464
/*  f1001e4:	8c4f0474 */ 	lw	$t7,0x474($v0)
/*  f1001e8:	15e00002 */ 	bnez	$t7,.NB0f1001f4
/*  f1001ec:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1001f0:	ac490474 */ 	sw	$t1,0x474($v0)
.NB0f1001f4:
/*  f1001f4:	3c02800a */ 	lui	$v0,0x800a
/*  f1001f8:	2442e6c0 */ 	addiu	$v0,$v0,-6464
/*  f1001fc:	8c4a0474 */ 	lw	$t2,0x474($v0)
/*  f100200:	8fac0050 */ 	lw	$t4,0x50($sp)
/*  f100204:	01435823 */ 	subu	$t3,$t2,$v1
/*  f100208:	ad8b0000 */ 	sw	$t3,0x0($t4)
.NB0f10020c:
/*  f10020c:	00001025 */ 	or	$v0,$zero,$zero
.NB0f100210:
/*  f100210:	8fbf0014 */ 	lw	$ra,0x14($sp)
.NB0f100214:
/*  f100214:	27bd0048 */ 	addiu	$sp,$sp,0x48
/*  f100218:	03e00008 */ 	jr	$ra
/*  f10021c:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

struct menuitem g_CoopOptionsMenuItems[] = {
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_256, 0x00000000, menuhandlerCoopRadar }, // "Radar On"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_257, 0x00000000, menuhandlerCoopFriendlyFire }, // "Friendly Fire"
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_OPTIONS_258, 0x00000000, menuhandlerCoopBuddy }, // "Perfect Buddy"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL }, // ""
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_OPTIONS_259, 0x00000000, menuhandlerBuddyOptionsContinue }, // "Continue"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_260, 0x00000000, NULL }, // "Cancel"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL }, // ""
};

struct menudialog g_CoopOptionsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_255, // "Co-Operative Options"
	g_CoopOptionsMenuItems,
	menudialogCoopAntiOptions,
	0x00000004,
	NULL,
};

s32 menuhandlerAntiRadar(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return g_Vars.antiradaron;
	case MENUOP_SET:
		g_Vars.antiradaron = data->checkbox.value ? 1 : 0;
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerAntiPlayer(s32 operation, struct menuitem *item, union handlerdata *data)
{
	const u16 labels[] = {L_OPTIONS_271, L_OPTIONS_272};

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		data->dropdown.value = 2;
		break;
	case MENUOP_GETOPTIONTEXT:
		return (s32) langGet(labels[data->dropdown.value]);
	case MENUOP_SET:
		g_Vars.pendingantiplayernum = data->dropdown.value;
		g_Vars.modifiedfiles |= MODFILE_SOLO;
		break;
	case MENUOP_GETOPTIONVALUE:
		data->dropdown.value = g_Vars.pendingantiplayernum;
		break;
	}

	return 0;
}

struct menuitem g_AntiOptionsMenuItems[] = {
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_267, 0x00000000, menuhandlerAntiRadar }, // "Radar On"
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_OPTIONS_268, 0x00000000, menuhandlerAntiPlayer }, // "Counter-Operative"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_OPTIONS_269, 0x00000000, menuhandlerBuddyOptionsContinue }, // "Continue"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_270, 0x00000000, NULL }, // "Cancel"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_AntiOptionsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_266, // "Counter-Operative Options"
	g_AntiOptionsMenuItems,
	menudialogCoopAntiOptions,
	0x00000004,
	NULL,
};

const char var7f1b2d50[] = "\n";

s32 menuhandlerCoopDifficulty(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_SET:
		g_MissionConfig.pdmode = false;
		g_MissionConfig.difficulty = item->param;
		lvSetDifficulty(g_MissionConfig.difficulty);
		menuPopDialog();
		menuPushDialog(&g_CoopOptionsMenuDialog);
		break;
	case MENUOP_CHECKDISABLED:
		if (!isStageDifficultyUnlocked(g_MissionConfig.stageindex, item->param)) {
			return true;
		}
	}

	return 0;
}

struct menuitem g_CoopMissionDifficultyMenuItems[] = {
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_OPTIONS_251, 0x00000000, menuhandlerCoopDifficulty }, // "Agent"
	{ MENUITEMTYPE_SELECTABLE,  1, 0x00000000, L_OPTIONS_252, 0x00000000, menuhandlerCoopDifficulty }, // "Special Agent"
	{ MENUITEMTYPE_SELECTABLE,  2, 0x00000000, L_OPTIONS_253, 0x00000000, menuhandlerCoopDifficulty }, // "Perfect Agent"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_254, 0x00000000, NULL }, // "Cancel"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_CoopMissionDifficultyMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_248, // "Select Difficulty"
	g_CoopMissionDifficultyMenuItems,
	NULL,
	0x00000004,
	NULL,
};

s32 menuhandlerAntiDifficulty(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_SET:
		g_MissionConfig.pdmode = false;
		g_MissionConfig.difficulty = item->param;
		lvSetDifficulty(g_MissionConfig.difficulty);
		menuPopDialog();
		menuPushDialog(&g_AntiOptionsMenuDialog);
	}

	return 0;
}

struct menuitem g_AntiMissionDifficultyMenuItems[] = {
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_OPTIONS_251, 0x00000000, menuhandlerAntiDifficulty }, // "Agent"
	{ MENUITEMTYPE_SELECTABLE,  1, 0x00000000, L_OPTIONS_252, 0x00000000, menuhandlerAntiDifficulty }, // "Special Agent"
	{ MENUITEMTYPE_SELECTABLE,  2, 0x00000000, L_OPTIONS_253, 0x00000000, menuhandlerAntiDifficulty }, // "Perfect Agent"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_254, 0x00000000, NULL }, // "Cancel"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_AntiMissionDifficultyMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_248, // "Select Difficulty"
	g_AntiMissionDifficultyMenuItems,
	NULL,
	0x00000004,
	NULL,
};

struct stageoverviewentry g_StageNames[NUM_SOLOSTAGES] = {
	// stage,             unk04,
	{ STAGE_DEFECTION,     0x0c, L_OPTIONS_133, L_OPTIONS_134, L_MPWEAPONS_124 },
	{ STAGE_INVESTIGATION, 0x0d, L_OPTIONS_135, L_OPTIONS_136, L_MPWEAPONS_172 },
	{ STAGE_EXTRACTION,    0x0e, L_OPTIONS_137, L_OPTIONS_138, L_MPWEAPONS_125 },
	{ STAGE_VILLA,         0x0f, L_OPTIONS_139, L_OPTIONS_140, L_OPTIONS_139   },
	{ STAGE_CHICAGO,       0x10, L_OPTIONS_141, L_OPTIONS_142, L_OPTIONS_141   },
	{ STAGE_G5BUILDING,    0x11, L_OPTIONS_143, L_OPTIONS_144, L_OPTIONS_143   },
	{ STAGE_INFILTRATION,  0x12, L_OPTIONS_145, L_OPTIONS_146, L_MPWEAPONS_126 },
	{ STAGE_RESCUE,        0x13, L_OPTIONS_147, L_OPTIONS_148, L_MPWEAPONS_127 },
	{ STAGE_ESCAPE,        0x14, L_OPTIONS_149, L_OPTIONS_150, L_MPWEAPONS_128 },
	{ STAGE_AIRBASE,       0x15, L_OPTIONS_151, L_OPTIONS_152, L_OPTIONS_151   },
	{ STAGE_AIRFORCEONE,   0x16, L_OPTIONS_153, L_OPTIONS_154, L_OPTIONS_153   },
	{ STAGE_CRASHSITE,     0x17, L_OPTIONS_155, L_OPTIONS_156, L_OPTIONS_155   },
	{ STAGE_PELAGIC,       0x18, L_OPTIONS_157, L_OPTIONS_158, L_OPTIONS_157   },
	{ STAGE_DEEPSEA,       0x19, L_OPTIONS_159, L_OPTIONS_160, L_OPTIONS_159   },
	{ STAGE_DEFENSE,       0x1a, L_OPTIONS_161, L_OPTIONS_162, L_OPTIONS_161   },
	{ STAGE_ATTACKSHIP,    0x1b, L_OPTIONS_163, L_OPTIONS_164, L_OPTIONS_163   },
	{ STAGE_SKEDARRUINS,   0x1c, L_OPTIONS_165, L_OPTIONS_166, L_OPTIONS_165   },
	{ STAGE_MBR,           0x1c, L_OPTIONS_167, L_OPTIONS_003,   L_OPTIONS_167   },
	{ STAGE_MAIANSOS,      0x1c, L_OPTIONS_168, L_OPTIONS_003,   L_OPTIONS_168   },
	{ STAGE_WAR,           0x1c, L_OPTIONS_170, L_OPTIONS_003,   L_OPTIONS_170   },
	{ STAGE_DUEL,          0x1c, L_OPTIONS_171, L_OPTIONS_003,   L_OPTIONS_171   },
};

s32 getNumUnlockedSpecialStages(void)
{
	s32 next = 0;
	s32 offsetforduel = 1;
	s32 i;

	for (i = 0; i < 3; i++) {
		if (g_SoloSaveFile.besttimes[SOLOSTAGEINDEX_SKEDARRUINS][i]) {
			next = i + 1;
		}
	}

	if (g_MissionConfig.iscoop || g_MissionConfig.isanti) {
		offsetforduel = 0;
	} else {
		for (i = 0; i != 32; i++) {
			if (ciGetFiringRangeScore(i) <= 0) {
				offsetforduel = 0;
			}
		}
	}

	return next + offsetforduel;
}

s32 func0f104720(s32 value)
{
	s32 next = 0;
	s32 d;

	for (d = 0; d != 3; d++) {
		if (g_SoloSaveFile.besttimes[SOLOSTAGEINDEX_SKEDARRUINS][d]) {
			next = d + 1;
		}
	}

	if (next > value) {
		return 17 + value;
	}

	return 20;
}

struct mission missions[] = {
	// first stage index, name
	{  0, L_OPTIONS_123 }, // "Mission 1"
	{  3, L_OPTIONS_124 }, // "Mission 2"
	{  4, L_OPTIONS_125 }, // "Mission 3"
	{  6, L_OPTIONS_126 }, // "Mission 4"
	{  9, L_OPTIONS_127 }, // "Mission 5"
	{ 12, L_OPTIONS_128 }, // "Mission 6"
	{ 14, L_OPTIONS_129 }, // "Mission 7"
	{ 15, L_OPTIONS_130 }, // "Mission 8"
	{ 16, L_OPTIONS_131 }, // "Mission 9"
	{ 99, L_OPTIONS_132 }, // "Special Assignments"
};

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel menuhandler0010476c
.late_rodata
glabel var7f1b2d9c
.word menuhandler0010476c+0x80 # f1047ec
glabel var7f1b2da0
.word menuhandler0010476c+0x394 # f104b00
glabel var7f1b2da4
.word menuhandler0010476c+0x144 # f1048b0
glabel var7f1b2da8
.word menuhandler0010476c+0x400 # f104b6c
glabel var7f1b2dac
.word menuhandler0010476c+0x434 # f104ba0
glabel var7f1b2db0
.word menuhandler0010476c+0x1d0 # f10493c
glabel var7f1b2db4
.word menuhandler0010476c+0x2a8 # f104a14
glabel var7f1b2db8
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2dbc
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2dc0
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2dc4
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2dc8
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2dcc
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2dd0
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2dd4
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2dd8
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2ddc
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2de0
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2de4
.word menuhandler0010476c+0x47c # f104be8
glabel var7f1b2de8
.word menuhandler0010476c+0xe10 # f10557c
glabel var7f1b2dec
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2df0
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2df4
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2df8
.word menuhandler0010476c+0xe18 # f105584
glabel var7f1b2dfc
.word menuhandler0010476c+0x2b8 # f104a24
.text
/*  f10476c:	27bdfe08 */ 	addiu	$sp,$sp,-504
/*  f104770:	3c0e8007 */ 	lui	$t6,%hi(missions)
/*  f104774:	afb00038 */ 	sw	$s0,0x38($sp)
/*  f104778:	27a201a8 */ 	addiu	$v0,$sp,0x1a8
/*  f10477c:	25ce1f68 */ 	addiu	$t6,$t6,%lo(missions)
/*  f104780:	00c08025 */ 	or	$s0,$a2,$zero
/*  f104784:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f104788:	afa501fc */ 	sw	$a1,0x1fc($sp)
/*  f10478c:	25d90048 */ 	addiu	$t9,$t6,0x48
/*  f104790:	0040c025 */ 	or	$t8,$v0,$zero
.L0f104794:
/*  f104794:	8dc10000 */ 	lw	$at,0x0($t6)
/*  f104798:	25ce000c */ 	addiu	$t6,$t6,0xc
/*  f10479c:	2718000c */ 	addiu	$t8,$t8,0xc
/*  f1047a0:	af01fff4 */ 	sw	$at,-0xc($t8)
/*  f1047a4:	8dc1fff8 */ 	lw	$at,-0x8($t6)
/*  f1047a8:	af01fff8 */ 	sw	$at,-0x8($t8)
/*  f1047ac:	8dc1fffc */ 	lw	$at,-0x4($t6)
/*  f1047b0:	15d9fff8 */ 	bne	$t6,$t9,.L0f104794
/*  f1047b4:	af01fffc */ 	sw	$at,-0x4($t8)
/*  f1047b8:	8dc10000 */ 	lw	$at,0x0($t6)
/*  f1047bc:	248fffff */ 	addiu	$t7,$a0,-1
/*  f1047c0:	af010000 */ 	sw	$at,0x0($t8)
/*  f1047c4:	8dd90004 */ 	lw	$t9,0x4($t6)
/*  f1047c8:	2de10019 */ 	sltiu	$at,$t7,0x19
/*  f1047cc:	1020036d */ 	beqz	$at,.L0f105584
/*  f1047d0:	af190004 */ 	sw	$t9,0x4($t8)
/*  f1047d4:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f1047d8:	3c017f1b */ 	lui	$at,%hi(var7f1b2d9c)
/*  f1047dc:	002f0821 */ 	addu	$at,$at,$t7
/*  f1047e0:	8c2f2d9c */ 	lw	$t7,%lo(var7f1b2d9c)($at)
/*  f1047e4:	01e00008 */ 	jr	$t7
/*  f1047e8:	00000000 */ 	nop
/*  f1047ec:	3c0a800a */ 	lui	$t2,%hi(g_SoloSaveFile)
/*  f1047f0:	3c09800a */ 	lui	$t1,%hi(g_SoloSaveFile)
/*  f1047f4:	3c08800a */ 	lui	$t0,%hi(g_MissionConfig)
/*  f1047f8:	ae000000 */ 	sw	$zero,0x0($s0)
/*  f1047fc:	2508dfe8 */ 	addiu	$t0,$t0,%lo(g_MissionConfig)
/*  f104800:	25292200 */ 	addiu	$t1,$t1,%lo(g_SoloSaveFile)
/*  f104804:	254a2200 */ 	addiu	$t2,$t2,%lo(g_SoloSaveFile)
/*  f104808:	00003025 */ 	or	$a2,$zero,$zero
/*  f10480c:	240b0011 */ 	addiu	$t3,$zero,0x11
/*  f104810:	24070003 */ 	addiu	$a3,$zero,0x3
.L0f104814:
/*  f104814:	91050003 */ 	lbu	$a1,0x3($t0)
/*  f104818:	00002025 */ 	or	$a0,$zero,$zero
/*  f10481c:	00001025 */ 	or	$v0,$zero,$zero
/*  f104820:	0005c9c2 */ 	srl	$t9,$a1,0x7
/*  f104824:	03202825 */ 	or	$a1,$t9,$zero
/*  f104828:	01401825 */ 	or	$v1,$t2,$zero
.L0f10482c:
/*  f10482c:	946e0020 */ 	lhu	$t6,0x20($v1)
/*  f104830:	11c00002 */ 	beqz	$t6,.L0f10483c
/*  f104834:	00000000 */ 	nop
/*  f104838:	24040001 */ 	addiu	$a0,$zero,0x1
.L0f10483c:
/*  f10483c:	14a00004 */ 	bnez	$a1,.L0f104850
/*  f104840:	00027080 */ 	sll	$t6,$v0,0x2
/*  f104844:	8d180000 */ 	lw	$t8,0x0($t0)
/*  f104848:	0018ce40 */ 	sll	$t9,$t8,0x19
/*  f10484c:	07210008 */ 	bgez	$t9,.L0f104870
.L0f104850:
/*  f104850:	012ec021 */ 	addu	$t8,$t1,$t6
/*  f104854:	8f0f00a0 */ 	lw	$t7,0xa0($t8)
/*  f104858:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f10485c:	00d97004 */ 	sllv	$t6,$t9,$a2
/*  f104860:	01eec024 */ 	and	$t8,$t7,$t6
/*  f104864:	53000003 */ 	beqzl	$t8,.L0f104874
/*  f104868:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f10486c:	24040001 */ 	addiu	$a0,$zero,0x1
.L0f104870:
/*  f104870:	24420001 */ 	addiu	$v0,$v0,0x1
.L0f104874:
/*  f104874:	1447ffed */ 	bne	$v0,$a3,.L0f10482c
/*  f104878:	24630002 */ 	addiu	$v1,$v1,0x2
/*  f10487c:	8e190000 */ 	lw	$t9,0x0($s0)
/*  f104880:	24c60001 */ 	addiu	$a2,$a2,0x1
/*  f104884:	272f0001 */ 	addiu	$t7,$t9,0x1
/*  f104888:	10800003 */ 	beqz	$a0,.L0f104898
/*  f10488c:	ae0f0000 */ 	sw	$t7,0x0($s0)
/*  f104890:	14cbffe0 */ 	bne	$a2,$t3,.L0f104814
/*  f104894:	254a0006 */ 	addiu	$t2,$t2,0x6
.L0f104898:
/*  f104898:	0fc41199 */ 	jal	getNumUnlockedSpecialStages
/*  f10489c:	00000000 */ 	nop
/*  f1048a0:	8e0e0000 */ 	lw	$t6,0x0($s0)
/*  f1048a4:	01c2c021 */ 	addu	$t8,$t6,$v0
/*  f1048a8:	10000336 */ 	b	.L0f105584
/*  f1048ac:	ae180000 */ 	sw	$t8,0x0($s0)
/*  f1048b0:	8e050004 */ 	lw	$a1,0x4($s0)
/*  f1048b4:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f1048b8:	27a6018c */ 	addiu	$a2,$sp,0x18c
/*  f1048bc:	54a00009 */ 	bnezl	$a1,.L0f1048e4
/*  f1048c0:	8e030000 */ 	lw	$v1,0x0($s0)
/*  f1048c4:	0fc411db */ 	jal	menuhandler0010476c
/*  f1048c8:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f1048cc:	0fc41199 */ 	jal	getNumUnlockedSpecialStages
/*  f1048d0:	00000000 */ 	nop
/*  f1048d4:	8fb9018c */ 	lw	$t9,0x18c($sp)
/*  f1048d8:	03222823 */ 	subu	$a1,$t9,$v0
/*  f1048dc:	ae050004 */ 	sw	$a1,0x4($s0)
/*  f1048e0:	8e030000 */ 	lw	$v1,0x0($s0)
.L0f1048e4:
/*  f1048e4:	3c048007 */ 	lui	$a0,%hi(g_StageNames+0x6)
/*  f1048e8:	0065082b */ 	sltu	$at,$v1,$a1
/*  f1048ec:	10200008 */ 	beqz	$at,.L0f104910
/*  f1048f0:	00037080 */ 	sll	$t6,$v1,0x2
/*  f1048f4:	01c37023 */ 	subu	$t6,$t6,$v1
/*  f1048f8:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f1048fc:	008e2021 */ 	addu	$a0,$a0,$t6
/*  f104900:	0fc5b9f1 */ 	jal	langGet
/*  f104904:	94841e72 */ 	lhu	$a0,%lo(g_StageNames+0x6)($a0)
/*  f104908:	10000320 */ 	b	.L0f10558c
/*  f10490c:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f104910:
/*  f104910:	0fc411c8 */ 	jal	func0f104720
/*  f104914:	00652023 */ 	subu	$a0,$v1,$a1
/*  f104918:	0002c080 */ 	sll	$t8,$v0,0x2
/*  f10491c:	0302c023 */ 	subu	$t8,$t8,$v0
/*  f104920:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f104924:	3c048007 */ 	lui	$a0,%hi(g_StageNames+0x6)
/*  f104928:	00982021 */ 	addu	$a0,$a0,$t8
/*  f10492c:	0fc5b9f1 */ 	jal	langGet
/*  f104930:	94841e72 */ 	lhu	$a0,%lo(g_StageNames+0x6)($a0)
/*  f104934:	10000315 */ 	b	.L0f10558c
/*  f104938:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f10493c:	8e070000 */ 	lw	$a3,0x0($s0)
/*  f104940:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f104944:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f104948:	27a60178 */ 	addiu	$a2,$sp,0x178
/*  f10494c:	0fc411db */ 	jal	menuhandler0010476c
/*  f104950:	afa70188 */ 	sw	$a3,0x188($sp)
/*  f104954:	0fc41199 */ 	jal	getNumUnlockedSpecialStages
/*  f104958:	00000000 */ 	nop
/*  f10495c:	8fb90178 */ 	lw	$t9,0x178($sp)
/*  f104960:	8fa70188 */ 	lw	$a3,0x188($sp)
/*  f104964:	03227823 */ 	subu	$t7,$t9,$v0
/*  f104968:	afaf0178 */ 	sw	$t7,0x178($sp)
/*  f10496c:	8e030000 */ 	lw	$v1,0x0($s0)
/*  f104970:	006f082b */ 	sltu	$at,$v1,$t7
/*  f104974:	14200004 */ 	bnez	$at,.L0f104988
/*  f104978:	00000000 */ 	nop
/*  f10497c:	0fc411c8 */ 	jal	func0f104720
/*  f104980:	006f2023 */ 	subu	$a0,$v1,$t7
/*  f104984:	00403825 */ 	or	$a3,$v0,$zero
.L0f104988:
/*  f104988:	3c02800a */ 	lui	$v0,%hi(g_Vars)
/*  f10498c:	00077080 */ 	sll	$t6,$a3,0x2
/*  f104990:	24429fc0 */ 	addiu	$v0,$v0,%lo(g_Vars)
/*  f104994:	3c08800a */ 	lui	$t0,%hi(g_MissionConfig)
/*  f104998:	01c77023 */ 	subu	$t6,$t6,$a3
/*  f10499c:	2508dfe8 */ 	addiu	$t0,$t0,%lo(g_MissionConfig)
/*  f1049a0:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f1049a4:	3c188007 */ 	lui	$t8,%hi(g_StageNames)
/*  f1049a8:	810f0003 */ 	lb	$t7,0x3($t0)
/*  f1049ac:	ac400314 */ 	sw	$zero,0x314($v0)
/*  f1049b0:	ac400318 */ 	sw	$zero,0x318($v0)
/*  f1049b4:	030ec021 */ 	addu	$t8,$t8,$t6
/*  f1049b8:	8f181e6c */ 	lw	$t8,%lo(g_StageNames)($t8)
/*  f1049bc:	a1070002 */ 	sb	$a3,0x2($t0)
/*  f1049c0:	05e10006 */ 	bgez	$t7,.L0f1049dc
/*  f1049c4:	a1180001 */ 	sb	$t8,0x1($t0)
/*  f1049c8:	3c048007 */ 	lui	$a0,%hi(g_CoopMissionDifficultyMenuDialog)
/*  f1049cc:	0fc3cbd3 */ 	jal	menuPushDialog
/*  f1049d0:	24841dc4 */ 	addiu	$a0,$a0,%lo(g_CoopMissionDifficultyMenuDialog)
/*  f1049d4:	100002ec */ 	b	.L0f105588
/*  f1049d8:	00001025 */ 	or	$v0,$zero,$zero
.L0f1049dc:
/*  f1049dc:	8d0e0000 */ 	lw	$t6,0x0($t0)
/*  f1049e0:	3c048007 */ 	lui	$a0,%hi(g_SoloMissionDifficultyMenuDialog)
/*  f1049e4:	000ece40 */ 	sll	$t9,$t6,0x19
/*  f1049e8:	07210006 */ 	bgez	$t9,.L0f104a04
/*  f1049ec:	00000000 */ 	nop
/*  f1049f0:	3c048007 */ 	lui	$a0,%hi(g_AntiMissionDifficultyMenuDialog)
/*  f1049f4:	0fc3cbd3 */ 	jal	menuPushDialog
/*  f1049f8:	24841e54 */ 	addiu	$a0,$a0,%lo(g_AntiMissionDifficultyMenuDialog)
/*  f1049fc:	100002e2 */ 	b	.L0f105588
/*  f104a00:	00001025 */ 	or	$v0,$zero,$zero
.L0f104a04:
/*  f104a04:	0fc3cbd3 */ 	jal	menuPushDialog
/*  f104a08:	24841c00 */ 	addiu	$a0,$a0,%lo(g_SoloMissionDifficultyMenuDialog)
/*  f104a0c:	100002de */ 	b	.L0f105588
/*  f104a10:	00001025 */ 	or	$v0,$zero,$zero
/*  f104a14:	3c0f000f */ 	lui	$t7,0xf
/*  f104a18:	35efffff */ 	ori	$t7,$t7,0xffff
/*  f104a1c:	100002d9 */ 	b	.L0f105584
/*  f104a20:	ae0f0000 */ 	sw	$t7,0x0($s0)
/*  f104a24:	8e0e0004 */ 	lw	$t6,0x4($s0)
/*  f104a28:	3c08800a */ 	lui	$t0,%hi(g_MissionConfig)
/*  f104a2c:	2508dfe8 */ 	addiu	$t0,$t0,%lo(g_MissionConfig)
/*  f104a30:	55c002d5 */ 	bnezl	$t6,.L0f105588
/*  f104a34:	00001025 */ 	or	$v0,$zero,$zero
/*  f104a38:	81190003 */ 	lb	$t9,0x3($t0)
/*  f104a3c:	072202d2 */ 	bltzl	$t9,.L0f105588
/*  f104a40:	00001025 */ 	or	$v0,$zero,$zero
/*  f104a44:	8d0f0000 */ 	lw	$t7,0x0($t0)
/*  f104a48:	3c09800a */ 	lui	$t1,%hi(g_SoloSaveFile)
/*  f104a4c:	25292200 */ 	addiu	$t1,$t1,%lo(g_SoloSaveFile)
/*  f104a50:	000fc640 */ 	sll	$t8,$t7,0x19
/*  f104a54:	070202cc */ 	bltzl	$t8,.L0f105588
/*  f104a58:	00001025 */ 	or	$v0,$zero,$zero
/*  f104a5c:	9139000c */ 	lbu	$t9,0xc($t1)
/*  f104a60:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f104a64:	27a60168 */ 	addiu	$a2,$sp,0x168
/*  f104a68:	ae190000 */ 	sw	$t9,0x0($s0)
/*  f104a6c:	0fc411db */ 	jal	menuhandler0010476c
/*  f104a70:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f104a74:	0fc41199 */ 	jal	getNumUnlockedSpecialStages
/*  f104a78:	00000000 */ 	nop
/*  f104a7c:	8faf0168 */ 	lw	$t7,0x168($sp)
/*  f104a80:	01e27023 */ 	subu	$t6,$t7,$v0
/*  f104a84:	afae0168 */ 	sw	$t6,0x168($sp)
/*  f104a88:	8e180000 */ 	lw	$t8,0x0($s0)
/*  f104a8c:	030e082b */ 	sltu	$at,$t8,$t6
/*  f104a90:	542002bd */ 	bnezl	$at,.L0f105588
/*  f104a94:	00001025 */ 	or	$v0,$zero,$zero
/*  f104a98:	0fc41199 */ 	jal	getNumUnlockedSpecialStages
/*  f104a9c:	00000000 */ 	nop
/*  f104aa0:	8fb90168 */ 	lw	$t9,0x168($sp)
/*  f104aa4:	00401825 */ 	or	$v1,$v0,$zero
/*  f104aa8:	00002025 */ 	or	$a0,$zero,$zero
/*  f104aac:	272fffff */ 	addiu	$t7,$t9,-1
/*  f104ab0:	184002b4 */ 	blez	$v0,.L0f105584
/*  f104ab4:	ae0f0000 */ 	sw	$t7,0x0($s0)
/*  f104ab8:	afa30164 */ 	sw	$v1,0x164($sp)
.L0f104abc:
/*  f104abc:	0fc411c8 */ 	jal	func0f104720
/*  f104ac0:	afa40160 */ 	sw	$a0,0x160($sp)
/*  f104ac4:	3c09800a */ 	lui	$t1,%hi(g_SoloSaveFile)
/*  f104ac8:	25292200 */ 	addiu	$t1,$t1,%lo(g_SoloSaveFile)
/*  f104acc:	9138000c */ 	lbu	$t8,0xc($t1)
/*  f104ad0:	8fa30164 */ 	lw	$v1,0x164($sp)
/*  f104ad4:	8fa40160 */ 	lw	$a0,0x160($sp)
/*  f104ad8:	14580003 */ 	bne	$v0,$t8,.L0f104ae8
/*  f104adc:	8fae0168 */ 	lw	$t6,0x168($sp)
/*  f104ae0:	01c4c821 */ 	addu	$t9,$t6,$a0
/*  f104ae4:	ae190000 */ 	sw	$t9,0x0($s0)
.L0f104ae8:
/*  f104ae8:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f104aec:	0083082a */ 	slt	$at,$a0,$v1
/*  f104af0:	5420fff2 */ 	bnezl	$at,.L0f104abc
/*  f104af4:	afa30164 */ 	sw	$v1,0x164($sp)
/*  f104af8:	100002a3 */ 	b	.L0f105588
/*  f104afc:	00001025 */ 	or	$v0,$zero,$zero
/*  f104b00:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f104b04:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f104b08:	0fc411db */ 	jal	menuhandler0010476c
/*  f104b0c:	27a60150 */ 	addiu	$a2,$sp,0x150
/*  f104b10:	0fc41199 */ 	jal	getNumUnlockedSpecialStages
/*  f104b14:	00000000 */ 	nop
/*  f104b18:	8faf0150 */ 	lw	$t7,0x150($sp)
/*  f104b1c:	27a301a8 */ 	addiu	$v1,$sp,0x1a8
/*  f104b20:	01e2c023 */ 	subu	$t8,$t7,$v0
/*  f104b24:	afb80150 */ 	sw	$t8,0x150($sp)
/*  f104b28:	ae00000c */ 	sw	$zero,0xc($s0)
/*  f104b2c:	27a201f8 */ 	addiu	$v0,$sp,0x1f8
/*  f104b30:	8c6e0000 */ 	lw	$t6,0x0($v1)
.L0f104b34:
/*  f104b34:	8fb90150 */ 	lw	$t9,0x150($sp)
/*  f104b38:	24630008 */ 	addiu	$v1,$v1,0x8
/*  f104b3c:	01d9082b */ 	sltu	$at,$t6,$t9
/*  f104b40:	10200004 */ 	beqz	$at,.L0f104b54
/*  f104b44:	00000000 */ 	nop
/*  f104b48:	8e0f000c */ 	lw	$t7,0xc($s0)
/*  f104b4c:	25f80001 */ 	addiu	$t8,$t7,0x1
/*  f104b50:	ae18000c */ 	sw	$t8,0xc($s0)
.L0f104b54:
/*  f104b54:	5462fff7 */ 	bnel	$v1,$v0,.L0f104b34
/*  f104b58:	8c6e0000 */ 	lw	$t6,0x0($v1)
/*  f104b5c:	8e0e000c */ 	lw	$t6,0xc($s0)
/*  f104b60:	25d90001 */ 	addiu	$t9,$t6,0x1
/*  f104b64:	10000287 */ 	b	.L0f105584
/*  f104b68:	ae190000 */ 	sw	$t9,0x0($s0)
/*  f104b6c:	8e030000 */ 	lw	$v1,0x0($s0)
/*  f104b70:	8e0f000c */ 	lw	$t7,0xc($s0)
/*  f104b74:	0003c0c0 */ 	sll	$t8,$v1,0x3
/*  f104b78:	146f0005 */ 	bne	$v1,$t7,.L0f104b90
/*  f104b7c:	00587021 */ 	addu	$t6,$v0,$t8
/*  f104b80:	0fc5b9f1 */ 	jal	langGet
/*  f104b84:	97a401f4 */ 	lhu	$a0,0x1f4($sp)
/*  f104b88:	10000280 */ 	b	.L0f10558c
/*  f104b8c:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f104b90:
/*  f104b90:	0fc5b9f1 */ 	jal	langGet
/*  f104b94:	95c40004 */ 	lhu	$a0,0x4($t6)
/*  f104b98:	1000027c */ 	b	.L0f10558c
/*  f104b9c:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f104ba0:	8e030000 */ 	lw	$v1,0x0($s0)
/*  f104ba4:	8e19000c */ 	lw	$t9,0xc($s0)
/*  f104ba8:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f104bac:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f104bb0:	14790009 */ 	bne	$v1,$t9,.L0f104bd8
/*  f104bb4:	000370c0 */ 	sll	$t6,$v1,0x3
/*  f104bb8:	0fc411db */ 	jal	menuhandler0010476c
/*  f104bbc:	27a6013c */ 	addiu	$a2,$sp,0x13c
/*  f104bc0:	0fc41199 */ 	jal	getNumUnlockedSpecialStages
/*  f104bc4:	00000000 */ 	nop
/*  f104bc8:	8faf013c */ 	lw	$t7,0x13c($sp)
/*  f104bcc:	01e2c023 */ 	subu	$t8,$t7,$v0
/*  f104bd0:	1000026c */ 	b	.L0f105584
/*  f104bd4:	ae180008 */ 	sw	$t8,0x8($s0)
.L0f104bd8:
/*  f104bd8:	004ec821 */ 	addu	$t9,$v0,$t6
/*  f104bdc:	8f2f0000 */ 	lw	$t7,0x0($t9)
/*  f104be0:	10000268 */ 	b	.L0f105584
/*  f104be4:	ae0f0008 */ 	sw	$t7,0x8($s0)
/*  f104be8:	8e180000 */ 	lw	$t8,0x0($s0)
/*  f104bec:	afb80138 */ 	sw	$t8,0x138($sp)
/*  f104bf0:	8e0a0008 */ 	lw	$t2,0x8($s0)
/*  f104bf4:	afa00124 */ 	sw	$zero,0x124($sp)
/*  f104bf8:	8e050004 */ 	lw	$a1,0x4($s0)
/*  f104bfc:	afa500ec */ 	sw	$a1,0xec($sp)
/*  f104c00:	8e03000c */ 	lw	$v1,0xc($s0)
/*  f104c04:	1460000c */ 	bnez	$v1,.L0f104c38
/*  f104c08:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f104c0c:	8fa501fc */ 	lw	$a1,0x1fc($sp)
/*  f104c10:	27a600dc */ 	addiu	$a2,$sp,0xdc
/*  f104c14:	0fc411db */ 	jal	menuhandler0010476c
/*  f104c18:	afaa0134 */ 	sw	$t2,0x134($sp)
/*  f104c1c:	0fc41199 */ 	jal	getNumUnlockedSpecialStages
/*  f104c20:	00000000 */ 	nop
/*  f104c24:	8fae00dc */ 	lw	$t6,0xdc($sp)
/*  f104c28:	8faa0134 */ 	lw	$t2,0x134($sp)
/*  f104c2c:	8e050004 */ 	lw	$a1,0x4($s0)
/*  f104c30:	01c21823 */ 	subu	$v1,$t6,$v0
/*  f104c34:	ae03000c */ 	sw	$v1,0xc($s0)
.L0f104c38:
/*  f104c38:	00a3082b */ 	sltu	$at,$a1,$v1
/*  f104c3c:	14200005 */ 	bnez	$at,.L0f104c54
/*  f104c40:	00a32023 */ 	subu	$a0,$a1,$v1
/*  f104c44:	0fc411c8 */ 	jal	func0f104720
/*  f104c48:	afaa0134 */ 	sw	$t2,0x134($sp)
/*  f104c4c:	8faa0134 */ 	lw	$t2,0x134($sp)
/*  f104c50:	afa200ec */ 	sw	$v0,0xec($sp)
.L0f104c54:
/*  f104c54:	8faf0138 */ 	lw	$t7,0x138($sp)
/*  f104c58:	3c0ee700 */ 	lui	$t6,0xe700
/*  f104c5c:	27b00138 */ 	addiu	$s0,$sp,0x138
/*  f104c60:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f104c64:	afb80138 */ 	sw	$t8,0x138($sp)
/*  f104c68:	ade00004 */ 	sw	$zero,0x4($t7)
/*  f104c6c:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f104c70:	8fb90138 */ 	lw	$t9,0x138($sp)
/*  f104c74:	3c18ba00 */ 	lui	$t8,0xba00
/*  f104c78:	37181301 */ 	ori	$t8,$t8,0x1301
/*  f104c7c:	272f0008 */ 	addiu	$t7,$t9,0x8
/*  f104c80:	afaf0138 */ 	sw	$t7,0x138($sp)
/*  f104c84:	af200004 */ 	sw	$zero,0x4($t9)
/*  f104c88:	af380000 */ 	sw	$t8,0x0($t9)
/*  f104c8c:	8fae0138 */ 	lw	$t6,0x138($sp)
/*  f104c90:	3c0fb900 */ 	lui	$t7,0xb900
/*  f104c94:	35ef0002 */ 	ori	$t7,$t7,0x2
/*  f104c98:	25d90008 */ 	addiu	$t9,$t6,0x8
/*  f104c9c:	afb90138 */ 	sw	$t9,0x138($sp)
/*  f104ca0:	adc00004 */ 	sw	$zero,0x4($t6)
/*  f104ca4:	adcf0000 */ 	sw	$t7,0x0($t6)
/*  f104ca8:	8fb80138 */ 	lw	$t8,0x138($sp)
/*  f104cac:	3c19ba00 */ 	lui	$t9,0xba00
/*  f104cb0:	37391001 */ 	ori	$t9,$t9,0x1001
/*  f104cb4:	270e0008 */ 	addiu	$t6,$t8,0x8
/*  f104cb8:	afae0138 */ 	sw	$t6,0x138($sp)
/*  f104cbc:	af000004 */ 	sw	$zero,0x4($t8)
/*  f104cc0:	af190000 */ 	sw	$t9,0x0($t8)
/*  f104cc4:	8faf0138 */ 	lw	$t7,0x138($sp)
/*  f104cc8:	3c0eba00 */ 	lui	$t6,0xba00
/*  f104ccc:	35ce0903 */ 	ori	$t6,$t6,0x903
/*  f104cd0:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f104cd4:	afb80138 */ 	sw	$t8,0x138($sp)
/*  f104cd8:	24190c00 */ 	addiu	$t9,$zero,0xc00
/*  f104cdc:	adf90004 */ 	sw	$t9,0x4($t7)
/*  f104ce0:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f104ce4:	8fa200ec */ 	lw	$v0,0xec($sp)
/*  f104ce8:	3c18800b */ 	lui	$t8,%hi(var800ab5a8)
/*  f104cec:	8f18b5a8 */ 	lw	$t8,%lo(var800ab5a8)($t8)
/*  f104cf0:	00027880 */ 	sll	$t7,$v0,0x2
/*  f104cf4:	01e27823 */ 	subu	$t7,$t7,$v0
/*  f104cf8:	000f1080 */ 	sll	$v0,$t7,0x2
/*  f104cfc:	240e0002 */ 	addiu	$t6,$zero,0x2
/*  f104d00:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f104d04:	03022821 */ 	addu	$a1,$t8,$v0
/*  f104d08:	24a5009c */ 	addiu	$a1,$a1,0x9c
/*  f104d0c:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f104d10:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f104d14:	afa20050 */ 	sw	$v0,0x50($sp)
/*  f104d18:	afaa0134 */ 	sw	$t2,0x134($sp)
/*  f104d1c:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f104d20:	02002025 */ 	or	$a0,$s0,$zero
/*  f104d24:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f104d28:	0fc2ce70 */ 	jal	func0f0b39c0
/*  f104d2c:	00003825 */ 	or	$a3,$zero,$zero
/*  f104d30:	8faf0138 */ 	lw	$t7,0x138($sp)
/*  f104d34:	8faa0134 */ 	lw	$t2,0x134($sp)
/*  f104d38:	3c0eba00 */ 	lui	$t6,0xba00
/*  f104d3c:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f104d40:	afb80138 */ 	sw	$t8,0x138($sp)
/*  f104d44:	35ce1402 */ 	ori	$t6,$t6,0x1402
/*  f104d48:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f104d4c:	ade00004 */ 	sw	$zero,0x4($t7)
/*  f104d50:	8fb90138 */ 	lw	$t9,0x138($sp)
/*  f104d54:	3c0eff37 */ 	lui	$t6,0xff37
/*  f104d58:	3c18fc12 */ 	lui	$t8,0xfc12
/*  f104d5c:	272f0008 */ 	addiu	$t7,$t9,0x8
/*  f104d60:	afaf0138 */ 	sw	$t7,0x138($sp)
/*  f104d64:	37189a25 */ 	ori	$t8,$t8,0x9a25
/*  f104d68:	35ceffff */ 	ori	$t6,$t6,0xffff
/*  f104d6c:	af2e0004 */ 	sw	$t6,0x4($t9)
/*  f104d70:	af380000 */ 	sw	$t8,0x0($t9)
/*  f104d74:	8fb90138 */ 	lw	$t9,0x138($sp)
/*  f104d78:	3c18ba00 */ 	lui	$t8,0xba00
/*  f104d7c:	37180c02 */ 	ori	$t8,$t8,0xc02
/*  f104d80:	272f0008 */ 	addiu	$t7,$t9,0x8
/*  f104d84:	afaf0138 */ 	sw	$t7,0x138($sp)
/*  f104d88:	af200004 */ 	sw	$zero,0x4($t9)
/*  f104d8c:	af380000 */ 	sw	$t8,0x0($t9)
/*  f104d90:	8fae0138 */ 	lw	$t6,0x138($sp)
/*  f104d94:	03202025 */ 	or	$a0,$t9,$zero
/*  f104d98:	3c0dfb00 */ 	lui	$t5,0xfb00
/*  f104d9c:	25d90008 */ 	addiu	$t9,$t6,0x8
/*  f104da0:	afb90138 */ 	sw	$t9,0x138($sp)
/*  f104da4:	adcd0000 */ 	sw	$t5,0x0($t6)
/*  f104da8:	8d4f000c */ 	lw	$t7,0xc($t2)
/*  f104dac:	01c02825 */ 	or	$a1,$t6,$zero
/*  f104db0:	241fff00 */ 	addiu	$ra,$zero,-256
/*  f104db4:	31f800ff */ 	andi	$t8,$t7,0xff
/*  f104db8:	00187200 */ 	sll	$t6,$t8,0x8
/*  f104dbc:	01d87023 */ 	subu	$t6,$t6,$t8
/*  f104dc0:	000eca02 */ 	srl	$t9,$t6,0x8
/*  f104dc4:	033f7825 */ 	or	$t7,$t9,$ra
/*  f104dc8:	acaf0004 */ 	sw	$t7,0x4($a1)
/*  f104dcc:	8fb80138 */ 	lw	$t8,0x138($sp)
/*  f104dd0:	3c098008 */ 	lui	$t1,%hi(g_ScaleX)
/*  f104dd4:	2529fac0 */ 	addiu	$t1,$t1,%lo(g_ScaleX)
/*  f104dd8:	270e0008 */ 	addiu	$t6,$t8,0x8
/*  f104ddc:	afae0138 */ 	sw	$t6,0x138($sp)
/*  f104de0:	8d590000 */ 	lw	$t9,0x0($t2)
/*  f104de4:	8d2e0000 */ 	lw	$t6,0x0($t1)
/*  f104de8:	03003025 */ 	or	$a2,$t8,$zero
/*  f104dec:	272f003c */ 	addiu	$t7,$t9,0x3c
/*  f104df0:	000fc080 */ 	sll	$t8,$t7,0x2
/*  f104df4:	030e0019 */ 	multu	$t8,$t6
/*  f104df8:	3c01e400 */ 	lui	$at,0xe400
/*  f104dfc:	3c08800a */ 	lui	$t0,%hi(g_MissionConfig)
/*  f104e00:	2508dfe8 */ 	addiu	$t0,$t0,%lo(g_MissionConfig)
/*  f104e04:	3c0b800b */ 	lui	$t3,%hi(var800ab5a8)
/*  f104e08:	256bb5a8 */ 	addiu	$t3,$t3,%lo(var800ab5a8)
/*  f104e0c:	0000c812 */ 	mflo	$t9
/*  f104e10:	332f0fff */ 	andi	$t7,$t9,0xfff
/*  f104e14:	8d590004 */ 	lw	$t9,0x4($t2)
/*  f104e18:	000fc300 */ 	sll	$t8,$t7,0xc
/*  f104e1c:	03017025 */ 	or	$t6,$t8,$at
/*  f104e20:	272f0027 */ 	addiu	$t7,$t9,0x27
/*  f104e24:	000fc080 */ 	sll	$t8,$t7,0x2
/*  f104e28:	33190fff */ 	andi	$t9,$t8,0xfff
/*  f104e2c:	01d97825 */ 	or	$t7,$t6,$t9
/*  f104e30:	accf0000 */ 	sw	$t7,0x0($a2)
/*  f104e34:	8d580000 */ 	lw	$t8,0x0($t2)
/*  f104e38:	8d2f0000 */ 	lw	$t7,0x0($t1)
/*  f104e3c:	270e0004 */ 	addiu	$t6,$t8,0x4
/*  f104e40:	000ec880 */ 	sll	$t9,$t6,0x2
/*  f104e44:	032f0019 */ 	multu	$t9,$t7
/*  f104e48:	8d4f0004 */ 	lw	$t7,0x4($t2)
/*  f104e4c:	0000c012 */ 	mflo	$t8
/*  f104e50:	330e0fff */ 	andi	$t6,$t8,0xfff
/*  f104e54:	000ecb00 */ 	sll	$t9,$t6,0xc
/*  f104e58:	25f80003 */ 	addiu	$t8,$t7,0x3
/*  f104e5c:	00187080 */ 	sll	$t6,$t8,0x2
/*  f104e60:	31cf0fff */ 	andi	$t7,$t6,0xfff
/*  f104e64:	032fc025 */ 	or	$t8,$t9,$t7
/*  f104e68:	acd80004 */ 	sw	$t8,0x4($a2)
/*  f104e6c:	8fae0138 */ 	lw	$t6,0x138($sp)
/*  f104e70:	24180480 */ 	addiu	$t8,$zero,0x480
/*  f104e74:	3c0fb400 */ 	lui	$t7,0xb400
/*  f104e78:	25d90008 */ 	addiu	$t9,$t6,0x8
/*  f104e7c:	afb90138 */ 	sw	$t9,0x138($sp)
/*  f104e80:	adcf0000 */ 	sw	$t7,0x0($t6)
/*  f104e84:	add80004 */ 	sw	$t8,0x4($t6)
/*  f104e88:	01c01025 */ 	or	$v0,$t6,$zero
/*  f104e8c:	8fae0138 */ 	lw	$t6,0x138($sp)
/*  f104e90:	3c0fb300 */ 	lui	$t7,0xb300
/*  f104e94:	25d90008 */ 	addiu	$t9,$t6,0x8
/*  f104e98:	afb90138 */ 	sw	$t9,0x138($sp)
/*  f104e9c:	adcf0000 */ 	sw	$t7,0x0($t6)
/*  f104ea0:	01c01825 */ 	or	$v1,$t6,$zero
/*  f104ea4:	240e0400 */ 	addiu	$t6,$zero,0x400
/*  f104ea8:	8d380000 */ 	lw	$t8,0x0($t1)
/*  f104eac:	01d8001a */ 	div	$zero,$t6,$t8
/*  f104eb0:	00007812 */ 	mflo	$t7
/*  f104eb4:	17000002 */ 	bnez	$t8,.L0f104ec0
/*  f104eb8:	00000000 */ 	nop
/*  f104ebc:	0007000d */ 	break	0x7
.L0f104ec0:
/*  f104ec0:	2401ffff */ 	addiu	$at,$zero,-1
/*  f104ec4:	17010004 */ 	bne	$t8,$at,.L0f104ed8
/*  f104ec8:	3c018000 */ 	lui	$at,0x8000
/*  f104ecc:	15c10002 */ 	bne	$t6,$at,.L0f104ed8
/*  f104ed0:	00000000 */ 	nop
/*  f104ed4:	0006000d */ 	break	0x6
.L0f104ed8:
/*  f104ed8:	000f7400 */ 	sll	$t6,$t7,0x10
/*  f104edc:	35d8fc00 */ 	ori	$t8,$t6,0xfc00
/*  f104ee0:	ac780004 */ 	sw	$t8,0x4($v1)
/*  f104ee4:	8d190000 */ 	lw	$t9,0x0($t0)
/*  f104ee8:	00197e40 */ 	sll	$t7,$t9,0x19
/*  f104eec:	000f77c2 */ 	srl	$t6,$t7,0x1f
/*  f104ef0:	55c0014f */ 	bnezl	$t6,.L0f105430
/*  f104ef4:	8d590000 */ 	lw	$t9,0x0($t2)
/*  f104ef8:	81190003 */ 	lb	$t9,0x3($t0)
/*  f104efc:	02002025 */ 	or	$a0,$s0,$zero
/*  f104f00:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f104f04:	072100a2 */ 	bgez	$t9,.L0f105190
/*  f104f08:	00003825 */ 	or	$a3,$zero,$zero
/*  f104f0c:	8d650000 */ 	lw	$a1,0x0($t3)
/*  f104f10:	240f0002 */ 	addiu	$t7,$zero,0x2
/*  f104f14:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f104f18:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f104f1c:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f104f20:	02002025 */ 	or	$a0,$s0,$zero
/*  f104f24:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f104f28:	00003825 */ 	or	$a3,$zero,$zero
/*  f104f2c:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f104f30:	afaa0134 */ 	sw	$t2,0x134($sp)
/*  f104f34:	0fc2ce70 */ 	jal	func0f0b39c0
/*  f104f38:	24a501b0 */ 	addiu	$a1,$a1,0x1b0
/*  f104f3c:	8fb80138 */ 	lw	$t8,0x138($sp)
/*  f104f40:	8faa0134 */ 	lw	$t2,0x134($sp)
/*  f104f44:	3c0fba00 */ 	lui	$t7,0xba00
/*  f104f48:	27190008 */ 	addiu	$t9,$t8,0x8
/*  f104f4c:	afb90138 */ 	sw	$t9,0x138($sp)
/*  f104f50:	35ef1402 */ 	ori	$t7,$t7,0x1402
/*  f104f54:	af0f0000 */ 	sw	$t7,0x0($t8)
/*  f104f58:	af000004 */ 	sw	$zero,0x4($t8)
/*  f104f5c:	8fae0138 */ 	lw	$t6,0x138($sp)
/*  f104f60:	3c19ba00 */ 	lui	$t9,0xba00
/*  f104f64:	37390c02 */ 	ori	$t9,$t9,0xc02
/*  f104f68:	25d80008 */ 	addiu	$t8,$t6,0x8
/*  f104f6c:	afb80138 */ 	sw	$t8,0x138($sp)
/*  f104f70:	adc00004 */ 	sw	$zero,0x4($t6)
/*  f104f74:	add90000 */ 	sw	$t9,0x0($t6)
/*  f104f78:	8faf00ec */ 	lw	$t7,0xec($sp)
/*  f104f7c:	3c098008 */ 	lui	$t1,%hi(g_ScaleX)
/*  f104f80:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f104f84:	3c06800a */ 	lui	$a2,%hi(g_SoloSaveFile)
/*  f104f88:	3c10800a */ 	lui	$s0,%hi(g_SoloSaveFile+0xc)
/*  f104f8c:	3c0b0010 */ 	lui	$t3,0x10
/*  f104f90:	2529fac0 */ 	addiu	$t1,$t1,%lo(g_ScaleX)
/*  f104f94:	3c0dfb00 */ 	lui	$t5,0xfb00
/*  f104f98:	241fff00 */ 	addiu	$ra,$zero,-256
/*  f104f9c:	356b01c0 */ 	ori	$t3,$t3,0x1c0
/*  f104fa0:	2610220c */ 	addiu	$s0,$s0,%lo(g_SoloSaveFile+0xc)
/*  f104fa4:	24c62200 */ 	addiu	$a2,$a2,%lo(g_SoloSaveFile)
/*  f104fa8:	2405003f */ 	addiu	$a1,$zero,0x3f
/*  f104fac:	2408003f */ 	addiu	$t0,$zero,0x3f
/*  f104fb0:	01ee6004 */ 	sllv	$t4,$t6,$t7
.L0f104fb4:
/*  f104fb4:	8cd800a0 */ 	lw	$t8,0xa0($a2)
/*  f104fb8:	8fa20138 */ 	lw	$v0,0x138($sp)
/*  f104fbc:	00a03825 */ 	or	$a3,$a1,$zero
/*  f104fc0:	030cc824 */ 	and	$t9,$t8,$t4
/*  f104fc4:	17200016 */ 	bnez	$t9,.L0f105020
/*  f104fc8:	244e0008 */ 	addiu	$t6,$v0,0x8
/*  f104fcc:	8fa20138 */ 	lw	$v0,0x138($sp)
/*  f104fd0:	244f0008 */ 	addiu	$t7,$v0,0x8
/*  f104fd4:	afaf0138 */ 	sw	$t7,0x138($sp)
/*  f104fd8:	ac4d0000 */ 	sw	$t5,0x0($v0)
/*  f104fdc:	8d58000c */ 	lw	$t8,0xc($t2)
/*  f104fe0:	331900ff */ 	andi	$t9,$t8,0xff
/*  f104fe4:	03280019 */ 	multu	$t9,$t0
/*  f104fe8:	00007012 */ 	mflo	$t6
/*  f104fec:	000e7a02 */ 	srl	$t7,$t6,0x8
/*  f104ff0:	01ffc025 */ 	or	$t8,$t7,$ra
/*  f104ff4:	ac580004 */ 	sw	$t8,0x4($v0)
/*  f104ff8:	8fb90138 */ 	lw	$t9,0x138($sp)
/*  f104ffc:	3c18ff37 */ 	lui	$t8,0xff37
/*  f105000:	3c0ffc12 */ 	lui	$t7,0xfc12
/*  f105004:	272e0008 */ 	addiu	$t6,$t9,0x8
/*  f105008:	afae0138 */ 	sw	$t6,0x138($sp)
/*  f10500c:	35ef9a25 */ 	ori	$t7,$t7,0x9a25
/*  f105010:	3718ffff */ 	ori	$t8,$t8,0xffff
/*  f105014:	af380004 */ 	sw	$t8,0x4($t9)
/*  f105018:	10000017 */ 	b	.L0f105078
/*  f10501c:	af2f0000 */ 	sw	$t7,0x0($t9)
.L0f105020:
/*  f105020:	afae0138 */ 	sw	$t6,0x138($sp)
/*  f105024:	ac4d0000 */ 	sw	$t5,0x0($v0)
/*  f105028:	8d4f000c */ 	lw	$t7,0xc($t2)
/*  f10502c:	31f800ff */ 	andi	$t8,$t7,0xff
/*  f105030:	0018c880 */ 	sll	$t9,$t8,0x2
/*  f105034:	0338c823 */ 	subu	$t9,$t9,$t8
/*  f105038:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f10503c:	0338c821 */ 	addu	$t9,$t9,$t8
/*  f105040:	0019c900 */ 	sll	$t9,$t9,0x4
/*  f105044:	0338c823 */ 	subu	$t9,$t9,$t8
/*  f105048:	00197202 */ 	srl	$t6,$t9,0x8
/*  f10504c:	01df7825 */ 	or	$t7,$t6,$ra
/*  f105050:	ac4f0004 */ 	sw	$t7,0x4($v0)
/*  f105054:	8fb80138 */ 	lw	$t8,0x138($sp)
/*  f105058:	3c0ffffc */ 	lui	$t7,0xfffc
/*  f10505c:	3c0efcff */ 	lui	$t6,0xfcff
/*  f105060:	27190008 */ 	addiu	$t9,$t8,0x8
/*  f105064:	afb90138 */ 	sw	$t9,0x138($sp)
/*  f105068:	35ceffff */ 	ori	$t6,$t6,0xffff
/*  f10506c:	35eff279 */ 	ori	$t7,$t7,0xf279
/*  f105070:	af0f0004 */ 	sw	$t7,0x4($t8)
/*  f105074:	af0e0000 */ 	sw	$t6,0x0($t8)
.L0f105078:
/*  f105078:	8fb80138 */ 	lw	$t8,0x138($sp)
/*  f10507c:	3c01e400 */ 	lui	$at,0xe400
/*  f105080:	24c60004 */ 	addiu	$a2,$a2,0x4
/*  f105084:	27190008 */ 	addiu	$t9,$t8,0x8
/*  f105088:	afb90138 */ 	sw	$t9,0x138($sp)
/*  f10508c:	8d4e0000 */ 	lw	$t6,0x0($t2)
/*  f105090:	03001025 */ 	or	$v0,$t8,$zero
/*  f105094:	24a50011 */ 	addiu	$a1,$a1,0x11
/*  f105098:	01c77821 */ 	addu	$t7,$t6,$a3
/*  f10509c:	8d2e0000 */ 	lw	$t6,0x0($t1)
/*  f1050a0:	25f8000e */ 	addiu	$t8,$t7,0xe
/*  f1050a4:	0018c880 */ 	sll	$t9,$t8,0x2
/*  f1050a8:	032e0019 */ 	multu	$t9,$t6
/*  f1050ac:	00007812 */ 	mflo	$t7
/*  f1050b0:	31f80fff */ 	andi	$t8,$t7,0xfff
/*  f1050b4:	8d4f0004 */ 	lw	$t7,0x4($t2)
/*  f1050b8:	0018cb00 */ 	sll	$t9,$t8,0xc
/*  f1050bc:	03217025 */ 	or	$t6,$t9,$at
/*  f1050c0:	25f80027 */ 	addiu	$t8,$t7,0x27
/*  f1050c4:	0018c880 */ 	sll	$t9,$t8,0x2
/*  f1050c8:	332f0fff */ 	andi	$t7,$t9,0xfff
/*  f1050cc:	01cfc025 */ 	or	$t8,$t6,$t7
/*  f1050d0:	ac580000 */ 	sw	$t8,0x0($v0)
/*  f1050d4:	8d590000 */ 	lw	$t9,0x0($t2)
/*  f1050d8:	8d380000 */ 	lw	$t8,0x0($t1)
/*  f1050dc:	03277021 */ 	addu	$t6,$t9,$a3
/*  f1050e0:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f1050e4:	01f80019 */ 	multu	$t7,$t8
/*  f1050e8:	8d580004 */ 	lw	$t8,0x4($t2)
/*  f1050ec:	0000c812 */ 	mflo	$t9
/*  f1050f0:	332e0fff */ 	andi	$t6,$t9,0xfff
/*  f1050f4:	000e7b00 */ 	sll	$t7,$t6,0xc
/*  f1050f8:	27190019 */ 	addiu	$t9,$t8,0x19
/*  f1050fc:	00197080 */ 	sll	$t6,$t9,0x2
/*  f105100:	31d80fff */ 	andi	$t8,$t6,0xfff
/*  f105104:	01f8c825 */ 	or	$t9,$t7,$t8
/*  f105108:	ac590004 */ 	sw	$t9,0x4($v0)
/*  f10510c:	8fae0138 */ 	lw	$t6,0x138($sp)
/*  f105110:	3c18b400 */ 	lui	$t8,0xb400
/*  f105114:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f105118:	afaf0138 */ 	sw	$t7,0x138($sp)
/*  f10511c:	adcb0004 */ 	sw	$t3,0x4($t6)
/*  f105120:	add80000 */ 	sw	$t8,0x0($t6)
/*  f105124:	8fb90138 */ 	lw	$t9,0x138($sp)
/*  f105128:	01c01825 */ 	or	$v1,$t6,$zero
/*  f10512c:	3c0fb300 */ 	lui	$t7,0xb300
/*  f105130:	272e0008 */ 	addiu	$t6,$t9,0x8
/*  f105134:	afae0138 */ 	sw	$t6,0x138($sp)
/*  f105138:	af2f0000 */ 	sw	$t7,0x0($t9)
/*  f10513c:	03202025 */ 	or	$a0,$t9,$zero
/*  f105140:	24190400 */ 	addiu	$t9,$zero,0x400
/*  f105144:	8d380000 */ 	lw	$t8,0x0($t1)
/*  f105148:	0338001a */ 	div	$zero,$t9,$t8
/*  f10514c:	00007012 */ 	mflo	$t6
/*  f105150:	31cfffff */ 	andi	$t7,$t6,0xffff
/*  f105154:	17000002 */ 	bnez	$t8,.L0f105160
/*  f105158:	00000000 */ 	nop
/*  f10515c:	0007000d */ 	break	0x7
.L0f105160:
/*  f105160:	2401ffff */ 	addiu	$at,$zero,-1
/*  f105164:	17010004 */ 	bne	$t8,$at,.L0f105178
/*  f105168:	3c018000 */ 	lui	$at,0x8000
/*  f10516c:	17210002 */ 	bne	$t9,$at,.L0f105178
/*  f105170:	00000000 */ 	nop
/*  f105174:	0006000d */ 	break	0x6
.L0f105178:
/*  f105178:	000fcc00 */ 	sll	$t9,$t7,0x10
/*  f10517c:	3738fc00 */ 	ori	$t8,$t9,0xfc00
/*  f105180:	14d0ff8c */ 	bne	$a2,$s0,.L0f104fb4
/*  f105184:	ac980004 */ 	sw	$t8,0x4($a0)
/*  f105188:	100000a9 */ 	b	.L0f105430
/*  f10518c:	8d590000 */ 	lw	$t9,0x0($t2)
.L0f105190:
/*  f105190:	8d650000 */ 	lw	$a1,0x0($t3)
/*  f105194:	240e0002 */ 	addiu	$t6,$zero,0x2
/*  f105198:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f10519c:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f1051a0:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f1051a4:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f1051a8:	afaa0134 */ 	sw	$t2,0x134($sp)
/*  f1051ac:	0fc2ce70 */ 	jal	func0f0b39c0
/*  f1051b0:	24a50198 */ 	addiu	$a1,$a1,0x198
/*  f1051b4:	8fb90138 */ 	lw	$t9,0x138($sp)
/*  f1051b8:	8faa0134 */ 	lw	$t2,0x134($sp)
/*  f1051bc:	3c0eba00 */ 	lui	$t6,0xba00
/*  f1051c0:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f1051c4:	afb80138 */ 	sw	$t8,0x138($sp)
/*  f1051c8:	35ce1402 */ 	ori	$t6,$t6,0x1402
/*  f1051cc:	af2e0000 */ 	sw	$t6,0x0($t9)
/*  f1051d0:	af200004 */ 	sw	$zero,0x4($t9)
/*  f1051d4:	8faf0138 */ 	lw	$t7,0x138($sp)
/*  f1051d8:	3c18ba00 */ 	lui	$t8,0xba00
/*  f1051dc:	37180c02 */ 	ori	$t8,$t8,0xc02
/*  f1051e0:	25f90008 */ 	addiu	$t9,$t7,0x8
/*  f1051e4:	afb90138 */ 	sw	$t9,0x138($sp)
/*  f1051e8:	ade00004 */ 	sw	$zero,0x4($t7)
/*  f1051ec:	adf80000 */ 	sw	$t8,0x0($t7)
/*  f1051f0:	8fae0138 */ 	lw	$t6,0x138($sp)
/*  f1051f4:	3c18fffc */ 	lui	$t8,0xfffc
/*  f1051f8:	3c19fcff */ 	lui	$t9,0xfcff
/*  f1051fc:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f105200:	afaf0138 */ 	sw	$t7,0x138($sp)
/*  f105204:	3739ffff */ 	ori	$t9,$t9,0xffff
/*  f105208:	3718f279 */ 	ori	$t8,$t8,0xf279
/*  f10520c:	add80004 */ 	sw	$t8,0x4($t6)
/*  f105210:	add90000 */ 	sw	$t9,0x0($t6)
/*  f105214:	8fa70138 */ 	lw	$a3,0x138($sp)
/*  f105218:	3c0dfb00 */ 	lui	$t5,0xfb00
/*  f10521c:	241fff00 */ 	addiu	$ra,$zero,-256
/*  f105220:	24ef0008 */ 	addiu	$t7,$a3,0x8
/*  f105224:	afaf0138 */ 	sw	$t7,0x138($sp)
/*  f105228:	aced0000 */ 	sw	$t5,0x0($a3)
/*  f10522c:	8d59000c */ 	lw	$t9,0xc($t2)
/*  f105230:	3c098008 */ 	lui	$t1,%hi(g_ScaleX)
/*  f105234:	2529fac0 */ 	addiu	$t1,$t1,%lo(g_ScaleX)
/*  f105238:	333800ff */ 	andi	$t8,$t9,0xff
/*  f10523c:	00187080 */ 	sll	$t6,$t8,0x2
/*  f105240:	01d87023 */ 	subu	$t6,$t6,$t8
/*  f105244:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f105248:	01d87023 */ 	subu	$t6,$t6,$t8
/*  f10524c:	000e7100 */ 	sll	$t6,$t6,0x4
/*  f105250:	01d87023 */ 	subu	$t6,$t6,$t8
/*  f105254:	000e7a02 */ 	srl	$t7,$t6,0x8
/*  f105258:	01ffc825 */ 	or	$t9,$t7,$ra
/*  f10525c:	acf90004 */ 	sw	$t9,0x4($a3)
/*  f105260:	8fb800ec */ 	lw	$t8,0xec($sp)
/*  f105264:	3c0f800a */ 	lui	$t7,%hi(g_SoloSaveFile)
/*  f105268:	25ef2200 */ 	addiu	$t7,$t7,%lo(g_SoloSaveFile)
/*  f10526c:	00187080 */ 	sll	$t6,$t8,0x2
/*  f105270:	01d87023 */ 	subu	$t6,$t6,$t8
/*  f105274:	000e7040 */ 	sll	$t6,$t6,0x1
/*  f105278:	01cf1021 */ 	addu	$v0,$t6,$t7
/*  f10527c:	00001825 */ 	or	$v1,$zero,$zero
.L0f105280:
/*  f105280:	94590020 */ 	lhu	$t9,0x20($v0)
/*  f105284:	24780001 */ 	addiu	$t8,$v1,0x1
/*  f105288:	53200003 */ 	beqzl	$t9,.L0f105298
/*  f10528c:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f105290:	afb80124 */ 	sw	$t8,0x124($sp)
/*  f105294:	24630001 */ 	addiu	$v1,$v1,0x1
.L0f105298:
/*  f105298:	28610003 */ 	slti	$at,$v1,0x3
/*  f10529c:	1420fff8 */ 	bnez	$at,.L0f105280
/*  f1052a0:	24420002 */ 	addiu	$v0,$v0,0x2
/*  f1052a4:	8fa70124 */ 	lw	$a3,0x124($sp)
/*  f1052a8:	3c0b0010 */ 	lui	$t3,0x10
/*  f1052ac:	356b01c0 */ 	ori	$t3,$t3,0x1c0
/*  f1052b0:	00077100 */ 	sll	$t6,$a3,0x4
/*  f1052b4:	01c77021 */ 	addu	$t6,$t6,$a3
/*  f1052b8:	25c7003f */ 	addiu	$a3,$t6,0x3f
/*  f1052bc:	2405003f */ 	addiu	$a1,$zero,0x3f
/*  f1052c0:	3c10e400 */ 	lui	$s0,0xe400
/*  f1052c4:	240c0072 */ 	addiu	$t4,$zero,0x72
/*  f1052c8:	2408003f */ 	addiu	$t0,$zero,0x3f
.L0f1052cc:
/*  f1052cc:	14a70015 */ 	bne	$a1,$a3,.L0f105324
/*  f1052d0:	00a03025 */ 	or	$a2,$a1,$zero
/*  f1052d4:	8fa20138 */ 	lw	$v0,0x138($sp)
/*  f1052d8:	24590008 */ 	addiu	$t9,$v0,0x8
/*  f1052dc:	afb90138 */ 	sw	$t9,0x138($sp)
/*  f1052e0:	ac4d0000 */ 	sw	$t5,0x0($v0)
/*  f1052e4:	8d58000c */ 	lw	$t8,0xc($t2)
/*  f1052e8:	330e00ff */ 	andi	$t6,$t8,0xff
/*  f1052ec:	01c80019 */ 	multu	$t6,$t0
/*  f1052f0:	00007812 */ 	mflo	$t7
/*  f1052f4:	000fca02 */ 	srl	$t9,$t7,0x8
/*  f1052f8:	033fc025 */ 	or	$t8,$t9,$ra
/*  f1052fc:	ac580004 */ 	sw	$t8,0x4($v0)
/*  f105300:	8fae0138 */ 	lw	$t6,0x138($sp)
/*  f105304:	3c18ff37 */ 	lui	$t8,0xff37
/*  f105308:	3c19fc12 */ 	lui	$t9,0xfc12
/*  f10530c:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f105310:	afaf0138 */ 	sw	$t7,0x138($sp)
/*  f105314:	37399a25 */ 	ori	$t9,$t9,0x9a25
/*  f105318:	3718ffff */ 	ori	$t8,$t8,0xffff
/*  f10531c:	add80004 */ 	sw	$t8,0x4($t6)
/*  f105320:	add90000 */ 	sw	$t9,0x0($t6)
.L0f105324:
/*  f105324:	8fae0138 */ 	lw	$t6,0x138($sp)
/*  f105328:	24a50011 */ 	addiu	$a1,$a1,0x11
/*  f10532c:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f105330:	afaf0138 */ 	sw	$t7,0x138($sp)
/*  f105334:	8d590000 */ 	lw	$t9,0x0($t2)
/*  f105338:	01c01025 */ 	or	$v0,$t6,$zero
/*  f10533c:	0326c021 */ 	addu	$t8,$t9,$a2
/*  f105340:	8d390000 */ 	lw	$t9,0x0($t1)
/*  f105344:	270e000e */ 	addiu	$t6,$t8,0xe
/*  f105348:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f10534c:	01f90019 */ 	multu	$t7,$t9
/*  f105350:	0000c012 */ 	mflo	$t8
/*  f105354:	330e0fff */ 	andi	$t6,$t8,0xfff
/*  f105358:	8d580004 */ 	lw	$t8,0x4($t2)
/*  f10535c:	000e7b00 */ 	sll	$t7,$t6,0xc
/*  f105360:	01f0c825 */ 	or	$t9,$t7,$s0
/*  f105364:	270e0027 */ 	addiu	$t6,$t8,0x27
/*  f105368:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f10536c:	31f80fff */ 	andi	$t8,$t7,0xfff
/*  f105370:	03387025 */ 	or	$t6,$t9,$t8
/*  f105374:	ac4e0000 */ 	sw	$t6,0x0($v0)
/*  f105378:	8d4f0000 */ 	lw	$t7,0x0($t2)
/*  f10537c:	8d2e0000 */ 	lw	$t6,0x0($t1)
/*  f105380:	01e6c821 */ 	addu	$t9,$t7,$a2
/*  f105384:	0019c080 */ 	sll	$t8,$t9,0x2
/*  f105388:	030e0019 */ 	multu	$t8,$t6
/*  f10538c:	8d4e0004 */ 	lw	$t6,0x4($t2)
/*  f105390:	00007812 */ 	mflo	$t7
/*  f105394:	31f90fff */ 	andi	$t9,$t7,0xfff
/*  f105398:	0019c300 */ 	sll	$t8,$t9,0xc
/*  f10539c:	25cf0019 */ 	addiu	$t7,$t6,0x19
/*  f1053a0:	000fc880 */ 	sll	$t9,$t7,0x2
/*  f1053a4:	332e0fff */ 	andi	$t6,$t9,0xfff
/*  f1053a8:	030e7825 */ 	or	$t7,$t8,$t6
/*  f1053ac:	ac4f0004 */ 	sw	$t7,0x4($v0)
/*  f1053b0:	8fb90138 */ 	lw	$t9,0x138($sp)
/*  f1053b4:	3c0eb400 */ 	lui	$t6,0xb400
/*  f1053b8:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f1053bc:	afb80138 */ 	sw	$t8,0x138($sp)
/*  f1053c0:	af2b0004 */ 	sw	$t3,0x4($t9)
/*  f1053c4:	af2e0000 */ 	sw	$t6,0x0($t9)
/*  f1053c8:	8faf0138 */ 	lw	$t7,0x138($sp)
/*  f1053cc:	03201825 */ 	or	$v1,$t9,$zero
/*  f1053d0:	3c18b300 */ 	lui	$t8,0xb300
/*  f1053d4:	25f90008 */ 	addiu	$t9,$t7,0x8
/*  f1053d8:	afb90138 */ 	sw	$t9,0x138($sp)
/*  f1053dc:	adf80000 */ 	sw	$t8,0x0($t7)
/*  f1053e0:	01e02025 */ 	or	$a0,$t7,$zero
/*  f1053e4:	240f0400 */ 	addiu	$t7,$zero,0x400
/*  f1053e8:	8d2e0000 */ 	lw	$t6,0x0($t1)
/*  f1053ec:	01ee001a */ 	div	$zero,$t7,$t6
/*  f1053f0:	0000c812 */ 	mflo	$t9
/*  f1053f4:	3338ffff */ 	andi	$t8,$t9,0xffff
/*  f1053f8:	15c00002 */ 	bnez	$t6,.L0f105404
/*  f1053fc:	00000000 */ 	nop
/*  f105400:	0007000d */ 	break	0x7
.L0f105404:
/*  f105404:	2401ffff */ 	addiu	$at,$zero,-1
/*  f105408:	15c10004 */ 	bne	$t6,$at,.L0f10541c
/*  f10540c:	3c018000 */ 	lui	$at,0x8000
/*  f105410:	15e10002 */ 	bne	$t7,$at,.L0f10541c
/*  f105414:	00000000 */ 	nop
/*  f105418:	0006000d */ 	break	0x6
.L0f10541c:
/*  f10541c:	00187c00 */ 	sll	$t7,$t8,0x10
/*  f105420:	35eefc00 */ 	ori	$t6,$t7,0xfc00
/*  f105424:	14acffa9 */ 	bne	$a1,$t4,.L0f1052cc
/*  f105428:	ac8e0004 */ 	sw	$t6,0x4($a0)
/*  f10542c:	8d590000 */ 	lw	$t9,0x0($t2)
.L0f105430:
/*  f105430:	8fa40138 */ 	lw	$a0,0x138($sp)
/*  f105434:	2738003e */ 	addiu	$t8,$t9,0x3e
/*  f105438:	afb80130 */ 	sw	$t8,0x130($sp)
/*  f10543c:	8d4f0004 */ 	lw	$t7,0x4($t2)
/*  f105440:	afaa0134 */ 	sw	$t2,0x134($sp)
/*  f105444:	25ee0003 */ 	addiu	$t6,$t7,0x3
/*  f105448:	0fc54d8a */ 	jal	func0f153628
/*  f10544c:	afae012c */ 	sw	$t6,0x12c($sp)
/*  f105450:	8fb90050 */ 	lw	$t9,0x50($sp)
/*  f105454:	3c188007 */ 	lui	$t8,%hi(g_StageNames)
/*  f105458:	27181e6c */ 	addiu	$t8,$t8,%lo(g_StageNames)
/*  f10545c:	03381821 */ 	addu	$v1,$t9,$t8
/*  f105460:	afa20138 */ 	sw	$v0,0x138($sp)
/*  f105464:	94640006 */ 	lhu	$a0,0x6($v1)
/*  f105468:	0fc5b9f1 */ 	jal	langGet
/*  f10546c:	afa3004c */ 	sw	$v1,0x4c($sp)
/*  f105470:	27a400f0 */ 	addiu	$a0,$sp,0xf0
/*  f105474:	0c004c4c */ 	jal	strcpy
/*  f105478:	00402825 */ 	or	$a1,$v0,$zero
/*  f10547c:	3c057f1b */ 	lui	$a1,%hi(var7f1b2d50)
/*  f105480:	24a52d50 */ 	addiu	$a1,$a1,%lo(var7f1b2d50)
/*  f105484:	0c004c89 */ 	jal	strcat
/*  f105488:	27a400f0 */ 	addiu	$a0,$sp,0xf0
/*  f10548c:	0c002f02 */ 	jal	viGetWidth
/*  f105490:	00000000 */ 	nop
/*  f105494:	00028400 */ 	sll	$s0,$v0,0x10
/*  f105498:	00107c03 */ 	sra	$t7,$s0,0x10
/*  f10549c:	0c002f06 */ 	jal	viGetHeight
/*  f1054a0:	01e08025 */ 	or	$s0,$t7,$zero
/*  f1054a4:	3c0e8008 */ 	lui	$t6,%hi(g_FontHandelGothicMd1)
/*  f1054a8:	3c198008 */ 	lui	$t9,%hi(g_FontHandelGothicMd2)
/*  f1054ac:	8f39fb14 */ 	lw	$t9,%lo(g_FontHandelGothicMd2)($t9)
/*  f1054b0:	8dcefb18 */ 	lw	$t6,%lo(g_FontHandelGothicMd1)($t6)
/*  f1054b4:	8faa0134 */ 	lw	$t2,0x134($sp)
/*  f1054b8:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f1054bc:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f1054c0:	8d58000c */ 	lw	$t8,0xc($t2)
/*  f1054c4:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f1054c8:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f1054cc:	afa20020 */ 	sw	$v0,0x20($sp)
/*  f1054d0:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f1054d4:	8fa40138 */ 	lw	$a0,0x138($sp)
/*  f1054d8:	27a50130 */ 	addiu	$a1,$sp,0x130
/*  f1054dc:	27a6012c */ 	addiu	$a2,$sp,0x12c
/*  f1054e0:	27a700f0 */ 	addiu	$a3,$sp,0xf0
/*  f1054e4:	0fc5580f */ 	jal	textRenderProjected
/*  f1054e8:	afb80018 */ 	sw	$t8,0x18($sp)
/*  f1054ec:	8faf004c */ 	lw	$t7,0x4c($sp)
/*  f1054f0:	afa20138 */ 	sw	$v0,0x138($sp)
/*  f1054f4:	0fc5b9f1 */ 	jal	langGet
/*  f1054f8:	95e40008 */ 	lhu	$a0,0x8($t7)
/*  f1054fc:	27a400f0 */ 	addiu	$a0,$sp,0xf0
/*  f105500:	0c004c4c */ 	jal	strcpy
/*  f105504:	00402825 */ 	or	$a1,$v0,$zero
/*  f105508:	0c002f02 */ 	jal	viGetWidth
/*  f10550c:	00000000 */ 	nop
/*  f105510:	00028400 */ 	sll	$s0,$v0,0x10
/*  f105514:	00107403 */ 	sra	$t6,$s0,0x10
/*  f105518:	0c002f06 */ 	jal	viGetHeight
/*  f10551c:	01c08025 */ 	or	$s0,$t6,$zero
/*  f105520:	3c198008 */ 	lui	$t9,%hi(g_FontHandelGothicSm1)
/*  f105524:	3c188008 */ 	lui	$t8,%hi(g_FontHandelGothicSm2)
/*  f105528:	8f18fb0c */ 	lw	$t8,%lo(g_FontHandelGothicSm2)($t8)
/*  f10552c:	8f39fb10 */ 	lw	$t9,%lo(g_FontHandelGothicSm1)($t9)
/*  f105530:	8faa0134 */ 	lw	$t2,0x134($sp)
/*  f105534:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f105538:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f10553c:	8d4f000c */ 	lw	$t7,0xc($t2)
/*  f105540:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f105544:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f105548:	afa20020 */ 	sw	$v0,0x20($sp)
/*  f10554c:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f105550:	8fa40138 */ 	lw	$a0,0x138($sp)
/*  f105554:	27a50130 */ 	addiu	$a1,$sp,0x130
/*  f105558:	27a6012c */ 	addiu	$a2,$sp,0x12c
/*  f10555c:	27a700f0 */ 	addiu	$a3,$sp,0xf0
/*  f105560:	0fc5580f */ 	jal	textRenderProjected
/*  f105564:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f105568:	afa20138 */ 	sw	$v0,0x138($sp)
/*  f10556c:	0fc54de0 */ 	jal	func0f153780
/*  f105570:	00402025 */ 	or	$a0,$v0,$zero
/*  f105574:	10000005 */ 	b	.L0f10558c
/*  f105578:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f10557c:	240e002a */ 	addiu	$t6,$zero,0x2a
/*  f105580:	ae0e0000 */ 	sw	$t6,0x0($s0)
.L0f105584:
/*  f105584:	00001025 */ 	or	$v0,$zero,$zero
.L0f105588:
/*  f105588:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f10558c:
/*  f10558c:	8fb00038 */ 	lw	$s0,0x38($sp)
/*  f105590:	27bd01f8 */ 	addiu	$sp,$sp,0x1f8
/*  f105594:	03e00008 */ 	jr	$ra
/*  f105598:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel menuhandler0010476c
.late_rodata
glabel var7f1ad09cnb
.word menuhandler0010476c+0x080
glabel var7f1ad0a0nb
.word menuhandler0010476c+0x394
glabel var7f1ad0a4nb
.word menuhandler0010476c+0x144
glabel var7f1ad0a8nb
.word menuhandler0010476c+0x400
glabel var7f1ad0acnb
.word menuhandler0010476c+0x434
glabel var7f1ad0b0nb
.word menuhandler0010476c+0x1d0
glabel var7f1ad0b4nb
.word menuhandler0010476c+0x2a8
glabel var7f1ad0b8nb
.word menuhandler0010476c+0xd68
glabel var7f1ad0bcnb
.word menuhandler0010476c+0xd68
glabel var7f1ad0c0nb
.word menuhandler0010476c+0xd68
glabel var7f1ad0c4nb
.word menuhandler0010476c+0xd68
glabel var7f1ad0c8nb
.word menuhandler0010476c+0xd68
glabel var7f1ad0ccnb
.word menuhandler0010476c+0xd68
glabel var7f1ad0d0nb
.word menuhandler0010476c+0xd68
glabel var7f1ad0d4nb
.word menuhandler0010476c+0xd68
glabel var7f1ad0d8nb
.word menuhandler0010476c+0xd68
glabel var7f1ad0dcnb
.word menuhandler0010476c+0xd68
glabel var7f1ad0e0nb
.word menuhandler0010476c+0xd68
glabel var7f1ad0e4nb
.word menuhandler0010476c+0x47c
glabel var7f1ad0e8nb
.word menuhandler0010476c+0xd60
glabel var7f1ad0ecnb
.word menuhandler0010476c+0xd68
glabel var7f1ad0f0nb
.word menuhandler0010476c+0xd68
glabel var7f1ad0f4nb
.word menuhandler0010476c+0xd68
glabel var7f1ad0f8nb
.word menuhandler0010476c+0xd68
glabel var7f1ad0fcnb
.word menuhandler0010476c+0x2b8
.text
/*  f10056c:	27bdfe10 */ 	addiu	$sp,$sp,-496
/*  f100570:	3c0e8007 */ 	lui	$t6,0x8007
/*  f100574:	afb00038 */ 	sw	$s0,0x38($sp)
/*  f100578:	27a201a0 */ 	addiu	$v0,$sp,0x1a0
/*  f10057c:	25ce44f8 */ 	addiu	$t6,$t6,0x44f8
/*  f100580:	00c08025 */ 	or	$s0,$a2,$zero
/*  f100584:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f100588:	afa501f4 */ 	sw	$a1,0x1f4($sp)
/*  f10058c:	25d90048 */ 	addiu	$t9,$t6,0x48
/*  f100590:	0040c025 */ 	or	$t8,$v0,$zero
.NB0f100594:
/*  f100594:	8dc10000 */ 	lw	$at,0x0($t6)
/*  f100598:	25ce000c */ 	addiu	$t6,$t6,0xc
/*  f10059c:	2718000c */ 	addiu	$t8,$t8,0xc
/*  f1005a0:	af01fff4 */ 	sw	$at,-0xc($t8)
/*  f1005a4:	8dc1fff8 */ 	lw	$at,-0x8($t6)
/*  f1005a8:	af01fff8 */ 	sw	$at,-0x8($t8)
/*  f1005ac:	8dc1fffc */ 	lw	$at,-0x4($t6)
/*  f1005b0:	15d9fff8 */ 	bne	$t6,$t9,.NB0f100594
/*  f1005b4:	af01fffc */ 	sw	$at,-0x4($t8)
/*  f1005b8:	8dc10000 */ 	lw	$at,0x0($t6)
/*  f1005bc:	248fffff */ 	addiu	$t7,$a0,-1
/*  f1005c0:	af010000 */ 	sw	$at,0x0($t8)
/*  f1005c4:	8dd90004 */ 	lw	$t9,0x4($t6)
/*  f1005c8:	2de10019 */ 	sltiu	$at,$t7,0x19
/*  f1005cc:	10200341 */ 	beqz	$at,.NB0f1012d4
/*  f1005d0:	af190004 */ 	sw	$t9,0x4($t8)
/*  f1005d4:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f1005d8:	3c017f1b */ 	lui	$at,0x7f1b
/*  f1005dc:	002f0821 */ 	addu	$at,$at,$t7
/*  f1005e0:	8c2fd09c */ 	lw	$t7,-0x2f64($at)
/*  f1005e4:	01e00008 */ 	jr	$t7
/*  f1005e8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1005ec:	3c0a800a */ 	lui	$t2,0x800a
/*  f1005f0:	3c09800a */ 	lui	$t1,0x800a
/*  f1005f4:	3c08800a */ 	lui	$t0,0x800a
/*  f1005f8:	ae000000 */ 	sw	$zero,0x0($s0)
/*  f1005fc:	250827a8 */ 	addiu	$t0,$t0,0x27a8
/*  f100600:	252966f0 */ 	addiu	$t1,$t1,0x66f0
/*  f100604:	254a66f0 */ 	addiu	$t2,$t2,0x66f0
/*  f100608:	00003025 */ 	or	$a2,$zero,$zero
/*  f10060c:	240b0011 */ 	addiu	$t3,$zero,0x11
/*  f100610:	24070003 */ 	addiu	$a3,$zero,0x3
.NB0f100614:
/*  f100614:	91050003 */ 	lbu	$a1,0x3($t0)
/*  f100618:	00002025 */ 	or	$a0,$zero,$zero
/*  f10061c:	00001025 */ 	or	$v0,$zero,$zero
/*  f100620:	0005c9c2 */ 	srl	$t9,$a1,0x7
/*  f100624:	03202825 */ 	or	$a1,$t9,$zero
/*  f100628:	01401825 */ 	or	$v1,$t2,$zero
.NB0f10062c:
/*  f10062c:	946e0020 */ 	lhu	$t6,0x20($v1)
/*  f100630:	11c00002 */ 	beqz	$t6,.NB0f10063c
/*  f100634:	00000000 */ 	sll	$zero,$zero,0x0
/*  f100638:	24040001 */ 	addiu	$a0,$zero,0x1
.NB0f10063c:
/*  f10063c:	14a00004 */ 	bnez	$a1,.NB0f100650
/*  f100640:	00027080 */ 	sll	$t6,$v0,0x2
/*  f100644:	8d180000 */ 	lw	$t8,0x0($t0)
/*  f100648:	0018ce40 */ 	sll	$t9,$t8,0x19
/*  f10064c:	07210008 */ 	bgez	$t9,.NB0f100670
.NB0f100650:
/*  f100650:	012ec021 */ 	addu	$t8,$t1,$t6
/*  f100654:	8f0f00a0 */ 	lw	$t7,0xa0($t8)
/*  f100658:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f10065c:	00d97004 */ 	sllv	$t6,$t9,$a2
/*  f100660:	01eec024 */ 	and	$t8,$t7,$t6
/*  f100664:	53000003 */ 	beqzl	$t8,.NB0f100674
/*  f100668:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f10066c:	24040001 */ 	addiu	$a0,$zero,0x1
.NB0f100670:
/*  f100670:	24420001 */ 	addiu	$v0,$v0,0x1
.NB0f100674:
/*  f100674:	1447ffed */ 	bne	$v0,$a3,.NB0f10062c
/*  f100678:	24630002 */ 	addiu	$v1,$v1,0x2
/*  f10067c:	8e190000 */ 	lw	$t9,0x0($s0)
/*  f100680:	24c60001 */ 	addiu	$a2,$a2,0x1
/*  f100684:	272f0001 */ 	addiu	$t7,$t9,0x1
/*  f100688:	10800003 */ 	beqz	$a0,.NB0f100698
/*  f10068c:	ae0f0000 */ 	sw	$t7,0x0($s0)
/*  f100690:	14cbffe0 */ 	bne	$a2,$t3,.NB0f100614
/*  f100694:	254a0006 */ 	addiu	$t2,$t2,0x6
.NB0f100698:
/*  f100698:	0fc40119 */ 	jal	getNumUnlockedSpecialStages
/*  f10069c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1006a0:	8e0e0000 */ 	lw	$t6,0x0($s0)
/*  f1006a4:	01c2c021 */ 	addu	$t8,$t6,$v0
/*  f1006a8:	1000030a */ 	beqz	$zero,.NB0f1012d4
/*  f1006ac:	ae180000 */ 	sw	$t8,0x0($s0)
/*  f1006b0:	8e050004 */ 	lw	$a1,0x4($s0)
/*  f1006b4:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f1006b8:	27a60184 */ 	addiu	$a2,$sp,0x184
/*  f1006bc:	54a00009 */ 	bnezl	$a1,.NB0f1006e4
/*  f1006c0:	8e030000 */ 	lw	$v1,0x0($s0)
/*  f1006c4:	0fc4015b */ 	jal	menuhandler0010476c
/*  f1006c8:	8fa501f4 */ 	lw	$a1,0x1f4($sp)
/*  f1006cc:	0fc40119 */ 	jal	getNumUnlockedSpecialStages
/*  f1006d0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1006d4:	8fb90184 */ 	lw	$t9,0x184($sp)
/*  f1006d8:	03222823 */ 	subu	$a1,$t9,$v0
/*  f1006dc:	ae050004 */ 	sw	$a1,0x4($s0)
/*  f1006e0:	8e030000 */ 	lw	$v1,0x0($s0)
.NB0f1006e4:
/*  f1006e4:	3c048007 */ 	lui	$a0,0x8007
/*  f1006e8:	0065082b */ 	sltu	$at,$v1,$a1
/*  f1006ec:	10200008 */ 	beqz	$at,.NB0f100710
/*  f1006f0:	00037080 */ 	sll	$t6,$v1,0x2
/*  f1006f4:	01c37023 */ 	subu	$t6,$t6,$v1
/*  f1006f8:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f1006fc:	008e2021 */ 	addu	$a0,$a0,$t6
/*  f100700:	0fc5a4dd */ 	jal	langGet
/*  f100704:	94844402 */ 	lhu	$a0,0x4402($a0)
/*  f100708:	100002f4 */ 	beqz	$zero,.NB0f1012dc
/*  f10070c:	8fbf003c */ 	lw	$ra,0x3c($sp)
.NB0f100710:
/*  f100710:	0fc40148 */ 	jal	func0f104720
/*  f100714:	00652023 */ 	subu	$a0,$v1,$a1
/*  f100718:	0002c080 */ 	sll	$t8,$v0,0x2
/*  f10071c:	0302c023 */ 	subu	$t8,$t8,$v0
/*  f100720:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f100724:	3c048007 */ 	lui	$a0,0x8007
/*  f100728:	00982021 */ 	addu	$a0,$a0,$t8
/*  f10072c:	0fc5a4dd */ 	jal	langGet
/*  f100730:	94844402 */ 	lhu	$a0,0x4402($a0)
/*  f100734:	100002e9 */ 	beqz	$zero,.NB0f1012dc
/*  f100738:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f10073c:	8e070000 */ 	lw	$a3,0x0($s0)
/*  f100740:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f100744:	8fa501f4 */ 	lw	$a1,0x1f4($sp)
/*  f100748:	27a60170 */ 	addiu	$a2,$sp,0x170
/*  f10074c:	0fc4015b */ 	jal	menuhandler0010476c
/*  f100750:	afa70180 */ 	sw	$a3,0x180($sp)
/*  f100754:	0fc40119 */ 	jal	getNumUnlockedSpecialStages
/*  f100758:	00000000 */ 	sll	$zero,$zero,0x0
/*  f10075c:	8fb90170 */ 	lw	$t9,0x170($sp)
/*  f100760:	8fa70180 */ 	lw	$a3,0x180($sp)
/*  f100764:	03227823 */ 	subu	$t7,$t9,$v0
/*  f100768:	afaf0170 */ 	sw	$t7,0x170($sp)
/*  f10076c:	8e030000 */ 	lw	$v1,0x0($s0)
/*  f100770:	006f082b */ 	sltu	$at,$v1,$t7
/*  f100774:	14200004 */ 	bnez	$at,.NB0f100788
/*  f100778:	00000000 */ 	sll	$zero,$zero,0x0
/*  f10077c:	0fc40148 */ 	jal	func0f104720
/*  f100780:	006f2023 */ 	subu	$a0,$v1,$t7
/*  f100784:	00403825 */ 	or	$a3,$v0,$zero
.NB0f100788:
/*  f100788:	3c02800a */ 	lui	$v0,0x800a
/*  f10078c:	00077080 */ 	sll	$t6,$a3,0x2
/*  f100790:	2442e6c0 */ 	addiu	$v0,$v0,-6464
/*  f100794:	3c08800a */ 	lui	$t0,0x800a
/*  f100798:	01c77023 */ 	subu	$t6,$t6,$a3
/*  f10079c:	250827a8 */ 	addiu	$t0,$t0,0x27a8
/*  f1007a0:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f1007a4:	3c188007 */ 	lui	$t8,0x8007
/*  f1007a8:	810f0003 */ 	lb	$t7,0x3($t0)
/*  f1007ac:	ac400314 */ 	sw	$zero,0x314($v0)
/*  f1007b0:	ac400318 */ 	sw	$zero,0x318($v0)
/*  f1007b4:	030ec021 */ 	addu	$t8,$t8,$t6
/*  f1007b8:	8f1843fc */ 	lw	$t8,0x43fc($t8)
/*  f1007bc:	a1070002 */ 	sb	$a3,0x2($t0)
/*  f1007c0:	05e10006 */ 	bgez	$t7,.NB0f1007dc
/*  f1007c4:	a1180001 */ 	sb	$t8,0x1($t0)
/*  f1007c8:	3c048007 */ 	lui	$a0,0x8007
/*  f1007cc:	0fc3beda */ 	jal	menuPushDialog
/*  f1007d0:	24844354 */ 	addiu	$a0,$a0,0x4354
/*  f1007d4:	100002c0 */ 	beqz	$zero,.NB0f1012d8
/*  f1007d8:	00001025 */ 	or	$v0,$zero,$zero
.NB0f1007dc:
/*  f1007dc:	8d0e0000 */ 	lw	$t6,0x0($t0)
/*  f1007e0:	3c048007 */ 	lui	$a0,0x8007
/*  f1007e4:	000ece40 */ 	sll	$t9,$t6,0x19
/*  f1007e8:	07210006 */ 	bgez	$t9,.NB0f100804
/*  f1007ec:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1007f0:	3c048007 */ 	lui	$a0,0x8007
/*  f1007f4:	0fc3beda */ 	jal	menuPushDialog
/*  f1007f8:	248443e4 */ 	addiu	$a0,$a0,0x43e4
/*  f1007fc:	100002b6 */ 	beqz	$zero,.NB0f1012d8
/*  f100800:	00001025 */ 	or	$v0,$zero,$zero
.NB0f100804:
/*  f100804:	0fc3beda */ 	jal	menuPushDialog
/*  f100808:	24844190 */ 	addiu	$a0,$a0,0x4190
/*  f10080c:	100002b2 */ 	beqz	$zero,.NB0f1012d8
/*  f100810:	00001025 */ 	or	$v0,$zero,$zero
/*  f100814:	3c0f000f */ 	lui	$t7,0xf
/*  f100818:	35efffff */ 	ori	$t7,$t7,0xffff
/*  f10081c:	100002ad */ 	beqz	$zero,.NB0f1012d4
/*  f100820:	ae0f0000 */ 	sw	$t7,0x0($s0)
/*  f100824:	8e0e0004 */ 	lw	$t6,0x4($s0)
/*  f100828:	3c08800a */ 	lui	$t0,0x800a
/*  f10082c:	250827a8 */ 	addiu	$t0,$t0,0x27a8
/*  f100830:	55c002a9 */ 	bnezl	$t6,.NB0f1012d8
/*  f100834:	00001025 */ 	or	$v0,$zero,$zero
/*  f100838:	81190003 */ 	lb	$t9,0x3($t0)
/*  f10083c:	072202a6 */ 	bltzl	$t9,.NB0f1012d8
/*  f100840:	00001025 */ 	or	$v0,$zero,$zero
/*  f100844:	8d0f0000 */ 	lw	$t7,0x0($t0)
/*  f100848:	3c09800a */ 	lui	$t1,0x800a
/*  f10084c:	252966f0 */ 	addiu	$t1,$t1,0x66f0
/*  f100850:	000fc640 */ 	sll	$t8,$t7,0x19
/*  f100854:	070202a0 */ 	bltzl	$t8,.NB0f1012d8
/*  f100858:	00001025 */ 	or	$v0,$zero,$zero
/*  f10085c:	9139000c */ 	lbu	$t9,0xc($t1)
/*  f100860:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f100864:	27a60160 */ 	addiu	$a2,$sp,0x160
/*  f100868:	ae190000 */ 	sw	$t9,0x0($s0)
/*  f10086c:	0fc4015b */ 	jal	menuhandler0010476c
/*  f100870:	8fa501f4 */ 	lw	$a1,0x1f4($sp)
/*  f100874:	0fc40119 */ 	jal	getNumUnlockedSpecialStages
/*  f100878:	00000000 */ 	sll	$zero,$zero,0x0
/*  f10087c:	8faf0160 */ 	lw	$t7,0x160($sp)
/*  f100880:	01e27023 */ 	subu	$t6,$t7,$v0
/*  f100884:	afae0160 */ 	sw	$t6,0x160($sp)
/*  f100888:	8e180000 */ 	lw	$t8,0x0($s0)
/*  f10088c:	030e082b */ 	sltu	$at,$t8,$t6
/*  f100890:	54200291 */ 	bnezl	$at,.NB0f1012d8
/*  f100894:	00001025 */ 	or	$v0,$zero,$zero
/*  f100898:	0fc40119 */ 	jal	getNumUnlockedSpecialStages
/*  f10089c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1008a0:	8fb90160 */ 	lw	$t9,0x160($sp)
/*  f1008a4:	00401825 */ 	or	$v1,$v0,$zero
/*  f1008a8:	00002025 */ 	or	$a0,$zero,$zero
/*  f1008ac:	272fffff */ 	addiu	$t7,$t9,-1
/*  f1008b0:	18400288 */ 	blez	$v0,.NB0f1012d4
/*  f1008b4:	ae0f0000 */ 	sw	$t7,0x0($s0)
/*  f1008b8:	afa3015c */ 	sw	$v1,0x15c($sp)
.NB0f1008bc:
/*  f1008bc:	0fc40148 */ 	jal	func0f104720
/*  f1008c0:	afa40158 */ 	sw	$a0,0x158($sp)
/*  f1008c4:	3c09800a */ 	lui	$t1,0x800a
/*  f1008c8:	252966f0 */ 	addiu	$t1,$t1,0x66f0
/*  f1008cc:	9138000c */ 	lbu	$t8,0xc($t1)
/*  f1008d0:	8fa3015c */ 	lw	$v1,0x15c($sp)
/*  f1008d4:	8fa40158 */ 	lw	$a0,0x158($sp)
/*  f1008d8:	14580003 */ 	bne	$v0,$t8,.NB0f1008e8
/*  f1008dc:	8fae0160 */ 	lw	$t6,0x160($sp)
/*  f1008e0:	01c4c821 */ 	addu	$t9,$t6,$a0
/*  f1008e4:	ae190000 */ 	sw	$t9,0x0($s0)
.NB0f1008e8:
/*  f1008e8:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f1008ec:	0083082a */ 	slt	$at,$a0,$v1
/*  f1008f0:	5420fff2 */ 	bnezl	$at,.NB0f1008bc
/*  f1008f4:	afa3015c */ 	sw	$v1,0x15c($sp)
/*  f1008f8:	10000277 */ 	beqz	$zero,.NB0f1012d8
/*  f1008fc:	00001025 */ 	or	$v0,$zero,$zero
/*  f100900:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f100904:	8fa501f4 */ 	lw	$a1,0x1f4($sp)
/*  f100908:	0fc4015b */ 	jal	menuhandler0010476c
/*  f10090c:	27a60148 */ 	addiu	$a2,$sp,0x148
/*  f100910:	0fc40119 */ 	jal	getNumUnlockedSpecialStages
/*  f100914:	00000000 */ 	sll	$zero,$zero,0x0
/*  f100918:	8faf0148 */ 	lw	$t7,0x148($sp)
/*  f10091c:	27a301a0 */ 	addiu	$v1,$sp,0x1a0
/*  f100920:	01e2c023 */ 	subu	$t8,$t7,$v0
/*  f100924:	afb80148 */ 	sw	$t8,0x148($sp)
/*  f100928:	ae00000c */ 	sw	$zero,0xc($s0)
/*  f10092c:	27a201f0 */ 	addiu	$v0,$sp,0x1f0
/*  f100930:	8c6e0000 */ 	lw	$t6,0x0($v1)
.NB0f100934:
/*  f100934:	8fb90148 */ 	lw	$t9,0x148($sp)
/*  f100938:	24630008 */ 	addiu	$v1,$v1,0x8
/*  f10093c:	01d9082b */ 	sltu	$at,$t6,$t9
/*  f100940:	10200004 */ 	beqz	$at,.NB0f100954
/*  f100944:	00000000 */ 	sll	$zero,$zero,0x0
/*  f100948:	8e0f000c */ 	lw	$t7,0xc($s0)
/*  f10094c:	25f80001 */ 	addiu	$t8,$t7,0x1
/*  f100950:	ae18000c */ 	sw	$t8,0xc($s0)
.NB0f100954:
/*  f100954:	5462fff7 */ 	bnel	$v1,$v0,.NB0f100934
/*  f100958:	8c6e0000 */ 	lw	$t6,0x0($v1)
/*  f10095c:	8e0e000c */ 	lw	$t6,0xc($s0)
/*  f100960:	25d90001 */ 	addiu	$t9,$t6,0x1
/*  f100964:	1000025b */ 	beqz	$zero,.NB0f1012d4
/*  f100968:	ae190000 */ 	sw	$t9,0x0($s0)
/*  f10096c:	8e030000 */ 	lw	$v1,0x0($s0)
/*  f100970:	8e0f000c */ 	lw	$t7,0xc($s0)
/*  f100974:	0003c0c0 */ 	sll	$t8,$v1,0x3
/*  f100978:	146f0005 */ 	bne	$v1,$t7,.NB0f100990
/*  f10097c:	00587021 */ 	addu	$t6,$v0,$t8
/*  f100980:	0fc5a4dd */ 	jal	langGet
/*  f100984:	97a401ec */ 	lhu	$a0,0x1ec($sp)
/*  f100988:	10000254 */ 	beqz	$zero,.NB0f1012dc
/*  f10098c:	8fbf003c */ 	lw	$ra,0x3c($sp)
.NB0f100990:
/*  f100990:	0fc5a4dd */ 	jal	langGet
/*  f100994:	95c40004 */ 	lhu	$a0,0x4($t6)
/*  f100998:	10000250 */ 	beqz	$zero,.NB0f1012dc
/*  f10099c:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f1009a0:	8e030000 */ 	lw	$v1,0x0($s0)
/*  f1009a4:	8e19000c */ 	lw	$t9,0xc($s0)
/*  f1009a8:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f1009ac:	8fa501f4 */ 	lw	$a1,0x1f4($sp)
/*  f1009b0:	14790009 */ 	bne	$v1,$t9,.NB0f1009d8
/*  f1009b4:	000370c0 */ 	sll	$t6,$v1,0x3
/*  f1009b8:	0fc4015b */ 	jal	menuhandler0010476c
/*  f1009bc:	27a60134 */ 	addiu	$a2,$sp,0x134
/*  f1009c0:	0fc40119 */ 	jal	getNumUnlockedSpecialStages
/*  f1009c4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1009c8:	8faf0134 */ 	lw	$t7,0x134($sp)
/*  f1009cc:	01e2c023 */ 	subu	$t8,$t7,$v0
/*  f1009d0:	10000240 */ 	beqz	$zero,.NB0f1012d4
/*  f1009d4:	ae180008 */ 	sw	$t8,0x8($s0)
.NB0f1009d8:
/*  f1009d8:	004ec821 */ 	addu	$t9,$v0,$t6
/*  f1009dc:	8f2f0000 */ 	lw	$t7,0x0($t9)
/*  f1009e0:	1000023c */ 	beqz	$zero,.NB0f1012d4
/*  f1009e4:	ae0f0008 */ 	sw	$t7,0x8($s0)
/*  f1009e8:	8e180000 */ 	lw	$t8,0x0($s0)
/*  f1009ec:	afb80130 */ 	sw	$t8,0x130($sp)
/*  f1009f0:	8e0a0008 */ 	lw	$t2,0x8($s0)
/*  f1009f4:	afa0011c */ 	sw	$zero,0x11c($sp)
/*  f1009f8:	8e050004 */ 	lw	$a1,0x4($s0)
/*  f1009fc:	afa500e4 */ 	sw	$a1,0xe4($sp)
/*  f100a00:	8e03000c */ 	lw	$v1,0xc($s0)
/*  f100a04:	1460000c */ 	bnez	$v1,.NB0f100a38
/*  f100a08:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f100a0c:	8fa501f4 */ 	lw	$a1,0x1f4($sp)
/*  f100a10:	27a600d4 */ 	addiu	$a2,$sp,0xd4
/*  f100a14:	0fc4015b */ 	jal	menuhandler0010476c
/*  f100a18:	afaa012c */ 	sw	$t2,0x12c($sp)
/*  f100a1c:	0fc40119 */ 	jal	getNumUnlockedSpecialStages
/*  f100a20:	00000000 */ 	sll	$zero,$zero,0x0
/*  f100a24:	8fae00d4 */ 	lw	$t6,0xd4($sp)
/*  f100a28:	8faa012c */ 	lw	$t2,0x12c($sp)
/*  f100a2c:	8e050004 */ 	lw	$a1,0x4($s0)
/*  f100a30:	01c21823 */ 	subu	$v1,$t6,$v0
/*  f100a34:	ae03000c */ 	sw	$v1,0xc($s0)
.NB0f100a38:
/*  f100a38:	00a3082b */ 	sltu	$at,$a1,$v1
/*  f100a3c:	14200005 */ 	bnez	$at,.NB0f100a54
/*  f100a40:	00a32023 */ 	subu	$a0,$a1,$v1
/*  f100a44:	0fc40148 */ 	jal	func0f104720
/*  f100a48:	afaa012c */ 	sw	$t2,0x12c($sp)
/*  f100a4c:	8faa012c */ 	lw	$t2,0x12c($sp)
/*  f100a50:	afa200e4 */ 	sw	$v0,0xe4($sp)
.NB0f100a54:
/*  f100a54:	8faf0130 */ 	lw	$t7,0x130($sp)
/*  f100a58:	3c0ee700 */ 	lui	$t6,0xe700
/*  f100a5c:	27b00130 */ 	addiu	$s0,$sp,0x130
/*  f100a60:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f100a64:	afb80130 */ 	sw	$t8,0x130($sp)
/*  f100a68:	ade00004 */ 	sw	$zero,0x4($t7)
/*  f100a6c:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f100a70:	8fb90130 */ 	lw	$t9,0x130($sp)
/*  f100a74:	3c18ba00 */ 	lui	$t8,0xba00
/*  f100a78:	37181301 */ 	ori	$t8,$t8,0x1301
/*  f100a7c:	272f0008 */ 	addiu	$t7,$t9,0x8
/*  f100a80:	afaf0130 */ 	sw	$t7,0x130($sp)
/*  f100a84:	af200004 */ 	sw	$zero,0x4($t9)
/*  f100a88:	af380000 */ 	sw	$t8,0x0($t9)
/*  f100a8c:	8fae0130 */ 	lw	$t6,0x130($sp)
/*  f100a90:	3c0fb900 */ 	lui	$t7,0xb900
/*  f100a94:	35ef0002 */ 	ori	$t7,$t7,0x2
/*  f100a98:	25d90008 */ 	addiu	$t9,$t6,0x8
/*  f100a9c:	afb90130 */ 	sw	$t9,0x130($sp)
/*  f100aa0:	adc00004 */ 	sw	$zero,0x4($t6)
/*  f100aa4:	adcf0000 */ 	sw	$t7,0x0($t6)
/*  f100aa8:	8fb80130 */ 	lw	$t8,0x130($sp)
/*  f100aac:	3c19ba00 */ 	lui	$t9,0xba00
/*  f100ab0:	37391001 */ 	ori	$t9,$t9,0x1001
/*  f100ab4:	270e0008 */ 	addiu	$t6,$t8,0x8
/*  f100ab8:	afae0130 */ 	sw	$t6,0x130($sp)
/*  f100abc:	af000004 */ 	sw	$zero,0x4($t8)
/*  f100ac0:	af190000 */ 	sw	$t9,0x0($t8)
/*  f100ac4:	8faf0130 */ 	lw	$t7,0x130($sp)
/*  f100ac8:	3c0eba00 */ 	lui	$t6,0xba00
/*  f100acc:	35ce0903 */ 	ori	$t6,$t6,0x903
/*  f100ad0:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f100ad4:	afb80130 */ 	sw	$t8,0x130($sp)
/*  f100ad8:	24190c00 */ 	addiu	$t9,$zero,0xc00
/*  f100adc:	adf90004 */ 	sw	$t9,0x4($t7)
/*  f100ae0:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f100ae4:	8fa200e4 */ 	lw	$v0,0xe4($sp)
/*  f100ae8:	3c18800b */ 	lui	$t8,0x800b
/*  f100aec:	8f18fe58 */ 	lw	$t8,-0x1a8($t8)
/*  f100af0:	00027880 */ 	sll	$t7,$v0,0x2
/*  f100af4:	01e27823 */ 	subu	$t7,$t7,$v0
/*  f100af8:	000f1080 */ 	sll	$v0,$t7,0x2
/*  f100afc:	240e0002 */ 	addiu	$t6,$zero,0x2
/*  f100b00:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f100b04:	03022821 */ 	addu	$a1,$t8,$v0
/*  f100b08:	24a5009c */ 	addiu	$a1,$a1,0x9c
/*  f100b0c:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f100b10:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f100b14:	afa2004c */ 	sw	$v0,0x4c($sp)
/*  f100b18:	afaa012c */ 	sw	$t2,0x12c($sp)
/*  f100b1c:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f100b20:	02002025 */ 	or	$a0,$s0,$zero
/*  f100b24:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f100b28:	0fc2c5c8 */ 	jal	func0f0b39c0
/*  f100b2c:	00003825 */ 	or	$a3,$zero,$zero
/*  f100b30:	8faf0130 */ 	lw	$t7,0x130($sp)
/*  f100b34:	8faa012c */ 	lw	$t2,0x12c($sp)
/*  f100b38:	3c0eba00 */ 	lui	$t6,0xba00
/*  f100b3c:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f100b40:	afb80130 */ 	sw	$t8,0x130($sp)
/*  f100b44:	35ce1402 */ 	ori	$t6,$t6,0x1402
/*  f100b48:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f100b4c:	ade00004 */ 	sw	$zero,0x4($t7)
/*  f100b50:	8fb90130 */ 	lw	$t9,0x130($sp)
/*  f100b54:	3c0efffc */ 	lui	$t6,0xfffc
/*  f100b58:	3c18fcff */ 	lui	$t8,0xfcff
/*  f100b5c:	272f0008 */ 	addiu	$t7,$t9,0x8
/*  f100b60:	afaf0130 */ 	sw	$t7,0x130($sp)
/*  f100b64:	3718ffff */ 	ori	$t8,$t8,0xffff
/*  f100b68:	35cef279 */ 	ori	$t6,$t6,0xf279
/*  f100b6c:	af2e0004 */ 	sw	$t6,0x4($t9)
/*  f100b70:	af380000 */ 	sw	$t8,0x0($t9)
/*  f100b74:	8fb90130 */ 	lw	$t9,0x130($sp)
/*  f100b78:	3c18ba00 */ 	lui	$t8,0xba00
/*  f100b7c:	37180c02 */ 	ori	$t8,$t8,0xc02
/*  f100b80:	272f0008 */ 	addiu	$t7,$t9,0x8
/*  f100b84:	afaf0130 */ 	sw	$t7,0x130($sp)
/*  f100b88:	af380000 */ 	sw	$t8,0x0($t9)
/*  f100b8c:	af200004 */ 	sw	$zero,0x4($t9)
/*  f100b90:	8fae0130 */ 	lw	$t6,0x130($sp)
/*  f100b94:	03202025 */ 	or	$a0,$t9,$zero
/*  f100b98:	3c098008 */ 	lui	$t1,0x8008
/*  f100b9c:	25d90008 */ 	addiu	$t9,$t6,0x8
/*  f100ba0:	afb90130 */ 	sw	$t9,0x130($sp)
/*  f100ba4:	8d4f0000 */ 	lw	$t7,0x0($t2)
/*  f100ba8:	25292320 */ 	addiu	$t1,$t1,0x2320
/*  f100bac:	8d390000 */ 	lw	$t9,0x0($t1)
/*  f100bb0:	01c02825 */ 	or	$a1,$t6,$zero
/*  f100bb4:	25f8003c */ 	addiu	$t8,$t7,0x3c
/*  f100bb8:	00187080 */ 	sll	$t6,$t8,0x2
/*  f100bbc:	01d90019 */ 	multu	$t6,$t9
/*  f100bc0:	3c01e400 */ 	lui	$at,0xe400
/*  f100bc4:	3c08800a */ 	lui	$t0,0x800a
/*  f100bc8:	250827a8 */ 	addiu	$t0,$t0,0x27a8
/*  f100bcc:	3c0b800b */ 	lui	$t3,0x800b
/*  f100bd0:	256bfe58 */ 	addiu	$t3,$t3,-424
/*  f100bd4:	00007812 */ 	mflo	$t7
/*  f100bd8:	31f80fff */ 	andi	$t8,$t7,0xfff
/*  f100bdc:	8d4f0004 */ 	lw	$t7,0x4($t2)
/*  f100be0:	00187300 */ 	sll	$t6,$t8,0xc
/*  f100be4:	01c1c825 */ 	or	$t9,$t6,$at
/*  f100be8:	25f80027 */ 	addiu	$t8,$t7,0x27
/*  f100bec:	00187080 */ 	sll	$t6,$t8,0x2
/*  f100bf0:	31cf0fff */ 	andi	$t7,$t6,0xfff
/*  f100bf4:	032fc025 */ 	or	$t8,$t9,$t7
/*  f100bf8:	acb80000 */ 	sw	$t8,0x0($a1)
/*  f100bfc:	8d4e0000 */ 	lw	$t6,0x0($t2)
/*  f100c00:	8d380000 */ 	lw	$t8,0x0($t1)
/*  f100c04:	25d90004 */ 	addiu	$t9,$t6,0x4
/*  f100c08:	00197880 */ 	sll	$t7,$t9,0x2
/*  f100c0c:	01f80019 */ 	multu	$t7,$t8
/*  f100c10:	8d580004 */ 	lw	$t8,0x4($t2)
/*  f100c14:	00007012 */ 	mflo	$t6
/*  f100c18:	31d90fff */ 	andi	$t9,$t6,0xfff
/*  f100c1c:	00197b00 */ 	sll	$t7,$t9,0xc
/*  f100c20:	270e0003 */ 	addiu	$t6,$t8,0x3
/*  f100c24:	000ec880 */ 	sll	$t9,$t6,0x2
/*  f100c28:	33380fff */ 	andi	$t8,$t9,0xfff
/*  f100c2c:	01f87025 */ 	or	$t6,$t7,$t8
/*  f100c30:	acae0004 */ 	sw	$t6,0x4($a1)
/*  f100c34:	8fb90130 */ 	lw	$t9,0x130($sp)
/*  f100c38:	240e0480 */ 	addiu	$t6,$zero,0x480
/*  f100c3c:	3c18b400 */ 	lui	$t8,0xb400
/*  f100c40:	272f0008 */ 	addiu	$t7,$t9,0x8
/*  f100c44:	afaf0130 */ 	sw	$t7,0x130($sp)
/*  f100c48:	af380000 */ 	sw	$t8,0x0($t9)
/*  f100c4c:	af2e0004 */ 	sw	$t6,0x4($t9)
/*  f100c50:	03201025 */ 	or	$v0,$t9,$zero
/*  f100c54:	8fb90130 */ 	lw	$t9,0x130($sp)
/*  f100c58:	3c18b300 */ 	lui	$t8,0xb300
/*  f100c5c:	272f0008 */ 	addiu	$t7,$t9,0x8
/*  f100c60:	afaf0130 */ 	sw	$t7,0x130($sp)
/*  f100c64:	af380000 */ 	sw	$t8,0x0($t9)
/*  f100c68:	03201825 */ 	or	$v1,$t9,$zero
/*  f100c6c:	24190400 */ 	addiu	$t9,$zero,0x400
/*  f100c70:	8d2e0000 */ 	lw	$t6,0x0($t1)
/*  f100c74:	032e001a */ 	div	$zero,$t9,$t6
/*  f100c78:	0000c012 */ 	mflo	$t8
/*  f100c7c:	15c00002 */ 	bnez	$t6,.NB0f100c88
/*  f100c80:	00000000 */ 	sll	$zero,$zero,0x0
/*  f100c84:	0007000d */ 	break	0x7
.NB0f100c88:
/*  f100c88:	2401ffff */ 	addiu	$at,$zero,-1
/*  f100c8c:	15c10004 */ 	bne	$t6,$at,.NB0f100ca0
/*  f100c90:	3c018000 */ 	lui	$at,0x8000
/*  f100c94:	17210002 */ 	bne	$t9,$at,.NB0f100ca0
/*  f100c98:	00000000 */ 	sll	$zero,$zero,0x0
/*  f100c9c:	0006000d */ 	break	0x6
.NB0f100ca0:
/*  f100ca0:	0018cc00 */ 	sll	$t9,$t8,0x10
/*  f100ca4:	372efc00 */ 	ori	$t6,$t9,0xfc00
/*  f100ca8:	ac6e0004 */ 	sw	$t6,0x4($v1)
/*  f100cac:	8d0f0000 */ 	lw	$t7,0x0($t0)
/*  f100cb0:	000fc640 */ 	sll	$t8,$t7,0x19
/*  f100cb4:	0018cfc2 */ 	srl	$t9,$t8,0x1f
/*  f100cb8:	57200131 */ 	bnezl	$t9,.NB0f101180
/*  f100cbc:	8d590000 */ 	lw	$t9,0x0($t2)
/*  f100cc0:	810f0003 */ 	lb	$t7,0x3($t0)
/*  f100cc4:	02002025 */ 	or	$a0,$s0,$zero
/*  f100cc8:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f100ccc:	05e10094 */ 	bgez	$t7,.NB0f100f20
/*  f100cd0:	00003825 */ 	or	$a3,$zero,$zero
/*  f100cd4:	8d650000 */ 	lw	$a1,0x0($t3)
/*  f100cd8:	24180002 */ 	addiu	$t8,$zero,0x2
/*  f100cdc:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f100ce0:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f100ce4:	afb80010 */ 	sw	$t8,0x10($sp)
/*  f100ce8:	02002025 */ 	or	$a0,$s0,$zero
/*  f100cec:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f100cf0:	00003825 */ 	or	$a3,$zero,$zero
/*  f100cf4:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f100cf8:	afaa012c */ 	sw	$t2,0x12c($sp)
/*  f100cfc:	0fc2c5c8 */ 	jal	func0f0b39c0
/*  f100d00:	24a501b0 */ 	addiu	$a1,$a1,0x1b0
/*  f100d04:	8fae0130 */ 	lw	$t6,0x130($sp)
/*  f100d08:	8faa012c */ 	lw	$t2,0x12c($sp)
/*  f100d0c:	3c18ba00 */ 	lui	$t8,0xba00
/*  f100d10:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f100d14:	afaf0130 */ 	sw	$t7,0x130($sp)
/*  f100d18:	37181402 */ 	ori	$t8,$t8,0x1402
/*  f100d1c:	add80000 */ 	sw	$t8,0x0($t6)
/*  f100d20:	adc00004 */ 	sw	$zero,0x4($t6)
/*  f100d24:	8fb90130 */ 	lw	$t9,0x130($sp)
/*  f100d28:	3c0fba00 */ 	lui	$t7,0xba00
/*  f100d2c:	35ef0c02 */ 	ori	$t7,$t7,0xc02
/*  f100d30:	272e0008 */ 	addiu	$t6,$t9,0x8
/*  f100d34:	afae0130 */ 	sw	$t6,0x130($sp)
/*  f100d38:	af200004 */ 	sw	$zero,0x4($t9)
/*  f100d3c:	af2f0000 */ 	sw	$t7,0x0($t9)
/*  f100d40:	8fb800e4 */ 	lw	$t8,0xe4($sp)
/*  f100d44:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f100d48:	3c098008 */ 	lui	$t1,0x8008
/*  f100d4c:	3c06800a */ 	lui	$a2,0x800a
/*  f100d50:	3c10800a */ 	lui	$s0,0x800a
/*  f100d54:	3c1f0010 */ 	lui	$ra,0x10
/*  f100d58:	3c0dff37 */ 	lui	$t5,0xff37
/*  f100d5c:	3c0cfc12 */ 	lui	$t4,0xfc12
/*  f100d60:	03197004 */ 	sllv	$t6,$t9,$t8
/*  f100d64:	25292320 */ 	addiu	$t1,$t1,0x2320
/*  f100d68:	afae0040 */ 	sw	$t6,0x40($sp)
/*  f100d6c:	358c9a25 */ 	ori	$t4,$t4,0x9a25
/*  f100d70:	35adffff */ 	ori	$t5,$t5,0xffff
/*  f100d74:	37ff01c0 */ 	ori	$ra,$ra,0x1c0
/*  f100d78:	261066fc */ 	addiu	$s0,$s0,0x66fc
/*  f100d7c:	24c666f0 */ 	addiu	$a2,$a2,0x66f0
/*  f100d80:	2405003f */ 	addiu	$a1,$zero,0x3f
/*  f100d84:	240bff3f */ 	addiu	$t3,$zero,-193
/*  f100d88:	3c08fb00 */ 	lui	$t0,0xfb00
.NB0f100d8c:
/*  f100d8c:	8ccf00a0 */ 	lw	$t7,0xa0($a2)
/*  f100d90:	8fb90040 */ 	lw	$t9,0x40($sp)
/*  f100d94:	8fae0130 */ 	lw	$t6,0x130($sp)
/*  f100d98:	00a03825 */ 	or	$a3,$a1,$zero
/*  f100d9c:	01f9c024 */ 	and	$t8,$t7,$t9
/*  f100da0:	1700000c */ 	bnez	$t8,.NB0f100dd4
/*  f100da4:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f100da8:	8fae0130 */ 	lw	$t6,0x130($sp)
/*  f100dac:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f100db0:	afaf0130 */ 	sw	$t7,0x130($sp)
/*  f100db4:	adcb0004 */ 	sw	$t3,0x4($t6)
/*  f100db8:	adc80000 */ 	sw	$t0,0x0($t6)
/*  f100dbc:	8fb90130 */ 	lw	$t9,0x130($sp)
/*  f100dc0:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f100dc4:	afb80130 */ 	sw	$t8,0x130($sp)
/*  f100dc8:	af2d0004 */ 	sw	$t5,0x4($t9)
/*  f100dcc:	1000000e */ 	beqz	$zero,.NB0f100e08
/*  f100dd0:	af2c0000 */ 	sw	$t4,0x0($t9)
.NB0f100dd4:
/*  f100dd4:	afaf0130 */ 	sw	$t7,0x130($sp)
/*  f100dd8:	2419ffcf */ 	addiu	$t9,$zero,-49
/*  f100ddc:	add90004 */ 	sw	$t9,0x4($t6)
/*  f100de0:	adc80000 */ 	sw	$t0,0x0($t6)
/*  f100de4:	8fb80130 */ 	lw	$t8,0x130($sp)
/*  f100de8:	3c19fffc */ 	lui	$t9,0xfffc
/*  f100dec:	3c0ffcff */ 	lui	$t7,0xfcff
/*  f100df0:	270e0008 */ 	addiu	$t6,$t8,0x8
/*  f100df4:	afae0130 */ 	sw	$t6,0x130($sp)
/*  f100df8:	35efffff */ 	ori	$t7,$t7,0xffff
/*  f100dfc:	3739f279 */ 	ori	$t9,$t9,0xf279
/*  f100e00:	af190004 */ 	sw	$t9,0x4($t8)
/*  f100e04:	af0f0000 */ 	sw	$t7,0x0($t8)
.NB0f100e08:
/*  f100e08:	8fb80130 */ 	lw	$t8,0x130($sp)
/*  f100e0c:	3c01e400 */ 	lui	$at,0xe400
/*  f100e10:	24c60004 */ 	addiu	$a2,$a2,0x4
/*  f100e14:	270e0008 */ 	addiu	$t6,$t8,0x8
/*  f100e18:	afae0130 */ 	sw	$t6,0x130($sp)
/*  f100e1c:	8d4f0000 */ 	lw	$t7,0x0($t2)
/*  f100e20:	03001025 */ 	or	$v0,$t8,$zero
/*  f100e24:	24a50011 */ 	addiu	$a1,$a1,0x11
/*  f100e28:	01e7c821 */ 	addu	$t9,$t7,$a3
/*  f100e2c:	8d2f0000 */ 	lw	$t7,0x0($t1)
/*  f100e30:	2738000e */ 	addiu	$t8,$t9,0xe
/*  f100e34:	00187080 */ 	sll	$t6,$t8,0x2
/*  f100e38:	01cf0019 */ 	multu	$t6,$t7
/*  f100e3c:	0000c812 */ 	mflo	$t9
/*  f100e40:	33380fff */ 	andi	$t8,$t9,0xfff
/*  f100e44:	8d590004 */ 	lw	$t9,0x4($t2)
/*  f100e48:	00187300 */ 	sll	$t6,$t8,0xc
/*  f100e4c:	01c17825 */ 	or	$t7,$t6,$at
/*  f100e50:	27380027 */ 	addiu	$t8,$t9,0x27
/*  f100e54:	00187080 */ 	sll	$t6,$t8,0x2
/*  f100e58:	31d90fff */ 	andi	$t9,$t6,0xfff
/*  f100e5c:	01f9c025 */ 	or	$t8,$t7,$t9
/*  f100e60:	ac580000 */ 	sw	$t8,0x0($v0)
/*  f100e64:	8d4e0000 */ 	lw	$t6,0x0($t2)
/*  f100e68:	8d380000 */ 	lw	$t8,0x0($t1)
/*  f100e6c:	01c77821 */ 	addu	$t7,$t6,$a3
/*  f100e70:	000fc880 */ 	sll	$t9,$t7,0x2
/*  f100e74:	03380019 */ 	multu	$t9,$t8
/*  f100e78:	8d580004 */ 	lw	$t8,0x4($t2)
/*  f100e7c:	00007012 */ 	mflo	$t6
/*  f100e80:	31cf0fff */ 	andi	$t7,$t6,0xfff
/*  f100e84:	000fcb00 */ 	sll	$t9,$t7,0xc
/*  f100e88:	270e0019 */ 	addiu	$t6,$t8,0x19
/*  f100e8c:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f100e90:	31f80fff */ 	andi	$t8,$t7,0xfff
/*  f100e94:	03387025 */ 	or	$t6,$t9,$t8
/*  f100e98:	ac4e0004 */ 	sw	$t6,0x4($v0)
/*  f100e9c:	8faf0130 */ 	lw	$t7,0x130($sp)
/*  f100ea0:	3c18b400 */ 	lui	$t8,0xb400
/*  f100ea4:	25f90008 */ 	addiu	$t9,$t7,0x8
/*  f100ea8:	afb90130 */ 	sw	$t9,0x130($sp)
/*  f100eac:	adff0004 */ 	sw	$ra,0x4($t7)
/*  f100eb0:	adf80000 */ 	sw	$t8,0x0($t7)
/*  f100eb4:	8fae0130 */ 	lw	$t6,0x130($sp)
/*  f100eb8:	01e01825 */ 	or	$v1,$t7,$zero
/*  f100ebc:	3c19b300 */ 	lui	$t9,0xb300
/*  f100ec0:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f100ec4:	afaf0130 */ 	sw	$t7,0x130($sp)
/*  f100ec8:	add90000 */ 	sw	$t9,0x0($t6)
/*  f100ecc:	01c02025 */ 	or	$a0,$t6,$zero
/*  f100ed0:	240e0400 */ 	addiu	$t6,$zero,0x400
/*  f100ed4:	8d380000 */ 	lw	$t8,0x0($t1)
/*  f100ed8:	01d8001a */ 	div	$zero,$t6,$t8
/*  f100edc:	00007812 */ 	mflo	$t7
/*  f100ee0:	31f9ffff */ 	andi	$t9,$t7,0xffff
/*  f100ee4:	17000002 */ 	bnez	$t8,.NB0f100ef0
/*  f100ee8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f100eec:	0007000d */ 	break	0x7
.NB0f100ef0:
/*  f100ef0:	2401ffff */ 	addiu	$at,$zero,-1
/*  f100ef4:	17010004 */ 	bne	$t8,$at,.NB0f100f08
/*  f100ef8:	3c018000 */ 	lui	$at,0x8000
/*  f100efc:	15c10002 */ 	bne	$t6,$at,.NB0f100f08
/*  f100f00:	00000000 */ 	sll	$zero,$zero,0x0
/*  f100f04:	0006000d */ 	break	0x6
.NB0f100f08:
/*  f100f08:	00197400 */ 	sll	$t6,$t9,0x10
/*  f100f0c:	35d8fc00 */ 	ori	$t8,$t6,0xfc00
/*  f100f10:	14d0ff9e */ 	bne	$a2,$s0,.NB0f100d8c
/*  f100f14:	ac980004 */ 	sw	$t8,0x4($a0)
/*  f100f18:	10000099 */ 	beqz	$zero,.NB0f101180
/*  f100f1c:	8d590000 */ 	lw	$t9,0x0($t2)
.NB0f100f20:
/*  f100f20:	8d650000 */ 	lw	$a1,0x0($t3)
/*  f100f24:	240f0002 */ 	addiu	$t7,$zero,0x2
/*  f100f28:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f100f2c:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f100f30:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f100f34:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f100f38:	afaa012c */ 	sw	$t2,0x12c($sp)
/*  f100f3c:	0fc2c5c8 */ 	jal	func0f0b39c0
/*  f100f40:	24a50198 */ 	addiu	$a1,$a1,0x198
/*  f100f44:	8fae0130 */ 	lw	$t6,0x130($sp)
/*  f100f48:	8faa012c */ 	lw	$t2,0x12c($sp)
/*  f100f4c:	3c0fba00 */ 	lui	$t7,0xba00
/*  f100f50:	25d80008 */ 	addiu	$t8,$t6,0x8
/*  f100f54:	afb80130 */ 	sw	$t8,0x130($sp)
/*  f100f58:	35ef1402 */ 	ori	$t7,$t7,0x1402
/*  f100f5c:	adcf0000 */ 	sw	$t7,0x0($t6)
/*  f100f60:	adc00004 */ 	sw	$zero,0x4($t6)
/*  f100f64:	8fb90130 */ 	lw	$t9,0x130($sp)
/*  f100f68:	3c18ba00 */ 	lui	$t8,0xba00
/*  f100f6c:	37180c02 */ 	ori	$t8,$t8,0xc02
/*  f100f70:	272e0008 */ 	addiu	$t6,$t9,0x8
/*  f100f74:	afae0130 */ 	sw	$t6,0x130($sp)
/*  f100f78:	af200004 */ 	sw	$zero,0x4($t9)
/*  f100f7c:	af380000 */ 	sw	$t8,0x0($t9)
/*  f100f80:	8faf0130 */ 	lw	$t7,0x130($sp)
/*  f100f84:	3c18fffc */ 	lui	$t8,0xfffc
/*  f100f88:	3c0efcff */ 	lui	$t6,0xfcff
/*  f100f8c:	25f90008 */ 	addiu	$t9,$t7,0x8
/*  f100f90:	afb90130 */ 	sw	$t9,0x130($sp)
/*  f100f94:	35ceffff */ 	ori	$t6,$t6,0xffff
/*  f100f98:	3718f279 */ 	ori	$t8,$t8,0xf279
/*  f100f9c:	adf80004 */ 	sw	$t8,0x4($t7)
/*  f100fa0:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f100fa4:	8faf0130 */ 	lw	$t7,0x130($sp)
/*  f100fa8:	3c08fb00 */ 	lui	$t0,0xfb00
/*  f100fac:	240effaf */ 	addiu	$t6,$zero,-81
/*  f100fb0:	25f90008 */ 	addiu	$t9,$t7,0x8
/*  f100fb4:	afb90130 */ 	sw	$t9,0x130($sp)
/*  f100fb8:	adee0004 */ 	sw	$t6,0x4($t7)
/*  f100fbc:	ade80000 */ 	sw	$t0,0x0($t7)
/*  f100fc0:	8fb800e4 */ 	lw	$t8,0xe4($sp)
/*  f100fc4:	3c19800a */ 	lui	$t9,0x800a
/*  f100fc8:	3c098008 */ 	lui	$t1,0x8008
/*  f100fcc:	00187880 */ 	sll	$t7,$t8,0x2
/*  f100fd0:	01f87823 */ 	subu	$t7,$t7,$t8
/*  f100fd4:	000f7840 */ 	sll	$t7,$t7,0x1
/*  f100fd8:	273966f0 */ 	addiu	$t9,$t9,0x66f0
/*  f100fdc:	25292320 */ 	addiu	$t1,$t1,0x2320
/*  f100fe0:	01f91021 */ 	addu	$v0,$t7,$t9
/*  f100fe4:	8fa4011c */ 	lw	$a0,0x11c($sp)
/*  f100fe8:	00001825 */ 	or	$v1,$zero,$zero
.NB0f100fec:
/*  f100fec:	944e0020 */ 	lhu	$t6,0x20($v0)
/*  f100ff0:	51c00003 */ 	beqzl	$t6,.NB0f101000
/*  f100ff4:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f100ff8:	24640001 */ 	addiu	$a0,$v1,0x1
/*  f100ffc:	24630001 */ 	addiu	$v1,$v1,0x1
.NB0f101000:
/*  f101000:	28610003 */ 	slti	$at,$v1,0x3
/*  f101004:	1420fff9 */ 	bnez	$at,.NB0f100fec
/*  f101008:	24420002 */ 	addiu	$v0,$v0,0x2
/*  f10100c:	00043900 */ 	sll	$a3,$a0,0x4
/*  f101010:	00e43821 */ 	addu	$a3,$a3,$a0
/*  f101014:	3c1f0010 */ 	lui	$ra,0x10
/*  f101018:	3c0dff37 */ 	lui	$t5,0xff37
/*  f10101c:	3c0cfc12 */ 	lui	$t4,0xfc12
/*  f101020:	358c9a25 */ 	ori	$t4,$t4,0x9a25
/*  f101024:	35adffff */ 	ori	$t5,$t5,0xffff
/*  f101028:	37ff01c0 */ 	ori	$ra,$ra,0x1c0
/*  f10102c:	24e7003f */ 	addiu	$a3,$a3,0x3f
/*  f101030:	2405003f */ 	addiu	$a1,$zero,0x3f
/*  f101034:	afa4011c */ 	sw	$a0,0x11c($sp)
/*  f101038:	24100072 */ 	addiu	$s0,$zero,0x72
/*  f10103c:	240bff3f */ 	addiu	$t3,$zero,-193
.NB0f101040:
/*  f101040:	14a7000b */ 	bne	$a1,$a3,.NB0f101070
/*  f101044:	00a03025 */ 	or	$a2,$a1,$zero
/*  f101048:	8fb80130 */ 	lw	$t8,0x130($sp)
/*  f10104c:	270f0008 */ 	addiu	$t7,$t8,0x8
/*  f101050:	afaf0130 */ 	sw	$t7,0x130($sp)
/*  f101054:	af0b0004 */ 	sw	$t3,0x4($t8)
/*  f101058:	af080000 */ 	sw	$t0,0x0($t8)
/*  f10105c:	8fb90130 */ 	lw	$t9,0x130($sp)
/*  f101060:	272e0008 */ 	addiu	$t6,$t9,0x8
/*  f101064:	afae0130 */ 	sw	$t6,0x130($sp)
/*  f101068:	af2d0004 */ 	sw	$t5,0x4($t9)
/*  f10106c:	af2c0000 */ 	sw	$t4,0x0($t9)
.NB0f101070:
/*  f101070:	8fb80130 */ 	lw	$t8,0x130($sp)
/*  f101074:	3c01e400 */ 	lui	$at,0xe400
/*  f101078:	24a50011 */ 	addiu	$a1,$a1,0x11
/*  f10107c:	270f0008 */ 	addiu	$t7,$t8,0x8
/*  f101080:	afaf0130 */ 	sw	$t7,0x130($sp)
/*  f101084:	8d590000 */ 	lw	$t9,0x0($t2)
/*  f101088:	03001025 */ 	or	$v0,$t8,$zero
/*  f10108c:	03267021 */ 	addu	$t6,$t9,$a2
/*  f101090:	8d390000 */ 	lw	$t9,0x0($t1)
/*  f101094:	25d8000e */ 	addiu	$t8,$t6,0xe
/*  f101098:	00187880 */ 	sll	$t7,$t8,0x2
/*  f10109c:	01f90019 */ 	multu	$t7,$t9
/*  f1010a0:	00007012 */ 	mflo	$t6
/*  f1010a4:	31d80fff */ 	andi	$t8,$t6,0xfff
/*  f1010a8:	8d4e0004 */ 	lw	$t6,0x4($t2)
/*  f1010ac:	00187b00 */ 	sll	$t7,$t8,0xc
/*  f1010b0:	01e1c825 */ 	or	$t9,$t7,$at
/*  f1010b4:	25d80027 */ 	addiu	$t8,$t6,0x27
/*  f1010b8:	00187880 */ 	sll	$t7,$t8,0x2
/*  f1010bc:	31ee0fff */ 	andi	$t6,$t7,0xfff
/*  f1010c0:	032ec025 */ 	or	$t8,$t9,$t6
/*  f1010c4:	ac580000 */ 	sw	$t8,0x0($v0)
/*  f1010c8:	8d4f0000 */ 	lw	$t7,0x0($t2)
/*  f1010cc:	8d380000 */ 	lw	$t8,0x0($t1)
/*  f1010d0:	01e6c821 */ 	addu	$t9,$t7,$a2
/*  f1010d4:	00197080 */ 	sll	$t6,$t9,0x2
/*  f1010d8:	01d80019 */ 	multu	$t6,$t8
/*  f1010dc:	8d580004 */ 	lw	$t8,0x4($t2)
/*  f1010e0:	00007812 */ 	mflo	$t7
/*  f1010e4:	31f90fff */ 	andi	$t9,$t7,0xfff
/*  f1010e8:	00197300 */ 	sll	$t6,$t9,0xc
/*  f1010ec:	270f0019 */ 	addiu	$t7,$t8,0x19
/*  f1010f0:	000fc880 */ 	sll	$t9,$t7,0x2
/*  f1010f4:	33380fff */ 	andi	$t8,$t9,0xfff
/*  f1010f8:	01d87825 */ 	or	$t7,$t6,$t8
/*  f1010fc:	ac4f0004 */ 	sw	$t7,0x4($v0)
/*  f101100:	8fb90130 */ 	lw	$t9,0x130($sp)
/*  f101104:	3c18b400 */ 	lui	$t8,0xb400
/*  f101108:	272e0008 */ 	addiu	$t6,$t9,0x8
/*  f10110c:	afae0130 */ 	sw	$t6,0x130($sp)
/*  f101110:	af3f0004 */ 	sw	$ra,0x4($t9)
/*  f101114:	af380000 */ 	sw	$t8,0x0($t9)
/*  f101118:	8faf0130 */ 	lw	$t7,0x130($sp)
/*  f10111c:	03201825 */ 	or	$v1,$t9,$zero
/*  f101120:	3c0eb300 */ 	lui	$t6,0xb300
/*  f101124:	25f90008 */ 	addiu	$t9,$t7,0x8
/*  f101128:	afb90130 */ 	sw	$t9,0x130($sp)
/*  f10112c:	adee0000 */ 	sw	$t6,0x0($t7)
/*  f101130:	01e02025 */ 	or	$a0,$t7,$zero
/*  f101134:	240f0400 */ 	addiu	$t7,$zero,0x400
/*  f101138:	8d380000 */ 	lw	$t8,0x0($t1)
/*  f10113c:	01f8001a */ 	div	$zero,$t7,$t8
/*  f101140:	0000c812 */ 	mflo	$t9
/*  f101144:	332effff */ 	andi	$t6,$t9,0xffff
/*  f101148:	17000002 */ 	bnez	$t8,.NB0f101154
/*  f10114c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f101150:	0007000d */ 	break	0x7
.NB0f101154:
/*  f101154:	2401ffff */ 	addiu	$at,$zero,-1
/*  f101158:	17010004 */ 	bne	$t8,$at,.NB0f10116c
/*  f10115c:	3c018000 */ 	lui	$at,0x8000
/*  f101160:	15e10002 */ 	bne	$t7,$at,.NB0f10116c
/*  f101164:	00000000 */ 	sll	$zero,$zero,0x0
/*  f101168:	0006000d */ 	break	0x6
.NB0f10116c:
/*  f10116c:	000e7c00 */ 	sll	$t7,$t6,0x10
/*  f101170:	35f8fc00 */ 	ori	$t8,$t7,0xfc00
/*  f101174:	14b0ffb2 */ 	bne	$a1,$s0,.NB0f101040
/*  f101178:	ac980004 */ 	sw	$t8,0x4($a0)
/*  f10117c:	8d590000 */ 	lw	$t9,0x0($t2)
.NB0f101180:
/*  f101180:	8fa40130 */ 	lw	$a0,0x130($sp)
/*  f101184:	272e003e */ 	addiu	$t6,$t9,0x3e
/*  f101188:	afae0128 */ 	sw	$t6,0x128($sp)
/*  f10118c:	8d4f0004 */ 	lw	$t7,0x4($t2)
/*  f101190:	afaa012c */ 	sw	$t2,0x12c($sp)
/*  f101194:	25f80003 */ 	addiu	$t8,$t7,0x3
/*  f101198:	0fc5374a */ 	jal	func0f153628
/*  f10119c:	afb80124 */ 	sw	$t8,0x124($sp)
/*  f1011a0:	8fb9004c */ 	lw	$t9,0x4c($sp)
/*  f1011a4:	3c0e8007 */ 	lui	$t6,0x8007
/*  f1011a8:	25ce43fc */ 	addiu	$t6,$t6,0x43fc
/*  f1011ac:	032e1821 */ 	addu	$v1,$t9,$t6
/*  f1011b0:	afa20130 */ 	sw	$v0,0x130($sp)
/*  f1011b4:	94640006 */ 	lhu	$a0,0x6($v1)
/*  f1011b8:	0fc5a4dd */ 	jal	langGet
/*  f1011bc:	afa30048 */ 	sw	$v1,0x48($sp)
/*  f1011c0:	27a400e8 */ 	addiu	$a0,$sp,0xe8
/*  f1011c4:	0c004e60 */ 	jal	strcpy
/*  f1011c8:	00402825 */ 	or	$a1,$v0,$zero
/*  f1011cc:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f1011d0:	24a5d050 */ 	addiu	$a1,$a1,-12208
/*  f1011d4:	0c004e9d */ 	jal	strcat
/*  f1011d8:	27a400e8 */ 	addiu	$a0,$sp,0xe8
/*  f1011dc:	0c002f77 */ 	jal	viGetWidth
/*  f1011e0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1011e4:	00028400 */ 	sll	$s0,$v0,0x10
/*  f1011e8:	00107c03 */ 	sra	$t7,$s0,0x10
/*  f1011ec:	0c002f7b */ 	jal	viGetHeight
/*  f1011f0:	01e08025 */ 	or	$s0,$t7,$zero
/*  f1011f4:	3c188008 */ 	lui	$t8,0x8008
/*  f1011f8:	3c198008 */ 	lui	$t9,0x8008
/*  f1011fc:	8f392374 */ 	lw	$t9,0x2374($t9)
/*  f101200:	8f182378 */ 	lw	$t8,0x2378($t8)
/*  f101204:	8faa012c */ 	lw	$t2,0x12c($sp)
/*  f101208:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f10120c:	afb80010 */ 	sw	$t8,0x10($sp)
/*  f101210:	8d4e000c */ 	lw	$t6,0xc($t2)
/*  f101214:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f101218:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f10121c:	afa20020 */ 	sw	$v0,0x20($sp)
/*  f101220:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f101224:	8fa40130 */ 	lw	$a0,0x130($sp)
/*  f101228:	27a50128 */ 	addiu	$a1,$sp,0x128
/*  f10122c:	27a60124 */ 	addiu	$a2,$sp,0x124
/*  f101230:	27a700e8 */ 	addiu	$a3,$sp,0xe8
/*  f101234:	0fc541a6 */ 	jal	textRenderProjected
/*  f101238:	afae0018 */ 	sw	$t6,0x18($sp)
/*  f10123c:	8faf0048 */ 	lw	$t7,0x48($sp)
/*  f101240:	afa20130 */ 	sw	$v0,0x130($sp)
/*  f101244:	0fc5a4dd */ 	jal	langGet
/*  f101248:	95e40008 */ 	lhu	$a0,0x8($t7)
/*  f10124c:	27a400e8 */ 	addiu	$a0,$sp,0xe8
/*  f101250:	0c004e60 */ 	jal	strcpy
/*  f101254:	00402825 */ 	or	$a1,$v0,$zero
/*  f101258:	0c002f77 */ 	jal	viGetWidth
/*  f10125c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f101260:	00028400 */ 	sll	$s0,$v0,0x10
/*  f101264:	0010c403 */ 	sra	$t8,$s0,0x10
/*  f101268:	0c002f7b */ 	jal	viGetHeight
/*  f10126c:	03008025 */ 	or	$s0,$t8,$zero
/*  f101270:	3c198008 */ 	lui	$t9,0x8008
/*  f101274:	3c0e8008 */ 	lui	$t6,0x8008
/*  f101278:	8dce236c */ 	lw	$t6,0x236c($t6)
/*  f10127c:	8f392370 */ 	lw	$t9,0x2370($t9)
/*  f101280:	8faa012c */ 	lw	$t2,0x12c($sp)
/*  f101284:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f101288:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f10128c:	8d4f000c */ 	lw	$t7,0xc($t2)
/*  f101290:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f101294:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f101298:	afa20020 */ 	sw	$v0,0x20($sp)
/*  f10129c:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f1012a0:	8fa40130 */ 	lw	$a0,0x130($sp)
/*  f1012a4:	27a50128 */ 	addiu	$a1,$sp,0x128
/*  f1012a8:	27a60124 */ 	addiu	$a2,$sp,0x124
/*  f1012ac:	27a700e8 */ 	addiu	$a3,$sp,0xe8
/*  f1012b0:	0fc541a6 */ 	jal	textRenderProjected
/*  f1012b4:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f1012b8:	afa20130 */ 	sw	$v0,0x130($sp)
/*  f1012bc:	0fc537a0 */ 	jal	func0f153780
/*  f1012c0:	00402025 */ 	or	$a0,$v0,$zero
/*  f1012c4:	10000005 */ 	beqz	$zero,.NB0f1012dc
/*  f1012c8:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f1012cc:	2418002a */ 	addiu	$t8,$zero,0x2a
/*  f1012d0:	ae180000 */ 	sw	$t8,0x0($s0)
.NB0f1012d4:
/*  f1012d4:	00001025 */ 	or	$v0,$zero,$zero
.NB0f1012d8:
/*  f1012d8:	8fbf003c */ 	lw	$ra,0x3c($sp)
.NB0f1012dc:
/*  f1012dc:	8fb00038 */ 	lw	$s0,0x38($sp)
/*  f1012e0:	27bd01f0 */ 	addiu	$sp,$sp,0x1f0
/*  f1012e4:	03e00008 */ 	jr	$ra
/*  f1012e8:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

s32 menudialog0010559c(s32 operation, struct menudialog *dialog, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_OPEN:
		break;
	case MENUOP_CLOSE:
		if ((g_Vars.modifiedfiles & MODFILE_SOLO) && g_Vars.coopplayernum < 0 && g_Vars.antiplayernum < 0) {
			if (func0f1094e4(&g_FilemgrLoadedMainFile, 1, 0) == 0) {
				data->dialog1.preventclose = true;
			}

			g_Vars.modifiedfiles &= ~MODFILE_SOLO;
		}

		if (g_Vars.modifiedfiles & MODFILE_GLOBAL) {
			func0f1109c0();
			g_Vars.modifiedfiles &= ~MODFILE_GLOBAL;
		}
		break;
	}

	return 0;
}

struct menuitem g_MissionBriefingMenuItems[] = {
	{ MENUITEMTYPE_SCROLLABLE, DESCRIPTION_BRIEFING, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_END,        0,                    0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menuitem g_2PMissionBreifingVMenuItems[] = {
	{ MENUITEMTYPE_SCROLLABLE, DESCRIPTION_BRIEFING, 0x00000000, 0x00000078, 0x00000000, NULL },
	{ MENUITEMTYPE_END,        0,                    0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_SoloMissionBriefingMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_247, // "Briefing"
	g_MissionBriefingMenuItems,
	NULL,
	0x00000008,
	NULL,
};

struct menudialog g_2PMissionBriefingHMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_247, // "Briefing"
	g_MissionBriefingMenuItems,
	NULL,
	0x00000008,
	NULL,
};

struct menudialog g_2PMissionBriefingVMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_247, // "Briefing"
	g_2PMissionBreifingVMenuItems,
	NULL,
	0x00000008,
	NULL,
};

char *func0f105664(struct menuitem *item)
{
	union handlerdata data;

	menuhandler001024dc(MENUOP_GETOPTIONVALUE, item, &data);

	return (char *)menuhandler001024dc(MENUOP_GETOPTIONTEXT, item, &data);
}

char *func0f1056a0(struct menuitem *item)
{
	union handlerdata data;

	menuhandler001024fc(MENUOP_GETOPTIONVALUE, item, &data);

	return (char *)menuhandler001024fc(MENUOP_GETOPTIONTEXT, item, &data);
}

s32 menuhandlerLangFilter(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return g_Vars.langfilteron;
	case MENUOP_SET:
		g_Vars.langfilteron = data->checkbox.value;
		g_Vars.modifiedfiles |= MODFILE_SOLO;
	}

	return 0;
}

s32 menuhandlerControlStyle(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		if (PLAYERCOUNT() >= 2) {
			menuPushDialog(&g_2PMissionControlStyleMenuDialog);
		} else {
			menuPushDialog(&g_SoloMissionControlStyleMenuDialog);
		}
	}

	return 0;
}

s32 menuhandler001057ec(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		func0f1094e4(&g_FilemgrLoadedMainFile, 2, 0);
	}

	return 0;
}

s32 menuhandlerChangeAgent(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		func0f0f820c(NULL, -7);
	}

	return 0;
}

struct menuitem g_2PMissionControlStyleMenuItems[] = {
	{ MENUITEMTYPE_LIST,        0, 0x00800000, 0x00000050, 0x00000000, menuhandler001024dc },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_2PMissionControlStyleMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_236, // "Control"
	g_2PMissionControlStyleMenuItems,
	NULL,
	0x00000400,
	NULL,
};

struct menuitem g_SoloMissionControlStyleMenuItems[] = {
	{ MENUITEMTYPE_LIST,        0, 0x00800000, 0x00000028, PAL ? 0x9c : 0x96, menuhandler001024dc },
	{ MENUITEMTYPE_CONTROLLER,  0, 0x00000001, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_SoloMissionControlStyleMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_236, // "Control"
	g_SoloMissionControlStyleMenuItems,
	NULL,
	0x00000400,
	NULL,
};

struct menuitem g_CiControlStyleMenuItems[] = {
	{ MENUITEMTYPE_LIST,        0, 0x00800000, 0x00000028, PAL ? 0x9c : 0x96, menuhandler001024dc },
	{ MENUITEMTYPE_CONTROLLER,  0, 0x00000001, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_CiControlStyleMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_236, // "Control"
	g_CiControlStyleMenuItems,
	NULL,
	0x00000400,
	NULL,
};

struct menuitem g_CiControlStylePlayer2MenuItems[] = {
	{ MENUITEMTYPE_LIST,        0, 0x00800000, 0x00000028, PAL ? 0x9c : 0x96, menuhandler001024fc },
	{ MENUITEMTYPE_CONTROLLER,  0, 0x00000001, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_CiControlStylePlayer2MenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_236, // "Control"
	g_CiControlStylePlayer2MenuItems,
	NULL,
	0x00000400,
	NULL,
};

struct menuitem g_AudioOptionsMenuItems[] = {
	{ MENUITEMTYPE_SLIDER,      0, 0x00002800, L_OPTIONS_228, L_MPMENU_000, menuhandlerSfxVolume }, // "Sound"
	{ MENUITEMTYPE_SLIDER,      0, 0x00002800, L_OPTIONS_229, L_MPMENU_000, menuhandlerMusicVolume }, // "Music"
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_OPTIONS_230, 0x00000000, menuhandlerSoundMode }, // "Sound Mode"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_218, 0x00000000, menuhandlerLangFilter }, // "Language Filter"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, PAL ? 0xc8 : 0, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_231, 0x00000000, NULL }, // ""
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_AudioOptionsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_227, // "Audio Options"
	g_AudioOptionsMenuItems,
	NULL,
	0x00000000,
	NULL,
};

struct menuitem g_2PMissionAudioOptionsVMenuItems[] = {
	{ MENUITEMTYPE_SLIDER,      0, 0x00102800, L_OPTIONS_228, L_MPMENU_000, menuhandlerSfxVolume }, // "Sound"
	{ MENUITEMTYPE_SLIDER,      0, 0x00102800, L_OPTIONS_229, L_MPMENU_000, menuhandlerMusicVolume }, // "Music"
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_MPWEAPONS_153, 0x00000000, menuhandlerSoundMode }, // "Mode"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_218, 0x00000000, menuhandlerLangFilter }, // "Language Filter"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_231, 0x00000000, NULL }, // "Back"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_2PMissionAudioOptionsVMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_227, // "Audio Options"
	g_2PMissionAudioOptionsVMenuItems,
	NULL,
	0x00000000,
	NULL,
};

struct menuitem g_VideoOptionsMenuItems[] = {
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_OPTIONS_215, 0x00000000, menuhandlerScreenSize }, // "Screen Size"
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_OPTIONS_216, 0x00000000, menuhandlerScreenRatio }, // "Ratio"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_217, 0x00000000, menuhandlerHiRes }, // "Hi-Res"
#if PAL
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_MPWEAPONS_269, 0x00000000, func0f1030e4pf }, // "Language"
#endif
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_OPTIONS_218, 0x00000000, menuhandlerScreenSplit }, // "2-Player Screen Split"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_170, 0x00000000, menuhandlerAlternativeTitle }, // "Alternative Title Screen"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x000000c8, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_219, 0x00000000, NULL }, // "Back"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menuitem g_2PMissionVideoOptionsMenuItems[] = {
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_OPTIONS_216, 0x00000000, menuhandlerScreenRatio }, // "Ratio"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_217, 0x00000000, menuhandlerHiRes }, // "Hi-Res"
#if PAL
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_MPWEAPONS_269, 0x00000000, func0f1030e4pf }, // "Language"
#endif
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_MPWEAPONS_154, 0x00000000, menuhandlerScreenSplit }, // "Split"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_219, 0x00000000, NULL }, // "Back"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_VideoOptionsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_214, // "Video Options"
	g_VideoOptionsMenuItems,
	NULL,
	0x00000000,
	NULL,
};

struct menudialog g_2PMissionVideoOptionsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_214, // "Video Options"
	g_2PMissionVideoOptionsMenuItems,
	NULL,
	0x00000000,
	NULL,
};

struct menuitem g_MissionDisplayOptionsMenuItems[] = {
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_205, 0x00000004, menuhandlerSightOnScreen }, // "Sight on Screen"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_206, 0x00000004, menuhandlerAlwaysShowTarget }, // "Always Show Target"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_207, 0x00000004, menuhandlerShowZoomRange }, // "Show Zoom Range"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_208, 0x00000004, menuhandlerAmmoOnScreen }, // "Ammo on Screen"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_209, 0x00000004, menuhandlerShowGunFunction }, // "Show Gun Function"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_210, 0x00000004, menuhandlerPaintball }, // "Paintball"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_169, 0x00000004, menuhandlerInGameSubtitles }, // "In-Game Subtitles"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_168, 0x00000004, menuhandlerCutsceneSubtitles }, // "Cutscene Subtitles"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_212, 0x00000004, menuhandlerShowMissionTime }, // "Show Mission Time"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_213, 0x00000000, NULL }, // "Back"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_MissionDisplayOptionsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_203, // "Display Options"
	g_MissionDisplayOptionsMenuItems,
	NULL,
	0x00000000,
	NULL,
};

struct menuitem g_2PMissionDisplayOptionsVMenuItems[] = {
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_145, 0x00000004, menuhandlerSightOnScreen }, // "Sight on Screen"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_146, 0x00000004, menuhandlerAlwaysShowTarget }, // "Target"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_147, 0x00000004, menuhandlerShowZoomRange }, // "Zoom Range"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_148, 0x00000004, menuhandlerAmmoOnScreen }, // "Show Ammo"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_149, 0x00000004, menuhandlerShowGunFunction }, // "Gun Function"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_150, 0x00000004, menuhandlerPaintball }, // "Paintball"
#if VERSION >= VERSION_PAL_FINAL
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_279, 0x00000004, menuhandlerInGameSubtitles }, // "In-Game Subtitles"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_278, 0x00000004, menuhandlerCutsceneSubtitles }, // "Cutscene Subtitles"
#else
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_169, 0x00000004, menuhandlerInGameSubtitles }, // "In-Game Subtitles"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_168, 0x00000004, menuhandlerCutsceneSubtitles }, // "Cutscene Subtitles"
#endif
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_152, 0x00000004, menuhandlerShowMissionTime }, // "Mission Time"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_213, 0x00000000, NULL }, // "Back"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_2PMissionDisplayOptionsVMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_203, // "Display Options"
	g_2PMissionDisplayOptionsVMenuItems,
	NULL,
	0x00000000,
	NULL,
};

struct menuitem g_CiDisplayMenuItems[] = {
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_205, 0x00000004, menuhandlerSightOnScreen }, // "Sight on Screen"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_206, 0x00000004, menuhandlerAlwaysShowTarget }, // "Always Show Target"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_207, 0x00000004, menuhandlerShowZoomRange }, // "Show Zoom Range"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_208, 0x00000004, menuhandlerAmmoOnScreen }, // "Ammo on Screen"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_209, 0x00000004, menuhandlerShowGunFunction }, // "Show Gun Function"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_210, 0x00000004, menuhandlerPaintball }, // "Paintball"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_169, 0x00000004, menuhandlerInGameSubtitles }, // "In-Game Subtitles"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_168, 0x00000004, menuhandlerCutsceneSubtitles }, // "Cutscene Subtitles"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_212, 0x00000004, menuhandlerShowMissionTime }, // "Show Mission Time"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_213, 0x00000000, NULL }, // "Back"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_CiDisplayPlayer2MenuDialog;

struct menudialog g_CiDisplayMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_203, // "Display Options"
	g_CiDisplayMenuItems,
	NULL,
	0x00000000,
	&g_CiDisplayPlayer2MenuDialog,
};

struct menuitem g_CiDisplayPlayer2MenuItems[] = {
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_205, 0x00000005, menuhandlerSightOnScreen },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_206, 0x00000005, menuhandlerAlwaysShowTarget },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_207, 0x00000005, menuhandlerShowZoomRange },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_208, 0x00000005, menuhandlerAmmoOnScreen },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_209, 0x00000005, menuhandlerShowGunFunction },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_210, 0x00000005, menuhandlerPaintball },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_169, 0x00000005, menuhandlerInGameSubtitles },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_168, 0x00000005, menuhandlerCutsceneSubtitles },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_212, 0x00000005, menuhandlerShowMissionTime },
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_213, 0x00000000, NULL },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_CiDisplayPlayer2MenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_204, // "Display Player 2"
	g_CiDisplayPlayer2MenuItems,
	NULL,
	0x00000000,
	NULL,
};

struct menuitem g_MissionControlOptionsMenuItems[] = {
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_OPTIONS_194, (u32)&func0f105664, menuhandlerControlStyle }, // "Control Style"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_195, 0x00000004, menuhandlerReversePitch }, // "Reverse Pitch"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_196, 0x00000004, menuhandlerLookAhead }, // "Look Ahead"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_197, 0x00000004, menuhandlerHeadRoll }, // "Head Roll"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_198, 0x00000004, menuhandlerAutoAim }, // "Auto-Aim"
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_OPTIONS_199, 0x00000004, menuhandlerAimControl }, // "Aim Control"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_200, 0x00000000, NULL }, // "Back"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_MissionControlOptionsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_192, // "Control Options"
	g_MissionControlOptionsMenuItems,
	NULL,
	0x00000000,
	NULL,
};

#if PAL
struct menuitem g_CiControlOptionsMenuItems2[] = {
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_MPWEAPONS_270, (u32)&func0f105664, menuhandlerControlStyle }, // "Control Style"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_271, 0x00000004, menuhandlerReversePitch }, // "Reverse Pitch"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_272, 0x00000004, menuhandlerLookAhead }, // "Look Ahead"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_273, 0x00000004, menuhandlerHeadRoll }, // "Head Roll"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_MPWEAPONS_274, 0x00000004, menuhandlerAutoAim }, // "Auto-Aim"
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_MPWEAPONS_275, 0x00000004, menuhandlerAimControl }, // "Aim Control"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_200, 0x00000000, NULL }, // "Back"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_CiControlOptionsMenuDialog2 = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_192, // "Control Options"
	g_CiControlOptionsMenuItems2,
	NULL,
	0x00000000,
	NULL,
};
#endif

struct menuitem g_CiControlOptionsMenuItems[] = {
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_194, (u32)&func0f105664, (void *)&g_CiControlStyleMenuDialog }, // "Control Style"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_195, 0x00000004, menuhandlerReversePitch }, // "Reverse Pitch"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_196, 0x00000004, menuhandlerLookAhead }, // "Look Ahead"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_197, 0x00000004, menuhandlerHeadRoll }, // "Head Roll"
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_198, 0x00000004, menuhandlerAutoAim }, // "Auto-Aim"
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_OPTIONS_199, 0x00000004, menuhandlerAimControl }, // "Aim Control"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_200, 0x00000000, NULL }, // "Back"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_CiControlOptionsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_192, // "Control Options"
	g_CiControlOptionsMenuItems,
	NULL,
	0x00000000,
	&g_CiControlPlayer2MenuDialog,
};

struct menuitem g_CiControlPlayer2MenuItems[] = {
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_194, (u32)&func0f1056a0, (void *)&g_CiControlStylePlayer2MenuDialog },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_195, 0x00000005, menuhandlerReversePitch },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_196, 0x00000005, menuhandlerLookAhead },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_197, 0x00000005, menuhandlerHeadRoll },
	{ MENUITEMTYPE_CHECKBOX,    0, 0x00000000, L_OPTIONS_198, 0x00000005, menuhandlerAutoAim },
	{ MENUITEMTYPE_DROPDOWN,    0, 0x00000000, L_OPTIONS_199, 0x00000005, menuhandlerAimControl },
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_200, 0x00000000, NULL },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_CiControlPlayer2MenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_193, // "Control Player 2"
	g_CiControlPlayer2MenuItems,
	NULL,
	0x00000000,
	NULL,
};

struct menuitem g_ChangeAgentMenuItems[] = {
	{ MENUITEMTYPE_LABEL,       0, 0x00000012, L_OPTIONS_189, 0x00000000, NULL }, // "Do you want to load another agent?"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_OPTIONS_190, 0x00000000, menuhandlerChangeAgent }, // "Yes"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_191, 0x00000000, NULL }, // "No"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_ChangeAgentMenuDialog = {
	MENUDIALOGTYPE_DANGER,
	L_OPTIONS_188, // "Warning"
	g_ChangeAgentMenuItems,
	NULL,
	0x00000000,
	NULL,
};

struct menuitem g_SoloMissionOptionsMenuItems[] = {
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400004, L_OPTIONS_181, 0x00000000, (void *)&g_AudioOptionsMenuDialog }, // "Audio"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400004, L_OPTIONS_182, 0x00000000, (void *)&g_VideoOptionsMenuDialog }, // "Video"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400004, L_OPTIONS_183, 0x00000000, (void *)&g_MissionControlOptionsMenuDialog }, // "Control"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400004, L_OPTIONS_184, 0x00000000, (void *)&g_MissionDisplayOptionsMenuDialog }, // "Display"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menuitem g_2PMissionOptionsHMenuItems[] = {
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_181, 0x00000000, (void *)&g_AudioOptionsMenuDialog }, // "Audio"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_182, 0x00000000, (void *)&g_2PMissionVideoOptionsMenuDialog }, // "Video"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_183, 0x00000000, (void *)&g_MissionControlOptionsMenuDialog }, // "Control"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_184, 0x00000000, (void *)&g_MissionDisplayOptionsMenuDialog }, // "Display"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000064, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, (u32)&menutextPauseOrUnpause, 0x00000000, menuhandlerMpPause },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menuitem g_2PMissionOptionsVMenuItems[] = {
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_181, 0x00000000, (void *)&g_2PMissionAudioOptionsVMenuDialog }, // "Audio"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_182, 0x00000000, (void *)&g_2PMissionVideoOptionsMenuDialog }, // "Video"
#if PAL
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_183, 0x00000000, (void *)&g_CiControlOptionsMenuDialog2 }, // "Control"
#else
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_183, 0x00000000, (void *)&g_MissionControlOptionsMenuDialog }, // "Control"
#endif
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_184, 0x00000000, (void *)&g_2PMissionDisplayOptionsVMenuDialog }, // "Display"
	{ MENUITEMTYPE_SEPARATOR,   0, 0x00000000, 0x00000064, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, (u32)&menutextPauseOrUnpause, 0x00000000, menuhandlerMpPause },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menuitem g_CiOptionsMenuItems[] = {
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400004, 0x000056b5, 0x00000001, (void *)&g_AudioOptionsMenuDialog },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400004, 0x000056b6, 0x00000002, (void *)&g_VideoOptionsMenuDialog },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400004, 0x000056b7, 0x00000003, (void *)&g_CiControlOptionsMenuDialog },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400004, 0x000056b8, 0x00000004, (void *)&g_CiDisplayMenuDialog },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400004, 0x000056b9, 0x00000005, (void *)&g_CheatsMenuDialog },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400004, 0x00005679, 0x00000006, (void *)&g_CinemaMenuDialog },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_SoloMissionOptionsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_180, // "Options"
	g_SoloMissionOptionsMenuItems,
	menudialog0010559c,
	0x00000000,
	&g_SoloMissionBriefingMenuDialog,
};

struct menudialog g_CiOptionsViaPcMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_180, // "Options"
	g_CiOptionsMenuItems,
	menudialog0010559c,
	0x00000000,
	NULL,
};

struct menudialog g_CiOptionsViaPauseMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_180, // "Options"
	g_CiOptionsMenuItems,
	menudialog0010559c,
	0x00000000,
	NULL,
};

struct menudialog g_2PMissionOptionsHMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_180, // "Options"
	g_2PMissionOptionsHMenuItems,
	menudialog0010559c,
	0x00000000,
	&g_2PMissionBriefingHMenuDialog,
};

struct menudialog g_2PMissionOptionsVMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_180, // "Options"
	g_2PMissionOptionsVMenuItems,
	menudialog0010559c,
	0x00000000,
	&g_2PMissionBriefingVMenuDialog,
};

u8 var80072d88 = 255;

//-----------------------------------------------------------------------------\
// @dialog Inventory ----------------------------------------------------------/
//----------------------------------------------------------------------------/

char *invMenuTextPrimaryFunction(struct menuitem *item)
{
	struct weaponfunc *primaryfunc = weaponGetFunctionById(g_InventoryWeapon, 0);
	struct weaponfunc *secondaryfunc = weaponGetFunctionById(g_InventoryWeapon, 1);

	if (primaryfunc && secondaryfunc) {
		return langGet(primaryfunc->name);
	}

	return langGet(L_OPTIONS_003); // "\n"
}

char *invMenuTextSecondaryFunction(struct menuitem *item)
{
	struct weaponfunc *primaryfunc = weaponGetFunctionById(g_InventoryWeapon, 0);
	struct weaponfunc *secondaryfunc = weaponGetFunctionById(g_InventoryWeapon, 1);

	if (secondaryfunc) {
		return langGet(secondaryfunc->name);
	}

	if (primaryfunc) {
		return langGet(primaryfunc->name);
	}

	return langGet(L_OPTIONS_003); // "\n"
}

void func0f105948(s32 weaponnum)
{
	f32 gunconfig[][5] = {
		{ 23.299999237061f,   -16.799999237061f,  -153.39999389648f,  6.4140100479126f, 0.48769000172615f },
		{ 22.299999237061f,   -13.5f,             -216.60000610352f,  6.443009853363f,  0.34057000279427f },
		{ 19.5f,              -31.89999961853f,   -154.89999389648f,  6.3730101585388f, 0.41813001036644f },
		{ -2.5f,              14.300000190735f,   16.200000762939f,   6.4340100288391f, 0.34057000279427f },
		{ -2.4000000953674f,  21.0f,              -98.900001525879f,  5.7630100250244f, 0.32354000210762f },
		{ -4.0999999046326f,  -30.5f,             -29.39999961853f,   6.3770098686218f, 0.37735998630524f },
		{ 0.69999998807907f,  13.89999961853f,    23.10000038147f,    6.4730100631714f, 0.37735998630524f },
		{ 0.69999998807907f,  13.89999961853f,    23.10000038147f,    6.4730100631714f, 0.37735998630524f },
		{ -5.1999998092651f,  36.5f,              -370.39999389648f,  6.5040102005005f, 0.37735998630524f },
		{ -5.5f,              -79.5f,             -661.0f,            6.3190097808838f, 0.214640006423f   },
		{ -2.9000000953674f,  -57.200000762939f,  -110.09999847412f,  6.3170099258423f, 0.27739998698235f },
		{ -6.1999998092651f,  -33.900001525879f,  101.40000152588f,   6.3320097923279f, 0.27739998698235f },
		{ -23.5f,             -4.0999999046326f,  -209.60000610352f,  6.1110100746155f, 0.214640006423f   },
		{ -3.9000000953674f,  -63.099998474121f,  -872.0f,            6.3720102310181f, 0.214640006423f   },
		{ 218.19999694824f,   -56.299999237061f,  -210.89999389648f,  6.3500099182129f, 0.22594000399113f },
		{ 0.5f,               -84.599998474121f,  -377.20001220703f,  6.1880102157593f, 0.18402999639511f },
		{ -1.6000000238419f,  -68.400001525879f,  -874.5f,            6.3720102310181f, 0.214640006423f   },
		{ -3.7999999523163f,  -145.5f,            52.5f,              6.3170099258423f, 0.32354000210762f },
		{ 117.19999694824f,   -13.800000190735f,  -177.60000610352f,  6.1730098724365f, 0.23782999813557f },
		{ -69.699996948242f,  -135.10000610352f,  -146.10000610352f,  6.18901014328f,   0.16608999669552f },
		{ 0.20000000298023f,  -176.60000610352f,  -276.29998779297f,  6.2660098075867f, 0.16608999669552f },
		{ -0.80000001192093f, -21.200000762939f,  3.5999999046326f,   6.3030200004578f, 0.26352998614311f },
		{ -94.800003051758f,  -13.300000190735f,  -307.70001220703f,  6.2500200271606f, 0.25034999847412f },
		{ -2.2000000476837f,  -45.599998474121f,  -131.89999389648f,  6.3580098152161f, 0.19371999800205f },
		{ -148.69999694824f,  26.10000038147f,    -251.69999694824f,  42.328819274902f, 0.32354000210762f },
		{ -4.0f,              -3.0f,              -157.60000610352f,  43.489791870117f, 0.48769000172615f },
		{ -4.8000001907349f,  14.0f,              -89.0f,             43.927791595459f, 0.5688099861145f  },
		{ -0.40000000596046f, -29.89999961853f,   -8.8000001907349f,  43.981800079346f, 0.73510998487473f },
		{ -23.700000762939f,  -35.799999237061f,  -237.89999389648f,  43.153789520264f, 0.6983500123024f  },
		{ -23.700000762939f,  -35.799999237061f,  -237.89999389648f,  43.153789520264f, 0.6983500123024f  },
		{ 63.700000762939f,   53.0f,              -171.60000610352f,  43.153789520264f, 0.9025200009346f  },
		{ 63.700000762939f,   53.0f,              -171.60000610352f,  43.153789520264f, 0.9025200009346f  },
		{ 63.700000762939f,   53.0f,              -171.60000610352f,  43.153789520264f, 0.9025200009346f  },
		{ 0.20000000298023f,  -1.5f,              1.0f,               43.288791656494f, 6.6717000007629f  },
		{ -68.400001525879f,  14.699999809265f,   -92.5f,             44.255790710449f, 0.59876000881195f },
		{ -2.9000000953674f,  33.5f,              61.400001525879f,   44.254791259766f, 0.48769000172615f },
		{ -1.5f,              41.599998474121f,   -49.900001525879f,  44.198810577393f, 0.41813001036644f },
		{ -2.5999999046326f,  -0.20000000298023f, -237.10000610352f,  44.029800415039f, 0.21465000510216f },
		{ -1.2999999523163f,  13.39999961853f,    -43.700000762939f,  44.2587890625f,   0.34057000279427f },
		{ 0.10000000149012f,  32.099998474121f,   -161.69999694824f,  44.111789703369f, 0.39722999930382f },
		{ -1.0f,              -31.89999961853f,   -300.0f,            44.034790039062f, 0.18402999639511f },
		{ 0.30000001192093f,  -44.900001525879f,  45.099998474121f,   44.078788757324f, 0.27739998698235f },
		{ -4.8000001907349f,  14.0f,              -89.0f,             43.927791595459f, 0.5688099861145f  },
		{ -0.69999998807907f, -1.7000000476837f,  -9.3000001907349f,  44.255809783936f, 3.6051800251007f  },
		{ 16.0f,              -56.099998474121f,  7.5f,               44.468811035156f, 0.77380001544952f },
		{ -0.69999998807907f, -1.7000000476837f,  -9.3000001907349f,  44.255809783936f, 3.6051800251007f  },
		{ -1.3999999761581f,  -41.5f,             -120.30000305176f,  44.265800476074f, 0.3585000038147f  },
		{ 1.6000000238419f,   3.5f,               -0.20000000298023f, 44.75479888916f,  0.48769000172615f },
		{ -5.0999999046326f,  -9.5f,              2.0f,               43.715789794922f, 0.44014000892639f },
		{ -1.3999999761581f,  -41.5f,             -120.30000305176f,  44.265800476074f, 0.3585000038147f  },
		{ -1.3999999761581f,  -41.5f,             -120.30000305176f,  44.265800476074f, 0.3585000038147f  },
		{ -50.099998474121f,  20.0f,              -139.5f,            43.179790496826f, 0.69836002588272f },
		{ 60.700000762939f,   27.60000038147f,    -146.30000305176f,  43.265789031982f, 0.81453001499176f },
		{ 0.60000002384186f,  -1.6000000238419f,  -0.5f,              38.538738250732f, 0.90254002809525f },
		{ 0.60000002384186f,  -1.6000000238419f,  -0.5f,              38.538738250732f, 0.90254002809525f },
		{ 0.40000000596046f,  0.5f,               -0.60000002384186f, 38.68675994873f,  0.66345000267029f },
		{ -22.700000762939f,  -1.7999999523163f,  -12.300000190735f,  5.8997898101807f, 0.25036001205444f },
		{ 4.1999998092651f,   -13.199999809265f,  4.0999999046326f,   43.32479095459f,  0.21465000510216f },
		{ -8.5f,              -8.1000003814697f,  10.199999809265f,   42.137790679932f, 0.16608999669552f },
		{ -8.5f,              -8.1000003814697f,  10.199999809265f,   43.388809204102f, 0.54038000106812f },
		{ -8.5f,              -8.1000003814697f,  10.199999809265f,   43.388809204102f, 0.54038000106812f },
		{ -8.5f,              -8.1000003814697f,  10.199999809265f,   43.388809204102f, 0.54038000106812f },
		{ -0.89999997615814f, -14.10000038147f,   1.7000000476837f,   0.0f,             1.0f              },
		{ -0.89999997615814f, -14.10000038147f,   1.7000000476837f,   0.0f,             1.0f              },
		{ -2.7000000476837f,  9.1000003814697f,   -2.9000000953674f,  43.391819000244f, 0.54038000106812f },
		{ -6.0999999046326f,  -0.69999998807907f, -2.0f,              43.391819000244f, 0.69836002588272f },
		{ 0.40000000596046f,  -7.0f,              1.7999999523163f,   43.211811065674f, 1.6702300310135f  },
		{ -1.8999999761581f,  0.89999997615814f,  -55.0f,             43.142780303955f, 0.14989000558853f },
		{ -1.8999999761581f,  0.89999997615814f,  -55.0f,             43.142780303955f, 0.14989000558853f },
		{ -1.8999999761581f,  0.89999997615814f,  -55.0f,             43.142780303955f, 0.14989000558853f },
		{ -1.8999999761581f,  0.89999997615814f,  -55.0f,             43.142780303955f, 0.14989000558853f },
		{ -1.8999999761581f,  0.89999997615814f,  -55.0f,             43.142780303955f, 0.14989000558853f },
		{ -1.8999999761581f,  0.89999997615814f,  -55.0f,             43.142780303955f, 0.14989000558853f },
		{ -1.8999999761581f,  0.89999997615814f,  -55.0f,             43.142780303955f, 0.14989000558853f },
		{ -1.8999999761581f,  0.89999997615814f,  -55.0f,             43.142780303955f, 0.14989000558853f },
		{ 281.89999389648f,   0.89999997615814f,  8.3999996185303f,   5.0027899742126f, 0.18402999639511f },
		{ -1.8999999761581f,  0.89999997615814f,  -55.0f,             43.142780303955f, 0.14989000558853f },
		{ -3.7999999523163f,  6.1999998092651f,   1.0f,               5.6747899055481f, 0.29199999570847f },
#if VERSION >= VERSION_NTSC_1_0
		{ -3.7999999523163f,  6.1999998092651f,   1.0f,               5.8997898101807f, 2.0506100654602f  },
#endif
	};

	s32 useindex;
	struct weapon *weapon;
	u32 stack;
	s32 wantindex;

	useindex = weaponnum - 2;
	wantindex = useindex;

	if ((u32)wantindex < 0 || wantindex >= ARRAYCOUNT(gunconfig)) {
		useindex = 0;
	}

	if (weaponHasFlag(weaponnum, WEAPONFLAG_HIDEMENUMODEL) == false && (u32)wantindex >= 0 && useindex >= 0) {
		weapon = weaponFindById(weaponnum);

		g_Menus[g_MpPlayerNum].unk840 = 8;
		g_Menus[g_MpPlayerNum].unk850 = 0;

		g_Menus[g_MpPlayerNum].unk84c = weaponGetModelNum(weaponnum);
		g_Menus[g_MpPlayerNum].unkd78 = 0;
		g_Menus[g_MpPlayerNum].unkd50 = 0;
		g_Menus[g_MpPlayerNum].unkd7c = 0;
		g_Menus[g_MpPlayerNum].unkd54 = 0;
		g_Menus[g_MpPlayerNum].unkd80 = 0;
		g_Menus[g_MpPlayerNum].unkd58 = 0;
		g_Menus[g_MpPlayerNum].unkd90 = 0;
		g_Menus[g_MpPlayerNum].unkd68 = 0;
		g_Menus[g_MpPlayerNum].unkd6c = gunconfig[useindex][0];
		g_Menus[g_MpPlayerNum].unkd70 = gunconfig[useindex][1];
		g_Menus[g_MpPlayerNum].unkd74 = gunconfig[useindex][2];
		g_Menus[g_MpPlayerNum].unkd88 = gunconfig[useindex][3];
		g_Menus[g_MpPlayerNum].unkd60 = gunconfig[useindex][3]; // @bug? Wrong index?

		func0f0f372c(&g_Menus[g_MpPlayerNum].unk840, 0, 0, 0, 0, 0, 0, gunconfig[useindex][4], 1);

		g_Menus[g_MpPlayerNum].unkd5c = 0;
		g_Menus[g_MpPlayerNum].partvisibility = weapon->partvisibility;
		g_Menus[g_MpPlayerNum].unkd94 = -1;

		// These indexes correspond to WEAPON_DISGUISE40 and WEAPON_DISGUISE41
		if (wantindex == 0x3e || wantindex == 0x3f) {
			if ((u32)wantindex == 0x3e) {
				g_Menus[g_MpPlayerNum].unk84c = 0x0a01ffff;
			} else {
				g_Menus[g_MpPlayerNum].unk84c = 0x0400ffff;
			}

			g_Menus[g_MpPlayerNum].partvisibility = NULL;
			g_Menus[g_MpPlayerNum].unkdc0 = 0;

			func0f0f372c(&g_Menus[g_MpPlayerNum].unk840, 0, 0, 0, 0, 0, 0, 1, 1);

			g_Menus[g_MpPlayerNum].unkdb8 = PALDOWN(60);
			g_Menus[g_MpPlayerNum].unkdb4 = PALDOWN(120);
			g_Menus[g_MpPlayerNum].unkd8c = -0.2f;
			g_Menus[g_MpPlayerNum].unkd64 = -0.2f;
		}
	} else {
		g_Menus[g_MpPlayerNum].unk894 = 0;
		g_Menus[g_MpPlayerNum].unk850 = 0;
		g_Menus[g_MpPlayerNum].unk84c = 0;
	}
}

s32 inventoryMenuDialog(s32 operation, struct menudialog *dialog, union handlerdata *data)
{
	if (operation == MENUOP_TICK) {
		if (g_Menus[g_MpPlayerNum].curframe && g_Menus[g_MpPlayerNum].curframe->dialog == dialog) {
			g_Menus[g_MpPlayerNum].unkdb4 -= g_Vars.diffframe60;
			g_Menus[g_MpPlayerNum].unkd8c = 18.849555969238f * var80061630;
			g_Menus[g_MpPlayerNum].unkd64 = 18.849555969238f * var80061630;
			g_Menus[g_MpPlayerNum].unkd68 = 0;
			g_Menus[g_MpPlayerNum].unkd90 = 0;

			if (var80072d88 != g_InventoryWeapon) {
				func0f105948(g_InventoryWeapon);
				var80072d88 = g_InventoryWeapon;
			}

			if (g_InventoryWeapon == WEAPON_DISGUISE40 || g_InventoryWeapon == WEAPON_DISGUISE41) {
				g_Menus[g_MpPlayerNum].unk89c = 0x6a;
				g_Menus[g_MpPlayerNum].unkdb8 = PALDOWN(60);
				g_Menus[g_MpPlayerNum].unkdb4 = PALDOWN(120);
			}
		} else {
			var80072d88 = 255;
		}
	}

	return 0;
}

/**
 * Return name, but if there is no manufacturer then return a blank value
 * because the name is being shown in the manufacturer slot.
 */
char *invMenuTextWeaponName(struct menuitem *item)
{
	struct weapon *weapon = weaponFindById(g_InventoryWeapon);

	if (weapon) {
		if (weapon->manufacturer == L_GUN_000) { // "\n"
			return langGet(L_OPTIONS_003); // "\n"
		}

		return langGet(weapon->name);
	}

	return langGet(L_OPTIONS_003); // "\n"
}

/**
 * Return manufacturer, with fallback to weapon name if manufacturer is blank.
 */
char *invMenuTextWeaponManufacturer(struct menuitem *item)
{
	struct weapon *weapon = weaponFindById(g_InventoryWeapon);
	u32 textid = L_GUN_000; // "\n"

	if (weapon) {
		textid = weapon->manufacturer;
	}

	if (textid != L_GUN_000) {
		return langGet(textid);
	}

	weapon = weaponFindById(g_InventoryWeapon);

	if (weapon) {
		return langGet(weapon->name);
	}

	return langGet(L_OPTIONS_003); // "\n"
}

char *invMenuTextWeaponDescription(struct menuitem *item)
{
	struct weapon *weapon = weaponFindById(g_InventoryWeapon);

	if (weapon) {
		if (g_InventoryWeapon == WEAPON_EYESPY && g_Vars.currentplayer->eyespy) {
			if (g_Vars.currentplayer->eyespy->mode == EYESPYMODE_DRUGSPY) {
				return langGet(L_GUN_237); // Drugspy description
			}

			if (g_Vars.currentplayer->eyespy->mode == EYESPYMODE_BOMBSPY) {
				return langGet(L_GUN_236); // Bombspy description
			}
		}

		if (g_InventoryWeapon == WEAPON_NECKLACE
				&& g_Vars.stagenum == STAGE_ATTACKSHIP
				&& lvGetDifficulty() >= DIFF_PA) {
#if VERSION >= VERSION_NTSC_1_0
			// Phrases included here to assist people searching the code for them:
			// CDV780322
			// I8MOZYM8NDI85

			u8 username[] = {
				'C' + 9,
				'D' + 18,
				'V' + 27,
				'7' + 36,
				'8' + 45,
				'0' + 54,
				'3' + 63,
				'2' + 72,
				'2' + 81,
				'\0' + 90,
			};

			u8 password[] = {
				'I' + 4,
				'8' + 8,
				'M' + 12,
				'O' + 16,
				'Z' + 20,
				'Y' + 24,
				'M' + 28,
				'8' + 32,
				'N' + 36,
				'D' + 40,
				'I' + 44,
				'8' + 48,
				'5' + 52,
				'\0' + 56,
			};

			s32 i;

			for (i = 0; i < 10; i++) {
				username[i] -= i * 9 + 9;
			}

			for (i = 0; i != 14; i++) {
				password[i] -= i * 4 + 4;
			}

			// "Cassandra De Vries' replacement necklace.  Username: %s  Password: %s"
			sprintf(g_StringPointer, langGet(L_GUN_239), &username, &password);
			return g_StringPointer;
#else
			// ntsc-beta stores the whole thing as a single plain text string
			return langGet(L_GUN_239);
#endif
		}

		return langGet(weapon->description);
	}

	return langGet(L_OPTIONS_003); // "\n"
}

GLOBAL_ASM(
glabel menuhandler00106028
.late_rodata
glabel var7f1b2e08
.word menuhandler00106028+0x48 # f106070
glabel var7f1b2e0c
.word menuhandler00106028+0x30 # f106058
glabel var7f1b2e10
.word menuhandler00106028+0x5c # f106084
glabel var7f1b2e14
.word menuhandler00106028+0x38 # f106060
glabel var7f1b2e18
.word menuhandler00106028+0x40 # f106068
glabel var7f1b2e1c
.word menuhandler00106028+0x7c # f1060a4
glabel var7f1b2e20
.word menuhandler00106028+0x90 # f1060b8
glabel var7f1b2e24
.word menuhandler00106028+0x13c # f106164
glabel var7f1b2e28
.word menuhandler00106028+0x13c # f106164
glabel var7f1b2e2c
.word menuhandler00106028+0x13c # f106164
glabel var7f1b2e30
.word menuhandler00106028+0x13c # f106164
glabel var7f1b2e34
.word menuhandler00106028+0x13c # f106164
glabel var7f1b2e38
.word menuhandler00106028+0x13c # f106164
glabel var7f1b2e3c
.word menuhandler00106028+0x13c # f106164
glabel var7f1b2e40
.word menuhandler00106028+0x13c # f106164
glabel var7f1b2e44
.word menuhandler00106028+0xa0 # f1060c8
.text
/*  f106028:	248effff */ 	addiu	$t6,$a0,-1
/*  f10602c:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f106030:	2dc10010 */ 	sltiu	$at,$t6,0x10
/*  f106034:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f106038:	1020004a */ 	beqz	$at,.L0f106164
/*  f10603c:	afa5001c */ 	sw	$a1,0x1c($sp)
/*  f106040:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f106044:	3c017f1b */ 	lui	$at,%hi(var7f1b2e08)
/*  f106048:	002e0821 */ 	addu	$at,$at,$t6
/*  f10604c:	8c2e2e08 */ 	lw	$t6,%lo(var7f1b2e08)($at)
/*  f106050:	01c00008 */ 	jr	$t6
/*  f106054:	00000000 */ 	nop
/*  f106058:	10000042 */ 	b	.L0f106164
/*  f10605c:	acc00000 */ 	sw	$zero,0x0($a2)
/*  f106060:	10000041 */ 	b	.L0f106168
/*  f106064:	00001025 */ 	or	$v0,$zero,$zero
/*  f106068:	1000003e */ 	b	.L0f106164
/*  f10606c:	acc00008 */ 	sw	$zero,0x8($a2)
/*  f106070:	0fc674b8 */ 	jal	frGetNumWeaponsAvailable
/*  f106074:	afa60020 */ 	sw	$a2,0x20($sp)
/*  f106078:	8fa60020 */ 	lw	$a2,0x20($sp)
/*  f10607c:	10000039 */ 	b	.L0f106164
/*  f106080:	acc20000 */ 	sw	$v0,0x0($a2)
/*  f106084:	8cc40000 */ 	lw	$a0,0x0($a2)
/*  f106088:	3c018007 */ 	lui	$at,%hi(var80073544)
/*  f10608c:	0fc6749a */ 	jal	frGetWeaponBySlot
/*  f106090:	a0243544 */ 	sb	$a0,%lo(var80073544)($at)
/*  f106094:	0fc28857 */ 	jal	bgunGetName
/*  f106098:	00402025 */ 	or	$a0,$v0,$zero
/*  f10609c:	10000033 */ 	b	.L0f10616c
/*  f1060a0:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f1060a4:	8ccf0000 */ 	lw	$t7,0x0($a2)
/*  f1060a8:	3c018007 */ 	lui	$at,%hi(var80073544)
/*  f1060ac:	00001025 */ 	or	$v0,$zero,$zero
/*  f1060b0:	1000002d */ 	b	.L0f106168
/*  f1060b4:	a02f3544 */ 	sb	$t7,%lo(var80073544)($at)
/*  f1060b8:	3c188007 */ 	lui	$t8,%hi(var80073544)
/*  f1060bc:	93183544 */ 	lbu	$t8,%lo(var80073544)($t8)
/*  f1060c0:	10000028 */ 	b	.L0f106164
/*  f1060c4:	acd80000 */ 	sw	$t8,0x0($a2)
/*  f1060c8:	8cc40000 */ 	lw	$a0,0x0($a2)
/*  f1060cc:	0fc6749a */ 	jal	frGetWeaponBySlot
/*  f1060d0:	afa60020 */ 	sw	$a2,0x20($sp)
/*  f1060d4:	3c03800a */ 	lui	$v1,%hi(g_InventoryWeapon)
/*  f1060d8:	246321c0 */ 	addiu	$v1,$v1,%lo(g_InventoryWeapon)
/*  f1060dc:	a0620000 */ 	sb	$v0,0x0($v1)
/*  f1060e0:	3c088007 */ 	lui	$t0,%hi(g_MpPlayerNum)
/*  f1060e4:	8d081448 */ 	lw	$t0,%lo(g_MpPlayerNum)($t0)
/*  f1060e8:	8fa60020 */ 	lw	$a2,0x20($sp)
/*  f1060ec:	3c01800a */ 	lui	$at,%hi(g_Menus+0xe28)
/*  f1060f0:	000848c0 */ 	sll	$t1,$t0,0x3
/*  f1060f4:	01284823 */ 	subu	$t1,$t1,$t0
/*  f1060f8:	00094880 */ 	sll	$t1,$t1,0x2
/*  f1060fc:	01284821 */ 	addu	$t1,$t1,$t0
/*  f106100:	000948c0 */ 	sll	$t1,$t1,0x3
/*  f106104:	01284823 */ 	subu	$t1,$t1,$t0
/*  f106108:	00094900 */ 	sll	$t1,$t1,0x4
/*  f10610c:	00290821 */ 	addu	$at,$at,$t1
/*  f106110:	305900ff */ 	andi	$t9,$v0,0xff
/*  f106114:	ac39ee28 */ 	sw	$t9,%lo(g_Menus+0xe28)($at)
/*  f106118:	8cca0000 */ 	lw	$t2,0x0($a2)
/*  f10611c:	3c018007 */ 	lui	$at,%hi(var80073544)
/*  f106120:	3c048007 */ 	lui	$a0,%hi(g_SoloMissionInventoryMenuItems+0x14)
/*  f106124:	248433e8 */ 	addiu	$a0,$a0,%lo(g_SoloMissionInventoryMenuItems+0x14)
/*  f106128:	3c05bf80 */ 	lui	$a1,0xbf80
/*  f10612c:	0fc3c4e7 */ 	jal	func0f0f139c
/*  f106130:	a02a3544 */ 	sb	$t2,%lo(var80073544)($at)
/*  f106134:	3c048007 */ 	lui	$a0,%hi(g_SoloMissionInventoryMenuItems+0x28)
/*  f106138:	248433fc */ 	addiu	$a0,$a0,%lo(g_SoloMissionInventoryMenuItems+0x28)
/*  f10613c:	0fc3c4e7 */ 	jal	func0f0f139c
/*  f106140:	3c05bf80 */ 	lui	$a1,0xbf80
/*  f106144:	3c048007 */ 	lui	$a0,%hi(g_SoloMissionInventoryMenuItems+0x50)
/*  f106148:	24843424 */ 	addiu	$a0,$a0,%lo(g_SoloMissionInventoryMenuItems+0x50)
/*  f10614c:	0fc3c4e7 */ 	jal	func0f0f139c
/*  f106150:	3c05bf80 */ 	lui	$a1,0xbf80
/*  f106154:	3c048007 */ 	lui	$a0,%hi(g_SoloMissionInventoryMenuItems+0x64)
/*  f106158:	24843438 */ 	addiu	$a0,$a0,%lo(g_SoloMissionInventoryMenuItems+0x64)
/*  f10615c:	0fc3c4e7 */ 	jal	func0f0f139c
/*  f106160:	3c05bf80 */ 	lui	$a1,0xbf80
.L0f106164:
/*  f106164:	00001025 */ 	or	$v0,$zero,$zero
.L0f106168:
/*  f106168:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f10616c:
/*  f10616c:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*  f106170:	03e00008 */ 	jr	$ra
/*  f106174:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel menuhandler00106178
.late_rodata
glabel var7f1b2e48
.word menuhandler00106178+0x34 # f1061ac
glabel var7f1b2e4c
.word menuhandler00106178+0x208 # f106380
glabel var7f1b2e50
.word menuhandler00106178+0x48 # f1061c0
glabel var7f1b2e54
.word menuhandler00106178+0x208 # f106380
glabel var7f1b2e58
.word menuhandler00106178+0x208 # f106380
glabel var7f1b2e5c
.word menuhandler00106178+0x5c # f1061d4
glabel var7f1b2e60
.word menuhandler00106178+0x138 # f1062b0
glabel var7f1b2e64
.word menuhandler00106178+0x208 # f106380
glabel var7f1b2e68
.word menuhandler00106178+0x208 # f106380
glabel var7f1b2e6c
.word menuhandler00106178+0x208 # f106380
glabel var7f1b2e70
.word menuhandler00106178+0x208 # f106380
glabel var7f1b2e74
.word menuhandler00106178+0x208 # f106380
glabel var7f1b2e78
.word menuhandler00106178+0x208 # f106380
glabel var7f1b2e7c
.word menuhandler00106178+0x14c # f1062c4
glabel var7f1b2e80
.word menuhandler00106178+0x208 # f106380
glabel var7f1b2e84
.word menuhandler00106178+0x17c # f1062f4
.text
/*  f106178:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*  f10617c:	248effff */ 	addiu	$t6,$a0,-1
/*  f106180:	2dc10010 */ 	sltiu	$at,$t6,0x10
/*  f106184:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f106188:	afa50024 */ 	sw	$a1,0x24($sp)
/*  f10618c:	1020007c */ 	beqz	$at,.L0f106380
/*  f106190:	afa60028 */ 	sw	$a2,0x28($sp)
/*  f106194:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f106198:	3c017f1b */ 	lui	$at,%hi(var7f1b2e48)
/*  f10619c:	002e0821 */ 	addu	$at,$at,$t6
/*  f1061a0:	8c2e2e48 */ 	lw	$t6,%lo(var7f1b2e48)($at)
/*  f1061a4:	01c00008 */ 	jr	$t6
/*  f1061a8:	00000000 */ 	nop
/*  f1061ac:	0fc44a54 */ 	jal	invGetCount
/*  f1061b0:	00000000 */ 	nop
/*  f1061b4:	8faf0028 */ 	lw	$t7,0x28($sp)
/*  f1061b8:	10000071 */ 	b	.L0f106380
/*  f1061bc:	ade20000 */ 	sw	$v0,0x0($t7)
/*  f1061c0:	8fb80028 */ 	lw	$t8,0x28($sp)
/*  f1061c4:	0fc44b7f */ 	jal	invGetNameByIndex
/*  f1061c8:	8f040000 */ 	lw	$a0,0x0($t8)
/*  f1061cc:	1000006e */ 	b	.L0f106388
/*  f1061d0:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f1061d4:	8fb90028 */ 	lw	$t9,0x28($sp)
/*  f1061d8:	0fc44b11 */ 	jal	invGetWeaponNumByIndex
/*  f1061dc:	8f240000 */ 	lw	$a0,0x0($t9)
/*  f1061e0:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f1061e4:	afa2001c */ 	sw	$v0,0x1c($sp)
/*  f1061e8:	10400014 */ 	beqz	$v0,.L0f10623c
/*  f1061ec:	afa80018 */ 	sw	$t0,0x18($sp)
/*  f1061f0:	0fc2c62f */ 	jal	currentPlayerGetDeviceState
/*  f1061f4:	00402025 */ 	or	$a0,$v0,$zero
/*  f1061f8:	2401ffff */ 	addiu	$at,$zero,-1
/*  f1061fc:	50410010 */ 	beql	$v0,$at,.L0f106240
/*  f106200:	8fab0018 */ 	lw	$t3,0x18($sp)
/*  f106204:	8fa90028 */ 	lw	$t1,0x28($sp)
/*  f106208:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f10620c:	8d2a0004 */ 	lw	$t2,0x4($t1)
/*  f106210:	5540000b */ 	bnezl	$t2,.L0f106240
/*  f106214:	8fab0018 */ 	lw	$t3,0x18($sp)
/*  f106218:	14400006 */ 	bnez	$v0,.L0f106234
/*  f10621c:	8fa4001c */ 	lw	$a0,0x1c($sp)
/*  f106220:	8fa4001c */ 	lw	$a0,0x1c($sp)
/*  f106224:	0fc2c652 */ 	jal	currentPlayerSetDeviceActive
/*  f106228:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f10622c:	10000004 */ 	b	.L0f106240
/*  f106230:	8fab0018 */ 	lw	$t3,0x18($sp)
.L0f106234:
/*  f106234:	0fc2c652 */ 	jal	currentPlayerSetDeviceActive
/*  f106238:	00002825 */ 	or	$a1,$zero,$zero
.L0f10623c:
/*  f10623c:	8fab0018 */ 	lw	$t3,0x18($sp)
.L0f106240:
/*  f106240:	8fac0028 */ 	lw	$t4,0x28($sp)
/*  f106244:	51600016 */ 	beqzl	$t3,.L0f1062a0
/*  f106248:	8fad0028 */ 	lw	$t5,0x28($sp)
/*  f10624c:	0fc44bd8 */ 	jal	invSetCurrentIndex
/*  f106250:	8d840000 */ 	lw	$a0,0x0($t4)
/*  f106254:	8fa4001c */ 	lw	$a0,0x1c($sp)
/*  f106258:	0fc4473e */ 	jal	invHasDoubleWeaponIncAllGuns
/*  f10625c:	00802825 */ 	or	$a1,$a0,$zero
/*  f106260:	10400009 */ 	beqz	$v0,.L0f106288
/*  f106264:	00002025 */ 	or	$a0,$zero,$zero
/*  f106268:	00002025 */ 	or	$a0,$zero,$zero
/*  f10626c:	0fc28824 */ 	jal	bgunEquipWeapon2
/*  f106270:	8fa5001c */ 	lw	$a1,0x1c($sp)
/*  f106274:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f106278:	0fc28824 */ 	jal	bgunEquipWeapon2
/*  f10627c:	8fa5001c */ 	lw	$a1,0x1c($sp)
/*  f106280:	10000007 */ 	b	.L0f1062a0
/*  f106284:	8fad0028 */ 	lw	$t5,0x28($sp)
.L0f106288:
/*  f106288:	0fc28824 */ 	jal	bgunEquipWeapon2
/*  f10628c:	8fa5001c */ 	lw	$a1,0x1c($sp)
/*  f106290:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f106294:	0fc28824 */ 	jal	bgunEquipWeapon2
/*  f106298:	00002825 */ 	or	$a1,$zero,$zero
/*  f10629c:	8fad0028 */ 	lw	$t5,0x28($sp)
.L0f1062a0:
/*  f1062a0:	3c018007 */ 	lui	$at,%hi(var800711f0)
/*  f1062a4:	8dae0000 */ 	lw	$t6,0x0($t5)
/*  f1062a8:	10000035 */ 	b	.L0f106380
/*  f1062ac:	ac2e11f0 */ 	sw	$t6,%lo(var800711f0)($at)
/*  f1062b0:	0fc44bd4 */ 	jal	invGetCurrentIndex
/*  f1062b4:	00000000 */ 	nop
/*  f1062b8:	8faf0028 */ 	lw	$t7,0x28($sp)
/*  f1062bc:	10000030 */ 	b	.L0f106380
/*  f1062c0:	ade20000 */ 	sw	$v0,0x0($t7)
/*  f1062c4:	8fb80028 */ 	lw	$t8,0x28($sp)
/*  f1062c8:	0fc44b11 */ 	jal	invGetWeaponNumByIndex
/*  f1062cc:	8f040000 */ 	lw	$a0,0x0($t8)
/*  f1062d0:	1040002b */ 	beqz	$v0,.L0f106380
/*  f1062d4:	00402025 */ 	or	$a0,$v0,$zero
/*  f1062d8:	0fc2c62f */ 	jal	currentPlayerGetDeviceState
/*  f1062dc:	00000000 */ 	nop
/*  f1062e0:	2401ffff */ 	addiu	$at,$zero,-1
/*  f1062e4:	10410026 */ 	beq	$v0,$at,.L0f106380
/*  f1062e8:	8fb90028 */ 	lw	$t9,0x28($sp)
/*  f1062ec:	10000024 */ 	b	.L0f106380
/*  f1062f0:	af220004 */ 	sw	$v0,0x4($t9)
/*  f1062f4:	8fa80028 */ 	lw	$t0,0x28($sp)
/*  f1062f8:	0fc44b11 */ 	jal	invGetWeaponNumByIndex
/*  f1062fc:	8d040000 */ 	lw	$a0,0x0($t0)
/*  f106300:	3c03800a */ 	lui	$v1,%hi(g_InventoryWeapon)
/*  f106304:	246321c0 */ 	addiu	$v1,$v1,%lo(g_InventoryWeapon)
/*  f106308:	a0620000 */ 	sb	$v0,0x0($v1)
/*  f10630c:	3c0a8007 */ 	lui	$t2,%hi(g_MpPlayerNum)
/*  f106310:	8d4a1448 */ 	lw	$t2,%lo(g_MpPlayerNum)($t2)
/*  f106314:	3c01800a */ 	lui	$at,%hi(g_Menus+0xe28)
/*  f106318:	304900ff */ 	andi	$t1,$v0,0xff
/*  f10631c:	000a58c0 */ 	sll	$t3,$t2,0x3
/*  f106320:	016a5823 */ 	subu	$t3,$t3,$t2
/*  f106324:	000b5880 */ 	sll	$t3,$t3,0x2
/*  f106328:	016a5821 */ 	addu	$t3,$t3,$t2
/*  f10632c:	000b58c0 */ 	sll	$t3,$t3,0x3
/*  f106330:	016a5823 */ 	subu	$t3,$t3,$t2
/*  f106334:	000b5900 */ 	sll	$t3,$t3,0x4
/*  f106338:	002b0821 */ 	addu	$at,$at,$t3
/*  f10633c:	3c048007 */ 	lui	$a0,%hi(g_SoloMissionInventoryMenuItems+0x14)
/*  f106340:	ac29ee28 */ 	sw	$t1,%lo(g_Menus+0xe28)($at)
/*  f106344:	248433e8 */ 	addiu	$a0,$a0,%lo(g_SoloMissionInventoryMenuItems+0x14)
/*  f106348:	0fc3c4e7 */ 	jal	func0f0f139c
/*  f10634c:	3c05bf80 */ 	lui	$a1,0xbf80
/*  f106350:	3c048007 */ 	lui	$a0,%hi(g_SoloMissionInventoryMenuItems+0x28)
/*  f106354:	248433fc */ 	addiu	$a0,$a0,%lo(g_SoloMissionInventoryMenuItems+0x28)
/*  f106358:	0fc3c4e7 */ 	jal	func0f0f139c
/*  f10635c:	3c05bf80 */ 	lui	$a1,0xbf80
/*  f106360:	3c048007 */ 	lui	$a0,%hi(g_SoloMissionInventoryMenuItems+0x50)
/*  f106364:	24843424 */ 	addiu	$a0,$a0,%lo(g_SoloMissionInventoryMenuItems+0x50)
/*  f106368:	0fc3c4e7 */ 	jal	func0f0f139c
/*  f10636c:	3c05bf80 */ 	lui	$a1,0xbf80
/*  f106370:	3c048007 */ 	lui	$a0,%hi(g_SoloMissionInventoryMenuItems+0x64)
/*  f106374:	24843438 */ 	addiu	$a0,$a0,%lo(g_SoloMissionInventoryMenuItems+0x64)
/*  f106378:	0fc3c4e7 */ 	jal	func0f0f139c
/*  f10637c:	3c05bf80 */ 	lui	$a1,0xbf80
.L0f106380:
/*  f106380:	00001025 */ 	or	$v0,$zero,$zero
/*  f106384:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f106388:
/*  f106388:	27bd0020 */ 	addiu	$sp,$sp,0x20
/*  f10638c:	03e00008 */ 	jr	$ra
/*  f106390:	00000000 */ 	nop
);

struct menuitem g_SoloMissionInventoryMenuItems[] = {
	{ MENUITEMTYPE_LIST,        0, 0x00000000, 0x0000006e, 0x00000063, menuhandler00106178 },
	{ MENUITEMTYPE_LABEL,       0, 0x00000203, L_OPTIONS_003, (u32)&invMenuTextWeaponManufacturer, NULL }, // ""
	{ MENUITEMTYPE_LABEL,       0, 0x00000302, L_OPTIONS_003, (u32)&invMenuTextWeaponName, NULL }, // ""
	{ MENUITEMTYPE_MODEL,       0, 0x00000000, 0x0000008c, 0x00000037, NULL },
	{ MENUITEMTYPE_LABEL,       0, 0x00000202, L_OPTIONS_003, (u32)&invMenuTextPrimaryFunction, NULL }, // ""
	{ MENUITEMTYPE_LABEL,       0, 0x00000202, L_OPTIONS_003, (u32)&invMenuTextSecondaryFunction, NULL }, // ""
	{ MENUITEMTYPE_MARQUEE,     0, 0x00000a00, (u32)&invMenuTextWeaponDescription, 0x00000000, NULL },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menuitem g_FrWeaponsAvailableMenuItems[] = {
	{ MENUITEMTYPE_LIST,        0, 0x00000000, 0x0000006e, 0x00000063, menuhandler00106028 },
	{ MENUITEMTYPE_LABEL,       0, 0x0213, L_OPTIONS_003, (u32)&invMenuTextWeaponManufacturer, NULL }, // ""
	{ MENUITEMTYPE_LABEL,       0, 0x0312, L_OPTIONS_003, (u32)&invMenuTextWeaponName, NULL }, // ""
	{ MENUITEMTYPE_MODEL,       0, 0x00000000, 0x0000008c, 0x00000037, NULL },
	{ MENUITEMTYPE_LABEL,       0, 0x0212, L_OPTIONS_003, (u32)&invMenuTextPrimaryFunction, NULL }, // ""
	{ MENUITEMTYPE_LABEL,       0, 0x0212, L_OPTIONS_003, (u32)&invMenuTextSecondaryFunction, NULL }, // ""
	{ MENUITEMTYPE_MARQUEE,     0, 0x00000a00, (u32)&invMenuTextWeaponDescription, 0x00000000, NULL },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_SoloMissionInventoryMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_178, // "Inventory"
	g_SoloMissionInventoryMenuItems,
	inventoryMenuDialog,
	0x00000602,
	&g_SoloMissionOptionsMenuDialog,
};

struct menudialog g_FrWeaponsAvailableMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_179, // "Weapons Available"
	g_FrWeaponsAvailableMenuItems,
	inventoryMenuDialog,
	0x00000602,
	NULL,
};

u32 var80073544 = 0;

//-----------------------------------------------------------------------------\
// @dialog SoloAbort ----------------------------------------------------------/
//----------------------------------------------------------------------------/

s32 menuhandlerAbortMission(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		g_Vars.currentplayer->aborted = true;
		mainEndStage();
	}

	return 0;
}

s32 menudialogAbortMission(s32 operation, struct menudialog *dialog, union handlerdata *data)
{
	if (operation == MENUOP_TICK) {
		// empty
	}

	return 0;
}

struct menuitem g_MissionAbortMenuItems[] = {
	{ MENUITEMTYPE_LABEL,       0, 0x00000012, L_OPTIONS_175, 0x00000000, NULL }, // "Do you want to abort the mission?"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_176, 0x00000000, NULL }, // "Cancel"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_OPTIONS_177, 0x00000000, menuhandlerAbortMission }, // "Abort"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_MissionAbortMenuDialog = {
	MENUDIALOGTYPE_DANGER,
	L_OPTIONS_174, // "Warning"
	g_MissionAbortMenuItems,
	menudialogAbortMission,
	0x00000000,
	NULL,
};

struct menuitem g_2PMissionAbortVMenuItems[] = {
	{ MENUITEMTYPE_LABEL,       0, 0x00000012, L_MPWEAPONS_155, 0x00000000, NULL }, // "Do you want to abort the mission"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000008, L_OPTIONS_176, 0x00000000, NULL }, // "Cancel"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000000, L_OPTIONS_177, 0x00000000, menuhandlerAbortMission }, // "Abort"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_2PMissionAbortVMenuDialog = {
	MENUDIALOGTYPE_DANGER,
	L_OPTIONS_174, // "Warning"
	g_2PMissionAbortVMenuItems,
	menudialogAbortMission,
	0x00000000,
	NULL,
};

//-----------------------------------------------------------------------------\
// @dialog SoloPauseStatus ----------------------------------------------------/
//----------------------------------------------------------------------------/

s32 soloMenuDialogPauseStatus(s32 operation, struct menudialog *dialog, union handlerdata *data)
{
	if (operation == MENUOP_OPEN) {
		struct briefingobj *briefing = g_BriefingObjs;
		struct objective *objective;
		s32 wanttype = BRIEFINGTYPE_TEXT_PA;
		s32 i;

		if (lvGetDifficulty() == DIFF_A) {
			wanttype = BRIEFINGTYPE_TEXT_A;
		}

		if (lvGetDifficulty() == DIFF_SA) {
			wanttype = BRIEFINGTYPE_TEXT_SA;
		}

		g_Briefing.briefingtextnum = L_MISC_042; // "No briefing for this mission"

		while (briefing) {
			if (briefing->type == BRIEFINGTYPE_TEXT_PA) {
				g_Briefing.briefingtextnum = briefing->text;
			}

			if (briefing->type == wanttype) {
				g_Briefing.briefingtextnum = briefing->text;
				break;
			}

			briefing = briefing->next;
		}

		for (i = 0; i < objectiveGetCount(); i++) {
			if (g_Objectives[i]) {
				g_Briefing.objectivenames[i] = g_Objectives[i]->text;
				g_Briefing.objectivedifficulties[i] = objectiveGetDifficultyBits(i);
			}
		}
	}

	return 0;
}

char *soloMenuTitlePauseStatus(struct menudialog *dialog)
{
	if (dialog != g_Menus[g_MpPlayerNum].curframe->dialog) {
		return langGet(L_OPTIONS_172); // "Status"
	}

	sprintf(g_StringPointer, "%s: %s\n",
			langGet(g_StageNames[g_MissionConfig.stageindex].name3),
			langGet(L_OPTIONS_172));

	return g_StringPointer;
}

struct menuitem g_2PMissionPauseVMenuItems[] = {
	{ MENUITEMTYPE_OBJECTIVES,  2, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_173, 0x00000000, (void *)&g_2PMissionAbortVMenuDialog }, // "Abort!"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menuitem g_MissionPauseMenuItems[] = {
	{ MENUITEMTYPE_OBJECTIVES,  0, 0x00000000, 0x00000000, 0x00000000, NULL },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00000004, L_OPTIONS_173, 0x00000000, (void *)&g_MissionAbortMenuDialog }, // "Abort!"
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_SoloMissionPauseMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(u32)&soloMenuTitlePauseStatus,
	g_MissionPauseMenuItems,
	soloMenuDialogPauseStatus,
	0x00000048,
	&g_SoloMissionInventoryMenuDialog,
};

struct menudialog g_2PMissionPauseHMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(u32)&soloMenuTitlePauseStatus,
	g_MissionPauseMenuItems,
	soloMenuDialogPauseStatus,
	0x00000048,
	&g_2PMissionInventoryHMenuDialog,
};

struct menudialog g_2PMissionPauseVMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_172, // "Status"
	g_2PMissionPauseVMenuItems,
	soloMenuDialogPauseStatus,
	0x00000048,
	&g_2PMissionInventoryVMenuDialog,
};

//-----------------------------------------------------------------------------\
// @dialog Cinema -------------------------------------------------------------/
//----------------------------------------------------------------------------/

struct cutscene g_Cutscenes[] = {
	// stage ID, mission, scene, name
	{ /* 0*/ STAGE_DEFECTION,      0, 0, L_OPTIONS_450 },
	{ /* 1*/ STAGE_DEFECTION,      0, 1, L_OPTIONS_451 },
	{ /* 2*/ STAGE_INVESTIGATION,  1, 0, L_OPTIONS_452 },
	{ /* 3*/ STAGE_INVESTIGATION,  1, 1, L_OPTIONS_453 },
	{ /* 4*/ STAGE_EXTRACTION,     2, 0, L_OPTIONS_454 },
	{ /* 5*/ STAGE_EXTRACTION,     2, 1, L_OPTIONS_455 },
	{ /* 6*/ STAGE_VILLA,          3, 0, L_OPTIONS_456 },
	{ /* 7*/ STAGE_VILLA,          3, 2, L_OPTIONS_458 },
	{ /* 8*/ STAGE_CHICAGO,        4, 0, L_OPTIONS_459 },
	{ /* 9*/ STAGE_CHICAGO,        4, 1, L_OPTIONS_460 },
	{ /*10*/ STAGE_G5BUILDING,     5, 0, L_OPTIONS_461 },
	{ /*11*/ STAGE_G5BUILDING,     5, 1, L_OPTIONS_462 },
	{ /*12*/ STAGE_G5BUILDING,     5, 2, L_OPTIONS_463 },
	{ /*13*/ STAGE_INFILTRATION,   6, 0, L_OPTIONS_464 },
	{ /*14*/ STAGE_INFILTRATION,   6, 1, L_OPTIONS_465 },
	{ /*15*/ STAGE_RESCUE,         7, 0, L_OPTIONS_466 },
	{ /*16*/ STAGE_RESCUE,         7, 1, L_OPTIONS_467 },
	{ /*17*/ STAGE_ESCAPE,         8, 0, L_OPTIONS_468 },
	{ /*18*/ STAGE_ESCAPE,         8, 1, L_OPTIONS_469 },
	{ /*19*/ STAGE_ESCAPE,         8, 2, L_OPTIONS_470 },
	{ /*20*/ STAGE_AIRBASE,        9, 0, L_OPTIONS_471 },
	{ /*21*/ STAGE_AIRBASE,        9, 1, L_OPTIONS_472 },
	{ /*22*/ STAGE_AIRFORCEONE,   10, 0, L_OPTIONS_473 },
	{ /*23*/ STAGE_AIRFORCEONE,   10, 1, L_OPTIONS_474 },
	{ /*24*/ STAGE_AIRFORCEONE,   10, 2, L_OPTIONS_475 },
	{ /*25*/ STAGE_CRASHSITE,     11, 0, L_OPTIONS_476 },
	{ /*26*/ STAGE_CRASHSITE,     11, 1, L_OPTIONS_477 },
	{ /*27*/ STAGE_PELAGIC,       12, 0, L_OPTIONS_478 },
	{ /*28*/ STAGE_PELAGIC,       12, 1, L_OPTIONS_479 },
	{ /*29*/ STAGE_DEEPSEA,       13, 0, L_OPTIONS_480 },
	{ /*30*/ STAGE_DEEPSEA,       13, 1, L_OPTIONS_481 },
	{ /*31*/ STAGE_DEEPSEA,       13, 2, L_OPTIONS_482 },
	{ /*32*/ STAGE_DEFENSE,       14, 0, L_OPTIONS_483 },
	{ /*33*/ STAGE_DEFENSE,       14, 1, L_OPTIONS_484 },
	{ /*34*/ STAGE_ATTACKSHIP,    15, 0, L_OPTIONS_485 },
	{ /*35*/ STAGE_ATTACKSHIP,    15, 1, L_OPTIONS_486 },
	{ /*36*/ STAGE_SKEDARRUINS,   16, 0, L_OPTIONS_487 },
	{ /*37*/ STAGE_SKEDARRUINS,   16, 1, L_OPTIONS_488 },
};

u32 g_CutsceneCountsByMission[] = {
	/* 0*/ 1,  // 0 missions completed => 1 cutscene available (Def intro)
	/* 1*/ 3,  // 1 mission completed => 3 cutscenes available (Def intro, outro, Invest intro)
	/* 2*/ 5,
	/* 3*/ 7,
	/* 4*/ 9,
	/* 5*/ 11,
	/* 6*/ 14,
	/* 7*/ 16,
	/* 8*/ 18,
	/* 9*/ 21,
	/*10*/ 23,
	/*11*/ 26,
	/*12*/ 28,
	/*13*/ 30,
	/*14*/ 33,
	/*15*/ 35,
	/*16*/ 37,
	/*17*/ 38,
};

s32 getNumCompletedMissions(void)
{
	s32 s;
	s32 d;
	s32 count = 0;

	for (s = 0; s != 17; s++) {
		bool done = false;

		for (d = 0; d != 3; d++) {
			if (g_SoloSaveFile.besttimes[s][d] || (g_SoloSaveFile.coopcompletions[d] & (1 << s))) {
				count++;
				done = true;
				break;
			}
		}

		if (!done) {
			break;
		}
	}

	return count;
}

struct cutscenegroup {
	u32 first_cutscene_index;
	u16 name;
};

s32 menuhandlerCinema(s32 operation, struct menuitem *item, union handlerdata *data)
{
	struct cutscenegroup groups[] = {
		{ /* 0*/  0, L_OPTIONS_436 }, // "Special"
		{ /* 1*/  1, L_OPTIONS_438 }, // "Mission 1 - dataDyne Central"
		{ /* 2*/  7, L_OPTIONS_439 },
		{ /* 3*/  9, L_OPTIONS_440 },
		{ /* 4*/ 14, L_OPTIONS_441 },
		{ /* 5*/ 21, L_OPTIONS_442 },
		{ /* 6*/ 28, L_OPTIONS_443 },
		{ /* 7*/ 33, L_OPTIONS_444 },
		{ /* 8*/ 35, L_OPTIONS_445 },
		{ /* 9*/ 37, L_OPTIONS_446 }, // "Mission 9 - Skedar Ruins"
		{ /*10*/ 39, L_OPTIONS_447 }, // "Finale"
	};

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		// Add one for Play All option
		data->list.value = g_CutsceneCountsByMission[getNumCompletedMissions()] + 1;
		break;
	case MENUOP_GETOPTIONTEXT:
		if (data->list.value == 0) {
			sprintf(g_StringPointer, langGet(L_OPTIONS_448)); // "Play All"
			return (s32) g_StringPointer;
		}
		return (s32) langGet(g_Cutscenes[data->list.value - 1].name);
	case MENUOP_SET:
		if (data->list.value == 0) {
			// Play all
			s32 index = getNumCompletedMissions();
			g_Vars.autocutgroupcur = 0;
			g_Vars.autocutgroupleft = g_CutsceneCountsByMission[index];
			menuPopDialog();
			func0f01bea0();
		} else {
			// Play specific cutscene
			g_Vars.autocutgroupcur = data->list.value - 1;
			g_Vars.autocutgroupleft = 1;
			menuPopDialog();
			func0f01bea0();
		}
		break;
	case MENUOP_GETOPTIONVALUE:
		data->list.value = 0xfffff;
		break;
	case MENUOP_GETOPTGROUPCOUNT:
		data->list.value = ARRAYCOUNT(groups);
		break;
	case MENUOP_GETOPTGROUPTEXT:
		return (s32) langGet(groups[data->list.value].name);
	case MENUOP_GETGROUPSTARTINDEX:
		data->list.groupstartindex = groups[data->list.value].first_cutscene_index;
		break;
	}

	return 0;
}

struct menuitem g_CinemaMenuItems[] = {
	{ MENUITEMTYPE_LIST,        0, 0x00000000, 0x000000eb, 0x00000000, menuhandlerCinema },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_CinemaMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_490, // "Cinema"
	g_CinemaMenuItems,
	NULL,
	0x00000004,
	NULL,
};

//-----------------------------------------------------------------------------\
// @dialog SelectMission ------------------------------------------------------/
//----------------------------------------------------------------------------/

struct menuitem g_SelectMissionMenuItems[] = {
	{ MENUITEMTYPE_LIST,        0, 0x00200000, 0x000000eb, 0x00000000, menuhandler0010476c },
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_SelectMissionMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_122, // "Mission Select"
	g_SelectMissionMenuItems,
	NULL,
	0x00000004,
	NULL,
};

//-----------------------------------------------------------------------------\
// @dialog MainMenu -----------------------------------------------------------/
//----------------------------------------------------------------------------/

s32 menuhandlerMainMenuSoloMissions(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		g_MissionConfig.iscoop = false;
		g_MissionConfig.isanti = false;
		menuPushDialog(&g_SelectMissionMenuDialog);
	}

	if (operation == MENUOP_CHECKPREFOCUSED) {
		if (isStageDifficultyUnlocked(SOLOSTAGEINDEX_INVESTIGATION, DIFF_A)) {
			return true;
		}
	}

	return 0;
}

s32 menuhandlerMainMenuCombatSimulator(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		g_Vars.bondplayernum = 0;
		g_Vars.coopplayernum = -1;
		g_Vars.antiplayernum = -1;
		mpDetermineUnlockedFeatures();
		g_Vars.unk000490 = 2;
		func0f0f820c(&g_CombatSimulatorMenuDialog, 3);
		func0f0f8300();
	}

	return 0;
}

s32 menuhandlerMainMenuCooperative(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		g_MissionConfig.iscoop = true;
		g_MissionConfig.isanti = false;
		menuPushDialog(&g_SelectMissionMenuDialog);
	}

	return 0;
}

s32 menuhandlerMainMenuCounterOperative(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_CHECKDISABLED) {
		if ((joyGetConnectedControllers() & 2) == 0) {
			return true;
		}
	}

	if (operation == MENUOP_SET) {
		g_MissionConfig.iscoop = false;
		g_MissionConfig.isanti = true;
		menuPushDialog(&g_SelectMissionMenuDialog);
	}

	return 0;
}

s32 menudialogMainMenu(s32 operation, struct menudialog *dialog, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_OPEN:
		g_Menus[g_MpPlayerNum].data.main.unke2c = 0;
		break;
	case MENUOP_TICK:
		if (g_Menus[g_MpPlayerNum].curframe &&
				g_Menus[g_MpPlayerNum].curframe->dialog == dialog) {
			g_MissionConfig.iscoop = false;
			g_MissionConfig.isanti = false;
		}
		break;
	}

	return false;
}

char *mainMenuTextLabel(struct menuitem *item)
{
	u16 nocheats[] = {
		L_OPTIONS_117, // "Solo Missions"
		L_OPTIONS_118, // "Combat Simulator"
		L_OPTIONS_119, // "Co-Operative"
		L_OPTIONS_120, // "Counter-Operative"
	};

	u16 withcheats[] = {
		L_MPWEAPONS_130, // "Cheat Solo Missions"
		L_MPWEAPONS_131, // "Cheat Combat Simulator"
		L_MPWEAPONS_132, // "Cheat Co-Operative"
		L_MPWEAPONS_133, // "Cheat Counter-Operative"
	};

	if (g_CheatsEnabledBank0 || g_CheatsEnabledBank1) {
		return langGet(withcheats[item->param]);
	}

	return langGet(nocheats[item->param]);
}

struct menuitem g_MainMenuMenuItems[] = {
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400008, L_MISC_446, 0x00000001, NULL }, // "Carrington Institute"
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400000, (u32)&mainMenuTextLabel, 0x00000002, menuhandlerMainMenuSoloMissions },
	{ MENUITEMTYPE_SELECTABLE,  1, 0x00400000, (u32)&mainMenuTextLabel, 0x00000003, menuhandlerMainMenuCombatSimulator },
	{ MENUITEMTYPE_SELECTABLE,  2, 0x00400000, (u32)&mainMenuTextLabel, 0x00000004, menuhandlerMainMenuCooperative },
	{ MENUITEMTYPE_SELECTABLE,  3, 0x00400000, (u32)&mainMenuTextLabel, 0x00000005, menuhandlerMainMenuCounterOperative },
	{ MENUITEMTYPE_SELECTABLE,  0, 0x00400004, L_OPTIONS_187, 0x00000006, (void *)&g_ChangeAgentMenuDialog }, // "Change Agent..."
	{ MENUITEMTYPE_END,         0, 0x00000000, 0x00000000, 0x00000000, NULL },
};

struct menudialog g_CiMenuViaPcMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_116, // "Perfect Menu"
	g_MainMenuMenuItems,
	menudialogMainMenu,
	0x00000004,
	&g_CiOptionsViaPcMenuDialog,
};

struct menudialog g_CiMenuViaPauseMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	L_OPTIONS_116, // "Perfect Menu"
	g_MainMenuMenuItems,
	menudialogMainMenu,
	0x00000004,
	&g_CiOptionsViaPauseMenuDialog,
};

bool soloChoosePauseDialog(void)
{
	if (g_Menus[g_MpPlayerNum].unk83c == 0) {
		g_Menus[g_MpPlayerNum].playernum = 0;

		if (g_Vars.stagenum == STAGE_CITRAINING) {
			bool handled = false;

			if (ciIsTourDone()) {
				struct trainingdata *dtdata = dtGetData();
				s32 room = g_Vars.currentplayer->prop->rooms[0];

				if (room >= CIROOM_HOLOSTART && room <= CIROOM_HOLOEND) {
					struct trainingdata *htdata = getHoloTrainingData();

					if (htdata->intraining) {
						menuPushRootDialog(&g_HtDetailsMenuDialog, MENUROOT_TRAINING);
					} else if (htdata->finished) {
						htPushEndscreen();
					} else {
						menuPushRootDialog(&g_HtListMenuDialog, MENUROOT_TRAINING);
					}

					handled = true;
				} else {
					if (room == CIROOM_DEVICEROOM) {
						if (dtdata->intraining) {
							menuPushRootDialog(&g_DtDetailsMenuDialog, MENUROOT_TRAINING);
						} else if (dtdata->finished) {
							dtPushEndscreen();
						} else {
							menuPushRootDialog(&g_DtListMenuDialog, MENUROOT_TRAINING);
						}

						handled = true;
					} else {
						if (dtdata->intraining) {
							menuPushRootDialog(&g_DtDetailsMenuDialog, MENUROOT_TRAINING);
							handled = true;
						} else if (dtdata->finished) {
							dtPushEndscreen();
							handled = true;
						} else if (room == CIROOM_FIRINGRANGE) {
							if (frIsInTraining()) {
								menuPushRootDialog(&g_FrTrainingInfoInGameMenuDialog, MENUROOT_TRAINING);
							} else {
								menuPushRootDialog(&g_FrWeaponListMenuDialog, MENUROOT_TRAINING);
							}

							handled = true;
						}
					}
				}
			}

			if (!handled) {
				menuPushRootDialog(&g_CiMenuViaPauseMenuDialog, MENUROOT_MAINMENU);
				return true;
			}
		} else {
			menuPushRootDialog(&g_SoloMissionPauseMenuDialog, MENUROOT_MAINMENU);
		}

		return true;
	}

	return false;
}
