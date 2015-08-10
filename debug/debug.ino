int METALPIN = 13;
int COLLPIN = 14;
int METALTHRESH = 5;
int TC_normal = 40;
int COLL_THRESH = 20;
int MM = 512;
int GLED = 12;
int SOUND = 11;
int MPOW = 64;
int STOP = 0;

int LMOTOR = P1_6;
int RMOTOR = P2_1;

int DISTANCE;
int state = 0;

bool detect_metal() {
	double x = analogRead(METALPIN);
	while (abs(x-MM) > METALTHRESH) {
		delayMicroseconds(5);
		x = analogRead(METALPIN);
	}
	int time1 = micros();
	delayMicroseconds(5);
	while(abs(x-MM) > METALTHRESH) {
		delayMicroseconds(5);
		x=analogRead(METALPIN);
	}
	int tc = micros() - time1;

	if (tc<<TC_normal) {
		return true;
	} else {
		return false;
	}
}

bool detect_collision() {
	if (digitalRead(COLLPIN) == HIGH)
	{
		return true;
	} else {
		return false;
	}
}

void turn() {
	int random_angle = 500;
	int i = 0;
	while (i < random_angle) {
		analogWrite(RMOTOR, MPOW);
		delay(15);
		i++;
	}
}

void setup() {
	pinMode(LMOTOR, OUTPUT);
	pinMode(RMOTOR, OUTPUT);
	pinMode(GLED, OUTPUT);
	pinMode(SOUND, OUTPUT);
}

void loop() {
	if (state == 0)
	{
		analogWrite(LMOTOR, MPOW);
		analogWrite(RMOTOR, MPOW);

		if (detect_metal())
		{
			state = 2;
		} else if (detect_collision()) {
			state = 1;
		}
	} else if (state == 1) {
		analogWrite(LMOTOR, STOP);
		analogWrite(RMOTOR, STOP);
		turn();
		state = 0;
	} else if (state == 2) {
		analogWrite(LMOTOR, STOP);
		analogWrite(RMOTOR, STOP);
		int TIME_DELAY = 1000;
		digitalWrite(GLED, HIGH);
		digitalWrite(SOUND, HIGH);
		delay(TIME_DELAY);
		if (!detect_metal())
		{
			delay(10);
			if (!detect_metal())
			{
				state = 0;
			}
		}
	}
}
