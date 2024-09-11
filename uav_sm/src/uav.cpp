#include <uav.hpp>

#include <iostream>

// ----------------------------------------------------------------------------
// Transition functions
//

// static void CallMaintenance() {
//   std::cout << "*** calling maintenance ***" << std::endl;
// }

// ----------------------------------------------------------------------------
// Base state: default implementations
//

void UAV::react(Idle_E const &) {
  std::cout << "Initialize event ignored" << std::endl;
}

void UAV::react(TakeOff_E const &) {
  std::cout << "TakeOff event ignored" << std::endl;
}

void UAV::react(Land_E const &) {
  std::cout << "Land event ignored" << std::endl;
}

void UAV::react(Hover_E const &) {
  std::cout << "Hover event ignored" << std::endl;
}

void UAV::react(StartMission_E const &) {
  std::cout << "Start mission event ignored" << std::endl;
}

void UAV::react(StopMission_E const &) {
  std::cout << "Stop mission event ignored" << std::endl;
}

void UAV::react(EmergencyStop_E const &) {
  std::cout << "Emergency stop engaged!" << std::endl;
  transit<EmergencyStop>();
}

// int UAV::current_floor = UAV::initial_floor;
// int UAV::dest_floor    = UAV::initial_floor;

// ----------------------------------------------------------------------------
// Initial state definition
//
FSM_INITIAL_STATE(UAV, Unconnected)
