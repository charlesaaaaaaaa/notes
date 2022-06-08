## Failed to get pooled connections
这个问题的原因是pgxz在运行完高并发的测试后，后台的idle（闲置进程）过多且要很久之后才会自动杀掉。  
**解决方式如下：**
* 1. 可以直接kill掉所有的postgres idle进程
  * `ps -ef | grep postgres | grep idle | awk '{print $2}' | sed '$d' | xargs kill -9`
  * 但这个要每次测试一次性能后 所有的cn节点和dn节点及其备节点所在的服务器 都要kill一次，很麻烦
* 2. 在配置文件设置idle超时自动杀掉参数。
  * 在pg14就加入了一个 `idle_session_timeout` 这个参数，以ms计, 为0代表禁用该功能。但当前的pgxz（tbase）用的是比较老的pg版本，所以没有这个参数。之所以提出来是因为想记录一下这个问题当前版本的pg的解决方案
