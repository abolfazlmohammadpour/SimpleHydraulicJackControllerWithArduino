// Definition Some Macros For Input And Output Devices
#define StartKeyPin 2
#define StopKeyPin 3

#define SensorPin 4
#define MicroSwitchPin 5

#define FirstValveOpenPin 6
#define FirstValveClosePin 7
#define SecondValveOpenPin 8
#define SecondValveClosePin 9

#define ProgramModePin 10

#ifdef ARDUINO_AVR_LEONARDO
#define FirstValveOpenKeyPin 14
#define FirstValveCloseKeyPin 15
#define SecondValveOpenKeyPin 16
#define SecondValveCloseKeyPin A0
#elif ARDUINO_AVR_UNO
#define FirstValveOpenKeyPin 11
#define FirstValveCloseKeyPin 12
#define SecondValveOpenKeyPin 13
#define SecondValveCloseKeyPin A0
#endif
// Definition Some Macros For MicroSwitch Status
#define EnableStatusOfMicroSwitch LOW
#define DisableStatusOfMicroSwitch HIGH

// Definition Some Macros Fro Sensor Status
#define EnableStatusOfSensor HIGH
#define DisableStatusOfSensor LOW

// Definition Some Macros For Working With Valves
#define TimeToOpenFirstValve 15000
#define TimeToCloseFirstValve 15000

#define TimeToOpenSecondValve 7500
#define TimeToCloseSecondValve 7500

#define EnableStatusOfFirstValveOpen HIGH
#define DisableStatusOfFirstValveOpen LOW
#define EnableStatusOfFirstValveClose HIGH
#define DisableStatusOfFirstValveClose LOW

#define EnableStatusOfSecondValveOpen HIGH
#define DisableStatusOfSecondValveOpen LOW
#define EnableStatusOfSecondValveClose HIGH
#define DisableStatusOfSecondValveClose LOW

#define ManualMode HIGH
#define AutomaticMode LOW

#define EnableStatusOfManualKey LOW
#define DisableStatusOfManualKey HIGH

// Definition Some Variables About Key Access For Start And Stop Key
bool AccessForUsingStartKey = true;
bool AccessForUsingStopKey = false;

void FirstValveOpenProgram(void);
void FirstValveCloseProgram(void);

void SecondValveOpenProgram(void);
void SecondValveCloseProgram(void);

void FindTrailerProgram(void);
void FindHomeProgram(void);

void StartProgram(void);
void StopProgram(void);

void AutomaticModeProgram(void);
void ManualModeProgram(void);

void setup(void) {
  pinMode((uint8_t)StartKeyPin, (uint8_t)INPUT_PULLUP);
  pinMode((uint8_t)StopKeyPin, (uint8_t)INPUT_PULLUP);

  pinMode((uint8_t)SensorPin, (uint8_t)INPUT);
  pinMode((uint8_t)MicroSwitchPin, (uint8_t)INPUT_PULLUP);

  pinMode((uint8_t)FirstValveOpenPin, (uint8_t)OUTPUT);
  pinMode((uint8_t)FirstValveClosePin, (uint8_t)OUTPUT);

  pinMode((uint8_t)SecondValveOpenPin, (uint8_t)OUTPUT);
  pinMode((uint8_t)SecondValveClosePin, (uint8_t)OUTPUT);

  pinMode((uint8_t)ProgramModePin, (uint8_t)INPUT_PULLUP);

  pinMode((uint8_t)FirstValveOpenKeyPin, (uint8_t)INPUT_PULLUP);
  pinMode((uint8_t)FirstValveCloseKeyPin, (uint8_t)INPUT_PULLUP);
  pinMode((uint8_t)SecondValveOpenKeyPin, (uint8_t)INPUT_PULLUP);
  pinMode((uint8_t)SecondValveCloseKeyPin, (uint8_t)INPUT_PULLUP);
}

void loop(void) {
  while (digitalRead((uint8_t)ProgramModePin) == (int)ManualMode) {
    ManualModeProgram();
  }
  while (digitalRead((uint8_t)ProgramModePin) == (int)AutomaticMode) {
    AutomaticModeProgram();
  }
}

void FirstValveOpenProgram(void) {
  digitalWrite((uint8_t)FirstValveOpenPin, (uint8_t)EnableStatusOfFirstValveOpen);
  delay((unsigned long int)TimeToOpenFirstValve);
  digitalWrite((uint8_t)FirstValveOpenPin, (uint8_t)DisableStatusOfFirstValveOpen);
}
void FirstValveCloseProgram(void) {
  digitalWrite((uint8_t)FirstValveClosePin, (uint8_t)EnableStatusOfFirstValveClose);
  delay(TimeToCloseFirstValve);
  digitalWrite((uint8_t)FirstValveClosePin, (uint8_t)DisableStatusOfFirstValveClose);
}

