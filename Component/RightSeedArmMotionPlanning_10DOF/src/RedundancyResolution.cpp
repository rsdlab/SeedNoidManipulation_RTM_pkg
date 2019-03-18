#include "RedundancyResolution.h"

Redundancy::Redundancy()
{
  //コンストラクタ
}


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

int CollisionCheck(TenDOF joint,std::vector<AABB> CCaabb,int ObNum, double lifterBottom, double lifterTop);

int Redundancy::getRightRedundantJoint(double eerot[9], double eetrans[3], double nowJoint[4], double redundancyJoint[], double endEEtrans[])
{

  InitRand();

  struct timeval start_time;
  struct timeval end_time;

  gettimeofday(&start_time, NULL);
  
  double eerotInLifter[9];
  double eetransInLifter[3];
  double waistRoll = 0;
  double elbow = 0;
  Frame WaistPos;
  WaistPos.roll = 0;
  WaistPos.pitch = 0;
  WaistPos.yaw = 0;
  
  //float REDUN_DOF = 4;
  REDUN_fourDOF start;
  start.theta1 = nowJoint[0];
  start.theta2 = nowJoint[1];
  start.theta3 = nowJoint[2];
  start.theta4 = nowJoint[3];
  //std::cout << "start.theta1 = " << start.theta1 << std::endl;
  //std::cout << "start.theta2 = " << start.theta2 << std::endl;
  //std::cout << "start.theta3 = " << start.theta3 << std::endl;
  //std::cout << "start.theta4 = " << start.theta4 << std::endl;
      
  //初期位置で解けるか検証==================
  //kinematics
  //lifter
  double lifterFkJoint[3];
  lifterFkJoint[0] = start.theta1;
  lifterFkJoint[1] = start.theta2;
  lifterFkJoint[2] = 0;//urdfの余り

  double lifterEEtrans[3];
  noid.Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);

  std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
  std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
  std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
  
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
  
  std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
  std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
  std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
      
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

  // cout<<query.rows<<endl;
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
	  //std::cout << "rand.theta1 = " << rand.theta1 << std::endl;
	  //std::cout << "rand.theta2 = " << rand.theta2 << std::endl;
	  //std::cout << "rand.theta3 = " << rand.theta3 << std::endl;
	  //std::cout << "rand.theta4 = " << rand.theta4 << std::endl;
	  //randGoalFlag = 1;
	  //std::cout << "rand" << std::endl;
	}
      else
	{
	  rand.theta1 = randPoint_theta1();
	  rand.theta2 = randPoint_theta2();
	  rand.theta3 = randPoint_theta3();
	  rand.theta4 = randPoint_theta4();
	}
      
	  
      //gettimeofday(&start_kd_time, NULL);
      //最近傍点探索====================================================
      //FLANN==============================================================
      query[0][0]=rand.theta1;
      query[0][1]=rand.theta2;
      query[0][2]=rand.theta3;
      query[0][3]=rand.theta4;
           
      //index.radiusSearch(query, indices, dists, 500000.0,flann::SearchParams(128));
      index.knnSearch(query, indices, dists, 4, flann::SearchParams(128));//4 = Dim

      int nearestNodeNum = indices[0][0];//最近傍点のNumber
      //std::cout << "nearestNodeNum = " << nearestNodeNum << std::endl;
      //std::cout << "dist = " << dists[0][0] << std::endl;
      //================================================================
      //gettimeofday(&now_kd_time, NULL);
      //double sec = (double)(now_kd_time.tv_sec - start_kd_time.tv_sec);
      //double micro = (double)(now_kd_time.tv_usec - start_kd_time.tv_usec);
      //double dif = sec + micro / 1000.0 / 1000.0;
      //std::cout << "dif_kd_time = " << dif << "[sec]" << std::endl;
      //sum_kd_time += sec + micro / 1000.0 / 1000.0;
    
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

      //std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
      //std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
      //std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
      
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
      //std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
      //std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
      //std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
 
      WaistPos.yaw = newNode.theta3;
      WaistPos.pitch = newNode.theta4;
      WaistPos.roll = 0;
      elbow = 0;

      //std::cout << "newNode.theta1 = " << newNode.theta1 << std::endl;
      //std::cout << "newNode.theta2 = " << newNode.theta2 << std::endl;
      //std::cout << "newNode.theta3 = " << newNode.theta3 << std::endl;
      //std::cout << "newNode.theta4 = " << newNode.theta4 << std::endl;
 
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
	      gettimeofday(&end_time, NULL);
	      double sec = (double)(end_time.tv_sec - start_time.tv_sec);
	      double micro = (double)(end_time.tv_usec - start_time.tv_usec);
	      double runTime = sec + micro / 1000.0 / 1000.0;
	      std::cout << "runTime = " << runTime << "[sec]" << std::endl;
	      return -1;//IKが解けない
	    }
	}
      if(!ret)
	{
	  //IKが解けた
	  std::cout << "randCount = " << randCount << std::endl;
	  gettimeofday(&end_time, NULL);
	  double sec = (double)(end_time.tv_sec - start_time.tv_sec);
	  double micro = (double)(end_time.tv_usec - start_time.tv_usec);
	  double runTime = sec + micro / 1000.0 / 1000.0;
	  std::cout << "runTime = " << runTime << "[sec]" << std::endl;
	  std::cout << "newNode.theta1 = " << newNode.theta1 << std::endl;
	  std::cout << "newNode.theta2 = " << newNode.theta2 << std::endl;
	  std::cout << "newNode.theta3 = " << newNode.theta3 << std::endl;
	  std::cout << "newNode.theta4 = " << newNode.theta4 << std::endl;
 
	  std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
	  std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
	  std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
	  std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
	  std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
	  std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
 
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

int Redundancy::getRightRedundantJoint_CollisionCheck(double eerot[9], double eetrans[3], double nowJoint[4], double redundancyJoint[], double endEEtrans[], std::vector<AABB> aabb, int setObstacleNum)
{
  InitRand();

  struct timeval start_time;
  struct timeval end_time;

  gettimeofday(&start_time, NULL);
  
  double eerotInLifter[9];
  double eetransInLifter[3];
  double waistRoll = 0;
  double elbow = 0;
  Frame WaistPos;
  WaistPos.roll = 0;
  WaistPos.pitch = 0;
  WaistPos.yaw = 0;
  
  //float REDUN_DOF = 4;
  REDUN_fourDOF start;
  start.theta1 = nowJoint[0];
  start.theta2 = nowJoint[1];
  start.theta3 = nowJoint[2];
  start.theta4 = nowJoint[3];
  //std::cout << "start.theta1 = " << start.theta1 << std::endl;
  //std::cout << "start.theta2 = " << start.theta2 << std::endl;
  //std::cout << "start.theta3 = " << start.theta3 << std::endl;
  //std::cout << "start.theta4 = " << start.theta4 << std::endl;
      
  //初期位置で解けるか検証==================
  //kinematics
  //lifter
  double lifterFkJoint[3];
  lifterFkJoint[0] = start.theta1;
  lifterFkJoint[1] = start.theta2;
  lifterFkJoint[2] = 0;//urdfの余り

  double lifterEEtrans[3];
  noid.Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);

  std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
  std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
  std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
  
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
  
  std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
  std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
  std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
      
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

  // cout<<query.rows<<endl;
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
	  //std::cout << "rand.theta1 = " << rand.theta1 << std::endl;
	  //std::cout << "rand.theta2 = " << rand.theta2 << std::endl;
	  //std::cout << "rand.theta3 = " << rand.theta3 << std::endl;
	  //std::cout << "rand.theta4 = " << rand.theta4 << std::endl;
	  //randGoalFlag = 1;
	  //std::cout << "rand" << std::endl;
	}
      else
	{
	  rand.theta1 = randPoint_theta1();
	  rand.theta2 = randPoint_theta2();
	  rand.theta3 = randPoint_theta3();
	  rand.theta4 = randPoint_theta4();
	}
      
	  
      //gettimeofday(&start_kd_time, NULL);
      //最近傍点探索====================================================
      //FLANN==============================================================
      query[0][0]=rand.theta1;
      query[0][1]=rand.theta2;
      query[0][2]=rand.theta3;
      query[0][3]=rand.theta4;
           
      //index.radiusSearch(query, indices, dists, 500000.0,flann::SearchParams(128));
      index.knnSearch(query, indices, dists, 4, flann::SearchParams(128));//4 = Dim

      int nearestNodeNum = indices[0][0];//最近傍点のNumber
      //std::cout << "nearestNodeNum = " << nearestNodeNum << std::endl;
      //std::cout << "dist = " << dists[0][0] << std::endl;
      //================================================================
      //gettimeofday(&now_kd_time, NULL);
      //double sec = (double)(now_kd_time.tv_sec - start_kd_time.tv_sec);
      //double micro = (double)(now_kd_time.tv_usec - start_kd_time.tv_usec);
      //double dif = sec + micro / 1000.0 / 1000.0;
      //std::cout << "dif_kd_time = " << dif << "[sec]" << std::endl;
      //sum_kd_time += sec + micro / 1000.0 / 1000.0;
    
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

      //std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
      //std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
      //std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
      
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
      //std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
      //std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
      //std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
 
      WaistPos.yaw = newNode.theta3;
      WaistPos.pitch = newNode.theta4;
      WaistPos.roll = 0;
      elbow = 0;

      //std::cout << "newNode.theta1 = " << newNode.theta1 << std::endl;
      //std::cout << "newNode.theta2 = " << newNode.theta2 << std::endl;
      //std::cout << "newNode.theta3 = " << newNode.theta3 << std::endl;
      //std::cout << "newNode.theta4 = " << newNode.theta4 << std::endl;
 
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
	      gettimeofday(&end_time, NULL);
	      double sec = (double)(end_time.tv_sec - start_time.tv_sec);
	      double micro = (double)(end_time.tv_usec - start_time.tv_usec);
	      double runTime = sec + micro / 1000.0 / 1000.0;
	      std::cout << "runTime = " << runTime << "[sec]" << std::endl;
	      return -1;//IKが解けない
	    }
	}
      if(!ret)
	{
	  //IKが解けた
	  int colret = 0;
	  TenDOF noidPos;
	  noidPos.theta1 = iksol[0];
	  noidPos.theta2 = iksol[1];
	  noidPos.theta3 = iksol[2];
	  noidPos.theta4 = iksol[3];
	  noidPos.theta5 = iksol[4];
	  noidPos.theta6 = iksol[5];
	  noidPos.theta7 = iksol[6];
	  noidPos.theta8 = iksol[7];
	  noidPos.theta9 = iksol[8];
	  noidPos.theta10 = iksol[9];

	  double lifterBottom;
	  double lifterTop;
	  lifterBottom = newNode.theta1;
	  lifterTop = newNode.theta2;
	  //setLifterPos[0] = lifterEEtrans[0];
	  //setLifterPos[1] = lifterEEtrans[1];
	  //setLifterPos[2] = lifterEEtrans[2];
	  colret = CollisionCheck(noidPos,aabb,setObstacleNum,lifterBottom,lifterTop);
 
	  if(colret)
	    {
	      //障害物と接触
	      std::cout << "Redun Collision" << std::endl;
	      continue;
	    }
	  if(!colret)
	    {
	      std::cout << "randCount = " << randCount << std::endl;
	      gettimeofday(&end_time, NULL);
	      double sec = (double)(end_time.tv_sec - start_time.tv_sec);
	      double micro = (double)(end_time.tv_usec - start_time.tv_usec);
	      double runTime = sec + micro / 1000.0 / 1000.0;
	      std::cout << "runTime = " << runTime << "[sec]" << std::endl;
	      std::cout << "newNode.theta1 = " << newNode.theta1 << std::endl;
	      std::cout << "newNode.theta2 = " << newNode.theta2 << std::endl;
	      std::cout << "newNode.theta3 = " << newNode.theta3 << std::endl;
	      std::cout << "newNode.theta4 = " << newNode.theta4 << std::endl;
 
	      std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
	      std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
	      std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
	      std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
	      std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
	      std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
 
	      endEEtrans[0] = eetransInLifter[0];
	      endEEtrans[1] = eetransInLifter[1];
	      endEEtrans[2] = eetransInLifter[2];
	      redundancyJoint[0] = newNode.theta1;
	      redundancyJoint[1] = newNode.theta2;
	      redundancyJoint[2] = newNode.theta3;
	      redundancyJoint[3] = newNode.theta4;
	      return 0;
	    }
	}
    }//while
}



