//
// Created on February 28th 2021 by loanselot1.
//
// Purpose:
//

#pragma once

#include "pch.h"

#include "EntityComponent.h"

class Entity;

typedef std::list<Entity *> EntityList;
typedef std::list<Entity *>::iterator EntityListItor;

class EntityCall {
public:
    Entity *handler;
    glm::vec2 updatedVec;
};

class Entity {
public:
    Entity(EntityComponent *component);
    Entity();
    ~Entity();

    void Initialize();

    Entity *AddEntity(Entity *entity);
    EntityComponent *AddComponent(EntityComponent *component);

    void RemoveAllEntities();
	void RemoveAllComponents();

public:
    VariantDB *GetShared() {
        return &m_sharedDB;
    }

    Variant *GetVar(const std::string &name) {
        return m_sharedDB.GetVar(name);
    }

    Variant *GetVarWithDefault(const std::string &name, const Variant &var) {
        return m_sharedDB.GetVarWithDefault(name, var);
    }

    FunctionObject *GetFunction(const std::string &name) {
        return m_sharedDB.GetFunction(name);
    }

    void CallFunction(const std::string &name, VariantList *vList) {
        return m_sharedDB.CallFunctionIfExists(name, vList);
    }

    Entity *GetParent() {
        return m_parent;
    }

    void SetParent(Entity *entity) {
        m_parent = entity;
    }

    EntityList *GetChildren() {
        return &m_children;
    }

    ComponentList *GetComponents() {
        return &m_components;
    }

private:
    void OnDelete(VariantList *vList);

private:
    EntityList m_children;
    ComponentList m_components;

    VariantDB m_sharedDB;
    Entity *m_parent = 0;

    Variant *m_posCache = 0;
};