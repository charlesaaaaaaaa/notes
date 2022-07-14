## 超大规模集群测试：
* 32、256个shard，每个shards两个备。
* 通过py创建sql文件，该sql文件里面要开启一个事务，随便insert多条sql语句，所有sql语句分别插入1kw，5kw，10kw行的数据行，然后commit该事务。根据该条事务所insert的数据量，计算一共要多少条事务可以灌到2TB、10TB数据量。
* 
