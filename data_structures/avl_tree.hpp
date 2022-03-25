
template <class TType>
struct TreeNode {
  TType data;
  TreeNode* pLeft;
  TreeNode* pRight;
  int bal; // balance value

  TreeNode(TType _data) : data(_data) {
    pLeft = pRight = nullptr;
    bal = 0;
  }

};

template <class TType>
class AVLTree {
private:

  TreeNode* pRoot;

  void rightRotation(TreeNode<TType>* node) {
    /*
    Right Rotation

    Before:
                    node
                   /    \
              pLeft      pRight
             /     \
    pLeftLeft       pLeftRight

    After:
                 pLeft
                /     \
       pLeftLeft       node
                      /    \
            pLeftRight      pRight
    */
    TreeNode<TType>* pLeft = node->pLeft;
    pLeft->pRight = node;
    node->pLeft = pLeft->pRight;
    node = pLeft;
    balanceNode(node->pRight);
    balanceNode(node);
  }

  void leftRotation(TreeNode<TType>* node) {
    /*
    Left Rotation

    Before:
          node
         /    \
    pLeft      pRight
              /      \
    pRightLeft        pRightRight

    After:
               pRight
              /      \
          node        pRightRight
         /    \
    pLeft      pRightLeft
    */
    TreeNode<TType>* pRight = node->pRight;
    pRight->pLeft = node;
    node->pRight = node->pRight->pLeft;
    node = pRight;
    balanceNode(node->pLeft);
    balanceNode(node);
  }

  int heightTreeNode(TreeNode<TType>* node) {
    if (this == nullptr)
      return 0;
    int heightLeft = heightTreeNode(node->pLeft);
    int heightRight = heightTreeNode(node->pRight);
    if (heightLeft > heightRight)
      return heightLeft + 1;
    else
      return heightRight + 1;
  }

  void balanceNode(TreeNode<TType>* node) {
    if (node != nullptr)
      bal = heightTreeNode(pRight) - heightTreeNode(pLeft);
  }

  void clear(TreeNode<TType>* node) {
    if (node == nullptr)
      return;
    clear(node->pLeft);
    clear(node->pRight);
    delete node;
    node = nullptr;
  }

  void Insert(TType& _data, TreeNode<TType>* node) {
    if (node == nullptr) {
      node = new TreeNode<TType>(_data);
      return;
    }
    if (_data < node->data) {
      Insert(_data, node->pLeft);
      if (node->bal < -1) {
        if (node->pLeft->bal > 0)
          leftRotation(node->pLeft);
        rightRotation(node);
      }
    }
    else if (_data > node->data)
    {
      Insert(_data, node->pRight);
      if (node->bal > 1) {
        if (node->pRight->bal < 0)
          rightRotation(node->pRight);
        leftRotation(node);
      }
    }
    balanceNode(node);
  }

public:

  BinaryTree() { pRoot = nullptr; }

  void Insert(TType& _data) { Insert(_data, pRoot); }

  int height() { return heightTreeNode(pRoot); }

  ~BinaryTree() { clear(pRoot); }

};
