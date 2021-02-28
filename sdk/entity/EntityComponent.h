//
// Created on February 28th 2021 by loanselot1.
//
// Purpose:
//

#pragma once

#include "pch.h"

#include "variant/VariantDB.h"

class Entity;

class EntityComponent {
public:
    EntityComponent();
    virtual ~EntityComponent();
    EntityComponent(const std::string &name);

    void SetName(const std::string &name);

    std::string GetName() {
        return m_name;
    }

    virtual void OnAdd(Entity *entity);
    virtual void OnRemove();

    Entity *GetParent() {
        return m_parent;
    }

    VariantDB *GetShared() {
        return &m_sharedDB;
    }

    Variant *GetVar(const std::string &varName) {
        return m_sharedDB.GetVar(varName);
    }

    Variant *GetVarWithDefault(const std::string &varName, const Variant &var) {
        return m_sharedDB.GetVarWithDefault(varName, var);
    }

    FunctionObject *GetFunction(const std::string &funcName) {
        return m_sharedDB.GetFunction(funcName);
    }

private:
    std::string m_name;
    Entity *m_parent;
    VariantDB m_sharedDB;
};

typedef std::list<EntityComponent *> ComponentList;
typedef std::list<EntityComponent *>::iterator ComponentListItor;