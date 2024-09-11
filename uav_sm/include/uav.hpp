#ifndef UAV_HPP_
#define UAV_HPP_

#include <tinyfsm.hpp>

#include <iostream>

// ----------------------------------------------------------------------------
// Event declarations
//

struct CommandEvent : tinyfsm::Event
{
  double val; // Active in states [TakeOff], [Hover]. Value which takes the context of the event. For Taking off, it is the height to take off to. For hover, it is the height to hover at.
  int mode; // Active in states [Mission].
};

// struct Idle    : CommandEvent { };
struct Idle_E : CommandEvent { };
struct TakeOff_E : CommandEvent { };
struct Land_E    : CommandEvent { };
struct Hover_E : CommandEvent { };
struct StartMission_E : CommandEvent { };
struct StopMission_E : CommandEvent { };
struct EmergencyStop_E : CommandEvent { };

// ----------------------------------------------------------------------------
// UAV (FSM base class) declaration
//

// forward declarations
class Unconnected;
class Idle; 
class Landing;
class TakingOff;
class Hovering; 
class Mission; 
class EmergencyStop;


class UAV
: public tinyfsm::Fsm<UAV>
{
  /* NOTE: react(), entry() and exit() functions need to be accessible
   * from tinyfsm::Fsm class. You might as well declare friendship to
   * tinyfsm::Fsm, and make these functions private:
   *
   * friend class Fsm;
   */
public:

  /* default reaction for unhandled events */
  void react(tinyfsm::Event const &) { };

  /* React() methods to be defined in each state*/
  virtual void react(Idle_E const &);
  virtual void react(TakeOff_E const &);
  virtual void react(Land_E  const &);
  virtual void react(Hover_E const &);
  virtual void react(StartMission_E const &);
  virtual void react(StopMission_E const &);

  // Emergency stop react() method is default for all states 
  void         react(EmergencyStop_E  const &);

  virtual void entry(void) { };  /* entry actions in some states */
  void         exit(void)  { };  /* no exit actions at all */

protected:

  // static constexpr int initial_floor = 0;
  // static int current_floor;
  // static int dest_floor;
};


// ----------------------------------------------------------------------------
// State: Unconnected
//    Reacts to: Idle_E
//

class Unconnected
: public UAV
{
  void entry() override {
    std::cout<< "Entered Unconnected " << std::endl;
    // Do nothing, wait for connection to Flight Controller Unit
  }

  void react(Idle_E const & e) override {
    // Connected to PX4
    transit<Idle>();
  };
};

// ----------------------------------------------------------------------------
// State: Idle
//    Reacts to: TakeOff_E
//

class Idle
: public UAV
{
  void entry() override {
    std::cout<< "Entered Idle " << std::endl;
    // Disarm
    // MotorDisarm()
  }

  void react(TakeOff_E const & e) override {
    transit<TakingOff>();
  };

};

// ----------------------------------------------------------------------------
// State: Landing
//    Reacts to: Idle_E
//

class Landing
: public UAV
{
  void entry() override {
    std::cout<< "Entered Landing " << std::endl;
    // send_event(MotorLand());
  }

  void react(Idle_E const & e) override {
    transit<Idle>();
  };

};

// ----------------------------------------------------------------------------
// State: TakingOff
//    Reacts to: Land_E, Hover_E
//

class TakingOff
: public UAV
{
  void entry() override {
    std::cout<< "Entered TakingOff " << std::endl;
    // send_event(MotorArm());
    // send_event(MotorTakeOff());
  }

  void react(Land_E const & e) override {
    transit<Landing>();
  };

  void react(Hover_E const & e) override {
    transit<Hovering>();
  };

};

// ----------------------------------------------------------------------------
// State: Hovering
//    Reacts to: Land_E, StartMission_E
//

class Hovering
: public UAV
{
  void entry() override {
    std::cout<< "Entered Hovering " << std::endl;
    // send_event(MotorHover());
  }

  void react(Land_E const & e) override {
    transit<Landing>();
  };

  void react(StartMission_E const & e) override {
    transit<Mission>();
  };
};


// ----------------------------------------------------------------------------
// State: Mission
//    Reacts to: Land_E, StopMission_E
//

class Mission
: public UAV
{
  void entry() override {
    std::cout<< "Entered Mission " << std::endl;
    // send_event(MotorMission());
  }

  void react(Land_E const & e) override {
    transit<Landing>();
  };

  void react(StopMission_E const & e) override {
    transit<Hovering>();
  };
};


// ----------------------------------------------------------------------------
// State: EmergencyStop
//    Reacts to: 
//

class EmergencyStop
: public UAV
{
  void entry() override {
    std::cout<< "Entered EmergencyStop " << std::endl;
    // send_event(MotorEmergencyStop());
  }
};

// ----------------------------------------------------------------------------
// Event dispatch
//

using fsm_list = tinyfsm::FsmList<UAV>;


/** dispatch event to "UAV" */
template<typename E>
void sendEvent(E const & event)
{
  fsm_list::template dispatch<E>(event);
}




#endif //UAV_HPP_
