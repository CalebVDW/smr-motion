#include "SmrUtils.h"
#include "Smr.h"

#include "UnrealAPI.h"

//This is essentially a copy of Tutorial01 with all of the Horde rendering code stripped out
class UnrealTest
{
public:
  UnrealTest();
  void createKinematicChain();
  void updateKinematicChain(float totalTime);
  SMRKinematicChain *m_kinematicChain;
};

UnrealTest::UnrealTest()
{
}

//This is all copied from Tutorial01
void UnrealTest::createKinematicChain()
{
  //instantiate an empty kinematic chain
  m_kinematicChain=new SMRKinematicChain(RELATIVEMODE,TRANSLATIONFIRST,"kinematicChain");

  SMRKinematicJoint *currentJoint,*prevJoint;
  prevJoint=NULL;

  for(int i=0;i<4;i++)
  {
    //instantiate a new SMRKinematicJoint
    currentJoint = (new SMRKinematicJoint());
  
    //give a name to the joint
    char name[100];
    sprintf(name,"joint%d",i);
    //currentJoint->setName(name+i);

    //set up joint translation parameters in local frame (bone length)
    currentJoint->setPosition(0,2,0);

    //take care of parenting issues
    if(prevJoint) 
    {
      currentJoint->setParentName(prevJoint->getName());
    }

    //add the new joint into the kinematics chain
    m_kinematicChain->insertJoint(currentJoint);

    //keep a reference of the newly created joint for the next turn (parenting issue)
    prevJoint=currentJoint;
  }

  //set root joint
  m_kinematicChain->setStartJointIndex(m_kinematicChain->getJoint(0)->getName());
}

void UnrealTest::updateKinematicChain(float totalTime)
{
  SMRKinematicJoint* joint;

  //rotate first joint
  joint=m_kinematicChain->getJoint(0);
  joint->setOrientation(SMRQuaternion(SMRVector3(1,0,0),sinf(totalTime)));

  //rotate second joint
  joint=m_kinematicChain->getJoint(1);
  joint->setOrientation(SMRQuaternion(SMRVector3(1,0,0),sinf(totalTime)));

  //rotate third joint
  joint=m_kinematicChain->getJoint(2);
  joint->setOrientation(SMRQuaternion(SMRVector3(1,0,0),sinf(totalTime)));
}


UnrealTest* scene;
//Create a new scene containing the kinematic chain from Tutorial01
void SmrInitializeBones()
{
	scene = new UnrealTest();
	scene->createKinematicChain();
}
//Update the scene using the time value passed in by the Unreal scene
void SmrUpdateBones(float totalTime)
{
	scene->updateKinematicChain(totalTime);
}
//Get the orientation of a bone in the kinematic chain
SmrQuat SmrGetBoneOrientation(int index)
{
	SmrQuat quat;
	auto orientation = scene->m_kinematicChain->getJoint(index)->getOrientation();
	quat.x = orientation.m_x;
	quat.y = orientation.m_y;
	quat.z = orientation.m_z;
	quat.w = orientation.m_w;
	return quat;
}
