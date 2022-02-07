#include <WiFi.h>
 
const char* ssid = "490Phone";
const char* password = "11501112";
 
const uint16_t port = 8090;
const char * host = "172.20.10.6";

//(fsrPin,fsrReading,fsrVoltage,fsrResistance,fsrConductance,fsrForce,s)

void setup()
{
  Serial.begin(115200); 
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

int fsrPin = 34;     // the FSR and 10K pulldown are connected to a0
int fsrPin2 = 35;
int fsrPin3 = 32;
int fsrPin4 = 33;
int fsrPin5 = 25;
int fsrPin6 = 26;

/*int fsrReading = 0;     // the analog reading from the FSR resistor divider
int fsrReading2 = 0;
int fsrReading3 = 0;
int fsrReading4 = 0;
int fsrReading5 = 0;
int fsrReading6 = 0;

int fsrVoltage = 0;     // the analog reading converted to voltage
int fsrVoltage2 = 0;
int fsrVoltage3 = 0;
int fsrVoltage4 = 0;
int fsrVoltage5 = 0;
int fsrVoltage6 = 0;*/

/*unsigned long fsrResistance;  // The voltage converted to resistance
unsigned long fsrResistance2;
unsigned long fsrResistance3;
unsigned long fsrResistance4;
unsigned long fsrResistance5;
unsigned long fsrResistance6;*/

/*double fsrResistance;  // The voltage converted to resistance
double fsrResistance2;
double fsrResistance3;
double fsrResistance4;
double fsrResistance5;
double fsrResistance6;

double fsrConductance;
double fsrConductance2;
double fsrConductance3;
double fsrConductance4;
double fsrConductance5;
double fsrConductance6;*/

/*
int fsrForce;       // Finally, the resistance converted to force
int fsrForce2;
int fsrForce3;
int fsrForce4;
int fsrForce5;
int fsrForce6;

int s = fsrForce;
int s2 = fsrForce2;
int s3 = fsrForce3;
int s4 = fsrForce4;
int s5 = fsrForce5;
int s6 = fsrForce6;
*/

double fsrForce;       // Finally, the resistance converted to force
double fsrForce2;
double fsrForce3;
double fsrForce4;
double fsrForce5;
double fsrForce6;

double s = fsrForce;
double s2 = fsrForce2;
double s3 = fsrForce3;
double s4 = fsrForce4;
double s5 = fsrForce5;
double s6 = fsrForce6;

//int int int unsigned long  unsigned long long long
long fsr(int fsrPin){
  long fsrReading,fsrVoltage;
  double fsrResistance,fsrConductance,fsrForce;
  
  //Serial.print("Sensor >>>>> ");Serial.println(dummy);
  fsrReading = analogRead(fsrPin);  
  //Serial.print("Analog reading = ");
  //Serial.println(fsrReading);

  //Serial.println("BE FORE MAP");
  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
  //Serial.print("FSR READIN >>>  ");Serial.println(fsrReading);
  fsrVoltage = map(fsrReading, 0, 4095, 0, 3300);

  //Serial.println("OUT FRM MAPPIN");
  
  //Serial.print("Voltage reading in mV = ");Serial.println(fsrVoltage);  
 
  if (fsrVoltage == 0) {
    Serial.println("No pressure");  
  } else {
    //Serial.println("NOT ZERO ??????????????????");
    // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
    // so FSR = ((Vcc - V) * R) / V        yay math!
    fsrResistance = 3300 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance *= 3300;                // 10K resistor
    fsrResistance /= fsrVoltage;
    //Serial.print("FSR resistance in ohms = ");Serial.println(fsrResistance);
    
    //Serial.println("DIVID BY 100000000000000000000000");
    fsrConductance = 100000.0;           // we measure in micromhos so 
    
    if (fsrResistance <= 0 ){
      fsrForce = -1;
      Serial.println(fsrForce);
    } else {
      fsrConductance = fsrConductance / fsrResistance;
    //Serial.print("Conductance in microMhos: ");
    //Serial.println(fsrConductance);
    //Serial.println("OUT FRM CONDUCT ??????????????????????");
    // Use the two FSR guide graphs to approximate the force
    if (fsrConductance <= 1000) {
      //Serial.println("IN THE IF <=1000 ???????????????");
      fsrForce = fsrConductance / 80;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce);  
          
    } else {
      //Serial.println("IN THE IF <=1000 BYT ELSE ????????");
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce);   

//      char snum[10];
//      itoa(fsrForce, snum, 10);
//      printf("%s\n", snum);
//
//      char snum2[10];
//      itoa(fsrForce2, snum2, 10);
//      printf("%s\n", snum2);
//
//      char snum3[10];
//      itoa(fsrForce3, snum3, 10);
//      printf("%s\n", snum3);
//
//      char snum4[10];
//      itoa(fsrForce4, snum4, 10);
//      printf("%s\n", snum4);
//
//      char snum5[10];
//      itoa(fsrForce5, snum5, 10);
//      printf("%s\n", snum5);
//
//      char snum6[10];
//      itoa(fsrForce6, snum6, 10);
//      printf("%s\n", snum6);
      
      //ans = strcat(fsrForce,fsrForce2,fsrForce3,fsrForce4,fsrForce5,fsrForce6);
      
      /*for (int i=1 ; i<=6;i++){
        
        Serial.print(snum[i]);
        
        }*/     
    }   
    }
  }
  Serial.print("return fsrForce");Serial.println(fsrForce);
  return fsrForce;
}

//long test_var;
 
void loop() {
  long test_var;
  Serial.println("LOOP L KAB");
  //test_var = fsr(fsrPin);
  //fsr(fsrPin2,fsrReading2,fsrVoltage2,fsrResistance2,fsrConductance2,fsrForce2,s2,dummy2);
  //fsr(fsrPin3,fsrReading3,fsrVoltage3,fsrResistance3,fsrConductance3,fsrForce3,s3,dummy3);
  //fsr(fsrPin4,fsrReading4,fsrVoltage4,fsrResistance4,fsrConductance4,fsrForce4,s4,dummy4);
  //fsr(fsrPin5,fsrReading5,fsrVoltage5,fsrResistance5,fsrConductance5,fsrForce5,s5,dummy5);
  test_var =  fsr(fsrPin6);
  Serial.print("long test_var = fsr(...)");Serial.println(test_var);

  Serial.println("--------------------");
  
//  Serial.println(ans);

  WiFiClient client;
 
  if (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        delay(500);
        return;
    }
 
    Serial.println("Connected to server successful!");
    //Serial.println(s); s=0 in this case
    //client.print("Hello from ESP32!");
     //client.print(s);
    Serial.print("Serial.print fsrForce");Serial.println(fsrForce);
    Serial.println("printed sth to py");
    client.print("sth");
    //client.print(fsrForce);
    client.print("back of fsrForce");
//    Serial.print("client.print(test_vsr) = ");Serial.println(test_vsr);
    client.print(test_var);
    //client.print(dummy);
    client.stop();
      
  delay(500);
}
