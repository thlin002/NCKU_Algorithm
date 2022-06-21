#include<iostream>
#include<vector>
#include<array>
#include<stdlib.h>
using namespace std;

const int inf = 10000000;

class vtx{
    public:
        vtx(){   
        }        
        
        vtx(int a, int b, int c){   
            d = a;
            parent = b;
            in_Q = c;
        }

        int d;
        int parent;
        int in_Q;
};

class graph{
    public:
        graph(int n): N(n), vertex(n), w_edge(n, vector<int>(n, -1)){
            for(int i = 0; i < N; ++i){
                vertex[i] = vtx(inf, -1, 1);
                for(int j = 0; j < N; ++j){
                    w_edge[i][j] = inf;
                }
            }
        }

        void set_wEdges(int a, int b,int k){
            if(k < w_edge[a][b]){
                w_edge[a][b] = k;
                w_edge[b][a] = k;
            }
        }

        void print_edges(){
            for(int i = 0; i < N; ++i){
                for(int j = 0; j < N; ++j){
                    printf("%*d", 5, w_edge[i][j]);
                }
                cout << endl;
            }
        }

        void print_vertex(){
            for(int i = 0; i < N; ++i){
                printf("vertex %d, index %d, parent %d, in_Q %d\n", i, vertex[i].d, vertex[i].parent, vertex[i].in_Q);
            }
        }

        void dijkstra(int s){
            init_single_source(s);
            int Q_size = N;
            vector<vtx> set;
            while( Q_size > 0){
                int u = extract_min();
                Q_size--;
                set.push_back( vertex[u] );
                for(int i = 0; i < N; ++i){
                    if(i != u){
                        relax(u, i);
                    }
                }
            }
        }

        int get_max_shortest_path(){
            int max = -1;
            for(int i = 0; i < N; ++i){
                if(vertex[i].d > max){
                    max = vertex[i].d;
                }
            }
            return max;
        }

    private:
        int N;
        vector<vtx> vertex;
        vector<vector<int>> w_edge;
    
        void init_single_source(int s){
            for(int i = 0; i < N; ++i){
                vertex[i] = vtx(inf, -1, 1);
            }
            vertex[s].d = 0;
        }

        void relax(int u, int v){
            if(vertex[v].d > vertex[u].d + w_edge[u][v] && vertex[u].d != inf && w_edge[u][v] != inf){   // If the problem have non reachable vertices than, we have to take into consideration
                vertex[v].d = vertex[u].d + w_edge[u][v];   // of the special characteristic of arithmetic operations on infinite.
                vertex[v].parent = u;                       // we need to consider that. for example, inf + 6 = inf. 
            }
        }

        int extract_min(){  // treat vertex vector as a min_queue
            int min = inf;
            int min_ind = 0;
            for(int i = 0; i < N; ++i){
                if(vertex[i].in_Q && vertex[i].d < min){
                    min = vertex[i].d;
                    min_ind = i;
                }
            }
            vertex[min_ind].in_Q = 0;
            return min_ind;
        }

};


int main(){
    int N, M;
    cin >> N >> M;
    graph G(N);
    int u, v, w;
    for(int i = 0; i < M; ++i){
        cin >> u >> v >> w;
        G.set_wEdges(u-1, v-1, w);
    }
    
    //G.print_edges();
    G.dijkstra(0);
    cout << G.get_max_shortest_path();


}