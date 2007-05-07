
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


#include "core/predictor.h"

// REVISIT: including SmoothedUniBiTrigramPlugin here because
// PluginManager and Plump are temporarily disabled. Plugin lifetime
// management is currently disabled. Only one plugin is used:
// SmoothedUniBiTrigramPlugin.
//
// IMPORTANT: remove following include when moving back to dynamically
// loaded plugins
//
#include "plugins/smoothedUniBiTrigramPlugin.h"


Predictor::Predictor(HistoryTracker &ht)
    : historyTracker( ht )
{
    profile = 0;

    // set Predictor options to their defaults
    PREDICT_TIME = DEFAULT_PREDICT_TIME;
    COMBINATION_METHOD = DEFAULT_COMBINATION_METHOD;
	
    assert( initCombiner() );
}


Predictor::~Predictor()
{
    // Clear out existing plugins vector (not strictly necessary)
    plugins.clear();

    delete profile;
}


bool Predictor::initCombiner()
{
    //	std::cout << "Initializing combiner..." << std::endl;

    // Temporarily commented out because Combiner objects are not yet implemented
    //	switch( COMBINATION_METHOD ) {
    //	case LINEAR:
    //		combiner = new LinearCombiner;
    //		break;
    //	case BACKOFF:
    //		combiner = new BackoffCombiner;
    //		break;
    //	case MAXENTROPY:
    //		combiner = new MaxEntropyCombiner;
    //		break;
    //	default:
    //		std::cerr << "Unknown combiner object specified!" << std::endl
    //			  << "Aborting..." << std::endl;
    //		abort();
    //		break;
    //	}
    //
    //	assert( combiner != NULL );

    // Return true if everything's allright
    return true;
}


void Predictor::addPlugin( Plugin* pPtr )
{
    assert( pPtr != NULL );
	
    plugins.push_back( pPtr );
}


bool Predictor::removePlugin( const Plugin* pPtr )
{
    assert( pPtr != NULL );

    std::vector< Plugin* >::iterator i = plugins.begin();
    // scan plugins to see if pPtr can be found
    while( i != plugins.end() && *i != pPtr ) {
        i++;
    }
    // if we find it, erase it and return true
    if( i != plugins.end() && *i == pPtr ) {
        plugins.erase( i );
        return true;
    } else {
        return false;
    }
}


// PLUMP callback
//void callback_predict(plump::PluginInstance* plugin, void* data)
//{
//    Prediction* p = reinterpret_cast<Prediction*>(data);
//    Plugin* predictivePlugin = reinterpret_cast<Plugin*>(plugin->instance());
//    *p = predictivePlugin->predict();
//}


Prediction Predictor::predict() const
{
    //	std::cout << "Predicting..." << std::endl;

    // Here goes code to instantiate a separate thread for each Plugin;
    // code can be taken from test file
    // /home/matt/word_predictor/programming_test/threads.cpp
	


    // All threads need to be synched together. One thread makes sure that
    // we are not exceeding the maximum time allowed.



    // Now that the all threads have exited or have been cancelled,
    // the predictions returned by each of them are combined.


    // PLUMP 	// TEMPORARY **** MODIFY THIS **** TODO
    // PLUMP 	// For the time being, print out predictions returned by each plugin
    // PLUMP 	// to standard output in sequential order
    Prediction p;
    // PLUMP 
    // PLUMP 	std::vector<Plugin*>::const_iterator i = plugins.begin();
    // PLUMP 	for( i=plugins.begin(); i!=plugins.end(); i++ ) {
    // PLUMP 		p = (*i)->predict();
    // PLUMP //		std::cout << p;
    // PLUMP 	}

    ////////
    // PLUMP
    //
    //plump.registerCallback(callback_predict, &p);
    //plump.run();
                
    SmoothedUniBiTrigramPlugin plugin(historyTracker, profile);
    p = plugin.predict();
    

    // Return prediction given by last plugin
    return p;
}


bool Predictor::setPredictTime( const int predictTime )
{
    // handle exception where predictTime is less than zero
    if( predictTime < 0 ) {
        std::cerr << "Error: attempted to set PREDICT_TIME option to "
                  << "a negative integer value. Please make sure that "
                  << "PREDICT_TIME option is set to a value greater "
                  << "than or equal to zero.\a" << std::endl;
        return false;
    } else {
        std::cout << "[Predictor] Setting PREDICT_TIME to " << predictTime << std::endl;
        PREDICT_TIME = predictTime;
        return true;
    }
}


bool Predictor::setCombinationMethod( const CombinationMethod cm )
{
    std::cout << "[Predictor] Setting COMBINATION_METHOD to " << cm << std::endl;
    if( COMBINATION_METHOD != cm ) {

        COMBINATION_METHOD = cm;
	
        // destroy previous combiner object
        delete combiner;
        // init new combiner
        return initCombiner();
    }
		
    return true;
}


int Predictor::getPredictTime() const
{
    return PREDICT_TIME;
}


CombinationMethod Predictor::getCombinationMethod() const
{
    return COMBINATION_METHOD;
}


void Predictor::setProfile(Profile* prof)
{
    delete profile;
    profile = prof;
}
