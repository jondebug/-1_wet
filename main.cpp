#include <iostream>
//#include "point.h"
#include "double_sided_list.h"

#include "avl_Tree.h"

#include <iostream>



class Print{
public:
    void operator()(int &k, treeNode<int,int>* node) {

        cout<<node->get_data()<<",\n";
        k--;

    }
};
class print_song_tree{
public:
    void operator()(int &k, treeNode<int,int>* song_tree) {
        Print p;

        //song_tree->get_data()->printKmax(k,p); TODO: this like should work
        //                                       TODO: when data is tree pointer

    }
};
void print_in_order(treeNode<int,int>* t)
{
    if (t== nullptr)
        return;
    print_in_order(t->get_left());
    cout<<t->get_data()<<"\n";
    print_in_order(t->get_right());

}

/*
 * testAVLTree.cpp
 *
 *  Created on: 19 ���� 2013
 *      Author: shirel
 */

#include "avl_Tree.h"
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>

int main(){
    avl_Tree<int, int> tree;

    tree.add_treeNode(8,8);
    tree.add_treeNode(3,3);
    tree.add_treeNode(4,4);
    tree.add_treeNode(9,9);
    tree.add_treeNode(10,10);
    tree.add_treeNode(5,5);
    tree.add_treeNode(7,7);
    tree.add_treeNode(1,1);
    tree.add_treeNode(2,2);
    tree.add_treeNode(6,6);





    tree.removeByKey(10);
    tree.removeByKey(1);

    tree.removeByKey(2);
    tree.removeByKey(3);
    tree.removeByKey(5);
    tree.removeByKey(7);
    tree.removeByKey(8);
    tree.removeByKey(9);
    tree.removeByKey(4);
    tree.removeByKey(6);

    tree.printTree();



    //Specific Cases

    /*correct output for the four next cases
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0 */

    //basic LL root change
    tree.add_treeNode(3,3);
    tree.add_treeNode(2,2);
    tree.add_treeNode(1,1);
    tree.printTree();
    tree.treeClear();

    //basic LR root change
    tree.add_treeNode(3,3);
    tree.add_treeNode(1,1);
    tree.add_treeNode(2,2);
    tree.printTree();
    tree.treeClear();

    //basic RR root change
    tree.add_treeNode(1,1);
    tree.add_treeNode(2,2);
    tree.add_treeNode(3,3);
    tree.printTree();
    tree.treeClear();

    //basic RL root change
    tree.add_treeNode(1,1);
    tree.add_treeNode(3,3);
    tree.add_treeNode(2,2);
    tree.printTree();
    tree.treeClear();

    //basic LR not root change
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    6 BF: 1 Height: 3
    7 BF: 0 Height: 0
    8 BF: 1 Height: 1 */
    tree.add_treeNode(6,6);
    tree.add_treeNode(4,4);
    tree.add_treeNode(8,8);
    tree.add_treeNode(3,3);
    tree.add_treeNode(5,5);
    tree.add_treeNode(7,7);
    tree.add_treeNode(1,1);
    tree.add_treeNode(2,2);
    tree.printTree();
    tree.treeClear();

    //basic LL not root change
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    6 BF: 1 Height: 3
    7 BF: 0 Height: 0
    8 BF: 1 Height: 1 */
    tree.add_treeNode(6,6);
    tree.add_treeNode(4,4);
    tree.add_treeNode(8,8);
    tree.add_treeNode(3,3);
    tree.add_treeNode(5,5);
    tree.add_treeNode(7,7);
    tree.add_treeNode(2,2);
    tree.add_treeNode(1,1);
    tree.printTree();
    tree.treeClear();

    //basic RR not root change
    /*correct output
     * 1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    5 BF: 1 Height: 2
    7 BF: 0 Height: 0*/
    tree.add_treeNode(5,5);
    tree.add_treeNode(7,7);
    tree.add_treeNode(1,1);
    tree.add_treeNode(2,2);
    tree.add_treeNode(3,3);
    tree.printTree();
    tree.treeClear();

    //basic RL not root change
    /*correct output
     * 1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    5 BF: 1 Height: 2
    7 BF: 0 Height: 0*/
    tree.add_treeNode(5,5);
    tree.add_treeNode(7,7);
    tree.add_treeNode(1,1);
    tree.add_treeNode(3,3);
    tree.add_treeNode(2,2);
    tree.printTree();
    tree.treeClear();

    //root deletion no roll successor is a neighbour
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    5 BF: 1 Height: 2
    6 BF: 0 Height: 0*/
    tree.add_treeNode(4,4);
    tree.add_treeNode(5,5);
    tree.add_treeNode(3,3);
    tree.add_treeNode(2,2);
    tree.add_treeNode(6,6);
    tree.removeByKey(4);
    tree.printTree();
    tree.treeClear();

    //root deletion no roll successor is not a neighbour
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    5 BF: 0 Height: 2
    6 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0 */
    tree.add_treeNode(4,4);
    tree.add_treeNode(3,3);
    tree.add_treeNode(7,7);
    tree.add_treeNode(2,2);
    tree.add_treeNode(5,5);
    tree.add_treeNode(8,8);
    tree.add_treeNode(6,6);
    tree.removeByKey(4);
    tree.printTree();
    tree.treeClear();

    //node deletion no roll successor is a neighbour case7
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    7 BF: 1 Height: 3
    8 BF: -1 Height: 1
    9 BF: 0 Height: 0*/
    tree.add_treeNode(7,7);
    tree.add_treeNode(3,3);
    tree.add_treeNode(8,8);
    tree.add_treeNode(2,2);
    tree.add_treeNode(4,4);
    tree.add_treeNode(9,9);
    tree.add_treeNode(5,5);
    tree.add_treeNode(1,1);
    tree.removeByKey(3);

    tree.printTree();
    tree.treeClear();

    //node deletion no roll successor is not a neighbour case8
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    5 BF: 0 Height: 2
    6 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0
    9 BF: 0 Height: 3
    10 BF: 0 Height: 0
    12 BF: -1 Height: 2
    13 BF: -1 Height: 1
    14 BF: 0 Height: 0*/
    tree.add_treeNode(9,9);
    tree.add_treeNode(3,3);
    tree.add_treeNode(12,12);
    tree.add_treeNode(2,2);
    tree.add_treeNode(7,7);
    tree.add_treeNode(10,10);
    tree.add_treeNode(13,13);
    tree.add_treeNode(1,1);
    tree.add_treeNode(5,5);
    tree.add_treeNode(8,8);
    tree.add_treeNode(14,14);
    tree.add_treeNode(6,6);
    tree.removeByKey(3);
    tree.printTree();
    tree.treeClear();

    //node deletion causing LR case9
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 0 Height: 2
    7 BF: -1 Height: 1
    8 BF: 0 Height: 0*/
    tree.add_treeNode(7,7);
    tree.add_treeNode(2,2);
    tree.add_treeNode(8,8);
    tree.add_treeNode(1,1);
    tree.add_treeNode(4,4);
    tree.add_treeNode(9,9);
    tree.add_treeNode(3,3);
    tree.removeByKey(9);
    tree.printTree();
    tree.treeClear();

    //node deletion causing LL case10
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    3 BF: 0 Height: 2
    4 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0*/
    tree.add_treeNode(7,7);
    tree.add_treeNode(3,3);
    tree.add_treeNode(8,8);
    tree.add_treeNode(2,2);
    tree.add_treeNode(4,4);
    tree.add_treeNode(9,9);
    tree.add_treeNode(1,1);
    tree.removeByKey(9);
    tree.printTree();
    tree.treeClear();

    //node deletion causing RR case11
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 0 Height: 1
    7 BF: 0 Height: 0
    8 BF: 0 Height: 2
    9 BF: -1 Height: 1
    10 BF: 0 Height: 0*/
    tree.add_treeNode(3,3);
    tree.add_treeNode(2,2);
    tree.add_treeNode(8,8);
    tree.add_treeNode(7,7);
    tree.add_treeNode(1,1);
    tree.add_treeNode(9,9);
    tree.add_treeNode(10,10);
    tree.removeByKey(1);
    tree.printTree();
    tree.treeClear();

    //node deletion causing RL case12
    /*correct output
    * 2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    7 BF: 0 Height: 2
    10 BF: 0 Height: 0
    13 BF: 0 Height: 1
    14 BF: 0 Height: 0*/
    tree.add_treeNode(3,3);
    tree.add_treeNode(2,2);
    tree.add_treeNode(13,13);
    tree.add_treeNode(7,7);
    tree.add_treeNode(1,1);
    tree.add_treeNode(14,14);
    tree.add_treeNode(10,10);
    tree.removeByKey(1);
    tree.printTree();
    tree.treeClear();

    //double rotations RL and RR case 13
    /*correct output
    3 BF: 0 Height: 0
    5 BF: 0 Height: 1
    7 BF: 0 Height: 0
    9 BF: 0 Height: 2
    11 BF: 0 Height: 0
    13 BF: 1 Height: 1
    15 BF: 0 Height: 3
    17 BF: 0 Height: 0
    19 BF: -1 Height: 2
    21 BF: -1 Height: 1
    23 BF: 0 Height: 0*/
    tree.add_treeNode(9,9);
    tree.add_treeNode(3,3);
    tree.add_treeNode(15,15);
    tree.add_treeNode(1,1);
    tree.add_treeNode(7,7);
    tree.add_treeNode(13,13);
    tree.add_treeNode(19,19);
    tree.add_treeNode(5,5);
    tree.add_treeNode(11,11);
    tree.add_treeNode(17,17);
    tree.add_treeNode(21,21);
    tree.add_treeNode(23,23);
    tree.removeByKey(1);
    tree.printTree();
    tree.treeClear();

    //double rotations RR and RR case 14
    /*correct output
    3 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0
    9 BF: 0 Height: 2
    11 BF: 0 Height: 0
    13 BF: 1 Height: 1
    15 BF: 0 Height: 3
    17 BF: 0 Height: 0
    19 BF: -1 Height: 2
    21 BF: -1 Height: 1
    23 BF: 0 Height: 0*/
    tree.add_treeNode(9,9);
    tree.add_treeNode(3,3);
    tree.add_treeNode(15,15);
    tree.add_treeNode(1,1);
    tree.add_treeNode(7,7);
    tree.add_treeNode(13,13);
    tree.add_treeNode(19,19);
    tree.add_treeNode(8,8);
    tree.add_treeNode(11,11);
    tree.add_treeNode(17,17);
    tree.add_treeNode(21,21);
    tree.add_treeNode(23,23);
    tree.removeByKey(1);
    tree.printTree();
    tree.treeClear();

    //double rotations RL and LL case 15
    /*correct output
    6 BF: 0 Height: 0
    7 BF: 1 Height: 1
    8 BF: 1 Height: 2
    9 BF: 0 Height: 0
    10 BF: 0 Height: 3
    11 BF: -1 Height: 1
    12 BF: 0 Height: 0
    15 BF: 0 Height: 2
    17 BF: 0 Height: 0
    18 BF: 0 Height: 1
    20 BF: 0 Height: 0
     */
    tree.add_treeNode(15,15);
    tree.add_treeNode(10,10);
    tree.add_treeNode(20,20);
    tree.add_treeNode(8,8);
    tree.add_treeNode(11,11);
    tree.add_treeNode(17,17);
    tree.add_treeNode(21,21);
    tree.add_treeNode(7,7);
    tree.add_treeNode(9,9);
    tree.add_treeNode(12,12);
    tree.add_treeNode(18,18);
    tree.add_treeNode(6,6);
    tree.removeByKey(21);
    tree.printTree();
    tree.treeClear();

    //double rotations LR and LL case 16
    /*correct output
    6 BF: 0 Height: 0
    7 BF: 1 Height: 1
    8 BF: 1 Height: 2
    9 BF: 0 Height: 0
    10 BF: 0 Height: 3
    11 BF: -1 Height: 1
    12 BF: 0 Height: 0
    15 BF: 0 Height: 2
    20 BF: 0 Height: 0
    21 BF: 0 Height: 1
    22 BF: 0 Height: 0 */
    tree.add_treeNode(15,15);
    tree.add_treeNode(10,10);
    tree.add_treeNode(20,20);
    tree.add_treeNode(8,8);
    tree.add_treeNode(11,11);
    tree.add_treeNode(17,17);
    tree.add_treeNode(22,22);
    tree.add_treeNode(7,7);
    tree.add_treeNode(9,9);
    tree.add_treeNode(12,12);
    tree.add_treeNode(21,21);
    tree.add_treeNode(6,6);
    tree.removeByKey(17);
    tree.printTree();
    tree.treeClear();

    //delete node cause LR
    /*correct output
     * 2 BF: 0 Height: 0
    3 BF: -1 Height: 2
    4 BF: 0 Height: 0
    6 BF: 1 Height: 1*/

    tree.add_treeNode(5,5);
    tree.add_treeNode(3,3);
    tree.add_treeNode(6,6);
    tree.add_treeNode(2,2);
    tree.add_treeNode(4,4);
    tree.removeByKey(5);

    cout<<"check here!!!!!!!!!!!!!!!!!!!!!\n";

    tree.printTree();
    tree.treeClear();


    //delete node cause LR
    /*correct output
     * 2 BF: 0 Height: 0
    3 BF: 0 Height: 1
    6 BF: 0 Height: 0*/
    tree.add_treeNode(5,5);
    tree.add_treeNode(3,3);
    tree.add_treeNode(6,6);
    tree.add_treeNode(2,2);
    tree.removeByKey(5);
    tree.printTree();
    tree.treeClear();
    //tree.recurtionDestroy(tree.getRoot());

    std::vector<int> vector;
    for (int i=1; i<=20; i++) vector.push_back(i);
    //return 0;
    //Randomly insert and removes nodes
    for (int k = 0; k < 30; ++k) {
        avl_Tree<int, int> tree;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            tree.add_treeNode(*it,*it);

        }
        tree.printTree();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        int counter=0;
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            counter++;
            if (counter==99){

            }
            printf("no\n\n\n");
            tree.removeByKey(*it);
            tree.printTree();

        }

        tree.printTree();
        std::cout << '\n';
    }

    return 0;
}

