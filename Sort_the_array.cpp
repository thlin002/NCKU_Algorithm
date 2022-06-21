#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
	int N;
    cin >> N;
    vector<int> nums(N);
    for(int i = 0; i < N; ++i){
        cin >> nums[i];
    }
    make_heap(nums.begin(), nums.end());
    sort_heap(nums.begin(), nums.end());
    for(int i = 0; i < N; ++i){
        cout << nums[i] << " ";
    }


    return 0;
}
