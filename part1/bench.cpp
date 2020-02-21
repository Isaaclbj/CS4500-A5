#include "modified_dataframe.h"
#include <fstream>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include "string.h"
#include <string>

int main(int argc, char **argv)
{
	const char* FILENAME = "modified_datafile.txt";
	//open datafile.txt
	std::ifstream datafile(FILENAME);

	std::string line;

	Schema sch("IIIIIBBBBS");
	DataFrame df(sch);

	//read in data to dataframe
	while (datafile.peek() != EOF)
	{
      getline(datafile, line);
	  std::cout << "LINE IS " << line << std::endl;
	  //tokenize by using space as delimiter
	  char buff[line.length() + 1];
	  strcpy(buff, line.c_str());

	  char * temp = strtok(buff, " ");
	  std::cout << "TEMP IS " << temp << std::endl;
	  Row r(df.get_schema());
	  //we know there's only 10 items in each row
	  for (int i = 0; i < 10; i++)
	  {
		  std::cout << "Adding " << temp << " to row at index " << i << std::endl;
		  //feed tokens into row
		  if (i <= 4)
		  {
			  std::cout << "BREAKING HERE?" << std::endl;
			  r.set(i, (int)atoi(temp));
			  std::cout << "DOESN'T GET HERE" << std::endl;
		  }
		  else if (i <= 8)
		  {
			  r.set(i, (bool) atoi(temp));
		  }
		  else if (i = 9)
		  {
			  String* s = new String(temp, strlen(temp));
			  r.set(i, s);
		  }
	  }

	  df.add_row(r);

	}
	std::cout << "FINISHED POPULATING DATAFRAME!" << std::endl;
	datafile.close();

	return 0;
}