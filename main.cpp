#include <sentry.h>
#include <iostream>
#include <vector>

int main() {
	sentry_options_t *options = sentry_options_new();
	sentry_options_set_dsn(options, SENTRY_DSN);
	sentry_user_consent_give();
	sentry_options_set_debug(options, 1);
#ifdef CRASHPAD_HANDLER
	sentry_options_set_handler_path(options, CRASHPAD_HANDLER);
	std::cout << CRASHPAD_HANDLER << std::endl;
#else
#error CRASHPAD_HANDLER not defined
#endif

	if (sentry_init(options)) {
		std::cerr << "Failed to initialize Sentry, crashes will not be reported!" << std::endl;
	}

	// to make sure capturing events works
	sentry_capture_event(sentry_value_new_message_event(SENTRY_LEVEL_INFO, "session", "Repro start"));

	sentry_reinstall_backend();

	*reinterpret_cast<int*>(0) = 1;

	sentry_shutdown();
}
