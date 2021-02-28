//
// Created on February 12th 2021 by loanselot1.
//
// Purpose: Database for "variants".
//

#pragma once

#include <unordered_map>

#include "VariantList.h"

#include <functional>

struct FunctionObject {
    std::function<void(VariantList *)> fun;

    template <class Fun>
    void Bind(Fun &f) {
        fun = f;
    }
};

typedef std::unordered_map<std::string, Variant *> DataList_t;
typedef std::unordered_map<std::string, FunctionObject *> FunctionList_t;

class VariantDB {
public:
    VariantDB() {
    }

    virtual ~VariantDB() {
    }

    FunctionObject *GetFunction(const std::string &name);
    FunctionObject *GetFunctionIfExists(const std::string &name);

    void CallFunctionIfExists(const std::string &name, VariantList *vlist);

    Variant *GetVar(const std::string &name);
    Variant *GetVarIfExists(const std::string &name);
    Variant *GetVarWithDefault(const std::string &name, const Variant &vDef);

    int DeleteVarsStartingWith(const std::string &deleteStr);
    int DeleteVar(const std::string &name);

private:
    DataList_t m_data;
    FunctionList_t m_functionData;
    DataList_t::iterator m_nextItor;
};