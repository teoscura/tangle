#ifndef TANGLE_MC_WORLD_SERIALIZER_H
#define TANGLE_MC_WORLD_SERIALIZER_H

#include <vector>

#include <mc/world/chunk.hh>

namespace tangle::mc::world {

class serializer {
    static std::vector<uint8_t> serialize_chunk(chunk& chunk);
};

}

#endif //TANGLE_MC_WORLD_SERIALIZER_H