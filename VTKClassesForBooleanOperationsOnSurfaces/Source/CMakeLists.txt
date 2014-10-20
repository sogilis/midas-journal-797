CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#Change PROJECT_NAME to the name of your project
PROJECT(BooleanOperationPolyData)

FIND_PACKAGE(VTK 5.10 REQUIRED)
INCLUDE(${VTK_USE_FILE})

#Set any libraries that your project depends on.
#examples: ITKCommon, VTKRendering, etc
SET(Libraries
  vtkFiltering
  vtkGraphics
  vtkIO
  vtkRendering
)


SET(CurrentExe "PolyDataBooleanOperationFilterExample")
ADD_EXECUTABLE(${CurrentExe}
  BooleanOperationPolyDataFilterExample.cxx
)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} )
