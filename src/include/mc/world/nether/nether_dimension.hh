#ifndef TANGLE_MC_WORLD_NETHER_NETHER_H
#define TANGLE_MC_WORLD_NETHER_NETHER_H

#include <mc/world/dimension.hh>

#include "mc/world/overworld/flatgen.hh"

namespace tangle::mc::world::nether {

using namespace world;

class nether_dimension : public dimension {
    //FIXME
    overworld::flatgen m_worldgen;
protected:
    virtual const worldgen& get_worldgen() const override;
public:
    nether_dimension(eid_authority& auth, uint64_t seed, int2 spawn);
};

}

#endif //TANGLE_MC_WORLD_NETHER_NETHER_H