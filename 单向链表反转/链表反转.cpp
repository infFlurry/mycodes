#if 1
/*
	单向链表，反转。尽可能少的减少额外空间使用。

	如果没有空间限制的的话，使用栈的思想先入后出即可反转，或者
	用指针数组遍历并保存各个节点，并保存指针，然后逆序，使用头
	插法重组即可。

	使用3个指针的思路，一个保存新链表的头节点，一个保存操作节点
	，一个保存操作节点的下一节点。逐一拆卸与头插即可。
*/
#include<iostream>
using namespace std;

struct node{
	int data;
	node* next;
	node() :data(0), next(NULL){}
	node(int data, node* ptr=NULL) :data(data), next(ptr){}
};

class listFun{
public:
	node* createList(int * data,int len)
	{
		if (len == 0)
			return NULL;
		node * head = new node(data[0]);
		node * cur = head;
		for (int i = 1; i < len; i++)
		{
			node * tmp = new node(data[i]);
			cur->next = tmp;
			cur = tmp;
		}
		return head;
	}

	node* reverseList(node* list)
	{
		if (!list)
			return NULL;
		node* curN=NULL,*nextN=NULL,*headN = NULL;
		nextN = list;
		do{
			curN = nextN;
			nextN = curN->next;

			curN->next = headN;
			headN = curN;
		} while (nextN != NULL);
		return headN;
	}

	void showList(node* list)
	{
		if (!list)
			cout << "Empty list" << endl;
		do{
			cout << list->data << " ";
			list = list->next;
		} while (list!= NULL);
		cout << endl;
	}

	void destroyList(node* list)
		//当reverse之后应该讲原头指针设为NULL，防止释放已经
		//释放的空间。reverse函数返回新的头指针，但是节点的
		//空间并没有多，仍然是原来的地址。
	{
		if (!list)
			return;
		node * cur = list;
		do{
			if (cur->next != NULL)
			{
				list = cur->next;
				delete[] cur;
				cur = list;
			}
			else
			{
				delete[] cur;
				break;
			}
		}while (1);
	}
};
int main()
{
	int initial[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int len = sizeof(initial) / sizeof(int);
	listFun LF;
	node * list1 = LF.createList(initial,len);
	LF.showList(list1);
	node * list2 = LF.reverseList(list1);
	list1 = NULL;
	LF.showList(list2);
	LF.destroyList(list2);
	return 0;
}
#endif