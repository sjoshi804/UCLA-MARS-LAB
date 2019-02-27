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
  KLT_FaceList faces = KLTCreateFaceList(2);
  VJ_Face face1 = VJCreateFace(10, 10, 100, 100);
  printf("Reaches here\n");
  VJ_Face face2 = VJCreateFace(110, 110, 100, 100);
  faces.faceList[0] = face1;
  faces.faceList[1] = face2;
  img1 = pgmReadFile("img0.pgm", NULL, &ncols, &nrows);
  img2 = pgmReadFile("img2.pgm", NULL, &ncols, &nrows);

  printf("not Initialization error");
  KLTSelectGoodFeatures(tc, img1, ncols, nrows, fl, &faces);

  printFeatures(&faces);

  KLTWriteFeatureListToPPM(fl, img1, ncols, nrows, "feat1b.ppm");

  KLTTrackFeatures(tc, img1, img2, ncols, nrows, fl);

  KLTWriteFeatureListToPPM(fl, img2, ncols, nrows, "feat2b.ppm");

  return 0;
}

