#include<iostream>
#include<vector>
#include<stack>
#include <algorithm>
using namespace std;

// ctrl+d signals the end of the input;

int time_stmp = 0;

typedef struct v{
    int index;
    bool color; // 0: white, 1: grey, 2: black
    int f;
} vtx;

bool compare_vtx(vtx a, vtx b){
    return a.f > b.f;
}

void count_sort(vector<int>& A, vector<int>& B, int N, int l){    // N the value range 0~N, l the number of elements 
    vector<int> cnt(N, 0);
    for(int i = 0; i < l; ++i){
        ++cnt[A[i]];
    }
    for(int i = 1; i < N; ++i){
        cnt[i] = cnt[i] + cnt[i-1]; 
    }
    for(int i = 0; i < l; ++i){
        B[cnt[A[i]]-1] = A[i];
        --cnt[A[i]];
    }
}


void count_sort(vector<vtx>& A, vector<vtx>& B, int N, int l, int mode){    // N the value range 0~N, l the number of elements 
    vector<int> cnt(N, 0);
    if(mode == 0){
        for(int i = 0; i < l; ++i){
            ++cnt[A[i].index];
        }
        for(int i = 1; i < N; ++i){
            cnt[i] = cnt[i] + cnt[i-1]; 
        }
        for(int i = 0; i < l; ++i){
            B[cnt[A[i].index]-1] = A[i];
            --cnt[A[i].index];
        }
    } else if(mode == 1){
        for(int i = 0; i < l; ++i){
            ++cnt[A[i].f];
        }
        for(int i = 1; i < N; ++i){
            cnt[i] = cnt[i] + cnt[i-1]; 
        }
        for(int i = 0; i < l; ++i){
            B[cnt[A[i].f]-1] = A[i];
            --cnt[A[i].f];
        }
    }
}

class graph{
    public:
        graph(int n): vertex(n), N(n){
            edge = new vector<int>[n];
        }

        ~graph(){
            delete[] edge;
        }

        void set_edge(int u, int v){
            edge[u].push_back(v);
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
            }
        }        

        void sort_edges(){  // sort adjacent list by node number from small to large
            for(int i = 0; i < N; ++i){
                vector<int> tmp(edge[i]);
                count_sort(tmp, edge[i], N, edge[i].size());
            } 
        }

        void topological_sort(){
            for(int i = 0; i < N; ++i){
                vertex[i].index = i;
                vertex[i].color = 0;
            }            
            DFS();
            print_topo_sort();

        }
        
        void DFS(){
            time_stmp = 0;
            for(int i = 0; i < N; ++i){
                if(vertex[i].color == 0){
                    DFS_visit(i);
                }
            }
        }


    private:
        int N;
        vector<int> *edge;
        vector<vtx> vertex;
        vector<vtx> f_stack;


        void print_topo_sort(){
            vector<vtx>::iterator iter;
            for(iter = f_stack.begin(); iter != f_stack.end(); ++iter){
                cout << (*iter).index + 1 << " ";
            }
            cout << endl;
        }

        void DFS_visit(short int u){
            vertex[u].color = 1;
            vector<int>::iterator iter;
            for(iter = edge[u].begin(); iter != edge[u].end(); ++iter){
                if(vertex[*iter].color == 0){
                    DFS_visit(*iter);
                }
            }    
            ++time_stmp;
            vertex[u].f = time_stmp;
            f_stack.insert(f_stack.begin(), vertex[u]);
        }

};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, u, v;
    
    while(cin >> N){   
        graph G(N);
        cin >> M;
        for(int i = 0; i < M; ++i){
            cin >> u >> v;
            G.set_edge(u-1, v-1);
        }
        G.print_edges();
        cout << "after edges are sorted\n"; 
        G.sort_edges();
        G.print_edges();
        G.topological_sort();
    }

    return 0;
}
