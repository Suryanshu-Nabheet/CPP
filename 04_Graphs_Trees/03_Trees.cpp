/*
 * ZCO PREPARATION - TREES: Tree Data Structure and Algorithms
 * 
 * Binary trees, tree traversals, and common tree problems
 * Essential for tree-based problems
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
#include <map>
using namespace std;

// ===== BINARY TREE NODE =====
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ===== TREE TRAVERSALS =====

// 1. Inorder: Left -> Root -> Right
void inorder(TreeNode *root, vector<int> &result) {
    if(!root) return;
    inorder(root->left, result);
    result.push_back(root->val);
    inorder(root->right, result);
}

// 2. Preorder: Root -> Left -> Right
void preorder(TreeNode *root, vector<int> &result) {
    if(!root) return;
    result.push_back(root->val);
    preorder(root->left, result);
    preorder(root->right, result);
}

// 3. Postorder: Left -> Right -> Root
void postorder(TreeNode *root, vector<int> &result) {
    if(!root) return;
    postorder(root->left, result);
    postorder(root->right, result);
    result.push_back(root->val);
}

// 4. Level Order (BFS)
vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> result;
    if(!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while(!q.empty()) {
        int size = q.size();
        vector<int> level;
        
        for(int i = 0; i < size; i++) {
            TreeNode *node = q.front();
            q.pop();
            level.push_back(node->val);
            
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        
        result.push_back(level);
    }
    
    return result;
}

// Iterative traversals (using stack)
vector<int> inorderIterative(TreeNode *root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode *curr = root;
    
    while(curr || !st.empty()) {
        while(curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top();
        st.pop();
        result.push_back(curr->val);
        curr = curr->right;
    }
    
    return result;
}

// ===== TREE PROPERTIES =====

// Height of tree
int height(TreeNode *root) {
    if(!root) return -1;  // or 0 if counting nodes
    return 1 + max(height(root->left), height(root->right));
}

// Size of tree (number of nodes)
int size(TreeNode *root) {
    if(!root) return 0;
    return 1 + size(root->left) + size(root->right);
}

// Maximum element
int maxElement(TreeNode *root) {
    if(!root) return INT_MIN;
    return max({root->val, maxElement(root->left), maxElement(root->right)});
}

// Check if tree is balanced (difference in height <= 1)
int isBalancedHelper(TreeNode *root) {
    if(!root) return 0;
    
    int leftHeight = isBalancedHelper(root->left);
    if(leftHeight == -1) return -1;
    
    int rightHeight = isBalancedHelper(root->right);
    if(rightHeight == -1) return -1;
    
    if(abs(leftHeight - rightHeight) > 1) return -1;
    
    return 1 + max(leftHeight, rightHeight);
}

bool isBalanced(TreeNode *root) {
    return isBalancedHelper(root) != -1;
}

// Check if tree is symmetric
bool isSymmetricHelper(TreeNode *left, TreeNode *right) {
    if(!left && !right) return true;
    if(!left || !right) return false;
    if(left->val != right->val) return false;
    
    return isSymmetricHelper(left->left, right->right) &&
           isSymmetricHelper(left->right, right->left);
}

bool isSymmetric(TreeNode *root) {
    if(!root) return true;
    return isSymmetricHelper(root->left, root->right);
}

// ===== TREE SEARCH =====

// Search in BST
TreeNode* searchBST(TreeNode *root, int val) {
    if(!root || root->val == val) return root;
    
    if(val < root->val) {
        return searchBST(root->left, val);
    } else {
        return searchBST(root->right, val);
    }
}

// Find path from root to target
bool findPath(TreeNode *root, int target, vector<TreeNode*> &path) {
    if(!root) return false;
    
    path.push_back(root);
    
    if(root->val == target) return true;
    
    if(findPath(root->left, target, path) ||
       findPath(root->right, target, path)) {
        return true;
    }
    
    path.pop_back();
    return false;
}

// ===== LOWEST COMMON ANCESTOR (LCA) =====

TreeNode* lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if(!root || root == p || root == q) return root;
    
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    
    if(left && right) return root;  // p and q in different subtrees
    return left ? left : right;
}

// LCA for BST (optimized)
TreeNode* lowestCommonAncestorBST(TreeNode *root, TreeNode *p, TreeNode *q) {
    if(!root) return nullptr;
    
    if(p->val < root->val && q->val < root->val) {
        return lowestCommonAncestorBST(root->left, p, q);
    }
    if(p->val > root->val && q->val > root->val) {
        return lowestCommonAncestorBST(root->right, p, q);
    }
    
    return root;  // Root is LCA
}

// ===== DISTANCE IN TREE =====

// Distance between two nodes
int findDistance(TreeNode *root, int a, int b) {
    // Find LCA
    TreeNode* findNode(TreeNode* root, int val) {
        if(!root) return nullptr;
        if(root->val == val) return root;
        TreeNode *left = findNode(root->left, val);
        TreeNode *right = findNode(root->right, val);
        return left ? left : right;
    }
    
    int distanceFromRoot(TreeNode *root, int val) {
        if(!root) return -1;
        if(root->val == val) return 0;
        
        int left = distanceFromRoot(root->left, val);
        int right = distanceFromRoot(root->right, val);
        
        if(left == -1 && right == -1) return -1;
        return 1 + (left == -1 ? right : left);
    }
    
    TreeNode *lca = lowestCommonAncestor(root, 
                                         findNode(root, a),
                                         findNode(root, b));
    
    int distA = distanceFromRoot(lca, a);
    int distB = distanceFromRoot(lca, b);
    
    return distA + distB;
}

// ===== TREE CONSTRUCTION =====

// Build tree from inorder and preorder
TreeNode* buildTreeFromInPre(vector<int> &preorder, vector<int> &inorder, 
                            int &preIdx, int inStart, int inEnd) {
    if(inStart > inEnd) return nullptr;
    
    TreeNode *root = new TreeNode(preorder[preIdx++]);
    
    int inIdx = find(inorder.begin() + inStart, 
                     inorder.begin() + inEnd + 1, root->val) - inorder.begin();
    
    root->left = buildTreeFromInPre(preorder, inorder, preIdx, inStart, inIdx - 1);
    root->right = buildTreeFromInPre(preorder, inorder, preIdx, inIdx + 1, inEnd);
    
    return root;
}

// ===== PATH PROBLEMS =====

// Maximum path sum (path can start/end at any node)
int maxPathSumHelper(TreeNode *root, int &maxSum) {
    if(!root) return 0;
    
    int leftSum = max(0, maxPathSumHelper(root->left, maxSum));
    int rightSum = max(0, maxPathSumHelper(root->right, maxSum));
    
    maxSum = max(maxSum, root->val + leftSum + rightSum);
    
    return root->val + max(leftSum, rightSum);
}

int maxPathSum(TreeNode *root) {
    int maxSum = INT_MIN;
    maxPathSumHelper(root, maxSum);
    return maxSum;
}

// Path sum (root to leaf equals target)
bool hasPathSum(TreeNode *root, int targetSum) {
    if(!root) return false;
    if(!root->left && !root->right) {
        return targetSum == root->val;
    }
    
    return hasPathSum(root->left, targetSum - root->val) ||
           hasPathSum(root->right, targetSum - root->val);
}

// All paths from root to leaf
void findAllPaths(TreeNode *root, vector<int> &path, vector<vector<int>> &result) {
    if(!root) return;
    
    path.push_back(root->val);
    
    if(!root->left && !root->right) {
        result.push_back(path);
    } else {
        findAllPaths(root->left, path, result);
        findAllPaths(root->right, path, result);
    }
    
    path.pop_back();
}

vector<vector<int>> allPaths(TreeNode *root) {
    vector<vector<int>> result;
    vector<int> path;
    findAllPaths(root, path, result);
    return result;
}

// ===== VIEW PROBLEMS =====

// Left view
void leftView(TreeNode *root, int level, vector<int> &result) {
    if(!root) return;
    
    if(level == result.size()) {
        result.push_back(root->val);
    }
    
    leftView(root->left, level + 1, result);
    leftView(root->right, level + 1, result);
}

vector<int> leftView(TreeNode *root) {
    vector<int> result;
    leftView(root, 0, result);
    return result;
}

// Right view
void rightView(TreeNode *root, int level, vector<int> &result) {
    if(!root) return;
    
    if(level == result.size()) {
        result.push_back(root->val);
    }
    
    rightView(root->right, level + 1, result);
    rightView(root->left, level + 1, result);
}

// Top view (using level order with horizontal distance)
struct NodeHD {
    TreeNode *node;
    int hd;  // Horizontal distance
    NodeHD(TreeNode *n, int h) : node(n), hd(h) {}
};

vector<int> topView(TreeNode *root) {
    if(!root) return {};
    
    map<int, int> m;  // {hd, value}
    queue<NodeHD> q;
    q.push(NodeHD(root, 0));
    
    while(!q.empty()) {
        NodeHD curr = q.front();
        q.pop();
        
        if(m.find(curr.hd) == m.end()) {
            m[curr.hd] = curr.node->val;
        }
        
        if(curr.node->left) {
            q.push(NodeHD(curr.node->left, curr.hd - 1));
        }
        if(curr.node->right) {
            q.push(NodeHD(curr.node->right, curr.hd + 1));
        }
    }
    
    vector<int> result;
    for(auto &p : m) {
        result.push_back(p.second);
    }
    
    return result;
}

// ===== MAIN FUNCTION =====
int main() {
    // Create sample tree
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   6
    
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    
    cout << "Inorder: ";
    vector<int> in;
    inorder(root, in);
    for(int x : in) cout << x << " ";
    cout << endl;
    
    cout << "Height: " << height(root) << endl;
    cout << "Size: " << size(root) << endl;
    
    cout << "Level Order:" << endl;
    vector<vector<int>> levels = levelOrder(root);
    for(auto &level : levels) {
        for(int x : level) cout << x << " ";
        cout << endl;
    }
    
    return 0;
}

