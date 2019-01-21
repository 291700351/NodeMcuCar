#include "MotorControl.h"

MotorControl ::MotorControl(uint8_t leftEN, uint8_t rightEN,
                            uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)
{
  _leftMotor = new L298N(leftEN, in1, in2);
  _rightMotor = new L298N(rightEN, in3, in4);
}

void MotorControl::leftMove(int speed)
{
  _leftMotor->setSpeed(abs(speed));
  if (speed < 0)
  {
    _leftMotor->backward();
  }
  else if (speed > 0)
  {
    _leftMotor->forward();
  }
  else
  {
    this->leftStop();
  }
}
void MotorControl::leftStop()
{
  _leftMotor->stop();
}

unsigned short MotorControl::getLeftSpeed()
{
  return _leftMotor->getSpeed();
}
boolean MotorControl::isLeftMoving()
{
  return _leftMotor->isMoving();
}

void MotorControl::rightMove(int speed)
{
  _rightMotor->setSpeed(abs(speed));
  if (speed < 0)
  {
    _rightMotor->backward();
  }
  else if (speed > 0)
  {
    _rightMotor->forward();
  }
  else
  {
    this->rightStop();
  }
}
void MotorControl::rightStop()
{
  _rightMotor->stop();
}

unsigned short MotorControl::getRightSpeed()
{
  return _rightMotor->getSpeed();
}
boolean MotorControl::isRightMoving()
{
  return _rightMotor->isMoving();
}

void MotorControl::reset()
{
  _leftMotor->reset();
  _rightMotor->reset();
}

void MotorControl::forward()
{
  this->stop();
  _leftMotor->forward();
  _rightMotor->forward();
}
void MotorControl::backward()
{
  this->stop();
  _leftMotor->backward();
  _rightMotor->backward();
}
void MotorControl::turnLeft()
{
  this->stop();
  _leftMotor->backward();
  _rightMotor->forward();
}
void MotorControl::turnRight()
{
  this->stop();
  _leftMotor->forward();
  _rightMotor->backward();
}
void MotorControl::stop()
{
  _leftMotor->stop();
  _rightMotor->stop();
}
