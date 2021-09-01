#include<bits/stdc++.h>

using namespace std;

void print(vector<int> temp)
{
	for(auto a: temp)
	{
		cout<<a<<" , ";
	}
	cout<<endl;
}

vector<vector<int>> convert_into_adjesensy(vector<int> from, vector<int> to, int size)
{
	vector<vector<int>> temp;
	for(int i=0; i<=size; i++)
	{
		vector<int> list;
		temp.push_back(list);
	}
	cout<<"created"<<temp.size()<<endl;
	for(int i=0; i<from.size(); i++)
	{
		//cout<<"in";
		temp[from[i]].push_back(to[i]);
		cout<<from[i]<<" -> ";
		print(temp[from[i]]);
	}
	return temp;
}

void print_list(vector<vector<int>> temp)
{
	int i=0;
	cout<<"out"<<temp.size()<<endl;
	for(auto a: temp)
	{
		cout<<"in";
		cout<<i<<" -> ";
		print(a);
		
		i++;
	}
	cout<<i;
}

bool dfs(vector<vector<int>> list, int size, int from, int to, bool arr[]) 
{
	if(from==to)
	return true;
	arr[from] = true;
	for(auto a: list[from])
	{
		if(!arr[a])
		{
			if(dfs(list,size,a,to,arr))
			return true;
		}
	}
	return false;
}


bool dfsPrep(vector<vector<int>> list, int size, int from, int to) //check if two nodes are connected or not
{
	bool arr[size+1] = { false };
	return dfs(list,size,from,to,arr);
}

int* bfs(vector<vector<int>> list, int size, int to, int prev[], bool visited[], deque<int> queue)
{
	if(queue.front() == to)
		return prev;
	if(queue.size() == 0 )
		return prev;
	
	int node = queue.front();
	queue.pop_front();
	for(auto a: list[node])
	{
		if(!visited[a])
		{
			visited[a] = true;
			queue.push_back(a);
			prev[a] = node;
		}
	}

	return bfs(list,size,to,prev,visited,queue);
}

void bfsPrer(vector<vector<int>> list, int size, int from, int to) //Check the path of two connected nodes
{
	int prev[size+1] = { 0 };

	bool visited[size+1] = { false };
	deque<int> queue;
	queue.push_back(from);
	int *previous = bfs(list,size,to,prev,visited,queue);
	
	int point = to;
	if(previous[point] == 0)
	{
		cout<<"Not found"<<endl;
	}
	else
	{
		
		while(point!=from)
		{
			cout<<point<<" <- ";
			point = previous[point];
			
		}
		cout<<point<<endl;
	}
	
	//return previous;
	
}

int main()
{
	//Enter Arrays
	vector<vector<int>> adjesensy_list;
	vector<int> from;
	vector<int> to;
	from.push_back(1);
	to.push_back(2);
	from.push_back(2);
	to.push_back(3);
	from.push_back(3);
	to.push_back(5);
	from.push_back(5);
	to.push_back(6);
	from.push_back(5);
	to.push_back(4);
	from.push_back(4);
	to.push_back(2);
	print(from);
	print(to); 
	
	//Convert array into list
	adjesensy_list = convert_into_adjesensy(from,to,6);
	cout<<adjesensy_list.size()<<endl;
	print_list(adjesensy_list);
	cout<<endl;
	
	//Find if start is connected to end;
	int start = 1, end = 4;
	if(dfsPrep(adjesensy_list,6,start,end))
	{
		cout<<"Conncted and the path is: ";
		bfsPrer(adjesensy_list,6,start,end);
	}
	else
	{
		cout<<"Not Connected";
	}
	
	
	
	
}
