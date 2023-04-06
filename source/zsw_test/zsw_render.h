#pragma once

#include <MaterialXFormat/Util.h>
#include <MaterialXGenShader/Util.h>
#include <MaterialXRender/ShaderMaterial.h>
#include <MaterialXRender/GeometryHandler.h>
#include <MaterialXRender/LightHandler.h>
#include <MaterialXRender/ImageHandler.h>
#include <MaterialXGenGlsl/GlslShaderGenerator.h>
#include <MaterialXRenderGlsl/GlslMaterial.h>

namespace mx = MaterialX;

class ZswRender
{
 public:
    ZswRender();

    bool loadStdLibs(const std::string &libraries_search_path);
    
    void loadMaterial(const std::string &material_file);

    void loadEnvironmentLight(
                              const std::string &env_radiance_file,
                              const std::string &env_irradiance_file,
                              const std::string &direct_light_file);

    void loadGeometry(const std::string &geometry_file);

    // render frame in opengl environment
    void renderFrame();

private:

    std::vector<mx::MaterialPtr> materials_;
    mx::GenContext context_;

    mx::GeometryHandlerPtr geometry_handler_;
    mx::ImageHandlerPtr image_handler_;
    mx::LightHandlerPtr light_handler_;

    mx::DocumentPtr direct_light_doc_;
    mx::DocumentPtr std_lib_;
    mx::CameraPtr view_camera_;

    // scene options
    
};
