#ifndef TANGLE_MC_WORLD_BASE_H
#define TANGLE_MC_WORLD_BASE_H

#include "mc/entity/eid_authority.hh"
#include <array>
#include <string>

#include <mc/world/dimension.hh>
#include <mc/world/file/reader.hh>

namespace tangle::mc::world {

class world {
    std::string m_name;
    eid_authority m_auth;
    uint64_t m_seed;
    std::array<std::shared_ptr<dimension>, 2> m_dimensions;
public:
    world(std::string name, uint64_t seed);
    std::shared_ptr<dimension> get_dimension(dimtype dim);
};

}

#endif //TANGLE_MC_WORLD_BASE_H