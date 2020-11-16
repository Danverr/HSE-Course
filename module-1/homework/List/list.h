#pragma once
#include <cstddef>


namespace task {


	class list {

	public:

		//  ---  Member functions   ---  //

		list();
		list(const list&);
		list(size_t count, const int& value = int());
		~list();

		list& operator=(const list& other);



		//  ---  Element access  ---  //

		int& front();
		const int& front() const;

		int& back();
		const int& back() const;



		//  ---  Capacity  ---  //

		bool empty() const;
		size_t size() const;



		//  ---  Modifiers  ---  //

		void push_back(const int& value);
		void pop_back();

		void push_front(const int& value);
		void pop_front();

		void resize(size_t count, const int& value = int());
		void swap(list& other);
		void clear();



		//  ---  Operations  ---  //

		void remove(const int& value);
		void unique();
		void sort();

	private:

		//  ---  Element struct  ---  //

		struct list_item {
			int value;
			list_item* prev_item, * next_item;

			list_item(
				const int& value = int(),
				list_item* prev_item = nullptr,
				list_item* next_item = nullptr
				);
		};

		//  ---  Private methods  ---  //

		void _pop_item(const list_item*);
		void _insert_value(const int&, list_item*, list_item*);

		size_t _size;
		list_item* _begin, * _end;
	};

}
