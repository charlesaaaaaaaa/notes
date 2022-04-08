# 安装gtm主：
## 初始化：
`initgtm -Z gtm -D /home/kunlun/TPC/postgres-xz/data/gtm`

## 修改对应的配置：gtm.conf
```
cat >> /home/kunlun/TPC/postgres-xz/data/gtm/gtm.conf << EOF
nodename = gtm
listen_addresses = '*'
port = 21000
startup = ACT
EOF
```
## 开启gtm主
`gtm_ctl -Z gtm -D /home/kunlun/TPC/postgres-xz/data/gtm start`

# 安装gtm备：
## 初始化：
`initgtm -Z gtm -D /home/kunlun/TPC/postgres-xz/data/gtms`

## 修改对应的配置：gtm.conf
```
cat >> /home/kunlun/TPC/postgres-xz/data/gtms/gtm.conf << EOF
nodename = gtms1
listen_addresses = '*'
port = 21000
startup = STANDBY
active_host = '192.168.0.134'
active_port = 21000
EOF
```
## start gtm slave
`gtm_ctl -Z gtm -D /home/kunlun/TPC/postgres-xz/data/gtms start`

# 安装coord node1：node2 及更多coord node也使用以下方式
## 初始化：
`initdb --locale=zh_CN.UTF-8 -U kunlun -E utf8 -D /home/kunlun/TPC/postgres-xz/data/cn01 --nodename=cn01 --nodetype=coordinator --master_gtm_nodename gtm1 --master_gtm_ip 192.168.0.134 --master_gtm_port 21000`

## 修改配置文件：postgresql.conf pg_hba.conf 

### postgresql.conf
```
cat >> /home/kunlun/TPC/postgres-xz/data/cn01/postgresql.conf << EOF
port =15432
pooler_port=15433
include_if_exists ='/home/kunlun/TPC/postgres-xz/global/postgresql.conf.user'
wal_level = replica
wal_keep_segments =256
max_wal_senders =4
archive_mode = on
archive_timeout =1800
archive_command ='echo 0'
log_truncate_on_rotation = on
log_filename ='postgresql-%M.log'
log_rotation_age =4h
log_rotation_size =100MB
hot_standby = on
wal_sender_timeout =30min
wal_receiver_timeout =30min
shared_buffers =1024MB
max_pool_size =2000
log_statement ='ddl'
log_destination ='csvlog'
logging_collector = on
log_directory ='pg_log'
listen_addresses ='*'
max_connections =2000
EOF
```

### pg_hba.conf

```
cat >> /home/kunlun/TPC/postgres-xz/data/cn01/pg_hba.conf << EOF
host    replication     all             0.0.0.0/0               trust
host    all             all             0.0.0.0/0               trust
EOF
```

## start coordinator nodes
`pg_ctl -Z coordinator -D /home/kunlun/TPC/postgres-xz/data/cn01 start`

## reload coordinator nodes
`pg_ctl -D /home/kunlun/TPC/postgres-xz/data/cn0 reload`

## check coordinator status
`pg_ctl -D /home/kunlun/TPC/postgres-xz/data/cn0 status`

# 安装datanode主节点:其它datanode主节点步骤相同
`initdb --locale=zh_CN.UTF-8 -U kunlun -E utf8 -D /home/kunlun/TPC/postgres-xz/data/dn01 --nodename=dn01 --nodetype=datanode --master_gtm_nodename gtm1 --master_gtm_ip 192.168.0.134 --master_gtm_port 21000`

## 修改配置文件：pg_hba.conf      postgresql.conf
### postgresql.conf
```
cat >> home/kunlun/TPC/postgres-xz/data/dn01/postgresql.conf << EOF
port =23002
pooler_port=23003
include_if_exists ='/data/tbase/global/postgresql.conf.user'
listen_addresses ='*'
wal_level = replica
wal_keep_segments =256
max_wal_senders =4
archive_mode = on
archive_timeout =1800
archive_command ='echo 0'
log_directory ='pg_log'
logging_collector = on
log_truncate_on_rotation = on
log_filename ='postgresql-%M.log'
log_rotation_age =4h
log_rotation_size =100MB
hot_standby = on
wal_sender_timeout =30min
wal_receiver_timeout =30min
shared_buffers =1024MB
max_connections =4000
max_pool_size =4000
log_statement ='ddl'
log_destination ='csvlog'
wal_buffers =1GB
EOF
```

### pg_hba.conf
```
cat >> home/kunlun/TPC/postgres-xz/data/dn01/pg_hba.conf << EOF
host    replication     all             0.0.0.0/0               trust
host    all             all             0.0.0.0/0               trust
EOF
```

## 启动节点：
`pg_ctl -Z datanode -D /home/kunlun/TPC/postgres-xz/data/dn01 start`

## 重载节点：
`pg_ctl -D /home/kunlun/TPC/postgres-xz/data/dn01 reload`

