# 二叉搜索树

## 定义

- 每个节点中的值必须大于（或等于）存储在其左侧子树中的任何值。
- 每个节点中的值必须小于（或等于）存储在其右子树中的任何值。

## 应用

[validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)

> 验证二叉搜索树

```c
//二叉搜索树中序遍历:递增序列
long pre = LONG_MIN;
bool isValidBST(TreeNode* root) {
    if(!root) return true;

    if(!isValidBST(root->left)) return false;

    if(root->val <= pre) return false;

    pre = root->val;

    return isValidBST(root->right);
}
```

[insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)

> 给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 保证原始二叉搜索树中不存在新值。

```c
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if(root == NULL) return new TreeNode(val);

    if(root->val < val){
        root->right = insertIntoBST(root->right, val);
    }else{
        root->left = insertIntoBST(root->left, val);
    }

    return root;
}
```

[delete-node-in-a-bst](https://leetcode-cn.com/problems/delete-node-in-a-bst/)

> 给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的  key  对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。

```c
TreeNode* deleteNode(TreeNode* root, int key) {
    // 删除节点分为三种情况：
    // 1、只有左节点 替换为右
    // 2、只有右节点 替换为左
    // 3、有左右子节点 左子节点连接到右边最左节点即可
    if(root == NULL) return root;

    if(root->val < key){
        root->right = deleteNode(root->right, key);
    }else if(root->val > key){
        root->left = deleteNode(root->left, key);
    }else{
        if(root->left == NULL){
            return root->right;
        }else if(root->right == NULL){
            return root->left;
        }else{
            TreeNode *cur = root->right;
            while(cur->left != NULL){
                cur = cur->left;
            }
            cur->left = root->left;
            return root->right;
        }
    }

    return root;
}
```

[balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)

> 给定一个二叉树，判断它是否是高度平衡的二叉树。

```c
/*
 自底向上
     遍历到最底部，开始从零计算从叶节点开始向上的高度
     每个节点都对比左右子树的高度
 */
int box(TreeNode* root){
    if(!root)   return 0;

    int l = box(root -> left);
    int r = box(root -> right);

    if(l == -1 || r == -1) return -1;

    return abs(l - r) < 2 ? max(l, r) + 1 : - 1;
}
bool isBalanced(TreeNode* root) {
    return box(root) != -1;
}

/*
 自顶向下
     每个节点都计算且对比左右子树的高度
     此方法会重复计算
 */
int depth(TreeNode* root){
    if(!root)   return 0;
    return max(depth(root -> left), depth(root -> right)) + 1;
}
bool isBalanced(TreeNode* root) {
    if(!root)   return true;
    return abs(depth(root -> left) - depth(root -> right)) < 2 && isBalanced(root -> left) && isBalanced(root -> right);
}
```

## 练习

- [ ] [validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)
- [ ] [insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)
- [ ] [delete-node-in-a-bst](https://leetcode-cn.com/problems/delete-node-in-a-bst/)
- [ ] [balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)
