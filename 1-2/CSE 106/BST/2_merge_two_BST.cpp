//To merge two balanced Binary Search Trees (BSTs) into a single balanced BST in O(m + n) time, we can follow this efficient approach:
#include <iostream>
#include <vector>
using namespace std;

// Definition of a BST Node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Perform Inorder Traversal and store elements in a vector
void inorderTraversal(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}

// Merge two sorted arrays into one
vector<int> mergeSortedArrays(vector<int>& arr1, vector<int>& arr2) {
    vector<int> merged;
    int i = 0, j = 0;
    while (i < arr1.size() && j < arr2.size()) {
        if (arr1[i] < arr2[j])
            merged.push_back(arr1[i++]);
        else
            merged.push_back(arr2[j++]);
    }
    while (i < arr1.size()) merged.push_back(arr1[i++]);
    while (j < arr2.size()) merged.push_back(arr2[j++]);
    return merged;
}

// Construct a balanced BST from a sorted array
TreeNode* sortedArrayToBST(vector<int>& arr, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    TreeNode* root = new TreeNode(arr[mid]);
    root->left = sortedArrayToBST(arr, start, mid - 1);
    root->right = sortedArrayToBST(arr, mid + 1, end);
    return root;
}

// Merge two BSTs into a balanced BST
TreeNode* mergeBSTs(TreeNode* root1, TreeNode* root2) {
    vector<int> arr1, arr2;
    inorderTraversal(root1, arr1);
    inorderTraversal(root2, arr2);
    
    vector<int> mergedArr = mergeSortedArrays(arr1, arr2);
    
    return sortedArrayToBST(mergedArr, 0, mergedArr.size() - 1);
}

// Helper function to print Inorder traversal of BST
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

// Driver Code
int main() {
    TreeNode* root1 = new TreeNode(10);
    root1->left = new TreeNode(5);
    root1->right = new TreeNode(15);

    TreeNode* root2 = new TreeNode(20);
    root2->left = new TreeNode(12);
    root2->right = new TreeNode(25);

    TreeNode* mergedRoot = mergeBSTs(root1, root2);

    cout << "Inorder traversal of merged BST: ";
    printInorder(mergedRoot);
    cout << endl;

    return 0;
}
