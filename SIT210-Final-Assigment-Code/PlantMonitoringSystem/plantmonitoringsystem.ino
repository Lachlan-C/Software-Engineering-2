// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>
#include "Adafruit_TSL2561_U.h"

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int SetMoistureThreshold(String threshold); 
int MoistureThreshold = 200;

double hum;
double temp;

int SoilMoisturePin = A0;
int SoilMoisture = 0;
int WaterPlantLEDpin = 6;
int Light;
bool waternotified = 0;

String DeviceName = "Plant1";
int SetDeviceName(String NewName); 

void configureSensor(void)
{
  /* You can also manually set the gain or enable auto-gain support */
  // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  
  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

  /* Update these values depending on what you've set above! */  
  Serial.println("------------------------------------");
  Serial.print  ("Gain:         "); Serial.println("Auto");
  Serial.print  ("Timing:       "); Serial.println("13 ms");
  Serial.println("------------------------------------");
}

int SetMoistureThreshold(String threshold)
{
    MoistureThreshold = threshold.toInt();
    return 1;
}

int SetDeviceName(String NewName)
{
    DeviceName = NewName;
    return 1;
}

void setup(void) 
{
  Serial.begin(9600);
  
  /* Initialise the sensor */
  if(!tsl.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  dht.begin();
  
  pinMode(WaterPlantLEDpin, OUTPUT);
  
  Particle.variable("humidity", hum);
  Particle.variable("temperature", temp);
  Particle.variable("SoilMoisture", SoilMoisture);
  Particle.variable("Light", Light);
  
  Particle.function("MoistureThreshold", SetMoistureThreshold);
  Particle.function("DeviceName", SetDeviceName);
}


void loop(void) 
{  
  /* Get a new sensor event */ 
  sensors_event_t event;
  tsl.getEvent(&event);
  
  hum = dht.getHumidity();
  temp = dht.getTempCelcius();
  SoilMoisture = analogRead(SoilMoisturePin);
  Light = event.light;
  
  /* Display the results (light is measured in lux) */
  if (event.light)
  {
    
    Serial.print(event.light); 
    Serial.print(" lux, ");
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.print(" Celsius, ");
    Serial.print("Soil Moisture: ");
    Serial.println(SoilMoisture);
    
    
    
    if (SoilMoisture < MoistureThreshold)
    {
        digitalWrite(WaterPlantLEDpin, HIGH);
        if (waternotified == false)
        {
        Particle.publish("WaterPlants", "Water");
        waternotified = true;
        Serial.println("notified");
        }
    }
    else 
    {
        digitalWrite(WaterPlantLEDpin, LOW);
        waternotified = false;
    }
  }
  else
  {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
  }
  delay(2000);
}
