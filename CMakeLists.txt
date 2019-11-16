cmake_minimum_required(VERSION 3.13)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

include_directories(ecs)
include_directories(Workers)

set(CMAKE_CXX_FLAGS "-W -Wextra -Wall -Werror -std=c++11")

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
        Main.cpp
)
