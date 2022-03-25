## ELK是由Elasticsreach 、logstash 、kibana三个开源软件组合使用的日志收集系统
# 安装ELK：
## 在安装前要先下载这些软件
```
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-8.1.1-x86_64.rpm
wget https://nodejs.org/dist/v16.14.2/node-v16.14.2.tar.gz
wget https://bitbucket.org/ariya/phantomjs/downloads/phantomjs-2.1.1-linux-x86_64.tar.bz2
git clone git@github.com:mobz/elasticsearch-head.git
wget https://artifacts.elastic.co/downloads/logstash/logstash-8.1.1-x86_64.rpm
wget https://artifacts.elastic.co/downloads/kibana/kibana-8.1.1-x86_64.rpm
```
## 前期准备：

关闭防火墙：`systemctl stop firewalld.service`

查看java环境：`java -version`

没有安装java就直接安装一个就行
## 安装elasticsearch rpm包

下载完elasticsearch的rpm包后，使用 `sudo rpm -ivh elasticsearch-8.1.1-x86_64.rpm` 进行安装  
重载systemctl : `sudo systemctl daemon-reload`  
`sudo systemctl enable elasticsearch.service`  
把elasticsearch 配置文件备份一个然后再编写对应的配置  
`sudo cp /etc/elasticsearch/elasticsearch.yml /etc/elasticsearch/elasticsearch.yml-bak`  
`sudo vi /etc/elasticsearch/elasticsearch.yml` ，配置主要改的参数如下(注意要把参数前面的#号注释给删掉)  
```
cluster.name:{指定集群的名字}  
node.name: {当前服务器名，如192.168.0.113是kunlun-test3}  
path.data: /var/lib/elasticsearch {把#注释删了就行,如果要自己指定目录要记得把目录权限改成 elasticsearch:elasticsearch}  
path.logs: /var/log/elasticsearch {把#注释删了就行,同上}  
bootstrap.memory_lock: false {原来是true}  
network.host: {服务器ip}  
http.port: {监听端口}  
discovery.seed_hosts:["0.0.0.0"] {0.0.0.0代表全部}  
xpack.security.enabled: false  {原本是true}  
xpack.security.enrollment.enabled: false {原本是true}  
enabled: false {原本是true}  
enabled: false {原本是true}{最后四个参数为true的话可能会无法创建目录导致启动失败}  
```

把elasticsearch目录权限全改成elasticsearch,在安装elasticserach的时候会自己创建elasticsearch用户，所以我们就不用自己创建了  
`sudo  chown -R elasticsearch:elasticsearch /etc/elasticsearch`  
## 启动elasticsearch : `systemctl start elasticsearch.service`  
通过 netstat -ano | grep 9200 (假设9200是监听端口) 查看是否已经启动elasticsearch  
然后可以通过 `curl http://ip:` 监听端口 查看有没有数据返回  
或者可以直接在web上访问`http://ip:9200` 查看是否正常有数据返回  

# 安装Elasticsreach-head插件
## 安装node
`which node` 如果有输出则不需要做该步骤  
`sudo yum install gcc gcc-c++ make -y`  
`tar -zxf node-v16.14.2.tar.gz`，不一定是这个版本  
```
cd node-v16.14.2/
./configure
make && make install
```
## 安装phantomjs
```
sudo tar -jxf phantomjs-2.1.1-linux-x86_64.tar.bz2 -C /usr/local/src/
sudo cd /usr/local/src/phantomjs-2.1.1-linux-x86_64/bin
sudo cp phantomjs /usr/local/bin
```
## 安装Elasticsreach-head
```
sudo cp elasticsearch-head/ /usr/local/src
cd /usr/local/src/elasticsearch-head/ && sudo npm install
```
如果出现了以下错误：  
```
error code ELIFECYCLE
error errno 1
error phantomjs-prebuilt@2.1.16 install: `node install.js`
error Exit status 1
error Failed at the phantomjs-prebuilt@2.1.16 install script.
error This is probably not a problem with npm. There is likely additional logging output above.
```
则 `sudo rm /usr/local/bin/phantomjs`  
`sudo npm -g install phantomjs-prebuilt@2.1.16 --ignore-script`
## 修改Elasticsreach配置文件
`vi /etc/elasticsearch/elasticsearch.yml` , 末尾添加以下内容  
```
http.cors.enabled: true         #开启跨域访问支持，默认为 false
http.cors.allow-origin: "*"         #指定跨域访问允许的域名地址为所有
```
随后重启elasticsearch : `systemctl restart elasticsearch`  
## 启动Elasticsreach-head
进入到Elasticsreach-head目录下 ： `cd /usr/local/src/elasticsearch-head/`  
`npm run start &`  
默认端口是9100，所以`sudo lsof -i:9100` 或者 `netstat -antp | grep 9100`查看是否启动成功  
随后访问web ： `http://ip:9100/`,在最上方的输入框里面输入`ip:监听端口`，点击连接，查看集群健康值是否为green  
# 安装logstash
`rpm -ivh logstash-5.5.1.rpm`  
`systemctl start logstash.service`  
`systemctl enable logstash.service`  
`ln -s /usr/share/logstash/bin/logstash /usr/local/bin/`

在开启的时候要注意配置文件有没有读取权限,还有就是index名不可以有大写
