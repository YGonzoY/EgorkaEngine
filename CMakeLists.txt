cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME EgorkaEngine)

add_subdirectory(EgorkaEngineEditor)
add_subdirectory(EgorkaEngineCore)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT EgorkaEngineEditor)