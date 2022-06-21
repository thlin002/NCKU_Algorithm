#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int inf = 10000000;

class graph{
    public:
        graph(int n): N(n), w_edge(n, vector<int>(n, inf)), f(n){

        }

        void set_wEdges(int a, int b,int k){
            w_edge[a][b] = k;
            w_edge[b][a] = k;
        }

        void set_f(int a){
            f.push_back(a);
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

            print_nearest(d, pi);
        } 

    private:
        int N;
        vector<vector<int>> w_edge;
        vector<int> f;

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

        void print_nearest(vector<vector<int>> &d, vector<vector<int>> &pi){
            sort(f.begin(), f.end());
            for(int u = 0; u < N; ++u){
                int min = inf;
                int min_index;
                for(int i = 0; i < f.size(); ++i){
                    if(d[u][f[i]] < inf && u != f[i]){
                        if(min > d[u][f[i]]){
                            min = d[u][f[i]];
                            min_index = f[i];
                        }
                    }
                        //cout << u << " " << v << endl;
                }
                printf("%d, %d", u, f[i]);
                if(min < inf){
                    printf("%d ", min);
                }else{
                    printf("-1");
                }
            }
        } 
      

};

int main(){
    int N , M, F;  // N: number of vertices, M: number of edges
    cin >> N >> M >> F;
    graph G(N);
    int u, v, w;
    for(int i = 0; i < M; ++i){
        cin >> u >> v >> w;
        G.set_wEdges(u-1, v-1, w);
    }
    for(int i = 0; i < F; ++i){
        int f;
        cin >> f;
        G.set_f(f);
    }
    //G.print_edges();
    G.floyd_warshall();
}
