add_library(clisystem SHARED system.c scene.c scene_handler.c)
target_include_directories(clisystem PUBLIC ${PROJECT_SOURCE_DIR}/include)