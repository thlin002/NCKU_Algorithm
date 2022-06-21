#include <iostream>
using namespace std;

int combination(int a[], int temp[], int N, int iter, int ind){
    if(ind > 5){
        for(int i = 0; i < 6; ++i){
            cout << temp[i];
            if(i < 5){
                cout << ' ';
            }
        }
        cout << endl;
        return 0;
    }else if(iter >= N){
        return 0;
    }else{
        int new_temp[6];
        for(int i = 0; i < ind; ++i){
            new_temp[i] = temp[i]; 
        }
        new_temp[ind] = a[iter];
        combination(a, new_temp, N, iter+1, ind+1);
        combination(a, new_temp, N, iter+1, ind);
        return 0;
    }
}


int main(){
    int N;
    cin >> N;
    int* array = (int*)malloc(sizeof(int)*N);
    for(int i = 0; i < N; ++i){
        cin >> array[i];
    }
    int temp[6];
    combination(array, temp, N, 0, 0);

    return 0;
}
