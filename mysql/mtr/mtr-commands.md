更多的mtr命令请查看[官方文档](https://dev.mysql.com/doc/dev/mysql-server/latest/PAGE_MYSQL_TEST_COMMANDS.html)
# append_file filename
这个和write_file命令不同的地方在于这个命令如果在目录下没有对应的文件会自动创建  
这个的用法是和linux里面的EOF差不多的：append_file开头,以EOF结尾，中间就是要写的文件内容  
```
write_file $MYSQL_TMP_DIR/data01;
line one for the file
line two for the file
EOF
append_file $MYSQL_TMP_DIR/data01;
line three for the file
EOF
```

# cat_file filename
这个命令是用来cat一个文件的,很直观。  
`cat_file data01`

# change_user [username],[passwd],[dbname]
这个命令就是用来更改当前的用户名，且将指定的数据库修改为当前的默认数据库。
```
change_user root
--change_user kunlun,,test
```

