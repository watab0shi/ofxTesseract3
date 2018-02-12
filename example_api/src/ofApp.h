//
// tesseract-ocr API Examples
// https://github.com/tesseract-ocr/tesseract/wiki/APIExample
//
// You Need to copy the traineddata
//
// eng.traineddata
// jpn.traineddata
// osd.traineddata
//
// to   data/tessdata
// from ofxTessarect3/libs/tesseract/copy_to_data_folder/tessdata

#pragma once

#include "ofMain.h"


// ofApp
//--------------------------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
  void setup();
  
  void example_1();
  void example_2();
  void example_3();
  void example_4();
  void example_5();
};
