#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "List.h"

int n;
vector<int> g[MAXN];
bool used[500];

void dfs(int v, List* comp) {
	used[v] = true;
	addData(comp, v);
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (!used[to])
		{
			dfs(to, comp);
		}
	}
}

void find_comps() {
	for (int i = 0; i < n; ++i)
	{
		used[i] = false;
	}
	for (int i = 0; i < n; ++i)
	{
		if (!used[i]) {
			List* comp = createList();
			dfs(i, &comp);

			printf("Component:\n");
			printList(comp);
		}
	}
}

int main()
{
	FILE* file = fopen("input.txt", "r");
	int n = 0;
	fscanf_s(file, "%d", &n);
	while (!feof(file))
	{
		// :(
	}
	find_comps();
}