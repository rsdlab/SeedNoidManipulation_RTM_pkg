#include "manipulator.h"

Manipulator::Manipulator()
{

}

void Manipulator::CalcManipLinkPos(fourDOF J,SegLine manip[LinkNum])
{
  float rad = M_PI / 180;  //degをradへ
  J.theta2 += -90;
  //原点
  manip[0].a.x = 0;
  manip[0].a.y = 0;
  manip[0].a.z = 0;
  //リンク1_end
  manip[0].b.x = 0;
  manip[0].b.y = 0;
  manip[0].b.z = LINK1;
  //リンク2_start
  manip[1].a.x = 0;
  manip[1].a.y = 0;
  manip[1].a.z = LINK1;
  //リンク2_end
  manip[1].b.x = cos(J.theta1 * rad) * (LINK2*cos((J.theta2)*rad));
  manip[1].b.y = sin(J.theta1 * rad) * (LINK2*cos((J.theta2)*rad));
  manip[1].b.z = LINK2*sin((J.theta2)*rad) + LINK1;
  //リンク3_start
  manip[2].a.x = cos(J.theta1 * rad) * (LINK2*cos((J.theta2)*rad));
  manip[2].a.y = sin(J.theta1 * rad) * (LINK2*cos((J.theta2)*rad));
  manip[2].a.z = LINK2*sin((J.theta2)*rad) + LINK1;
  //リンク3_end
  manip[2].b.x = cos(J.theta1 * rad) * (LINK2*cos((J.theta2)*rad) + LINK3*cos((J.theta2 + J.theta3)*rad));
  manip[2].b.y = sin(J.theta1 * rad) * (LINK2*cos((J.theta2)*rad) + LINK3*cos((J.theta2 + J.theta3)*rad));
  manip[2].b.z = (LINK2*sin((J.theta2)*rad) + LINK3*sin((J.theta2 + J.theta3)*rad)) + LINK1;
  //リンク4_start
  manip[3].a.x = cos(J.theta1 * rad) * (LINK2*cos((J.theta2)*rad) + LINK3*cos((J.theta2 + J.theta3)*rad));
  manip[3].a.y = sin(J.theta1 * rad) * (LINK2*cos((J.theta2)*rad) + LINK3*cos((J.theta2 + J.theta3)*rad));
  manip[3].a.z = (LINK2*sin((J.theta2)*rad) + LINK3*sin((J.theta2 + J.theta3)*rad)) + LINK1;
  //リンク4_end
  manip[3].b.x = cos(J.theta1 * rad) * (LINK2*cos((J.theta2)*rad) + LINK3*cos((J.theta2 + J.theta3)*rad) + LINK4*cos((J.theta2 + J.theta3 + J.theta4)*rad));
  manip[3].b.y = sin(J.theta1 * rad) * (LINK2*cos((J.theta2)*rad) + LINK3*cos((J.theta2 + J.theta3)*rad) + LINK4*cos((J.theta2 + J.theta3 + J.theta4)*rad));
  manip[3].b.z = (LINK2*sin((J.theta2)*rad) + LINK3*sin((J.theta2 + J.theta3)*rad) + LINK4*sin((J.theta2 + J.theta3 + J.theta4)*rad)) + LINK1;
}

