#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache: public Cache
{
    public:
    LRUCache(int c) { cp = c; }
    
    void set(int key,int val)
    {
        if(mp.empty()) {
            Node *temp = new Node(key,val);
            head = tail = temp;
            mp[key] = temp;
            return;
        }

        // found
        if(mp.find(key) != mp.end()) {
            mp[key]->value = val;

            // if it's head 
            if(mp[key] == head) {
                return;
            }

            mp[key]->prev->next = mp[key]->next;

            if(tail == mp[key]) {
                tail = tail->prev;
            }
            else {
                mp[key]->next->prev = mp[key]->prev;
            }

            mp[key]->next = head;
            mp[key]->prev = NULL;
            head->prev = mp[key];
            head = mp[key];
        }

        else {
            Node *temp = new Node(NULL, head, key,val);
            head->prev = temp;
            head = temp;
            mp[key] = temp;

            if(mp.size() > cp) {
                tail = tail->prev;
                mp.erase(tail->next->key);
                delete tail->next;
                tail->next = NULL;

            }
        }
    }
    
    int get(int key)
    {
        if(mp.find(key) != mp.end()) {
            return mp[key]->value;
        }
        
        return -1;
    }
    
};


int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
