//
// Created by jonathan_pc on 5/8/2020.
//

#ifndef INC_1_WET_GIT_MUSICMANAGER_H
#define INC_1_WET_GIT_MUSICMANAGER_H

#include "double_sided_list.h"
#include "avl_Tree.h"
#include "library1.h"


//function objects, used by recommended songs function:

class Print{
public:
    void operator()(int numOfsongs,int &k, treeNode<int*,int>* song_node,int* artists,int* songs,int artistID) {

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

    }
};


class array_len{
public:

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

    int total_songs = 0 ;
public:

    MusicManager ();

    StatusType RemoveArtistFromDB(int artistID);

    double_sided_list<avl_Tree<avl_Tree<int*,int>*,int>*> get_list(){
        return popularSongList;
    }

    StatusType AddDataCenter(int artistID,int numOfSongs);
    StatusType AddToSongCountDB(int ArtistId,int songID);
    void QuitDB();
    StatusType NumberOfStreamsDB(int artistID, int songID, int *streams);
    StatusType GetRecommendedSongsDB(int numOfSongs, int *artists, int *songs);

};



#endif //INC_1_WET_GIT_MUSICMANAGER_H
