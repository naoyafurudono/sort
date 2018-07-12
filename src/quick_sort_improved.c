#include <stdio.h>

//フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] をソートして昇順に書き換える関数
*/
void quick_sort(int A[], int n){
        if(n < 2) return;
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
       quick_sort(A, l);
       quick_sort(A+r, n-r);
   }

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
// すべての要素が同じ場合でも計算が早く終わるか確認する

  quick_sort(A, N);
  for(i=0;i<N;i++){
    if(A[i] != i){
        printf("ERROR %dth element is %d\n", i, A[i]);
    }else{
        printf("OK %dth element is %d\n", i, A[i]);
    }
  }
}
