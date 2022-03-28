#include <iostream>

template <class TType>
class AVLTree {
private:

  struct TreeNode {
    TType data;
    TreeNode* pLeft;
    TreeNode* pRight;
    int bal; // balance value

    TreeNode(TType _data = {}) : data(_data) {
      pLeft = pRight = nullptr;
      bal = 0;
    }
  };

  TreeNode* pRoot;

  void rightRotation(TreeNode*& node) {
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
    TreeNode* pLeft = node->pLeft;
    TreeNode* pLeftRight = node->pLeft->pRight;
    pLeft->pRight = node;
    node->pLeft = pLeftRight;
    node = pLeft;
    balanceNode(node->pRight);
    balanceNode(node);
  }

  void leftRotation(TreeNode*& node) {
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
    TreeNode* pRight = node->pRight;
    TreeNode* pRightLeft = node->pRight->pLeft;
    pRight->pLeft = node;
    node->pRight = pRightLeft;
    node = pRight;
    balanceNode(node->pLeft);
    balanceNode(node);
  }

  int heightTreeNode(TreeNode*& node) {
    if (node == nullptr)
      return 0;
    int heightLeft = heightTreeNode(node->pLeft);
    int heightRight = heightTreeNode(node->pRight);
    if (heightLeft > heightRight)
      return heightLeft + 1;
    else
      return heightRight + 1;
  }

  int balanceNode(TreeNode*& node) {
    if (node != nullptr)
      node->bal = heightTreeNode(node->pRight) - heightTreeNode(node->pLeft);
    return node->bal;
  }

  void balanceTree(TreeNode*& node) {
    balanceNode(node);
    if (node->bal == -2) {
      if (balanceNode(node->pLeft) > 0)
        leftRotation(node->pLeft);
      rightRotation(node);
    }
    if (node->bal == 2) {
      if (balanceNode(node->pRight) < 0)
        rightRotation(node->pRight);
      leftRotation(node);
    }
  }

  TreeNode* findMinNode(TreeNode*& node) {
    if (node->pLeft != nullptr)
      return findMinNode(node->pLeft);
    return node;
  }

  TreeNode* deleteMinNode(TreeNode*& node) {
    if (node->pLeft == nullptr)
      return node->pRight;
    node->pLeft = deleteMinNode(node->pLeft);
    return;
  }

  void Insert(TType _data, TreeNode*& node) {
    if (node == nullptr) {
      node = new TreeNode(_data);
      return;
    }
    if (_data < node->data)
      Insert(_data, node->pLeft);
    else if (_data > node->data)
      Insert(_data, node->pRight);
    balanceTree(node);
  }

  TreeNode* FindNode(TType _data, TreeNode*& node) {
    if (node == nullptr)
      return nullptr;
    if (node->data == _data)
      return node;
    if (_data < node->data)
      return Find(_data, node->pLeft);
    if (_data > node->data)
      return Find(_data, node->pRight);
  }

  TType* Find(TType _data, TreeNode*& node) {
    return &FindNode(_data, node)->data;
  }

  void Delete(TType _data, TreeNode*& node) {
    if (node == nullptr)
      return;
    if (_data < node->data) {
      Delete(_data, node->pLeft);
    }
    if (_data > node->data) {
      Delete(_data, node->pRight);
    }
    if (_data == node->data) {
      TreeNode* pLeft = node->pLeft;
      TreeNode* pRight = node->pRight;
      delete node;
      if (pRight == nullptr)
        node = pLeft;
      TreeNode* tmp = findMinNode(pRight);
      tmp->pRight = deleteMinNode(pRight);
      tmp->pLeft = pLeft;
      balanceTree(tmp);
      return;
    }
    balanceTree(node);
  }

  void clear(TreeNode*& node) {
    if (node == nullptr)
      return;
    clear(node->pLeft);
    clear(node->pRight);
    delete node;
    node = nullptr;
  }

public:

  AVLTree() { pRoot = nullptr; }

  void Insert(TType _data) { Insert(_data, pRoot); }

  TType* Find(TType _data) { return Find(_data, pRoot); }

  void Delete(TType _data) { }

  int height() { return heightTreeNode(pRoot); }

  void print(TreeNode*& node) {
    static int tabs = 0;
    if (!node)
      return; //Если ветки не существует - выходим. Выводить нечего
    tabs += 5; //Иначе увеличим счетчик рекурсивно вызванных процедур
    //Который будет считать нам отступы для красивого вывода

    print(node->pLeft); //Выведем ветку и ее подветки слева

    for (int i = 0; i < tabs; i++) std::cout << " "; //Потом отступы
    std::cout << node->data << std::endl; //Данные этой ветки

    print(node->pRight);//И ветки, что справа

    tabs -= 5; //После уменьшим кол-во отступов
    return;
  }

  void print() { return print(pRoot); }

  ~AVLTree() { clear(pRoot); }

};
