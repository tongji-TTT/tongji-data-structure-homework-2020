// 项目ten.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void UI()
{
	cout << "||" << "               " << "算法排序比较" << "                " << "||" << endl;
	cout << "||" << "--------------" << "--------------" << "---------------" << "||" << endl;
	cout << "||" << "               " << "选择您的操作" << "                " << "||" << endl;
	cout << "||" << "               " << "1--冒泡排序" << "                 " << "||" << endl;
	cout << "||" << "               " << "2--选择排序" << "                 " << "||" << endl;
	cout << "||" << "               " << "3--直接插入排序" << "             " << "||" << endl;
	cout << "||" << "               " << "4--希尔排序" << "                 " << "||" << endl;
	cout << "||" << "               " << "5--快速排序" << "                 " << "||" << endl;
	cout << "||" << "               " << "6--堆排序" << "                   " << "||" << endl;
	cout << "||" << "               " << "7--归并排序" << "                 " << "||" << endl;
	cout << "||" << "               " << "8--基数排序" << "                 " << "||" << endl;
	cout << "||" << "               " << "9--退出程序" << "                 " << "||" << endl;
	cout << "||" << "--------------" << "--------------" << "---------------" << "||" << endl;

}


int main()
{
	UI();
	int number;
	cout << "请输入所需要排序的个数" << endl;
	cin >> number;
	int *a = (int *)malloc(number * sizeof(int));
	int *p = (int *)malloc(number * sizeof(int));
	srand(time(NULL));
	for (int n = 0; n < number; n++)
	{
		a[n] = rand();
	}
	for (int n = 0; n < number; n++)
	{
		p[n] = a[n];
	}
	int change = 0; int time = 0; 
	void bubblesort(int *a, int &change, int &time, int number);//冒泡和选择
	void insertsort(int *a, int &change, int &time, int number);//直接插入
	void shellsort(int *a, int &change, int &time, int number);//希尔排序
	//快排
	int quickswap(int *a,int head,int end, int &change);
	int quickswap2(int *a, int head, int end, int &change);
	void quicksort(int *a, int &change, int &time, int number);
	//堆排序
	void adjustheap(int *&a,int &change,int number,int current);
	void heapsort(int *a, int &change, int &time, int number);
	//归并排序
    void merge(int *a,int *b, int &change, int head,int end,int middle);
	int  mergesort(int *a, int *b, int &change, int head, int end);
	void mergesort2(int *a, int *b, int &change, int &time, int head, int end);

	/*{
		int *b = (int *)malloc(number * sizeof(int));
		int head = 0;
		int end = number - 1;
		mergesort2(a, b, change, time, head, end);
	}*/
	//基数排序
	void bucket(int *&a,int&change,int loop,int number);
	void bucketsort(int *a, int &change, int &time, int number);
	int which = 0; int end = 0;
	for (;;)
	{
		cout << "请选择所需要的算法" << endl;
		cin >> which;
		change = 0; time = 0;
		for (int n = 0; n < number; n++)
		{
			a[n] = p[n];
		}

		switch (which)
		{
		case 1:
		{
			bubblesort(a, change, time, number);
			cout << "change" << change << endl;
			cout << "time" << time * 1000 << endl;
			break;
		}
		case 2:
		{
			bubblesort(a, change, time, number);
			cout << "change" << change << endl;
			cout << "time" << time * 1000 << endl;
			break;
		}
		case 3:
		{
			insertsort(a, change, time, number);
			cout << "change" << change << endl;
			cout << "time" << time * 1000 << endl;
			break;
		}
		case 4:
		{
			shellsort(a, change, time, number);
			cout << "change" << change << endl;
			cout << "time" << time * 1000 << endl;
			break;
		}
		case 5:
		{
			quicksort(a, change, time, number);
			cout << "change" << change << endl;
			cout << "time" << time * 1000 << endl;
			break;
		}
		case 6:
		{
			heapsort(a, change, time, number);
			cout << "change" << change << endl;
			cout << "time" << time * 1000 << endl;
			break;
		}
		case 7:
		{
			int *b = (int *)malloc(number * sizeof(int));
			int head = 0;
			int end = number - 1;
			mergesort2(a, b, change, time, head, end);
			cout << "change" << change << endl;
			cout << "time" << time * 1000 << endl;
			break;
		}
		case 8:
		{
			bucketsort(a, change, time, number);
			cout << "change" << change << endl;
			cout << "time" << time * 1000 << endl;
			break;
		}
		case 9: {end = 1; break; }
		default:
		{
			cout << "请输入正确的数字" << endl;
			break;
		}
		}
		cin.clear();
		cin.ignore(1024, '\n');
		if (end == 1) { break; }
	}

	return 0;
}

void bubblesort(int *a, int &change, int &time, int number)
{
	int timestart = clock();
	for (int n=0; n < number; n++)
	{
		for (int m=0; m < number-1-n; m++)
		{
			int temp;
			if (a[m] > a[m+1]) 
			{
				temp = a[m]; a[m] = a[m + 1]; a[m + 1] = temp;
				change++;
			}
		}
	}
	int timeend = clock();
	time = timeend - timestart;

}

void insertsort(int *a, int &change, int &time, int number)
{
	int timestart = clock();
	for (int n = 1; n < number; n++)
	{
		for (int m = 0; m < n; m++)
		{
			int temp;
			if (a[m] > a[n])
			{
				temp = a[n];
				for (int y = n - 1; y >= m; y--)
				{
					a[y + 1] = a[y];
					change++;
				}
				a[m] = temp;
			}
		}
	}
	int timeend = clock();
	time = timeend - timestart;
}

