#pragma once

#include <cstdint>

#include "eos_api.h"

#pragma pack(push, 8)

struct EOS_Connect_LoginCallbackInfo {
	EOS_EResult ResultCode;
	void* ClientData;
	EOS_ProductUserId LocalUserId;
	EOS_ContinuanceToken ContinuanceToken;
};

struct EOS_Connect_Credentials {
	int32_t ApiVersion;
	const char* Token;
	int Type;
};

struct EOS_Connect_UserLoginInfo {
	int32_t ApiVersion;
	const char* DisplayName;
	const char* NsaIdToken;
};

struct EOS_Connect_LoginOptions {
	int32_t ApiVersion;
	EOS_Connect_Credentials* Credentials;
	EOS_Connect_UserLoginInfo* UserLoginInfo;
};

EOS_DECLARE_CALLBACK(EOS_Connect_OnLoginCallback, const EOS_Connect_LoginCallbackInfo*);

#pragma pack(pop)
