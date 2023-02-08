# calloc函数

* calloc函数的功能就是在内存中动态分配n个长度为size的连续内存空间
  * `void * calloc(unsigned n, unsigned size);`
* 使用calloc函数要包含stdlib.h头文件。
* 成功时会返回一个指针，该指针会指向动态分配的连接内存空间的首地址
  * 失败时会返回NULL
* 示例
```
int *pArray;
pArray = (int*)calloc(3, sizeof(int*));
```
