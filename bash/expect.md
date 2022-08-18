== expect
* `sudo yum install expect`
* 这个不是系统自带的软件
* 这个暂时是用来自动远程输入密码的，其它的用法还没有研究到
* 在一些不能用ssh互信的场景下可以使用该命令自动输入密码进行操作
* 直接看代码吧
```
expect -c "
    spawn scp ./test.txt root@192.168.100.22:/root
    expect {
        \"yes/no\" {send \"yes\r\";exp_continue;}
        \"*password\" {set timeout 500;send \"123456\r\";}
    }
expect eof"
```

