#ifndef TANGLE_MC_WORLD_WRITER_H
#define TANGLE_MC_WORLD_WRITER_H

#include <string_view>
#include <filesystem>

namespace tangle::mc::world {

class world;

namespace file {

class writer {
    std::filesystem::path m_folder;
public:
    writer(std::string_view pathname);
    std::size_t write(world);
    ~writer();
};

}

}

#endif //TANGLE_MC_WORLD_WRITER_H