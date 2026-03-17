cmake_minimum_required(VERSION 3.16)

project(Qt_ParticleSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appQt_ParticleSystem
    main.cpp
    Application/constants.cpp
    Application/simulationengine.cpp
    Application/physicsmanager.cpp
    Application/particlerenderer.cpp
    Interface/cppinterface.cpp
)


qt_add_qml_module(appQt_ParticleSystem
    URI Qt_ParticleSystem
    VERSION 1.0
    QML_FILES
        Presentation/Main.qml
        Presentation/Particle.qml
        SOURCES Application/constants.h Application/constants.cpp
        SOURCES Application/simulationengine.h Application/simulationengine.cpp
        SOURCES Interface/cppinterface.h Interface/cppinterface.cpp
        SOURCES Application/particlerenderer.h Application/particlerenderer.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQt_ParticleSystem PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQt_ParticleSystem
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQt_ParticleSystem
    PRIVATE Qt6::Quick
)
target_link_libraries(appQt_ParticleSystem PRIVATE Qt6::Core)
target_link_libraries(appQt_ParticleSystem PRIVATE Qt6::Core)
target_link_libraries(appQt_ParticleSystem PRIVATE Qt6::Core)
target_link_libraries(appQt_ParticleSystem PRIVATE Qt6::Core Qt6::Quick)

target_include_directories(appQt_ParticleSystem PUBLIC
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Application>
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
)

include(GNUInstallDirs)
install(TARGETS appQt_ParticleSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