void Manipulator::CalcManipLinkPos_ten(TenDOF J,SegLine manip[LinkNum])
{
  double eetrans_1[3];
  double eetrans_2[3];
  double eetrans_3[3];
  double eetrans_4[3];
  double eetrans_5[3];
  double eetrans_6[3];
  double eerot[9];
  double elbowAbsolute;
  double elbow;
  double elbow_a;
  double elbow_b;
  double Mobile_z = 196;
  double Lifter_z = 720;

  elbow = J.theta7;
  elbowAbsolute = 0.000000000000491110199391109*pow(elbow,6) - 0.00000000039070227836422*pow(elbow,5) + 0.000000130488756716618*pow(elbow,4) - 0.0000234826686984491*pow(elbow,3) + 0.00161963482241845*pow(elbow,2) + 0.261403325177525*elbow - 0.00665618754283059;
  elbow_a = -0.00000000692890119585732*pow(elbowAbsolute,6) + 0.00000124710103754921*pow(elbowAbsolute,5) - 0.000084428935736014*pow(elbowAbsolute,4) + 0.0031388252882607*pow(elbowAbsolute,3) - 0.0662216643686406*pow(elbowAbsolute,2) + 2.63918264403765*elbowAbsolute + 0.0360316324076848;
  elbow_b = 0.0000000459591281663785*pow(elbowAbsolute,6) - 0.00000466502825657855*pow(elbowAbsolute,5) + 0.000185818559202744*pow(elbowAbsolute,4) - 0.00313808415239691*pow(elbowAbsolute,3) + 0.0314923537516734*pow(elbowAbsolute,2) + 1.03307512408355*elbowAbsolute + 0.0815648272255203;
  
  double seednoid_ikfast_joint[12];
  seednoid_ikfast_joint[0] = J.theta1*M_PI/180;
  seednoid_ikfast_joint[1] = J.theta2*M_PI/180;
  seednoid_ikfast_joint[2] = J.theta3*M_PI/180;
  seednoid_ikfast_joint[3] = -J.theta4*M_PI/180;
  seednoid_ikfast_joint[4] = -0.1745;//仮想10°
  seednoid_ikfast_joint[5] = -J.theta5*M_PI/180+M_PI/2;
  seednoid_ikfast_joint[6] = -J.theta6*M_PI/180;
  seednoid_ikfast_joint[7] = elbow_a*M_PI/180;
  seednoid_ikfast_joint[8] = elbow_b*M_PI/180;
  seednoid_ikfast_joint[9] = -J.theta8*M_PI/180;
  seednoid_ikfast_joint[10] = -J.theta9*M_PI/180;
  seednoid_ikfast_joint[11] = -J.theta10*M_PI/180;
  
  double ikjoint_1[4];
  ikjoint_1[0] = seednoid_ikfast_joint[0];
  ikjoint_1[1] = seednoid_ikfast_joint[1];
  ikjoint_1[2] = seednoid_ikfast_joint[2];
  ikjoint_1[3] = seednoid_ikfast_joint[3];
  IKFAST_LINK1::ComputeFk(ikjoint_1,eetrans_1,eerot);
  manip[0].a.x = 0;
  manip[0].a.y = 0;
  manip[0].a.z = 0;
  manip[0].b.x = eetrans_1[0]*1000;//mmに変換
  manip[0].b.y = eetrans_1[1]*1000;
  manip[0].b.z = eetrans_1[2]*1000 + Mobile_z + Lifter_z;
  
  double ikjoint_2[6];
  ikjoint_2[0] = seednoid_ikfast_joint[0];
  ikjoint_2[1] = seednoid_ikfast_joint[1];
  ikjoint_2[2] = seednoid_ikfast_joint[2];
  ikjoint_2[3] = seednoid_ikfast_joint[3];
  ikjoint_2[4] = seednoid_ikfast_joint[4];
  ikjoint_2[5] = seednoid_ikfast_joint[5];
  IKFAST_LINK2::ComputeFk(ikjoint_2,eetrans_2,eerot);
  manip[1].a.x = eetrans_1[0]*1000;
  manip[1].a.y = eetrans_1[1]*1000;
  manip[1].a.z = eetrans_1[2]*1000 + Mobile_z + Lifter_z;
  manip[1].b.x = eetrans_2[0]*1000;
  manip[1].b.y = eetrans_2[1]*1000;
  manip[1].b.z = eetrans_2[2]*1000 + Mobile_z + Lifter_z;
  
  double ikjoint_3[8];
  ikjoint_3[0] = seednoid_ikfast_joint[0];
  ikjoint_3[1] = seednoid_ikfast_joint[1];
  ikjoint_3[2] = seednoid_ikfast_joint[2];
  ikjoint_3[3] = seednoid_ikfast_joint[3];
  ikjoint_3[4] = seednoid_ikfast_joint[4];
  ikjoint_3[5] = seednoid_ikfast_joint[5];
  ikjoint_3[6] = seednoid_ikfast_joint[6];
  ikjoint_3[7] = seednoid_ikfast_joint[7];
  IKFAST_LINK3::ComputeFk(ikjoint_3,eetrans_3,eerot);
  manip[2].a.x = eetrans_2[0]*1000;
  manip[2].a.y = eetrans_2[1]*1000;
  manip[2].a.z = eetrans_2[2]*1000 + Mobile_z + Lifter_z;
  manip[2].b.x = eetrans_3[0]*1000;
  manip[2].b.y = eetrans_3[1]*1000;
  manip[2].b.z = eetrans_3[2]*1000 + Mobile_z + Lifter_z;
  
  double ikjoint_4[9];
  ikjoint_4[0] = seednoid_ikfast_joint[0];
  ikjoint_4[1] = seednoid_ikfast_joint[1];
  ikjoint_4[2] = seednoid_ikfast_joint[2];
  ikjoint_4[3] = seednoid_ikfast_joint[3];
  ikjoint_4[4] = seednoid_ikfast_joint[4];
  ikjoint_4[5] = seednoid_ikfast_joint[5];
  ikjoint_4[6] = seednoid_ikfast_joint[6];
  ikjoint_4[7] = seednoid_ikfast_joint[7];
  ikjoint_4[8] = seednoid_ikfast_joint[8];
  IKFAST_LINK4::ComputeFk(ikjoint_4,eetrans_4,eerot);
  manip[3].a.x = eetrans_3[0]*1000;
  manip[3].a.y = eetrans_3[1]*1000;
  manip[3].a.z = eetrans_3[2]*1000 + Mobile_z + Lifter_z;
  manip[3].b.x = eetrans_4[0]*1000;
  manip[3].b.y = eetrans_4[1]*1000;
  manip[3].b.z = eetrans_4[2]*1000 + Mobile_z + Lifter_z;
  
  double ikjoint_5[11];
  ikjoint_5[0] = seednoid_ikfast_joint[0];
  ikjoint_5[1] = seednoid_ikfast_joint[1];
  ikjoint_5[2] = seednoid_ikfast_joint[2];
  ikjoint_5[3] = seednoid_ikfast_joint[3];
  ikjoint_5[4] = seednoid_ikfast_joint[4];
  ikjoint_5[5] = seednoid_ikfast_joint[5];
  ikjoint_5[6] = seednoid_ikfast_joint[6];
  ikjoint_5[7] = seednoid_ikfast_joint[7];
  ikjoint_5[8] = seednoid_ikfast_joint[8];
  ikjoint_5[9] = seednoid_ikfast_joint[9];
  ikjoint_5[10] = seednoid_ikfast_joint[10];
  IKFAST_LINK5::ComputeFk(ikjoint_5,eetrans_5,eerot);
  manip[4].a.x = eetrans_4[0]*1000;
  manip[4].a.y = eetrans_4[1]*1000;
  manip[4].a.z = eetrans_4[2]*1000 + Mobile_z + Lifter_z;
  manip[4].b.x = eetrans_5[0]*1000;
  manip[4].b.y = eetrans_5[1]*1000;
  manip[4].b.z = eetrans_5[2]*1000 + Mobile_z + Lifter_z;
  
  double ikjoint_6[13];
  ikjoint_6[0] = seednoid_ikfast_joint[0];
  ikjoint_6[1] = seednoid_ikfast_joint[1];
  ikjoint_6[2] = seednoid_ikfast_joint[2];
  ikjoint_6[3] = seednoid_ikfast_joint[3];
  ikjoint_6[4] = seednoid_ikfast_joint[4];
  ikjoint_6[5] = seednoid_ikfast_joint[5];
  ikjoint_6[6] = seednoid_ikfast_joint[6];
  ikjoint_6[7] = seednoid_ikfast_joint[7];
  ikjoint_6[8] = seednoid_ikfast_joint[8];
  ikjoint_6[9] = seednoid_ikfast_joint[9];
  ikjoint_6[10] = seednoid_ikfast_joint[10];
  ikjoint_6[11] = seednoid_ikfast_joint[11];
  ikjoint_6[12] = 0;
  IKFAST_LINK6::ComputeFk(ikjoint_6,eetrans_6,eerot);
  manip[5].a.x = eetrans_5[0]*1000;
  manip[5].a.y = eetrans_5[1]*1000;
  manip[5].a.z = eetrans_5[2]*1000 + Mobile_z + Lifter_z;
  manip[5].b.x = eetrans_6[0]*1000;
  manip[5].b.y = eetrans_6[1]*1000;
  manip[5].b.z = eetrans_6[2]*1000 + Mobile_z + Lifter_z;
}

