cmake_minimum_required(VERSION 3.23)

project(BreakoutClone
        VERSION 0.2
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# For YouCompleteMe Intillisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/olcPixelGameEngine/olcPixelGameEngine.h")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

set(SOURCES
    src/BallGraphicsComponent.cpp
    src/BallInputComponent.cpp
    src/BallPhysicsComponenet.cpp
    src/BatGraphicsComponent.cpp
    src/BatInputComponent.cpp
    src/BatPhysicsComonent.cpp
    src/GameObject.cpp
    src/BreakOut.cpp
	src/World.cpp
    src/main.cpp
	src/olcPixelGameEngine.cpp
)

set(HEADERS
    src/BallInputComponent.h
    src/BallGraphicsComponent.h
    src/BallPhysicsComponenet.h
    src/BatGraphicsComponent.h
    src/BatInputComponent.h
    src/BatPhysicsComponent.h
    src/BreakOut.h
    src/GameObject.h
    src/GraphicsComponent.h
    src/InputComponent.h
    src/PhysicsComponent.h
	src/World.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/external/olcPixelGameEngine/)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(PNG REQUIRED)

set(LINK_LIBS ${X11_LIBRARIES}
              ${OPENGL_LIBRARIES}
              Threads::Threads
              ${PNG_LIBRARIES}
              stdc++fs
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LINK_LIBS})
