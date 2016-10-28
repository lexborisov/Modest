# Modest C/C++ HTML Render

[![Build Status](https://travis-ci.org/lexborisov/Modest.svg?branch=master)](https://travis-ci.org/lexborisov/Modest)

Modest is a fast HTML Render implemented as a pure C99 library with no outside dependencies.

## Now

```text
The current version is 0.0.1 - devel
```

## Changes
Please, see [CHANGELOG.md] file

## Features

Render is in development. Now available:

- Search nodes by Selectors 
- See Features of [MyHTML]
- See Features of [MyCSS]

## Introduction

[Introduction]

## Build and Installation

**Make**

```bash
make
```

If successful copy lib/* and include/* at the right place for you

Flags that can be passed to make:
- `MODEST_OPTIMIZATION_LEVEL=-O2` set compiler optimization level. Default: -O2
- `MODEST_BUILD_WITHOUT_THREADS=YES` build without POSIX Threads. Default: NO

*for example*
```bash
make MODEST_BUILD_WITHOUT_THREADS=NO
```

```bash
cp lib/* /usr/local/lib
cp -r include/* /usr/local/include
```

**CMake**

In modest/project directory:

```bash
cmake .
make
sudo make install
```

Flags that can be passed to CMake:
- `MODEST_OPTIMIZATION_LEVEL=-O2` set compiler optimization level. Default: -O2
- `CMAKE_INSTALL_LIBDIR=lib` set path to install created library. Default: lib
- `MODEST_BUILD_SHARED=ON` build shared library. Default: ON
- `MODEST_BUILD_STATIC=ON` build static library. Default: ON
- `MODEST_INSTALL_HEADER=OFF` install header files. Default OFF
- `MODEST_BUILD_WITHOUT_THREADS=YES` build without POSIX Threads. Default: NO
- `MODEST_EXTERN_MALLOC=my_malloc_func` set extern malloc function. Default: UNDEFINED
- `MODEST_EXTERN_REALLOC=my_realloc_func` set extern realloc function. Default: UNDEFINED
- `MODEST_EXTERN_CALLOC=my_calloc_func` set extern calloc function. Default: UNDEFINED
- `MODEST_EXTERN_FREE=my_free_func` set extern free function. Default: UNDEFINED

*for example*
```bash
cmake . -DCMAKE_INSTALL_LIBDIR=lib64 -DMODEST_INSTALL_HEADER=ON
```


## Build with your program

I advise to build using clang, but decided to show examples of gcc

**for example**

*build with shared library*
```bash
gcc -Wall -Werror -O2 -lmodest your_program.c -o your_program
```

*build with static library*
```bash
gcc -Wall -Werror -O2 your_program.c /path/to/libmodest_static.a -o your_program
```

## Dependencies

None

## In other languages, external bindings

Send pull request if you create any bindings

## Examples

See [examples] directory

## AUTHOR

Alexander Borisov <lex.borisov@gmail.com>

## COPYRIGHT AND LICENSE

Copyright (C) 2015-2016 Alexander Borisov

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA

See the [LICENSE] file.


[high]: https://github.com/lexborisov/modest/blob/master/include/myhtml/api.h
[low]: https://github.com/lexborisov/modest/tree/master/include/myhtml
[examples]: https://github.com/lexborisov/modest/tree/master/examples
[MyHTML]: https://github.com/lexborisov/myhtml
[MyCSS]: https://github.com/lexborisov/mycss
[CHANGELOG.md]: https://github.com/lexborisov/modest/blob/master/CHANGELOG.md
[Introduction]: http://lexborisov.github.io/myhtml/
[LICENSE]: https://github.com/lexborisov/myhtml/blob/master/LICENSE
