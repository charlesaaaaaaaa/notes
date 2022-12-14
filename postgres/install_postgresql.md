## 编译
* 先下载一个postgresql的源码包
  * [https://www.postgresql.org/ftp/source/ 官网下载]
* 下载好后解压
* 进入到源码包里
  * `./configure --prefix=/nvme2/compare/postgresql-15.1/base`
    * `--prefix`就是要把二进制包安装在哪个位置
    * 不指定就会默认安装在`/usr/local/pgsql`
  * `cd src`
    * configure 完成后会把对应的包放到src目录下，所以我们要cd到这个目录下
  * `make -j16`
    * -j后面的数字不可以超过系统最大逻辑核数
  * `make install`

## 初始化
* 进入到编译好的bin目录下
* `./initdb -D /nvme2/compare/postgres/data`
  * `-D` 就是你要安装的数据目录
* init完成后，有如下输出：
```
[kunlun@kunlun-test8 bin]$ ./initdb -D /nvme2/compare/postgres/data
The files belonging to this database system will be owned by user "kunlun".
This user must also own the server process.

The database cluster will be initialized with locale "en_US.UTF-8".
The default database encoding has accordingly been set to "UTF8".
The default text search configuration will be set to "english".

Data page checksums are disabled.

fixing permissions on existing directory /nvme2/compare/postgres/data ... ok
creating subdirectories ... ok
selecting dynamic shared memory implementation ... posix
selecting default max_connections ... 100
selecting default shared_buffers ... 128MB
selecting default time zone ... Asia/Shanghai
creating configuration files ... ok
running bootstrap script ... ok
performing post-bootstrap initialization ... ok
syncing data to disk ...
ok

initdb: warning: enabling "trust" authentication for local connections
initdb: hint: You can change this by editing pg_hba.conf or using the option -A, or --auth-local and --auth-host, the next time you run initdb.

Success. You can now start the database server using:

    pg_ctl -D /nvme2/compare/postgres/data -l logfile start
```
* 注意最后的这个启动命令，这个最后启动pg用得上

## 配置
* 在数据目录下，有两个文件`postgresql.conf`和`pg_hba.conf`
  * `postgresql.conf`把`listen_addresses`的值改成‘*’
  * `pg_hba.conf`在`IPv4 local connections:`的位置下增加
```
# IPv4 local connections:
host    all             all             0.0.0.0/0               trust
host    all             all             127.0.0.1/32            trust
```

## 启动
* 这里就用到了刚刚初始化输出的最后一条命令
* cd到base目录的bin下
* `./pg_ctl -D /nvme2/compare/postgres/data -l logfile start`
* 第一次进入如果没有改过`postgresql.conf`下port参数的话
  * 直接运行`psql -h 192.168.0.132 -d postgres`

## 新增用户abc
* 像一些工具和库，一定要指定账户和密码才能运行的
* 进入pg
  * `create user abc with superuser password 'abc';`
* 完成后可以在其它同一局域网的机器上远程登录一下验证是否成功增加用户
  * `PGPASSWORD=abc psql -h 192.168.0.132 -d postgres -Uabc`
