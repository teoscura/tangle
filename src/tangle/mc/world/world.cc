#include <mc/world/world.hh>

#include <mc/world/overworld/overworld_dimension.hh>
#include <mc/world/nether/nether_dimension.hh>

namespace tangle::mc::world {

world::world(std::string name, uint64_t seed) 
: m_name(name)
, m_auth(0) 
, m_seed(seed)
, m_dimensions{
    std::make_shared<overworld::overworld_dimension>(m_auth, m_seed, int2{0,0}),
    std::make_shared<nether::nether_dimension>(m_auth, m_seed, int2{0,0})} {}

std::shared_ptr<dimension> world::get_dimension(dimtype dim) {
    switch(dim) {
    case dimtype::OVERWORLD:
        return m_dimensions[0];
    case dimtype::NETHER:
        return m_dimensions[1];
    default:
        return nullptr;
    }
}

}