[elasticksearch文档](https://www.elastic.co/guide/index.html)
1.下载二进制包：
```
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-8.1.2-linux-x86_64.tar.gz
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-8.1.2-linux-x86_64.tar.gz.sha512
shasum -a 512 -c elasticsearch-8.1.2-linux-x86_64.tar.gz.sha512 
tar -xzf elasticsearch-8.1.2-linux-x86_64.tar.gz
cd elasticsearch-8.1.2/ 
```
shasum 的作用就是和md5sum作用差不多，校验是否下载完整，下载没问题会有 `elasticsearch-{version}-linux-x86_64.tar.gz: OK` 的输出  

