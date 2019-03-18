// -*-C++-*-
/*!
 * @file  MotionPlanningSVC_impl.cpp
 * @brief Service implementation code of MotionPlanning.idl
 *
 */

#include "MotionPlanningSVC_impl.h"

#define ARRAY_LEN(ARR) (sizeof(ARR) / sizeof((ARR)[0]))

inline void InitRand()
{
    srand((unsigned int)time(NULL));
}

inline int randPoint_theta1()//0~85
{
  return (rand() % 86);
}

inline int randPoint_theta2()//0~85
{
  return (rand() % 86);
}

inline int randPoint_theta3()//-90~90
{
  return (rand() % 241) - 120;
}

inline int randPoint_theta4()//-9~39
{
  return (rand() % 49) - 9;
}

inline int randPoint_theta5()//-7~7
{
  return (rand() % 15) - 7;
}

inline int randPoint_theta6()//-20~89
{
  return (rand() % 110) - 20;
}

inline int randPoint_theta7()//0~90
{
  return (rand() % 181) - 90;
}

inline int randPoint_theta8()//-135~135
{
  return (rand() % 271) - 135;
}

inline int randPoint_theta9()//0~180
{
    return rand() % 181;
}

inline int randPoint_theta10()//-135~135
{
  return (rand() % 271) - 135;
}

inline int randPoint_theta11()//-80~40
{
  return (rand() % 121) - 80;
}

inline int randPoint_theta12()//-180~180
{
  return (rand() % 361) - 180;
}


inline int randGoal()
{
  return rand() % 10;
}


/*
 * Example implementational code for IDL interface Planning::MotionPlanningInterface
 */
Planning_MotionPlanningInterfaceSVC_impl::Planning_MotionPlanningInterfaceSVC_impl()
{
  // Please add extra constructor code here.
}


Planning_MotionPlanningInterfaceSVC_impl::~Planning_MotionPlanningInterfaceSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
::CORBA::Long Planning_MotionPlanningInterfaceSVC_impl::MotionGenerate_Joint(const Planning::theta& q_goal)
{
  std::cout << "MotionGenerate_Joint" << std::endl;
  std::cout << "ERROR : コマンド未実装" << std::endl;
  return -1;
}

