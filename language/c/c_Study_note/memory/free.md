# free函数
* free函数的功能就是释放指针ptr指向的内存区域，使该区域能被其它变量所使用
  * `void free(void *ptr);`
* 其中，ptr是最近一次调用calloc或者malloc函数时返回的值，free函数无返回值
```
free(pInt);
```
