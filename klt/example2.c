/**********************************************************************
Finds the 100 best features in an image, tracks these
features to the next image, and replaces the lost features with new
features in the second image.  Saves the feature
locations (before and after tracking) to text files and to PPM files.
**********************************************************************/

#include "pnmio.h"
#include "klt.h"

#ifdef WIN32
int RunExample2()
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
  KLT_FaceList faces = KLTCreateFaceList(2);
  VJ_Face face1 = VJCreateFace(10, 10, 100, 100);
  VJ_Face face2 = VJCreateFace(110, 110, 100, 100);
  faces.faceList[0] = face1;
  faces.faceList[1] = face2;
  img1 = pgmReadFile("img0.pgm", NULL, &ncols, &nrows);
  img2 = pgmReadFile("img1.pgm", NULL, &ncols, &nrows);

  KLTSelectGoodFeatures(tc, img1, ncols, nrows, fl, &faces);

  KLTWriteFeatureListToPPM(fl, img1, ncols, nrows, "feat1.ppm");
  KLTWriteFeatureList(fl, "feat1.txt", "%3d");

  KLTTrackFeatures(tc, img1, img2, ncols, nrows, fl);
  KLTReplaceLostFeatures(tc, img2, ncols, nrows, fl, &faces);

  KLTWriteFeatureListToPPM(fl, img2, ncols, nrows, "feat2.ppm");
  KLTWriteFeatureList(fl, "feat2.txt", "%3d");

  return 0;
}

