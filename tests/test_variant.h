
/*  test_variant.h                                                       */



#ifndef TEST_VARIANT_H
#define TEST_VARIANT_H

#include "core/variant.h"
#include "core/variant_parser.h"

#include "tests/test_macros.h"

namespace TestVariant {

TEST_CASE("[Variant] Writer and parser integer") {
	int64_t a32 = 2147483648; // 2^31, so out of bounds for 32-bit signed int [-2^31,-2^31-1].
	String a32_str;
	VariantWriter::write_to_string(a32, a32_str);

	CHECK_MESSAGE(a32_str != "-2147483648", "Should not wrap around");

	int64_t b64 = 9223372036854775807; // 2^63-1, upper bound for signed 64-bit int.
	String b64_str;
	VariantWriter::write_to_string(b64, b64_str);

	CHECK_MESSAGE(b64_str == "9223372036854775807", "Should not wrap around.");

	VariantParser::StreamString ss;
	String errs;
	int line;
	Variant b64_parsed;
	int64_t b64_int_parsed;

	ss.s = b64_str;
	VariantParser::parse(&ss, b64_parsed, errs, line);
	b64_int_parsed = b64_parsed;

	CHECK_MESSAGE(b64_int_parsed == 9223372036854775807, "Should parse back.");

	ss.s = "9223372036854775808"; // Overflowed by one.
	VariantParser::parse(&ss, b64_parsed, errs, line);
	b64_int_parsed = b64_parsed;

	CHECK_MESSAGE(b64_int_parsed == 9223372036854775807, "The result should be clamped to max value.");

	ss.s = "1e100"; // Googol! Scientific notation.
	VariantParser::parse(&ss, b64_parsed, errs, line);
	b64_int_parsed = b64_parsed;

	CHECK_MESSAGE(b64_int_parsed == 9223372036854775807, "The result should be clamped to max value.");
}

TEST_CASE("[Variant] Writer and parser float") {
	// Assuming real_t is double.
	real_t a64 = 340282346638528859811704183484516925440.0; // std::numeric_limits<real_t>::max()
	String a64_str;
	VariantWriter::write_to_string(a64, a64_str);

	CHECK_MESSAGE(a64_str == "3.40282e+38", "Writes in scientific notation.");
	CHECK_MESSAGE(a64_str != "inf", "Should not overflow.");
	CHECK_MESSAGE(a64_str != "nan", "The result should be defined.");

	VariantParser::StreamString ss;
	String errs;
	int line;
	Variant b64_parsed;
	real_t b64_float_parsed;

	ss.s = a64_str;
	VariantParser::parse(&ss, b64_parsed, errs, line);
	b64_float_parsed = b64_parsed;

	CHECK_MESSAGE(b64_float_parsed == 340282001837565597733306976381245063168.0, "Should parse back.");
	// Loses precision, but that's alright.

	ss.s = "1.0e+100"; // Float version of Googol!
	VariantParser::parse(&ss, b64_parsed, errs, line);
	b64_float_parsed = b64_parsed;

	CHECK_MESSAGE(b64_float_parsed == 340282001837565597733306976381245063168.0, "Should not overflow.");
}

} // namespace TestVariant

#endif // TEST_VARIANT_H
