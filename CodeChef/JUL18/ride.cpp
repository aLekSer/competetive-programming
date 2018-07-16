#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <set>

//PDELIV

using namespace std;
const int mod = 1000000007;
typedef long long  ll; 

class Graph
{
    int V;    // No. of vertices
	int size ;
    list<int> *adj;    // Pointer to an array containing adjacency lists
    bool isCyclicUtil(int v, bool visited[], int parent, int size);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph
    bool isCyclic(int n);   // returns true if there is a cycle
	int getSize() {
		return size;
	}
};
 
 vector<vector<list<int>>> v;
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v-1].push_back(w-1); // Add w to v’s list.
    adj[w-1].push_back(v-1); // Add v to w’s list.
}
bool Graph::isCyclicUtil(int v, bool visited[], int parent, int a_size)
{
    // Mark the current node as visited
    visited[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        // If an adjacent is not visited, then recur for that adjacent
        if (!visited[*i])
        {
           if (isCyclicUtil(*i, visited, v, a_size + 1)) {
				size  =  a_size + 1;
			   cerr <<  "path " <<  *i;
              return true;
		   }
        }
 
        // If an adjacent is visited and not parent of current vertex,
        // then there is a cycle.
        else if (*i != parent) {
			size  =  a_size + 1;
           return true;

		}
    }
    return false;
}
 
// Returns true if the graph contains a cycle starting from node n (1 to N), else false.
bool Graph::isCyclic(int n)
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
	size = 1;
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    //My change to support starting from one node
	//for (int u = 0; u < V; u++)
        if (!visited[n-1]) // Don't recur for u if it is already visited
          if (isCyclicUtil(n-1, visited, -1, size))
             return true;
 
    return false;
}

// Create a que for BFS
list<int> que;
vector<int> path;
// Doubled path
bool isReachable(int s, int d)
{
    // Base case
    if (s == d)
      return true;
	
	int V = v.size();
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
 
    // Mark the current node as visited and enque it
    visited[s] = true;
    que.push_back(s);
 
    // it will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;
     queue<vector<int> > q;
	     path.push_back(s);
    q.push(path);
    while (!que.empty())
    {       
		 path = q.front();        q.pop();
        // Deque a vertex from que and print it
		path.push_back(que.front());
        s = que.front();
        que.pop_front();
 
        // Get all adjacent vertices of the dequed vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enque it
        for (int i = 0; i != V; ++i)
        {
            // If this adjacent node is the destination node, then 
            // return true
            if (v[s][i].size() != 0 && i == d) {
				path.push_back(d);
                return true;
			}
 
            // Else, continue to do BFS
            if (v[s][i].size() != 0 && !visited[i])
            {
                visited[i] = true;
                que.push_back(i);     
				vector<int> newpath(path);
                newpath.push_back(i);
                q.push(newpath);
            }
        }
    }
     
    // If BFS is complete without visiting d
    return false;
}

int main()
{
	int n = 0, m;
	cin >> n >> m;
	vector<ll> a(n);
	vector<ll> c(m), k(m);
	v = vector<vector<list<int>>>(n, vector<list<int>>(n));
	for (int i = 0; i < m; i++) {
		int u, e ,w ;
		cin >> u >> e >> w;
		v[u-1][e-1].push_back(w);
		v[e-1][u-1].push_back(w);
	}
	int q;
	cin >> q;
	
	for (int i = 0; i < q; i++) {
		que = list<int> ();
		int u,e ,w ;
		cin >> u >> e;
		cerr << endl;
		path = vector<int>();
		isReachable(u-1, e-1);
		for (vector<int>::iterator it = path.begin(); it != path.end(); it+= 2 ){
			cerr << "Path" << *it + 1 << endl;
		}
	}
	//vector<set<int>> g(n, set<int>());
	Graph g(n);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int t; 
	int x;
	int y;
	int v;
	for (int i = 0; i < m; i++) {
		cin >> t;
		if (t == 1) {
			cin >> x;
			cin >> y;
			a[x] = y;
		} else if (t == 2) {
			cin >> x;
			cin >> y;	
			cerr << "Adding edge " << x << " " << y;
			//g[x].insert(y);		
			g.addEdge(x, y);
		} else if (t == 3) {
			cin >> x;
			cin >> y;
			cin >> v;
			if (g.isCyclic(x)) {
				int s = g.getSize();
					cerr << "Number" << i<< ": " <<  s << endl;
				if ((s + 1) % 2 == 1 ) {
					cout << 0 << endl;
				} else {
					cout << 1 << endl;
				}
			}
		}
		
	}

	cerr << "ASDD";
	/*
	for (int i = 0; i < m; i++) {
		long long min = 9223372036854775807;
		for (int j = 0; j < n; j++) {
			if (un[i].find(j) != un[i].end())
				continue;
			long long cur = (c[i] - s[j] )* (c[i] - s[j] ) + p[j];
				if (cur < min)
					min = cur;
		}
		cout << min << endl;
	}*/
}

