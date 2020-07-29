# 回溯法

## 背景

回溯法（backtrack）常用于遍历列表所有子集，是 DFS 深度搜索一种，一般用于全排列，穷尽所有可能，遍历的过程实际上是一个决策树的遍历过程。时间复杂度一般 O(N!)，它不像动态规划存在重叠子问题可以优化，回溯算法就是纯暴力穷举，复杂度一般都很高。

## 模板

```c
result = []
func backtrack(选择列表,路径):
    if 满足结束条件:
        result.add(路径)
        return
    for 选择 in 选择列表:
        做选择
        backtrack(选择列表,路径)
        撤销选择
```

核心就是从选择列表里做一个选择，然后一直递归往下搜索答案，如果遇到路径不通，就返回来撤销这次选择。

## 示例

### [subsets](https://leetcode-cn.com/problems/subsets/)

> 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

遍历过程

![image.png](https://img.fuiboom.com/img/backtrack.png)

参照[leetcode题解](https://leetcode-cn.com/problems/subsets/solution/hui-su-si-xiang-tuan-mie-pai-lie-zu-he-zi-ji-wen-t/):

```c
vector<vector<int>> res;
vector<vector<int>> subsets(vector<int>& nums) {
    if(nums.empty()) return res;
    // 记录走过的路径
    vector<int> temp;
    backTrace(nums, 0, temp);
    return res;
}

void backTrace(vector<int>& nums, int start, vector<int>& temp){
    res.push_back(temp);

    for(int i = start; i < nums.size(); i++){
        temp.push_back(nums[i]); // 做选择
        backTrace(nums, i + 1, temp); //回溯
        temp.pop_back(); //删除最后一个
    }
}
```

### [subsets-ii](https://leetcode-cn.com/problems/subsets-ii/)

> 给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。说明：解集不能包含重复的子集。

```c
vector<vector<int>> res;
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    if(nums.empty()) return res;
    //先排序
    sort(nums.begin(), nums.end());

    vector<int> temp;
    backTrace(nums, 0, temp);
    return res;
}

void backTrace(vector<int>& nums, int start, vector<int> temp){
    res.push_back(temp);
    // 选择时需要剪枝、处理、撤销选择
    for(int i = start; i < nums.size(); i++){
        // 排序之后，如果再遇到重复元素，则不选择此元素
        if(i != start && nums[i] == nums[i - 1]) continue;

        temp.push_back(nums[i]);
        backTrace(nums, i + 1, temp);
        temp.pop_back();
    }
}
```

### [permutations](https://leetcode-cn.com/problems/permutations/)

> 给定一个没有重复数字的序列，返回其所有可能的全排列。

思路：需要记录已经选择过的元素，满足条件的结果才进行返回

```c
vector<vector<int>> res;
vector<vector<int>> permute(vector<int>& nums) {
    if(nums.empty()) return res;

    vector<int> temp;
    vector<bool> visited(nums.size(), 0); // 标记这个元素是否已经添加到结果集
    backTrace(nums, temp, visited);
    return res;
}

void backTrace(vector<int>& nums, vector<int>& temp, vector<bool>& visited){
    // 返回条件：临时结果和输入集合长度一致 才是全排列
    if(nums.size() == temp.size()){
        res.push_back(temp);
        return;
    }

    //全排列需要从0开始
    for(int i = 0; i < nums.size(); i++){
        if(visited[i] == true) continue;  // 已经添加过的元素，直接跳过

        temp.push_back(nums[i]);
        visited[i] = true;
        backTrace(nums, temp, visited);
        visited[i] = false;
        temp.pop_back();
    }
}
```

### [permutations-ii](https://leetcode-cn.com/problems/permutations-ii/)

> 给定一个可包含重复数字的序列，返回所有不重复的全排列。

```c
vector<vector<int>> res;
vector<vector<int>> permuteUnique(vector<int>& nums) {
    if(nums.empty()) return res;

    sort(nums.begin(), nums.end());
    vector<int> temp;
    //标记数组
    vector<bool> visited(nums.size(), 0);
    backTrace(nums, temp, visited);
    return res;
}

void backTrace(vector<int>& nums, vector<int>&temp, vector<bool>& visited){
    if(temp.size() == nums.size()) {
        res.push_back(temp);
        return;
    }

    for(int i = 0; i < nums.size(); i++){
        // 已经添加过的元素，直接跳过
        if(visited[i]) continue;
        // 上一个元素和当前相同，并且没有访问过就跳过
        if(i != 0 && nums[i] == nums[i - 1] && !visited[i - 1]) continue;

        temp.push_back(nums[i]);
        visited[i] = true;
        backTrace(nums, temp, visited);
        visited[i] = false;
        temp.pop_back();
    }
}
```

## 挑战题目

### [combination-sum](https://leetcode-cn.com/problems/combination-sum/)

> 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。(candidates 中的数字可以无限制重复被选取。)

```c
vector<vector<int>> res;
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
     if(candidates.empty()) return res;

     sort(candidates.begin(), candidates.end());
     vector<int> temp;

     backTrace(candidates, temp, target, 0);
     return res;
}

void backTrace(vector<int>& nums, vector<int>& temp, int target, int start){
     if(target == 0) {
         res.push_back(temp);
         return;
     }

     if(target < nums[start]){
         return;
     }

     for(int i = start; i < nums.size(); i++){
         target -= nums[i];
         temp.push_back(nums[i]);
         backTrace(nums, temp, target, i);
         target += nums[i];
         temp.pop_back();
     }
}
```

## 练习

- [x] [subsets](https://leetcode-cn.com/problems/subsets/)
- [x] [subsets-ii](https://leetcode-cn.com/problems/subsets-ii/)
- [x] [permutations](https://leetcode-cn.com/problems/permutations/)
- [x] [permutations-ii](https://leetcode-cn.com/problems/permutations-ii/)

挑战题目

- [ ] [combinations](https://leetcode-cn.com/problems/combinations/)
- [ ] [combination-sum](https://leetcode-cn.com/problems/combination-sum/)
- [ ] [letter-combinations-of-a-phone-number](https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/)
- [ ] [palindrome-partitioning](https://leetcode-cn.com/problems/palindrome-partitioning/)
- [ ] [restore-ip-addresses](https://leetcode-cn.com/problems/restore-ip-addresses/)
