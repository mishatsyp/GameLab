add_executable(dungeon_tests
        test_entity.cpp
        ../src/Entity.cpp
        test_event.cpp
        ../src/Event.cpp
        test_random.cpp
        ../src/Random.cpp
)

target_include_directories(dungeon_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(dungeon_tests
        GTest::gtest_main
        GTest::gtest
)

enable_testing()

add_test(NAME DungeonTests COMMAND dungeon_tests)