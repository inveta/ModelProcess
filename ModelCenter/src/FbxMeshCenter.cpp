#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Exporter.hpp>

void FindMeshInfo(const aiScene *scene, aiNode *node)
{
  //std::cout << node->mName.C_Str() << std::endl;
  if (0 == node->mNumMeshes)
  {
    return;
  }
  std::string nodeName = node->mName.C_Str();

  aiVector3D nodeCenter(0, 0, 0);
  for (unsigned int meshi = 0; meshi < node->mNumMeshes; meshi++)
  {
    auto meshIndex = node->mMeshes[meshi];
    auto mesh = scene->mMeshes[meshIndex];

    aiVector3D meshCenter(0, 0, 0);
    for (unsigned int facei = 0; facei < mesh->mNumFaces; facei++)
    {
      aiVector3D faceCenter(0, 0, 0);
      auto face = mesh->mFaces[facei];
      for (unsigned int indicei = 0; indicei < face.mNumIndices; indicei++)
      {
        auto indice = face.mIndices[indicei];
        faceCenter = faceCenter + mesh->mVertices[indice];
      }
      faceCenter = faceCenter /= (ai_real)face.mNumIndices;
      meshCenter = meshCenter + faceCenter;
    }
    meshCenter = meshCenter /= (ai_real)mesh->mNumFaces;
    nodeCenter = nodeCenter + meshCenter;
  }
  nodeCenter = nodeCenter /= (ai_real)node->mNumMeshes;
  nodeCenter = nodeCenter *= node->mTransformation;
  auto parent = node->mParent;
  while (true)
  {
    if (nullptr == parent)
    {
      break;
    }
    std::string name = parent->mName.C_Str();
    {
      nodeCenter = nodeCenter *= parent->mTransformation;
    }

    parent = parent->mParent;
  }

  std::cout << node->mName.C_Str() << std::endl;
  std::cout << "x:" << nodeCenter.x << " y:" << nodeCenter.y << " z:" << nodeCenter.z << std::endl;
}
void FindMesh(const aiScene *scene, aiNode *node)
{
  FindMeshInfo(scene, node);
  for (unsigned int m = 0; m < node->mNumChildren; ++m)
  {
    FindMesh(scene, node->mChildren[m]);
  }
}

int main()
{
  std::cout << "Hello, from FbxParsing!\n";

  auto inFile = R"(tt.fbx)";
  Assimp::Importer mImporter;
  const aiScene *mScenePtr = mImporter.ReadFile(inFile, aiProcess_MakeLeftHanded);
  if (nullptr == mScenePtr)
  {
    std::cout << "nullptr == mScenePtr" << std::endl;
    return -1;
  }

  auto rootNode = mScenePtr->mRootNode;
  FindMesh(mScenePtr, rootNode);
  Assimp::Exporter mExporter;
  mExporter.Export(mScenePtr, "fbxa", "1.fbx");

  return 0;
}