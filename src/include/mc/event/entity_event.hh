#ifndef TANGLE_MC_EVENT_ENTITY_H
#define TANGLE_MC_EVENT_ENTITY_H

#include <mc/event/base_event.hh>
#include <mc/world/region.hh>
#include <mc/entity/registry.hh>

namespace tangle::mc::event {

using namespace entity;

class entity_event : public base_event {
    uint32_t m_eid;
public:
    entity_event(uint32_t eid);
    virtual void get_handled(region& handler) const {
        this->get_handled(handler.get_registry());
    }
    virtual void get_handled(registry& handler) const = 0; 
    virtual ~entity_event() = 0;
};

}

#endif //TANGLE_MC_EVENT_ENTITY_H