#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#define TYPE int

enum Direction {
    D_LEFT = 0,
    D_RIGHT = 1,
    D_NEITHER = -1
};

enum OperationResult {
    R_BALANCED = 0,
    R_GREW = 1,
    R_ROTATE = 2
};

struct AVLNode {
    TYPE value;
    AVLNode *children[2];
    Direction balance;
};

class AVLTree {
    public:
        AVLTree();
        ~AVLTree();
        void Print();
        void Insert(TYPE value);
        int Remove(TYPE value);
    private:
        OperationResult insertRec(TYPE value, AVLNode *node);
        void printRec(AVLNode *node);
        AVLNode *root;
};

#endif
