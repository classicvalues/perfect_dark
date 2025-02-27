#ifndef _IN_LIB_LIB_24E40_H
#define _IN_LIB_LIB_24E40_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

f32 func00024e40(void);
void func00024e4c(struct coord *arg0, struct coord *arg1, u32 line, char *file);
f32 func00024e98(void);
s32 func00024ea4(void);
struct prop *cdGetObstacle(void);
void cdGetPos(struct coord *pos, u32 line, char *file);
void func00024ee8(struct coord *arg0);
u32 cdGetTileFlags(void);
void func00024f6c(void);
void func00024fb0(struct coord *arg0, struct coord *arg1, struct prop *prop);
u32 func00025038(void);
void func000250cc(struct coord *arg0, struct coord *arg1, f32 width);
void func00025168(struct prop *prop);
u32 func000251ac(void);
void func00025254(struct coord *arg0, struct coord *arg1, struct coord *pos, struct prop *prop, f32 arg4, struct tile *tile);
u32 func00025314(void);
u32 func00025364(void);
u32 func000253c4(void);
u32 func00025410(void);
u32 func000254d8(void);
f32 func00025654(f32 x1, f32 z1, f32 x2, f32 z2, f32 x3, f32 z3);
f32 func00025724(f32 x1, f32 z1, f32 x2, f32 z2);
bool func00025774(f32 x1, f32 z1, f32 x2, f32 z2, f32 x3, f32 z3);
void func00025848(f32 tilex, f32 tilez, f32 tilewidth, f32 posx, f32 posz, f32 *x1, f32 *z1, f32 *x2, f32 *z2);
void func00025928(struct tile *tile, struct coord *arg1);
void tileGetFloorCol(struct tile *tile, u16 *floorcol);
void tileGetFloorType(struct tile *tile, u8 *floortype);
f32 cdFindGroundInTileType0AtVertex(struct tiletype0 *tile, f32 x, f32 z, s32 vertexindex);
f32 cdFindGroundInTileType0(struct tiletype0 *tile, f32 x, f32 z);
f32 cdFindGroundInTileType1(struct tiletype1 *tile, f32 x, f32 z);
bool cdIs2dPointInTileType0(struct tiletype0 *tile, f32 x, f32 z);
bool cdIs2dPointInTileType1(struct tiletype1 *tile, f32 x, f32 z);
bool cdIs2dPointInTileType2(struct tiletype2 *tile, f32 x, f32 z);
bool cdIs2dPointInTileType3(struct tiletype3 *tile, f32 x, f32 z);
bool func000266a4(f32 x, f32 z, struct tile *tile);
void platformGetRidingProps(struct prop *platform, s16 *propnums, s32 len);
bool func00026a04(struct coord *pos, u8 *start, u8 *end, u16 flags, s32 room, struct tile **tileptr, s32 *roomptr, f32 *groundptr, bool arg8);
void func00026e7c(struct coord *pos, s16 *rooms, u16 arg2, struct tile **tileptr, s16 *arg4, f32 *arg5, struct prop **arg6, s32 arg7);
bool func0002709c(struct tiletype0 *tile, f32 x, f32 z, f32 width, struct prop *prop, struct collisionthing *thing);
bool func000272f8(struct tiletype1 *tile, f32 x, f32 z, f32 width, struct prop *prop, struct collisionthing *thing);
s32 func000274e0(struct tiletype2 *tile, f32 x, f32 z, f32 width, struct prop *prop, struct collisionthing *thing);
bool func000276c8(struct tiletype3 *tile, f32 x, f32 z, f32 width, struct prop *prop, struct collisionthing *thing);
void func00027738(struct coord *pos, f32 width, u8 *start, u8 *end, u16 flags, bool checkvertical, f32 arg6, f32 arg7, struct prop *prop, struct collisionthing *things, s32 maxthings, s32 *thingnum, s32 roomnum);
void func00027d1c(struct coord *pos, f32 width, s16 *rooms, u32 types, u16 arg4, u32 arg5, f32 arg6, f32 arg7, struct collisionthing *arg8, s32 arg9);
u32 func00027f78(void);
s32 func00028200(struct tiletype0 *tile, struct coord *pos, f32 width, f32 y1, f32 y2);
u32 func0002840c(void);
u32 func00028638(void);
u32 func0002885c(void);
s32 func00028914(u8 *start, u8 *end, struct coord *pos, f32 width, u16 flags, bool checkvertical, f32 arg6, f32 arg7, struct prop *prop, struct collisionthing *things, s32 maxthings, s32 *thingnum);
void func00028df0(struct coord *pos, f32 width, s16 *rooms, u32 types, u16 arg4, u32 arg5, f32 ymax, f32 ymin, struct collisionthing *arg8, s32 arg9);
void func0002901c(struct coord *pos, struct coord *dist, f32 width, struct collisionthing *arg3);
f32 func000296a0(struct collisionthing *arg0, struct coord *pos, struct tilething **arg2, f32 width);
bool func00029ffc(struct coord *pos, f32 width, f32 foreheadheight, f32 inversefeettoeyesheight, s16 *rooms, u16 arg5, struct coord *laddernormal);
bool func0002a13c(struct coord *pos, f32 width, f32 arg2, f32 arg3, s16 *rooms, u16 arg5);
f32 cdFindGroundY(struct coord *pos, f32 width, s16 *rooms, u16 *floorcol, u8 *floortype, u16 *floorflags, s16 *floorroom, s32 *inlift, struct prop **lift);
f32 func0002a324(void);
f32 cdFindGroundYSimple(struct coord *pos, f32 width, s16 *rooms, u16 *floorcol, u8 *floortype);
f32 func0002a36c(struct coord *coord, s16 *rooms, u16 *floorcol, u8 *floortype);
s32 func0002a400(struct coord *pos, s16 *rooms);

