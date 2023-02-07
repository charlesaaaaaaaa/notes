# 文件操作
* 文件操作是很重要一个基础知道，实际工作场景有很多地方都要用上文件操作。

## 文件指针
* 文件指针是一个指向文件有关信息的指针，这些信息包括文件名、文件位置和状态等全都保存在一个结构体当中
* 使用文件时需要在内存中为其分配空间，用来存放文件的基本信息。
* 该结构体类型由系统定义的，c语言规定该类型为FILE型
```
typedef struct
{
	short level;
	unsigned flags;
	char fd;
	unsigned char hold;
	short bsize;
	unsigned char *buffer;
	unsigned ar *curp;
	unsigned istemp;
	short token;
}FILE;
```

* 注意：在定义变量的时不必将结构内容全部给出，只需要写成如下形式就行
`FILE *fp;`
