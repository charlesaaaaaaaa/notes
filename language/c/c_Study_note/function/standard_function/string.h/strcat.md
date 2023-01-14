## strcat函数

* 注意，这个cat不是linux里面的读取文件命令
  * 是`concatenate`的缩写，连接的意思
  * 就是把一个 **字符数组2** 连接到 **字符数组1** 的后面
  * 连接后的变量名为 **字符数组1** 的变量名

```
char dir[30], file[30];
puts("输入路径：");
gets(dir);
puts("输入文件名");
gets(file);

puts("文件全路径为：");
strcat(dir, file);
puts(dir);
```
