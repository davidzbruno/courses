#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "bmp.h"

bool isColor(RGBTRIPLE pixel, RGBTRIPLE target){
    if(pixel.rgbtBlue == target.rgbtBlue && pixel.rgbtGreen == target.rgbtGreen && pixel.rgbtRed == target.rgbtRed)
        return true;
    return false;
}

void makeDarker(RGBTRIPLE *pixel){
    pixel->rgbtBlue -= 0xf0;
    pixel->rgbtGreen -= 0xff;
    pixel->rgbtRed -= 0xff;
}

int main(int argc, char *argv[]){

    /*
    If your program is executed with fewer or more than two command-line arguments,
    it should remind the user of correct usage, as with fprintf (to stderr), and main should return 1.
    */
    if(argc != 3){
        fprintf(stderr,"Usage: %s [inputfile-name].bmp [outputfile-name].bmp",argv[0]);
        return 1;
    }

    char *infile = argv[1];
    char *outfile = argv[2];
    FILE *ifp, *ofp;
    /*
    If the input file cannot be opened for reading, your program should
    inform the user as much, as with fprintf (to stderr), and main should return 2.
    */
    ifp = fopen(infile, "r");
    if (ifp == NULL) {
        fprintf(stderr, "Can't open input file %s!\n",argv[1]);
        return 2;
    }

    /*
    If the output file cannot be opened for writing, your program should
    inform the user as much, as with fprintf (to stderr), and main should return 3.
    */
    ofp = fopen(argv[2], "w");
    if(ofp == NULL){
        fprintf(stderr, "Can't open output file %s!\n", argv[2]);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, ifp);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, ifp);

    /*
    If the input file is not a 24-bit uncompressed BMP 4.0, your program should 
    inform the user as much, as with fprintf (to stderr), and main should return 4.
    */  
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0){
        fclose(ofp);
        fclose(ifp);
        fprintf(stderr, "Unsupported file format [input].\n");
        return 4;
    }

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, ofp);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, ofp);
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    RGBTRIPLE red = {0x00,0x00,0xff};
    RGBTRIPLE white = {0xff,0xff,0xff};

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++){
        for (int j = 0; j < bi.biWidth; j++){
            RGBTRIPLE triple;

            fread(&triple, sizeof(RGBTRIPLE), 1, ifp);

            //change color of red pixels else write them to outfile normally    
            if(isColor(triple,red) || isColor(triple,white)){
                fwrite(&white, sizeof(RGBTRIPLE), 1, ofp);
            }
            else{
                makeDarker(&triple);
                fwrite(&triple, sizeof(RGBTRIPLE), 1, ofp);
            }
        }

        fseek(ifp, padding, SEEK_CUR);
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, ofp);
        }
    }

    fclose(ifp);
    fclose(ofp);
    return 0;
}