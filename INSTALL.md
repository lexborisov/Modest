# Modest: Build and Installation

## make

In root directory:
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

and copy to the right place for you
```bash
cp lib/* /usr/local/lib
cp -r include/* /usr/local/include
```

## cmake

In `project` directory:
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
- `MODEST_INSTALL_HEADER=OFF` install header files. Default ON
- `MODEST_BUILD_WITHOUT_THREADS=YES` build without POSIX Threads. Default: NO
- `MODEST_EXTERN_MALLOC=my_malloc_func` set extern malloc function. Default: UNDEFINED
- `MODEST_EXTERN_REALLOC=my_realloc_func` set extern realloc function. Default: UNDEFINED
- `MODEST_EXTERN_CALLOC=my_calloc_func` set extern calloc function. Default: UNDEFINED
- `MODEST_EXTERN_FREE=my_free_func` set extern free function. Default: UNDEFINED

*for example*
```bash
cmake . -DCMAKE_INSTALL_LIBDIR=lib64 -DMODEST_INSTALL_HEADER=ON
```
