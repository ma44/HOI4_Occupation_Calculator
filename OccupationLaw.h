#include <string>

using namespace std;

class OccupationLaw 
{ 
public:
  OccupationLaw(double new_gain, double new_factory, string new_name);
  double compliance_gain;
  double factory_percent_modifier;
  string name;
};
 
