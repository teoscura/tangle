#ifndef TANGLE_MC_EVENT_INVENTORY_H
#define TANGLE_MC_EVENT_INVENTORY_H

#include <cstdint>

#include "mc/event/base_event.hh"
#include "mc/inv/registry.hh"
#include "mc/world/region.hh"

namespace tangle::mc::event {

using registry = inv::registry;

class inventory_event : public base_event {
    uint32_t m_invid;
public:
    inventory_event(uint32_t invid);
    virtual void get_handled(region& handler) const;
    virtual void get_handled(registry& handler) const = 0; 
    virtual ~inventory_event() = 0;
};

};

#endif //TANGLE_MC_EVENT_INVENTORY_H