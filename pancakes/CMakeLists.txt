# Copyright (c) 2016 olibre <olibre@Lmap.org>
#
# Fair License:   Usage of the works is permitted provided
#                 that this instrument is retained with the works,
#                 so that any entity that uses the works
#                 is notified of this instrument.
#                 DISCLAIMER: THE WORKS ARE WITHOUT WARRANTY.
#
# Possible French Translation:
#
#                 Les oeuvres peuvent etre reutilisees
#                 a condition d'etre accompagnees du texte de cette licence,
#                 afin que tout utilisateur en soit informe'.
#                 AVERTISSEMENT : LES OEUVRES N'ONT AUCUNE GARANTIE.
#
# Extract of the GOOGLE CODE JAM TERMS AND CONDITIONS
# accepted by olibre in order to participate to the contest:
#
# 8. Ownership; Rights in Your Submissions; Privacy.
#  8.3 License to Submissions.
#      For any submission you make to the Contest,
#      you grant Google a non-exclusive, worldwide, perpetual, irrevocable,
#      free license (with the right to sublicense) to reproduce,
#      prepare derivative works of, distribute, publicly perform,
#      publicly display, and otherwise use such submission for the purpose
#      of administering and promoting the Contest.
#      Your submitted source code may be made available for anyone
#      to view on the Internet and download and use at the end of the Contest.

project (revenge-of-the-pancakes)

cmake_minimum_required (VERSION 2.8)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Default = Release
if (NOT CMAKE_BUILD_TYPE)
    message (STATUS "** No build type => Default is 'Release'")
    set (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug") # For 'cmake -i' and 'cmake-gui'
endif()

aux_source_directory (. SRC_LIST)
add_executable (${PROJECT_NAME} ${SRC_LIST})

add_compile_options (-Ofast)

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
add_compile_options (-Wshadow ) #Variable/typedef/struct/class/enum shadows another one having same name
add_compile_options (-Wswitch ) #Missing enumerated type in 'case' labels
add_compile_options (-fstack-protector-strong ) #Checks for buffer overflows such as stack smashing attacks (extra code is added)
add_compile_options (-Wstack-protector ) #Warn if option '-fstack-protector-strong' complained about codes vulnerable to stack smashing
add_compile_options (-Wunreachable-code ) #Unreachable code
add_compile_options (-Wunused ) #Unused entity (functions, labels, variables, typedefs, parameters, ...)
add_compile_options (-Wwrite-strings ) #Deprecated conversion from string literals to 'char *' (enable by default in C++)

