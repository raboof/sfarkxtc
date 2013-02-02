// Basic sfArk decompressor for Mac
// Copyright 2002 Andy Inman
// Contact via: http://netgenius.co.uk or http://melodymachine.com

// This file is part of sfArkLib.
//
// sfArkLib is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// sfArkLib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with sfArkLib.  If not, see <http://www.gnu.org/licenses/>.

//  based on SDL_Test

//  Reads an existing .sfArk file and writes an sf2 file using standard file i/o
//	Return 0 if successful, 1 if some error occured.
//  Info and error messages are printed to stdout

//	Initial version,	andyi, 14-Sep-2002

char	*ThisProg = "sfArkXTm";
char	*ThisVersion = "1.01 beta";	// Version of program

// Standard includes...
#include <stdio.h>
#include <string.h>
#include <time.h>
//#include <iostream>

#include "sfArkLib.h"

// Application-supplied functions...
void msg(const char *MessageText, int Flags);				// Message display function
void UpdateProgress(int ProgressPercent);						// Progress indication
bool GetLicenseAgreement(const char *LicenseText);	// Display/confirm license
void DisplayNotes(const char *NotesFileName);				// Display notes text file

int ReportError(long error)
{
	// Display an error message, return 0 if there was no error else 1
	char *msg;

	switch (error)
	{
		case SFARKLIB_SUCCESS:	
			msg = "Successful";
			break;
		case SFARKLIB_ERR_INIT:
			msg = "Failed initialisation";
			break;
		case SFARKLIB_ERR_MALLOC:
			msg = "Memory allocation error";
			break;
		case SFARKLIB_ERR_SIGNATURE:
			msg = "Signature not found (file is corrupt or is not a sfArk file)";
			break;
		case SFARKLIB_ERR_HEADERCHECK:
			msg = "Header check fails (file is corrupt)";
			break;
		case SFARKLIB_ERR_INCOMPATIBLE:
			msg = "File was created by incompatible sfArk version (not 2.x)";
			break;
		case SFARKLIB_ERR_UNSUPPORTED:
			msg = "Unsupported feature was used";
			break;
		case SFARKLIB_ERR_CORRUPT:
			msg = "Invalid compressed data (file is corrupt)";
			break;
		case SFARKLIB_ERR_FILECHECK:
			msg = "Checksum failed (file is corrupt)";
			break;
		case SFARKLIB_ERR_FILEIO:
			msg = "File i/o failed";
			break;
		case SFARKLIB_ERR_OTHER:
			msg = "Other error";
			break;
		default:
			msg = "Undefined error";
	}
	printf("Result:	%s  errorcode %ld\n", msg, -error);

	if(error != SFARKLIB_SUCCESS) 
	{
		printf("*** FAILED ***\n");
		return 1;
	}
	else
	{
		return 0;
	}
}


// ============================ m a i n ==============================================

int main(int argc, char** argv)
{
	char InFileName[SFARKLIB_MAX_FILEPATH] = "elepiano.sfArk";//"testfile1.sfArk";
	//char InFileName[SFARKLIB_MAX_FILEPATH] = "testfile2.sfArk";
	char OutFileName[SFARKLIB_MAX_FILEPATH] = "testfile_mac.sf2";

	// Print welcome message...

	printf("======================================================================\n");
	printf("%s %s ", ThisProg, ThisVersion);
	printf("(using sfArkLib version: %d)\n", sfkl_GetVersion());
	printf("copyright (c) 1998-2002 melodymachine.com, free for non-commercial use\n");
	printf("======================================================================\n");
        
	// Open input and output files...

/******
	char *InFileName = argv[1];
	char *OutFileName = argv[2];
	// useage
	if (argc != 3)
	{
		printf("Specify input and output files on the command line, i.e:\n");
		printf("%s <InputFilename> <OutputFilename>\n", ThisProg);
		printf("Press ENTER."); //getc(stdin);
		return 1;
	}

*********/
	if (argc < 2)
	{
		printf("HINT: Drag & drop a sfArk file onto the %s icon to avoid this...\n", ThisProg);
		printf("Enter name of sfArk file to decompress and press return: \n");
	}
	else
	{
		strncpy(InFileName, argv[1], sizeof(InFileName)-1);
	}
	
	// Uncompress the file...
	printf("Uncompressing %s to %s...\n", InFileName, OutFileName);

	long StartTime = clock();
	int err = sfkl_Decode(InFileName, OutFileName);	//call decompression, report & return
        
	long TimeTaken = 1000 * (clock() - StartTime) / CLOCKS_PER_SEC;
	printf("cpu time taken %ld ms\n", TimeTaken);

	return ReportError(err);
}

// ============================================================================================
void msg(const char *MessageText, int Flags)
{
	if (Flags & SFARKLIB_MSG_PopUp)	printf("*** ");
	printf("%s\n", MessageText);
}

// ============================================================================================
void UpdateProgress(int ProgressPercent)
{
    //char ProgressBar[101];
    //int i;
    
    //for (i = 0; i < ProgressPercent; i++)
    //    ProgressBar[i] = '*';
    //for ( ; i < 100; i++)
    //    ProgressBar[i] = '-';
    //ProgressBar[100] = '\0';
        
    //printf(ProgressBar);
    //printf("\r");
    
    //printf("*");
    printf("Progress: %d%%\n", ProgressPercent);
    //if (ProgressPercent == 100)  printf("\n");
	return;
}

// ==========================================================================================
// Display/confirm license 
bool GetLicenseAgreement(const char *LicenseText)
{
        char c;
        
	printf("%s\n\nDo you agree to the above terms? (Y/N) ", LicenseText);
	//c = getc(stdin);
        c = 'y';
	while (c != 'y' && c != 'Y' && c != 'n' &&  c != 'N')
	{
            printf("\nPlease answer Y or N and press return: ");
            c = getc(stdin);
	}
	if (c == 'y' || c == 'Y')
		return true;
	else
		return false;
}

// ============================================================================================
void DisplayNotes(const char *NotesFilePath)				// Display notes text file
{
	printf("Notes text file extracted to: %s\n ", NotesFilePath);
}

// =====================================================================================
