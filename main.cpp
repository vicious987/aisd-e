#include <stdbool.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
vector<vector<int>> tree;
stack<int> bfsstack;
int n;
int * deg;
bool * discovered;
bool** in_edges;
int* priority;
int r = 0;
int stacksize = 0;
bool* in;

void printtab(int* t, int c){
	printf("\n");
	for(int i = 1; i <= c; i++)
		printf("v: %d c: %d\n", i, t[i]);
}
void printtree(vector<vector<int>> const &mat) {
	int i = 0;
	for (vector<int> row: mat) {
		printf("%d :: ", i);
		for (int val: row) {
			printf("%d ", val);
		}
		i++;
		printf("\n");
	}
}

void bfs(int node){
	discovered[node] = true;
	queue<int> q;
	q.push(node);

	while(not q.empty()){
		int v = q.front();
		q.pop();
		stacksize++;
		priority[v] = stacksize;
		bfsstack.push(v);
		for(int x : tree[v]){
			if (not discovered[x]){
				discovered[x] = true;
				q.push(x);
			}
		}
	}
}


void cut(int v, int neighbor){
	//printf("cutting %d - %d\n", v, neighbor);
	in[neighbor] = false;
	r++;
	deg[neighbor]--;
}

int main() {
	scanf("%d", &n);

	for(int i = 0; i <= n; i++){
		vector<int> v;
		tree.push_back(v);
	}
	deg = new int[n+1];
	memset(deg, 0, n+1);

	discovered = new bool[n+1];
	memset(discovered, false, n+1);

	in = new bool[n+1];
	memset(in, true, n+1);

	priority = new int[n+1];

	int x, y;
	for(int i = 1; i <= n-1; i++){
		scanf("%d %d", &x, &y);
	//	printf("uzupełniam %d %d %d\n",x,y, i);

		deg[x]++;
		deg[y]++;

		tree[x].push_back(y);
		tree[y].push_back(x);
	}

	bfs(1);


	/*
	printtab(deg, n);
	printf("\n");
	printtree(tree);
	printf("\n");

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++)
			printf("%d ", in_edges[i][j]);
		printf("\n");
	}

	printf("priority!\n");
	for (int i = 1; i <= n; i++){
		printf("%d ", priority[i]);
	}
	printf("\n");
*/	


	/*
	while(not bfsstack.empty()){
		printf("%d : ", bfsstack.top());
		bfsstack.pop();
	}
	*/

	
	while(not bfsstack.empty()){
		int v = bfsstack.top();
		//printf("working with %d(%d), deg %d, %dth element\n", v,priority[v], deg[v], stacksize);
		bfsstack.pop();
		stacksize--;
		if (deg[v] > 2){ // find 2 CHILDREN, cut everything but children
			int count = 2;
			for(int neighbor : tree[v]){
				if (count > 0){
					if (priority[neighbor] < priority[v]) // check if it is parent
						cut(v, neighbor);
					else 
						if (in[neighbor])
							count--;
				} else 
					cut(v, neighbor);

			}
			deg[v] = 2;
		}
	}
	r++;
	printf("%d", r);
	
	

//!clear mem	
	
	delete [] in_edges;
	delete [] deg;
	delete [] discovered;
	return 0;
}

