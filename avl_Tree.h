//
// Created by jonathan_pc on 4/30/2020.
//



#include <cmath>
#ifndef INC_1_WET_NEW_AVL_TREE_H
#define INC_1_WET_NEW_AVL_TREE_H
#include <iostream>
using namespace std;

template<typename T,typename S>

class treeNode {

    treeNode *left_son;
    treeNode *right_son;
    treeNode *father;
    int height;
    S key;
    T data;
public:
    //tree node constructor with data and key
    treeNode (const T data,const S key):left_son(nullptr), right_son(nullptr),
    father
    (nullptr),
                            height(0),key(key),data(data){};

    //override the default tree node constructor and set params to 0/null.
    treeNode():left_son(nullptr), right_son(nullptr),father(nullptr),
               height(0){};


    void set_data(const T data){
        this->data=data;
    }

    void set_key(const S key){
        this->key=key;
    }

    void set_father(treeNode* const father){
        this->father=father;
    }

    void set_left(treeNode* const left){
        this->left_son=left;
    }

    void set_right(treeNode* const right){
        this->right_son=right;
    }

    void set_height(const int HEIGHT){
        this->height=HEIGHT;
    }

    ///swap the data and key of two nodes
    void swapNodes(treeNode* to_swap) {
        treeNode temp(*to_swap);

        to_swap->data=data;
        to_swap->key=key;

        data=temp.data;
        key=temp.key;

    }

    treeNode* get_left() const {
        return left_son;
    }

    treeNode* get_right() const{
        return right_son;
    }
    treeNode* get_father() const{
        return father;
    }

    int get_height() const{
        return height;
    }

    T get_data()const {
        return data;
    }

    S get_key()const {
        return key;
    }

};
template<typename T,typename S>
class avl_Tree{

    treeNode<T,S> * root;

    treeNode<T,S> * largestNode;
    treeNode<T,S> * smallestNode;



public:
    //// default constructor taking no params, set pointers to null
    avl_Tree(): root(nullptr), largestNode(nullptr),smallestNode(nullptr){};

    //// constructor taking 1 int param: m. will construct a tree with m nodes,
    ////all of which will have keys and values from 1 to m

    avl_Tree(int m){
        int height=floor(log2(m));
        treeNode<T,S> *tree=tree_create_helper(height+1,nullptr);
        root=tree;
        int numberToDelete=pow(2,height+1)-1-m;
        delete_unwanted_nodes(tree,numberToDelete,true, nullptr);
        int counter=0;
        set_value_inOrder(tree,m,counter);
        largestNode=findRightMost(root);
        smallestNode=findLeftMost(root);

    }
    ////create an empty FULL tree with the minimum height to hold m nodes

    treeNode<T,S>* tree_create_helper(int height,treeNode<T,S> *father){
        if (height<=0) return nullptr;
        treeNode<T,S> *tree = new treeNode<T,S>();
        tree->set_father(father);
        tree->set_height(height-1);
        tree->set_left(tree_create_helper(height-1,tree));
        tree->set_right(tree_create_helper(height-1,tree));
        return tree;
    }

    //// delete leafs from rightmost to leftmost untill there are exactly m
    //// nodes in the tree. numberToDelete is the number of nodes left to delete
    void delete_unwanted_nodes(treeNode<T,S> *node,int &numberToDelete, bool
    right_son , treeNode<T,S> *Father)
    {
        if ((node== nullptr)||(numberToDelete==0)) return;
        delete_unwanted_nodes(node->get_right(),numberToDelete,true,node);

        if (numberToDelete==0) return;
        if (node->get_height()==0) {
            if ((right_son)&&(Father!= nullptr)){//check if leaf is right son
                Father->set_right(nullptr);
            }
            else{//leaf is left son
                if(Father!= nullptr) Father->set_left(nullptr);
            }
            delete node;
            node=nullptr;
            numberToDelete--;   //update number of nodes left to delete
            return;
        }
        //recursive call:
        delete_unwanted_nodes(node->get_left(),numberToDelete,false, node);

        //update height of node:
        node->set_height(std::max(get_height_addition(node->get_left()),
                                  get_height_addition(node->get_right()))+1);
    }

/// in order pass over all of the tree while placing values in each node
/// data and key, starting at 0. counter saves how many nodes we have visited
/// updated and is used to place the correct value in each node.
    void set_value_inOrder(treeNode<T,S> *node,const int m,int &counter){
        if ((node==nullptr)||(counter>m)) return;
        set_value_inOrder(node->get_left(),m,counter);

        int* data=new int;// data to be set in the node

        *data=counter;
        node->set_data(data);

        node->set_key(counter);
        counter++;//update counter before next recursive call
        set_value_inOrder(node->get_right(),m,counter);



    }


