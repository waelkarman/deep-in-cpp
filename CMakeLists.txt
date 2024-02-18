cmake_minimum_required(VERSION 3.5)

project(main_theory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


add_executable(main_asyncfuture main_asyncfuture.cpp)
add_executable(main_atomic main_atomic.cpp)
add_executable(main_threadpromise main_threadpromise.cpp)
add_executable(main_callonce main_callonce.cpp)
add_executable(main_mutexlockguard main_mutexlockguard.cpp)
add_executable(main_conditionvariable main_conditionvariable.cpp)

add_executable(main_iterator main_iterator.cpp)
add_executable(main_template main_template.cpp)
add_executable(main_inheritance main_inheritance.cpp)
add_executable(main_copyandswap main_copyandswap.cpp)
add_executable(main_functionalobject main_functionalobject.cpp)
add_executable(main_smartpointers main_smartpointers.cpp)
add_executable(main_referencesandpointers main_referencesandpointers.cpp)
add_executable(main_friends main_friends.cpp)
add_executable(main_exceptions main_exceptions.cpp)
add_executable(main_casts main_casts.cpp)
add_executable(main_operators main_operators.cpp)

add_executable(main_theory main_theory.cpp)
add_executable(main_tricks main_tricks.cpp)

add_executable(main_io main_io.cpp)
add_executable(main_threadpooling main_threadpooling.cpp)


include(GNUInstallDirs)
install(TARGETS main_theory
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
