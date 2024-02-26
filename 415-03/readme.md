This project was to create a 'driving' simulation via accelerometer.

Leaning the accelerometer in the forward direction makes the green led turn on.
Leaning backward makes the red led turn on
Leaning to the left or right will make the yellow blinkers enable accordingly - and having some acceleration in either the forward or backward direction will enable the green or red LED while the blinkers are blinking.

The speeds are sent to the raspberry pi which then interprets them and sends a message back to the OLED stating the direction and if they are moving too fast around corners or too slow.
