#include <iostream>
#include <glad/gl.h>
#include "glfw_window.h"
#include "zsw_render.h"

namespace mx = MaterialX;

int main(int argc, char * argv[])
{    
    x_engine::samples::Window::Properties properties;
    properties.title = "zsw_materialx_demo";

    x_engine::samples::GlfwWindow window(properties);
    
    // init glad
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD!");
    }

    //std::string material_file = "/home/wegatron/win-data/opensource_code/MaterialX/resources/Materials/Examples/GltfPbr/gltf_pbr_boombox.mtlx";
    std::string material_file = "/home/wegatron/win-data/opensource_code/MaterialX/resources/Materials/Examples/StandardSurface/standard_surface_default.mtlx";
    std::string env_radiance_file = "/home/wegatron/win-data/opensource_code/MaterialX/resources/Lights/san_giuseppe_bridge_split.hdr";
    std::string env_irradiance_file = "/home/wegatron/win-data/opensource_code/MaterialX/resources/Lights/irradiance/san_giuseppe_bridge_split.hdr";
    std::string geometry_file = "/home/wegatron/win-data/opensource_code/MaterialX/resources/Geometry/shaderball.glb";
    std::string direct_light_file = "/home/wegatron/win-data/opensource_code/MaterialX/resources/Lights/san_giuseppe_bridge_split.mtlx";    
    ZswRender zsw_render;

    zsw_render.setViewSize(properties.extent.width, properties.extent.height);

    zsw_render.loadStdLibs("/home/wegatron/win-data/opensource_code/MaterialX");

    // load environment light before material
    zsw_render.loadEnvironmentLight(env_radiance_file, env_irradiance_file, direct_light_file);
    zsw_render.loadMaterial(material_file);

    zsw_render.loadGeometry(geometry_file);

    window.setWindowSizeCallback([&zsw_render](int width, int height){ zsw_render.setViewSize(width, height); });    

    while (!window.should_close()) {
        window.process_events();
        zsw_render.renderFrame();
        glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(window.get_handle()));
    }
    
    std::cout << "finish" << std::endl;
    return 0;
}
