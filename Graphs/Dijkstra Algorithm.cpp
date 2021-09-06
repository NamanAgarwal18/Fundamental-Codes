#include<bits/stdc++.h>

using namespace std;

/*
	Dijkstra's Algorithm -> Used to find shortest path to any vortex from a particular vortex. 
							It is a greedy algorithm.
							Used for directed weighted graph.
							The graph can be cyclic.
							Can also work for a undirected graph.
	
	Condition 			 -> All the edge weights must be 0 or +ve.
	
	Modification		 -> Can be modified to make a minimum spanning tree
							Can be optimized to find the minimum distance between 2 points and not for all points.
	
	Better Optimization  -> Can be better optimized by using an "Indexed priority queue"
																	     OR
																    "D-array heap"
																         OR
																   "Fibonacci Heap"
																
*/

void print(map<int,int> array[], int size)
{
	for(int i=0; i<size; i++)
	{
		cout<<i<<" -> ";
		for(auto a: array[i])
		{
			cout<<"{ "<<a.first<<" - "<<a.second<<" }, ";
		}
		cout<<endl;
	}
}

void list_create(vector<int> from, vector<int> to, vector<int> weight, map<int,int> array[])
{
	for(int i=0; i<from.size(); i++)
	{
		(array[from[i]])[to[i]] = weight[i];
	}
}

//To initialize any array of any datatype to any value
void initialize(auto array[], int size, auto value)
{
	for(int i=0; i<size; i++)
	{
		array[i] = value;
	}
}

void print_arr(auto array[], int size)
{
	for(int i=0; i<size; i++)
	{
		cout<<array[i]<<" , ";
	}
	cout<<endl;
}

//The original dijkstra's allgorithm to find the minimum distance for any node from start node and an array previous to help create a path to any node from start
void dijkstra(map<int,int> array[], int size, int start, int previous[], int distance[])
{
	/*
	 	Creating a Min Heap priority queue of pairs <ai,bi>
		ai -> minimum distance to the point bi from the start node
		it is sorted based on "ai"
	*/
	priority_queue< pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>> > queue;
	queue.push(make_pair(0,start));
	distance[start] = 0;
	/*
		In the previous array -> 
		 -2 indicates that this was the start node for the dijkstra
		 -1 indicates that the node is unreachable from the start node
	*/
	previous[start] = -2;
	while(!queue.empty())
	{
		pair<int,int> temp = queue.top();
		int dist = temp.first, node = temp.second;
		queue.pop();
		if(distance[node] >= dist)
		{
			distance[node] = dist;
			for(auto edges: array[node])
			{
				int d = dist + edges.second;
				if(d < distance[edges.first])
				{
					distance[edges.first] = d;
					previous[edges.first] = node;
					queue.push(make_pair(d,edges.first));
				}
			}
		}
	}
}

//The modified dijkstra's algorithm to find the minimum distance between 2 nodes
int dijkstra_only_2_nodes(map<int,int> array[], int size, int start, int end, int previous[], int distance[])
{
	priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > queue;
	/*
	 	Creating a Min Heap priority queue of pairs <ai,bi>
		ai -> minimum distance to the point bi from the start node
		it is sorted based on "ai"
	*/
	queue.push(make_pair(0,start));
	distance[start] = 0;
	/*
		In the previous array -> 
		 -2 indicates that this was the start node for the dijkstra
		 -1 indicates that the node is unreachable from the start node
	*/
	previous[start] = -2;
	while(!queue.empty())
	{
		pair<int,int> temp = queue.top();
		int dist = temp.first, node = temp.second;
		queue.pop();
		if(distance[node] >= dist)
		{
			distance[node] = dist;
			if(node == end)
				return distance[node];
			for(auto edges: array[node])
			{
				int d = dist + edges.second;
				if(d < distance[edges.first])
				{
					distance[edges.first] = d;
					previous[edges.first] = node;
					queue.push(make_pair(d,edges.first));
				}
			}
		}
	}
}

//To print the shortest path between 2 nodes
void shortestPath(int start, int end, int size, int previous[])
{
	vector<int> array;
	array.push_back(end);
	for(int i=end; i!=start; )
	{
		i = previous[i];
		if(i == -1)
		{
			cout<<"No path exists";
			return;
		}
		array.push_back(i);
	}
	cout<<"The path from "<<start<<" to "<<end<<" is: ";
	for(int i=array.size()-1; i>=0; i--)
	{
		cout<<array[i]<<" -> ";
	}
	cout<<endl;
}

