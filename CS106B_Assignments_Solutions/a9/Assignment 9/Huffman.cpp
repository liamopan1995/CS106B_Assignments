#include "Huffman.h"
#include "priorityqueue.h"
#include "map.h"
#include "set.h"
using namespace std;


//struct PQueueNode {
//    EncodingTreeNode* anode;
//    double weight;
//};


/**
 * Deallocates all nodes in a Huffman tree. We've provided this helper function
 * to you since we also use it in our test driver and figured you might want
 * to make use of it.
 */
void deleteTree(EncodingTreeNode* tree) {
    /* TODO: Delete this comment and the next few lines, then implement this. */

    if (tree != nullptr) {
        deleteTree(tree->zero);
        deleteTree(tree->one);
        delete tree;
    }
}

/**
 * Constructs a Huffman coding tree for the given string, using the algorithm
 * described in lecture.
 *
 * If the input string does not contain at least two different characters,
 * this function should report an error.
 *
 * When assembling larger trees out of smaller ones, make sure to set the first
 * tree dequeued from the queue to be the zero subtree of the new tree and the
 * second tree as the one subtree.
 */



EncodingTreeNode* huffmanTreeFor(const string& str) {
    /* TODO: Delete this comment and the next few lines, then implement this. */

    // compute character frequency
    Map <char,int> frequencies= {};

    for ( int i= 0.0; i<size(str);i++) {

        frequencies[str[i]]++;

    }
    if(size(frequencies) < 2) error ("priority must have at least two elements!");

    // build a priority queue of type <*PQueueNode, double>
    double factor = 1.0;
    PriorityQueue<PQueueNode*> pqueue;
    for (char elem: frequencies) {
        EncodingTreeNode* cell= new EncodingTreeNode;
        cell->ch = elem;
        cell->one = nullptr;
        cell->zero = nullptr;
        PQueueNode* pNode = new PQueueNode;
        pNode->anode = cell;

        pNode->weight = factor*frequencies[elem];
        pqueue.enqueue(pNode,pNode->weight);
    }
    //

    while ( true/*size(pqueue) !=1 */) {

        PQueueNode* znode = pqueue.dequeue();
        PQueueNode* fnode = pqueue.dequeue();
//        EncodingTreeNode* zchild = znode->anode;//deque 0 child
//        EncodingTreeNode* fchild = fnode->anode;//deque 1 child

        EncodingTreeNode* subtree = new EncodingTreeNode;
        subtree ->ch = ' ';
        subtree -> zero = znode->anode;//deque 0 child//combine
        subtree -> one = fnode->anode;

        //  successing condition check
        if (size(pqueue) == 0 ) return subtree;

        // enque
        PQueueNode* pNode = new PQueueNode;
        pNode->anode = subtree;
        pNode->weight = znode->weight + fnode->weight;
        pqueue.enqueue(pNode,pNode->weight);
//        delete subtree;
//        delete znode;
//        delete fnode;
    }

    return pqueue.dequeue()->anode;





}

/**
 * Given a Queue<Bit> containing a compressed message and a tree that was used
 * to encode those bits, decodes the bits back to the original message.
 *
 * You can assume the input tree is not null and is not a single character;
 * those are edge cases you don't need to handle.
 *
 * You can assume the input Queue<Bit> is well-formed in that every character
 * was encoded correctly, there are no stray bits in the Queue, etc.
 */
string decodeText(Queue<Bit>& bits, EncodingTreeNode* tree) {
    /* TODO: Delete this comment and the next few lines, then implement this. */
    string str = "";

    while(size(bits) != 0){
        EncodingTreeNode* sentinel = tree;
        while(size(bits) != 0){
            Bit nextmove = bits.dequeue();
            if(nextmove == 1) {sentinel = sentinel->one;}
            if(nextmove == 0) {sentinel = sentinel->zero;}

            // check is current node a leaf node
            if(sentinel->one ==nullptr && sentinel->zero==nullptr) {
                str+=sentinel->ch; break;
            }

        }
    }
    return str;
}

