[elasticksearch文档](https://www.elastic.co/guide/index.html)
## 1.下载二进制包：
```
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-8.1.2-linux-x86_64.tar.gz
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-8.1.2-linux-x86_64.tar.gz.sha512
shasum -a 512 -c elasticsearch-8.1.2-linux-x86_64.tar.gz.sha512 
tar -xzf elasticsearch-8.1.2-linux-x86_64.tar.gz
cd elasticsearch-8.1.2/ 
```
shasum 的作用就是和md5sum作用差不多，校验是否下载完整，下载没问题会有 `elasticsearch-{version}-linux-x86_64.tar.gz: OK` 的输出  

## 2.简单运行
`./bin/elasticsearch`  
没问题的话运行不会有报错，但一般不直接运行，一般是要先配置

## 3.配置elasticksearch
elasticksearch 有三个配置文件：配置文件为YAML格式，遵循YAML规则  
* 1.elasticsearch.yml用于配置 Elasticsearch  
* 2.jvm.options用于配置 Elasticsearch JVM 设置
* 3.log4j2.properties用于配置 Elasticsearch 日志记录

这些文件都是在与 **bin目录同级的config目录** 下  

* elasticsearch.yml:
  * 配置集群名，在配置文件里面找到以下内容，并且修改值与去掉#注释
    * 改前：`#cluster.name: my-application`
    * 改后：`cluster.name: first-application`
  * 配置路径：elasticksearch官方强烈建议要把路径设置在es_home目录之处的目录里
    * 改前：`#node.name: node-1`
    * 改后：`node.name: es-node1`