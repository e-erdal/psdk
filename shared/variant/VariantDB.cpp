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