#ifndef TANGLE_NET_CLIENT_DESCR_H
#define TANGLE_NET_CLIENT_DESCR_H

#include <cstdint>

namespace tangle::net {

struct client_descriptor {
    uint32_t fd;
};

}

#endif //TANGLE_NET_CLIENT_DESCR_H