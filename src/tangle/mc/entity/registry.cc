#include <mc/entity/registry.hh>

#include <memory>

#include "mc/entity/base_entity.hh"

namespace tangle::mc::entity {
  
registry::registry(eid_authority& auth, std::size_t initial_size)
: m_auth(auth), m_entities(initial_size) {}

bool registry::insert_entity(std::shared_ptr<base_entity> entity) {
    if(m_entities.contains(entity->eid())) return false;
    m_entities.insert_or_assign(entity->eid(), entity);
    return true;
}

std::shared_ptr<base_entity> registry::get_entity(uint32_t eid) {
    auto it = m_entities.find(eid);
    return it == m_entities.end() ? nullptr : it->second;
}

bool registry::exists_entity(uint32_t eid) const {
    return m_entities.contains(eid);
}

bool registry::remove_entity(uint32_t eid) {
    auto it = m_entities.find(eid);
    if(it == m_entities.end()) return false;
    m_entities.erase(it);
    return true;
}

registry::~registry() {}

}