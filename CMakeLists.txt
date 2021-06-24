cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(TestUnigine)

set(Helpers
src/Helpers/Vector2.h
src/Helpers/Vector2.cpp
src/Helpers/Point.h
src/Helpers/Point.cpp
src/Helpers/Grid.h
src/Helpers/Grid.cpp
)

set(GameClasses
src/GameClasses/Unit.h
src/GameClasses/Unit.cpp
)

source_group("Helpers" FILES ${Helpers})
source_group("GameClasses" FILES ${GameClasses})

add_executable(${PROJECT_NAME} 
${Helpers}

${GameClasses}

src/main.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)