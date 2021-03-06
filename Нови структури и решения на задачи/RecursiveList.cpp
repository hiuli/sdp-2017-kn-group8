#pragma once
#include<iostream>
using std::cout;

struct Node {
	int data;
	Node* next;
	Node(int _data) : data(_data), next(nullptr) {}
};

class List {
	Node* start;

public:
    class Iterator {
        Node* crr;
    public:
        Iterator(Node* node) {
            crr = node;
        }
        bool operator != (const Iterator& other) {
            return crr != other.crr;
        }
        void operator++ () {
            crr = crr->next;
        }
        int operator* () {
            return crr->data;
        }
    };

    Iterator begin() {
        return Iterator(start);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

	List() : start(nullptr) {}

	~List() {
		del(start);
	}

	void print() const {
		print(start);
	}

	void push_back(int x) {
		if (start == nullptr) {
			start = new Node(x);
			return;
		}
		push_back(x, start);
	}
	
	void pop_back() {
		if (start == nullptr) {
			return;
		}
		if (start->next == nullptr) {
			delete[] start;
			start = nullptr;
			return;
		}
		pop_back(start);
	}

private:
	void print(const Node* top) const {
		if (top == nullptr) {
			return;
		}
		cout << top->data << " ";
		print(top->next);
	}

	void push_back(int x, Node*& top) {
		if (top->next == nullptr) {
			top->next = new Node(x);
			return;
		}
		push_back(x, top->next);
	}
	
	void pop_back(Node*& top) {
		if (top->next->next == nullptr) {
			delete[] top->next;
			top->next = nullptr;
			return;
		}
		pop_back(top->next);
	}
	
	void del(Node*& top) {
		if (top == nullptr) {
			return;
		}
		cout << "Deleting " << top->data << '\n';    // For test purposes - do NOT leave
		                                             // such lines in official solutions
		Node* temp = top->next;
		delete[] top;
		del(temp);
	}
};

// VERY important - they may not be the best tests, but there have to be tests
void test_the_list() {
	List lis;
	lis.push_back(2);
	lis.push_back(4);
	lis.push_back(6);
	lis.push_back(8);

	lis.pop_back();
	lis.print();
	cout << '\n';		// Expected output: 2 4 6

	lis.pop_back();
	lis.pop_back();
	lis.print();
	cout << '\n';		// Expected output: 2

	lis.pop_back();
	lis.print();
	cout << '\n';		// Expected output: (only the new line)

	lis.push_back(3);
	lis.push_back(5);
	lis.push_back(7);
	
	// Expected output at the end:
	// Deleting 3
	// Deleting 5
	// Deleting 7
}