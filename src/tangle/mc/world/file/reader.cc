#include <mc/world/file/reader.hh>

#include <filesystem>
#include <stdexcept>

#include <mc/world/world.hh>

namespace tangle::mc::world::file {

reader::reader(std::string_view pathname) 
: m_folder(pathname) {
    if(!std::filesystem::is_directory(m_folder)) throw std::runtime_error("given path name is not a directory");
}
    
std::shared_ptr<world> reader::create_handle() {
    return std::make_shared<world>("world", 0);
}   

//fixme add loading of dimensions, add loading of maps, player data etc.

reader::~reader() {
}

};