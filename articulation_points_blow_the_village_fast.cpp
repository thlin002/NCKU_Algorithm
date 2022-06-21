#include<iostream>
#include<list>
#include<vector>
using namespace std;

int time_stmp = 0;
int bcc_index = 0;

typedef struct v{
    int index;
    int color; // 0: white, 1: grey, 2: black
    int pi; // ancestor, -1: no ancestor
    int d;
    int low;
    int isAP;
    int importance;
} vtx;

class eStack{
    public:
        eStack(int n, int m){
            u = n;
            v = m;
        }
        int u;
        int v;
};

void count_sort(vector<vtx>& A, vector<vtx>& B, int N, int l, int mode){
    vector<int> cnt(N, 0);
    if(mode == 0){
        for(int i = 0; i < l; ++i){
            ++cnt[A[i].importance];
        }
        for(int i = 1; i < N; ++i){
            cnt[i] = cnt[i] + cnt[i-1]; 
        }
        for(int i = 0; i < l; ++i){
            B[cnt[A[i].importance]-1] = A[i];
            --cnt[A[i].importance];
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
            edge[v].push_back(u);
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

        void articulation_point(int M){
            for(int i = 0; i < N; ++i){
                vertex[i].index = i;
                vertex[i].color = 0;
                vertex[i].isAP = 0;
                vertex[i].pi = -1;
                vertex[i].importance = 1;
            }
            time_stmp = 0;
            bcc_index = 0;
            for(int u = 0; u < N; ++u){
                if(vertex[u].color == 0){
                    Articulation_visit(u);
                }
            }


            // output format
            vector<vtx> sorted(N);

            count_sort(vertex, sorted, N+1, N, 0);
            int k = 0;
            for(int i = N-1; i >= 0 ; --i){
                if(k < M){
                    cout << sorted[i].index << " " << sorted[i].importance << endl;
                    ++k;
                }
            }

        }           

    private:
        int N;
        vector<int> *edge;
        vector<vtx> vertex;
        int count;

        void Articulation_visit(int u){
            ++time_stmp;
            int children = 0;
            vertex[u].color = 1;
            vertex[u].d = time_stmp;
            vertex[u].low = time_stmp;
            for(int i = 0; i < edge[u].size(); ++i){
                int v = edge[u][i];
                if(vertex[v].color == 0){
                    ++children; // only those not visited is counted as children to avoid loops.
                    vertex[v].pi = u;

                    Articulation_visit(v);
                    
                    // take min 
                    if(vertex[u].low > vertex[v].low){
                        vertex[u].low = vertex[v].low;
                    }

                    if(vertex[u].pi != -1 && vertex[v].low >= vertex[u].d){    // if chidren's low >= u's d, then it doesn't form a loop
                        vertex[u].isAP = 1;
                        
                    }

                    // since we have to increment the importance of the root for each of its children;
                    if((vertex[u].pi == -1 && children > 1) || (vertex[u].pi != -1 && vertex[v].low >= vertex[u].d) ){
                        ++vertex[u].importance;
                    }
                }else if(v != vertex[u].pi){   // when encounter an ancester in the children
                    // take min
                    if(vertex[u].low > vertex[v].d){
                        vertex[u].low = vertex[v].d;
                        
                    }
                }
            }
            
            if(vertex[u].pi == -1 && children > 1){
                vertex[u].isAP = 1;   
            }
        }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);    
    int N, M, u, v;
    cin >> N >> M;
    graph G(N);
    cin >> u >> v;
    while(u != -1 && v != -1){
        G.set_edge(u, v);
        cin >> u >> v;
    }
    G.articulation_point(M);
    
    //cout << "*********************\n";
    //G.print_edges();

    return 0;
}
