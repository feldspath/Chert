set(GLAD_FILES
	"include/glad/glad.h"
	"include/KHR/khrplatform.h"
	"src/glad.c"
)
add_library(glad STATIC ${GLAD_FILES})
target_include_directories(glad PRIVATE include)
