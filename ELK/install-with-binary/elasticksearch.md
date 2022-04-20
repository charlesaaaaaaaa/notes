[elasticsearch文档](https://www.elastic.co/guide/index.html)
## 1.下载二进制包：
```
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-8.1.2-linux-x86_64.tar.gz
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-8.1.2-linux-x86_64.tar.gz.sha512
shasum -a 512 -c elasticsearch-8.1.2-linux-x86_64.tar.gz.sha512 
tar -xzf elasticsearch-8.1.2-linux-x86_64.tar.gz
cd elasticsearch-8.1.2/ 
```
shasum 的作用就是和md5sum作用差不多，校验是否下载完整，下载没问题会有 `elasticsearch-{version}-linux-x86_64.tar.gz: OK` 的输出  

## 2.配置elasticsearch
elasticksearch 有三个配置文件：配置文件为YAML格式，遵循YAML规则  
* 1.elasticsearch.yml用于配置 Elasticsearch  
* 2.jvm.options用于配置 Elasticsearch JVM 设置
* 3.log4j2.properties用于配置 Elasticsearch 日志记录

这些文件都是在与 **bin目录同级的config目录** 下  

### elasticsearch.yml:
  * 配置集群名，在配置文件里面找到以下内容，并且修改值与去掉#注释
    * 改前：`#cluster.name: my-application`
    * 改后：`cluster.name: first-application`
  * 配置节点名：
    * 改前：`#node.name: node-1`
    * 改后：`node.name: es-node1`
  * 配置data目录路径：elasticksearch官方强烈建议要把路径设置在es_home目录之处的目录里
    * 改前：`#path.data: /path/to/data`
    * 改后：`path.data: /home/es/data`
  * 配置log目录路径：
    * 改前：`#path.logs: /path/to/logs`
    * 改后：`path.logs: /home/es/logs`
  * data & log 目录还可以这样配置：
```
path:
  data: /home/es/data
  logs: /home/es/logs
```
  * 配置ip：默认情况下es会绑定127.0.0.1或者 ::1,如果不想要这两个，用需要改变以下配置：
    * 改前：`#network.host: 192.168.0.1`
    * 改后：`network.host: 192.168.0.100` 或者为 0.0.0.0 ，意为全部
    * 修改该项之后，es会认为要从开发模式变成生产模式，会有很多异常信息。如果有错误的配置，则会阻止启动
* 配置集群信息：该配置项是用来联系其它主机的节点形成集群的。如果没有加上端口号则用默认的9200端口号来寻找
  * 改前：`#discovery.seed_hosts: ["host1", "host2"]`
  * 改后：`discovery.seed_hosts: ["192.168.0.100:9210", "192.168.0.101"]`
```
也可以改成：
discovery.seed_hosts: 
  - 192.168.0.100:9210
  - 192.168.0.101
```
* 配置网页端的监听端口和ip
  * 将`http.host: [_local_, _site_]`和`#http.port: 9200`修改成对应的值

* 将所有xpack的配置项都关闭：否则会连接不上网页端, 暂不清楚原因
```
xpack.security.enabled: false

xpack.security.enrollment.enabled: false

# Enable encryption for HTTP API client connections, such as Kibana, Logstash, and Agents
xpack.security.http.ssl:
  enabled: false
  keystore.path: certs/http.p12

# Enable encryption and mutual authentication between cluster nodes
xpack.security.transport.ssl:
  enabled: false

```
## 3.运行elasticsearch
* `./bin/elasticsearch`
  * 没问题的话运行不会有报错
* 以守护进程的方式进行elasticsearch
  * `./bin/elasticsearch -d -p pid`
  * -d 以守护进程的方式运行
  * -p 指定pid文件路径, 不一定要加这个选项
* 当增加新节点的时候，要用到 **bin/elasticsearch-create-enrollment-token** 产生口令
  * 在已经运行了es的服务器上，运行 `./bin/elasticsearch-create-enrollment-token -s node`
  * 复制下产生的口令
  * 在要新增的服务器上，运行 `./bin/elasticsearch --enrollment-token <enrollment-token>`

### 运行完毕后连接网页端
* window下打开浏览器，输入es所在的ip:port
* linux下 `curl http://es-ip:es-port`
  * 返回类似以下的json串则为成功
```
{
  "name" : "node1",
  "cluster_name" : "first",
  "cluster_uuid" : "_na_",
  "version" : {
    "number" : "8.1.2",
    "build_flavor" : "default",
    "build_type" : "tar",
    "build_hash" : "31df9689e80bad366ac20176aa7f2371ea5eb4c1",
    "build_date" : "2022-03-29T21:18:59.991429448Z",
    "build_snapshot" : false,
    "lucene_version" : "9.0.0",
    "minimum_wire_compatibility_version" : "7.17.0",
    "minimum_index_compatibility_version" : "7.0.0"
  },
  "tagline" : "You Know, for Search"
}
```

