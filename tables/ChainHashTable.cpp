#include "tables.hpp"

const Polinom* ChainHashTable::Find(std::string key)
{
    int index = Hash(key);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
    {
        if ((it)->get()->getName() == key)
            return &it.cur->data.get()->getPol();
    }
    return nullptr;
}

unsigned int ChainHashTable::Hash(const std::string& key)
{
    unsigned int h = 0;
    for (char c : key)
        h = (h * 1664525) + c + 1013904223;
    return h % size;
}

void ChainHashTable::Insert(std::shared_ptr<PolinomObj> obj)
{
    if(Find(obj->getName()) == nullptr)
        return;
    else
    {
        int index = Hash(obj->getName());
        tables[index].InsertFirst(obj);
    }
}

void ChainHashTable::Delete(std::string key)
{
    int index = Hash(key);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
    {
        if ((it)->get()->getName() == key)
            return tables[index].Delete(it);
    }
}

void ChainHashTable::Print()
{

}