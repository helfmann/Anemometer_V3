#define int_number 0                     // INT0 on digital pin 2
volatile int16_t pwm = 0; //pwm value
volatile int16_t trig = 0; //timer value
#define pin 2 //pin the interrupt is attached to
volatile byte pulses;
unsigned long timeold;
unsigned int rpm;
float velocity;
unsigned int pulsesperturn = 1;




void setup() {
Serial.begin(9600);               
attachInterrupt(int_number, int_event, RISING);      
pinMode(pin, INPUT); //set the pin to input
 pulses = 0;
}        


void loop()
{
   if (millis() - timeold >= 1000){
        /*Uptade every one second, this will be equal to reading frecuency (Hz).*/
        //Don't process interrupts during calculations
        detachInterrupt(0);
        //Note that this would be 60*1000/(millis() - timeold)*pulses if the interrupt
        //happened once per revolution
        rpm = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulses;
        timeold = millis();
        pulses = 0;
        velocity = 0.0010 * rpm * 0.432724;
        //Write it out to serial port
       // Serial.print("RPM = ");
        Serial.println("Velocity of FumeHood 1:");
        Serial.println(velocity,2);
       // updateDisplay(rpm);
        //Restart the interrupt processing
        attachInterrupt(int_number, int_event, RISING);    
    }
}


void int_event(void) {

   pulses++;
}        

     
