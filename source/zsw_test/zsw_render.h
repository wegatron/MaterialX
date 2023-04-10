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
    ZswRender(const std::string &search_path);

    bool loadStdLibs();
    
    void loadMaterial(const std::string &material_file);

    void loadEnvironmentLight(
                              const std::string &env_radiance_file,
                              const std::string &env_irradiance_file,
                              const std::string &direct_light_file);

    void loadGeometry(const std::string &geometry_file);

    // render frame in opengl environment
    void renderFrame();

    void setViewSize(uint32_t width, uint32_t height);

private:

    void resetViewCamera();
    
    void updateViewCamera();

    mx::FileSearchPath search_path_;
    mx::GenContext context_;

    std::vector<mx::MaterialPtr> materials_;

    mx::GeometryHandlerPtr geometry_handler_;
    mx::ImageHandlerPtr image_handler_;
    mx::LightHandlerPtr light_handler_;
    mx::ShadowState shadow_state_;    

    mx::DocumentPtr direct_light_doc_;
    mx::DocumentPtr std_lib_;
    
    mx::CameraPtr view_camera_;
};
