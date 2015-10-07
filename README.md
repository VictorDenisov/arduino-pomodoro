Arduino-Pomodoro Timer
======================

This project contains code for a pomodoro timer built on arduino uno.

Description
-----------

This pomodoro time consists of:

 - Red LED - means busy, in a pomodoro.
 - Green LED - means available, out of a pomodoro.
 - Five position binary indicator which tells you how many minutes left.
 - Button which switches between in pomodoro state and out of pomodoro state.
 - Speaker - notifies you about elapsed pomodoro.

States
------

This timer has 3 states: POMODORO, SIGNALING, INITIAL.
Initially the timer is in (as you can guess) INITIAL state. If you press the
button you get into POMODORO state and the timer starts counting down 25
minutes.

If you press the button one more time before the timer elapses you are
back to INITIAL state. If the timer elapses you are in SIGNALING state.

When the timer is in SIGNALING state the speaker is beeping and the binary
indicator is flashing. The timer is in this state for 10 seconds or if you
press the button then you are back to INITIAL state.

Pin Out
-------

2 - red led, busy
3 - green led, available
4 - yellow led, 4-th position of the binary indicator
5 - yellow led, 3-th position of the binary indicator
6 - yellow led, 2-th position of the binary indicator
7 - yellow led, 1-th position of the binary indicator
8 - yellow led, 0-th position of the binary indicator
9 - button, switches states between in a pomodoro and out of a pomodoro
10 - speaker
