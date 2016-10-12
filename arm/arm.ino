#include "arm.h";

void setup() {} //fuck you setup

void loop() {
  CommandResult result;
  uint16_t commandId;
  size_t commandSize;
  int16_t commandData;
  uint32_t watchdogTimer_us = 0; //increment this value everytime we don't get a command. When we've waited for a command for longer than our timeout value, stop all arm movement
  
  initialize();
  
  while(1)
  {
    commandSize = 0;
    commandId = 0;
    commandData = 0;//reset variables
    
    roveComm_GetMsg(&commandId, &commandSize, &commandData);
    passEndefToBase();
    
    if((commandSize == 1 || commandSize == 2) && commandId != 0) //command packets come in 1 or 2 bytes
    {
      watchdogTimer_us = 0; //reset watchdog timer since we received a command
      
      if(commandId == ArmStop)
      {
        result = stopArm();
      }
      else if(commandId == ArmJ1)
      {
        result = moveJ1(commandData);  
      }
      else if(commandId == ArmJ2)
      {
        result = moveJ2(commandData);
      }
      else if(commandId == ArmJ3)
      {
        result = moveJ3(commandData);
      }
      else if(commandId == ArmJ4)
      {
        result = moveJ4(commandData);
      }
      else if(commandId == ArmJ5)
      {
        result = moveJ5(commandData);
      }
      else if(commandId == ArmJ6)
      {
        result = moveJ6(commandData);
      }
      else if(commandId == Gripper || commandId == Drill) //if the message is meant for the endefector, pass it along
      {
        sendMsgToEndef(commandId, commandSize, &commandData);
      }

      

      if(result != Success)
      {
        //todo: if there's ever any telemetry about what to do when the command isn't successful, this is where we'll send telemetry back about it
      }
    }//end if

    //if no messages were recieved, increment our watchdog counter. If the counter has gone over a certain period of time since we last got a transmission, cease all movement.
    //This is to keep the arm from committing suicide on the environment/the rover if communications ever get interrupted while it's in the middle of moving
    else 
    {
      uint8_t microsecondDelay = 10;
      delayMicroseconds(microsecondDelay);

      watchdogTimer_us += microsecondDelay;

      if(watchdogTimer_us >= WATCHDOG_TIMEOUT_US) //if more than our timeout period has passed, then kill arm movement
      {
        stopArm();
        watchdogTimer_us = 0;
      }
    }//end else
  }//end while
  
}

void initialize()
{
  roveComm_Begin(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
}

CommandResult sendMsgToEndef(uint16_t dataId, size_t dataSize, void * data)
{
  //todo: after deciding how comm between arm and endef boards shall work, implement software to pass the information
}

void passEndefToBase()
{
  //todo: after deciding how comm between arm and endef boards shall work, implement software to pass the information from endefector to base station
}

CommandResult stopArm()
{
  
}

CommandResult moveJ1(int16_t moveValue)
{
  
}

CommandResult moveJ2(int16_t moveValue)
{
  
}

CommandResult moveJ3(int16_t moveValue)
{
  
}

CommandResult moveJ4(int16_t moveValue)
{
  
}

CommandResult moveJ5(int16_t moveValue)
{
  
}

CommandResult moveJ6(int16_t moveValue)
{
  
}
