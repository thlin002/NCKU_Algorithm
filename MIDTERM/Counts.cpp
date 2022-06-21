#include<iostream>
#include<vector>
using namespace std;

int main(){
	int N;
	cin >> N;
	vector<int> arr(N);
	/*
	after input i'll + 10000
	*/
	vector<int> ans(N,0);
	for(int i = 0; i < N; ++i){
		cin >>  arr[i];
	}
	for(int i = N-2; i >= 0; --i){
		int j = i+1;
		while(arr[i] <=arr[j] && j < N){
			j++;
		}
		if(j < N){
			ans[i] = 1 + ans[j];
		}else{
			ans[i] = 0;
		}
	}
	for(int i = 0; i < N; ++i){
		cout << ans[i] << " ";
	}

	return 0;
}
