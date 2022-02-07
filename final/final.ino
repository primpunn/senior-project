#include <WiFi.h>
 
const char* ssid = "Tenda_01";
const char* password = "1122334455";
 
const uint16_t port = 8090;
const char * host = "192.168.5.249";

int fsrPin = 34;     // the FSR and 10K pulldown are connected to a0
int fsrPin2 = 35;
int fsrPin3 = 32;
int fsrPin4 = 33;
int fsrPin5 = 36;
int fsrPin6 = 39;

void setup() {

  Serial.begin(115200); 
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

long fsr(int fsrPin){
  long fsrReading,fsrVoltage;
  double fsrResistance,fsrConductance;
  double fsrForce = 0.0;
  fsrReading = analogRead(fsrPin);
  fsrVoltage = map(fsrReading, 0, 4095, 0, 3300);

  if (fsrVoltage == 0) {
    //Serial.println("No pressure");  
  } else {
    fsrResistance = 3300 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance *= 3300;                // 10K resistor
    fsrResistance /= fsrVoltage;
    fsrConductance = 100000.0;           // we measure in micromhos so 
    
    if (fsrResistance <= 0 ){
      fsrForce = -1;
      //Serial.println(fsrVoltage);
    } else {
      fsrConductance = fsrConductance / fsrResistance;
    
      if (fsrConductance <= 1000) {
        fsrForce = fsrConductance / 80;
        //Serial.print("Force in Newtons: ");
        //Serial.println(fsrForce);      
      } 
      else {     
        fsrForce = fsrConductance - 1000;
        fsrForce /= 30;
        //Serial.print("Force in Newtons: ");
        //Serial.println(fsrForce);      
      }   
    }
  }
  
  Serial.print(fsrPin);
  Serial.print(" : return fsrForce =");Serial.println(fsrForce);
  return fsrForce; 
}

void fsr_strcat(double test_var, char fsr){
  char fsr[10];  
  ftoa(test_var, fsr, 10);
  printf("%s\n", fsr);
  return fsr
}
  char fsr1[10];
  char fsr2[10];
  char fsr3[10];
  char fsr4[10];
  char fsr5[10];
  char fsr6[10];

  fsr_strcat(test_var1, fsr1);
  fsr_strcat(test_var2, fsr2);
  fsr_strcat(test_var3, fsr3);
  fsr_strcat(test_var4, fsr4);
  fsr_strcat(test_var5, fsr5);
  fsr_strcat(test_var6, fsr6);
  
  strcat(fsr5,fsr6 );
  strcat(fsr5,"," );
  strcat(fsr4, fsr5);
  strcat(fsr4,"," );
  strcat(fsr3, fsr4);
  strcat(fsr3,"," );
  strcat(fsr2, fsr3);
  strcat(fsr2,"," );
  strcat(fsr1, fsr2);
  strcat(fsr1,"," );
  printf("%s", fsr);
 
void loop() {
  long test_var1;
  long test_var2;
  long test_var3;
  long test_var4;
  long test_var5;
  long test_var6;
  
  Serial.println("***********");
  test_var1 = fsr(fsrPin);
  test_var2 = fsr(fsrPin2);
  test_var3 = fsr(fsrPin3);
  test_var4 = fsr(fsrPin4);
  test_var5 = fsr(fsrPin5);
  test_var6 = fsr(fsrPin6);
  
  WiFiClient client;
 
  if (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        delay(500);
        return;
    }
 
    Serial.println("Connected to server successful!");
    client.print("force1 = "); 
    client.println(test_var1);
    client.print("force2 = "); 
    client.println(test_var2);
    client.print("force3 = "); 
    client.println(test_var3);
    client.print("force4 = "); 
    client.println(test_var4);
    client.print("force5 = "); 
    client.println(test_var5);
    client.print("force6 = "); 
    client.println(test_var6);
    client.stop();
      
  delay(500);
}
