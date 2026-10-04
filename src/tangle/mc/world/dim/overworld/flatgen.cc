#include <mc/world/overworld/flatgen.hh>

namespace tangle::mc::world::overworld {

flatgen::flatgen()
: overworld_worldgen(0) {}

std::shared_ptr<chunk> flatgen::gen_chunk(int32_t cx, int32_t cz) {
    std::array<block, 16*16*128> blocks;
    for(uint8_t z = 0; z<16; z++) {
        for(uint8_t x = 0; x<16; x++) {
            for(uint8_t y = 0; y<128; y++) {
                if(y==0) blocks[y + x*16 + z*16*16] = {1, 0, 0};
                else if(y<3) blocks[y + x*16 + z*16*16] = {3, 0, 0};
                else if(y==3) blocks[y + x*16 + z*16*16] = {2, 0, 0xff};
                else blocks[y + x*16 + z*16*16] = {0, 0, 0xff};
            }
        }
    }
    return std::make_shared<chunk>(cx, cz, blocks);
}

}
