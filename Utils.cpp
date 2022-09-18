#include <iostream>
#include <string>
using namespace std;

static void PrintLine(string message) {
	cout << message << endl;
};

//
// static void HRManager(HRESULT hr, std::string errorMessage)
// {
// 	if (FAILED(hr))
// 	{
// 		std::cout << "FAILED : " << errorMessage << std::endl;
// 	}
// 	else if (hr == S_OK)
// 	{
// 		std::cout << "SUCCESS: " << errorMessage << std::endl;
// 	}
// }