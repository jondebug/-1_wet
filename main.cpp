#include <iostream>
//#include "point.h"
#include "double_sided_list.h"

#include "avl_Tree.h"

#include <iostream>

class compare{
public:
    int operator()(int x, int y) {

        return y-x;

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












   // std::cout << "Hello, World!" << std::endl;

    print_in_order(t1.getRoot());

    //cout<<"\n"<<t1.getLargest()->get_data();


    return 0;
}
