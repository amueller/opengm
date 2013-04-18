#ifdef WITH_TRWS
#include <boost/python.hpp>
#include <string>
#include "inf_def_visitor.hxx"

#include <opengm/inference/external/trws.hxx>
#include <param/trws_external_param.hxx>

template<class GM,class ACC>
void export_trws(){
   using namespace boost::python;
   import_array();
   append_subnamespace("solver");

   // setup 
   InfSetup setup;
   setup.algType    = "message-passing";
   setup.examples   = ">>> parameter = opengm.InfParam(steps=100)\n"
                      ">>> inference = opengm.inference.TrwsExternal(gm=gm,accumulator='minimizer',parameter=parameter)\n"; 
                      "\n\n";
   setup.dependencies = "This algorithm needs the Trws library from ??? , " 
                        "compile OpenGM with CMake-Flag ``WITH_TRWS` set to ``ON`` ";
   // export parameter
   typedef opengm::external::TRWS<GM>  PyTrws; 
   exportInfParam<exportTag::NoSubInf,PyTrws>("_TrwsExternal");
   // export inference
   class_< PyTrws>("_TrwsExternal",init<const GM & >())  
   .def(InfSuite<PyTrws,false>(std::string("TrwsExternal"),setup))
   ;
}

template void export_trws<GmAdder,opengm::Minimizer>();

#endif //WITH_TRWS