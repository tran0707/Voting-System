/**
 * @file candidates.h
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */
#ifndef SRC_CANDIDATES_H
#define SRC_CANDIDATES_H


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <string>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
  * @brief Candidate is an entity participating in the election.
  * It holds vote information when it's Open Party List voting.
  */
class Candidate {
 public:
  /**
  * @brief Candidate is constructor of class Candidate for Closed Party list
  * which takes name of candidate and order_priority_party
  *
  * @return None
  *
  */
  Candidate(std::string name, int order_priority_party);
  /**
  * @brief Candidate is constructor of class Candidate for Open Party list
  * which takes name of candidate
  *
  * @return None
  *
  */
  Candidate(std::string name);
  /**
  * @brief Candidate is a default constructor
  *
  * @return None
  */
  Candidate();
  /**
  * @brief set the order of priority party for Closed Party List
  *
  * @return None
  */
  void SetOrderPriorityParty(int order_priority_party);
  /**
  * @brief get the name of the candidates in each party
  *
  * @return name_
  */
  std::string GetName();
  /**
  * @brief set the number of ballot to count the ballot number
  *
  * @return None
  */
  void SetBallotNum(int num);
  /**
  * @brief get the ballot number from Candidate class
  *
  * @return counting_ballot
  */
  int GetBallotNum();
  /**
  * @brief get the priority order for Closed Party List
  *
  * @return order_priority_party_
  */
  int GetPriority();

  // the list of integer for identification's ballot
  std::vector <int> list_ballot_id_ = {};
 private:
  // the name of the candidates
	 std::string name_{""};
  // the order of priority party for closed party list
	 int order_priority_party_{0};
  // count the ballot
	 int counting_ballot{0};
};
#endif  // SRC_CANDIDATES_H
