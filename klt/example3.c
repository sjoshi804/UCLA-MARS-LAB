/**********************************************************************
Finds the 150 best features in an image and tracks them through the 
next two images.  The sequential mode is set in order to speed
processing.  The features are stored in a feature table, which is then
saved to a text file; each feature list is also written to a PPM file.
**********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "pnmio.h"
#include "klt.h"

//#define REPLACE 

#ifdef WIN32
int RunExample3()
#else
int main()
#endif
{
  unsigned char *img1, *img2;
  char fnamein[100], fnameout[100];
  KLT_TrackingContext tc;
  KLT_FeatureList fl;
  KLT_FeatureTable ft;
  
  int nFeatures = 150, nFrames = 12;
  int ncols, nrows;
  int i;

  tc = KLTCreateTrackingContext();
  fl = KLTCreateFeatureList(nFeatures);
  ft = KLTCreateFeatureTable(nFrames, nFeatures);
  
  tc->sequentialMode = TRUE;
  tc->writeInternalImages = FALSE;
  tc->affineConsistencyCheck = 2;  /* set this to 2 to turn on affine consistency check */


  //Modify code to work correctly 
  /*
  int flag;
  int in_flag , in_width , in_height , in_maxgrey;
  int ret_val=1;
	     
  printf ("-- entering main function --\r\n");
  printf ("-- loading image --\r\n");
         
  // 320 X 240 Input image in hex format 
  #include INPUT_IMAGE

  double duration;

  // Arguments to be passed to DUT	
  MyRect result[RESULT_SIZE];
  int result_x[RESULT_SIZE];
  int result_y[RESULT_SIZE];
  int result_w[RESULT_SIZE];
  int result_h[RESULT_SIZE];

  int res_size=0;
  int *result_size = &res_size;
  int i;

  // As the SDSoC generated data motion network does not support sending 320 X 240 images at once
  // We needed to send all the 240 rows using 240 iterations. The last invokation of detectFaces() does the actual face detection

  for ( i = 0; i < IMAGE_HEIGHT-1; i+=1 ){
      detectFaces ( Data[i], result_x, result_y, result_w, result_h, result_size);
  }

  printf ("-- detecting faces --\r\n");

  std::clock_t start = std::clock();
  detectFaces ( Data[IMAGE_HEIGHT-1], result_x, result_y, result_w, result_h, result_size);
  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

  printf("\nresult_size = %d", *result_size);

  KLT_FaceList faces = KLTCreateFaceList(*result_size);
  for (int j = 0; j < RESULT_SIZE; j++)
    faces.faceList[j] = VJCreateFace(result_x[j], result_y[j], result_w[j], result_h[j]);

  if ( *result_size > 0)
    ret_val = 0;
  */

  //Delete this after ensuring code above works
  KLT_FaceList faces = KLTCreateFaceList(1);      
  VJ_Face face1 = VJCreateFace(244, 82, 44, 44); 
  faces.faceList[0] = face1;
  //Delete the 3 lines above


  img1 = pgmReadFile("frame0.pgm", NULL, &ncols, &nrows);
  img2 = (unsigned char *) malloc(ncols*nrows*sizeof(unsigned char));

  KLTSelectGoodFeatures(tc, img1, ncols, nrows, fl, &faces);
  KLTStoreFeatureList(fl, ft, 0);
  KLTWriteFeatureListToPPM(fl, img1, ncols, nrows, "noReplacenewOutput0.ppm");

  for (i = 1 ; i < nFrames ; i++)  {
    sprintf(fnamein, "frame%d0.pgm", i);
    pgmReadFile(fnamein, img2, &ncols, &nrows);
    KLTTrackFeatures(tc, img1, img2, ncols, nrows, fl);
#ifdef REPLACE
      KLTReplaceLostFeatures(tc, img2, ncols, nrows, fl, &faces);
#endif
    KLTStoreFeatureList(fl, ft, i);
    sprintf(fnameout, "noReplacenewOutput%d.pgm", i);
    KLTWriteFeatureListToPPM(fl, img2, ncols, nrows, fnameout);
  }
  KLTWriteFeatureTable(ft, "features.txt", "%5.1f");
  KLTWriteFeatureTable(ft, "features.ft", NULL);

  KLTFreeFeatureTable(ft);
  KLTFreeFeatureList(fl);
  KLTFreeTrackingContext(tc);
  free(img1);
  free(img2);

  return 0;
}

