project(physics LANGUAGES ${RYTHE_LANGUAGE})

rythe_find_sources(sources "${PROJECT_SOURCE_DIR}/src")
add_library(physics ${RYTHE_LIBRARY_TYPE} ${sources})

rythe_configure_module(physics)
rythe_copy_module_output(physics rythe/engine/physics)
