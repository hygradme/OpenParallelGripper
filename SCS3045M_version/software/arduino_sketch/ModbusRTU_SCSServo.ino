#include <SCServo.h>
#include "M5Atom.h"
#include <ModbusRTU.h>

SMS_STS sms_sts;
unsigned int SERVO_POS = 0;

#define TX_UART 33
#define RX_UART 23
 
// modbus-rtu setup
#define RX_MODBUS 32
#define TX_MODBUS 26
#define SLAVE_ID 1
#define REGN 10
#define REG_GRIPPER_POS 128
#define REG_READ_GRIPPER_POS 257

#define LITE6_OUTPUT0 21
#define LITE6_OUTPUT1 22

int lite6_0;
int lite6_1;
uint16_t gripper_pos = 1500;
uint16_t gripper_open_pos = 2200;
uint16_t gripper_close_pos = 200;

ModbusRTU mb;

void setup() {

  pinMode(LITE6_OUTPUT0, INPUT_PULLUP);
  pinMode(LITE6_OUTPUT1, INPUT_PULLUP);
  // put your setup code here, to run once:
  M5.begin(true, false, true);

  // for servo control uart
  Serial1.begin(1000000, SERIAL_8N1, RX_UART, TX_UART);
  sms_sts.pSerial = &Serial1;

  // modbus rtu
  Serial2.begin(115200, SERIAL_8N1, RX_MODBUS, TX_MODBUS);
  mb.begin(&Serial2);
  mb.slave(SLAVE_ID);

  mb.addHreg(REG_GRIPPER_POS);
  mb.Hreg(REG_GRIPPER_POS,  gripper_pos);
  mb.addIreg(REG_READ_GRIPPER_POS, gripper_pos);

  delay(1000);
}

void loop() {
  // with digital input
  lite6_0 = digitalRead(LITE6_OUTPUT0);
  lite6_1 = digitalRead(LITE6_OUTPUT1);
  if(lite6_0 == LOW && lite6_1 == HIGH){
    sms_sts.WritePosEx(1, gripper_open_pos, 2500, 200);    
   }
  if(lite6_0 == HIGH && lite6_1 == LOW){
    sms_sts.WritePosEx(1, gripper_close_pos, 2500, 200);    
   }

  // with modbus control mode
  if(lite6_0 == HIGH && lite6_1 == HIGH){

    gripper_pos = mb.Hreg(REG_GRIPPER_POS);
    
    sms_sts.WritePosEx(1, gripper_pos, 2500, 200);  
  }

  mb.task();
  yield();
}
