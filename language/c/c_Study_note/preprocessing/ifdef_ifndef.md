# #ifdef 及 #ifndef命令

* 如果判断一个符号常量对应的具体值，我们会使用#if
* 如果判断一个符号常量有没有被定义，我们就会使用到#ifdef && #ifndef
## #ifdef
* 如果宏替换名被定义，则对#ifdef和#endif间语句行进行编译
  * #ifdef可以和#else共用,当然不用#else也是正确的
  ```
#ifdef 宏替换名
  对应语句行
#else 宏替换名
  对应语句行
#endif
  ```
## #ifndef
* 如果宏替换名没有被定义，则对#ifndef和#endif语句行进行编译
  * #ifndef 可以和else共用，当然else不是必须要用的
  ```
#ifndef 宏替换名
  对应的语句行
#else 宏替换名
  对应的语句行
#endif
  ```

