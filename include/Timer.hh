//////////////////////////////////////////////////////////////////////////
// CachedParameterisation
// ======================
// High fidelity parameterised geometry in GEANT4 described by data
//
// Author:  Christopher M Poole <mail@christopherpoole.net>
// Source:  http://github.com/christopherpoole/CachedParameterisation
//
// License & Copyright
// ===================
// 
// Copyright 2013 Christopher M Poole <mail@christopherpoole.net>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////////


#ifndef Timer_h
#define Timer_h 1

// GEANT4 //
#include "globals.hh"

// STL/SYS //
#include <string>
#include <fstream>
#include <sys/time.h>


class Timer
{
  public:
    Timer(std::string name) {
        this->name = name;
    };

    ~Timer() {
    };

  public:
    void start() {
        clock_gettime(CLOCK_REALTIME, &start_time);
    };

    timespec stop() {
        clock_gettime(CLOCK_REALTIME, &stop_time);

        timespec time;
        time.tv_sec = stop_time.tv_sec - start_time.tv_sec;
        time.tv_nsec = stop_time.tv_nsec - start_time.tv_nsec;
            
        return time;
    };

  protected: 
    std::string name;
   
    timespec start_time;
    timespec stop_time;
};


class TimingHistogram
{
  public:
    TimingHistogram(std::string name) {
        timer = new Timer(name);
        events = new std::vector<timespec>();
    };

    ~TimingHistogram() {
    };

  public:
    unsigned int GetLength() {
        return events->size();
    };

    void start() {
        this->timer->start();
    };

    void stop() {
        events->push_back(timer->stop());
    };    

    void dump(std::string filename) {
        std::ofstream output(filename.c_str());

        for (unsigned int i=0; i<GetLength(); i++) {
            timespec ts = events->at(i);
            output << ts.tv_sec << " " << ts.tv_nsec << std::endl;
        }
        output.close();
    };

  private:
    Timer* timer;
    std::vector<timespec>* events;
};

#endif

