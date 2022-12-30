## KunlunBase与OceanBase对比TPC-C结果
### 测试服务器说明：
| IP | CPU | Memory | Disk | Operation System |
| ---- | ---- | ---- | ---- | ---- |
| 132(enp5s0) | AMD Ryzen 9 5950X 16 cores 32 threads | 128G | 2T.m2 + 1T.m2 + 4THDD | Centos8.3 |
| 134(enp5s0) | AMD Ryzen 9 5950X 16 cores 32 threads | 128G | 2T.m2 + 1T.m2 + 4THDD | Centos8.3 |
| 140(enp5s0) | AMD Ryzen 9 5950X 16 cores 32 threads | 64G | 1T.m2 + 1T.m2 | Centos8.3 |

### 集群说明：
##### KunlunBase：
* 集群模式为rbr
* 三台服务器各部署一个Cluster_mgr、Node_mgr、计算节点、元数据节点
  * 三台服务器上部署两个存储分片，其中132和134上各一个主
  * 每个存储分片都以一主两备的形式存在

##### OceanBase：
* 三台测试服务器上各部署一个observer
* 在132和134上各部署一个obproxy

### 测试说明：
* 本次使用的是Banchmarksql5.0
* OceanBase根据下面这篇[文章](https://www.oceanbase.com/docs/community-observer-cn-10000000000901541)修改Benchmarksql ,且使用OceanBase[官方jdbc驱动](https://mvnrepository.com/artifact/com.oceanbase/oceanbase-client)
* 本次两个数据库集群都是灌50个warehouse
* 本次测试时间都是5分钟
* 本次测试在每个测试后都会停止5分钟后再继续下一个测试

### 集群配置说明：
##### KunlunBase-性能模式：
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
                "innodb_buffer_pool_size": "10*1024*1024*1024",
                "max_binlog_size": "1*1024*1024*1024"
                }
        ]
}

```
##### KunlunBase-生产模式:
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
                "enable_fullsync": "ON",
                "innodb_flush_log_at_trx_commit": 1,
                "sync_binlog": 1,
                "innodb_buffer_pool_size": "10*1024*1024*1024",
                "max_binlog_size": "1*1024*1024*1024"
                }
        ]
}

```

##### OceanBase：
```
    writing_throttling_trigger_percentage: 100
    memory_limit_percentage: 80
    syslog_io_bandwidth_limit: 10MB
    enable_async_syslog: True
    builtin_db_data_verify_cycle: 0
    enable_monotonic_weak_read: False
    weak_read_version_refresh_interval: 0
    enable_sql_audit: False
    enable_perf_event: False
    syslog_level: PERF
    enable_syslog_recycle: true
    enable_syslog_wf: true
    max_syslog_file_count: 4
```
### 对比结果：
| ---- | ---- | ---- |
| threads | OceanBase | KunlunBase-性能模式 | KunlunBase-生产模式 |
| ---- | ---- | ---- | ---- |
| 25 | 26727.9 | 22538.99 | 8287.79 |
| 50 | 26449.72 | 33431.78 | 9617.06 |
| 75 | 25716.25 | 36090.11 | 12671.91 |
| 100 | 24998.16 | 36072.49 | 13287.26 |
| 125 | 21698.29 | 35211.52 | 15660.77 |
| 150 | 21011.14 | 40422.41 | 15519.44 |
| 175 | 20230.11 | 38191.84 | 17044.21 |
| 200 | 19124.72 | 36993.18 | 18800.43 |
| 225 | 19829.38 | 35779.81 | 16175.82 |
| 250 | 17830.15 | 29728.55 | 18107.56 |

### 对比图  
![compare](https://github.com/charlesaaaaaaaa/notes/blob/main/work/KunlunBase/1.1.1/ap.png)
