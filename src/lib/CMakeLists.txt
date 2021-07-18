add_library(system SHARED system.c scene.c)
target_include_directories(system PUBLIC ${PROJECT_SOURCE_DIR}/include)