#include "RedundancyResolution.h"

Redundancy::Redundancy()
{
  //コンストラクタ
}

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

inline int randPoint_theta3()//-120~120
{
  return (rand() % 241) - 120;
}

inline int randPoint_theta4()//-9~39
{
  return (rand() % 48) - 9;
}

inline int randMax()
{
  return rand() % 10;
}

inline int randHalf()
{
  return rand() % 2;
}


int Redundancy::getRightRedundantJoint(double eerot[9], double eetrans[3], double nowJoint[4], double redundancyJoint[], double endEEtrans[])
{

  InitRand();

  SeedUpper noid;

  double eerotInLifter[9];
  double eetransInLifter[3];
  double elbow = 0;
  Frame WaistPos;
  WaistPos.roll = 0;
  WaistPos.pitch = 0;
  WaistPos.yaw = 0;
  
  REDUN_fourDOF start;
  start.theta1 = nowJoint[0];
  start.theta2 = nowJoint[1];
  start.theta3 = nowJoint[2];
  start.theta4 = nowJoint[3];
      
  //初期位置で解けるか検証==================
  //kinematics
  //lifter
  double lifterFkJoint[3];
  lifterFkJoint[0] = start.theta1;
  lifterFkJoint[1] = start.theta2;
  lifterFkJoint[2] = 0;//urdfの余り

  double lifterEEtrans[3];
  noid.Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);

  eerotInLifter[0] = eerot[0];
  eerotInLifter[1] = eerot[1];
  eerotInLifter[2] = eerot[2];
  eerotInLifter[3] = eerot[3];
  eerotInLifter[4] = eerot[4];
  eerotInLifter[5] = eerot[5];
  eerotInLifter[6] = eerot[6];
  eerotInLifter[7] = eerot[7];
  eerotInLifter[8] = eerot[8];
  eetransInLifter[0] = eetrans[0] - lifterEEtrans[0];
  eetransInLifter[1] = eetrans[1] - lifterEEtrans[1];
  eetransInLifter[2] = eetrans[2] - lifterEEtrans[2];

  WaistPos.yaw = start.theta3;
  WaistPos.pitch = start.theta4;
  WaistPos.roll = 0;
  elbow = 0;

  double nowJointPos[10];
  for(int l=0;l<10;l++){
    nowJointPos[l] = 0;
  }
  double iksol[10];
  int ret;
  ret = noid.Solve_WRArmIk(eerotInLifter,eetransInLifter,elbow,WaistPos,nowJointPos,iksol);
      
  if(!ret)
    {
      //IKが解けた
      endEEtrans[0] = eetransInLifter[0];
      endEEtrans[1] = eetransInLifter[1];
      endEEtrans[2] = eetransInLifter[2];
      redundancyJoint[0] = start.theta1;
      redundancyJoint[1] = start.theta2;
      redundancyJoint[2] = start.theta3;
      redundancyJoint[3] = start.theta4;
      return 0;
    }
  //===========================================================
  
  REDUN_fourDOF max;
  max.theta1 = 0;
  max.theta2 = 85;
  max.theta3 = 120;
  max.theta4 = 39;
  REDUN_fourDOF min;
  min.theta1 = -85;
  min.theta2 = 0;
  min.theta3 = -120;
  min.theta4 = -9;
 
  int randCount = 0;
  REDUN_fourDOF rand;
  std::vector<REDUN_fourDOF> nodeList;

  float expandDis = 5;

  nodeList.push_back(start);
  flann::Matrix<float> dataset(new float[REDUN_DOF*1], 1, REDUN_DOF);
  dataset[0][0] = start.theta1;
  dataset[0][1] = start.theta2;
  dataset[0][2] = start.theta3;
  dataset[0][3] = start.theta4;

  flann::Index<flann::L2<float> > index(dataset, flann::KDTreeIndexParams(4));
  index.buildIndex();

  flann::Matrix<float> query(new float[REDUN_DOF*1],1, REDUN_DOF);
  //radius
  //flann::Matrix<int> indices(new int[query.rows],query.rows,1);
  //flann::Matrix<float> dists(new float[query.rows],query.rows, 1);
  //knn
  flann::Matrix<int> indices(new int[query.rows*REDUN_DOF],query.rows,REDUN_DOF);
  flann::Matrix<float> dists(new float[query.rows*REDUN_DOF],query.rows, REDUN_DOF);

    while(1)
    {
      randCount++;
      
      if(randMax() == 0)
	{
	  //theta1
	  if(randHalf() == 0){
	    rand.theta1 = randPoint_theta1();
	  }
	  else if(randHalf() == 0){
	    rand.theta1 = max.theta1;
	  }
	  else{
	    rand.theta1 = min.theta1;
	  }
	  //theta2
	  if(randHalf() == 0){
	    rand.theta2 = randPoint_theta2();
	  }
	  else if(randHalf() == 0){
	    rand.theta2 = max.theta2;
	  }
	  else{
	    rand.theta2 = min.theta2;
	  }
	  //theta3
	  if(randHalf() == 0){
	    rand.theta3 = randPoint_theta3();
	  }
	  else if(randHalf() == 0){
	    rand.theta3 = max.theta3;
	  }
	  else{
	    rand.theta3 = min.theta3;
	  }
	  //theta4
	  if(randHalf() == 0){
	    rand.theta4 = randPoint_theta4();
	  }
	  else if(randHalf() == 0){
	    rand.theta4 = max.theta4;
	  }
	  else{
	    rand.theta4 = min.theta4;
	  }
	}
      else
	{
	  rand.theta1 = randPoint_theta1();
	  rand.theta2 = randPoint_theta2();
	  rand.theta3 = randPoint_theta3();
	  rand.theta4 = randPoint_theta4();
	}
      
      //最近傍点探索====================================================
      //FLANN==============================================================
      query[0][0]=rand.theta1;
      query[0][1]=rand.theta2;
      query[0][2]=rand.theta3;
      query[0][3]=rand.theta4;
           
      //index.radiusSearch(query, indices, dists, 500000.0,flann::SearchParams(128));
      index.knnSearch(query, indices, dists, 4, flann::SearchParams(128));//4 = Dim

      int nearestNodeNum = indices[0][0];//最近傍点のNumber
      
      REDUN_fourDOF newNode;
      REDUN_fourDOF nearestNode;
      nearestNode.theta1 = nodeList[nearestNodeNum].theta1;
      nearestNode.theta2 = nodeList[nearestNodeNum].theta2;
      nearestNode.theta3 = nodeList[nearestNodeNum].theta3;
      nearestNode.theta4 = nodeList[nearestNodeNum].theta4;
      float distance = (sqrt((nearestNode.theta1 - rand.theta1)*(nearestNode.theta1 - rand.theta1) + (nearestNode.theta2 - rand.theta2)*(nearestNode.theta2 - rand.theta2) + (nearestNode.theta3 - rand.theta3)*(nearestNode.theta3 - rand.theta3) + (nearestNode.theta4 - rand.theta4)*(nearestNode.theta4 - rand.theta4)));
      //std::cout << "distance = " << distance << std::endl;
      if(distance < expandDis)
	{
	  newNode.theta1 = rand.theta1;
	  newNode.theta2 = rand.theta2;
	  newNode.theta3 = rand.theta3;
	  newNode.theta4 = rand.theta4;
	}
      else
	{
	  newNode.theta1 = nearestNode.theta1 + ((rand.theta1 - nearestNode.theta1)*(expandDis/distance));
	  newNode.theta2 = nearestNode.theta2 + ((rand.theta2 - nearestNode.theta2)*(expandDis/distance));
	  newNode.theta3 = nearestNode.theta3 + ((rand.theta3 - nearestNode.theta3)*(expandDis/distance));
	  newNode.theta4 = nearestNode.theta4 + ((rand.theta4 - nearestNode.theta4)*(expandDis/distance));
	}

      //kinematics
      //lifter
      lifterFkJoint[0] = newNode.theta1;
      lifterFkJoint[1] = newNode.theta2;
      lifterFkJoint[2] = 0;//urdfの余り

      noid.Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);

      eerotInLifter[0] = eerot[0];
      eerotInLifter[1] = eerot[1];
      eerotInLifter[2] = eerot[2];
      eerotInLifter[3] = eerot[3];
      eerotInLifter[4] = eerot[4];
      eerotInLifter[5] = eerot[5];
      eerotInLifter[6] = eerot[6];
      eerotInLifter[7] = eerot[7];
      eerotInLifter[8] = eerot[8];
      eetransInLifter[0] = eetrans[0] - lifterEEtrans[0];
      eetransInLifter[1] = eetrans[1] - lifterEEtrans[1];
      eetransInLifter[2] = eetrans[2] - lifterEEtrans[2];

      WaistPos.yaw = newNode.theta3;
      WaistPos.pitch = newNode.theta4;
      WaistPos.roll = 0;
      elbow = 0;

      ret = noid.Solve_WRArmIk(eerotInLifter,eetransInLifter,elbow,WaistPos,nowJointPos,iksol);
      
      if(ret)
	{
	  //IKが解けない
	  flann::Matrix<float> add(new float[REDUN_DOF*1],1, REDUN_DOF);
	  //干渉しない
	  add[0][0]=newNode.theta1;
	  add[0][1]=newNode.theta2;
	  add[0][2]=newNode.theta3;
	  add[0][3]=newNode.theta4;
	  index.addPoints(add);
	  nodeList.push_back(newNode);

	  if(randCount > 5000)
	    {
	      return -1;//IKが解けない
	    }
	}
      if(!ret)
	{
	  //IKが解けた
	  endEEtrans[0] = eetransInLifter[0];
	  endEEtrans[1] = eetransInLifter[1];
	  endEEtrans[2] = eetransInLifter[2];
	  redundancyJoint[0] = newNode.theta1;
	  redundancyJoint[1] = newNode.theta2;
	  redundancyJoint[2] = newNode.theta3;
	  redundancyJoint[3] = newNode.theta4;
	  return 0;
	}
    }//while

}



