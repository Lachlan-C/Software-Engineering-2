int ledRed = D2; 
int ledGreen = D4;
int ledBlue = D6;
int LedRed(String On);

void setup() {

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  
  Particle.function("LedOn",LedOn);
}

void loop() {

}

int LedOn(String ledColour)
{
    if (ledColour == "Red")
    {
        digitalWrite(ledRed, HIGH);
        return 1;
    }
    else if (ledColour == "Green")
    {
        digitalWrite(ledGreen, HIGH);
        return 1;
    }
    else if (ledColour == "Blue")
    {
        digitalWrite(ledBlue, HIGH);
        return 1;
    }
    if (ledColour == "RedOff")
    {
        digitalWrite(ledRed, LOW);
        return 1;
    }
    else if (ledColour == "GreenOff")
    {
        digitalWrite(ledGreen, LOW);
        return 1;
    }
    else if (ledColour == "BlueOff")
    {
        digitalWrite(ledBlue, LOW);
        return 1;
    }
    else
    {
        return -1;
    }
}
