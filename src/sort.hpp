//  C++的排序方式
//  https://blog.csdn.net/chen1234520nnn/article/details/82084700

#ifndef Demo5_2_sort_hpp
#define Demo5_2_sort_hpp

#include <stdio.h>
#include "Demo1_2_1_deleteArrRepeat.hpp"
#include "CommonTools.hpp"

void sortDemoTest();

void __swap(int &a, int &b);
void __merge(vector<int>& nums, int start, int mid, int end);
void __mergeGroups(vector<int>& nums, int len, int gap);

//插入排序
void insertSort(vector<int>& nums, int n);

//快速排序
void quickSort(vector<int>& nums, int n);
void __quickSort(vector<int>& nums, int start, int end); //原地交换，所以传入交换索引
int partition(vector<int>& nums, int start, int end); //分区

//归并排序(从上往下)
void mergeSortUpToDown(vector<int>& nums, int start, int end);
//归并排序(从下往上)
void mergeSortDownToUp(vector<int>& nums, int n);

//堆排序
void heapSort(vector<int>& nums);
void buildMaxHeap(vector<int>& nums);
void heapHelper(vector<int>& nums, int i, int length);

#endif /* Demo5_2_sort_hpp */
