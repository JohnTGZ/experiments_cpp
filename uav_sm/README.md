# uav_sm 
State machine prototype for a quadrotor

```bash
cd build
cmake .. && make && ./main
```


## UAV State Machine
Events available: 
- Idle_E
- TakeOff_E
- Land_E
- Hover_E
- StartMission_E
- StopMission_E
- EmergencyStop_E

States available:
- Unconnected
- Idle
- Landed
- Hovering
- Takingoff
- Mission
- EmergencyStop

# Structure
We will use the following components:
1. Internally kept UAV State machine (UAVSM)
2. Periodic timer to query the actual state of the MAV, send motor commands to the MAV and send events to the UAVSM.  