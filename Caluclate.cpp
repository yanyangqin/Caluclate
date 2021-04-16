#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

/////////////���Ը���
int GetResult(WORD &index, string strInput)
{
	string strOneNum;
	index = index + 1;
	WORD resultTemp = strInput[index] - '0'; 
	while(resultTemp >= 0 && resultTemp <= 9)
	{
		strOneNum.push_back(strInput[index]);
		index++;
		resultTemp = strInput[index] - '0';
	}

	return atoi(strOneNum.c_str());
}

LONGLONG CaluclateResult()
{
loop:
	cout << "��������㹫ʽ :" << endl;
	string strInput;
	fflush(stdin);
	getline(cin, strInput);
	if (strInput.find("=") == -1)
	{
		system("cls");
		cout << "û������Ⱥ� !" << endl;
		strInput.clear();
		goto loop;
	}

	vector<int> vecNumber;
	string strOneNum;
	WORD i = 0;
	while(strInput[i] != '=')
	{
		int result = strInput[i] - '0'; 
		if (result >= 0 && result <= 9) 
		{
			strOneNum.push_back(strInput[i]);
		}
		else
		{
			switch (strInput[i])
			{
			case '+':
				{
					vecNumber.push_back(atoi(strOneNum.c_str()));
					strOneNum.clear();
					break;
				}
			case '-':
				{
					vecNumber.push_back(-GetResult(i, strInput));
					i = i - 1;
					break;
				}
			case '*':
				{
					WORD nNum = atoi(strOneNum.c_str());
					strOneNum.clear();
					vecNumber.push_back(nNum*GetResult(i, strInput));
					i = i - 1;
					break;
				}
			case '/':
				{
					WORD nNum = atoi(strOneNum.c_str());
					strOneNum.clear();
					vecNumber.push_back(nNum/GetResult(i, strInput));
					i = i - 1;
					break;
				}
			}
		}
		i++;
	}

	if (!strOneNum.empty())
	{
		vecNumber.push_back(atoi(strOneNum.c_str()));
		strOneNum.clear();
	}

	LONGLONG nSum = 0;
	for (WORD j = 0; j < vecNumber.size();j++)
	{
		nSum+=vecNumber[j];
	}

	cout << "������Ϊ : " << nSum << endl;
	return nSum;
}

int main()
{
	cout << "test" << endl;
	system("title ������");
	WORD type = 1;

	while(type != 2)
	{
		CaluclateResult();
loop:
		cout << "��Ҫ���������� ?" << endl;
		cout << "  1.��������	" << endl;
		cout << "  2.�˳�����	" << endl;
		cin >> type;
		if (type != 1 && type != 2)
		{
			system("cls");
			cout << "������� !" << endl;
			//system("pause");
			goto loop;
		}
		else if(type == 1)
		{
			system("cls");
		}
	}

	return 0;
}