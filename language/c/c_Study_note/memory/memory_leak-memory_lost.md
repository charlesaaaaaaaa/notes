# 内存泄露和内存丢失

## 内存泄露
* 在使用malloc函数和calloc函数分配过内存后，一定要记得还要用free函数释放内存
* 如果该程序很简单不会占用过多内存，free函数可以不用。但是如果该程序要使用malloc或者calloc函数分配多次内存，还不使用free函数释放内存，则会造成内存泄露
  * 如一个malloc一次要分配一个10MB的内存空间。然后循环10w次，那一共要100G的内存空间才可以运行完该程序，这就是内存泄露。如果用上了free函数，则只用10MB的内存就好了。

## 内存丢失
* 在使用malloc或者calloc函数分配了内存给pOne和pTwo两个指针变量时，把pOne的指针指向pTwo
  * 此时free(pOne)函数，但pOne指向的pTwo没有释放其内存空间，这里就会造成内存丢失  * 上述示例如下
```
pOne = (int*)malloc(sizeof(int));
pTwo = (int*)malloc(sizeof(int));

pOne = pTwo; //此时把pOne指向pTwo
free(pOne); //最后释放了pOne，但没有释放pTwo，这就是内存丢失
```
