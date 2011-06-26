/**
 * \ingroup SmrCore
 * \file SmrCore/SmrLoader.h
 * 
 */
#ifndef _SMRLOADER__H_
#define _SMRLOADER__H_

#include "SmrSTL.h"

#include "SmrSkeleton.h"
#include "SmrKinematicChain.h" 
#include "SmrMotion.h"

/**
* /brief
* Those C style functions are provided to load different 
* mocap file formats
*/

/**
* /brief
* Load a bvh into an SMRSkeleton
*/
SMRSkeleton loadSkeletonFromBVH(string _filename);
/**
* /brief
* Load a bvh into an SMRMotion
*/
SMRMotion loadMotionFromBVH(string _filename);
/**
* /brief
* Load an acclaim skeleton into an SMRSkeleton
*/
SMRSkeleton loadSkeletonFromAcclaim(string _filename);
/**
* /brief
* Load an Acclaim motion into an SMRMotion
*/
SMRMotion loadMotionFromAcclaim(string _skelfilename, string _motionfilename);

/**
* /brief
* Load a vsk into an SMRSkeleton
*/
SMRSkeleton loadSkeletonFromVSK(string _filename);
/**
* /brief
* Load a vsk into an SMRMotion
*/
SMRMotion loadMotionFromVSK(string _skelFileName, string _motionfilename);




inline bool expect (const string _word, ifstream &_infile){
  string chunk;
  do{_infile >> chunk;
    if (chunk == _word) return true;
  }while(!_infile.eof());
  return false;
}

#endif // _SMRLOADER__H_

