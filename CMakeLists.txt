cmake_minimum_required(VERSION 3.13)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

include_directories(ecs)
include_directories(Workers)
include_directories("${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/include")

add_executable(Sandbox
        ecs/ComponentBase.hpp
        ecs/ComponentList.hpp
        ecs/DataBank.hpp
        ecs/Ecs.hpp
        ecs/Entity.cpp
        ecs/Entity.hpp
        ecs/Time.cpp
        ecs/Time.hpp
        ecs/TimedEvent.cpp
        ecs/TimedEvent.hpp
        ecs/TimedEventAdmin.cpp
        ecs/TimedEventAdmin.hpp
        ecs/Vector2.hpp
        Workers/ThreadPool.cpp
        Workers/ThreadPool.hpp
        Main.cpp)

TARGET_LINK_LIBRARIES(Sandbox "${PROJECT_SOURCE_DIR}/lib/libIrrlicht.so.1.8.4")
        #"/usr/lib64/libIrrlicht.so.1.8.4")
