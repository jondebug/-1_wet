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

    treeNode (T data,S key):left_son(nullptr), right_son(nullptr),father(nullptr),
                            height(0),key(key),data(data){};


    treeNode():left_son(nullptr), right_son(nullptr),father(nullptr),
               height(0){};


    void set_data(T data){
        this->data=data;
    }

    void set_key(S key){
        this->key=key;
    }

    void set_father(treeNode* father){
        this->father=father;
    }

    void set_left(treeNode* left){
        this->left_son=left;
    }

    void set_right(treeNode* right){
        this->right_son=right;
    }

    void set_height(int HEIGHT){
        this->height=HEIGHT;
    }
    void swapNodes(treeNode* to_swap) {
        treeNode temp(*to_swap);

        to_swap->data=data;
        to_swap->key=key;

        data=temp.data;
        key=temp.key;

    }

    treeNode* get_left(){
        return left_son;
    }

    treeNode* get_right(){
        return right_son;
    }
    treeNode* get_father(){
        return father;
    }

    int get_height(){
        return height;
    }

    T get_data(){
        return data;
    }

    S get_key(){
        return key;
    }

};
template<typename T,typename S>
class avl_Tree{

    treeNode<T,S> * root;

    treeNode<T,S> * largestNode;
    treeNode<T,S> * smallestNode;



public:
    avl_Tree(): root(nullptr), largestNode(nullptr),smallestNode(nullptr){};

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

    void delete_unwanted_nodes(treeNode<T,S> *node,int &numberToDelete, bool
    right_son , treeNode<T,S> *Father)
    {
        if ((node== nullptr)||(numberToDelete==0)) return;
        delete_unwanted_nodes(node->get_right(),numberToDelete,true,node);

        if (numberToDelete==0) return;
        if (node->get_height()==0) {
            if ((right_son)&&(Father!= nullptr)){
                Father->set_right(nullptr);
            }
            else{
                if(Father!= nullptr) Father->set_left(nullptr);
            }
            delete node;
            node=nullptr;
            numberToDelete--;
            return;
        }
        delete_unwanted_nodes(node->get_left(),numberToDelete,false, node);
        node->set_height(std::max(get_height_addition(node->get_left()),
                                  get_height_addition(node->get_right()))+1);
    }

    treeNode<T,S>* tree_create_helper(int height,treeNode<T,S> *father){
        if (height<=0) return nullptr;
        treeNode<T,S> *tree = new treeNode<T,S>();
        tree->set_father(father);
        tree->set_height(height-1);
        tree->set_left(tree_create_helper(height-1,tree));
        tree->set_right(tree_create_helper(height-1,tree));
        return tree;
    }

    void set_value_inOrder(treeNode<T,S> *node,int m,int &counter){
        if ((node==nullptr)||(counter>m)) return;
        set_value_inOrder(node->get_left(),m,counter);
        int* data=new int;

        *data=counter;
        node->set_data(data);

        node->set_key(counter);
        counter++;
        set_value_inOrder(node->get_right(),m,counter);



    }



    void add_treeNode(T data,S key) {
        if (this->root == nullptr) {

            treeNode<T,S> *new_node = new treeNode<T,S>(data,key);

            root = new_node;

        } else
            recurtionAdd(root,data,key);


        largestNode=findRightMost(root);
        smallestNode=findLeftMost(root);

    }
    int get_balanceFactor(treeNode<T,S> *node){
        return get_height_addition(node->get_left())- get_height_addition
                (node->get_right());

    }

    void repairBF(treeNode<T,S> *new_node) {
        treeNode<T, S> *current = new_node;
        int bf;

        while (current!= nullptr) {
            bf = get_height_addition(current->get_left()) -
                 get_height_addition(current->get_right());

            current->set_height(std::max(get_height_addition(current->get_left()),
                                         get_height_addition(current->get_right()))+1);
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
            current->set_height(std::max(get_height_addition(current->get_left()),
                                         get_height_addition(current->get_right()))+1);

            current=current->get_father();

        }
    }

    treeNode<T,S>* recursionDelete(S key,treeNode<T,S> *node) {
        if (root==NULL)
            return root;


    }


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


