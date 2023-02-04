# enum -- 枚举类型

* 实际工作中，有的变量会有限定范围，如果这个时候直接使用基本数据类型或者其它类型，是不行的，因为他们都没有限定的范围
  * 所以就有了枚举类型
* 枚举类型也是一种基本类型，不能再被分拆
* 使用enum关键字声明，并使用枚举类型定义变量
* 一个枚举变量包含一组的相关的标识符，每个标识符都对应一个整数值，称为枚举常量

## 定义

```
enum eStu(first, second, third);
```
* 如上述例子，first的整数常量为0，second为2，third为3
* 如果给第一个枚举变量赋值为1，则之后的枚举变量都会在些基础上加1，如下
```
enum eStu1(first=1, second, third);
int main()
{
	int iInt;
	scanf('%d', &iInt);
	switch(iInt)
	{
		case first:
			puts("第一个");
			break;
		case second:
			puts("第二个");
			break;
		case third:
			puts("第三个");
			break;
		defult:
			puts("???");
			break;
	}
	return 0;
}
```