/**
 * Given a string and a Huffman encoding tree, encodes that text using the tree
 * and outputs a Queue<Bit> corresponding to the encoded representation.
 *
 * The input tree will not be null and will not consist of a single node; these
 * are edge cases you don't have to handle. The input tree will contain all
 * characters that make up the input string.
 */

/**   helper function to find the char, it returns a pointer type  EncodingTreeNode* which contains the corresponding char we looking for
**/
//   wrtie the helper here

//EncodingTreeNode* findChar (const char& goal,EncodingTreeNode* root){
//    if (root==nullptr) return nullptr;
//    if(root->ch == goal) return root;
//    return findChar(goal,root->zero) ;
//    return findChar(goal,root->one) ;





//}

/**  get code book_rec
 **/
void getCodeBook(char letter, EncodingTreeNode* tree,Map<char,string>& codeBook ,string path){
    while ( tree->one == nullptr&& tree->zero==nullptr) {
        if (letter == tree->ch) codeBook[letter] = path;
        return;
    }
    getCodeBook (letter, tree->zero, codeBook, path+"0");
    getCodeBook (letter, tree->one, codeBook, path+"1");
    return;
}


Queue<Bit> encodeText(const string& str, EncodingTreeNode* tree) {
    /* TODO: Delete this comment and the next few lines, then implement this. */


    Queue<Bit> result = {};

    // make a characters set
    Set<char> letters={};
    for(int i = 0; i < size( str ); i++){  // or simply for(auto s: str)Letters += s;
        letters += str[i];
    }
    // get the CodeBook
    Map<char,string> codeBook={};
    for (char elem : letters){
        getCodeBook(elem, tree,codeBook, "");
    }

    // encoding
    for (int i = 0;i< size(str);i++) {   // or simply writte : for(auto code_i : str)
    string code_i = codeBook[str[i]];
        for (int j = 0;j< size(code_i);j++) { // or simply for(auto code_ij : code_i)
//               if (code_i[j] == '1'){

//                   result.enqueue(1);
//               }
//               else{

//                   result.enqueue(0);
//               }
               result.enqueue(int(code_i[j]) - 48);  // since: int('0') = 48 int('1') = 49
           }

    }

    return result;

}

/**
 * Decodes the given Queue<Bit> and Queue<char> into a Huffman coding tree.
 *
 * You can assume that the input Queues are structured properly in that they
 * represent a legal encoding of a tree, that there aren't stray characters
 * or bits in them, etc.
 */

void decodeTree_Rec(Queue<Bit>& bits, Queue<char>& leaves,EncodingTreeNode*& subtree,EncodingTreeNode*& result) {
    /* TODO: Delete this comment and the next few lines, then implement this. */

    if (bits.dequeue()==1) {
        EncodingTreeNode* treecell_zero = new EncodingTreeNode;// youwu erzi
        treecell_zero -> ch = '*';
        treecell_zero -> zero = nullptr;
        treecell_zero -> one  = nullptr;
        EncodingTreeNode* treecell_one = new EncodingTreeNode;// youwu erzi
        treecell_one -> ch = '*';
        treecell_one -> zero = nullptr;
        treecell_one -> one = nullptr;
        EncodingTreeNode* treecell = new EncodingTreeNode;// youwu erzi
        treecell -> ch = '*';
        treecell -> zero = treecell_zero;
        treecell -> one = treecell_one;
        subtree = treecell;

        if (result ==nullptr) result = subtree;

        delete treecell_zero;
        delete treecell_one;     // delete yige 释放2 object 的内存是为什么？
                                //， 为什么treecell pointer 不用delete，是因为 subtree=treecell， 而subtree在后续又继续被下一层函数调用吧
        decodeTree_Rec(bits,leaves,subtree->zero,result);
        decodeTree_Rec(bits,leaves,subtree->one,result);




    }


    else{

        EncodingTreeNode* treecell = new EncodingTreeNode;// youwu erzi
        treecell -> ch = leaves.dequeue();
        treecell -> zero = nullptr;
        treecell -> one = nullptr;
        subtree = treecell;
    }











}

