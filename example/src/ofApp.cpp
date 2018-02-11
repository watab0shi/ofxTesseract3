#include "ofApp.h"


// setup
//------------------------------------------------------------
void ofApp::setup()
{
  assets.emplace_back( "images/eng.png",      "eng", ofxTesseract::BLOCK );
  assets.emplace_back( "images/jpn.png",      "jpn", ofxTesseract::BLOCK );
  assets.emplace_back( "images/jpn_vert.png", "jpn", ofxTesseract::BLOCK_VERT );
  
  for( auto& a : assets ) ofLog() << endl << ocr( tess, a );
}


// ocr
//------------------------------------------------------------
string ofApp::ocr( ofxTesseract& _tess, OcrAsset& _asset )
{
  _tess.setup( "", false, _asset.lang );
  _tess.setMode( _asset.mode );
  
  string text = _tess.findText( _asset.img.getPixels() );
  
  _tess.clear();
  
  return text;
}


// update
//------------------------------------------------------------
void ofApp::update()
{
}


// draw
//------------------------------------------------------------
void ofApp::draw()
{
  ofSetColor( 255 );
  
  int y = 0;
  for( auto& a : assets )
  {
    a.img.draw( 0, y );
    y += a.img.getHeight() + 10;
  }
}


// exit
//------------------------------------------------------------
void ofApp::exit()
{
  // should close tesseract before exiting!
  tess.close();
}