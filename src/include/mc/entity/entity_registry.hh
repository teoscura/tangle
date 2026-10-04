#ifndef TANGLE_MC_ENTITY_REGISTRY_H
#define TANGLE_MC_ENTITY_REGISTRY_H

#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>

#include <mc/entity/base_entity.hh>
#include <mc/entity/eid_authority.hh>

namespace tangle::mc::entity {

class entity_registry {
    eid_authority& m_auth;
    std::unordered_map<uint32_t, std::shared_ptr<base_entity>> m_entities;
    std::vector<uint32_t> m_block_entities;
    std::vector<uint32_t> m_moving_entities;
    std::vector<uint32_t> m_npc_entities;
    std::vector<uint32_t> m_players;
public: 
    entity_registry(eid_authority& auth, std::size_t initial_size); 
    bool insert_entity(std::shared_ptr<base_entity> entity);
    std::shared_ptr<base_entity> get_entity(uint32_t eid);
    bool exists_entity(uint32_t eid) const;
    bool remove_entity(uint32_t eid);
    ~entity_registry();
};

}

#endif //TANGLE_MC_ENTITY_REGISTRY_H