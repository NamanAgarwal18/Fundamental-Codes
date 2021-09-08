#include<bits/stdc++.h>

using namespace std;

/*
	Bellman Ford Algorithm 		 -> Computes shortest paths from a single source vertex to all of the other vertices
							  		Can handle negative weights
							  		Can detect negative cycles
	
	Average Speed 		   		 -> O(E.V)
	Worst Speed	(Complete Graph) -> O(V^3)
	
	Optimization for a sparse graphs -> Shortest Path Faster Algorithm (SPFA)
	
*/



void initialise(auto arr[], int size, auto val)
{
	for(int i=0; i<size; i++)
	{
		arr[i] = val;
	}
}

//Bellman Fort to find if a negative cycle exists or not
void bellmanFord(vector<int> from, vector<int> to, vector<int> weight, int size, int dist[], int start)
{
	int i = 0;
	dist[start] = 0;
	for(i = 0; i<size-1; i++)
	{
		int change = 0;
		for(int j=0; j<from.size(); j++)
		{
			if(dist[to[j]] > dist[from[j]] + weight[j])
			{
				change++;
				dist[to[j]] = dist[from[j]] + weight[j];
			}
		}
		if(change == 0)
			break;
	}
	if(i==size-1)
	{
		int change = 0;
		for(int j=0; j<from.size(); j++)
		{
			if(dist[to[j]] > dist[from[j]] + weight[j])
			{
				cout<<"Negative Loop"<<endl;
				break;
			}
		}
	}
	for(i=0; i<size; i++)
	{
		cout<<dist[i]<<" , ";
	}
	cout<<endl;
}

//Bellman Fort to find if a negative cycle exists and if it does then find the nodes affected.
void bellmanFordComplete(vector<int> from, vector<int> to, vector<int> weight, int size, int dist[], int start)
{
	int i = 0;
	dist[start] = 0;
	for(i = 0; i<size-1; i++)
	{
		int change = 0;
		for(int j=0; j<from.size(); j++)
		{
			if(dist[to[j]] > dist[from[j]] + weight[j])
			{
				change++;
				dist[to[j]] = dist[from[j]] + weight[j];
			}
		}
		if(change == 0)
			break;
	}
	if(i==size-1)
	{
		for(int j=0; j<from.size(); j++)
		{
			if(dist[from[j]] == INT_MIN)
			{
				//Handling the logic that anything + -(inf) = -(inf)
				dist[to[j]] = INT_MIN;
			}
			else if(dist[to[j]] > dist[from[j]] + weight[j])
			{
				dist[to[j]] = INT_MIN;
			}
		}
	}
	for(i=0; i<size; i++)
	{
		if(dist[i] != INT_MIN)
		{
			cout<<dist[i]<<" , ";
		}
		else
		{
			cout<<"-(inf) , ";
		}
	}
	cout<<endl;
}

//Shortest Path Faster Algorithm to find if a negative cycle exists and if it does then find the nodes affected.
void shortestPathFasterAlgorithm(vector<int> from, vector<int> to, vector<int> weight, int size, int dist[], int start)
{
	int i = 0;
	dist[start] = 0;
	//Constant is true if there has not been any changes in the optimization of that node's distance in thye last 2 turns.
	bool constant[size] = {false};
	for(i = 0; i<size-1; i++)
	{
		int change = 0;
		for(int j=0; j<from.size(); j++)
		{
			if(constant[from[j]]==false)
			{
				//if no changed happened in the node then the node won't affect any other node as well.
				if(dist[to[j]] > dist[from[j]] + weight[j])
				{
					change++;
					dist[to[j]] = dist[from[j]] + weight[j];
					constant[to[j]] = false;
				}
				else
				{
					constant[to[j]] = true;
				}
			}
		}
		if(change == 0)
			break;
	}
	if(i==size-1)
	{
		for(int j=0; j<from.size(); j++)
		{
			if(dist[from[j]] == INT_MIN)
			{
				//Handling the logic that anything + -(inf) = -(inf)
				dist[to[j]] = INT_MIN;
			}
			else if(dist[to[j]] > dist[from[j]] + weight[j])
			{
				dist[to[j]] = INT_MIN;
			}
		}
	}
	for(i=0; i<size; i++)
	{
		if(dist[i] != INT_MIN)
		{
			cout<<dist[i]<<" , ";
		}
		else
		{
			cout<<"-(inf) , ";
		}
	}
	cout<<endl;
}

//Steps to find if a negative cycle exists or not
void bellmanFord_Identify_Negative_Loop(vector<int> from, vector<int> to, vector<int> weight, int size)
{
	cout<<endl;
	int dist[size];
	initialise(dist,size,INT_MAX);
	bellmanFord(from,to,weight,size,dist,0);
}

//Steps to find if a negative cycle exists or not and if it does then find the nodes affected.
void bellmanFord_Negative_Infinity(vector<int> from, vector<int> to, vector<int> weight, int size)
{
	cout<<endl;
	int dist[size];
	initialise(dist,size,INT_MAX);
	shortestPathFasterAlgorithm(from,to,weight,size,dist,0);
}

//Steps to find if a negative cycle exists or not and if it does then find the nodes affected using SPFA
void SPFA_Negative_Infinity(vector<int> from, vector<int> to, vector<int> weight, int size)
{
	cout<<endl;
	int dist[size];
	initialise(dist,size,INT_MAX);
	shortestPathFasterAlgorithm(from,to,weight,size,dist,0);
}

int main()
{
	vector<int> from = {0,1,1,1,2,2,3,4,5,5,5,6,7};
	vector<int> to = {1,2,5,6,3,4,2,9,4,6,8,7,8};
	vector<int> weight = {5,20,30,60,10,75,-15,100,25,5,50,-50,-10};
	int size = 10;

	//To find if a negative cycle exists or not
	bellmanFord_Identify_Negative_Loop(from,to,weight,size);
	
	//To find if a negative cycle exists or not and if it does then find the nodes affected.
	bellmanFord_Negative_Infinity(from,to,weight,size);
	
	//To find if a negative cycle exists or not and if it does then find the nodes affected using SPFA
	SPFA_Negative_Infinity(from,to,weight,size);
}
