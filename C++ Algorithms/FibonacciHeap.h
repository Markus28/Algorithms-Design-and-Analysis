#ifndef KRUSKAL_MST_FIBONACCIHEAP_H
#define KRUSKAL_MST_FIBONACCIHEAP_H


#include <cassert>
#include <unordered_map>
#include <vector>
#include <list>
#include <iostream>

template <class T>
class FibonacciHeap {
public:
    class FibonacciNode {
    public:

        FibonacciNode(T value, double key, bool marked, unsigned int rank, FibonacciNode* child,
                FibonacciNode* parent, FibonacciNode* next, FibonacciNode* prev): value(value), key(key), marked(marked),
                rank(rank), child(child), parent(parent), next(next), prev(prev) {};

        /**
         * This method will create a deep copy of the FibonacciNode. All pointers (next, prev, child, parent)
         * will be referring to copies.
         * @return
         */
        FibonacciNode* deep_copy() {
            //We want to copy everything. We just call deep_copy with an empty hashmap
            std::unordered_map < FibonacciNode * , FibonacciNode * > do_not_copy;
            return deep_copy(do_not_copy);
        }

        /**
         * This method will create a deep copy of the FibonacciNode. In order to prevent an infinite copying loop (after
         * all the linked lists are circular) adresses of nodes which already have a copy are stored in the do_not_copy
         * table. The value associated to that adress (which is the key in this hash map) is the adress of the copy.
         * This adress will be substituted instead of a copy. deep_copy will alter do_not_copy and call it recursively.
         * @param do_not_copy A hashtable which maps adresses of already copied nodes to the adresses of the copy
         * @return Pointner to the deep copy of this node
         */
        FibonacciNode* deep_copy(std::unordered_map<FibonacciNode*, FibonacciNode*> &do_not_copy) {
            //Check whether we have copied this node at some point
            typename std::unordered_map<FibonacciNode*, FibonacciNode*>::const_iterator got = do_not_copy.find(this);

            if (got != do_not_copy.end()) {
                //We have already copied this element at some point -> return pointer to existing copy
                return got->second;
            }


            //First create a shallow copy of this node (rank, being_destroyed, value, marked are copied properly)
            FibonacciNode *result = new FibonacciNode(*this);

            //Record that we have made a copy of this node
            do_not_copy.insert({this, result});

            //Recursively copy (or look up) child, parent, next, prev and store their adresses in result
            if(child!=nullptr)
                result->child = child->deep_copy(do_not_copy);
            if(parent!=nullptr)
                result->parent = parent->deep_copy(do_not_copy);
            if(next!= nullptr)
                result->next = next->deep_copy(do_not_copy);
            if(prev!= nullptr)
                result->prev = prev->deep_copy(do_not_copy);

            return result;
        }

        ~FibonacciNode() {
            delete child;
            /*
             * We need to set this flag in order to prevent the prev sibling from calling the destructor again,
             * which would cause an infinte loop
            */
            being_destroyed = true;
            if (next!=nullptr && !next->being_destroyed) {
                delete next;
            }
        }
        
        
    private:
        T value;
        double key;
        bool marked;
        unsigned int rank;
        FibonacciNode* child;
        FibonacciNode* parent;
        FibonacciNode* next;
        FibonacciNode* prev;

        //This flag specifies whether the destructor has already been called on this node
        bool being_destroyed = false;
        
        friend class FibonacciHeap;
    };
    

    //In order not to expose the user to pointers, we define an alias
    using handle_type = FibonacciNode*;
    
    
    
    FibonacciHeap(){
        heap_size = 0;
        minimum = nullptr;
    };
    
    FibonacciHeap(const FibonacciHeap& other){
        heap_size = other.heap_size;
        if(other.minimum == nullptr) {
            minimum = nullptr;
        }
        else {
            minimum = other.minimum->deep_copy();
        }
    };


    FibonacciHeap& operator=(FibonacciHeap other){          //We use the already implemented copy constructor to make other
        heap_size = other.heap_size;
        FibonacciNode* temp = minimum;
        minimum = other.minimum;
        other.minimum = temp;
        //Now other has the garbage and will be destroyed
    };
    

    
    unsigned int size() const{
        return heap_size;
    };

    T& get(handle_type handle){
        return handle->value;
    };
    
    const T& get(handle_type handle) const{
        return handle->value;
    };

    void decrease_key(handle_type handle, double new_key){
        if(new_key<handle->key)
            handle->key = new_key;
        else
            throw "Key is being increased";

        double old_minimum = minimum->key;

        //If the handle is in the root list we do not have to make a cut.
        if(handle->parent == nullptr){
            handle->marked = false;

            if(new_key<old_minimum){
                minimum = handle;
            }

            return;
        }


        //We check if the heap invariant is violated. If not we are done
        if(new_key>=(handle->parent->key))
            return;

        //If we reach this part of the code the invariant is violated. We have to make cascading cuts.
        cut_node(handle);


        //Finally check whether we have to update the minimum
        if(old_minimum>new_key)
            minimum = handle;
    };
    
    double min_key() const {
        if (heap_size == 0)
            throw "Heap is empty!";
        return minimum->key;
    };

