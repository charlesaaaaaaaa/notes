## 连接不上github解决方法
* 连接不上github目前已经遇到了两种问题。如下  
### 因网络问题无法连接上github  
* 这个比较简单解决，分两种情况，一个是windows下，一个是linux下  
如是是linux下连接不上，git pull或者push/clone使用https连接会出现以下错误提示：  
`fatal: unable to access 'https:git': Failed to connect to github.com port 443: Connection refused`  
代表你现在的网络有问题，要在/etc/hosts下任意位置添加github.com的静态地址，如下：  
`140.82.112.3 github.com`  
当添加后会绕过DNS域名解析这一步，直接访问140.82.112.3。其它的网站也是一样的道理。  
* windows上用gitbash使用https的方式也会出现该错误，也是添加github的静态ipv4地址  
文件位置在 `C:\Windows\System32\drivers\etc\hosts`  

### 因配置文件$HOME/.ssh/known_hosts错误无法连接上github
如图  
[err-pic](https://github.com/charlesaaaaaaaa/pic/blob/master/err/github-known_hosts.png)  

Add correct host key in /home/charles/.ssh/known_hosts to get rid of this message.  
Offending ECDSA key in /home/charles/.ssh/known_hosts:1  

