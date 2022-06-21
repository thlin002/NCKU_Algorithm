#include <iostream>
#include <vector>
using namespace std;

int inf = 10000000;

class graph{
    public:
        graph(int n): N(n), w_edge(n, vector<int>(n, inf)){

        }

        void set_wEdges(int a, int b,int k){
            w_edge[a][b] = k;
        }

        void print_edges(){
            for(int i = 0; i < N; ++i){
                for(int j = 0; j < N; ++j){
                    printf("%*d", 12, w_edge[i][j]);
                }
                cout << endl;
            }
        }

        void floyd_warshall(){
            vector<vector<int>> d(N, vector<int>(N, inf));
            vector<vector<int>> pi(N, vector<int>(N, -1));

            for(int i = 0; i < N; ++i){
                for(int j = 0; j < N; ++j){
                    d[i][j] = w_edge[i][j];
                    if(d[i][j] < inf && i != j){
                        pi[i][j] = i;
                    }
                }
            }

            for(int k = 0; k < N; ++k){
                for(int u = 0; u < N; ++u){
                    for(int v = 0; v < N; ++v){
                        if(d[u][v] > d[u][k] + d[k][v] && d[u][k] < inf && d[k][v] < inf){
                            d[u][v] = d[u][k] + d[k][v];
                            pi[u][v] = pi[k][v];
                        }
                    }
                }
            }

            print_sol_fw(d, pi);
        }

    private:
        int N;
        vector<vector<int>> w_edge;

        void print_path_fw(int u, int v, vector<vector<int>> &pi){
            int k = pi[u][v];
            if(k != u && k != -1){
                print_path_fw(u, k, pi);
            }
            if(k != -1){
                printf("%d -> ", k);
            }
        }

        void print_sol_fw(vector<vector<int>> &d, vector<vector<int>> &pi){
            for(int u = 0; u < N; ++u){
                for(int v = 0; v < N; ++v){
                    if(d[u][v] < inf && u != v){
                        //cout << u << " " << v << endl;
                        printf("vertex %d to %d, ", u, v);
                        printf(" shortest path dist %d, ", d[u][v]);
                        printf("shortest path: ");
                        print_path_fw(u, v, pi);    // print the path
                        printf("%d", v);    // print the destination
                        cout << endl;
                    }
                }
            }
        }

};

int main(){
    int N , M;  // N: number of vertices, M: number of edges
    cin >> N >> M;
    graph G(N);
    int u, v, w;
    for(int i = 0; i < M; ++i){
        cin >> u >> v >> w;
        G.set_wEdges(u, v, w);
    }
    //G.print_edges();
    G.floyd_warshall();
}
