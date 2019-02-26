/**********************************************************************
Demonstrates manually tweaking the tracking context parameters.
**********************************************************************/

#include "pnmio.h"
#include "klt.h"
#include <stdlib.h>

#ifdef WIN32
int RunExample5()
#else
int main()
#endif
{
  unsigned char *img1, *img2;
  KLT_TrackingContext tc;
  KLT_FeatureList fl;
  int nFeatures = 100;
  int ncols, nrows;

  tc = KLTCreateTrackingContext();
  fl = KLTCreateFeatureList(nFeatures);
  //TODO: make functions for initialization
  KLT_FaceList faces;
  faces.nFaces = 2;
  faces.faceList = (VJ_Face*) malloc(sizeof(VJ_Face) * faces.nFaces);
  VJ_Face face1;
  face1.features = NULL; face1.startX = face1.startY = 10; 
  face1.limitX = face1.limitY = 110;
  VJ_Face face2;
  face2.features = NULL; face2.startX = face2.startY = 110; 
  face2.limitX = face2.limitY = 210;
  faces.faceList[0] = face1;
  faces.faceList[1] = face2;
  img1 = pgmReadFile("img0.pgm", NULL, &ncols, &nrows);
  img2 = pgmReadFile("img2.pgm", NULL, &ncols, &nrows);

  KLTSelectGoodFeatures(tc, img1, ncols, nrows, fl, &faces);

  KLTWriteFeatureListToPPM(fl, img1, ncols, nrows, "feat1b.ppm");

  KLTTrackFeatures(tc, img1, img2, ncols, nrows, fl);

  KLTWriteFeatureListToPPM(fl, img2, ncols, nrows, "feat2b.ppm");

  return 0;
}

