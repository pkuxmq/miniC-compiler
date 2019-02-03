#ifndef __BIT_SET__
#define __BIT_SET__

class Bit_set {
public:
	int n;
	int *bits;

public:
	Bit_set(int n);
	Bit_set(const Bit_set &s);
	~Bit_set();
	int operator [] (int index);
	Bit_set operator = (const Bit_set &s);
	friend Bit_set operator & (Bit_set s1, Bit_set s2);
	friend Bit_set operator | (Bit_set s1, Bit_set s2);
	friend Bit_set operator ^ (Bit_set s1, Bit_set s2);
	friend bool operator == (Bit_set s1, Bit_set s2);
	void set_bit(int index, int bit);
	void clear();
	int num();
	friend void print(Bit_set s);
};

Bit_set operator & (Bit_set s1, Bit_set s2);
Bit_set operator | (Bit_set s1, Bit_set s2);
Bit_set operator ^ (Bit_set s1, Bit_set s2);
bool operator == (Bit_set s1, Bit_set s2);

#endif