/** A function wraper of decodeTree_Rec **/
EncodingTreeNode* decodeTree(Queue<Bit>& bits, Queue<char>& leaves) {
    /* TODO: Delete this comment and the next few lines, then implement this. */

    if (size(bits)<2) error(" huffman tree must at least have 2 leaves ");

    EncodingTreeNode* hufftree = nullptr;
    EncodingTreeNode* result = nullptr;
    decodeTree_Rec(bits,leaves,hufftree,result);

    return result;
}



/**
 * Encodes the given Huffman tree as a Queue<Bit> and Queue<char> in the manner
 * specified in the assignment handout.
 *
 * You can assume the input Queues are empty on entry to this function.
 *
 * You can assume that the Huffman tree provided to you is properly structured,
 * in that each internal node will have two children and only the characters in
 * the leaves matter, etc.
 */


void encodeTree(EncodingTreeNode* tree, Queue<Bit>& bits, Queue<char>& leaves) {
    /* TODO: Delete this comment and the next few lines, then implement this. */
    if (tree == nullptr) return;

    if ( tree->zero != nullptr || tree->one != nullptr) {   // use the difference btw leaf and nonleaf nodes
        bits.enqueue(1);
        encodeTree (tree->zero,bits,leaves);
        encodeTree (tree->one,bits,leaves);

    } else {
        bits.enqueue(0);
        leaves.enqueue(tree->ch);// base case
        return;
    }



}

/**
 * Compresses the given text string using Huffman coding, producing as output
 * a HuffmanResult containing the encoded tree and message.
 *
 * Your implementation of this function should report an error if there are
 * fewer than two distinct characters in the input string.
 */
HuffmanResult compress(const string& text) {
    /* TODO: Delete this comment and the next few lines, then implement this. */

    HuffmanResult result ={};
    Set<char> frequencies ;
    for ( int i= 0.0; i<size(text);i++) {

        frequencies.add(text[i]);

    }
    if (size(frequencies) < 2) error ("the input string to compress doesnʼt have at least two distinct characters");

    EncodingTreeNode* huffmantree = huffmanTreeFor(text);
    encodeTree( huffmantree, result.treeBits, result.treeLeaves);
    result.messageBits = encodeText(text,  huffmantree);
    deleteTree(huffmantree);  // always remember to use speicall decomposor , delete will only delete a single cell allocated

//    result.treeBits  = ;// Queue<Bit>
//    result.treeLeaves =;// Queue<char>
//    result.messageBits;// Queue<Bit>
    return result;
}

/**
 * Decompresses the given HuffmanResult and returns the string it represents.
 *
 * Your implementation may change the file parameter however it sees fit. There
 * are no requirements about what it should look like after this function
 * returns.
 *
 * You can assume the input file is well-formed and was created by a correct
 * implementation of compress.
 */
string decompress(HuffmanResult& file) {
    /* TODO: Delete this comment and the next few lines, then implement this. */

    EncodingTreeNode* huffmantree= decodeTree(file.treeBits, file.treeLeaves);
    string result = decodeText(file.messageBits, huffmantree);
    deleteTree(huffmantree);
    return result;
}


/* * * * * * Test Cases Below This Point * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own custom tests here! */













/* * * * * Provided Tests Below This Point * * * * */
#include <limits>

/* Utility function to test if a purported Huffman tree is indeed a Huffman tree.
 * Specifically, this checks that each internal node has either zero or two
 * children. There are other ways you could produce an invalid Huffman tree - for
 * example, by having uninitialized pointers or by linking in a cycle - but we
 * don't test for that here.
 */
