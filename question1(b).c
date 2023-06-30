
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// this function will sort the array in descending order(Bubble sort)
void descendingSort(int arr[], int n)
{
	int i, j, temp;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

// this function will sort the array in ascending order(Bubble sort)

void ascendingSort(int arr[], int n)
{
	int i, j, temp;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

int main()
{
	int num; // total number of elements in the array

	printf("Enter elements in array: ");
	scanf("%d", &num);
	int arr[num];
	printf("Enter the elements of the array: "); //elements in the array 
	for (int i = 0; i < num; i++)
	{
		scanf("%d", &arr[i]);
	}
	int pid = fork();
	if (pid == 0)
	{
		// Child process sorts the array in ascending order
		ascendingSort(arr, num);
		printf("Ascending order: ");
		for (int i = 0; i < num; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
	else
	{
		// Parent process sorts the array in descending order
		wait(NULL);
		descendingSort(arr, num);
		printf("Descending order: ");
		for (int i = 0; i < num; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
	return 0;
}