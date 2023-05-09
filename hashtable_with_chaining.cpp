#include <iostream>

using namespace std;

struct Node {
    string key; // Changed from "user_name" to "key" for consistency with hash table
    string value; // Changed from "password" to "value" for flexibility
    Node* link = nullptr;
};

struct LinkedList {
    Node* head = nullptr;
    Node* tail = nullptr;
    int length = 0;

    void insert(string key, string value) {
        Node* temp = new Node;
        temp->key = key;
        temp->value = value;
        temp->link = nullptr;

        if (head == nullptr) {
            head = temp;
            tail = temp;
        } else {
            tail->link = temp;
            tail = temp;
        }

        length++;
    }

    Node* search(string key) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->key == key) {
                return temp;
            }
            temp = temp->link;
        }
        return nullptr;
    }

    void print_list() {
        if (head == nullptr) {
            cout << "[]\n";
        } else {
            Node* temp = head;
            cout << "[";
            while (temp != nullptr) {
                cout << temp->key << ":" << temp->value;
                temp = temp->link;
                if (temp != nullptr) {
                    cout << ", ";
                }
            }
            cout << "]\n";
        }
    }
};

struct HashTable {
    int MAX_LENGTH = 4;
    int MAX_CHAIN_LENGTH = 2;
    LinkedList* password = new LinkedList[MAX_LENGTH];

    bool isFull() {
        for (int i = 0; i < MAX_LENGTH; i++) {
            if (password[i].length < MAX_CHAIN_LENGTH) {
                return false;
            }
        }
        return true;
    }

    int hashfunc(string key) {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % MAX_LENGTH;
    }

    bool is_slot_empty(int hash) {
        return (password[hash].head == nullptr);
    }

    void insert(string key, string value) {
        int hash = hashfunc(key);
        if (password[hash].length < MAX_CHAIN_LENGTH) {
            password[hash].insert(key, value);
        } else {
            cout << "Linked List reached MAX CAP!\n";
        }
    }

    void print_hashtable() {
        for (int i = 0; i < MAX_LENGTH; i++) {
            cout << "[" << i << "]: ";
            password[i].print_list();
        }
    }

    void hash_lookup(string key) {
        int hash = hashfunc(key);
        Node* node = password[hash].search(key);
        if (node != nullptr) {
            cout << "Value for " << key << " is " << node->value << endl;
        } else {
            cout << "Key not found in hash table\n";
        }
    }
};
int main(){
    HashTable * hashtbl = new HashTable;
    cout<< hashtbl->isFull()<<"\n";
    int command=0;
    string user_name;
    string password;
    while (command!=-1){
        /* code */
        cout << "Type command: ";
        cin >> command;
        switch (command){
        case 1:
            /* insert the new item*/
            cout << "Enter user name: ";
            cin >> user_name;
            cout << "Enter password to be saved: ";
            cin >> password;
            hashtbl->insert(user_name,password);
            break;
        case 2:
            /* hash lookup password*/
            cout << "Enter user name to look up password:";
            cin >> user_name;
            hashtbl->hash_lookup(user_name);
            break;
        case 3:
            hashtbl->print_hashtable();
            break;
        case -1:
            /* hash lookup password*/
            hashtbl->print_hashtable();
            cout << "Exiting...\n";
            break;
        
        }
    
    }
    return 0;
}
