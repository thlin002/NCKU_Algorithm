#include <stdio.h>
#include <iostream>

using namespace std;

int inv_count(int* A, int p, int r, int N){
	//printf("Verify checkpoint 1\n");
	if(p < r){
		int q = (p + r)/2;
		int left = inv_count(A, p, q, N);
		int right = inv_count(A, q+1, r, N);

		// Merging part
		int count = 0;
		int* temp = (int*)malloc(sizeof(int)*(r-p+1));
	
		int n = p;
		int m = q+1;
		int i = 0;
	
		while(n <= q && m <= r){
			if(A[n] <= A[m]){
				temp[i] = A[n];
				++n;
			}else{
				temp[i] = A[m];
				++m;
				count = (count + (q-n+1))%524287;
			}
			++i;
		}
/*
		cout << "XXXXXXXXXXXXXX p=" << p << " q=" << q << " r=" << r << endl;
		for(int i = 0; i < (r-p+1); ++i){
        	cout << temp[i] << " ";
    	}
		cout << endl;
*/
		while(n <= q){
			temp[i] = A[n];
			++i;
			++n;
		}
		
		while(m <= r){
			temp[i] = A[m];
			++i;
			++m;
		}

		for(int i = 0; i < (r-p+1); ++i){
			A[p+i] = temp[i];
		}
/*
		// for verifying
		cout << "#####" << endl;
		for(int i = 0; i < N; ++i){
        	cout << A[p+i] << " ";
    	}
		cout << endl;
		cout << "End Result: " << count << endl;
*/		
		count = count % 524287;
		free(temp);
		// Merging part ends 

		return ((left + right)%524287 + count) % 524287;
	}else{
		return 0;
	}
}

int main() {
	int N;
    cin >> N;
	int* series = (int*)malloc(sizeof(int)*N);
    for(int i = 0; i < N; ++i){
        cin >> series[i];
    }

	int result = (inv_count(series, 0, N-1, N)) % 524287;
	free(series);
	cout << result;
	return 0;
}
