# gdb使用笔记
* 在编译好c后，使用时core了并且产生了core文件
* 我们就可以直接使用gdb查看core文件
* 其中`gdb -c core.xxx`就是查看core文件的命令行参数
* 也可以`gdb`进入gdb命令行界面
  * 然后使用`core-file core.xxx`查看core文件
* 退出gdb命令行界面使用`quit`