### CMakeLists file for downloading external dependencies

## Get fetch content
include(FetchContent)

## List of dependencies
set(GFX_DEPS
    "GLFW https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip"
    "GLAD https://gitfront.io/r/Moztanku/8s4L1GHF3Tsc/Resources/raw/glad-cmake.zip")

function (download_dep dep)
    string(REPLACE " " ";" dep_list ${dep})

    list(GET dep_list 0 dep_name)
    list(GET dep_list 1 dep_url)

    message(STATUS "Downloading ${dep_name} from ${dep_url}")

    FetchContent_Declare(
        ${dep_name}
        URL ${dep_url}
        SOURCE_DIR ${VENDOR_DIR}/${dep_name}
    )

    FetchContent_MakeAvailable(${dep_name})
endfunction()

if(${PROJECT_NAME}_GRAPHICS)
    foreach(dep ${GFX_DEPS})
        download_dep(${dep})
    endforeach()
endif()
