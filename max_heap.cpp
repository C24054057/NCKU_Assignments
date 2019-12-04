#include<iostream>
#define SIZE 1000000
using namespace std;

void Insert(int*, int, int&);
void reP(int*, int);

int main(){
	int TestNumber;
	int RowNumber;
	int PeopleInLine;
	int Seats;
	int count = 0;
	int Earning=0;
	int *result = new int [1000000];
	fill(result, result+1000000, 0);

	cin>>TestNumber;
	while(TestNumber>0)
	{
		int *heap = new int [1000000];
		fill(heap, heap+1000000, 0);
		cin>>RowNumber;
		cin>>PeopleInLine;
		while(RowNumber>0)
		{
			cin>>Seats;
			Insert(heap, SIZE, Seats);
			RowNumber--;
		}
		while(PeopleInLine>0)
		{
			Earning = heap[0] + Earning;
			reP(heap, SIZE);
			PeopleInLine--;
		}
		result[count] = Earning;
		Earning = 0;
		count++;
		delete [] heap;
		TestNumber--;
	}
	for(int k=0; k<count; k++)
		cout<<result[k]<<endl;
	
	delete [] result;
	return 0;
}

void Insert(int *h, int size, int &s)
{
	int i=0;
	while(h[i]!=0)
		i++;
	while(i!=0 && h[(i-1)/2]<s)
	{
		h[i] = h[(i-1)/2];
		i = (i-1)/2;
	}
	h[i] = s;
}

void reP(int *h, int size)
{
	h[0]--;
	int temp = h[0];
	int i=0;
	int leftchild = 2*i+1, rightchild = 2*i+2;
	while((h[leftchild]!=0 && h[leftchild]>temp) || (h[rightchild]!=0 && h[rightchild]>temp))
	{
		if(h[leftchild] >= h[rightchild])
		{
			h[i] = h[leftchild];
			i = leftchild;
		}
		else
		{
			h[i] = h[rightchild];
                        i = rightchild;
		}
	}
	h[i] = temp;
}
