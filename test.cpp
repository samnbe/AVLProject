//#include "../src/main.cpp"
//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
//
/////*
////	To check output (At the Project1 directory):
////		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
////*/
////
////TEST_CASE("AVL Insert Improper", "[format]") {
////	AVL tree;
////	tree.Insert("A11y Gator", 11111111);
////	tree.Insert("Ally Gator", 111111122);
//	tree.Insert("Ally Gator", "11s111s1");
//	tree.Insert("Ally Gator", 1111111);
//	tree.Insert("Ally Gat0r", 11111111); 
//
//	std::vector<string> actualOutput = printInorder();  
//	std::vector<string> expectedOutput = {};
//	REQUIRE(actualOutput.size() == expectedOutput.size());
//	REQUIRE(actualOutput == expectedOutput); 
//}
//
//TEST_CASE("AVL Edge Cases", "[edges]") {
//	AVL tree; 
//	tree.RemoveID(11111112);
//	tree.SearchID(55555555);
//	tree.SearchName("Ally Gator"); 
//
//	std::vector<string> actualOutput = printInorder(); 
//	std::vector<string> expectedOutput = {}; 
//	REQUIRE(actualOutput.size() == expectedOutput.size());
//	REQUIRE(actualOutput == expectedOutput);
//}
//
//TEST_CASE("AVL Rotation Test", "[rotations]") {
//	AVL tree;
//	tree.Insert("a", 48754592);
//	tree.Insert("b", 90765792);
//	tree.Insert("c", 67890321); 
//	tree.Insert("d", 76543134); 
//	tree.Insert("e", 86543219);
//	tree.Insert("f", 38763690);
//	tree.Insert("g", 23764867); 
//	tree.Insert("h", 95657383); 
//	tree.Insert("i", 98758398); 
//
//	std::vector<string> actualOutput = printPreorder();
//	std::vector<string> expectedOutput = {"c", "f", "g", "a", "e", "d", "h", "b", "i"};
//	REQUIRE(actualOutput.size() == expectedOutput.size());
//	REQUIRE(actualOutput == expectedOutput);
//}
//
//TEST_CASE("AVL Deletion Test", "[deletions]") {
//	AVL tree;
//	tree.Insert("a", 68754592);
//	tree.Insert("b", 40765792);
//	tree.Insert("c", 87890321);
//	tree.Insert("d", 76543134);
//	tree.Insert("e", 96543219);
//	tree.Insert("f", 38763690);
//	tree.Insert("g", 53764867);
//	tree.Insert("h", 25657383);
//	tree.RemoveID(87890321); //2 children
//	tree.RemoveID(38763690); //1 child
//	tree.RemoveID(53764867); //no chilren
//
//	std::vector<string> actualOutput = printPreorder();
//	std::vector<string> expectedOutput = { "a", "b", "h", "d", "e"};
//	REQUIRE(actualOutput.size() == expectedOutput.size());
//	REQUIRE(actualOutput == expectedOutput);
//}
//
//TEST_CASE("AVL Loop", "[loop]") {
//	AVL tree;
//	std::vector<int> expectedOutput, actualOutput;
//
//	for (int i = 0; i < 100; i++) {
//		int randomInput = rand();
//		if (std::count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0) {
//			expectedOutput.push_back(randomInput);
//			tree.Insert(randomInput);
//		}
//	}
//
//	for (int x = 0; x < 10; x++) {
//		int randomInput = rand() % 100;
//		if (std::count(expectedOutput.begin(), expectedOutput.end(), randomInput) != 0) {
//			expectedOutput.erase(std::remove(expectedOutput.begin(), expectedOutput.end(), randomInput));
//			tree.RemoveInorderN(randomInput);
//		}
//	}
//
//	actualOutput = printInorder();
//	REQUIRE(actualOutput.size() == expectedOutput.size());
//	std::sort(expectedOutput.begin(), expectedOutput.end());
//	REQUIRE(actualOutput == expectedOutput);
//}