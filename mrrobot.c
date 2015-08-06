/**
 * Code for metal detector robot
 * @author: Steven Truong and Christoph Sachse
 */


////////////////// INSTANCE VARIABLES ///////////////////

// metal detection variables 
int LMOTOR = P1_6;
int RMOTOR = P2_1;
bool METAL_DETECTED;

// variables for actions 
int GLED = /* pin for blinking LED */;
int SOUND = /* pin to speaker to make noise */;
int MPOW = 64;		 				// set motors to use only 25% power 
int STOP = 0;
int DISTANCE;						// keeps track of how far we've moved 

////////////////// HELPER METHODS ///////////////////

/**
 * Helper function that returns a boolean depending on the input that indicates whether metal is being detected or not 
 * @param  input - integer type that stores a value from our target pin (this target pin will send information on whether we're dectecting metal or not)
 * @return       - boolean type : true if we detected metal, false otherwise 
 */
bool detect_metal(int input) 
{
	// conditional statement that defines metal detection
	if (/* pin_X > or < threshhold */) 
	{
		// metal detected return true! 
		return true;
	} 
	else 
	{	
		// metal not detected return false
		return false;
	}
}

/**
 * Helpter function that returns a boolean depending on the input that indicates whether the robot has collided with something
 * @param  input - intger type that stores a value from our target pin (this target pin will send information on whether we're blocked or not)
 * @return       - boolean type: true if we're impeded, false otherwise 
 */
bool detect_collision(int input) {
	// conditional statement that defines collision detection 
	if (/* pin_Y > or < threshold */)
	{
		// we hit something, switch activated: return true!
		return true;
	} 
	else
	{
		return false;
	}
}

/**
 * Helper function that returns nothing. When called, stops the robot from moving.
 */
void stop_moving() {
	analogWrite(LMOTOR, STOP);
	analogWrite(RMOTOR, STOP);
}

/**
 * Helper function that returns nothing, when callsed starts the robot's movement.
 */
void start_moving() {
	analogWrite(LMOTOR, MPOW);
	analogWrite(RMOTOR, MPOW);
}

/**
 * Helper function that returns nothing. When called, alerts via flashing LED lights and making noise.
 */
void alert_detection() {
	// to alert make noise and flash LED lights 
	int TIME_DELAY = 1000; 								// default to one second 
	digitalWrite(GLED, HIGH);
	digitalWrite(SOUND, HIGH);
	delay(TIME_DELAY);
}


void turn() {
	int random_angle = random(10)*1000;						// turn for random number of second s
	int i = 0;
	while (i < random_angle) 
	{
		analogWrite(RMOTOR, MPOW);
		i++;
	}
}

////////////////// SETUP FUNCTION ///////////////////

void setup () 
{
	pinMode(LMOTOR, OUTPUT);
	pinMode(RMOTOR, OUTPUT);
	pinMode(GLED, OUTPUT);
	pinMode(SOUND, OUTPUT);
}

////////////////// LOOP FUNCTION ///////////////////

void loop () 
{
	 
	// state 2	(detected metal) happens when metal is detected - action: stop, blink, and make sounds 
	if (detect_metal(/* pass in input from pin_X */))
	{	
		analogWrite(LMOTOR, STOP);
		analogWrite(RMOTOR, STOP);
		// stop and blink lights 
		stop_moving();
		alert_detection();
	}

	
	// state 1	(collision case) happens when a collision is detected - action: calculate and store random angle 
	if (detect_collision(/* input coming from pin_Y */))
	{
		// go to state 3 
		stop_moving();
		turn();
	}


	// state 0 (default) move straight by turning motors
	start_moving();

}