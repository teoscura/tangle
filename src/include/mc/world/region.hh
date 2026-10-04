#ifndef TANGLE_MC_WORLD_BLOB_H
#define TANGLE_MC_WORLD_BLOB_H

#include <unordered_map>

#include <common/vector.hh>
#include <mc/world/chunk.hh>
#include <mc/entity/entity_registry.hh>

namespace tangle::mc::world {

using namespace tangle::common;
using namespace tangle::mc::entity;

class dimension;

class region {
    dimension& m_parent;
    int2 m_region_coords;
    std::unordered_map<int2, chunk_record> m_chunks;
    entity_registry m_registry;
public:
    region(dimension& parent, int2 region_coords);
    region(dimension& parent, int2 region_coords, std::unordered_map<int2, chunk_record> map);
    region(dimension& parent, int2 region_coords, std::unordered_map<int2, chunk_record> map, entity_registry entities);
    bool load_chunk_or(int2 coords);
    std::size_t unload_chunk(int2 coords);
    entity_registry& get_registry();
    const entity_registry& get_registry() const;
    std::size_t unload_and_save();
    ~region();
};

}

#endif //TANGLE_MC_WORLD_BLOB_H