import sys
import time

from xarm.wrapper import XArmAPI


def int_to_2bytes_list(value):
    value_in_hex = hex(value)[2:].zfill(4)
    return [int(value_in_hex[0:2], base=16), int(value_in_hex[2:4], base=16)]


class ParalleGripperOpenRB150:
    def __init__(self, arm, torque_limit=150):
        self._arm = arm
        self._arm.set_mode(0)
        self._arm.set_state(0)
        # code = self._arm.set_tgpio_modbus_baudrate(57600)
        code = self._arm.set_tgpio_modbus_baudrate(115200)
        print('set_tgpio_modbus_baudrate, code={}'.format(code))
        self.close_in_res = 0
        self.open_in_res = 250

        self._arm.set_tgpio_modbus_timeout(50)
        self._arm.set_tgpio_digital(0, 1)
        self._arm.set_tgpio_digital(1, 1)
    def open(self):
        data = [0x01, 0x06, 0x00, 0x80]
        data += int_to_2bytes_list(self.open_in_res)
        res = self._arm.getset_tgpio_modbus_data(data)

    def close(self):
        data = [0x01, 0x06, 0x00, 0x80]
        data += int_to_2bytes_list(self.close_in_res)

        res = self._arm.getset_tgpio_modbus_data(data)

    def move(self, pos):
        assert pos >= self.close_in_res
        assert pos <= self.open_in_res

        data = [0x01, 0x06, 0x00, 0x80] + int_to_2bytes_list(pos)
        res = self._arm.getset_tgpio_modbus_data(data)

    def move_out_of_10(self, ratio):
        assert ratio <= 9
        pos = (self.open_in_res - self.close_in_res) * ratio / 10 + self.close_in_res
        self.move(int(pos))

    def get_pos(self):
        cmd = [0x01, 0x03, 0x01, 0x01, 0x00, 0x01]   # 0x03(Holding register), Addr 0x0101, Len 1
        code, resp = self._arm.getset_tgpio_modbus_data(cmd)
        if code != 0:
            raise RuntimeError(f"xArm SDK error code={code}")

        return (resp[3] << 8) | resp[4]

if __name__ == "__main__":
    action_list = "oc"
    ip = sys.argv[1]
    if len(sys.argv) >= 3:
        action_list = sys.argv[2]
    arm = XArmAPI(ip, is_radian=False)
    pga = ParalleGripperOpenRB150(arm)
    time.sleep(1)
    while True:
        for action in action_list:
            if action == "o":
                pga.open()

            elif action == "c":
                pga.close()

            elif action == "s":
                time.sleep(1)

            elif action.isdecimal():
                val = int(action)
                pga.move_out_of_10(val)
            time.sleep(0.1)
            print(f"current pos:{pga.get_pos()} deg")
            time.sleep(2)
