更多的mtr命令请查看[这里](https://dev.mysql.com/doc/dev/mysql-server/latest/PAGE_MYSQL_TEST_COMMANDS.html)
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



