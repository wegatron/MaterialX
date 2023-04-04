#include "zsw_render.h"

#include <iostream>

#include <MaterialXRender/StbImageLoader.h>
#include <MaterialXRenderGlsl/GLTextureHandler.h>

ZswRender::ZswRender() 
    : context_(mx::GlslShaderGenerator::create()), 
    image_handler_(mx::GLTextureHandler::create(mx::StbImageLoader::create())), 
    light_handler_(mx::LightHandler::create())
{

}

void ZswRender::loadGeometry(const std::string &geometry_file)
{
    geometry_handler_->loadGeometry(geometry_file);
}

void ZswRender::loadEnvironmentLight(
                                     const std::string &env_radiance_file,
                                     const std::string &env_irradiance_file)
{
    mx::ImagePtr env_radiance_map = image_handler_->acquireImage(env_radiance_file);
    if(!env_radiance_map) {
        std::cerr << "*** Load Light warnings for " << env_radiance_file << " ***" << std::endl;
        std::throw_with_nested(std::runtime_error("loadEnvironmentLight Fail!"));
    }

    mx::ImagePtr env_irradiance_map = image_handler_->acquireImage(env_irradiance_file);
    if(!env_irradiance_map) {
        std::cerr << "*** Load Light warnings for " << env_irradiance_file << " ***" << std::endl;
        std::throw_with_nested(std::runtime_error("loadEnvironmentLight Fail!"));
    }
    
    image_handler_->releaseRenderResources(light_handler_->getEnvRadianceMap());
    image_handler_->releaseRenderResources(light_handler_->getEnvIrradianceMap());
    light_handler_->setEnvRadianceMap(env_radiance_map);
    light_handler_->setEnvIrradianceMap(env_irradiance_map);
}

void ZswRender::loadMaterial(const std::string &material_file)
{
    mx::DocumentPtr doc = mx::createDocument();
    mx::readFromXmlFile(doc, material_file);

    // Validate the document.
    std::string message;
    if (!doc->validate(&message))
    {
        std::cerr << "*** Validation warnings for " << material_file << " ***" << std::endl;
        std::cerr << message;
        std::throw_with_nested(std::runtime_error("Validation errors found."));
    }    

    std::vector<mx::TypedElementPtr> elems = mx::findRenderableElements(doc);
    std::vector<mx::NodePtr> materialNodes;
    mx::StringVec renderablePaths;
    for (mx::TypedElementPtr elem : elems)
    {
        mx::TypedElementPtr renderableElem = elem;
        mx::NodePtr node = elem->asA<mx::Node>();
        materialNodes.push_back(node && node->getType() == mx::MATERIAL_TYPE_STRING ? node : nullptr);
        auto renderable_path = renderableElem->getNamePath();
        renderablePaths.push_back(renderableElem->getNamePath());
    }

    // Check for any udim set.
    mx::ValuePtr udimSetValue = doc->getGeomPropValue(mx::UDIM_SET_PROPERTY);

    // Create new materials.
    mx::TypedElementPtr udimElement;
    for (size_t i=0; i<renderablePaths.size(); i++)
    {
        const auto& renderablePath = renderablePaths[i];
        mx::ElementPtr elem = doc->getDescendant(renderablePath);
        mx::TypedElementPtr typedElem = elem ? elem->asA<mx::TypedElement>() : nullptr;
        if (!typedElem)
        {
            continue;
        }
        if (udimSetValue && udimSetValue->isA<mx::StringVec>())
        {
            for (const std::string& udim : udimSetValue->asA<mx::StringVec>())
            {
                mx::MaterialPtr mat = mx::GlslMaterial::create();
                mat->setDocument(doc);
                mat->setElement(typedElem);
                mat->setMaterialNode(materialNodes[i]);
                mat->setUdim(udim);
                materials_.push_back(mat);
                udimElement = typedElem;
            }
        }
        else
        {
            mx::MaterialPtr mat = mx::GlslMaterial::create();
            mat->setDocument(doc);
            mat->setElement(typedElem);
            mat->setMaterialNode(materialNodes[i]);
            materials_.push_back(mat);
        }
    }

    // context
    auto gen_context = mx::GlslShaderGenerator::create();
    if (!materials_.empty())
    {
        // Extend the image search path to include material source folders.
        // mx::FileSearchPath extendedSearchPath = _searchPath;
        // extendedSearchPath.append(_materialSearchPath);
        // _imageHandler->setSearchPath(extendedSearchPath);

        mx::MaterialPtr udimMaterial = nullptr;
        for (mx::MaterialPtr mat : materials_)
        {
            // Clear cached implementations, in case libraries on the file system have
            context_.clearNodeImplementations();

            mx::TypedElementPtr elem = mat->getElement();

            std::string udim = mat->getUdim();
            if (!udim.empty())
            {
                if ((udimElement == elem) && udimMaterial)
                {
                    // Reuse existing material for all udims
                    mat->copyShader(udimMaterial);
                }
                else {
                    // Generate a shader for the new material.
                    mat->generateShader(context_);
                    if (udimElement == elem) {
                        udimMaterial = mat;
                    }
                }
            }
            else {
                // Generate a shader for the new material.
                mat->generateShader(context_);
            }
        }
    }
}


void ZswRender::renderFrame()
{
    // initialize opengl state
    // glDisable(GL_BLEND);
    // glEnable(GL_DEPTH_TEST);
    // glDepthMask(GL_TRUE);
    // glDepthFunc(GL_LEQUAL);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // glDisable(GL_CULL_FACE);
    // glDisable(GL_FRAMEBUFFER_SRGB);

    // update lighting state    
    //light_handler_->setLightTransform(mx::Matrix44::createRotationY(lightRotation / 180.0f * PI));
}
