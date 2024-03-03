# External dependencies
add_subdirectory(external/spdlog/)
add_subdirectory(external/glfw/)

set(CHERT_SRC 
    src/Chert/Application.cpp
    src/Chert/LayerStack.cpp
    src/Chert/Log.cpp
    src/Chert/WindowsWindow.cpp
)

set(CHERT_HEADERS
    src/Chert.h
    src/Chert/Application.h
    src/Chert/Core.h
    src/Chert/EntryPoint.h
    src/Chert/Layer.h
    src/Chert/LayerStack.h
    src/Chert/Log.h
    src/Chert/Window.h
    src/Chert/WindowsWindow.h
    src/Chert/Events/ApplicationEvent.h
    src/Chert/Events/Event.h
    src/Chert/Events/KeyEvent.h
    src/Chert/Events/MouseEvent.h
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${CHERT_SRC} ${CHERT_HEADERS})

add_library(Chert STATIC ${CHERT_SRC} ${CHERT_HEADERS})

# Headers
target_include_directories(Chert PUBLIC external/spdlog/include)
target_include_directories(Chert PUBLIC external/glfw/include)
target_include_directories(Chert PUBLIC src/)

# Libaries
target_link_libraries(Chert glfw)
target_link_libraries(Chert spdlog::spdlog)
find_package(OpenGL REQUIRED)
target_link_libraries(Chert ${OPENGL_LIBRARIES})

target_compile_definitions(Chert PUBLIC CHERT_PLATFORM_WINDOWS)
target_compile_definitions(Chert PUBLIC "$<$<CONFIG:Debug>:CHERT_BUILD_DEBUG>")

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(isMultiConfig)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "" FORCE) 
endif()