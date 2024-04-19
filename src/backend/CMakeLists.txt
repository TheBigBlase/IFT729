cmake_minimum_required(VERSION 3.14)

project(
	GuessMyDraw
    VERSION 0.1.0
    DESCRIPTION "skribbl.io from scratch"
	LANGUAGES CXX
)

set(src
	server.cpp
	player.cpp
	game.cpp
	main.cpp
)
set(CMAKE_CXX_STANDARD 23)
find_package(Boost 1.70 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_DEBUG_POSTFIX d)
add_executable(guessMyDraw ${src})
set_target_properties(guessMyDraw PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(guessMyDraw LINK_PUBLIC ${Boost_LIBRARIES})
target_compile_features(guessMyDraw PRIVATE cxx_std_23)
