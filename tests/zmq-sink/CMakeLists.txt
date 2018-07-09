project(push_pull)

set(CMAKE_CXX_STANDARD 11)

add_executable(push push.cpp zhelpers.h)
add_executable(pull pull.cpp zhelpers.h)
target_link_libraries(push czmq zmq)
target_link_libraries(pull czmq zmq)
