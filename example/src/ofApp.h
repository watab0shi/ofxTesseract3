#pragma once

#include "ofMain.h"
#include "ofxTesseract.h"


// OcrAsset
//--------------------------------------------------------------------------------
struct OcrAsset
{
  OcrAsset( string _imgPath, string _lang, ofxTesseract::Mode _mode )
  : lang( _lang )
  , mode( _mode )
  {
    img.load( _imgPath );
    img.setImageType( OF_IMAGE_GRAYSCALE );
    img.update();
  }
  
  ofImage            img;
  string             lang;
  ofxTesseract::Mode mode;
};


// ofApp
//--------------------------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();
  void exit();
  
  ofxTesseract       tess;
  vector< OcrAsset > assets;
  
  string             ocr( ofxTesseract& _tess, OcrAsset& _asset );
};
