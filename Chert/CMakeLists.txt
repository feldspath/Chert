# External dependencies
add_compile_definitions(_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)
add_subdirectory(external/spdlog/)
add_subdirectory(external/glfw/)
add_subdirectory(external/glad/)
add_subdirectory(external/glm/)

set(CHERT_SRC
    "src/Chert/Application.cpp"
    "src/Chert/LayerStack.cpp"
    "src/Chert/Log.cpp"
    "src/Chert/Input.cpp"

    # Imgui
    "src/Chert/Imgui/ImguiBuild.cpp"
    "src/Chert/Imgui/ImguiLayer.cpp"

    # Platform specific
    "src/Platform/Windows/WindowsWindow.cpp"
    "src/Platform/Windows/WindowsInput.cpp"
    "src/Platform/OpenGL/OpenGLContext.cpp"
    "src/Platform/OpenGL/OpenGLShader.cpp"
    "src/Platform/OpenGL/Buffers/OpenGLVertexBuffer.cpp"
    "src/Platform/OpenGL/Buffers/OpenGLIndexBuffer.cpp"
    "src/Platform/OpenGL/Buffers/OpenGLVertexArray.cpp"
    "src/Platform/OpenGL/OpenGLRenderAPI.cpp"

    # Rendering
    "src/Chert/Renderer/Renderer.cpp"
    "src/Chert/Renderer/RenderAPI.cpp"
)

set(CHERT_HEADERS
    "src/Chert.h"
    "src/Chert/Application.h"
    "src/Chert/Core.h"
    "src/Chert/EntryPoint.h"
    "src/Chert/Layer.h"
    "src/Chert/LayerStack.h"
    "src/Chert/Log.h"
    "src/Chert/Window.h"
    "src/Chert/Input.h"

    # Events
    "src/Chert/Events/ApplicationEvent.h"
    "src/Chert/Events/BaseEvent.h"
    "src/Chert/Events/KeyEvent.h"
    "src/Chert/Events/MouseEvent.h"
    "src/Chert/Events/Event.h"

    # Imgui
    "src/Chert/Imgui/ImguiLayer.h"

    # Platform specific
    "src/Platform/Windows/WindowsWindow.h"
    "src/Platform/Windows/WindowsInput.h"
    "src/Platform/OpenGL/OpenGLContext.h"
    "src/Platform/OpenGL/OpenGLShader.h"
    "src/Platform/OpenGL/Buffers/OpenGLVertexBuffer.h"
    "src/Platform/OpenGL/Buffers/OpenGLIndexBuffer.h"
    "src/Platform/OpenGL/Buffers/OpenGLVertexArray.h"
    "src/Platform/OpenGL/OpenGLRenderAPI.h"

    # Renderer
    "src/Chert/Renderer/Renderer.h"
    "src/Chert/Renderer/RenderingContext.h"
    "src/Chert/Renderer/Shader.h"
    "src/Chert/Renderer/Buffers/VertexBuffer.h"
    "src/Chert/Renderer/Buffers/IndexBuffer.h"
    "src/Chert/Renderer/Buffers/BufferLayout.h"
    "src/Chert/Renderer/Buffers/VertexArray.h"
    "src/Chert/Renderer/RenderAPI.h"
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${CHERT_SRC} ${CHERT_HEADERS})

add_library(Chert STATIC ${CHERT_SRC} ${CHERT_HEADERS})

# Headers
target_include_directories(Chert PUBLIC external/spdlog/include)
target_include_directories(Chert PUBLIC external/glfw/include)
target_include_directories(Chert PUBLIC external/glad/include)
target_include_directories(Chert PUBLIC external/imgui/)
target_include_directories(Chert PUBLIC external/glm/)
target_include_directories(Chert PUBLIC src/)

# Libaries

# imgui
set(IMGUI_FILES
	"external/imgui/imgui.cpp"
	"external/imgui/imgui_demo.cpp"
	"external/imgui/imgui_draw.cpp"
	"external/imgui/imgui_tables.cpp"
	"external/imgui/imgui_widgets.cpp"
)
add_library(imgui STATIC ${IMGUI_FILES})

target_link_libraries(Chert glfw)
target_link_libraries(Chert spdlog)
target_link_libraries(Chert glad)
target_link_libraries(Chert glm)
find_package(OpenGL REQUIRED)
target_link_libraries(Chert ${OPENGL_LIBRARIES})
target_link_libraries(Chert imgui)

target_compile_definitions(Chert PUBLIC CHERT_PLATFORM_WINDOWS)
target_compile_definitions(Chert PUBLIC "$<$<CONFIG:Debug>:CHERT_BUILD_DEBUG>")

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(isMultiConfig)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "" FORCE) 
endif()