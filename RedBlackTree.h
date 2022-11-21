#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <string>

using namespace std;

#define COLOR_BLACK 0
#define COLOR_RED 1
#define COLOR_BLACK_BLACK 2

struct RBTNode {
int val;
int color;
RBTNode* left = nullptr;
RBTNode* right = nullptr;
RBTNode* prev = nullptr;
};

class RedBlackTree {

    public:
        RedBlackTree();
        RedBlackTree(RedBlackTree &other);
        ~RedBlackTree();
        bool Contains(int a);
        int GetMin();
        int GetMax();
        void Insert(int a);
        unsigned long long int Size() { return numItems; };
        string ToInfixString() const {return ToInfixString(root);};
        string ToPrefixString() const { return ToPrefixString(root);};
        string ToPostfixString() const { return ToPostfixString(root);};

    private:
        unsigned long long int numItems = 0;
        RBTNode *root = nullptr;
        RBTNode* empty = new RBTNode;
        const string ToInfixString(RBTNode* rbt) const;
        const string ToPrefixString(RBTNode* rbt) const;
        const string ToPostfixString(RBTNode* rbt) const;
        void validate(RBTNode* rbt);
        void L_Rotate(RBTNode* rbt);
        void R_Rotate(RBTNode* rbt);
        RBTNode* zenith(RBTNode* where, int a);
        int SearchMin(RBTNode* where);
        int SearchMax(RBTNode* where);
};

#endif