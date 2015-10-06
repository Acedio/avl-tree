#include <cstddef>
#include <iostream>

#include "AVLTree.h"

Direction flipDir(Direction dir) {
    if(dir == D_LEFT) return D_RIGHT;
    if(dir == D_RIGHT) return D_LEFT;
    return D_NEITHER;
}

AVLNode *createAVLNode(TYPE value) {
    AVLNode *node = new AVLNode;
    node->value = value;
    node->children[D_LEFT] = NULL;
    node->children[D_RIGHT] = NULL;
    node->balance = D_NEITHER;

    return node;
}

AVLNode *rotateAVLNode(AVLNode *node, Direction dir) {
    Direction antidir = flipDir(dir);

    AVLNode *child = node->children[antidir];

    node->children[antidir] = child->children[dir];
    child->children[dir] = node;

    return child;
}

AVLTree::AVLTree() {
    root = NULL;
}

AVLTree::~AVLTree() {
    // tbi
}

void printValue(AVLNode *node) {
    std::cout << "\"" << node->value;
    switch(node->balance) {
        case D_LEFT: 
            std::cout << " (-)";
            break;
        case D_RIGHT: 
            std::cout << " (+)";
            break;
        default:
            break;
    }
    std::cout << "\"";
}

void AVLTree::printRec(AVLNode *node) {
    if(node != NULL) {
        //std::cout << node->value << " (b:" << node->balance << ") ";

        /*if(node->children[D_LEFT] == NULL && node->children[D_RIGHT] == NULL) {
            printValue(node);
            std::cout << std::endl;
            return;
        }*/

        int child;
        for(child = 0; child < 2; child++){
            std::cout << "\t";
            printValue(node);
            std::cout << " -> ";
            if(node->children[child] != NULL) {
                printValue(node->children[child]);
            } else {
                std::cout << "\"" << node->value << "_" << child << "\"" << std::endl;
                std::cout << "\t\"" << node->value << "_" << child << "\"" << " [shape = point]";
            }
            std::cout << std::endl;
        }
        //std::cout << std::endl;

        for(child = 0; child < 2; child++){
            if(node->children[child] != NULL) {
                printRec(node->children[child]);
            }
        }
    }
}

void AVLTree::Print() {
    std::cout << "digraph G {" << std::endl;
    printRec(root);
    std::cout << "}" << std::endl;
}

OperationResult AVLTree::insertRec(TYPE value, AVLNode *node) {
    Direction dir = value <= node->value? D_LEFT : D_RIGHT;

    if(node->children[dir] == NULL) {
        node->children[dir] = createAVLNode(value);
        
        if(node->balance == D_NEITHER) {
            node->balance = dir;

            return R_GREW; // grew by one
        } else {
            // the other child was populated, so we are now balanced
            node->balance = D_NEITHER;
            
            return R_BALANCED;
        }
    }

    int result = insertRec(value, node->children[dir]);
    // std::cout << "result: " << result << std::endl;

    switch(result) {
        case R_BALANCED:
            return R_BALANCED;
        case R_GREW:
            if(node->balance == dir) {
                // we grew and need to rotate
                return R_ROTATE;
            } else if(node->balance == D_NEITHER) {
                // we are unbalanced in one direction
                node->balance = dir;
                return R_GREW;
            } else {
                // we have re-balanced
                node->balance = D_NEITHER;
                return R_BALANCED;
            }
        case R_ROTATE:
            AVLNode *child = node->children[dir];

            // we're rotating, so the node was added to the heavy side of the child
            AVLNode *grandchild = child->children[child->balance];

            if(child->balance != grandchild->balance) {
                // rotate to the opposite dir before balancing
                child->children[child->balance] = rotateAVLNode(grandchild, child->balance);

                // update the old granchilds balance
                if(grandchild->balance == child->children[child->balance]->balance) {
                    grandchild->balance = flipDir(grandchild->balance);
                } else {
                    grandchild->balance = D_NEITHER;
                }

                // new grandchild->balance should equal child->balance now
                child->children[child->balance]->balance = child->balance;
            }

            Direction antidir = flipDir(child->balance);

            node->children[dir]->balance = D_NEITHER;

            node->children[dir] = rotateAVLNode(child, antidir);

            node->children[dir]->balance = D_NEITHER;

            return R_BALANCED;
    }
}

void AVLTree::Insert(TYPE value) {
    if(root == NULL) {
        root = createAVLNode(value);
        return;
    }

    OperationResult result = insertRec(value, root);
    // std::cout << "result: " << result << std::endl;

    if(result == R_ROTATE) {
        AVLNode *child = root;
        AVLNode *grandchild = child->children[child->balance];

        if(child->balance != grandchild->balance) {
            // rotate to the opposite dir before balancing
            child->children[child->balance] = rotateAVLNode(grandchild, child->balance);

            // update the old granchilds balance
            if(grandchild->balance == child->children[child->balance]->balance) {
                grandchild->balance = flipDir(grandchild->balance);
            } else {
                grandchild->balance = D_NEITHER;
            }

            // new grandchild->balance should equal child->balance now
            child->children[child->balance]->balance = child->balance;
        }

        Direction antidir = flipDir(child->balance);

        root->balance = D_NEITHER;

        root = rotateAVLNode(root, antidir);

        root->balance = D_NEITHER;
    }
}

int AVLTree::Remove(TYPE value) {
    return 0;
}
