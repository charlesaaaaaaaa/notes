[[PageOutline]]
## 将产生的100G数据文件分割成数个小文件
* 现在需要灌100G的TPC-DS数据，按正常的步骤走，到最后的灌数据步骤，使用的是copy语句，把外部文件的数据copy到pg里，如下
```
\COPY call_center from 'datas/call_center-00' with DELIMITER '|' NULL ''  ;
\COPY catalog_page from 'datas/catalog_page-00' with DELIMITER '|' NULL ''  ;
\COPY catalog_returns from 'datas/catalog_returns-00' with DELIMITER '|' NULL ''  ;
```
* TPC-DS会产生很多的数据文件，以100G数据为例，最大的单个文件可达35G
* 35G如果只是用copy进去的话，根据服务器的好坏，所需的时间也不同，但绝对不会少，所以需要的集群语句超时时间也需要很大，比如五六个小时
* 此时会用到split命令对单个文件进行分割
  * `split -l 280000 -d catalog_sales.dts catalog_sales-`
  * 上述该命令示例中，`-l` 是以行数为分割，`-d`分割后的文件名以数据为后缀,示例是每280000行分割一次文件，还有其它类似以大小为分割等，这边不说了
    * 如果最后剩下的不够280000行，就单独分割成一个文件
  * `catalog_sales.dts`，要分割的文件名，`catalog_sales-` 分割后的文件名前缀
```
catalog_sales-00
catalog_sales-01
catalog_sales-02
catalog_sales-03
catalog_sales-04
catalog_sales-05
catalog_sales-06
```
* 把分割好的文件统一放到一个文件夹里，该文件夹只能有分割的文件

## 产生sql文件
* 随后根据该文件夹里所有的文件名产生对应的copy语句，并统一把这些copy语句写入到一个sql文件里
```
for i in `ls datas`
do
    table#`echo $i | awk -F- '{print $1}'` #这步是把table名给筛选出来
    echo "\COPY $table from 'datas/$i' with DELIMITER '|' NULL ''  ;" >> copy.sql
done
```

* 完成后，产生的sql文件内容应该类似下面的示例
```
\COPY web_sales from 'datas/web_sales-9156' with DELIMITER '|' NULL ''  ;
\COPY web_sales from 'datas/web_sales-9157' with DELIMITER '|' NULL ''  ;
\COPY web_sales from 'datas/web_sales-9158' with DELIMITER '|' NULL ''  ;
\COPY web_sales from 'datas/web_sales-9159' with DELIMITER '|' NULL ''  ;
\COPY web_sales from 'datas/web_sales-9160' with DELIMITER '|' NULL ''  ;
\COPY web_sales from 'datas/web_sales-9161' with DELIMITER '|' NULL ''  ;
\COPY web_sales from 'datas/web_sales-9162' with DELIMITER '|' NULL ''  ;
\COPY web_sales from 'datas/web_sales-9163' with DELIMITER '|' NULL ''  ;
\COPY web_sales from 'datas/web_sales-9164' with DELIMITER '|' NULL ''  ;
\COPY web_sales from 'datas/web_sales-9165' with DELIMITER '|' NULL ''  ;
\COPY web_sales from 'datas/web_sales-9166' with DELIMITER '|' NULL ''  ;
\COPY web_sales from 'datas/web_sales-9167' with DELIMITER '|' NULL ''  ;
```

* 现在sql文件全产生了，现在要再把产生的文件根据需要开启的进程数继续进行分割并把文件放到copy目录下
  * 以sql文件有3001行，要开5个进程为例
  * 可以将文件分割成每个文件为601行的文件，命令为`cd copy && split -l 601 -d ../copy.sql copy`
  * 命令完成后应该会在对应目录下产生 `copy00  copy01  copy02  copy03  copy04` 这五个文件

## 运行脚本
* 所有的准备都完成了，现在就是开启五个进行灌TPC-DS数据了
  * 创建一个名为a.sh的脚本,内容为
```
for i in `ls copy`
do
        PGPASSWORD#abc psql -h 192.168.0.132 -p 35001 -U abc -d tpcds -f copy/$i & >> sql.log
done
```

* 运行脚本
`nohup /bin/bash a.sh > log.log 2>&1 &`

* 最后`ps -ef`可以看到以下五个进程的存在
```
[charles@kunlun-test3 TPC-DS]$ ps -ef | grep tpcds && date && cat log.log | wc -l
charles  3703340       1  0 16:59 pts/0    00:00:04 psql -h 192.168.0.132 -p 35001 -U abc -d tpcds -f copy/copy00
charles  3703341       1  0 16:59 pts/0    00:00:12 psql -h 192.168.0.132 -p 35001 -U abc -d tpcds -f copy/copy01
charles  3703342       1  0 16:59 pts/0    00:00:12 psql -h 192.168.0.132 -p 35001 -U abc -d tpcds -f copy/copy02
charles  3703343       1  0 16:59 pts/0    00:00:09 psql -h 192.168.0.132 -p 35001 -U abc -d tpcds -f copy/copy03
charles  3703344       1  0 16:59 pts/0    00:00:08 psql -h 192.168.0.132 -p 35001 -U abc -d tpcds -f copy/copy04
charles  3754519 3696661  0 17:47 pts/0    00:00:00 grep --color#auto tpcds
Mon Nov 21 17:47:03 CST 2022
1891
```

* 注意
  * 进程数不是越多越好，而是要刚刚好，如我之前用132 134 140搭建的集群，开了10个进程
  * 结果速度远不及5个进程就算了，灌了不到10分钟集群还崩溃了，以对应的速度来推测10个进程灌100G的TPC-DS数据来算
  * 约要3个多小时才能灌完
  * 开五个进程，约七八十分钟，不到一个半小时
  * 最重要的是，不会崩溃，而且全程三台机的负载和cpu使用率几乎都是满的
  * 五个进程大概1s可以灌三十万行的TPC-DS数据，这个吞吐量可比sysbench的point_select得出的数据还高

