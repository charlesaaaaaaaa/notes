## Substr 是用来截取字符串的，如  
* `select substr ('192.168.0.1 , 6')` 结果：68.0.1
  * 这个sql有两个值，第一个是要操作的字符串
  * 第二个的意思是从第6个字符截取到最后一个字符
* `select substr('192.168.0.1, 1, 6')` 结果：192.16
  * 这个sql有两个值，第一个是要操作的字符串
  * 第二个和第三个代表的是从第1个字符截取到第6个字符
* 当我们要对其中数据进行聚合操作但对应列数据有小部分是不同的，如
  * 192.168.0.134：123412, 分号前面的地址可能就两三个，我们要筛选的也是ip地址，但后面的端口号不重复，直接用该列就无法进行聚合操作  
  * 所以这个时候就可以用Substr只截取前面的ip地址，然后进行聚合操作，如  
  * `SELECT SUBSTR(host, 1, 13)  FROM stuinfo group 1;`
  * 这个时候就只会对ip地址进行聚合操作 ,host是列名，1是从第1个字符开始，13是到第13个字符为止

