// 项目three.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
class palace                //建立迷宫函数
{
public:
	int movepath; //一个用于记录是否是空路，一个用于记录是否曾走过这条路
	int move;
	palace() { movepath = 1; move = 1; };
};

struct date
{
public :
	int row;
	int col;
	date* node;
};

class stack                  //建立一个栈
{
private :
	date * top;
public:
	stack() ;
	void  pushin(int n,int m) ;//压入函数
	int  decline();
	void  sendstack(int &n,int &m);//推栈函数
	void  showout();
};
stack::stack()
{
	top = new date;
	top->col = 1;
	top->row = 1;
	top->node = NULL;
}
void stack::pushin(int n,int m)
{
	date *p;
	p = new date;
	p->col = m;
	p->row = n;
	p->node = top;
	top = p;
}
void stack::sendstack(int &n,int &m)
{
	n = top->row;
	m = top->col;
}
int stack::decline() 
{
	if (top->node != NULL)
	{
		date *p;
		p = top;
		top = p->node;
		delete p;
		return 1;
	}
	else
	{
		if (top->node == NULL) { return 0; }

	}
}

void stack::showout()
{
	date *p = top;
	for (;;)
	{
		cout << "(" << top->row+1 << "," << top->col+1 << ")" << " " << endl;
		if (top->node == NULL) { break; }
		top = top->node;
	}
	top = p;
}

int main()
{
	palace a[7][7];
	a[1][1].move = a[2][1].move = a[2][2].move = a[2][3].move = a[3][3].move = a[4][3].move = a[4][4].move = a[4][5].move = a[5][5].move = 0;
	a[1][1].movepath = a[2][1].movepath = a[2][2].movepath = a[2][3].movepath = a[3][3].movepath = a[4][3].movepath = a[4][4].movepath = a[4][5].movepath = a[5][5].movepath = 0;
	a[3][1].move = a[3][1].movepath = 0;
	a[4][1].move = a[4][1].movepath = 0;
	a[2][4].move = a[2][4].movepath = 0;
	a[2][5].move = a[2][5].movepath = 0;
	a[4][5].move = a[4][5].movepath = 1;
	for (int n = 0; n <= 6; n++)
	{
		for (int m = 0; m <= 6; m++)
		{
			cout << a[n][m].move << "  ";
		}
		cout << endl;
	}
	stack b;
	bool rightseekload(palace a[7][7], stack &b, int &n, int &m);//右寻路
	bool downseekload(palace a[7][7], stack &b, int &n, int &m);//下寻路
	bool liftseekload(palace a[7][7], stack &b, int &n, int &m);//左寻路
	bool upseekload(palace a[7][7], stack &b, int &n, int &m);//上寻路
	int setrow; int setcol;
	setrow = setcol = 1;
	int end = 0;
	for (;;)
	{
		for (;;)
		{

			if (rightseekload(a, b, setrow, setcol) == false)
			{
				if (setrow == 5 && setcol == 5)
				{
					break;
				}
				if (downseekload(a, b, setrow, setcol) == false)
				{
					if (setrow == 5 && setcol == 5)
					{
						break;
					}
					if (liftseekload(a, b, setrow, setcol) == false)
					{
						if (setrow == 5 && setcol == 5)
						{
							break;
						}
						if (upseekload(a, b, setrow, setcol) == false)
						{
							if (setrow == 5 && setcol == 5)
							{
								break;
							}
							if (b.decline() == 0) { end = 1; break; }
							b.sendstack(setrow, setcol);
							//cout << setrow+1 << " " << setcol+1 << endl;  检验压入点的具体位置
							break;
						}
					}
				}
			}
		}
		if (end == 1) { cout << "该迷宫没有可达出口路径" << endl; break; }
		if (setrow == 5 && setcol == 5)
		{
			break;
		}
	}
	if (end != 1)
	{
		b.showout();
	}
	return 0;


}

bool rightseekload(palace a[7][7],stack &b, int &n, int &m)
{
	if (m + 1 > 6) return false;
	if (a[n][m + 1].movepath == 0) { b.pushin(n, m + 1); a[n][m + 1].movepath = 1; m++; return true; }
	else return false;
}

bool downseekload(palace a[7][7], stack &b, int &n, int &m)
{
	if (n + 1 > 6) return false;
	if (a[n + 1][m].movepath == 0) { b.pushin(n + 1, m); a[n + 1][m].movepath = 1; n++; return true; }
	else return false;
}
bool liftseekload(palace a[7][7], stack &b, int &n, int &m)
{
	if (m - 1 < 0) return false;
	if (a[n][m - 1].movepath == 0) { b.pushin(n, m - 1); a[n][m - 1].movepath = 1; m--; return true; }
	else return false;
}

bool upseekload(palace a[7][7], stack &b, int &n, int &m)
{
	if (n - 1 < 0) return false;
	if (a[n - 1][m].movepath == 0) { b.pushin(n - 1, m); a[n - 1][m].movepath = 1; n--; return true; }
	else return false;
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