void minSpanTree(map<int,int> array[], int size, vector<int> from, vector<int> to, vector<int> weight, int previous[])
{
	for(int i=0; i<size; i++)
	{
		if(previous[i]>=0)
		{
			from.push_back(previous[i]);
			to.push_back(i);
			weight.push_back((array[previous[i]])[i]);
		}
	}
	cout<<"\nMin Span Tree: \n";
	//cout<<from.size();
	for(int i=0; i<from.size(); i++)
	{
		cout<<from[i]<<" ---"<<weight[i]<<"---> "<<to[i]<<endl;
	}
	
}

// Steps to find minimum distance from start node to all the nodes
void minimum_distance_from_start_to_all(map<int,int> array[], int size)
{
	cout<<"\nGetting distance from start to all nodes: \n";
	/*
		previous -> the node that right before the current node
					"previous[i] points to i"
		distance -> distance to reach this node from the start node		
	*/
	int previous[size], distance[size];
	initialize(previous,size,-1);
	initialize(distance,size,INT_MAX);
	//print_arr(previous,size);
	//print_arr(distance,size);
	int start = 0;
	dijkstra(array,size,start,previous,distance);
	print_arr(previous,size);
	print_arr(distance,size);
}


// Steps to find minimum distance between 2 nodes
void minimum_distance_between_two_nodes(map<int,int> array[], int size)
{
	cout<<"\nGetting distance between 2 nodes: \n";
	/*
		previous -> the node that right before the current node
					"previous[i] points to i"
		distance -> distance to reach this node from the start node		
	*/
	int previous[size], distance[size];
	initialize(previous,size,-1);
	initialize(distance,size,INT_MAX);
	//print_arr(previous,size);
	//print_arr(distance,size);
	int start = 0, end = 3;
	dijkstra_only_2_nodes(array,size,start,end,previous,distance);
	print_arr(previous,size);
	print_arr(distance,size);
}

// Steps to find shortest path between 2 nodes
void shortest_path_between_two_nodes(map<int,int> array[], int size)
{
	cout<<"\nGetting shortest path between 2 nodes: \n";
	/*
		previous -> the node that right before the current node
					"previous[i] points to i"
		distance -> distance to reach this node from the start node		
	*/
	int previous[size], distance[size];
	initialize(previous,size,-1);
	initialize(distance,size,INT_MAX);
	//print_arr(previous,size);
	//print_arr(distance,size);
	int start = 0, end = 3;
	dijkstra_only_2_nodes(array,size,start,end,previous,distance);
	print_arr(previous,size);
	print_arr(distance,size);
	
	shortestPath(start,end,size,previous);
}

// Steps to find sminimum spanning tree
void min_span_tree(map<int,int> array[], int size)
{
	//Minimum spanning tree can only be created if all the points are linked and if start can reach all the points
	cout<<"\nGetting minimum spanning tree: \n";
	int previous[size], distance[size];
	initialize(previous,size,-1);
	initialize(distance,size,INT_MAX);
	//print_arr(previous,size);
	//print_arr(distance,size);
	int start = 0;
	dijkstra(array,size,start,previous,distance);
	print_arr(previous,size);
	print_arr(distance,size);
	vector<int> from;
	vector<int> to;
	vector<int> weight;
	minSpanTree(array,size,from,to,weight,previous);
}

int main()
{
	vector<int> from = {0,0,1,2,2,3};
	vector<int> to = {1,2,3,1,3,4};
	vector<int> weight = {4,1,1,2,5,3};
	int size = 5;
	map<int,int> array[size];	
	list_create(from,to,weight,array);
	print(array,size);

	// To find minimum distance from start node to all the nodes
	minimum_distance_from_start_to_all(array,size);
	
	// To find minimum distance between 2 nodes
	minimum_distance_between_two_nodes(array,size);
	
	// To find shortest path between 2 nodes
	shortest_path_between_two_nodes(array,size);
	
	// To find the minimum spanning tree
	min_span_tree(array,size);
}
