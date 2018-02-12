#include "ofApp.h"


// setup
//------------------------------------------------------------
void ofApp::setup()
{
  ocr.setup( "eng", ofxTesseract::BLOCK );
  
  ofSetFrameRate( 60 );
}


// draw
//------------------------------------------------------------
void ofApp::draw()
{
  if( img.isAllocated() )
  {
    ofSetColor( 255 );
    img.draw( 0, 50 );
    ofDrawBitmapStringHighlight( text, img.getWidth() + 10, 65 );
  }
  
  ofSetColor( 0 );
  ofDrawBitmapStringHighlight( "Drag an image file into this window", 10, 20 );
  ofDrawBitmapStringHighlight( "FPS : " + ofToString( ofGetFrameRate(), 2 ), 10, 40 );
}


// dragEvent
//------------------------------------------------------------
void ofApp::dragEvent( ofDragInfo _dragInfo )
{
  if( _dragInfo.files.empty() ) return;
  
  for( auto path : _dragInfo.files )
  {
    string ext = ofToLower( ofFile( path ).getExtension() );
    
    if( ext == "jpg" || ext == "png" || ext == "gif" )
    {
      img.load( path );
      text = "";
      
      ocr.start( &img.getPixels(), &text );
      return;
    }
    else
    {
      ofLog() << "Invalid extension! drag jpg or png or gif file!";
    }
  }
}


// exit
//------------------------------------------------------------
void ofApp::exit()
{
  // wait for thread
  while( ocr.isThreadRunning() ) ;
  
  // should close tesseract before exiting!
  ocr.close();
}
