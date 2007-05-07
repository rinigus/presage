
/*****************************************************************************\
 *                                                                           *
 * Soothsayer, an extensible predictive text entry system                    *
 * ------------------------------------------------------                    *
 *                                                                           *
 * Copyright (C) 2004  Matteo Vescovi <matteo.vescovi@yahoo.co.uk>           *
 *                                                                           *
 * This program is free software; you can redistribute it and/or             *
 * modify it under the terms of the GNU General Public License               *
 * as published by the Free Software Foundation; either version 2            *
 * of the License, or (at your option) any later version.                    *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License         *
 * along with this program; if not, write to the Free Software               *
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.*
 *                                                                           *
\*****************************************************************************/


#ifndef SOOTH_DUMMYPLUGIN
#define SOOTH_DUMMYPLUGIN

#include "plugins/plugin.h"


/** Dummy plugin is provided here to show how to implement real plugins.
 *
 */
class DummyPlugin : public Plugin {
public:
    DummyPlugin(HistoryTracker&, Profile*);
    ~DummyPlugin();

    virtual Prediction predict() const;

    virtual void learn();
    virtual void extract();
    virtual void train();

private:
	
};


// Class factory functions
extern "C" DummyPlugin* create (HistoryTracker&, Profile*);
extern "C" void         destroy(DummyPlugin*);


#endif // SOOTH_DUMMYPLUGIN
