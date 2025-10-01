cmake_minimum_required(VERSION 3.22)
project(PhonebookApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Try to find Qt6 first, then Qt5 as fallback
find_package(Qt6 6.5 QUIET COMPONENTS Core Gui Widgets Sql Concurrent)
if(NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core Gui Widgets Sql Concurrent)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()


# Qt setup based on version
if(QT_VERSION_MAJOR EQUAL 6)
    qt_standard_project_setup()
endif()

# Sources
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    src/*.cpp 
    src/*.h
)

# Resources
set(APP_RESOURCES resources/resources.qrc)

# Create executable
if(QT_VERSION_MAJOR EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        ${APP_SOURCES}
        ${APP_RESOURCES}
    )
else()
    add_executable(${PROJECT_NAME}
        ${APP_SOURCES}
        ${APP_RESOURCES}
    )
endif()

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Link Qt libraries
if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Sql Qt6::Concurrent
    )
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Sql Qt5::Concurrent
    )
endif()


# Enable automatic MOC/UIC/RCC
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)


# Windows: set working dir for easier launching
if (WIN32)
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
endif()