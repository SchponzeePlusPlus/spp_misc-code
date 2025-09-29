# Solution_Justification.md

This attempt at the solution is not what I would personally define as the most pratical, clean, and efficient, but rather it is my first revision at the solution. In this first revision, I have attempted to solve the entire challenge using concepts that I am more familiar with. Assuming that the output is correct, I would use this revision as my own personal benchmark for future revisions.

This revision generates every possible combination on a 4 x 5 keyboard, then checks which combinations are correct as per the challenge criteria. The biggest limitation is that it can calculate an answer for a maximum digit sequence of 5 and not beyond up to 10 as is specified in the challenge. This is due to the use of large dynamic arrays, the dependance on them would have to be removed in the next revision since storage of each combination is not a requirement for the challenge.

The solution is also not clean, it lacks modularity, and conforming naming conventions. It is not clear to read and I would not recommend it as a final attemmpt at the solution that is fit for peer review, but rather a proof of concept developed within a week as the time constraint.

If time permits, I am also hoping to eventually explore impelenting advanced data structure/s and algorithm/s using concept/s such as linked lists. This would require some re-learning on my part to implmement. I believe that implementing a concept such as a linked list would be more efficient than checking 20 ^ 10 different raw combinations.

I approached the problem by thinking about how to manage each different possibility. The easiest method to achieve this was to treat the keyboard's 18 (20 if you include the empty spaces) keys like a number system. The combination would then become a 10 digit value in a base-20 numbering system. To increment the value, you could shift to the next character on the keyboard (e.g. A to B, E to F, or O to 1). This way you could generate every possible combination by treating the keyboard combinations as possible numbers that can be incremented. To increment and shift values from one key to another, it was easier to work in terms of 2-Dimensional array elements rather than the characters themselves, and remaining in this format would be easier for the knight move checking as well. I know my algorithm correctly checks the challenge criteria because I have looked at the combinations being considered as valid, and so far they appear to conform.

3 Digit Sequence, Valid Combinations: 188
4 Digit Sequence, Valid Combinations: 598
5 Digit Sequence, Valid Combinations: 1899