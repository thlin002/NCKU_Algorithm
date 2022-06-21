#include<iostream>
#include<vector>
#include<array>
#include<stdlib.h>
using namespace std;

const int inf = -100;

class vtx{
    public:
        vtx(){   
        }        
        
        vtx(int i, int a, int b, bool c){   
            index = i;          // in heap's member data hp, index points to the node number. 
                                //in graph member data vertex, index points to the corresponding heap element
            key = a;
            parent = b;
            in_Q = c;
        }

        int index;
        int key;
        int parent;
        bool in_Q;
};

class heap{
    public:
        heap(vector<vtx> &vertex): hp(vertex){
            vp = &vertex;
            size = hp.size();
            //cout << "size : " << size << endl;
            build_max_heap();
        }

        int get_size(){
            return size;
        }

        void max_heapify(int i){
            //printf("min heapilfy i = %d\n", i);
            int ind = i+1;
            int large = ind;
            int left = 2*(ind);
            int right = 2*(ind)+1;
            //printf("left child hp[%d].key = %d, ind hp[%d].key = %d\n", left-1, hp[left-1].key, small-1, hp[small-1].key);
            if(left<=size && hp[left-1].key > hp[large-1].key){
                large = left;
                //printf("change smallest from %d to left %d\n", small, left);
            }
            //printf("right child hp[%d].key = %d, ind hp[%d].key = %d\n", right-1, hp[right-1].key, small-1, hp[small-1].key);
            if(right<=size && hp[right-1].key > hp[large-1].key){
                large = right;
                //printf("change smallest from %d to left %d\n", small, left);
            }
            if(large != ind){
                // record the position change
                //cout << "min heapilfy change position\n";
                //printf("vertex %d index %d to ", hp[small-1].index, (*vp)[hp[small-1].index].index);
                (*vp)[hp[large-1].index].index = i;
                //printf("vertex %d index %d\n", hp[small-1].index, (*vp)[hp[small-1].index].index);
                //printf("vertex %d index %d to ", hp[i].index, (*vp)[hp[i].index].index);
                (*vp)[hp[i].index].index = large-1;
                //printf("vertex %d index %d\n", hp[i].index, (*vp)[hp[i].index].index);
		        

                vtx temp(hp[i]);
		        hp[i] = hp[large-1];
                hp[large-1] = temp;

                max_heapify(large-1);
            }
        }

        void build_max_heap(){
            for(int ind = size/2; ind > 0; --ind){
		        max_heapify(ind-1);
	        }
        }

        vtx extract_max(){
            if(size < 1){
                //cout << "heap underflow\n";
                return vtx(-1, -1, -1, -1);
            }else{
                //cout << "extract min\n";
                // record the position change
                (*vp)[hp[size-1].index].index = 0;
                (*vp)[hp[0].index].index = -1; // -1 represents that the vertex no longer exists in the heap

                vtx max(hp[0]);
                hp[0] = hp[size-1];
            
                hp.pop_back();
                size = hp.size();
                //cout << "extract min start min heapify\n";
                max_heapify(0);
                return max;
            }
        }

        
        void increase_key(int i, int key){
            if(key < hp[i].key){
                //cout << "new key is larger than current key";
            }
            hp[i].key = key;
            //printf("vertex %d, assign key = %d\n", hp[i].index, hp[i].key);
            int parent = (i+1)/2;
            while(hp[parent-1].key < hp[i].key && i > 0){
                //printf("before vertex %d index: %d\n", hp[i].index, (*vp)[hp[i].index].index);
                //printf("before vertex %d index: %d\n", hp[parent-1].index, (*vp)[hp[parent-1].index].index);
                // record the position change
                (*vp)[hp[i].index].index = parent-1;
                (*vp)[hp[parent-1].index].index = i;
                //printf("after vertex %d index: %d\n", hp[i].index, (*vp)[hp[i].index].index);
                //printf("after vertex %d index: %d\n", hp[parent-1].index, (*vp)[hp[parent-1].index].index);

                vtx tmp(hp[parent-1]);
                hp[parent-1] = hp[i];
                hp[i] = tmp;

                i = parent-1;
                parent = (i+1)/2;
            }
        }
        


    private:
        vector<vtx> hp;
        vector<vtx> *vp;
        int size;
	
};

class graph{
    public:
        graph(int n): N(n), vertex(n), w_edge(n, vector<int>(n, -1)){
            for(int i = 0; i < N; ++i){
                vertex[i] = vtx(i, inf, -1, 1);
                for(int j = 0; j < N; ++j){
                    w_edge[i][j] = inf;
                }                
            }
        }

        void set_wEdges(int a, int b,int k){
            w_edge[a][b] = k;
            w_edge[b][a] = k;
        }

        void print_edges(){
            for(int i = 0; i < N; ++i){
                for(int j = 0; j < N; ++j){
                    printf("%*d", 5, w_edge[i][j]);
                }
                cout << endl;
            }
        }

        void print_vertices(){
            for(int i = 0; i < N; ++i){
                printf("vertex %d, index %d, key %d, parent %d, in_Q %d\n", i, vertex[i].index, vertex[i].key, vertex[i].parent, vertex[i].in_Q);
            }
        }

        int MST_Prim(){
            vertex[0].key = 0;  // select vertex[0] as the arbitrary root
            //printf("=======================before build min heap\n");
            //print_vertices();
            //printf("=======================\n");            
            heap H(vertex);
            int cost = 0;

            while(H.get_size() > 0){
                //printf("=======================before extract min\n");
                //print_vertices();
                //printf("=======================\n");                
                vtx u( H.extract_max() );
                vertex[u.index].in_Q = 0;     // it is not in Queue anymore
                cost = cost + u.key;
                //cout << "extract vertex: " << u.index << " key: " << u.key << endl;
                for(int i = 0; i < N; ++i){
                    if(w_edge[u.index][i] >= 0 && w_edge[u.index][i] > vertex[i].key && vertex[i].in_Q == 1){
                        //printf("=======================before decrease key\n");
                        //print_vertices();
                        //printf("=======================\n");

                        vertex[i].parent = u.index;
                        vertex[i].key = w_edge[u.index][i];
                        H.increase_key(vertex[i].index, w_edge[u.index][i]);
                    }
                }
            }
            
            return cost;
        }

    private:
        int N;
        vector<vtx> vertex;
        vector<vector<int>> w_edge;

};

int main(){
    int N, M;
    cin >> N >> M;
    graph G(N);
    int u, v, w;
    for(int i = 0; i < M; ++i){
        cin >> u >> v >> w;
        G.set_wEdges(u, v, w);
    }
    //G.print_edges();
    cout << G.MST_Prim();

}