    T extract_min(){
        if(heap_size==0)
            throw "Heap is empty!";
        
        heap_size-=1;
        T minimum_element = minimum->value;

        FibonacciNode* first_child = minimum->child;
        FibonacciNode* current_child = first_child;
        FibonacciNode* next_child;

        FibonacciNode* old_minimum = minimum;

        if(first_child!=nullptr) {
            do {
                next_child = current_child->next;

                //We seperate the child from its parent
                current_child->parent = nullptr;

                //The child is seperated from its siblings
                current_child->next = current_child;
                current_child->prev = current_child;

                //We merge the child into the root list
                merge(old_minimum, current_child);

                current_child = next_child;
            } while (current_child != first_child);
        }

        //We let minimum point to an arbitrary root in the root list. This root is not necessarily minimal
        if(old_minimum->next != old_minimum)
            minimum = old_minimum->next;
        else
            minimum = nullptr;

        //We cut the minimum from the root list
        old_minimum->next->prev = old_minimum->prev;
        old_minimum->prev->next = old_minimum->next;

        //To make sure only old_minimum is cleaned up, we seperate the Node from all children and siblings
        old_minimum->child = nullptr;
        old_minimum->next = nullptr;
        old_minimum->prev = nullptr;

        delete  old_minimum;

        //We have to tidy up the heap and find the new minimum
        minimum = consolidate();

        //Finally return the element we have extracted
        return minimum_element;
    };


    handle_type push(const T &element, double key){
       ++heap_size;

        //Create a new node
       FibonacciNode* new_node = new FibonacciNode(element, key,  false, 0, nullptr, nullptr, nullptr, nullptr);

        //Link the node to itself
       new_node->next = new_node;
       new_node->prev = new_node;

       //Add the node to the root list, update minimum pointer
       minimum = merge(minimum, new_node);
       return new_node;
    };

    ~FibonacciHeap(){
        //All we have to do is delete minimum. All children and siblings will be deleted recursively
        delete minimum;
    };

private:
    unsigned int heap_size;
    FibonacciNode* minimum;

    /**
     * Given two circular, doubly linked circular lists which have their minimal elements at a and b respectively,
     * merge them into one doubly linked circular list and return the pointer to the minimal element
     * @param a Minimum element of first list
     * @param b MInimum element of second list
     */
    FibonacciNode* merge(FibonacciNode* a, FibonacciNode* b){
        if(a==nullptr)
            return b;
        if(b==nullptr)
            return a;
        
        FibonacciNode* a_next = a->next;
        
        a->next = b->next;
        a->next->prev = a;
        b->next = a_next;
        b->next->prev = b;
        
        if((a->key)<(b->key))
            return a;
        
        return b;
        
    };

    /**
     * Cut node from the heap, insert it into the root list and apply cascading cuts
     * @param node The node which is supposed to be cut
     */
    void cut_node(FibonacciNode* node){
        node->marked = false;

        //We don't need to cut nodes that are in the root list!
        if(node->parent == nullptr)
            return;
        
        FibonacciNode* node_parent = node->parent;

        //We rewire node's neighbours
        node->prev->next = node->next;
        node->next->prev = node->prev;

        //node_parent loses a child
        node_parent->rank -= 1;

        //seperate node from parent
        node->parent = nullptr;

        //If parent points at node we need to change it to a different child
        if(node_parent->child == node && node!=node->next){
            node_parent->child = node->next;
        }

        //In this case parent had only node as its child
        else if(node_parent->child == node){
            assert(node_parent->rank == 0);
            node_parent->child = nullptr;
        }

        //Wire node to itself
        node->next = node;
        node->prev = node;

        //We add node to the root list
        merge(minimum, node);

        //If nodes former parent has already lost a child in the past, make a cascading cut
        if(node_parent->marked)
            cut_node(node_parent);

        //Else, mark nodes former parent. Note that we don't mark nodes that are in the root list!
        else if(node_parent->parent != nullptr)
        {
            node_parent->marked = true;
        }
    };
    

    /**
     * Tidy up the heap
     * @return The new minimum
     */
    FibonacciNode* consolidate(){
        if(minimum == nullptr)
            return nullptr;

        std::vector<FibonacciNode*> rank_nodes;
        FibonacciNode* a;
        FibonacciNode* b;
        FibonacciNode* current_node = minimum;
        FibonacciNode* new_minimum = minimum;

        //We create a list of all roots
        std::list<FibonacciNode*> to_visit;
        
        do{
            to_visit.push_back(current_node);
            current_node = current_node->next;
        }while(current_node!=minimum);
        
        
        for(FibonacciNode* current_node: to_visit){
            
            while(true){
                while((current_node->rank)>=rank_nodes.size()){
                    rank_nodes.push_back(nullptr);
                }

                b = rank_nodes[current_node->rank];

                if(b==nullptr){
                    rank_nodes[current_node->rank] = current_node;
                    break;
                }

                //a is supposed to be the node with the smaller key
                if((b->key) < (current_node->key)){
                    a = b;
                    b = current_node;
                }

                else{
                    a = current_node;
                }

                //link b to a
                b->parent = a;
                a->rank += 1;

                //Seperate b from its siblings
                b->prev->next = b->next;
                b->next->prev = b->prev;

                //Link b to itself
                b->prev = b;
                b->next = b;

                //Merge b with as children
                a->child = merge(b, a->child);

                //Now we look at the resulting tree
                current_node = a;

                //There are no more trees with this rank -> free the spot in the array
                rank_nodes[a->rank-1] = nullptr;
            }

            if((current_node->key) <= (new_minimum->key)){
                new_minimum = current_node;
            }
        }
        return new_minimum;
    };
};


#endif //KRUSKAL_MST_FIBONACCIHEAP_H
