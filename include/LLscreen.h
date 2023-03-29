#ifndef LLSCREEN_H
#define LLSCREEN_H

struct Node {
    int data;
    Node *pNext;
};
class SLL {
private:
    Node *pHead;
    int numberOfNode;
public:
    SLL ();
    void build(int inputNumberOfNode);
    void insertAtBeginning(int newData);
    void insertAtEnding(int newData);
    void insertAfterIndex(int newData, int idx);
    void deleteAtBeginning();
    void deleteAtEnding();
    void deleteAtIndex(int idx);
    void updateAtIndex(int newData, int idx);
    int searchElement(int searchData);
    void printList();
};



#endif