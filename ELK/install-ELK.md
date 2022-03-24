##ELK是由Elasticsreach 、logstash 、kibana三个开源软件组合使用的日志收集系统
#安装ELK：
##在安装前要先下载这些软件
```
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-8.1.1-x86_64.rpm
wget https://nodejs.org/dist/v16.14.2/node-v16.14.2.tar.gz
wget https://bitbucket.org/ariya/phantomjs/downloads/phantomjs-2.1.1-linux-x86_64.tar.bz2
git clone git@github.com:mobz/elasticsearch-head.git
wget https://artifacts.elastic.co/downloads/logstash/logstash-8.1.1-x86_64.rpm
wget https://artifacts.elastic.co/downloads/kibana/kibana-8.1.1-x86_64.rpm
```
##前期准备：
关闭防火墙：`systemctl stop firewalld.service`
查看java环境：`java -version`
没有安装java就直接安装一个就行
安装elasticsreach rpm包
下载完elasticsreach的rpm包后，使用 sudo rpm -ivh elasticsearch-8.1.1-x86_64.rpm 进行安装
重载systemctl : sudo systemctl daemon-reload
sudo systemctl enable elasticsearch.service
把elasticsreach 配置文件备份一个然后再编写对应的配置
sudo cp /etc/elasticsearch/elasticsearch.yml /etc/elasticsearch/elasticsearch.yml-bak
sudo vi /etc/elasticsearch/elasticsearch.yml ，配置主要改的参数如下(注意要把参数前面的#号注释给删掉)
cluster.name:{指定集群的名字}
node.name: {当前服务器名，如192.168.0.113是kunlun-test3}
path.data: /var/lib/elasticsearch {把#注释删了就行}
path.logs: /var/log/elasticsearch {把#注释删了就行}
bootstrap.memory_lock: false {原来是true}
network.host: {服务器ip}
http.port: {监听端口}
discovery.seed_hosts:["0.0.0.0"] {0.0.0.0代表全部}
xpack.security.enabled: false  {原本是true}
xpack.security.enrollment.enabled: false {原本是true}
enabled: false {原本是true}
enabled: false {原本是true}{最后四个参数为true的话可能会无法创建目录导致启动失败}
把elasticsearch目录权限全改成elasticsearch,在安装elasticserach的时候会自己创建elasticsearch用户，所以我们就不用自己创建了
sudo  chown -R elasticsearch:elasticsearch /etc/elasticsearch
启动elasticsearch : systemctl start elasticsearch.service
通过 netstat -ano | grep 9200 (假设9200是监听端口) 查看是否已经启动elasticsearch
然后可以通过curl http://ip:监听端口 查看有没有数据返回
或者可以直接在web上访问​http://ip:9200 查看是否正常有数据返回
Last modified 0 seconds ago
 
