#include <ultra64.h>
#include "libultra_internal.h"
#include "constants.h"
#include "bss.h"
#include "lib/lib_06100.h"
#include "lib/lib_06330.h"
#include "lib/lib_4b170.h"
#include "lib/lib_4e090.h"
#include "lib/lib_513b0.h"
#include "data.h"
#include "types.h"

s32 osPfsFileState(OSPfs *pfs, s32 fileNo, OSPfsState *state)
{
	s32 ret;
	s32 pages;
	__OSInode inode;
	__OSDir dir;
	__OSInodeUnit page;
	u8 bank;

	if (fileNo >= pfs->dir_size || fileNo < 0) {
		return PFS_ERR_INVALID;
	}

	if (!(pfs->status & PFS_INITIALIZED)) {
		return PFS_ERR_INVALID;
	}

	if ((ret = __osCheckId(pfs)) != 0) {
		return ret;
	}

	if (pfs->activebank != 0 && (ret = __osPfsSelectBank(pfs, 0)) != 0) {
		return ret;
	}

	if ((ret = __osContRamRead(pfs->queue, pfs->channel, pfs->dir_table + fileNo, (u8*)&dir)) != 0) {
		return ret;
	}

	if (dir.company_code == 0 || dir.game_code == 0) {
		return PFS_ERR_INVALID;
	}

	page = dir.start_page;
	pages = 0;
	bank = 0xff;

	while (true) {
		if (page.ipage < pfs->inode_start_page) {
			break;
		}

		if (page.inode_t.bank != bank) {
			bank = page.inode_t.bank;

			if ((ret = __osPfsRWInode(pfs, &inode, PFS_READ, bank)) != 0) {
				return ret;
			}
		}

		pages++;
		page = inode.inode_page[page.inode_t.page];
	}

	if (page.ipage != 1) {
		return PFS_ERR_INCONSISTENT;
	}

	state->file_size = pages * PFS_ONE_PAGE * BLOCKSIZE;
	state->company_code = dir.company_code;
	state->game_code = dir.game_code;

	bcopy(&dir.game_name, state->game_name, PFS_FILE_NAME_LEN);
	bcopy(&dir.ext_name, state->ext_name, PFS_FILE_EXT_LEN);

	return __osPfsGetStatus(pfs->queue, pfs->channel);
}
