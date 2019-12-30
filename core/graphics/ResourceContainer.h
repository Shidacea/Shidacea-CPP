#pragma once

#include <queue>

template <class T> class ResourceContainer {

public:

	ResourceContainer();
	~ResourceContainer();

	int add();
	void remove(int index);
	T* access(int index);

private:

	//! Use unique_ptr to optimize performance, and just give out raw pointers
	std::vector<std::unique_ptr<T>> contents;
	std::queue<int> free_spots;

};

template <class T> ResourceContainer<T>::ResourceContainer() {

	//! Reserve some spots to ensure faster access
	//! 100000 should be a reasonable amount
	contents.reserve(100000);

}

template <class T> ResourceContainer<T>::~ResourceContainer() {

}

template <class T> int ResourceContainer<T>::add() {

	if (free_spots.empty()) {

		contents.push_back(std::make_unique<T>());
		return static_cast<int>(contents.size() - 1);

	}
	else {

		auto index = free_spots.front();
		contents[index] = std::make_unique<T>();
		free_spots.pop();

		return index;

	}
}

template <class T> void ResourceContainer<T>::remove(int index) {

	contents[index] = nullptr;
	free_spots.push(index);

}

template <class T> T* ResourceContainer<T>::access(int index) {

	return contents.at(index).get();

}
