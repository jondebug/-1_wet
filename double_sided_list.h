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

    ///set key of this node
    void set_key(const int key){
        this->key=key;
    }

    int get_key() const{
        return key;
    }

    void set_data(T const data){
        this->data=data;
    }

    void set_next(listNode* const next) {

        this->next=next;
    }

    void set_prev(listNode* const prev) {


        this->prev =prev;
    }
    listNode<T> *get_next()const  {
        if (this== nullptr)
            return nullptr;
        return this->next;

    }

    listNode<T> *get_prev()const {
        if (this== nullptr)
            return nullptr;
        return this->prev;

    }
    void print(){
        cout<<this->data<<"\n";
    }

    T get_data() const{
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

///create empty list with length 0
    double_sided_list():first(nullptr), last(nullptr),length(0), iterator(
            nullptr){};


/// add node to the end of list with data: node_data and key: key.
    void addNode(T node_data, int key){
        this->length=this->length+1;
        //this is the first node
        if(first==nullptr){
            first = new listNode<T>;
            first->set_data(node_data);
            first->set_next(nullptr);
            first->set_prev(nullptr);
            last=first;
            iterator=first;
            first->set_key(key);
        }
        //node is not the first node in list
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
///return node iterator currently points to
    T get_current(){
        if (this->iterator!=nullptr)
            return this->iterator->get_data();

    }
    /// return node after current node, move iterator to next node.
    T get_next(){
        if ((iterator!=nullptr)||(iterator->get_next()!=nullptr)) {
            iterator = iterator->get_next();
            return iterator->get_data();
        }
        return nullptr;

    }
/// get data of first node on the list
    T get_first_data() {
        iterator = this->first;
        return iterator->get_data();
    }
///get first node on the list
    listNode<T>* get_first() {
        iterator = this->first;
        return iterator;
    }
///get last node on the list
    listNode<T>* get_last() {
        iterator = this->last;
        return iterator;
    }
///remove node_to_remove from the list
    void remove_node(listNode<T> * node_to_remove) {
        if (node_to_remove->get_prev() != nullptr) {
             node_to_remove->get_prev()->set_next(node_to_remove->get_next());
         }
        else{ // this node is first in list
            first=node_to_remove->get_next();
        }
        // this node is not last in list
        if (node_to_remove->get_next() != nullptr) {
            node_to_remove->get_next()->set_prev(node_to_remove->get_prev());
        }
            // this node is last in list
        else{
            last=node_to_remove->get_prev();
        }
		delete node_to_remove->get_data();
        delete node_to_remove;
    }
/// given pointer to a node in the list: node_to_add_after, create a new node
/// with data: data and key :key. and this new node after given node.
    listNode<T>* add_node_after(listNode<T> * node_to_add_after, T data, int
    key){


        listNode<T>* new_node=new listNode<T>;

        // set all data for new node:
        new_node->set_prev(node_to_add_after);
        new_node->set_next(node_to_add_after->get_next());
        new_node->set_data(data);
        new_node->set_key(key);

        //set all data for prev node:
        node_to_add_after->set_next(new_node);

        //set all data for next node:

        if(new_node->get_next()!= nullptr)
            new_node->get_next()->set_prev(new_node);

        return new_node;

    }
///destructor for list, iterate over all of the list and delete all nodes
/// after freeing their data
    ~double_sided_list<T> (){
        listNode<T> *it = this->first;
        listNode<T> *temp = this->first;

        while(it!=nullptr){
            it=temp->get_next();
            if (temp->get_data()!= nullptr)
                delete temp->get_data();
            delete temp;
            temp=it;
        }

    }

};

#endif //INC_1_WET_NEW_DOUBLE_SIDED_LIST_H
