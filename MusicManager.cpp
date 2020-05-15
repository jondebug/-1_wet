

//
// Created by jonathan_pc on 5/8/2020.
//
#include "MusicManager.h"
//#include "library1.h"

//#include <iostream>
//#include <arra


StatusType MusicManager::AddDataCenter(int artistID, int numOfSongs) {
    // add artist to database function

    try {

        //check valid input
        if ((this == nullptr) || (numOfSongs <= 0) || (artistID <= 0))
            return INVALID_INPUT;

        if (this->allArtistsTree.searchKey(artistID,
                                           allArtistsTree.getRoot()) !=
            nullptr)
            return FAILURE;

        //create song-array, each cell points to zero node of listNode:
        array_len *new_array = new array_len;
        new_array->array=new listNode<avl_Tree<avl_Tree<int*,int>*,int>*>*[numOfSongs];
        for (int i=0;i<numOfSongs;i++){
            new_array->array[i]=popularSongList.get_first();
        }
        new_array->len = numOfSongs;


        //add this artist treenode to allArtist tree
        this->allArtistsTree.add_treeNode(new_array, artistID);
        avl_Tree<int*,int> *new_song_tree = new avl_Tree<int*,int>(numOfSongs);

        //add this artist song tree to zero artists tree (which is pointded by first
        //node of listNode)
        popularSongList.get_first_data()->add_treeNode(new_song_tree, artistID);

        return SUCCESS;
    }

    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

StatusType MusicManager::RemoveArtistFromDB(int artistID) {

    try {
        //check valid input:
        if (artistID <= 0) return INVALID_INPUT; //artist<=0 => invalid
        if (allArtistsTree.searchKey(artistID, allArtistsTree.getRoot()) ==
            nullptr)
            return FAILURE; // if artist isnt in the database => faliure


        array_len *songsArray = allArtistsTree.searchKey(artistID,
                                                         allArtistsTree
                                                                 .getRoot())->get_data();
        // remove all nodes in artist trees that this artist has
        for (int i = 0; i < songsArray->len; i++) {
            songsArray->array[i]->get_data()->removeByKey(artistID);

        // remove list nodes, if they point to trees with no songs
            if ((songsArray->array[i]->get_data()->getRoot() == nullptr) &&
                (songsArray->array[i]->get_key() != 0)) {
                popularSongList.remove_node(songsArray->array[i]);
            }

        }

        allArtistsTree.removeByKey(artistID);

        return SUCCESS;
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}


StatusType MusicManager:: AddToSongCountDB(int ArtistId,int songID){
    try {
        //check valid input:
        if (allArtistsTree.searchKey(ArtistId,
                                     allArtistsTree.getRoot()) == nullptr)
            return FAILURE;

        array_len *arr = allArtistsTree.searchKey(ArtistId,
                                                  allArtistsTree.getRoot())
                ->get_data();

        int numOfSongs = arr->len;
        if (numOfSongs <= songID) return INVALID_INPUT;


        int *songIdInt=new int; // data of the song tree
        *songIdInt=songID;


        avl_Tree<avl_Tree<int*,int> *, int> *artistTree = arr->array[songID]->get_data();
        avl_Tree<int*,int> *songTree = artistTree->searchKey(ArtistId,
                                                             artistTree->getRoot())->get_data();

        songTree->removeByKey(songID);

        //if we removed this artist last song, remove artists tree
        if (songTree->getRoot() == nullptr) { //
            artistTree->removeByKey(ArtistId);
        }


        int numberOfplays = arr->array[songID]->get_key();
        int newPlays = numberOfplays + 1;


        listNode<avl_Tree<avl_Tree<int*,int> *, int> *> *nextNode = arr->array[songID]->get_next();
        listNode<avl_Tree<avl_Tree<int*,int> *, int> *> *curNode = arr->array[songID];

        //if we removed the last songs with this number of plays, remove node from list
        if ((artistTree->getRoot() ==
            nullptr)&&(popularSongList.get_first()!=curNode)) {
            popularSongList.remove_node(arr->array[songID]);
        }

        //if the next node doest exist or its key bigger than newPlays, create a new node in list:
        if ((nextNode == nullptr) || (nextNode->get_key() !=
                                      newPlays))
        {

            //create new song tree and artist tree
            avl_Tree<int*,int> *newSongTree = new avl_Tree<int*,int>();
            newSongTree->add_treeNode(songIdInt, songID);

            avl_Tree<avl_Tree<int*,int> *, int> *newArtistTree = new avl_Tree<avl_Tree<int*,int> *, int>();
            newArtistTree->add_treeNode(newSongTree, ArtistId);

            if (nextNode == nullptr) { //this song is now the most played song
                                        //add new node in the end of the list

                popularSongList.addNode(newArtistTree, newPlays);
                arr->array[songID]=popularSongList.get_last();

            } else {

                //this song is not the most played song
                //add new node after its previous node

                popularSongList.add_node_after(nextNode->get_prev(),
                                               newArtistTree, newPlays);
                arr->array[songID] = nextNode->get_prev();
            }
        } else {

            //the next node exists and its the right one!
            //add artist tree to the next node

            treeNode<avl_Tree<int*,int> *, int> *artistNode = nextNode->get_data()->searchKey(
                    ArtistId, nextNode->get_data()->getRoot()); //song tree

                    // artistNode = the node belog to this artist in the next tree

                    if (artistNode ==nullptr) { //next node does not have songs from this artist
                avl_Tree<int*,int> *newSongTree = new avl_Tree<int*,int>();
                newSongTree->add_treeNode(songIdInt, songID);

                nextNode->get_data()->add_treeNode(newSongTree, ArtistId);

            } else { //next node has songs from this artist
                artistNode->get_data()->add_treeNode(songIdInt, songID);
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
    delete this; //TODO -check if works
}

StatusType MusicManager::NumberOfStreamsDB(int artistID, int songID, int *streams) {
    //check valid input
    if (allArtistsTree.searchKey(artistID,allArtistsTree.getRoot())== nullptr)
        return FAILURE;

    array_len *songsArray = allArtistsTree.searchKey(artistID,
                                                     allArtistsTree.getRoot
                                                             ())->get_data();
    if (songID>=songsArray->len) return INVALID_INPUT;

    //find number of streams:
    int key=(songsArray->array[songID]->get_key());
    *streams=key;

    return SUCCESS;

}

StatusType MusicManager::GetRecommendedSongsDB(int numOfSongs, int *artists,
                                               int *songs) {
    //if there are less songs than numOfSongs -> return FALIURE:
    print_song_tree p;
    listNode<avl_Tree<avl_Tree<int*,int>*,int>*>* iterator=popularSongList
            .get_last();

    //find the recommended songs and put in artist and sogs arrays:
    int counter=numOfSongs;
    while((iterator!=nullptr)&&(counter>0)){
        iterator->get_data()->printKmin(numOfSongs,counter,artists,songs,0,p);
        iterator=iterator->get_prev();
    }

    if (counter>0) return FAILURE;

    return SUCCESS;
}



MusicManager::MusicManager() {
    //initiate zero node of popularSonglist

    avl_Tree<avl_Tree<int*,int> *, int> *zero_tree = new avl_Tree<avl_Tree<int*,
            int> *, int>;
    popularSongList.addNode(zero_tree, 0);


}


array_len::~array_len() {
    delete[] array;
}
