#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define MPU6050_ADDR 0x68

Adafruit_MPU6050 mpu;

void connect_MPU(){
  while(!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
}

void data_to_serial(sensors_event_t *a, sensors_event_t *g){
  Serial.print("Acc");
  Serial.print(a -> acceleration.x);
  Serial.print(",");
  Serial.print(a -> acceleration.y);
  Serial.print(",");
  Serial.print(a -> acceleration.z);
  Serial.print(", ");
  Serial.print("Gyro");
  Serial.print(g ->gyro.x);
  Serial.print(",");
  Serial.print(g -> gyro.y);
  Serial.print(",");
  Serial.print(g -> gyro.z);
  Serial.println("");
}

void setup() {
  connect_MPU();

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  Serial.begin(115200);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  data_to_serial(&a, &g);

  delay(20);
}