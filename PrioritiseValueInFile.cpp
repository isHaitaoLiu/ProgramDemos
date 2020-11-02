/*
Question:
Write a program by implementing the following functionality: 

Prioritise a value in a text file:

The main() will call a self-defined function to prioritise a value in a text file. Program should start from an empty file. You can pick a proper name for your self-defined function. Each line in the file only has one value.

The self-defined function implementation should be as follows: 

Ask user to enter an input value each time 

If the input value already exists in any line in the file, prioritise the value by swapping with the value ahead of it. 
If the input value equals to the value of the first value in the file, keep the file as it is.
If the input value does not exist in the file, add a new line with this value at the end of the file. 
For example, when the file has 5 valid values, 11 22 44 33 55 (each value in one line), 11 is the first value and 55 is the end. 

if the user input is 44, after calling the self-defined function, the file will be 11 44 22 33 55 (each value in one line)
if the user input is 11, after calling the self-defined function, the file will be 11 22 44 33 55 (each value in one line)
if the user input is 66, after calling the self-defined function, the file will be 11 22 44 33 55 66 (each value in one line)
The self-defined function exits EITHER the user input is 0 OR 10 valid values are in the file, whichever happens first. The input 0 should not be saved in the file.

You MUST use dynamic memory allocation in your implementation.

The self-defined function checks if the user input is valid or not, valid value should be any integer between 1 and 100, inclusive. If the user's input is invalid, the function will ask the user to enter again, until a valid input is entered.

After the self-defined function exits and returns to the main, the program should print all the values in the file from the beginning to the end in the main, separate each value by one space.

*/

#include <cstdio>
#include <stdlib.h>
int count = 0;

int* fun()
{
	int* array;
	array = (int*)malloc(10 * sizeof(int));
	
	FILE* fp = NULL;
	fp = fopen("test.txt", "r");
	for (int i = 0; i < 10; i++)
	{
		if (fscanf(fp, "%d", array + i) != EOF)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	fclose(fp);
	int inputNum, index = -1;
	printf("please input a number(1 <= num <= 100):");
	scanf("%d", &inputNum);
	while ((inputNum < 1 || inputNum > 100)&& inputNum != 0)
	{
		printf("Wrong number!\n");
		printf("please input a number(1 <= num <= 100):");
		scanf("%d", &inputNum);
	}
	if (inputNum == 0 || count >= 10)
	{
		return NULL;
	}
	for (int i = 0; i < count; i++)
	{
		if (array[i] == inputNum) index = i;
	}
	if (index != 0 && index != -1)
	{
		int temp = array[index];
		array[index] = array[index - 1];
		array[index - 1] = temp;
	}
	if (index == -1)
	{
		array[count] = inputNum;
		count++;
		fp = fopen("test.txt", "a+");
		fprintf(fp, "%d\n", inputNum);
		fclose(fp);
	}
	return array;
}

int main() 
{
	int* array;
	array = fun();
	if (array != NULL) {
		for (size_t i = 0; i < count; i++)
		{
			printf("%d ", array[i]);
		}
	}
	return 0;
}
