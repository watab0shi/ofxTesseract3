#pragma once

// small excerpt from forthcoming of-cv utility/addon

#include "ofConstants.h"
#include "ofImage.h"
#include "cv.h"

namespace cv
{
  inline int getCvImageType( const ofImageType& _ofType )
  {
    switch( _ofType )
    {
      case OF_IMAGE_GRAYSCALE:   return CV_8UC1;
      case OF_IMAGE_COLOR:       return CV_8UC3;
      case OF_IMAGE_COLOR_ALPHA: return CV_8UC4;
      default:                   return CV_8UC1;
    }
  }
  
  inline Mat getMat( ofImage& _img )
  {
    int cvImageType = getCvImageType( _img.getPixels().getImageType() );
    return Mat( _img.getHeight(), _img.getWidth(), cvImageType, _img.getPixels().getData(), 0 );
  }
  
  inline int forceOdd( int _x )
  {
    return ( _x / 2 ) * 2 + 1;
  }
  
  inline void medianBlur( ofImage& _img, int _size )
  {
    _size   = forceOdd( _size );
    Mat mat = getMat( _img );
    medianBlur( mat, mat, _size );
    _img.update();
  }
};