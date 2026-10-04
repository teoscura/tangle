//TODO
#ifndef TANGLE_MC_WORLD_CHUNK_H
#define TANGLE_MC_WORLD_CHUNK_H

#include <array>
#include <cstdint>
#include <memory>

namespace tangle::mc::world {

struct block {
    uint8_t type;
    uint8_t meta;
    uint8_t lights; //first 4 skylight, second 4 blocklight
};

class chunk {
    friend class serializer;

    int32_t m_cx, m_cz;
    std::array<block, 16*16*128> m_blocks;
public:
    chunk(int32_t cx, int32_t cz);
    chunk(int32_t cx, int32_t cz, std::array<block, 16*16*128> blocks);
    bool set_block(block block, uint8_t x, uint8_t y, uint8_t z);
    block get_block(uint8_t x, uint8_t y, uint8_t z);
    ~chunk();
};

enum class load_type : uint8_t {
    NEED_GEN,
    ON_FILE,
    GEN_WIP,
    ON_RAM,
};

struct chunk_record {
    load_type load;
    std::shared_ptr<chunk> data;
};

}

#endif //TANGLE_MC_WORLD_CHUNK_H