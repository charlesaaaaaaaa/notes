## hammerdb
* hammerdb是一款测试数据库性能的工具，不是数据库

## 下载安装
* 可以直接去hammerdb官网下载
  * 选择`for Linux 64-bit compressed tar file`
  * [hammerdb官网下载页面](https://www.hammerdb.com/download.html)

* 下载完成后，直接解压
  * cd到hammerdb目录下
  * 运行hammerdbcli，进入shell界面
  * `./hammerdbcli`

## 修改配置信息

### 查看当前配置信息
* `print dict`
  * 这个命令是查看当前数据库配置信息的命令
  * 后续修改数据库信息的时候用得上，所以先提这个命令
```
hammerdb>print dict
Dictionary Settings for PostgreSQL
connection {
 pg_host    = 192.168.0.132
 pg_port    = 35001
 pg_sslmode = disable
}
tpcc       {
 pg_count_ware       = 10
 pg_num_vu           = 10
 pg_superuser        = abc
 pg_superuserpass    = abc
 pg_defaultdbase     = tpcc
 pg_user             = abc
 pg_pass             = abc
 pg_dbase            = tpcc
 pg_tspace           = pg_default
 pg_vacuum           = false
 pg_dritasnap        = false
 pg_oracompat        = false
 pg_cituscompat      = false
 pg_storedprocs      = false
 pg_partition        = false
 pg_total_iterations = 10000000
 pg_raiseerror       = false
 pg_keyandthink      = false
 pg_driver           = timed
 pg_rampup           = 2
 pg_duration         = 5
 pg_allwarehouse     = false
 pg_timeprofile      = false
 pg_async_scale      = false
 pg_async_client     = 10
 pg_async_verbose    = false
 pg_async_delay      = 1000
 pg_connect_pool     = false
}
```

### 修改数据库类型
* 使用`dbset`
  * `dbset help`
  * `dbset`可以配置数据库类型和测试基准集类型
  * `dbset db pg` ,配置数据库类型为postgres
  * `dbset bm TPC-C` ,配置测试集为TPC-C
```
hammerdb>dbset help
Usage: dbset [db|bm] value
```
* 这个意思就是`dbset`这个命令可以有db和bm这两个子命令，加上对应的值
  * 可以再加上子命令help查看对应子命令可使用的参数
```
hammerdb>dbset db help
Unknown prefix help, choose one from ora mssqls db2 mysql pg maria
```

### 修改数据库信息
* 使用`diset`命令
  * 这个时候就要参考`print dict`命令打印的配置信息了
  * 比如下面的connection信息
    * 要修改pg_host这个参数的值
    * `diset connection pg_host loaclhost`
    * 组成部分就是diset 连接配置|测试集配置 参数名 参数值
    * 测试集配置也是一样的

```
connection {
 pg_host    = localhost
 pg_port    = 35001
 pg_sslmode = disable
}
```

## 准备数据
* 该步骤要确保数据库配置和基准测试集配置要正确，不然会直接报错
  * `buildschema`

* 删除数据
  * `deleteschema`
