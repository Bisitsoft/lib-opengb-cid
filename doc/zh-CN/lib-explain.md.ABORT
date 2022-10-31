[中文](./lib-explain.md)
[返回首页](../../README.md)

**<font color="red">！哦，快找个工具来创建这个文档，这样子直接用markdown编写引用不得累死！</font>**

# 库解释



## 命名空间

### `opengb`命名空间

*

### `opengb::cizidn`命名空间

* *我们使用`opengb::cizidn`而不是`opengb::cid`作为命名空间是因为这可能会和常用变量名`cid`冲突，所以我们起了一个较长的名字。*

## 开关

### `OPENGB_CODE_PREFER_FAST`宏定义、`OPENGB_CODE_PREFER_TIGHT`宏定义

我们提供了两种代码，一种是高效的代码，定义`OPENGB_CODE_PREFER_FAST`宏定义来开启；一种是低内存使用的代码，定义`OPENGB_CODE_PREFER_TIGHT`宏定义来开启。二者互斥，通过[`ckdef_code_prefer.h`](#ckdefcodepreferh头文件)中的宏检查。

---

# `areacode.h`头文件

* 暂未实现，是占位符文件。将来可能会迁至新的仓库——`lib-opengb-area`。

---

# `ckdef_code_prefer.h`头文件

* 用于检查`OPENGB_CODE_PREFER_<preference>`宏定义冲突的头文件。

---

# `cizidn.h`头文件

* 这个头文件是用于实现身份证号类的。

## 宏定义

### `OPENGB_CID_<number>CID_LENGTH`宏定义、`OPENGB_CID_<number>CID_<part>_LENGTH`宏定义

* 定义身份证号或者其中某一部分长度。

## 类型定义

### `OPENGB_CID_<part>_TYPE`宏定义

* 定义[`opengb::cizidn::S_CitizenId`](#opengbcizidnscitizenid类)中各部分类型。

## `opengb::cizidn::S_CitizenId`结构体

* 包含身份证号中`地区码`、`生日`、`顺序码`、`校验码`。

## `opengb::cizidn::CitizenId`类

* 用于存储与处理身份证号码的类。

### 属性

#### `m_cid`

*

### 构造函数

#### `CitizenId()`函数

* 构造[`opengb::cizidn::CitizenId`](#opengbcizidncitizenid类)类。

#### `CitizenId(OPENGB_CID_AREA_TYPE area, OPENGB_CID_BIRTHDAY_TYPE birthday, OPENGB_CID_ORDER_TYPE order, OPENGB_CID_CHECKSUM_TYPE checksum, bool check_cid)`函数

* 构造[`opengb::cizidn::CitizenId`](#opengbcizidncitizenid类)类。

##### 参数

* `check_cid`：是否检查身份证号的正确性。默认为`true`。

---

# `main.cpp`源文件

* 用来测试该库的函数。

---

# `mod11_2.h`头文件

* 这个头文件是用于实现用于计算身份证号码的校验码的。实现基于`GB 11643-1999`中所叙述的`ISO 7064:1983`中的`MOD 11-2`算法。

## 宏定义

### `_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER`宏定义

* **不要改动！**

### `_OPENGB_MOD11_2_METHOD(opengb::cizidn::CitizenId _18cid)`函数

* 用于计算身份证的校验码。

* **`_18cid`请务必使用18位身份证号！**

***... ...***

---

# `opengb_cid_rcmd.h`头文件

* 包含必要的`lib-opengb-cid`的头文件与推荐的宏定义配置。

## 引用的头文件

* [`ctzidn.h`](#cizidnh)
* [`mod11_2.h`](#mod112h)
* [`opengbex.h`](#opengbexh)

## 声明的宏定义

* [`OPENGB_CODE_PREFER_FAST`](#opengbcodepreferfast宏定义opengbcodeprefertight宏定义)：使用快速的方法。如果在该头文件之前声明[`OPENGB_CODE_PREFER_TIGHT`](#opengbcodepreferfast宏定义opengbcodeprefertight宏定义)，则该[`OPENGB_CODE_PREFER_FAST`](#opengbcodepreferfast宏定义opengbcodeprefertight宏定义)声明会自动被屏蔽。

---

# `opengbex.h`头文件

* 这个头文件是用于集中存放`OpenGB`的异常类。

## `opengb::OpenGBException`类

* 继承自`exception`库中的`std::exception`。
* *是大部分[`opengb`](#opengb命名空间)的异常类的基类。*

## `opengb::CitizenIdException`类

* 继承自[`opengb::OpenGBException`](#opengbopengbexception类)。
* *是大部分[`opengb::cizidn`](#opengbcizidn命名空间)的异常类的基类。*

## `opengb::Not18CIdException`类

* 继承自[`opengb::CitizenIdException`](#opengbnot18cidexception类)。
* 用于表示某个参数不是18位的身份证号。

---
