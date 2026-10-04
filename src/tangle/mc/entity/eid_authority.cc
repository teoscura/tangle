#include <mc/entity/eid_authority.hh>

namespace tangle::mc::entity {

eid_authority::eid_authority(uint32_t last) 
: m_next(last+1) {}

uint32_t eid_authority::get_next() {
    return m_next++;
}

}