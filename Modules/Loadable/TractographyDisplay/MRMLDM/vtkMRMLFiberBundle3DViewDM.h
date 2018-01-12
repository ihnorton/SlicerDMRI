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

#ifndef __vtkMRMLFiberBundle3DViewDM_h
#define __vtkMRMLFiberBundle3DViewDM_h

// Tractography includes
#include "vtkMRMLFiberBundleDMExport.h"

class vtkMRMLFiberBundleDisplayNode;
class vtkMRMLFiberBundleNode;

// MRML DisplayableManager includes
#include <vtkMRMLAbstractThreeDViewDisplayableManager.h>

// STD includes
#include <vector>

/// \ingroup Slicer_QtModules_Tractography
class VTK_SLICER_TRACTOGRAPHYDISPLAY_MODULE_MRMLDM_EXPORT vtkMRMLFiberBundle3DViewDM
  : public vtkMRMLAbstractThreeDViewDisplayableManager
{
public:
  static vtkMRMLFiberBundle3DViewDM *New();
  vtkTypeMacro(vtkMRMLFiberBundle3DViewDM, vtkMRMLAbstractThreeDViewDisplayableManager);
  void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkMRMLFiberBundle3DViewDM();
  ~vtkMRMLFiberBundle3DViewDM();
  vtkMRMLFiberBundle3DViewDM(const vtkMRMLFiberBundle3DViewDM&);
  void operator=(const vtkMRMLFiberBundle3DViewDM&);

  virtual void SetMRMLSceneInternal(vtkMRMLScene* newScene);
  virtual void ProcessMRMLNodesEvents(vtkObject *caller, unsigned long event, void *callData);

  virtual void OnMRMLSceneNodeAdded(vtkMRMLNode*);
  virtual void OnMRMLSceneNodeRemoved(vtkMRMLNode*);

private:
  class Internal;
  std::unique_ptr<Internal> P;
};

#endif