    void recurtionAdd(treeNode<T,S> *root, T to_add, S key)
    {
        if (root->get_key()==key) {// new node already exists
            return ;
        }
        if (root->get_key()<key){ // new node is larger

            if (root->get_right() == nullptr) {

                treeNode<T,S> *new_node = new treeNode<T,S>(to_add,key);

                new_node->set_father(root);

                root->set_right(new_node);

                repairBF(new_node);

                return;

            } else {
                recurtionAdd(root->get_right(),to_add,key);

                return;
            }
        }


        if (root->get_key()>key){ // new node is smaller

            if (root->get_left() == nullptr) {

                treeNode<T,S>* new_node = new treeNode<T,S>(to_add,key);

                new_node->set_father(root);

                root->set_left(new_node);
                repairBF(new_node); //TO-BE-WRITTEN
                return;
            }
            else {

                recurtionAdd(root->get_left(), to_add,key);
            }
        }
    }


    int get_height_addition(treeNode<T,S>* node){
        if (node)
            return node->get_height();
        else return -1;

    }


    void recurtionDestroy(treeNode<T,S>* node){
        if (!node) return;
        recurtionDestroy(node->get_left());
        recurtionDestroy(node->get_right());
        if(node->get_data()!= nullptr)
            delete node->get_data();
        delete node;
        
    }



    ~avl_Tree(){
        recurtionDestroy(root);
    }

    void treeClear(){
        recurtionDestroy(root);
        root= nullptr;

    }
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

