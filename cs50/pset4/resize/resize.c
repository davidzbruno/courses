#include <stdio.h>
#include <stdlib.h>
// #include <stdbool.h>

#include "bmp.h"

int main(int argc, char *argv[]){

    /*
    Your program should accept exactly three command-line arguments, whereby
    - the first (n) must be a positive integer less than or equal to 100,
    - the second must be the name of a BMP to be resized, and
    - the third must be the name of the resized version to be written.
    
    If your program is not executed with such, it should remind the user of 
    correct usage, as with fprintf (to stderr), and main should return 1.
    */
    if(argc != 4){
        fprintf(stderr,"Usage: %s [resize-value] [inputfile-name].bmp [outputfile-name].bmp\n",argv[0]);
        return 1;
    }

    if(atoi(argv[1]) < 1){
        fprintf(stderr,"Resize Value [%s] must be positive integer\n",argv[1]);
        return 1;
    }

    FILE *ifp, *ofp;
    ifp = fopen(argv[2], "r");
    ofp = fopen(argv[3], "w");

    if (ifp == NULL || ofp == NULL) {
        fprintf(stderr, "Can't open the file(s) %s %s!\n",argv[2],argv[3]);
        return 1;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, ifp);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, ifp);
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0){
        fclose(ofp);
        fclose(ifp);
        fprintf(stderr, "Unsupported file format %s.\n",argv[2]);
        return 4;
    }

    int scale = atoi(argv[1]), j = 0, k = 0, inPadding = 0, outPadding = 0;
    inPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    int resize_width = bi.biWidth, resize_height = bi.biHeight;
    //modify output header fields to work with the newly enlarged picture
    if(scale > 1){
        // might not need to change these
        // bf.bfSize*=scale;
        // bi.biSize*=scale;
        // bi.biBitCount*=scale;
        // bi.biSizeImage = ((sizeof(RGBTRIPLE) * newWidth) + outPadding) * abs(newHeight);
        // f.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        resize_width = bi.biWidth*scale;
        resize_height = bi.biHeight*scale;
    }
    outPadding = (4 - (resize_width * sizeof(RGBTRIPLE)) % 4) % 4;

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, ofp);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, ofp);
    
    RGBTRIPLE line[resize_width * sizeof(RGBTRIPLE)];

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; ++i){
        for (j = 0; j < bi.biWidth; ++j){
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, ifp);

            //add the pixel N times to the array -- scales horizontally
            for(k = 0; k < scale; ++k){
                line[(j*scale)+k] = triple;
            }
        }
        //skip over padding in input
        fseek(ifp, inPadding, SEEK_CUR);

        //adds the new line N times to the output -- scales vertically
        for(j = 0; j < scale; ++j){
            fwrite(line, sizeof(RGBTRIPLE), 1, ofp);

            //add additional padding in output
            for (k = 0; k < outPadding; ++k)
            {
                fputc(0x00, ofp);
            }
        }
    }

    fclose(ifp);
    fclose(ofp);
    return 0;
}