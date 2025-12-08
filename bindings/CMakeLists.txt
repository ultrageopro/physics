pybind11_add_module(core bindings.cpp)

set_target_properties(core PROPERTIES
    OUTPUT_NAME "_core"
)

target_link_libraries(core PRIVATE physics)
target_include_directories(core PRIVATE
    ${pybind11_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include
)

add_custom_command(
    TARGET core
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            ${PROJECT_SOURCE_DIR}/python/physics
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:core>
            ${PROJECT_SOURCE_DIR}/python/physics/
    COMMENT "Copying Python module _core.so → python/physics/"
)
