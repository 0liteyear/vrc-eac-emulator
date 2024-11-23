#include "eos_platform.h"

#include "eos_utils.h"
#include "eos/eos_api.h"

EOS_HPlatform hPlatform = NULL;

void eos_platform::create_platform(EOS_Platform_Options const& options) {
	typedef EOS_HPlatform (EOS_CALL*EOS_Platform_Create)(EOS_Platform_Options const*);
	static auto eos_create_platform = reinterpret_cast<EOS_Platform_Create>(
		eos_utils::get_eos_proc_addr("EOS_Platform_Create"));
	if (!eos_create_platform) {
		PLOGF.printf("Could not resolve EOS_Platform_Create");
		return;
	}

	hPlatform = eos_create_platform(&options);
	if (!hPlatform) {
		PLOGE.printf("Failed to call EOS_Platform_Create!");
		return;
	}
	PLOGI.printf("Platform Created: product_id=%s, client_id=%s", options.ProductId, options.ClientCredentials.ClientId);
}

EOS_HConnect eos_platform::get_connect_interface() {
	typedef EOS_HConnect (EOS_CALL*EOS_Platform_GetConnectInterface)(EOS_HPlatform);
	static auto eos_platform_get_connect_interface = reinterpret_cast<EOS_Platform_GetConnectInterface>(
		eos_utils::get_eos_proc_addr("EOS_Platform_GetConnectInterface"));
	if (!eos_platform_get_connect_interface) {
		PLOGF.printf("Could not resolve EOS_Platform_GetConnectInterface");
		return 0;
	}

	EOS_HConnect hConnect = eos_platform_get_connect_interface(hPlatform);
	if (!hConnect) {
		PLOGE.printf("Failed to call EOS_Platform_GetConnectInterface!");
		return 0;
	}

	return hConnect;
}

void eos_platform::connect_login(EOS_HConnect hConnect, EOS_Connect_LoginOptions const& options, const EOS_Connect_OnLoginCallback callback) {
	typedef void (EOS_CALL*EOS_Connect_Login)(EOS_HConnect, EOS_Connect_LoginOptions const*, void*, EOS_Connect_OnLoginCallback);
	static auto eos_connect_login = reinterpret_cast<EOS_Connect_Login>(
		eos_utils::get_eos_proc_addr("EOS_Connect_Login"));
	if (!eos_connect_login) {
		PLOGF.printf("Could not resolve EOS_Connect_Login");
		return;
	}

	eos_connect_login(hConnect, &options, nullptr, callback);
}