bool isEncodingTree(EncodingTreeNode* tree) {
    /* The empty tree is not a Huffman tree. */
    if (tree == nullptr) return false;

    /* If we have one missing child, we should have two missing children. */
    if ((tree->zero == nullptr) != (tree->one == nullptr)) return false;

    /* If we have children at all, they need to be Huffman trees. */
    return tree->zero == nullptr || (isEncodingTree(tree->zero) && isEncodingTree(tree->one));
}

/* Utility function to test if two trees are equal. This is adapted from Section
 * Handout 8 and particularized to Huffman trees.
 */
bool areEqual(EncodingTreeNode* lhs, EncodingTreeNode* rhs) {
    /* Base case: If either is a leaf, both should be. */
    bool lhsLeaf = lhs->zero == nullptr && lhs->one == nullptr;
    bool rhsLeaf = rhs->zero == nullptr && rhs->one == nullptr;
    if (lhsLeaf || rhsLeaf) {
        return lhs->ch == rhs->ch && lhsLeaf == rhsLeaf;
    }

    /* Otherwise, they're both internal nodes. Check that they match. */
    return areEqual(lhs->zero, rhs->zero) && areEqual(lhs->one, rhs->one);
}

/* Utility function to return a string of all possible characters. */
string pangrammaticString() {
    string result;

    char ch = numeric_limits<char>::min();
    result += ch;
    do {
        ch++;
        result += ch;
    } while (ch != numeric_limits<char>::max());

    return result;
}

/* Utility function that makes an inefficient but still valid encoding tree
 * for the given characters.
 */
EncodingTreeNode* strandTreeFor(const string& text, size_t index = 0) {
    if (index == text.size()) error("No characters provided to strandTreeFor.");

    /* We always get a leaf node. */
    EncodingTreeNode* leaf = new EncodingTreeNode {
        text[index], nullptr, nullptr
    };

    /* Last character? If so, that's all. */
    if (index + 1 == text.size()) return leaf;

    /* Otherwise, build a larger tree. */
    else return new EncodingTreeNode {
        ' ', leaf, strandTreeFor(text, index + 1)
    };
}

PROVIDED_TEST("huffmanTreeFor reports errors on invalid inputs.") {
    EXPECT_ERROR(huffmanTreeFor(""));    // No characters
    EXPECT_ERROR(huffmanTreeFor("a"));   // One character
    EXPECT_ERROR(huffmanTreeFor("aaa")); // One character
}

