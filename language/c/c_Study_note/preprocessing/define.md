# defind -- 宏定义
* #define宏定义是一个预处理命令，和变量不同，宏定义只做字符替换，不分配内存空间
* 使用#define宏定义的好处是如果有一个常量要被多次引用，若需要修改其值，直接修改#define命令行就行。
* [不带参数的宏定义](#不带参数的宏定义)
* [带参数的宏定义](#带参数的宏定义)
## 不带参数的宏定义
* 一般宠定义的形式如下
  * `#define 宏名 字符串`
  * 宏名虽然没有大小写限定，但一般都是全大写来表示这是一个宏定义
* 字符串可以是常数，表达式，格式字符串等,以下都是正确的宏定义
```
#define SIDE 5
#define PERIMETER 4*SIDE
#define AREA SIDE*SIDE
#define STANDARD "you are welcome to join us"
```

* 注意：在字符串，也就是用双引号里面遇到宏定义名是不生效的
```
#define TEST "i am you father!"
int main()
{
	char a[30] = "this TEST"
	printf(TEST);
	printf("%s\n", a);
	return 0
}
```
```
i am you father!
this TEST
```

## 带参数的宏定义
* 宏定义还可以带参数，示例如下
```
define ADD(a,b,c) ((a)*((b)+(c)))
int main()
{
	int x = 3, y = 6, z = 8;
	printf("add = %d\b", add(y, x, z));
	return 0;
}
```
```
add = 66;
```

* 注意：
  * 宏定义时一定要给参数加上括号
  * 宏定义时，宏名与带参数的括号之间不要加空格，否则会认识空格后面的字符全认为是要替换的字符串一部分
  * 在带参数的宏定义里，形参不分配内存单元，所以不用做类型定义
