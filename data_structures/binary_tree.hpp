
template <class TType>
class BinaryTree
{
private:
  struct TreeNode
  {
    TType data;
    TreeNode* pLeft, pRight;
    TreeNode();
  };

  Node* pFirst;
  int size;

public:

  BinaryTree() : pFirst(nullptr), pLast(nullptr), size(0) {}

  ~BinaryTree() { clear(); }

  BinaryTree(const TList& list);

  TList& operator=(const TList& list);

  int get_size() const noexcept { return size; } // Получение значения размера списка

  bool is_empty() const noexcept { return size == 0; } // Проверка на пустоту

  void clear();

};

