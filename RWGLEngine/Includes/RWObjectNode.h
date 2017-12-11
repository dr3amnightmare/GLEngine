#ifndef RWOBJECTNODE_H
#define RWOBJECTNODE_H

typedef struct RWObjectNode RWObjectNode;

struct RWObjectNode {
    RWObjectNode *next;
    RWObjectNode *previous;
    void *object;
};

#endif //RWOBJECTNODE_H
