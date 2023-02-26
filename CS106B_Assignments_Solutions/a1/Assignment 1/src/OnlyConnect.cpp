/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
#include "strlib.h"
#include <cctype>
using namespace std;
// Function Prototype//
bool isVowel(char ch);

string onlyConnectize(string phrase) {
    /* TODO: The next few lines just exist to make sure you don't get compiler warning messages
     * when this function isn't implemented. Delete these lines, then implement this function.
     */
//    (void) phrase;
//    return "";
    string result = "";
    if (phrase.size() > 0)
    {
        if ( isalpha(phrase[0]) ) {
            if ( isVowel( phrase[0] )){
                return result += onlyConnectize( phrase.substr(1) );
            } else {
                result +=  phrase[0] + onlyConnectize( phrase.substr(1));  // this return we do really care to be uppercase
                return toUpperCase(result);
            }


        } else {
            return result +=onlyConnectize( phrase.substr(1));
        }
    }
    else {
        return "";
    }
}



//
// isVowel //
bool isVowel(char ch){
    switch (ch) {
    case 'A': case 'E': case 'I': case 'O': case 'U':
    case 'a': case 'e': case 'i': case 'o': case 'u':
        return true;
    default:
        return false;
    }
}


/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

STUDENT_TEST("strings including other languages") {
    EXPECT_EQUAL(onlyConnectize("早上好，现在我有冰淇淋"), "");
}
STUDENT_TEST("strings including other languages") {
        EXPECT_EQUAL(onlyConnectize("überqueren ä"), "BRQRN");
}

/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */






