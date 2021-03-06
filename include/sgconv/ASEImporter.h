#pragma once

#include <blueprint/typedef.h>
#include <shaderlab/Node.h>

#include <node0/typedef.h>
#include <aseimp/FileLoader.h>
#include <SM_Vector.h>

#include <string>
#include <vector>
#include <map>

namespace sgconv
{

class ASEImporter
{
public:
    ASEImporter();

    void LoadAsset(const ur::Device& dev, const std::string& filepath);
    void LoadShader(const ur::Device& dev, const std::string& filepath);

    auto& GetNodes() const { return m_scene_nodes; }

private:
    void Load(const ur::Device& dev, const aseimp::FileLoader& loader);

    void CreateSceneNode(const bp::NodePtr& bp_node, const sm::vec2& pos);

    static int PortTypeASEImpToBP(aseimp::WirePortDataType type);
    static void InputPortASEImpToSG(std::vector<shaderlab::Node::PinDesc>& dst,
        const std::vector<aseimp::FileLoader::InputPort>& src);
    static void OutputPortASEImpToSG(std::vector<shaderlab::Node::PinDesc>& dst,
        const std::vector<aseimp::FileLoader::OutputPort>& src);

private:
    struct Node
    {
        Node(const aseimp::FileLoader::Node& src, bp::NodePtr dst) : src(src), dst(dst) {}

        const aseimp::FileLoader::Node& src;
        bp::NodePtr dst;
    };

private:
    std::vector<n0::SceneNodePtr> m_scene_nodes;

    std::map<int, Node> m_map_nodes;

}; // ASEImporter

}