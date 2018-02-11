#include "ofxTesseract.h"


// setup
//------------------------------------------------------------
void ofxTesseract::setup( string _dataPath, bool _absolute, string _language )
{
  // this has to be done in setup() instead of a constructor
  // because the OF data path isn't ready during construction
  string absoluteTessdataPath = _absolute ? _dataPath : ofToDataPath( _dataPath, true );
  
//  setenv( "TESSDATA_PREFIX", absoluteTessdataPath.c_str(), 1 );
  tess.Init( absoluteTessdataPath.c_str(), _language.c_str() );
  
//  tess.SetInputName( "" );
  setMode( AUTO );
  
  bInit = true;
}

// setWhitelist
//------------------------------------------------------------
void ofxTesseract::setVariable( string _varName, string _value )
{
  tess.SetVariable( _varName.c_str(), _value.c_str() );
}

// setWhitelist
//------------------------------------------------------------
void ofxTesseract::setWhitelist( string _whitelistCharacters )
{
  setVariable( "tessedit_char_whitelist", _whitelistCharacters );
}

// setBlacklist
//------------------------------------------------------------
void ofxTesseract::setBlacklist( string _blacklistCharacters )
{
  setVariable( "tessedit_char_blacklist", _blacklistCharacters );
}

// setMode
//------------------------------------------------------------
void ofxTesseract::setMode( Mode _mode )
{
  tess.SetPageSegMode( ( tesseract::PageSegMode )_mode );
}

// getMode
//------------------------------------------------------------
ofxTesseract::Mode ofxTesseract::getMode( string _modeName )
{
  if     ( _modeName == "AUTO"       ) return AUTO;
  else if( _modeName == "COLUMN"     ) return COLUMN;
  else if( _modeName == "BLOCK"      ) return BLOCK;
  else if( _modeName == "BLOCK_VERT" ) return BLOCK_VERT;
  else if( _modeName == "LINE"       ) return LINE;
  else if( _modeName == "WORD"       ) return WORD;
  else if( _modeName == "CHAR"       ) return CHAR;
  else if( _modeName == "SPARSE"     ) return SPARSE;
  else                                 return AUTO;
}

// findText
//------------------------------------------------------------
string ofxTesseract::findText( ofImage& _img )
{
  ofRectangle roi( 0, 0, _img.getWidth(), _img.getHeight() );
  return findText( _img, roi );
}

string ofxTesseract::findText( ofImage& _img, ofRectangle& _roi )
{
  ofPixels& pixels = _img.getPixels();
  return findText( pixels, _roi );
}

string ofxTesseract::findText( ofPixels& _pixels )
{
  ofRectangle roi( 0, 0, _pixels.getWidth(), _pixels.getHeight() );
  return findText( _pixels, roi );
}

string ofxTesseract::findText( ofPixels& _pixels, ofRectangle& _roi )
{
  int bytesPerPixel = _pixels.getBytesPerPixel();
  return tess.TesseractRect( _pixels.getData(), bytesPerPixel, _pixels.getWidth() * bytesPerPixel,
                             _roi.x, _roi.y, _roi.width, _roi.height );
}

// findTextHocr
//------------------------------------------------------------
string ofxTesseract::findTextHocr( ofImage& _img )
{
  ofRectangle roi( 0, 0, _img.getWidth(), _img.getHeight() );
  return findTextHocr( _img, roi );
}

string ofxTesseract::findTextHocr( ofImage& _img, ofRectangle& _roi )
{
  ofPixels& pixels        = _img.getPixels();
  int       bytesPerPixel = pixels.getBytesPerPixel();
  
  tess.SetImage( pixels.getData(), _img.getWidth(), _img.getHeight(), bytesPerPixel, pixels.getWidth() * bytesPerPixel );
  tess.SetRectangle( _roi.x, _roi.y, _roi.width, _roi.height );
  
  return tess.GetHOCRText( 0 );
}

// clear
//------------------------------------------------------------
void ofxTesseract::clear()
{
  tess.Clear();
}

// close
//------------------------------------------------------------
void ofxTesseract::close()
{
  if( bInit ) tess.End();
}
