//
// You Need to copy the traineddata
//
// eng.traineddata
//
// to   data/tessdata
// from ofxTessarect3/libs/tesseract/copy_to_data_folder/tessdata

#pragma once

#include "ofMain.h"
#include "ofxTesseract.h"


// ThreadedOcr
//--------------------------------------------------------------------------------
class ThreadedOcr : public ofThread
{
public:
  void setup( string _lang, ofxTesseract::Mode _mode )
  {
    tess.setup( "", false, _lang );
    tess.setMode( _mode );
  }
  
  void start( ofPixels* _pixels, string* _dstText )
  {
    bFinished = false;
    pixels    = _pixels;
    text      = _dstText;
    time      = ofGetElapsedTimef();
    
    ofThread::startThread();
    ofLog() << "[threadedOcr] start";
  }
  
  void stop()
  {
    tess.clear();
    ofThread::stopThread();
    
    bFinished = true;
    time      = ofGetElapsedTimef() - time;
    ofLog() << "[threadedOcr] stop ( time : " << time << " )";
  }
  
  bool isFinished()
  {
    return bFinished;
  }
  
  void close()
  {
    tess.close();
  }
  
private:
  void threadedFunction()
  {
    *text = tess.findText( *pixels );
    ofLog() << "[threadedOcr] " << endl << *text;
    
    stop();
  }
  
  ofxTesseract tess;
  ofPixels*    pixels;
  string*      text;
  bool         bFinished;
  float        time;
};


// ofApp
//--------------------------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
  void setup();
  void draw();
  void dragEvent( ofDragInfo _dragInfo );
  void exit();
  
  ThreadedOcr ocr;
  ofImage     img;
  string      text;
};
