[中文](#致预备贡献者)|[English](#To-Pre-contributors)

---

# 致预备贡献者

## 一些命名规则（建议） Some Name Rules (Suggestions)

这个规则与其说是规范代码，倒不如说是能够让你更好的结合以下的规则，去读懂我们的代码。

### 变量 Variables

主要针对全局变量或常量。但没什么特别要求。

### 函数 Functions

大部分采用大驼峰（帕斯卡）。对于不公开函数，或者非直接被调用函数（如`ctzidn.h`中的`_gb11643_1999_mod11_2_tt`函数），使用小驼峰法，再加上一个`_`做前缀，表示不应当随意的直接调用。

建议用驼峰法+下划线，此时下划线作域分隔符，如`OpenGB_CId_DoSomething()`或者写成`opengb_cid_DoSomething()`

### 宏定义 Macro Definations

宏定义函数每个单词或缩写用下划线分隔，一组单词的缩写锁国可以理解则不用分隔。

对于不公开函数、非直接被调用函数或代码块（如`opengbex.h`中的`_OPENGB_THROW`宏定义函数），加上一个`_`做前缀，表示不应当随意的直接调用。

### 其他字段 Other Words

虽然`typedef`有其的优点，但是因为不大会使，经常报错，所以就干脆全用宏定义了。

## 翻译 Translation

如果你希望帮助我们进行翻译，请提交`Issus`或者`Pull Request`。

## 最后 Final

感谢每一个人的参与！`:>`

<p align="right">——OurOpenSource项目组</p>

---

# To Pre-contributors

## Some Name Rules (Suggestions)

这个规则与其说是规范代码，倒不如说是能够让你更好的结合以下的规则，去读懂我们的代码。

### Variables

主要针对全局变量或常量。但没什么特别要求。

### Functions

大部分采用大驼峰（帕斯卡）。对于不公开函数，或者非直接被调用函数（如`ctzidn.h`中的`_gb11643_1999_mod11_2_tt`函数），使用小驼峰法，再加上一个`_`做前缀，表示不应当随意的直接调用。

建议用驼峰法+下划线，此时下划线作域分隔符，如`OpenGB_CId_DoSomething()`或者写成`opengb_cid_DoSomething()`

### Macro Definations

宏定义函数每个单词或缩写用下划线分隔，一组单词的缩写锁国可以理解则不用分隔。

对于不公开函数、非直接被调用函数或代码块（如`opengbex.h`中的`_OPENGB_THROW`宏定义函数），加上一个`_`做前缀，表示不应当随意的直接调用。

### Other Words

虽然`typedef`有其的优点，但是因为不大会使，经常报错，所以就干脆全用宏定义了。

## Translation

如果你希望帮助我们进行翻译，请提交`Issus`或者`Pull Request`。

## Final

Thanks for erveryone's participation! `:>`

<p align="right">-OurOpenSource Group</p>
