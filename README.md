# Brainfuck解释器

linux环境下c++写的解释器


# 语法规则

```c++
>   // ++ptr;
<   // --ptr;
+   // ++*ptr;
-   // --*ptr;
.   // 输出指针指向单元的内容
,   // 输入内容到指针指向单元
[   // 循环块的开始
]   // 循环块的结束(如果执行该代码时 \*ptr 值为0,则跳出循环)
```

# 使用

编译

```shell
g++ src/*.cpp -std=c++11 -o bf
```

执行

```shell
./bf bf_file/helloworld.b
```

# 功能

带有终端打印可视化效果

效果

![brainfuck](https://github.com/changdingfang/brainfuck/blob/master/imgs/brainfuck.gif)
