

#include <iostream>
using namespace std;
template<class T>
class date
{
public:
	T number;
	date* link;
};

template <class T>
class list 
{
private:
	date<T>* head;
	date<T>* current;
	int nowsetnumber = 0;
public:
	list(int a);
	list();
	void output();
	void relist();
	template<class T>
	friend bool change(list<T> &a, list<T> &b, list<T> &c);
};
template<class T>
list<T>::list(int a)
{
	head = new date<T>;
	if (head == NULL) { cout << "头指针分配失败" << endl; }
	current = new date<T>;
	current->number = a;
	head->link = current;
	current->link = NULL;
	nowsetnumber++;
}

template<class T>
list<T>::list()
{
	head = new date<T>;
	if (head == NULL) { cout << "头指针分配失败" << endl; }
	for (int n=1;;n++)
	{
		T input;
		cin >> input;
		if (input < -1) { cout << "输入了非负1以外的负数,请重试" << endl; n--; continue; }
		if (n == 1)
			
		{
			nowsetnumber++;
			current = new date<T>;
			current->number = input;
			head->link = current;
			current->link = NULL;
			if (current->number == -1) { break; }
		}
		else
		{
			nowsetnumber++;
			current->link = new date<T>;
			current = current->link;
			current->number = input;
			current->link = NULL;
			if (current->number == -1) { break; }

		}
	}
}

template <class T>
void list<T>::output()
{
	current = head->link;
	if (current->number == -1) { cout << "NULL" << endl; }
	else
	{

		for (int n = 1; n <= nowsetnumber - 1; n++)
		{
			cout << current->number << endl;
			current = current->link;
		}
	}
}

template<class T>
void list<T>::relist()
{
	current = head->link;
	for (int n = 1; n <= nowsetnumber-2; n++)
	{
		current = head->link;
		for (int m = n; m <= nowsetnumber-2; m++)
		{
			if (current->number > current->link->number)
			{
				T a;
				a = current->number;
				current->number = current->link->number;
				current->link->number = a;
				current = current->link;
			}
			else
			{ current = current->link; }
		}	
	}
}
template<class T>
bool change(list<T>&a, list<T>&b, list<T>&c)
{
	a.current = a.head->link;
	b.current = b.head->link;
	if (a.nowsetnumber <= 1 || b.nowsetnumber <= 1)
	{
		return false;
	}
	else
	{
		for (;;)
		{
			if (a.current->number == -1 || b.current->number == -1) { break; }
			if (a.current->number < b.current->number)
			{
				a.current = a.current->link;
			}
			else 
			{
				if (a.current->number >b.current->number)
				{
					b.current = b.current->link;
				}
				else 
				{
					c.current->number = a.current->number;
					c.current->link = new date<T>;
					c.current = c.current->link;
					c.current->number = -1;
					c.current->link = NULL;
					c.nowsetnumber++;
					a.current = a.current->link;
					b.current = b.current->link;
				}
			}
		}
		return true;
	}
}
int main()
{
	list<int> a;
	a.relist();
	list<int> b;
	b.relist();
	list<int> c(-1);
	change(a, b, c);
	c.output();
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
