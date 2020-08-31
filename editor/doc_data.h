
/*  doc_data.h                                                           */



#ifndef DOC_DATA_H
#define DOC_DATA_H

#include "core/io/xml_parser.h"
#include "core/map.h"
#include "core/variant.h"

class DocData {
public:
	struct ArgumentDoc {
		String name;
		String type;
		String enumeration;
		String default_value;
		bool operator<(const ArgumentDoc &p_arg) const {
			return name < p_arg.name;
		}
	};

	struct MethodDoc {
		String name;
		String return_type;
		String return_enum;
		String qualifiers;
		String description;
		Vector<ArgumentDoc> arguments;
		bool operator<(const MethodDoc &p_method) const {
			return name < p_method.name;
		}
	};

	struct ConstantDoc {
		String name;
		String value;
		bool is_value_valid;
		String enumeration;
		String description;
		bool operator<(const ConstantDoc &p_const) const {
			return name < p_const.name;
		}
	};

	struct PropertyDoc {
		String name;
		String type;
		String enumeration;
		String description;
		String setter, getter;
		String default_value;
		bool overridden = false;
		bool operator<(const PropertyDoc &p_prop) const {
			return name < p_prop.name;
		}
	};

	struct TutorialDoc {
		String link;
		String title;
	};

	struct ClassDoc {
		String name;
		String inherits;
		String category;
		String brief_description;
		String description;
		Vector<TutorialDoc> tutorials;
		Vector<MethodDoc> methods;
		Vector<MethodDoc> signals;
		Vector<ConstantDoc> constants;
		Vector<PropertyDoc> properties;
		Vector<PropertyDoc> theme_properties;
		bool operator<(const ClassDoc &p_class) const {
			return name < p_class.name;
		}
	};

	String version;

	Map<String, ClassDoc> class_list;
	Error _load(Ref<XMLParser> parser);

public:
	void merge_from(const DocData &p_data);
	void remove_from(const DocData &p_data);
	void generate(bool p_basic_types = false);
	Error load_classes(const String &p_dir);
	static Error erase_classes(const String &p_dir);
	Error save_classes(const String &p_default_path, const Map<String, String> &p_class_path);

	Error load_compressed(const uint8_t *p_data, int p_compressed_size, int p_uncompressed_size);
};

#endif // DOC_DATA_H
