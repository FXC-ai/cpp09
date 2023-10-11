#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>

class Display
{
	public :
		template <typename T>
		void operator()(T & a)
		{
			std::cout << a << " - ";
		}
};

int main()
{
	std::ifstream csv_file("data.csv");
	// std::vector<std::string> datas;

	std::istream_iterator<std::string> it(csv_file);
	std::istream_iterator<std::string> end;


	while (it!=end)
	{


		std::stringstream ss(*it);
    	std::string date;
		while (!ss.eof())
		{
			getline(ss, date, ',');
			std::cout << date << std::endl;
		}

		++it;
	}


	// std::back_insert_iterator<std::vector<std::string> > back_insert_it(datas);

	// copy(it, end, back_insert_it);

	// for_each(datas.begin(), datas.end(), Display());

	// for (std::vector<std::string>::iterator it_v = datas.begin(); it_v!=datas.end(); ++it_v)
	// {
	// 	std::stringstream ss(*it_v);
	// 	std::string date;
	// 	getline(ss, date, ',');
	// 	std::cout << date << " * ";
	// }
	


	return 0;
}