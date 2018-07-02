#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

int quick_select(int A[], int n, int k){
    int i, l, r, pivot;
     l = 0;
     r = n;
     //先頭の要素をpivotにする
     pivot = A[0];
    // printf("A[0]%d\n",A[0]);
     for(i = 1; i < r; i++){
       if(A[i] < pivot){//A[l]とA[i]を入れ替え
           int z = A[l];
           A[l] = A[i];
           A[i] = z;
           l++;
       }
       if(A[i] > pivot){//A[r]とA[i]を入れ替えて、iを変えずにA[i]を次に読む
           r--;
           int z = A[r];
           A[r] = A[i];
           A[i] = z;
           i--;
       }
       //A[i] == pivotのときは、何もしないで次に進む
   }
   //printf("l%d:r%d:k%d",l,r,k);
    if(l <= k && k < r)return pivot;
    if(r <= k)return quick_select(A+r, n-r, k-r);
    if(k < l) return quick_select(A, l, k);
}

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/

int median_of_median(int A[], int n){//Aは配列。nはAの長さ。Aの中央値を求める。
  if(n <= 5){
      quick_select(A,n,n/2);
  }else{
      int l = (n + 5 - 1)/ 5;
      int i;
      for(i = 0; i < l - 1; i++){
          A[i] = median_of_median(A + l*i,l);
      }
      A[l-1] = median_of_median(A + l - 1,n - (l - 1)*5);
      median_of_median(A,l);
  }
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
    if(median_of_median(A, N) != N/2) printf("ERROR");
    else printf("OK");
}