    ///add node to this tree while retaining all avl tree properties
    void add_treeNode(const T data,const S key) {
        //this is the first node in the tree,
        // will automatically be placed in root:
        if (this->root == nullptr) {

            treeNode<T,S> *new_node = new treeNode<T,S>(data,key);

            root = new_node;

        } else// not the first node in the tree
            recurtionAdd(root,data,key);


        largestNode=findRightMost(root);
        smallestNode=findLeftMost(root);

    }
    //return balance factor of node.
    int get_balanceFactor(treeNode<T,S> const *node){
        return get_height_addition(node->get_left())- get_height_addition
                (node->get_right());

    }
    ///repair balance factor of tree, starting at node, using left/right rolls
    void repairBF(treeNode<T,S> *new_node) {
        treeNode<T, S> *current = new_node;
        int bf;
        //while loop to be executed on all nodes in the path from original
        // node to root.
        while (current!= nullptr) {
            bf = get_height_addition(current->get_left()) -
                 get_height_addition(current->get_right());

            current->set_height(std::max(get_height_addition(current->get_left()),
                                         get_height_addition(current->get_right()))+1);

            //avl tree ensures adding or removing node will cause
            // maximum balance factor error of 2 or -2

            if (bf == 2) {
                if (get_balanceFactor(current->get_left()) > 0)
                    rightRotation(current);
                else {
                    leftRotation(current->get_left());
                    rightRotation(current);
                }
            }

            if (bf == -2) {
                if (get_balanceFactor(current->get_right()) > 0) {
                    rightRotation(current->get_right());
                    leftRotation(current);
                } else
                    leftRotation(current);
            }
            //update height of node that could have been changed
            current->set_height(std::max(get_height_addition(current->get_left()),
                                         get_height_addition(current->get_right()))+1);

            //move up one node in the path to root
            current=current->get_father();

        }
    }

//    treeNode<T,S>* recursionDelete(S key,treeNode<T,S> *node) {
//        if (root==NULL)
//            return root;
//
//
//    }

    ///return node pointer containing the key given. param node is given to
    /// specify where to stat searching from, used for recursion call and is
    /// root in the beginning. return null if node not found.
    treeNode<T,S>* searchKey(S key,treeNode<T,S> *node){
        if (node==nullptr)
            return nullptr;
        if(key==node->get_key())
            return node;
        if(key<node->get_key())
            return searchKey(key,node->get_left());
        else
            return searchKey(key,node->get_right());
    }

    /// function to add node to tree that already has a root. searches for
    /// node in tree, if node is found, exit. otherwise observe the last leaf
    /// in the search path, if the node to add is bigger make it a right son
    /// of the leaf. otherwise make it the left.
    void recurtionAdd(treeNode<T,S> *root, T to_add, S key)
    {
        if (root->get_key()==key) {// new node already exists
            return ;
        }
        if (root->get_key()<key){ // new node is larger than current node in
            // search path

            if (root->get_right() == nullptr) {//this is where node needs to
                // be added.

                treeNode<T,S> *new_node = new treeNode<T,S>(to_add,key);

                new_node->set_father(root);

                root->set_right(new_node);

                repairBF(new_node); //repair balance factor of tree, starting
                // at new node.

                return;

            } else {// recursion call with right son
                recurtionAdd(root->get_right(),to_add,key);

                return;
            }
        }


        if (root->get_key()>key){ // new node is smallerthan current node in
            // search path

            if (root->get_left() == nullptr) {//this is where node needs to
                // be added

                treeNode<T,S>* new_node = new treeNode<T,S>(to_add,key);

                new_node->set_father(root);

                root->set_left(new_node);

                repairBF(new_node); //repair balance factor of tree, starting
                // at new node.
                return;
            }
            else {
// recursion call with right son
                recurtionAdd(root->get_left(), to_add,key);
            }
        }
    }

