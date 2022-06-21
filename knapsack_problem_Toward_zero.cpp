#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
/*
We caculate the sum of the input array, divide the sum by 2 and take it celing.
We can view this value as the max weight we want to fill in the knapsack,
by filling it to maximum with the some values in the array and see the remaining 
number to be negated.
We can thus balance this array toward zero.  
*/
int knapsack(vector<int> &arr, vector<vector<int>> &v, int i, int w){
	
	if(v[i][w] != -1){
		return v[i][w];
	}else{
		if(arr[i-1] > w){
			//cout << "arr[i]: " << arr[i] << " w: " << w << " arr[i] > w,  i-1: " << i-1 << endl; 
			v[i][w] = knapsack(arr, v, i-1, w);
		}else{
			//cout << "index "<< i-1 << ": " << arr[i-1] << endl;
			//cout << "weight :"<< w-arr[i-1] << endl;
			int a = knapsack(arr, v, i-1, w-arr[i-1]) + arr[i-1];
			int b = knapsack(arr, v, i-1, w);	
			if(a > b){
				v[i][w] = a;
				//cout << "a: " << a << endl;
			}else{
				v[i][w] = b;
				//cout << "b: " << b << endl;
			}				
		}
		return v[i][w];
	}
}

int main(){
	int N;
	cin >> N;
	vector<int> arr(N);
	
	int sum = 0;
	for(int i = 0; i < N; ++i){
		cin >> arr[i];
		sum += arr[i];
	}
	sort(arr.begin(), arr.end());
	/*
	for(int i = 0; i < N ; ++i){
		cout << arr[i] << " ";
	}
	cout << endl;
	*/
	vector<vector<int>> v(N+1, vector<int> (sum+1, -1));
	int i = 0;
	for(int j = 0; j <= sum; ++j ){
		v[i][j] = 0;		
	}
	int j = 0;
	for(int i = 1; i <= N; ++i ){
		v[i][j] = 0;
	}
	
	int a = knapsack(arr, v, N, round(sum/2.0));
	/*
	for(int i = 0; i <= N; ++i){
		for(int j = 0; j <= sum; ++j){
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	*/
	//cout << a << endl;
	int result = 2*a - sum;
	if(result > 0){
		cout << result;
	}else{
		cout << -1*result;
	}
	return 0;
}
