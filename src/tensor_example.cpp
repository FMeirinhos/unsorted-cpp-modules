//
//  tensor_example.cpp
//  SB+LMF
//
//  Created by Francisco Meirinhos on 20/04/2017.
//  Copyright © 2017 meirinhos. All rights reserved.
//

#include "tensor.hpp"

#include <iostream>
#include <vector>

int main() {
  const size_t size = 16;
  std::vector<double> vec(size);

  Tensor<decltype(vec), 2, 2, 2, 2> tensor(vec);

  tensor(0, 0, 0, 0) = 1;
  tensor(1, 0, 1, 0) = 2;
  tensor(0, 1, 1, 1) = 99;

  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << i << "\t" << vec[i] << std::endl;
  }
  return 0;
}
