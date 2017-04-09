# Copyright (c) 2016 olibre <olibre@Lmap.org>
#
# This file is licensed under the "Fair License":
#     Usage of the works is permitted provided
#     that this instrument is retained with the works,
#     so that any entity that uses the works
#     is notified of this instrument.
#     DISCLAIMER: THE WORKS ARE WITHOUT WARRANTY.
#
# Possible French translation:
#     Les oeuvres peuvent etre reutilisees
#     a condition d'etre accompagnees du texte de cette licence,
#     afin que tout utilisateur en soit informe'.
#     AVERTISSEMENT : LES OEUVRES N'ONT AUCUNE GARANTIE.

project (GCJ-2017-Qualification)

cmake_minimum_required (VERSION 3.5)

set (CMAKE_CXX_STANDARD 14)
#set (CMAKE_CXX_STANDARD_REQUIRED ON)
#add_definitions( -D_GLIBCXX_USE_CXX11_ABI=0 )

# Release if no BUILD_TYPE
if (NOT CMAKE_BUILD_TYPE)
    message (STATUS "** No build type => Default is 'Release'")
    set (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug") # For 'cmake -i' and 'cmake-gui'
endif()
message (STATUS "** Build type = ${CMAKE_BUILD_TYPE}")

# Speed up build if ccache installed
find_program (ccache ccache)
if (ccache)
    message(STATUS "** Command 'ccache' detected => Use 'ccache' to speed up build" )
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK    ccache)
    #et_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache) # Before cmake-3.4
    set (CMAKE_C_COMPILER_LAUNCHER   ccache)
    set (CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()


#add_compile_options( -pipe )
add_compile_options( -march=native )
#add_compile_options (-Ofast)
add_compile_options (-g -ggdb3)

add_compile_options (-Wall   ) #Classic warnings
add_compile_options (-Wextra ) #Extra amount of warnings
add_compile_options (-Weffc++) #Effective C++ series of books from Scott Meyers
add_compile_options (-pedantic ) #Reject code not following ISO C++ (e.g. GNU extensions)
add_compile_options (-pedantic-errors ) #Pedantic warnings are converted into errors
add_compile_options (-Winit-self ) #Variables initialized with themselves (enabled by -Wall)
add_compile_options (-Wswitch-enum ) #Missing case for values of switch(enum)
add_compile_options (-Wcast-align ) #Incompatible alignment pointers
add_compile_options (-Wcast-qual ) #Cast between pointers leads to target type qualifier removal
add_compile_options (-Wconversion ) #Conversion might lead to value alteration, confusing overload resolution
add_compile_options (-Wformat=2 ) #Invalid argument types and format strings in formatting functions (printf, scanf...)
add_compile_options (-Winit-self ) #Uninitialized variable initialized with themselves
add_compile_options (-Wuninitialized ) #Variable used without being initialized
add_compile_options (-Wmissing-field-initializers ) #Fields is left uninitialized during (non-designated) structure initialization
add_compile_options (-Wmissing-include-dirs ) #User-supplied include directory does not exist
add_compile_options (-Wpointer-arith ) #[void and function] Operations addition/subtraction/sizeof are GNU extension
add_compile_options (-Wredundant-decls ) #Multiple declarations of the same entity is encountered in the same scope
#dd_compile_options (-Wshadow ) #Variable/typedef/struct/class/enum shadows another one having same name
add_compile_options (-Wswitch ) #Missing enumerated type in 'case' labels
add_compile_options (-fstack-protector-strong ) #Checks for buffer overflows such as stack smashing attacks (extra code is added)
add_compile_options (-Wstack-protector ) #Warn if option '-fstack-protector-strong' complained about codes vulnerable to stack smashing
add_compile_options (-Wunreachable-code ) #Unreachable code
add_compile_options (-Wunused ) #Unused entity (functions, labels, variables, typedefs, parameters, ...)
add_compile_options (-Wwrite-strings ) #Deprecated conversion from string literals to 'char *' (enable by default in C++)

add_executable (a a.cpp)
add_executable (b b.cpp)
add_executable (c c.cpp)
add_executable (d d.cpp)
