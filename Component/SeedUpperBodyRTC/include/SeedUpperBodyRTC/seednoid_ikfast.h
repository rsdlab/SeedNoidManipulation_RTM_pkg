#ifndef _SEEDNOID_IKFAST_H
#define _SEEDNOID_IKFAST_H

#include "ikfast.h"

typedef double IkReal;


namespace IKFAST_WR_VIRTUAL{

  IKFAST_API int ik_solve(IkReal eerot[9], IkReal eetrans[3], std::vector<std::vector<IkReal> >& sol_joint, std::vector<IkReal> free_joint, int *NumSolutions);

  IKFAST_API bool ComputeIk(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions);
  
  /** \brief Similar to ComputeIk except takes OpenRAVE boost::shared_ptr<RobotBase::Manipulator>*
   */
  IKFAST_API bool ComputeIk2(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions, void* pOpenRAVEManip);
  
  /// \brief Computes the end effector coordinates given the joint values. This function is used to double check ik.
  IKFAST_API void ComputeFk(const IkReal* joints, IkReal* eetrans, IkReal* eerot);
  
  /// \brief returns the number of free parameters users has to set apriori
  IKFAST_API int GetNumFreeParameters();

  /// \brief the indices of the free parameters indexed by the chain joints
  IKFAST_API int* GetFreeParameters();

  /// \brief the total number of indices of the chain
  IKFAST_API int GetNumJoints();

  /// \brief the size in bytes of the configured number type
  IKFAST_API int GetIkRealSize();

  /// \brief the ikfast version used to generate this file
  IKFAST_API const char* GetIkFastVersion();

  /// \brief the ik type ID
  IKFAST_API int GetIkType();

  /// \brief a hash of all the chain values used for double checking that the correct IK is used.
  IKFAST_API const char* GetKinematicsHash();
}

namespace IKFAST_WR_REAL{

   IKFAST_API int ik_solve(IkReal eerot[9], IkReal eetrans[3], std::vector<std::vector<IkReal> >& sol_joint, std::vector<IkReal> free_joint, int *NumSolutions);
  IKFAST_API bool ComputeIk(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions);
  IKFAST_API bool ComputeIk2(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions, void* pOpenRAVEManip);
  IKFAST_API void ComputeFk(const IkReal* joints, IkReal* eetrans, IkReal* eerot);
  IKFAST_API int GetNumFreeParameters();
  IKFAST_API int* GetFreeParameters();
  IKFAST_API int GetNumJoints();
  IKFAST_API int GetIkRealSize();
  IKFAST_API const char* GetIkFastVersion();
  IKFAST_API int GetIkType();
  IKFAST_API const char* GetKinematicsHash();
}

namespace IKFAST_WL_VIRTUAL{

   IKFAST_API int ik_solve(IkReal eerot[9], IkReal eetrans[3], std::vector<std::vector<IkReal> >& sol_joint, std::vector<IkReal> free_joint, int *NumSolutions);
  IKFAST_API bool ComputeIk(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions);
  IKFAST_API bool ComputeIk2(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions, void* pOpenRAVEManip);
  IKFAST_API void ComputeFk(const IkReal* joints, IkReal* eetrans, IkReal* eerot);
  IKFAST_API int GetNumFreeParameters();
  IKFAST_API int* GetFreeParameters();
  IKFAST_API int GetNumJoints();
  IKFAST_API int GetIkRealSize();
  IKFAST_API const char* GetIkFastVersion();
  IKFAST_API int GetIkType();
  IKFAST_API const char* GetKinematicsHash();
}

namespace IKFAST_WL_REAL{

   IKFAST_API int ik_solve(IkReal eerot[9], IkReal eetrans[3], std::vector<std::vector<IkReal> >& sol_joint, std::vector<IkReal> free_joint, int *NumSolutions);
  IKFAST_API bool ComputeIk(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions);
  IKFAST_API bool ComputeIk2(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions, void* pOpenRAVEManip);
  IKFAST_API void ComputeFk(const IkReal* joints, IkReal* eetrans, IkReal* eerot);
  IKFAST_API int GetNumFreeParameters();
  IKFAST_API int* GetFreeParameters();
  IKFAST_API int GetNumJoints();
  IKFAST_API int GetIkRealSize();
  IKFAST_API const char* GetIkFastVersion();
  IKFAST_API int GetIkType();
  IKFAST_API const char* GetKinematicsHash();
}

namespace IKFAST_VIRTUAL{

   IKFAST_API int right_ik_solve(IkReal eerot[9], IkReal eetrans[3], std::vector<std::vector<IkReal> >& sol_joint, std::vector<IkReal> free_joint, int *NumSolutions);
   IKFAST_API int left_ik_solve(IkReal eerot[9], IkReal eetrans[3], std::vector<std::vector<IkReal> >& sol_joint, std::vector<IkReal> free_joint, int *NumSolutions);
  IKFAST_API bool ComputeIk(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions);
  IKFAST_API bool ComputeIk2(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions, void* pOpenRAVEManip);
  IKFAST_API void ComputeFk(const IkReal* joints, IkReal* eetrans, IkReal* eerot);
  IKFAST_API int GetNumFreeParameters();
  IKFAST_API int* GetFreeParameters();
  IKFAST_API int GetNumJoints();
  IKFAST_API int GetIkRealSize();
  IKFAST_API const char* GetIkFastVersion();
  IKFAST_API int GetIkType();
  IKFAST_API const char* GetKinematicsHash();
}

namespace IKFAST_REAL{

   IKFAST_API int right_ik_solve(IkReal eerot[9], IkReal eetrans[3], std::vector<std::vector<IkReal> >& sol_joint, std::vector<IkReal> free_joint, int *NumSolutions);
   IKFAST_API int left_ik_solve(IkReal eerot[9], IkReal eetrans[3], std::vector<std::vector<IkReal> >& sol_joint, std::vector<IkReal> free_joint, int *NumSolutions);
   IKFAST_API bool ComputeIk(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions);
  IKFAST_API bool ComputeIk2(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, ikfast::IkSolutionListBase<IkReal>& solutions, void* pOpenRAVEManip);
  IKFAST_API void ComputeFk(const IkReal* joints, IkReal* eetrans, IkReal* eerot);
  IKFAST_API int GetNumFreeParameters();
  IKFAST_API int* GetFreeParameters();
  IKFAST_API int GetNumJoints();
  IKFAST_API int GetIkRealSize();
  IKFAST_API const char* GetIkFastVersion();
  IKFAST_API int GetIkType();
  IKFAST_API const char* GetKinematicsHash();
}



#endif // _SEEDNOID_IKFAST_H
