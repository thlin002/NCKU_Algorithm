#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

class ctail{
    public:
    int juice, syrup, base;
    float con;
    string name;
    };

void swap(vector<ctail> &arr, int a, int b){
    int t_j, t_s, t_b;
    float t_c;
    string t_n;
    t_j = arr[a].juice;
    t_s = arr[a].syrup;
    t_b = arr[a].base;
    t_c = arr[a].con;
    t_n = arr[a].name;
    arr[a].juice = arr[b].juice;
    arr[a].syrup = arr[b].syrup;
    arr[a].base = arr[b].base;
    arr[a].con = arr[b].con;
    arr[a].name = arr[b].name;
    arr[b].juice = t_j;
    arr[b].syrup = t_s;
    arr[b].base = t_b;
    arr[b].con = t_c;
    arr[b].name = t_n;
} 

int partition(vector<ctail> &arr, int p, int r)
{
    if((r-p) > 0){
        int random = p + rand() % (r-p);
        swap(arr, random, r);
    }
    int i = p;
    for(int j = p; j < r; ++j){
        //cout << arr[j].base << " " << arr[r].base << endl;
        if(arr[j].con > arr[r].con){
            //cout << "swap" << endl;
            swap(arr, i, j);
            ++i;
        }
    }
    swap(arr, i, r);

    return i;
}

string kthBiggest(vector<ctail> &arr, int p, int r, int k)
{
    int q = partition(arr, p, r);

    //cout << q << endl;
    int index = q-p;
    if(index == k-1){
        //cout << "q == k" << endl;
        return arr[q].name;
    }else if(index > k-1){
        //cout << "q > k" << endl;
        return kthBiggest(arr, p, q-1, k);
    }else{
        //cout << "q < K" << endl;
        return kthBiggest(arr, q+1, r, k-(index+1)); // k-(q+1-p)
    }
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(NULL));
    int N, K;
    cin >> N >> K;

    vector<ctail> list(N);
    for(int i = 0; i < N; ++i){
        cin >> list[i].juice >> list[i].syrup >> list[i].base >> list[i].name;
        list[i].con = list[i].base / (float)(list[i].juice + list[i].syrup + list[i].base);
    }
    /*
    for(int i = 0; i < N; ++i){
        cout << list[i].juice << list[i].syrup << list[i].base << list[i].name << list[i].con << endl;
    }
    */
    cout << kthBiggest(list, 0, N - 1, K);
    /*
    cout << endl;
    for(int i = 0; i < N; ++i){
        cout << list[i].juice << " " << list[i].syrup << " " << list[i].base << " " << list[i].name << " " << list[i].con << endl;
    }
    */
    return 0;
} 