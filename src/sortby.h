/**
 * @file common.h
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */

#ifndef SRC_SORTBY_H_
#define SRC_SORTBY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

/*******************************************************************************
 * Common Template Functions
 ******************************************************************************/
/**
 * @brief A structor operator using for sorting function.
 * used by Audit() to compare between 2 candidate priority. Ascending order.
 * e.g. Candidate A has priority 1, Candidate B has priority 2 =>
 * sort will call this operator structor and put A before B
 */
 struct sortbypriority {
   inline bool operator() (std::pair<int, int> p1, std::pair<int, int> p2) {
       return (p1.first < p2.first);
   }
 };

 /**
  * @brief A structor operator using for sorting function.
  * used by Audit() to compare between 2 pairs (Compare Party num votes
  * which is the first element).
  * Ascending order.
  * comparing value of First only
  * e.g. Comparing <123, 456>, <321, 456> =>
  * sort will call this operator structor and put <321, 456> before <123, 456>
  */
 struct sortbypartyvote {
     inline bool operator() (std::pair<int, int> p1, std::pair<int, int> p2) {
         return (p1.first > p2.first);
     }
 };

#endif  // SRC_SORTBY_H_
