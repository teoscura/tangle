#ifndef TANGLE_MC_INVENTORY_TRANSACTION_H
#define TANGLE_MC_INVENTORY_TRANSACTION_H

#include <cstdint>

namespace tangle::mc::event {
    class inventory_event;
}

namespace tangle::mc::inv {

using namespace event;

class transaction {
    uint64_t m_tid;
public:
    transaction(uint64_t tid);
    uint64_t tid() const;
    virtual bool process(inventory_event event) = 0;
    virtual ~transaction();
};

}

#endif //TANGLE_MC_INVENTORY_TRANSACTION_H