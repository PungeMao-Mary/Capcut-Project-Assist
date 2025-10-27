cmake_minimum_required(VERSION 3.16)

project(CapcutProjectAssist VERSION 1.0 LANGUAGES CXX)

# macOS
if(APPLE)
    set(CMAKE_PREFIX_PATH "/Volumes/ExtremeSSD/Applications/Qt/6.10.0/macos")
endif()
# Windows
if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/msvc2022_64")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

set(PROJECT_SOURCES
    main.cpp
    capcutprojectassist.h
    capcutprojectassist.cpp
)

qt_add_executable(CapcutProjectAssist
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

set_target_properties(CapcutProjectAssist PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourcompany.CapcutProjectAssist"
)

target_link_libraries(CapcutProjectAssist PRIVATE
    Qt6::Widgets
    Qt6::Core
)

qt_finalize_executable(CapcutProjectAssist)

include(GNUInstallDirs)
install(TARGETS CapcutProjectAssist
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
