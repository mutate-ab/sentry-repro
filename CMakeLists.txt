project(foobar)

option(SENTRY_LIB "sentry lib")
option(SENTRY_INCLUDE "sentry include")
option(CRASHPAD_HANDLER "CRASHPAD_HANDLER")

add_executable(repro main.cpp)
target_link_libraries(repro PUBLIC ${SENTRY_LIB})
target_link_libraries(repro PUBLIC pthread)
target_include_directories(repro PUBLIC ${SENTRY_INCLUDE})
target_compile_definitions(repro PUBLIC CRASHPAD_HANDLER=${CRASHPAD_HANDLER} SENTRY_DSN=${SENTRY_DSN})
