cmake_minimum_required(VERSION 3.14)

project(
	GuessMyDraw
    VERSION 0.1.0
    DESCRIPTION "skribbl.io from scratch"
	LANGUAGES CXX
)

set(src
	src/backend/main.cpp
	src/backend/utils.cpp
	)

set(CMAKE_DEBUG_POSTFIX d)
add_executable(guessMyDraw ${src})
set_target_properties(guessMyDraw PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_compile_features(guessMyDraw PRIVATE cxx_std_20)
