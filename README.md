# Processing Raw12 file

The applications process a RAW12 sample file contained in sample directory. The code extract grayscale channels from sample.raw12 in the form of Red , Green and blue channels. 
The final image is debayered using Bilinear interpolation. All the images are stored into .ppm format and grayscale in .pgm.

## Required Tools

For building purpose , The code uses cmake tools (preferred version if 3.5.0 or below)

installation command for linux



``` 
   sudo apt -y install cmake

   Cmake --version
    
    
```             


## Building instructions



``` 
      git clone ..
      cd to cloned repo directory
      mkdir build 
      cmake.. 
      ./sample

    
```               
