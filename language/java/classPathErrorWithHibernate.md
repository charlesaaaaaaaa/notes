## Could not locate cfg.xml resource [hibernate.cfg.xml]
* 这个问题很明显是hibernate找不到配置文件
* 我出现这个原因是因为我加了-cp参数。不加-cp参数的情况下是会默认用系统的CLASSPATH. 
  * 在这个系统默认的CLASSPATH里面有Hibernate的src绝对路径。所以在我不用-cp参数的时候是可以正常找到全局配置文件的。
  * 但我加了-cp后，Hibernate程序的src目录绝对路径给冲掉了，所以Hibernate就会报错无法找到hibernate全局配置文件。
* 出现这个问题要确保以下两点：
  * Hibernate 5.0全局配置文件是默认在src目录下的，所以我们要把全局配置文件放到src下面就好。网上说的src/main/resources目录应该不是5.0的，反正我没试过
  * 确保CLASSPATH有src的绝对路径，这样java才能读到这个路径下
