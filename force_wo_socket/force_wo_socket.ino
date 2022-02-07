#include <WiFi.h>
/* 
const char* ssid = "primpunn.p";
const char* password = "Hpsb_8741";
 
const uint16_t port = 8090;
const char * host = "172.20.10.5";
*/
//(fsrPin,fsrReading,fsrVoltage,fsrResistance,fsrConductance,fsrForce,s)

void setup()
{

  Serial.begin(115200); 
 /*
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
 */
}


int dummy1=1;
int dummy2=2;
int dummy3=3;
int dummy4=4;
int dummy5=5;
int dummy6=6;

int fsrPin = 34;     // the FSR and 10K pulldown are connected to a0
int fsrPin2 = 35;
int fsrPin3 = 32;
int fsrPin4 = 33;
int fsrPin5 = 25;
int fsrPin6 = 26;

int fsrReading = 0;     // the analog reading from the FSR resistor divider
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
int fsrVoltage6 = 0;

unsigned long fsrResistance;  // The voltage converted to resistance
unsigned long fsrResistance2;
unsigned long fsrResistance3;
unsigned long fsrResistance4;
unsigned long fsrResistance5;
unsigned long fsrResistance6;

unsigned long fsrConductance;
unsigned long fsrConductance2;
unsigned long fsrConductance3;
unsigned long fsrConductance4;
unsigned long fsrConductance5;
unsigned long fsrConductance6;

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

long fsrForce;       // Finally, the resistance converted to force
long fsrForce2;
long fsrForce3;
long fsrForce4;
long fsrForce5;
long fsrForce6;

long s = fsrForce;
long s2 = fsrForce2;
long s3 = fsrForce3;
long s4 = fsrForce4;
long s5 = fsrForce5;
long s6 = fsrForce6;


//int int int unsigned long  unsigned long long long
void fsr(int fsrPin,int fsrReading,int fsrVoltage,unsigned long fsrResistance,unsigned long fsrConductance,long fsrForce,long s,int dummy){
  Serial.print("Sensor >>>>> ");Serial.println(dummy);
  fsrReading = analogRead(fsrPin);  
  //Serial.print("Analog reading = ");
  //Serial.println(fsrReading);


  Serial.println("BE FORE MAP");
  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
  Serial.print("FSR READIN >>>  ");Serial.println(fsrReading);
  fsrVoltage = map(fsrReading, 0, 4095, 0, 3300);

  Serial.println("OUT FRM MAPPIN");
  
  Serial.print("Voltage reading in mV = ");Serial.println(fsrVoltage);  
 
  if (fsrVoltage == 0) {
    Serial.println("No pressure");  
  } else {
    Serial.println("NOT ZERO ??????????????????");
    // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
    // so FSR = ((Vcc - V) * R) / V        yay math!
    fsrResistance = 3300 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance *= 3300;                // 10K resistor
    fsrResistance /= fsrVoltage;
    Serial.print("FSR resistance in ohms = ");Serial.println(fsrResistance);
    
    Serial.println("DIVID BY 100000000000000000000000");
    fsrConductance = 1000000L;           // we measure in micromhos so 
    if (fsrResistance <= 0 ){
      fsrResistance = 1;
      Serial.println("ZEROOOOOOOOOOOOOOOOOOOOOOOOOO");
    }
    fsrConductance = (long)fsrConductance / fsrResistance;
    //Serial.print("Conductance in microMhos: ");
    //Serial.println(fsrConductance);
    Serial.println("OUT FRM CONDUCT ??????????????????????");
    // Use the two FSR guide graphs to approximate the force
    if (fsrConductance <= 1000) {
      Serial.println("IN THE IF <=1000 ???????????????");
      fsrForce = fsrConductance / 80;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce);      
    } else {
      Serial.println("IN THE IF <=1000 BYT ELSE ????????");
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce);  
    }
  }
}
 
void loop() {
  Serial.println("LOOP L KAB");
  fsr(fsrPin,fsrReading,fsrVoltage,fsrResistance,fsrConductance,fsrForce,s,dummy1 );
  fsr(fsrPin2,fsrReading2,fsrVoltage2,fsrResistance2,fsrConductance2,fsrForce2,s2,dummy2);
  fsr(fsrPin3,fsrReading3,fsrVoltage3,fsrResistance3,fsrConductance3,fsrForce3,s3,dummy3);
  fsr(fsrPin4,fsrReading4,fsrVoltage4,fsrResistance4,fsrConductance4,fsrForce4,s4,dummy4);
  fsr(fsrPin5,fsrReading5,fsrVoltage5,fsrResistance5,fsrConductance5,fsrForce5,s5,dummy5);
  fsr(fsrPin6,fsrReading6,fsrVoltage6,fsrResistance6,fsrConductance6,fsrForce6,s6,dummy6);

  Serial.println("--------------------");
/*
  WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(500);
        return;
    }
 
    Serial.println("Connected to server successful!");
 
    //client.print("Hello from ESP32!");
     client.print(s); 
    //client.print(dummy);
    client.stop();
  */    
  delay(1000);
}
