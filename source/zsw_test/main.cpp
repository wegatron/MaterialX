#include <iostream>

#include "zsw_render.h"

namespace mx = MaterialX;

int main(int argc, char * argv[])
{
    std::string material_file = "/home/wegatron/win-data/opensource_code/MaterialX/resources/Materials/Examples/GltfPbr/gltf_pbr_boombox.mtlx";
    std::string env_radiance_file = "/home/wegatron/win-data/opensource_code/MaterialX/resources/Lights/san_giuseppe_bridge_split.hdr";
    std::string env_irradiance_file = "/home/wegatron/win-data/opensource_code/MaterialX/resources/Lights/irradiance/san_giuseppe_bridge_split.hdr";
    std::string geometry_file = "/home/wegatron/win-data/opensource_code/MaterialX/resources/Geometry/shaderball.glb";
    ZswRender zsw_render;
    zsw_render.loadMaterial(material_file);
    zsw_render.loadEnvironmentLight(env_radiance_file, env_irradiance_file);
    zsw_render.loadGeometry(geometry_file);

    // render frame
    return 0;
}
