include("vcpkg.cmake")
file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.h" "imgui-console-master/include/*.h" "imgui-console-master/src/*.cpp")
file(GLOB_RECURSE SERVER_SOURCES "server/*.h" "server/*.cpp")

add_executable (ChessSFML ${SOURCES})
add_executable (ChessServer ${SERVER_SOURCES})

target_link_libraries(ChessSFML PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio imgui::imgui ImGui-SFML::ImGui-SFML unofficial::sqlite3::sqlite3)

target_link_libraries(ChessServer PRIVATE sfml-system sfml-network)

find_package(SFML COMPONENTS system window graphics network audio CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

target_include_directories(ChessSFML PRIVATE "include")
target_include_directories(ChessSFML PRIVATE "imgui-console-master/include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ChessSFML PROPERTY CXX_STANDARD 20)
  set_property(TARGET ChessServer PROPERTY CXX_STANDARD 20)
endif()

# Копирование ресурсов игры
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/ChessSFML/source")
set(DESTINATION_DIR ${CMAKE_BINARY_DIR})
file(COPY ${SOURCE_DIR} DESTINATION "${DESTINATION_DIR}/ChessSFML")