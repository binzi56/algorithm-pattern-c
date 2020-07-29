# 递归

## 介绍

将大问题转化为小问题，通过递归依次解决各个小问题

## 示例

[reverse-string](https://leetcode-cn.com/problems/reverse-string/)

> 编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组  `char[]`  的形式给出。

```c
void reverseString(vector<char>& s) {
		vector<char> res;
		reveseHandle(s, 0, res);
		for(int i = 0; i < s.size(); i++){
				s[i] = res[i];
		}
}

void reveseHandle(vector<char> &s, int i, vector<char>& res){
			if(i == s.size()) return;
			reveseHandle(s, i + 1, res);
			res.push_back(s[i]);
}
```

[swap-nodes-in-pairs](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)

> 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
> **你不能只是单纯的改变节点内部的值**，而是需要实际的进行节点交换。

```c
ListNode* swapPairs(ListNode* head) {
		// 思路：将链表翻转转化为一个子问题，然后通过递归方式依次解决
		// 先翻转两个，然后将后面的节点继续这样翻转，然后将这些翻转后的节点连接起来
		return swap(head);
}

ListNode *swap(ListNode *head){
		if(head == NULL || head->next == NULL){
				return head;
		}

		// 保存下一阶段的头指针
		ListNode *nextNode = head->next->next;
		// 翻转当前阶段指针
		ListNode *curNode = head->next;
		curNode->next = head;
		head->next = swap(nextNode);
		return curNode;
}
```

[unique-binary-search-trees-ii](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/)

> 给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。

```c
vector<TreeNode*> generateTrees(int n) {
		 if(n <= 0) return vector<TreeNode*>();
		 return generateHandle(1, n);
 }
 vector<TreeNode*> generateHandle(int start, int end){
		 vector<TreeNode *> res;
		 if(start > end) {
				 res.push_back(NULL);
				 return res;
		 }

		 for(int i = start; i <= end; i++){
					// 递归生成所有左右子树
					vector<TreeNode *> lefts(generateHandle(start, i - 1));
					vector<TreeNode *> rights(generateHandle(i + 1, end));
					// 拼接左右子树后返回
					for(TreeNode *left : lefts){
							for(TreeNode *right : rights){
									TreeNode *root = new TreeNode(i);
									root->left = left;
									root->right = right;
									res.push_back(root);
							}
					}
		 }
		 return res;
 }
```

## 递归+备忘录

[fibonacci-number](https://leetcode-cn.com/problems/fibonacci-number/)

> 斐波那契数，通常用  F(n) 表示，形成的序列称为斐波那契数列。该数列由  0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：
> F(0) = 0,   F(1) = 1
> F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
> 给定  N，计算  F(N)。

```c
unordered_map<int, int> mp;
int fib(int N) {
	 return dfs(N);
}

int dfs(int n){
		if(n <= 1) return n;
		// 读取缓存
		if(mp[n] != 0) return mp[n];

		int ans = dfs(n - 1) + dfs(n - 2);
		//缓存计算过的值
		mp[n] = ans;
		return ans;
}
```

## 练习

- [ ] [reverse-string](https://leetcode-cn.com/problems/reverse-string/)
- [ ] [swap-nodes-in-pairs](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)
- [x] [unique-binary-search-trees-ii](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/)
- [ ] [fibonacci-number](https://leetcode-cn.com/problems/fibonacci-number/)
