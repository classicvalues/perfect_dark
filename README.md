# Perfect Dark Decompilation (WIP)

This repository contains a work-in-progress decompilation of Perfect Dark for the Nintendo 64.

## Status

See the [Perfect Dark Decompilation Status Page](https://ryandwyer.gitlab.io/pdstatus/).

## Installation Requirements

For Arch Linux:

* Install these packages: `binutils fakeroot gcc make python vim`
* Install from AUR: `mips64-elf-binutils`

For Debian and Ubuntu:

* Install these packages: `binutils-mips-linux-gnu make`

## ROM Versions

Perfect Dark has six known versions:

| ROM ID     | Description                                                   |
|------------|---------------------------------------------------------------|
| ntsc-beta  | NTSC 6.4 beta - supported but mismatching                     |
| ntsc-1.0   | NTSC 8.7 final (the initial, buggy release) - fully supported |
| ntsc-final | NTSC 8.7 final - fully supported                              |
| pal-beta   | PAL 28.7 beta - can extract assets only                       |
| pal-final  | PAL 8.7 final - supported but mismatching                     |
| jpn-final  | Japanese 8.7 final - can extract assets only                  |

The project uses the `$ROMID` environment variable to know which version to work with. If not set, it defaults to `ntsc-final`. You can change it by running something like `export ROMID=ntsc-1.0`.

## Extracting the base ROM

Before you do anything you need an existing ROM to extract assets from.

1. Save your existing ROM file into the root of the repository with the name `pd.ntsc-final.z64`. It should not be byteswapped (the first four bytes should be `0x80371240`).
2. Run `make extract`.

This will extract assets to `src/assets`. If any asset already exists then it will not be overwritten. This means you can modify assets as desired, and your changes will not be overwritten if you run the extract command again.

The extract command will also create an `extracted/ntsc-final` directory. This directory contains some compiled code segments from the ROM and is only used for comparison purposes.

## Compiling

* Run `make -j` to build the ROM. The ROM will be written to `build/ntsc-final/pd.z64`.

## How do I know the built files are matching?

Run `make` followed by `make test`. If `make test` produces no output then the compiled project is matching.

You can also md5sum your base ROM with the built ROM and check they have the same hash: `md5sum pd.ntsc-final.z64 build/ntsc-final/pd.z64`.
