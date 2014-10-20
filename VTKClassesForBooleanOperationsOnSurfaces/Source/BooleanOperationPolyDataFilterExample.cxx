#include <vtkActor.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSTLReader.h>

vtkActor* GetBooleanOperationActor( double x, int operation )
{
  double centerSeparation = 0.15;

  vtkSmartPointer<vtkSTLReader> reader =
          vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName("sphere-dilated.stl");

  vtkSmartPointer<vtkSphereSource> sphere1 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere1->SetThetaResolution(50);
  sphere1->SetPhiResolution(50);
  sphere1->SetRadius(2.5);

  vtkSmartPointer<vtkBooleanOperationPolyDataFilter> boolFilter =
    vtkSmartPointer<vtkBooleanOperationPolyDataFilter>::New();
  boolFilter->SetOperation( operation );
  boolFilter->SetInputConnection(0, reader->GetOutputPort());
  boolFilter->SetInputConnection(1, sphere1->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(boolFilter->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkActor *actor = vtkActor::New();
  actor->SetMapper(mapper);
  actor->SetPosition(-centerSeparation + x, 0.0, 0.0);

  return actor;
}

int main(int argc, char* argv[])
{
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renWinInteractor->SetRenderWindow( renWin );

  vtkActor *unionActor =
    GetBooleanOperationActor(-10.0, vtkBooleanOperationPolyDataFilter::VTK_UNION);
  renderer->AddActor( unionActor );
  unionActor->Delete();

  vtkActor *intersectionActor =
    GetBooleanOperationActor(0.0, vtkBooleanOperationPolyDataFilter::VTK_INTERSECTION);
  renderer->AddActor( intersectionActor );
  intersectionActor->Delete();

  vtkActor *differenceActor =
    GetBooleanOperationActor(10.0, vtkBooleanOperationPolyDataFilter::VTK_DIFFERENCE);
  renderer->AddActor( differenceActor );
  differenceActor->Delete();

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> interactorStyle =
          vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renWinInteractor->SetInteractorStyle(interactorStyle);

  renWin->Render();
  renWinInteractor->Start();

  return EXIT_SUCCESS;
}
