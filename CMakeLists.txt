cmake_minimum_required(VERSION 3.23)
project(theia LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_library(theia)
add_library(theia::theia ALIAS theia)

target_compile_features(theia PUBLIC cxx_std_23)

target_sources(theia
        PRIVATE
        # [[[cog
        # import glob
        # import os
        #
        # sources = glob.glob("src/**/*.cpp", recursive=True)
        # for f in sorted(sources):
        #     cog.outl(f'"{f.replace(os.sep, "/")}"')
        # ]]]
        "src/glfwpp/context.cpp"
        "src/glfwpp/cursor.cpp"
        "src/glfwpp/glfwpp.cpp"
        "src/glfwpp/input.cpp"
        "src/glfwpp/monitor.cpp"
        "src/glfwpp/window.cpp"
        "src/theia/dear.cpp"
        "src/theia/io.cpp"
        "src/theia/logger.cpp"
        "src/theia/theia.cpp"
        # [[[end]]]

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
        # [[[cog
        # import glob
        # import os
        #
        # headers = glob.glob("include/**/*.hpp", recursive=True)
        # for f in sorted(headers):
        #     cog.outl(f'"{f.replace(os.sep, "/")}"')
        # ]]]
        "include/glfwpp/context.hpp"
        "include/glfwpp/cursor.hpp"
        "include/glfwpp/glfwpp.hpp"
        "include/glfwpp/input.hpp"
        "include/glfwpp/monitor.hpp"
        "include/glfwpp/window.hpp"
        "include/theia/dear.hpp"
        "include/theia/hermes.hpp"
        "include/theia/io.hpp"
        "include/theia/logger.hpp"
        "include/theia/theia.hpp"
        # [[[end]]]

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS thirdparty/stb
        FILES
        # [[[cog
        # import glob
        # import os
        #
        # headers = glob.glob("thirdparty/stb/**/*.h", recursive=True)
        # for f in sorted(headers):
        #     cog.outl(f'"{f.replace(os.sep, "/")}"')
        # ]]]
        "thirdparty/stb/stb_image.h"
        # [[[end]]]

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS thirdparty/imgui/include
        FILES
        # [[[cog
        # import glob
        # import os
        #
        # headers = glob.glob("thirdparty/imgui/include/**/*.h", recursive=True)
        # for f in sorted(headers):
        #     cog.outl(f'"{f.replace(os.sep, "/")}"')
        # ]]]
        "thirdparty/imgui/include/imconfig.h"
        "thirdparty/imgui/include/imgui.h"
        "thirdparty/imgui/include/imgui_impl_glfw.h"
        "thirdparty/imgui/include/imgui_impl_opengl3.h"
        "thirdparty/imgui/include/imgui_impl_opengl3_loader.h"
        "thirdparty/imgui/include/imgui_internal.h"
        "thirdparty/imgui/include/imstb_rectpack.h"
        "thirdparty/imgui/include/imstb_textedit.h"
        "thirdparty/imgui/include/imstb_truetype.h"
        # [[[end]]]

        PRIVATE
        # [[[cog
        # import glob
        # import os
        #
        # sources = glob.glob("thirdparty/imgui/src/**/*.cpp", recursive=True)
        # for f in sorted(sources):
        #     cog.outl(f'"{f.replace(os.sep, "/")}"')
        # ]]]
        "thirdparty/imgui/src/imgui.cpp"
        "thirdparty/imgui/src/imgui_demo.cpp"
        "thirdparty/imgui/src/imgui_draw.cpp"
        "thirdparty/imgui/src/imgui_impl_glfw.cpp"
        "thirdparty/imgui/src/imgui_impl_opengl3.cpp"
        "thirdparty/imgui/src/imgui_tables.cpp"
        "thirdparty/imgui/src/imgui_widgets.cpp"
        # [[[end]]]
)

target_compile_definitions(theia PUBLIC IMGUI_IMPL_GLFW_DISABLE_X11)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 12.0.0
)
FetchContent_MakeAvailable(fmt)

set(SPDLOG_FMT_EXTERNAL ON)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG v1.16.0
)
FetchContent_MakeAvailable(spdlog)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_INSTALL OFF)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG glad2
        SOURCE_SUBDIR cmake
)
FetchContent_MakeAvailable(glad)
glad_add_library(glad_gl_core_46 REPRODUCIBLE API gl:core=4.6)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 1.0.2
)
FetchContent_MakeAvailable(glm)

target_link_libraries(theia PUBLIC
        glad_gl_core_46
        fmt::fmt
        spdlog::spdlog
        glfw
        glad_gl_core_46
        glm::glm
)

add_subdirectory("example")