    /// get height of node with option of returning -1 if node is null.
    /// needed to calculate balance factor.
    int get_height_addition(treeNode<T,S>* node){
        if (node)
            return node->get_height();

        else return -1;//node is null

    }

    ///destroy tree recursively, remove all nodes and free their data.
    void recursionDestroy(treeNode<T,S>* node){
        if (!node) return;
        recursionDestroy(node->get_left());
        recursionDestroy(node->get_right());
        if(node->get_data()!= nullptr)
            delete node->get_data();
        delete node;
        
    }


///destructor using recursion destroy
    ~avl_Tree(){
        recursionDestroy(root);
    }

    ///replace node with right son, move node to the left
    void leftRotation(treeNode<T,S>* node){

        treeNode<T,S>* right=node->get_right();
        treeNode<T,S>* rightLeft=right->get_left();

        right->set_left(node);
        node->set_right(rightLeft);

        if(rightLeft!= nullptr){
            rightLeft->set_father(node);
        }


        right->set_father(node->get_father());
        if(node->get_father()!=nullptr){
            if(node->get_father()->get_left()==node){
                (node->get_father())->set_left(right);
            }
            else
                (node->get_father())->set_right(right);
        }
        else{
            this->root=right;
        }
        node->set_father(right);

        //update height of nodes moved
        node->set_height(std::max(get_height_addition(node->get_left()),get_height_addition(node->get_right()))+1);
        right->set_height(std::max(get_height_addition(right->get_left()),get_height_addition(right->get_right()))+1);
    }

    ///replace node with left son, move node to the right
    void rightRotation(treeNode<T,S>* node){
        treeNode<T,S>* left=node->get_left();
        treeNode<T,S>* leftRight=left->get_right();

        left->set_right(node);

        node->set_left(leftRight);
        if(leftRight!= nullptr){
            leftRight->set_father(node);
        }

        left->set_father(node->get_father());
        if(node->get_father()!=nullptr){
            if(node->get_father()->get_left()==node){
                (node->get_father())->set_left(left);
            } else
                (node->get_father())->set_right(left);
        }
        else{
            this->root=left;
        }

        node->set_father(left);

        //update height of nodes moved

        node->set_height(std::max(get_height_addition(node->get_left()),
                                  get_height_addition(node->get_right()))+1);
        left->set_height(std::max(get_height_addition(left->get_left()),get_height_addition(left->get_right()))+1);
    }




///given generic action "p", do p for the k smallest nodes in the tree. arr1,
/// and arr2, are given to fill them with most popular songs. k: is the number
/// nodes left to do the generic action with, num: total number of actions to do
    template<typename P>
    int printKmin(int num,int &k,int *arr1,int *arr2,int id, P p) {
        int counter = 0;
        treeNode<T, S> *curr=smallestNode;
        treeNode<T, S> *last = nullptr; //last node we did generic action with



        while ((0 < k)&&(curr!= nullptr)) {
            if (curr->get_left() == last) { //we finished with left sub tree
                p(num,k,curr,arr1,arr2,id);
                counter++;

                if (curr->get_right()!= nullptr) { //we finished with left sub tree -> go to right sub tree
                    //get next largest after curr:
                    curr = findLeftMost(curr->get_right());
                    last=curr->get_left();
                }
                else { //we finished with both left and right sub tree, and there is no left sub tree
                    last = curr;
                    curr = curr->get_father();
                }

            } else if (last->get_father() == curr) { //finished with both left and right sub trees
                last = curr;
                curr = last->get_father();
            }

        }
        return k;
            //k is the number of items need to be printed after this function

    }


///find rightmost node in tree, when given tree root
    treeNode<T,S>* findRightMost( treeNode<T,S>* node) const{

        while(node->get_right()!= nullptr)
            node=node->get_right();
        return node;
    }
    ///find leftmost node in tree, when given tree root
    treeNode<T,S>* findLeftMost(treeNode<T,S>* node)const {
        while(node->get_left()!= nullptr)
            node=node->get_left();
        return node;
    }

/// return tree root
    treeNode<T,S>* getRoot() const {
        return root;
    }

