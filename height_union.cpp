#include<iostream>
#include<cstring>
#define SIZE 10001
using namespace std;

typedef struct result{
	int key;
	struct result *ptr;
}result;

void heightUnion(int&, int&, int*, int*);
int collapsingFind(int&, int*);

int main(){
	char command[6];
	memset(command,0,5);
	int *parent= new int [SIZE];
	fill(parent, parent+SIZE, 0);
	int *h = new int [200];
	fill(h, h+200, 0);
	int p_h=0;
	int forest;
	int NumberOfNode=0;
	int child,Itsparent;
	cin>>forest;
	while(forest>0)
	{
		forest--;
		cin>>NumberOfNode;
		while(NumberOfNode>0)
		{
			NumberOfNode--;			
			cin>>child;
			cin>>Itsparent;
			if(Itsparent>=0)
				parent[child]=Itsparent;
			else
			{
				//this node is root
				h[p_h] = child;
				h[p_h+1] = (-1)*Itsparent;
				p_h = p_h+2;
				parent[child]=-1;
			}
		}
	}
	
	int root1, root2, node;
	result *head = NULL;
	result *tail = NULL;
	result *p_result = NULL;
	while(1)
	{
		cin>>command;
		if(!strcmp(command,"STOP"))
			break;
		if(!strcmp(command,"UNION"))
		{
			cin>>root1;
			cin>>root2;
			heightUnion(root1, root2, h, parent);
		}
		if(!strcmp(command,"FIND"))
		{
			cin>>node;
			result *r = new result;
			r->key = collapsingFind(node, parent);
			r->ptr = NULL;
			if(head == NULL)
			{
				head = r;
				tail = r;
			}
			else
			{
				tail->ptr = r;
				tail = r;
			}
		}
	}
	//print out the result
	p_result = head;
	while(p_result != NULL)
	{
		cout << p_result->key << endl;
		p_result = p_result->ptr;
	}

	return 0;
}

void heightUnion(int &r1, int &r2, int *height, int *p)
{
	int n1=-1, n2=-1;
	for(int i=0; i<200; i++)
	{
		//find the location of r1 in h[]
		if(height[i]==r1 && (i%2)==0)
		{
			n1 = height[i+1];
		}
		//find the location of r2 in h[]
		if(height[i]==r2 && (i%2)==0)
                {
                        n2 = height[i+1];
                }
		if(n1!=-1 && n2!=-1)   //finish finding
			break;
	}

	if(n1<n2)
		p[r1] = r2;
	else
		p[r2] = r1;
}


int collapsingFind(int &i, int *p)
{
	int count=0;
	int root, trail, lead;
	//climb up the tree for searching the number of the root
	for(root=i; p[root]>=0; root=p[root])
		count++;
	for(trail=i; trail!=root; trail=lead)
	{
		lead = p[trail];
		if(p[trail]!=root)
		{
			p[trail]=root;
			count++;
		}
	}
	return count;
}
		