::CORBA::Long Planning_MotionPlanningInterfaceSVC_impl::MotionGenerate(const Planning::ManipPos& EEfPos)
{
  std::cout << "MotionGenerate" << std::endl;
  for(int i=0;i<9;i++)
    {
      std::cout << "targetEEfPos.rotation["<<i<<"] = " << EEfPos.rotation[i] << std::endl;
    }
  for(int i=0;i<3;i++)
    {
      std::cout << "targetEEfPos.position["<<i<<"] = " << EEfPos.position[i] << std::endl;
    }
  
  Manipulator manip;
  Collision cc;
  Redundancy redun;
  float fixedWaist_roll = 0;
  float fixedElbow = 0;
  int endStartFlag = 0;
  InitRand();
  //CreateAABBObstacle6();
  m_rtcPtr->getObstacle(aabb);
  Mat inMat,OutMat;
  ObstacleNum = aabb.size();
  std::cout << "ObstacleNum = " << ObstacleNum << std::endl;
  /*
  for(int i=0;i<ObstacleNum;i++)
    {
      inMat.Rotation[0] = 1;
      inMat.Rotation[1] = 0;
      inMat.Rotation[2] = 0;
      inMat.Rotation[3] = 0;
      inMat.Rotation[4] = 1;
      inMat.Rotation[5] = 0;
      inMat.Rotation[6] = 0;
      inMat.Rotation[7] = 0;
      inMat.Rotation[8] = 1;
      inMat.Position[0] = aabb[i].center.x;
      inMat.Position[1] = aabb[i].center.y;
      inMat.Position[2] = aabb[i].center.z;
      std::cout << "conv1" << std::endl;
      m_rtcPtr->ConversionMat(inMat,&OutMat);
      std::cout << "conv2" << std::endl;
      aabb[i].center.x = OutMat.Position[0];
      aabb[i].center.y = OutMat.Position[1];
      aabb[i].center.z = OutMat.Position[2]+914;//下半身補正
      std::cout << "aabb["<<i<<"].center.x = " << aabb[i].center.x << std::endl;
      std::cout << "aabb["<<i<<"].center.y = " << aabb[i].center.y << std::endl;
      std::cout << "aabb["<<i<<"].center.z = " << aabb[i].center.z << std::endl;
      std::cout << "aabb["<<i<<"].rx = " << aabb[i].rx << std::endl;
      std::cout << "aabb["<<i<<"].ry = " << aabb[i].ry << std::endl;
      std::cout << "aabb["<<i<<"].rz = " << aabb[i].rz << std::endl;
    }
  */
  double nowLifterPos[2];
  double nowWaistPos[3];
  double nowRightPos[7];
  double nowLeftPos[7];
  double oldLifterPos[2];
  double oldWaistPos[3];
  double oldRightPos[7];
  double oldLeftPos[7];
    for(int i=0;i<5;i++)
    {
      //m_rtcPtr->getSeedCurrentJoint(oldLifterPos,oldWaistPos,oldRightPos,oldLeftPos);
  m_rtcPtr->getSeedCurrentJoint(nowLifterPos,nowWaistPos,nowRightPos,nowLeftPos);
  std::cout << "nowRightPos[0] = " << nowRightPos[0] << std::endl;
  std::cout << "nowRightPos[1] = " << nowRightPos[1] << std::endl;
  std::cout << "nowRightPos[2] = " << nowRightPos[2] << std::endl;
  std::cout << "nowRightPos[3] = " << nowRightPos[3] << std::endl;
  std::cout << "nowRightPos[4] = " << nowRightPos[4] << std::endl;
  std::cout << "nowRightPos[5] = " << nowRightPos[5] << std::endl;
  std::cout << "nowRightPos[6] = " << nowRightPos[6] << std::endl;
    }
    /*
  for(int i=0;i<30;i++)
    {
      m_rtcPtr->getSeedCurrentJoint(oldLifterPos,oldWaistPos,oldRightPos,oldLeftPos);
      m_rtcPtr->getSeedCurrentJoint(nowLifterPos,nowWaistPos,nowRightPos,nowLeftPos);
      double diff[7];
      diff[0] = oldRightPos[0]-nowRightPos[0];
      diff[0] = oldRightPos[0]-nowRightPos[0];
      diff[0] = oldRightPos[0]-nowRightPos[0];
      diff[0] = oldRightPos[0]-nowRightPos[0];
      diff[0] = oldRightPos[0]-nowRightPos[0];
      diff[0] = oldRightPos[0]-nowRightPos[0];
      diff[0] = oldRightPos[0]-nowRightPos[0];
    }
    */
  double eerot[9];
  double eetrans[3];
  double nowRedunJoint[4];
  double redundancyJoint[4];
  double endEEtrans[3];
  for(int i=0;i<9;i++)
    {
      eerot[i] = EEfPos.rotation[i];
    }
  for(int i=0;i<3;i++)
    {
      eetrans[i] = EEfPos.position[i];
    }
  nowRedunJoint[0] = nowLifterPos[0];
  nowRedunJoint[1] = nowLifterPos[1];
  nowRedunJoint[2] = nowWaistPos[0];
  nowRedunJoint[3] = nowWaistPos[1];
  int ret;
  ret = redun.getRightRedundantJoint_CollisionCheck(eerot,eetrans,nowRedunJoint,redundancyJoint,endEEtrans,aabb,ObstacleNum);
  if(ret)
    {
      std::cout << "can not solve Ik" << std::endl;
      return -1;
    }
  
  double lifter[2];
  lifter[0] = redundancyJoint[0];
  lifter[1] = redundancyJoint[1];
  Frame WaistPos;
  WaistPos.yaw = redundancyJoint[2];
  WaistPos.pitch = redundancyJoint[3];
  WaistPos.roll = 0;
  double elbow = 0;
  double iksol[12];
  double nowJointPos[12];

  nowJointPos[0] = redundancyJoint[0];
  nowJointPos[1] = redundancyJoint[1];
  nowJointPos[2] = redundancyJoint[2];
  nowJointPos[3] = redundancyJoint[3];
  
  
  std::cout << "elbow = " << elbow << std::endl;
  std::cout << "lifter[0] = " << lifter[0] << std::endl;
  std::cout << "lifter[1] = " << lifter[1] << std::endl;
  std::cout << "WaistPos.yaw = " << WaistPos.yaw << std::endl;
  std::cout << "WaistPos.pitch = " << WaistPos.pitch << std::endl;
  std::cout << "WaistPos.roll = " << WaistPos.roll << std::endl;

  ret = noid.Solve_LIWARArmIkSetRedun(eerot,eetrans,elbow,WaistPos,lifter,nowJointPos,iksol);

  TenDOF start;
  start.theta1 = nowLifterPos[0];
  start.theta2 = nowLifterPos[1];
  start.theta3 = nowWaistPos[0];
  start.theta4 = nowWaistPos[1];
  start.theta5 = nowRightPos[0];
  start.theta6 = nowRightPos[1];
  start.theta7 = nowRightPos[3];
  start.theta8 = nowRightPos[4];
  start.theta9 = nowRightPos[5];
  start.theta10 = nowRightPos[6];

  std::cout << "start.theta1 = " << start.theta1 << std::endl;
  std::cout << "start.theta2 = " << start.theta2 << std::endl;
  std::cout << "start.theta3 = " << start.theta3 << std::endl;
  std::cout << "start.theta4 = " << start.theta4 << std::endl;
  std::cout << "start.theta5 = " << start.theta5 << std::endl;
  std::cout << "start.theta6 = " << start.theta6 << std::endl;
  std::cout << "start.theta7 = " << start.theta7 << std::endl;
  std::cout << "start.theta8 = " << start.theta8 << std::endl;
  std::cout << "start.theta9 = " << start.theta9 << std::endl;
  std::cout << "start.theta10 = " << start.theta10 << std::endl;

  TenDOF end;
  end.theta1 = iksol[0];
  end.theta2 = iksol[1];  
  end.theta3 = iksol[2];
  end.theta4 = iksol[3];
  end.theta5 = iksol[5];
  end.theta6 = iksol[6];
  end.theta7 = iksol[8];
  end.theta8 = iksol[9];
  end.theta9 = iksol[10];
  end.theta10 = iksol[11];

  std::cout << "end.theta1 = " << end.theta1 << std::endl;
  std::cout << "end.theta2 = " << end.theta2 << std::endl;
  std::cout << "end.theta3 = " << end.theta3 << std::endl;
  std::cout << "end.theta4 = " << end.theta4 << std::endl;
  std::cout << "end.theta5 = " << end.theta5 << std::endl;
  std::cout << "end.theta6 = " << end.theta6 << std::endl;
  std::cout << "end.theta7 = " << end.theta7 << std::endl;
  std::cout << "end.theta8 = " << end.theta8 << std::endl;
  std::cout << "end.theta9 = " << end.theta9 << std::endl;
  std::cout << "end.theta10 = " << end.theta10 << std::endl;

  int randCount = 0;
  TenDOF rand;
  std::vector<TenDOF> nodeList;
  std::vector<int> parentNode;

  float expandDis = 10;
  int randGoalFlag = 0;
  //gettimeofday(&start_time, NULL);

  //=====どっちが狭いか判定=====================================
  //int narrow_start = 0;
  int startCollisionCount = 0;
  int endCollisionCount = 0;
  float bunnkai = 10;
  float j1_min = start.theta1 - bunnkai;
  float j1_max = start.theta1 + bunnkai;
  float j2_min = start.theta2 - bunnkai;
  float j2_max = start.theta2 + bunnkai;
  float j3_min = start.theta3 - bunnkai;
  float j3_max = start.theta3 + bunnkai;
  int Scolret = 0;
  TenDOF SnoidPos;

  double lifter_bottom;
  double lifter_top;
  lifter_bottom = start.theta1;
  lifter_top = start.theta2;
  SnoidPos.theta1 = start.theta3;
  SnoidPos.theta2 = start.theta4;
  SnoidPos.theta3 = fixedWaist_roll;
  SnoidPos.theta4 = start.theta5;
  SnoidPos.theta5 = start.theta6;
  SnoidPos.theta6 = fixedElbow;
  SnoidPos.theta7 = start.theta7;
  SnoidPos.theta8 = start.theta8;
  SnoidPos.theta9 = start.theta9;
  SnoidPos.theta10 = start.theta10;

  for(float j1=j1_min;j1<=j1_max;j1++)
    {
      for(float j2=j2_min;j2<=j2_max;j2++)
	{
	  for(float j3=j3_min;j3<=j3_max;j3++)
	    {
	      lifter_bottom = j1;
	      lifter_top = j2;
	      SnoidPos.theta1 = j3;
	      SnoidPos.theta2 = start.theta4;
	      SnoidPos.theta3 = fixedWaist_roll;
	      SnoidPos.theta4 = start.theta5;
	      SnoidPos.theta5 = start.theta6;
	      SnoidPos.theta6 = fixedElbow;
	      SnoidPos.theta7 = start.theta7;
	      SnoidPos.theta8 = start.theta8;
	      SnoidPos.theta9 = start.theta9;
	      SnoidPos.theta10 = start.theta10;
	      /*
	      std::cout << "noidPos.theta1 = " << SnoidPos.theta1 << std::endl;
	      std::cout << "noidPos.theta2 = " << SnoidPos.theta2 << std::endl;
	      std::cout << "noidPos.theta3 = " << SnoidPos.theta3 << std::endl;
	      std::cout << "noidPos.theta4 = " << SnoidPos.theta4 << std::endl;
	      std::cout << "noidPos.theta5 = " << SnoidPos.theta5 << std::endl;
	      std::cout << "noidPos.theta6 = " << SnoidPos.theta6 << std::endl;
	      std::cout << "noidPos.theta7 = " << SnoidPos.theta7 << std::endl;
	      std::cout << "noidPos.theta8 = " << SnoidPos.theta8 << std::endl;
	      std::cout << "noidPos.theta9 = " << SnoidPos.theta9 << std::endl;
	      std::cout << "noidPos.theta10 = " << SnoidPos.theta10 << std::endl;
		*/
	      Scolret = CollisionCheck(SnoidPos,lifter_bottom,lifter_top,aabb,ObstacleNum);
	      if(Scolret)
		{
		  startCollisionCount++;
		}
	    }
	}
    }

  j1_min = end.theta1 - bunnkai;
  j1_max = end.theta1 + bunnkai;
  j2_min = end.theta2 - bunnkai;
  j2_max = end.theta2 + bunnkai;
  j3_min = end.theta3 - bunnkai;
  j3_max = end.theta3 + bunnkai;
  Scolret = 0;
  lifter_bottom = end.theta1;
  lifter_top = end.theta2;
  SnoidPos.theta1 = end.theta3;
  SnoidPos.theta2 = end.theta4;
  SnoidPos.theta3 = fixedWaist_roll;
  SnoidPos.theta4 = end.theta5;
  SnoidPos.theta5 = end.theta6;
  SnoidPos.theta6 = fixedElbow;
  SnoidPos.theta7 = end.theta7;
  SnoidPos.theta8 = end.theta8;
  SnoidPos.theta9 = end.theta9;
  SnoidPos.theta10 = end.theta10;
  for(float j1=j1_min;j1<=j1_max;j1++)
    {
      for(float j2=j2_min;j2<=j2_max;j2++)
	{
	  for(float j3=j3_min;j3<=j3_max;j3++)
	    {
	      lifter_bottom = j1;
	      lifter_top = j2;
	      SnoidPos.theta1 = j3;
	      SnoidPos.theta2 = end.theta4;
	      SnoidPos.theta3 = fixedWaist_roll;
	      SnoidPos.theta4 = end.theta5;
	      SnoidPos.theta5 = end.theta6;
	      SnoidPos.theta6 = fixedElbow;
	      SnoidPos.theta7 = end.theta7;
	      SnoidPos.theta8 = end.theta8;
	      SnoidPos.theta9 = end.theta9;
	      SnoidPos.theta10 = end.theta10;
	      Scolret = CollisionCheck(SnoidPos,lifter_bottom,lifter_top,aabb,ObstacleNum);
	      if(Scolret)
		{
		  endCollisionCount++;
		}
	    }
	}
    }
  std::cout << "startCollisionCount = " << startCollisionCount << std::endl;
  std::cout << "endCollisionCount = " << endCollisionCount << std::endl;
  TenDOF changePos;
  if(endCollisionCount > startCollisionCount)
    {
      changePos.theta1 = start.theta1;
      changePos.theta2 = start.theta2;
      changePos.theta3 = start.theta3;
      changePos.theta4 = start.theta4;
      changePos.theta5 = start.theta5;
      changePos.theta6 = start.theta6;
      changePos.theta7 = start.theta7;
      changePos.theta8 = start.theta8;
      changePos.theta9 = start.theta9;
      changePos.theta10 = start.theta10;
      start.theta1 = end.theta1;
      start.theta2 = end.theta2;
      start.theta3 = end.theta3;
      start.theta4 = end.theta4;
      start.theta5 = end.theta5;
      start.theta6 = end.theta6;
      start.theta7 = end.theta7;
      start.theta8 = end.theta8;
      start.theta9 = end.theta9;
      start.theta10 = end.theta10;
      end.theta1 = changePos.theta1;
      end.theta2 = changePos.theta2;
      end.theta3 = changePos.theta3;
      end.theta4 = changePos.theta4;
      end.theta5 = changePos.theta5;
      end.theta6 = changePos.theta6;
      end.theta7 = changePos.theta7;
      end.theta8 = changePos.theta8;
      end.theta9 = changePos.theta9;
      end.theta10 = changePos.theta10;
      endStartFlag = 1;
    }


  nodeList.push_back(start);
  flann::Matrix<float> dataset(new float[DOF*1], 1, DOF);
  dataset[0][0] = start.theta1;
  dataset[0][1] = start.theta2;
  dataset[0][2] = start.theta3;
  dataset[0][3] = start.theta4;
  dataset[0][4] = start.theta5;
  dataset[0][5] = start.theta6;
  dataset[0][6] = start.theta7;
  dataset[0][7] = start.theta8;
  dataset[0][8] = start.theta9;
  dataset[0][9] = start.theta10;
  
  // cout<<query.rows<<endl;
  flann::Index<flann::L2<float> > index(dataset, flann::KDTreeIndexParams(4));
  index.buildIndex();

  flann::Matrix<float> query(new float[DOF*1],1, DOF);
  //radius
  //flann::Matrix<int> indices(new int[query.rows],query.rows,1);
  //flann::Matrix<float> dists(new float[query.rows],query.rows, 1);
  //knn
  flann::Matrix<int> indices(new int[query.rows*DOF],query.rows,DOF);
  flann::Matrix<float> dists(new float[query.rows*DOF],query.rows, DOF);

  //std::cout << "sleep" << std::endl;
  //sleep(5000);
  while(1)
    {
      randCount++;
      if(randGoal() == 0)
	{
	  rand.theta1 = end.theta1;
	  rand.theta2 = end.theta2;
	  rand.theta3 = end.theta3;
	  rand.theta4 = end.theta4;
	  rand.theta5 = end.theta5;
	  rand.theta6 = end.theta6;
	  rand.theta7 = end.theta7;
	  rand.theta8 = end.theta8;
	  rand.theta9 = end.theta9;
	  rand.theta10 = end.theta10;
	  randGoalFlag = 1;
	  //std::cout << "randGoal" << std::endl;
	}
      else
	{
	  rand.theta1 = randPoint_theta1();
	  rand.theta2 = randPoint_theta2();
	  rand.theta3 = randPoint_theta3();
	  rand.theta4 = randPoint_theta4();
	  rand.theta5 = randPoint_theta6();
	  rand.theta6 = randPoint_theta7();
	  rand.theta7 = randPoint_theta9();
	  rand.theta8 = randPoint_theta10();
	  rand.theta9 = randPoint_theta11();
	  rand.theta10 = randPoint_theta12();
	  //std::cout << "not randGoal" << std::endl;
	}

      //gettimeofday(&start_kd_time, NULL);
      //最近傍点探索====================================================
      //既存ノードとランダムノードの距離計算 全探索
      //Find nearest node
      std::vector<float> distancelist;
      float minNode;
      //float min;
      //std::cout << "nodeList.size = " << nodeList.size() << std::endl;
      for(int h=0;h<nodeList.size();h++)
	{
	  distancelist.push_back(sqrt((nodeList[h].theta1 - rand.theta1)*(nodeList[h].theta1 - rand.theta1) + (nodeList[h].theta2 - rand.theta2)*(nodeList[h].theta2 - rand.theta2) + (nodeList[h].theta3 - rand.theta3)*(nodeList[h].theta3 - rand.theta3) + (nodeList[h].theta4 - rand.theta4)*(nodeList[h].theta4 - rand.theta4) + (nodeList[h].theta5 - rand.theta5)*(nodeList[h].theta5 - rand.theta5) + (nodeList[h].theta6 - rand.theta6)*(nodeList[h].theta6 - rand.theta6) + (nodeList[h].theta7 - rand.theta7)*(nodeList[h].theta7 - rand.theta7) + (nodeList[h].theta8 - rand.theta8)*(nodeList[h].theta8 - rand.theta8) + (nodeList[h].theta9 - rand.theta9)*(nodeList[h].theta9 - rand.theta9) + (nodeList[h].theta10 - rand.theta10)*(nodeList[h].theta10 - rand.theta10)));
	  //distancelist.push_back(sqrt((nodeList[h].theta1 - rand.theta1)*(nodeList[h].theta1 - rand.theta1) + (nodeList[h].theta2 - rand.theta2)*(nodeList[h].theta2 - rand.theta2)));
	  //std::cout << "distancelist["<<h<<"] = " << distancelist[h] << std::endl;
	}
      std::vector<float>::iterator iter = std::min_element(distancelist.begin(), distancelist.end());
      int nearestNodeNum = std::distance(distancelist.begin(), iter);
      //FLANN==============================================================
      /*
      query[0][0]=rand.theta1;
      query[0][1]=rand.theta2;
      query[0][2]=rand.theta3;
      query[0][3]=rand.theta4;
      query[0][4]=rand.theta5;
      query[0][5]=rand.theta6;
      query[0][6]=rand.theta7;
      query[0][7]=rand.theta8;
      query[0][8]=rand.theta7;
      query[0][9]=rand.theta8;           
      //index.radiusSearch(query, indices, dists, 500000.0,flann::SearchParams(128));
      index.knnSearch(query, indices, dists, 8, flann::SearchParams(128));//8 = Dim

      int nearestNodeNum = indices[0][0];//最近傍点のNumber
      */
      TenDOF newNode;
      TenDOF nearestNode;
      nearestNode.theta1 = nodeList[nearestNodeNum].theta1;
      nearestNode.theta2 = nodeList[nearestNodeNum].theta2;
      nearestNode.theta3 = nodeList[nearestNodeNum].theta3;
      nearestNode.theta4 = nodeList[nearestNodeNum].theta4;
      nearestNode.theta5 = nodeList[nearestNodeNum].theta5;
      nearestNode.theta6 = nodeList[nearestNodeNum].theta6;
      nearestNode.theta7 = nodeList[nearestNodeNum].theta7;
      nearestNode.theta8 = nodeList[nearestNodeNum].theta8;
      nearestNode.theta9 = nodeList[nearestNodeNum].theta9;
      nearestNode.theta10 = nodeList[nearestNodeNum].theta10;
      float distance = (sqrt((nearestNode.theta1 - rand.theta1)*(nearestNode.theta1 - rand.theta1) + (nearestNode.theta2 - rand.theta2)*(nearestNode.theta2 - rand.theta2) + (nearestNode.theta3 - rand.theta3)*(nearestNode.theta3 - rand.theta3) + (nearestNode.theta4 - rand.theta4)*(nearestNode.theta4 - rand.theta4) + (nearestNode.theta5 - rand.theta5)*(nearestNode.theta5 - rand.theta5) + (nearestNode.theta6 - rand.theta6)*(nearestNode.theta6 - rand.theta6) + (nearestNode.theta7 - rand.theta7)*(nearestNode.theta7 - rand.theta7) + (nearestNode.theta8 - rand.theta8)*(nearestNode.theta8 - rand.theta8) + (nearestNode.theta9 - rand.theta9)*(nearestNode.theta9 - rand.theta9) + (nearestNode.theta10 - rand.theta10)*(nearestNode.theta10 - rand.theta10)));
      //std::cout << "distance = " << distance << std::endl;
      if(distance < expandDis)
	{
	  newNode.theta1 = rand.theta1;
	  newNode.theta2 = rand.theta2;
	  newNode.theta3 = rand.theta3;
	  newNode.theta4 = rand.theta4;
	  newNode.theta5 = rand.theta5;
	  newNode.theta6 = rand.theta6;
	  newNode.theta7 = rand.theta7;
	  newNode.theta8 = rand.theta8;
	  newNode.theta9 = rand.theta9;
	  newNode.theta10 = rand.theta10;
	}
      else
	{
	  newNode.theta1 = nearestNode.theta1 + ((rand.theta1 - nearestNode.theta1)*(expandDis/distance));
	  newNode.theta2 = nearestNode.theta2 + ((rand.theta2 - nearestNode.theta2)*(expandDis/distance));
	  newNode.theta3 = nearestNode.theta3 + ((rand.theta3 - nearestNode.theta3)*(expandDis/distance));
	  newNode.theta4 = nearestNode.theta4 + ((rand.theta4 - nearestNode.theta4)*(expandDis/distance));
	  newNode.theta5 = nearestNode.theta5 + ((rand.theta5 - nearestNode.theta5)*(expandDis/distance));
	  newNode.theta6 = nearestNode.theta6 + ((rand.theta6 - nearestNode.theta6)*(expandDis/distance));
	  newNode.theta7 = nearestNode.theta7 + ((rand.theta7 - nearestNode.theta7)*(expandDis/distance));
	  newNode.theta8 = nearestNode.theta8 + ((rand.theta8 - nearestNode.theta8)*(expandDis/distance));
	  newNode.theta9 = nearestNode.theta9 + ((rand.theta9 - nearestNode.theta9)*(expandDis/distance));
	  newNode.theta10 = nearestNode.theta10 + ((rand.theta10 - nearestNode.theta10)*(expandDis/distance));
	}

      //gettimeofday(&start_col_time, NULL);
      SegLine segManip[LinkNum];
      //SegLine segManip[4];
      int colret = 0;
      TenDOF noidPos;
      double lifter_bottom;
      double lifter_top;
      lifter_bottom = newNode.theta1;
      lifter_top = newNode.theta2;
      noidPos.theta1 = newNode.theta3;
      noidPos.theta2 = newNode.theta4;
      noidPos.theta3 = fixedWaist_roll;
      noidPos.theta4 = newNode.theta5;
      noidPos.theta5 = newNode.theta6;
      noidPos.theta6 = fixedElbow;
      noidPos.theta7 = newNode.theta7;
      noidPos.theta8 = newNode.theta8;
      noidPos.theta9 = newNode.theta9;
      noidPos.theta10 = newNode.theta10;
      /*
      std::cout << "noidPos.theta1 = " << noidPos.theta1 << std::endl;
      std::cout << "noidPos.theta2 = " << noidPos.theta2 << std::endl;
      std::cout << "noidPos.theta3 = " << noidPos.theta3 << std::endl;
      std::cout << "noidPos.theta4 = " << noidPos.theta4 << std::endl;
      std::cout << "noidPos.theta5 = " << noidPos.theta5 << std::endl;
      std::cout << "noidPos.theta6 = " << noidPos.theta6 << std::endl;
      std::cout << "noidPos.theta7 = " << noidPos.theta7 << std::endl;
      std::cout << "noidPos.theta8 = " << noidPos.theta8 << std::endl;
      std::cout << "noidPos.theta9 = " << noidPos.theta9 << std::endl;
      std::cout << "noidPos.theta10 = " << noidPos.theta10 << std::endl;
      */
      colret = CollisionCheck(noidPos,lifter_bottom,lifter_top,aabb,ObstacleNum);
      /*
      //CollisionCheck
      manip.CalcManipLinkPos_ten_Lifter(noidPos,segManip,lifter_bottom,lifter_top);
      //manip.CalcManipLinkPos(newNode,segManip);
      SegLine inSegLine;
      AABB inAABB;

      for(int i=0;i<ARRAY_LEN(segManip);i++)
	{
	  //std::cout << "seg" << i << std::endl;
	  for(int j=0;j<ObstacleNum;j++)
	    {
	      //std::cout << "ob" << j << std::endl;
	      inSegLine.a.x = segManip[i].a.x;
	      inSegLine.a.y = segManip[i].a.y;
	      inSegLine.a.z = segManip[i].a.z;
	      inSegLine.b.x = segManip[i].b.x;
	      inSegLine.b.y = segManip[i].b.y;
	      inSegLine.b.z = segManip[i].b.z;
	      //std::cout << inSegLine.a.x << " " << inSegLine.a.y << " " << inSegLine.a.z  << " " << inSegLine.b.x << " " << inSegLine.b.y <<  " " << inSegLine.b.z << std::endl; 
	      inAABB.center.x = aabb[j].center.x;
	      inAABB.center.y = aabb[j].center.y;
	      inAABB.center.z = aabb[j].center.z;
	      inAABB.rx = aabb[j].rx;
	      inAABB.ry = aabb[j].ry;
	      inAABB.rz = aabb[j].rz;
	      //std::cout << "inAABB.center.x = " << inAABB.center.x << std::endl;
	      //std::cout << "inAABB.center.y = " << inAABB.center.y << std::endl;
	      //std::cout << "inAABB.center.z = " << inAABB.center.z << std::endl;
	      //std::cout << "inAABB.rx = " << inAABB.rx << std::endl;
	      //std::cout << "inAABB.ry = " << inAABB.ry << std::endl;
	      //std::cout << "inAABB.rz = " << inAABB.rz << std::endl;
	      colret = cc.ColDecSegLineAABB(inSegLine,inAABB);
	      if(colret)//collision
		break;
	    }
	  if(colret)//collision
	    {
	      //std::cout << "seg" << i << std::endl;
	      break;
	    }
	}
      //gettimeofday(&now_col_time, NULL);
      //sec = (double)(now_col_time.tv_sec - start_col_time.tv_sec);
      //micro = (double)(now_col_time.tv_usec - start_col_time.tv_usec);
      //sum_col_time += sec + micro / 1000.0 / 1000.0;
      */
      //std::cout << "colret = " << colret << std::endl;
      if(colret)
	{
	  //std::cout << "collision node1 = " << newNode.theta1 << std::endl;
	  //std::cout << "collision node2 = " << newNode.theta2 << std::endl;
	  //std::cout << "collision node3 = " << newNode.theta3 << std::endl;
	  //std::cout << "collision node4 = " << newNode.theta4 << std::endl;
	  //fprintf(fp1,"%f,%f,%f,%f,%f,%f\n",newNode.theta1,newNode.theta2,newNode.theta3,newNode.theta4,newNode.theta5,newNode.theta6);
	  //std::cout << "collision" << std::endl;
	}
      if(!colret)
	{
	  flann::Matrix<float> add(new float[DOF*1],1, DOF);
	  //干渉しない
	  add[0][0]=newNode.theta1;
	  add[0][1]=newNode.theta2;
	  add[0][2]=newNode.theta3;
	  add[0][3]=newNode.theta4;
	  add[0][4]=newNode.theta5;
	  add[0][5]=newNode.theta6;
	  add[0][6]=newNode.theta7;
	  add[0][7]=newNode.theta8;
	  add[0][8]=newNode.theta9;
	  add[0][9]=newNode.theta10;
	  index.addPoints(add);
	  nodeList.push_back(newNode);
	  parentNode.push_back(nearestNodeNum);
	  //push.theta1 = manip.theta1;
	  //push.theta2 = manip.theta2;
	  //push.theta3 = manip.theta3;
	  //free.push_back(push);

	  //check goal
	  TenDOF Dis;
	  float d;
	  Dis.theta1 = newNode.theta1 - end.theta1;
	  Dis.theta2 = newNode.theta2 - end.theta2;
	  Dis.theta3 = newNode.theta3 - end.theta3;
	  Dis.theta4 = newNode.theta4 - end.theta4;
	  Dis.theta5 = newNode.theta5 - end.theta5;
	  Dis.theta6 = newNode.theta6 - end.theta6;
	  Dis.theta7 = newNode.theta7 - end.theta7;
	  Dis.theta8 = newNode.theta8 - end.theta8;
	  Dis.theta9 = newNode.theta9 - end.theta9;
	  Dis.theta10 = newNode.theta10 - end.theta10;

	  d = sqrt(Dis.theta1*Dis.theta1 + Dis.theta2*Dis.theta2 + Dis.theta3*Dis.theta3 + Dis.theta4*Dis.theta4 + Dis.theta5*Dis.theta5 + Dis.theta6*Dis.theta6 + Dis.theta7*Dis.theta7 + Dis.theta8*Dis.theta8 + Dis.theta9*Dis.theta9 + Dis.theta10*Dis.theta10);
	  /*
	  if(randGoalFlag == 1)
	    {
	      std::cout << "newNode.theta1 = " << newNode.theta1 << std::endl;
	      std::cout << "newNode.theta2 = " << newNode.theta2 << std::endl;
	      std::cout << "newNode.theta3 = " << newNode.theta3 << std::endl;
	      std::cout << "newNode.theta4 = " << newNode.theta4 << std::endl;
	      std::cout << "newNode.theta5 = " << newNode.theta5 << std::endl;
	      std::cout << "newNode.theta6 = " << newNode.theta6 << std::endl;
	      std::cout << "newNode.theta7 = " << newNode.theta7 << std::endl;
	      std::cout << "newNode.theta8 = " << newNode.theta8 << std::endl;
	      std::cout << "newNode.theta9 = " << newNode.theta9 << std::endl;
	      std::cout << "newNode.theta10 = " << newNode.theta10 << std::endl;
	      std::cout << "end.theta1 = " << end.theta1 << std::endl;
	      std::cout << "end.theta2 = " << end.theta2 << std::endl;
	      std::cout << "end.theta3 = " << end.theta3 << std::endl;
	      std::cout << "end.theta4 = " << end.theta4 << std::endl;
	      std::cout << "end.theta5 = " << end.theta5 << std::endl;
	      std::cout << "end.theta6 = " << end.theta6 << std::endl;
	      std::cout << "end.theta7 = " << end.theta7 << std::endl;
	      std::cout << "end.theta8 = " << end.theta8 << std::endl;
	      std::cout << "end.theta9 = " << end.theta9 << std::endl;
	      std::cout << "end.theta10 = " << end.theta10 << std::endl;
	      
	      std::cout << "d = " << d << std::endl;
	      randGoalFlag = 0;
	    }
	  */
	  /*
	    if(randGoalFlag == 1)
	    {
	    std::cout << "d = "<< d  <<"   randGoal" << std::endl;
	    randGoalFlag = 0;
	    }
	    else
	    {
	      std::cout << "d = " << d << std::endl;
	    }
	  */

	  if(d <= expandDis)
	    {
	      parentNode.push_back(nodeList.size() - 1);
	      std::cout << "Goal!" << std::endl;
	      //gettimeofday(&end_time, NULL);
	      std::cout << "randNum = " << randCount << std::endl;
	      break;
	    }
	}
    }//while


  //最終パスの生成
  int parentNum;
  TenDOF parent;
  std::vector<TenDOF> endPath;
  //std::cout << "nodeList.size() = " << nodeList.size() << std::endl;
  //std::cout << "parentNode.size() = " << parentNode.size() << std::endl;
  //std::cout << "parentNode[parentNode.size()-1] = " << parentNode[parentNode.size()-1] << std::endl;
  parentNum = parentNode.size() - 1;
  //parentNum = parentNode.size();
  parent.theta1 = nodeList[parentNum].theta1;
  parent.theta2 = nodeList[parentNum].theta2;
  parent.theta3 = nodeList[parentNum].theta3;
  parent.theta4 = nodeList[parentNum].theta4;
  parent.theta5 = nodeList[parentNum].theta5;
  parent.theta6 = nodeList[parentNum].theta6;
  parent.theta7 = nodeList[parentNum].theta7;
  parent.theta8 = nodeList[parentNum].theta8;
  parent.theta9 = nodeList[parentNum].theta9;
  parent.theta10 = nodeList[parentNum].theta10;
    
  endPath.push_back(end);
  endPath.push_back(parent);
  //fprintf(path_fp1,"%f,%f,%f\n",end.theta1,end.theta2,end.theta3);
  //std::cout << "parentNum = " << parentNum << std::endl;
  //fprintf(path_fp1,"%f,%f,%f\n",parent.theta1,parent.theta2,parent.theta3);
  int parentcount = 0;
  //std::cout << "nodeList[parentNum] = " << nodeList[parentNum].theta1 << std::endl; 

  while(1)
    {
      //std::cout << "debug4" << std::endl;
      parentNum = parentNode[parentNum-1];
      //std::cout << "parentNum = " << parentNum << std::endl;
      parent.theta1 = nodeList[parentNum].theta1;
      parent.theta2 = nodeList[parentNum].theta2;
      parent.theta3 = nodeList[parentNum].theta3;
      parent.theta4 = nodeList[parentNum].theta4;
      parent.theta5 = nodeList[parentNum].theta5;
      parent.theta6 = nodeList[parentNum].theta6;
      parent.theta7 = nodeList[parentNum].theta7;
      parent.theta8 = nodeList[parentNum].theta8;
      parent.theta9 = nodeList[parentNum].theta9;
      parent.theta10 = nodeList[parentNum].theta10;
      endPath.push_back(parent);
      //fprintf(path_fp1,"%f,%f,%f\n",parent.theta1,parent.theta2,parent.theta3);
      if(parentNum == 0)
	{
	  //fprintf(path_fp1,"%f,%f,%f\n",start.theta1,start.theta2,start.theta3);
	  break;
	}
      parentcount++;
      if(parentcount > 100000)
	{
	  break;
	}
    }

  int endPathNum;
  std::vector<TenDOF> trajectory;
  TenDOF pushTraj;

  if(endStartFlag)
    {
      endPathNum = 0;
      while(1)
	{
	  pushTraj.theta1 = endPath[endPathNum].theta1;
	  pushTraj.theta2 = endPath[endPathNum].theta2;
	  pushTraj.theta3 = endPath[endPathNum].theta3;
	  pushTraj.theta4 = endPath[endPathNum].theta4;
	  pushTraj.theta5 = endPath[endPathNum].theta5;
	  pushTraj.theta6 = endPath[endPathNum].theta6;
	  pushTraj.theta7 = endPath[endPathNum].theta7;
	  pushTraj.theta8 = endPath[endPathNum].theta8;
	  pushTraj.theta9 = endPath[endPathNum].theta9;
	  pushTraj.theta10 = endPath[endPathNum].theta10;
	  trajectory.push_back(pushTraj);
	  endPathNum++;
	  if(endPathNum>endPath.size()-1)
	    {
	      break;
	    }
	}
    }
  else
    {
      endPathNum = endPath.size() - 1;
      while(1)
	{
	  pushTraj.theta1 = endPath[endPathNum].theta1;
	  pushTraj.theta2 = endPath[endPathNum].theta2;
	  pushTraj.theta3 = endPath[endPathNum].theta3;
	  pushTraj.theta4 = endPath[endPathNum].theta4;
	  pushTraj.theta5 = endPath[endPathNum].theta5;
	  pushTraj.theta6 = endPath[endPathNum].theta6;
	  pushTraj.theta7 = endPath[endPathNum].theta7;
	  pushTraj.theta8 = endPath[endPathNum].theta8;
	  pushTraj.theta9 = endPath[endPathNum].theta9;
	  pushTraj.theta10 = endPath[endPathNum].theta10;
	  trajectory.push_back(pushTraj);
	  endPathNum--;
	  if(endPathNum<0)
	    {
	      break;
	    }
	}
    }

  m_rtcPtr->PathGenerate(trajectory);

  std::cout << "Success" << std::endl;

  return 0;
}

