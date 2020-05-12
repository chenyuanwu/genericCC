#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include "string.h"
#include "copa-sender.hh"
#include "generic-receiver.hh"

//using namespace std;
//namespace py = pybind11;
//
//PYBIND11_MODULE(pygenericCC, m) {
//    py::class_<COPASender>(m, "COPASender")
//        .def(py::init<string, int, int>())
//        .def("send", &COPASender::send);
//
//    py::class_<Receiver>(m, "Receiver")
//        .def(py::init<int>())
//        .def("recvfrom", &Receiver::recvfrom);
//}

BOOST_PYTHON_MODULE(pygenericcc){
    using namespace boost::python;
    class_<COPASender>("COPASender", init<std::string, int, int>())
      .def("send", &COPASender::send);
}