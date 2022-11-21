#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <climits> // it's probably not necessary but I'm paranoid

using namespace std;

RedBlackTree::RedBlackTree() {
	// root doesn't need to be initialized, since it gets replaced by the first value inserted into the tree.
	// empty is a null node used to mark empty space in the tree's paths
    empty->left = nullptr;
    empty->right = nullptr;
    empty->color = COLOR_BLACK_BLACK;
    empty->val = 0;
}
RedBlackTree::RedBlackTree(RedBlackTree &other) {
	other.root = root;
}

RedBlackTree::~RedBlackTree() {
	delete(root);
}

bool Search(RBTNode* where, int a) {
	if (where->val == a) {
		return true;
	}
	if (a < where->val) {
		if (where->left != nullptr) {
			return Search(where->left, a);
		}
		else {
			return false;
		}
	}
	else {
		if (where->right != nullptr) {
			return Search(where->right, a);
		}
		else {
			return false;
		}
	}
}

int RedBlackTree::SearchMin(RBTNode* where) {
	while (where->left != empty) {
		where = where->left;
	}
	return where->val;
}

int RedBlackTree::SearchMax(RBTNode* where) {
    while (where->right != empty) {
		where = where->right;
	}
	return where->val;
}

string GetColor(RBTNode* rbt) {
if (rbt->color == COLOR_BLACK) {
    return "B";
}
else if (rbt->color == COLOR_RED) {
    return "R";
}
else if (rbt->color == COLOR_BLACK_BLACK) {
    return "BB";
}
return "";
}

RBTNode* RedBlackTree::zenith(RBTNode* where, int a) {
    RBTNode* destination = nullptr;
	while (where != empty) { // Scan down the tree until you find a null node
			destination = where;
			if (a < where->val) {
				where = where->left;
			} else {
				where = where->right;
			}
		}
	return destination;
}

bool RedBlackTree::Contains(int a) {
    return Search(root, a);
}

int RedBlackTree::GetMin() {
    return SearchMin(root);
}

int RedBlackTree::GetMax() {
    return SearchMax(root);
}

void RedBlackTree::L_Rotate(RBTNode* rbt) {
    //cout << "rotate left!" << endl;
    RBTNode* pivot = rbt->right;
		rbt->right = pivot->left;
		if (pivot->left != empty) {
			pivot->left->prev = rbt;
		}
		pivot->prev = rbt->prev;
		if (rbt->prev == nullptr) {
			this->root = pivot;
		} else if (rbt == rbt->prev->left) {
			rbt->prev->left = pivot;
		} else {
			rbt->prev->right = pivot;
		}
		pivot->left = rbt;
		rbt->prev = pivot;
}

void RedBlackTree::R_Rotate(RBTNode* rbt) {
    //cout << "rotate right!" << endl;
    RBTNode* pivot = rbt->left;
		rbt->left = pivot->right;
		if (pivot->right != empty) {
			pivot->right->prev = rbt;
		}
		pivot->prev = rbt->prev;
		if (rbt->prev == nullptr) {
			this->root = pivot;
		} else if (rbt == rbt->prev->right) {
			rbt->prev->right = pivot;
		} else {
			rbt->prev->left = pivot;
		}
		pivot->right = rbt;
		rbt->prev = pivot;
}

void RedBlackTree::validate(RBTNode* rbt) {
        //cout << "fixing tree!" << endl;
		RBTNode* uncle;
		while (rbt->prev->color == COLOR_RED) {
			if (rbt->prev == rbt->prev->prev->right) {
				// If the previous offenders are skewed to the right
				uncle = rbt->prev->prev->left; // uncle
				if (uncle->color == COLOR_RED) {
					// If the uncle is red
					uncle->color = COLOR_BLACK;
					rbt->prev->color = COLOR_BLACK;
					rbt->prev->prev->color = COLOR_RED;
					rbt = rbt->prev->prev;
				} else {
					if (rbt == rbt->prev->left) {
						// If the current offenders are skewed to the right
						rbt = rbt->prev;
						R_Rotate(rbt);
					}
					// If the current offenders are skewed to the left
					rbt->prev->color = COLOR_BLACK;
					rbt->prev->prev->color = COLOR_RED;
					L_Rotate(rbt->prev->prev);
				}
			} else {
				// If the previous offenders are skewed to the left
				// (everything is the same, but left is swapped with right and vice versa)
				uncle = rbt->prev->prev->right; // uncle

				if (uncle->color == COLOR_RED) {
					// ...
					uncle->color = COLOR_BLACK;
					rbt->prev->color = COLOR_BLACK;
					rbt->prev->prev->color = COLOR_RED;
					rbt = rbt->prev->prev;	
				} else {
					if (rbt == rbt->prev->right) {
						// ...
						rbt = rbt->prev;
						L_Rotate(rbt);
					}
					// ...
					rbt->prev->color = COLOR_BLACK;
					rbt->prev->prev->color = COLOR_RED;
					R_Rotate(rbt->prev->prev);
				}
			}
			if (rbt == root) {
				break;
			}
		}
		root->color = COLOR_BLACK;
		// Root should ALWAYS be black
}

void RedBlackTree::Insert(int a) {

	RBTNode* insertMe = new RBTNode; // turning 'a' into a leaf; it's red, has empty children, and stores 'a' as a value
	// Side note: I probably could've used nullptr instead of an empty double black node, but based on the links
	// and other sources that I found, double black nodes are instrumental to making remove work, so I think it's best to add them now.
	insertMe->prev = nullptr; insertMe->val = a; insertMe->left = empty; insertMe->right = empty; insertMe->color = COLOR_RED;

	if (root == nullptr) {
		// If root isn't defined, that new node becomes black and replaces root.
		root = insertMe;
		root->color = COLOR_BLACK;
		return;
	}

	// Otherwise, run a function to find the last node that would appear before the inserted node.
	// Ex: if the tree has 10, 20, 30, 40, 50 with root 20, inserting 35 would trace through 20->40->30 and place a new node to its right.
	RBTNode* destination = zenith(root, a);

	insertMe->prev = destination;
	if (insertMe->val < destination->val) {
		destination->left = insertMe;
	}
	else {
		destination->right = insertMe;
	}
    validate(insertMe);
}

const string RedBlackTree::ToInfixString(RBTNode* rbt) const {
    string output = "";
    if (rbt == nullptr) {
        return output;
    }
    string curr = GetColor(rbt) + to_string(rbt->val);
	// Go left, then print, then go right
    if (rbt->left != empty) {
        output += ToInfixString(rbt->left);
    }
	output += (" " + curr + " ");
    if (rbt->right != empty) {
        output += ToInfixString(rbt->right);
    }
    return output;
};
const string RedBlackTree::ToPrefixString(RBTNode* rbt) const {
    string output = "";
    if (rbt == nullptr) {
        return output;
    }
    string curr = GetColor(rbt) + to_string(rbt->val);
	// Print, then go left, then go right
    output += (" " + curr + " ");
    if (rbt->left != empty) {
        output += ToPrefixString(rbt->left);
    }
    if (rbt->right != empty) {
        output += ToPrefixString(rbt->right);
    }
    return output;
};
const string RedBlackTree::ToPostfixString(RBTNode* rbt) const {
    string output = "";
    if (rbt == nullptr) {
        return output;
    }
    string curr = GetColor(rbt) + to_string(rbt->val);
	// go left, then go right, then print
    if (rbt->left != empty) {
        output += ToPostfixString(rbt->left);
    }
    if (rbt->right != empty) {
        output += ToPostfixString(rbt->right);
    }
	output += (" " + curr + " ");
    return output;
};