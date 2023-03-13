#include "main.hpp"
#include <cstddef>
#include <gtest/gtest.h>
#include <ios>
#include <opencv2/imgcodecs.hpp>
#include <vector>


int main() {
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}


void get_image(const std::string path, int& L1, int& L2, int& alpha, std::vector<std::vector<int>>& buff) {
	std::string image_path = cv::samples::findFile(path);
	cv::Mat img = imread(image_path, cv::IMREAD_GRAYSCALE);
    if(img.empty())
        throw std::runtime_error("~Could not read the image~");
    //imshow("Display window", img);
	//cv::moveWindow("Display window", 0, 0);
    //int k = cv::waitKey(0); // Wait for a keystroke in the window
	size_t Height = static_cast<size_t>(img.rows);
	size_t Weight = static_cast<size_t>(img.cols);
	L1 = std::ceil(std::log2(7)) + std::ceil(std::log2(Height)) + std::ceil(std::log2(Weight));
	L2 = std::ceil(std::log2(Height * Weight));
	int leftU = -1 * std::pow(2, alpha - 1);
	int rightU = std::pow(2, alpha - 1) - 1;

	buff.resize(Height, std::vector<int>(Weight));
	for(int i = 0; i < img.rows; ++i) {
		for(int j = 0; j < img.cols; ++j) {
			buff[i][j] = static_cast<int>(img.at<cv::Vec3b>(i, j)[0]);
		}
	}
}

template<typename Type>
void printvec(const std::vector<std::vector<Type>>& vec) {
	for(size_t i = 0; i < vec.size(); ++i) {
		for(size_t j = 0; j < vec[0].size(); ++j) {
			std::cout<<vec[i][j]<<' ';
		}
		std::cout<<'\n';
	}
}

template<typename Type>
void printvec(const std::vector<std::vector<Type>>& vec, const size_t& y, const size_t& x) {
	for(size_t i = 0; i < y; ++i) {
		for(size_t j = 0; j < x; ++j) {
			std::cout<<vec[i][j]<<' ';
		}
		std::cout<<'\n';
	}
}


void printvec(const std::vector<std::vector<char>>& vec) {
	for(size_t i = 0; i < vec.size(); ++i) {
		for(size_t j = 0; j < vec[0].size(); ++j) {
			std::cout<<static_cast<int>(vec[i][j])<<' ';
		}
		std::cout<<'\n';
	}
}

void printvec(const std::vector<std::vector<char>>& vec, const size_t& y, const size_t& x) {
	for(size_t i = 0; i < y; ++i) {
		for(size_t j = 0; j < x; ++j) {
			std::cout<<static_cast<int>(vec[i][j])<<' ';
		}
		std::cout<<'\n';
	}
}


void generation_labeling(int& alpha, std::vector<std::vector<int>>& buff, std::vector<std::vector<int>>& labeled, std::vector<std::vector<int>>& label_map) {
	labeled.resize(buff.size(), std::vector<int>(buff[0].size()));
	for(size_t i = 0; i < buff.size(); ++i)
		labeled[i][0] = buff[i][0];
	for(size_t i = 0; i < buff[0].size(); ++i)
		labeled[0][i] = buff[0][i];

	label_map.resize(buff.size(), std::vector<int>(buff[0].size(), 1));
	int leftU = -1 * std::pow(2, alpha - 1);
	int rightU = std::pow(2, alpha - 1) - 1;
	std::cout<<leftU<<' '<<rightU<<'\n';

	std::vector<std::vector<std::pair<int, int>>> logtable;
	logtable.resize(buff.size(), std::vector<std::pair<int, int>>(buff[0].size()));

	for(size_t i = 1; i < buff.size(); ++i) {
		for(size_t j = 1; j < buff[0].size(); ++j) {
			int v;
			if(buff[i-1][j-1] <= std::min(buff[i-1][j], buff[i][j-1])) {
				v = std::max(buff[i-1][j], buff[i][j-1]);
			} else if(buff[i-1][j-1] >= std::max(buff[i-1][j], buff[i][j-1])) {
				v = std::min(buff[i-1][j], buff[i][j-1]);
			} else {
				v = buff[i-1][j] + buff[i][j-1] - buff[i-1][j-1];
			}
			int e = buff[i][j] - v;
			
			logtable[i][j].first = e;

			if(leftU <= e && e <= rightU) {
				label_map[i][j] = 0;
				int new_p = 0, new_e = 0;
				if(buff[i][j] != 0)
					new_p = 255 ^ (buff[i][j] - 1);

				if(e > 0) {
					new_e = 255 ^ (e - 1);
				} else if(e < 0) {
					int al2 = std::pow(2, alpha);
					int k = 1;
					for(int l = 0; l < 8; ++l) {
						new_e = new_e + (((static_cast<int>((al2 + e) / k)) % 2) << l);
						k *= 2;
					}
				}
				new_e = new_e & static_cast<int>(std::pow(2, alpha) - 1);
				
				logtable[i][j].second = new_e;

				labeled[i][j] = (new_p & (255 - ((1 << alpha) - 1))) + e;
			} else {
				labeled[i][j] = buff[i][j];
			}
		}
	}

	for(size_t i = 0; i < logtable.size(); ++i) {
		for(size_t j = 0; j < logtable[0].size(); ++j) {
			std::cout<<logtable[i][j].first<<' '<<logtable[i][j].second<<'\t';
		}
		std::cout<<'\n';
	}

}
