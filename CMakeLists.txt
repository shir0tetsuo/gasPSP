cmake_minimum_required(VERSION 3.5)

project(gaSP)

set(IMG_ASSETS_DIR "${CMAKE_SOURCE_DIR}/img")

# **Add this section to find the PSP SDK**
find_path(PSPSDK_INCLUDE_DIR pspkernel.h
    /home/inpw/pspdev/psp/sdk/include
    #/usr/local/pspdev/psp/sdk/include # Example alternative location
    # Add more potential locations if needed
)

# Check if the PSP SDK was found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PSPSDK DEFAULT_MSG PSPSDK_INCLUDE_DIR)

add_executable(${PROJECT_NAME} main.c)

# **Include the found directory**
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PSPSDK_INCLUDE_DIR} 
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pspdebug
    pspdisplay
    pspge
    pspctrl
    pspaudio
    pspaudiolib
    psputility
)

# Create an EBOOT.PBP file
create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH ${IMG_ASSETS_DIR}/ICON0.png
    BACKGROUND_PATH ${IMG_ASSETS_DIR}/PIC1.png
    PREVIEW_PATH NULL
    TITLE ${PROJECT_NAME}
    VERSION 01.00
)
