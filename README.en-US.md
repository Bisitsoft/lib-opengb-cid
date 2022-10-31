[中文](./README.md)|[English](./README.en-US.md)

---

# lib-opengb-cid Library

`OpenGB` is a library for implement functions of `GB` (China national standrad).

`lib-opengb-cid` is for `GB 11643-1999` (Citizen identification number).

## Compilation

We recommand use `make` or `mingw32-make` .etc to assist comiplation. `makefile` use `gcc` as default compilation tool.

### Compile Static Library

Compilation of static library requires `ar`.

Please execute following commands in repository root directory:
```bash
cd src
make static-library #Or: mingw32-make static-library
```

The library will be generated to `src/lib-opengb-cid.a`.

### Compile Shared Library

Please execute following commands in repository root directory:
```bash
cd src
make shared-library #Or: mingw32-make shared-library
```

The library will be generated to `src/lib-opengb-cid.so`.

### Compile Test Program

Please execute following commands in repository root directory:
```bash
cd src
make test #Or: mingw32-make test
./test.exe
```

The test program will be generated to `src/test.exe`.

## Implementations

**The current IDE is `VSCode`.**

<!--[Library Explainations](./doc/en-US/lib-explain.md)-->
View the comment in the code file for explainations.

---

# Contributors

## Programmer
* [Orange233](https://github.com/Orange23333)

---

**Copyright (c) [Bisitsoft](https://www.ourorangenet.com) 2022.**

View source code on **[Github](https://github.com/Bisitsoft/lib-opengb-cid).**