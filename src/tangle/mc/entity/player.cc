#include <mc/entity/player.hh>

namespace tangle::mc::entity {

player::player(uint32_t eid, std::string name) 
: moving_entity(eid)
, m_name(name)
, m_pose(pose::standing) {}

pose player::get_pose() const {
    return m_pose;
}

void player::new_pose(pose new_pose) {
    m_pose = new_pose;
}

player::~player() {}

}