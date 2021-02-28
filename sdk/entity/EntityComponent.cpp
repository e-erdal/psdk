#include "EntityComponent.h"

EntityComponent::EntityComponent() {
    m_parent = NULL;
}

EntityComponent::~EntityComponent() {
    if (!m_parent) {
        OnRemove();
    }
}
EntityComponent::EntityComponent(const std::string &name) {
    SetName(name);
}
void EntityComponent::SetName(const std::string &name) {
    m_name = name;
}

void EntityComponent::OnAdd(Entity *pEnt) {
    m_parent = pEnt;
}

void EntityComponent::OnRemove() {
    FunctionObject *fun = GetShared()->GetFunctionIfExists("OnDelete");
    if (fun) {
        VariantList v(this);
        fun->sig(&v);
    }
}