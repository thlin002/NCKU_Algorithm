#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int N;
	cin >> N;
	vector<int> a(N);
	for(int i = 0; i < N; ++i){
		cin >> a[i];
	}

	if(N == 1){
		cout << 0;
		return 0;
	}

    sort(a.begin(), a.end());
/*
	for(int i = 0; i < N; ++i){
		cout << ap[i];
	}
*/
	int large = 0;
	for(int i = 0; i < N-1; ++i){
		if(large < a[i+1] - a[i]){
			large = a[i+1] - a[i];
		}
	}
	cout << large;
	return 0;
}
