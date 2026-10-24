#ifndef TANGLE_MC_WORLD_BLOB_H
#define TANGLE_MC_WORLD_BLOB_H

#include <unordered_map>

#include <common/vector.hh>
#include <common/queue.hh>
#include <mc/event/base_event.hh>
#include <mc/world/chunk.hh>
#include <mc/entity/registry.hh>

namespace tangle::mc::world {

using namespace common;
using namespace event;
using namespace entity;

class dimension;

class region {
    dimension& m_parent;
    int2 m_region_coords;
    uint64_t m_current_tick;
    std::atomic<bool> m_running;
    registry m_registry;
    std::unordered_map<int2, chunk_record> m_chunks;
    queue<std::unique_ptr<base_event>> m_queue;
public:
    region(dimension& parent, int2 region_coords);
    region(dimension& parent, int2 region_coords, std::unordered_map<int2, chunk_record> map, registry entities);
    //Locally called:
    bool load_chunk_or(int2 coords);
    std::size_t unload_chunk(int2 coords);
    registry& get_registry();
    const registry& get_registry() const;
    //Remotely called:
    std::size_t halt_and_save();
    void main_loop();
    ~region();
};

}

#endif //TANGLE_MC_WORLD_BLOB_H