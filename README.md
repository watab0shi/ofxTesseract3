# ofxTesseract3 is an addon for openFrameworks that provides access to the Tesseract OCR library v3.0
![ofxaddons_thumbnail](ofxaddons_thumbnail.png)
  
Original source is [kylemcdonald/ofxTesseract](https://github.com/kylemcdonald/ofxTesseract).

## Generate Project
![Project Generator](images/01.png)  
  
Open in Xcode  
![Project Generator](images/02.png)  
  
Drag & Drop `libs/leptonica/lib` and `libs/tesseract/lib` to Navigator from Finder  
![Project Generator](images/03.png)  
  
Drag & Drop `libtesseract.3.dylib` and `liblept.5.dylib` to `Project > Build Phases > Link Binary With Libraries` from Navigator  
![Project Generator](images/04.png)  
  
Finally, You Need to copy the traineddata what you want to use  
  
`[lang].traineddata`  
  
to   `data/tessdata`  
from `ofxTessarect/libs/tesseract/copy_to_data_folder/tessdata`  
  
There are only `eng`, `jpn` and `osd` data.
If you want other languages, please download from [here](https://github.com/tesseract-ocr/tesseract/wiki/Data-Files#data-files-for-version-304305).  