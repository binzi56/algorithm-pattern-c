# 动态规划

## 背景

先从一道题目开始~

如题  [triangle](https://leetcode-cn.com/problems/triangle/)

> 给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。

例如，给定三角形：

```text
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
```

自顶向下的最小路径和为  11（即，2 + 3 + 5 + 1 = 11）。

使用 DFS（遍历 或者 分治法）

遍历

![image.png](https://img.fuiboom.com/img/dp_triangle.png)

分治法

![image.png](https://img.fuiboom.com/img/dp_dc.png)

优化 DFS，缓存已经被计算的值（称为：记忆化搜索 本质上：动态规划）

![image.png](https://img.fuiboom.com/img/dp_memory_search.png)

动态规划就是把大问题变成小问题，并解决了小问题重复计算的方法称为动态规划

动态规划和 DFS 区别

- 二叉树 子问题是没有交集，所以大部分二叉树都用递归或者分治法，即 DFS，就可以解决
- 像 triangle 这种是有重复走的情况，**子问题是有交集**，所以可以用动态规划来解决

动态规划，自底向上

```c
int minimumTotal(vector<vector<int>>& triangle) {
    if(triangle.size() == 0 || triangle[0].size() == 0) return 0;

    // 1、状态定义：f[i][j] 表示从i,j出发，到达最后一层的最短路径
    int l = triangle.size();
    // 2、初始化
    vector<vector<int>> f;
    for(int i = 0; i < l; i++){
        vector<int> g;
        for(int j = 0; j < triangle[i].size(); j++){
             g.push_back(triangle[i][j]);
        }
        f.push_back(g);
    }

    // 3、递推求解
    for(int i = triangle.size() - 2; i >= 0; i--){
        for(int j = 0; j < triangle[i].size(); j++){
            f[i][j] = min(f[i + 1][j], f[i + 1][j + 1]) + triangle[i][j];
        }
    }

    // 4、答案
    return f[0][0];
}
```

动态规划，自顶向下

```c
// 测试用例：
// [
// [2],
// [3,4],
// [6,5,7],
// [4,1,8,3]
// ]
int minimumTotal(vector<vector<int>>& triangle) {
    if(triangle.size() == 0 || triangle[0].size() == 0) return 0;

    // 1、状态定义：f[i][j] 表示从0,0出发，到达i,j的最短路径
    int l = triangle.size();
    // 2、初始化
    vector<vector<int>> f;
    for(int i = 0; i < l; i++){
        vector<int> g;
        for(int j = 0; j < triangle[i].size(); j++){
             g.push_back(triangle[i][j]);
        }
        f.push_back(g);
    }

    // 3、递推求解
    for(int i = 1; i < l; i++){
        for(int j = 0; j < triangle[i].size(); j++){
            // 这里分为两种情况：
            // 1、上一层没有左边值
            // 2、上一层没有右边值
            if (j-1 < 0) {
                f[i][j] = f[i-1][j] + triangle[i][j];
            } else if (j >= f[i-1].size()) {
                f[i][j] = f[i-1][j-1] + triangle[i][j];
            } else {
                f[i][j] = min(f[i-1][j], f[i-1][j-1]) + triangle[i][j];
            }
        }
    }

    // 4、答案
    int result = f[l-1][0];
    for(int i = 1; i < f[l-1].size(); i++){
        result = min(f[l - 1][i], result);
    }

    return result;
}
```

优化空间复杂度:
```c
int minimumTotal(vector<vector<int>>& triangle) {
     int n = triangle.size();
     vector<int> dp(n + 1);
     for(int i = n - 1; i >= 0; i--){
         for(int j = 0; j <= i; j++){
             dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
         }
     }

     return dp[0];
}
```

## 递归和动规关系

递归是一种程序的实现方式：函数的自我调用

```go
Function(x) {
	...
	Funciton(x-1);
	...
}
```

动态规划：是一种解决问题的思想，大规模问题的结果，是由小规模问题的结果运算得来的。动态规划可用递归来实现(Memorization Search)

## 使用场景

满足两个条件

- 满足以下条件之一
  - 求最大/最小值（Maximum/Minimum ）
  - 求是否可行（Yes/No ）
  - 求可行个数（Count(\*) ）
- 满足不能排序或者交换（Can not sort / swap ）

如题：[longest-consecutive-sequence](https://leetcode-cn.com/problems/longest-consecutive-sequence/)  位置可以交换，所以不用动态规划

## 四点要素

1. **状态 State**
   - 灵感，创造力，存储小规模问题的结果
2. 方程 Function
   - 状态之间的联系，怎么通过小的状态，来算大的状态
3. 初始化 Intialization
   - 最极限的小状态是什么, 起点
4. 答案 Answer
   - 最大的那个状态是什么，终点

## 常见四种类型

1. Matrix DP (10%)
1. Sequence (40%)
1. Two Sequences DP (40%)
1. Backpack (10%)

> 注意点
>
> - 贪心算法大多题目靠背答案，所以如果能用动态规划就尽量用动规，不用贪心算法

## 1、矩阵类型（10%）

### [minimum-path-sum](https://leetcode-cn.com/problems/minimum-path-sum/)

> 给定一个包含非负整数的  *m* x *n*  网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

思路：动态规划
1、state: f[x][y]从起点走到 x,y 的最短路径
2、function: f[x][y] = min(f[x-1][y], f[x][y-1]) + A[x][y]
3、intialize: f[0][0] = A[0][0]、f[i][0] = sum(0,0 -> i,0)、 f[0][i] = sum(0,0 -> 0,i)
4、answer: f[n-1][m-1]

```c
int minPathSum(vector<vector<int>>& grid) {
    // 思路：动态规划
    // f[i][j] 表示i,j到0,0的和最小
    int row = grid.size(), col = grid[0].size();
    if(row == 0 || col == 0) return 0;

    // 复用原来的矩阵列表
    // 初始化：f[i][0]、f[0][j]
    for(int i = 1; i < row; i++){
        grid[i][0] += grid[i - 1][0];
    }      

    for(int j = 1; j < col; j++){
        grid[0][j] += grid[0][j - 1];
    }

    for(int i = 1; i < row; i++){
        for(int j = 1; j < col; j++){
            grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]) + grid[i][j];
        }
    }

    return grid[row - 1][col - 1];
}
```

### [unique-paths](https://leetcode-cn.com/problems/unique-paths/)

> 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
> 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
> 问总共有多少条不同的路径？

```c
int uniquePaths(int m, int n) {
    if(m == 0 || n == 0) return 1;

    vector<vector<int>> dp(m, vector<int>(n));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(i == 0 || j == 0) {
                dp[i][j] = 1;
            }else{
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }

    return dp[m - 1][n - 1];
}
```

### [unique-paths-ii](https://leetcode-cn.com/problems/unique-paths-ii/)

> 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
> 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
> 问总共有多少条不同的路径？
> 现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

```c
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if(obstacleGrid[0][0] == 1) return 0;
    // f[i][j] = f[i-1][j] + f[i][j-1] 并检查障碍物
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<vector<int>> f(m, vector<int>(n, 1));
    for(int i = 1; i < m; i++){
        if(obstacleGrid[i][0] == 1 || f[i - 1][0] == 0){
            f[i][0] = 0;
        } 
    }

    for(int i = 1; i < n; i++){
        if(obstacleGrid[0][i] == 1 || f[0][i - 1] == 0){
            f[0][i] = 0;
        }
    }

    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            if(obstacleGrid[i][j] == 1){
                f[i][j] = 0;
            }else{
                f[i][j] = f[i - 1][j] + f[i][j - 1];
            }
        }
    }

    return f[m - 1][n - 1];
}
```
优化空间:
```c
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int n = obstacleGrid.size(), m = obstacleGrid.at(0).size();
    vector <int> f(m);

    f[0] = (obstacleGrid[0][0] == 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (obstacleGrid[i][j] == 1) {
                f[j] = 0;
                continue;
            }
            if (j - 1 >= 0 && obstacleGrid[i][j - 1] == 0) {
                f[j] += f[j - 1];
            }
        }
    }

    return f.back();  //相当于f[m - 1]
}
```


## 2、序列类型（40%）

### [climbing-stairs](https://leetcode-cn.com/problems/climbing-stairs/)

> 假设你正在爬楼梯。需要  *n*  阶你才能到达楼顶。

```c
int climbStairs(int n) {
    if(n < 3) return n;

    int a = 1, b = 2;
    for(int i = 3; i <= n; i++){
        int sum = a + b;
        a = b;
        b = sum;
    }

    return b;
}
```

### [jump-game](https://leetcode-cn.com/problems/jump-game/)

> 给定一个非负整数数组，你最初位于数组的第一个位置。
> 数组中的每个元素代表你在该位置可以跳跃的最大长度。
> 判断你是否能够到达最后一个位置。

```c
bool canJump(vector<int>& nums) {
    int n = nums.size();
    int rightmost = 0;
    for (int i = 0; i < n; ++i) {
        if (i <= rightmost) {
            rightmost = max(rightmost, i + nums[i]);
            if (rightmost >= n - 1) {
                return true;
            }
        }
    }
    return false;
}
```

### [jump-game-ii](https://leetcode-cn.com/problems/jump-game-ii/)

> 给定一个非负整数数组，你最初位于数组的第一个位置。
> 数组中的每个元素代表你在该位置可以跳跃的最大长度。
> 你的目标是使用最少的跳跃次数到达数组的最后一个位置。

```c
int jump(vector<int>& nums) {
    int n = nums.size();
    if(n == 0) return 0;

    int ans = 0;
    int end = 0;
    int maxPos = 0;
    for(int i = 0; i < n - 1; i++){
        maxPos = max(maxPos, nums[i] + i);
        if(i == end){
            end = maxPos;
            ans++;
        }
    }

    return ans;
}
```

### [palindrome-partitioning-ii](https://leetcode-cn.com/problems/palindrome-partitioning-ii/)

> 给定一个字符串 _s_，将 _s_ 分割成一些子串，使每个子串都是回文串。
> 返回符合要求的最少分割次数。

```c
int minCut(string s) {
    // state: f[i] "前i"个字符组成的子字符串需要最少几次cut(个数-1为索引)
	// function: f[i] = MIN{f[j]+1}, j < i && [j+1 ~ i]这一段是一个回文串
	// intialize: f[i] = i - 1 (f[0] = -1)
	// answer: f[s.length()]
    int n = s.size(); 
    if(n == 0 || n == 1) return 0;

    vector<int> f(n + 1);
    f[0] = -1;
    f[1] = 0;
    for(int i = 1; i <= n; i++){
        f[i] = i - 1;
        for(int j = 0; j < i; j++){
            if(isPalindrome(s, j, i - 1)){
                f[i] = min(f[i], f[j] + 1);
            }
        }
    }

    return f[n];
}

//注: 此处不用 & 会发生超时
bool isPalindrome(const string& s, int i, int j){
    while(i < j){
        if(s[i++] != s[j--]) return false;
    }
    return true;
}
```

注意点

- 判断回文字符串时，可以提前用动态规划算好，减少时间复杂度

### [longest-increasing-subsequence](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

> 给定一个无序的整数数组，找到其中最长上升子序列的长度。

```c
int lengthOfLIS(vector<int>& nums) {
    // f[i] 表示从0开始到i结尾的最长序列长度
    // f[i] = max(f[j])+1 ,a[j]<a[i]
    // f[0...n-1] = 1
    // max(f[0]...f[n-1])
    int len = nums.size();
    if(len == 0 || len == 1) return len;
    
    vector<int> f(len);
    f[0] = 1;
    for(int i = 1; i < len; i++){
        f[i] = 1;
        for(int j = 0; j < i; j++){
            if(nums[j] < nums[i]){
                f[i] = max(f[i], f[j] + 1);
            }
        }
    }
    
    int result = f[0];
    for(int i = 1; i < f.size(); i++){
        result = max(result, f[i]);
    }
    return result;
}
```

### [word-break](https://leetcode-cn.com/problems/word-break/)

> 给定一个**非空**字符串  *s*  和一个包含**非空**单词列表的字典  *wordDict*，判定  *s*  是否可以被空格拆分为一个或多个在字典中出现的单词。

```c
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> wordDictSet;
    for(auto word : wordDict){
    wordDictSet.insert(word);
    }

    int len = s.size();    
    vector<bool> dp(len + 1);
    dp[0] = true;    //dp[0]=true 表示空串且合法
    for(int i = 1; i <= len; i++){
        for(int j = 0; j < i; j++){
            if(dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end()){
                dp[i] = true;
                break;
            }
        }
    }

    return dp[len];
}
```

小结

常见处理方式是给 0 位置占位，这样处理问题时一视同仁，初始化则在原来基础上 length+1，返回结果 f[n]

- 状态可以为前 i 个
- 初始化 length+1
- 取值 index=i-1
- 返回值：f[n]或者 f[m][n]

## Two Sequences DP（40%）

### [longest-common-subsequence](https://leetcode-cn.com/problems/longest-common-subsequence/)

> 给定两个字符串  text1 和  text2，返回这两个字符串的最长公共子序列。
> 一个字符串的   子序列   是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
> 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。

```c
int longestCommonSubsequence(string text1, string text2) {
    // dp[i][j] a前i个和b前j个字符最长公共子序列
    // dp[m+1][n+1]
    //   ' a d c e
    // ' 0 0 0 0 0
    // a 0 1 1 1 1
    // c 0 1 1 2 1
    //
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(text1[i - 1] == text2[j - 1]){
                // 相等取左上元素+1，否则取左或上的较大值
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }else{
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}
```

注意点

- c 切片初始化

```c++
  vector<vector<int>> dp(m + 1, vector<int>(n + 1));
```

- 从 1 开始遍历到最大长度
- 索引需要减一

### [edit-distance](https://leetcode-cn.com/problems/edit-distance/)

> 给你两个单词  word1 和  word2，请你计算出将  word1  转换成  word2 所使用的最少操作数  
> 你可以对一个单词进行如下三种操作：
> 插入一个字符
> 删除一个字符
> 替换一个字符

思路：和上题很类似，相等则不需要操作，否则取删除、插入、替换最小操作次数的值+1

```c
int minDistance(string word1, string word2) {
    // dp[i][j] 表示a字符串的前i个字符编辑为b字符串的前j个字符最少需要多少次操作
    // dp[i][j] = OR(dp[i-1][j-1]，a[i]==b[j],min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])+1)
    int m = word1.size(), n = word2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for(int i = 0; i <= m; i++){
        dp[i][0] = i;
    }
    for(int i = 0; i <=n; i++){
        dp[0][i] = i;
    }

    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(word1[i - 1] == word2[j - 1]){
                // 相等则不需要操作
                dp[i][j] = dp[i - 1][j - 1]; 
            }else{
                // 否则取删除、插入、替换最小操作次数的值+1
                dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
            }
        }
    }

    return dp[m][n];
}
```

说明

> 另外一种做法：MAXLEN(a,b)-LCS(a,b)

## 零钱和背包（10%）

### [coin-change](https://leetcode-cn.com/problems/coin-change/)

> 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回  -1。

思路：和其他 DP 不太一样，i 表示钱或者容量

```c
int coinChange(vector<int>& coins, int amount) {
    // 状态 dp[i]表示金额为i时，组成的最小硬币个数
    // 推导 dp[i]  = min(dp[i-1], dp[i-2], dp[i-5])+1, 前提 i-coins[j] > 0
    // 初始化为最大值 dp[i]=amount+1
    // 返回值 dp[n] or dp[n]>amount =>-1
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for(int i = 1; i <= amount; i++){
        for(int j = 0; j < coins.size(); j++){
            if(i - coins[j] >= 0){
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }

    if(dp[amount] > amount){
        return -1;
    }

    return dp[amount];
}
```

注意

> dp[i-a[j]] 决策 a[j]是否参与

### [backpack](https://www.lintcode.com/problem/backpack/description)

> 在 n 个物品中挑选若干物品装入背包，最多能装多满？假设背包的大小为 m，每个物品的大小为 A[i]

```c
int backPack(int m, vector<int> &A) {
    // f[i][j] 前i个物品，是否能装j
    // f[i][j] =f[i-1][j] f[i-1][j-a[i] j>a[i]
    // f[0][0]=true f[...][0]=true
    // f[n][X]
    int n = A.size();
    vector<vector<int>> f(n + 1, vector<int>(m + 1));
    
    f[0][0] = true;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= m; j++){
            f[i][j] = f[i - 1][j];
            if(j - A[i - 1] >= 0 && f[i - 1][j - A[i - 1]]){
                f[i][j] = true;
            }
        }
    }
    
    for(int i = m; i >= 0; i--){
        if(f[n][i]) return i;
    }
    
    return 0;
}
```

### [backpack-ii](https://www.lintcode.com/problem/backpack-ii/description)

> 有 `n` 个物品和一个大小为 `m` 的背包. 给定数组 `A` 表示每个物品的大小和数组 `V` 表示每个物品的价值.
> 问最多能装入背包的总价值是多大?

思路：f[i][j] 前 i 个物品，装入 j 背包 最大价值

```c
int backPackII(int m, vector<int> &A, vector<int> &V) {
    // f[i][j] 前i个物品，装入j背包 最大价值
    // f[i][j] =max(f[i-1][j] ,f[i-1][j-A[i]]+V[i]) 是否加入A[i]物品
    // f[0][0]=0 f[0][...]=0 f[...][0]=0
    int n = A.size();
    vector<vector<int>> f(n + 1, vector<int>(m + 1));
    
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= m; j++){
            f[i][j] = f[i - 1][j];
            if(j - A[i - 1] >= 0){
                f[i][j] = max(f[i - 1][j], f[i - 1][j - A[i - 1]] + V[i - 1]);
            }
        }
    }
    
    return f[n][m];
}
```

## 练习

Matrix DP (10%)

- [ ] [triangle](https://leetcode-cn.com/problems/triangle/)
- [ ] [minimum-path-sum](https://leetcode-cn.com/problems/minimum-path-sum/)
- [ ] [unique-paths](https://leetcode-cn.com/problems/unique-paths/)
- [ ] [unique-paths-ii](https://leetcode-cn.com/problems/unique-paths-ii/)

Sequence (40%)

- [ ] [climbing-stairs](https://leetcode-cn.com/problems/climbing-stairs/)
- [ ] [jump-game](https://leetcode-cn.com/problems/jump-game/)
- [ ] [jump-game-ii](https://leetcode-cn.com/problems/jump-game-ii/)
- [ ] [palindrome-partitioning-ii](https://leetcode-cn.com/problems/palindrome-partitioning-ii/)
- [ ] [longest-increasing-subsequence](https://leetcode-cn.com/problems/longest-increasing-subsequence/)
- [ ] [word-break](https://leetcode-cn.com/problems/word-break/)

Two Sequences DP (40%)

- [ ] [longest-common-subsequence](https://leetcode-cn.com/problems/longest-common-subsequence/)
- [ ] [edit-distance](https://leetcode-cn.com/problems/edit-distance/)

Backpack & Coin Change (10%)

- [ ] [coin-change](https://leetcode-cn.com/problems/coin-change/)
- [ ] [backpack](https://www.lintcode.com/problem/backpack/description)
- [ ] [backpack-ii](https://www.lintcode.com/problem/backpack-ii/description)
