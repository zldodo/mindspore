/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ut/tools/converter/parser/tflite/tflite_parsers_test_utils.h"
#include <iostream>
#include "common/common_test.h"

namespace mindspore {
class TestTfliteParserSparseToDense : public TestTfliteParser {
 public:
  TestTfliteParserSparseToDense() {}
  void SetUp() override {
    meta_graph = LoadAndConvert("./sparse_to_dense.tflite");
  }
};

TEST_F(TestTfliteParserSparseToDense, OpType) {
  ASSERT_NE(meta_graph, nullptr);
  ASSERT_GT(meta_graph->nodes.size(), 0);
  ASSERT_NE(meta_graph->nodes.front()->primitive.get(), nullptr);
  ASSERT_EQ(meta_graph->nodes.front()->primitive->value.type, schema::PrimitiveType_SparseToDense) << "wrong Op Type";
}

TEST_F(TestTfliteParserSparseToDense, AttrValue) {
  std::vector<int> outputShape{5, 5};
  std::vector<int> sparseValue{1};
  std::vector<int> defaultValue{0};
  ASSERT_NE(meta_graph, nullptr);
  ASSERT_GT(meta_graph->nodes.size(), 0);
  ASSERT_NE(meta_graph->nodes.front()->primitive.get(), nullptr);
  ASSERT_NE(meta_graph->nodes.front()->primitive->value.AsSparseToDense(), nullptr);
  ASSERT_EQ(meta_graph->nodes.front()->primitive->value.AsSparseToDense()->outputShape, outputShape);
  ASSERT_EQ(meta_graph->nodes.front()->primitive->value.AsSparseToDense()->sparseValue, sparseValue);
  ASSERT_EQ(meta_graph->nodes.front()->primitive->value.AsSparseToDense()->defaultValue, defaultValue);
  ASSERT_EQ(meta_graph->nodes.front()->primitive->value.AsSparseToDense()->validateIndices, false);
}
}  // namespace mindspore