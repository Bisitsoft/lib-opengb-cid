# lib-opengb-cid

`OpenGB`是一个用于实现`GB`（国标）中的功能的库。 `OpenGB` is a library for implement functions of `GB` (China national standrad).

这个子库适用于`GB 11643-1999`（公民身份证号）的。 This sub-library is for `GB 11643-1999` (Citizen identification number).

## 实现 Implementations

### cizidn.h

这个头文件是用于实现身份证号类的。 This header file is for implement the class of ID number.

* `opengb::cid`

### mod11_2.h mod11_2.cpp

这个头文件是用于实现用于计算身份证号码的校验码的。 This header file is for implement the function for calculate the check code of ID number.
实现基于`GB 11643-1999`中所叙述的`ISO 7064:1983`中的`MOD 11-2`算法。 This header file is implement the algorithm of `ISO 7064:1983` MOD 11-2 which is described in `GB 11643-1999`.

---

Copyright (c) [Bisitsoft](https://www.ourorangenet.com) 2022.

View code on [Github](https://github.com/Bisitsoft/lib-opengb-cid).