# 7.1 GNU 汇编语法

ARM 汇编，使用 GCC 编译器，需要符合 GNU 语法。

GNU 汇编语句有3个可选部分：

```
label: instruction @ comment
```

label 是标号，地址位置，也可以表示数据地址。

instruction 是指令

@ 后面是注释

.section 可定义 段