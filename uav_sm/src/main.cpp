#include <uav.hpp>
#include <motor_callback.hpp>

#include <iostream>

// States are derived classes from a base FSM state
//      react():    Events are passed to react()
//      entry()
//      exit()

// Event dispatching
//      TinyFSM does not hold state/event function tables 
//      Instead, it keeps a pointer to the current state
//      Dispatching an event simple calls the react() function
//      of the current state, with the event class as argument
//
//      Event dispatching on an FsmList<> are simply dispatch() calls 
//      to all state machines in the list.

// 1. Declare events
//      declare events your SM will listen to.

// 2. Declare the state machine class

// 3. Declare the states

// 4. Implement actions and event reactions

//      1. Change some local data
//      2. Send events to other state machines
//      3. Transit to different state
//
//      Important: Make sure that the transit<>() function call is the last command executed within a reaction function!
//      Important: Don't use transit<>() in entry/exit actions!

// 5. Define the Initial State
//      Use the macro FSM_INITIAL_STATE(fsm, state) for defining the 
//      initial state (or "start state") of your state machine:
//          Example: FSM_INITIAL_STATE(Elevator, Idle)

// 6.. Use function template

// declare function
// template<typename F>
// dispatcherAndDecisionMakingFunction(void) {
//     F::staticStateMachineFunction(void);
// }
// // call function
// dispatcherAndDecisionMakingFunction<MyStateMachine>();

class TrajectoryServer
{
public:
  TrajectoryServer(){};

  void init(){
    // start UAV state machine
    fsm_list::start();

    auto getState = [&]()
    {
      // Check all states
      if (UAV::is_in_state<Unconnected>()){
        std::cout << "Unconnected" << std::endl;
        return;
      }
      else if (UAV::is_in_state<Idle>()){
        std::cout << "Idle" << std::endl;
        return;
      }
      else if (UAV::is_in_state<Landing>()){
        std::cout << "Landing" << std::endl;
        return;
      }
      else if (UAV::is_in_state<TakingOff>()){
        std::cout << "TakingOff" << std::endl;
        return;
      }
      else if (UAV::is_in_state<Hovering>()){
        std::cout << "Hovering" << std::endl;
        return;
      }
      else if (UAV::is_in_state<Mission>()){
        std::cout << "Mission" << std::endl;
        return;
      }
      else if (UAV::is_in_state<EmergencyStop>()){
        std::cout << "EmergencyStop" << std::endl;
        return;
      }
      else {
        std::cout << "Undefined UAV state" << std::endl;
        return;
      }
      // std::cout << fsm_list::fsmtype::current_state_ptr << std::endl;
      // std::cout << UAV::is_in_state<Unconnected>() << std::endl;
    };
    std::function<void(void)> get_state = getState;

    // Start timer thread
    callback_timer.start(1000, get_state);
  };

private:
    CallbackTimer callback_timer;

};  // class TrajectoryServer

int main()
{
  TrajectoryServer traj_server;

  traj_server.init();

  while(1)
  {
    char c;

    std::cout << "a=Initialize, b=TakeOff, c=EmergencyStop, q=Quit ? ";
    std::cin >> c;
    switch(c) {
    case 'a':
      sendEvent(Idle_E());
      break;
    case 'b':
      sendEvent(TakeOff_E());
      break;
    case 'c':
      sendEvent(EmergencyStop_E());
      break;
    case 'q':
      std::cout << "Thanks for playing!" << std::endl;
      return 0;
    default:
      std::cout << "Invalid input" << std::endl;
    };
  }
  
}