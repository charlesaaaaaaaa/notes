# malloc函数

* 该函数的功能是在内存中分配一块size大小的内存空间
  * `void * malloc(unsigned int size);`
* 使用malloc函数要包含stdlib.h头文件
* 成功会返回一个指针，指向分配的空间
  * 失败会返回NULL
* 示例
```
int *pLint;
pLnt= (int*)malloc(sizeof(int));
```
