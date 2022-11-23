[[PageOutline]]
* 本次使用mysql 8.0.30版本做示范
## 下载mysql-8.0
* [https://downloads.mysql.com/archives/community/](mysql社区版下载)
* `Product Version`版本任意选择，这里选择最新的8.0.30
* `Operating System`操作系统选择`Linux - Generic`,这个是已经编译好的版本
* `OS Version` 根据自身服务器的glibc版本选择对应的版本
  * 可以通过`rpm -q glibc` 或者 `rpm -qa | grep glibc`来查看现在安装的是什么版本的glibc
* 最后通过wget下载到服务器上然后解压，因为是已经编译过了的，所以不用去再下载boost
  * boost官网下载真的是龟速，所以能用已编译好的版本就不要去下载源码了，反正也没有很特别的需求

## 修改my.cnf配置文件
* 主要是要改socket和各种目录的位置，如果默认3306端口已经被占用就要再指定下端口

```
[mysql]
port=12345
socket=/nvme2/compare/mysql/mysql.sock

[client]
port=12345
socket=/nvme2/compare/mysql/mysql.sock

[mysqldump]
quick
max_allowed_packet = 16M

[mysqld]
user = mysql
basedir = /nvme2/compare/mysql/mysql-8.0.31
datadir = /nvme2/compare/mysql/data
port=12345
server-id = 1
socket=/nvme2/compare/mysql/mysql.sock

character-set-server = utf8mb4
collation-server = utf8mb4_general_ci
init_connect='SET NAMES utf8mb4'
lower_case_table_names = 1
```

## 初始化mysql
* 在初始化之前，要确认my.cnf的所有指定的目录都存在，没有的话就`mkdir -p`
* 初始化使用到mysql包里bin目录下的mysqld程序
  * `./mysqld --defaults-file=../../my.cnf --initialize --user=kunlun`
  * `--defaults-file` 这个是用来指定my.cnf配置文件位置的，如果不指定一般就会去找/etc/my.cnf
    * 这个选项一定要在最前面，不然初始化会直接去找默认路径的my.cnf
  * `--initialize` 初始化
  * `--user` 不指定就会默认是mysql用户
* 初始化完成后输出的日志最后一段内容有root用户默认的密码

## 启动mysql
* 这步用的是mysql包里bin目录下mysqld_safe启动的
  * `./mysqld_safe --defaults-file=../../my.cnf --user=kunlun &`
  * 每个选项的用法和初始化差不多

## 登录mysql
* 首次登录mysql只能用socket登录
  * `mysql --defaults-file=../../my.cnf -uroot -p`
  * 输入初始化给的临时密码
* 修改密码
  * ALTER user 'root'@'localhost' IDENTIFIED BY 'root';
* 修改远程登录权限
  * `use mysql`
  * `update user set host = '%' where User = 'root';`
  * `FLUSH PRIVILEGES;`
  * 不修改这一步，就只能用scoket连接mysql
