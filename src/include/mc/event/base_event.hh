#ifndef TANGLE_MC_EVENT_EVENT_H
#define TANGLE_MC_EVENT_EVENT_H

namespace tangle::mc{

namespace world {
    class region;
}

namespace event {

using namespace world;

class base_event {
public:
    virtual void get_handled(region& handler) const = 0; 
    virtual ~base_event() = 0;
};

}

}

#endif //TANGLE_MC_EVENT_EVENT_H