#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class graph{
    public:
        graph(int n): N(n){
            edge = new vector<short int>[n];
        }

        ~graph(){
            delete[] edge;
        }

        void set_edge(short int u, short int v, short int e){
            edge[u].push_back(v);
            if(e == 2){
                edge[v].push_back(u);
            }            
        }

        int get_index_cc(){
            return index_cc;
        }

        graph transpose(){   // t(n) = O(V+E)
            graph G(N);
            for(int i = 0; i < N; ++i){
                vector<short int>::iterator iter;
                for(iter = edge[i].begin(); iter != edge[i].end(); ++iter){
                    G.edge[*iter].push_back(i);
                }
            }
            return G;
        }
        
        void DFS_fill_stack(stack<short int> &f_stack, bool *color){
            for(int i = 0; i < N; ++i){
                if(color[i] == 0){
                    DFS_visit_fill_stack(i, color, f_stack);
                }
            }
        }

        void DFS_cc(stack<short int> &f_stack, bool *color){
            index_cc = 0;
            while(f_stack.empty() != 1){
                short int v = f_stack.top();
                f_stack.pop();
                if(color[v] == 0){
                    DFS_visit(v, color);
                    ++index_cc;
                }
            }
        }                    

        int Strongly_CC(){
            stack<short int> f_stack;

            bool *color = new bool[N];
            for(int i = 0; i < N; ++i){
                color[i] = 0;
            }            
            DFS_fill_stack(f_stack, color);

            graph G_T = transpose();

            for(int i = 0; i < N; ++i){
                color[i] = 0;
            } 
            G_T.DFS_cc(f_stack, color);

            delete[] color;

            return G_T.get_index_cc();
        }        

    private:
        short int N;
        short int index_cc;
        vector<short int> *edge;

        void DFS_visit_fill_stack(short int u, bool *color, stack<short int> &f_stack){
            color[u] = 1;
            vector<short int>::iterator iter;
            for(iter = edge[u].begin(); iter != edge[u].end(); ++iter){
                if(color[*iter] == 0){
                    DFS_visit_fill_stack(*iter, color, f_stack);
                }
            }    
            f_stack.push(u); 
        }

        void DFS_visit(short int u, bool *color){ 
            color[u] = 1;
            vector<short int>::iterator iter;
            for(iter = edge[u].begin(); iter != edge[u].end(); ++iter){
                if(color[*iter] == 0){
                    DFS_visit(*iter, color);
                }
            }    
        }        

};

int main(){
    int N, M;

    cin >> N >> M;
    while(N != 0 && M != 0){
        graph G(N);
        for(int i = 0; i < M ; ++i){
            short int u, v, e;
            cin >> u >> v >> e;
            G.set_edge(u-1, v-1, e);
        }

        if(G.Strongly_CC() > 1){
            cout << 0 << endl;
        }else{
            cout << 1 << endl;
        }

        cin >> N >> M;
    }
    return 0;
}
