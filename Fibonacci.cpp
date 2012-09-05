#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

int Fibonacci(int n)
{
	if(n<=2) return 1;
	int a = 1, b = 1;
	for(int i=3; i<=n; ++i)
	{
		int tmp = b;
		b = a + b;
		a = tmp;
	}
	return b;
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<Fibonacci(6)<<endl;
	getchar();
	return 0;
}