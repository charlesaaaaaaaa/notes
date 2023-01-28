# 数组 -- 定义结构体类型数组
* 定义一个基本类型变量时，我们还可以定义成数组。
* 结构体类型也可以定义成一个数组

* [](#)

## 定义
```
struct Student
{
    char cName[64];
    int iYear;
    int iGrade;
    char cSex;
} student1[5];
```
* 上述示例就是定义了一个结构体类型的数组，有5个元素

## 初始化
```
struct Student
{
    char cName[64];
    int iYear;
    int iGrade;
    char cSex;
} student1[5] = {{"张三", 18, 3, "m"},
				{"李四", 17, 2, "w"},	
				{"王五", 18, 3, "m"},
				{"小六", 19, 3, "m"},
				{"小七", 17, 1, "w"}};
```

## 赋值
