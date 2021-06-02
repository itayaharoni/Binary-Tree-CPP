#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace std;
#include "BinaryTree.hpp"
using namespace ariel;
const int max_rand = 1000;
const int div_factor = 100;

double NextDouble() {
    return (double)((unsigned int)rand() % max_rand) / div_factor;
}

int NextInt() {
    return (rand() % max_rand);
}

bool RandomBool() {
    return rand() % 2 == 0;
}

enum class _order {
    inorder,
    postorder,
    preorder,
};

template <typename T>
BinaryTree<T> create_dummy(int adder = 0) {
    BinaryTree<T> tree;

    // create the following tree
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23
    tree.add_root(1 + adder);
    tree.add_left(1 + adder, 2 + adder);
    tree.add_right(1 + adder, 3 + adder);
    tree.add_left(2 + adder, 4 + adder);
    tree.add_right(2 + adder, 5 + adder);
    tree.add_left(5 + adder, 10 + adder);
    tree.add_right(5 + adder, 11 + adder);
    tree.add_left(10 + adder, 20 + adder);
    tree.add_right(11 + adder, 23 + adder);

    return tree;
}

// define a string class
// we define it in order to have an easy + int or + double operator.
// iam just lazy.
class myString {
public:
    string val;
    myString(int a) {
        val = std::to_string(a);
    }

    myString &operator+(const myString &other) {
        val += other.val;
        return *this;
    }

    myString &operator+(int other) {
        val += to_string(other);
        return *this;
    }

    myString &operator+(double other) {
        val += to_string(other);
        return *this;
    }

    bool operator==(const myString &other) {
        return this->val == other.val;
    }

    // need to define this for maps...
    friend bool operator<(const myString &t, const myString &other) {
        return t.val < other.val;
    }

    friend std::ostream &operator<<(std::ostream &os, const myString &c) {
        return (os << c.val);
    }
};



int main() {
 srand(time(nullptr));
    // create the following tree on i = 0
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23

    auto print = [](myString n) { cout << ", " << n; };
    // for_each(preorder.begin(), preorder.end(), print);

    // Test inorder preorder postorder with match.

    for (int i = 0; i < 1; i++) {
        // create a tree that we can delete at any time!
        BinaryTree<myString> *tree = new BinaryTree<myString>(create_dummy<myString>());
        // inorder : 4, 10, 5, 11, 2, 1, 3
        vector<myString> inorder = {4, 2, 20, 10, 5, 11, 23, 1, 3};
        //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
        vector<myString> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
        //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
        vector<myString> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};

        int randval = NextInt();

        auto f = [](myString val, int add) {
            return val + add;
        };

        // here we are creating a transformation function in order to update the tree and the vector.
        auto f2 = bind(f, placeholders::_1, randval);
        transform(inorder.begin(), inorder.end(), inorder.begin(), f2);
        transform(preorder.begin(), preorder.end(), preorder.begin(), f2);
        transform(postorder.begin(), postorder.end(), postorder.begin(), f2);
        transform(tree->begin(), tree->end(), tree->begin(), f2);
        BinaryTree<myString> tree3 = *tree;
        BinaryTree<myString> tree4;
        tree4 = *tree;
        auto begin=tree4.begin();
        auto end=tree4.end();
        if (begin ==end)
        {
           cout << "wtfffffffffff" << endl;
        }
        
        for (auto i = tree4.begin(); i !=tree4.end(); i++)
        {
           cout << "what " <<endl;
        }  
        delete tree;
  
    }
    return 0;
}