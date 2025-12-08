pybind11_add_module(core bindings.cpp)

set_target_properties(core PROPERTIES
    OUTPUT_NAME "_core"
)

target_link_libraries(core PRIVATE physics)

target_include_directories(core PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

install(TARGETS core
    LIBRARY DESTINATION physics
    ARCHIVE DESTINATION physics
)

if(PHYSICS_GENERATE_STUBS)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)

    add_custom_command(
        TARGET core
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E env
            PYTHONPATH=${PROJECT_SOURCE_DIR}/python
            ${Python3_EXECUTABLE} ${PROJECT_SOURCE_DIR}/python/scripts/generate_stubs.py
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generating Python stub (_core.pyi)"
    )
endif()