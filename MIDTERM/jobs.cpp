#include<iostream>
#include<vector>
using namespace std;

struct activity{
    int start;
    int finish;
};

void heapify(vector<struct activity>& a, int i, int N){
    int left = 2*i;
    int right = 2*i+1;
    int large = i;
    if(left<=N && a[left-1].finish > a[i-1].finish){
        large = left;
    }
    if(right<=N && a[right-1].finish > a[large-1].finish){
        large = right;
    }
    if(large != i){
        struct activity temp = a[i-1];
		a[i-1] = a[large-1];
        a[large-1] = temp;
		heapify(a, large, N);
    }
}

int heap_sort(vector<struct activity>& heap, int N){
    int heap_size = N;
    for(int i = N; i >= 2; --i){
        struct activity temp = heap[0];
		heap[0] = heap[i-1];
        heap[i-1] = temp;
        --heap_size;
		heapify(heap, 1, heap_size); 
    }
    return 0;
}


int main(){
    int T;
    int N;
    cin >> T;
    vector<int> count(T,1);
    for(int k = 0; k < T; ++k){
        cin >> N;
        vector<struct activity> act(N);
        int ind = 0;
        for(int i = 0; i < N; ++i){
            cin >> act[i].start >> act[i].finish;
        }
        for(int i = N/2; i > 0; --i){
            heapify(act, i, N);
        }
        heap_sort(act, N);
        for(int i = 1; i < N; ++i){
            if(act[i].start >= act[ind].finish){
                count[k]++;
                ind = i;
            }
        }
    }
    for(int k = 0; k < T; ++k){
        cout << count[k] << endl;
    }
	return 0;
}
