cmake_minimum_required(VERSION 3.13)
project(Sandbox)
#project(TCPTest)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads)
find_package(Boost 1.65.0 REQUIRED COMPONENTS filesystem system)

include_directories(SBEngine)
include_directories(SBEngine/ecs)
include_directories(SBEngine/update)
include_directories(SBEngine/component)
include_directories(SBEngine/Workers)
include_directories(game)
include_directories(lib/irrlicht/includes/irrlicht)
include_directories(lib/irrKlang/includes/irrKlang)

include_directories(${Boost_INCLUDE_DIR})

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
        SBEngine/component/controllers/Mouse.hpp
        SBEngine/component/SceneNode.hpp
        SBEngine/component/Online.hpp
        SBEngine/component/FpsCamera.hpp
        SBEngine/component/Speed.hpp

        SBEngine/interface/loadLevelFromFile.cpp
        SBEngine/interface/loadLevelFromFile.hpp
        SBEngine/interface/PlayerCreator.cpp
        SBEngine/interface/PlayerCreator.hpp
        SBEngine/interface/ObjectCreator.cpp
        SBEngine/interface/ObjectCreator.hpp
        SBEngine/interface/MapCreator.cpp
        SBEngine/interface/MapCreator.hpp

        Main.cpp
        SBEngine/network/server/TCPServer.cpp
        SBEngine/network/server/TCPServer.hpp
        SBEngine/network/server/TCPConnection.cpp
        SBEngine/network/server/TCPConnection.hpp
        SBEngine/network/server/UDPServer.cpp
        SBEngine/network/server/UDPServer.hpp
        SBEngine/component/controllers/Light.hpp
        SBEngine/network/client/TCPClient.cpp
        SBEngine/network/client/TCPClient.hpp)
target_compile_definitions(Sandbox PRIVATE CLIENT_SOLO)

#add_executable(TCPTest
#        SBEngine/network/server/TCPServer.cpp
#        SBEngine/network/server/TCPServer.hpp
#        SBEngine/network/server/TCPConnection.cpp
#        SBEngine/network/server/TCPConnection.hpp
#        SBEngine/network/server/UDPServer.cpp
#        SBEngine/network/server/UDPServer.hpp
#
#        SBEngine/test/MainTest.cpp
#        )

if (WIN32)
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrlicht/Irrlicht.dll)
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrKlang/IrrKlang.dll)
    target_link_libraries(Sandbox ${CMAKE_THREAD_LIBS_INIT})
    target_link_libraries(Sandbox ${Boost_LIBRARIES})

#    target_link_libraries(TCPTest ${CMAKE_CURRENT_LIST_DIR}/lib/irrlicht/Irrlicht.dll)
#    target_link_libraries(TCPTest ${CMAKE_CURRENT_LIST_DIR}/lib/irrKlang/IrrKlang.dll)
#    target_link_libraries(TCPTest ${CMAKE_THREAD_LIBS_INIT})
#    target_link_libraries(TCPTest ${Boost_LIBRARIES})
else()
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrlicht/libIrrlicht.so)
    target_link_libraries(Sandbox ${CMAKE_CURRENT_LIST_DIR}/lib/irrKlang/libIrrKlang.so)
    target_link_libraries(Sandbox ${CMAKE_THREAD_LIBS_INIT})
    target_link_libraries(Sandbox ${Boost_LIBRARIES})

#    target_link_libraries(TCPTest ${CMAKE_CURRENT_LIST_DIR}/lib/irrlicht/libIrrlicht.so)
#    target_link_libraries(TCPTest ${CMAKE_CURRENT_LIST_DIR}/lib/irrKlang/libIrrKlang.so)
#    target_link_libraries(TCPTest ${CMAKE_THREAD_LIBS_INIT})
#    target_link_libraries(TCPTest ${Boost_LIBRARIES})
endif()
