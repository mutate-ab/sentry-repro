project(foobar)

option(SENTRY_LIB "Path to sentry link library")
option(SENTRY_INCLUDE "Path to sentry include dir")
option(CRASHPAD_HANDLER "Path to crashpad_handler executable")
option(SENTRY_DSN "Sentry DSN to use")

add_executable(repro main.cpp)
target_link_libraries(repro PUBLIC ${SENTRY_LIB})
target_link_libraries(repro PUBLIC pthread)
target_include_directories(repro PUBLIC ${SENTRY_INCLUDE})
target_compile_definitions(repro PUBLIC CRASHPAD_HANDLER="${CRASHPAD_HANDLER}" SENTRY_DSN="${SENTRY_DSN}")
