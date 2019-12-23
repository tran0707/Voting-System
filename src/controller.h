/**
 * @file controller.h
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>

#include "src/voting_system.h"
#include "src/common.h"
#include "src/communication.h"
#include "src/graphics_voting_system_viewer.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

class GraphicsVotingSystemViewer;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Controller that mediates Arena and GraphicsVotingSystemViewer communication.
 *
 * The Controller instantiates the Arena and the GraphicsVotingSystemViewer. The
 * viewer contains the main loop that keeps it live, but at each update, the
 * viewer sends a message to the controller to update its time.
 *
 * Other types of communication between Arena and Viewer include:
 * - keypresses intercepted by the Viewer.
 * - Play/Pause/New Game user input via the Viewer.
 * - Game status from arena to the viewer.
 **/
class Controller {
 public:
  /**
   * @brief Controller's constructor that will create Arena and Viewer.
   */
  Controller();

  /**
   * @brief Run launches the graphics and starts the game.
   */
  void Run();

  /**
   * @brief AdvanceTime is communication from the Viewer to advance the
   * simulation.
   */
  void AdvanceTime(double dt);

  /**
   * @brief AcceptCommunication from either the viewer or the Arena
   */
  void AcceptCommunication(Communication com);

  /**
  * @brief Converts the communication from one to send to the other.
  *
  * Used primarily for testing purposes to insure communication is being
  * correctly received, interpreted, and relayed.
  */
  Communication ConvertComm(Communication com);

 private:
  double last_dt{0};
  VotingSystem* voting_system_{nullptr};
  GraphicsVotingSystemViewer* viewer_{nullptr};
};

#endif /* SRC_CONTROLLER_H_ */
