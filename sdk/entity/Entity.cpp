#include "Entity.h"

Entity::Entity(EntityComponent *component) {
    Initialize();
    AddComponent(component);
}

Entity::Entity() {
    Initialize();
}

Entity::~Entity() {
    RemoveAllEntities();
    RemoveAllComponents();
}

void asd(VariantList *v) {

}

void Entity::Initialize() {
    GetFunction("OnDelete")->sig = std::bind(&Entity::OnDelete, this, _1);
}

Entity *Entity::AddEntity(Entity *entity) {
    entity->SetParent(this);
    m_children.push_back(entity);
    return entity;
}

EntityComponent *Entity::AddComponent(EntityComponent *component) {
    m_components.push_back(component);
    component->OnAdd(this);
    return component;
}

void Entity::RemoveAllEntities() {
    EntityListItor itor = m_children.begin();
    for (; itor != m_children.end();) {
        //done this way so entities that want to do searches through entity trees because some OnDelete sig
        //was run won't crash

        Entity *pTemp = (*itor);
        itor = m_children.erase(itor);
        delete pTemp;
    }

    m_children.clear();
}

void Entity::RemoveAllComponents() {
    ComponentListItor itor = m_components.begin();
    for (; itor != m_components.end(); itor++) {
        (*itor)->OnRemove();
        delete (*itor);
    }

    m_components.clear();
}

void Entity::OnDelete(VariantList *vList) {

}