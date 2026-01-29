#include <stdio.h>

#define MAX 100

int n, source, dest, e;
int graph[MAX][MAX];
int parent[MAX];


int bfs() {
    int visited[MAX];
    int queue[MAX];
    int front = 0, rear = 0;
    
    
    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
    }
    
    queue[rear++] = source;
    visited[source] = 1;
    parent[source] = -1;
    
    while (front < rear) {
        int u = queue[front++];
        
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && graph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = 1;
                
                if (v == dest) {
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

int main() {
    
    scanf("%d", &n);
    
    
    scanf("%d %d %d", &source, &dest, &e);
    
    
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            graph[i][j] = 0;
        }
    }
    
    
    for (int i = 0; i < e; i++) {
        int from, to, bandwidth;
        scanf("%d %d %d", &from, &to, &bandwidth);
        
        
        graph[from][to] += bandwidth;
        graph[to][from] += bandwidth;
    }
    
    
    int total_flow = 0;
    
    while (bfs()) {
        
        int min_cap = 99999;
        for (int v = dest; v != source; v = parent[v]) {
            int u = parent[v];
            if (graph[u][v] < min_cap) {
                min_cap = graph[u][v];
            }
        }
        
        
        for (int v = dest; v != source; v = parent[v]) {
            int u = parent[v];
            graph[u][v] -= min_cap;
            graph[v][u] += min_cap;
        }
        
        total_flow += min_cap;
    }
    
    
    printf("The bandwidth is %d\n", total_flow);
    
    return 0;
}
