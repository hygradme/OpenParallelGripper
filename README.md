# Electric Parallel Gripper for UFACTORY LITE 6

## Introduction
This project provide electric parallel gripper for UFACTORY LITE 6.
This gripper can also be used for UFACTORY xArm series and possibly with other industrial cobots like Universal Robot etc.

## Spec of the gripper
- stroke: 0-55mm
- weight: about 340g
- Communication protocol: Two digital inputs(compatible with default LITE 6 gripper) or Modbus-RTU with RS485.

## BOM
Check [BOM](./BOM.md)

## Software

If you prefer to use two digital inputs to control the gripper for simplicity, you can use xArm SDK from UFACTORY(https://github.com/xArm-Developer/xArm-Python-SDK/blob/master/xarm/wrapper/xarm_api.py#L3654).

If you want to control the gripper more detail, you need to use Modbus-RTU with RS485.

