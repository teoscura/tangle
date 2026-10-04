#ifndef TANGLE_MC_MOVINGENTITY_H
#define TANGLE_MC_MOVINGENTITY_H

#include <common/vector.hh>
#include <mc/entity/base_entity.hh>

namespace tangle::mc::entity {

using namespace common;

class moving_entity : public base_entity {
    uint32_t m_hp;
    double3 m_pos;
    double3 m_vel;
    float2 m_look;
public:
    moving_entity(uint32_t eid);
    uint32_t hp() const;
    double3 pos() const;
    double3 vel() const;
    float2 look() const;
    virtual void set_hp(uint32_t new_hp);
    virtual void set_pos(double3 new_pos);
    virtual void set_vel(double3 new_vel);
    virtual void set_look(float2 new_look);
    virtual void on_rightclick() override = 0;
    virtual ~moving_entity();
};

}

#endif //TANGLE_MC_MOVINGENTITY_H