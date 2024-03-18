cmake_minimum_required(VERSION 3.0.0)
project(WorkoutManager VERSION 0.1.0)


add_executable(WorkoutManager main.cpp date.cpp date.h exercise.cpp exercise.h user.cpp 
user.h utilities.h utilities.cpp workout.cpp workout.h Training.h 
Training.cpp functions.h functions.cpp binaryrw.h binaryrw.cpp)

if(MSVC)
  target_compile_options(WorkoutManager PRIVATE /W4 /WX)
else()
  target_compile_options(WorkoutManager PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 17)
