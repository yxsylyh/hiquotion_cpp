# DB 操作类库

包括 Ado，MySql和oracle的occi操作的包装类。

分类|文件|说明
----|----|----
ADOLib||
.|AdoConnection.h|Ado连接类，根据用户名、密码等信息创建的数据库连接类
.|AdoRecordset.h|Ado数据集类
MySqlLib||
.|MysqlDbHelper.h|MySQL连接助手类，根据用户名、密码等信息获取到数据库连接类
.|DbOperation.h|MySQL数据库操作类，执行sql（增删改），查询，事务处理等
OCCILib||
.|DbConfig.h|从配置文件读取用户名、密码和orcl，从而获取oracle数据库连接
.|OCCIWrapper.h|occi包装类，包括执行Statement（增删）、执行Statement更新、根据查询获取记录集、BLOB操作、事务处理等）


