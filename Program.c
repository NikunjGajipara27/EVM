#include <LiquidCrystal_I2C.h>
#include <ezButton.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

ezButton greenButton(26);
ezButton yellowButton(25);
ezButton blueButton(27);
ezButton resultButton(18);
ezButton resetButton(19);

const int greenLedPin = 2;    // LED pin for green button
const int yellowLedPin = 0;   // LED pin for yellow button
const int blueLedPin = 4;     // LED pin for blue button
const int buzzerPin = 5;      // Buzzer pin

int teamA = 0;
int teamB = 0;
int teamC = 0;

bool isVotingCompleted = false;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  greenButton.setDebounceTime(15);
  yellowButton.setDebounceTime(15);
  blueButton.setDebounceTime(15);
  resultButton.setDebounceTime(15);
  resetButton.setDebounceTime(15);

  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.print("Start voting APP");
  lcd.setCursor(0, 1);
  lcd.print("BJP or CONGRESS");

  Serial.println("Result will be shown after the black button is pressed!");
}

void loop() {
  greenButton.loop();
  yellowButton.loop();
  blueButton.loop();
  resultButton.loop();
  resetButton.loop();

  if (!isVotingCompleted) {
    if (greenButton.isPressed() || yellowButton.isPressed() || blueButton.isPressed()) {
      // If any voting button is pressed, activate the buzzer
      digitalWrite(buzzerPin, HIGH);
      delay(100); // Buzzer ON time
      digitalWrite(buzzerPin, LOW);
      
      if (greenButton.isPressed()) {
        teamA++;
        digitalWrite(greenLedPin, HIGH); // Turn on green LED
        delay(100); // Delay for visual feedback
        digitalWrite(greenLedPin, LOW); // Turn off green LED
      } else if (yellowButton.isPressed()) {
        teamB++;
        digitalWrite(yellowLedPin, HIGH); // Turn on yellow LED
        delay(100); // Delay for visual feedback
        digitalWrite(yellowLedPin, LOW); // Turn off yellow LED
      } else if (blueButton.isPressed()) {
        teamC++;
        digitalWrite(blueLedPin, HIGH); // Turn on blue LED
        delay(100); // Delay for visual feedback
        digitalWrite(blueLedPin, LOW); // Turn off blue LED
      }
    } else if (resultButton.isPressed()) {
      isVotingCompleted = true;
      voteCount();
      delay(2000);
      lcd.clear();
      Serial.println("voting completed");
    }
  } else {
    determineWinner();
  }

  if (resetButton.isPressed()) {
    resetVoting();
  }

  delay(10);
}

void voteCount() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BJP");
  lcd.setCursor(0, 1);
  lcd.print("CONGRESS");
  lcd.setCursor(13, 0);
  lcd.print("APP");
  lcd.setCursor(10, 0);
  lcd.print(teamA/2);
  lcd.setCursor(10, 1);
  lcd.print(teamB/2);
  lcd.setCursor(14, 1);
  lcd.print(teamC/2);
  lcd.setCursor(4, 2);
  delay(1000);
}

void determineWinner() {
  lcd.setCursor(0, 0);

  if (teamA > teamB && teamA > teamC) {
    lcd.print("BJP is the ");
    lcd.setCursor(0, 1);
    lcd.print("Winner");
  } else if (teamB > teamA && teamB > teamC) {
    lcd.print("Congress is the ");
    lcd.setCursor(0, 1);
    lcd.print("Winner");
  } else if (teamC > teamA && teamC > teamB) {
    lcd.print("APP is the ");
    lcd.setCursor(0, 1);
    lcd.print("Winner");
  } else {
    lcd.print("There was a tie.");
    lcd.setCursor(0, 1);
  }
}

void resetVoting() {
  teamA = 0;
  teamB = 0;
  teamC = 0;
  isVotingCompleted = false;
  lcd.clear();
  lcd.print("Voting reset.");
  delay(2000);
  lcd.clear();
  lcd.print("Start voting APP");
  lcd.setCursor(0, 1);
  lcd.print("BJP or CONGRESS");
}
