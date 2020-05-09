//
// Created by jonathan_pc on 5/8/2020.
//
#include "library1.h"
#include "MusicManager.h"
#include "MusicManager.h"

void *Init() {
    MusicManager *DS = new MusicManager();

    avl_Tree<avl_Tree<int,int>*,int>* zero_tree = new avl_Tree<avl_Tree<int,
            int>*,int>;

    DS->get_list()->addNode(zero_tree,0);

    return (void *)DS;

}
StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    return ((MusicManager *)DS)-> AddDataCenter(artistID, numOfSongs);
}

