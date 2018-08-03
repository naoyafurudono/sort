#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

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
    quick_sort(A, l+1);
    quick_sort(A+r, n-r);
}

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/

int quick_select(int A[], int n, int k){
  int i, l, r, pivot, z, len;
  if(n <= 5){
    quick_sort(A, n);
    return A[k];
  }
  for(i = 0; i * 5 < n; i++){
    if(i * 5 + 4 < n) len = 5;
    else len = n - i*5;

    quick_sort(A + i*5, len);
    z = A[i];
    A[i] = A[i*5 + len / 2];
    A[i*5 + len / 2] = z;
  }
  pivot = quick_select(A, i, i / 2);
  l = 0;
  r = n;

  for(i = 0; i < r; i++){
      if(A[i] < pivot){
          int z = A[l];
          A[l] = A[i];
          A[i] = z;
          l++;
      }else if(A[i] > pivot){
          r--;
          int z = A[r];
          A[r] = A[i];
          A[i] = z;
          i--;
      }
  }

  if(l <= k && k < r)return pivot;
  if(r <= k)return quick_select(A+r, n-r, k-r);
  if(k < l) return quick_select(A, l, k);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
    else printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
