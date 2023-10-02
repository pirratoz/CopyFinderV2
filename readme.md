# CopyFinder
This utility helps you find identical files by content

## Created with
![c++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=C%2B%2B&logoColor=white)
![QT](https://img.shields.io/badge/5.15.3-blue?style=flat&logo=qt&logoColor=white&labelColor=black)

## Flags
```sh
flag: --SB | --SizeBlock
description:
    Sets the block size to be memory-friendly.
    This flag allows you to limit reading from a file to N bytes.
description parameters:
    "param1" - unsigned integer (default 512)
examples:
    -sb 1024
    -sizeblock 2048
```
```sh
flag: -l
description:
    This flag allows you to enable/disable the ability to scan subdirectories.
examples:
    -l
```
```sh
flag: --sf | --SizeFile
description:
    This flag sets the minimum file size for identity checking.
description parameters:
    "param1" - unsigned integer (default 1)
examples:
    --fs 512
    --sizefile 1024
```
```sh
flag: --mf | --MaskFile
description:
    This flag sets the mask for scanned files.
description parameters:
    "params" - string (regexp)
examples:
    --mf ".*.txt" "test[0-9]+.py"
    --maskfile ".*.txt" ".*.jpg"
```
```sh
flag: --p | --Path
description:
    This flag allows you to add directories to check specific files.
description parameters:
    "params" - string (absolute path)
examples:
    --p "/home/dev/c++" "/home/dev/rust" "/home/dev/python" "/home/dev/asm"
    --path "/home/плохой путь с пробелом/c++" /home/good_path/
```
```sh
flag: --up | --uPath
description:
    This flag allows you to exclude directories for scanning.
description parameters:
    "params" - string (absolute path)
examples:
    --up "/home/dev/c++" "/home/dev/rust" "/home/dev/python" "/home/dev/asm"
    --upath "/home/плохой путь с пробелом/c++" /home/good_path/
```
## Examples of running the utility
```sh
./CopyFinderV2 -l --sf 16000 --p "/home/pirratoz/dev/c++/CopyFinderV2/DIR_FOR_TEST"
```
```sh
./CopyFinderV2 --path "/home/pirratoz/dev/c++/CopyFinderV2/DIR_FOR_TEST"
```
```sh
./CopyFinderV2 --mf ".*.py" --p "/home/pirratoz/dev/c++/CopyFinderV2/DIR_FOR_TEST"
```
```sh
./CopyFinderV2 --p /home/pirratoz/Pictures /home/pirratoz/dev/c++/CopyFinderV2/DIR_FOR_TEST --upath /home/pirratoz/dev/c++/CopyFinderV2/DIR_FOR_TEST/dir2 -l --sb 1024 --mf ".*.jpg"
```