    /// return largest node in tree
    treeNode<T,S>* getLargest(){
        return largestNode;
    }
/// return smalles node in tree
    treeNode<T,S>* getSmallest(){
        return smallestNode;
    }
///remove root in tree
    void removeRoot(int key) {
        //root is the only node in the tree:
        if ((root->get_right() == nullptr) && (root->get_left() == nullptr)) {
            delete root->get_data();
            delete root;
            root=nullptr;//TODO is this ok?
            return;
        }
        //root only has left son:
        if (root->get_right() == nullptr) {
            root = root->get_left();
            delete root->get_father()->get_data();
            delete root->get_father();

            root->set_father(nullptr);

            return;
        }
        //root only has right son:
        if (root->get_left() == nullptr) {
            root = root->get_right();
            delete root->get_father()->get_data();
            delete root->get_father();

            root->set_father(nullptr);

            return;
        }
        //root has two sons. we will find the next largest after root:
        treeNode<T,S>* NextLargest=findLeftMost(root->get_right());

        //swap places with root and next largest. tree is not a search tree
        // now but once we remove root it will be again.
        root->swapNodes(NextLargest);

        //check if next largest is a right or left son:
        bool right_son=(root->get_right() == NextLargest);

        //check if next largest was not a leaf:
        if((NextLargest->get_left()!= nullptr)||(NextLargest->get_right()!=
                                                 nullptr)) {

            //call function for removing a node that has one son
            removeOneSonNode(NextLargest, right_son,
                             NextLargest->get_father());
            return;
        }

        //next largest was a leaf, to remove the root we just need to delete it
        treeNode<T,S>* father=NextLargest->get_father();

        //set next largest's father to have null son where next largest was.
        if(right_son)
            root->set_right(nullptr);
        else
            father->set_left(nullptr);
        delete NextLargest->get_data();
        delete NextLargest;
        NextLargest= nullptr;

        //update height of of father, because we deleted a son.
        father->set_height(std::max(get_height_addition(father->get_left()),
                                    get_height_addition(father->get_right()))
                           +1);


    }
    ///function to remove a node that has one son. param NodeToRemove will
    /// be removed, param right son specifies if NodeToRemove is a right son
    /// or not, Father is NodeToRemove's father node.
    void removeOneSonNode(treeNode<T,S>* NodeToRemove, bool rightSon,
                          treeNode<T,S>* Father ){
        //NodeToRemove to remove only has left son,
        // move the left son up to where node was:
        if(NodeToRemove->get_right()== nullptr) {

            if (rightSon) {//NodeToRemove is a right son
                Father->set_right(NodeToRemove->get_left());
                NodeToRemove->get_left()->set_father(Father);
                delete NodeToRemove->get_data();
                delete NodeToRemove;
                NodeToRemove= nullptr;
                Father->set_height(std::max(get_height_addition(Father->get_left
                        ()),get_height_addition(Father->get_right()))+1);

                //repair balance factor if it was damaged, using rolls.

                repairBF(Father->get_right());

            } else {//NodeToRemove is a left son
                Father->set_left(NodeToRemove->get_left());

                NodeToRemove->get_left()->set_father(Father);
                delete NodeToRemove->get_data();
                delete NodeToRemove;
                NodeToRemove= nullptr;
                Father->set_height(std::max(get_height_addition(Father->get_left
                        ()),get_height_addition(Father->get_right()))+1);

                //repair balance factor if it was damaged, using rolls.
                repairBF(Father->get_left());
            }
            //tree has changed, therefore we need to update these:
            largestNode=findRightMost(root);
            smallestNode=findLeftMost(root);
            return;

        }
        //Node to remove only has right son, move the left son up to where
        // node was
        else if(NodeToRemove->get_left()== nullptr){

            if (rightSon) {//Node is a right son

                Father->set_right(NodeToRemove->get_right());
                NodeToRemove->get_right()->set_father(Father);
                delete NodeToRemove->get_data();
                delete NodeToRemove;
                NodeToRemove= nullptr;
                Father->set_height(std::max(get_height_addition(Father->get_left
                        ()),get_height_addition(Father->get_right()))+1);

                //repair balance factor if it was damaged, using rolls.
                repairBF(Father->get_right());

            } else {//Node is a left son

                Father->set_left(NodeToRemove->get_right());
                NodeToRemove->get_right()->set_father(Father);
                delete NodeToRemove->get_data();
                delete NodeToRemove;
                NodeToRemove= nullptr;
                Father->set_height(std::max(get_height_addition(Father->get_left
                        ()),get_height_addition(Father->get_right()))+1);

                //repair balance factor if it was damaged, using rolls.
                repairBF(Father->get_left());
            }

            return;
        }

    }

