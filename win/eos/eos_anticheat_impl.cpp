#include "base64.hpp"
#include "../client.h"
#include "eos/eos_anticheat_types.h"
#include "eos/eos_api.h"
#include "protocol/packets/begin_session_packet.h"
#include "protocol/packets/receive_message_packet.h"

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_AntiCheatClient_BeginSession(EOS_HAntiCheatClient handle, const EOS_AntiCheatClient_BeginSessionOptions* options) {
	PLOGI.printf("Beginning session with mode: %d", options->Mode);
	auto packet = std::make_shared<begin_session_packet>();
	packet->api_version = options->ApiVersion;
	packet->user_id = options->LocalUserId;
	packet->mode = options->Mode;
	client::send_packet(packet);

	return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_AntiCheatClient_ReceiveMessageFromServer(EOS_HAntiCheatClient handle, const EOS_AntiCheatClient_ReceiveMessageFromServerOptions* options) {
	// encode message data
	std::vector<char> message_bytes;
	for (int i = 0; i < options->DataLengthBytes; i++) {
		message_bytes.push_back(static_cast<const char*>(options->Data)[i]);
	}
	auto message_base64 = base64::encode_into<std::string>(message_bytes.begin(), message_bytes.end());

	auto packet = std::make_shared<receive_message_packet>();
	packet->api_version = options->ApiVersion;
	packet->base64_message = nullable_string(message_base64);
	packet->data_length_bytes = options->DataLengthBytes;
	client::send_packet(packet);

	return EOS_Success;
}
