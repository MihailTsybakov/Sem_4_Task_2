cmake_minimum_required(VERSION 3.1)

project(Task_2_Sem_4)

include_directories(${PROJECT_SOURCE_DIR})

set(TASK_1_SRC main.cpp Create.cpp CIntN.cpp Autotest.cpp exceptions.cpp Factory.cpp CIntN_hori.cpp CIntN_vert.cpp)
set(TASK_1_HDR CIntN.h Create.h Autotest.h CIntN_hori.h CIntN_vert.h Factory.h)

add_executable(${PROJECT_NAME} ${TASK_1_SRC} ${TASK_1_HDR})
