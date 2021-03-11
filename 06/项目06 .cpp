// 项目six.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdio.h>
#include<string>
#include<sstream>
using namespace std;

class family
{
private:
	string name;
	int sonnumber;
public:
	family*link;
	family*son;
	family*brother;
	int add(family *&p1, int &number);  //添加子女函数
	int remove(string namestring);  //删除一个成员函数
	int refamily();//解散家庭函数
	int find(family * &head, int &a, string b, family *&p1);  //寻找一个成员函数
	int putin(int &a); //添加函数子函数
	void show();//显示名字
	void showson();//显示所有子女的名字
	void changename(string b);//改变该成员的姓名
	family(string b,family a);
	family(string b);
	family() { son = NULL; brother = NULL; sonnumber = 0; }
};

family::family(string b)
{
	name = b;
	son = NULL; brother = NULL; sonnumber = 0;
}
family::family(string b, family a)
{
	family * head;
	head = new family;
	family * current;
	int stacknumber = 0;
	if (a.find(head, stacknumber, b, current) == 1)
	{
	}
	name = b;
	son = NULL; brother = NULL; sonnumber = 0;
}
void family::show()
{
	cout << name << "  " << sonnumber << endl;
}
void family::changename(string b)
{
	name = b;
}
void family::showson()
{
	if (son == NULL) { cout << "该成员没有子女" << endl; }
	else
	{
		cout << son->name << " ";
		if (son->brother != NULL)
		{
			family*p1;
			p1 = son;
			for (;;)
			{
				cout << p1->brother->name << " ";
				if (p1->brother->brother == NULL) { break; }
				p1 = p1->brother;
			}

		}
	}
	cout << sonnumber << endl;
}

int family::putin(int &a)   //多输入，少输入判断！
{
	sonnumber = a;
	if (a >= 1)
	{

		string namestring1;
		getline(cin, namestring1);  //getline用于读入带有空格的字符串
		istringstream is(namestring1); //istringsteam 用于分隔空格
		is >> namestring1;
		son = new family(namestring1);
		family * p1;
		p1 = son;
		for (int m = 1; m < a; m++)
		{
			is >> namestring1;
			p1->brother = new family(namestring1);
			p1 = p1->brother;
		}
	}
	if (a < 0)
	{
		cout << "输入子女个数小于1 " << endl;
	}
	return 0;
}

int family::find(family * &head, int &a, string b, family* &p1)  //通过成员的名字来寻找
{
	if (name == b) { p1 = this; return 1; }
	else
	{
		if (son == NULL && brother == NULL)
		{
			if (a != 0)
			{
				head = head->link;
				if (head->find(head, a, b, p1) == 1) { return 1; };

			}
			else { return 0; }
		}

		if (son != NULL && brother == NULL)
		{
			if (son->find(head, a, b, p1) == 1) { return 1; }
		}
		if (son == NULL && brother != NULL)
		{
			if (brother->find(head, a, b, p1) == 1) { return 1; }
		}
		if (son != NULL && brother != NULL)
		{
			a++;
			brother->link = head->link;//栈添加
			head->link = brother;
			if (son->find(head, a, b, p1) == 1) { return 1; }
		}
	}
}


int family::add(family *&p1, int &number)
{
	if (p1->son == NULL)
	{
		p1->putin(number);
	}
	else
	{
		family* p2;
		p2 = p1->son;
		for (;;)
		{
			if (p2->brother == NULL) { break; }
			p2 = p2->brother;
		}
		string namestring;
		getline(cin, namestring);
		istringstream is(namestring);
		for (int m = 0; m < number; m++)
		{
			is >> namestring;
			p2->brother = new family(namestring);
			p2 = p2->brother;
		}
	}
	return 1;

}

