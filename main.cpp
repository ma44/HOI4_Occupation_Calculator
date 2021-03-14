#include <iostream>
#include <vector>
#include <tgmath.h>
#include <algorithm>
#include "OccupationLaw.h"

//Base gain of 0.08, hoi4 vanilla, goes from this to -0.08 based on 0-100% current compliance
#define BASE_COMPLIANCE_GAIN 0.08

//Any other sources of flat compliance game like WARDEN, Handdogs, Santa Anna etc, non-core manpower laws ETC.
#define ADDITIONAL_COMPLIANCE_GAIN 0.000

//Number of factories being occupied for test run
#define OCCUPIED_FACTORIES 100

//Number of days to run the simulation for
#define DAYS_SIMULATED 365 * 3

//Switches to sporadic outposts at this compliance level %
#define SPORADIC_AT_COMPLIANCE 80

int main() {

  /*
  Occupation laws and effects initialization
  Parameters are; daily compliance gain, -% factories from occupation and occupation name
  */

  OccupationLaw sporadic_outposts_occupation = OccupationLaw(0.05, -0.1, "sporadic outposts");
  OccupationLaw caravan_guards_occupation = OccupationLaw(0.10, -0.3, "caravan guards");
  OccupationLaw road_patrols_occupation = OccupationLaw(0.15, -0.5, "road patrols");
  OccupationLaw extensive_patrols_occupation = OccupationLaw(0.20, -0.7, "extensive patrols");
  OccupationLaw wasteland_pacification_occupation = OccupationLaw(0.25, -0.9, "wasteland pacify");

  //For loops
  vector<OccupationLaw> OccupationLaws;
  OccupationLaws.push_back(sporadic_outposts_occupation); OccupationLaws.push_back(caravan_guards_occupation); OccupationLaws.push_back(road_patrols_occupation); OccupationLaws.push_back(extensive_patrols_occupation); OccupationLaws.push_back(wasteland_pacification_occupation);

  double compliance_overall;
  double next_compli_benchmark;
  int active_factories_in_days;

  cout << "Simulating " << DAYS_SIMULATED << " days of occupation when occupying " << OCCUPIED_FACTORIES << " factories." << endl;

  for(OccupationLaw law : OccupationLaws){
    compliance_overall = 0.00;
    active_factories_in_days = 0;
    next_compli_benchmark = 0.00;
    for(int i = 1; i < DAYS_SIMULATED; i++){
      compliance_overall += ADDITIONAL_COMPLIANCE_GAIN;
      compliance_overall += law.compliance_gain;
      compliance_overall += BASE_COMPLIANCE_GAIN - ((BASE_COMPLIANCE_GAIN * compliance_overall) / 100);
      compliance_overall = std::fmin(compliance_overall, 100);

      if(law.compliance_gain != 0.05 &&  compliance_overall >= SPORADIC_AT_COMPLIANCE){
        law.compliance_gain = 0.05;
        law.factory_percent_modifier = -0.1;
        cout << "Swapped to sporadic outposts with factory days accumulated at " << active_factories_in_days << ", taking " << i << " days to reach occupation law swap trigger." << endl;
      }

      active_factories_in_days += std::fmax(floor(OCCUPIED_FACTORIES * (law.factory_percent_modifier + 1 - 0.75  + (0.65 * (compliance_overall / 100)))), 0);
      }

    std::cout << "Finished processing of " << law.name << endl;
    std::cout << "Compliance level of " << compliance_overall << endl;
    std::cout << "Total factory output in days of working; " << active_factories_in_days << "\n==============\n";

    }


}