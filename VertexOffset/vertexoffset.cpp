#include <iostream>
#include "Common.h"
#include <string>
using namespace std;
#include <fbxsdk/utils/fbxclonemanager.h>
#include <fbxsdk/core/fbxobject.h>

void DisplayContent(FbxNode *pNode);
void DisplayMesh(FbxNode *pNode);
void DisplayControlsPoints(FbxMesh *pMesh);

int main(int, char **)
{
  std::cout << "Hello, vertexoffset!" << std::endl;
  FbxManager *lSdkManager = NULL;
  FbxScene *lScene = NULL;

  // Prepare the FBX SDK.
  InitializeSdkObjects(lSdkManager, lScene);

  string lFilePath = R"(D:\work\code\study\github\other\fbxsdk\cplus\tt.fbx)";

  auto lResult = LoadScene(lSdkManager, lScene, lFilePath.c_str());
  FbxNode *rootNode = lScene->GetRootNode();

  if (rootNode)
  {
    for (auto i = 0; i < rootNode->GetChildCount(); i++)
    {
      DisplayContent(rootNode->GetChild(i));
    }
  }
  SaveScene(lSdkManager, lScene, "tt2.fbx");
  return 0;
}

void DisplayContent(FbxNode *pNode)
{
  for (auto i = 0; i < pNode->GetChildCount(); i++)
  {
    DisplayContent(pNode->GetChild(i));
  }

  FbxNodeAttribute::EType lAttributeType;
  if (pNode->GetNodeAttribute() == NULL)
  {
    std::cout << "NULL Node Attribute" << std::endl;
    return;
  }
  lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());
  if (FbxNodeAttribute::eMesh == lAttributeType)
  {
    DisplayMesh(pNode);
  }
}
void DisplayMesh(FbxNode *pNode)
{
  FbxMesh *lMesh = (FbxMesh *)pNode->GetNodeAttribute();
  DisplayControlsPoints(lMesh);
}
void DisplayControlsPoints(FbxMesh *pMesh)
{
  int i, lControlPointsCount = pMesh->GetControlPointsCount();
  FbxVector4 *lControlPoints = pMesh->GetControlPoints();
  for (i = 0; i < lControlPointsCount; i++)
  {
    lControlPoints[i][0] = lControlPoints[i][0] - 2;
    lControlPoints[i][1] = lControlPoints[i][1] - 2;
  }
}