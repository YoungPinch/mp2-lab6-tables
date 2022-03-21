#pragma once
#include "tables.hpp"

class UnsortListTable final : public TTable {
private:
    TList<std::shared_ptr<PolinomObj>> list;
public:
    void Insert(std::shared_ptr<PolinomObj> obj) {
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
