# gcc使用笔记
* -l (小写的L)
  * 这个选择跟着的就是要用的什么连接库的名
  * 如mysql连接库 -- mysqlclient
  * 就可以用 `-lmysqlclient`

* -L
  * 当在使用-l（小写的L）时被提示
  * `cannot find -lmysqlclient`
  * 是因为gcc无法从系统中找到对应的连接库
  * 这个时候我们首先要用`locate mysqlclient`这条命令去linux里面查找对应的连接库
```
/usr/lib64/mysql/libmysqlclient.a
/usr/lib64/mysql/libmysqlclient.so
/usr/lib64/mysql/libmysqlclient.so.21
/usr/lib64/mysql/libmysqlclient.so.21.1.23
/usr/lib64/pkgconfig/mysqlclient.pc
/usr/local/kunluntesting/lib/libmysqlclient.so
```
* -L(接上面的)
  * 这个时候就把`/usr/lib64/mysql`放在`-L`后面，这样gcc就会在这个路径去找`mysqlclient`的连接库
  * 示例：
    * `gcc odbc_mysql.c -o odbc_mysql -lmysqlclient -L/usr/lib64/mysql`