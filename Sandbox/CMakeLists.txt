set(CHERT_INCLUDE ${PROJECT_SOURCE_DIR}/Chert/src/)

add_executable(ChertSandbox src/Sandbox.cpp)

target_include_directories(ChertSandbox PUBLIC ${CHERT_INCLUDE})
target_link_libraries(ChertSandbox PUBLIC Chert)
