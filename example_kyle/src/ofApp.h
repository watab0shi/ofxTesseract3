//
// Original src
// https://github.com/kylemcdonald/ofxTesseract
//
// You Need to copy traineddata
//
// eng.traineddata
//
// to   data/tessdata
// from ofxTessarect3/libs/tesseract/copy_to_data_folder/tessdata

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxTesseract.h"


class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();
  
  ofxTesseract     tess;
  ofImage          img, scaled;
  string           ocrResult;
  vector< string > lines;
  string           runOcr( float scale, int medianSize );
  
  ofxPanel         gui;
  ofxFloatSlider   scale;
  ofxIntSlider     medianSize;
  ofxButton        process;
  
  void             processButtonPressed();
};
