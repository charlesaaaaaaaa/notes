## 在windows上写好的java程序怎么在linux上运行

* 先在windows上用idea或者其它的工具写好程序。
* 把文件夹上传到linux里面
* 再把对应的jar包给上传到linux里，之所以不在linux下载是因为这些找起来太麻烦了。用工具下载好的jar包最方便了
## 编译
* 如果这个java文件没有要导入的包，直接javac name.java
* 如果有一个要导入的包，javac -cp 包的绝对路径 name.java
* 如果有多个要导入的包，每个包之间用:分隔开，如 javac -cp 包1的绝对路径:包2的绝对路径 name.java
  * 网上很多人都说导入多个包直接把jar包放在一个目录下，然后`javac -cp jarDirPath/* name.java` 就行，但是我自己那么用的时候就会报说某个jar包找不到，所以这个我就没有在用了
* 如果要导入的包是自建的，则要进入到对应的要导入的java文件下，先用javac编译好，生成class文件。然后回去看要编译的java文件，要导入的自建包路径是什么。如要编译的java文件里面`import patha.pathb.pakname`,则在自建包pakname.class的上两级目录，确认路径是patha/pathb/pakname.class。然后在patha目录下用jar命令打包。`jar cvf pakname.jar patha`。
  * 打好包后再用javac -cp 自建包绝对路径:其它包绝对路径 name.java
  * jar命令和tar命令用法类似，所以可以直接参考tar命令
## 运行
* 这个和编译的命令很像
* java [-cp jar包绝对路径] name
* 如果在编译的时候用有到-cp参数，则在运行的时候也要。后面是跟的class文件，但不用加.class.
* 如果在写代码的时候有加package patha.pathb。则在运行的时候要到patha目录下运行，如 `cd /patha-path/ && java [-cp jar包绝对路径] patha.pathb.name`。文件夹之间用.隔开，而不是/
