#ifndef TANGLE_MC_INV_ITEM_H
#define TANGLE_MC_INV_ITEM_H

#include <cstdint>

namespace tangle::mc::inv {

struct item {
    uint8_t m_slot;
    uint16_t m_id;
    uint8_t m_count;
    uint16_t m_damage;
};

}

#endif //TANGLE_MC_INV_ITEM_H
