  // ---------------------------------------------------------------------------
  // Example NewPing library sketch that does a ping about 20 times per second.
  // ---------------------------------------------------------------------------
  
  #include <NewPing.h>
  
  #define TRIGGER_PIN1  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
  #define ECHO_PIN1     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
  #define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
  #define LED 53
  
  NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
  
  void setup() {
    Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
    pinMode(LED,OUTPUT);
  }
  
  
  void sense(NewPing sonar){
  
    delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    Serial.print("Distance: ");
    float cm = uS / US_ROUNDTRIP_CM;
    //float inches = .393701 * cm;
    Serial.print(cm); // Convert ping time to distance in cm and print result (0 = outside set distance range)
    Serial.println(" cm");
    if(cm < 10 && cm > 0){
      digitalWrite(LED,HIGH);
       
  }
  else{
      digitalWrite(LED,LOW);
  }
  
}
  
  void loop() {
    
    //Serial.print("Sensor 1: \n");
    sense(sonar1);
    
  }
