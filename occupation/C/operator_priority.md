在C语言中，运算符的优先级决定了在表达式中运算符的计算顺序。优先级高的运算符会先进行计算。运算符的优先级从高到低可以分为以下几个层次，并且每个层次的运算符还具有相应的结合性（左结合或右结合）。

以下是C语言中常用运算符的优先级表，从高到低排列：

| 优先级 | 运算符类型       | 运算符                          | 结合性     |
|--------|------------------|--------------------------------|------------|
| 1      | 括号与数组下标   | `()`、`[]`、`.`、`->`         | 左结合     |
| 2      | 单目运算符       | `!`、`~`、`++`、`--`、`+`、`-`、`*`、`&`、`sizeof` | 右结合     |
| 3      | 指数运算符       | `**`（非标准，有些编译器支持） | 右结合     |
| 4      | 乘除取模运算     | `*`、`/`、`%`                 | 左结合     |
| 5      | 加减运算         | `+`、`-`                      | 左结合     |
| 6      | 移位运算         | `<<`、`>>`                    | 左结合     |
| 7      | 关系运算         | `<`、`<=`、`>`、`>=`          | 左结合     |
| 8      | 相等性运算       | `==`、`!=`                    | 左结合     |
| 9      | 位与运算         | `&`                           | 左结合     |
| 10     | 位异或运算       | `^`                           | 左结合     |
| 11     | 位或运算         | `|`                           | 左结合     |
| 12     | 逻辑与运算       | `&&`                          | 左结合     |
| 13     | 逻辑或运算       | `||`                          | 左结合     |
| 14     | 条件运算符       | `? :`                         | 右结合     |
| 15     | 赋值运算符       | `=`、`+=`、`-=`、`*=`、`/=`、`%=`、`<<=`、`>>=`、`&=`、`^=`、`|=` | 右结合     |
| 16     | 逗号运算符       | `,`                           | 左结合     |

### 示例解析

给定一个表达式：

```c
int a = 5, b = 10, c = 15;
int result = a + b * c > b && a || b;
```

解析过程如下：

1. **乘法 `*`** 的优先级高于 **加法 `+`** 和 **关系运算符 `>`**，所以先计算 `b * c`。
2. 接下来计算 `a + (b * c)`。
3. 然后计算关系表达式 `(a + b * c) > b`。
4. 然后执行 **逻辑与 `&&`** 操作，再执行 **逻辑或 `||`** 操作。

### 注意点

- **优先级和结合性**：高优先级运算符先计算，结合性决定了相同优先级运算符的计算方向。
- **括号优先**：使用括号可以改变默认的优先级，有助于提升代码的可读性。
- **赋值运算符结合性**：赋值运算符的结合性是右结合，因此可以连续赋值，如 `a = b = c = 10`。

### 总结

运算符优先级是C语言表达式计算的重要规则。合理运用运算符优先级和括号可以确保表达式按照预期顺序进行计算，避免潜在的错误。