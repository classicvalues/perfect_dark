#ifndef _IN_LIB_LIB_317F0_H
#define _IN_LIB_LIB_317F0_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

void func000317f0(void *arg0);
u32 func00031b34(void);
u32 func00033090(void);
u32 func00033100(void);
u32 func00033180(void);
u32 func00033274(void);
void func00033378(void *fn);
u32 func00033390(void);
void func00033634(void *fn);
u32 func0003364c(void);
u32 audioIsPlaying(struct audiohandle *handle);
struct audiohandle *func00033820(s32 arg0, s16 soundnum, s32 arg2, s32 arg3, f32 arg4, s32 arg5, s32 arg6, struct audiohandle **handle);
void audioStop(struct audiohandle *handle);
u32 func00033bc0(void);
u32 func00033c30(void);
u32 func00033cf0(void);
u32 func00033db0(void);
u32 func00033dd8(void);
void func00033e50(struct audiohandle *handle, s32 arg1, s32 arg2);
u16 func00033ec4(s32 arg0);
u32 func00033f08(void);
u32 func00033f24(void);
void func00033f44(u8 index, u16 volume);

#endif
