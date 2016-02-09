//This header declares all functions exposed to Unreal
//There is also a .def file included in this project to prevent C++ function name mangling
#ifdef UNREALAPI_EXPORTS
#define UNREALAPI_API __declspec(dllexport) 
#else
#define UNREALAPI_API __declspec(dllimport) 
#endif

//A simple struct to use to carry data from SMR to Unreal
//SmrMath structures cannot be used in Unreal without linking all of the SMR libraries to the Unreal project 
//Obviously a more advanced system will be needed in the future but this will work for a quick example
struct SmrQuat{
	float x;
	float y;
	float z;
	float w;
};

void UNREALAPI_API SmrInitializeBones();
void UNREALAPI_API SmrUpdateBones(float totalTime);
SmrQuat UNREALAPI_API SmrGetBoneOrientation(int index);