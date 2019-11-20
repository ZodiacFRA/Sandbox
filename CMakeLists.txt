cmake_minimum_required(VERSION 3.13)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

include_directories(SBEngine)
include_directories(SBEngine/ecs)
include_directories(SBEngine/update)
include_directories(SBEngine/component)
include_directories(SBEngine/Workers)
include_directories(game)
include_directories(lib/irrlicht/includes/irrlicht)
include_directories(lib/irrKlang/includes/irrKlang)

add_executable(Sandbox
        SBEngine/ecs/ComponentBase.hpp
        SBEngine/ecs/ComponentList.hpp
        SBEngine/ecs/DataBank.hpp
        SBEngine/ecs/Ecs.cpp
        SBEngine/ecs/Ecs.hpp
        SBEngine/ecs/Entity.cpp
        SBEngine/ecs/Entity.hpp
        SBEngine/ecs/Time.cpp
        SBEngine/ecs/Time.hpp
        SBEngine/ecs/TimedEvent.cpp
        SBEngine/ecs/TimedEvent.hpp
        SBEngine/ecs/TimedEventAdmin.cpp
        SBEngine/ecs/TimedEventAdmin.hpp
	SBEngine/ecs/Vector2.hpp

        SBEngine/Workers/ThreadPool.cpp
        SBEngine/Workers/ThreadPool.hpp

	SBEngine/update/Update.hpp
	SBEngine/update/KeyboardEvent.hpp
        SBEngine/update/KeyboardEvent.cpp
        SBEngine/update/Update.cpp

        SBEngine/component/controllers/Keyboard.hpp
        SBEngine/component/SceneNode.hpp
        SBEngine/component/Online.hpp
        SBEngine/component/FpsCamera.hpp
        SBEngine/component/Speed.hpp

        SBEngine/interface/Player.cpp
        SBEngine/interface/Player.hpp
        SBEngine/interface/Map.cpp
        SBEngine/interface/Map.hpp
        SBEngine/interface/loadLevelFromFile.cpp

        Main.cpp
)

if (WIN32)
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrlicht/Irrlicht.dll)
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrKlang/IrrKlang.dll)
else()
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrlicht/libIrrlicht.so)
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrKlang/libIrrKlang.so)
endif()