        node->set_height(std::max(get_height_addition(node->get_left()),get_height_addition(node->get_right()))+1);
        right->set_height(std::max(get_height_addition(right->get_left()),get_height_addition(right->get_right()))+1);
    }


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

        node->set_height(std::max(get_height_addition(node->get_left()),
                                  get_height_addition(node->get_right()))+1);
        left->set_height(std::max(get_height_addition(left->get_left()),get_height_addition(left->get_right()))+1);
    }

    treeNode<T,S>* findNext(treeNode<T,S>* node){


    }

    template<typename P>
    int printKmax(int &k, P p) {
        int counter = 0;
        treeNode<T, S> *curr = largestNode;
        treeNode<T, S> *last = nullptr;

        while ((counter < k) && (curr != nullptr)) {

            if (curr->get_right() == last) { //we finished with right sub tree
                p(k, curr);
                counter++;

                if (curr->get_left() !=nullptr) { //we finished with right sub tree -> go to left sub tree
                    curr = findRightMost(curr->get_left());
                    last = curr->get_right();
                } else { //we finished with both left and right sub tree, and there is no left sub tree
                    last = curr;
                    curr = curr->get_father();
                }

            } else if (last->get_father() ==
                       curr) { //finished with both left and right sub trees
                last = curr;
                curr = last->get_father();
            }
        }

        return counter;
    }




    template<typename P>
    int printKmin(int num,int &k,int *arr1,int *arr2,int id, P p) {
        int counter = 0;
        treeNode<T, S> *curr=smallestNode;
        treeNode<T, S> *last = nullptr;



        while ((0 < k)&&(curr!= nullptr)) {
            if (curr->get_left() == last) { //we finished with left sub tree
                p(num,k,curr,arr1,arr2,id);
                counter++;

                if (curr->get_right()!= nullptr) { //we finished with left sub tree -> go to right sub tree
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
        return k; //k is the number of items need to be printed after this function

    }



    treeNode<T,S>* findRightMost(treeNode<T,S>* node){

        while(node->get_right()!= nullptr)
            node=node->get_right();
        return node;
    }
    treeNode<T,S>* findLeftMost(treeNode<T,S>* node){
        while(node->get_left()!= nullptr)
            node=node->get_left();
        return node;
    }


    treeNode<T,S>* getRoot(){
        return root;
    }
    treeNode<T,S>* getLargest(){
        return largestNode;
    }

    treeNode<T,S>* getSmallest(){
        return smallestNode;
    }

    void removeRoot(int key) {

        if ((root->get_right() == nullptr) && (root->get_left() == nullptr)) {
            delete root->get_data();
            delete root;
            root=nullptr;//TODO is this ok?
            return;
        }
        if (root->get_right() == nullptr) {
            root = root->get_left();
            delete root->get_father()->get_data();
            delete root->get_father();

            root->set_father(nullptr);

            return;
        }
        if (root->get_left() == nullptr) {
            root = root->get_right();
            delete root->get_father()->get_data();
            delete root->get_father();

            root->set_father(nullptr);

            return;
        }

        treeNode<T,S>* NextLargest=findLeftMost(root->get_right());
        root->swapNodes(NextLargest);

        bool right_son=(root->get_right() == NextLargest);

        if((NextLargest->get_left()!= nullptr)||(NextLargest->get_right()!=
                                                 nullptr)) {


            removeOneSonNode(NextLargest, right_son,
                             NextLargest->get_father());
            return;
        }

        treeNode<T,S>* father=NextLargest->get_father();

        if(right_son)
            root->set_right(nullptr);
        else
            father->set_left(nullptr);
        delete NextLargest->get_data();
        delete NextLargest;
        NextLargest= nullptr;
        father->set_height(std::max(get_height_addition(father->get_left()),
                                    get_height_addition(father->get_right()))
                           +1);


    }

    void removeOneSonNode(treeNode<T,S>* NodeToRemove, bool rightSon,
                          treeNode<T,S>* Father ){

        if(NodeToRemove->get_right()== nullptr) {//Node to remove only has
            // left son, move the left son up to where node was
            if (rightSon) {//Node is a right son
                Father->set_right(NodeToRemove->get_left());
                NodeToRemove->get_left()->set_father(Father);
                delete NodeToRemove->get_data();
                delete NodeToRemove;
                NodeToRemove= nullptr;
                Father->set_height(std::max(get_height_addition(Father->get_left
                        ()),get_height_addition(Father->get_right()))+1);


                repairBF(Father->get_right());
            } else {//Node is a left son
                Father->set_left(NodeToRemove->get_left());

                NodeToRemove->get_left()->set_father(Father);
                delete NodeToRemove->get_data();
                delete NodeToRemove;
                NodeToRemove= nullptr;
                Father->set_height(std::max(get_height_addition(Father->get_left
                        ()),get_height_addition(Father->get_right()))+1);

                repairBF(Father->get_left());
            }
            largestNode=findRightMost(root);
            smallestNode=findLeftMost(root);
            return;

        }
        else if(NodeToRemove->get_left()== nullptr){//Node to remove only has
            // right son, move the left son up to where node was
            if (rightSon) {//Node is a right son
                Father->set_right(NodeToRemove->get_right());
                NodeToRemove->get_right()->set_father(Father);
                delete NodeToRemove->get_data();
                delete NodeToRemove;
                NodeToRemove= nullptr;
                Father->set_height(std::max(get_height_addition(Father->get_left
                        ()),get_height_addition(Father->get_right()))+1);

                repairBF(Father->get_right());
            } else {//Node is a left son
                Father->set_left(NodeToRemove->get_right());
                NodeToRemove->get_right()->set_father(Father);
                delete NodeToRemove->get_data();
                delete NodeToRemove;
                NodeToRemove= nullptr;
                Father->set_height(std::max(get_height_addition(Father->get_left
                        ()),get_height_addition(Father->get_right()))+1);
                repairBF(Father->get_left());
            }

            return;
        }

    }
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
        largestNode=findRightMost(root);
        smallestNode=findLeftMost(root);
        return;


    }

    void removeByKey (S key){

        treeNode<T,S>* NodeToRemove=this->searchKey(key, root);

        if (NodeToRemove==nullptr)
            return;
        bool rightSon= false;


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
        NodeToRemove->swapNodes(NextLargest);
        if((NextLargest->get_left()==nullptr)&&(NextLargest->get_right()
                                                ==nullptr))

        {
            removeLeaf(NextLargest,NodeToRemove->get_right() == NextLargest,NextLargest->get_father());
            largestNode=findRightMost(root);
            smallestNode=findLeftMost(root);
            return;
        }

        removeOneSonNode(NextLargest, NodeToRemove->get_right() == NextLargest,
                         NextLargest->get_father());
        largestNode=findRightMost(root);
        smallestNode=findLeftMost(root);

    }

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
