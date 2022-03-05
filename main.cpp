// Name: Amer Yono
// Student ID: 200711334
// Email: yono004@cougars.csusm.edu

#include <iostream>
using std::cout, std::endl;

// Node Structure
struct Node {
    int num;
    Node* next;
};

// Function that adds nodes to a linked list.
void addToLinkedList(Node** linkedList, int numberToAdd) {
    // Initialize and add new node
    Node* newItem = new Node();

    // Add values to the node
    newItem->num = numberToAdd;
    newItem->next = *linkedList;

    // Add the node the linked list
    *linkedList = newItem;
}

Node* unionLL(Node* LA, Node* LB) {
    // Initialize unionizedLL
    Node* unionizedLL = NULL;
    
    // Add both linked lists to unionizedLL
    while (LA) {
        addToLinkedList(&unionizedLL, LA->num);
        LA = LA->next;
    }

    while (LB) {
        addToLinkedList(&unionizedLL, LB->num);
        LB = LB->next;
    }

    // Set pointer equal to unionizedLL
    Node* unionizedPointer = unionizedLL;

    // Create pointers for looping through unionizedPointer and removing duplicates
    Node* insidePointer = NULL;
    Node* duplicateNumber = NULL;
    
    // Go through the linked list by 1. The insidePointer will loop through every node during this.
    while (unionizedPointer->next) {
        insidePointer = unionizedPointer;

        // Go through every unionizedPointer->num to check for duplicates
        while (insidePointer->next) {
            if (unionizedPointer->num == insidePointer->next->num) {
                duplicateNumber = insidePointer->next;
                insidePointer->next = insidePointer->next->next;
                delete(duplicateNumber);
            } else insidePointer = insidePointer->next;
        }
        unionizedPointer = unionizedPointer->next;
    }

    return unionizedLL;
}

Node* sortLinkedList(Node* LL){
    // Prevent recursion bugs
	if (!LL) return LL;

    // Set pointer equal to the linked list
	Node* mergedPointer = LL;

    // Set pointer equal to the next value in the linked list
	Node* nextValuePointer = mergedPointer->next;

    // Create pointers for the lower and higher numbers
    Node* lowerNumber = NULL;
	Node* higherNumber = NULL;

    // Go through the linked list by 1. The insidePointer will loop through every node during this.
	while (nextValuePointer) {
	    Node* insidePointer = nextValuePointer->next;

        // Go through every nextValuePointer->num to compare values
		if (nextValuePointer->num < mergedPointer->num){
            nextValuePointer->next = lowerNumber;
            lowerNumber = nextValuePointer;
		} else {
            nextValuePointer->next = higherNumber;
            higherNumber = nextValuePointer;
		}
		nextValuePointer = insidePointer;
	}

    // Sort the lower and higher numbers
	lowerNumber = sortLinkedList(lowerNumber);
	higherNumber = sortLinkedList(higherNumber);

    // Go through all lower and higher numbers
	if (lowerNumber) {
	    Node* less_end = lowerNumber;
	    while (less_end->next) less_end = less_end->next;

        less_end->next = mergedPointer;
        mergedPointer->next = higherNumber;

        return lowerNumber;
	} else mergedPointer->next = higherNumber;
	
    return mergedPointer;
}

Node* mergeLL(Node* LA, Node* LB) {
    // Initialize unionizedLL
    Node* mergedLL = NULL;
    
    // Add both linked lists to unionizedLL
    while (LA) {
        addToLinkedList(&mergedLL, LA->num);
        LA = LA->next;
    }

    while (LB) {
        addToLinkedList(&mergedLL, LB->num);
        LB = LB->next;
    }

    // Sort mergedLL
    mergedLL = sortLinkedList(mergedLL);

    return mergedLL;
}

// Function that outputs all nodes in a linked list.
void outputLinkedList(Node* node) {
    // Check if a node exists
    while (node) {
        // If the next node does not exist, output two new lines instead of a comma
        if (!node->next) cout << node->num << endl << endl;
        else cout << node->num << ", ";
    
        // Set node equal to the next node
        node = node->next;
    }
}

int main() {
    // Initialize linkedLists
    Node* linkedListA = NULL;
    Node* linkedListB = NULL;
    Node* linkedListUnion = NULL;
    Node* linkedListMerge = NULL;

    // Add elements to linkedListA
    addToLinkedList(&linkedListA, 10);
    addToLinkedList(&linkedListA, 16);
    addToLinkedList(&linkedListA, 18);
    addToLinkedList(&linkedListA, 21);
    addToLinkedList(&linkedListA, 26);
    
    // Add elements to linkedListB
    addToLinkedList(&linkedListB, 10);
    addToLinkedList(&linkedListB, 13);
    addToLinkedList(&linkedListB, 16);
    addToLinkedList(&linkedListB, 17);
    addToLinkedList(&linkedListB, 20);
    addToLinkedList(&linkedListB, 23);

    // Output all nodes in linkedListA
    cout << "Linked List A:\n";
    outputLinkedList(linkedListA);

    // Output all nodes in linkedListB
    cout << "Linked List B:\n";
    outputLinkedList(linkedListB);

    // Unionize linkedLists
    linkedListUnion = unionLL(linkedListA, linkedListB);

    // Output all nodes in linkedListUnion
    cout << "Linked List Union:\n";
    outputLinkedList(linkedListUnion);

    // Merge linkedLists
    linkedListMerge = mergeLL(linkedListA, linkedListB);

    // Output all nodes in linkedListMerge
    cout << "Linked List Merge:\n";
    outputLinkedList(linkedListMerge);

    // Free memory
    delete(linkedListA);
    delete(linkedListB);
    delete(linkedListUnion);
    delete(linkedListMerge);

    return 0;
}