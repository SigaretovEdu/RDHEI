#include "main.hpp"
#include <gtest/gtest.h>

namespace {

int alpha = 3;
int L1, L2, leftU, rightU;
std::vector<std::vector<int>> buff, labeled, label_map;


	TEST(GET_IMAGE, params) {
		std::string path = "../crop10x10.jpg";
		std::vector<std::vector<int>> buff_ans = { 
			{ 171, 175, 190, 187, 195, 201, 188, 4, 27, 7, 20, 20, 5, 12, 167, 114, 124, 117, 52, 78 },
			{ 18, 9, 0, 11, 0, 4, 5, 204, 162, 123, 115, 47, 40, 158, 0, 1, 13, 6, 10, 4 },
			{ 199, 140, 108, 119, 118, 40, 128, 0, 19, 0, 19, 8, 1, 10, 118, 21, 34, 17, 123, 194 },
			{ 10, 6, 14, 19, 8, 10, 7, 160, 26, 21, 26, 62, 217, 139, 4, 6, 20, 2, 18, 3 },
			{ 175, 60, 26, 30, 26, 184, 162, 1, 0, 10, 7, 5, 0, 9, 11, 28, 62, 30, 53, 194 },
			{ 1, 4, 9, 16, 19, 11, 8, 54, 9, 108, 19, 50, 204, 194, 9, 0, 14, 4, 2, 8 }, 
			{ 171, 27, 105, 22, 13, 144, 188, 22, 15, 4, 5, 28, 18, 4, 22, 33, 48, 43, 19, 219 },
			{ 10, 3, 31, 5, 6, 11, 2, 20, 127, 72, 38, 8, 170, 247, 11, 19, 3, 0, 15, 12 }, 
			{ 53, 67, 97, 24, 21, 66, 252, 10, 1, 15, 21, 20, 24, 6, 174, 39, 9, 91, 51, 227 },
			{ 14, 29, 16, 15, 15, 15, 2, 97, 216, 15, 105, 36, 221, 221, 6, 10, 10, 6, 21, 8 },
			{ 48, 185, 50, 49, 58, 152, 225, 20, 14, 31, 26, 16, 8, 9, 152, 194, 71, 65, 108, 204 },
			{ 2, 1, 9, 4, 7, 7, 7, 53, 230, 5, 70, 98, 150, 216, 15, 7, 7, 11, 11, 7 },
			{ 73, 227, 51, 88, 146, 111, 233, 0, 5, 18, 29, 16, 8, 13, 145, 232, 237, 126, 152, 203 },
			{ 14, 9, 9, 16, 11, 10, 7, 183, 192, 231, 163, 168, 185, 210, 9, 5, 2, 23, 22, 19 }, 
			{ 192, 141, 223, 201, 111, 166, 211, 23, 28, 7, 9, 9, 14, 6, 203, 210, 159, 161, 154, 190 },
			{ 14, 3, 13, 15, 44, 1, 15, 199, 211, 194, 143, 158, 180, 206, 10, 11, 19, 18, 10, 9 },
			{ 198, 207, 202, 144, 168, 161, 201, 7, 8, 25, 10, 15, 8, 8, 198, 195, 183, 191, 200, 197 },
			{ 3, 9, 19, 11, 21, 10, 9, 191, 195, 207, 187, 201, 201, 190, 10, 14, 9, 13, 12, 6 },
			{ 185, 198, 200, 185, 197, 196, 192, 5, 18, 4, 13, 15, 8, 6, 0, 0, 2, 0, 0, 0 },
			{ 3, 16, 8, 12, 14, 8, 4, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 180, 85 }
		};

		get_image(path, L1, L2, alpha, buff);

		//EXPECT_EQ(buff, buff_ans);
		EXPECT_EQ(L1, 13);
		EXPECT_EQ(L2, 9);
		//EXPECT_EQ(leftU, -4);
		//EXPECT_EQ(rightU, 3);
	}

	TEST(GENERATION_LABELING, params) {
		buff = {
			{162, 164, 161, 156, 155},
			{164, 163, 163, 156, 159},
			{168, 161, 162, 161, 159},
			{161, 163, 164, 159, 155},
			{163, 162, 163, 160, 156}
		};

		generation_labeling(alpha, buff, labeled, label_map);

		std::vector<std::vector<int>> labeled_ans = {
			{162, 164, 161, 156, 155},
			{164, 161, 167, 155, 157},
			{168, 162, 162, 161, 156},
			{161, 160, 164, 152, 153},
			{163, 162, 165, 165, 156}
		};

		std::vector<std::vector<int>> label_map_ans = {
			{1,1,1,1,1},
			{1,0,0,0,0},
			{1,0,0,0,0},
			{1,0,1,0,0},
			{1,1,0,0,1}
		};

		EXPECT_EQ(labeled, labeled_ans);
		EXPECT_EQ(label_map, label_map_ans);
	}
}
