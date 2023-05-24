// Collaborated with: Valerie Wong, Kira Hammond, zyBooks

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
  string payload;
  Node* next;
};

Node* newNode(string payload) {
  Node* node = new Node;
  node->payload = payload;
  node->next = nullptr;
  return node;
}

Node* loadGame(int n, vector<string> names) {
  Node* head = nullptr;
  Node* prev = nullptr;
  string name;

  for (int i = 0; i < n; ++i) {
    name = names.at(i);
    if (head == nullptr) {
      head = newNode(name); // initialize head specially
      prev = head; // only one node, so prev & head point to same node
    } 
    else {
      prev->next = newNode(name);
      prev = prev->next;
    }
  }

  if (prev != nullptr) {
    prev->next = head; // points prev's next ptr to head (make circular)
  } 

  return head;
}

void print(Node* start) { // prints list
  Node* curr = start;
  while (curr != nullptr) {
    cout << curr->payload << endl;
    curr = curr->next;
    if (curr == start) {
      break; // exit circular list
    }
  }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
  Node* curr = start;
  Node* prev = curr;

  while (curr->next != curr) { // exit condition, last person standing
    for (int i = 0; i < k; ++i) { // find kth node
      curr = curr->next;

      // if i != index of the node being removed, update prev ptr
      // finds the prev value to the node we want to remove
      if (i != k - 1) {
        prev = curr;
      }
    }

    prev->next = curr->next; // points prev next ptr to curr next ptr
    delete curr; // delete kth node
    curr = prev->next; // sets the next curr
    prev = curr;
  }

  return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
  int n=1, k=1; // n = num names; k = num skips (minus 1)
  string name;
  vector<string> names;

  // get inputs
  cin >> n >> k;
  while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

  // initialize and run game
  Node* startPerson = loadGame(n, names);
  Node* lastPerson = runGame(startPerson, k);

  if (lastPerson != nullptr) {
    cout << lastPerson->payload << " wins!" << endl;
  } else {
    cout << "error: null game" << endl;
  }

  return 0;
}

