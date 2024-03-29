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

## 常用汇编指令

1. MOV 将数据从一个寄存器拷贝到另一个寄存器
2. MRS 将【特殊寄存器】的值拷贝到【通用寄存器】
3. MSR 将【通用寄存器】的值拷贝到【特殊寄存器】

ARM 不能直接访问存储器，需要专门的【存储器访问指令】
1. LDR 把存储器中的值加载到寄存器中
2. STR 把寄存器中的值存储到存储器中

压栈出栈指令
1. PUSH
2. POP

跳转指令
1. B <label> 跳转到 label 处，实质：把 PC 值设置为跳转地址
2. BX <Rm> 跳转到 Rm 中的地址处，切换指令集
3. BL <label> 跳转到 label 处，把返回值地址存储到 LR 中，实质：跳转前把 PC 值保存到 LR 中
4. BLX <Rm> 跳转到 Rm 中的地址处，返回值地址保存到 LR 中，切换指令集