#ifndef TANGLE_MC_WORLD_WORLDGEN_H
#define TANGLE_MC_WORLD_WORLDGEN_H

#include <memory>

#include "mc/world/chunk.hh"

namespace tangle::mc::world {

class worldgen {
    uint64_t m_seed;
public:
    worldgen(uint64_t seed);
    virtual std::shared_ptr<chunk> gen_chunk(int32_t cx, int32_t cz) = 0;
};

}

#endif //TANGLE_MC_WORLD_WORLDGEN_H