add_definitions(${MATERIALXVIEW_RENDER_BACKEND_DEFINITIONS})

include_directories(
  /home/wegatron/win-data/opensource_code/MaterialX/source/MaterialXView/NanoGUI/ext/glfw/deps
)
set(GLFW_LIBRARIES /usr/lib/x86_64-linux-gnu/libglfw.so)

file(GLOB headers *.h)
file(GLOB sources *.cpp)

add_executable(zsw_test ${headers} ${sources})

set(MATERIALX_LIBRARIES
    MaterialXFormat
    MaterialXGenGlsl
    MaterialXRender
    MaterialXRenderGlsl)
 

target_link_libraries(
  zsw_test
  ${MATERIALX_LIBRARIES}
  ${GLFW_LIBRARIES}
)
