* 实际开发中，往往要对整块数据进行读写，这个时候就可以使用fread和fwrite函数
# fread
* fread函数的功能是：将fp指向的文件中读取count次，每次读size字节，读取的信息保存在buffer地址中
* 一般使用形式：
`fread(buffer,size,count,fp);`
* 示例
`fread(a,2,3,fp)`
```
上述示例说的是，从fp指向文件中每次读取两个字符并保存在数组a中，连续读取3次
```

# fwrite

* fwrite函数的功能是：将buffer地址开始的信息输出count次，每次写size字节到fp指向的文件中
* 一般使用形式：
`fwrite(buffer,size,count,fp);`
* 示例：
`fwrite(a,2,3,fp)`
```
上述示例说的是：
	将a地址开始的信息输出3次，每次写2字节到fp指向的文件中
```