PROVIDED_TEST("huffmanTreeFor builds tree for two characters.") {
    EncodingTreeNode* reference = new EncodingTreeNode {
        ' ', new EncodingTreeNode {'a', nullptr, nullptr}, new EncodingTreeNode {'b', nullptr, nullptr}
    };

    EncodingTreeNode* tree = huffmanTreeFor("aaabbbb");
    EXPECT(isEncodingTree(tree));
    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("huffmanTreeFor works on the full range of characters.") {
    /* Get a string of all possible characters, then pair them off and see what we find. */
    string allChars = pangrammaticString();
    for (size_t i = 0; i < allChars.size(); i += 2) {
        string toEncode;
        toEncode += allChars[i];
        toEncode += allChars[i + 1];
        toEncode += allChars[i + 1];

        EncodingTreeNode* reference = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        EncodingTreeNode* tree = huffmanTreeFor(toEncode);
        EXPECT(isEncodingTree(tree));
        EXPECT(areEqual(tree, reference));

        deleteTree(reference);
        deleteTree(tree);
    }
}

PROVIDED_TEST("huffmanTreeFor uses cumulative weights (v1).") {
    /* This tree:
     *                 *
     *                / \
     *               *   D
     *              / \
     *             C   *
     *                / \
     *               A   B
     */
    EncodingTreeNode* reference = new EncodingTreeNode {
        '*',
            new EncodingTreeNode { '!',
                new EncodingTreeNode { 'C', nullptr, nullptr },
                new EncodingTreeNode { '?',
                    new EncodingTreeNode { 'A', nullptr, nullptr },
                    new EncodingTreeNode { 'B', nullptr, nullptr }
                }
            },
            new EncodingTreeNode { 'D', nullptr, nullptr }
    };

    /* Ax2, Bx3, Cx4, Dx10 */
    EncodingTreeNode* tree = huffmanTreeFor("AABBBCCCCDDDDDDDDDD");
    EXPECT(isEncodingTree(tree));
    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("huffmanTreeFor uses cumulative weights (v2).") {
    /*
     *          *
     *       /     \
     *      *       *
     *     / \     / \
     *    D   E   F   *
     *               / \
     *              C   *
     *                 / \
     *                A   B
     */
    EncodingTreeNode* reference =new EncodingTreeNode {
        ' ',
        new EncodingTreeNode {
            ' ',
            new EncodingTreeNode{ 'D', nullptr, nullptr },
            new EncodingTreeNode{ 'E', nullptr, nullptr }
        },
        new EncodingTreeNode {
            ' ',
            new EncodingTreeNode{ 'F', nullptr, nullptr },
            new EncodingTreeNode {
                ' ',
                new EncodingTreeNode{ 'C', nullptr, nullptr },
                new EncodingTreeNode{
                    ' ',
                    new EncodingTreeNode{ 'A', nullptr, nullptr },
                    new EncodingTreeNode{ 'B', nullptr, nullptr },
                }
            }
        }
    };

    /* Ax2, Bx3, Cx4, Dx6, Ex7, Fx8 */
    EncodingTreeNode* tree = huffmanTreeFor("AABBBCCCCDDDDDDEEEEEEEFFFFFFFF");
    EXPECT(isEncodingTree(tree));

    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("decodeText works on small sample.") {
    /* This tree:
     *                 *
     *                / \
     *               O   *
     *                  / \
     *                 *   N
     *                / \
     *               M   S
     */
    EncodingTreeNode* tree = new EncodingTreeNode {
        '*',
            new EncodingTreeNode { 'O', nullptr, nullptr },
            new EncodingTreeNode { '*',
                new EncodingTreeNode{ '*',
                    new EncodingTreeNode { 'M', nullptr, nullptr },
                    new EncodingTreeNode { 'S', nullptr, nullptr }
                },
                new EncodingTreeNode{ 'N', nullptr, nullptr }
            }
    };

    /* What you get if you encode MONSOON with this tree. */
    Queue<Bit> bits = { 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1 };

    EXPECT_EQUAL(decodeText(bits, tree), "MONSOON");

    deleteTree(tree);
}

PROVIDED_TEST("Can decode all char values.") {
    /* All possible characters. */
    string allChars = pangrammaticString();

    /* Try decoding all pairs of adjacent characters. */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        string expected;
        expected += allChars[i];
        expected += allChars[i + 1];
        expected += allChars[i + 1];

        EncodingTreeNode* tree = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        /* Decode the bitstream 011, which should map back to the expected
         * string.
         */
        Queue<Bit> bits = { 0, 1, 1 };
        EXPECT_EQUAL(decodeText(bits, tree), expected);

        deleteTree(tree);
    }
}

PROVIDED_TEST("encodeText works on small sample.") {
    /* This tree:
     *                 *
     *                / \
     *               O   *
     *                  / \
     *                 *   N
     *                / \
     *               M   S
     */
    EncodingTreeNode* tree = new EncodingTreeNode {
           '*',
           new EncodingTreeNode { 'O', nullptr, nullptr },
               new EncodingTreeNode { '*',
               new EncodingTreeNode{ '*',
               new EncodingTreeNode { 'M', nullptr, nullptr },
               new EncodingTreeNode { 'S', nullptr, nullptr }
            },
            new EncodingTreeNode{ 'N', nullptr, nullptr }
        }
    };

    /* What you get if you encode MONSOON with this tree. */
    Queue<Bit> expected = { 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1 };

    EXPECT_EQUAL(encodeText("MONSOON", tree), expected);

    deleteTree(tree);
}

PROVIDED_TEST("Can encode all char values.") {
    /* All possible characters. */
    string allChars = pangrammaticString();

    /* Try encoding all pairs of adjacent characters. */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        string toEncode;
        toEncode += allChars[i];
        toEncode += allChars[i + 1];
        toEncode += allChars[i + 1];

        EncodingTreeNode* tree = new EncodingTreeNode {
                ' ',
                new EncodingTreeNode {allChars[i], nullptr, nullptr},
                new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        /* See what bits we get back. We should get 011, since the first
         * character has code 0 and the second has code 1.
         */
        Queue<Bit> bits = encodeText(toEncode, tree);
        Queue<Bit> expected = { 0, 1, 1 };

        EXPECT_EQUAL(bits, expected);

        deleteTree(tree);
    }
}

PROVIDED_TEST("decodeText undoes encodeText on range of sample strings.") {
    Vector<string> testCases = {
        "THAT THAT IS IS THAT THAT IS NOT IS NOT IS THAT IT IT IS",
        "AABAAABBABAAABAAAA",
        ":-) :-D XD <(^_^)>",
        pangrammaticString(),
    };

    for (string test: testCases) {
        /* Use a silly encoding scheme, but one that works regardless of what
         * characters are provided.
         */
        EncodingTreeNode* tree = strandTreeFor(test);
        EXPECT(isEncodingTree(tree));

        Queue<Bit> bits = encodeText(test, tree);
        string result = decodeText(bits, tree);

        EXPECT_EQUAL(test.size(), result.size());
        EXPECT_EQUAL(test, result);

        deleteTree(tree);
    }
}

PROVIDED_TEST("Can decode an example tree.") {
    /* This encodes this tree:
     *
     *                 *
     *                / \
     *               *   C
     *              / \
     *             A   B
     */
    Queue<Bit>  bits   = { 1, 1, 0, 0, 0 };
    Queue<char> leaves = { 'A', 'B', 'C' };

    EncodingTreeNode* tree = decodeTree(bits, leaves);
    EXPECT(isEncodingTree(tree));

    /* Confirm this is the right tree. */
    EncodingTreeNode* expected = new EncodingTreeNode {
        '*',
            new EncodingTreeNode {
                '*',
                new EncodingTreeNode { 'A', nullptr, nullptr },
                new EncodingTreeNode { 'B', nullptr, nullptr },
            },
            new EncodingTreeNode { 'C', nullptr, nullptr }
    };

    EXPECT(areEqual(tree, expected));

    deleteTree(tree);
    deleteTree(expected);
}

PROVIDED_TEST("Can decode trees using all possible char values.") {
    /* All possible characters. */
    string allChars = pangrammaticString();

    /* Try encoding all pairs of adjacent characters. */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        EncodingTreeNode* expected = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };
        Queue<Bit>  treeBits   = { 1, 0, 0 };
        Queue<char> treeLeaves = { allChars[i], allChars[i + 1] };

        EncodingTreeNode* tree = decodeTree(treeBits, treeLeaves);
        EXPECT(isEncodingTree(tree));
        EXPECT(areEqual(tree, expected));

        deleteTree(tree);
        deleteTree(expected);
    }
}

