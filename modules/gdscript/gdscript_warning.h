
/*  gdscript_warning.h                                                   */

#ifndef GDSCRIPT_WARNINGS
#define GDSCRIPT_WARNINGS

#ifdef DEBUG_ENABLED

#include "core/ustring.h"
#include "core/vector.h"

class GDScriptWarning {
public:
	enum Code {
		UNASSIGNED_VARIABLE, // Variable used but never assigned.
		UNASSIGNED_VARIABLE_OP_ASSIGN, // Variable never assigned but used in an assignment operation (+=, *=, etc).
		UNUSED_VARIABLE, // Local variable is declared but never used.
		UNUSED_LOCAL_CONSTANT, // Local constant is declared but never used.
		SHADOWED_VARIABLE, // Variable name shadowed by other variable in same class.
		SHADOWED_VARIABLE_BASE_CLASS, // Variable name shadowed by other variable in some base class.
		UNUSED_PRIVATE_CLASS_VARIABLE, // Class variable is declared private ("_" prefix) but never used in the file.
		UNUSED_PARAMETER, // Function parameter is never used.
		UNREACHABLE_CODE, // Code after a return statement.
		UNREACHABLE_PATTERN, // Pattern in a match statement after a catch all pattern (wildcard or bind).
		STANDALONE_EXPRESSION, // Expression not assigned to a variable.
		VOID_ASSIGNMENT, // Function returns void but it's assigned to a variable.
		NARROWING_CONVERSION, // Float value into an integer slot, precision is lost.
		INCOMPATIBLE_TERNARY, // Possible values of a ternary if are not mutually compatible.
		UNUSED_SIGNAL, // Signal is defined but never emitted.
		RETURN_VALUE_DISCARDED, // Function call returns something but the value isn't used.
		PROPERTY_USED_AS_FUNCTION, // Function not found, but there's a property with the same name.
		CONSTANT_USED_AS_FUNCTION, // Function not found, but there's a constant with the same name.
		FUNCTION_USED_AS_PROPERTY, // Property not found, but there's a function with the same name.
		INTEGER_DIVISION, // Integer divide by integer, decimal part is discarded.
		UNSAFE_PROPERTY_ACCESS, // Property not found in the detected type (but can be in subtypes).
		UNSAFE_METHOD_ACCESS, // Function not found in the detected type (but can be in subtypes).
		UNSAFE_CAST, // Cast used in an unknown type.
		UNSAFE_CALL_ARGUMENT, // Function call argument is of a supertype of the require argument.
		DEPRECATED_KEYWORD, // The keyword is deprecated and should be replaced.
		STANDALONE_TERNARY, // Return value of ternary expression is discarded.
		ASSERT_ALWAYS_TRUE, // Expression for assert argument is always true.
		ASSERT_ALWAYS_FALSE, // Expression for assert argument is always false.
		REDUNDANT_AWAIT, // await is used but expression is synchronous (not a signal nor a coroutine).
		WARNING_MAX,
	};

	Code code = WARNING_MAX;
	int start_line = -1, end_line = -1;
	int leftmost_column = -1, rightmost_column = -1;
	Vector<String> symbols;

	String get_name() const;
	String get_message() const;
	static String get_name_from_code(Code p_code);
	static Code get_code_from_name(const String &p_name);
};

#endif // DEBUG_ENABLED

#endif // GDSCRIPT_WARNINGS
