#include "list.h"
#include "algorithm"






//  ---  Member functions   ---  //


task::list::list() : _begin(nullptr), _end(nullptr), _size(0) {};

task::list::list(const list& other) : list() {
	*this = other;
};

task::list::list(size_t count, const int& value) : list() {
	for (int i = 0; i < count; i++) {
		push_back(value);
	}
};

task::list::~list() {
	clear();
};


task::list& task::list::operator=(const list& other) {
	if(this == &other){
		return *this;
	}

	clear();

	for (auto item = other._begin; item != nullptr; item = item->next_item) {
		push_back(item->value);
	}

	return *this;
};






//  ---  Element access  ---  //


int& task::list::front() {
	return _begin->value;
};

const int& task::list::front() const {
	return _begin->value;
};


int& task::list::back() {
	return _end->value;
};

const int& task::list::back() const {
	return _end->value;
};






//  ---  Capacity  ---  //


bool task::list::empty() const {
	return size() == 0;
};

size_t task::list::size() const {
	return _size;
};






//  ---  Modifiers  ---  //


void task::list::push_back(const int& value) {
	_insert_value(value, _end, nullptr);
};

void task::list::pop_back() {
	_pop_item(_end);
};


void task::list::push_front(const int& value) {
	_insert_value(value, nullptr, _begin);
};

void task::list::pop_front() {
	_pop_item(_begin);
};


void task::list::resize(size_t count, const int& value) {
	while (count != size()) {
		if (count > size()) {
			push_back(int());
		}
		else {
			pop_back();
		}
	}
};

void task::list::swap(list& other) {
	std::swap(_begin, other._begin);
	std::swap(_end, other._end);
	std::swap(_size, other._size);
};

void task::list::clear() {
	while (size()) {
		pop_back();
	}
};






//  ---  Operations  ---  //


void task::list::remove(const int& value) {

	// If value stored in this list
	// we must save pointer to an item with given value and delete it last
	list_item* value_ptr = nullptr;

	for (auto item = _begin; item != nullptr; ) {
		auto next = item->next_item;

		if (item->value == value) {
			if (&item->value == &value) {
				value_ptr = item; // Save pointer if it is given value
			}
			else {
				_pop_item(item);  // Delete item if it is not
			}
		}

		item = next;
	}

	// Finally delete the item with given value
	_pop_item(value_ptr);
};

void task::list::unique() {
	for (auto item = _begin; item != nullptr; item = item->next_item) {

		// Delete next values while they are the same as the current
		while (item->next_item != nullptr && item->value == item->next_item->value) {
			_pop_item(item->next_item);
		}
	}
};

void task::list::sort() { // Simple bubble sort implementation
	bool sorted;

	do {
		sorted = true;

		for (auto item = _begin; item != nullptr; item = item->next_item) {
			if (item->next_item != nullptr && item->next_item->value < item->value) {
				int temp = item->value;
				item->value = item->next_item->value;
				item->next_item->value = temp;

				sorted = false;
			}
		}
	} while (sorted != true);
};





//  ---  Element struct  ---  //


task::list::list_item::list_item(const int& value, list_item* prev_item, list_item* next_item)
	: value(value), prev_item(prev_item), next_item(next_item) {}






//  ---  Private methods  ---  //


void task::list::_pop_item(const task::list::list_item* list_item) {
	auto next = list_item->next_item;
	auto prev = list_item->prev_item;

	// Reconnecting nearby items
	if (prev != nullptr) prev->next_item = next;
	if (next != nullptr) next->prev_item = prev;

	// Updating _end and _begin
	if (list_item == _end) _end = prev;
	if (list_item == _begin) _begin = next;

	// Finally delete item
	delete list_item;
	list_item = nullptr;

	--_size;
}

void task::list::_insert_value(const int& value, task::list::list_item* prev_item, task::list::list_item* next_item) {
	auto ptr = new list_item(value, prev_item, next_item);

	// Connecting to a new item
	if (prev_item != nullptr) prev_item->next_item = ptr;
	if (next_item != nullptr) next_item->prev_item = ptr;

	// Updating _end and _begin
	if (prev_item == _end) _end = ptr;
	if (next_item == _begin) _begin = ptr;

	++_size;
}