# realloc函数
* realloc函数的功能是把ptr指针指向的内存空间大小改为size
  * `void * realloc(void *ptr, size_t size);`

* 使用realloc函数要包含stdlib.h函数
* size表示新分配的内存空间大小，其值可以是任意的
  *可以比原来的大，也可以比原来的小
* 返回值是一个指向新地址的指针
  * 如果出现错误则返回NULL
* 示例：把分配的实型大小改为整型大小
```
fDouble = (double*)malloc(sizeof(double));
iInt = realloc(fDouble, sizeof(int));
```