#if VERSION >= VERSION_NTSC_1_0
s16 func0002a440(struct coord *pos, s16 *rooms, f32 *arg2, u16 *floorcolptr, u16 *flagsptr);
#else
s16 func0002a440(struct coord *pos, s16 *rooms, f32 *arg2, u16 *floorcolptr);
#endif

s16 func0002a4d0(struct coord *pos, s16 *rooms, f32 *arg2, u16 *floorcolptr, u16 *flagsptr);
s32 func0002a564(struct coord *pos, s16 *rooms, f32 *arg2, u16 *floorcol, struct coord *arg4, struct prop **propptr);
s32 func0002a5e4(struct coord *pos, s16 *rooms, f32 *arg2, u16 *floorcol, u16 *arg4, struct coord *arg5);
s32 cdTestVolume(struct coord *pos, f32 width, s16 *rooms, s32 types, s32 arg4, f32 ymax, f32 ymin);
s32 func0002a6fc(struct coord *pos, struct coord *pos2, f32 width, s16 *rooms, s32 types, bool arg5, f32 arg6, f32 arg7);
s32 cdTestAToB1(struct coord *origpos, struct coord *dstpos, f32 width, s16 *dstrooms, s32 types, s32 arg5, f32 ymax, f32 ymin);
u32 func0002aac0(void);
u32 func0002ab98(void);
u32 func0002ac70(void);
u32 func0002b128(void);
u32 func0002b560(void);
u32 func0002b954(void);
bool func0002bd04(u8 *start, u8 *end, struct coord *arg2, struct coord *arg3, struct coord *arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, f32 arg9);
u32 func0002c328(void);
u32 func0002c528(void);
bool func0002c714(u8 *start, u8 *end, struct coord *arg2, struct coord *arg3, struct coord *arg4, u16 arg5, s32 arg6, s32 arg7, f32 ymax, f32 ymin, f32 *arg10, struct coord *arg11, struct coord *arg12, struct coord *arg13, struct tile **tile, s32 roomnum);
bool func0002d15c(struct coord *pos, struct coord *coord2, s16 *rooms, u32 types, u16 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8);
s32 func0002d3b0(struct coord *arg0, struct coord *arg1, s16 *arg2, s32 types, u16 arg4, s32 arg5, s32 arg6, f32 ymax, f32 ymin);
bool func0002d6ac(struct coord *pos, s16 *rooms, struct coord *targetpos, u32 types, u32 arg4, f32 arg5, f32 arg6);
s32 cdTestAToB2(struct coord *pos, s16 *rooms, struct coord *coord2, s16 *rooms2, u32 types, s32 arg5, f32 arg6, f32 arg7);
bool func0002d7c0(struct coord *pos, s16 *rooms, struct coord *arg2, u32 arg3, u32 arg4, f32 ymax, f32 ymin);
s32 func0002d840(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, u32 types, s32 arg5, f32 ymax, f32 ymin);
s32 func0002d8b8(struct coord *pos, s16 *rooms, struct coord *pos2, s16 *rooms2, s32 types, bool arg5, f32 ymax, f32 ymin);
s32 cdTestAToB3(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, f32 arg4, s32 types, s32 arg6, f32 ymax, f32 ymin);
void func0002da50(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, u32 types, s32 arg5, f32 ymax, f32 ymin);
s32 func0002dac8(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, f32 width, u32 types, s32 arg6, f32 ymax, f32 ymin);
bool func0002db98(struct coord *viewpos, s16 *rooms, struct coord *targetpos, u32 types, u16 arg4);
bool func0002dc18(struct coord *coord, s16 *rooms, struct coord *coord2, s32 arg3);
bool hasLineOfSight(struct coord *coord, s16 *rooms, struct coord *coord2, s16 *rooms2, s32 arg4, u16 arg5);
bool func0002dcd0(struct coord *arg0, s16 *rooms1, struct coord *arg2, s16 *rooms2, u32 arg4);
bool func0002dcfc(struct coord *pos, s16 *rooms, struct coord *pos2, s16 *rooms2, s16 *rooms3, u32 types, u16 arg6);
s32 cdTestAToB4(struct coord *pos, s16 *rooms, struct coord *pos2, u32 types, u16 arg4);
s32 func0002de10(struct coord *pos, s16 *rooms, struct coord *pos2, u32 types);
s32 func0002de34(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, u32 types, u16 arg5);
s32 func0002deac(struct coord *arg0, s16 *arg1, struct coord *arg2, s16 *arg3, u32 types);
bool func0002ded8(struct coord *arg0, struct coord *arg1, struct prop *prop);
bool func0002dffc(struct tiletype2 *arg0, struct tiletype2 *arg1);
s32 func0002e278(u8 *start, u8 *end, struct tiletype2 *ref, u16 flags);
s32 func0002e4c4(struct tiletype2 *geo, s16 *rooms, u32 types);
u32 func0002e680(void);
u32 func0002e82c(void);
u32 func0002e9d8(void);
u32 func0002eb84(void);
u32 func0002ed30(void);
u32 func0002f02c(void);
bool func0002f308(struct coord *viewpos, s16 *rooms, struct coord *targetpos, f32 distance, s32 arg4, u16 arg5);
bool func0002f450(struct coord *viewpos, s16 *rooms, struct coord *targetpos, f32 distance, s32 arg4);

#endif
