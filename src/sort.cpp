
#include "Demo5_2_sort.hpp"

void sortDemoTest(){
    vector<int> a {80,30,60,40,20,10,50,70};
    int len = (sizeof(a)) / (sizeof(a[0]));
    
//    insertSort(a, len);
//    printf("\n插入排序结果:\n");
//    printfIntArr(a);
    
    quickSort(a, len);
    printf("\n快速排序结果:\n");
    printfIntArr(a);
    
//    mergeSortUpToDown(a, 0, len-1);        // 归并排序(从上往下)
//    mergeSortDownToUp(a, len);            // 归并排序(从下往上)
//    printf("\n归并排序结果:\n");
//    printfIntArr(a);
}

#pragma mark - 冒泡排序
void bubbleSort(vector<int>& nums, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (nums[j] > nums[j + 1]){
                __swap(nums[j], nums[j+1]);
            }
        }
    }
}

#pragma mark - 选择排序
void selectSort(vector<int>& nums, int n){
    for (int i = 0; i < n; i++){
        int min = i;
        for (int j = i + 1; j < n ; j++) {
            if (nums[j] < nums[min]){
                min = j;
            }
        }
        
        if (min != i){
            __swap(nums[i],nums[min]);
        }
    }
}

#pragma mark - 插入排序
void insertSort(vector<int>& nums, int n){
    if(n <= 1) return;
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0; j--) {
            if (nums[j] < nums[j - 1]){
                __swap(nums[j], nums[j - 1]);
            } else{
                break;
            }
        }
    }
}

#pragma mark - 希尔排序
void shellSort(vector<int>& nums, int n){
    int temp;
    int gap = n;
    do{
        gap = gap / 3 + 1;
        for (int i = gap; i < n; i++)
        {
            if (nums[i] < nums[i - gap]){
                temp = nums[i];
                int j;
                for (j = i; j >= gap && temp < nums[j - gap]; j -= gap){
                    nums[j] = nums[j - gap];
                }
                nums[j] = temp;
            }
        }
    } while (gap > 1);
}

#pragma mark - 快速排序
void quickSort(vector<int>& nums, int n){
    // 思路：把一个数组分为左右两段，左段小于右段
    __quickSort(nums, 0, n - 1);
}

// 原地交换，所以传入交换索引
void __quickSort(vector<int>& nums, int start, int end){
    if (start < end) {
        int pivot = partition(nums, start, end);
        __quickSort(nums, start, pivot - 1);
        __quickSort(nums, pivot + 1, end);
    }
}

// 分区
int partition(vector<int>& nums, int start, int end){
    // 选取最后一个元素作为基准pivot
    int p = nums[end];
    int i = start;
    // 最后一个值就是基准所以不用比较
    for (int j = start; j < end; j++) {
        if (nums[j] < p) {
            swap(nums[i], nums[j]);
            i++;
        }
    }
    // 把基准值换到中间
    swap(nums[i], nums[end]);
    return i;
}

#pragma mark - 归并排序
//归并排序(从上往下)
void mergeSortUpToDown(vector<int>& nums, int start, int end){
    if(nums.empty() || start >= end){
        return;
    }
    
    int mid = (end + start)/2;
    mergeSortUpToDown(nums, start, mid);
    mergeSortUpToDown(nums, mid+1, end);
    
    __merge(nums, start, mid, end);
}

//归并排序
void __merge(vector<int>& nums, int start, int mid, int end){
    vector<int>temp(end-start+1, 0);     //temp是汇总2个有序区的临时区域
    int i = start;                       //第1个有序区的索引
    int j = mid + 1;                     //第2个有序区的索引
    int k = 0;                           //临时区域的索引
    
    //将部分小的移动到前面
    while(i <= mid && j <= end){
        temp[k++] = (nums[i] <= nums[j]) ? nums[i++] : nums[j++];
    }
    
    while(i <= mid)
        temp[k++] = nums[i++];
    
    while(j <= end)
        temp[k++] = nums[j++];
    
    //将排序后的元素，全部都整合到数组nums中
    for (i = 0; i < k; i++)
        nums[start + i] = temp[i];
}

//对数组a做若干次合并：数组a的总长度为len，将它分为若干个长度为gap的子数组；将"每2个相邻的子数组" 进行合并排序
void __mergeGroups(vector<int>& nums, int len, int gap){
    int i;
    //将"每2个相邻的子数组" 进行合并排序
    for(i = 0; i+2*gap-1 < len; i+=(2*gap))
    {
        __merge(nums, i, i+gap-1, i+2*gap-1);
    }
    
    //若i+gap-1 < len-1，则剩余一个子数组没有配对
    //将该子数组合并到已排序的数组中
    if ( i+gap-1 < len-1)
    {
        __merge(nums, i, i + gap - 1, len - 1);
    }
}

//归并排序(从下往上)
void mergeSortDownToUp(vector<int>& nums, int n)
{
    int first = 0;
    
    if (nums.empty() || n<=0){
        return;
    }
    
    for(n = 1; first < n; n*=2){
        __mergeGroups(nums, n, first);
    }
}

//交互数组元素
void __swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}


#pragma mark - 堆排序
//堆排序
void heapSort(vector<int>& nums){
    // 1、无序数组nums
    // 2、将无序数组nums构建为一个大根堆
    buildMaxHeap(nums);

    // 3、交换nums[0]和nums[nums.size()-1]
    // 4、然后把前面这段数组继续下沉保持堆结构，如此循环即可
    int len = nums.size();  //此处len需要变换,单独拎出来
    for (int i = nums.size() - 1; i > 0; i--) {
        swap(nums[0], nums[i]);  // 从后往前填充值
        len--;                   // 前面的长度也减一
        heapHelper(nums, 0, len);
    }
}

// 建立大顶堆
void buildMaxHeap(vector<int>& nums){
    int length = nums.size();
    for (int i = length / 2; i >= 0; i--) {
        heapHelper(nums, i, length);
    }
}

//堆调整
void heapHelper(vector<int>& nums, int i, int length){
    int left = 2 * i + 1;  // 左节点索引(从0开始，所以左节点为i*2+1)
    int right = 2 * i + 2; // 右节点索引
    int largest = i;

    // largest保存根、左、右三者之间较大值的索引
    // 存在左节点，左节点值较大，则取左节点
    if (left < length && nums[left] > nums[largest]) {
        largest = left;
    }
    // 存在有节点，且值较大，取右节点
    if (right < length && nums[right] > nums[largest]) {
        largest = right;
    }

    // 如果非根节点较大，则继续递归
    if (largest != i) {
        swap(nums[i], nums[largest]);
        heapHelper(nums, largest, length);
    }
}
