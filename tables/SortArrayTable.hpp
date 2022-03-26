#pragma once
#include <vector>
#include "tables.hpp"

class SortArrayTable final : public TTable {
private:
  std::vector<std::shared_ptr<PolinomObj>> row;
  int size;

  void Rewrite(int index) {
    for (int i = index; i < row.size(); i++)
      row[i] = row[i + 1];
  }

public:
  SortArrayTable(int sz) : size(sz), row(size) {}

  std::shared_ptr<PolinomObj> Find(std::string key) override {
    int left = 0;
    int right = row.size() - 1;
    int mid = 0;
    while (left <= right) {
      mid = (right + left) / 2;
      if (key == row[mid].get()->getName())
        return row[mid];
      else if (key > row[mid].get()->getName())
        left = mid + 1;
      else
        right = mid - 1;
    }
    return nullptr;
  }

  void Insert(std::shared_ptr<PolinomObj> obj) override {
    int left = 0;
    int right = row.size() - 1;
    int mid = 0;
    while (left <= right) {
      mid = (right + left) / 2;
      if (obj.get()->getName() == row[mid].get()->getName())
        return;
      else if (obj.get()->getName() > row[mid].get()->getName())
        left = mid + 1;
      else
        right = mid - 1;
    }
    row[left] = obj;
  }

  void Delete(std::string key) override {
    int left = 0;
    int right = row.size() - 1;
    int mid = 0;
    bool isFound = false;
    while (left <= right) {
      mid = (right + left) / 2;
      if (key == row[mid].get()->getName()) {
        isFound = true;
        break;
      }
      else if (key > row[mid].get()->getName())
        left = mid + 1;
      else
        right = mid - 1;
    }
    if (isFound)
      delete row[mid].get();
    else if (row[right].get()->getName() == key) {

      // Нужно дописать

    }
  }

  void Print() override {

    // Нужно дописать

  }
};
