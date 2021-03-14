#include "OccupationLaw.h"

using namespace std;

OccupationLaw::OccupationLaw(double new_compli, double new_factory, string new_name){
  compliance_gain = new_compli;
  factory_percent_modifier = new_factory;
  name = new_name;
}

