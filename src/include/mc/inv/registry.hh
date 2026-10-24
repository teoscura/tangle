#ifndef TANGLE_MC_INVENTORY_REGISTRY_H
#define TANGLE_MC_INVENTORY_REGISTRY_H

#include <atomic>
#include <memory>
#include <unordered_map>

#include <mc/inv/inventory.hh>

namespace tangle::mc::inv {

class registry {
    std::unordered_map<uint64_t, std::shared_ptr<inventory>> m_invs;
    std::unordered_map<uint32_t, uint64_t> m_einvs;
    std::atomic<uint64_t> m_next;
public:
    registry(std::size_t size);
    std::shared_ptr<inventory> get_entityinv(uint32_t eid);
    std::shared_ptr<inventory> get_inventory(uint64_t inv_id);
    uint64_t add_inv(std::shared_ptr<uint64_t> inv);
    bool set_einv(uint32_t eid, std::shared_ptr<inventory> inv);
    bool link_inventory(uint64_t inv_id, uint32_t eid);
};

}

#endif //TANGLE_MC_INVENTORY_REGISTRY_H