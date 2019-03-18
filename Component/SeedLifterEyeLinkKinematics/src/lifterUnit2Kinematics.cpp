#include "lifterUnit2Kinematics.h"

namespace LIFTER_KINEMA
{
  void Solve_Lifter_Fk(double eetrans[3], double joint[])
  { 
    double calcJoint[2];
    calcJoint[0] = -joint[0];
    calcJoint[1] = joint[1];
  
    eetrans[0] = LIFTER_L1*cos(M_PI/2+(-calcJoint[0]*M_PI/180)) + LIFTER_L2*cos(M_PI/2+(-calcJoint[1]*M_PI/180));
    eetrans[1] = 0;
    eetrans[2] = (MOBILE_LIFTER_Z) + LIFTER_L1*sin(M_PI/2+(-calcJoint[0]*M_PI/180)) + LIFTER_L2*sin(M_PI/2+(-calcJoint[1]*M_PI/180));
  }
}
