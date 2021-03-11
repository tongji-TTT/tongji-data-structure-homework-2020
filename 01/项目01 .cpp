
#include <iostream>
#include<cstring>
using namespace std;
struct date
{
public:
	int number;
	char name[20];
	char gender[20];
	int age;
	char job[20];
	 date*link;
};
class list
{
private:             //头指针，动指针，新指针
	date* head;     //动-新；动=新；
	date* end;
	date* current;
	date* temp;
	int firstsetnumber;
	int nowsetnumber;
public:
	list(int n,int *m);
	bool input();//输入函数
	bool output();//输出函数
	void relist();//按学号重排列函数
	bool insert(int n);//插入到n位函数
	bool remove(int n);//删去n位函数
	bool seek(int n);//寻找学号为n的函数
	bool change(int n);//修改学号为n的函数
	void check();//判断是否有重复学号出现

};
list::list(int n,int *m)
{
	if (n < 1) { cout << "请输入正整数" << endl; *m =0; }
	else
	{
		firstsetnumber = n;
		nowsetnumber = n;
		head = new date;
		if (head == NULL)
		{
			cout << "头指针内存分配失败";
		}
	}
}
bool list::input()
{
	if (nowsetnumber >= 1)
	{
		current = new date;
		cin >> current->number;
		cin >> current->name;
		cin >> current->gender;
		cin >> current->age;
		cin >> current->job;
		head->link = current;
		for (int n = 2; n <= nowsetnumber; n++)
		{
			temp = new date;
			cin >> temp->number;
			cin >> temp->name;
			cin >> temp->gender;
			cin >> temp->age;
			cin >> temp->job;
			current->link = temp;
			current = temp;
			if (n == nowsetnumber) { current->link = NULL; end = current; current = head->link; }
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool list::output()
{
	current = head->link;
	if (nowsetnumber >= 1)
	{

		for (int n = 1; n <= nowsetnumber; n++)
		{

			cout << current->number;
			cout << "     ";
			cout << current->name;
			cout << "     ";
		    cout << current->gender;
			cout << "     ";
			cout << current->age;
			cout << "     ";
			cout << current->job;
			cout << endl;
			if (current->link != NULL) { current = current->link; }
			else { return true; }

		}
		return true;
	}
	else
	{
		return false;
	}
}

void list::relist()
{
	if (nowsetnumber < 1) { cout << "人数少于1，错误" << endl; }
	else
	{
		for (int m = 1; m < nowsetnumber; m++)
		{
			current = head->link;
			for (int n = m; n < nowsetnumber; n++)
			{
				if (current->number > current->link->number)
				{

					temp = new date;
					temp->number = current->link->number;
					current->link->number = current->number;
					current->number = temp->number;

					strcpy(temp->name, current->link->name);
					strcpy(current->link->name, current->name);
					strcpy(current->name, temp->name);

					strcpy(temp->gender, current->link->gender);
					strcpy(current->link->gender, current->gender);
					strcpy(current->gender, temp->gender);

					temp->age = current->link->age;
					current->link->age = current->age;
					current->age = temp->age;

					strcpy(temp->job, current->link->job);
					strcpy(current->link->job, current->job);
					strcpy(current->job, temp->job);

					delete temp;

					current = current->link;

				}
				else { current = current->link; }
			}

		}
	}
}
bool list::insert(int n)
{
	current = head;
	temp = new date;
	if (temp == NULL) { cout << "插入时，空间不足" << endl; return false; }
	cin >> temp->number;
	cin >> temp->name;
	cin >> temp->gender;
	cin >> temp->age;
	cin >> temp->job;
	nowsetnumber++;
	if (n > nowsetnumber) { cout << "插入空间有空隙" << endl; return false; }
	if (n <= 0) { cout << "插入位置小于1" << endl; return false; }
	for (int m = 0; m <= n - 1; m++)
	{
		if (m == n - 1) 
		{
			temp->link = current->link;
			current->link = temp;
			if (temp->link == NULL) { end = temp; }
		}
		else
		{current = current->link;}

	}

	return true;
}

bool list::remove(int n)
{
	int location=0;
	current = head;
	temp = new date;
	if (temp == NULL) { cout << "删除时，空间不足" << endl; return false; }
	for (int m = 1; m <= nowsetnumber; m++)
	{
		if (current->link == NULL) { break; }
		if (current->link->number != n) { current = current->link; }
		else
		{   
			location = m; 
			temp = current->link;
			current->link = temp->link;
			cout << "您要删除的信息是" << endl;
		    cout << temp->number;
			cout << "     ";
			cout << temp->name;
			cout << "     ";
			cout << temp->gender;
			cout << "     ";
			cout << temp->age;
			cout << "     ";
			cout << temp->job;
			cout<< endl;
			delete temp; nowsetnumber--;
			if (current->link == NULL) { end = current; }
			break;
		}
	}
	//location代表位置，current指向前一个
	if (location == 0)
	{
		cout << "未找到合适学号" << endl; return false;
	}
	return true;
}
bool list::seek(int n) 
{

	current = head->link;
	for (int m = 1; m <= nowsetnumber; m++)
	{
		if (current->number == n) 
		{
			cout << "输出学生";
		cout << current->number;
		cout << "     ";
		cout << current->name;
		cout << "     ";
		cout << current->gender;
		cout << "     ";
		cout << current->age;
		cout << "     ";
		cout << current->job;
		cout << endl;
		return true;
		}
		else { current = current->link; }
	}


	return false;
}
bool list::change(int n)
{

	current = head->link;
	for (int m = 1; m <= nowsetnumber; m++)
	{
		if (current->number == n) 
		{
		int a; cin >> a; current->number = a;
		char b[20]; cin >> b; strcpy(current->name,b);
		char c[20]; cin >> c; strcpy(current->gender, c);
		int d; cin >> d; current->age = d;
		char e[20]; cin >> e; strcpy(current->job, e);
		return true;
		}
		else { current = current->link; }
	}


	return false;
}
void list::check()
{
	current = head->link;
	for (int m = 1; m < nowsetnumber; m++)
	{
		if (current->number == current->link->number)
		{
			cout << "如下数据学号重合请修改" << endl;
			cout << current->number;
			cout << "     ";
			cout << current->name;
			cout << "     ";
			cout << current->gender;
			cout << "     ";
			cout << current->age;
			cout << "     ";
			cout << current->job;
			cout << endl;

			cout << current->link->number;
			cout << "     ";
			cout << current->link->name;
			cout << "     ";
			cout << current->link->gender;
			cout << "     ";
			cout << current->link->age;
			cout << "     ";
			cout << current->link->job;
			cout << endl;
			break;
		}
		else { current = current->link; }
	}
}

void choice(int n,list &a)
{
	switch (n)
	{
	case 1:
	{   
		int m;
		cout << "请选择插入位置" << endl;
		cin >> m;
		cout << "请依次输入考号，姓名，性别，年龄，报考类型" << endl;
		a.insert(m);
		cout << "考号" << "     " << "姓名" << "     " << "性别" << "     " << "年龄" << "     " << "报考类型" << "     " << endl;
		a.output();
		break;
	}
	case 2:
	{
		int m;
		cout << "请选择删除考号" << endl;
		cin >> m;
		a.remove(m);
		cout << "考号" << "     " << "姓名" << "     " << "性别" << "     " << "年龄" << "     " << "报考类型" << "     " << endl;
		a.output();
		break;
	}
	case 3:
	{
		int m;
		cout << "请选择要查找的考号" << endl;
		cin >> m;
		int b;
		b = a.seek(m);
		if (b == 0)
		{
			cout << "表中无该考生数据" << endl;
		}
		break;
	}
	case 4:
	{
		int m;
		cout << "请选择修改的考号" << endl;
		cin >> m;
		cout << "请依次输入考号，姓名，性别，年龄，报考类型" << endl;
		int b;
		b=a.change(m);
		if (b == 1)
		{

			cout << "考号" << "     " << "姓名" << "     " << "性别" << "     " << "年龄" << "     " << "报考类型" << "     " << endl;
			a.output();
		}
		else 
		{
			cout << "表中无该考生数据" << endl;
		}
		break;
	}
	case 5:
	{
		a.relist();
		a.output();
		a.check();
		break;
	}
	case 0:
	{   
		break;
	
	}
	}
}
int main()
{
	int check = 1;
	cout << "首先建立考试系统" << endl;
	cout << "输入初始人数" << endl;
	int k;
	cin >> k;
	list a(k, &check);
	if (check == 1)
	{
		cout << "请依次输入考号，姓名，性别，年龄，报考类型" << endl;
		a.input();
		a.output();
		for (;;)
		{
			int n;
			cout << "选择您的操作（1.插入，2.删去，3.查找，4.修改，5.排序，0.取消操作,-1.结束程序）" << endl;
			cin >> n;
			if (n >= 0 && n <= 5)
			{
				choice(n, a);
			}
			else
			{
				if (n == -1) { break; }
				else { cout << "无效的操作数" << endl; }
			}
		}
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
