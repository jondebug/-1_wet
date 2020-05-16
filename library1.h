//
// Created by jonathan_pc on 5/8/2020.
//
/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 1                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library1.h                                                   */
/*                                                                          */
/****************************************************************************/

#ifndef _234218_WET1
#define _234218_WET1

#ifdef __cplusplus
extern "C" {
#endif
//#include "avl_Tree.h"

/* Return Values
 * ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;

///initiate data structure
void *Init();

///Add artist to data structure. artistID must not exist yet, numOfSongs must
/// be positive.
StatusType AddArtist(void *DS, int artistID, int numOfSongs);

/// remove artist to data structure, artistID must exist already.
StatusType RemoveArtist(void *DS, int artistID);

/// 1 play to play count of a specific song. artistID must exist already.
/// songID must be a song of artistID
StatusType AddToSongCount(void *DS, int artistID, int songID);

///return number of plays given song number songID, of artist ArtistId has in
/// param streams.
///artistID must exist already.
/// songID must be a song of artistID
StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams);

///return the numOfSongs most played in the database. song numbers in *songs
/// and their respective artist numbers in *artists. numOfSongs must be positive
StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs);

/// free entire database
void Quit(void** DS);


#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1 */
