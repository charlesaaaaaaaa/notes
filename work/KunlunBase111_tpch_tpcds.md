## KunlunBase TPC-H 和 TPC-DS 测试结果
### 测试服务器说明：
| IP | CPU | Memory | Disk | Operation System |
| ---- | ---- | ---- | ---- | ---- |
| 132(enp5s0) | AMD Ryzen 9 5950X 16 cores 32 threads | 128G | 2T.m2 + 1T.m2 + 4THDD | Centos8.3 |
| 134(enp5s0) | AMD Ryzen 9 5950X 16 cores 32 threads | 128G | 2T.m2 + 1T.m2 + 4THDD | Centos8.3 |
| 140(enp5s0) | AMD Ryzen 9 5950X 16 cores 32 threads | 64G | 1T.m2 + 1T.m2 | Centos8.3 |

### 测试说明：
* 本次TPC-DS及TPC-H测试都灌10G数据。
* 在灌完10G数据后，需要对所有表进入analyze操作，可以使用以下脚本快速完成
```
echo 'show tables;' > tmp.sql
for i in `psql postgres://abc:abc@ip:port/tpcds -f tmp.sql | sed '1,2d' | sed '$d' | sed '$d'`
do
        echo "select * from $i limit 1;" > a.sql
        clomun=`psql postgres://abc:abc@ ip:port /tpcds -f a.sql | sed -n 1p | sed 's/|/,/g'`
        analyze="analyze $i($clomun)"
        echo $analyze; echo $analyze > tmp.sql
        psql postgres://abc:abc@192.168.0.132:35001/tpcds -f tmp.sql
done

```

### 集群说明：
* 集群模式为rbr
* 三台服务器各部署一个Cluster_mgr、Node_mgr、计算节点、元数据节点
  * 三台服务器上部署两个存储分片，其中132和134上各一个主
  * 每个存储分片都以一主两备的形式存在

### 集群配置说明：
```
{
        "comp":[{
                        "statement_timeout":1200000,
                        "mysql_read_timeout":1200,
                        "mysql_write_timeout":1200,
                        "lock_timeout":1200000,
                        "autovacuum": "off",
                        "log_min_duration_statement":1200000
                }
        ],
        "metadata":[{
                        "lock_wait_timeout":1200,
                        "innodb_lock_wait_timeout":1200
                }
        ],
        "storage":[{
                "lock_wait_timeout":1200,
                "innodb_lock_wait_timeout":1200,
                "fullsync_timeout":1200,
                "enable_fullsync": "OFF",
                "innodb_flush_log_at_trx_commit": 0,
                "sync_binlog": 0,
                "innodb_buffer_pool_size": "32*1024*1024*1024",
                "max_binlog_size": "1*1024*1024*1024"
                }
        ]
}

```

### TPC-H结果：
| sql | result | cost | error |
| ---- | ---- | ---- | ---- |
| Q1 | succ | 147.86 | |
| Q2 | fail | 1200.01 | psql:query/2.sql:47: ERROR:  canceling statement due to statement timeout |
| Q3 | succ | 32.63 | |
| Q4 | succ | 28.82 | |
| Q5 | succ | 49.18 | |
| Q6 | succ | 18.07 | |
| Q7 | succ | 29.88 | |
| Q8 | succ | 56.75 | |
| Q9 | succ | 105.17 | |
| Q10 | succ | 30.52 | |
| Q11 | succ | 7.67 | |
| Q12 | succ | 28.27 | |
| Q13 | succ | 14.72 | |
| Q14 | succ | 19.07 | |
| Q15 | succ | 38.29 | |
| Q16 | succ | 10.65 | |
| Q17 | succ | 85.78 | |
| Q18 | succ | 100.61 | |
| Q19 | succ | 21.61 | |
| Q20 | succ | 37.63 | |
| Q21 | fail | 1200.07 | psql:query/21.sql:43: ERROR:  canceling statement due to statement timeout |
| Q22 | succ | 6.97 | |


### TPC-DS结果：
