#include <SimpleFOC.h>
#include "MagneticSensorMT6826.h"
#include "StatusLED.h"
// ===== Sensor =====
MagneticSensorMT6826 sensor(PA3);
StatusLED statusLED(PB14, PB12);

// ===== Serial =====
HardwareSerial Serial3(USART3);

// ===== Motor & Driver =====
BLDCMotor motor = BLDCMotor(20);
BLDCDriver6PWM driver = BLDCDriver6PWM(
  PC1, PB0,
  PC2, PB1,
  PC3, PC5,
  PC15
);

// ===== Commander =====
Commander command = Commander(Serial3);
void doTarget(char* cmd) { command.scalar(&motor.target, cmd); }

unsigned long long timer = 0;

void setup() {
  // ---- Serial ----
  Serial3.setTx(PA9);
  Serial3.setRx(PA10);
  Serial3.begin(115200);
  SimpleFOCDebug::enable(&Serial3);

  Serial3.println("MT6826 FOC torque test");

  // ---- Sensor ----
  sensor.init();
  motor.linkSensor(&sensor);
  Serial3.println("MT6826 ready");
  statusLED.begin();

  // ---- Driver ----
  driver.voltage_power_supply = 24.0f;
  driver.voltage_limit = 24.0f;
  driver.dead_zone = 0.05f;

  if (!driver.init()) {
    Serial3.println("Driver init failed!");
    while (1) {}
  }
  motor.linkDriver(&driver);
  Serial3.println("Driver ready!");

  // ---- Motor config ----
  motor.torque_controller = TorqueControlType::voltage;
  motor.controller = MotionControlType::angle;

  motor.voltage_limit = 24.0f;
  motor.voltage_sensor_align = 3.0f;

  // optional helpers
  motor.P_angle.P = 2.0;
  motor.P_angle.I = 0.1;
  motor.P_angle.D = 0.0;
  motor.PID_velocity.P = 0.3f;
  motor.PID_velocity.I = 2.0f;
  motor.PID_velocity.D = 0.0f;
  motor.LPF_velocity.Tf = 0.01f;
  motor.PID_velocity.output_ramp = 10.0f;

  // ---- Init ----
  motor.init();
  motor.initFOC();

  // ---- Commander ----
  command.add('T', doTarget, "target torque voltage");
  motor.useMonitoring(Serial3);

  motor.target = 3.14f;

  Serial3.println("Ready");
  Serial3.println("Try: T0.3  or  T1.0");
}

void loop() {
  if(millis() - timer > 2000){
    motor.target *= -1.0f;
    timer = millis();
  }
  motor.loopFOC();
  motor.move();
  command.run();
  statusLED.update();

  // sensor.update();
  // Serial3.println(sensor.getAngle());
}