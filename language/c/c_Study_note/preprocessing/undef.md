# #undef命令
* 如果我们在定义好一个宏定义时，到任意某处我们不希望这个宏定义会生效
  * 这个时候就可以使用#undef命令
* #undef一般使用形式
`#undef 宏替换名`  
```
#define 宏替换名 字符串
	int a ...
	struct b ...
	void c...
	int main...
	等任意语句行
#undef 宏替换名
```
* #undef可以在文件里任意地方生效
