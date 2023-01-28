# 指针 -- 结构体类型指针变量
```
struct Student
{
	char cName[64];
    int iYear;
    int iGrade;
    char cSex;
} student1 = {"张三", "18", "3", "m"};
```
## 定义

```
struct Student *pStudent1; // 声明有一个Student结构体类型的指针变量pStudent1
pStudent1 = &student1; //把结构体变量student1给到结构体指针pStudent1
```

## 引用
```
printf("%s", (*pStudent).cName);
```
* 注意：这里在引用的时候指针变量要加上小括号
  * 因为**成员运算符`.`**的优先级是要高于`*`的
  * 如果不加小括号，会先运算`.`然后再运算`*`，这样就不对了

* 下述是另一种引用结构体成员的形式
```
pStudent -> cName; //引用pStudent指向的cName成员
pStudnet -> cName = "李四"; //赋值给pStudent指向的cName成员并且引用
```
