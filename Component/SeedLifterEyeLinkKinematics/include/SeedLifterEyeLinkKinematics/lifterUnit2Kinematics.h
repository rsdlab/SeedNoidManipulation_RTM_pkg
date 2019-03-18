// lifterUnit2Kinematics.h
#ifndef __LIFTERUNIT2KINEMATICS_H_
#define __LIFTERUNIT2KINEMATICS_H_

//数学定数の使用
#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>

#define LIFTER_L1 250
#define LIFTER_L2 250
#define MOBILE_LIFTER_Z 415

namespace LIFTER_KINEMA
{
    void Solve_Lifter_Fk(double eetrans[3], double joint[]);
}

#endif // __LIFTERUNIT2KINEMATICS_H_