void Manipulator::CalcManipLinkPos_ten_Lifter(TenDOF J,SegLine manip[LinkNum],double Lifter_bottom,double Lifter_top)
{
  double eetrans_1[3];
  double eetrans_2[3];
  double eetrans_3[3];
  double eetrans_4[3];
  double eetrans_5[3];
  double eetrans_6[3];
  double eetrans_Lifter[3];
  double eerot[9];
  double elbowAbsolute;
  double elbow;
  double elbow_a;
  double elbow_b;
  //double Mobile_z = 196;
  //double Lifter_z = 720;

  double lifter[2];
  lifter[0] = Lifter_bottom;
  lifter[1] = Lifter_top;
  noid.Solve_Lifter_Fk(eetrans_Lifter,lifter);
  double Lifter_x = eetrans_Lifter[0];
  double Lifter_z = eetrans_Lifter[2];
 
  elbow = J.theta7;
  elbowAbsolute = 0.000000000000491110199391109*pow(elbow,6) - 0.00000000039070227836422*pow(elbow,5) + 0.000000130488756716618*pow(elbow,4) - 0.0000234826686984491*pow(elbow,3) + 0.00161963482241845*pow(elbow,2) + 0.261403325177525*elbow - 0.00665618754283059;
  elbow_a = -0.00000000692890119585732*pow(elbowAbsolute,6) + 0.00000124710103754921*pow(elbowAbsolute,5) - 0.000084428935736014*pow(elbowAbsolute,4) + 0.0031388252882607*pow(elbowAbsolute,3) - 0.0662216643686406*pow(elbowAbsolute,2) + 2.63918264403765*elbowAbsolute + 0.0360316324076848;
  elbow_b = 0.0000000459591281663785*pow(elbowAbsolute,6) - 0.00000466502825657855*pow(elbowAbsolute,5) + 0.000185818559202744*pow(elbowAbsolute,4) - 0.00313808415239691*pow(elbowAbsolute,3) + 0.0314923537516734*pow(elbowAbsolute,2) + 1.03307512408355*elbowAbsolute + 0.0815648272255203;
  
  double seednoid_ikfast_joint[12];
  seednoid_ikfast_joint[0] = J.theta1*M_PI/180;
  seednoid_ikfast_joint[1] = J.theta2*M_PI/180;
  seednoid_ikfast_joint[2] = J.theta3*M_PI/180;
  seednoid_ikfast_joint[3] = -J.theta4*M_PI/180;
  seednoid_ikfast_joint[4] = -0.1745;//仮想10°
  seednoid_ikfast_joint[5] = -J.theta5*M_PI/180+M_PI/2;
  seednoid_ikfast_joint[6] = -J.theta6*M_PI/180;
  seednoid_ikfast_joint[7] = elbow_a*M_PI/180;
  seednoid_ikfast_joint[8] = elbow_b*M_PI/180;
  seednoid_ikfast_joint[9] = -J.theta8*M_PI/180;
  seednoid_ikfast_joint[10] = -J.theta9*M_PI/180;
  seednoid_ikfast_joint[11] = -J.theta10*M_PI/180;
  
  double ikjoint_1[4];
  ikjoint_1[0] = seednoid_ikfast_joint[0];
  ikjoint_1[1] = seednoid_ikfast_joint[1];
  ikjoint_1[2] = seednoid_ikfast_joint[2];
  ikjoint_1[3] = seednoid_ikfast_joint[3];
  IKFAST_LINK1::ComputeFk(ikjoint_1,eetrans_1,eerot);
  manip[0].a.x = 0;
  manip[0].a.y = 0;
  manip[0].a.z = 0;
  manip[0].b.x = eetrans_1[0]*1000 + Lifter_x;//mmに変換
  manip[0].b.y = eetrans_1[1]*1000;
  manip[0].b.z = eetrans_1[2]*1000 + Lifter_z;
  
  double ikjoint_2[6];
  ikjoint_2[0] = seednoid_ikfast_joint[0];
  ikjoint_2[1] = seednoid_ikfast_joint[1];
  ikjoint_2[2] = seednoid_ikfast_joint[2];
  ikjoint_2[3] = seednoid_ikfast_joint[3];
  ikjoint_2[4] = seednoid_ikfast_joint[4];
  ikjoint_2[5] = seednoid_ikfast_joint[5];
  IKFAST_LINK2::ComputeFk(ikjoint_2,eetrans_2,eerot);
  manip[1].a.x = eetrans_1[0]*1000 + Lifter_x;
  manip[1].a.y = eetrans_1[1]*1000;
  manip[1].a.z = eetrans_1[2]*1000 + Lifter_z;
  manip[1].b.x = eetrans_2[0]*1000 + Lifter_x;
  manip[1].b.y = eetrans_2[1]*1000;
  manip[1].b.z = eetrans_2[2]*1000 + Lifter_z;
  
  double ikjoint_3[8];
  ikjoint_3[0] = seednoid_ikfast_joint[0];
  ikjoint_3[1] = seednoid_ikfast_joint[1];
  ikjoint_3[2] = seednoid_ikfast_joint[2];
  ikjoint_3[3] = seednoid_ikfast_joint[3];
  ikjoint_3[4] = seednoid_ikfast_joint[4];
  ikjoint_3[5] = seednoid_ikfast_joint[5];
  ikjoint_3[6] = seednoid_ikfast_joint[6];
  ikjoint_3[7] = seednoid_ikfast_joint[7];
  IKFAST_LINK3::ComputeFk(ikjoint_3,eetrans_3,eerot);
  manip[2].a.x = eetrans_2[0]*1000 + Lifter_x;
  manip[2].a.y = eetrans_2[1]*1000;
  manip[2].a.z = eetrans_2[2]*1000 + Lifter_z;
  manip[2].b.x = eetrans_3[0]*1000 + Lifter_x;
  manip[2].b.y = eetrans_3[1]*1000;
  manip[2].b.z = eetrans_3[2]*1000 + Lifter_z;
  
  double ikjoint_4[9];
  ikjoint_4[0] = seednoid_ikfast_joint[0];
  ikjoint_4[1] = seednoid_ikfast_joint[1];
  ikjoint_4[2] = seednoid_ikfast_joint[2];
  ikjoint_4[3] = seednoid_ikfast_joint[3];
  ikjoint_4[4] = seednoid_ikfast_joint[4];
  ikjoint_4[5] = seednoid_ikfast_joint[5];
  ikjoint_4[6] = seednoid_ikfast_joint[6];
  ikjoint_4[7] = seednoid_ikfast_joint[7];
  ikjoint_4[8] = seednoid_ikfast_joint[8];
  IKFAST_LINK4::ComputeFk(ikjoint_4,eetrans_4,eerot);
  manip[3].a.x = eetrans_3[0]*1000 + Lifter_x;
  manip[3].a.y = eetrans_3[1]*1000;
  manip[3].a.z = eetrans_3[2]*1000 + Lifter_z;
  manip[3].b.x = eetrans_4[0]*1000 + Lifter_x;
  manip[3].b.y = eetrans_4[1]*1000;
  manip[3].b.z = eetrans_4[2]*1000 + Lifter_z;
  
  double ikjoint_5[11];
  ikjoint_5[0] = seednoid_ikfast_joint[0];
  ikjoint_5[1] = seednoid_ikfast_joint[1];
  ikjoint_5[2] = seednoid_ikfast_joint[2];
  ikjoint_5[3] = seednoid_ikfast_joint[3];
  ikjoint_5[4] = seednoid_ikfast_joint[4];
  ikjoint_5[5] = seednoid_ikfast_joint[5];
  ikjoint_5[6] = seednoid_ikfast_joint[6];
  ikjoint_5[7] = seednoid_ikfast_joint[7];
  ikjoint_5[8] = seednoid_ikfast_joint[8];
  ikjoint_5[9] = seednoid_ikfast_joint[9];
  ikjoint_5[10] = seednoid_ikfast_joint[10];
  IKFAST_LINK5::ComputeFk(ikjoint_5,eetrans_5,eerot);
  manip[4].a.x = eetrans_4[0]*1000 + Lifter_x;
  manip[4].a.y = eetrans_4[1]*1000;
  manip[4].a.z = eetrans_4[2]*1000 + Lifter_z;
  manip[4].b.x = eetrans_5[0]*1000 + Lifter_x;
  manip[4].b.y = eetrans_5[1]*1000;
  manip[4].b.z = eetrans_5[2]*1000 + Lifter_z;
  
  double ikjoint_6[13];
  ikjoint_6[0] = seednoid_ikfast_joint[0];
  ikjoint_6[1] = seednoid_ikfast_joint[1];
  ikjoint_6[2] = seednoid_ikfast_joint[2];
  ikjoint_6[3] = seednoid_ikfast_joint[3];
  ikjoint_6[4] = seednoid_ikfast_joint[4];
  ikjoint_6[5] = seednoid_ikfast_joint[5];
  ikjoint_6[6] = seednoid_ikfast_joint[6];
  ikjoint_6[7] = seednoid_ikfast_joint[7];
  ikjoint_6[8] = seednoid_ikfast_joint[8];
  ikjoint_6[9] = seednoid_ikfast_joint[9];
  ikjoint_6[10] = seednoid_ikfast_joint[10];
  ikjoint_6[11] = seednoid_ikfast_joint[11];
  ikjoint_6[12] = 0;
  IKFAST_LINK6::ComputeFk(ikjoint_6,eetrans_6,eerot);
  manip[5].a.x = eetrans_5[0]*1000 + Lifter_x;
  manip[5].a.y = eetrans_5[1]*1000;
  manip[5].a.z = eetrans_5[2]*1000 + Lifter_z;
  manip[5].b.x = eetrans_6[0]*1000 + Lifter_x;
  manip[5].b.y = eetrans_6[1]*1000;
  manip[5].b.z = eetrans_6[2]*1000 + Lifter_z;

  //std::cout << "manip[5].b.x(sentan) = " << manip[5].b.x << std::endl;
  //std::cout << "manip[5].b.y(sentan) = " << manip[5].b.y << std::endl;
  //std::cout << "manip[5].b.z(sentan) = " << manip[5].b.z << std::endl;
  //std::cout << "Lifter_bottom = " << Lifter_bottom << std::endl;
  //std::cout << "Lifter_top = " << Lifter_top << std::endl;
  //std::cout << "Lifter_x = " << Lifter_x << std::endl;
  //std::cout << "Lifter_z = " << Lifter_z << std::endl;
}
