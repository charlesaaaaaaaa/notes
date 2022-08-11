# 环境
## 使用的是centos8
```
yum install -y git cmake libarchive flex bison make gcc gcc-c++ ncurses-devel ncurses-libs libtirpc libtirpc-devel zlib-devel openssl openssl-devel libaio libaio-devel icu libicu libicu-devel readline readline-devel wget sudo vim python2 python3
wget https://github.com/thkukuk/rpcsvc-proto/releases/download/v1.4/rpcsvc-proto-1.4.tar.gz
tar -xzf rpcsvc-proto-1.4.tar.gz
cd rpcsvc-proto-1.4
./configure
make
sudo make install
```
* 添加用户
  * useradd kunlun
  * passwd -stdin kunlun
  * echo -e 'Kunlun1#\nKunlun1#' | passwd kunlun

## 下载二进制包
* sudo su kunlun
* cd /home/kunlun
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
