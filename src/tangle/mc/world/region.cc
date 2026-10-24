#include <mc/world/region.hh>

#include <chrono>
#include <stdexcept>
#include <thread>
#include <unordered_map>

#include <mc/world/dimension.hh>

namespace tangle::mc::world {

using namespace std::chrono_literals;

region::region(dimension& parent, int2 region_coords) 
: m_parent(parent) 
, m_region_coords(region_coords)
, m_current_tick(0)
, m_running(0)
, m_registry(parent.auth(), 256)
, m_queue(0) {
    int2 corner1 = {region_coords.x*32, region_coords.z*32};
    int2 corner2 = {corner1.x+32, corner1.z+32}; 
    for(int32_t x = corner1.x; x < corner2.x; x++) {
        for(int32_t z = corner1.z; z < corner2.z; z++) {
            int2 idx = {x,z};
            m_chunks.insert_or_assign(idx, chunk_record{load_type::NEED_GEN, nullptr});
        }
    }

}

region::region(dimension& parent, int2 region_coords, std::unordered_map<int2, chunk_record> map, registry entities)
: m_parent(parent) 
, m_region_coords(region_coords)
, m_registry(entities) 
, m_chunks(map)
, m_queue(0)  {}

bool region::load_chunk_or(int2 coords) {
    const auto& it = m_chunks.find(coords);
    if(it == m_chunks.end()) throw std::range_error("Invalid chunk coordinates, something wrong happened uptrace!");
    const auto& record = it->second;
    if(record.load == load_type::ON_RAM) return true;
    else return false;
    //FIXME add async gen
}

std::size_t region::unload_chunk(int2 coords) {
    const auto& it = m_chunks.find(coords);
    if(it == m_chunks.end()) throw std::range_error("Invalid chunk coordinates, something wrong happened uptrace!");
    const auto& record = it->second;
    if(record.load!=load_type::ON_RAM) return 0;
    else return 1;
    //FIXME return saved file size.
}

registry& region::get_registry() {
    return m_registry;
}
const registry& region::get_registry() const {
    return m_registry;
}

std::size_t region::halt_and_save() {
    m_running = false;
    
    //FIXME add saving.
    return 0;
}

void region::main_loop() {
    auto instant_start = std::chrono::steady_clock::now();
    m_running = true;
    while(m_running) {
        auto instant_now = std::chrono::steady_clock::now();
        uint64_t tentative_tick = (instant_now - instant_start) / 50ms;
        if(tentative_tick <= m_current_tick) {
            std::this_thread::sleep_for(50ms - (instant_now - instant_start));
        }
        m_current_tick = tentative_tick;
        const auto& input_events = m_queue.pending();
        for(const auto& ref : input_events) {
            ref->get_handled(*this);
        }
    }
}

region::~region() {}

}