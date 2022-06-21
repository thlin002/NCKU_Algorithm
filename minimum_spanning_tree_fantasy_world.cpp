#include<iostream>
#include<vector>
#include<array>
using namespace std;


const int inf = 100000000;

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

        void min_heapify(int i){
            //printf("min heapilfy i = %d\n", i);
            int ind = i+1;
            int small = ind;
            int left = 2*(ind);
            int right = 2*(ind)+1;
            //printf("left child hp[%d].key = %d, ind hp[%d].key = %d\n", left-1, hp[left-1].key, small-1, hp[small-1].key);
            if(left<=size && hp[left-1].key < hp[small-1].key){
                small = left;
                //printf("change smallest from %d to left %d\n", small, left);
            }
            //printf("right child hp[%d].key = %d, ind hp[%d].key = %d\n", right-1, hp[right-1].key, small-1, hp[small-1].key);
            if(right<=size && hp[right-1].key < hp[small-1].key){
                small = right;
                //printf("change smallest from %d to left %d\n", small, left);
            }
            if(small != ind){
                // record the position change
                //cout << "min heapilfy change position\n";
                //printf("vertex %d index %d to ", hp[small-1].index, (*vp)[hp[small-1].index].index);
                (*vp)[hp[small-1].index].index = i;
                //printf("vertex %d index %d\n", hp[small-1].index, (*vp)[hp[small-1].index].index);
                //printf("vertex %d index %d to ", hp[i].index, (*vp)[hp[i].index].index);
                (*vp)[hp[i].index].index = small-1;
                //printf("vertex %d index %d\n", hp[i].index, (*vp)[hp[i].index].index);
		        

                vtx temp(hp[i]);
		        hp[i] = hp[small-1];
                hp[small-1] = temp;

                min_heapify(small-1);
            }
        }

        void build_max_heap(){
            for(int ind = size/2; ind > 0; --ind){
		        min_heapify(ind-1);
	        }
        }

        vtx extract_min(){
            if(size < 1){
                //cout << "heap underflow\n";
                return vtx(-1, -1, -1, -1);
            }else{
                //cout << "extract min\n";
                // record the position change
                (*vp)[hp[size-1].index].index = 0;
                (*vp)[hp[0].index].index = -1; // -1 represents that the vertex no longer exists in the heap

                vtx min(hp[0]);
                hp[0] = hp[size-1];
            
                hp.pop_back();
                size = hp.size();
                //cout << "extract min start min heapify\n";
                min_heapify(0);
                return min;
            }
        }

        
        void decrease_key(int i, int key){
            if(key > hp[i].key){
                //cout << "new key is larger than current key";
            }
            hp[i].key = key;
            //printf("vertex %d, assign key = %d\n", hp[i].index, hp[i].key);
            int parent = (i+1)/2;
            while(hp[parent-1].key > hp[i].key && i > 0){
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
                vtx u( H.extract_min() );
                vertex[u.index].in_Q = 0;     // it is not in Queue anymore
                cost = cost + u.key;
                //cout << "extract vertex: " << u.index << " key: " << u.key << endl;
                for(int i = 0; i < N; ++i){
                    if(w_edge[u.index][i] >= 0 && w_edge[u.index][i] < vertex[i].key && vertex[i].in_Q == 1){
                        //printf("=======================before decrease key\n");
                        //print_vertices();
                        //printf("=======================\n");

                        vertex[i].parent = u.index;
                        vertex[i].key = w_edge[u.index][i];
                        H.decrease_key(vertex[i].index, w_edge[u.index][i]);
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

int dist(array<char, 7> &a, array<char, 7> &b){
    int d = 0;
    int size = a.size();
    for(int i = 0; i < size; ++i){
        if(a[i] != b[i]){
            ++d;
        }
    }
    return d;
}

int main(){
    int N;
    cin >> N;
    vector<array<char, 7>> input(N);

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < 7; ++j){
            cin >> input[i][j];
        }
    }
    int input_done = 1;
    cin >> input_done;

    graph G(N);
    for(int i = 1; i < N; ++i){
        for(int j = 0; j < i; ++j){
            int tmp = dist(input[i], input[j]);
            G.set_wEdges(i, j, tmp);
        }
    }    
    //G.print_edges();
    printf("The highest possible quality is 1/%d.",G.MST_Prim());

    return 0;
}