void shellsort(int *a, int &change, int &time, int number)
{
	int k = 1; int delta;
	for (;; k++)
	{

		if (number <= pow(2, k + 1) - 1 && number >= pow(2, k)-1) { break; }
	}

	int timestart = clock();
	for (; k >= 1; k--)
	{
		delta = pow(2, k) - 1;
		for (int i = 0; i < delta; i++)
		{
			for (int n = 0 + i; n < number; n = n + delta)
			{
				for (int m = 0 + i; m < number - delta - n; m = m + delta)
				{
					int temp;
					if (a[m] > a[m + delta])
					{
						temp = a[m]; a[m] = a[m + delta]; a[m + delta] = temp;
						change++;
					}
				}
			}
		}
	}
	int timeend = clock();
	time = timeend - timestart;

	/*for (int n = 0; n < number; n++)
	{
		cout << a[n] << " ";
	}*/
}
int quickswap(int *a, int head, int end, int &change)
{
	int x = head; int y = end;
	int k = a[head];
	while (x < y)
	{
		for (;x<y; y--)
		{
			if (k >= a[y]) { a[x] = a[y]; x++; change++; break; }
		}

		for (; x<y; x++)
		{

			if (a[x] > k) { a[y] = a[x]; y--; change++; break; }
		}
	}
	a[x] = k;
	return x;
}
int quickswap2(int *a, int head, int end, int &change)
{
	if (head<end)
	{

		int temp = quickswap(a, head, end,change);
		quickswap2(a, head, temp - 1,change);
		quickswap2(a, temp + 1, end,change);
	}
	else
	{
		return 0;
	}
}
void quicksort(int *a, int &change, int &time, int number)
{
	int head = 0; int end = number-1;
	int timestart = clock();
	quickswap2(a, head, end,change);
	int timeend = clock();
	time = timeend - timestart;	
}



void adjustheap(int *&a, int &change, int number, int current)//该点的顶大堆
{
	int temp = a[current];
	for (int n = 2 * current + 1; n < number; n = n * 2 + 1)
	{
		if (n + 1 < number&&a[n + 1] > a[n]) { n = n+ 1; }
		if (a[n] > temp)
		{
			a[current] = a[n];
			current = n; change++;
		}
		else { break; }
	}
	a[current] = temp;
}

void heapsort(int *a, int &change, int &time, int number)
{
	int max = number;
	//建立一个顶大堆
	int timestart = clock();
	for (int current = number / 2 - 1; current >= 0; current--)
	{
		adjustheap(a, change, number, current);
	}
	//从堆顶将最大的元素放到最后
	for (int n=0;n<number;)
	{
		int temp = a[number-1];
		a[number - 1] = a[0]; change++;
		a[0] = temp;
		number--;
		adjustheap(a, change, number, 0);
	}

	int timeend = clock();
	time = timeend - timestart;
}

void merge(int *a, int *b, int &change, int head, int end, int middle)
{
	int x = head; int y = middle + 1; int k = head;
	//比较排序
	while (x<middle+1&&y<end+1)
	{
		if (a[x] < a[y])
		{
			b[k] = a[x]; change++;
			k++; x++;
		}
		else 
		{
			b[k] = a[y]; change++;
			k++; y++;
		}
	}
	//剩余链接
	while (x != middle + 1)
	{
		b[k] = a[x]; change++;
		k++; x++;
	}
	while (y != end + 1)
	{
		b[k] = a[y]; change++;
		k++; y++;
	}
	//将整个链赋值回去
	for (int n = head; n <= end; n++)
	{
		a[n] = b[n];
	}
}

int mergesort(int *a, int *b, int &change, int head,int end)
{
	int middle;
	if (head < end)
	{
		middle = head + (end-head) / 2;
		mergesort(a, b, change, head, middle);
		mergesort(a, b, change, middle + 1, end);
		merge(a, b, change, head, end, middle);
		return 0;
	}
}
void  mergesort2(int *a, int *b, int &change, int &time, int head, int end)
{
	int timestart = clock();
	mergesort(a, b, change, head, end);
	int timeend = clock();
	time = timeend - timestart;
}

void bucket(int *&a, int&change, int loop,int number)
{
	int putin[10][10000] = {};
	int k = pow(10, loop - 1);
	int n, m; 
	for (n=0; n < number; n++)
	{
		int row = (a[n] / k) % 10;
		for (m=0; m < 10000; m++)
		{
			if (putin[row][m] == NULL)
			{
				change++;
				putin[row][m] = a[n]; break;
			}
		}
	}
	//放回去
	int temp = 0;
	for (n = 0; n < 10; n++)
	{
		for (m = 0; m < 10000; m++)
		{
			if (putin[n][m] == NULL)
			{
				break;
			}
			a[temp] = putin[n][m]; temp++; change++;
		}
	}
}
void bucketsort(int *a, int &change, int &time, int number)
{
	int max; int loop;
	max = 0; loop = 1;
	int timestart = clock();
	for (int n = 0; n < number; n++)
	{
		if (a[n] > max) { max = a[n]; }
	}
	for (;;)
	{
		max = max / 10;
		if (max > 0)
		{
			loop++;
		}
		else { break; }
	}
	for (int n=1;n<=loop;n++)
	{
		bucket(a, change,n,number);
	}

	int timeend = clock();
	time = timeend - timestart;
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
