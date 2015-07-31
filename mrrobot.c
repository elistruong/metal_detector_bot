/**
 * Code for metal detector robot
 * @author: Steven Truong and Christoph Sachse
 */


// Instance Variables

// metal detection variables 
int LMOTOR = P1_6;
int RMOTOR = P2_1;
bool METAL_DETECTED;

// variables for actions 
int GLED = /* pin for blinking LED */;
int MPOW = 64;		 				// set motors to use only 25% power 
int STOP = 0;
int DISTANCE;						// keeps track of how far we've moved 

void setup () 
{
	pinMode(LMOTOR, OUTPUT);
	pinMode(RMOTOR, OUTPUT);
}

/**
 * Helper function that returns a boolean depending on the input that indicates whether metal is being detected or not 
 * @param  input - integer type that stores a value from our target pin (this target pin will send information on whether we're dectecting metal or not)
 * @return       - boolean type : true if we detected metal, false otherwise 
 */
void bool detect_metal(int input) 
{
	// conditional statement that defines metal detection
	if (/* condition */) 
	{
		/* code */
	} 
	else 
	{
		return false;
	}
}

void bool detect_collision(int input) {
	// conditional statement that defines collision detection 
	if (/* condition */)
	{
		/* code */
	} 
	else
	{
		return false;
	}
}

void loop () 
{
	// state 0 (default) move straight by turning motors
	analogWrite(LMOTOR, MPOW);
	analogWrite(RMOTOR, MPOW);
	 
	// state 1	(collision case) happens when a collision is detected - action: calculate and store random angle 
	if (detect_collision(/* input */))
	{
		/* code */
	}
	// state 2	(detected metal) happens when metal is detected - action: stop, blink, and make sounds 
	if (detect_metal(/* input */))
	{	
		analogWrite(LMOTOR, STOP);
		analogWrite(RMOTOR, STOP);
		// stop and blink lights 
	}
	// state 3	(respond to collision) happens after a collision is detected - action: adjust our angle until no collision is detected 

}