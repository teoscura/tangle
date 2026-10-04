#ifndef TANGLE_MC_ENTITY_AUTHORITY_H
#define TANGLE_MC_ENTITY_AUTHORITY_H

#include <atomic>
#include <cstdint>

namespace tangle::mc::entity {

class eid_authority {
    std::atomic<uint32_t> m_next;
public:
    eid_authority(uint32_t last);
    uint32_t get_next();
};

}

#endif //TANGLE_MC_ENTITY_AUTHORITY_H