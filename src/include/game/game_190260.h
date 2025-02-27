#ifndef _IN_GAME_GAME_190260_H
#define _IN_GAME_GAME_190260_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

bool func0f190260(struct chrdata *chr);
void mpChrReset(struct chrdata *chr, u8 full);
void mpInitSimulant(struct chrdata *chr, u8 full);
void mpInitSimulants(void);
u32 add87654321(u32 value);
u32 propobjHandlePickupByAibot(struct prop *prop, struct chrdata *chr);
bool func0f190be4(struct prop *prop, struct chrdata *chr);
void func0f19124c(struct chrdata *chr);
s32 chrGuessCrouchPos(struct chrdata *chr);
bool func0f191448(struct chrdata *chr);
bool func0f191638(struct chrdata *chr, bool arg1);
s32 aibotTick(struct prop *prop);
f32 aibotCalculateMaxSpeed(struct chrdata *chr);
void func0f1921f8(struct chrdata *chr, f32 *arg1, s32 arg2, f32 arg3);
void aibotLoseGun(struct chrdata *chr, struct prop *attacker);
void func0f19277c(struct chrdata *chr, s32 propnum);
bool func0f19294c(struct chrdata *botchr, struct chrdata *otherchr);
bool chrHasGround(struct chrdata *chr);
void func0f192a74(struct chrdata *chr);
bool func0f192d64(struct chrdata *botchr, struct chrdata *otherchr);
bool func0f192dc0(struct chrdata *botchr, struct chrdata *chr);
u32 func0f192e90(void);
void func0f19369c(struct chrdata *chr, s32 arg1);
s32 func0f1937a4(struct chrdata *chr, s32 arg1);
s32 mpGetNumOpponentsInHill(struct chrdata *chr);
void func0f194b40(struct chrdata *chr);
s32 mpObjIsSafe(struct defaultobj *obj);
s32 mpchrGetWeaponNum(struct chrdata *chr);
u8 mpchrGetTargetsWeaponNum(struct chrdata *chr);
char *mpGetBotCommandName(s32 command);
void mpAibotApplyAttack(struct chrdata *chr, struct prop *prop);
void mpAibotApplyFollow(struct chrdata *chr, struct prop *prop);
void mpAibotApplyProtect(struct chrdata *chr, struct prop *prop);
void mpAibotApplyDefend(struct chrdata *chr, struct coord *pos, s16 *room, f32 arg3);
void mpAibotApplyHold(struct chrdata *chr, struct coord *pos, s16 *room, f32 arg3);
void mpAibotApplyScenarioCommand(struct chrdata *chr, u32 arg1);
bool mpIsChrFollowedByChr(struct chrdata *leader, struct chrdata *follower);
s32 func0f193530(struct chrdata *chr, f32 range);
bool func0f194670(struct chrdata *chr);
s32 func0f194694(struct chrdata *chr);
s32 func0f1946b4(struct chrdata *chr);
s32 mpGetNumPlayerTeammates(struct chrdata *chr);
s32 mpCountAibotsWithCommand(struct chrdata *self, u32 command, bool includeself);
s32 scenarioCtcIsChrsTokenHeld(struct chrdata *chr);
bool func0f19489c(struct chrdata *chr);
s32 mpGetNumTeammatesDefendingHill(struct chrdata *bot);
void func0f197544(struct chrdata *chr);

#endif
