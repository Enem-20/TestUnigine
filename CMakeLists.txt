cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(TestUnigine)

set(Helpers
src/Helpers/Vector2.h
src/Helpers/Vector2.cpp
src/Helpers/IVector2.h
src/Helpers/IVector2.cpp
src/Helpers/Grid.h
src/Helpers/Grid.cpp
)

set(GameClasses
src/GameClasses/Unit.h
src/GameClasses/Unit.cpp
)

set(Resources
src/Resources/ResourceManager.h
src/Resources/ResourceManager.cpp
src/Resources/Serializer.h
src/Resources/Serializer.cpp
)

set(Components
src/Components/Vision.h
src/Components/Vision.cpp
)

source_group("Helpers" FILES ${Helpers})
source_group("GameClasses" FILES ${GameClasses})
source_group("Resources" FILES ${Resources})
source_group("Components" FILES ${Components})

add_executable(${PROJECT_NAME} 
${Helpers}

${GameClasses}

${Resources}

${Components}

src/main.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_include_directories(${PROJECT_NAME} PUBLIC external/rapidjson/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)