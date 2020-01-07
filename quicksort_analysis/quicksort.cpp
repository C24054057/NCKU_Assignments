#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;


void SWAP(int, int, int);
void quickSort_LO(int [], int, int);
void quickSort_LS(int [], int, int);
void quickSort_LL(int [], int, int);
void quickSort_MO(int [], int, int);
void quickSort_MS(int [], int, int);
void quickSort_ML(int [], int, int);
void (*pfunc[])(int [], int, int) = {quickSort_LO,
				quickSort_LS,
				quickSort_LL,
				quickSort_MO,
				quickSort_MS,
				quickSort_ML};

clock_t start, End;
double cpu_time_used;

int main(){
        int count = 0;
        int test = 0;
        fstream file;
        file.open("hw10.txt", ios::in);
        while(file >> test)
        {
                count++;
        }
        file.close();

	int i;
	for(i=0; i<6; i++)
	{
        	int *array = new int [count];
        	file.open("hw10.txt", ios::in);
        	for(test=0; test<count; test++)
        	{
                	file >> array[test];
        	}

		start = clock();
        	pfunc[i](array,0,count-1);
        	End = clock();
		cpu_time_used = ((double)(End - start))/CLOCKS_PER_SEC;
		switch(i)
		{
			case 0:
        			printf("use leftmost and original execution time = %f\n", cpu_time_used);
        			break;
			case 1:
				printf("use leftmost and Shorter first execution time = %f\n", cpu_time_used);
				break;
			case 2:
				printf("use leftmost and Longer first execution time = %f\n", cpu_time_used);
				break;
			case 3:
				printf("use median of three and original execution time = %f\n", cpu_time_used);
				break;
			case 4:
				printf("use median of three and Shorter first execution time = %f\n", cpu_time_used);
                        	break;
			case 5:
				printf("use median of three and Longer first execution time = %f\n", cpu_time_used);
		}	
		delete [] array;
        	array = NULL;
	}
	file.close();	
	return 0;
}

void SWAP(int b, int c, int d)
{
        d = c;
        c = b;
        b = d;
}

void quickSort_LO(int a[], int left, int right)
{
        int pivot, i, j;
        int temp;
        int middle;
        if(left < right)
        {
                i = left;  j = right+1;
                pivot = a[left];
                do{
                        do i++; while(a[i]<pivot);
                        do j--; while(a[j]>pivot);
                        if(i<j) SWAP(a[i],a[j],temp);
                }while (i<j);
                SWAP( a[left], a[j], temp);
                quickSort_LO(a, left, j-1);
                quickSort_LO(a, j+1, right);
        }
}

void quickSort_LS(int a[], int left, int right)
{
        int pivot, i, j;
        int temp;
        int middle;
        if(left < right)
        {
                i = left;  j = right+1;
                pivot = a[left];
                do{
                        do i++; while(a[i]<pivot);
                        do j--; while(a[j]>pivot);
                        if(i<j) SWAP(a[i],a[j],temp);
                }while (i<j);
                SWAP( a[left], a[j], temp);
                if(j <= right/2)
                        quickSort_LS(a, left, j-1);
                else
                        quickSort_LS(a, j+1, right);
        }
}

void quickSort_LL(int a[], int left, int right)
{
        int pivot, i, j;
        int temp;
        int middle;
        if(left < right)
        {
                i = left;  j = right+1;
                pivot = a[left];
                do{
                        do i++; while(a[i]<pivot);
                        do j--; while(a[j]>pivot);
                        if(i<j) SWAP(a[i],a[j],temp);
                }while (i<j);
                SWAP( a[left], a[j], temp);
                if(j <= right/2)
                        quickSort_LL(a, j+1, right);
                else
                        quickSort_LL(a, left, j-1);
        }
}

void quickSort_MO(int a[], int left, int right)
{
        int pivot, i, j;
        int temp;
        int middle;
        if(left < right)
        {
                i = left;  j = right+1;
                middle = (left+right)/2;
                if(a[left] == a[right] || a[left] == a[middle])
                        pivot = a[left];
                else if(a[right] == a[middle])
                        pivot = a[right];
                else if( (a[left] > a[right] && a[left] < a[middle]) || (a[left] < a[right] && a[left] > a[middle]) )
                        pivot = a[left];
                else if( (a[right] > a[left] && a[right] < a[middle]) || (a[right] < a[left] && a[right] > a[middle]) )
                        pivot = a[right];
                else
                        pivot = a[middle];
                do{
                        do i++; while(a[i]<pivot);
                        do j--; while(a[j]>pivot);
                        if(i<j) SWAP(a[i],a[j],temp);
                }while (i<j);
                SWAP( a[left], a[j], temp);
                quickSort_MO(a, left, j-1);
                quickSort_MO(a, j+1, right);
        }
}

void quickSort_MS(int a[], int left, int right)
{
        int pivot, i, j;
        int temp;
        int middle;
        if(left < right)
        {
                i = left;  j = right+1;
                middle = (left+right)/2;
                if(a[left] == a[right] || a[left] == a[middle])
                        pivot = a[left];
                else if(a[right] == a[middle])
                        pivot = a[right];
                else if( (a[left] > a[right] && a[left] < a[middle]) || (a[left] < a[right] && a[left] > a[middle]) )
                        pivot = a[left];
                else if( (a[right] > a[left] && a[right] < a[middle]) || (a[right] < a[left] && a[right] > a[middle]) )
                        pivot = a[right];
                else
                        pivot = a[middle];
                do{
                        do i++; while(a[i]<pivot);
                        do j--; while(a[j]>pivot);
                        if(i<j) SWAP(a[i],a[j],temp);
                }while (i<j);
                SWAP( a[left], a[j], temp);
                if(j <= right/2)
                        quickSort_MS(a, left, j-1);
                else
                        quickSort_MS(a, j+1, right);
        }
}

void quickSort_ML(int a[], int left, int right)
{
        int pivot, i, j;
        int temp;
        int middle;
        if(left < right)
        {
                i = left;  j = right+1;
                middle = (left+right)/2;
                if(a[left] == a[right] || a[left] == a[middle])
                        pivot = a[left];
                else if(a[right] == a[middle])
                        pivot = a[right];
                else if( (a[left] > a[right] && a[left] < a[middle]) || (a[left] < a[right] && a[left] > a[middle]) )
                        pivot = a[left];
                else if( (a[right] > a[left] && a[right] < a[middle]) || (a[right] < a[left] && a[right] > a[middle]) )
                        pivot = a[right];
                else
                        pivot = a[middle];
                do{
                        do i++; while(a[i]<pivot);
                        do j--; while(a[j]>pivot);
                        if(i<j) SWAP(a[i],a[j],temp);
                }while (i<j);
                SWAP( a[left], a[j], temp);
                if(j <= right/2)
                        quickSort_ML(a, j+1, right);
                else
                        quickSort_ML(a, left, j-1);
        }
}



