
#include <iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<iomanip>
using namespace  std;
class date //记录先驱点所连接的所有后继点
{
public:
	date * link;
	string classnumber;
	string classname;
	int put;
	date() { link = NULL; put = 0; }
};

class lesson //记录所有的课程的信息
{
public:
	string classnumber; //课程编号
	string classname; //课程名
	int hours; //一周的课时
	int term;  //开课的时期
	string beforeclass1; //需要所学的课程1
	string beforeclass2;  //需要所学的课程2
	string beforeclass3;  //需要所学的课程3
	int used; //是否被先使用过
	int out; //重要程度（越是越多的课程的先驱课程，重要性越高）
	int must; //必须程度（若是有学期规定的课程的先行课，其先行课就拥有必须性）
	int putintable;//有没有进入可选课表中
	date * link;//链接date类
	lesson * tablelink;//链接自己类，用于构建可选课表
};
int main()
{
	int totalnumber = 0;//课表中的课程总数
	int a[8];//各个学期的课程数
	int end = 0;//错误中止的记录符
	cout << "请输入需要排课的总数" << endl;
	cin >> totalnumber;
	cin.clear();
	cin.ignore(1024, '\n');
	cout << "学期的课程数" << endl;
	cout << "所输入的各个学期课程数总和需要等于课表的总和" << endl;
	cout<<"且学期课程数要大于等于3小于等于8"<<endl;
	for (int n = 0; n < 8; n++)
	{
		cin >> a[n]; if (a[n] > 8 || a[n] < 3) { cout << "输入的学期课程不符合规定" << endl; return 2; }

	}
	cin.clear();
	cin.ignore(1024, '\n');
	
	int total = 0;
	for (int n = 0; n < 8; n++)
	{
		total = total + a[n];
	}
	if (total != totalnumber) { cout << "输入的学期课程之和与排课总数有错误" << endl; return 1; }
	

	lesson *totalclass = new lesson[totalnumber];
	for (int n = 0; n < totalnumber; n++)//初始化总课表单
	{
		totalclass[n].classnumber = '-1';
		totalclass[n].classname = '-1';
		totalclass[n].beforeclass1 = '-1';
		totalclass[n].beforeclass2 = '-1';
		totalclass[n].beforeclass3 = '-1';
		totalclass[n].hours = totalclass[n].term = totalclass[n].used = totalclass[n].out = totalclass[n].must= totalclass[n].putintable = -1;
		totalclass[n].link = NULL;
		totalclass[n].tablelink = NULL;
	}
	//打开文本输入阶段
	fstream infile;
	infile.open("1.txt");
	fstream infile2;
	infile2.open("2.txt", ios::out);//清除2.txt中的文字
	infile2.close();
	if (infile.is_open() != 1)
	{
		cout << "文件没有成功打开" << endl;
	}
	else 
	{
		for (int n = 0; n < totalnumber; n++)
		{
			infile >> totalclass[n].classnumber;
			infile >> totalclass[n].classname;
			infile >> totalclass[n].hours;
			infile >> totalclass[n].term;
			infile >> totalclass[n].beforeclass1;
			infile >> totalclass[n].beforeclass2;
			infile >> totalclass[n].beforeclass3;
		}
	}
	int * count = new int[totalnumber];

	for (int n = 0; n < totalnumber; n++)//辅助数组标志该n点是否可以开始学习该课程
	{
		count[n] = 0;
	}
	// 开始构建拓扑排序的链表
	for (int n = 0; n < totalnumber; n++)  //改变辅助数组和每个totalclass的date域链接
	{
		if (totalclass[n].beforeclass1 != "-1")
		{
			for (int m = 0; m < totalnumber; m++)
			{
				if (totalclass[m].classnumber == totalclass[n].beforeclass1)
				{
					count[n]++;
					date *p = new date;
					p->classnumber = totalclass[n].classnumber;
					p->link = NULL;
					if (totalclass[m].link == NULL) 
					{
						totalclass[m].link = p;
					}
					else
					{
						date* head;
						head = totalclass[m].link;
						for (;;)
						{
							if (head->link == NULL) { break; }
							head = head->link;
						}
						head->link = p;
					}
					totalclass[m].out++;
					if (totalclass[n].term != 0) { totalclass[m].must++; }
					break;
				}
			}
		}

		if (totalclass[n].beforeclass2 != "-1")
		{
			for (int m = 0; m < totalnumber; m++)
			{
				if (totalclass[m].classnumber == totalclass[n].beforeclass2)
				{
					count[n]++;
					date *p = new date;
					p->classnumber = totalclass[n].classnumber;
					p->link = NULL;
					if (totalclass[m].link == NULL)
					{
						totalclass[m].link = p;
					}
					else
					{
						date* head;
						head = totalclass[m].link;
						for (;;)
						{
							if (head->link == NULL) { break; }
							head = head->link;
						}
						head->link = p;
					}
					totalclass[m].out++;
					if (totalclass[n].term != 0) { totalclass[m].must++; }
					break;
				}
			}
		}

		if (totalclass[n].beforeclass3 != "-1")
		{
			for (int m = 0; m < totalnumber; m++)
			{
				if (totalclass[m].classnumber == totalclass[n].beforeclass3)
				{
					count[n]++;
					date *p = new date;
					p->classnumber = totalclass[n].classnumber;
					p->link = NULL;
					if (totalclass[m].link == NULL)
					{
						totalclass[m].link = p;
					}
					else
					{
						date* head;
						head = totalclass[m].link;
						for (;;)
						{
							if (head->link == NULL) { break; }
							head = head->link;
						}
						head->link = p;
					}
					totalclass[m].out++;
					if (totalclass[n].term != 0) { totalclass[m].must++; }
					break;
				}
			}
		}
	}
	
	cout << "下面是总体课表的辅助数组值 编号 重要度" << endl;
	for (int n = 0; n < totalnumber; n++)
	{
		cout << count[n] << " " << totalclass[n].classnumber << " " << totalclass[n].out << "  ";
		cout << endl;
	}
	cout << endl;
    //开始构建一个链表用于存放可以优先输出的课程
    lesson * tablehead = new lesson;
	tablehead->tablelink=NULL;
    int tablenumber = 0;
	void putin(lesson *&tablehead,lesson*a, int &tablenumber);//放入函数，按out从大到小进行排序
	int putout(lesson *&tablehead, int time,int&tablenumber ,lesson *&outlink);//开始构建一个判断输出函数（used，must，out）
	void classtablesetup(lesson* head, int number);//开始构建一个排课到周一到周五的程序
	lesson *head1, *head2;
	head1 = new lesson;
	head2 = head1;
	int number1 = 0;
	//8个学期的排课
	for (int k = 0; k < 8; k++)
	{
		head1 = head2;
		number1 = 0;
		int howmanyclass;
		int time;
		time = k+1;
		howmanyclass = a[k];
		for (int n = 0; n < totalnumber; n++)
		{
			if (count[n] == 0 && totalclass[n].used == -1&&totalclass[n].putintable==-1) { putin(tablehead, &totalclass[n], tablenumber); }  //放入到可选表中
		}
		cout << "该学期中的可选课程" << endl;
		lesson*p2 = tablehead;
	/*	for (int n = 0; n < tablenumber; n++)
		{
			cout << tablehead->tablelink->classnumber << " " << tablehead->tablelink->out << " " << tablehead->tablelink->term << " " << endl;
			tablehead = tablehead->tablelink;
		}
		*/
		tablehead = p2;
		ofstream outfile;
		outfile.open("2.txt", ios::app);
		outfile << setw(32) << setiosflags(ios::right) << setfill(' ') << "该学期" << k + 1 << "选课为" << endl;
		outfile << setw(32) << setiosflags(ios::right) << setfill(' ') << "---------------------------------------------------------------------------------------------------------------------------------------" << endl;
		outfile.close();
		cout << "该学期"<<k+1<<"选课为" << endl;
		for (int n = 0; n < howmanyclass; howmanyclass--)//排出该学期的课程
		{
			if (howmanyclass > tablenumber) { cout << "wrong" << endl; end = 1; break; }
			lesson* p1;
			if (putout(tablehead, time, tablenumber, p1) == 0) { cout << "too large" << endl; end = 1; break; }
			cout << p1->classnumber << " " << p1->classname << " ";
			head1->tablelink = p1;
			head1 = head1->tablelink; number1++;
			//对其链接的其他点进行辅助数组的的值的减小
			if (p1->link != NULL)
			{
				date * p;
				p = p1->link;
				for (;;)
				{
					if (p == NULL) { break; }
					for (int n = 0; n < totalnumber; n++)
					{
						if (p->classnumber == totalclass[n].classnumber)
						{
							count[n]--; break;
						}
					}
					p = p->link;
				}
			}
		}
		cout << endl;
		if (end == 1) { break; }
		head1 = head2;
		classtablesetup(head1, number1);
	}

	return 0;
}

