#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

int FindDupCharCount(string);

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<FindDupCharCount("aaabbbceeddfffggaaa55566615000225")<<endl;
	getchar();
	return 0;
}

int FindDupCharCount(string str)
{
	int count = 0;
	for(int i = 0; i < str.length() - 1; ++i)
	{
		if(
			(str[i] == str[i + 1]) && 
			((i <= str.length() - 2) && str[i] != str[i + 2])
		  )
		count++;
	}
	return count;
}