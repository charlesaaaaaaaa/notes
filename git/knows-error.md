## 连接不上github解决方法
* 连接不上github目前已经遇到了两种问题。如下  
### 因网络问题无法连接上github  
* 分两种情况，一个是windows下，一个是linux下  
如是是linux下连接不上，git pull或者push/clone使用https连接会出现以下错误提示：  
`fatal: unable to access 'https:git': Failed to connect to github.com port 443: Connection refused`  
代表你现在的网络有问题，要在/etc/hosts下任意位置添加github.com的静态地址，如下：  
`140.82.112.3 github.com`  
当添加后会绕过DNS域名解析这一步，直接访问140.82.112.3。其它的网站也是一样的道理。  
* windows上用gitbash使用https的方式也会出现该错误，也是添加github的ip和域名映射  
文件位置在 `C:\Windows\System32\drivers\etc\hosts`  

### 因配置文件$HOME/.ssh/known_hosts错误无法连接上github
如图  
![err-pic](https://github.com/charlesaaaaaaaa/pic/blob/master/err/github-known_hosts.png)  

从图示上可以看到，有以下错误提示我们的.ssh/known_hosts文件里github的host key出问题了  
```
Add correct host key in /home/charles/.ssh/known_hosts to get rid of this message.  
Offending ECDSA key in /home/charles/.ssh/known_hosts:1  
```
只要把文件里对应的行给删了就行。如图示我这是`.ssh/known_hosts:1`第一行有问题  
删除了之后再重新操作一次，会提示你是否添加host，yes就行了
然后在.ssh/known_hosts就会出现新的github的host key

## github 网页端无法显示图片
这个其实和无法连接上github的解决方法是一样的。  
* 如果是windows，直接在`C:\Windows\System32\drivers\etc\hosts`下新增以下ip和域名的映射：  
```
140.82.112.3 github.com
140.82.114.20     gist.github.com
151.101.184.133    assets-cdn.github.com
151.101.184.133    raw.githubusercontent.com
151.101.184.133    gist.githubusercontent.com
151.101.184.133    cloud.githubusercontent.com
151.101.184.133    camo.githubusercontent.com
151.101.184.133    avatars0.githubusercontent.com
199.232.68.133     avatars0.githubusercontent.com
199.232.28.133     avatars1.githubusercontent.com
151.101.184.133    avatars1.githubusercontent.com
151.101.184.133    avatars2.githubusercontent.com
199.232.28.133     avatars2.githubusercontent.com
151.101.184.133    avatars3.githubusercontent.com
199.232.68.133     avatars3.githubusercontent.com
151.101.184.133    avatars4.githubusercontent.com
199.232.68.133     avatars4.githubusercontent.com
151.101.184.133    avatars5.githubusercontent.com
199.232.68.133     avatars5.githubusercontent.com
151.101.184.133    avatars6.githubusercontent.com
199.232.68.133     avatars6.githubusercontent.com
151.101.184.133    avatars7.githubusercontent.com
199.232.68.133     avatars7.githubusercontent.com
151.101.184.133    avatars8.githubusercontent.com
199.232.68.133     avatars8.githubusercontent.com
185.199.111.133    raw.githubusercontent.com 
185.199.110.133    raw.githubusercontent.com 
185.199.108.133    raw.githubusercontent.com 
185.199.109.133    raw.githubusercontent.com 
```
  * 这些都是github 曾经或者现在使用的ip，不知道那个有用那个没有，索性直接全部添加
  * 这个时候再去网页端就可以显示图片了
* 如果是在linux下，如ubuntu等有图形界面的linux发行版，在/etc/hosts下添加上述的github ip和域名的映射就行。

