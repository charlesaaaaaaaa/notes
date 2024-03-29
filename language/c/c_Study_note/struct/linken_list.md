* [链表](#链表)
  * [创建链表](#创建链表)
  * [输出链表](#输出链表)
  * [完整示范](#完整示范)
* [结点操作](#结点操作)
  * [插入结点](#插入结点)
  * [删除结点](#删除结点)
# 链表

* 要实现链表，就要用到指针，所以链表中的所有结点都会包含一个指针变量，保存下一个结点的地址
* 一个链表结点，要包含两个部分，一个是存放数据的地方，称之为元素域；另一个是存放下一个结点的指针变量，称为指针域
* 每一个已完成的链表，最后一个结节的指针变量所指向的地址应该为NULL，如果只有一个结点则认为该结点的指针变量为NULL。
* 注意这三个函数：
  * malloc 
    * 动态分配一个size大小的内存空间
    * void malloc(unsigned int size)
  * calloc
    * 动态分配n个size大小的内存空间
    * void calloc(unsigned int n, unsigned int size)
  * free
    * 释放str指针所占的内存空间
	* free(void *str)

## 创建链表
```
// 现在新建一个名为Student的结点
struct Student
{
	char cName[20];
	int iNum;
	struct Student *pNext; //这个地方使用pNext指针指向下一个结节
};      

int iCount; //声明一个全局变量，表示链表的长度

struct Student *Create()
{
	struct Student *pHead = NUll; //定义一个头指针，这时应该为NULL;
	struct Student *pEnd, *pNew; //定义一个尾指针，和一个指向下一个结节的新指针

	pEnd = pNew = (struct Student*)molloc(sizeof(struct Student)); //动态分配一个新的内存空间
	if(pNew == NULL) //当分配空间时失败了，molloc会返回NULL，如果失败了应该及时停下
	{
		exit(1); 
	}
	puts("请输入学生的名字和编号，结束时按两次回车");
	scanf("%s", pNew -> cName);
	scanf("%s", pNew -> iNum);
	while(pNew -> iNum !=0 ) //判断当学生学号不为0时，则进行循环
	{
		iCount++; //结点数加1
		if(iCount == 1) //当只有一个节点时，结节的指针变量应该为头指针，就是上面为NULL的指针
		{
			pNew -> pNext = pHead; //新结节的指针变量为空
			pEnd = pNew; //把pNew赋给尾指针，使原来的尾指针指向新的结节
			pHead = pNew; //这个时候头指针应该指向新结节
		}
		else
		{
			pNew -> pNext = NULL; //新结节的指针变量一定为空
			pEnd -> pNext = pNew; //原来的结点指针指向新的结点
			pEnd = pNew; //pEnd 指向新结节
		}
		pEnd = pNew = (struct Student*)molloc(sizeof(struct Student); //重新分配动态内存空间
		if(pNew == NULL)
		{
			exit(1);
		}
		scanf("%s", pNew -> cName);
		scanf("%s", pNew -> iNum); //为下一次循环做准备
	}
	free(pNew); //当输入的iNum为0时，代表输入结果了，用free函数释放掉空的指针所占的内存空间资源
	return 0;
}
```

* 从上述示例可以看出来，一个链表，要声明一个有元素域和指针域的结点（结构体）
* 再各声明一个头指针结点、尾指针结点、新指针结点。其中头指针节点应该为NULL且只用在第一个结节上就好了
* 使用malloc或者calloc函数动态分配结点的内存空间
* 当前结节的计数为1时
  * 将头指针指向新指针的结点上，且把新指针分别给到尾结点和头指针，这时旧的结点有对应的元素且指向了NULL
* 当前结点的计数超过1时
  * 这个时候用不上了头指针了，所以我们这时就不用去管头指针了
  * 新指针指向的结点一定是NULL
  * 尾指针的指针应该指向新结点
  * 再把pEnd指向pNew

## 输出链表
```
void Print(struct Student *pHead)
{
	int iIndex = 1;
	struct Student *pTemp;// 定义一个临时的变量来存放结点
	pTemp = pHead;

	while(pTemp != NULL)
	{
		printf("NO.%d Student:", iIndex);
		printf("name: %s, ", pTemp -> cName);
		printf("age: %d\n", pTemp -> iNum);
		pTemp = pTemp -> pNext; //这个时候临时变量指向了pNext，而pNext存放下一个节点的地址，所以相当于指向了下一个结点
		iIndex++
	}
}
```
* 在输出的时候只要记住要一个临时的结构体指针变量来存放结点就行
* 在输出完所有的元素域时，把临时的指针变量指向pNext来指向下一个结点的地址

## 完整示范
```
#include "stdio.h"
#include "stdlib.h"

int main()
{
	struct Student *pHead; //定义一个首结点
	pHead = Create();//创建一个首节点，调用Create函数并把返回值给到pHead指针
	Print(pHead); //利用pHead指针作为Print函数的参数
	return 0;
}
```
* 完整的一个简单链表把创建链表和输出链表的示例部分copy到main函数前面就行了
  * 写太多会有点影响观感
# 结点操作

## 插入结点
* 插入结点有三种情况，一个是在插在首节点，一个是插在中间位置，最后一个是插到最后一个
  * 这三个都是把前结点的指针指向要插入的结点，要插入的结点再把指针指向后一个结点

## 删除结点
* 结点的删除，就是把**对应位置结点的前一个结点**的指针指向**对应位置结点的后一个结点**，随后用free函数释放掉对应的结点
  * 所以要定义一个**临时结点**和**前结点**
* 删除一个节点，首先我们要知道要删除的结点在第几个
* 当知道了结点的编号后，循环该编号的次数
  * 每次循环，把临时变量给到前结点
  * 再把临时变量的指针指向的地址给到临时变量
  * 循环到第编号次，就找到了要用的
* 循环完毕，把前结点和后结点连接
* 释放当前的临时结点
```
void Delete(struct Student *pHead, int iIndex)
{
	struct Student *pPre; //定义一个前结点
	struct Student *pTemp; //定义一个临时结点
	pTemp = pHead; // 把头结点给到临时结点
	pPre = pTemp; //把临时节点给到前结点

	for(int i = 1; i < iIndex; i++) //注意i初始值应该为1
	{
		pPre = pTemp; //把临时结点给到头结点
		pTemp = pTemp -> pNext; //临时结点指向下一个结点的指针
	}
	pPre -> pNext = pTemp -> pNext; //把临时结点的指向的下一个地址给到前结点指向的地址，也就是完成了头结点和后结点的连接
	free(pTemp); //使用free函数释放掉临时结点
	iCount--; //iCount是之前的链表里的iCount变量，就是结点的结点数。因为删除了一个结点，所以这里结点数也要减少1
}

//加入删除操作
int main()
{
	struct Student *pHead(); //定义头结点
	pHead = Create(); //把头结点给到Create函数创建链表
	Delete(pHead); //执行删除操作
	Print(pHead); //打印链表
	return 0;
}
```
