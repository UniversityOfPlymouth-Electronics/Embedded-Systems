# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
set(APP_TARGET mbed-os-example-for-azure)

include(${MBED_PATH}/tools/cmake/app.cmake)

add_subdirectory(${MBED_PATH})
add_subdirectory(mbed-client-for-azure)
add_subdirectory(ntp-client)

if("wifi_ism43362" IN_LIST MBED_TARGET_LABELS)
    add_subdirectory(drivers/COMPONENT_wifi_ism43362)
endif()

add_executable(${APP_TARGET})

project(${APP_TARGET})

target_include_directories(${APP_TARGET}
    PRIVATE
        .
)

target_sources(${APP_TARGET}
    PRIVATE
        main.cpp
)

if("wifi_ism43362" IN_LIST MBED_TARGET_LABELS)
    target_link_libraries(${APP_TARGET}
        PRIVATE
            wifi-ism43362
    )
endif()

target_link_libraries(${APP_TARGET}
    PRIVATE
        mbed-client-for-azure
        mbed-os
        ntp-client
        mbed-mbedtls
)

mbed_set_post_build(${APP_TARGET})

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()
