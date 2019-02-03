#include "Bit_set.h"
#include <stdio.h>
#include "symtab.h"

Bit_set::Bit_set(int n) {
	this->n = n;
	int p = (n - 1) / 32 + 1;
	bits = new int[p];
	for (int i = 0; i < p; i++)
		bits[i] = 0;
}

Bit_set::Bit_set(const Bit_set &s) {
	n = s.n;
	int p = (n - 1) / 32 + 1;
	bits = new int[p];
	for (int i = 0; i < p; i++)
		bits[i] = s.bits[i];
}

Bit_set::~Bit_set() {
	delete[] bits;
}

int Bit_set::operator[] (int index) {
	int p = index / 32, q = index - p * 32;
	return ((bits[p]) >> q) & 1;
}

Bit_set Bit_set::operator=(const Bit_set &s) {
	int p = (n - 1) / 32 + 1;
	for (int i = 0; i < p; i++)
		bits[i] = s.bits[i];
	return *this;
}

Bit_set operator & (Bit_set s1, Bit_set s2) {
	Bit_set s(s1.n);
	if (s1.n != s2.n) {
		fprintf(stderr, "Unmatched size!\n");
	}
	else {
		for (int i = 0; i < (s1.n - 1) / 32 + 1; i++)
			s.bits[i] = s1.bits[i] & s2.bits[i];
	}
	return s;
}


Bit_set operator | (Bit_set s1, Bit_set s2) {
	Bit_set s(s1.n);
	if (s1.n != s2.n) {
		fprintf(stderr, "Unmatched size!\n");
	}
	else {
		for (int i = 0; i < (s1.n - 1) / 32 + 1; i++)
			s.bits[i] = s1.bits[i] | s2.bits[i];
	}
	return s;
}

Bit_set operator ^ (Bit_set s1, Bit_set s2) {
	Bit_set s(s1.n);
	if (s1.n != s2.n) {
		fprintf(stderr, "Unmatched size!\n");
	}
	else {
		for (int i = 0; i < (s1.n - 1) / 32 + 1; i++)
			s.bits[i] = s1.bits[i] ^ s2.bits[i];
	}
	return s;
}

bool operator == (Bit_set s1, Bit_set s2) {
	bool eq = true;
	if (s1.n != s2.n) {
		fprintf(stderr, "Unmatched size!\n");
		return false;
	}
	else {
		for (int i = 0; i < (s1.n - 1) / 32 + 1; i++) {
			if (s1.bits[i] != s2.bits[i]) {
				eq = false;
				break;
			}
		}
	}
	return eq;
}

void Bit_set::set_bit(int index, int bit) {
	int p = index / 32, q = index - p * 32;
	bits[p] = (bits[p] & (0xFFFFFFFF - (1 << q))) + ((bit & 1) << q);
}

void Bit_set::clear() {
	int p = (n - 1) / 32 + 1;
	for (int i = 0; i < p; i++)
		bits[i] = 0;
}

int Bit_set::num() {
	int p = (n - 1) / 32 + 1, cnt = 0;
	for (int i = 0; i < p; i++) {
		int tmp = bits[i];
		for (int j = 0; j < 32; j++) {
			if ((tmp & 1) == 1) {
				cnt++;
			}
			tmp >>= 1;
		}
	}
	return cnt;
}

void print(Bit_set s) {
	for (int i = 0; i < s.n; i++) {
		if (s[i] == 1)
			printf("%c%d ", index_var[i].kind, index_var[i].index);
	}
}
