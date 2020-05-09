//
// Created by jonathan_pc on 5/8/2020.
//

#ifndef INC_1_WET_GIT_MUSICMANAGER_H
#define INC_1_WET_GIT_MUSICMANAGER_H

#include "double_sided_list.h"
#include "avl_Tree.h"
#include "library1.h"


//typedef enum {
//    SUCCESS = 0,
//    FAILURE = -1,
//    ALLOCATION_ERROR = -2,
//    INVALID_INPUT = -3
//} StatusType;

class array_len{
public:
    //int* array;
    listNode<avl_Tree<avl_Tree<int,int>*,int>*>** array;
    int len;
};



class MusicManager{

    double_sided_list<avl_Tree<avl_Tree<int,int>*,int>*>* popularSongList;

    avl_Tree<array_len*,int>* allArtistsTree;

public:
    StatusType RemoveArtistFromDB(int artistID);


    double_sided_list<avl_Tree<avl_Tree<int,int>*,int>*>* get_list(){
        return popularSongList;
    }

    StatusType AddDataCenter(int artistID,int numOfSongs);
    //StatusType AddArtist(MusicManager* DS, int ArtistId, int numOfSongs);
    StatusType AddToSongCountDB(int ArtistId,int songID);
    void QuitDB();
    StatusType NumberOfStreamsDB(int artistID, int songID, int *streams);

};



#endif //INC_1_WET_GIT_MUSICMANAGER_H
