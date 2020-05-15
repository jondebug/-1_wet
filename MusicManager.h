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

//functors:

class Print{
public:
    void operator()(int numOfsongs,int &k, treeNode<int*,int>* song_node,int* artists,int* songs,int artistID) {

        //cout<<song_node->get_data()<<",\n";
        songs[numOfsongs-k]=*song_node->get_data();
        artists[numOfsongs-k]=artistID;
        k--;


    }
};

class print_song_tree{
public:
    void operator()(int numOfsongs,int &k,treeNode<avl_Tree<int*,int>*,int>* artist_node,int* artists,int* songs,int artistID) {
        Print p;

        artist_node->get_data()->printKmin(numOfsongs, k, artists, songs,
                                           artist_node->get_key(), p);
        //
    }
};


    class array_len{
public:
    //int* array;
    listNode<avl_Tree<avl_Tree<int*,int>*,int>*>** array;
    void setLength(int numOfSongs){
        this->array=new listNode<avl_Tree<avl_Tree<int*,int>*,int>*>*[numOfSongs];

    }
    int len;

    ~array_len();


    };





class MusicManager{

    double_sided_list<avl_Tree<avl_Tree<int*,int>*,int>*> popularSongList;

    avl_Tree<array_len*,int> allArtistsTree;

public:

    MusicManager ();

    StatusType RemoveArtistFromDB(int artistID);

    double_sided_list<avl_Tree<avl_Tree<int*,int>*,int>*> get_list(){
        return popularSongList;
    }

    StatusType AddDataCenter(int artistID,int numOfSongs); // add artist function
    StatusType AddToSongCountDB(int ArtistId,int songID);
    void QuitDB();
    StatusType NumberOfStreamsDB(int artistID, int songID, int *streams);
    StatusType GetRecommendedSongsDB(int numOfSongs, int *artists, int *songs);

   // ~MusicManager();

};



#endif //INC_1_WET_GIT_MUSICMANAGER_H
