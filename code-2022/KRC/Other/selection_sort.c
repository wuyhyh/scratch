#include<stdio.h>
#include<stdlib.h>

int* rand_n(int n)
{
  int* temp = (int*)malloc(n * sizeof(*temp));
  for (int i = 0; i < n; i++) {
    temp[i] = rand() % RAND_MAX + 1;
  }
  return temp;
}

void show(int arr[], int n)
{
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
    if ((i + 1) % 10 == 0)//每10个数打印一行
      putchar('\n');
  }
}

void swap(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

//插入排序的操作步骤非常死板，一定是确定的步数
void selection_sort(int arr[], int n)
{
  int i, j;
  int min;

  for (i = 0; i < n; i++) {
    min = i;
    for (j = i + 1; j < n; j++) {//从剩余数字里面找到最小的
      if (arr[j] < arr[min])
        min = j;
    }
    swap(&arr[min], &arr[i]);
  }
}

#define NUM 110
int main()
{
  int* ss = rand_n(NUM);
  //show(ss, NUM);
  selection_sort(ss, NUM);
  show(ss, NUM);

  return 0;
}