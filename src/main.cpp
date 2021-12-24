#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#define MPU6050_ADDR 0x68

Adafruit_MPU6050 mpu;

File workingfile;

String fileName;  // Immer 'Logs:0000' hoch iteriert bis maximal 9999

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
  File root = SD.open("/");
  
  String lastname = "";
  while (true){
    File entry = root.openNextFile();
    if (! entry) {
      break;  // no more files
    }
    Serial.print(entry.name());  // Zum testen
    lastname = entry.name();
  }
  if (lastname == "" || lastname == "test.txt"){
    fileName = "Logs:0000";
    Serial.print("Erstes File angelegt");  // Zum testen
  }else{
    int file_number = lastname.charAt(5) * 1000 + lastname.charAt(6) * 100 + lastname.charAt(7) * 10 + lastname.charAt(8); // Ab stelle 5 kommt die Zahl und ist genau 4 stellen
    Serial.print(file_number);  // Zum testen
    file_number ++;
    fileName = "Logs:" + file_number;
  }
}

void add_table_head(){
  workingfile = SD.open(fileName, FILE_WRITE);
  if(workingfile){
    Serial.println("Step,AccX,AccY,AccZ,GyrX,GyrY,GyrZ");
    workingfile.close();
  }else{
    Serial.println("Error while Writing table head.");
  }
}

void fill_test_file(){
  workingfile = SD.open(fileName, FILE_WRITE);
  if(workingfile){
    workingfile.println("This is a test file :)");
    workingfile.println("testing 1, 2, 3.");
    for (int i = 0; i < 20; i++) {
      workingfile.println(i);
    }
    workingfile.close();
  }else{
    Serial.println("Error while Writing testfile.");
  }
}

void data_to_sd(sensors_event_t *a, sensors_event_t *g){
  workingfile = SD.open(fileName, FILE_WRITE);
  if(workingfile){
    Serial.print(step);
    Serial.print(",");
    Serial.print(a -> acceleration.x);
    Serial.print(",");
    Serial.print(a -> acceleration.y);
    Serial.print(",");
    Serial.print(a -> acceleration.z);
    Serial.print(", ");
    Serial.print(g ->gyro.x);
    Serial.print(",");
    Serial.print(g -> gyro.y);
    Serial.print(",");
    Serial.print(g -> gyro.z);
    Serial.println("");
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
  fill_test_file();
}

void loop() {
  // sensors_event_t a, g, temp;
  // mpu.getEvent(&a, &g, &temp);
  // data_to_serial(&a, &g);
  // delay(20);
}