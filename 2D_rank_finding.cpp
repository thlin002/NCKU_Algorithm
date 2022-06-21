#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class point{
    public:
        int ind;    // indicates the position in the unsorted input (for printing the answer)
        long long int x;
        long long int y;
        int r;
};

int cmp(point a, point b){
    // if x value equals, then compare y values
    if(a.x == b.x){
        return (a.y < b.y);
    }
    return (a.x < b.x);
}

int cmp_y(point a, point b){
    return a.y < b.y;
}

int cmp_restore(point a, point b){
    return (a.ind < b.ind);
}

void two_d_rank_merge(vector<point> &arr ,int low, int mid, int high){
    int width = high-low+1;
    vector<point> tmp(width);
    for(int i = 0; i < width; ++i){
        tmp[i].ind = i+low;
        tmp[i].x = arr[i+low].x;
        tmp[i].y = arr[i+low].y;
        tmp[i].r = arr[i+low].r;
    }
    stable_sort(tmp.begin(), tmp.end(), cmp_y);     // stable to keep the right side on the right if y value is the same

    int update_cnt = 0; // the base of r for low to mid
    int first_flag = 0;
    for(int i = 0; i < width; ++i){
        if(tmp[i].ind <= high && tmp[i].ind >= mid+1){
            arr[tmp[i].ind].r = arr[tmp[i].ind].r + update_cnt;
        }else{
            if(first_flag == 0){
                update_cnt = tmp[i].r;
                first_flag = 1;
            }
            ++update_cnt;
        }
    }
    
}

void two_d_rank_finding(vector<point> &arr ,int low, int high){
    if(low < high){
        int mid = (low+high)/2;
        two_d_rank_finding(arr, low, mid);
        two_d_rank_finding(arr, mid+1, high);
        two_d_rank_merge(arr, low, mid, high);
    }
}

int main(){
    int n;
    cin >> n;
    vector<point> array(n);
    for(int i = 0; i < n; ++i){
        cin >> array[i].x >> array[i].y;
        array[i].ind = i;
        array[i].r = 0; // initailize rank to zero
    }

    sort(array.begin(), array.end(), cmp);

    two_d_rank_finding(array, 0, n-1);

    sort(array.begin(), array.end(), cmp_restore);
    for(int i = 0; i < n; ++i){
        cout << array[i].r << " ";
    }
    
    return 0;
}