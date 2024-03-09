#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int* CreateArray(int n)//产生随机数n个随机数
{
  int* arr = (int*)malloc(n * sizeof(*arr));//分配内存单元存储数据

  for (int i = 0; i < n; i++) {
    arr[i] = rand() + 1;
  }
  return arr;
}

void print_arr(int arr[], int n)//打印排序前后数组方便对比
{
  for (int i = 0; i < n; i += 100) {//元素太多了，每隔100个数进行抽样显示
    printf("%6d\t", arr[i]);
    if ((i + 1) % 120 == 0)//控制一下每行的数字个数
      putchar('\n');
  }
  putchar('\n');
}

void swap(int* a, int* b)//定义一个交换方法，方便排序函数调用
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void InsertSort(int arr[], int n)//直接插入排序
{
  int i, j;//定义计数器

  for (i = 1; i < n; i++)//从第一个元素的后面开始插入，一共n-1轮
  {
    for (j = i; j > 0; j--)//将a[i]插入到a[i-1]、a[i-2]、a[i-3]...之中
      if (arr[j - 1] > arr[j])//如果前面的元素比后面大，就交换，另外使用j-1刚好可以处理到arr[0]
        swap(&arr[j - 1], &arr[j]);
  }
}

//寻找切分元素，这将极大影响快速排序的性能。
//切分元素是每一次快速排序递归调用时排定的第一个元素，
//它保证大于等于左侧的元素小于等于右侧的元素。
//为了寻找切分元素的位置，我们从数组两端开始分别开始扫描，并顺便交换元素。
//两个扫描标记相遇的时候就找到了切分元素的位置

enum boolean { false, true };

int partition(int arr[], int low, int high)//low,high作为扫描数组的标记
{
  int i = low;
  int j = high;
  int key = arr[low];//假定输入是乱序的，不妨指定第一个元素作为切分元素

  while (true) {
    while (arr[i++] <= key) {//从左向右扫描，直到遇到大于key的元素或者到达右边界
      if (i == high)
        break;
    }
    while (arr[j--] >= key) {//从右向左扫描，直到遇到小于key的元素或者到达左边界
      if (j == low)
        break;
    }

    if (i >= j)//此时说明两个扫描标记相遇了
      break;
    else
      swap(&arr[i], &arr[j]);//交换让扫面停止的一对值
  }

  //切分的任务由以下两行代码完成，之前的while循环是为了寻找这个位置
  swap(&arr[low], &arr[j]);//将存放在arr[low]的切分元素放置到他的最终位置j
  return j;//返回j
}

//快速排序利用切分元素把一个数组切分为两部分，再分别对两部分进行排序，
//当两部分排序完成时，整体也自然有序
void QuickSort(int arr[], int start, int end)
{
  int pos;//定义切分位置
  if (start < end)
  {
    //快速排序的递归调用
    pos = partition(arr, start, end);//切分
    QuickSort(arr, start, pos - 1);//对左半部分进行排序
    QuickSort(arr, pos + 1, end);//对右半部分进行排序
  }
}

void blank(int i)
{
  while (i >= 1) {
    putchar('\n');
    i--;
  }
}

#define MAXSIZE 20001

int main()
{
  int arr[MAXSIZE], b[MAXSIZE];//定义两个存放待排序元素的数组
  int* a = CreateArray(MAXSIZE);//生成随机数放入arr中
  ;
  for (int i = 0; i < MAXSIZE; i++)
  {
    b[i] = a[i];
  }//数组b的内容是从数组a复制过来的

  printf("Insertion sort:\n");
  print_arr(a, MAXSIZE);//打印排序前的数组
  blank(2);//输出一定的间隔
  clock_t start, end;//定义计时器变量
  start = clock();
  InsertSort(a, MAXSIZE);
  end = clock();
  double insertion_sort_cast = (double)(end - start) / CLOCKS_PER_SEC;

  print_arr(a, MAXSIZE);//打印排序后的数组
  blank(5);//输出一定的间隔

  printf("Quick_sort:\n");
  print_arr(b, MAXSIZE);//打印排序前的数组
  blank(2);//输出一定的间隔
  clock_t start1, end1;//定义计时器变量
  start1 = clock();
  QuickSort(b, 1, MAXSIZE - 1);
  end1 = clock();
  double q_sort_cast = (double)(end1 - start1) / CLOCKS_PER_SEC;

  print_arr(b, MAXSIZE);//打印排序后的数组
  blank(5);//输出一定的间隔

  //插入排序耗时
  printf("插入排序用时:%f秒\n", insertion_sort_cast);
  //快速排序耗时
  printf("快速排序用时:%f秒\n", q_sort_cast);
}