/*
 * debounce_reader.hpp
 *
 *  Created on: Oct 17, 2025
 *      Author: Oleksiy
 */

#ifndef DECORATORS_DEBOUNCE_READER_HPP_
#define DECORATORS_DEBOUNCE_READER_HPP_

#include <cstdint>
#include "../interfaces/reader.hpp"

namespace nikolex {

class DebounceReader: public Reader {

	Reader* _reader;
	uint32_t prevTime;
	volatile uint32_t* _counter;
	uint32_t debounce;

public:

	DebounceReader(Reader* reader, volatile uint32_t* counter, uint32_t debounce_ms = 30):
	_reader(reader),
	_counter(counter),
	debounce(debounce_ms)
	{
		prevTime = 0;
	}

	virtual void read(){
		if(prevTime == 0){
			prevTime = *_counter;
			_reader->read();
		}
		else {
			if((prevTime + debounce) < *_counter){
				prevTime = *_counter;
				_reader->read();
			}
		}
	}
};

}



#endif /* DECORATORS_DEBOUNCE_READER_HPP_ */
