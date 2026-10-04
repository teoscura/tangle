#ifndef TANGLE_MC_WORLD_OVERWORLD_WORLDGEN_H
#define TANGLE_MC_WORLD_OVERWORLD_WORLDGEN_H

#include <memory>

#include <mc/world/worldgen.hh>

namespace tangle::mc::world::overworld {

using namespace tangle::mc::world;

class overworld_worldgen : public worldgen {
    uint64_t m_seed;
public:
    overworld_worldgen(uint64_t seed);
    std::shared_ptr<chunk> gen_chunk(int32_t cx, int32_t cz) override;
};

}

#endif //TANGLE_MC_WORLD_OVERWORLD_WORLDGEN_H