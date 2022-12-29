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
| sql | result | cost | error |
| ---- | ---- | ---- | ---- |
| Q1 | fail | 1199.99 | psql:query/q1.sql:22: ERROR:  canceling statement due to statement timeout |
| Q2 | succ | 33.47 | |
| Q3 | succ | 13.15 | |
| Q4 | fail | 1206.71 | psql:query/q4.sql:113: ERROR:  canceling statement due to statement timeout |
| Q5 | succ | 35.67 | |
| Q6 | fail | 1199.99 | psql:query/q6.sql:23: ERROR:  canceling statement due to statement timeout |
| Q7 | succ | 36.00 | |
| Q8 | succ | 15.79 | |
| Q9 | succ | 78.69 | |
| Q10 | succ | 37.90 | |
| Q11 | succ | 607.60 | |
| Q12 | succ | 3.17 | |
| Q13 | succ | 15.21 | |
| Q14 | fail | 1199.99 | psql:query/q14.sql:105: ERROR:  canceling statement due to statement timeout |
| Q15 | succ | 34.71 | |
| Q16 | succ | 0.11 | |
| Q17 | succ | 73.08 | |
| Q18 | fail | 1199.99 | psql:query/q18.sql:35: ERROR:  canceling statement due to statement timeout |
| Q19 | fail | 1199.99 | psql:query/q19.sql:26: ERROR:  canceling statement due to statement timeout |
| Q20 | succ | 10.08 | |
| Q21 | succ | 42.76 | |
| Q22 | succ | 165.87 | |
| Q23 | succ | 194.73 | |
| Q24 | succ | 29.57 | |
| Q25 | fail | 1222.80 | psql:query/q25.sql:49: ERROR:  canceling statement due to statement timeout |
| Q26 | fail | 1200.00 | psql:query/q26.sql:22: ERROR:  canceling statement due to statement timeout |
| Q27 | succ | 0.06 | |
| Q28 | succ | 52.84 | |
| Q29 | fail | 1199.99 | psql:query/q29.sql:48: ERROR:  canceling statement due to statement timeout |
| Q30 | fail | 1200.00 | psql:query/q30.sql:32: ERROR:  canceling statement due to statement timeout |
| Q31 | succ | 125.51 | |
| Q32 | fail | 1199.99 | psql:query/q32.sql:29: ERROR:  canceling statement due to statement timeout |
| Q33 | succ | 27.31 | |
| Q34 | succ | 11.47 | |
| Q35 | succ | 19.57 | |
| Q36 | succ | 85.41 | |
| Q37 | succ | 41.47 | |
| Q38 | succ | 126.61 | |
| Q39 | succ | 213.64 | |
| Q40 | succ | 8.29 | |
| Q41 | succ | 39.71 | |
| Q42 | succ | 243.83 | |
| Q43 | succ | 67.13 | |
| Q44 | succ | 32.96 | |
| Q45 | succ | 4.31 | |
| Q46 | succ | 23.64 | |
| Q47 | succ | 59.03 | |
| Q48 | succ | 15.10 | |
| Q49 | succ | 25.74 | |
| Q50 | fail | 1199.99 | psql:query/q50.sql:60: ERROR:  canceling statement due to statement timeout |
| Q51 | succ | 38.30 | |
| Q52 | succ | 244.98 | |
| Q53 | succ | 13.55 | |
| Q54 | succ | 164.25 | |
| Q55 | succ | 126.09 | |
| Q56 | succ | 34.33 | |
| Q57 | succ | 29.45 | |
| Q58 | succ | 21.54 | |
| Q59 | succ | 53.23 | |
| Q60 | succ | 25.27 | |
| Q61 | fail | 1199.99 | psql:query/q61.sql:45: ERROR:  canceling statement due to statement timeout |
| Q62 | succ | 12.35 | |
| Q63 | succ | 14.06 | |
| Q64 | succ | 42.16 | |
| Q65 | succ | 44.58 | |
| Q66 | succ | 16.99 | |
| Q67 | succ | 99.05 | |
| Q68 | succ | 28.37 | |
| Q69 | succ | 56.41 | |
| Q70 | succ | 106.87 | |
| Q71 | succ | 21.69 | |
| Q72 | fail | 1200.10 | psql:query/q72.sql:30: ERROR:  canceling statement due to statement timeout |
| Q73 | succ | 0.24 | |
| Q74 | fail | 1200.05 | psql:query/q74.sql:62: ERROR:  canceling statement due to statement timeout |
| Q75 | succ | 59.52 | |
| Q76 | succ | 14.52 | |
| Q77 | fail | 0.00 | psql:query/q77.sql:109: ERROR:  syntax error at or near "returns" |
| Q78 | succ | 229.67 | |
| Q79 | succ | 25.25 | |
| Q80 | succ | 29.31 | |
| Q81 | succ | 0.42 | |
| Q82 | succ | 53.84 | |
| Q83 | succ | 0.91 | |
| Q84 | succ | 2.89 | |
| Q85 | succ | 76.26 | |
| Q86 | succ | 6.56 | |
| Q87 | succ | 123.08 | |
| Q88 | fail | 1200.10 | psql:query/q88.sql:95: ERROR:  canceling statement due to statement timeout |
| Q89 | succ | 38.94 | |
| Q90 | succ | 17.84 | |
| Q91 | succ | 1.86 | |
| Q92 | succ | 687.43 | |
| Q93 | succ | 16.96 | |
| Q94 | succ | 467.21 | |
| Q95 | fail | 1200.24 | psql:query/q95.sql:33: ERROR:  canceling statement due to statement timeout |
| Q96 | succ | 1101.59 | |
| Q97 | succ | 25.18 | |
| Q98 | succ | 12.29 | |
| Q99 | succ | 15.71 | |

