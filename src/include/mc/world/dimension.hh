#ifndef TANGLE_MC_WORLD_DIM_BASE_H
#define TANGLE_MC_WORLD_DIM_BASE_H

#include <cstdint>
#include <memory>

#include <common/vector.hh>
#include <mc/entity/base_entity.hh>
#include <mc/entity/eid_authority.hh>
#include <mc/world/worldgen.hh>
#include <mc/world/chunk.hh>
#include <mc/world/region.hh>

namespace tangle::mc::world {

using namespace common;

enum class dimtype : uint8_t {
    OVERWORLD,
    NETHER,
};

class dimension {
    eid_authority& m_auth;
    int2 m_spawnpoint;
    std::unordered_map<int2, std::shared_ptr<region>> m_region;
protected:
    virtual const worldgen& get_worldgen() const = 0;
    void spin_up(int2 region_coords);
    void spin_down(int2 region_coords);
public:
    dimension(eid_authority& auth, int2 spawn);
    eid_authority& auth();
    bool pass_entity(std::shared_ptr<base_entity>, int2 dest_chunk);
    std::shared_ptr<region> get_region_in_charge(int2 chunk);
};

}

#endif //TANGLE_MC_WORLD_DIM_BASE_H