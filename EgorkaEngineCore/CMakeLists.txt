cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME EgorkaEngineCore)

add_library(${ENGINE_PROJECT_NAME} STATIC
	src/EgorkaEngineCore/Utils/test.cpp
	include/EgorkaEngineCore/Utils/test.hpp
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)