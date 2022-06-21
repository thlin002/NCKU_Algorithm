#include<iostream>
#include<vector>
#include<stack>
#include<array>
using namespace std;

class graph{
    public:
        graph(int n): N(n){
            edge = new vector<short int>[n];
            color = new bool[n];            
        }

        ~graph(){
            delete[] edge;
            delete[] color;
        }

        void set_edge(short int u, short int v, short int e){
            edge[u].push_back(v);
            if(e == 2){
                edge[v].push_back(u);
            }            
        }

        void set_T_edge(short int u, short int v, short int e){
            edge[v].push_back(u);
            if(e == 2){
                edge[u].push_back(v);
            }            
        }

        void clear_edge(){
            for(int i = 0; i < N; ++i){
                edge[i].clear();
            }
        }

        int get_index_cc(){
            return index_cc;
        }

        void print_edges(){
            for(int i = 0; i < N; ++i){
                vector<short int>::iterator iter;
                cout << "list[" << i << "] : ";
                for(iter = edge[i].begin(); iter != edge[i].end(); ++iter){
                    cout << *iter << " ";
                }
                cout << endl;
            }            
        }

        void DFS_fill_stack(){
            for(int i = 0; i < N; ++i){
                color[i] = 0;
            }
            for(int i = 0; i < N; ++i){
                if(color[i] == 0){
                    DFS_visit_fill_stack(i);
                }
            }
        }

        void DFS_cc(){
            for(int i = 0; i < N; ++i){
                color[i] = 0;
            }            
            index_cc = 0;
            while(f_stack.empty() != 1){
                short int v = f_stack.top();
                f_stack.pop();
                if(color[v] == 0){
                    DFS_visit(v);
                    ++index_cc;
                }
            }
        }      

    private:
        short int N;
        short int index_cc;
        vector<short int> *edge;
        stack<short int> f_stack;
        bool *color;

        void DFS_visit_fill_stack(short int u){
            color[u] = 1;
            vector<short int>::iterator iter;
            for(iter = edge[u].begin(); iter != edge[u].end(); ++iter){
                if(color[*iter] == 0){
                    DFS_visit_fill_stack(*iter);
                }
            }    
            f_stack.push(u); 
        }

        void DFS_visit(short int u){ 
            color[u] = 1;
            vector<short int>::iterator iter;
            for(iter = edge[u].begin(); iter != edge[u].end(); ++iter){
                if(color[*iter] == 0){
                    DFS_visit(*iter);
                }
            }    
        }        

};

int main(){
    int N, M;

    cin >> N >> M;
    while(N != 0 && M != 0){
        graph G(N);
        vector<array<short int, 3>> arr(M); 
        for(int i = 0; i < M ; ++i){
            cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
            G.set_edge(arr[i][0]-1, arr[i][1]-1, arr[i][2]);
        }
        //cout << "edge created\n";

        G.DFS_fill_stack();
        //cout << "stack filled\n";

        G.clear_edge();
        //cout << "edge cleared\n";

        for(int i = 0; i < M ; ++i){
            G.set_T_edge(arr[i][0]-1, arr[i][1]-1, arr[i][2]);
        }
        
        //G.print_edges();
        
        G.DFS_cc();

        if(G.get_index_cc() > 1){
            cout << 0 << endl;
        }else{
            cout << 1 << endl;
        }

        cin >> N >> M;
    }
    return 0;
}
