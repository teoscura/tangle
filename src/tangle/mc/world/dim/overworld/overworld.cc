#include <mc/world/overworld/overworld_dimension.hh>

namespace tangle::mc::world::overworld {

using namespace world;

overworld_dimension::overworld_dimension(eid_authority& auth, uint64_t seed, int2 spawn) 
: dimension(auth, spawn), m_worldgen() {
    (void) seed;
}

const worldgen& overworld_dimension::get_worldgen() const {
    return m_worldgen;
}

};