//
//  RWObjectNode.h
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-06-11.
//  Copyright © 2017 RWG. All rights reserved.
//

#ifndef RWOBJECTNODE_H
#define RWOBJECTNODE_H

typedef struct RWObjectNode RWObjectNode;

struct RWObjectNode {
    RWObjectNode *next;
    RWObjectNode *previous;
    void *object;
};

#endif //RWOBJECTNODE_H
