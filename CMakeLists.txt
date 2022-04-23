cmake_minimum_required(VERSION 3.23)

project(BreakoutClone
        VERSION 0.2
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# YouCompleteMe Intillisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/BallGraphicsComponent.cpp
    src/BallInputComponent.cpp
    src/BallPhysicsComponenet.cpp
    src/BatGraphicsComponent.cpp
    src/BatInputComponent.cpp
    src/BatPhysicsComonent.cpp
    src/GameObject.cpp
    src/olcPixelGameEngine.cpp
    src/BreakOut.cpp
    src/World.cpp
    src/main.cpp
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

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

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
