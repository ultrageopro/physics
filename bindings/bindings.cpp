#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <physics/units/quantity.hpp>
#include <physics/vector/vector.hpp>
#include <physics/object/object.hpp>
#include <physics/formulas/mech.hpp>
#include <physics/formulas/gravity.hpp>

namespace py = pybind11;

template <typename T, size_t N>
void bind_vector(py::module_ &m, const std::string &name) {
  using Vec = physics::vector::Vector<T, N>;
  py::class_<Vec>(m, name.c_str())
      .def(py::init([](py::object iterable) {
        Vec v;
        auto seq = py::cast<py::sequence>(iterable);

        if (seq.size() != N) {
          throw std::runtime_error("Vector length must be exactly " + std::to_string(N));
        }

        for (size_t i = 0; i < N; i++) {
          v[i] = seq[i].cast<T>();
        }
        return v;
      }))
      .def("size", &Vec::Size)
      .def("__getitem__", [](const Vec &v, size_t i) { return v[i]; })
      .def("__setitem__", [](Vec &v, size_t i, const T &x) { v[i] = x; })
      .def("__repr__",
           [name](const Vec &v) {
             std::stringstream ss;
             ss << name << "(";
             for (size_t i = 0; i < N; i++) {
               if constexpr (physics::units::kIsQuantityV<T>) {
                 ss << v.data[i].value;
               } else {
                 ss << v.data[i];
               }
               if (i + 1 < N) {
                 ss << ", ";
               }
             }
             ss << ")";
             return ss.str();
           })
      .def("__add__", [](const Vec &a, const Vec &b) { return a + b; })
      .def("__sub__", [](const Vec &a, const Vec &b) { return a - b; })
      .def("dot", &physics::vector::Dot<T, N>)
      .def("norm", &physics::vector::Norm<T, N>)
      .def("normalize", &physics::vector::Normalize<T, N>);
}

void bind_quantities(py::module_ &m) {
  py::class_<physics::units::Quantity<0, 0, 0>>(m, "Dimensionless")
      .def(py::init<double>())
      .def_readwrite("value", &physics::units::Quantity<0, 0, 0>::value)
      .def("__repr__", [](const physics::units::Quantity<0, 0, 0> &q) { return "Dimensionless(" + std::to_string(q.value) + ")"; });

  py::class_<physics::units::Length>(m, "Length").def(py::init<double>()).def_readwrite("value", &physics::units::Length::value);
  py::class_<physics::units::Mass>(m, "Mass").def(py::init<double>()).def_readwrite("value", &physics::units::Mass::value);
  py::class_<physics::units::Speed>(m, "Speed").def(py::init<double>()).def_readwrite("value", &physics::units::Speed::value);
  py::class_<physics::units::Acceleration>(m, "Acceleration").def(py::init<double>()).def_readwrite("value", &physics::units::Acceleration::value);
  py::class_<physics::units::Force>(m, "Force").def(py::init<double>()).def_readwrite("value", &physics::units::Force::value);
  py::class_<physics::units::Energy>(m, "Energy").def(py::init<double>()).def_readwrite("value", &physics::units::Energy::value);

  m.def("scalar", &physics::units::ScalarValue<double>, "Extract raw value");
}

void bind_object(py::module_ &m) {
  py::class_<physics::object::Object>(m, "Object")
      .def(py::init<physics::units::Mass, physics::vector::Vector<physics::units::Length, 3>, physics::vector::Vector<physics::units::Speed, 3>,
                    physics::vector::Vector<physics::units::Acceleration, 3>>(),
           py::arg("mass"), py::arg("position") = physics::vector::Vector<physics::units::Length, 3>{},
           py::arg("speed") = physics::vector::Vector<physics::units::Speed, 3>{},
           py::arg("acceleration") = physics::vector::Vector<physics::units::Acceleration, 3>{})
      .def_readwrite("mass", &physics::object::Object::mass)
      .def_readwrite("position", &physics::object::Object::position)
      .def_readwrite("speed", &physics::object::Object::speed)
      .def_readwrite("acceleration", &physics::object::Object::acceleration)
      .def("distance_to", &physics::object::Object::DistanceTo)
      .def("direction_to", &physics::object::Object::DirectionTo)
      .def("gravity_force", &physics::object::Object::GravitationalForceVector)
      .def("gravity_magnitude", &physics::object::Object::GravitationalForceMagnitude);
}

void bind_mechanics(py::module_ &m) {
  m.def("kinetic_energy", &physics::mech::KineticEnergy);
  m.def("potential_energy", &physics::mech::PotentialEnergy);
  m.def("work", &physics::mech::Work);
  m.def("momentum", &physics::mech::Momentum);
}

PYBIND11_MODULE(_core, m) {
  m.doc() = "Python bindings for the Physics engine";

  bind_quantities(m);

  bind_vector<double, 3>(m, "Vector3d");
  bind_vector<physics::units::Length, 3>(m, "Vector3Length");
  bind_vector<physics::units::Acceleration, 3>(m, "Vector3Acceleration");
  bind_vector<physics::units::Speed, 3>(m, "Vector3Speed");
  bind_vector<physics::units::Force, 3>(m, "Vector3Force");

  bind_mechanics(m);
  bind_object(m);
}