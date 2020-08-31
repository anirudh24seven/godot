
/*  compressed_translation.h                                             */



#ifndef COMPRESSED_TRANSLATION_H
#define COMPRESSED_TRANSLATION_H

#include "core/translation.h"

class PHashTranslation : public Translation {
	GDCLASS(PHashTranslation, Translation);

	//this translation uses a sort of modified perfect hash algorithm
	//it requires hashing strings twice and then does a binary search,
	//so it's slower, but at the same time it has an extreemly high chance
	//of catching untranslated strings

	//load/store friendly types
	Vector<int> hash_table;
	Vector<int> bucket_table;
	Vector<uint8_t> strings;

	struct Bucket {
		int size;
		uint32_t func;

		struct Elem {
			uint32_t key;
			uint32_t str_offset;
			uint32_t comp_size;
			uint32_t uncomp_size;
		};

		Elem elem[1];
	};

	_FORCE_INLINE_ uint32_t hash(uint32_t d, const char *p_str) const {
		if (d == 0) {
			d = 0x1000193;
		}
		while (*p_str) {
			d = (d * 0x1000193) ^ uint32_t(*p_str);
			p_str++;
		}

		return d;
	}

protected:
	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;
	static void _bind_methods();

public:
	virtual StringName get_message(const StringName &p_src_text, const StringName &p_context = "") const override; //overridable for other implementations
	virtual StringName get_plural_message(const StringName &p_src_text, const StringName &p_plural_text, int p_n, const StringName &p_context = "") const override;
	void generate(const Ref<Translation> &p_from);

	PHashTranslation() {}
};

#endif // COMPRESSED_TRANSLATION_H
