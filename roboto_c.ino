/**
 * Code for metal detector robot
 * @author: Steven Truong and Christoph Sachse
 */

////////////////// INSTANCE VARIABLES ///////////////////
int METALPIN = 13;              // pin that indicates metal detection 
int COLLPIN = 14;             // pin that indicates collision 
int METALTHRESH = 5;            // threshold that determines metal detection
int TC_normal = 40;             
int COLL_THRESH = 20;
int MM = 512;
int GLED = 12;                // pin for blinking LED 
int SOUND = 11;               // pin for speaker to make noise 
int MPOW = 64;                // set motors to use only 25% power 
int STOP = 0;               // cut off power to motors (stop)

int LMOTOR = P1_6;              // pin of the left motor 
int RMOTOR = P2_1;              // pin of the right motor   


int DISTANCE;						// keeps track of how far we've moved 
int state=0;            // initial state machine is in (moves forward)

////////////////// HELPER METHODS ///////////////////

/**
 * Helper function that returns a boolean depending on the input that indicates whether metal is being detected or not 
 * @param  input - integer type that stores a value from our target pin (this target pin will send information on whether we're dectecting metal or not)
 * @return       - boolean type : true if we detected metal, false otherwise 
 */
bool detect_metal(){   
  //measure out one period.
  //First finds starting zero, records, finds second zero
  double x=analogRead(METALPIN);
  while(abs(x-MM)>METALTHRESH){
    delayMicroseconds(5);
    x=analogRead(METALPIN);
  }
  int time1=micros();
  delayMicroseconds(5);
  while(abs(x-MM)>METALTHRESH){
    delayMicroseconds(5);
    x=analogRead(METALPIN);
  }
  int tc=micros()-time1;
  // conditional statement that defines metal detection
  if (tc<TC_normal){
    return true;
  } else {	
    return false;
  }
}

/**
 * Helper function that returns a boolean depending on the input that indicates whether the robot has collided with something
 * @param  input - intger type that stores a value from our target pin (this target pin will send information on whether we're blocked or not)
 * @return       - boolean type: true if we're impeded, false otherwise 
 */
bool detect_collision() {
  // conditional statement that defines collision detection 
  if (digitalRead(COLLPIN)==HIGH){
    // we hit something, switch activated: return true!
    return true;
  } else {
    return false;
  }
}

void turn() {
  int random_angle = 500;//random(10)*1000;	        // turn for random number of second s
  int i = 0;
  while (i < random_angle) {
    analogWrite(RMOTOR, MPOW);
    delay(15);
    i++;
  }
}

////////////////// SETUP FUNCTION ///////////////////

void setup() {
  pinMode(LMOTOR, OUTPUT);
  pinMode(RMOTOR, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(SOUND, OUTPUT);
}

////////////////// LOOP FUNCTION ///////////////////

void loop () 
{
  if(state==0){
    analogWrite(LMOTOR, MPOW);
    analogWrite(RMOTOR, MPOW);
    if (detect_metal()){
      state=2;
    } else if (detect_collision()){
      state=1;
    }
  } else if (state==1){
    //stop moving
    analogWrite(LMOTOR, STOP);
    analogWrite(RMOTOR, STOP);
    //turn around
    turn();
    state=0;  
  } else if (state==2){
     // state 2	(detected metal) happens when metal is detected - action: stop, blink, and make sounds 
      //stop moving
      analogWrite(LMOTOR, STOP);
      analogWrite(RMOTOR, STOP);
      // to alert make noise and flash LED lights 
      int TIME_DELAY = 1000; 
      digitalWrite(GLED, HIGH);
      digitalWrite(SOUND, HIGH);
      delay(TIME_DELAY);
      //If we can transition out
      if (!detect_metal()){
        delay(10);
        if(!detect_metal()){
          state=0;
        }
      }
    }
}
