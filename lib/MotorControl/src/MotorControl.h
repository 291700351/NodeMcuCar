#ifndef MotorControl_h
#define MotorControl_h

#include "Arduino.h"
#include <L298N.h>

class MotorControl
{
  public:
    MotorControl(uint8_t leftEN, uint8_t rightEN, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4);
    void leftMove(int speed);
    void leftStop();
    unsigned short getLeftSpeed();
    boolean isLeftMoving();
    void rightMove(int speed);
    void rightStop();
    unsigned short getRightSpeed();
    boolean isRightMoving();
    void reset();

    void forward();
    void backward();
    void turnLeft();
    void turnRight();
    void stop();
    



  private:
    L298N *_leftMotor;
    L298N *_rightMotor;
};
#endif