// 项目five.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

class stack 
{
public:
	int number;
	stack* link;
	stack() { number = 0; }
};

int main()
{
	int total = 0;
	int putin[1000] = {0};
	int a, b; 
	stack* head1, * head2;
	stack* current1, * current2;
	int checka, checkb, wrong;
	for (;;)
	{
		a = b = 0;
		wrong = checka = checkb = 0;
		current1 = new stack;
		current2 = new stack;
		head1 = current1;
		head2 = current2;
		cin >> total;
		if (total <= 0) { cout << "总数不能小于或等于0" << endl; }
		else
		{
			for (int n = 0; n <= total - 1; n++)
			{
				cin >> putin[n];
				if (putin[n] <= 0) { cout << "数列中有负数或零" << endl; wrong++; break; }
				else
				{
					if (putin[n] % 2 != 0)
					{
						current1->link = new stack;
						current1 = current1->link;
						current1->number = putin[n];
						a++;
					}
					else
					{
						current2->link = new stack;
						current2 = current2->link;
						current2->number = putin[n];
						b++;
					}
				}
			}
			//check
			if (wrong == 0)
			{
				current1 = head1;
				current2 = head2;
				for (int n = 1; n <= a; n++)
				{
					current1 = current1->link;
					stack *check;
					check = current1;
					for (int m = 1; m <= a - n; m++)
					{
						check = check->link;
						if (check->number == current1->number) { checka++; break; }
					}
					if (checka != 0) { break; }
				}

				for (int n = 1; n <= b; n++)
				{
					current2 = current2->link;
					stack *check;
					check = current2;
					for (int m = 1; m <= b - n; m++)
					{
						check = check->link;
						if (check->number == current2->number) { checkb++; break; }
					}
					if (checkb != 0) { break; }
				}

				if (checka == 0 && checkb == 0)
				{
					for (;;)
					{
						if (a >= 2)
						{
							cout << head1->link->number << " ";
							head1 = head1->link;
							cout << head1->link->number << " ";
							head1 = head1->link;
							a--; a--;
						}
						else
						{
							for (int n = 1; n <= a; n++)
							{
								cout << head1->link->number << " ";
								head1 = head1->link;
							}
							a = 0;
						}
						if (b != 0)
						{
							cout << head2->link->number << " ";
							head2 = head2->link;
							b--;
						}
						if (a == 0 && b == 0) { break; }
					}
				}
				else
				{
					cout << "输入中有重复的数字" << endl;
				}
			}

		}
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "重复实验?" << "  " << "(Y,N)";
		char k;
		cin >> k;
		for (;;)
		{
			if (k == 'N' || k == 'Y') { break; }
			else { cout << "请输入正确字符" << endl; }
		}
		if (k == 'N') { break; }
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
