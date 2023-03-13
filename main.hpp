#pragma once

#ifndef HEADERS
#define HEADERS

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/matx.hpp>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <pthread.h>



void get_image(const std::string, int&, int&, int&, std::vector<std::vector<int>>&);


template<typename Type>
void printvec(const std::vector<std::vector<Type>>& vec);


template<typename Type>
void printvec(const std::vector<std::vector<Type>>& vec, const size_t& y, const size_t& x);


void printvec(const std::vector<std::vector<char>>& vec);


void printvec(const std::vector<std::vector<char>>& vec, const size_t& y, const size_t& x);


void generation_labeling(int&, std::vector<std::vector<int>>&, std::vector<std::vector<int>>&, std::vector<std::vector<int>>&);

/*
size_t Height;
size_t Weight;
int L1;
int L2;
int alpha = 3;
int leftU, rightU;
std::vector<std::vector<int>> buff;
std::vector<std::vector<int>> labeled;
std::vector<std::vector<int>> label_map;
*/
#endif
