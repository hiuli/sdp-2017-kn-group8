#pragma once
#include<iostream>
#include<stack>
#include<vector>
#include"util.h"
using std::cout;
using std::stack;
using std::vector;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int _data)
        : data(_data), left(nullptr), right(nullptr) {}

    bool childless() const {
        return left == nullptr && right == nullptr;
    }
};

class BinTree {
    Node* root;

public:
    BinTree() : root(nullptr) {}

    ~BinTree() {
        del(root);
    }

    void add(int x, char* path) {
        add(x, root, path);
    }

    unsigned count_elements() const {
        return count_elements(root);
    }

    unsigned height() const {
        return height(root);
    }

    unsigned leaves() const {
        return leaves(root);
    }

    // The old trivial "print" - with a better name
    void print_in_row() const {
        print_in_row(root);
    }

    void print_hierarchy() const {
        print_hierarchy(root, 0);
    }

    void print_with_stack() const {
        stack<Node*> st;
        st.push(root);
        vector<Node*> for_delete;

        while (!st.empty()) {                 // Long functions are hard to trace and understand.
            pop_and_update(st, for_delete);   // And when you have a complex loop body where you want to write
        }                                     // "continue", it's probably time to extract it into separate function
        
        for (vector<Node*>::iterator it = for_delete.begin();  it != for_delete.end();  ++it) {
            delete *it;
        }
    }

private:
    // Helper for print_with_stack
    void pop_and_update(stack<Node*>& st, vector<Node*>& for_delete) const {
        Node* crr = pop(st);
        if (crr == nullptr) {
            return;
        }
        if (crr->childless()) {
            cout << crr->data << " ";
            return;
        }
        st.push(crr->right);
        st.push(crr->left);
        st.push(new Node(crr->data));
        for_delete.push_back(st.top());
    }

    void add(int x, Node*& sub_root, char* path) {
        if (sub_root == nullptr) {
            sub_root = new Node(x);
            return;
        }
        if (path[0] == 'L') {
            add(x, sub_root->left, path + 1);
            return;
        }
        // Now path[0] is 'R'
        add(x, sub_root->right, path + 1);
        return;
    }
    
    unsigned count_elements(Node* sub_root) const {
        if (sub_root == nullptr) {
            return 0;
        }
        return 1
            + count_elements(sub_root->left)
            + count_elements(sub_root->right);
    }

    void del(Node*& sub_root) {
        if (sub_root == nullptr) {
            return;
        }
        del(sub_root->left);
        del(sub_root->right);
        delete sub_root;
    }
   
    unsigned height(Node* sub_root) const {
        if (sub_root == nullptr) {
            return 0;
        }
        unsigned left = height(sub_root->left);
        unsigned right = height(sub_root->right);
        return 1 + (left > right ? left : right);
    }

    unsigned leaves(Node* sub_root) const {
        if (sub_root == nullptr) {
            return 0;
        }
        if (sub_root->left == nullptr && sub_root->right == nullptr) {
            return 1;
        }
        return leaves(sub_root->left) + leaves(sub_root->right);
    }

    // The old trivial "print" - with a better name
    void print_in_row(Node* sub_root) const {
        if (sub_root == nullptr) {
            return;
        }
        cout << sub_root->data << " ";
        print_in_row(sub_root->left);
        print_in_row(sub_root->right);
    }
    
    void print_hierarchy(Node* sub_root, unsigned spaces) const {
        if (sub_root == nullptr) {
            return;
        }
        print_spaces(spaces);
        cout << sub_root->data << '\n';
        print_hierarchy(sub_root->left, spaces + 2);
        print_hierarchy(sub_root->right, spaces + 2);
    }
};
