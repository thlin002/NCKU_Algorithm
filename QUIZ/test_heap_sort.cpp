#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> arr(N);
    for(int i = 0; i < N; ++i){
        cin >> arr[i];
    }
    make_heap(arr.begin(), arr.end());
    for(int i = 0; i < N; ++i){
        cout << arr[i];
        if(i == N-1){
            break;
        }
        cout << " ";
    }
    cout << endl;
    sort_heap(arr.begin(), arr.end());
    for(int i = 0; i < N; ++i){
        cout << arr[i];
        if(i == N-1){
            break;
        }
        cout << " ";        
    }
    return 0;
}
