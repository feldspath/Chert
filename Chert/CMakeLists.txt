# External dependencies
add_compile_definitions(_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)
add_subdirectory(external/spdlog/)
add_subdirectory(external/glfw/)
add_subdirectory(external/glad/)
add_subdirectory(external/glm/)

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(external/assimp/)

set(CHERT_SRC
    "src/Chert/Core/Application.cpp"
    "src/Chert/Core/LayerStack.cpp"
    "src/Chert/Core/Log.cpp"
    "src/Chert/Core/Input.cpp"

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
    "src/Chert/Renderer/Buffers/Buffers.cpp"

    # Scene
    "src/Chert/Scene/Scene.cpp"

    # Resources
    "src/Chert/Resources/ResourceManager.cpp"
)

set(CHERT_HEADERS
    "src/Chert.h"

    # Core
    "src/Chert/Core/Application.h"
    "src/Chert/Core/Core.h"
    "src/Chert/Core/EntryPoint.h"
    "src/Chert/Core/Layer.h"
    "src/Chert/Core/LayerStack.h"
    "src/Chert/Core/Log.h"
    "src/Chert/Core/Window.h"
    "src/Chert/Core/Input.h"
    "src/Chert/Core/Keycodes.h"
    "src/Chert/Core/MouseButtons.h"

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
    "src/Chert/Renderer/Camera.h"
    
    # Scene
    "src/Chert/Scene/Scene.h"
    "src/Chert/Scene/Entity/Entity.h"
    "src/Chert/Scene/Entity/NativeScript.h"
    "src/Chert/Scene/Components/Transform.h"
    "src/Chert/Scene/Components/Camera.h"
    "src/Chert/Scene/Components/Mesh.h"
    "src/Chert/Scene/Components/NativeScript.h"
    "src/Chert/Scene/Model/Mesh.h"
    "src/Chert/Scene/Model/Model.h"

    # Resources
    "src/Chert/Resources/ResourceManager.h"
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${CHERT_SRC} ${CHERT_HEADERS})

add_library(Chert STATIC ${CHERT_SRC} ${CHERT_HEADERS})

# Headers
target_include_directories(Chert PUBLIC external/spdlog/include)
target_include_directories(Chert PUBLIC external/glfw/include)
target_include_directories(Chert PUBLIC external/glad/include)
target_include_directories(Chert PUBLIC external/imgui/)
target_include_directories(Chert PUBLIC external/entt/src)
target_include_directories(Chert PUBLIC external/nativefiledialog/src/include)
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

# nfd
# todo: handle other platforms
set(NFD_FILES 
    "external/nativefiledialog/src/nfd_common.c"
    #"external/nativefiledialog/src/nfd_gtk.c"
    "external/nativefiledialog/src/nfd_win.cpp"
    #"external/nativefiledialog/src/nfd_zenity.c"
)
add_library(nfd STATIC ${NFD_FILES})
target_include_directories(nfd PUBLIC external/nativefiledialog/src/include)

target_link_libraries(Chert glfw)
target_link_libraries(Chert spdlog)
target_link_libraries(Chert glad)
target_link_libraries(Chert glm)
target_link_libraries(Chert assimp)
find_package(OpenGL REQUIRED)
target_link_libraries(Chert ${OPENGL_LIBRARIES})
target_link_libraries(Chert imgui)
target_link_libraries(Chert nfd)

target_compile_definitions(Chert PUBLIC CHERT_PLATFORM_WINDOWS)
target_compile_definitions(Chert PUBLIC "$<$<CONFIG:Debug>:CHERT_BUILD_DEBUG>")

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(isMultiConfig)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "" FORCE) 
endif()