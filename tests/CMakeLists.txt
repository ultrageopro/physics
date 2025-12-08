function(add_physics_test name)
    add_executable(${name} ${name}.cpp)

    target_link_libraries(${name} PRIVATE
        physics
        gtest_main
    )

    target_include_directories(${name} PRIVATE
        ${gtest_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/include
    )

    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_physics_test(test_vector)
add_physics_test(test_formulas)
add_physics_test(test_obj_gravity)
add_physics_test(test_friction)