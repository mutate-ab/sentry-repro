#include <sentry.h>
#include <thread>
#include <iostream>
#include <functional>
#include <vector>

#define xstr(a) str(a)
#define str(a) #a

int main() {
	sentry_options_t *options = sentry_options_new();
	sentry_options_set_dsn(options, xstr(SENTRY_DSN));
	sentry_user_consent_give();
	sentry_options_set_debug(options, 1);
#ifdef CRASHPAD_HANDLER
	sentry_options_set_handler_path(options, xstr(CRASHPAD_HANDLER));
	std::cout << xstr(CRASHPAD_HANDLER) << std::endl;
#else
#error CRASHPAD_HANDLER not defined
#endif

	if (sentry_init(options)) {
		std::cerr << "Failed to initialize Sentry, crashes will not be reported!" << std::endl;
	}

	// to make sure capturing events works
	sentry_capture_event(sentry_value_new_message_event(SENTRY_LEVEL_INFO, "session", "Repro start"));

	auto now = std::chrono::high_resolution_clock::now();
	sentry_reinstall_backend();

	std::function<void()> threadFunc;
	std::thread coolThread([]() {
		std::vector<int> foo;
		foo.data()[5] = 1;
	});

	while ((std::chrono::high_resolution_clock::now() - now) <= std::chrono::seconds(5)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	coolThread.join();

	sentry_shutdown();
}
