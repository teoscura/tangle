#ifndef TANGLE_MC_NPCENTITY_H
#define TANGLE_MC_NPCENTITY_H

#include <common/vector.hh>
#include <mc/entity/moving_entity.hh>

namespace tangle::mc::entity {

using namespace common;

class npc_entity : public moving_entity {
public:
    npc_entity(uint32_t eid);
    virtual void tick() = 0;
    virtual void trigger() = 0;
    virtual ~npc_entity();
};

}

#endif //TANGLE_MC_NPCENTITY_H