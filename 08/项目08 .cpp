// 项目eight.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
using namespace std;

class matrix 
{
public:
	int cost;
	int path;
};

class checkarray 
{
public:
	int  putin;
	char name;
};
void UI()
{
	cout << "||" << "               " << "电网造价模拟系统" << "                " << "||" << endl;
	cout << "||" << "--------------" << "--------------" << "-------------------" << "||" << endl;
	cout << "||" << "               " << "选择您的操作" << "                    " << "||" << endl;
	cout << "||" << "               " << "A--添加顶点名称" << "                 " << "||" << endl;
	cout << "||" << "               " << "B--添加电网的边" << "                 " << "||" << endl;
	cout << "||" << "               " << "C--构造最小生成树" << "               " << "||" << endl;
	cout << "||" << "               " << "D--展现最小生成树" << "               " << "||" << endl;
	cout << "||" << "               " << "E--退出程序" << "                     " << "||" << endl;
	cout << "||" << "--------------" << "--------------" << "-------------------" << "||" << endl;

}

int main()
{
	UI();
	int number = 0;
	cout << "请输入顶点的个数" << endl;
	cin >> number;
	cin.clear();
	cin.ignore(1024,'\n');
	matrix **a = (matrix**)malloc(number * sizeof(matrix*));//动态开辟一个二维数组用于邻接矩阵的存放
	checkarray*b = (checkarray*)malloc(number * sizeof(checkarray));//动态开辟一个一维数组用于判断该点是否链接
	int *putin = (int *)malloc((2 * (number - 1)) * sizeof(int));//放入最小树的两端点
	int find(matrix**a, int row, int number);//返回该顶点所在的该行最小的未使用的边
	int min(int& stamp, int a, int b);//用于求一行最小的边
	for (;;)
	{
		int end = 0;
		char select;
		cout << "请选择您的操作" << "  ";
		cin >> select;

		switch (select)
		{
		case 'A':
		{
			for (int n = 0; n < number; n++)  //建立二维数组
			{
				a[n] = (matrix*)malloc(number * sizeof(matrix));
			}
			for (int n = 0; n < number; n++)    //初始化
			{
				for (int m = 0; m < number; m++)
				{
					a[n][m].cost = 0;
					a[n][m].path = 0;
				}
			}
			for (int n = 0; n < number; n++)  //将对角排除在外
			{
				a[n][n].cost = -1;
				a[n][n].path = -1;
			}

			for (int n = 0; n < number; n++)//初始化
			{
				b[n].putin = 0;
				b[n].name = '0';
			}

			char putinname;

			cout << "请输入要输入的顶点名称（请按照小写字母顺序）" << " " << endl;
			for (int n = 0; n < number; n++)  //开始输入顶点的个数
			{
				cin >> putinname;
				if (int(putinname) - 97 > number - 1) { cout << "输入的字母不符合字母表逻辑" << endl; break; }
				if (b[int(putinname) - 97].name != '0') { cout << "重复输入" << endl; break; }
				b[int(putinname) - 97].name = putinname;
			}
			break;
		}
		//

		case 'B':
		{
			int wrong = 0;
			char head, tail;
			int length = 0;

			cout << "请输入顶点之间的边的长度" << endl;
			for (;;)   //输入各个顶点之间的路径长度
			{
				cin >> head;
				cin >> tail;
				cin >> length;
				if (head == '?') { break; }
				if (int(head) - 97 > number - 1) { cout << "head wrong" << endl; wrong = 1; break; }
				if (int(tail) - 97 > number - 1) { cout << "tail wrong" << endl; wrong = 1; break; }
				if (a[int(head) - 97][int(tail) - 97].cost != 0) { cout << "有重复的边出现" << endl; wrong = 1; break; }
				a[int(head) - 97][int(tail) - 97].cost = length;
				a[int(tail) - 97][int(head) - 97].cost = length;
				b[int(head) - 97].putin = 1;
				b[int(tail) - 97].putin = 1;
			}
			//边界错误情况判断
			if (wrong == 1) { cout << "该步骤有错误，请重新进行该步骤" << endl; break; }
			for (int n = 0; n < number; n++)
			{
				if (b[n].putin == 0) { cout << "有节点没有链接上去" << endl; wrong = 1; break; }
			}
			if (wrong == 1) { cout << "该步骤有错误，请重新进行该步骤" << endl; break; }
			//将没有路径的顶点之间的路径封段
			for (int n = 0; n < number; n++)
			{
				for (int m = 0; m < number; m++)
				{
					if (a[n][m].cost == 0) { a[n][m].path = -1; }
				}
			}
			break;
		}
		case'C':
		{	
		cout << "请输入顶点的名称" << "  ";
		char first;
		cin >> first;
		if (int(first) < int(b[0].name) || int(first) > int(b[number - 1].name))
		{ cout << "输入的字符不在原先的顶点中" << endl; cout << "该步骤有错误，请重新进行该步骤" << endl; break; };
		int  row, col;
		row = int(first) - 97;
		int one = 0;
		int temp = 0;
		//搜索该确定行的最小的路径长度
		for (int m = 0; m < number - 1; m++)
		{
			int cost = 0; int stamp = 0;
			for (int n = 0; n < number; n++)
			{
				if (a[row][n].path == 0)
				{
					cost = min(stamp, cost, a[row][n].cost);
					if (stamp == 1)
					{
						stamp = 0;
						col = n;
					}
				}
			}
			a[row][col].path = 1;
			a[col][row].path = 1;
			putin[one] = row;
			//cout << putin[one] << endl;
			one++;
			putin[one] = col;
			//cout << putin[one] << endl;
			one++;
			col = 0;
			temp = 0;
		//确定下一行从哪一行进行寻找
			for (int n = 0; n < one - 1; n++)
			{
				int x, y; x = y = 0;
				x = find(a, putin[n], number);// cout << "x"<<x << endl;
				y = find(a, putin[n + 1], number);// cout << "y" << y <<endl;
				if (x == 0)
				{
					if (temp > y || temp == 0)
					{
						temp = y; row = putin[n + 1];
					}
				}
				else
				{
					if (x < y)
					{
						if (temp > y || temp == 0)
						{

							temp = x; row = putin[n];
						}
					}
					else
					{
						if (temp > y || temp == 0)
						{
							temp = y; row = putin[n + 1];
						}
					}
				}
			}
			if (temp == 0) { cout << "wrong" << endl; break; }
		}
		
			break;
		}

		case'D':
		{
			cout << "最小生成树的顶点和边如下" << endl;
			for (int n = 0; n < 2 * (number - 1) - 1;)
			{
				cout << char(putin[n] + 97) << " ";
				cout << a[putin[n]][putin[n + 1]].cost << " ";
				cout << char(putin[n + 1] + 97) << "         ";
				n = n + 2;
			}
			break;
		}
		case 'E':
		{   end = 1;
			break;
		}
		default: {cout << "请输入正确的字符" << endl; break; }
		}
		if (end == 1) { break; }
	}



	return 0;
}



int min(int & stamp, int a, int b)
{
	if (a <= 0) { stamp = 1; return b; }
	if (a > b) { stamp = 1; return b; }
	else { return a; }
}
int find(matrix**a, int row, int number)
{
	int cost = 0; int stamp = 0; int col = -1;
	for (int n = 0; n < number; n++)
	{
		if (a[row][n].path == 0)
		{
			cost = min(stamp, cost, a[row][n].cost);
			if (stamp == 1)
			{
				stamp = 0;
				col = n;
			}
		}
	}
	if (col != -1)
	{

		return a[row][col].cost;
	}
	else
	{
		return 0;
	}
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
