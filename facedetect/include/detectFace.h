#ifndef IMI_FACE_DETECT_API_H_
#define IMI_FACE_DETECT_API_H_
#include"imiCV.h"


namespace imi
{
	
		 bool FaceDetectionInitialization();
		 std::vector<imi::FaceInfo> detectFace(const imiMat *pImg);
		 bool FaceDetectionRelease();

}  // namespace imi

#endif  
