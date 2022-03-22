#pragma once
#include "tables.hpp"

class OpenHashTable final : public TTable {
private:
  struct Bucket {
    std::shared_ptr<PolinomObj> po;
    bool isDeleted;
  };

    Bucket *table;
    unsigned int memSize;
    unsigned int size;
    unsigned int step = 7;

    unsigned int Hash(std::string key){ // HashLy
        unsigned int h = 0;

        for(char c: key)
            h = (h * 1664525) + c + 1013904223;
        
        return h % memSize;
    }
public:
    OpenHashTable(){
        MAX_SIZE = 24;
        table = new Bucket[MAX_SIZE]{nullptr, false};
        memSize = MAX_SIZE;
        size = 0;
    }
    void Insert(std::shared_ptr<PolinomObj> obj) {
        if(size == memSize)
            throw -1;
        unsigned int h = Hash(obj->name);
        while(!table[h].isDeleted)
            if(table[h].po == nullptr)
                break;
            if(table[h].po->name == obj->name)
                throw -1; // already exist
            else
                h = (h + step) % memSize;
        
        table[h] = Bucket{obj, false};
        ++size;
    }
    const Polinom& Find(std::string name) {
        unsigned int h = Hash(name), i = 0;
        while(!(table[h].isDeleted || i == size))
            if(table[h].po == nullptr)
                throw -1;
            if(table[h].po->name == name)
                return *(table[h]->po->pol);
            else{
                h = (h + step) % memSize;
                ++i;
            }
        throw -1;
    }
    void Delete(std::string _name){
        unsigned int h = Hash(name), i = 0;
        while(!(table[h].isDeleted || i == size))
            if(table[h].po == nullptr)
                return;
            if(table[h].po->name == obl->name){
                table[h].isDeleted = true;
                --size;
            }else{
                h = (h + step) % memSize;
                ++i;
            }
    }
    ~OpenHashTable(){
        delete[] table;
    }
};
