include("C:/Users/gmens/vcpkg/scripts/buildsystems/vcpkg.cmake")
file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.h" "imgui-console-master/include/*.h" "imgui-console-master/src/*.cpp")


add_executable (ChessSFML ${SOURCES} "include/NetServer.h")
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(ChessSFML PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)
find_package(imgui CONFIG REQUIRED)
target_link_libraries(ChessSFML PRIVATE imgui::imgui)


find_package(ImGui-SFML CONFIG REQUIRED)
target_link_libraries(ChessSFML PRIVATE ImGui-SFML::ImGui-SFML)


target_include_directories(ChessSFML PRIVATE "include")

target_include_directories(ChessSFML PRIVATE "imgui-console-master/include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ChessSFML PROPERTY CXX_STANDARD 20)
endif()

# Копирование ресурсов игры
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/ChessSFML/source")
set(DESTINATION_DIR ${CMAKE_BINARY_DIR})
file(COPY ${SOURCE_DIR} DESTINATION "${DESTINATION_DIR}/ChessSFML")