# 内存管理
* 计算机程序的机器语言指令和数据库都是存放在同一个逻辑内存空间里的
* 程序编写完成后，需要先装到计算机的内核或者半导体内存中，然后才可以运行。计算机程序一般被组织成4个逻辑段：可执行代码，静态数据，动态数据(堆)和栈
  * 可执行代码和静态数据存放在固定的内存位置
  * 动态数据需要系统动态分配内存，一般存放在堆区的内存池中
  * 局部数据对象、函数对象，以及调用函数和被调用函数的联系，存放在栈区的内存池中
