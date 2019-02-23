


#ifndef raw12_processing
#define raw12_proceesing

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>




namespace Image_Processing 
{
	enum Process{
	 LINEAR,
	 BILINEAR,
	 SODAK
	};

    enum Channel {
     RED,
     GR1,
     GR2,
     BLU
    };

   class Image_Operating
   { 
    int height;
      int width;
        uint8_t * REDImage;      
        uint8_t * GREEN0Image;   
        uint8_t * GREEN1Image;   
        uint8_t * BLUEImage;        
        uint32_t length;
        uint8_t * bufferImage;
        uint8_t * arrayImage;
        uint8_t * COLORImage;
     public:

     Image_Operating(char *inputfilename, int width, int height);
    // ~Image_Operating();

     int Channel_Sepration();
     void CHANNEL_To_PMM();
     void Debayering_Image();
     int PMM();
     int PMG();



   };


}


   #endif