void putin(lesson *&tablehead, lesson*a, int &tablenumber)
{
	lesson * q = a; q->putintable = 0;
	if (tablehead->tablelink == NULL) { tablehead->tablelink = q; tablenumber++; }
	else
	{
		if (tablenumber == 1)
		{
			if (tablehead->tablelink->out > q->out)
			{
				tablehead->tablelink->tablelink = q; 
			}
			else
			{
				q->tablelink = tablehead->tablelink;
				tablehead->tablelink = q; 
			}
			tablenumber++;
		}
		//
		else
		{
			lesson * b = tablehead;
			for (int n = 0; n < tablenumber - 1; n++)
			{
				if (q->out > b->tablelink->out) { q->tablelink = b->tablelink; b->tablelink = q; tablenumber++; break; }
				if (b->tablelink->out >= q->out && b->tablelink->tablelink->out <= q->out)
				{
					q->tablelink = b->tablelink->tablelink;
					b->tablelink->tablelink = q; tablenumber++;  break;
				}
				if (n == tablenumber - 2 && q->out < b->tablelink->tablelink->out)
				{

					b->tablelink->tablelink->tablelink = q; tablenumber++;  break;
				}
				b = b->tablelink;
			}
		}
	}
}

int putout(lesson *&tablehead, int time, int&tablenumber,  lesson *&outlink)//先进行学期判断，再进行must判断，最后按out的大小顺序进行输出
{
	lesson * b = tablehead;
	for (int n = 0; n < tablenumber; n++)
	{
		if (b->tablelink->term == time)
		{
			outlink = b->tablelink;
			outlink->used = 1;
			b->tablelink = b->tablelink->tablelink;
			outlink->tablelink = NULL;
			tablenumber--; return 1;
		}
		else { b = b->tablelink;  }
	}

    b = tablehead;
	for (int n = 0; n < tablenumber; n++)
	{
		if (b->tablelink->must != -1 )
		{
			outlink = b->tablelink;
			outlink->used = 1;
			b->tablelink = b->tablelink->tablelink;
			outlink->tablelink = NULL;
			tablenumber--; return 2;
		}
		else { b = b->tablelink; }
	}

	b = tablehead;
	for (int n = 0; n < tablenumber ; n++)
	{
		if (b->tablelink->term == 0)
		{
			outlink = b->tablelink;
			outlink->used = 1;
			b->tablelink = b->tablelink->tablelink;
			outlink->tablelink = NULL;
			tablenumber--; return 3;
		}
		else { b = b->tablelink; }
	}
	return 0;
}

