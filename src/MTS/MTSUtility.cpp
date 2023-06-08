#include "MTSUtility.h"
void scroll(unsigned& index, const unsigned size, const int strike, bool loop) {
	if (size == 0)
		return;
	if (loop) {
		int mod = (static_cast<int>(index) + strike) % static_cast<int>(size);
		index = static_cast<unsigned>(mod < 0 ? mod + size : mod);
	}
	else {
		int temp = static_cast<int>(index) + strike;
		if (temp < 0)
			index = 0;
		else if (temp >= static_cast<int>(size))
			index = size - 1;
		else
			index = static_cast<unsigned>(temp);
	}
}