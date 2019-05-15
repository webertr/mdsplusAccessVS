#pragma once

#include <iostream>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

class Kirana
{

private:
	short byteDepth;              // Number of bytes per pixel
	short compressionType;        // Compression type

	int magicNumber,              // magic Number to read at begining ("SVF")
		imageNum,                 // number of images
		imageWidth,               // width of image in pixels
		imageHeight,              // height of image in pixels
		frameZeroSize,            // Size of frame 0
		frameZeroOffset,          // Frame 0 offset
		headerSize,               // size of header in bytes
		metaDataSize,             // size of meta data block (images)
		imageInfoSize,            // size of image info structure
		imageSeqSize,             // Size of image sequence
		offsetBytes,              //  number of bytes offset for the file
		setupDataSize,            // Size of xml setup block
		versionNum,               // Version number
		cropRowLow,               // The crop row value on the bottom
		cropRowHigh,              // The crop row value in the top
		cropColHigh,              // The crop value on the far right
		cropColLow;               // The crop value on the far left

	long metaData,                // Offset of meta data block
		setupData,                // Offset of xml setup block
		imageInfo,                // Offset of image info structure
		imageSeq;                 // Offset for image sequence

	std::string fileName;         // The file name

	static const int FRAME_NUMBER = 180; // Number of frame in kirana image  

	/* sizes and offset for all 180 frame */
	int frameSizeArray[FRAME_NUMBER];
	int frameOffset[FRAME_NUMBER];

	short* data;             // Pointer to all frames.

public:

	int width;               // The width of the frame in pixels
	int height;              // The height of the frame in pixels
	int frameNum;            // The Number of frames.
	int frameSize;           // Size of an image in...

	Kirana(std::string fileNameParam="K:\Kirana Videos\2018\180215\KirImage_0001.SVF");
	~Kirana();
	gsl_matrix* getImage(int imageNumber);
	void saveImage(int imageNumber, std::string fileName);
	void saveVideo(std::string fileName);
	void setCropRow(int rowLow, int rowHigh);
	void setCropCol(int colLow, int colHigh);

};

