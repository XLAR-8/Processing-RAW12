#include "processing/imageprocessing.h"

 char INPUT_FILE[] = "index.raw12";


 int WIDTH = 4096;
 int HEIGHT = 3072;

int main() 
{
    std::cout << " ** ALL SET TO GO ** " << std::endl;

    std::cout << " - Reading file: " << INPUT_FILE << std::endl;
    Image_Processing::Image_Operating obj1(INPUT_FILE, WIDTH, HEIGHT);

    std::cout << "-- Seprating Channels --" << std::endl;
    obj1.Channel_Sepration();

    std::cout << "-  grayscale-images ready "<< std::endl;
    obj1.CHANNEL_To_PMM();


    std::cout << "- Debayering  image: "<< std::endl;
    std::cout << "- Colouring  image : "<< std::endl;
    obj1.Debayering_Image();
    //obj1.WriteColored(LINEAR_RESULT, Debayer::DebayeringAlgorithm::LINEAR);

    //std::cout << "[All operations done]" << std::endl;

    return 0;
}