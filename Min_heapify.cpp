#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int>& a, int i, int N){
    int left = 2*i;
    int right = 2*i+1;
    int small = i;
    if(left<=N && a[left-1] < a[i-1]){
        small = left;
    }
    if(right<=N && a[right-1] < a[small-1]){
        small = right;
    }
    if(small != i){
        int temp = a[i-1];
		a[i-1] = a[small-1];
        a[small-1] = temp;
		heapify(a, small, N);
    }
}


int main(){
	int N;
	cin >> N;
	vector<int> heap(N);

	for(int i = 0; i < N; ++i){
        cin >> heap[i];
	}
	for(int i = heap.size()/2; i > 0; --i){
		heapify(heap, i, N);
	}



	for(int i = 0; i < N; ++i){
		cout << heap[i] << " ";
	}

	return 0;
}
