/**
 * @file controller.cc
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>

#include "src/common.h"
#include "src/controller.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

Controller::Controller() : last_dt(0) {
  // Initialize default properties
  voting_system_ = new VotingSystem();

  // Start up the graphics (which creates the menu graphic).
  // Run() will enter the nanogui::mainloop().
  viewer_ = new GraphicsVotingSystemViewer( voting_system_, this);
}

void Controller::Run() {
  // graphic running
  viewer_->Run();
}

void Controller::AdvanceTime(double dt) {
  if ((last_dt + dt) <= .05) {  // Time step ~ 0.5
    last_dt += dt;
    return;
  }
  last_dt = 0;
  // voting_system get update each time step
  voting_system_->AdvanceTime(dt);
}

void Controller::AcceptCommunication(Communication com) {
  // sending commands to voting system
  voting_system_->AcceptCommand(ConvertComm(com));
}

/** Converts communication from one source to appropriate communication to
 * the other source. For example, the viewer sends a bButtonAudit communication,
 * and this translate to a kAudit communication to VotingSystem.
 */
Communication Controller::ConvertComm(Communication com) {
  // getting commands from the graphic, translate to VotingSystem.
  Communication key_value = kNone;
  switch (com) {
    case (bButtonAudit) :
      key_value = kAudit;
      break;
    case (bButtonExportAudit) :
      key_value = kSaveAudit;
      break;
    case (bButtonExportSharing) :
      key_value = kSaveSharing;
      break;
    case (bButtonOpen) :
      key_value = kOpen;
      break;
    case (bButtonRestart) :
      key_value = kReset;
      break;
    default: return kNone;
  }
  return key_value;
}
