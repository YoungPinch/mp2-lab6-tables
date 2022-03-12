#include <tables.hpp>
#define STEP 7

class UnsortListTable final : public TTable {
private:
  TList<PolinomObj*> list;
public:
    void Insert(PolinomObj* obj) {
        list.InsertFirst(obj);
    }
    const Polinom& Find(std::string name) {
        for(auto it = list.cbegin(); it != list.cend(); ++it)
            if((*it)->name == name)
                return (*it)->pol;
        throw -1;
    }
    void Delete(std::string _name){
        for(auto it = list.cbegin(); it != list.cend(); ++it)
            if((*it)->name == _name)
                list.Delete(it);
    }
};

class OpenHashTable final : public TTable {
private:
    struct Bucket{
        PolinomObj* po;
        bool isDeleted;
    }
    Backet *table;
    int memSize;
    int size;
    int Hash(std::string key){
        int h = 0, p = 31, p_pow = 1;
        for(char c: key){
            h = (h + (c - '0' + 1) * p_pow) % memSize;
            p_pow = (p_pow * p) % memSize;
        }
        return (h % memSize + memSize) % memSize;
    }
public:
    OpenHashTable(int n){
        Table = new Bucket[n]{nullptr, false};
        memSize = n;
        size = 0;
    }
    void Insert(PolinomObj* obj) {
        int h = Hash(obj->name);
        while(!table[h].isDeleted)
            if(table[h].po == nullptr)
                break;
            if(table[h].po->name != obl->name)
                h = (h + STEP) % memSize;
            else
                throw -1;
        
        table[h] = Bucket{obj, false};
    }
    const Polinom& Find(std::string name) {
        h = Hash(name);
        while(!table[h].isDeleted)
            if(table[h].po == nullptr)
                throw -1;
            if(table[h].po->name != obl->name)
                h = (h + STEP) % memSize;
            else
                return *(table[h]->po->pol);
        throw -1;
    }
    void Delete(std::string _name){
        h = Hash(name);
        while(!table[h].isDeleted)
            if(table[h].po == nullptr)
                return;
            if(table[h].po->name != obl->name)
                h = (h + STEP) % memSize;
            else
                table[h].isDeleted = true;
    }
    ~OpenHashTable(){
        delete[] table;
    }
};
