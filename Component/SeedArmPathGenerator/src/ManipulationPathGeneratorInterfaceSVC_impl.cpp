// -*-C++-*-
/*!
 * @file  ManipulationPathGeneratorInterfaceSVC_impl.cpp
 * @brief Service implementation code of ManipulationPathGeneratorInterface.idl
 *
 */

#include "ManipulationPathGeneratorInterfaceSVC_impl.h"
#include "GeneratorReturnID.h"
#include "LibManipulatorPathGenerator.h"

/*
 * Example implementational code for IDL interface Manipulation::PathGeneratorInterface
 */
Manipulation_PathGeneratorInterfaceSVC_impl::Manipulation_PathGeneratorInterfaceSVC_impl()
{
  // Please add extra constructor code here.
  SeedArmJointLimit[0].Upper = Angle1_LimitMax;
  SeedArmJointLimit[0].Lower = Angle1_LimitMin;
  SeedArmJointLimit[1].Upper = Angle2_LimitMax;
  SeedArmJointLimit[1].Lower = Angle2_LimitMin;
  SeedArmJointLimit[2].Upper = Angle3_LimitMax;
  SeedArmJointLimit[2].Lower = Angle3_LimitMin;
  SeedArmJointLimit[3].Upper = Angle4_LimitMax;
  SeedArmJointLimit[3].Lower = Angle4_LimitMin;
  SeedArmJointLimit[4].Upper = Angle5_LimitMax;
  SeedArmJointLimit[4].Lower = Angle5_LimitMin;
  SeedArmJointLimit[5].Upper = Angle6_LimitMax;
  SeedArmJointLimit[5].Lower = Angle6_LimitMin;
  SeedArmJointLimit[6].Upper = Angle7_LimitMax;
  SeedArmJointLimit[6].Lower = Angle7_LimitMin;
  SeedArmJointLimit[7].Upper = Angle8_LimitMax;
  SeedArmJointLimit[7].Lower = Angle8_LimitMin;
  SeedArmJointLimit[8].Upper = Angle9_LimitMax;
  SeedArmJointLimit[8].Lower = Angle9_LimitMin;
  SeedArmJointLimit[9].Upper = Angle10_LimitMax;
  SeedArmJointLimit[9].Lower = Angle10_LimitMin;
  SeedArmJointLimit[10].Upper = Angle11_LimitMax;
  SeedArmJointLimit[10].Lower = Angle11_LimitMin;
  SeedArmJointLimit[11].Upper = Angle12_LimitMax;
  SeedArmJointLimit[11].Lower = Angle12_LimitMin;
}


