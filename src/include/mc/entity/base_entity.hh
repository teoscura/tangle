#ifndef TANGLE_MC_ENTITY_H
#define TANGLE_MC_ENTITY_H

#include <cstdint>

namespace tangle::mc::entity {

class base_entity {
    uint32_t m_eid;
public:
    base_entity(uint32_t eid);
    uint32_t eid() const;
    virtual void on_rightclick() = 0;
    virtual ~base_entity();
};

}

#endif //TANGLE_MC_ENTITY_H