#include "RisingTides.h"
#include "GUI/SimpleTest.h"
#include "queue.h"
#include "grid.h"

using namespace std;
// function prototype
Vector<GridLocation> getAdjacentLo( const GridLocation &atLocation);
// main function
Grid<bool> floodedRegionsIn(const Grid<double>& terrain,
                            const Vector<GridLocation>& sources,
                            double height) {
    /* TODO: Delete this line and the next four lines, then implement this function. */

    Grid<bool> isFlooded(terrain.numRows(),terrain.numCols(),false);
    Grid<bool> isEvaluated(terrain.numRows(),terrain.numCols(),false);
    Grid<bool> isInQueue(terrain.numRows(),terrain.numCols(),false);

    Queue <GridLocation> toEvaluate= {};    // set up a queue to hold loactions to analyse at next
    for (GridLocation lo: sources) {
        if (terrain.get(lo) <= height && terrain.inBounds(lo)) {
            isFlooded[lo] = true;
            isEvaluated[lo] = true;
            toEvaluate.enqueue(lo);
            isInQueue[lo] = true;  // if source location is smaller than the water height then add it into the queue
        }
    }

    while (!toEvaluate.isEmpty()) {   // process if the queue not empty
        GridLocation atLocation = toEvaluate.dequeue(); // dequeue a location , name it as atLoction
        //            if(terrain.get(atLocation) <= height ) {
        //                isFlooded[atLocation] = true;
        //                isEvaluated[atLocation] = true;
        // analyse the just dequequed location
        // on conditions : this location is inside of terrian

        Vector<GridLocation> adjacentLo = getAdjacentLo( atLocation );
        // save neighboured loaction as a vector
        for (GridLocation i:adjacentLo) {    //  place those neighbouring locations in that vector into the queue
            if(terrain.inBounds(i)) {
                if (terrain[i] <= height && !isFlooded[i]  )  {
                    isFlooded[i] =true;
                    toEvaluate.enqueue(i);     // only when it is shallowr than the water
                    //and hasn't be flooded , it will be enqueued , so that . the queue can get shorter to empty while running this programm
                    // this is the same as create another list which is made to store all notes which were already been explored but here
                    //more smarter trick has been used . no problem, just keep it in mind we need a record that prevents undless exploring

                }
            }


    }

    }


    return isFlooded;
}

// function declaration
Vector<GridLocation> getAdjacentLo( const GridLocation &atLocation){


//    adjacentLo.add([atLocation.row + 1,atLocation.row]);
//    adjacentLo.add([atLocation.row - 1,atLocation.row]);
//    adjacentLo.add([atLocation.row ,atLocation.row - 1]);
//    adjacentLo.add([atLocation.row ,atLocation.row + 1]);
//  复制粘贴多行语句时一定要谨慎，  下面一开始复制粘贴错误了 就像上面4行 全是.row ， 查这个bug 查了快半个下午了，下次注意这种错误不要再出现了！！

    GridLocation location1 = {atLocation.row,atLocation.col};
    GridLocation location2 = {atLocation.row,atLocation.col};
    GridLocation location3 = {atLocation.row ,atLocation.col};
    GridLocation location4 = {atLocation.row ,atLocation.col};
    location1.row = location1.row + 1;
    location2.row = location2.row - 1;
    location3.col = location3.col - 1;
    location4.col = location4.col + 1;
    Vector<GridLocation> adjacentLo= {location1, location2, location3, location4};
    return adjacentLo;
}

/***** Test Cases Below This Point *****/
PROVIDED_TEST("Nothing gets wet if there are no water sources.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        // empty
    };

    /* There are no water sources, so nothing should be underwater. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Everything gets wet if all locations are below the water level.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Everything should flood; there are no barriers to stop the water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true,  true },
        {  true,  true,  true },
        {  true,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a vertical levee.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 0, 2, 0 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Only locations to the left of the barrier should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true, false, false },
        {  true, false, false },
        {  true, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a diagonal levee.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Water only flows in the four cardinal directions, so it can't
     * pass through the barrier. Only the top should be flooded.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't flow diagonally.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 2, 0, 2 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* Water should be trapped in the center, since it can't move
     * diagonally.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false,  true, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow in all cardinal directions.") {
    Grid<double> world = {
        { 2, 0, 2 },
        { 0, 0, 0 },
        { 2, 0, 2 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* The water in this case should flow up, down, left, and right. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false,  true, false },
        {  true,  true,  true },
        { false,  true, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow from multiple sources.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 },
        { 2, 2 }
    };

    /* Everything except the levee should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false,  true },
        { false,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Handles asymmetric worlds and non-square grids") {
    Grid<double> world = {
        { 3, 1, 4, 1 },
        { 5, 9, 2, 6 },
        { 5, 3, 5, 8 }
    };

    /* Initial test - water shouldn't leak out from the 2 if the height is 3.5. */
    Vector<GridLocation> sources = {
        { 1, 2 }
    };

    Grid<bool> expected = {
        { false, false, false, false },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 3.5), expected);

    /* Now, increase the water height to 4.5. */
    expected = {
        {  true,  true,  true,  true },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 4.5), expected);

    /* Now, increase the water height to 5.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true, false },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 5.5), expected);

    /* Now, increase the water height to 6.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true,  true },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 6.5), expected);

    /* Now, increase the water height to 9.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 9.5), expected);
}

PROVIDED_TEST("Stress test: Handles a large, empty world quickly.") {
    Grid<double> world(100, 100); // Large world, everything defaults to 0 height.
    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* This may take a long time to complete if the solution is inefficient. Look
     * for things like
     *
     * 1. passing around large objects by *value* rather than by *reference*,
     * 2. revisiting the same squares multiple times (e.g. flooding the same
     *    cell many times due to not checking if something is flooded),
     *
     * etc.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    EXPECT_EQUAL(water.numRows(), world.numRows());
    EXPECT_EQUAL(water.numCols(), world.numCols());

    /* Everything should be flooded. */
    for (int row = 0; row < world.numRows(); row++) {
        for (int col = 0; col < world.numCols(); col++) {
            EXPECT_EQUAL(water[row][col], true);
        }
    }
}
