#ifndef TANGLE_MC_BLOCKENTITY_H
#define TANGLE_MC_BLOCKENTITY_H

#include <common/vector.hh>
#include <mc/entity/base_entity.hh>

namespace tangle::mc::entity {

using namespace common;

class block_entity : public base_entity {
    int3 m_pos;
public:
    block_entity(uint32_t eid);
    int3 pos() const;
    void set_pos(int3 new_pos);
    virtual void tick() = 0;
    virtual ~block_entity();
};

}

#endif //TANGLE_MC_BLOCKENTITY_H