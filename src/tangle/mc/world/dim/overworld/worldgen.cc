#include <mc/world/overworld/worldgen.hh>

namespace tangle::mc::world::overworld {

overworld_worldgen::overworld_worldgen(uint64_t seed)
: worldgen(seed) {}

std::shared_ptr<chunk> overworld_worldgen::gen_chunk(int32_t cx, int32_t cz) {
    std::array<block, 16*16*128> blocks = {{{0, 0, 0}}};
    return std::make_shared<chunk>(cx, cz, blocks);

    //FIXME
}

}