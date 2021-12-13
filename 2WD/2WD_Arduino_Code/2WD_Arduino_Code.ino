#include <Wire.h>

/*Motor Driver*/
int motorLpin1 = 4;
int motorLpin2 = 5;
int motorRpin1 = 2;
int motorRpin2 = 3;

int speedL = 10;
int speedR = 9;

void setup() {
	/*Motor Driver*/
	pinMode(motorLpin1, OUTPUT);
	pinMode(motorLpin2, OUTPUT);
	pinMode(motorRpin1, OUTPUT);
	pinMode(motorRpin2, OUTPUT);

	pinMode(speedL, OUTPUT);
	pinMode(speedR, OUTPUT);

	//anticlockwise
	digitalWrite(motorLpin1, HIGH); //left
	digitalWrite(motorLpin2, LOW); // left
	digitalWrite(motorRpin1, HIGH); //right
	digitalWrite(motorRpin2, LOW); //right

	Wire.begin(8);                /* join i2c bus with address 8 */
	Wire.onReceive(receiveEvent); /* register receive event */
	Wire.onRequest(requestEvent); /* register request event */
	Serial.begin(115200);           /* start serial for debug */
}

void loop() {
	//delay(100);

}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
	while (0 < Wire.available()) {
		byte low = Wire.read();
		byte high = Wire.read();
		int val = word(high, low);

		Serial.println(val);

		
	}
	Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
	Wire.write("Hello NodeMCU");  /*send string on request */
}