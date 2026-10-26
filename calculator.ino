#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

long num1 = 0;
long num2 = 0;
char operation = 0;
bool secondNumber = false;

void setup() {
  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("       ARDUINO CALCULATOR");
  Serial.println("================================");
  Serial.println("A = Addition (+)");
  Serial.println("B = Subtraction (-)");
  Serial.println("C = Multiplication (*)");
  Serial.println("D = Division (/)");
  Serial.println("# = Calculate");
  Serial.println("* = Clear");
  Serial.println();
  Serial.println("Enter first number:");
}

void loop() {

  char key = keypad.getKey();

  if (key == NO_KEY) {
    return;
  }

  // CLEAR
  if (key == '*') {
    num1 = 0;
    num2 = 0;
    operation = 0;
    secondNumber = false;

    Serial.println();
    Serial.println("Cleared!");
    Serial.println("Enter first number:");
    return;
  }

  // NUMBER
  if (key >= '0' && key <= '9') {

    if (secondNumber == false) {
      num1 = (num1 * 10) + (key - '0');

      Serial.print("First number: ");
      Serial.println(num1);
    }
    else {
      num2 = (num2 * 10) + (key - '0');

      Serial.print("Second number: ");
      Serial.println(num2);
    }

    return;
  }

  // OPERATOR
  if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {

    if (secondNumber == false) {

      operation = key;
      secondNumber = true;

      Serial.print("Operator: ");

      if (key == 'A') {
        Serial.println("+");
      }
      else if (key == 'B') {
        Serial.println("-");
      }
      else if (key == 'C') {
        Serial.println("*");
      }
      else if (key == 'D') {
        Serial.println("/");
      }

      Serial.println("Enter second number:");
    }

    return;
  }

  // CALCULATE
  if (key == '#') {

    if (operation == 0) {
      Serial.println("Please select an operator!");
      return;
    }

    long result = 0;

    if (operation == 'A') {
      result = num1 + num2;
    }

    else if (operation == 'B') {
      result = num1 - num2;
    }

    else if (operation == 'C') {
      result = num1 * num2;
    }

    else if (operation == 'D') {

      if (num2 == 0) {
        Serial.println("ERROR: Cannot divide by zero!");

        num1 = 0;
        num2 = 0;
        operation = 0;
        secondNumber = false;

        return;
      }

      result = num1 / num2;
    }

    Serial.println();
    Serial.print("RESULT = ");
    Serial.println(result);
    Serial.println();

    // Make result the first number for another calculation
    num1 = result;
    num2 = 0;
    operation = 0;
    secondNumber = false;

    Serial.println("Enter next number or press * to clear:");

    return;
  }
}