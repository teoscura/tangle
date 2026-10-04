#include "mc/world/chunk.hh"
#include <mc/world/region.hh>

#include <mc/world/dimension.hh>
#include <stdexcept>
#include <unordered_map>

namespace tangle::mc::world {


region::region(dimension& parent, int2 region_coords) 
: m_parent(parent) 
, m_region_coords(region_coords)
, m_registry(parent.auth(), 256) {
    int2 corner1 = {region_coords.x*32, region_coords.z*32};
    int2 corner2 = {corner1.x+32, corner1.z+32}; 
    for(int32_t x = corner1.x; x < corner2.x; x++) {
        for(int32_t z = corner1.z; z < corner2.z; z++) {
            int2 idx = {x,z};
            m_chunks[idx] = chunk_record{load_type::NEED_GEN, nullptr};
        }
    }

}

region::region(dimension& parent, int2 region_coords, std::unordered_map<int2, chunk_record> map)
: m_parent(parent) 
, m_region_coords(region_coords)
, m_chunks(map) 
, m_registry(parent.auth(), 256) {}

region::region(dimension& parent, int2 region_coords, std::unordered_map<int2, chunk_record> map, entity_registry entities)
: m_parent(parent) 
, m_region_coords(region_coords)
, m_chunks(map) 
, m_registry(entities) {}

bool region::load_chunk_or(int2 coords) {
    auto it = m_chunks.find(coords);
    if(it == m_chunks.end()) throw std::range_error("Invalid chunk coordinates, something wrong happened uptrace!");
    auto record = it->second;
    if(record.load == load_type::ON_RAM) return true;
    else return false;
    //FIXME add async gen
}

std::size_t region::unload_chunk(int2 coords) {
    auto it = m_chunks.find(coords);
    if(it == m_chunks.end()) throw std::range_error("Invalid chunk coordinates, something wrong happened uptrace!");
    auto record = it->second;
    if(record.load!=load_type::ON_RAM) return 0;
    else return 1;
    //FIXME return saved file size.
}

entity_registry& region::get_registry() {
    return m_registry;
}
const entity_registry& region::get_registry() const {
    return m_registry;
}

std::size_t region::unload_and_save() {
    return 0;
    //FIXME add funct.
}

region::~region() {}

}