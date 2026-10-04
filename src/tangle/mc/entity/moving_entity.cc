#include <mc/entity/moving_entity.hh>

#include <common/vector.hh>

namespace tangle::mc::entity {

using namespace common;

moving_entity::moving_entity(uint32_t eid) 
: base_entity(eid) {}

uint32_t moving_entity::hp() const {
    return m_hp;
}

double3 moving_entity::pos() const {
    return m_pos;
}

double3 moving_entity::vel() const {
    return m_vel;
}

float2 moving_entity::look() const {
    return m_look;
}

void moving_entity::set_hp(uint32_t new_hp) {
    m_hp = new_hp; 
}

void moving_entity::set_pos(double3 new_pos) {
    m_pos = new_pos; 
}

void moving_entity::set_vel(double3 new_vel) {
    m_vel = new_vel; 
}

void moving_entity::set_look(float2 new_look) {
    m_look = new_look; 
}

moving_entity::~moving_entity() {}

}