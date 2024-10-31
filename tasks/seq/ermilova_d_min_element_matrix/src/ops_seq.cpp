// Copyright 2024 Nesterov Alexander
#include "seq/ermilova_d_min_element_matrix/include/ops_seq.hpp"

#include <algorithm>
#include <functional>
#include <random>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

bool ermilova_d_min_element_matrix_seq::TestTaskSequential::pre_processing() {
  internal_order_test();
  // Init value for input and output
  rows = taskData->inputs_count[0];
  cols = taskData->inputs_count[1];

  input_.resize(rows, std::vector<int>(cols));

  for (int i = 0; i < rows; i++) {
    auto* tpr_ptr = reinterpret_cast<int*>(taskData->inputs[i]);
    for (int j = 0; j < cols; j++) {
      input_[i][j] = tpr_ptr[j];
    }
  }

  // Init value for output
  res = INT_MAX;
  return true;
}

bool ermilova_d_min_element_matrix_seq::TestTaskSequential::validation() {
  internal_order_test();
  // Check count elements of output

  return taskData->outputs_count[0] == 1 && taskData->inputs_count[0] > 0 && taskData->inputs_count[1] > 0;
}

bool ermilova_d_min_element_matrix_seq::TestTaskSequential::run() {
  internal_order_test();
  for (size_t i = 0; i < input_.size(); i++) {
    for (size_t = 0; j < input_[i].size(); j++) {
      if (res > input_[i][j]) {
        res = input_[i][j];
      }
    }
  }
  return true;
}

bool ermilova_d_min_element_matrix_seq::TestTaskSequential::post_processing() {
  internal_order_test();
  reinterpret_cast<int*>(taskData->outputs[0])[0] = res;
  return true;
}

std::vector<int> ermilova_d_min_element_matrix_seq::getRandomVector(int size, int upper_border, int lower_border) {
  std::random_device dev;
  std::mt19937 gen(dev());
  if (sz <= 0) throw "Incorrect size";
  std::vector<int> vec(sz);
  for (int i = 0; i < sz; i++) {
    vec[i] = lower_border + gen() % (upper_border - lower_border + 1);
  }
  return vec;
}

std::vector<std::vector<int>> ermilova_d_min_element_matrix_seq::getRandomMatrix(int rows, int cols, int upper_border,
                                                                                 int lower_border) {
  if (rows <= 0 || cols <= 0) throw "Incorrect size";
  std::vector<std::vector<int>> vec(rows);
  for (int i = 0; i < rows; i++) {
    vec[i] = ermilova_d_min_element_matrix_seq::getRandomVector(cols, upper_border, lower_border);
  }
  return vec;
}