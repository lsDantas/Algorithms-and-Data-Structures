#include <stdio.h>
#include <stdlib.h>

typedef struct Node_ {
    struct Node_ *parent;
    int rank;
    int value;
    int quant;

} Node;

Node* find(Node *searchedNode);
void unite(Node *nodeA, Node *nodeB);
Node* createSet(int value);

Node* createSet(int value) {
    Node *node;
    node = (Node *) malloc(sizeof(Node));
    node->parent = node;
    node->value = value;
    node->rank = 0;
    node->quant = 1;

    return node;
}

void unite(Node *nodeA, Node *nodeB) {
    Node *parentA = find(nodeA);
    Node *parentB = find(nodeB);

    // If parents are the same, nodes are in the same set
    if(parentA->value == parentB->value) {
        return;
    }

    // If parents are different, check for greatest rank
    if(parentA->rank >= parentB->rank) {
        parentB->parent = parentA;
        parentA->quant = parentA->quant + parentB->quant;

        // Increase Parent Rank if Ranks are Equal
        if(parentA->rank ==parentB->rank) {
            parentA->rank++;
        }

    } else {
        parentA->parent = parentB;
        parentB->quant = parentB->quant + parentA->quant;
    }
}

Node* find(Node *searchedNode) {
    Node *originalNode = searchedNode;

    // Follow Parent till Root
    while(searchedNode->parent != searchedNode) {
        searchedNode = searchedNode->parent;
    }

    // Optimize Future Searches (path compression) 
    originalNode->parent = searchedNode;

    return searchedNode;
}

int main() {
    Node **setPeople;
    int numPeople, numRelations, numTests;
    int personA, personB;
    int i, j;
    int quantTemp = 1;
    int quantTemp2 = 1;
    int greatest;

    // Read number of tests
    scanf("%d", &numTests);

    for(i = 0; i < numTests; i++){
        // Restart Counter
        greatest = 1;

        // Read Number of People and Relations
        scanf("%d %d", &numPeople, &numRelations);

        // Initialize Set
        setPeople = (Node **) malloc(numPeople * sizeof(Node*));
        for(j=0; j < numPeople; j++) {
            setPeople[j] = createSet(j);
        }

        // Read each Relation
        for(j=0; j < numRelations; j++) {
            scanf("%d %d", &personA, &personB);
            unite(setPeople[personA - 1], setPeople[personB - 1]);

            quantTemp = find(setPeople[personA - 1])->quant;
            quantTemp2 = find(setPeople[personB - 1])->quant;
            if(quantTemp > greatest) {
                greatest = quantTemp;
            }
            if(quantTemp2 > greatest) {
                greatest = quantTemp2;
            }
        }

        printf("%d\n", greatest);
    }


    return 0;
}