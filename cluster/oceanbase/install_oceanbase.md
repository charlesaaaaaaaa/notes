* `sudo yum install -y yum-utils`
* `sudo yum-config-manager --add-repo https://mirrors.aliyun.com/oceanbase/OceanBase.repo`
* `sudo yum install -y ob-deploy` 
  * 该操作只需要在 OB 中控机上执行，因为 OBD 是一个黑屏部署、管理和运维工具，统一从一台机器上发起操作，所以不需要每台机器均安装
* `sudo yum install -y yum-utils` 
  * 如果上一步已经执行该操作，请忽略
* `sudo yum-config-manager --add-repo https://mirrors.aliyun.com/oceanbase/OceanBase.repo` 
  * 如果上一步已经执行该操作，请忽略
* `sudo yum install -y oceanbase-ce-libs` 
  * 所有机器均需安装
* `sudo yum install -y libobclient`
* `sudo yum install -y obclient`
```
user:
  username: admin
  password: admin
oceanbase-ce:
  servers:
    - name: observer1
      ip: 192.168.3.171
    - name: observer2
      ip: 192.168.3.172
    - name: observer3
      ip: 192.168.3.173
  global:
    home_path: /home/admin/observer
    data_dir: /data/obdata
    redo_dir: /data/obdata/redo
    devname: eno1
    mysql_port: 2881
    rpc_port: 2882
    zone: zone1
    datafile_size: 3000G
    appname: obcluster
    root_password: observer
    proxyro_password: obproxy
  observer1:
    zone: zone1
  observer2:
    zone: zone2
  observer3:
    zone: zone3
obproxy-ce:
  depends:
    - oceanbase-ce
  servers:
    - 192.168.3.171
    - 192.168.3.172
  global:
    home_path: /home/admin/obproxy
    skip_proxy_sys_private_check: true
    enable_strict_kernel_release: false
    listen_port: 2883
    prometheus_listen_port: 2884
    cluster_name: obcluster
    obproxy_sys_password: obproxy-sys
    observer_sys_password: obproxy
```

* `obd cluster autodeploy obcluster -c obcluster.yml`

* 修改root账户
  * 在初始化完成后会有如下日志：

```
+-------------------------------------------------+
|                     observer                    |
+---------------+---------+------+-------+--------+
| ip            | version | port | zone  | status |
+---------------+---------+------+-------+--------+
| 192.168.0.132 | 4.0.0.0 | 2881 | zone1 | ACTIVE |
+---------------+---------+------+-------+--------+
obclient -h192.168.0.132 -P2881 -uroot -pobserver -Doceanbase -A

obcluster running
```
* 直接运行`obclient -h192.168.0.132 -P2881 -uroot -pobserver -Doceanbase -A`
  * 进入ob数据库

* 把root用户密码修改成root
  * `ALTER user 'root'@'%' IDENTIFIED BY 'root';`

* 之后就可以愉快地用mysql连接了
