#ifndef HashMap_h
#define HashMap_h

#include <string>

template <typename T> 
class HashMap
{ 
public: 
	HashMap(double max_load = 0.75); // constructor 
	~HashMap(); // destructor; deletes all of the items in the hashmap 
	// return the number of associations in the hashmap
	int size() const { return m_used; }
	// The insert method associates one item (key) with another (value). 
	// If no association currently exists with that key, this method inserts 
	// a new association into the hashmap with that key/value pair. If there is 
	// already an association with that key in the hashmap, then the item 
	// associated with that key is replaced by the second parameter (value). 
	// Thus, the hashmap must contain no duplicate keys. 
	void insert(const std::string& key, const T& value); 
	// If no association exists with the given key, return nullptr; otherwise, 
	// return a pointer to the value associated with that key. This pointer can be 
	// used to examine that value or modify it directly within the map. 
	T* find(const std::string& key);
	// Defines the bracket operator for HashMap, so you can use your map like this:
	// your_map["david"] = 2.99;
	// If the key does not exist in the hashmap, this will create a new entry in 
	// the hashmap and map it to the default value of type T. Then it will return a
	// reference to the newly created value in the map.
	T& operator[](const std::string& key);

private:
	// prevent copying and assigning HashMaps
	HashMap(const HashMap& other) {}
	HashMap& operator=(const HashMap& other) {}

	int hash(const std::string& key);

	struct Node {
		std::string key;
		T value;
		Node* next;
	};

	int m_size;
	int m_used;
	double m_max_load;
	Node** m_map;
}; 

template <typename T> 
HashMap<T>::HashMap(double max_load)
{
	m_size = 10;
	m_used = 0;
	m_max_load = max_load;
	m_map = new Node*[m_size];

	for (int i = 0; i < m_size; i++)
		m_map[i] = nullptr;
}

template <typename T>
HashMap<T>::~HashMap()
{
	for (int i = 0; i < m_size; i++) {
		Node* curr = m_map[i];
		Node* next = nullptr;
		while (curr != nullptr) {
			next = curr->next;
			delete curr;
			curr = next;
		}
	}

	delete [] m_map;
}

template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value)
{
	int i = hash(key);
	Node* curr = m_map[i];

	// TODO check max load

	if (curr == nullptr) {
		m_map[i] = new Node{key, value, nullptr};
		m_used++;
		return;
	}

	Node* prev = curr;
	while (curr != nullptr) {
		if (curr->key == key) {
			curr->value = value;
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	
	prev->next = new Node{key, value, nullptr};
	m_used++;
}

template <typename T>
T* HashMap<T>::find(const std::string& key)
{
	Node* curr = m_map[hash(key)];

	if (curr == nullptr)
		return nullptr;

	while (curr != nullptr) {
		if (curr->key == key)
			return &curr->value;
		curr = curr->next;
	}

	return nullptr;
}

template <typename T>
T& HashMap<T>::operator[](const std::string& key)
{
	T* val_ptr = find(key);
	if (val_ptr != nullptr)
		return *val_ptr;

	T val;
	insert(key, val);
	val_ptr = find(key);
	return *val_ptr;
}

template <typename T>
int HashMap<T>::hash(const std::string& key)
{
	return std::hash<std::string>()(key) % m_size;
}

#endif // HashMap_h
