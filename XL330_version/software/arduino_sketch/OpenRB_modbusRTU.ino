#include <Dynamixel2Arduino.h>
#include <ModbusRTU.h>

#define DXL_SERIAL Serial1
#define DEBUG_SERIAL Serial
const int DXL_DIR_PIN = -1;

ModbusRTU mb;
#define SLAVE_ID 1

#define REG_GRIPPER_POS 128
#define REG_READ_GRIPPER_POS 257

#define LITE6_OUTPUT0 4
#define LITE6_OUTPUT1 5

int lite6_0;
int lite6_1;
uint16_t gripper_pos = 0;
uint16_t gripper_open_pos = 250;// 150 for 75mm rail version
uint16_t gripper_close_pos = 0;

const uint8_t DXL_ID = 1;
const float DXL_PROTOCOL_VERSION = 2.0;
int current_val = 75;//50;
Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

using namespace ControlTableItem;

void setup() {
  pinMode(LITE6_OUTPUT0, INPUT_PULLUP);
  pinMode(LITE6_OUTPUT1, INPUT_PULLUP);

  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl.ping(DXL_ID);

  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_CURRENT_BASED_POSITION);
  dxl.torqueOn(DXL_ID);

  DEBUG_SERIAL.begin(115200);
  
  // modbus RTU
  Serial2.begin(57600, SERIAL_8N1);
  mb.begin(&Serial2);
  mb.slave(SLAVE_ID);

  mb.addHreg(REG_GRIPPER_POS);
  mb.Hreg(REG_GRIPPER_POS,  gripper_pos);
  mb.addIreg(REG_READ_GRIPPER_POS, gripper_pos);
  delay(1000);
}

void loop() {
    lite6_0 = digitalRead(LITE6_OUTPUT0);
    lite6_1 = digitalRead(LITE6_OUTPUT1);
    if(lite6_0 == LOW && lite6_1 == HIGH){
      dxl.setGoalCurrent(DXL_ID, current_val);
      dxl.setGoalPosition(DXL_ID, gripper_open_pos, UNIT_DEGREE);
    }
    else if(lite6_0 == HIGH && lite6_1 == LOW){
      dxl.setGoalCurrent(DXL_ID, current_val);
      dxl.setGoalPosition(DXL_ID, gripper_close_pos, UNIT_DEGREE);
      
    }
    else if(lite6_0 == LOW && lite6_1 == LOW){

      gripper_pos = mb.Hreg(REG_GRIPPER_POS);
    
      dxl.setGoalCurrent(DXL_ID, current_val);
      dxl.setGoalPosition(DXL_ID, gripper_pos, UNIT_DEGREE);
      
      DEBUG_SERIAL.print("Present gripper_pos(target) : ");
      DEBUG_SERIAL.println(gripper_pos);      
  }
    mb.task();
    yield();

}
