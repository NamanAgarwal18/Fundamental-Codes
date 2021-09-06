#include<bits/stdc++.h>

using namespace std;

/*
	Conditions -> Only works for directed acyclic graph
		      Needs to find topological sorting first
*/

void print(map<int,int> array[], int size)
{
	for(int i=0; i<size; i++)
	{
		cout<<i<<" -> ";
		for(auto a : array[i])
		{
			cout<<"{ "<<a.first<<" , "<<a.second<<" } , ";
		}
		cout<<endl;
	}

}

void list_create(vector<int> from, vector<int> to, vector<int> weight, int size, map<int,int> array[])
{
	for(int i=0; i<from.size(); i++)
	{
		(array[from[i]])[to[i]] = weight[i];
	}	
}

int topological_sort(map<int,int> array[], int size, int topposort[], bool flag[], int index, int node)
{
	if(index == -1)
		return -1;
	for(auto a: array[node])
	{
		if(!flag[a.first])
		{
			index = topological_sort(array,size,topposort,flag,index,a.first);
			flag[a.first] = true;
		}
	}
	topposort[index] = node;
	index--;
	return index;
}


void topological_sort_wrapper(map<int,int> array[], int size, int topposort[])
{
	int index = size-1;
	bool flag[size] = { false };
	for(int i=0; i<size; i++)
	{
		if(!flag[i])
		{
			flag[i] = true;
			index = topological_sort(array,size,topposort,flag,index,i);
		}
	}
}

void shortest_path(map<int,int> array[], int size, int topsort[],int from, int to,int Distance[],bool smallest)
{
	for(int i=0; i<size; i++)
	{
		if(smallest) //find smallest distance
			Distance[i] = (INT_MAX);
		else //find largest distance
			Distance[i] = (INT_MIN);		
	}	
	int index = 0;
	for(int i=0; i<size; i++)
	{
		if(topsort[i] == from)
		{
			index = i;
			break;
		}
	}
	Distance[from] = 0;
	int a = from;
	while(a!=to && index!=size){
		for(auto temp: array[a])
		{
			int dist = Distance[a];
			dist = dist + temp.second;
			if(smallest)
			{
				dist = min(dist,Distance[temp.first]);
			}
			else
			{
				dist = max(dist,Distance[temp.first]);
			}
			Distance[temp.first] = dist;
		}
		index++;
		a = topsort[index];
	}
}


int main()
{
	vector<int> from = {0,0,1,1,1,2,2,3,3,3,4,5,6};
	vector<int> to = {1,2,4,3,2,3,6,4,5,6,7,7,7};
	vector<int> weight = {3,6,11,4,4,8,11,-4,5,2,9,1,2};
	int size = 8;
	map<int,int> array[size];
	list_create(from,to,weight,size,array);
	print(array,size);
	int ordering[size] = {0};
	topological_sort_wrapper(array,size,ordering);
	cout<<endl;
	for(int i=0; i<size; i++){
		cout<<ordering[i]<<" , ";
	}
	cout<<endl;
	int shortestDistance[size] ;
	shortest_path(array,size,ordering,1,0,shortestDistance,true);
	for(int i=0; i<size; i++){
		if(INT_MAX == shortestDistance[i])
		{
			cout<<"i: "<<i<<" -> infinity"<<"\n";

		}
		else
		{
			cout<<"i: "<<i<<" -> "<<shortestDistance[i]<<"\n";

		}
	}
	cout<<endl;
	shortest_path(array,size,ordering,1,0,shortestDistance,false);
	for(int i=0; i<size; i++){
		if(INT_MIN== shortestDistance[i])
		{
			cout<<"i: "<<i<<" -> infinity"<<"\n";

		}
		else
		{
			cout<<"i: "<<i<<" -> "<<shortestDistance[i]<<"\n";

		}
	}
	
}
