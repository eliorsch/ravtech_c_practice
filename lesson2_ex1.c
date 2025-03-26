#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Q1()
{
	/*
	* sizeof(arr) == 40 (size of element*count of elements)
	* sizeof(p) == 8/4 (size of pointer. exact size depend on the system depend on the system)
	* size(*p) == 4 (size of the element type pointed by p (int))
	*/
}

int* intcpy(int* origin, int count)
{
	int* dest = malloc(sizeof(int) * count);
	for (size_t i = 0; i < count; i++)
	{
		dest[i] = origin[i];
	}
	return dest;
}

int isPalindrome(char* str)
{
	char* start = str, * end = str;

	while (*(end + 1)) end++;
	
	while (start < end)
	{
		if (*start != *end) return 0;
		start++;
		end--;
	}
	
	return 1;
}

void setIntTo100(int** ptrptr)
{
	**ptrptr = 100;
}

void dynamicMatrix(int m, int n)
{
	int** mat = malloc(sizeof(int*) * m);

	for (int i = 0; i < m; i++)
	{
		mat[i] = malloc(sizeof(int) * n);
		for (int j = 0; j < n; j++)
		{
			mat[i][j] = (i+1) * (j+1);
		}
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < m; i++)
	{		
		free(mat[i]);
	}
	free(mat);
}

void Q6()
{
	/*
	line:
	for (int i = 0; i <= 5; i++) {
	array's indexes ranges from 0 to n-1.
	the n index is out of range.
	should be:
	for (int i = 0; i < 5; i++) {

	*/
}

void Q7()
{
	/*
	line:
	name++ / free(name)
	the code try to free memory block not from its beginning memory pointer

	*/
}

int main()
{
	


	return 0;
}