PROVIDED_TEST("Can encode an example tree.") {
    /* Build an encoding tree for "ABBCCCC." It should look like this:
     *
     *                 *
     *                / \
     *               *   C
     *              / \
     *             A   B
     *
     * This will compress down to
     *
     *        11000
     *        ABC
     */
    EncodingTreeNode* tree = huffmanTreeFor("ABBCCCC");

    Queue<Bit>  bits;
    Queue<char> leaves;

    encodeTree(tree, bits, leaves);

    Queue<Bit>  expectedBits   = { 1, 1, 0, 0, 0 };
    Queue<char> expectedLeaves = { 'A', 'B', 'C' };

    EXPECT_EQUAL(bits,   expectedBits);
    EXPECT_EQUAL(leaves, expectedLeaves);

    deleteTree(tree);
}

PROVIDED_TEST("Can encode trees using all possible char values.") {
    /* All possible characters. */
    string allChars = pangrammaticString();

    /* Try encoding all pairs of adjacent characters. */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        EncodingTreeNode* tree = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        /* See what we get back. It should be the bitstring 100 (root with
         * two children) and the two leaves, in order.
         */
        Queue<Bit>  treeBits;
        Queue<char> treeLeaves;

        Queue<Bit>  expectedBits = { 1, 0, 0 };
        Queue<char> expectedLeaves = { allChars[i], allChars[i + 1] };

        encodeTree(tree, treeBits, treeLeaves);
        EXPECT_EQUAL(treeBits, expectedBits);
        EXPECT_EQUAL(treeLeaves, expectedLeaves);

        deleteTree(tree);
    }
}

