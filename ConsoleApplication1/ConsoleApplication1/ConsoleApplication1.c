////Write a function that gets two strings containing positive integers, and outputs a new string
////containing their sum.
////char* str_compute_sum(const char* num1, const char* num2)
////For example, str_compute_sum(“ 123456789 ”, ” 987654321 ”) returns “ 1111111110 ” .
////1. You may assume that the input is always legal, i.e., both strings are positive numbers
////2. Note that the numbers may be larger than the maximum of int or long .
////3. Also make sure that the returned string is created on the heap(and not as a local variable).
//// must use malloc()
//
//#pragma warning(disable : 4996)
//#define MAX_LIMIT 30
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdbool.h>
//char* check_str(int number)
//{
//	char revertedstr[50];
//	char str[50];
//	int length = 0;
//	while (number > 0)
//	{
//		int check = number % 10;
//		str[length++] = check | '0';
//		number /= 10;
//	}
//
//	length--;
//	int rev = 0;
//	revertedstr[length + 1] = '\0';
//	for (int i = length; 0 <= i; i--)
//	{
//		revertedstr[rev] = str[length--];
//		rev++;
//	}
//	return revertedstr;
//}
//int stringToInt(char str[]) {
//	int i = 0, sum = 0;
//	while (str[i] != '\0') {
//		sum = sum * 10 + (str[i] - 48);
//		i++;
//	}
//	return sum;
//};
//char* str_compute_sum(const char* num1, const char* num2)
//{
//	char* pos;
//	// Erase null terminator.
//	if ((pos = strchr(num1, '\n')) != NULL)
//		*pos = '\0';
//	if ((pos = strchr(num2, '\n')) != NULL)
//		*pos = '\0';
//
//
//	int numCheck= stringToInt(num1);
//	int numCheck2 = stringToInt(num2);
//	int sum = numCheck + numCheck2;
//	char* str = "";
//	str=check_str(sum);
//	return str;
//};
//
//int main()
//{
//
//	char str[MAX_LIMIT];
//	char str2[MAX_LIMIT];
//	fgets(str, MAX_LIMIT, stdin);
//	fgets(str2, MAX_LIMIT, stdin);
//	char* check = (char*)malloc(20 * sizeof(char));
//	char check2[MAX_LIMIT] = "";
//	check = "";
//	check = str_compute_sum(str, str2);
//	strcpy(check2, check);
//
//	printf("%s \n\n", check2);
//	*check = NULL;
//	check = NULL;
//	free(check);
//	//printf("%s \n\n", arr);
//	return 0;
//}
//
//
////malloc allocates memory for you but it doesn't set it to anything. malloc() returns a block of uninitialized memory.
////If you strcpy to the allocated memory then you will have a null-terminator provided for you.
//// I don't want to use string copy in this case because I want you undesrtaning ..properly.
//
