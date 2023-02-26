#include "ShiftScheduling.h"
#include "Shift.h"
using namespace std;

/* TODO: Refer to ShiftScheduling.h for more information about what this function should do.
 * Then, delete this comment and replace it with one of your own.
 */
// function portotype
Set<Shift> wrapped( const Set<Shift>& shifts, int  maxHours, Set<Shift> &ShiftAssigned);
bool checkTime(Shift shift,const Set<Shift>& ShiftToAsign, int maxHours);


// func declaration
Set<Shift> highestValueScheduleFor(const Set<Shift>& shifts, int maxHours) {
    /* TODO: Delete the next few lines and implement this function. */
    if (maxHours < 0) error("unfeasible working hour!");
    Set<Shift> ShiftAssigned;
    return wrapped(shifts, maxHours,ShiftAssigned);

}

// function declaration

Set<Shift> wrapped( const Set<Shift>& shifts, int maxHours,Set<Shift> &ShiftAssigned ){
    if(shifts.isEmpty()) {
        return ShiftAssigned;
    }

    else {
        for (Shift shift :shifts) {

            if (checkTime(shift,ShiftAssigned,maxHours)) {         // bool checktime : check if both time left enough for this shift and
                // there is no overlap between this time slot and previously picked schedule
                //add that feasible work to ShiftAssigned
                // *** there are two options, include this schedule or not to,  the scond is missing***

                ShiftAssigned += shift;
                ShiftAssigned += wrapped(shifts-ShiftAssigned,maxHours-lengthOf(shift),ShiftAssigned);
            }  else {
                shifts - shift;
                return ShiftAssigned;
            }
        }

    }
    return ShiftAssigned;
}

// func declare  check time

bool checkTime(Shift shift,const Set<Shift>& ShiftAssigned, int maxHours){
    bool isNotOverlap = true;
    for (Shift alreadyAssigned :ShiftAssigned){
        isNotOverlap = !overlapsWith(shift,alreadyAssigned);// shift and those already assigned
    }
    return lengthOf(shift) < maxHours && isNotOverlap;    // true when time enough and time not across the scheduled

}
