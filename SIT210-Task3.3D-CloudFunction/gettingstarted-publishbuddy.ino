int led = D6;
void myHandler(const char *event, const char *data); // forward declaration

// We start with the setup function.

void setup() {
	// This part is mostly the same:
	pinMode(led,OUTPUT); // Our LED pin is output (lighting up the LED)

	// Here we are going to subscribe to your buddy's event using Particle.subscribe
	Particle.subscribe("Deakin_RIOT_SIT210_Photon_Buddy", myHandler);
	// Subscribe will listen for the event buddy_unique_event_name and, when it finds it, will run the function myHandler()
	// (Remember to replace buddy_unique_event_name with your buddy's actual unique event name that they have in their firmware.)
	// myHandler() is declared later in this app.
}


void loop() {

}


// Now for the myHandler function, which is called when the cloud tells us that our buddy's event is published.
void myHandler(const char *event, const char *data)
{
	if (strcmp(data,"wave")==0) {
		digitalWrite(led,HIGH);
		delay(200);
		digitalWrite(led,LOW);
		delay(200);
		digitalWrite(led,HIGH);
		delay(200);
		digitalWrite(led,LOW);
		delay(200);
		digitalWrite(led,HIGH);
		delay(200);
		digitalWrite(led,LOW);
	}
}