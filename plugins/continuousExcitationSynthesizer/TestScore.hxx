/*
 * Copyright (c) 2001-2004 MUSIC TECHNOLOGY GROUP (MTG)
 *                         UNIVERSITAT POMPEU FABRA
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef _TestScore_HXX
#define _TestScore_HXX

#include "ContinuousExcitationControlSource.hxx"
#include <string>
#include <vector>

namespace CLAM {

/**
* This class can be used to load a score from disk that gives a control stream
* of pitch and amplitude values in the following format:
* pitch amplitude
* where pitch is in hertz and the amplitude is a value between 0 and 1.
* Scores in this format are generated by people working with audio analysis
* algorithms in Matlab.
*
* \author greg kellum [gkellum@iua.upf.edu] 7/15/07
* \since  CLAM v1.1.
*/
class TestScore : public ContinuousExcitationControlSource
{
public:
	TestScore();
	TestScore(std::string filename);
	virtual ~TestScore();

	/**
	* The path of the score file to load.
	*/
	bool LoadScore(std::string filename);

	/**
	* This method can be used to ask for the next line of control information.
	*/
	bool GetControlValues(float& pitch, float& amplitude);

protected:
	void tokenize(	const std::string& str,
					std::vector<std::string>& tokens,
					const std::string& delimiters = " ");

	bool NextFrameAutogenerated(float& pitch, float& amplitude);

	bool NextFrameFromScore(float& pitch, float& amplitude);

private:
	int counter;
	int numberOfIterations;
	int numberOfEventsLoaded;
	bool isScoreLoaded;
	std::vector< std::vector<float> > scoreVector;
};

} // end namespace CLAM

#endif
