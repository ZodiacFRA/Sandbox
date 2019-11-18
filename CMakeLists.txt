cmake_minimum_required(VERSION 3.13)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

include_directories(ecs)
include_directories(Workers)
include_directories(lib/irrlicht/includes/irrlicht)
include_directories(lib/irrKlang/includes/irrKlang)

#include_directories("/usr/include/irrlicht")

add_executable(Sandbox
        ecs/ComponentBase.hpp
        ecs/ComponentList.hpp
        ecs/DataBank.hpp
        ecs/Ecs.cpp
        ecs/Ecs.hpp
        ecs/Entity.cpp
        ecs/Entity.hpp
        ecs/Time.cpp
        ecs/Time.hpp
        ecs/TimedEvent.cpp
        ecs/TimedEvent.hpp
        ecs/TimedEventAdmin.cpp
        ecs/TimedEventAdmin.hpp
        update/Updates.hpp
        update/KeyboardEvent.hpp
        ecs/Vector2.hpp
        Workers/ThreadPool.cpp
        Workers/ThreadPool.hpp

        component/SceneNode.hpp
        component/Speed.hpp

        Main.cpp component/controllers/Keyboard.hpp update/KeyboardEvent.cpp)

if (WIN32)
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrlicht/Irrlicht.dll)
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrKlang/IrrKlang.dll)
else()
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrlicht/libIrrlicht.so)
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrKlang/libIrrKlang.so)
endif()