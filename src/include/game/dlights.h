#ifndef IN_GAME_DLIGHTS_H
#define IN_GAME_DLIGHTS_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

s32 func0f000920(s32 num1, s32 num2);
struct light *roomGetLight(s32 roomnum, s32 lightnum);
u8 func0f0009c0(s32 roomnum);
u8 func0f000a10(s32 roomnum);
u8 func0f000b24(s32 roomnum);
u8 roomGetBrightness(s32 room);
s32 func0f000c54(s32 roomnum);
f32 roomGetUnk5c(s32 roomnum);
f32 func0f000dbc(s32 roomnum);
bool lightGetBboxCentre(s32 roomnum, u32 lightnum, struct coord *pos);
bool lightIsHealthy(s32 roomnum, s32 lightnum);
bool lightIsVulnerable(s32 roomnum, s32 lightnum);
bool lightIsOn(s32 roomnum, s32 lightnum);
void roomSetUnk52(s32 roomnum, s32 value);
void roomSetDefaults(struct room *room);
Gfx *func0f001138(Gfx *gdl, s16 roomnum);
Gfx *func0f001300(Gfx *gdl);
void roomInitLights(s32 roomnum);
s32 func0f001734(struct coord *arg0, struct coord *arg1, s32 roomnum);
void roomSetLightsFaulty(s32 roomnum, s32 chance);
void roomSetLightBroken(s32 roomnum, s32 lightnum);
void func0f001bdc(void);
void func0f001c0c(void);
u32 func0f00215c(void);
u32 func0f0023b8(void);
u32 func0f00259c(void);
u32 func0f002844(void);
void func0f002a98(void);
void roomSetLightsOn(s32 roomnum, s32 enable);
void roomSetLighting(s32 roomnum, s32 operation, u8 arg2, u8 arg3, u8 arg4);
u32 func0f002ef8(void);
void lightingTick(void);
void func0f003444(void);
void func0f0035c0(void);
void func0f00372c(void);
void func0f0037ac(void);
void func0f004314(void);
void roomAdjustLighting(s32 roomnum, s32 start, s32 limit);
void func0f004558(s32 roomnum, s32 increment, s32 limit);
void func0f004604(s32 roomnum);
void func0f004c6c(void);
u32 func0f00505c(void);
u32 func0f0053d0(void);
void func0f0056f4(s32 room1, struct coord *coord1, s32 room2, struct coord *coord2, s32 arg4, f32 *arg5, s32 arg6);
void func0f005bb0(void);

#endif
