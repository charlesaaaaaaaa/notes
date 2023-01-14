#include "string.h"
#include "stdio.h"

void add(char c1[10], char c2[10], char c3[10], char c4[10]);

int main()
{
	static char cTime[][10] = {"08:00 ", "12:00 ", "16:00 ", "20:00 ", "00:00 "};
	static char cTemp[][10] = {"晴 ", "晴 ", "晴 ", "晴 " ,"晴 "};
	static char cNum[][10] = {"13度 ", "19度 ", "18度 ", "15度 " ,"12度 "};
	static char cTian[][10] = {"微风", "微风", "微风", "微风" ,"微风"};

	for(int i = 0; i < 5; i++)
	{
		add(cTime[i], cTemp[i], cNum[i], cTian[i]);
	}
	return 0;
}

void add(char c1[10], char c2[10], char c3[10], char c4[10])
{
	char cTotal[100];
	strcpy(cTotal, c1); 
	//这个把c1 copy给cTotal是因为如果直接用c1进行strcat操作
	//会把上面定义的cTime的所有元素给直接替换成strcat c1后的元素
	//所以我们要把c1的值给到cTotal，隔离开cTime，不让strcat影响到原来的cTime
	//还有就是为什么一定要用strcpy,因为直接cTotal = c1在编译时会失败，只能用strcpy函数

	strcat(cTotal, c2);
	strcat(cTotal, c3);
	strcat(cTotal, c4);

	printf("%s\n", cTotal);
}