int family::refamily()
{
	cout << "该成员的子女如下" << endl;
	showson();
	son = NULL; sonnumber = 0;
	cout << "现成员子女如下" << endl;
	showson();
	return 0;
}
int family::remove(string namestring)
{
	if (sonnumber >= 1)
	{
		family * p1, *p2;
		p1 = son;
		p2 = son;
		for (int n = 0; n < sonnumber; n++)
		{
			if (p1->name == namestring) { break; }
			p2 = p1;
			p1 = p1->brother;
		}
		if (p1 == NULL) { return 0; }
		else
		{
			if (p1 == son && p1->brother == NULL) { son = NULL; sonnumber--; return 1; }
			if (p1 == son && p1->brother != NULL) { son = son->brother; sonnumber--; return 1; }
			if (p1 != son && p1->brother == NULL) { p2->brother = NULL; sonnumber--; return 1; }
			if (p1 != son && p1->brother != NULL) { p2->brother = p1->brother; sonnumber--; delete p1; return 1; }
		}
	}
	else
	{
		return 0;
	}
}
void UI()
{
	cout << "||" << "               " << "家谱管理系统" << "               " << "||" << endl;
	cout << "||" << "--------------" << "--------------" << "--------------" << "||" << endl;
	cout << "||" << "               " << "选择您的操作" << "               " << "||" << endl;
	cout << "||" << "               " << "A--添加子女" << "                " << "||" << endl;
	cout << "||" << "               " << "B--查找姓名" << "                " << "||" << endl;
	cout << "||" << "               " << "C--修改姓名" << "                " << "||" << endl;
	cout << "||" << "               " << "D--解散子女" << "                " << "||" << endl;
	cout << "||" << "               " << "E--删除子女" << "                " << "||" << endl;
	cout << "||" << "               " << "F--退出程序" << "                " << "||" << endl;
	cout << "||" << "--------------" << "--------------" << "--------------" << "||" << endl;

}
int main()
{
	int familynumber = 0;
	string namestring;
	char kind;
	int end = 0;
	int stacknumber = 0;
	family * head;
	head = new family;
	family * current;
	family * ancester;
	UI();
	cout << "首先建立一个家谱" << endl;
	cout << "请输入家谱祖先的姓名" << endl;
	getline(cin, namestring);
	family root(namestring);
	cout << "请输入家谱祖先的子女个数" << endl;
	cin >> familynumber;
	cin.ignore();
	cout << "请输入家谱祖先的子女姓名" << endl;
	root.putin(familynumber);
	ancester = &root;
	for (;;)
	{
		cout << "请选择您的操作" << endl;
		cin >> kind;
		cin.ignore();
		switch (kind)
		{
		case 'A':
		{
			cout << "输入需要增加子女的成员姓名" << endl;
			getline(cin, namestring);
			if (root.find(head, stacknumber, namestring, current) == 1)
			{
				cout << "该点的子女如下" << endl;
				current->showson();
				cout << "请输入要加入的子女个数" << endl;
				int childnumber = 0; cin >> childnumber; cin.ignore();
				cout << "请输入要加入的子女姓名" << endl;
				if (current->add(current, childnumber) == 1)
				{
					cout << "该点的子女修改后如下" << endl;
					current->showson();
				}
			}
			else
			{
				cout << "家谱中该成员不存在" << endl;
			}
			break;
		}
		case 'B':
		{
			cout << "输入需要查找的成员名" << endl;
			getline(cin, namestring);
			if (root.find(head, stacknumber, namestring, current) == 1)
			{
				cout << "该成员存在" << endl;
				cout << "该成员的子女为" << " ";
				current->showson();
			}
			else
			{
				cout << "家谱中该成员不存在" << endl;
			}
			break;
		}
		case 'C':
		{
			cout << "输入需要修改名字的成员名" << endl;
			getline(cin, namestring);
			if (root.find(head, stacknumber, namestring, current) == 1)
			{
				cout << "输入修改后的名字" << endl;
				getline(cin, namestring);
				current->changename(namestring);
			}
			else
			{
				cout << "家谱中该成员不存在" << endl;
			}
			break;
		}
		case 'D':
		{
			cout << "输入需要解散子女的成员名" << endl;
			getline(cin, namestring);
			if (root.find(head, stacknumber, namestring, current) == 1)
			{
				current->refamily();
			}
			else
			{
				cout << "家谱中该成员不存在" << endl;
			}
			break;
		}
		case 'E':
		{
			cout << "输入需要删去子女的双亲名" << endl;
			getline(cin, namestring);
			if (root.find(head, stacknumber, namestring, current) == 1)
			{
				cout << "该成员的子女有如下" << endl;
				current->showson();
				cout << "输入需要删去的子女名字" << endl;
				getline(cin, namestring);
				if (current->remove(namestring) == 1)
				{
					cout<<"该点的子女修改后如下"<<endl;
					current->showson();
				}
				else
				{
					cout << "该成员中无该子女" << endl;
				}

			}
			else
			{
				cout << "家谱中该成员不存在" << endl;
			}
			break;
		}
		case 'F': {end = 1; break; }
		default: {cout << "无效字符请重新输入" << endl; break; }
		}
		if (end == 1) { break; }
	}
	/*int n = 0;
	string namestring;
	getline(cin, namestring);
	family root(namestring);
	root.putin(3);



	family * head;
	head = new family;
	int a = 0;
	family * p1;
	getline(cin, namestring);
	int number = 0;
	cin >> number;
	cin.ignore();//清除前方的回车
	root.add(head,a,namestring,p1, number);
	getline(cin, namestring);
	a = 0;
	if (root.find(head, a, namestring, p1) == 1)
	{
		p1->show();
	}
	else
	{
		cout << "wu"<< endl;
	}*/

	return 0;
}

