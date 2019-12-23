/**
 * @file communication.h
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */

#ifndef SRC_COMMUNICATION_H_
#define SRC_COMMUNICATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
enum Communication {
  // communications from GUI to controller
  bButtonExportAudit,
  bButtonExportSharing,
  bButtonOpen,
  bButtonRestart,
  bButtonAudit,

  // communications from controller to Voting System
  kOpen,
  kSaveAudit,
  kSaveSharing,
  kAudit,
  kReset,

  // communications from Voting System to Controller
  
  kNone   // in case it is needed
};

#endif  // SRC_COMMUNICATION_H_
