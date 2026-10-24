#ifndef TANGLE_MC_WORLD_READER_H
#define TANGLE_MC_WORLD_READER_H

#include <string_view>
#include <filesystem>

namespace tangle::mc::world {

class world;

namespace file {

class reader {
    std::filesystem::path m_folder;
public:
    reader(std::string_view pathname);
    std::shared_ptr<world> create_handle();   
    ~reader();
};

}

}

#endif //TANGLE_MC_WORLD_READER_H