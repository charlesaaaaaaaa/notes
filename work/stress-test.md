## 极限测试：
* 根据系统核心数产生对应的线程数。
  * 可以使用参数选项产生对应的进程数，每个进程都会产生系统cpu核心数个线程

* 新建表
  * 新建8个分区表
    * 有16，64，256，1024，2048，4096，8192，16384个子分区
  * 新建2个大单表
  * 新建1个极限大宽表
    * 有500个列，30个固定列和其它470个列，随机从30个类型中抽取，然后再随机决定是否增加索引，索引有六种。

* 插入数据：
  * 8个分区表：根据总分区表数据平均4亿行数据，每个事务要插入1kw行，5kw行，10kw行数据，直到4亿行
  * 2个大单表分别有1kw和5kw行数据
  * 对bigint类型的列，数据要类似serial的自增数，使其有迹可循。
  

* 根据写入100w行数据所使用的空间来推断500G，2T要多少行数据
* 插入1024个不同的表，具体看连接
* 30个固定列和其它470个列，随机从30个类型中抽取，然后再随机决定是否增加索引，索引有六种。
* 根据对应列产生对应的sql类型数据。可以判断数据类型，是否带索引，带的什么类型的索引。

## 目前已知可使用的数据类型：
```
integer
smallint
bigint
decimal
numeric
real
double precision
smallserial
serial
bigserial
money
character varying
varchar
character
char
text
bytea
boolean
cidr
inet
macaddr
macaddr8
Bit
timestamp
timestamp without time zone
timestamp with time zone
date
time
time without time zone
time with time zone
```

## 未加入的数据类型：
```
Enumerated Types
Geometric Types（不支持）
UUID Type
XML Type
JSON Types
Arrays
Composite Types
Range Types
Domain Types
Object Identifier Types
pg_lsn Type
Pseudo-Types
```
