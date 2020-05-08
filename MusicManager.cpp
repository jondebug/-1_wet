//
// Created by jonathan_pc on 5/8/2020.
//
#include "MusicManager.h"


StatusType MusicManager::AddDataCenter(int artistID, int numOfSongs) {
    {

        if((this== nullptr)||(numOfSongs<=0)||artistID<=0) return INVALID_INPUT;

        array_len* new_array = new array_len;

        new_array->array=new int[numOfSongs];

        *new_array->array={0}; //TODO check if this is a zero array

        new_array->len=numOfSongs;

        if(this->allArtistsTree->searchKey(artistID,
                allArtistsTree->getRoot())== nullptr) return FAILURE;

        this->allArtistsTree->add_treeNode(new_array,artistID);

        if(this->allArtistsTree->searchKey(artistID,
                allArtistsTree->getRoot())==nullptr) return ALLOCATION_ERROR;

        avl_Tree<int,int>* new_song_tree= new avl_Tree<int,int>(numOfSongs);

        popularSongList->get_first()->add_treeNode(new_song_tree,artistID);

    }
}
