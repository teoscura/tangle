
#include "net/packet/incoming_packet.hh"
#include <common/queue.hh>
#include <net/network.hh>

#include <thread>
#include <print>

using namespace tangle::common;
using namespace tangle::net;

int main() {
    queue<std::unique_ptr<incoming_packet>> queue(0x100);
    network net;
    net.bind();
    std::vector<std::jthread> threads;
    net.accept(queue);
    for(int i = 0; i < 4; i++) {
        threads.emplace_back(&network::run, &net);
    }
}