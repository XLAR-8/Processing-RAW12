
#include "imageprocessing.h"
 Image_Processing::Image_Operating::Image_Operating(char *inputfilename, int width, int height)
{   
 this->width = width;
 this->height = height;
	
 std::ifstream rawImage (inputfilename, std::ios::binary);
    if (rawImage) 
    {
        rawImage.seekg(0, rawImage.end);
        length = rawImage.tellg();
        rawImage.seekg(0, rawImage.beg);

     }
     else
     {
       std::cerr << "Error: Cannot open input file, exiting now!" << std::endl;
        exit(1);
     }
	


    REDImage      = new uint8_t[(width/2)*(height/2)];
    GREEN0Image   = new uint8_t[(width/2)*(height/2)];
    GREEN1Image   = new uint8_t[(width/2)*(height/2)];
    BLUEImage     = new uint8_t[(width/2)*(height/2)];

        bufferImage = new uint8_t[length];
        rawImage.read(reinterpret_cast<char*>(bufferImage), length);

        // Closes file.
        rawImage.close();

}


 int  Image_Processing::Image_Operating::Channel_Sepration()
 {
  arrayImage = new uint8_t[height*width];
  int j = 0;
        for (long long i = 0; i < length; i += 3) 
        {   arrayImage[j]   = bufferImage[i];
            arrayImage[j+1] = ((bufferImage[i+1] & 0x0F) << 4) | (bufferImage[i+2] >> 4);
            j+=2;
        }	
//std::cout<<"no. to come "<<  (int)(unsigned char)arrayImage[2]<<"  "<<(int)(unsigned char)arrayImage[3]<<"  "<<(int)(unsigned char)arrayImage[6000]<<" "<<(int)(unsigned char)arrayImage[6];
            
   int odd = 0, even = 0;
        for (long long i = 0; i < width*height; i += 2) 
        {
            if ((i % 8192) < width) {
                REDImage[even]      = arrayImage[i];
                GREEN0Image[even]   = arrayImage[i + 1];
                even++;
            } else {
                GREEN1Image[odd]    = arrayImage[i];
                BLUEImage[odd]      = arrayImage[i + 1];
                odd++;
            }
        }   

        COLORImage = new uint8_t[width*height* 3];   
 }


//void Image_Processing::Image_Operating::Display_5cross5()


void Image_Processing::Image_Operating::CHANNEL_To_PMM()
{
   
    std::ofstream RED;  
     RED.open("REDImage.pgm", std::ios::binary);   
     
     RED.write("P5 ",3);
     RED.write("2048 ",5);
     RED.write("1537 ",5);
     RED.write("255 ",4); 
    
     RED.write(reinterpret_cast<char*>(REDImage), 2048 * 1537);
    std::cout << "REDImage.pgm is ready"<<std::endl; 
      
     RED.close(); 
    
     std::ofstream GREEN0;  
     GREEN0.open("GREEN0Image.pgm", std::ios::binary);   

     GREEN0.write("P5 ",3);
     GREEN0.write("2048 ",5);
     GREEN0.write("1537 ",5);
     GREEN0.write("255 ",4); 
    
     GREEN0.write(reinterpret_cast<char*>(GREEN0Image), 2048 * 1537);
     std::cout << "GREEN0Image.pgm is ready"<<std::endl;
     
     GREEN0.close(); 
    
     std::ofstream GREEN1;  
     GREEN1.open("GREEN1Image.pgm", std::ios::binary);   

     GREEN1.write("P5 ",3);
     GREEN1.write("2048 ",5);
     GREEN1.write("1537 ",5);
     GREEN1.write("255 ",4); 
   
     GREEN1.write(reinterpret_cast<char*>(GREEN1Image), 2048 * 1537);
     std::cout << "GREEN1Image.pmm is ready"<<std::endl;
     
     GREEN1.close();

     std::ofstream BLUE;  
     BLUE.open("blue.pmm", std::ios::binary);   

     BLUE.write("P6 ",3);
     BLUE.write("2048 ",5);
     BLUE.write("1537 ",5);
     BLUE.write("255 ",4); 
   
     BLUE.write(reinterpret_cast<char*>(BLUEImage), 2048 * 1537);
     std::cout << "blue.pmm is ready"<<std::endl;
      
     BLUE.close();

}

