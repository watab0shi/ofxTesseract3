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
// from ofxTessarect/libs/tesseract/copy_to_data_folder/tessdata

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "ofApp.h"


// setup
//------------------------------------------------------------
void ofApp::setup()
{
  example_1();
  example_2();
  example_3();
  example_4();
  example_5();
}

// 1. Basic example
//--------------------------------------------------------------------------------
void ofApp::example_1()
{
  tesseract::TessBaseAPI api;
  
  // Initialize tesseract-ocr with Japanese, with tessdata path
  if( api.Init( ofToDataPath( "" ).c_str(), "jpn" ) )
  {
    ofLog( OF_LOG_ERROR, "Could not initialize tesseract." );
    ofExit();
  }
  
  ofImage img;
  img.load( "images/jpn.png" );
  int      imgW          = img.getWidth();
  int      imgH          = img.getHeight();
  ofPixels pixels        = img.getPixels();
  int      bytesPerPixel = pixels.getBytesPerPixel();
  
  // Set Image
  api.SetImage( pixels.getData(), imgW, imgH, bytesPerPixel, imgW * bytesPerPixel );
  
  // Get OCR result
  string result = api.GetUTF8Text();
  ofLog( OF_LOG_NOTICE, "OCR output: %s", result.c_str() );
  
  // Destroy used object and release memory
  api.End();
}

// 2. GetComponentImages example
//--------------------------------------------------------------------------------
void ofApp::example_2()
{
  ofImage img;
  img.load( "images/jpn.png" );
  int      imgW          = img.getWidth();
  int      imgH          = img.getHeight();
  ofPixels pixels        = img.getPixels();
  int      bytesPerPixel = pixels.getBytesPerPixel();
  
  tesseract::TessBaseAPI api;
  api.Init( ofToDataPath( "" ).c_str(), "jpn" );
  
  // Set Image
  api.SetImage( pixels.getData(), imgW, imgH, bytesPerPixel, imgW * bytesPerPixel );
  
  Boxa* boxes = api.GetComponentImages( tesseract::RIL_TEXTLINE, true, NULL, NULL );
  
  ofLog( OF_LOG_NOTICE, "Found %d textline image components.", boxes->n );
  
  for( int i = 0; i < boxes->n; ++i )
  {
    BOX* box = boxaGetBox( boxes, i, L_CLONE );
    api.SetRectangle( box->x, box->y, box->w, box->h );
    
    string ocrResult = api.GetUTF8Text();
    int    conf      = api.MeanTextConf();
    
    ofLog( OF_LOG_NOTICE, "Box[%d]: x=%d, y=%d, w=%d, h=%d, confidence: %d, text: %s",
          i, box->x, box->y, box->w, box->h, conf, ocrResult.c_str() );
  }
  
  api.End();
}

// 3. Result iterator example
//--------------------------------------------------------------------------------
void ofApp::example_3()
{
  ofImage img;
  img.load( "images/eng.png" );
  int      imgW          = img.getWidth();
  int      imgH          = img.getHeight();
  ofPixels pixels        = img.getPixels();
  int      bytesPerPixel = pixels.getBytesPerPixel();
  
  tesseract::TessBaseAPI api;
  api.Init( ofToDataPath( "" ).c_str(), "eng" );
  api.SetImage( pixels.getData(), imgW, imgH, bytesPerPixel, imgW * bytesPerPixel );
  api.Recognize( 0 );
  
  tesseract::ResultIterator    *ri    = api.GetIterator();
  tesseract::PageIteratorLevel  level = tesseract::RIL_WORD;
  
  if( ri != nullptr )
  {
    do
    {
      const string word = ri->GetUTF8Text( level );
      float        conf = ri->Confidence( level );
      int          x1, y1, x2, y2;
      ri->BoundingBox( level, &x1, &y1, &x2, &y2 );
      
      ofLog( OF_LOG_NOTICE, "word: '%s';  \tconf: %.2f; BoundingBox: %d,%d,%d,%d;", word.c_str(), conf, x1, y1, x2, y2 );
    }
    while( ri->Next( level ) );
  }
  
  api.End();
}

// 4. Orientation and script detection (OSD) example
//--------------------------------------------------------------------------------
void ofApp::example_4()
{
  tesseract::Orientation      orientation;
  tesseract::WritingDirection direction;
  tesseract::TextlineOrder    order;
  float                       deskew_angle;
  
  ofImage img;
  img.load( "images/eng.png" );
  int      imgW          = img.getWidth();
  int      imgH          = img.getHeight();
  ofPixels pixels        = img.getPixels();
  int      bytesPerPixel = pixels.getBytesPerPixel();
  
  tesseract::TessBaseAPI api;
  api.Init( ofToDataPath( "" ).c_str(), "eng" );
  api.SetPageSegMode( tesseract::PSM_AUTO_OSD );
  api.SetImage( pixels.getData(), imgW, imgH, bytesPerPixel, imgW * bytesPerPixel );
  api.Recognize( 0 );
  
  tesseract::PageIterator* it = api.AnalyseLayout();
  it->Orientation( &orientation, &direction, &order, &deskew_angle );
  
  ofLog( OF_LOG_NOTICE, "\nOrientation: %d\nWritingDirection: %d\nTextlineOrder: %d\nDeskew angle: %.4f\n",
         orientation, direction, order, deskew_angle );
  
  api.End();
}

// 5. Example of iterator over the classifier choices for a single symbol
//--------------------------------------------------------------------------------
void ofApp::example_5()
{
  ofImage img;
  img.load( "images/jpn.png" );
  int      imgW          = img.getWidth();
  int      imgH          = img.getHeight();
  ofPixels pixels        = img.getPixels();
  int      bytesPerPixel = pixels.getBytesPerPixel();
  
  tesseract::TessBaseAPI api;
  api.Init( ofToDataPath( "" ).c_str(), "jpn" );
  api.SetImage( pixels.getData(), imgW, imgH, bytesPerPixel, imgW * bytesPerPixel );
  api.SetVariable( "save_blob_choices", "T" );
  api.Recognize( NULL );
  
  tesseract::ResultIterator    *ri    = api.GetIterator();
  tesseract::PageIteratorLevel  level = tesseract::RIL_SYMBOL;
  
  if( ri != nullptr )
  {
    do
    {
      const string symbol = ri->GetUTF8Text( level );
      float        conf   = ri->Confidence( level );
      if( !symbol.empty() )
      {
        ofLog( OF_LOG_NOTICE, "symbol %s conf: %f", symbol.c_str(), conf );
        
        bool indent = false;
        tesseract::ChoiceIterator ci( *ri );
        do
        {
          const string choice = ci.GetUTF8Text();
          ofLog( OF_LOG_NOTICE, "       %s conf: %f", choice.c_str(), ci.Confidence() );
          indent = true;
        }
        while( ci.Next() );
      }
      
      ofLog( OF_LOG_NOTICE, "---------------------------------------------\n" );
    }
    while( ( ri->Next( level ) ) );
  }
  
  api.End();
}
