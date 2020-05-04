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



int main() {

    int x=5;
    int &y=x;


    double_sided_list<int> l;
    l.addNode(5);
    l.addNode(8);
    listNode<int> *n1(l.get_current_node());

    l.add_node_after(n1,10);



    l.add_node_after(n1->get_next(),11);

    n1=n1->get_next();
    n1=n1->get_next();
    l.add_node_after(n1,100);
    //l.printList();



    avl_Tree<int,int> t1;






    t1.add_treeNode(10,10);
    t1.add_treeNode(9,9);
    t1.add_treeNode(12,12);
    t1.add_treeNode(13,13);
    t1.add_treeNode(18,18);
    t1.add_treeNode(6,6);
    t1.add_treeNode(15,15);
    t1.add_treeNode(11,11);
    t1.add_treeNode(7,7);
    t1.add_treeNode(22,22);
    t1.add_treeNode(5,5);
    t1.add_treeNode(8,8);
    t1.add_treeNode(2,2);
    t1.add_treeNode(1,1);
    t1.add_treeNode(15,15);
    t1.add_treeNode(1,1);

 //   t1.removeByKey(1);
    t1.removeByKey(2);
 //   t1.removeByKey(22);
t1.removeByKey(8);
//t1.removeByKey(10);
t1.removeByKey(15);
t1.removeByKey(18);
t1.removeByKey(22);
t1.removeByKey(11);
    Print p2;

  //  print_song_tree p1;

    int m=5;

    t1.printKmax(m,p2);

    printf("\n-------------\n");


    print_in_order(t1.getRoot());


    return 0;
}
