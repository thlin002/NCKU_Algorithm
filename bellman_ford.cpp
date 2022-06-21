#include<iostream>
#include<vector>
#include<array>
using namespace std;

const int inf = 100000000;

class vtx{
    public:
        vtx(){
        }    
        vtx(int a, int b){
            d = a;
            pi = b;
        }
        int d;  // shortest path estimate
        int pi; // ancestor, -1: no ancestor
};

class graph{
    public:
        graph(int n): vertex(n), N(n){
            edge = new vector<array<int,2>>[n];
        }

        ~graph(){
            delete[] edge;
        }

        void set_edge(int u, array<int, 2> v){
            edge[u].push_back(v);
        }

        void print_edges(){
            for(int i = 0; i < N; ++i){
                vector<array<int,2>>::iterator iter;
                cout << "list[" << i << "] : ";
                for(iter = edge[i].begin(); iter != edge[i].end(); ++iter){
                    cout << (*iter)[0] << ", " << (*iter)[1] << " // ";
                }
                cout << endl;
            }            
        }

        void print_vertices(){
            for(int i = 0; i < N; ++i) {
                printf("vertex %d, d = %d, pi = %d\n", i, vertex[i].d, vertex[i].pi);
            }
        }

        int bellman_ford(int s){
            init_single_source(s);
            for(int i = 0; i < N-1; ++i){
                for(int u = 0; u < N; ++u){
                    vector<array<int,2>>::iterator iter;
                    for(iter = edge[u].begin(); iter != edge[u].end(); ++iter){
                        int v = (*iter)[0];
                        int w = (*iter)[1];
                        relax(u, v, w);
                    }
                }
            }
            for(int u = 0; u < N; ++u){
                vector<array<int,2>>::iterator iter;
                for(iter = edge[u].begin(); iter != edge[u].end(); ++iter){
                    int v = (*iter)[0];
                    int w = (*iter)[1];                    
                    if(vertex[v].d > vertex[u].d + w && vertex[u].d != inf){
                        return 1;
                    }
                }
            }
            return 0;
        }

        void print_path_bf(int s, int v){
            int k = vertex[v].pi;
            if(k != s && k != -1){
                print_path_bf(s, k);
            }
            if(k != -1){
                printf("%d -> ", k);
            }
        }

        void print_all_path(int s){
            for(int i = 0; i < N; ++i){
                if(i != s){
                    print_path_bf(s, i);
                    printf("%d\n", i);
                }
            }
        }

        void solve_diff_constraints(){
            int flag = bellman_ford(0);
            if(flag == 0){
                for(int i = 1; i < N; ++i){
                    printf("x%d = %d\n", i, vertex[i].d);
                }
            }else{
                cout << "no feasible solution exists\n";
            }
        }

    private:
        int N;
        vector<array<int, 2>> *edge; 
        // the first element of the array: the destination vertex,
        // the second element of the array: the weight of the edge

        vector<vtx> vertex;
        int count;
        void init_single_source(int s){
            for(int i = 0; i < N; ++i){
                vertex[i] = vtx(inf, -1);
            }
            vertex[s].d = 0;
        }

        void relax(int u, int v, int w){
            if(vertex[v].d > vertex[u].d + w && vertex[u].d != inf){
                vertex[v].d = vertex[u].d + w;
                vertex[v].pi = u;
            }
        }        
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);    
    int N, M, u, v, w;
    cin >> N >> M;
    graph G(N);
    array<int, 2> tmp;
    for(int i = 0; i < M; ++i){
        cin >> u >> v >> w;
        tmp[0] = v;
        tmp[1] = w;
        G.set_edge(u, tmp);
    }  

    //G.bellman_ford(0); 
    //G.print_vertices();
    G.solve_diff_constraints();
    G.print_all_path(0);

    return 0;
}
