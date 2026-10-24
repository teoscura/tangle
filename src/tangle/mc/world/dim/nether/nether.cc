#include <mc/world/nether/nether_dimension.hh>

namespace tangle::mc::world::nether {

using namespace world;

nether_dimension::nether_dimension(eid_authority& auth, uint64_t seed, int2 spawn) 
: dimension(auth, spawn), m_worldgen() {
    (void) seed;
}

const worldgen& nether_dimension::get_worldgen() const {
    return m_worldgen;
}

};
