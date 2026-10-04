//TODO

#include <mc/world/chunk.hh>
#include <common/validate.hh>

namespace tangle::mc::world {

chunk::chunk(int32_t cx, int32_t cz) 
: m_cx(cx)
, m_cz(cz)
, m_blocks{} {}


chunk::chunk(int32_t cx, int32_t cz, std::array<block, 16*16*128> blocks)
: m_cx(cx)
, m_cz(cz)
, m_blocks(blocks) {}

bool chunk::set_block(block block, uint8_t x, uint8_t y, uint8_t z) {
    if((x|z)&0xf0) return false;
    if(M_validateb(block)) return false;
    m_blocks[y+16*x+16*16*z] = block;
    return true;
}

block chunk::get_block(uint8_t x, uint8_t y, uint8_t z) {
    if((x|z)&0xf0) return {0,0,0};
    return m_blocks[y+16*x+16*16*z];
}

chunk::~chunk() {}


}
