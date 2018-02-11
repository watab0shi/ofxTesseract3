//
// Original src
// https://github.com/kylemcdonald/ofxTesseract
//
// You Need to copy the traineddata what you want to use
//
// [lang].traineddata
//
// to   data/tessdata
// from ofxTessarect/libs/tesseract/copy_to_data_folder/tessdata

#pragma once

#include <tesseract/baseapi.h>
#include "ofMain.h"


// ofxTesseract
//--------------------------------------------------------------------------------
class ofxTesseract
{
public:
  enum Mode
  {
    AUTO       = tesseract::PSM_AUTO,
    COLUMN     = tesseract::PSM_SINGLE_COLUMN,
    BLOCK      = tesseract::PSM_SINGLE_BLOCK,
    BLOCK_VERT = tesseract::PSM_SINGLE_BLOCK_VERT_TEXT,
    LINE       = tesseract::PSM_SINGLE_LINE,
    WORD       = tesseract::PSM_SINGLE_WORD,
    CHAR       = tesseract::PSM_SINGLE_CHAR,
    SPARSE     = tesseract::PSM_SPARSE_TEXT
  };
  
  // dataPath is where to find a folder with tessdata inside
  // default arguments assume bin/data/tessdata/eng.traineddata
  void setup( string _dataPath = "", bool _absolute = false, string _language = "eng" );
  
  // you must call these after setup, contrary to the tesseract-ocr docs
  void setVariable( string _varName, string _value );
  
  // whitelist means only those characters are used
  void setWhitelist( string _whitelistCharacters );
  
  // blacklist means none of those characters are used
  void setBlacklist( string _blacklistCharacters );
  
  // provides a hint for how to segment things
  // by default this is ofxTesseract::AUTO
  void setMode( Mode _mode );
  
  // transform a mode name into a constant, for loading from XML files
  static Mode getMode( string _modeName );
  
  // finally, do OCR on an image, or on an image within an roi
  // make sure your text is at least 10 pixels tall
  // OF_IMAGE_COLOR and OF_IMAGE_GRAYSCALE are both fine
  string findText( ofImage& _img );
  string findText( ofImage& _img, ofRectangle& _roi );
  
  // raw pixel data? why not!
  string findText( ofPixels& _pixels );
  string findText( ofPixels& _pixels, ofRectangle& _roi );
  
  // HOCR goodness
  string findTextHocr( ofImage& _img );
  string findTextHocr( ofImage& _img, ofRectangle& _roi );
  
  // clear stored data
  void clear();
  
  // close
  void close();
  
protected:
  tesseract::TessBaseAPI tess;
  bool                   bInit;
};