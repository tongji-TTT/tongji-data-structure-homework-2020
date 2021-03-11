// 项目four（2）.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <math.h>
using namespace std;
class numberstack 
{

public:
	double number;
	numberstack * link;
	numberstack() {  number = 0; }
};

class charstack
{
public:
	char sign;
	charstack * link;
	charstack() { sign = ' '; }
};

int main()
{
	char putin[100];//一串输入的表达式
	int putinnumber; //表达式的长度
	char putinchar[5];//存储字符型的数字
	int checkputinchar1 = 0;  // 判断是否进行数字栈的存储
	int checkputinchar2 = 0; // 记录写入putinchar数组的元素个数
	double changechar(char a[5],int b,int *c);//将字符变成double
	int checkchar(char a);//符号辨别函数
	int count(numberstack *&head1, charstack *&head2,char a);//对数字栈和字符栈操作
	int count2(numberstack *&head1, charstack *&head2,char a);//对数字栈和字符栈操作(括号)
	int judge(char putin[100], int n);//判断符号之间是否正确
	int numberstack1 = 0;  //中期检验数字串
	int charstack1 = 0;   //中期检验字符串
	int changenumber = 0; //单目+-的判断
	int bracket = 0;//判断是否有括号存在,同时可以判断是几级括号
	int answerkind = 0;//判断答案的种类

	for (;;)
	{
		 checkputinchar1 = 0;  // 判断是否进行数字栈的存储
		 checkputinchar2 = 0; // 记录写入putinchar数组的元素个数
		 numberstack1 = 0;  //中期检验数字串
		 charstack1 = 0;   //中期检验字符串
		 changenumber = 0; //单目+-的判断
		 bracket = 0;//判断是否有括号存在,同时可以判断是几级括号
		 putinnumber = 0;
		 cout << "请输入表达式" << endl;
		 putin[0] = '#';
		for (int n = 1; n <= 99; n++)
		{
			putin[n]=getchar() ; putinnumber = n;
			if (int(putin[n]) == 10) { break; }
		}

		//开始将数字和字符分开放入两个栈中
		numberstack* head1;
		numberstack* current1;
		current1 = new numberstack;
		head1 = current1;

		charstack* head2;
		charstack* current2;
		current2 = new charstack;
		head2 = current2;

		for (int n = 0; n <= putinnumber; n++)
		{
			if (int(putin[n]) >= 48 && int(putin[n]) <= 57)
			{
				checkputinchar1 = 1;
				putinchar[checkputinchar2] = putin[n];
				checkputinchar2++;
			}    //数字处理

			if (int(putin[n]) < 48 || int(putin[n]) > 57)
			{
				if (checkchar(putin[n]) == 0) {  answerkind = 1; break; }//错误弹出
				if (judge(putin, n) != 0) { answerkind = judge(putin, n); break; };
				if (checkputinchar1 == 1)  //进行数字栈的存储
				{
					numberstack1++;
					head1->number = changechar(putinchar, checkputinchar2 - 1, &changenumber);//放入栈中
					current1 = new numberstack;
					current1->link = head1;
					head1 = current1;
					checkputinchar1 = 0;
					checkputinchar2 = 0;
				}
				if (checkputinchar1 == 0)            //进行符号栈的存储
				{

					if (charstack1 == 0)                      //先进行‘#’的存储
					{
						charstack1++;
						head2->sign = putin[n];
						current2 = new charstack;
						current2->link = head2;
						head2 = current2;
					}
					else               //正常符号进行存储
					{


						if (checkchar(putin[n]) == -3 || bracket == 1|| checkchar(putin[n]) == -4) //进行括号的储存
						{
							if (checkchar(putin[n]) == -3)
							{

								bracket++;                             //将（存储进入栈中
								charstack1++;
								head2->sign = putin[n];
								current2 = new charstack;
								current2->link = head2;
								head2 = current2;
							}
							else
							{
								if (checkchar(putin[n]) > checkchar(head2->link->sign))//不需要退栈的符号
								{
									if ((putin[n] == '+' || putin[n] == '-') && (checkchar(putin[n - 1]) != 0 && checkchar(putin[n - 1]) != 1) && checkchar(putin[n - 1]) != -4)
									{
										if (putin[n] == '+') { changenumber = 1; }
										if (putin[n] == '-') { changenumber = -1; }
									}
									else
									{
										charstack1++;
										head2->sign = putin[n];
										current2 = new charstack;
										current2->link = head2;
										head2 = current2;
									}
								}
								else
								{
									if ((putin[n] == '+' || putin[n] == '-') && (checkchar(putin[n - 1]) != 0 && checkchar(putin[n - 1]) != 1) && checkchar(putin[n - 1]) != -4)
									{
										if (putin[n] == '+') { changenumber = 1; }
										if (putin[n] == '-') { changenumber = -1; }
									}
									else
									{
										int k = count2(head1, head2, putin[n]);
										if (k >= -1) { bracket = bracket + k; }
										else { answerkind = k+1; break; }//括号不匹配错误弹出
									}

								}
							}
						}
						else         //非括号的存储
						{

							if (checkchar(putin[n]) > checkchar(head2->link->sign))//不需要退栈的符号
							{   //
								if ((putin[n] == '+' || putin[n] == '-') && (checkchar(putin[n - 1]) != 0 && checkchar(putin[n - 1]) != 1) && checkchar(putin[n - 1]) != -4)
								{
									if (putin[n] == '+') { changenumber = 1; }
									if (putin[n] == '-') { changenumber = -1; }
								}
								else
								{
									charstack1++;
									head2->sign = putin[n];
									current2 = new charstack;
									current2->link = head2;
									head2 = current2;
								}
							}
							else
							{
								if ((putin[n] == '+' || putin[n] == '-') && (checkchar(putin[n - 1]) != 0 && checkchar(putin[n - 1]) != 1))
								{
									if (putin[n] == '+') { changenumber = 1; }
									if (putin[n] == '-') { changenumber = -1; }
								}
								else
								{
									count(head1, head2, putin[n]);
								}
							}
						}
					}
				}
			}
		}
		if (answerkind == 0)
		{	
			cout << head1->link->number << endl;
		}
		else 
		{
			switch (answerkind)
			{
			case 4: {cout << "0不可以成为除数" << endl; break; }
			case 3: {cout << "%后面字符非法" << endl; break; }
			case 2: {cout << "*/%^前面字符非法" << endl; break; }
			case 1: {cout << "输入出现非法字符" << endl; break; }
			case -1: {cout << "括号不匹配" << endl; break; }
			case -2: {cout << "输入的数字小于等于一个" << endl; break; }
			default:break;
			}
		
		}
		cout << "是否要继续" << "    " << "(Y,N)" << endl;
		char going;
		for (;;)
		{
			cin >> going;
			if (going == 'Y' || going == 'N') { break; }
			cout << "请输入正确的符号" << endl;
		}
		if (going == 'N') { break; }
		getchar();//清除缓冲区的回车键
	}

	return 0;
}





