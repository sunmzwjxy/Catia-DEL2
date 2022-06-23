//===================================================================
// COPYRIGHT DS 2021/12/06
//===================================================================
// COMACView2PicCmd.cpp
// Header definition of class COMACView2PicCmd
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2021/12/06 Creation: Code generated by the 3DS wizard
//===================================================================

#ifndef COMACView2PicCmd_H
#define COMACView2PicCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

//DialogEngine 
#include "CATPathElementAgent.h"

//----------------------------------------------------------------------

/**
* Describe your command here.
* <p>
* Using this prefered syntax will enable mkdoc to document your class.
* <p>
* refer to programming resources of Dialog engine framework.
* (consult base class description).
*/
class COMACView2PicCmd: public CATStateCommand
{
// Allows customization/internationalization of command's messages
// ---------------------------------------------------------------
DeclareResource( COMACView2PicCmd, CATStateCommand )

public:
COMACView2PicCmd();
virtual ~COMACView2PicCmd();

/**
* Defines the command automata.
* <br>
* <i>(states, transitions and agents)</i>
*/
virtual void     BuildGraph();


/**
* Action associated to state transitions.
*/
virtual CATBoolean  ActionOne(void * data);

private:

	CATPathElementAgent	* _pSelectAgent;
};

//----------------------------------------------------------------------

#endif