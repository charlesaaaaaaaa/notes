## centos 8 时间同步：
1.下载chrony。sudo yum install chrony 或者 sudo dnf install chrony  
2.修改/etc/chrony.conf 文件，新增阿里云的NTP时间服务器地址  
```
#pool 2.centos.pool.ntp.org iburst 把这行注释掉  
  server 210.72.145.44 iburst  
  server ntp.aliyun.com iburst 新增以上两行  
```
3.重启chronyd 服务，如果没有开启就先开启  
systemctl restart chronyd  
4.使用 timedatectl 命令  
5.查看NTP service是否为yes  

