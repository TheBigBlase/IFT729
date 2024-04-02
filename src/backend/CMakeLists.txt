cmake_minimum_required(VERSION 3.14)

project(
	GuessMyDraw
    VERSION 0.1.0
    DESCRIPTION "skribbl.io from scratch"
	LANGUAGES CXX
)

set(src
	server.cpp
	main.cpp
	)

## load in pkg-config support
find_package(PkgConfig)
## use pkg-config to get hints for 0mq locations
pkg_check_modules(PC_ZeroMQ QUIET zmq)

## use the hint from above to find where 'zmq.hpp' is located
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

## use the hint from above to find the location of libzmq
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

set(CMAKE_DEBUG_POSTFIX d)
add_executable(guessMyDraw ${src})
set_target_properties(guessMyDraw PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_compile_features(guessMyDraw PRIVATE cxx_std_20)

target_include_directories(guessMyDraw PUBLIC ${ZeroMQ_INCLUDE_DIR})
## at the 0mq library to our link directive
target_link_libraries(guessMyDraw PUBLIC ${ZeroMQ_LIBRARY})
