//Question 4[25 points].
//Write a function that gets a 2 - d array of given dimensions of ints.
//It returns true if the array contains two columns with exactly the same values in the same
//order, and returns false otherwise.
//
//	Examples:
//On input
//{ {1,2,3,2},
//  {2,3,4,3},
//  {1,2,3,2} }
//it returns true . (the column(2, 3, 2) appears twice)


//On input
//{ {1, 2, 3, 4},
//	{ 2,3,4,5 },
//	{ 3,4,5,6 }
//}
//it returns false .
//On input
//{ {1,1,1,1},
//  {2,2,2,2},
//  {4,4,1,6} }
//it returns true (the column(1, 2, 4) appears twice)


#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

bool contains_equal_columns(int height, int width, const int arr[][6])
{
	int col = 0;
	int row = 0;
	int identical = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = i+1; j < width; j++)
		{
			// if the first value is matched, then for loop to checking.
			if (arr[row][i] == arr[row][j])
			{
				//Checking the next value in a row.
				int checking = 0;
				while (row < height)
				{
					if (arr[row][i] == arr[row][j])
					{
						checking++;
						if (checking == height)
						{
							identical++;
						}
					}
					else {
						break;
					}
					row++;
				}
				row = 0;
			}
		}
	}

	if (identical > 0)
	{
		return true;
	}
	else {
		return false;
	}
}
int main()
{
	const int ar1[5][6] = {
	  { 1,2,3,4,1,6},
	  {-1,6,3,3,2,5},
	  { 1,2,3,5,1,7},
	  { 1,2,3,5,1,4},
	  { 1,2,3,5,1,1}
	};

	bool checking = contains_equal_columns(5, 6, ar1);

	if (checking)
	{
		printf("TRUE. \n\n");
	}
	else {
		printf("FALSE. \n\n");
	}
	return 0;
}

