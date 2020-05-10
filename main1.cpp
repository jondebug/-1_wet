/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Winter 2019-2020                                     */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library1.h"

#ifdef __cplusplus
extern "C" {
#endif
int main(int argc, const char**argv) {

    void* DS= Init();
    AddArtist(DS,50,8);
    AddArtist(DS,80,20);
    return 0;
}
}