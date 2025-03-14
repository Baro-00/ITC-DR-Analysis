function(add_nav_test test_name test_source)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name}
        PRIVATE
            nav_components
            gtest
            gtest_main
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# UNIT Tests
add_nav_test(matrix_tests unit/core/MatrixTests.cpp)
add_nav_test(vector_tests unit/core/Vector3DTests.cpp)
add_nav_test(quaternion_tests unit/core/QuaternionTests.cpp)
# add_nav_test(kalman_filter_tests unit/filters/KalmanFilterTests.cpp)
# add_nav_test(madgwick_filter_tests unit/filters/MadgwickFilterTests.cpp)
# add_nav_test(dead_reckoning_tests unit/navigation/DeadReckoningTests.cpp)
# add_nav_test(csv_handler_tests unit/io/CSVHandlerTests.cpp)

# INTEGRATION Tests
# add_nav_test(navigation_system_tests integration/NavigationSystemTests.cpp)
# add_nav_test(filter_comparison_tests integration/FilterComparisonTests.cpp)