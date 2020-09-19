
/*  string_name.cpp                                                      */

#include "string_name.h"

#include "core/os/os.h"
#include "core/print_string.h"

StaticCString StaticCString::create(const char *p_ptr) {
	StaticCString scs;
	scs.ptr = p_ptr;
	return scs;
}

StringName::_Data *StringName::_table[STRING_TABLE_LEN];

StringName _scs_create(const char *p_chr) {
	return (p_chr[0] ? StringName(StaticCString::create(p_chr)) : StringName());
}

bool StringName::configured = false;
Mutex StringName::mutex;

void StringName::setup() {
	ERR_FAIL_COND(configured);
	for (int i = 0; i < STRING_TABLE_LEN; i++) {
		_table[i] = nullptr;
	}
	configured = true;
}

void StringName::cleanup() {
	MutexLock lock(mutex);

	int lost_strings = 0;
	for (int i = 0; i < STRING_TABLE_LEN; i++) {
		while (_table[i]) {
			_Data *d = _table[i];
			lost_strings++;
			if (OS::get_singleton()->is_stdout_verbose()) {
				if (d->cname) {
					print_line("Orphan StringName: " + String(d->cname));
				} else {
					print_line("Orphan StringName: " + String(d->name));
				}
			}

			_table[i] = _table[i]->next;
			memdelete(d);
		}
	}
	if (lost_strings) {
		print_verbose("StringName: " + itos(lost_strings) + " unclaimed string names at exit.");
	}
}

void StringName::unref() {
	ERR_FAIL_COND(!configured);

	if (_data && _data->refcount.unref()) {
		MutexLock lock(mutex);

		if (_data->prev) {
			_data->prev->next = _data->next;
		} else {
			if (_table[_data->idx] != _data) {
				ERR_PRINT("BUG!");
			}
			_table[_data->idx] = _data->next;
		}

		if (_data->next) {
			_data->next->prev = _data->prev;
		}
		memdelete(_data);
	}

	_data = nullptr;
}

bool StringName::operator==(const String &p_name) const {
	if (!_data) {
		return (p_name.length() == 0);
	}

	return (_data->get_name() == p_name);
}

bool StringName::operator==(const char *p_name) const {
	if (!_data) {
		return (p_name[0] == 0);
	}

	return (_data->get_name() == p_name);
}

bool StringName::operator!=(const String &p_name) const {
	return !(operator==(p_name));
}

bool StringName::operator!=(const StringName &p_name) const {
	// the real magic of all this mess happens here.
	// this is why path comparisons are very fast
	return _data != p_name._data;
}

void StringName::operator=(const StringName &p_name) {
	if (this == &p_name) {
		return;
	}

	unref();

	if (p_name._data && p_name._data->refcount.ref()) {
		_data = p_name._data;
	}
}

StringName::StringName(const StringName &p_name) {
	_data = nullptr;

	ERR_FAIL_COND(!configured);

	if (p_name._data && p_name._data->refcount.ref()) {
		_data = p_name._data;
	}
}

StringName::StringName(const char *p_name) {
	_data = nullptr;

	ERR_FAIL_COND(!configured);

	if (!p_name || p_name[0] == 0) {
		return; //empty, ignore
	}

	MutexLock lock(mutex);

	uint32_t hash = String::hash(p_name);

	uint32_t idx = hash & STRING_TABLE_MASK;

	_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}
		_data = _data->next;
	}

	if (_data) {
		if (_data->refcount.ref()) {
			// exists
			return;
		}
	}

	_data = memnew(_Data);
	_data->name = p_name;
	_data->refcount.init();
	_data->hash = hash;
	_data->idx = idx;
	_data->cname = nullptr;
	_data->next = _table[idx];
	_data->prev = nullptr;
	if (_table[idx]) {
		_table[idx]->prev = _data;
	}
	_table[idx] = _data;
}

StringName::StringName(const StaticCString &p_static_string) {
	_data = nullptr;

	ERR_FAIL_COND(!configured);

	ERR_FAIL_COND(!p_static_string.ptr || !p_static_string.ptr[0]);

	MutexLock lock(mutex);

	uint32_t hash = String::hash(p_static_string.ptr);

	uint32_t idx = hash & STRING_TABLE_MASK;

	_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_static_string.ptr) {
			break;
		}
		_data = _data->next;
	}

	if (_data) {
		if (_data->refcount.ref()) {
			// exists
			return;
		}
	}

	_data = memnew(_Data);

	_data->refcount.init();
	_data->hash = hash;
	_data->idx = idx;
	_data->cname = p_static_string.ptr;
	_data->next = _table[idx];
	_data->prev = nullptr;
	if (_table[idx]) {
		_table[idx]->prev = _data;
	}
	_table[idx] = _data;
}

StringName::StringName(const String &p_name) {
	_data = nullptr;

	ERR_FAIL_COND(!configured);

	if (p_name == String()) {
		return;
	}

	MutexLock lock(mutex);

	uint32_t hash = p_name.hash();
	uint32_t idx = hash & STRING_TABLE_MASK;

	_data = _table[idx];

	while (_data) {
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}
		_data = _data->next;
	}

	if (_data) {
		if (_data->refcount.ref()) {
			// exists
			return;
		}
	}

	_data = memnew(_Data);
	_data->name = p_name;
	_data->refcount.init();
	_data->hash = hash;
	_data->idx = idx;
	_data->cname = nullptr;
	_data->next = _table[idx];
	_data->prev = nullptr;
	if (_table[idx]) {
		_table[idx]->prev = _data;
	}
	_table[idx] = _data;
}

StringName StringName::search(const char *p_name) {
	ERR_FAIL_COND_V(!configured, StringName());

	ERR_FAIL_COND_V(!p_name, StringName());
	if (!p_name[0]) {
		return StringName();
	}

	MutexLock lock(mutex);

	uint32_t hash = String::hash(p_name);
	uint32_t idx = hash & STRING_TABLE_MASK;

	_Data *_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}
		_data = _data->next;
	}

	if (_data && _data->refcount.ref()) {
		return StringName(_data);
	}

	return StringName(); //does not exist
}

StringName StringName::search(const char32_t *p_name) {
	ERR_FAIL_COND_V(!configured, StringName());

	ERR_FAIL_COND_V(!p_name, StringName());
	if (!p_name[0]) {
		return StringName();
	}

	MutexLock lock(mutex);

	uint32_t hash = String::hash(p_name);

	uint32_t idx = hash & STRING_TABLE_MASK;

	_Data *_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}
		_data = _data->next;
	}

	if (_data && _data->refcount.ref()) {
		return StringName(_data);
	}

	return StringName(); //does not exist
}

StringName StringName::search(const String &p_name) {
	ERR_FAIL_COND_V(p_name == "", StringName());

	MutexLock lock(mutex);

	uint32_t hash = p_name.hash();

	uint32_t idx = hash & STRING_TABLE_MASK;

	_Data *_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && p_name == _data->get_name()) {
			break;
		}
		_data = _data->next;
	}

	if (_data && _data->refcount.ref()) {
		return StringName(_data);
	}

	return StringName(); //does not exist
}

StringName::~StringName() {
	unref();
}
