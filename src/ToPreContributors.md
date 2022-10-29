[中文](#致预备贡献者) | [English](#To-Pre-contributors)

---

# 致预备贡献者

## 一些名称

* `CId`、`CizIdN`：全称“Citizen Identification Number”，身份证号。

* `EV`：全称“Extend Values”，扩展值。

## 一些命名规则（建议）

这个规则与其说是规范代码，倒不如说是能够让你更好的结合以下的规则去读懂我们的代码。

### 变量

主要针对全局变量或常量。但没什么特别要求。

### 函数

大部分采用大驼峰（帕斯卡）。对于不公开函数，或者非直接被调用函数（如`ctzidn.h`中的`_gb11643_1999_mod11_2_tt`函数），使用小驼峰法，再加上一个`_`做前缀，表示不应当随意的直接调用。

建议用驼峰法+下划线，此时下划线作域分隔符，如`OpenGB_CId_DoSomething()`或者写成`opengb_cid_DoSomething()`

### 宏定义

宏定义函数每个单词或缩写用下划线分隔，一组单词的缩写可以理解则不用分隔。

对于不公开函数、非直接被调用函数或代码块（如`opengbex.h`中的`_OPENGB_THROW`宏定义函数），加上一个`_`做前缀，表示不应当随意的直接调用。

### 其他字段

虽然`typedef`有其的优点，但是因为不大会使，经常报错，所以就干脆全用宏定义了。

## 导读

库中主要有两个部分：身份证号处理（主要功能）与异常机制。

行政区划码将来会专门用一个仓库存储，而本库会引用它。

### 身份证号处理

文件：`ctzidn.c`和`ctzidn.h`。

包含用于存储身份证号的`CitizenId`结构体，一些身份证号常数宏，身份证号处理函数以及`Mod11/2`验证方法。

### 异常处理机制

文件：`opengbex.c`和`opengbex.h`。

我们采用了类似`errno`的机制，并在此基础上扩展了可选的附带更多信息功能。

部分错误码仅仅是临时存放于此。

## 注意事项

* 如你所见，不要乱动`opengb_cid_switches.h`中的第一个`zone`，这个通知机制很脆弱。*（它似乎是为了一个已经解决的问题而产生的，现在仅仅只是用作第一次使用通知。或许现在可以移除或者变成别的什么？）*

## 翻译

如果你希望帮助我们进行翻译，请提交`Issus`或者`Pull Request`。

## 最后

感谢每一个人的参与！`:>`

*备注：虽然目前这个项目只有我一个人，但是为了以后不用改，这里用了“我们”这个词。*

<p align="right">——OurOpenSource项目组</p>

---

# To Pre-contributors

## Some Names

* `CId`, `CizIdN`: Full name is "Citizen Identification Number".

* `EV`: Full name is "Extend Values".

## Some Name Rules (Suggestions)

This rule is not so much to regulate the code as to enable you to better understand our code in combination with the following rules.

### Variables

Mainly for variables and constants. There is not any special rules.

### Functions

Large Hump (Pascal) is mostly adopted. To private funtions or non-directly calling funtions (such as `_gb11643_1999_mod11_2_tt` function in `ctzidn.h`), We use Small Hump with a `_` as prefix to indicate that it should not be called directly at will.

We suggest use Hump + underscores. The underscores is used as the separators. Such as `OpenGB_CId_DoSomething()` or `opengb_cid_DoSomething()`.

### Macro Definations

Every words in macro function names use underscores as separators. The abbreviation of a group of words needn't separate.

To private funtions or non-directly calling funtions or code blocks (such as `_OPENGB_THROW` macro funtion in `opengbex.h`), we added a `_` as prefix to indecate that it should not be called directly at will.

### Other Words

Although `typedef` has its own advantages, it is not easy to use and often reports errors. Therefore, all of `typedef` has insteaded with macro definations.

## Guide

Library has 2 main part: CId processing and exception handling mechanism.

Administrative Division Code will ues an appropriative repository to store. And this library will refer it.

### CId Processing

Files: `ctzidn.c` and `ctzidn.h`.

It contains the `CitizenId` structure used to store the ID number, some ID number constant macros, some ID number processing functions, and the `Mod11/2` authentication method.

### Exception Handling Mechanism

Files: `opengbex.c` and `opengbex.h`.

We used a mechanism similar to `errno`. Based on it, we extend an optional attach more information function.

Some error code just store here temporarily.

## Attention

* As you can see, Don't touch the first `zone` in `opengb_cid_switches.h` in will. This notification mechanism is very fragile. *(It was bore for an resolved problem. It is just work as first use notification. Maybe we could remove it or tansfer to something else?)*

## Translation

If you want help us to make translation, please commit `Issus` or `Pull Request`.

## Final

Thanks for erveryone's participation! `:>`

*P.S.: Although I am the only one in this project, the word "we" is used here in order not to change it in the future.*

<p align="right">- OurOpenSource Group</p>
