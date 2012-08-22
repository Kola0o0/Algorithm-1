// Algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int FindSecondBig(int arr[], int n)
{
	if(n < 2)
		return -1;
	int num1,num2;
	if(arr[0] >= arr[1])
	{
		num1 = arr[0];
		num2 = arr[1];
	}
	else
	{
		num1 = arr[1];
		num2 = arr[2];
	}
	for(int i = 2; i < n; ++i)
	{
		if(arr[i] > num1)
		{
			num2 = num1;
			num1 = arr[i];
		}
		else if(arr[i] > num2)
			num2 = arr[i];
	}
	return num2;
}

int Find2ndMaxNum(int *pArrary, int length)
{
	if(length < 2)
		return -1;
	int num1,num2;
	if(*pArrary >= *(pArrary + 1))
	{
		num1 = *pArrary;
		num2 = *(pArrary + 1);
	}
	else
	{
		num1 = *(pArrary + 1);
		num2 = *pArrary;
	}
	for(int *pbegin = pArrary, *pend = pArrary + length; *pbegin != *pend; ++pbegin)
	{
		if(*pbegin > num1)
		{
			num2 = num1;
			num1 = *pbegin;
		}
		else if(*pbegin > num2)
		{
			num2 = *pbegin;
		}
	}
	return num2;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int arr[5] = { 2, 5, 8, 10, 34};

	cout<<FindSecondBig(arr, 5)<<endl;

	cout<<Find2ndMaxNum(arr, 5)<<endl;

	getchar();
	return 0;
}