int Redundancy::getLeftRedundantJoint(double eerot[9], double eetrans[3], double nowJoint[4], double redundancyJoint[], double endEEtrans[])
{

  InitRand();

  struct timeval start_time;
  struct timeval end_time;

  gettimeofday(&start_time, NULL);
  
  double eerotInLifter[9];
  double eetransInLifter[3];
  double waistRoll = 0;
  double elbow = 0;
  Frame WaistPos;
  WaistPos.roll = 0;
  WaistPos.pitch = 0;
  WaistPos.yaw = 0;
  
  //float DOF = 4;
  REDUN_fourDOF start;
  start.theta1 = nowJoint[0];
  start.theta2 = nowJoint[1];
  start.theta3 = nowJoint[2];
  start.theta4 = nowJoint[3];
  //std::cout << "start.theta1 = " << start.theta1 << std::endl;
  //std::cout << "start.theta2 = " << start.theta2 << std::endl;
  //std::cout << "start.theta3 = " << start.theta3 << std::endl;
  //std::cout << "start.theta4 = " << start.theta4 << std::endl;
      
  //初期位置で解けるか検証==================
  //kinematics
  //lifter
  double lifterFkJoint[3];
  lifterFkJoint[0] = start.theta1;
  lifterFkJoint[1] = start.theta2;
  lifterFkJoint[2] = 0;//urdfの余り

  double lifterEEtrans[3];
  noid.Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);

  std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
  std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
  std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
  
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
  
  std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
  std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
  std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
      
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

  // cout<<query.rows<<endl;
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
	  //std::cout << "rand.theta1 = " << rand.theta1 << std::endl;
	  //std::cout << "rand.theta2 = " << rand.theta2 << std::endl;
	  //std::cout << "rand.theta3 = " << rand.theta3 << std::endl;
	  //std::cout << "rand.theta4 = " << rand.theta4 << std::endl;
	  //randGoalFlag = 1;
	  //std::cout << "rand" << std::endl;
	}
      else
	{
	  rand.theta1 = randPoint_theta1();
	  rand.theta2 = randPoint_theta2();
	  rand.theta3 = randPoint_theta3();
	  rand.theta4 = randPoint_theta4();
	}
      
	  
      //gettimeofday(&start_kd_time, NULL);
      //最近傍点探索====================================================
      //FLANN==============================================================
      query[0][0]=rand.theta1;
      query[0][1]=rand.theta2;
      query[0][2]=rand.theta3;
      query[0][3]=rand.theta4;
           
      //index.radiusSearch(query, indices, dists, 500000.0,flann::SearchParams(128));
      index.knnSearch(query, indices, dists, 4, flann::SearchParams(128));//4 = Dim

      int nearestNodeNum = indices[0][0];//最近傍点のNumber
      //std::cout << "nearestNodeNum = " << nearestNodeNum << std::endl;
      //std::cout << "dist = " << dists[0][0] << std::endl;
      //================================================================
      //gettimeofday(&now_kd_time, NULL);
      //double sec = (double)(now_kd_time.tv_sec - start_kd_time.tv_sec);
      //double micro = (double)(now_kd_time.tv_usec - start_kd_time.tv_usec);
      //double dif = sec + micro / 1000.0 / 1000.0;
      //std::cout << "dif_kd_time = " << dif << "[sec]" << std::endl;
      //sum_kd_time += sec + micro / 1000.0 / 1000.0;
    
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

      //std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
      //std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
      //std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
      
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
      //std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
      //std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
      //std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
 
      WaistPos.yaw = newNode.theta3;
      WaistPos.pitch = newNode.theta4;
      WaistPos.roll = 0;
      elbow = 0;

      //std::cout << "newNode.theta1 = " << newNode.theta1 << std::endl;
      //std::cout << "newNode.theta2 = " << newNode.theta2 << std::endl;
      //std::cout << "newNode.theta3 = " << newNode.theta3 << std::endl;
      //std::cout << "newNode.theta4 = " << newNode.theta4 << std::endl;
 
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
	      gettimeofday(&end_time, NULL);
	      double sec = (double)(end_time.tv_sec - start_time.tv_sec);
	      double micro = (double)(end_time.tv_usec - start_time.tv_usec);
	      double runTime = sec + micro / 1000.0 / 1000.0;
	      std::cout << "runTime = " << runTime << "[sec]" << std::endl;
	      return -1;//IKが解けない
	    }
	}
      if(!ret)
	{
	  //IKが解けた
	  std::cout << "randCount = " << randCount << std::endl;
	  gettimeofday(&end_time, NULL);
	  double sec = (double)(end_time.tv_sec - start_time.tv_sec);
	  double micro = (double)(end_time.tv_usec - start_time.tv_usec);
	  double runTime = sec + micro / 1000.0 / 1000.0;
	  std::cout << "runTime = " << runTime << "[sec]" << std::endl;
	  std::cout << "newNode.theta1 = " << newNode.theta1 << std::endl;
	  std::cout << "newNode.theta2 = " << newNode.theta2 << std::endl;
	  std::cout << "newNode.theta3 = " << newNode.theta3 << std::endl;
	  std::cout << "newNode.theta4 = " << newNode.theta4 << std::endl;
 
	  std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
	  std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
	  std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
	  std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
	  std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
	  std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
 
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


int Redundancy::getLeftRedundantJoint_CollisionCheck(double eerot[9], double eetrans[3], double nowJoint[4], double redundancyJoint[], double endEEtrans[], std::vector<AABB> aabb, int setObstacleNum)
{
  InitRand();

  struct timeval start_time;
  struct timeval end_time;

  gettimeofday(&start_time, NULL);
  
  double eerotInLifter[9];
  double eetransInLifter[3];
  double waistRoll = 0;
  double elbow = 0;
  Frame WaistPos;
  WaistPos.roll = 0;
  WaistPos.pitch = 0;
  WaistPos.yaw = 0;
  
  //float DOF = 4;
  REDUN_fourDOF start;
  start.theta1 = nowJoint[0];
  start.theta2 = nowJoint[1];
  start.theta3 = nowJoint[2];
  start.theta4 = nowJoint[3];
  //std::cout << "start.theta1 = " << start.theta1 << std::endl;
  //std::cout << "start.theta2 = " << start.theta2 << std::endl;
  //std::cout << "start.theta3 = " << start.theta3 << std::endl;
  //std::cout << "start.theta4 = " << start.theta4 << std::endl;
      
  //初期位置で解けるか検証==================
  //kinematics
  //lifter
  double lifterFkJoint[3];
  lifterFkJoint[0] = start.theta1;
  lifterFkJoint[1] = start.theta2;
  lifterFkJoint[2] = 0;//urdfの余り

  double lifterEEtrans[3];
  noid.Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);

  std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
  std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
  std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
  
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
  
  std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
  std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
  std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
      
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

  // cout<<query.rows<<endl;
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
	  //std::cout << "rand.theta1 = " << rand.theta1 << std::endl;
	  //std::cout << "rand.theta2 = " << rand.theta2 << std::endl;
	  //std::cout << "rand.theta3 = " << rand.theta3 << std::endl;
	  //std::cout << "rand.theta4 = " << rand.theta4 << std::endl;
	  //randGoalFlag = 1;
	  //std::cout << "rand" << std::endl;
	}
      else
	{
	  rand.theta1 = randPoint_theta1();
	  rand.theta2 = randPoint_theta2();
	  rand.theta3 = randPoint_theta3();
	  rand.theta4 = randPoint_theta4();
	}
      
	  
      //gettimeofday(&start_kd_time, NULL);
      //最近傍点探索====================================================
      //FLANN==============================================================
      query[0][0]=rand.theta1;
      query[0][1]=rand.theta2;
      query[0][2]=rand.theta3;
      query[0][3]=rand.theta4;
           
      //index.radiusSearch(query, indices, dists, 500000.0,flann::SearchParams(128));
      index.knnSearch(query, indices, dists, 4, flann::SearchParams(128));//4 = Dim

      int nearestNodeNum = indices[0][0];//最近傍点のNumber
      //std::cout << "nearestNodeNum = " << nearestNodeNum << std::endl;
      //std::cout << "dist = " << dists[0][0] << std::endl;
      //================================================================
      //gettimeofday(&now_kd_time, NULL);
      //double sec = (double)(now_kd_time.tv_sec - start_kd_time.tv_sec);
      //double micro = (double)(now_kd_time.tv_usec - start_kd_time.tv_usec);
      //double dif = sec + micro / 1000.0 / 1000.0;
      //std::cout << "dif_kd_time = " << dif << "[sec]" << std::endl;
      //sum_kd_time += sec + micro / 1000.0 / 1000.0;
    
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

      //std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
      //std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
      //std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
      
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
      //std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
      //std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
      //std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
 
      WaistPos.yaw = newNode.theta3;
      WaistPos.pitch = newNode.theta4;
      WaistPos.roll = 0;
      elbow = 0;

      //std::cout << "newNode.theta1 = " << newNode.theta1 << std::endl;
      //std::cout << "newNode.theta2 = " << newNode.theta2 << std::endl;
      //std::cout << "newNode.theta3 = " << newNode.theta3 << std::endl;
      //std::cout << "newNode.theta4 = " << newNode.theta4 << std::endl;
 
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
	      gettimeofday(&end_time, NULL);
	      double sec = (double)(end_time.tv_sec - start_time.tv_sec);
	      double micro = (double)(end_time.tv_usec - start_time.tv_usec);
	      double runTime = sec + micro / 1000.0 / 1000.0;
	      std::cout << "runTime = " << runTime << "[sec]" << std::endl;
	      return -1;//IKが解けない
	    }
	}
      if(!ret)
	{
	  //IKが解けた
	  int colret = 0;
	  TenDOF noidPos;
	  noidPos.theta1 = iksol[0];
	  noidPos.theta2 = iksol[1];
	  noidPos.theta3 = iksol[2];
	  noidPos.theta4 = iksol[3];
	  noidPos.theta5 = iksol[4];
	  noidPos.theta6 = iksol[5];
	  noidPos.theta7 = iksol[6];
	  noidPos.theta8 = iksol[7];
	  noidPos.theta9 = iksol[8];
	  noidPos.theta10 = iksol[9];

	  double setLifterPos[3];
	  setLifterPos[0] = lifterEEtrans[0];
	  setLifterPos[1] = lifterEEtrans[1];
	  setLifterPos[2] = lifterEEtrans[2];
	  double lifterBottom;
	  double lifterTop;
	  lifterBottom = newNode.theta1;
	  lifterTop = newNode.theta2;
	  colret = CollisionCheck(noidPos,aabb,setObstacleNum,lifterBottom,lifterTop);
 
	  if(colret)
	    {
	      //障害物と接触
	      continue;
	    }
	  if(!colret)
	    {
	      std::cout << "randCount = " << randCount << std::endl;
	      gettimeofday(&end_time, NULL);
	      double sec = (double)(end_time.tv_sec - start_time.tv_sec);
	      double micro = (double)(end_time.tv_usec - start_time.tv_usec);
	      double runTime = sec + micro / 1000.0 / 1000.0;
	      std::cout << "runTime = " << runTime << "[sec]" << std::endl;
	      std::cout << "newNode.theta1 = " << newNode.theta1 << std::endl;
	      std::cout << "newNode.theta2 = " << newNode.theta2 << std::endl;
	      std::cout << "newNode.theta3 = " << newNode.theta3 << std::endl;
	      std::cout << "newNode.theta4 = " << newNode.theta4 << std::endl;
 
	      std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0] << std::endl;
	      std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1] << std::endl;
	      std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2] << std::endl;
	      std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
	      std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
	      std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
 
	      endEEtrans[0] = eetransInLifter[0];
	      endEEtrans[1] = eetransInLifter[1];
	      endEEtrans[2] = eetransInLifter[2];
	      redundancyJoint[0] = newNode.theta1;
	      redundancyJoint[1] = newNode.theta2;
	      redundancyJoint[2] = newNode.theta3;
	      redundancyJoint[3] = newNode.theta4;
	      return 0;
	    }
	}
    }//while


}

//現状右だけ
int CollisionCheck(TenDOF joint,std::vector<AABB> CCaabb,int ObNum, double lifterBottom, double lifterTop)
{
  Manipulator manip;
  Collision cc;
  SegLine segManip[LinkNum];
  
  //SegLine segManip[4];
  int colret = 0;
  //CollisionCheck
  manip.CalcManipLinkPos_ten_Lifter(joint,segManip,lifterBottom,lifterTop);
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
