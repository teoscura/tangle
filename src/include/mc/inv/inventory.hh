#ifndef TANGLE_MC_INV_INVENTORY_H
#define TANGLE_MC_INV_INVENTORY_H

#include <cstddef>
#include <cstdint>
#include <memory>

#include <mc/inv/item.hh>

namespace tangle::mc::inv {

class inventory {
    uint64_t m_id;
public:
    inventory(uint64_t id) : m_id(id) {}
    uint64_t id() const {return m_id; }
    virtual std::size_t get_cells() const = 0;
    virtual std::shared_ptr<item> pop_item(std::size_t cell) = 0;
    virtual std::shared_ptr<item> get_item(std::size_t cell) = 0;
    virtual bool set_item(std::size_t cell, std::shared_ptr<item> item) = 0;
};

}

#endif //TANGLE_MC_INV_INVENTORY_H