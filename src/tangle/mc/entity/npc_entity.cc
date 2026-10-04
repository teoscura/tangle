#include "mc/entity/moving_entity.hh"
#include <mc/entity/npc_entity.hh>

namespace tangle::mc::entity {

npc_entity::npc_entity(uint32_t eid) 
: moving_entity(eid) {}

npc_entity::~npc_entity() {}

}