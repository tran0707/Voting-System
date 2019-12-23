/**
 * @file main.cc
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "voting_system.h"
#include "controller.h"
/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(__unused int argc, __unused char **argv) {
	//auto * voting_system = new VotingSystem;

	auto * controller = new Controller;
	// The controller will call its Run to begin the process.
	controller->Run();
	return 0;
}
