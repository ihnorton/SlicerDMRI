/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// Slicer includes
#include "vtkMRMLFiberBundle3DViewDM.h"

// std includes
#include <memory>

// MRML includes
#include "vtkEventBroker.h"
#include "vtkMRMLViewNode.h"
#include "vtkMRMLFiberBundleNode.h"
#include "vtkMRMLFiberBundleDisplayNode.h"
#include "vtkMRMLFiberBundleLineDisplayNode.h"
#include "vtkMRMLFiberBundleTubeDisplayNode.h"
#include "vtkMRMLFiberBundleGlyphDisplayNode.h"

#include <vtkMRMLScene.h>

// VTK includes

#include "vtkInteractorStyle.h"
#include <vtkNew.h>
#include "vtkObjectFactory.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkPointData.h"

#define vtkSP vtkSmartPointer

// TODO ifdef c++14
namespace std {
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}; // namespace std

//- Internal Implementation

struct FBPipeline {
  // data
  vtkSP<vtkActor> actor;
  vtkSP<vtkPolyDataMapper> mapper;

  // constructor
  FBPipeline() :
    actor(vtkSP<vtkActor>::New()),
    mapper(vtkSP<vtkPolyDataMapper>::New())
    {
    actor->SetMapper(mapper);
    }

  ~FBPipeline()
    {
    this->actor->Delete();
    this->mapper->Delete();
    }
};

//---------------------------------------------------------------------------

struct vtkMRMLFiberBundle3DViewDM::Internal {
  vtkMRMLFiberBundle3DViewDM* E;
  std::map< vtkMRMLNode*, std::unique_ptr<FBPipeline> > nodemap;

  // constructor
  Internal(vtkMRMLFiberBundle3DViewDM* e) { E(e); };
};

//---------------------------------------------------------------------------
vtkStandardNewMacro (vtkMRMLFiberBundle3DViewDM);

//---------------------------------------------------------------------------
vtkMRMLFiberBundle3DViewDM::vtkMRMLFiberBundle3DViewDM() :
  P(std::unique_ptr<Internal>(new Internal(this)))
{
  /*
  this->RemoveInteractorStyleObservableEvent(vtkCommand::LeftButtonPressEvent);
  this->RemoveInteractorStyleObservableEvent(vtkCommand::LeftButtonReleaseEvent);
  this->RemoveInteractorStyleObservableEvent(vtkCommand::RightButtonPressEvent);
  this->RemoveInteractorStyleObservableEvent(vtkCommand::RightButtonReleaseEvent);
  this->RemoveInteractorStyleObservableEvent(vtkCommand::MiddleButtonPressEvent);
  this->RemoveInteractorStyleObservableEvent(vtkCommand::MiddleButtonReleaseEvent);
  this->RemoveInteractorStyleObservableEvent(vtkCommand::MouseWheelBackwardEvent);
  this->RemoveInteractorStyleObservableEvent(vtkCommand::MouseWheelForwardEvent);
  this->RemoveInteractorStyleObservableEvent(vtkCommand::EnterEvent);
  this->RemoveInteractorStyleObservableEvent(vtkCommand::LeaveEvent);
  */

  this->AddInteractorStyleObservableEvent(vtkCommand::KeyPressEvent);
}

//---------------------------------------------------------------------------
vtkMRMLFiberBundle3DViewDM::~vtkMRMLFiberBundle3DViewDM()
{
}

//---------------------------------------------------------------------------
void vtkMRMLFiberBundle3DViewDM::PrintSelf(std::ostream &os, vtkIndent indent)
{
  os<<indent<<"Print logic"<<endl;
}

//---------------------------------------------------------------------------
void vtkMRMLFiberBundle3DViewDM::SetMRMLSceneInternal(vtkMRMLScene* newScene)
{
  Superclass::SetMRMLSceneInternal(newScene);
}

//---------------------------------------------------------------------------
void vtkMRMLFiberBundle3DViewDM::ProcessMRMLNodesEvents
       (vtkObject *caller, unsigned long event, void * vtkNotUsed(callData))
{
  if (!caller->IsA("vtkMRMLFiberBundleDisplayNode")) return;
}

void vtkMRMLFiberBundle3DViewDM::OnMRMLSceneNodeAdded(vtkMRMLNode* node)
{
  if (!node->IsA("vtkMRMLFiberBundleTubeDisplayNode")) return;

  auto dnode = vtkMRMLFiberBundleTubeDisplayNode::SafeDownCast(node);
  auto p = std::unique_ptr<FBPipeline>(new FBPipeline());
  this->P->nodemap[dnode] = std::make_unique(p);

  p->mapper->SetInputConnection(dnode->GetOutputMeshConnection());
  this->GetRenderer()->AddViewProp(p->actor);
}

void vtkMRMLFiberBundle3DViewDM::OnMRMLSceneNodeRemoved(vtkMRMLNode* node)
{
  if (!node->IsA("vtkMRMLFiberBundleNode")) return;

}
