add_definitions(${MATERIALXVIEW_RENDER_BACKEND_DEFINITIONS})

add_executable(zsw_test zsw_render.h zsw_render.cpp main.cpp)

set(MATERIALX_LIBRARIES
    MaterialXFormat
    MaterialXGenGlsl
    MaterialXRender
    MaterialXRenderGlsl)
 

target_link_libraries(
  zsw_test
  ${MATERIALX_LIBRARIES}
)
