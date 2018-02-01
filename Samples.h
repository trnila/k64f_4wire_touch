#pragma once

template<typename T, comparator>
class Samples {
public:
	Samples(int size): size(size), count(0), last(0) {
		samples = new T[size];
	}

	void add(T sample) {
		samples[last++] = sample;
	}

	T median() {
		std::sort(samples, samples + size, comparator);
	}

	~Samples() {
		delete[] samples;
	}

private:
	T *samples;
	int size;
	int count;
	int last;
};
