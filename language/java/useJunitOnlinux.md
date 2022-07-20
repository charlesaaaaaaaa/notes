## 怎么在linux上面使用junit测试类
* 如果只是用于测试的话，是不推荐用main函数，因为会和程序代码混在一起。
* 这个时候就到junit的出场了。
* 我现在用的是junit4，因为5不知道怎么在linux上面运行
* junit4下载方法：(官网下载地址)[https://www.jetbrains.com/idea/download/#section=linux]
  * 先下载一个idea linux版本到服务器上面。
  * 解压后进入到lib目录里，在该目录下可以找到junit4.jar。
  * 把jar包复制到其它地方后就可以直接删了idea的包了
## 如何使用：
* 先编译：
  * `javac -cp $cp insertById.java`
* 后运行：
  * `java org.junit.runner.JUnitCore insertById`
* 注意java代码里面不要有package，不然会很麻烦
  * 不写package可以直接在当前目录下运行该测试类
## Tips:
* $cp 的内容：
```
.:/home/charles/file/java/classpath/junit4.jar:/home/charles/file/java/classpath/junit.jar:/home/charles/file/java/classpath/antlr-2.7.7.jar:/home/charles/file/java/classpath/byte-buddy-1.11.20.jar:/home/charles/file/java/classpath/classmate-1.5.1.jar:/home/charles/file/java/classpath/FastInfoset-1.2.15.jar:/home/charles/file/java/classpath/hibernate-commons-annotations-5.1.2.Final.jar:/home/charles/file/java/classpath/hibernate-core-5.6.2.Final.jar:/home/charles/file/java/classpath/istack-commons-runtime-3.0.7.jar:/home/charles/file/java/classpath/jandex-2.2.3.Final.jar:/home/charles/file/java/classpath/javax.activation-api-1.2.0.jar:/home/charles/file/java/classpath/javax.persistence-api-2.2.jar:/home/charles/file/java/classpath/jaxb-api-2.3.1.jar:/home/charles/file/java/classpath/jaxb-runtime-2.3.1.jar:/home/charles/file/java/classpath/jboss-logging-3.4.2.Final.jar:/home/charles/file/java/classpath/jboss-transaction-api_1.2_spec-1.1.1.Final.jar:/home/charles/file/java/classpath/junit-jupiter-5.7.0.jar:/home/charles/file/java/classpath/junit-jupiter-api-5.7.0.jar:/home/charles/file/java/classpath/junit-jupiter-engine-5.7.0.jar:/home/charles/file/java/classpath/junit-jupiter-params-5.7.0.jar:/home/charles/file/java/classpath/persistence-api-2.2.jar:/home/charles/file/java/classpath/stax-ex-1.8.jar:/home/charles/file/java/classpath/txw2-2.3.1.jar:/home/charles/file/java/classpath/validation-api-2.0.1.Final.jar:/home/charles/file/Hibernate-test/src/Hibernate.jar
```
