# **Expression 表达式计算**
这份代码是用于将中缀表达式转换成后缀表达式（逆波兰表达式）并计算表达式的值（其中我将显示后缀表达式的部分注释）

## **expr.cpp**
转换的主函数，将从expr.txt中读取的表达式转换并计算出值

## **random.cpp**
生成随机的数据，构成合法的中缀表达式

## **test.cpp**
一份很简单的测试数据，但代表了我之前忽略的一个细小的知识

## **expr.in**
存储随机生成的中缀表达式

----
----

# **Summary**
表达式计算是对数据结构 栈 的应用，我在之前的学习过程中就一直无法快速将他完成，这次又重新编写，使用新的方法，
也尝试写了随机测试数据生成器，但没有注意到一些问题，那就是***被除数不能是0***（错误代码的编号：3221225620）
一个小问题，真的花费很多时间才将它解决。  
有关于表达式计算具体如何实现，可以看我的博文 https://blog.csdn.net/qq_43575926/article/details/95041517
