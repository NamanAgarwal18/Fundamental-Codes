#include<bits/stdc++.h>

using namespace std;

/*
	Floyd Warshall		-> Used to find "All Pair Shortest Path Problem"
						   Dynamic Programing
	
	Space Complexity	-> O(N^2)
	
	Time Complexity		-> O(N^3)
	
*/

/* 
	Possible Valies :-
	
	array -> 1. INT_MAX - Cant reach that node.
			 2. INT_MIN - Node caught in negative cycle.
			 3. Integer value - Min Cost of reaching a node.
			 
	path  -> 1. (-1) - Can't reach the node.
			 2. INT_MIN - Node caight in negative cycle.
			 3. Integer Value - Previous node to reach that node.

*/

void print(int size, vector<vector<int>> array)
{
	cout<<endl;
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			if(array[i][j]==INT_MAX)
			cout<<"   +\t|";
			else if(array[i][j]==INT_MIN)
			cout<<"   -\t|";
			else if(array[i][j]==-1)
			cout<<"\t|";
			else
			cout<<array[i][j]<<"\t|";
		}
		cout<<endl<<"--------|-------|-------|-------|-------|-------|-------|"<<endl;
	}
	cout<<endl;
}

vector<vector<int>> initialize(vector<int> from, vector<int> to, vector<int> weight, int size, vector<vector<int>> array,vector<vector<int>> &path)
{
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			if(i==j)
			{
				array[i][j] = 0;
				path[i][j]=i;
			}
			else
			{
				array[i][j] = INT_MAX;
			}
		}
	}
	for(int i=0; i<from.size(); i++)
	{
		array[from[i]][to[i]] = weight[i];
		path[from[i]][to[i]] = from[i];
	}
	return array;
}

vector<vector<int>> floydWarshall(vector<vector<int>> array, int size, vector<vector<int>> &path)
{
	for(int k=0; k<size; k++)
	{
		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				if(array[i][k] != INT_MAX && array[k][j] != INT_MAX)
				{
					if(array[i][k] + array[k][j] < array[i][j])
					{
						array[i][j] = array[i][k] + array[k][j];
						path[i][j] = k;
					}
				}
			}
		}
	}
	/*
		To find negative cycles
	*/
	for(int k=0; k<size; k++)
	{
		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				if(array[i][k] != INT_MAX && array[k][j] != INT_MAX)
				{
					if(array[i][k]==INT_MIN || array[k][j]==INT_MIN)
					{
						array[i][j] = INT_MIN;
						path[i][j] = INT_MIN;
					}
					else if(array[i][k] + array[k][j] < array[i][j])
					{
						array[i][j] = INT_MIN;
						path[i][j] = INT_MIN;
					}
				}
			}
		}
	}
	print(size,array);
	cout<<"============================================================"<<endl;
	print(size,path);
	cout<<"============================================================"<<endl;
	return array;
}

void printPath(int start, int end, vector<vector<int>> path, vector<vector<int>> array)
{
	int i = end;
	stack<int> stk;
	while(i!=-1 && i!=INT_MIN && i!=INT_MAX)
	{
		//cout<<stk.size()<<endl;
		stk.push(i);
		//cout<<i<<endl;
		if(i==start)
			i=INT_MAX;
		else
			i = path[start][i];
	}
	cout<<endl<<stk.size()<<endl;

	if(i==INT_MIN)
		cout<<"Negative Cycle Encountered";
	else if(i==-1)
	{
		cout<<"Node Unreachable";
	}
	else
	{
		cout<<"Distance - "<<array[start][end]<<"\nPath - ";
		while(!stk.empty())
		{
			cout<<stk.top()<<" -> ";
			stk.pop();
		}
	}
}

int main()
{
	vector<int> from = {0,0,0, 1,1, 2,6,4,5};
	vector<int> to = {1,2,6, 2,4, 6,5,5,4};
	vector<int> weight = {2,5,10, 2,11, 2,11,1,-2};
	int size = 7;
	vector<vector<int>> array(size, vector<int> (size,0));
	vector<vector<int>> path(size, vector<int> (size,-1));
	
	cout<<"============================================================"<<endl;
	
	array = initialize(from,to,weight,size,array,path);

	array = floydWarshall(array,size,path);
	
	printPath(6,4,path,array);
	
}
