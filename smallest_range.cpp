#include<iostream>
#include<vector>
using namespace std;

class node{
    public:
        node(){
        }

        node(int a, int b){
            ind = a;
            key = b;
        }

        int ind;
        int key;
};

class heap{
    public:
        heap(vector<int> &vertex): hp(vertex.size()), size(vertex.size()){
            for(int i = 0; i < size; ++i){
                hp[i].ind = i;
                hp[i].key = vertex[i];
            }
            //cout << "size : " << size << endl;
            build_min_heap();
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
		        
                node temp(hp[i]);
		        hp[i] = hp[small-1];
                hp[small-1] = temp;

                min_heapify(small-1);
            }
        }

        void build_min_heap(){
            for(int ind = size/2; ind > 0; --ind){
		        min_heapify(ind-1);
	        }
        }

        int extract_min(){
            if(size < 1){
                //cout << "heap underflow\n";
                return -1;
            }else{
                //cout << "extract min\n";

                node min(hp[0]);
                hp[0] = hp[size-1];
            
                hp.pop_back();
                size = hp.size();
                //cout << "extract min start min heapify\n";
                min_heapify(0);
                return min.ind;
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

                node tmp(hp[parent-1]);
                hp[parent-1] = hp[i];
                hp[i] = tmp;

                i = parent-1;
                parent = (i+1)/2;
            }
        }

        void insert(int ind, int key){
            size = size + 1;
            hp.push_back(node(ind, 100000000));
            decrease_key(size-1, key);
        }

    private:
        vector<node> hp;
        int size;
	
};

void smallest_range(int K, vector<int> *lists, int &min, int &max){
    int ptr[K]; // points to the element current used in list k
    int max_ind = 0; // points to the list that holds the current max element
    int min_ind; // points to the list that holds the current max element
    vector<int> tmp(K);
    //initialize
    int tmp_max = -100000000;
    for(int i = 0; i < K; ++i){
        ptr[i] = 0;
        tmp[i] = lists[i][0];
        if(tmp_max < lists[i][0]){
            tmp_max = lists[i][0];
            max_ind = i;
        }
    }
    heap min_q(tmp);
    
    int min_range = 100000000;
    int r_upper_bnd, r_lower_bnd;
    min_ind = min_q.extract_min();
    while(ptr[min_ind] < lists[min_ind].size()){
        int range = lists[max_ind][ptr[max_ind]] - lists[min_ind][ptr[min_ind]];
        //printf("range = %d min_range = %d\n", range, min_range);
        if(range < min_range){
            min_range = range;

            r_upper_bnd = lists[max_ind][ptr[max_ind]];
            r_lower_bnd = lists[min_ind][ptr[min_ind]];
            if(min_range == 0){
                break;
            }
        }

        //printf("min_ind: %d, max_ind: %d\n", min_ind, max_ind);
        //printf("min: %d, max: %d\n", lists[min_ind][ptr[min_ind]], lists[max_ind][ptr[max_ind]]);
        if(ptr[min_ind] < lists[min_ind].size()-1){
            ptr[min_ind] = ptr[min_ind] + 1;
        }else{
            break;
        }
        min_q.insert(min_ind, lists[min_ind][ptr[min_ind]]);
        if(lists[min_ind][ptr[min_ind]] > lists[max_ind][ptr[max_ind]]){
            max_ind = min_ind;
        }
        
        min_ind = min_q.extract_min();
    }
    
    min = r_lower_bnd;
    max = r_upper_bnd;
    
}



int main(){
    int K;
    cin >> K;
    vector<int> *lists = new vector<int>[K];
    for(int i = 0; i < K; ++i){
        int N;
        cin >> N;
        for(int j = 0; j < N; ++j){
            int tmp;
            cin >> tmp;
            lists[i].push_back(tmp);
        }
    }
    int min, max;
    smallest_range(K, lists, min, max);
    cout << min << " " << max;
    delete[] lists;
    return 0;
}