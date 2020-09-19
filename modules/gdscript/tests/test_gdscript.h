
/*  test_gdscript.h                                                      */

#ifndef TEST_GDSCRIPT_H
#define TEST_GDSCRIPT_H

namespace TestGDScript {

enum TestType {
	TEST_TOKENIZER,
	TEST_PARSER,
	TEST_COMPILER,
	TEST_BYTECODE,
};

void test(TestType p_type);

} // namespace TestGDScript

#endif // TEST_GDSCRIPT_H
