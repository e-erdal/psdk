#include "VariantDB.h"

FunctionObject *VariantDB::GetFunction(const std::string &name) {
    FunctionObject *fun = GetFunctionIfExists(name);

    if (!fun) {
        fun = new (FunctionObject);
        m_functionData[name] = fun;
    }

    return fun;
}

FunctionObject *VariantDB::GetFunctionIfExists(const std::string &name) {
    FunctionList_t::iterator itor = m_functionData.find(name);

    if (itor != m_functionData.end()) {
        return &((*itor->second));
    }
    return 0;
}

void VariantDB::CallFunctionIfExists(const std::string &name, VariantList *vlist) {
    FunctionObject *f = GetFunctionIfExists(name);
    if (f) {
        f->fun(vlist);
    }
}

Variant *VariantDB::GetVar(const std::string &name) {
    Variant *v = GetVarIfExists(name);

    if (!v) {
        v = new (Variant);
        m_data[name] = v;
    }

    return v;
}

Variant *VariantDB::GetVarIfExists(const std::string &name) {
    DataList_t::iterator itor = m_data.find(name);

    if (itor != m_data.end()) {
        return &((*itor->second));
    }

    return NULL;
}

Variant *VariantDB::GetVarWithDefault(const std::string &name, const Variant &vDef) {
    Variant *v = GetVarIfExists(name);

    if (!v) {
        v = new Variant(vDef);
        m_data[name] = v;
    }

    return v;
}

int VariantDB::DeleteVarsStartingWith(const std::string &deleteStr) {
    int deleted = 0;

    DataList_t::iterator itor = m_data.begin();

    while (itor != m_data.end()) {
        if (itor->first.compare(0, deleteStr.size(), deleteStr) == 0) {
            delete (itor->second);
            DataList_t::iterator itorTemp = itor;
            itor++;

            m_data.erase(itorTemp);
            deleted++;
            continue;
        }

        itor++;
    }

    return deleted;
}

int VariantDB::DeleteVar(const std::string &name) {
    int deleted = 0;

    DataList_t::iterator itor = m_data.begin();

    while (itor != m_data.end()) {
        if (itor->first == name) {
            delete (itor->second);
            DataList_t::iterator itorTemp = itor;
            itor++;

            m_data.erase(itorTemp);
            deleted++;
            continue;
        }

        itor++;
    }

    return deleted;
}