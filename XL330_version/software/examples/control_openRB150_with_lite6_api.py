import sys
import time

from xarm.wrapper import XArmAPI


if __name__ == "__main__":
    action_list = "oc"
    ip = sys.argv[1]
    if len(sys.argv) >= 3:
        action_list = sys.argv[2]
    arm = XArmAPI(ip, is_radian=False)

    for action in action_list:
        if action == "o":
            arm.open_lite6_gripper()

        elif action == "c":
            arm.close_lite6_gripper()

        elif action == "s":
            time.sleep(1)
