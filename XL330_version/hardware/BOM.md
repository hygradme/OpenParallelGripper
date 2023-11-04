# Electric Parallel Gripper Bill Of Materials(XL330 version)

## 1. 3D print parts
stl files are available in ./3dprint_parts/stl
  - [Base](./3dprint_parts/stl/XL330_base_for65mm.stl) x1
  - [TipCover](./3dprint_parts/stl/TipCover_for65mm.stl) x1
  - [ToArm](./3dprint_parts/stl/ToArm.stl) x1
  - [R75_cover](./3dprint_parts/stl/R75_cover.stl) x1
  - [XL330_cover](./3dprint_parts/stl/XL330_cover.stl) x2
  - [Rail_base_to_rack](./3dprint_parts/stl/Rail_base_to_rack_dynamixel.stl) x2
  - [Claw_adapter](./3dprint_parts/stl/claw_adapter.stl) x2

Note: To keep the gripper weight small, thickness of these parts are thin.

<img src="./3dprint_parts.jpg" width="400">

  - [Gear20Tooth_forXL330](./3dprint_parts/stl/Gear20Tooth_forXL330.stl) x1 (3D printing with metal material strongly reccomended. I used SLM)


<img src="./Gear_front.jpg" width="200">
<img src="./Gear_back.jpg" width="200">


## 2. CNC Miling parts
step files and drawings are available in ./cnc_miling_parts/
Optionally, stl files for 3d printing are also available but these parts need stiffness so I recommend to use Aluminum for these parts.

  - [Claw50mm](./cnc_miling_parts/Claw_50mm.step) x2


## 3. parts from shops
  - XL330-M288-T x1 (https://emanual.robotis.com/docs/en/dxl/x/xl330-m288/)
  - SSE2B6-100 x1 (https://us.misumi-ec.com/vona2/detail/110302586530/?HissuCode=SSE2B6-100)
  - RGEAL0.8KA-55-A5-B10-C10-D10 x2 (https://us.misumi-ec.com/vona2/detail/110300429920/?HissuCode=RGEAL0.8KA-55-A5-B10-C10-D10)

- M6 x 10mm x2
- M3.5 x 8mm x 4
- M3x8mm x 20
- M3x6mm x 4
- M2 x 4mm x 4
- M2 x 6mm x 4
- M2 Tapping screw x 4 (Included in Dynamixel XL330 package)
- M3.5 Nuts x 4
- M3 Nuts x 24
- M2 Nuts x 4

## 4. electronic components (Just for reference. You can choose your own micro controller and other components to control the servo motor)
  - OpenRB-150(https://emanual.robotis.com/docs/en/parts/controller/openrb-150/)

      (OpenRB-150 with XL330-M288-T set is alaso avaiable: https://www.robotis.us/openrb-150/)
  - RS485 to TTL Converter Unit (https://shop.m5stack.com/products/rs485-module)
  -  Lite 6 end adapter cable (Included in Lite 6. If not, ask UFACTORY to purchase)
  - Wires