void classtablesetup(lesson* head,int number)
{
	ofstream outfile;
	outfile.open("2.txt",ios::app);
	int remainder, result;
	remainder = result = 0;
	date timetable[5][10];
	for (int n = 0; n < 5; n++)
	{
		for (int m = 0; m < 10; m++)
		{
			timetable[n][m].put = 0;
		}
	}
	for (int y = 0; y < number; y++)
	{

		switch (head->tablelink->hours)
		{
		case 6:
		{
			int last = 0;
			for (int n = 0; n < 5; n++)
			{
				if (timetable[n][2].put == 0)
				{
					last = n;
					timetable[n][2].put = timetable[n][3].put = timetable[n][4].put = 1;
					timetable[n][2].classname = timetable[n][3].classname = timetable[n][4].classname = head->tablelink->classname;
					break;
				}
				if (timetable[n][7].put == 0)
				{
					last = n;
					timetable[n][7].put = timetable[n][8].put = timetable[n][9].put = 1;
					timetable[n][7].classname = timetable[n][8].classname = timetable[n][9].classname = head->tablelink->classname;
					break;
				}
			}

			if (last < 2)
			{
				for (int n = last + 2; n < 5; n++)
				{
					if (timetable[n][2].put == 0)
					{
						timetable[n][2].put = timetable[n][3].put = timetable[n][4].put = 1;
						timetable[n][2].classname = timetable[n][3].classname = timetable[n][4].classname = head->tablelink->classname;
						break;
					}
					if (timetable[n][7].put == 0)
					{
						timetable[n][7].put = timetable[n][8].put = timetable[n][9].put = 1;
						timetable[n][7].classname = timetable[n][8].classname = timetable[n][9].classname = head->tablelink->classname;
						break;
					}
				}
			}
			else
			{
				if (last == 2)
				{
					for (int n = last - 2; n < 5; n = n + 4)
					{
						if (timetable[n][2].put == 0)
						{
							timetable[n][2].put = timetable[n][3].put = timetable[n][4].put = 1;
							timetable[n][2].classname = timetable[n][3].classname = timetable[n][4].classname = head->tablelink->classname;
							break;
						}
						if (timetable[n][7].put == 0)
						{
							timetable[n][7].put = timetable[n][8].put = timetable[n][9].put = 1;
							timetable[n][7].classname = timetable[n][8].classname = timetable[n][9].classname = head->tablelink->classname;
							break;
						}
					}
				}
				else
				{
					for (int n = last - 2; n >= 0; n = n--)
					{
						if (timetable[n][2].put == 0)
						{
							timetable[n][2].put = timetable[n][3].put = timetable[n][4].put = 1;
							timetable[n][2].classname = timetable[n][3].classname = timetable[n][4].classname = head->tablelink->classname;
							break;
						}
						if (timetable[n][7].put == 0)
						{
							timetable[n][7].put = timetable[n][8].put = timetable[n][9].put = 1;
							timetable[n][7].classname = timetable[n][8].classname = timetable[n][9].classname = head->tablelink->classname;
							break;
						}
					}
				}
			}
			break;
		}
		case 5:
		{
			int last = 0;
			for (int n = 0; n < 5; n++)
			{
				if (timetable[n][2].put == 0)
				{
					last = n;
					timetable[n][2].put = timetable[n][3].put = timetable[n][4].put = 1;
					timetable[n][2].classname = timetable[n][3].classname = timetable[n][4].classname = head->tablelink->classname;
					break;
				}
				if (timetable[n][7].put == 0)
				{
					last = n;
					timetable[n][7].put = timetable[n][8].put = timetable[n][9].put = 1;
					timetable[n][7].classname = timetable[n][8].classname = timetable[n][9].classname = head->tablelink->classname;
					break;
				}
			}
			if (last < 2)
			{
				for (int n = last + 2; n < 5; n++)
				{
					if (timetable[n][0].put == 0)
					{
						timetable[n][0].put = timetable[n][1].put = 1;
						timetable[n][0].classname = timetable[n][1].classname = head->tablelink->classname;
						break;
					}
					if (timetable[n][5].put == 0)
					{
						timetable[n][5].put = timetable[n][6].put = 1;
						timetable[n][5].classname = timetable[n][6].classname = head->tablelink->classname;
						break;
					}
				}
			}
			else
			{
				if (last == 2)
				{
					for (int n = last - 2; n < 5; n = n + 4)
					{
						if (timetable[n][0].put == 0)
						{
							timetable[n][0].put = timetable[n][1].put = 1;
							timetable[n][0].classname = timetable[n][1].classname = head->tablelink->classname;
							break;
						}
						if (timetable[n][5].put == 0)
						{
							timetable[n][5].put = timetable[n][6].put = 1;
							timetable[n][5].classname = timetable[n][6].classname = head->tablelink->classname;
							break;
						}
					}
				}
				else
				{
					for (int n = last - 2; n >= 0; n = n--)
					{
						if (timetable[n][0].put == 0)
						{
							timetable[n][0].put = timetable[n][1].put = 1;
							timetable[n][0].classname = timetable[n][1].classname = head->tablelink->classname;
							break;
						}
						if (timetable[n][5].put == 0)
						{
							timetable[n][5].put = timetable[n][6].put = 1;
							timetable[n][5].classname = timetable[n][6].classname = head->tablelink->classname;
							break;
						}
					}
				}
			}
			break;
		}
		case 4:
		{
			int last = 0;
			for (int n = 0; n < 5; n++)
			{
				if (timetable[n][0].put == 0)
				{
					last = n;
					timetable[n][0].put = timetable[n][1].put = 1;
					timetable[n][0].classname = timetable[n][1].classname = head->tablelink->classname;
					break;
				}
				if (timetable[n][5].put == 0)
				{
					last = n;
					timetable[n][5].put = timetable[n][6].put = 1;
					timetable[n][5].classname = timetable[n][6].classname = head->tablelink->classname;
					break;
				}
			}
			if (last < 2)
			{
				for (int n = last + 2; n < 5; n++)
				{
					if (timetable[n][0].put == 0)
					{
						timetable[n][0].put = timetable[n][1].put = 1;
						timetable[n][0].classname = timetable[n][1].classname = head->tablelink->classname;
						break;
					}
					if (timetable[n][5].put == 0)
					{
						timetable[n][5].put = timetable[n][6].put = 1;
						timetable[n][5].classname = timetable[n][6].classname = head->tablelink->classname;
						break;
					}
				}
			}
			else
			{
				if (last == 2)
				{
					for (int n = last - 2; n < 5; n = n + 4)
					{
						if (timetable[n][0].put == 0)
						{
							timetable[n][0].put = timetable[n][1].put = 1;
							timetable[n][0].classname = timetable[n][1].classname = head->tablelink->classname;
							break;
						}
						if (timetable[n][5].put == 0)
						{
							timetable[n][5].put = timetable[n][6].put = 1;
							timetable[n][5].classname = timetable[n][6].classname = head->tablelink->classname;
							break;
						}
					}
				}
				else
				{
					for (int n = last - 2; n >= 0; n = n--)
					{
						if (timetable[n][0].put == 0)
						{
							timetable[n][0].put = timetable[n][1].put = 1;
							timetable[n][0].classname = timetable[n][1].classname = head->tablelink->classname;
							break;
						}
						if (timetable[n][5].put == 0)
						{
							timetable[n][5].put = timetable[n][6].put = 1;
							timetable[n][5].classname = timetable[n][6].classname = head->tablelink->classname;
							break;
						}
					}
				}
			}
			break;
		}
		case 3:
		{
			for (int n = 0; n < 5; n++)
			{
				if (timetable[n][2].put == 0)
				{
					timetable[n][2].put = timetable[n][3].put = timetable[n][4].put = 1;
					timetable[n][2].classname = timetable[n][3].classname = timetable[n][4].classname = head->tablelink->classname;
					break;
				}
				if (timetable[n][7].put == 0)
				{
					timetable[n][7].put = timetable[n][8].put = timetable[n][9].put = 1;
					timetable[n][7].classname = timetable[n][8].classname = timetable[n][9].classname = head->tablelink->classname;
					break;
				}
			}
			break;

		}
		case 2:
		{
			for (int n = 0; n < 5; n++)
			{
				if (timetable[n][0].put == 0)
				{
					timetable[n][0].put = timetable[n][1].put = 1;
					timetable[n][0].classname = timetable[n][1].classname = head->tablelink->classname;
					break;
				}
				if (timetable[n][5].put == 0)
				{
					timetable[n][5].put = timetable[n][6].put = 1;
					timetable[n][5].classname = timetable[n][6].classname = head->tablelink->classname;
					break;
				}
			}
			break;
		}
		case 1:
		{
			int ending = 0;
			for (int n = 0; n < 5; n++)
			{
				for (int m = 0; m < 10; m++)
				{
					if (timetable[n][m].put == 0)
					{
						timetable[n][m].put = 1;
						timetable[n][m].classname = head->tablelink->classname; ending = 1; break;
					}
				}
				if (ending == 0) { break; }
			}
			break;
		}
		default:
		{cout << "wrong" << " "; break; }
		}
		head = head->tablelink;
	}
	outfile  << setw(32) << setiosflags(ios::right)<<setfill(' ') << "星期一";
	outfile << setw(32) << setiosflags(ios::right) << setfill(' ') << "星期二";
	outfile << setw(32) << setiosflags(ios::right) << setfill(' ') << "星期三";
	outfile << setw(32) << setiosflags(ios::right) << setfill(' ') << "星期四";
	outfile << setw(32) << setiosflags(ios::right) << setfill(' ') << "星期五";
	outfile << endl;
	for (int m = 0; m < 10; m++)
	{
		for (int n = 0; n < 5; n++)
		{
			if (timetable[n][m].put == 0)
			{
				outfile << setw(32) << setiosflags(ios::right) << setfill(' ')<< "无";
			}
			else 
			{
				outfile << setw(32) << setiosflags(ios::right) << setfill(' ')<< timetable[n][m].classname;
			}
		}
		outfile << endl;
	}
	outfile.close();
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
