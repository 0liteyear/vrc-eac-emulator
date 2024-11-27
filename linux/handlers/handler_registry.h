#pragma once

#include <unordered_map>

#include "common/handshake_packet_handler.h"
#include "common/initialize_eos_handler.h"
#include "platform/begin_session_handler.h"
#include "platform/create_platform_handler.h"
#include "protocol/packet.h"

class handler_registry {
public:
	typedef void(*HandlerFuncPtr)(std::shared_ptr<packet>);
	static inline std::unordered_map<int, HandlerFuncPtr> handlers;

	static void init() {
		handlers[HANDSHAKE_PACKET_ID] = handshake_packet_handler::handle;
		handlers[CREATE_PLATFORM_PACKET_ID] = create_platform_handler::handle;
		handlers[INITIALIZE_EOS_PACKET_ID] = initialize_eos_handler::handle;
		handlers[BEGIN_SESSION_PACKET_ID] = begin_session_handler::handle;

		PLOGD.printf("Collected %d handlers", handlers.size());
	}

	static HandlerFuncPtr get_handler_by_id(unsigned char packet_id) {
		if (!handlers.contains(packet_id)) {
			PLOGE.printf("Invalid handler id specified: %d", packet_id);
			return nullptr;
		}

		return handlers[packet_id];
	}
};
