#pragma once
#include "tables.hpp"

class UnsortListTable final : public TTable {
private:
    TList<std::shared_ptr<PolinomObj>> list;
public:
    UnsortListTable() {
        MAX_SIZE = 16;
    }
    void Insert(std::shared_ptr<PolinomObj> obj) {
        if (list.GetSize() == MAX_SIZE)
            throw - 1;
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
