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

project(counting-sheep)
cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