    ///remove a leaf from tree, right son specifies if the leaf is a right
    /// son, NodeToRemove is the leaf to be removed, Father is the leaf's father
    void removeLeaf(treeNode<T,S>* NodeToRemove, bool rightSon,
                    treeNode<T,S>* Father ){
        if(rightSon){
            Father->set_right(nullptr);
        }
        else{
            Father->set_left(nullptr);
        }
        delete NodeToRemove->get_data();
        delete NodeToRemove;
        NodeToRemove= nullptr;
        Father->set_height(std::max(get_height_addition(Father->get_left
                ()),get_height_addition(Father->get_right()))+1);
        repairBF(Father);
        if (root == nullptr) return;

        //tree has changed so we need to update these
        largestNode=findRightMost(root);
        smallestNode=findLeftMost(root);
        return;


    }
    /// remove a node from this tree that has Key
    void removeByKey (S key){
        //find the node to remove
        treeNode<T,S>* NodeToRemove=this->searchKey(key, root);

        if (NodeToRemove==nullptr)
            return;// node does not exist in this tree

        bool rightSon= false;

        //node to remove is the root of the tree:
        if(NodeToRemove==this->root){

            this->removeRoot(key);

            repairBF(root);

            if (root == nullptr) return;

            largestNode=findRightMost(root);
            smallestNode=findLeftMost(root);
            return;
        }
        treeNode<T,S>* Father=NodeToRemove->get_father();
        if(Father->get_right()==NodeToRemove){ //
            // Node to remove is a right son
            rightSon=true;
        }
        // Node to remove is a leaf
        if((NodeToRemove->get_left()==nullptr)&&(NodeToRemove->get_right()
                                                 ==nullptr))

        {
            //call leaf removing function
            removeLeaf(NodeToRemove,rightSon,Father);
            return;

        }
            //Node has one son
        else if((NodeToRemove->get_left()== nullptr)||(NodeToRemove->get_right
                ()==nullptr)){

            removeOneSonNode(NodeToRemove, rightSon, Father);

            largestNode=findRightMost(root);
            smallestNode=findLeftMost(root);
            return;
        }
        //Node to remove has two children

        //find the next largest:
        treeNode<T,S>* NextLargest=findLeftMost(NodeToRemove->get_right());
        //swap the two nodes. NextLargest has to be a leaf, or one son node.
        NodeToRemove->swapNodes(NextLargest);

        //next largest node was a leaf:
        if((NextLargest->get_left()==nullptr)&&(NextLargest->get_right()
                                                ==nullptr))

        {
            removeLeaf(NextLargest,NodeToRemove->get_right() == NextLargest,NextLargest->get_father());
            largestNode=findRightMost(root);
            smallestNode=findLeftMost(root);
            return;
        }
        //next largest was a one son node:
        removeOneSonNode(NextLargest, NodeToRemove->get_right() == NextLargest,
                         NextLargest->get_father());
        largestNode=findRightMost(root);
        smallestNode=findLeftMost(root);

    }
    //print all nodes in tree n order
    void print_in_order(treeNode<int*,int>* t)
    {
        if (t== nullptr)
            return;
        print_in_order(t->get_left());
        int bf=get_height_addition(t->get_left())-get_height_addition
                (t->get_right());

        cout<<t->get_data()<<"  bf:  "<<bf<<"  height:  "<<t->get_height()
            <<"\n";
        print_in_order(t->get_right());
    }

    void printTree()
    {
        if (root== nullptr)
            return;
        print_in_order(root);
        cout<<"-----------------\n";
    }


};
#endif //INC_1_WET_NEW_AVL_TREE_H
