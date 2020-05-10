//
// Created by jonathan_pc on 5/8/2020.
//
#include "library1.h"
#include "MusicManager.h"
//#include "avl_Tree.h"
//#include "double_sided_list.h"




void *Init() {
    try {
        MusicManager *DS = new MusicManager();
        return (void *)DS;
    }
    catch(std::bad_alloc& e){
        return NULL;
    }

}
StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if (!DS) {
        return INVALID_INPUT;
    }
    return ((MusicManager *)DS)-> AddDataCenter(artistID, numOfSongs);
}



StatusType RemoveArtist(void* DS,int artistID) {
    if (!DS)
        return INVALID_INPUT;
    StatusType res = ((MusicManager *) DS)->RemoveArtistFromDB(artistID);
    return res;
}

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

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams) {
    if ((!DS) || (songID < 0) || (artistID < 0)) {
        return INVALID_INPUT;
    }
    StatusType res=((MusicManager *) DS)->NumberOfStreamsDB(artistID,songID,streams);
    return res;
}


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

void Quit(void** DS){
    if (!DS){
        return;
    }
    ((MusicManager*)*DS)->QuitDB();
    *DS=NULL;
}
