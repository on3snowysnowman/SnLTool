cmake_minimum_required(VERSION 3.24)

project(SnLTool)

set(LSDLE_PATH "C:/Users/Joel/LSDLE")

# Find the LSDLE library
find_library(LSDLE_LIB NAMES LSDLE PATHS "${LSDLE_PATH}/lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# set (CMAKE_BUILD_TYPE "RELEASE")

add_library(SnLTool
    
    src/SaveHandler.cpp
    src/Simulator.cpp
    
    src/Menus/AddInventoryItemMenu.cpp
    src/Menus/AddPotionMenu.cpp
    src/Menus/AddSpellMenu.cpp
    src/Menus/CharacterSaveTypeSelectionMenu.cpp
    src/Menus/CreateCharacterMenu.cpp
    src/Menus/CreateSaveMenu.cpp
    src/Menus/DeleteSaveMenu.cpp
    src/Menus/EditInventoryItemMenu.cpp
    src/Menus/EditStatsMenu.cpp
    src/Menus/IntroMenu.cpp
    src/Menus/MainMenu.cpp
    src/Menus/ModifyHitpointManaMenu.cpp
    src/Menus/SaveLoadMenu.cpp
    src/Menus/SelectCharacterMenu.cpp
    src/Menus/SimulationMenu.cpp
    src/Menus/ViewInventoryMenu.cpp
)
 
target_include_directories(SnLTool
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Menus>
        $<BUILD_INTERFACE:${LSDLE_PATH}/include/LSDLE>
        $<BUILD_INTERFACE:${LSDLE_PATH}/include/LSDLE/MenuTools>
        $<BUILD_INTERFACE:${LSDLE_PATH}/include/LSDLE/ModularComponents>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(SnLTool
    PUBLIC
        SDL2::SDL2
        SDL2_image
        ${LSDLE_LIB}
)

add_executable(Main main.cpp)

target_link_libraries(Main ${LSDLE_LIB} SnLTool)
