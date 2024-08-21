set(CHERT_INCLUDE ${PROJECT_SOURCE_DIR}/Chert/src/)

add_executable(ChertEditor 
	"src/Editor.cpp"
	"src/Panels/SceneHierarchyPanel.h"
	"src/Panels/SceneHierarchyPanel.cpp"
	"src/Panels/ContentBrowserPanel.h"
	"src/Panels/ContentBrowserPanel.cpp"
	"src/EditorLayer.h"
	"src/EditorLayer.cpp")

target_include_directories(ChertEditor PUBLIC ${CHERT_INCLUDE})
target_link_libraries(ChertEditor PUBLIC Chert)
