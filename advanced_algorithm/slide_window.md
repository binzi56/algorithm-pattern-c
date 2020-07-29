# 滑动窗口

## 模板

```cpp
/* 滑动窗口算法框架 */
void slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;

    int left = 0, right = 0;
    int valid = 0;
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 右移窗口
        right++;
        // 进行窗口内数据的一系列更新
        ...

        /*** debug 输出的位置 ***/
        printf("window: [%d, %d)\n", left, right);
        /********************/

        // 判断左侧窗口是否要收缩
        while (window needs shrink) {
            // d 是将移出窗口的字符
            char d = s[left];
            // 左移窗口
            left++;
            // 进行窗口内数据的一系列更新
            ...
        }
    }
}
```

需要变化的地方

- 1、右指针右移之后窗口数据更新
- 2、判断窗口是否要收缩
- 3、左指针右移之后窗口数据更新
- 4、根据题意计算结果

## 示例

[minimum-window-substring](https://leetcode-cn.com/problems/minimum-window-substring/)

> 给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串

```c
string minWindow(string s, string t) {
    // needs存储t的<字符,出现次数>,windows存储<s中与t中字符相同的字符,出现次数>
    unordered_map<char, int> needs, window;

    for(char c : t) needs[c]++;

    int left = 0, right = 0; // 窗口
    int match = 0; // match匹配次数
    int start = 0, min = INT_MAX;
    while(right < s.size()){
         char c = s[right];
         right++;
         // 在需要的字符集里面，添加到窗口字符集里面
         if(needs.count(c)){
             window[c]++;
             // 如果当前字符的数量匹配需要的字符的数量，则match值+1
             if(window[c] == needs[c]){
                 match++;
             }
         }

         // 当所有字符数量都匹配之后，开始缩紧窗口
         while(match == needs.size()){
             // 获取结果
             if(right - left < min){
                 min = right - left;
                 start = left;
             }

             char d = s[left];
             left++;
             // 左指针指向不在需要字符集则直接跳过
             if(needs.count(d)){
                  // 左指针指向字符数量和需要的字符相等时，右移之后match值就不匹配则减一
                  // 因为win里面的字符数可能比较多，如有10个A，但需要的字符数量可能为3
                  // 所以在压死骆驼的最后一根稻草时，match才减一，这时候才跳出循环
                  if(window[d] == needs[d]){
                      match--;
                  }
                  window[d]--;
             }
         }
    }

    if(min == INT_MAX) return "";

    return s.substr(start, min);
}
```

[permutation-in-string](https://leetcode-cn.com/problems/permutation-in-string/)

> 给定两个字符串  **s1**  和  **s2**，写一个函数来判断  **s2**  是否包含  **s1 **的排列。

```c
bool checkInclusion(string s1, string s2) {
    unordered_map<char, int> needs, window;

    for(char c : s1) needs[c]++;

    int left = 0, right = 0, match = 0;
    while(right < s2.size()){
        char c = s2[right];
        right++;

        if(needs.count(c)){
            window[c]++;
            if(needs[c] == window[c]){
                match++;
            }
        }
        // 当窗口长度大于字符串长度，缩紧窗口
        while(right - left >= s1.size()){
            // 当窗口长度和字符串匹配，并且里面每个字符数量也匹配时，满足条件
            if(match == needs.size()) return true;

            char d = s2[left];
            left++;
            if(needs.count(d)){
                if(window[d] == needs[d]){
                    match--;
                }
                window[d]--;
            }
        }
    }

    return false;
}
```

[find-all-anagrams-in-a-string](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/)

> 给定一个字符串  **s **和一个非空字符串  **p**，找到  **s **中所有是  **p **的字母异位词的子串，返回这些子串的起始索引。

```c
vector<int> findAnagrams(string s, string p) {
    vector<int> res;
    if(p.size() > s.size())  return res;

    unordered_map<char, int> needs, window;
    for(char c : p) needs[c]++;

    int left = 0, right = 0, match = 0;
    while(right < s.size()){
        char c = s[right];
        right++;
        if(needs.count(c)){
            window[c]++;
            if(window[c] == needs[c]){
                match++;
            }
        }

        // 当窗口长度大于字符串长度，缩紧窗口
        while(right - left >= p.size()){
            // 当窗口长度和字符串匹配，并且里面每个字符数量也匹配时，满足条件
            if(right - left == p.size() && match == needs.size()){
                res.push_back(left);
            }
            char d = s[left];
            left++;
            if(needs.count(d)){
                if(window[d] == needs[d]){
                    match--;
                }
                window[d]--;
            }
        }  
    }

    return res;
}
```

[longest-substring-without-repeating-characters](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)

> 给定一个字符串，请你找出其中不含有重复字符的   最长子串   的长度。
> 示例  1:
>
> 输入: "abcabcbb"
> 输出: 3
> 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

```c
int lengthOfLongestSubstring(string s) {
      if(s.empty()) return 0;
      // 滑动窗口核心点：1、右指针右移 2、根据题意收缩窗口 3、左指针右移更新窗口 4、根据题意计算结果
      unordered_map<char,int> window;

      int left = 0, right = 0, ans = 1;
      while(right < s.size()){
          char c = s[right];
          right++;
          window[c]++;

          // 缩小窗口
          while(window[c] > 1){
              char d = s[left];
              left++;
              window[d]--;
          }
          // 计算结果
          ans = max(ans, right - left);
      }

      return ans;
}
```

## 总结

- 和双指针题目类似，更像双指针的升级版，滑动窗口核心点是维护一个窗口集，根据窗口集来进行处理
- 核心步骤
  - right 右移
  - 收缩
  - left 右移
  - 求结果

## 练习

- [x] [minimum-window-substring](https://leetcode-cn.com/problems/minimum-window-substring/)
- [x] [permutation-in-string](https://leetcode-cn.com/problems/permutation-in-string/)
- [x] [find-all-anagrams-in-a-string](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/)
- [x] [longest-substring-without-repeating-characters](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)
