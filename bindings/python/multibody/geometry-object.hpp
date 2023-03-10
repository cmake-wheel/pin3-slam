//
// Copyright (c) 2017-2020 CNRS INRIA
//

#ifndef __pinocchio_python_geometry_object_hpp__
#define __pinocchio_python_geometry_object_hpp__

#include <boost/python.hpp>
#include <eigenpy/memory.hpp>
#include <eigenpy/eigen-to-python.hpp>
#include "pinocchio/bindings/python/utils/registration.hpp"
#include "pinocchio/bindings/python/utils/deprecation.hpp"


#include "pinocchio/multibody/geometry.hpp"

EIGENPY_DEFINE_STRUCT_ALLOCATOR_SPECIALIZATION(pinocchio::GeometryObject)

namespace pinocchio
{
  namespace python
  {
    namespace bp = boost::python;

    struct GeometryObjectPythonVisitor
    : public boost::python::def_visitor< GeometryObjectPythonVisitor >
    {
      typedef GeometryObject::CollisionGeometryPtr CollisionGeometryPtr;

      template<class PyClass>
      void visit(PyClass& cl) const
      {
        cl
        .def(bp::init<std::string,JointIndex,FrameIndex,SE3,CollisionGeometryPtr,
                      bp::optional<std::string,Eigen::Vector3d,bool,Eigen::Vector4d,std::string> >
             (
             bp::args("self","name","parent_joint","parent_frame","placement","collision_geometry",
                       "mesh_path", "mesh_scale", "override_material", "mesh_color", "mesh_texture_path"),
             "Full constructor of a GeometryObject."))
        .def(bp::init<std::string,JointIndex,SE3,CollisionGeometryPtr,
                      bp::optional<std::string,Eigen::Vector3d,bool,Eigen::Vector4d,std::string> >
             (
              bp::args("self","name","parent_joint","placement","collision_geometry",
                        "mesh_path", "mesh_scale", "override_material", "mesh_color", "mesh_texture_path"),
              "Reduced constructor of a GeometryObject. This constructor does not require to specify the parent frame index."
              ))
        .def(bp::init<std::string,FrameIndex,JointIndex,CollisionGeometryPtr,SE3,
                      bp::optional<std::string,Eigen::Vector3d,bool,Eigen::Vector4d,std::string> >
             (
             bp::args("self","name","parent_frame","parent_joint","collision_geometry",
                      "placement", "mesh_path", "mesh_scale", "override_material", "mesh_color", "mesh_texture_path"),
             "Deprecated. Full constructor of a GeometryObject.")[deprecated_function<>()] )
        .def(bp::init<std::string,JointIndex,CollisionGeometryPtr,SE3,
                      bp::optional<std::string,Eigen::Vector3d,bool,Eigen::Vector4d,std::string> >
             (
              bp::args("self","name","parent_joint","collision_geometry",
                       "placement", "mesh_path", "mesh_scale", "override_material", "mesh_color", "mesh_texture_path"),
              "Deprecated. Reduced constructor of a GeometryObject. This constructor does not require to specify the parent frame index."
              )[deprecated_function<>()] )
        .def(bp::init<const GeometryObject&>
             (
              bp::args("self","otherGeometryObject"),
              "Copy constructor"
              ))
        .def_readwrite("meshScale",&GeometryObject::meshScale,
                       "Scaling parameter of the mesh.")
        .add_property("meshColor",
                      bp::make_getter(&GeometryObject::meshColor,
                                      bp::return_value_policy<bp::return_by_value>()),
                      bp::make_setter(&GeometryObject::meshColor),
                      "Color rgba of the mesh.")
        .def_readwrite("geometry", &GeometryObject::geometry,
                       "The FCL CollisionGeometry associated to the given GeometryObject.")
        .def_readwrite("name", &GeometryObject::name,
                       "Name associated to the given GeometryObject.")
        .def_readwrite("parentJoint", &GeometryObject::parentJoint,
                       "Index of the parent joint.")
        .def_readwrite("parentFrame", &GeometryObject::parentFrame,
                       "Index of the parent frame.")
        .def_readwrite("placement",&GeometryObject::placement,
                       "Position of geometry object in parent joint's frame.")
        .def_readwrite("meshPath", &GeometryObject::meshPath,
                       "Path to the mesh file.")
        .def_readwrite("overrideMaterial", &GeometryObject::overrideMaterial,
                       "Boolean that tells whether material information is stored inside the given GeometryObject.")
        .def_readwrite("meshTexturePath", &GeometryObject::meshTexturePath,
                       "Path to the mesh texture file.")
        .def_readwrite("disableCollision", &GeometryObject::disableCollision,
                       "If true, no collision or distance check will be done between the Geometry and any other geometry.")

        .def(bp::self == bp::self)
        .def(bp::self != bp::self)

#ifdef PINOCCHIO_WITH_HPP_FCL
          .def("CreateCapsule", &GeometryObjectPythonVisitor::maker_capsule)
          .staticmethod("CreateCapsule")
#endif // PINOCCHIO_WITH_HPP_FCL
        ;
      }

#ifdef PINOCCHIO_WITH_HPP_FCL
      static GeometryObject maker_capsule(const double radius, const double length)
      {
        return GeometryObject("",JointIndex(0),FrameIndex(0),
                              SE3::Identity(),
                              std::shared_ptr<fcl::CollisionGeometry>(new fcl::Capsule(radius, length)));

      }
#endif // PINOCCHIO_WITH_HPP_FCL

      static void expose()
      {
        if(!register_symbolic_link_to_registered_type<GeometryObject>())
        {
          bp::class_<GeometryObject>("GeometryObject",
                                     "A wrapper on a collision geometry including its parent joint, parent frame, placement in parent joint's frame.\n\n",
                                     bp::no_init
                                     )
          .def(GeometryObjectPythonVisitor())
          ;
        }

        if(!register_symbolic_link_to_registered_type<GeometryType>())
        {
          bp::enum_<GeometryType>("GeometryType")
          .value("VISUAL",VISUAL)
          .value("COLLISION",COLLISION)
          .export_values()
          ;
        }
      }

    };


  } // namespace python
} // namespace pinocchio

#endif // ifndef __pinocchio_python_geometry_object_hpp__
