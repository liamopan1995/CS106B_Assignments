#include "HumanPyramids.h"
#include "error.h"
#include "grid.h"
#include "map.h"

using namespace std;
// function prototype
double computeWeightOnBack(int row, int col, Map<int, Map<int, double> > &table);

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */
//double weightOnBackOf(int row, int col, int pyramidHeight) {                // it is a wrapper
//    /* TODO: Delete the next few lines and implement this function. */
//    if ( row < 0||col < 0|| row > pyramidHeight - 1|| col > pyramidHeight - 1) error("false");


//    if ( row == 0) {
//        return 0;
//    }
//    else {
//        if (col == 0 || col == row ) {
//            return 80 + weightOnBackOf(row -1, 0 ,pyramidHeight)/2;
//        }
//        else {
//            return weightOnBackOf(row - 1, col-1, pyramidHeight)/2 + 160 +
//                   weightOnBackOf(row - 1, col, pyramidHeight)/2;

//        }
//    }

//}             // milestone one successed


double weightOnBackOf(int row, int col, int pyramidHeight) {                                        // it is a wrapper

    if ( row < 0||col < 0|| row > pyramidHeight - 1|| col > pyramidHeight - 1) error("false");  // initial condition check 1.no nega roc or col
                                                                                                // no  location out of pyramide
    Map<int,Map<int,double>>table;                                                              // initialize the empty table first int represents row  , second col
    return computeWeightOnBack(row, col,table); // the function that takes the real work
}

// function declaration
double computeWeightOnBack(int row, int col, Map<int,Map<int,double>> & table){
    if ( row == 0) {
        return 0;
    }
    else {
        if (col == 0 || col == row ) {
        if(table.containsKey(row) && table[row].containsKey(col)) {
            return table[row][col];                                     //check in table
        }

        else {
            table[row][col] = 80 + computeWeightOnBack(row -1, 0, table)/2;    // do when not in table
            return table[row][col];
        }
        }
        else {
            if(table.containsKey(row) && table[row].containsKey(col)) {
                return table[row][col];
            }
            else {
                table[row][col] = computeWeightOnBack(row -1, col-1, table)/2 + 160 +
                        computeWeightOnBack(row -1, col, table)/2;
                return table[row][col];
            }

        }
    }
return 0;
    }



/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */














/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */
    //SHOW_ERROR("This test is configured to always fail until you delete this line from\n         HumanPyramids.cpp. Once you have implemented memoization and want\n         to check whether it works correctly, remove the indicated line.");

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
STUDENT_TEST("Check Person A from the handout.") {
    /* Person E is located at row 0, column 0. */
    EXPECT_EQUAL(weightOnBackOf(0, 0, 5), 0);
}

STUDENT_TEST("Check ERROR OF bad input.") {
    /* Person E is located at row 0, column 0. */
    EXPECT_ERROR(weightOnBackOf(5, 2, 5));
}
STUDENT_TEST("Check Person M from the handout.") {
    /* Person E is located at row 0, column 0. */
    EXPECT_EQUAL(weightOnBackOf(4, 2, 5), 500);
}
STUDENT_TEST("My testcase.") {
    double a=weightOnBackOf(0,0,1);
    EXPECT_EQUAL(a,0);
    a=weightOnBackOf(4,2,5);
    EXPECT_EQUAL(a,500);

}


