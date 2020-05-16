//
// Created by jonathan_pc on 5/8/2020.
//
#include "library1.h"
#include "MusicManager.h"
//#include "avl_Tree.h"
//#include "double_sided_list.h"



///initiate data structure
void *Init() {
    try {
        MusicManager *DS = new MusicManager();
        return (void *)DS;
    }
    catch(std::bad_alloc& e){
        return NULL;
    }

}
///Add artist to data structure. artistID must not exist yet, numOfSongs must
/// be positive.
StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if (!DS) {
        return INVALID_INPUT;
    }
    return ((MusicManager *)DS)-> AddDataCenter(artistID, numOfSongs);
}


/// remove artist to data structure, artistID must exist already.
StatusType RemoveArtist(void* DS,int artistID) {
    if (!DS)
        return INVALID_INPUT;
    StatusType res = ((MusicManager *) DS)->RemoveArtistFromDB(artistID);
    return res;
}
/// 1 play to play count of a specific song. artistID must exist already.
/// songID must be a song of artistID
StatusType AddToSongCount(void *DS, int artistID, int songID){

    if((!DS)||(songID<0)||(artistID<=0)) return INVALID_INPUT;
    try {
        StatusType res = ((MusicManager *) DS)->AddToSongCountDB(artistID,
                                                                 songID);
        return res;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}
///return number of plays given song number songID, of artist ArtistId has in
/// param streams.
///artistID must exist already.
/// songID must be a song of artistID
StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams) {
    if ((!DS) || (songID < 0) || (artistID < 0)) {
        return INVALID_INPUT;
    }
    StatusType res=((MusicManager *) DS)->NumberOfStreamsDB(artistID,songID,
            streams);
    return res;
}

///return the numOfSongs most played in the database. song numbers in *songs
/// and their respective artist numbers in *artists. numOfSongs must be positive
StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs){
    if((!DS)||(numOfSongs<=0)) return INVALID_INPUT;
    try {
        StatusType res = ((MusicManager *) DS)->GetRecommendedSongsDB(
                numOfSongs, artists, songs);
        return res;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}
/// free entire database
void Quit(void** DS){
    if (!DS){
        return;
    }
    ((MusicManager*)*DS)->QuitDB();
    *DS=NULL;
}
