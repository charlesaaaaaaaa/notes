## 嵌套
* 在声明一个结构体类型时是可以嵌套另一个已经声明了的结构体类型
```
struct date
{
	int iYear;
	int iMonth;
	int iDay;
};
struct Student
{
	char cName[64];
	int iAge;
	struct date brithday;
};
```

* 定义

```
struct Student student1;
```

* 赋值
  * 因为brithday是用的date结构体类型，所以还要在brithday后面再引出对应的列名才可以赋值
```
student1.brithday.iYear = 1999;
student1.brithday.iMonth = 2;
student1.brithday.iDay = 1;
```

