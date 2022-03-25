#include "tables.hpp"

const Polinom* SortArrayTable::Find(std::string key)
{
    int left = 0;
    int right = row.size() - 1;
    int mid = 0;
    while (left <= right)
    {
        mid = (right + left) / 2;
        if (key == row[mid].get()->getName())
            return &row[mid].get()->getPol();
        else if (key > row[mid].get()->getName())
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return nullptr;
}


void SortArrayTable::Insert(std::shared_ptr<PolinomObj> obj)
{
    int left = 0;
    int right = row.size() - 1;
    int mid = 0;
    while (left <= right)
    {
        mid = (right + left) / 2;
        if (obj.get()->getName() == row[mid].get()->getName())
            return;
        else if (obj.get()->getName() > row[mid].get()->getName())
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    row[left] = obj;
}

void SortArrayTable::Rewrite(int index)
{
    for (int i = index; i < row.size(); i++)
    {
        row[i] = row[i + 1];
    }
}

void SortArrayTable::Delete(std::string key)
{
    int left = 0;
    int right = row.size() - 1;
    int mid = 0;
    bool isFound = false;
    while (left <= right)
    {
        mid = (right + left) / 2;
        if (key == row[mid].get()->getName())
        {
            isFound = true;
            break;
        }
        else if (key > row[mid].get()->getName())
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    if (isFound)
    {
        delete row[mid].get();
        
    }
    else if (row[right].get()->getName() == key)
    {

    }
    
}

void SortArrayTable::Print()
{

}