PROVIDED_TEST("decodeTree undoes encodeTree on sample strings.") {
    /* Make a Huffman tree for the string of all characters. */
    EncodingTreeNode* sourceTree = huffmanTreeFor(pangrammaticString());
    EXPECT(isEncodingTree(sourceTree));

    /* Encode, then decode it. */
    Queue<Bit>  bits;
    Queue<char> leaves;
    encodeTree(sourceTree, bits, leaves);

    EncodingTreeNode* resultTree = decodeTree(bits, leaves);
    EXPECT(isEncodingTree(resultTree));
    EXPECT(areEqual(sourceTree, resultTree));

    deleteTree(sourceTree);
    deleteTree(resultTree);
}

PROVIDED_TEST("Can decompress a small sample file.") {
    HuffmanResult file = {
        { 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0 },
        { 'u', 'k', 'p', 'n', 'a', 'm', 'h' },
        { 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1,
          0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
          0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0 }
    };

    EXPECT_EQUAL(decompress(file), "humuhumunukunukuapuaa");
}

PROVIDED_TEST("Compress reports errors on bad inputs.") {
    EXPECT_ERROR(compress(""));
    EXPECT_ERROR(compress("A"));
    EXPECT_ERROR(compress("AAAA"));
}

PROVIDED_TEST("Can compress a small sample file.") {
    HuffmanResult file = compress("ABANANAABANDANA");
    Queue<Bit>  treeBits    = { 1, 1, 1, 0, 0, 0, 0 };
    Queue<char> treeChars   = { 'D', 'B', 'N', 'A' };
    Queue<Bit>  messageBits = { 1, 0, 0, 1, 1, 0, 1, 1, 0,
                                1, 1, 1, 0, 0, 1, 1, 0, 1,
                                0, 0, 0, 1, 0, 1, 1 };

    EXPECT_EQUAL(file.treeBits, treeBits);
    EXPECT_EQUAL(file.treeLeaves, treeChars);
    EXPECT_EQUAL(file.messageBits, messageBits);
}

PROVIDED_TEST("Compress undoes decompress on a range of strings.") {
    Vector<string> testCases = {
        "THAT THAT IS IS THAT THAT IS NOT IS NOT IS THAT IT IT IS",
        "AABAAABBABAAABAAAA",
        ":-) :-D XD <(^_^)>",
        pangrammaticString(),
    };

    for (string test: testCases) {
        HuffmanResult file = compress(test);
        string result = decompress(file);

        EXPECT_EQUAL(result.size(), test.size());
        EXPECT_EQUAL(test, result);
    }
}


STUDENT_TEST("huffmanTreeFor builds tree for two puctuation marks.") {
    EncodingTreeNode* reference = new EncodingTreeNode {
        ' ', new EncodingTreeNode {'!', nullptr, nullptr}, new EncodingTreeNode {'?', nullptr, nullptr}
    };

    EncodingTreeNode* tree = huffmanTreeFor("!!!????");
    EXPECT(isEncodingTree(tree));
    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}
