#define BOOST_TEST_MODULE calc_test
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include "../newCalculator/Kalkulator.h"

namespace tt = boost::test_tools;
namespace utf = boost::unit_test; 

const char* functions[] = { "sin(40)","tg(45)", "tg(30)", "cos(60)" };
double arr[]{ 0.745,1.619,-6.405, -0.952 };
auto ds = boost::unit_test::data::make(functions) ^ boost::unit_test::data::make(arr); 

BOOST_AUTO_TEST_SUITE(calc) 
BOOST_AUTO_TEST_CASE(calc_expr_1)
{
	Kalkulator<int> k;
	std::string expr("2 + 8 - 9 + 1");
	k.Parsing(expr);
	BOOST_TEST(expr == "2",expr);
	expr = "2  * -2 / 10";
	k.Parsing(expr);
	int res = std::stoi(expr);
	BOOST_TEST(res == 0, res);  
}

BOOST_AUTO_TEST_CASE(calc_expr_2, * utf::tolerance(0.1))  
{
	Kalkulator<double> k;
	std::string expr("2 + 8 - 9*0");
	k.Parsing(expr);
	double r = std::stod(expr);
	BOOST_TEST(r == 10.00);
	expr = "2  - -2*2-1/ 1";
	k.Parsing(expr);
	r = std::stod(expr); 
	BOOST_TEST(r == 5.089);
}

BOOST_AUTO_TEST_CASE(calc_expr_3)
{
	Kalkulator<int> k;
	std::string expr(" -9 + (9 * 0)");
	k.Parsing(expr);
	BOOST_TEST(expr == "-9", expr);
	expr = "2  -(-2*(2-1)) - 9";
	k.Parsing(expr);
	int res = std::stoi(expr);
	BOOST_TEST(res == -5, res);
}

BOOST_AUTO_TEST_CASE(calc_expr_4, * utf::tolerance(0.001))
{
	Kalkulator<float> k;
	std::string expr("tg(45)");
	k.Parsing(expr); 
	float r = std::stof(expr);   
	BOOST_TEST(r == 1.61977);
	expr = "sin(90) + cos(45)";
	k.Parsing(expr);
	r = std::stof(expr);
	BOOST_TEST(r == 1.4, tt::tolerance(0.1));  
	expr = "cos(90) * tg(45)";
	k.Parsing(expr); 
	r = std::stof(expr); 
	BOOST_TEST(r == -0.72,tt::tolerance(0.01));
}
BOOST_AUTO_TEST_CASE(calc_expr_5)
{
	Kalkulator<float> k;
	std::string expr("sin(50)+ 6 * 8-9");
	k.Parsing(expr);
	float r = std::stof(expr);
	BOOST_TEST(r == 38.737, tt::tolerance(0.001));
	expr = "tg(45) - sin(50)+ ((8/2)-(9*0))";
	k.Parsing(expr);
	r = std::stof(expr);
	BOOST_TEST(r == 5.882, tt::tolerance(0.001));

}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////

BOOST_AUTO_TEST_SUITE(trygonometry)
BOOST_AUTO_TEST_CASE(trygonometry_expr_1) 
{
	Trygonometry tr;
	std::string expr ("tg(4)");
	int pos = 2;
	auto res = tr.get_trygonometry_Function(expr,pos); //return v --> position of trygonometry function number
	BOOST_TEST(res == 2, res); 
	expr = "45";
	res = tr.get_trygonometry_Function(expr, pos); //
	BOOST_TEST(res == -1, res);
}
BOOST_AUTO_TEST_CASE(trygonometry_expr_2, * utf::tolerance(0.001))
{
	Trygonometry tr;
	std::string expr("cos(45)");
	int pos = 3;
	auto res = tr.get_trygonometry_Function(expr, pos); //return v --> position of trygonometry function number
	BOOST_TEST(tr.calculate_trygonometry_function(res, 45) == 0.525); 

}
BOOST_DATA_TEST_CASE(trygonometry_expr_3, ds,tr_function, results)  
{
	Kalkulator<double> k; 
	std::string expr(tr_function);
	k.Parsing(expr);
	double v = std::stod(expr); 
	BOOST_TEST(v == results, tt::tolerance(0.03));
}
BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(file_reader)
BOOST_AUTO_TEST_CASE(file_reader_test)
{
	Reader r;
	std::string path;
	BOOST_TEST(!r.ReadfromFile(path), "file is not open"); 
	path = "test.txt";
	BOOST_TEST(r.ReadfromFile(path), "file is not open");

}
BOOST_AUTO_TEST_SUITE_END()