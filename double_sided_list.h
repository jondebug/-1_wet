//
// Created by jonathan_pc on 4/30/2020.
//

#ifndef INC_1_WET_NEW_DOUBLE_SIDED_LIST_H
#define INC_1_WET_NEW_DOUBLE_SIDED_LIST_H
#include <iostream>
using namespace std;

template<typename T>
class listNode {

    listNode *next;

    listNode *prev;

    T data;

    int key;

public:

//
//    listNode(T data, listNode *prev = nullptr, listNode *next = nullptr) :
//            data(data), next(next), prev(prev) {
    //    }
    void set_key(int key){
        this->key=key;
    }


    int get_key(){
        return key;
    }

    void set_data(T data){
        this->data=data;
    }

    void set_next(listNode* next) {

        this->next=next;
    }

    void set_prev(listNode* prev) {


        this->prev =prev;
    }
    listNode<T> *get_next() {
        if (this== nullptr)
            return nullptr;
        return this->next;

    }

    listNode<T> *get_prev() {
        if (this== nullptr)
            return nullptr;
        return this->prev;

    }
    void print(){
        cout<<this->data<<"\n";
    }

    T get_data(){
        return this->data;
    }



    void operator= (listNode<T>* node){
        this->next=node->next;
        this->prev=node->prev;
        this->data=node->data;
    }


};
//---------------------------------------------

template<typename T>

class double_sided_list {



    listNode<T>* first;

    listNode<T>* last;

    int length;

    listNode<T>* iterator;

public:


    double_sided_list():first(nullptr), last(nullptr),length(0), iterator(
            nullptr){};



    void addNode(T node_data, int key){
        this->length=this->length+1;

        if(first==nullptr){
            first = new listNode<T>;
            first->set_data(node_data);
            first->set_next(nullptr);
            first->set_prev(nullptr);
            last=first;
            iterator=first;
            first->set_key(key);
        }
        else{
            listNode<T>* new_node = new listNode<T>;
            new_node->set_data(node_data);
            new_node->set_prev(last);
            new_node->set_next(nullptr);
            new_node->set_key(key);
            last->set_next(new_node);
            last=new_node;
        }


    }

    T get_current(){
        if (this->iterator!=nullptr)
            return this->iterator->get_data();

    }


    T get_next(){
        if ((iterator!=nullptr)||(iterator->get_next()!=nullptr)) {
            iterator = iterator->get_next();
            return iterator->get_data();
        }
        return nullptr;

    }

    T get_first_data() {
        iterator = this->first;
        return iterator->get_data();
    }

    listNode<T>* get_first() {
        iterator = this->first;
        return iterator;
    }

    listNode<T>* get_last() {
        iterator = this->last;
        return iterator;
    }




    listNode<T>* get_current_node(){
        return iterator;
    }



    void printList(){

        listNode<T> *it = this->first;

        while (it!= nullptr)
        {
            T data = it->get_data();
            cout<<data<<"\n";
            it=it->get_next();

        }

    }

    void remove_node(listNode<T> * node_to_remove) {
        if (node_to_remove->get_prev() != nullptr) {
             node_to_remove->get_prev()->set_next(node_to_remove->get_next());
         }
        else{ // this node is first in list
            first=node_to_remove->get_next();
        }
        if (node_to_remove->get_next() != nullptr) {
            node_to_remove->get_next()->set_prev(node_to_remove->get_prev());
        }
        else{ // this node is last in list
            last=node_to_remove->get_prev();
        }
		delete node_to_remove->get_data();
        delete node_to_remove;
    }

    listNode<T>* add_node_after(listNode<T> * node_to_add_after, T data, int
    key){

//        if(node_to_add_after== nullptr){
//            listNode<T>* temp=first;
//        }

        listNode<T>* new_node=new listNode<T>;

        // all data for new node:
        new_node->set_prev(node_to_add_after);
        new_node->set_next(node_to_add_after->get_next());
        new_node->set_data(data);
        new_node->set_key(key);

        // all data for prev node:
        node_to_add_after->set_next(new_node);
        //all data for next node:

//        if(node_to_add_after->get_next()!= nullptr)
//            node_to_add_after->get_next()->set_prev(new_node);

        //need to be changed to:
        if(new_node->get_next()!= nullptr)
            new_node->get_next()->set_prev(new_node);

        return new_node;

    }

    ~double_sided_list<T> (){
        listNode<T> *it = this->first;
        listNode<T> *temp = this->first;
        while(it!=nullptr){
            it=temp->get_next();
            if (temp->get_data()!= nullptr)
                delete temp->get_data();
                //temp->get_data()->pointer_tree_destroy();
            delete temp;
            temp=it;
        }

    }

};

#endif //INC_1_WET_NEW_DOUBLE_SIDED_LIST_H
