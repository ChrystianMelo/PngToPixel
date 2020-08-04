#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#pragma warning(disable : 4996)
#include <string>  
#include <iostream>  
#include <sstream>  
#include "libraries/lodepng.h"
#include "libraries/lodepng.cpp"
#include <experimental/filesystem>  

using namespace std;
namespace fs = std::experimental::filesystem;


vector<string> getFilesFrom(const fs::path& directory)//get all files in directory ~pathToShow

{
	vector<string> files;//all filenames in the directory will be here
	int level = 0;
	if (fs::exists(directory) && fs::is_directory(directory))
	{
		auto lead = std::string(level * 3, ' ');
		for (const auto& entry : fs::directory_iterator(directory))
		{
			auto filename = entry.path().filename();
			if (fs::is_directory(entry.status()))
			{
				cout << lead << "[+] " << filename << "\n";
				level++;
				cout << "\n";
			}
			else if (fs::is_regular_file(entry.status())) {
				files.push_back(filename.generic_string());//+1 file found
			}
			else {
				cout << lead << " [?]" << filename << "\n";
			}
		}
	}
	return files;
}

void pngToPix(string directory) {//using lodepng.h to transfrom png file to pix vet
	std::vector<unsigned char> image;//vet of pixels as RGBARGBA..
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, directory);//return 1 == error
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;//error
	else std::cout << directory << " - " << image.size() << "px" << "\n";//success
}

int main() {
	const fs::path baseDirectory = ("images/");//all imgs will be in this dir
	vector<string> files = getFilesFrom(baseDirectory);
	for (int i = 0; i < files.size(); i++)
		pngToPix(baseDirectory.generic_string() + files[i]);
}