Manipulation_PathGeneratorInterfaceSVC_impl::~Manipulation_PathGeneratorInterfaceSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
Manipulation::RETURN_ID* Manipulation_PathGeneratorInterfaceSVC_impl::JointSpaceGenerateRightArmMotion(const Manipulation::JointAngleSeq& goalJointPos)
{
  std::cout << "JointSpaceGenerateRightArmMotion" << std::endl;
  
  double CmdCycle;
  double CurrentLifterPos[2];
  double CurrentWaistPos[3];
  double CurrentRightArmPos[7];
  double CurrentLeftArmPos[7];
  double CurrentLIWARJointPos[12];
  
  double Movetime;//[s]
  double MaxSpeed;
  double SpdRatio;
  double AngularVelocity;
  double RotationLength[12];
  double MaxMoveJoint;
  double targetJointPos[12];

  double pathNumber;
  //時間計測
  int first=0;
  struct timeval start;
  struct timeval end;
  double sec;
  double micro;
  double duration;

  CmdCycle = m_rtcPtr->getcmdCycle();
  MaxSpeed = m_rtcPtr->getMaxSpeedJoint();
  SpdRatio = m_rtcPtr->getSpeedRatioJoint();
  AngularVelocity = MaxSpeed*SpdRatio/100;
  m_rtcPtr->getSeedCurrentJoint(CurrentLifterPos,CurrentWaistPos,CurrentRightArmPos,CurrentLeftArmPos);

  CurrentLIWARJointPos[0] = CurrentLifterPos[0];
  CurrentLIWARJointPos[1] = CurrentLifterPos[1];
  CurrentLIWARJointPos[2] = CurrentWaistPos[0];
  CurrentLIWARJointPos[3] = CurrentWaistPos[1];
  CurrentLIWARJointPos[4] = CurrentWaistPos[2];
  for(int k=0;k<7;k++)
    {
      CurrentLIWARJointPos[k+5] =  CurrentRightArmPos[k];
    }  

  for(int k=0;k<12;k++)
    {
      RotationLength[k] = fabs(goalJointPos[k]-CurrentLIWARJointPos[k]);
    }
  MaxMoveJoint = RotationLength[0];
  for(int j=0;j<12;j++)
    {
      if(MaxMoveJoint<RotationLength[j]){
	MaxMoveJoint = RotationLength[j];    
      }
    }
  Movetime = (MaxMoveJoint/AngularVelocity);

   //=============================================================
  double startpos;
  double goalpos;
  std::vector<double> path;
  std::vector<std::vector<double> > manippath;
  for(int i=0;i<12;i++){
    startpos = CurrentLIWARJointPos[i];
    goalpos = goalJointPos[i];
    pathNumber = Movetime*CmdCycle;
    path.resize(pathNumber);
    m_path.pathPlan(startpos,goalpos,path,Movetime,CmdCycle);
    manippath.push_back(path);
  }

  gettimeofday(&start, NULL);
  int nowPathNum=0;
  double usleeptime;
  for(int f=0; f<manippath[0].size(); f++)
    {
      targetJointPos[0] = manippath[0][nowPathNum];
      targetJointPos[1] = manippath[1][nowPathNum];
      targetJointPos[2] = manippath[2][nowPathNum];
      targetJointPos[3] = manippath[3][nowPathNum];
      targetJointPos[4] = manippath[4][nowPathNum];
      targetJointPos[5] = manippath[5][nowPathNum];
      targetJointPos[6] = manippath[6][nowPathNum];
      targetJointPos[7] = manippath[7][nowPathNum];
      targetJointPos[8] = manippath[8][nowPathNum];
      targetJointPos[9] = manippath[9][nowPathNum];
      targetJointPos[10] = manippath[10][nowPathNum];
      targetJointPos[11] = manippath[11][nowPathNum];

      for(int b=0;b<12;b++)
	{
	  if(targetJointPos[b]>SeedArmJointLimit[b].Upper){
	    targetJointPos[b] = SeedArmJointLimit[b].Upper;
	  }
	  if(targetJointPos[b]<SeedArmJointLimit[b].Lower){
	    targetJointPos[b] = SeedArmJointLimit[b].Lower;
	  }
	}
      
      if(first!=0)
	{
	  gettimeofday(&end, NULL);
	  sec = (double)(end.tv_sec - start.tv_sec);
	  micro = (double)(end.tv_usec - start.tv_usec);
	  duration = sec + micro / 1000.0 / 1000.0;
	  std::cout << "duration = " << duration <<"[s]"<<std::endl;
	  if(duration < 1/CmdCycle){
	    usleeptime = 1000*(1000/CmdCycle) - (duration * 1000*1000);
	    usleep(usleeptime);
	    std::cout << "sleeptime = " << usleeptime/(1000*1000) << "[s]" << std::endl;
	  }
	}
      gettimeofday(&start, NULL);
      first = 1;
      m_rtcPtr->movePTPLIWARJointAbs(targetJointPos);
      nowPathNum++;
    }
  
  std::cout << "Movetime = " << Movetime << std::endl;
  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

Manipulation::RETURN_ID* Manipulation_PathGeneratorInterfaceSVC_impl::JointSpaceGenerateRightArmViaMotion(const Manipulation::ViaPosSeq& viaJointPos, const Manipulation::JointAngleSeq& goalJointPos)
{
  std::cout << "JointSpaceGenerateRightArmViaMotion" << std::endl;
  
  int first=0;
  double CmdCycle;
  double MaxSpeed;
  double SpdRatio;
  double usleeptime;
  double startPos;
  double goalPos;
  double CurrentLifterPos[2];
  double CurrentWaistPos[3];
  double CurrentRightArmPos[7];
  double CurrentLeftArmPos[7];
  double CurrentLIWARJointPos[12];

  std::vector<double> Movetime;//[s]
  double AngularVelocity;
  double RotationLength[12];
  double MaxMoveJoint;
  double targetJointPos[12];

  double pathNumber;
  int numberViaPos;
  struct timeval start;
  struct timeval end;
  double sec;
  double micro;
  double duration;
  std::vector<double> viaPos;
  std::vector<double> path;
  std::vector<std::vector<double> > manippath;
  
  numberViaPos = viaJointPos.length();

  CmdCycle = m_rtcPtr->getcmdCycle();
  MaxSpeed = m_rtcPtr->getMaxSpeedJoint();
  SpdRatio = m_rtcPtr->getSpeedRatioJoint();
  AngularVelocity = MaxSpeed*SpdRatio/100;
  m_rtcPtr->getSeedCurrentJoint(CurrentLifterPos,CurrentWaistPos,CurrentRightArmPos,CurrentLeftArmPos);
  CurrentLIWARJointPos[0] = CurrentLifterPos[0];
  CurrentLIWARJointPos[1] = CurrentLifterPos[1];
  CurrentLIWARJointPos[2] = CurrentWaistPos[0];
  CurrentLIWARJointPos[3] = CurrentWaistPos[1];
  CurrentLIWARJointPos[4] = CurrentWaistPos[2];
  for(int k=0;k<7;k++)
    {
      CurrentLIWARJointPos[k+5] =  CurrentRightArmPos[k];
    }  
  
  //速度計算-現在位置とviaPos[0]================================================
  for(int q=0;q<12;q++)
    {
      RotationLength[q] = fabs(viaJointPos[0][q]-CurrentLIWARJointPos[q]);
    }

  MaxMoveJoint = RotationLength[0];
  for(int w=0;w<12;w++)
    {
      if(MaxMoveJoint<RotationLength[w]){
	MaxMoveJoint = RotationLength[w];
      }
    }
  Movetime.push_back(MaxMoveJoint/AngularVelocity);
  //viaPos[0]==========================================================

  //速度計算-viaPosとviaPos================================================
  if(numberViaPos>1)
    {
      for(int t=0;t<numberViaPos-1;t++)
	{
	  for(int y=0;y<12;y++)
	    {
	      RotationLength[y] = fabs(viaJointPos[t][y]-viaJointPos[t+1][y]);
	    }
	  
	  MaxMoveJoint = RotationLength[0];
	  for(int u=0;u<12;u++)
	    {
	      if(MaxMoveJoint<RotationLength[u]){
		MaxMoveJoint = RotationLength[u];
	      }
	    }
	  Movetime.push_back(MaxMoveJoint/AngularVelocity);
	}
    }
  //最後の点と最後のviaPos[]======================================================
  for(int p=0;p<12;p++)
    {
      RotationLength[p] = fabs(viaJointPos[numberViaPos-1][p]-goalJointPos[p]);
    }
  
  MaxMoveJoint = RotationLength[0];
  for(int a=0;a<3;a++)
    {
      if(MaxMoveJoint<RotationLength[a]){
	MaxMoveJoint = RotationLength[a];
      }
    }
  Movetime.push_back(MaxMoveJoint/AngularVelocity);

  
  double sumtime;
  //======================================================
  for(int fh=0;fh<numberViaPos+1;fh++)
    {
      pathNumber += Movetime[fh]*CmdCycle;
      sumtime += Movetime[fh];
    }
  std::cout << "pathNumber = " << pathNumber << std::endl;
  std::cout << "sumtime = " << sumtime << std::endl;
  
  for(int f=0;f<12;f++)
    {
      startPos = CurrentLIWARJointPos[f];
      goalPos = goalJointPos[f];
      for(int g=0;g<numberViaPos;g++)
	{
	  viaPos.push_back(viaJointPos[g][f]);
	}
      path.resize(pathNumber);
      m_path.pathPlanIncludeViaPos(startPos,goalPos,viaPos,path,Movetime,CmdCycle);
      manippath.push_back(path);
      viaPos.clear();
    }


  gettimeofday(&start, NULL);
  int nowPathNum=0;
  for(int k=0; k<manippath[0].size(); k++)
    {
      targetJointPos[0] = manippath[0][nowPathNum];
      targetJointPos[1] = manippath[1][nowPathNum];
      targetJointPos[2] = manippath[2][nowPathNum];
      targetJointPos[3] = manippath[3][nowPathNum];
      targetJointPos[4] = manippath[4][nowPathNum];
      targetJointPos[5] = manippath[5][nowPathNum];
      targetJointPos[6] = manippath[6][nowPathNum];
      targetJointPos[7] = manippath[7][nowPathNum];
      targetJointPos[8] = manippath[8][nowPathNum];
      targetJointPos[9] = manippath[9][nowPathNum];
      targetJointPos[10] = manippath[10][nowPathNum];
      targetJointPos[11] = manippath[11][nowPathNum];

      for(int b=0;b<12;b++)
	{
	  if(targetJointPos[b]>SeedArmJointLimit[b].Upper){
	    targetJointPos[b] = SeedArmJointLimit[b].Upper;
	  }
	  if(targetJointPos[b]<SeedArmJointLimit[b].Lower){
	    targetJointPos[b] = SeedArmJointLimit[b].Lower;
	  }
	}
      
      if(first!=0)
	{
	  gettimeofday(&end, NULL);
	  sec = (double)(end.tv_sec - start.tv_sec);
	  micro = (double)(end.tv_usec - start.tv_usec);
	  duration = sec + micro / 1000.0 / 1000.0;
	  //std::cout << "duration = " << duration <<"[s]"<<std::endl;
	  if(duration < 1/CmdCycle){
	    usleeptime = 1000*(1000/CmdCycle) - (duration * 1000*1000);
	    usleep(usleeptime);
	    //std::cout << "sleeptime = " << usleeptime/(1000*1000) << "[s]" << std::endl;
	  }
	}
      gettimeofday(&start, NULL);
      first = 1;
      m_rtcPtr->movePTPLIWARJointAbs(targetJointPos);
      nowPathNum++;
    }
  
  std::cout << "sumtime = " << sumtime << std::endl;
  std::cout << "Success" << std::endl << std::endl;
  RETURNID_OK;
}

Manipulation::RETURN_ID* Manipulation_PathGeneratorInterfaceSVC_impl::JointSpaceGenerateLeftArmMotion(const Manipulation::JointAngleSeq& goalJointPos)
{
  std::cout << "JointSpaceGenerateLeftArmMotion" << std::endl;
  
  double CmdCycle;
  double CurrentLifterPos[2];
  double CurrentWaistPos[3];
  double CurrentRightArmPos[7];
  double CurrentLeftArmPos[7];
  double CurrentLIWALJointPos[12];
  
  double Movetime;//[s]
  double MaxSpeed;
  double SpdRatio;
  double AngularVelocity;
  double RotationLength[12];
  double MaxMoveJoint;
  double targetJointPos[12];

  double pathNumber;
  //時間計測
  int first=0;
  struct timeval start;
  struct timeval end;
  double sec;
  double micro;
  double duration;

  CmdCycle = m_rtcPtr->getcmdCycle();
  MaxSpeed = m_rtcPtr->getMaxSpeedJoint();
  SpdRatio = m_rtcPtr->getSpeedRatioJoint();
  AngularVelocity = MaxSpeed*SpdRatio/100;
  m_rtcPtr->getSeedCurrentJoint(CurrentLifterPos,CurrentWaistPos,CurrentRightArmPos,CurrentLeftArmPos);

  CurrentLIWALJointPos[0] = CurrentLifterPos[0];
  CurrentLIWALJointPos[1] = CurrentLifterPos[1];
  CurrentLIWALJointPos[2] = CurrentWaistPos[0];
  CurrentLIWALJointPos[3] = CurrentWaistPos[1];
  CurrentLIWALJointPos[4] = CurrentWaistPos[2];
  for(int k=0;k<7;k++)
    {
      CurrentLIWALJointPos[k+5] =  CurrentLeftArmPos[k];
    }

  for(int k=0;k<12;k++)
    {
      RotationLength[k] = fabs(goalJointPos[k]-CurrentLIWALJointPos[k]);
    }
  MaxMoveJoint = RotationLength[0];
  for(int j=0;j<12;j++)
    {
      if(MaxMoveJoint<RotationLength[j]){
	MaxMoveJoint = RotationLength[j];    
      }
    }
  Movetime = (MaxMoveJoint/AngularVelocity);

   //=============================================================
  double startpos;
  double goalpos;
  std::vector<double> path;
  std::vector<std::vector<double> > manippath;
  for(int i=0;i<12;i++){
    startpos = CurrentLIWALJointPos[i];
    goalpos = goalJointPos[i];
    pathNumber = Movetime*CmdCycle;
    path.resize(pathNumber);
    m_path.pathPlan(startpos,goalpos,path,Movetime,CmdCycle);
    manippath.push_back(path);
  }

  gettimeofday(&start, NULL);
  int nowPathNum=0;
  double usleeptime;
  for(int f=0; f<manippath[0].size(); f++)
    {
      targetJointPos[0] = manippath[0][nowPathNum];
      targetJointPos[1] = manippath[1][nowPathNum];
      targetJointPos[2] = manippath[2][nowPathNum];
      targetJointPos[3] = manippath[3][nowPathNum];
      targetJointPos[4] = manippath[4][nowPathNum];
      targetJointPos[5] = manippath[5][nowPathNum];
      targetJointPos[6] = manippath[6][nowPathNum];
      targetJointPos[7] = manippath[7][nowPathNum];
      targetJointPos[8] = manippath[8][nowPathNum];
      targetJointPos[9] = manippath[9][nowPathNum];
      targetJointPos[10] = manippath[10][nowPathNum];
      targetJointPos[11] = manippath[11][nowPathNum];

      for(int b=0;b<12;b++)
	{
	  if(targetJointPos[b]>SeedArmJointLimit[b].Upper){
	    targetJointPos[b] = SeedArmJointLimit[b].Upper;
	  }
	  if(targetJointPos[b]<SeedArmJointLimit[b].Lower){
	    targetJointPos[b] = SeedArmJointLimit[b].Lower;
	  }
	}
      
      if(first!=0)
	{
	  gettimeofday(&end, NULL);
	  sec = (double)(end.tv_sec - start.tv_sec);
	  micro = (double)(end.tv_usec - start.tv_usec);
	  duration = sec + micro / 1000.0 / 1000.0;
	  std::cout << "duration = " << duration <<"[s]"<<std::endl;
	  if(duration < 1/CmdCycle){
	    usleeptime = 1000*(1000/CmdCycle) - (duration * 1000*1000);
	    usleep(usleeptime);
	    std::cout << "sleeptime = " << usleeptime/(1000*1000) << "[s]" << std::endl;
	  }
	}
      gettimeofday(&start, NULL);
      first = 1;
      m_rtcPtr->movePTPLIWALJointAbs(targetJointPos);
      nowPathNum++;
    }
  
  std::cout << "Movetime = " << Movetime << std::endl;
  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

Manipulation::RETURN_ID* Manipulation_PathGeneratorInterfaceSVC_impl::JointSpaceGenerateLeftArmViaMotion(const Manipulation::ViaPosSeq& viaJointPos, const Manipulation::JointAngleSeq& goalJointPos)
{
  std::cout << "JointSpaceGenerateLeftArmViaMotion" << std::endl;
  
  int first=0;
  double CmdCycle;
  double MaxSpeed;
  double SpdRatio;
  double usleeptime;
  double startPos;
  double goalPos;
  double CurrentLifterPos[2];
  double CurrentWaistPos[3];
  double CurrentRightArmPos[7];
  double CurrentLeftArmPos[7];
  double CurrentLIWALJointPos[12];

  std::vector<double> Movetime;//[s]
  double AngularVelocity;
  double RotationLength[12];
  double MaxMoveJoint;
  double targetJointPos[12];

  double pathNumber;
  int numberViaPos;
  struct timeval start;
  struct timeval end;
  double sec;
  double micro;
  double duration;
  std::vector<double> viaPos;
  std::vector<double> path;
  std::vector<std::vector<double> > manippath;
  
  numberViaPos = viaJointPos.length();

  CmdCycle = m_rtcPtr->getcmdCycle();
  MaxSpeed = m_rtcPtr->getMaxSpeedJoint();
  SpdRatio = m_rtcPtr->getSpeedRatioJoint();
  AngularVelocity = MaxSpeed*SpdRatio/100;
  m_rtcPtr->getSeedCurrentJoint(CurrentLifterPos,CurrentWaistPos,CurrentRightArmPos,CurrentLeftArmPos);
  CurrentLIWALJointPos[0] = CurrentLifterPos[0];
  CurrentLIWALJointPos[1] = CurrentLifterPos[1];
  CurrentLIWALJointPos[2] = CurrentWaistPos[0];
  CurrentLIWALJointPos[3] = CurrentWaistPos[1];
  CurrentLIWALJointPos[4] = CurrentWaistPos[2];
  for(int k=0;k<7;k++)
    {
      CurrentLIWALJointPos[k+5] =  CurrentRightArmPos[k];
    }  
  
  //速度計算-現在位置とviaPos[0]================================================
  for(int q=0;q<12;q++)
    {
      RotationLength[q] = fabs(viaJointPos[0][q]-CurrentLIWALJointPos[q]);
    }

  MaxMoveJoint = RotationLength[0];
  for(int w=0;w<12;w++)
    {
      if(MaxMoveJoint<RotationLength[w]){
	MaxMoveJoint = RotationLength[w];
      }
    }
  Movetime.push_back(MaxMoveJoint/AngularVelocity);
  //viaPos[0]==========================================================

  //速度計算-viaPosとviaPos================================================
  if(numberViaPos>1)
    {
      for(int t=0;t<numberViaPos-1;t++)
	{
	  for(int y=0;y<12;y++)
	    {
	      RotationLength[y] = fabs(viaJointPos[t][y]-viaJointPos[t+1][y]);
	    }
	  
	  MaxMoveJoint = RotationLength[0];
	  for(int u=0;u<12;u++)
	    {
	      if(MaxMoveJoint<RotationLength[u]){
		MaxMoveJoint = RotationLength[u];
	      }
	    }
	  Movetime.push_back(MaxMoveJoint/AngularVelocity);
	}
    }
  //最後の点と最後のviaPos[]======================================================
  for(int p=0;p<12;p++)
    {
      RotationLength[p] = fabs(viaJointPos[numberViaPos-1][p]-goalJointPos[p]);
    }
  
  MaxMoveJoint = RotationLength[0];
  for(int a=0;a<3;a++)
    {
      if(MaxMoveJoint<RotationLength[a]){
	MaxMoveJoint = RotationLength[a];
      }
    }
  Movetime.push_back(MaxMoveJoint/AngularVelocity);

  
  double sumtime;
  //======================================================
  for(int fh=0;fh<numberViaPos+1;fh++)
    {
      pathNumber += Movetime[fh]*CmdCycle;
      sumtime += Movetime[fh];
    }
  std::cout << "pathNumber = " << pathNumber << std::endl;
  std::cout << "sumtime = " << sumtime << std::endl;
  
  for(int f=0;f<12;f++)
    {
      startPos = CurrentLIWALJointPos[f];
      goalPos = goalJointPos[f];
      for(int g=0;g<numberViaPos;g++)
	{
	  viaPos.push_back(viaJointPos[g][f]);
	}
      path.resize(pathNumber);
      m_path.pathPlanIncludeViaPos(startPos,goalPos,viaPos,path,Movetime,CmdCycle);
      manippath.push_back(path);
      viaPos.clear();
    }


  gettimeofday(&start, NULL);
  int nowPathNum=0;
  for(int k=0; k<manippath[0].size(); k++)
    {
      targetJointPos[0] = manippath[0][nowPathNum];
      targetJointPos[1] = manippath[1][nowPathNum];
      targetJointPos[2] = manippath[2][nowPathNum];
      targetJointPos[3] = manippath[3][nowPathNum];
      targetJointPos[4] = manippath[4][nowPathNum];
      targetJointPos[5] = manippath[5][nowPathNum];
      targetJointPos[6] = manippath[6][nowPathNum];
      targetJointPos[7] = manippath[7][nowPathNum];
      targetJointPos[8] = manippath[8][nowPathNum];
      targetJointPos[9] = manippath[9][nowPathNum];
      targetJointPos[10] = manippath[10][nowPathNum];
      targetJointPos[11] = manippath[11][nowPathNum];

      for(int b=0;b<12;b++)
	{
	  if(targetJointPos[b]>SeedArmJointLimit[b].Upper){
	    targetJointPos[b] = SeedArmJointLimit[b].Upper;
	  }
	  if(targetJointPos[b]<SeedArmJointLimit[b].Lower){
	    targetJointPos[b] = SeedArmJointLimit[b].Lower;
	  }
	}
      
      if(first!=0)
	{
	  gettimeofday(&end, NULL);
	  sec = (double)(end.tv_sec - start.tv_sec);
	  micro = (double)(end.tv_usec - start.tv_usec);
	  duration = sec + micro / 1000.0 / 1000.0;
	  //std::cout << "duration = " << duration <<"[s]"<<std::endl;
	  if(duration < 1/CmdCycle){
	    usleeptime = 1000*(1000/CmdCycle) - (duration * 1000*1000);
	    usleep(usleeptime);
	    //std::cout << "sleeptime = " << usleeptime/(1000*1000) << "[s]" << std::endl;
	  }
	}
      gettimeofday(&start, NULL);
      first = 1;
      m_rtcPtr->movePTPLIWALJointAbs(targetJointPos);
      nowPathNum++;
    }
  
  std::cout << "sumtime = " << sumtime << std::endl;
  std::cout << "Success" << std::endl << std::endl;
  RETURNID_OK;
}

Manipulation::RETURN_ID* Manipulation_PathGeneratorInterfaceSVC_impl::JointSpaceGenerateDualArmMotion(const Manipulation::DualUpperJoint& goalJointPos)
{
  std::cout<<"JointSpaceGenerateDualArmMotion"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

Manipulation::RETURN_ID* Manipulation_PathGeneratorInterfaceSVC_impl::JointSpaceGenerateDualArmViaMotion(const Manipulation::ViaDualUpperJointSeq& viaJointPos, const Manipulation::DualUpperJoint& goalJointPos)
{
  std::cout<<"JointSpaceGenerateDualArmViaMotion"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}



// End of example implementational code



