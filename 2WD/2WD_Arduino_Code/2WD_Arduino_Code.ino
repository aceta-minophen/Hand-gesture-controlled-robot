#include <Wire.h>

/*Motor Driver*/
int motorLpin1 = 4;
int motorLpin2 = 5;
int motorRpin1 = 2;
int motorRpin2 = 3;

int speedL = 10;
int speedR = 9;

int x;
int y;

int pitch;
int roll;

int X;
int Y;

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

	analogWrite(speedR, 0);
	analogWrite(speedL, 0);
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

		if (val <= 128 && val>0) {
			x = val;
		}
		else if (val > 128) {
			y = val;
		}

		/*Serial.print("X: ");
		Serial.print(x);
		Serial.print("      ");
		Serial.print("Y: ");
		Serial.println(y);*/

		pitch = x / 0.711;
		roll = (y - 128) / 0.711;

		X = 0.6 * pitch;
		Y = 0.6 * roll;


		if (roll >= 135) {
			analogWrite(speedL, 0);
			analogWrite(speedR, X);
			Serial.println("Turning left");
		}
		else if (roll <= 45) {
			analogWrite(speedR, 0);
			analogWrite(speedL, X);
			Serial.println("Turning right");
		}
		else {
			analogWrite(speedL, X);
			analogWrite(speedR, X);
			Serial.println("Heading Straight");
		}


		Serial.print("Pitch: ");
		Serial.print(X);
		Serial.print("      ");
		Serial.print("Roll: ");
		Serial.println(Y);
	}
	Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
	Wire.write("Hello NodeMCU");  /*send string on request */
}