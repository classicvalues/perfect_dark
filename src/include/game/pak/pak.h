#ifndef IN_GAME_PAK_PAK_H
#define IN_GAME_PAK_PAK_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

u32 func0f1165d0(s8 device);
u32 func0f1165f8(s8 device, u32 arg1);
u32 func0f116658(s8 arg0, u32 arg1);
u32 func0f116684(u32 arg0);
u32 func0f11668c(s8 device);
bool pakIsConnected(s8 device);
s32 func0f1167b0(s8 device, u32 arg1, u32 *buffer1024);
u32 func0f1167d8(s8 arg0);
s32 func0f116800(s8 arg0, s32 arg1, void *arg2, s32 arg3);
s32 func0f116828(s8 arg0, s32 arg1, s32 arg2, void *arg3, s32 *arg4, s32 arg5);
bool filemgrDeleteFile(s8 arg0, s32 arg1);
s32 pakDeleteGameNote(s8 device, u16 company_code, u32 game_code, char *game_name, char *ext_name);
s32 func0f1168c4(s8 device, struct pakdata **arg1);
u32 func0f116914(s8 device);
s32 func0f11693c(s8 device);
void func0f116994(void);
void func0f1169c8(s8 device, s32 arg1);
bool func0f116aec(s8 device);
bool func0f116b5c(s8 device);
void func0f116bdc(s8 device, u8 *arg1, u8 *arg2);
u16 func0f116c54(s8 device);
u32 func0f116c94(s8 device);
void func0f116db0(s8 device, s32 value);
s32 func0f116df0(s8 device, struct pakdata **arg1);
s32 func0f116e84(s8 device, u16 company_code, u32 game_code, char *game_name, char *ext_name);
bool func0f116fa0(s8 device, s32 arg1);
s32 func0f11702c(s8 device);
u32 func0f11706c(s8 device);
s32 func0f117094(s8 arg0, u32 arg1);
void func0f117150(s8 device, u8 *ptr);
void func0f1171b4(s8 device, s32 arg1, s32 arg2);
s32 func0f117210(s8 device);
u32 func0f117430(void);
u32 func0f117520(s8 arg0, u32 arg1, u32 *arg2);
void pakDumpBuffer(u8 *buffer, u32 len, char *name);
void pakDumpEeprom(void);
s32 func0f11789c(s8 arg0, s32 arg1, s32 arg2, void *arg3, s32 *arg4, s32 arg5);

#if VERSION >= VERSION_NTSC_1_0
s32 pakInitPak(OSMesgQueue *mq, OSPfs *pfs, s32 channel, s32 *arg3);
#else
s32 pakInitPak(OSMesgQueue *mq, OSPfs *pfs, s32 channel);
#endif