## 查看节点状态：
`pg_ctl -D /home/kunlun/TPC/postgres-xz/data/dn01 status`
===================================================

# 安装datanode备用节点
## 初始化：
`pg_basebackup -p 23003 -h 192.168.0.132 -U kunlun -D /home/kunlun/TPC/postgres-xz/data/dn01s1 -X f -P -v`  
这里的host和port表示的是要复制的主的host,port。只有用pg_basebackup备份主节点，才能有相同的标识码，-D 后面跟随的是要复制到的目录  

## 修改配置文件：pg_hba.conf      postgresql.conf
### postgresql.conf
```
cat >> home/kunlun/TPC/postgres-xz/data/dn01/postgresql.conf << EOF
port =23005
pooler_port=23006
include_if_exists ='/data/tbase/global/postgresql.conf.user'
listen_addresses ='*'
wal_level = replica
wal_keep_segments =256
max_wal_senders =4
archive_mode = on
archive_timeout =1800
archive_command ='echo 0'
log_directory ='pg_log'
logging_collector = on
log_truncate_on_rotation = on
log_filename ='postgresql-%M.log'
log_rotation_age =4h
log_rotation_size =100MB
hot_standby = on
wal_sender_timeout =30min
wal_receiver_timeout =30min
shared_buffers =1024MB
max_connections =4000
max_pool_size =4000
log_statement ='ddl'
log_destination ='csvlog'
wal_buffers =1GB
EOF
```
### pg_hba.conf
```
cat >> home/kunlun/TPC/postgres-xz/data/dn01/pg_hba.conf << EOF
host    replication     all             0.0.0.0/0               trust
host    all             all             0.0.0.0/0               trust
EOF
```
### 增加recovery.conf配置文件：这个文件的primary_conninfo 是指datanode主的信息
```
touch home/kunlun/TPC/postgres-xz/data/dn01/pg_hba.conf && cat >> home/kunlun/TPC/postgres-xz/data/dn1s1/recovery.conf << EOF
standby_mode = on 
primary_conninfo ='host = 192.168.0.132 port = 23002 user = kunlun application_name = dn01'
EOF
```
## start datanode_slave
`pg_ctl -Z datanode -D /home/kunlun/TPC/postgres-xz/data/dn1s1 start`
## reload datanode_slave
`pg_ctl -D /home/kunlun/TPC/postgres-xz/data/dn1s1 reload`
## check datanode_slave status
`pg_ctl -D /home/kunlun/TPC/postgres-xz/data/dn1s1 status`

## 路由配置：该设置只设置主节点，不设置备节点
### cn 1
```
psql -h 192.168.0.134 -d postgres -p 15432
alter node cn01 with(host='192.168.0.134',port=15432);
create node cn02 with(type=coordinator,host='192.168.0.132',port=15432,primary=false,preferred=false);
create node dn01 with(type=datanode,host='192.168.0.134',port=23002,primary=false,preferred=false);
create node dn02 with(type=datanode,host='192.168.0.132',port=23002,primary=false,preferred=false);
select pgxc_pool_reload();
```
### cn 2
```
psql -h 192.168.0.132 -d postgres -p 15432
alter node cn02 with(host='192.168.0.132',port=15432);
create node cn01 with(type=coordinator,host='192.168.0.132',port=15432,primary=false,preferred=false);
create node dn01 with(type=datanode,host='192.168.0.134',port=23002,primary=false,preferred=false);
create node dn02 with(type=datanode,host='192.168.0.132',port=23002,primary=false,preferred=false);
select pgxc_pool_reload();
```
### datanode 1
```
psql -h 192.168.0.132 -d postgres -p 23002
alter node dn01 with(host='192.168.0.132',port=23002);
create node cn02 with(type=coordinator,host='192.168.0.132',port=15432,primary=false,preferred=false);
create node dn02 with(type=datanode,host='192.168.0.134',port=23002,primary=false,preferred=false);
create node cn01 with(type=datanode,host='192.168.0.134',port=15432,primary=false,preferred=false);
select pgxc_pool_reload();
```
### datanode 2
```
psql -h 192.168.0.134 -d postgres -p 23002
alter node dn01 with(host='192.168.0.134',port=23002);
create node dn02 with(type=coordinator,host='192.168.0.132',port=23002,primary=false,preferred=false);
create node cn02 with(type=datanode,host='192.168.0.134',port=15432,primary=false,preferred=false);
create node cn01 with(type=datanode,host='192.168.0.132',port=15432,primary=false,preferred=false);
select pgxc_pool_reload();
```


## 创建默认group
```
psql -h 192.168.0.134 -d postgres -p 15432
create default node group default_group with(dn01, dn02);
create sharding group to group default_group;
select*from pgxc_group;
```

```
psql -h 192.168.0.132 -d postgres -p 15432
create default node group default_group with(dn01, dn02);
create sharding group to group default_group;
select*from pgxc_group;
```