int Redundancy::getLeftRedundantJoint(double eerot[9], double eetrans[3], double nowJoint[4], double redundancyJoint[], double endEEtrans[])
{
  InitRand();

  SeedUpper noid;
  
  double eerotInLifter[9];
  double eetransInLifter[3];
  double elbow = 0;
  Frame WaistPos;
  WaistPos.roll = 0;
  WaistPos.pitch = 0;
  WaistPos.yaw = 0;
  
  REDUN_fourDOF start;
  start.theta1 = nowJoint[0];
  start.theta2 = nowJoint[1];
  start.theta3 = nowJoint[2];
  start.theta4 = nowJoint[3];
      
  //初期位置で解けるか検証==================
  //kinematics
  //lifter
  double lifterFkJoint[3];
  lifterFkJoint[0] = start.theta1;
  lifterFkJoint[1] = start.theta2;
  lifterFkJoint[2] = 0;//urdfの余り

  double lifterEEtrans[3];
  noid.Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);
  
  eerotInLifter[0] = eerot[0];
  eerotInLifter[1] = eerot[1];
  eerotInLifter[2] = eerot[2];
  eerotInLifter[3] = eerot[3];
  eerotInLifter[4] = eerot[4];
  eerotInLifter[5] = eerot[5];
  eerotInLifter[6] = eerot[6];
  eerotInLifter[7] = eerot[7];
  eerotInLifter[8] = eerot[8];
  eetransInLifter[0] = eetrans[0] - lifterEEtrans[0];
  eetransInLifter[1] = eetrans[1] - lifterEEtrans[1];
  eetransInLifter[2] = eetrans[2] - lifterEEtrans[2];

  WaistPos.yaw = start.theta3;
  WaistPos.pitch = start.theta4;
  WaistPos.roll = 0;
  elbow = 0;

  double nowJointPos[10];
  for(int l=0;l<10;l++){
    nowJointPos[l] = 0;
  }
  double iksol[10];
  int ret;
  ret = noid.Solve_WLArmIk(eerotInLifter,eetransInLifter,elbow,WaistPos,nowJointPos,iksol);
      
  if(!ret)
    {
      //IKが解けた
      endEEtrans[0] = eetransInLifter[0];
      endEEtrans[1] = eetransInLifter[1];
      endEEtrans[2] = eetransInLifter[2];
      redundancyJoint[0] = start.theta1;
      redundancyJoint[1] = start.theta2;
      redundancyJoint[2] = start.theta3;
      redundancyJoint[3] = start.theta4;
      return 0;
    }
  //===========================================================
  
  REDUN_fourDOF max;
  max.theta1 = 0;
  max.theta2 = 85;
  max.theta3 = 120;
  max.theta4 = 39;
  REDUN_fourDOF min;
  min.theta1 = -85;
  min.theta2 = 0;
  min.theta3 = -120;
  min.theta4 = -9;
 
  int randCount = 0;
  REDUN_fourDOF rand;
  std::vector<REDUN_fourDOF> nodeList;

  float expandDis = 5;

  nodeList.push_back(start);
  flann::Matrix<float> dataset(new float[REDUN_DOF*1], 1, REDUN_DOF);
  dataset[0][0] = start.theta1;
  dataset[0][1] = start.theta2;
  dataset[0][2] = start.theta3;
  dataset[0][3] = start.theta4;

  flann::Index<flann::L2<float> > index(dataset, flann::KDTreeIndexParams(4));
  index.buildIndex();

  flann::Matrix<float> query(new float[REDUN_DOF*1],1, REDUN_DOF);
  //radius
  //flann::Matrix<int> indices(new int[query.rows],query.rows,1);
  //flann::Matrix<float> dists(new float[query.rows],query.rows, 1);
  //knn
  flann::Matrix<int> indices(new int[query.rows*REDUN_DOF],query.rows,REDUN_DOF);
  flann::Matrix<float> dists(new float[query.rows*REDUN_DOF],query.rows, REDUN_DOF);

    while(1)
    {
      randCount++;
      
      if(randMax() == 0)
	{
	  //theta1
	  if(randHalf() == 0){
	    rand.theta1 = randPoint_theta1();
	  }
	  else if(randHalf() == 0){
	    rand.theta1 = max.theta1;
	  }
	  else{
	    rand.theta1 = min.theta1;
	  }
	  //theta2
	  if(randHalf() == 0){
	    rand.theta2 = randPoint_theta2();
	  }
	  else if(randHalf() == 0){
	    rand.theta2 = max.theta2;
	  }
	  else{
	    rand.theta2 = min.theta2;
	  }
	  //theta3
	  if(randHalf() == 0){
	    rand.theta3 = randPoint_theta3();
	  }
	  else if(randHalf() == 0){
	    rand.theta3 = max.theta3;
	  }
	  else{
	    rand.theta3 = min.theta3;
	  }
	  //theta4
	  if(randHalf() == 0){
	    rand.theta4 = randPoint_theta4();
	  }
	  else if(randHalf() == 0){
	    rand.theta4 = max.theta4;
	  }
	  else{
	    rand.theta4 = min.theta4;
	  }
	}
      else
	{
	  rand.theta1 = randPoint_theta1();
	  rand.theta2 = randPoint_theta2();
	  rand.theta3 = randPoint_theta3();
	  rand.theta4 = randPoint_theta4();
	}
      
      //最近傍点探索====================================================
      //FLANN==============================================================
      query[0][0]=rand.theta1;
      query[0][1]=rand.theta2;
      query[0][2]=rand.theta3;
      query[0][3]=rand.theta4;
           
      //index.radiusSearch(query, indices, dists, 500000.0,flann::SearchParams(128));
      index.knnSearch(query, indices, dists, 4, flann::SearchParams(128));//4 = Dim

      int nearestNodeNum = indices[0][0];//最近傍点のNumber
    
      REDUN_fourDOF newNode;
      REDUN_fourDOF nearestNode;
      nearestNode.theta1 = nodeList[nearestNodeNum].theta1;
      nearestNode.theta2 = nodeList[nearestNodeNum].theta2;
      nearestNode.theta3 = nodeList[nearestNodeNum].theta3;
      nearestNode.theta4 = nodeList[nearestNodeNum].theta4;
      float distance = (sqrt((nearestNode.theta1 - rand.theta1)*(nearestNode.theta1 - rand.theta1) + (nearestNode.theta2 - rand.theta2)*(nearestNode.theta2 - rand.theta2) + (nearestNode.theta3 - rand.theta3)*(nearestNode.theta3 - rand.theta3) + (nearestNode.theta4 - rand.theta4)*(nearestNode.theta4 - rand.theta4)));
      if(distance < expandDis)
	{
	  newNode.theta1 = rand.theta1;
	  newNode.theta2 = rand.theta2;
	  newNode.theta3 = rand.theta3;
	  newNode.theta4 = rand.theta4;
	}
      else
	{
	  newNode.theta1 = nearestNode.theta1 + ((rand.theta1 - nearestNode.theta1)*(expandDis/distance));
	  newNode.theta2 = nearestNode.theta2 + ((rand.theta2 - nearestNode.theta2)*(expandDis/distance));
	  newNode.theta3 = nearestNode.theta3 + ((rand.theta3 - nearestNode.theta3)*(expandDis/distance));
	  newNode.theta4 = nearestNode.theta4 + ((rand.theta4 - nearestNode.theta4)*(expandDis/distance));
	}

      //kinematics
      //lifter
      lifterFkJoint[0] = newNode.theta1;
      lifterFkJoint[1] = newNode.theta2;
      lifterFkJoint[2] = 0;//urdfの余り

      noid.Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);
      
      eerotInLifter[0] = eerot[0];
      eerotInLifter[1] = eerot[1];
      eerotInLifter[2] = eerot[2];
      eerotInLifter[3] = eerot[3];
      eerotInLifter[4] = eerot[4];
      eerotInLifter[5] = eerot[5];
      eerotInLifter[6] = eerot[6];
      eerotInLifter[7] = eerot[7];
      eerotInLifter[8] = eerot[8];
      eetransInLifter[0] = eetrans[0] - lifterEEtrans[0];
      eetransInLifter[1] = eetrans[1] - lifterEEtrans[1];
      eetransInLifter[2] = eetrans[2] - lifterEEtrans[2];
      
      WaistPos.yaw = newNode.theta3;
      WaistPos.pitch = newNode.theta4;
      WaistPos.roll = 0;
      elbow = 0;

      ret = noid.Solve_WLArmIk(eerotInLifter,eetransInLifter,elbow,WaistPos,nowJointPos,iksol);
      
      if(ret)
	{
	  //IKが解けない
	  flann::Matrix<float> add(new float[REDUN_DOF*1],1, REDUN_DOF);
	  //干渉しない
	  add[0][0]=newNode.theta1;
	  add[0][1]=newNode.theta2;
	  add[0][2]=newNode.theta3;
	  add[0][3]=newNode.theta4;
	  index.addPoints(add);
	  nodeList.push_back(newNode);

	  if(randCount > 5000)
	    {
	      return -1;//IKが解けない
	    }
	}
      if(!ret)
	{
	  //IKが解けた 
	  endEEtrans[0] = eetransInLifter[0];
	  endEEtrans[1] = eetransInLifter[1];
	  endEEtrans[2] = eetransInLifter[2];
	  redundancyJoint[0] = newNode.theta1;
	  redundancyJoint[1] = newNode.theta2;
	  redundancyJoint[2] = newNode.theta3;
	  redundancyJoint[3] = newNode.theta4;
	  return 0;
	}
    }//while

}

