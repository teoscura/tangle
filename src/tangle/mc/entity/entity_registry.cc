#include "mc/entity/base_entity.hh"
#include <mc/entity/entity_registry.hh>
#include <memory>

namespace tangle::mc::entity {
  
entity_registry::entity_registry(eid_authority& auth, std::size_t initial_size)
: m_auth(auth), m_entities(initial_size) {}

bool entity_registry::insert_entity(std::shared_ptr<base_entity> entity) {
    if(m_entities.contains(entity->eid())) return false;
    m_entities.insert_or_assign(entity->eid(), entity);
    return true;
}

std::shared_ptr<base_entity> entity_registry::get_entity(uint32_t eid) {
    auto it = m_entities.find(eid);
    return it == m_entities.end() ? nullptr : it->second;
}

bool entity_registry::exists_entity(uint32_t eid) const {
    return m_entities.contains(eid);
}

bool entity_registry::remove_entity(uint32_t eid) {
    auto it = m_entities.find(eid);
    if(it == m_entities.end()) return false;
    m_entities.erase(it);
    return true;
}

entity_registry::~entity_registry() {}

}