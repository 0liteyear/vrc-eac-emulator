#pragma once
#include <memory>

#include "protocol/packet.h"

class client_packet_handler {
public:
    static void handle(std::shared_ptr<packet> packet);
};
