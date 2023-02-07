* printf/scanf函数都是格式化读写函数，fprintf/fscanf和他们差不多，但是读写的不是终端，而是磁盘文件
# fprintf
* 一般使用方式
`fprintf(文件指针，格式字符串，输出列表)`
`fprintf(fp, "%d", i)`
* 上述一般使用方式中，fprintf是以%d的格式把变量i输出到fp指向的文件中

# fscanf
* 一般使用方式
`fscanf(文件类型指针, 格式字符串, 输入列表);`
`fscanf(fp,"%d",i);`
* 上述一般使用方式中，fscanf是读取fp指向文件中i的值，以%d的格式读取

