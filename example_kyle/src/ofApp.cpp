#include "ofApp.h"
#include "CvUtils.h"


void ofApp::setup()
{
  gui.setup();// most of the time you don't need a name
  
  process.addListener( this, &ofApp::processButtonPressed );
  
  gui.add( scale.setup( "scale", 2.5, 1, 4 ) );
  gui.add( medianSize.setup( "medianSize", 2, 0, 12 ) );
  gui.add( process.setup( "process" ) );
  
  tess.setup( "", false, "eng" );
  tess.setWhitelist( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.," );
  tess.setMode( ofxTesseract::AUTO );
  
  img.load( "article.png" );
  img.setImageType( OF_IMAGE_GRAYSCALE );
  img.update();
  
  processButtonPressed();
}

void ofApp::update()
{
}

void ofApp::draw()
{
  ofPushMatrix();
  {
    ofTranslate( 300, 0 );
    
    ofSetColor( 0 );
    int i = 0;
    for( auto& l : lines )
    {
      ofDrawBitmapString( l, 10, 20 + i * 12 );
      ++i;
    }
    
    ofSetColor( 255 );
    img.draw( 0, 200 );
    scaled.draw( 0, 400 );
  }
  ofPopMatrix();
  
  gui.draw();
}

// depending on the source of the text you want to OCR,
// you might need to preprocess it. here i'm doing a
// simple resize followed by a median blur.
string ofApp::runOcr( float _scale, int _medianSize )
{
  scaled = img;
  
  // resize and median blur the image
  scaled.resize( img.getWidth() * _scale, img.getHeight() * _scale);
  
  cv::medianBlur( scaled, _medianSize );
  
  return tess.findText( scaled );
}

void ofApp::processButtonPressed()
{
  ocrResult = runOcr( scale, medianSize );
  lines     = ofSplitString( ocrResult, "\n" );
}

