[中文](./README.md)|[English](./README.en-US.md)

---

# lib-opengb-cid 库

`OpenGB`是一个用于实现`GB`（国标）中的功能的库。

`lib-opengb-cid`是用于`GB 11643-1999`（公民身份证号）的。

## 编译

建议使用`make`或`mingw32-make`等工具帮助编译，`makefile`默认使用`gcc`作为编译工具。

### 编译静态库

编译静态库依赖生成工具`ar`。

请在仓库根目录下执行：
```bash
cd src
make static-library #或：mingw32-make static-library
```

库将生成为`src/lib-opengb-cid.a`。

### 编译共享库

请在仓库根目录下执行：
```bash
cd src
make shared-library #或：mingw32-make shared-library
```

库将生成为`src/lib-opengb-cid.so`。

## 实现

**当前是用的IDE是`VSCode`。**

<!--[库解释](./doc/zh-CN/lib-explain.md)-->
程序解释请看代码注释。

---

# 贡献者

## 代码
* [Orange233](https://github.com/Orange23333)

---

**Copyright (c) [Bisitsoft](https://www.ourorangenet.com) 2022.**

在 **[Github](https://github.com/Bisitsoft/lib-opengb-cid).** 上浏览源代码。
