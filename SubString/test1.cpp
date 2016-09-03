// 要求：
// 查询子字符串，输入两个字符串A和B，A的长度大于B，找出B字符串在A中第一次出现的位置。

#include<stdio.h>

int Instring(char *P)  // 字符串输入函数
{
	int L = 0;
	char a;
	a = getchar();
	L++;
	*P = a;
	P++;
	while (a != '\n') {
		a = getchar();
		if (a == '\n')
			break;
		L++;
		*P = a;
		P++;
	}
	return L;  // L记录输入字符串的长度
}


void main() {
	char *A, *B, *P1, *P2, a, b;
	int i, L1, L2;
	A = &a;
	B = &b;
	P1 = A;                                     //预存字符串首地址
	P2 = B;
	printf("请输入第一串字符串，以回车结束");
	L1 = Instring(A);
	printf("请输入第二串字符串，以回车结束");
	L2 = Instring(B);

	if (L1 < L2)                               //总将长串赋给A
	{
		char *Temp;
		Temp = P1;
		P1 = P2;
		P2 = Temp;

		int temp;
		temp = L1;
		L1 = L2;
		L2 = temp;
	}

	int flag, L, num;
	char *LA, *LB;

	for (i = 0; i <= L1 - L2; i++)                //顺序比较，只需比较L1-L2+1次
	{
		LA = A + i;                             //LA 为实时更新的A串起始判断位置
		LB = B;                               //LB 为B串起始位置
		flag = 1;
		L = 0;
		while (flag == 1) {
			if (*LA == *LB) {
				LA++;
				LB++;
				L++;                          //L 记录当前已检测的字符串长度
				if (L == L2) {
					num = i + 1;              //num 记录B出现在A的起始位置
					break;
				}
			} else
				flag = 0;
		}
	}

	if (flag == 0)
		printf("无法在A串中找到相应的B串");
	getchar();
	getchar();
}
