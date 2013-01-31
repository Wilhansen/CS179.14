#ifndef ComboSequenceDecector_HPP__
#define ComboSequenceDecector_HPP__

/****
 *
 * ComboSequenceDetector Class
 *
 *
 Copyright (c) 2013 Wilhansen B. Li
 
 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source
 distribution.
 *
 */

class ComboSequenceDetector {
	const double duration;
	const std::vector<uint8_t> sequence;
	const bool autoreset;
	
	uint8_t currentState;
	double currentDuration;
	size_t sequencePosition;
	
	uint8_t currentTargetState() const {
		if ( sequencePosition >= sequence.size() )
			return 0;
		return sequence[sequencePosition];
	}
	uint8_t previousTargetState() const {
		if ( sequencePosition >= sequence.size() || sequencePosition == 0 )
			return 0;
		return sequence[sequencePosition - 1];
	}
public:
	ComboSequenceDetector(const std::vector<uint8_t> &sequence, double duration = 1.0, bool autoreset = true) : duration(duration), sequence(sequence), currentState(0), currentDuration(0), sequencePosition(0), autoreset(autoreset) {}
	
	void keyUp(uint8_t code) {
		currentState &= ~code;
	}
	
	void keyDown(uint8_t code) {
		currentState |= code;
	}
	
	void reset() {
		currentDuration = 0;
		sequencePosition = 0;
	}
	void update(double dt) {
		if ( *this ) {
			if ( autoreset )
				reset();
			else
				return;
		}
		
		currentDuration += dt;
		if ( currentDuration > duration ) {
			reset();
		}
		
		if ( *this ) return;
		
		if ( currentState ==  currentTargetState() ) {
			++sequencePosition;
			return;
		}
		
		auto stateMask = currentTargetState() | previousTargetState();
		if ( (stateMask | currentState) ^ stateMask ) {
			reset();
			if ( currentState == currentTargetState() )
				++sequencePosition;
		} else {
			//indeterminate
		}
	}
	
	operator bool() const {
		return sequencePosition >= sequence.size();
	}
};

#endif