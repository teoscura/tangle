#include <mc/entity/block_entity.hh>

namespace tangle::mc::entity {

block_entity::block_entity(uint32_t eid) 
: base_entity(eid) {}
    
int3 block_entity::pos() const {
    return m_pos;
}

void block_entity::set_pos(int3 new_pos) {
    m_pos = new_pos;
}

block_entity::~block_entity() {}

}