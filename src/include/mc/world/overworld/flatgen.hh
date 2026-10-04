#ifndef TANGLE_MC_WORLD_OVERWORLD_FLATGEN_H
#define TANGLE_MC_WORLD_OVERWORLD_FLATGEN_H

#include <mc/world/overworld/worldgen.hh>

namespace tangle::mc::world::overworld {

class flatgen : public overworld_worldgen {
public:
    flatgen();
    std::shared_ptr<chunk> gen_chunk(int32_t cx, int32_t cz) override;
};

}

#endif //TANGLE_MC_WORLD_OVERWORLD_FLATGEN_H