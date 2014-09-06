cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(META_PROJECT_NAME           "Shootet")
set(META_PROJECT_DESCRIPTION    "")
set(META_PROJECT_MAJOR          "1")
set(META_PROJECT_MINOR          "2")
set(META_PROJECT_BUILD          "1")
set(META_VERSION                "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_PROJECT_BUILD}")
set(META_AUTHOR_MAINTAINER      "mrzesn@t-online.de")

project(${META_PROJECT_NAME} C CXX)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL_ttf REQUIRED)

add_definitions(-DPLATFORM_PANDORA)

add_subdirectory(src)
