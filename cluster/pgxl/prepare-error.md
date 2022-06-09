## 超过最大prepare 事务数：
* 一般这个只有在pgxl才有(pgxz,pgxc都没有)，pgxl默认的max_prepared_transactions 数量太小，只有10
* 一般情况下这个参数是要大于max_connections这个参数的才不会有该错误。
