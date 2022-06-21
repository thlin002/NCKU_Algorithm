#include<iostream>
#include<vector>
using namespace std;

int time_stmp = 0;

typedef struct v{
    int color; // 0: white, 1: grey, 2: black
    int pi; // ancestor, -1: no ancestor
    int d;
    int f;    
    int cc; // cc would be the same if the vertex is connected in the same tree after dfs
} vtx;

class graph{
    public:
        graph(int n): vertex(n), N(n){
            edge = new vector<int>[n];
        }

        ~graph(){
            delete[] edge;
        }

        void set_edge(int u, int v, int e){
            edge[u].push_back(v);
            if(e == 2){
                edge[v].push_back(u);
            }            
        }

        void print_edges(){
            for(int i = 0; i < N; ++i){
                vector<int>::iterator iter;
                cout << "list[" << i << "] : ";
                for(iter = edge[i].begin(); iter != edge[i].end(); ++iter){
                    cout << *iter << " ";
                }
                cout << endl;
            }            
        }

        void print_vertex_info(){
            for(int i = 0; i < N; ++i){
                printf("---------------\n");
                printf("vertex %d: info\n", i);
                printf("f num: %d\n", vertex[i].f);
                printf("cc num: %d\n", vertex[i].cc);
            }
            printf("+++++++++++++++ f sort\n");
            for(int i = 0; i < N; ++i){
                printf("f num: %d\n", vertex[f_order[i]].f);
            }            
        }

        int get_index_cc(){
            return index_cc;
        }

        void transpose(vector<vector<int>> &Tedge){   // t(n) = O(V+E)
            for(int i = 0; i < N; ++i){
                vector<int>::iterator iter;
                for(iter = edge[i].begin(); iter != edge[i].end(); ++iter){
                    Tedge[*iter].push_back(i);
                }
            }
        }

        void DFS(){
            index_cc = 0;
            for(int i = 0; i < N; ++i){
                vertex[i].color = 0;
                vertex[i].pi = -1;
            }
            time_stmp = 0;
            for(int i = 0; i < N; ++i){
                if(vertex[i].color == 0){
                    DFS_visit(i, index_cc);
                    ++index_cc;
                }
            }
        }           

        void Strongly_CC(){
            DFS();
            DFS_T();
        }        

    private:
        int N;
        int index_cc;
        vector<int> *edge;
        vector<vtx> vertex;
        vector<int> f_order;

        void DFS_visit(int u, int ind_cc){
            ++time_stmp;
            vertex[u].color = 1;
            vertex[u].cc = ind_cc;
            vector<int>::iterator iter;
            for(iter = edge[u].begin(); iter != edge[u].end(); ++iter){
                if(vertex[*iter].color == 0){
                    vertex[*iter].pi = u;
                    vertex[*iter].cc = ind_cc;
                    DFS_visit(*iter, ind_cc);
                }
            }    
            vertex[u].color = 2;
            ++time_stmp;
            vertex[u].f = time_stmp;
            f_order.push_back(u); // a neater data structure for f_order is stack
        }

        void DFS_visit(int u, int ind_cc, vector<vector<int>> &Tedge){  // fuction overload for other edge relations
            ++time_stmp;
            vertex[u].color = 1;
            vertex[u].cc = ind_cc;
            vector<int>::iterator iter;
            for(iter = Tedge[u].begin(); iter != Tedge[u].end(); ++iter){
                if(vertex[*iter].color == 0){
                    vertex[*iter].pi = u;
                    vertex[*iter].cc = ind_cc;
                    DFS_visit(*iter, ind_cc, Tedge);
                }
            }    
            vertex[u].color = 2;
            ++time_stmp;
        }        

        void DFS_T(){
            index_cc = 0;
            vector<vector<int>> Tedge(N);
            transpose(Tedge);
            for(int i = 0; i < N; ++i){
                vertex[i].color = 0;
                vertex[i].pi = -1;
            }
            time_stmp = 0;
            for(int i = N-1; i >= 0 ; --i){
                if(vertex[f_order[i]].color == 0){
                    DFS_visit(f_order[i], index_cc, Tedge);
                    ++index_cc;
                }
            }
        } 

};

int main(){
    int N = 1, M = 1;
    vector<int> ans;
    cin >> N >> M;
    while(N != 0 && M != 0){
        graph G(N);
        vector<vector<int>> Tedge(N);
        for(int i = 0; i < M ; ++i){
            int u, v, e;
            cin >> u >> v >> e;
            G.set_edge(u-1, v-1, e);
        }

        G.Strongly_CC();
        if(G.get_index_cc() > 1){
            ans.push_back(0);
        }else{
            ans.push_back(1);
        }

        cin >> N >> M;
    }

    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << endl;
    }

    return 0;
}
