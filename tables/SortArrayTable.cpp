#include "SortArrayTable.h"

void SortArrayTable::Rewrite(int index) {
  for (int i = index; i < row.size() - 1; i++)
    row[i] = row[i + 1];
}

std::shared_ptr<PolinomObj> SortArrayTable::Find(std::string key) {
  int left = 0;
  int right = size - 1;
  int mid = 0;
  while (left <= right) {
    mid = (right + left) / 2;
    if (key == row[mid].get()->GetName())
      return row[mid];
    else if (key > row[mid].get()->GetName())
      left = mid + 1;
    else
      right = mid - 1;
  }
  return nullptr;
}

void SortArrayTable::Insert(std::shared_ptr<PolinomObj> obj) {
  int left = 0;
  int right = size - 1;
  int mid = 0;
  while (left <= right) {
    mid = (right + left) / 2;
    if (obj.get()->GetName() == row[mid].get()->GetName())
      return;
    else if (obj.get()->GetName() > row[mid].get()->GetName())
      left = mid + 1;
    else
      right = mid - 1;
  }
  row[left] = obj;
}

void SortArrayTable::Delete(std::string key) {
  int left = 0;
  int right = size - 1;
  int mid = 0;
  while (left <= right) {
    mid = (right + left) / 2;
    if (key == row[mid].get()->GetName()) {
      delete row[mid].get();
      Rewrite(mid);
      break;
    }
    else if (key > row[mid].get()->GetName())
      left = mid + 1;
    else
      right = mid - 1;
  }   
}

void SortArrayTable::Print() {

}
