# 左移运算符

* 左移运算符就是把整个二进制数往左边位移
  * 高位直接去掉，低位补0

* 以数字1为例
  * 往左边位移1位
  ```
  int x = 1;
  x = x<<1;
  printf("x=%d\n", x);
  ```
  ```
  x=2
  ```

  *	移位两次
  ```
  int x = 1;
  x = x<<2;
  printf("x=%d\n", x);
  ```
  ```
  x=4
  ```
* 从上述例子中可以看出来，每位移一次，就相当于x2
  * 位移几次，相当于x2的几次方
***
* 现在来看看在计算机中是怎么计算的
* 我们知道在计算机中，所有的数据都是由二进制组成
* 现在假设一个整型在计算机中占用一个字符，8个位。
  * 当然实际上是4个字符32位。为了方便这里暂时认为是1个字符8位
* 所以数字1在计算机存储中是长这样的
  * 00000001
* 现在我们把这个数字1左移一个位，按照 **高位去掉，低位补0** 的规则
  * 00000010
  * 现在1左移后1位就变成了十进制的2
* 现在我们再把十进制的二左移5个位
  * 01000000
  * 现在2左移5个位就变成了十进制64
* 现在我们再把十进制的64往左移2个位，会发现不够位了
  * 那么这个时候计算机会按照**高位去掉，低位补0**的规则直接把高位的1给去掉，所以会变成
  * 00000000
  * 假设一个整型占8个位(实际大部分是32位),如果1已经是最高位，则再左移会直接把1去掉，变成0.

# 循环左移
* 左移运算符会以**高位去掉，低位补0的**规则进行移位
* 如果我们不想去掉高位的，而且是把高位补到低位继续进行移位
* 这就是循环左移

* 再假设整型变量占8个位（实际32位），十进制64向左位移2位过程如下
```
01000000(原x)
00000001(循环左移后的x)
```
* 循环左移大概分为这三步
  * 定义三个变量x、y、z，把x的高n位放到z的低n位中
    * `z=y>>(32-n)`, 这里还是按照正常的32位来
  * 把x左移n位，右边低n位补0
    * `y=x<<n`
  * 最后把y、z进行按位或运算
    * `y = y | z`