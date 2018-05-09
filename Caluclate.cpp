#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;


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
	cout << "请输入计算公式 :" << endl;
	string strInput;
	fflush(stdin);
	getline(cin, strInput);
	if (strInput.find("=") == -1)
	{
		system("cls");
		cout << "没有输入等号 !" << endl;
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

	cout << "计算结果为 : " << nSum << endl;
	return nSum;
}

int main()
{
	system("title 计算器");
	WORD type = 1;

	while(type != 2)
	{
		CaluclateResult();
loop:
		cout << "需要继续计算吗 ?" << endl;
		cout << "  1.继续计算	" << endl;
		cout << "  2.退出程序	" << endl;
		cin >> type;
		if (type != 1 && type != 2)
		{
			system("cls");
			cout << "输入错误 !" << endl;
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