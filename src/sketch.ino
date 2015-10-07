
#define LED_PIN 13

#define INITIAL_STATE 0
#define POMODORO_STATE 1
#define SIGNALING_STATE 2

int clockState = 0;

int switchState = 0;
int prevSwitchState = 0;

int initialValue = 25;
int currentValue = 0;
unsigned long previousTime = 0;
unsigned long startedSignaling = 0;
int oneMinute = 60000;
int switchPin = 9;
int beeperPin = 10;

void playSound() {
	tone(beeperPin, 262, 200);
}

void makeFree() {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
}

void makeBusy() {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
}

void setupLights() {
    for (int i = 0; i < 5; ++i) {
        if (((1 << i) & currentValue) != 0) {
            digitalWrite(8 - i, HIGH);
        } else {
            digitalWrite(8 - i, LOW);
        }
    }
}

void setup()
{
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, INPUT);
    currentValue = 0;
    setupLights();
    clockState = INITIAL_STATE;
    makeFree();
    Serial.begin(9600);
}

void loop()
{
    if (clockState == POMODORO_STATE) {
        unsigned long currentTime = millis();
        if (currentTime - previousTime > oneMinute) {
            previousTime = currentTime;
            --currentValue;
        }
        setupLights();
        if (currentValue == 0) {
			playSound();
            clockState = SIGNALING_STATE;
			startedSignaling = millis();
            makeFree();
        }
    }
    if (clockState == SIGNALING_STATE) {
        unsigned long currentTime = millis();
        if (currentTime - previousTime > 300) {
            previousTime = currentTime;
            currentValue = 31 - currentValue;
			playSound();
        }
        setupLights();
		if (currentTime - startedSignaling > 10000) {
			clockState = INITIAL_STATE;
			currentValue = 0;
			setupLights();
		}
    }

    switchState = digitalRead(switchPin);
    //Serial.println(switchState);

    if (switchState != prevSwitchState && switchState == 0) {
        Serial.println("Entered switch change");
        if (clockState == INITIAL_STATE) {
            previousTime = millis();
            clockState = POMODORO_STATE;
            makeBusy();
            currentValue = initialValue;
            setupLights();
        } else {
            if ((clockState == SIGNALING_STATE) || (clockState == POMODORO_STATE)) {
                clockState = INITIAL_STATE;
                makeFree();
                currentValue = 0;
                setupLights();
            }
        }
    }
    prevSwitchState = switchState;
}
