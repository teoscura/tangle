#include <mc/entity/base_entity.hh>

namespace tangle::mc::entity {

base_entity::base_entity(uint32_t eid)
: m_eid(eid) {}
    
uint32_t base_entity::eid() const {
    return m_eid;
}

base_entity::~base_entity() {}

}