int Planning_MotionPlanningInterfaceSVC_impl::CollisionCheck(TenDOF joint, double lifterBottom, double lifterTop, std::vector<AABB> CCaabb,int ObNum)
{
  Manipulator manip;
  Collision cc;
  SegLine segManip[LinkNum];
  //SegLine segManip[4];
  int colret = 0;
  //CollisionCheck
  manip.CalcManipLinkPos_ten_Lifter(joint,segManip,lifterBottom,lifterTop);
  //manip.CalcManipLinkPos_ten(joint,segManip);
  //manip.CalcManipLinkPos(newNode,segManip);
  SegLine inSegLine;
  AABB inAABB;

  for(int i=0;i<ARRAY_LEN(segManip);i++)
    {
      //std::cout << "seg" << i << std::endl;
      for(int j=0;j<ObNum;j++)
	{
	  //std::cout << "ob" << j << std::endl;
	  inSegLine.a.x = segManip[i].a.x;
	  inSegLine.a.y = segManip[i].a.y;
	  inSegLine.a.z = segManip[i].a.z;
	  inSegLine.b.x = segManip[i].b.x;
	  inSegLine.b.y = segManip[i].b.y;
	  inSegLine.b.z = segManip[i].b.z;
	  //std::cout << inSegLine.a.x << " " << inSegLine.a.y << " " << inSegLine.a.z  << " " << inSegLine.b.x << " " << inSegLine.b.y <<  " " << inSegLine.b.z << std::endl; 
	  inAABB.center.x = CCaabb[j].center.x;
	  inAABB.center.y = CCaabb[j].center.y;
	  inAABB.center.z = CCaabb[j].center.z;
	  inAABB.rx = CCaabb[j].rx;
	  inAABB.ry = CCaabb[j].ry;
	  inAABB.rz = CCaabb[j].rz;
	  //std::cout << "inAABB.center.x = " << inAABB.center.x << std::endl;
	  //std::cout << "inAABB.center.y = " << inAABB.center.y << std::endl;
	  //std::cout << "inAABB.center.z = " << inAABB.center.z << std::endl;
	  //std::cout << "inAABB.rx = " << inAABB.rx << std::endl;
	  //std::cout << "inAABB.ry = " << inAABB.ry << std::endl;
	  //std::cout << "inAABB.rz = " << inAABB.rz << std::endl;
	  colret = cc.ColDecSegLineAABB(inSegLine,inAABB);
	  if(colret)//collision
	    return 1;
	  //std::cout << "collision" << std::endl;
	}
      if(colret)//collision
	{
	  //std::cout << "seg" << i << std::endl;
	  return 1;
	  //std::cout << "collision" << std::endl;
	}
    }

  return 0;//not collision
}


// End of example implementational code



