#include <movement.h>


//Testing for the motors

//----------------------------------------------------------------------------
// Movement Setup
//
#define RME 8 //Right Motor Enable
#define RMD 23 //Right Motor Direction
#define RMQA 25 //Right Motor input A from quadrature-encoder
#define RMQB 27 //Right Motor input B from quadrature-encoder
//
#define LME 9 //Same stuff just with left motor
#define LMD 22
#define LMQA 24
#define LMQB 26
//
#define Speed 180
//
movement Robot(RMD, RME, RMQA, RMQB, LMD, LME, LMQA, LMQB, Speed);
//
//----------------------------------------------------------------------------


void setup(){
}
void loop(){

  Robot.goXinches(1);

}
