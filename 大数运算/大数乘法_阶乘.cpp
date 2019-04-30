#if 1
/*
	编写函数，返回N的阶乘对应的十进制字符串，N>=1，N<=10000000
*/
#include<iostream>
#include<string>
#include<vector>

using namespace std;
class factorial{
public:
	string Factorial(int N)
	{
		string out("1");
		for (int i = 1; i <= N; i++)
			out = multiplication(out, to_string(i));
		return out;
	}

private:

	string multiplication(string &a, string &b)
	{
		int lena = a.size(), lenb = b.size();
		int posA = lena - 1, posB = lenb - 1;
		int carry = 0;
		string out("0");
		vector<string> middleValue;
		for (int i = posA; i >= 0; i--)
		{
			string tmp("");
			carry = 0;
			for (int j = posB; j >= 0; j--)
			{
				int valueA = a[i] - '0';
				int valueB = b[j] - '0';
				int res = valueA * valueB + carry;
				if (res >= 10)
				{
					carry = res / 10;
					res -= carry * 10;
				}
				else
				{
					carry = 0;
				}
				tmp += res + '0';
			}
			if (carry != 0)
				tmp += carry+'0';
			//为了减少复杂度先保持反序，最后1次反转即可
			middleValue.push_back(tmp);
		}
		int i = 0;
		for (auto it = middleValue.begin(); it != middleValue.end(); it++)
		{
			string move("");//第二个中间量开始要逐个向高位移动1位，即乘以10
			for (int j = 0; j < i; j++)
			{
				move += '0';
			}
			out = reveseOrderAddition(move + (*it), out);//此时的两个加数都是反序的
			i++;
		}
		reverse(out.begin(), out.end());//中间量与加法均为反序，仅此一次反向即可
		return out;
	}

	string reveseOrderAddition(string &a, string &b)
		//注意此处的输入a，b都是反序的
		//为了减少复杂度，返回值不反转，在乘法中最后统一反转
	{
		int lena = a.size(), lenb = b.size();
		int addLen = lena>lenb ? lena : lenb;
		int posA = 0, posB = 0;
		int valueA, valueB, carry = 0;
		addLen--;
		string out("");
		while (addLen >= 0)
		{
			if (posA < lena)
			{
				valueA = a[posA] - '0';
			}
			else
			{
				valueA = 0;
			}
			if (posB < lenb)
			{
				valueB = b[posB] - '0';
			}
			else
			{
				valueB = 0;
			}
			int res = valueA + valueB + carry;
			if (res >= 10)
			{
				res -= 10;
				carry = 1;
			}
			else
			{
				carry = 0;
			}
			out += res + '0';
			addLen--;
			posA++;
			posB++;
		}
		if (carry != 0)
			out += '1';
		return out;
	}
};

int main()
{
	int input = 50;
	factorial fun;
	cout << fun.Factorial(input) << endl;
	return 0;
}

#endif