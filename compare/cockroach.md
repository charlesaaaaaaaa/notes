部署cockroach群集是因为要用来和我们Kunlun进行对比  
所以我们就直接用insecure模式进行部署就行  
## 前期准备
`sudo timedatectl set-ntp no`  
`timedatectl`  
然后进去[这个网站](https://www.cockroachlabs.com/docs/v21.2/deploy-cockroachdb-on-premises-insecure.html#step-2-start-nodes),下载最新的软件  
下载完毕后`cp -i cockroach-v21.2.7.linux-amd64/cockroach /usr/local/bin/`  
```
mkdir -p /usr/local/lib/cockroach
cp -i cockroach-v21.2.7.linux-amd64/lib/libgeos.so /usr/local/lib/cockroach/
cp -i cockroach-v21.2.7.linux-amd64/lib/libgeos_c.so /usr/local/lib/cockroach/
```
## 以insecure模式启动cockroachdb
```
cockroach start \
--insecure \
--advertise-addr=<node1 address> \
--join=<node1 address>,<node2 address>,<node3 address> \
--cache=.25 \
--max-sql-memory=.25 \
--background
```
--advertise-addr,当前的服务器的ip，如果不想用默认的26257端口，则写成ip:port的形式  
--join，分别写上对应的要部署的服务器的ip，如果端口不是默认的26257，则写成ip:port  
--cache=.25，默认的.25是用在生产环境下的，我们对比就用8GiB吧，数值越大性能越好  
--max-sql-memory，存储临时sql语句的，像什么ddl，查询dml啥的。生产环境默认.25就行，但如果是用在开发环境，官方建议是128MiB来防止内存不足，那我们就用128MiB来配置
