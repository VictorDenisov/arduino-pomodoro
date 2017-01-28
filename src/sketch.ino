
#define LED_PIN 13

#define INITIAL_STATE 0
#define POMODORO_STATE 1
#define SIGNALING_STATE 2

int clockState = 0;

int switchState = 1;
int prevSwitchState = 1;

int initialValue = 25;
int currentValue = 0;
unsigned long previousTime = 0;
unsigned long startedSignaling = 0;
unsigned long oneMinute = 60000;
int switchPin = 9;
int beeperPin = 10;

void playSound() {
    tone(beeperPin, 262, 200);
}

void makeFree() {
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    currentValue = 0;
    setupLights();
}

void makeBusy() {
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
}

void setupLights() {
    for (int i = 0; i < 5; ++i) {
        if (((1 << i) & currentValue) != 0) {
            digitalWrite(i, HIGH);
        } else {
            digitalWrite(i, LOW);
        }
    }
}

void setup()
{
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);

    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);

    pinMode(9, INPUT);
    digitalWrite(9, HIGH);
    currentValue = 0;
    setupLights();
    clockState = INITIAL_STATE;
    makeFree();
}

void loop()
{
    if (clockState == POMODORO_STATE) {
        unsigned long currentTime = millis();
        unsigned long diffValue = currentTime - previousTime;
        if (diffValue > oneMinute) {
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

    if (switchState != prevSwitchState && switchState == 1) {
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
