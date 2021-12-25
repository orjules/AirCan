#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

using namespace std;

#define MPU6050_ADDR 0x68

Adafruit_MPU6050 mpu;

File workingfile;

String fileName = "empty";  // Immer 'Logs0' wobei die 0 hochiteriert wird

int step = 0;

void start_serial(){
  // Serial.begin(115200); // Für MPU ausgabe
  Serial.begin(9600); // Für SD Karte
  while (!Serial)
  {
    // Warten bis ausgabe bereit. Nur wichtig bei Lesen von Serial.
  }
}

void connect_MPU(){
  Serial.print("Initializing MPU card...");
  while(!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    delay(10);
  }
  Serial.println("MPU6050 connected!");
}

void set_MPU(){
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.println("MPU6050 configured!");
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

void connect_SD(){
  Serial.print("Initializing SD card...");
  while (!SD.begin(5))
  {
    Serial.println("Failed to find SD card");
    delay(10);
  }
  Serial.println("initialization done.");
}

void iterate_file_name(){
  int number = 0;
  while (true){
    fileName = "Logs";
    fileName = fileName + String(number);
    fileName = fileName + ".txt";
    Serial.println(fileName);
    if (!SD.exists(fileName)){
      Serial.println("Iteriert bis: " + fileName);
      break;
    }
    number ++;
  }
}

void add_table_head(){
  workingfile = SD.open(fileName, FILE_WRITE);
  if(workingfile){
    workingfile.println("Step,AccX,AccY,AccZ,GyrX,GyrY,GyrZ");
    workingfile.close();
  }else{
    Serial.println("Error while Writing table head.");
  }
}

/*void fill_test_file(){
  Serial.println("Writing to testfile.");
  workingfile = SD.open(fileName, FILE_WRITE);
  if(workingfile){
    workingfile.println("Lorem ipsum!");
    workingfile.close();
    Serial.println("Sucessfully written to " + fileName);
  }else{
    Serial.println("Error while Writing testfile.");
  }
}*/

void data_to_sd(sensors_event_t *a, sensors_event_t *g){
  workingfile = SD.open(fileName, FILE_WRITE);
  if(workingfile){
    workingfile.print(step);
    workingfile.print(",");
    workingfile.print(a -> acceleration.x);
    workingfile.print(",");
    workingfile.print(a -> acceleration.y);
    workingfile.print(",");
    workingfile.print(a -> acceleration.z);
    workingfile.print(", ");
    workingfile.print(g ->gyro.x);
    workingfile.print(",");
    workingfile.print(g -> gyro.y);
    workingfile.print(",");
    workingfile.print(g -> gyro.z);
    workingfile.println("");
    workingfile.close();
  }else{
    Serial.println("Error while Writing mpu data.");
  }
  step ++;
}

void setup() {

  start_serial();
  
  connect_MPU();
  set_MPU();

  connect_SD();
  iterate_file_name();
  // fill_test_file();
  add_table_head();
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  // data_to_serial(&a, &g);
  // delay(20);
  data_to_sd(&a, &g);
}