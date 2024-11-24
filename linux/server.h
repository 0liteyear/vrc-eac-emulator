#pragma once
#include "protocol/packet.h"

class server {
    static void receive_loopback();
public:
    static void run();

    static void send_packet(const std::shared_ptr<packet>& packet);

	static void tick();
};