void SecondValveOpenProgram(void) {
  digitalWrite((uint8_t)SecondValveOpenPin, (uint8_t)EnableStatusOfSecondValveOpen);
  delay((unsigned long int)TimeToOpenSecondValve);
  digitalWrite((uint8_t)SecondValveOpenPin, (uint8_t)DisableStatusOfSecondValveOpen);
}
void SecondValveCloseProgram(void) {
  digitalWrite((uint8_t)SecondValveClosePin, (uint8_t)EnableStatusOfSecondValveClose);
  delay((unsigned long int)TimeToCloseSecondValve);
  digitalWrite((uint8_t)SecondValveClosePin, (uint8_t)DisableStatusOfSecondValveClose);
}

void FindTrailerProgram(void) {
  while (true) {
    if (digitalRead((uint8_t)SensorPin) == (int)DisableStatusOfSensor) {
      digitalWrite((uint8_t)FirstValveClosePin, (uint8_t)EnableStatusOfFirstValveClose);
    } else if (digitalRead((uint8_t)SensorPin) == (int)EnableStatusOfSensor) {
      digitalWrite((uint8_t)FirstValveClosePin, (uint8_t)DisableStatusOfFirstValveClose);

      break;
    } else if (digitalRead((uint8_t)ProgramModePin) == (int)ManualMode) {
      digitalWrite((uint8_t)FirstValveClosePin, (uint8_t)DisableStatusOfFirstValveClose);

      break;
    }
  }
}

void FindHomeProgram(void) {
  while (true) {
    if (digitalRead((uint8_t)MicroSwitchPin) == (int)DisableStatusOfMicroSwitch) {
      digitalWrite((uint8_t)FirstValveClosePin, (uint8_t)EnableStatusOfFirstValveClose);
    } else if (digitalRead((uint8_t)MicroSwitchPin) == (int)EnableStatusOfMicroSwitch) {
      digitalWrite((uint8_t)FirstValveClosePin, (uint8_t)DisableStatusOfFirstValveClose);

      break;
    } else if (digitalRead((uint8_t)ProgramModePin) == (int)ManualMode) {
      digitalWrite((uint8_t)FirstValveClosePin, (uint8_t)DisableStatusOfFirstValveClose);

      break;
    }
  }
}

void StartProgram(void) {
  if (AccessForUsingStartKey) {
    if (digitalRead((uint8_t)StartKeyPin) == LOW) {
      delay(250);
      if (digitalRead((uint8_t)StartKeyPin) == HIGH) {
        FirstValveOpenProgram();
        SecondValveOpenProgram();
        FindTrailerProgram();

        AccessForUsingStartKey = false;
        AccessForUsingStopKey = true;
      }
    }
  }
}

void StopProgram(void) {
  if (AccessForUsingStopKey) {
    if (digitalRead((uint8_t)StopKeyPin) == LOW) {
      delay(250);
      if (digitalRead((uint8_t)StopKeyPin) == HIGH) {
        FirstValveOpenProgram();
        SecondValveCloseProgram();
        FindHomeProgram();

        AccessForUsingStartKey = true;
        AccessForUsingStopKey = false;
      }
    }
  }
}

void AutomaticModeProgram(void) {
  StartProgram();
  StopProgram();
}

void ManualModeProgram(void) {
  if (digitalRead((uint8_t)FirstValveOpenKeyPin) == (int)EnableStatusOfManualKey) {
    digitalWrite((uint8_t)FirstValveOpenPin, (uint8_t)EnableStatusOfFirstValveOpen);
  }
  if (digitalRead((uint8_t)FirstValveOpenKeyPin) == (int)DisableStatusOfManualKey) {
    digitalWrite((uint8_t)FirstValveOpenPin, (uint8_t)DisableStatusOfFirstValveOpen);
  }

  if (digitalRead((uint8_t)FirstValveCloseKeyPin) == (int)EnableStatusOfManualKey) {
    digitalWrite((uint8_t)FirstValveClosePin, (uint8_t)EnableStatusOfFirstValveClose);
  }
  if (digitalRead((uint8_t)FirstValveCloseKeyPin) == (int)DisableStatusOfManualKey) {
    digitalWrite((uint8_t)FirstValveClosePin, (uint8_t)DisableStatusOfFirstValveClose);
  }

  if (digitalRead((uint8_t)SecondValveOpenKeyPin) == (int)EnableStatusOfManualKey) {
    digitalWrite((uint8_t)SecondValveOpenPin, (uint8_t)EnableStatusOfSecondValveOpen);
  }
  if (digitalRead((uint8_t)SecondValveOpenKeyPin) == (int)DisableStatusOfManualKey) {
    digitalWrite((uint8_t)SecondValveOpenPin, (uint8_t)DisableStatusOfSecondValveOpen);
  }

  if (digitalRead((uint8_t)SecondValveCloseKeyPin) == (int)EnableStatusOfManualKey) {
    digitalWrite((uint8_t)SecondValveClosePin, (uint8_t)EnableStatusOfSecondValveClose);
  }
  if (digitalRead((uint8_t)SecondValveCloseKeyPin) == (int)DisableStatusOfManualKey) {
    digitalWrite((uint8_t)SecondValveClosePin, (uint8_t)DisableStatusOfSecondValveClose);
  }
}