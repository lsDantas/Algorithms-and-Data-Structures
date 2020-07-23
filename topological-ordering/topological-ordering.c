#include <stdio.h>
#include <stdlib.h>

// Data Structures
typedef struct {
    int top;
    int *content;
} Stack;

typedef struct {
    Stack predecessors;
    Stack successors;
    int nPredecessors;
} TaskNode;

// Functions
void initStack(Stack *stackInit);
void push(Stack *modifiedStack, int value);

// Main Program
int main(void) {
    // Tasks
    int numTasks = 1;
    int numRelations = 1;
    TaskNode *tasks;

    // Counters and Buffers
    int i, j;
    int first, second;
    int originPos;
    int destinyPos;

    // Graph-Building in Layers
    Stack nextTasks;
    int numInserted = 0;
    int *used;

    // Result
    Stack resultingGraph;

    // Cycle through Inputs
    while(numTasks != 0 && numRelations != 0) {
        // Read Number of Tasks and Relations
        scanf("%d %d", &numTasks, &numRelations);

        // Allocate Memory for Tasks
        tasks = (TaskNode *) malloc(numTasks * sizeof(TaskNode));

        // Initialize Successor and Predecessor Stacks
        for(i=0; i < numTasks; i++) {
            initStack(&(tasks[i].predecessors));
            initStack(&(tasks[i].successors));
            tasks[i].nPredecessors=0;
        }

        // Allocate Memory for next Tasks and Resulting Graph
        initStack(&resultingGraph);
        used = (int *) calloc(numTasks, sizeof(int));

        // Read Tasks
        for(i = 0; i < numRelations; i++) {
            scanf("%d %d", &first, &second);

            // Define Successors and Predecessors
            push(&(tasks[first - 1].successors), second - 1);
            push(&(tasks[second - 1].predecessors), first - 1);
            tasks[second - 1].nPredecessors++;
        }

        // Determine Initial Tasks
        initStack(&nextTasks);
        for(i = 0; i < numTasks; i++) {
            if(tasks[i].nPredecessors == 0) {
                push(&nextTasks, i);
                push(&resultingGraph, i);
                used[i] = 1;
                numInserted++;
            }
        }

        // Analyse Successor Tasks of Included Tasks
        for (i = 0; i < nextTasks.top; i++) {
            originPos = nextTasks.content[i];

            // Lower Predecessor Count
            for (j = 0; j < tasks[originPos].successors.top; j++) {
                destinyPos = tasks[originPos].successors.content[j];
                tasks[destinyPos].nPredecessors--;
            }
        }

        // While there are Tasks in Graph
        while(numInserted < numTasks) {

            // Determine next Task
            initStack(&nextTasks);
            for(i = 0; i < numTasks; i++) {
                if(used[i] != 1 && tasks[i].nPredecessors == 0) {
                    push(&nextTasks, i);
                    push(&resultingGraph, i);
                    used[i] = 1;
                    numInserted++;
                }
            }

            // Analyse Successor Tasks of Included Tasks
            for (i = 0; i < nextTasks.top; i++) {
                originPos = nextTasks.content[i];

                // Lower Predecessor Count
                for (j = 0; j < tasks[originPos].successors.top; j++) {
                    destinyPos = tasks[originPos].successors.content[j];
                    tasks[destinyPos].nPredecessors--;
                }
            }
        }

        // Print Final List
        for(i=0; i < numTasks; i++) {
            printf("%d ", resultingGraph.content[i] + 1);
        }
    }

    return 0;
}

// Functions for Stack Operations
void initStack(Stack *stackInit) {
    stackInit->top = 0;
    stackInit->content = (int *) malloc(sizeof(int));
}

void push(Stack *modifiedStack, int value) {
    modifiedStack->content[modifiedStack->top] = value;
    modifiedStack->content = (int *) realloc(modifiedStack->content, modifiedStack->top + 1);
    modifiedStack->top++;
}