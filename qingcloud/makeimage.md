# #依赖
## #使用的是centos7
```
yum install -y git cmake libarchive flex bison make gcc gcc-c++ ncurses-devel ncurses-libs libtirpc libtirpc-devel zlib-devel openssl openssl-devel libaio libaio-devel icu libicu libicu-devel readline readline-devel wget sudo vim python2 python3
wget https://github.com/thkukuk/rpcsvc-proto/releases/download/v1.4/rpcsvc-proto-1.4.tar.gz
tar -xzf rpcsvc-proto-1.4.tar.gz
cd rpcsvc-proto-1.4
./configure
make
sudo make install
```

## #安装app-agent
### #这个是使用青云的meta服务必需要安装的软件
* wget https://docsv3.qingcloud.com/appcenter/dev-platform/cluster-developer-guide/scripts/app-agent.tar.gz
* tar -zxf app-agent.tar.gz
* cd app-agent-linux-amd64
* bash ./install.sh


* #添加用户
  * useradd kunlun
  * echo -e 'Kunlun1#\nKunlun1#' | passwd kunlun
    * #这个是模拟输入两次密码
* #增加用户sudo权限
  * sed -i '100akunlun  ALL=(ALL)       NOPASSWD:ALL' /etc/sudoers


## #下载二进制包
* sudo su kunlun
* mkdir -p /home/kunlun/base
* cd /home/kunlun/base
```
wget http://zettatech.tpddns.cn:14000/thirdparty/hadoop-3.3.1.tar.gz
wget http://zettatech.tpddns.cn:14000/thirdparty/jdk-8u131-linux-x64.tar.gz
wget http://zettatech.tpddns.cn:14000/thirdparty/mysql-connector-python-2.1.3.tar.gz
wget http://zettatech.tpddns.cn:14000/thirdparty/prometheus.tgz
wget http://zettatech.tpddns.cn:14000/thirdparty/haproxy-2.5.0-bin.tar.gz

Version=1.0.1
wget http://kunlunbase.com:14000/releases/$Version/release-binaries/kunlun-cluster-manager-$Version.tgz
wget http://kunlunbase.com:14000/releases/$Version/release-binaries/kunlun-node-manager-$Version.tgz
wget http://kunlunbase.com:14000/releases/$Version/release-binaries/kunlun-server-$Version.tgz
wget http://kunlunbase.com:14000/releases/$Version/release-binaries/kunlun-storage-$Version.tgz
```

# #建立文件目录
```
mkdir -p /home/kunlun/base/program_binaries/util /home/kunlun/base/instance_binaries \
/home/kunlun/base/server_datadir /home/kunlun/base/storage_datadir /home/kunlun/base/storage_logdir \
/home/kunlun/base/storage_waldir /home/kunlun/base/instance_binaries/storage/6001 \
/home/kunlun/base/storage_datadir/6001 /home/kunlun/base/storage_logdir/6001 /home/kunlun/base/storage_waldi/6001 \
/home/kunlun/base/instance_binaries/computer
```
* mv *gz /home/kunlun/base/program_binaries
* cd /home/kunlun/base/program_binaries
```
tar -zxf hadoop-3.3.1.tar.gz
tar -zxf haproxy-2.5.0-bin.tar.gz
tar -zxf jdk-8u131-linux-x64.tar.gz
tar -zxf kunlun-cluster-manager-$Version.tgz
tar -zxf kunlun-node-manager-$Version.tgz
tar -zxf kunlun-server-$Version.tgz
tar -zxf kunlun-storage-$Version.tgz
tar -zxf mysql-connector-python-2.1.3.tar.gz
tar -zxf prometheus.tgz 

rm -rf hadoop-3.3.1.tar.gz haproxy-2.5.0-bin.tar.gz jdk-8u131-linux-x64.tar.gz  \
kunlun-cluster-manager-$Version.tgz kunlun-node-manager-$Version.tgz kunlun-server-1.0.1.tgz \
kunlun-storage-$Version.tgz mysql-connector-python-2.1.3.tar.gz prometheus.tgz

mv kunlun-cluster-manager-$Version ..
mv kunlun-node-manager-$Version ..
cp kunlun-storage-$Version /home/kunlun/base/instance_binaries/storage/6001
```

# #环境
```
JAVA_HOME=home/kunlun/base/program_binaries/jdk1.8.0_131
HADOOP_HOME=/home/kunlun/base/program_binaries/hadoop-3.3.1
SERVER_HOME=/home/kunlun/base/program_binaries/kunlun-server-$Version
STORAGE_HOME=/home/kunlun/base/program_binaries/kunlun-storage-$Version
CLUSTER_HOME=/home/kunlun/base/kunlun-cluster-manager-$Version
NODE_HOME=/home/kunlun/base/kunlun-node-manager-$Version
cat << EOF >> ~/.bashrc
JAVA_HOME=home/kunlun/base/program_binaries/jdk1.8.0_131
HADOOP_HOME=/home/kunlun/base/program_binaries/hadoop-3.3.1
SERVER_HOME=/home/kunlun/base/program_binaries/kunlun-server-$Version
STORAGE_HOME=/home/kunlun/base/program_binaries/kunlun-storage-$Version
CLUSTER_HOME=/home/kunlun/base/kunlun-cluster-manager-$Version
NODE_HOME=/home/kunlun/base/kunlun-node-manager-$Version
export PATH=$SERVER_HOME/bin:$STORAGE_HOME/bin:$CLUSTER_HOME/bin:$NODE_HOME/bin:$JAVA_HOME/bin:$HADOOP_HOME/bin:$PATH
export LD_LIBRARY_PATH=$SERVER_HOME/lib:$STORAGE_HOME/lib:$CLUSTER_HOME/lib:$NODE_HOME/lib:$LD_LIBRARY_PATH
EOF
source ~/.bashrc
```
