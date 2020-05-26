#include <pybind11/pybind11.h>
#include "string.h"
#include "copa-sender.hh"
#include "remy-sender.hh"
#include "generic-receiver.hh"


// For Remy
double TRAINING_LINK_RATE = 4000000.0/1500.0;
bool LINK_LOGGING = false;
std::string LINK_LOGGING_FILENAME;


using namespace std;
namespace py = pybind11;

PYBIND11_MODULE(pygenericcc, m) {
    py::class_<COPASender>(m, "COPASender")
        .def(py::init<string, string, int, int>())
        .def("send", &COPASender::send);

    py::class_<Receiver>(m, "Receiver")
        .def(py::init<int>())
        .def("recvfrom", &Receiver::recvfrom);

    py::class_<REMYSender>(m, "REMYSender")
        .def(py::init<string, string, int, int>())
        .def("send", &REMYSender::send);
}