s32 pakReadWriteFile(OSPfs *pfs, s32 file_no, u8 flag, u32 address, u32 len, u8 *buffer);
s32 func0f117c0c(s32 arg0, s32 *arg1, s32 *arg2);
s32 pakFreeBlocks(OSPfs *pfs, s32 *bytes_not_used);
s32 pakFileState(OSPfs *pfs, s32 file_no, OSPfsState *note);
s32 pakAllocateFile(OSPfs *pfs, u16 company_code, u32 game_code, char *game_name, char *ext_name, s32 size, s32 *file_no);
u32 pakDeleteFile(OSPfs *pfs, u16 company_code, u32 game_code, char *game_name, char *ext_name);
s32 pakFindFile(OSPfs *pfs, u16 company_code, u32 game_code, char *game_name, char *ext_name, s32 *file_no);
s32 func0f117ec0(OSPfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name, u32 numbytes);
s32 func0f117f80(s8 device);
s32 func0f117fc0(s8 device);
s32 func0f118000(s8 device);
s32 func0f11807c(s8 device);
s32 func0f118148(s8 device);
s32 func0f118230(s8 device, s32 arg1);
s32 func0f118334(s8 device, s32 numpages);
void func0f1185e0(s8 device, s32 arg1, s32 param_3);
u32 func0f118674(s8 arg0, u32 arg1, u32 arg2);
void func0f1189d8(void);
void func0f118ae4(u8 *arg0, u8 *arg1, u16 *arg2);
s32 func0f118bc8(s8 arg0, s32 arg1, void *arg2, s32 arg3);
s32 func0f118d18(s8 device, u32 arg1, u32 *buffer1024);
s32 func0f1190bc(s8 device, s32 arg1, s32 *arg2);
u32 func0f119298(s8 index);
void func0f119340(u32 arg0);
u32 func0f119368(s32 device, u32 arg1, struct pakthing16 *pakthing16);
#if VERSION >= VERSION_NTSC_FINAL
bool func0f119478(u32 arg0, u32 arg1, u32 *arg2);
#endif
u32 func0f1194e0(s8 arg0, u32 *arg1, u32 arg2);
u32 func0f11970c(void);
void pakCorrupt(void);
u32 func0f119e8c(void);
u32 func0f11a0e8(void);
u32 func0f11a1d0(void);
void func0f11a2e4(void);
void func0f11a32c(s8 device, u8 arg1, u32 line, char *file);
void func0f11a434(s8 arg0);
s32 func0f11a504(s8 device, OSPfs *pfs, s32 file_no, u8 flag, u32 address, u32 len, u8 *buffer);
s32 func0f11a574(s8 device);
u32 func0f11a7dc(void);
u32 func0f11a8f4(void);
u32 func0f11ac7c(void);
void pakWipeEeprom(s32 arg0, s32 arg1, s32 arg2);
u32 func0f11b178(void);
u32 func0f11b488(void);
void pakForceScrub(s32 arg0);
u32 func0f11b75c(void);
u32 func0f11b86c(void);
u32 func0f11bbd8(void);
u32 func0f11bc54(s8 device, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, u32 arg7, u32 arg8);
bool pakRepair(s32 arg0);
u32 func0f11c39c(u32 arg0, s8 device, u32 ar2, u32 arg3);
void func0f11c54c(void);
void func0f11c6d0(void);
void pakExecuteDebugOperations(void);
void func0f11ca30(void);
void func0f11cb9c(u32 arg0);
s32 func0f11cbd8(s8 device, s32 arg1, char *arg2, u16 arg3);
s32 func0f11cc6c(s8 device, u16 arg1, char *arg2, u16 arg3);
s32 func0f11cd00(s8 arg0, s32 arg1, char *arg2, s32 arg3, bool arg4);
s32 func0f11ce00(s8 arg0, s32 arg1, char *arg2, s32 arg3, bool arg4);
u32 func0f11d118(void);
u32 func0f11d174(void);
u32 func0f11d214(void);
u32 func0f11d3f8(void);
u32 func0f11d478(void);
u32 func0f11d4dc(void);
s32 func0f11d540(s8 index, s32 arg1);
s32 func0f11d5b0(s8 index);
void func0f11d620(s8 device);
u32 func0f11d8b4(void);
u32 func0f11d9c4(void);
void func0f11dc04(s32 arg0, f32 arg1, s32 arg2, s32 arg3);
void func0f11dcb0(s32 arg0);
void func0f11dd58(s8 playernum);
void func0f11de20(s8 device);
void func0f11deb8(void);
void func0f11df38(void);
void pakDumpPak(void);
void func0f11df94(s8 device);
void func0f11e3bc(s8 device);
void pakProbeEeprom(void);
s32 pakReadEeprom(u8 address, u8 *buffer, u32 len);
s32 pakWriteEeprom(u8 address, u8 *buffer, u32 len);
void pakSetBitflag(u32 flagnum, u8 *bitstream, bool set);
bool pakHasBitflag(u32 flagnum, u8 *stream);
void pakClearAllBitflags(u8 *flags);
void func0f11e618(char *src, char *dst, u32 len);
s8 pakSearch(s32 arg0);
s32 func0f11e750(s8 arg0);
bool func0f11e78c(void);
bool func0f11e7f0(char *a, char *b);
s32 func0f11e844(s8 device);
bool func0f11ea34(s8 arg0);

extern const char var7f1b423c[];
extern const char var7f1b4244[];
extern const char var7f1b424c[];
extern const char var7f1b4254[];
extern const char var7f1b425c[];

#endif
