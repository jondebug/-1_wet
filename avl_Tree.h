//
// Created by jonathan_pc on 4/30/2020.
//

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

    treeNode (T data,S key):father(nullptr), right_son(nullptr),left_son(nullptr),
                            height(0),data(data),key(key){};

    void set_data(T data){
        this->data=data;
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



public:
    avl_Tree(): root(nullptr), largestNode(nullptr){};

    void add_treeNode(T data,S key) {

        int left_counter = 0;

        if (this->root == nullptr) {

            treeNode<T,S> *new_node = new treeNode<T,S>(data,key);

            root = new_node;

            return;
        } else
            recurtionAdd(root,data,key);


        //treeNode<T,S>* largest=new treeNode<T,S>(0,0); //TODO mabye need to change to new treeNode
        treeNode<T,S>* largest=root;
        largest=root;
        while(largest->get_right()!=nullptr){
            largest=largest->get_right();
        }
        largestNode=largest;
    }
    int get_balanceFactor(treeNode<T,S> *node){
        return get_height_addition(node->get_left())- get_height_addition
                                                                  (node->get_right());

    }

    void repairBF(treeNode<T,S> *new_node) {
        treeNode<T, S> *current = new_node->get_father();
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
                    leftRotation(current->get_left());
                } else
                    leftRotation(current);
            }

            current=current->get_father();

        }
    }

    treeNode<T,S>* searchKey(S key,treeNode<T,S> *node){
        if (node==nullptr)
            return NULL;
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

                repairBF(new_node); //TO-BE-WRITTEN

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
        if (node!=nullptr)
            return node->get_height();
        else return -1;
    }


    void recurtionDestroy(treeNode<T,S>* node){
        if (!node) return;
        recurtionDestroy(node->get_left());
        recurtionDestroy(node->get_right());
        delete node;
    }

    ~avl_Tree(){
        recurtionDestroy(root);
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

    treeNode<T,S>* getRoot(){
        return root;
    }
    treeNode<T,S>* getLargest(){
        return largestNode;
    }

};
#endif //INC_1_WET_NEW_AVL_TREE_H
