# OpenParallelGripper Software
## Software part is under development so you may need some effort to work this gripper.

## Summary
To control the gripper, you need to use either digital inputs from tool IO of LITE 6 or Modbus-RTU through RS485 of tool IO of LITE 6.


## Requirement

### Arduino IDE

- Modbus-RTU Library (https://github.com/emelianov/modbus-esp8266)
- DYNAMIXEL2Arduino (https://github.com/ROBOTIS-GIT/dynamixel2arduino)

### PythonSDK
- xArm-Python-SDK(https://github.com/xArm-Developer/xArm-Python-SDK)

## Installation
Connect your OpenRB-150 to your PC and write the sketch software/arduino_sketch/OpenRB_modbusRTU.ino into your OpenRB-150.

Then run either of python script to open and close your gripper.

```
# For Modbus-RTU control
$ python3 control_openRB150_with_modbus_rtu.py <IP address of arm> oc

# For digital input control
$ python3 control_openRB150_with_lite6_api.py <IP address of arm> oc
```

The 2nd argument is list of action. "o" means open and "c" means close.
```
# Just open the gripper
$ python3 control_openRB150_with_lite6_api.py <IP address of arm> o

# Just close the gripper
$ python3 control_openRB150_with_lite6_api.py <IP address of arm> c

# Open and Close the gripper 4th times
$ python3 control_openRB150_with_lite6_api.py <IP address of arm> ococococ
```

Using Modbus-RTU interface, you can move the gripper stroke to the state between Open-Close.
```
import sys

from control_openRB150_with_modbus_rtu import ParalleGripperOpenRB150


ip = sys.argv[1]
arm = XArmAPI(ip, is_radian=False)
pga = ParalleGripperOpenRB150(arm)
storke = 100 # deg in servo axis. range is 0-250 for 65mm stroke gripper.
pga.move(stroke)
storke = 50
pga.move(stroke)

```