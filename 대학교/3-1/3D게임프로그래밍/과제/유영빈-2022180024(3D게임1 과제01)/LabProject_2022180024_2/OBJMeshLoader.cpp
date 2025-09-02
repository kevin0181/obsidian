#include "OBJMeshLoader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

CMesh* LoadOBJToMesh(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return nullptr;

    std::vector<XMFLOAT3> vertices;
    std::vector<std::vector<int>> faces;

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v")
        {
            float x, y, z;
            iss >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        }
        else if (type == "f")
        {
            std::vector<int> face;
            std::string vertexStr;
            while (iss >> vertexStr)
            {
                std::istringstream vss(vertexStr);
                std::string idxStr;
                std::getline(vss, idxStr, '/'); // 정점/텍스처/노멀 무시
                int index = std::stoi(idxStr) - 1;
                face.push_back(index);
            }

            if (face.size() == 3 || face.size() == 4)
                faces.push_back(face);
        }
    }

    CMesh* pMesh = new CMesh(static_cast<int>(faces.size()));

    for (size_t i = 0; i < faces.size(); ++i)
    {
        const auto& face = faces[i];
        CPolygon* poly = new CPolygon(static_cast<int>(face.size()));
        for (size_t j = 0; j < face.size(); ++j)
        {
            XMFLOAT3 pos = vertices[face[j]];
            poly->SetVertex(static_cast<int>(j), CVertex(pos.x, pos.y, pos.z));
        }
        pMesh->SetPolygon(static_cast<int>(i), poly);
    }

    // 바운딩 박스 생성
    BoundingBox bbox;
    BoundingBox::CreateFromPoints(bbox, static_cast<UINT>(vertices.size()), vertices.data(), sizeof(XMFLOAT3));
    BoundingOrientedBox obb;
    BoundingOrientedBox::CreateFromBoundingBox(obb, bbox);
    pMesh->m_xmOOBB = obb;

    return pMesh;
}
