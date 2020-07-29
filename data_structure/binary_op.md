# 二进制

## 常见二进制操作

### 基本操作

a=0^a=a^0

0=a^a

由上面两个推导出：a=a^b^b

### 交换两个数

a=a^b

b=a^b

a=a^b

### 移除最后一个 1

a=n&(n-1)

### 获取最后一个 1

diff=(n&(n-1))^n

### 位运算概览
| 符号 | 描述 | 运算规则                                                     |
| :--- | :--- | :---------------------- |
| &    | 与   | 两个位都为1时，结果才为1                                     |
| \||   或   | 两个位都为0时，结果才为0                                     |
| ^    | 异或 | 两个位相同为0，相异为1                                       |
| ~    | 取反 | 0变1，1变0                                                   |
| <<   | 左移 | 各二进位全部左移若干位，高位丢弃，低位补0                    |
| >>   | 右移 | 各二进位全部右移若干位，对无符号数，高位补0，有符号数，各编译器处理方法不一样，有的补符号位（算术右移），有的补0（逻辑右移） |

## 常见题目

[single-number](https://leetcode-cn.com/problems/single-number/)

> 给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

```c
int singleNumber(vector<int>& nums) {
  // 10 ^10 == 00
  // 两个数异或就变成0
    int res = 0;
    for(auto n : nums){
        res = n ^ res;
    }

    return res;
}
```

[single-number-ii](https://leetcode-cn.com/problems/single-number-ii/)

> 给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。找出那个只出现了一次的元素。

```c
//解法一
//状态机
int singleNumber(vector<int>& nums) {
     int a = 0, b = 0;
     for(int num : nums){
         a = a ^ num & (~b);
         b = b ^ num & (~a);
     }
     return a;
}

//解法二
int singleNumber(vector<int>& nums) {
    int res = 0;
    for (int i = 0; i < 32; ++i) {
        int cnt = 0;
        for (auto x : nums) {
            cnt += (x>>i)&1;
        }
        res |= (cnt%3)<<i;
    }
    return res;
}
```

[single-number-iii](https://leetcode-cn.com/problems/single-number-iii/)

> 给定一个整数数组  `nums`，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。

```c
vector<int> singleNumber(vector<int>& nums) {
    int s = 0;

    for(auto n : nums){
        s = s ^ n;  //先对所有数字进行一次异或，得到两个出现一次的数字的异或值
    }

    s = (s & (s - 1)) ^ s;   // 去掉末尾的1后异或s就得到最后一个1的位置
    vector<int> res(2,0);
    for(auto n : nums){
        if(n & s){
           res[0] ^= n;
        }else{
           res[1] ^= n;
        }
    }

    return res;
}
```

[number-of-1-bits](https://leetcode-cn.com/problems/number-of-1-bits/)

> 编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’  的个数（也被称为[汉明重量](https://baike.baidu.com/item/%E6%B1%89%E6%98%8E%E9%87%8D%E9%87%8F)）。

```c
int hammingWeight(uint32_t n) {
    int count = 0;
    while(n > 0){
        n = n & (n - 1);
        count++;
    }

    return count;
}
```

[counting-bits](https://leetcode-cn.com/problems/counting-bits/)

> 给定一个非负整数  **num**。对于  0 ≤ i ≤ num  范围中的每个数字  i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

```c
vector<int> countBits(int num) {
    vector<int> res;
    for(int i = 0; i <= num; i++){
        res.push_back(count1(i));
    }
    return res;
}

int count1(int num){
    int count = 0;
    while(num != 0){
        num &= (num - 1);
        count++;
    }
    return count;
}
```

另外一种动态规划解法

```c
vector<int> countBits(int num) {
    vector<int> res(num + 1);
    for(int i = 1; i <= num; i++){
        res[i] = res[i & (i - 1)] + 1; // 上一个缺1的元素+1即可
    }
    return res;
}
```

[reverse-bits](https://leetcode-cn.com/problems/reverse-bits/)

> 颠倒给定的 32 位无符号整数的二进制位。

思路：依次颠倒即可

```c
uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    int pow = 31;
    while(n != 0){
       // 把最后一位取出来，左移之后累加到结果中
       res += (n & 1) << pow;
       n >>= 1;
       pow--;
    }

    return res;
}
```

[bitwise-and-of-numbers-range](https://leetcode-cn.com/problems/bitwise-and-of-numbers-range/)

> 给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，返回此范围内所有数字的按位与（包含 m, n 两端点）。

```c
//解法一
int rangeBitwiseAnd(int m, int n) {
    while(m < n){
      n &= n - 1;
    }
    return m & n;
}

//解法二
int rangeBitwiseAnd(int m, int n) {
  // m 5 1 0 1
  //   6 1 1 0
  // n 7 1 1 1
  // 把可能包含0的全部右移变成
  // m 5 1 0 0
  //   6 1 0 0
  // n 7 1 0 0
  // 所以最后结果就是m<<count

   int count = 0; //统计移位次数
   while(m != n){
       m >>= 1;
       n >>= 1;
       count++;
   }
   return n <<= count;
}
```

## 练习

- [ ] [single-number](https://leetcode-cn.com/problems/single-number/)
- [x] [single-number-ii](https://leetcode-cn.com/problems/single-number-ii/)
- [x] [single-number-iii](https://leetcode-cn.com/problems/single-number-iii/)
- [ ] [number-of-1-bits](https://leetcode-cn.com/problems/number-of-1-bits/)
- [x] [counting-bits](https://leetcode-cn.com/problems/counting-bits/)
- [x] [reverse-bits](https://leetcode-cn.com/problems/reverse-bits/)
- [x]
[bitwise-and-of-numbers-range](https://leetcode-cn.com/problems/bitwise-and-of-numbers-range/)
