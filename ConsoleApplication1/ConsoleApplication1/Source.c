//
//#pragma warning(disable : 4996)
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdbool.h>
//
//void left_rotate(char* str, unsigned int n) {
//    int num = n;
//    int len = strlen(str);
//    int numcheck = 0;
//    if (num > len)
//    {
//        num %= len;
//    }
//    int left = len - num - 1;
//    char temp[256];
//    char storeNElements[256];
//    int i = 0;
//
//    // store n characters into temp array 
//    if (num == 0)
//        strcpy(str, str);
//
//    else {
//        for (i = 0; i < n; i++)
//        {
//            storeNElements[i] = str[i];
//
//        }
//        storeNElements[num] = '\0';
//        strcpy(temp, &str[num]);
//        strcat(temp, storeNElements);
//        strcpy(str, temp);
//    }
//}
//
//int main(void) {
//    int leftNum = 0;
//    char str[256] = "";
//
//
//
//    //if str contains the string ”abcdef”and n = 2, then after the call str will contain ”cdefab” .
//    strcpy(str, "abcdef");
//    printf("Original string is %s\n", str);
//    leftNum = 2;
//    left_rotate(str, leftNum);
//    printf("Left [%d] and Result is [%s].\n\n", leftNum, &str[0]); 
//
//    //if str contains the string ”abcdeefg123”and n = 8, then after the call str will contain”123abcdeefg” .
//    strcpy(str, "abcdeefg123");
//    printf("Original string is %s\n", str);
//    leftNum = 8;
//    left_rotate(str, leftNum);
//    printf("Left [%d] and Result is [%s].\n\n", leftNum,  &str[0]); 
//
//    //if str contains the string ”abcd”and n = 0, then after the call str will contain ”abcd” .
//    strcpy(str, "abcd");
//    printf("Original string is %s\n", str);
//    leftNum = 0;
//    left_rotate(str, leftNum);
//    printf("Left [%d] and Result is [%s].\n\n", leftNum, &str[0]);
//
//    //if str contains the string ”abc”and n = 6, then after the call str will contain ”abc” .
//    strcpy(str, "abc");
//    printf("Original string is %s\n", str);
//    leftNum = 6;
//    left_rotate(str, leftNum);
//    printf("Left [%d] and Result is [%s].\n\n", leftNum, &str[0]);
//
//    return 0;
//}