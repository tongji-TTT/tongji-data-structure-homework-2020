// 项目seven.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

class huffman 
{
	public:
		huffman* left, *right;   //左右子女
		huffman* link;
		int total;  //该节点的代价 
		huffman() { total = 0; left == NULL; right == NULL; link = NULL; } //构造函数1
		huffman(int a) { left = new huffman; left->total = a; total = a; right = NULL; }//构造函数2
		void add() { total = left->total + right->total; } //计算该节点的代价
		void swap(huffman * &a, huffman * &b);  //交换该节点和之后的节点
		int combine(int &number,huffman *&a); //将节点合并，自己和后面一个节点
		int addtotal(int &a); //计算以自己为根节点的Huffman代价

};
void huffman::swap(huffman * &a,huffman * &b)//返回两个指针方便再次链接
{
	if (link == NULL) { cout<<"link=null"<<endl; }
	if (link->link != NULL)   //后面不为空节点
	{
		huffman* p1;
		p1 = link;
		link = link->link;
		p1->link = this;
		a = link;
		b = p1;
	}
	else   //后面为空节点
	{
		huffman* p1;
		p1 = link;
		link = NULL;
		p1->link = this;
		a = link;
		b = p1;
	}
}

int huffman::combine(int &number,huffman* &a)  
{
	if (number < 1) { cout << "number < 1" << endl; return 0; }
	huffman *p1;             //创造一个新指针进行相加，并将新指针通过参数返回
	huffman *p2;
	huffman * newone = new huffman;
	p1 = this;
	p2 = link;
	newone->link = link->link;
	link->link = NULL;
	link = NULL;
	newone->left = p1;
	newone->right = p2;
	newone->add();
	number--;
	a = newone;
	return 1;
}
int huffman::addtotal(int &a) //递归进行总代价的计算
{

	if (right != NULL && left != NULL)
	{
		a = a + total;
		right->addtotal(a);
		left->addtotal(a);
	}
	else
	{
		return 0;
	}
}

int main()
{
	int end = 0;
	for (;;)
	{
		int putnumber[1024];
		int number = 0;
		//进行输入和排序，从小到大
		cin >> number;
		if (number <= 1) { cout << "输入的数小于或等于1   错误" << endl; }//边界条件
		else
		{
			int k = 0;
			for (int n = 0; n < number; n++)
			{
				cin >> putnumber[n];
				if (putnumber[n] <= 0) { cout << "输入的数字小于或等于0   错误" << endl; k = 1; break; }
			}
			if (k == 1) { break; }
			if (number == 2)
			{
				cout << putnumber[0] + putnumber[1] << endl;
			}
			else
			{
				for (int n = 0; n < number - 1; n++)
				{
					int temp;
					for (int m = 0; m < number - n - 1; m++)
					{
						if (putnumber[m] > putnumber[m + 1])
						{
							temp = putnumber[m];
							putnumber[m] = putnumber[m + 1];
							putnumber[m + 1] = temp;
						}
					}
				}
				//通过从小到大的数组建立一个从小到大的链表来表示森林
				huffman *head, *current;
				head = new huffman;
				current = new huffman(putnumber[0]);
				head->link = current;
				for (int n = 1; n < number; n++)
				{
					current->link = new huffman(putnumber[n]);
					current = current->link;
				}

				huffman *a;
				for (;;)
				{
					head->link->combine(number, a);//最小的两项相加
					head->link = a;
					current = head;
					for (int m = 1; m < number; m++)//进行交换
					{
						huffman * a; huffman * b;
						if (head->link->link == NULL) { break; }
						if (head->link->total <= head->link->link->total) { break; }
						head->link->swap(a, b);
						head->link = b;
						head = b;
					}
					head = current;

					/*	cout << endl << number << endl;
						for (int k = 0; k< number; k++)
						{
							cout << head->link->total << " ";
							head = head->link;
						}
					head = current;*/
					if (number == 1) { break; }
				}
				int general = 0;
				head->link->addtotal(general);//从根节点计算代价
				cout << general << endl;
			}
		}

		char answer;  //循环输入
		cout << "是否再次进行实验？   （Y，N）" << endl;
		for (;;)
		{
			cin >> answer;
			if (answer == 'Y' || answer == 'N') { break; }
			cout << "请输入正确的字符" << endl;
		}
		if (answer == 'N') { break; }
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
