## 局部变量

* 嵌套：
  * 在一个嵌套中，如下层的嵌套所有的变量不会影响到其它层的嵌套，不同层的嵌套变量可以同名
  * 反之，相同层级的嵌套变量不可以同名,此为局部变量的**隔离性**
  * 示例：
```
#include "stdio.h"

int main()
{
	for(int i = 0; i < 2; i++)
	{
		printf("first level: %d\n", i);
		for(int i = 0; i < 5; i++)
		{
			printf("second level: %d\n", i);
		}
		printf("first level: %d\n", i);
	}
	return 0;
}
```
```
first level: 0
second level: 0
second level: 1
second level: 2
second level: 3
second level: 4
first level: 0
first level: 1
second level: 0
second level: 1
second level: 2
second level: 3
second level: 4
first level: 1
```
* 局部变量
  * 函数：
    * 不同的函数，变量不会相互影响
    * 反之，同一函数内且在同一个嵌套层级的变量会相互影响
