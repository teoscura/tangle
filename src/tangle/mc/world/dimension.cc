#include <mc/world/dimension.hh>

namespace tangle::mc::world {

using namespace common;

dimension::dimension(eid_authority& auth, int2 spawn)
: m_auth(auth), m_spawnpoint(spawn) {

}

void dimension::spin_up(int2 region_coords) {
    if(m_region.contains(region_coords)) {
        //FIXME No need to spin up.
        return;
    }
}

void dimension::spin_down(int2 region_coords) {
    if(!m_region.contains(region_coords)) {
        //FIXME No need to spin down.
        return;
    }
    m_region.at(region_coords)->halt_and_save();

}

eid_authority& dimension::auth() {
    return m_auth;
}

bool dimension::pass_entity(std::shared_ptr<base_entity>, int2 dest_chunk) {
    //FIXME
    (void) dest_chunk;
    return true;
}

std::shared_ptr<region> dimension::get_region_in_charge(int2 chunk) {
    //FIXME
    (void) chunk;
    return nullptr;
}

}