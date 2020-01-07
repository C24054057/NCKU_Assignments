#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;

void SWAP(int, int, int);
void quickSort(int [], int , int );

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

        int *array = new int [count];
        file.open("hw10.txt", ios::in);
        for(test=0; test<count; test++)
        {
                file >> array[test];
        }

        start = clock();
        quickSort(array,0,count-1);
        End = clock();

        cpu_time_used = ((double)(End - start))/CLOCKS_PER_SEC;
        printf("use leftmost and Shorter first execution time = %f\n", cpu_time_used);
        delete [] array;
        array = NULL;
        return 0;
}

void SWAP(int b, int c, int d)
{
        d = c;
        c = b;
        b = d;
}

void quickSort(int a[], int left, int right)
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
			quickSort(a, left, j-1);
		else
			quickSort(a, j+1, right);
        }
}

