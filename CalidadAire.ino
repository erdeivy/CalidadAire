#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

int maxHum = 60;
int maxTemp = 40;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  dht.begin();
    pinMode(3, INPUT);
  pinMode(5, INPUT);

}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

am2302();
mq7();
mq135();
  
  Serial.println(" ");

}

void printValue(String parametro, double valor){
  Serial.print(","+parametro+": ");
  Serial.print(valor);
}

void am2302(){
    // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  printValue("Humedad", h);
printValue("Temp", t);
}

void mq7(){
    // MQ-7
  int mq7_adc = analogRead(3);
  float mq7_voltaje = mq7_adc * (5.0 / 1023.0);
  float mq7_resistencia = 1000*((5-mq7_voltaje)/mq7_voltaje);
  double monoxidoDeCarbono = 233.9*pow(mq7_resistencia/5463, -1.40);
  String mq7_umbral = "false";

  if(digitalRead(3) == 0){
    mq7_umbral = "true";
  }
printValue("Monoxido de Carbono", monoxidoDeCarbono);
}

void mq135(){
     // MQ-135
  int mq135_adc = analogRead(5);
  float mq135_voltaje = mq135_adc * (5.0 / 1023.0);
  float mq135_resistencia = 1000*((5-mq135_voltaje)/mq135_voltaje);
  double dioxidoDeCarbono = 245*pow(mq135_resistencia/5463, -2.26);
  double oxidosDeNitrogeno = 132.6*pow(mq135_resistencia/5463, -2.74);
  double amoniaco = 161.7*pow(mq135_resistencia/5463, -2.26);
  String mq135_umbral = "false";

  if(digitalRead(5) == 0){
    mq135_umbral = "true";
  }
  printValue("Dioxido de Carbono", dioxidoDeCarbono);

}
