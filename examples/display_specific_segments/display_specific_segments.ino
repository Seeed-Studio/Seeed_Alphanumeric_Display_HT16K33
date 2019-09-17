/*
   display_basic.ino
   Example for displaying specific segments on a tube.


   Author     : dagwoodland
   Create Time: Sep 2019

   The MIT License (MIT)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include "Wire.h"
#include "grove_alphanumeric_display.h"

// Keeps track of the current stage of tube 2's animation.
int currentSegment = 0;

// The frames of tube 2's animation.
uint16_t tubeTwoFrames[] = {
  SEGMENT_TOP,
  SEGMENT_TOP_LEFT,
  SEGMENT_TOP_LEFT_DIAGONAL,
  SEGMENT_TOP_VERTICAL,
  SEGMENT_TOP_RIGHT_DIAGONAL,
  SEGMENT_TOP_RIGHT,
  SEGMENT_MIDDLE_LEFT,
  SEGMENT_MIDDLE_RIGHT,
  SEGMENT_BOTTOM_LEFT,
  SEGMENT_BOTTOM_LEFT_DIAGONAL,
  SEGMENT_BOTTOM_VERTICAL,
  SEGMENT_BOTTOM_RIGHT_DIAGONAL,
  SEGMENT_BOTTOM_RIGHT,
  SEGMENT_BOTTOM
};

// -----------------------------------------------------------
// TIP - You can use shorthand notation to avoid long lines.
// Shorthand is simply 'SEG_' and then the first letter of each
// word. Eg. 'SEGMENT_TOP_LEFT_DIAGANOL' becomes 'SEG_TLD'.
// -----------------------------------------------------------

// Reference to the Seeed_Digital_Tube.
Seeed_Digital_Tube tube;

void setup() {
  // Setup wire using default I2C pins.
  Wire.begin();

  // If using four digital tubes, use this configuration.
  tube.setTubeType(TYPE_4, TYPE_4_DEFAULT_I2C_ADDR);

  // If using two digital tubes, use this configuration.
  // tube.setTubeType(TYPE_2,TYPE_2_DEFAULT_I2C_ADDR);

  tube.setBrightness(15);
  tube.setBlinkRate(BLINK_OFF);
}

// Display the top and bottom segments on the first tube.
void displayTubeOne() {
  // To display specific segments add together their values.
  tube.setTubeSegments(FIRST_TUBE, SEGMENT_TOP + SEGMENT_BOTTOM);
}

// Display an animation going through all 14 segments in turn.
void displayTubeTwo() {
  // Increment tube 2's animation frame.
  currentSegment += 1;

  // Restart the animation if it has finished.
  if (currentSegment >= 14) {
    currentSegment = 0;
  }

  // Display the current frame of tube 2's animation.
  tube.setTubeSegments(SECOND_TUBE, tubeTwoFrames[currentSegment]);
}

void loop() {
  // Clear the tube's buffer. Using tube.clearBuf() prevents
  // the display blinking because the display is not updated
  // until tube.display() is called, unlike tube.clear()
  tube.clearBuf();

  displayTubeOne();
  displayTubeTwo();

  // Display the new contents of both tube's buffers.
  tube.display();

  delay(200);
}
