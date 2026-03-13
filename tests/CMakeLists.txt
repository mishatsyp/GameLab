add_executable(dungeon_tests
        test_entity.cpp
        ../src/Entity.cpp
        test_event.cpp
        ../src/Event.cpp
        test_random.cpp
        ../src/Random.cpp
        test_room.cpp
        ../src/Room.cpp
        test_Item.cpp
        ../src/Item.cpp
        test_Player.cpp
        ../src/Player.cpp
        ../src/Dungeon.cpp
        ../src/Screen.cpp
        ../src/GameEngine.cpp
        test_Dungeon.cpp
        test_Screen.cpp
)

target_include_directories(dungeon_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(dungeon_tests
        GTest::gtest_main
        GTest::gtest
        GTest::gmock
)

enable_testing()

add_test(NAME EntityTest COMMAND dungeon_tests --gtest_filter=EntityTest.*)
add_test(NAME EventTest COMMAND dungeon_tests --gtest_filter=EventTest.*)
add_test(NAME RandomTest COMMAND dungeon_tests --gtest_filter=RandomTest.*)
add_test(NAME RoomTest COMMAND dungeon_tests --gtest_filter=RoomTest.*)
add_test(NAME DungeonTest COMMAND dungeon_tests --gtest_filter=DungeonTest.*)
add_test(NAME ItemTest COMMAND dungeon_tests --gtest_filter=ItemTest.*)
add_test(NAME ScreenTest COMMAND dungeon_tests --gtest_filter=ScreenTest.*)
add_test(NAME PlayerTest COMMAND dungeon_tests --gtest_filter=PlayerTest.*)