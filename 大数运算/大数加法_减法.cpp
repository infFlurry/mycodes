#if 0
/*
输入数据行数N， 1 <= N <= 100
接下来N行，每行空格隔开的两个十进制整数

输出
N行和
input:
3
1 3
7855244 785833942
-1 5
output:
4
793689186
4

此题大数加减法都涵盖
判断ab正负的四种情况
全正和全负类似，后者加上负号，同时长度为size() - 1 到1而不是到0
一正一负，要判断结果的正负性，结果与位数高者相同，位数相同则用字符串字典序
比较，用其大者减去小者。
注意进位与借位，以及其对最高位的影响。

在输出时注意左侧多余的零，以及零结果。
*/
#include<string>
#include<iostream>
#include<vector>
using namespace std;
#define MAX(A,B) (A>B)?A:B
class addition{
public:
	void add(const string &a, const string &b,string &out)
	{
		//string *out = new string("");
		out = "";
		bool aisMinus = false, bisMinus = false;
		if (a[0] == '-')
			aisMinus = true;
		if (b[0] == '-')
			bisMinus = true;

		if ((aisMinus == true && bisMinus == true) || (aisMinus == false && bisMinus == false))
		{
			int lenA = a.size(),lenB=b.size();
			int addlen = MAX(lenA, lenB);//注意最后的进位
			int posA = lenA - 1, posB = lenB - 1;
			int lowAddData = 0;
			int valueA = 0, valueB = 0,valueAdd = 0;
			if (aisMinus == true)
				addlen -= 1;//去负号
			for (int i = 0; i < addlen; ++i)
			{
				if (aisMinus == false)
				{
					if (posA >= 0)
					{
						valueA = a[posA--] - '0';
					}
					else
					{
						valueA = 0;
					}
					if (posB >= 0)
					{
						valueB = b[posB--] - '0';
					}
					else
					{
						valueB = 0;
					}
				}
				else
				{
					//去负号
					if (posA >= 1)
					{
						valueA = a[posA--] - '0';
					}
					else
					{
						valueA = 0;
					}
					if (posB >= 1)
					{
						valueB = b[posB--] - '0';
					}
					else
					{
						valueB = 0;
					}
				}
				
				valueAdd = valueA + valueB + lowAddData;
				if (valueAdd >= 10)
				{
					valueAdd -= 10;
					lowAddData = 1;
				}
				else
				{
					lowAddData = 0;
				}
				out += '0' + valueAdd;
			}
			if (lowAddData == 1)
			{
				out += '1';
			}
			if (aisMinus == true)
				out += '-';
		}

		if ((aisMinus == true && bisMinus == false) || (aisMinus == false && bisMinus == true))
		{
			int lenA ,lenB;
			if (aisMinus == true)
			{
				lenA = a.size() - 1;
				lenB = b.size();
			}
			else
			{
				lenA = a.size();
				lenB = b.size() - 1;
			}
			int addlen = MAX(lenA, lenB);//判断完正负后，不存在最高位借位
			int posA = a.size() - 1, posB = b.size() - 1;//尽管有正负号但是还是要从最后一位开始
			int lowSubData = 0;
			int valueA = 0, valueB = 0, valueSub = 0;
			int isMinus = 0;
			if (lenA > lenB)
			{
				if (aisMinus == true)
					isMinus = 1;
			}
			else if (lenA < lenB)
			{ 
				if (aisMinus == false)
					isMinus = 1;
			}
			else
			{
				string tmpA;
				string tmpB;
				if (aisMinus)
					tmpA = a.substr(1);
				else
					tmpA = a;
				if (bisMinus)
					tmpB = b.substr(1);
				else
					tmpB = b;
				//AB等长时，用字典序判断大小
				if (tmpA > tmpB)
					isMinus = 2;
				else if (tmpA < tmpB)
					isMinus = 3;
				else
				{
					out += '0';
					return;
				}
			}

			for (int i = 0; i < addlen; ++i)
			{
				if (aisMinus == false)
				{
					if (posA >= 0)
					{
						valueA = a[posA--] - '0';
					}
					else
					{
						valueA = 0;
					}
					if (posB >= 1)
					{
						valueB = b[posB--] - '0';
					}
					else
					{
						valueB = 0;
					}
				}
				else
				{
					if (posA >= 1)
					{
						valueA = a[posA--] - '0';
					}
					else
					{
						valueA = 0;
					}
					if (posB >= 0)
					{
						valueB = b[posB--] - '0';
					}
					else
					{
						valueB = 0;
					}
				}
				if (lenA > lenB)
				{
					valueSub = valueA - valueB - lowSubData;
				}
				else if (lenB > lenA)
				{
					valueSub = valueB - valueA - lowSubData;
				}
				else
				{
					if (isMinus == 2)
						valueSub = valueA - valueB - lowSubData;
					if (isMinus == 3)
						valueSub = valueB - valueA - lowSubData;
				}
				if (valueSub < 0)
				{
					valueSub += 10;
					lowSubData = 1;
				}
				else
				{
					lowSubData = 0;
				}
				out += '0' + valueSub;
			}
			if (lenA != lenB)
			{
				if (isMinus == 1)
					out += '-';
			}
			else
			{
				if ((isMinus == 2 && aisMinus == true)||(isMinus == 3 && bisMinus == true))
					out += '-';
			}
		}
	}

	void showString(string &a)
	{
		int len = a.size();
		bool firstNotZero = false;
		for (int i = len - 1; i >= 0; )
		{
			while (!firstNotZero && i != 0 && a[i] == '0') i--;
			if (a[i] != '-')
				firstNotZero = true;
			cout << a[i];
			if (--i == -1)
			{
				cout << endl;
			}
		}
	}
};
int main()
{
	struct unit{
		string a;
		string b;
	};
	vector<unit> data;
	int size;
	cin >> size;
	addition Add;
	for (int i = 0; i < size; ++i)
	{
		unit tmp;
		cin >> tmp.a >> tmp.b;
		data.push_back(tmp);
	}

	for (int i = 0; i < size; ++i)
	{
		string out;
		Add.add(data[i].a, data[i].b,out);
		Add.showString(out);
	}
	return 0;
}
#endif