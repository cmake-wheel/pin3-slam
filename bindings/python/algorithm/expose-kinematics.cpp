//
// Copyright (c) 2015-2020 CNRS INRIA
//

#include "pinocchio/bindings/python/algorithm/algorithms.hpp"
#include "pinocchio/algorithm/kinematics.hpp"

namespace pinocchio
{
  namespace python
  {

    BOOST_PYTHON_FUNCTION_OVERLOADS(getVelocity_overload, (getVelocity<context::Scalar,context::Options,JointCollectionDefaultTpl>), 3, 4)
    BOOST_PYTHON_FUNCTION_OVERLOADS(getAcceleration_overload, (getAcceleration<context::Scalar,context::Options,JointCollectionDefaultTpl>), 3, 4)
    BOOST_PYTHON_FUNCTION_OVERLOADS(getClassicalAcceleration_overload, (getClassicalAcceleration<context::Scalar,context::Options,JointCollectionDefaultTpl>), 3, 4)

    void exposeKinematics()
    {
      typedef context::Scalar Scalar;
      typedef context::VectorXs VectorXs;
      enum { Options = context::Options };
      
      bp::def("updateGlobalPlacements",
              &updateGlobalPlacements<Scalar,Options,JointCollectionDefaultTpl>,
              bp::args("model","data"),
              "Updates the global placements of all joint frames of the kinematic "
              "tree and store the results in data according to the relative placements of the joints.\n\n"
              "Parameters:\n"
              "\tmodel: model of the kinematic tree\n"
              "\tdata: data related to the model\n");

      bp::def("getVelocity",
              &getVelocity<Scalar,Options,JointCollectionDefaultTpl>,
              getVelocity_overload(
                bp::args("model","data","joint_id","reference_frame"),
                "Returns the spatial velocity of the joint expressed in the coordinate system given by reference_frame.\n"
                "forwardKinematics(model,data,q,v[,a]) should be called first to compute the joint spatial velocity stored in data.v"));

      bp::def("getAcceleration",
              &getAcceleration<Scalar,Options,JointCollectionDefaultTpl>,
              getAcceleration_overload(
                bp::args("model","data","joint_id","reference_frame"),
                "Returns the spatial acceleration of the joint expressed in the coordinate system given by reference_frame.\n"
                "forwardKinematics(model,data,q,v,a) should be called first to compute the joint spatial acceleration stored in data.a ."));

      bp::def("getClassicalAcceleration",
              &getClassicalAcceleration<Scalar,Options,JointCollectionDefaultTpl>,
              getClassicalAcceleration_overload(
                bp::args("model","data","joint_id","reference_frame"),
                "Returns the \"classical\" acceleration of the joint expressed in the coordinate system given by reference_frame.\n"
                "forwardKinematics(model,data,q,v,a) should be called first to compute the joint spatial acceleration stored in data.a ."));

      bp::def("forwardKinematics",
              &forwardKinematics<Scalar,Options,JointCollectionDefaultTpl,VectorXs>,
              bp::args("model","data","q"),
              "Compute the global placements of all the joints of the kinematic "
              "tree and store the results in data.\n\n"
              "Parameters:\n"
              "\tmodel: model of the kinematic tree\n"
              "\tdata: data related to the model\n"
              "\tq: the joint configuration vector (size model.nq)\n");
      
      bp::def("forwardKinematics",
              &forwardKinematics<Scalar,Options,JointCollectionDefaultTpl,VectorXs,VectorXs>,
              bp::args("model","data","q","v"),
              "Compute the global placements and local spatial velocities of all the joints of the kinematic "
              "tree and store the results in data.\n\n"
              "Parameters:\n"
              "\tmodel: model of the kinematic tree\n"
              "\tdata: data related to the model\n"
              "\tq: the joint configuration vector (size model.nq)\n"
              "\tv: the joint velocity vector (size model.nv)\n");
      
      bp::def("forwardKinematics",
              &forwardKinematics<Scalar,Options,JointCollectionDefaultTpl,VectorXs,VectorXs,VectorXs>,
              bp::args("model","data","q","v","a"),
              "Compute the global placements, local spatial velocities and spatial accelerations of all the joints of the kinematic "
              "tree and store the results in data.\n\n"
              "Parameters:\n"
              "\tmodel: model of the kinematic tree\n"
              "\tdata: data related to the model\n"
              "\tq: the joint configuration vector (size model.nq)\n"
              "\tv: the joint velocity vector (size model.nv)\n"
              "\ta: the joint acceleration vector (size model.nv)\n");
    }
    
  } // namespace python
} // namespace pinocchio
