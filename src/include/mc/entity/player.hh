#ifndef TANGLE_MC_PLAYER_H
#define TANGLE_MC_PLAYER_H

#include <string>

#include <mc/entity/moving_entity.hh>

namespace tangle::mc::entity {

enum class pose : uint8_t {
    standing,
    sleeping,
    riding
};

class player : public moving_entity {
    std::string m_name;
    pose m_pose;
public:
    player(uint32_t eid, std::string name);
    pose get_pose() const;
    void new_pose(pose new_pose);
    ~player() override;
};

}

#endif //TANGLE_MC_PLAYER_H