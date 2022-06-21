#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int compare_str4(char a[], string b){
	int v = 1;
	for(int i = 0; i < 4; ++i){
		if(a[i] != b[i]){
			v = 0;
		}
	}
	return v;
}

void find(int a[][1000], int t, int N, int end[], int r[]){
	for(int i = 0; i < N; ++i){
		int j = 0;
		while(j <= end[i]){
			if(a[i][j] == t){
				// record the target coordinate
				r[0] = i;
				r[1] = j;
				//cout << "find " << r[0] << " " << r[1] << endl; 
			}
			++j;
			//printf("%d %d\n", i , j);
		}
	}
}

void restore(int a[][1000], int t[], int N, int end[]){
	int i = t[1]+1;
	int slot = t[0];
	while(i <= end[slot]){
		int num = a[slot][i];
		
		// find the end of the slot, num-1 since there is a matching difference
		int j = 0;
		while(j <= end[num-1]){
			++j;
		}
		// insert the blk
		a[num-1][j] = a[slot][i];
		end[num-1] = j;
		
		++i;				
	}
	// mark the end of the slot
	end[slot] = t[1];
}

void insert(int a[][1000], int obj[], int t, int N, int end[]){

	// copy the obj array elements to tmp array 
	int i = 0;
	int tmp[1000];
	int end_tmp = 0;
	while( (obj[1]+i) <= end[obj[0]]){
		tmp[i] = a[obj[0]][obj[1]+i];
		++i;
	}
	end_tmp = i-1;
	end[obj[0]] = obj[1]-1;

	
	// join the tmp array to the end of the target array
	int j = 0;
	while(j <= end_tmp){
		a[t][end[t]+1 + j] = tmp[j];
		++j;
	}
	end[t] = end[t]+j;
}

void print(int a[][1000], int N, int end[]){
	for(int i = 0; i < N; ++i){
		int j = 0;
		printf("%d:", i+1);
		while(j <= end[i]){
			cout << " " << a[i][j];
			++j;
		}
		cout << '\n';
	}
	//cout << "--------------" << '\n';
}

int main(){
	int N = 0;
	int M = 0;
	scanf("%d%d ", &N, &M);
	int blk[1000][1000];
	int end[1000];
	for(int i = 1; i <= N; ++i){
		blk[i-1][0] = i;
		end[i-1] = 0;
	}
	char cmd[200000][4][5];
	for(int i = 0; i < M; ++i){
		for(int j = 0; j < 4; ++j){
			cin >> cmd[i][j];
		}
	}
	
	for(int i = 0; i < M; ++i){
		int loc_a[2];
		int loc_b[2];
		int a = atoi(cmd[i][1]);
		int b = atoi(cmd[i][3]);
		find(blk, a, N, end, loc_a);
		find(blk, b, N, end, loc_b);
		if( loc_a[0] == loc_b[0] ){
			//cout << "##########a == b##########" << endl;
		}else if( compare_str4(cmd[i][0], "move") ){
			if( compare_str4(cmd[i][2], "onto") ){
				//printf("###########move %d onto %d##########\n", a , b);
				restore(blk, loc_a, N, end);
				//print(blk, N, end);
				restore(blk, loc_b, N, end);
				//print(blk, N, end);
				insert(blk, loc_a, loc_b[0], N, end);
				//print(blk, N, end);
			}else if( compare_str4(cmd[i][2], "over") ){
				//printf("##########move %d over %d##########\n", a, b);
				restore(blk, loc_a, N, end);
				//print(blk, N, end);
				insert(blk, loc_a, loc_b[0], N, end);
				//print(blk, N, end);
			}else{
				//cout << "format error" << endl;
			}
		}else if( compare_str4(cmd[i][0], "pile") ){
            if( compare_str4(cmd[i][2], "onto") ){
				//printf("##########pile %d onto %d##########\n", a, b);
				restore(blk, loc_b, N, end);
				//print(blk, N, end);		
				insert(blk, loc_a, loc_b[0], N, end);
				//print(blk, N, end);
			}else if( compare_str4(cmd[i][2], "over") ){
				//printf("##########pile %d over %d##########\n", a, b);
				insert(blk, loc_a, loc_b[0], N, end);
				//print(blk, N, end);
			}else{
				//cout << "format error" << endl;
			}
		}else{
			//cout << "format error" << endl;
		}
	}

	// verify
	print(blk, N, end);
}