void Image_Processing::Image_Operating::Debayering_Image()
{        



        
        
        for (long long i = 0; i < width * height; i += 2) {
            
            if (i < width * 2 || i > (width * height - width * 2) || (i % width) < 2 || (i % width) > (width - 2)) {
                // Avoids accessing invalid or inadequate pixels.
                if ((i % width * 2) < width) {
                    // Red Pixel.
                    COLORImage[i*3    ] = arrayImage[i];
                    COLORImage[i*3 + 1] = arrayImage[i + 1];
                    COLORImage[i*3 + 2] = arrayImage[i + width + 1];
                    // Green0 Pixel.
                    COLORImage[i*3 + 3] = arrayImage[i];
                    COLORImage[i*3 + 4] = arrayImage[i + 1];
                    COLORImage[i*3 + 5] = arrayImage[i + width + 1];
                } else {
                    // Green1 Pixel.
                    COLORImage[i*3    ] = arrayImage[i - width];
                    COLORImage[i*3 + 1] = arrayImage[i];
                    COLORImage[i*3 + 2] = arrayImage[i + 1];
                    // Blue Pixel.
                    COLORImage[i*3 + 3] = arrayImage[i - width];
                    COLORImage[i*3 + 4] = arrayImage[i];
                    COLORImage[i*3 + 5] = arrayImage[i + 1];
                }
            } else {
                if ((i % width * 2) < width) {
                    // Red Pixel.
                    COLORImage[i*3    ] = arrayImage[i];
                    COLORImage[i*3 + 1] = (arrayImage[i + 1] + arrayImage[i - 1] + arrayImage[i + width * 2 + 1] + arrayImage[i - width * 2 + 1]) >> 2;
                    COLORImage[i*3 + 2] = (arrayImage[i + width + 1] + arrayImage[i - width + 1] + arrayImage[i + width + 3] + arrayImage[i + width - 1]) >> 2;
                    // Green0 Pixel.
                    COLORImage[i*3 + 3] = (arrayImage[i] + arrayImage[i + 2] + arrayImage[i + width * 2] + arrayImage[i - width * 2]) >> 2;
                    COLORImage[i*3 + 4] = arrayImage[i + 1];
                    COLORImage[i*3 + 5] = (arrayImage[i + width + 1] + arrayImage[i - width + 1] + arrayImage[i + width + 3] + arrayImage[i + width - 1]) >> 2;
                } else {
                    // Green1 Pixel.
                    COLORImage[i*3    ] = (arrayImage[i - width] + arrayImage[i + width] + arrayImage[i - width + 2] + arrayImage[i - width - 2]) >> 2;
                    COLORImage[i*3 + 1] = arrayImage[i];
                    COLORImage[i*3 + 2] = (arrayImage[i + 1] + arrayImage[i - 1] + arrayImage[i + width * 2 + 1] + arrayImage[i - width * 2 + 1]) >> 2;
                    // Blue Pixel.
                    COLORImage[i*3 + 3] = (arrayImage[i - width] + arrayImage[i + width] + arrayImage[i - width + 2] + arrayImage[i - width - 2]) >> 2;
                    COLORImage[i*3 + 4] = (arrayImage[i] + arrayImage[i + 2] + arrayImage[i + width * 2] + arrayImage[i - width * 2]) >> 2;
                    COLORImage[i*3 + 5] = arrayImage[i + 1];
                }
            }
        }

     std::ofstream CLOUR;  
     CLOUR.open("COLOUR.ppm", std::ios::binary);   

     CLOUR.write("P6 ",3);
     CLOUR.write("4096 ",5);
     CLOUR.write("3072 ",5);
     CLOUR.write("255 ",4); 
   
     CLOUR.write(reinterpret_cast<char*>(COLORImage), 4096 * 3072 * 3);
     std::cout << "COLOUR.ppm is ready"<<std::endl;
      
     CLOUR.close();

        
 }       