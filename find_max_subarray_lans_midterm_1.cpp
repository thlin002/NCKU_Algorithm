#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

void find_max_crossing_subarray(vector<int>& seq, int low, int mid, int high, int* ans){
    int left_sum = -1000000000;
    int sum = 0;
    int max_left;
    for(int i = mid; i >= low; --i){
        sum = sum + seq[i];
        if(sum > left_sum){
            left_sum = sum;
            max_left = i;
        }
    }
    int right_sum = -1000000000;
    sum = 0;
    int max_right;
    for(int i = mid+1; i <= high; ++i){
        sum = sum + seq[i];
        if(sum > right_sum){
            right_sum = sum;
            max_right = i;
        }
    }
    ans[0] = max_left;
    ans[1] = max_right;
    ans[2] = left_sum + right_sum;
    //printf("%d %d %d\n", ans[2], ans[0], ans[1]);
}

void find_max_subarray(vector<int>& seq, int low, int high, int* ans){
    int ans_left[3];
    int ans_cross[3];
    int ans_right[3];
    if(high == low){
        ans[0] = low;
        ans[1] = high;
        ans[2] = seq[low];
        //printf("%d %d %d\n", ans[2], ans[0], ans[1]);
        return;
    }else{
        int mid = floor((low + high)/2);
        find_max_subarray(seq, low, mid, ans_left);
        find_max_subarray(seq, mid+1, high, ans_right);
        find_max_crossing_subarray(seq, low, mid, high, ans_cross);
    }
    if(ans_left[2] >= ans_right[2] && ans_left[2] >= ans_cross[2]){
        ans[0] = ans_left[0];
        ans[1] = ans_left[1];
        ans[2] = ans_left[2];
        //printf("left: %d %d %d\n", ans[2], ans[0], ans[1]);
    }else if(ans_right[2] >= ans_left[2] && ans_right[2] >= ans_cross[2]){
        ans[0] = ans_right[0];
        ans[1] = ans_right[1];
        ans[2] = ans_right[2];
        //printf("right: %d %d %d\n", ans[2], ans[0], ans[1]);
    }else{
        ans[0] = ans_cross[0];
        ans[1] = ans_cross[1];
        ans[2] = ans_cross[2];
        //printf("cross: %d %d %d\n", ans[2], ans[0], ans[1]);        
    }
    return;
}

int main(){
    int N;
    cin >> N;
    vector<int> seq(N);
    for(int i = 0; i < N; ++i){
        cin >> seq[i];
    }
    int ans[3];     // ans[0]: low , ans[1]: high , ans[2] : sum
    find_max_subarray(seq, 0, N-1, ans);
    printf("%d %d %d", ans[2], ans[0]+1, ans[1]+1);
}