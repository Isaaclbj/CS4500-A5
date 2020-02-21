#include "modified_dataframe.h"
#include <fstream>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include "string.h"
#include <math.h>
#include <cstdio>

//simple adding function
class Adder : public Rower
{
public:
	int total;
	int count;

	Adder()
	{
		total = 0;
		count = 0;
	}

	bool accept(Row& r)
	{
		total += r.get_int(0) + r.get_int(1);
	}

	void join_delete(Rower* other)
	{
		total += dynamic_cast<Adder*>(other)->total;
		delete other;
	}
};

//expensive trig functions
class Trigger : public Rower
{
public:
	double total;
	int count;
	Trigger()
	{
		total = 10;
	}

	bool accept(Row& r)
	{
		total = sqrt(abs(total));
		total += (r.get_int(1));
		total = cos(r.get_int(0));
		total = sin(r.get_int(1));
	}

	void join_delete(Rower* other)
	{
		total += dynamic_cast<Trigger*>(other)->total;
		delete other;
	}
};

DataFrame* gen_df()
{
	Schema sch("II");
	DataFrame* df = new DataFrame(sch);

	String* name0;

	for (size_t i = 0; i < 6250000; i++)
	{
		Row* r = new Row(sch);
		r->name = name0->cstr_;
		r->set(0, (int)i);
		r->set(1, (int)i + 1);
		df->add_row(*r);

	}


	return df;
}
int main(int argc, char **argv)
{
	DataFrame* df = gen_df();

	//time map execution on Adder with df data
	//time pmap execution on Adder with df data
	//compare times

	//time map execution on Trigger with df data
	//time pmap execution on Trigger with df data
	//compare times
	return 0;
}