#ifndef TANGLE_MC_WORLD_OVERWORLD_OVERWORLD_H
#define TANGLE_MC_WORLD_OVERWORLD_OVERWORLD_H

#include <mc/world/dimension.hh>
#include <mc/world/overworld/flatgen.hh>

namespace tangle::mc::world::overworld {

using namespace world;

class overworld_dimension : public dimension {
    flatgen m_worldgen;
protected:
    virtual const worldgen& get_worldgen() const override;
public:
    overworld_dimension(eid_authority& auth, uint64_t seed, int2 spawn);
};

}

#endif //TANGLE_MC_WORLD_OVERWORLD_OVERWORLD_H