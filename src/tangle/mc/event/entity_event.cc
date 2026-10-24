#include "mc/event/entity_event.hh"

namespace tangle::mc::event {

entity_event::entity_event(uint32_t eid) 
: m_eid(eid) {}

entity_event::~entity_event() {}

}