double changechar(char a[5], int b,int *c)//将字符变成double
{
	double number = 0;
	for (int n = 0; n <= b; n++)
	{
		number = number + (int(a[n]) - 48)*pow(10, b - n);
	}
	if (*c == 1 || *c == 0)
	{
		*c = 0;   return number; 
	}
	if (*c == -1)
	{

		*c = 0;  return -number;
	}
}

int checkchar(char a)  //判断字符
{

	switch (a)
	{
	case '#': {return -1; break; }
	case '+': {return 1; break; }
	case '-': {return 1; break; }
	case '*': {return 2; break; }
	case '/': {return 2; break; }
	case '%': {return 2; break; }
	case '^': {return 3; break; }
	case '(': {return -3; break; }
	case ')': {return -4; break; }
	case 10: {return-1; break; }
	default:  return 0;
		break;
	}
}

int count(numberstack  *&head1, charstack *&head2,char a)//对数字栈和字符栈操作
{
	if (head1->link == NULL) { return -3; }
	double temp;
	numberstack *p1;
	charstack *p2;
	switch (head2->link->sign)
	{ 
	case '+': 
	{   
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = head1->link->number + temp;
	break;
	}
	case '-': 
	{
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = head1->link->number - temp;
		break;
	}
	case '*':
	{
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = head1->link->number * temp;
		break;
	}
	case '/': 
	{
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = (head1->link->number/temp);
		break;
	}
	case '%':
	{
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = int(head1->link->number) %int(temp);
		break;
	}
	case '^': 
	{
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = pow(head1->link->number ,temp);
		break;
	}
	case'#':
	{
		return 0; break;
	}
	default: break;
	}
	
	p2 = head2;
	head2 = head2->link;
	delete p2;

	if (checkchar(a) > checkchar(head2->link->sign))
	{
		head2->sign = a;
		p2 = new charstack;
		p2->link = head2;
		head2 = p2;
		return 0;
	}
	else 
	{
		if (checkchar(a) == checkchar(head2->link->sign) && checkchar(a) == -1)
		{
			return 0;
		}
		else
		{
			count(head1, head2, a);
		}
	}
}

int count2(numberstack  *&head1, charstack *&head2, char a)//对数字栈和字符栈操作(括号)
{
	if (head1->link == NULL) { return -3; }
	double temp;
	numberstack *p1;
	charstack *p2;
	switch (head2->link->sign)
	{
	case '+':
	{   
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = head1->link->number + temp;
		break;
	}
	case '-':
	{
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = head1->link->number - temp;
		break;
	}
	case '*':
	{   //cout << "*" << endl;
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = head1->link->number * temp;
		break;
	}
	case '/':
	{  // cout << "/" << endl;
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = (head1->link->number / temp);
		break;
	}
	case '%':
	{
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = int(head1->link->number) % int(temp);
		break;
	}
	case '^':
	{
		temp = head1->link->number;
		p1 = head1;
		head1 = head1->link;
		delete p1;
		head1->link->number = pow(head1->link->number, temp);
		break;
	}

	default: break;
	}

		p2 = head2;
		head2 = head2->link;
		delete p2;
	if (checkchar(a) > checkchar(head2->link->sign))
	{
		head2->sign = a;
		p2 = new charstack;
		p2->link = head2;
		head2 = p2;
		return 0;
	}
	else
	{
		if (checkchar(a)<checkchar(head2->link->sign)&&checkchar(head2->link->sign)==-3)
		{
			p2 = head2;
			head2 = head2->link;
			delete p2;
			return -1;
		}
		else
		{
			if (checkchar(a) == -4 && checkchar(head2->link->sign) == -1)
			{  
				return -2;
			}
			else
			{
				count2(head1, head2, a);
			}
		}
	}
}


int judge(char putin[100], int n) //判断是否表达式中符号数学错误
{
	if (n >= 1)
	{
		if (checkchar(putin[n]) == 2 || checkchar(putin[n]) == 3)
		{
			if (checkchar(putin[n-1]) != -4 && checkchar(putin[n-1]) != 0)
			{
				return 2;
			}
		}
		if (putin[n] == '%'&&putin[n + 1] == '-') { return 3; }
		if (putin[n] == '/'&&putin[n + 1] == '0') { return 4; }
	}
	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
