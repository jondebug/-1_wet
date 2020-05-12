

//
// Created by jonathan_pc on 5/8/2020.
//
#include "MusicManager.h"
//#include "library1.h"

//#include <iostream>
//#include <array>




StatusType MusicManager::AddDataCenter(int artistID, int numOfSongs) {
    try {

        if ((this == nullptr) || (numOfSongs <= 0) || artistID <= 0)
            return INVALID_INPUT;

        array_len *new_array = new array_len;

        new_array->array=new listNode<avl_Tree<avl_Tree<int,int>*,int>*>*[numOfSongs];
        for (int i=0;i<numOfSongs;i++){
            new_array->array[i]=popularSongList.get_first();
        }

        new_array->len = numOfSongs;

        if (this->allArtistsTree.searchKey(artistID,
                                           allArtistsTree.getRoot()) !=
            nullptr)
            return FAILURE;

        this->allArtistsTree.add_treeNode(new_array, artistID);

        avl_Tree<int, int> *new_song_tree = new avl_Tree<int, int>(numOfSongs);

        popularSongList.get_first_data()->add_treeNode(new_song_tree, artistID);

        return SUCCESS;
    }

    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

StatusType MusicManager::RemoveArtistFromDB(int artistID) {

    try {

        if (artistID <= 0) return INVALID_INPUT; //artist<=0 => invalid
        if (allArtistsTree.searchKey(artistID, allArtistsTree.getRoot()) ==
            nullptr)
            return FAILURE;


        array_len *songsArray = allArtistsTree.searchKey(artistID,
                                                         allArtistsTree
                                                                 .getRoot())->get_data();

        for (int i = 0; i < songsArray->len; i++) {
            songsArray->array[i]->get_data()->removeByKey(artistID);


            if ((songsArray->array[i]->get_data()->getRoot() == nullptr) &&
                (songsArray->array[i]->get_key() != 0)) {
                popularSongList.remove_node(songsArray->array[i]);
            }
            allArtistsTree.removeByKey(artistID);
        }

        return SUCCESS;
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}


StatusType MusicManager:: AddToSongCountDB(int ArtistId,int songID){
    try {
        if (allArtistsTree.searchKey(ArtistId,
                                     allArtistsTree.getRoot()) == nullptr)
            return FAILURE;

        array_len *arr = allArtistsTree.searchKey(ArtistId,
                                                  allArtistsTree.getRoot())
                ->get_data();
        int numOfSongs = arr->len;
        if (numOfSongs <= songID) return INVALID_INPUT;
        //arr->array[songID]++;
        avl_Tree<avl_Tree<int, int> *, int> *artistTree = arr->array[songID]->get_data();
        avl_Tree<int, int> *songTree = artistTree->searchKey(ArtistId,
                                                             artistTree->getRoot())->get_data();
        songTree->removeByKey(songID);
        if (songTree->getRoot() == nullptr) { //we removed this artist last song
            artistTree->removeByKey(ArtistId);
        }
        int numberOfplays = arr->array[songID]->get_key();
        int newPlays = numberOfplays + 1;
        listNode<avl_Tree<avl_Tree<int, int> *, int> *> *nextNode = arr->array[songID]->get_next();

        //line for debug
        listNode<avl_Tree<avl_Tree<int, int> *, int> *> *node_to_check=arr->array[songID];

        if (artistTree->getRoot() ==
            nullptr) { //we removed the last songs with this number of plays
            popularSongList.remove_node(arr->array[songID]);
        }


        if ((nextNode == nullptr) || (nextNode->get_key() !=
                                      newPlays)) //we need to make a new node in a list
        {
            avl_Tree<int, int> *newSongTree = new avl_Tree<int, int>();
            newSongTree->add_treeNode(songID, songID);

            avl_Tree<avl_Tree<int, int> *, int> *newArtistTree = new avl_Tree<avl_Tree<int, int> *, int>();
            newArtistTree->add_treeNode(newSongTree, ArtistId);

            if (nextNode == nullptr) { //this song is now the most played song
                popularSongList.addNode(newArtistTree, newPlays);
                arr->array[songID]=popularSongList.get_last();

            } else {
                popularSongList.add_node_after(nextNode->get_prev(),
                                               newArtistTree, newPlays);
                arr->array[songID] = nextNode->get_prev();
            }
        } else { //the next node exists and its the right one!

            treeNode<avl_Tree<int, int> *, int> *artistNode = nextNode->get_data()->searchKey(
                    ArtistId, nextNode->get_data()->getRoot()); //song tree
            //artist node - the node belog to this artist in the next tree
            if (artistNode ==
                nullptr) { //next node does not have songs from this artist
                avl_Tree<int, int> *newSongTree = new avl_Tree<int, int>();
                newSongTree->add_treeNode(songID, songID);

                nextNode->get_data()->add_treeNode(newSongTree, ArtistId);



            } else { //next node has songs from this artist
                artistNode->get_data()->add_treeNode(songID, songID);
            }
            arr->array[songID]=nextNode;

        }
        return SUCCESS;
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

void MusicManager::QuitDB() {
//    delete this; //TODO -check if works
}

StatusType MusicManager::NumberOfStreamsDB(int artistID, int songID, int *streams) {
    if (allArtistsTree.searchKey(artistID,allArtistsTree.getRoot())== nullptr)
        return FAILURE;
    array_len *songsArray = allArtistsTree.searchKey(artistID,
                                                     allArtistsTree.getRoot
                                                             ())->get_data();
    if (songID>=songsArray->len) return INVALID_INPUT;
    int key=(songsArray->array[songID]->get_key());
    *streams=key;

    return SUCCESS;

}

StatusType MusicManager::GetRecommendedSongsDB(int numOfSongs, int *artists,
                                               int *songs) {
    //if there are less songs than numOfSongs -> return FALIURE:
    print_song_tree p;
    listNode<avl_Tree<avl_Tree<int,int>*,int>*>* iterator=popularSongList
            .get_last();
    int counter=numOfSongs;
    while((iterator!=nullptr)&&(counter>0)){
        iterator->get_data()->printKmin(numOfSongs,counter,artists,songs,0,p);
        iterator=iterator->get_prev();
    }

    if (counter>0) return FAILURE;


    return SUCCESS;
}



MusicManager::MusicManager() {
    avl_Tree<avl_Tree<int, int> *, int> *zero_tree = new avl_Tree<avl_Tree<int,
            int> *, int>;

    popularSongList =*new double_sided_list<avl_Tree<avl_Tree<int, int> *,
            int>*>;


    popularSongList.addNode(zero_tree, 0);
    allArtistsTree =*new avl_Tree<array_len*,int>;

}

//MusicManager::~MusicManager() {
//
////    delete popularSongList;
//
//    delete allArtistsTree;
//
//
//}





