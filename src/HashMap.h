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
	// Defines the bracket operator for HashMap, so you can use your map like this:
	// your_map["david"] = 2.99;
	// If the key does not exist in the hashmap, this will create a new entry in 
	// the hashmap and map it to the default value of type T. Then it will return a
	// reference to the newly created value in the map.
	T& operator[](const std::string& key);
	// If no association exists with the given key, return nullptr; otherwise, 
	// return a pointer to the value associated with that key. This pointer can be 
	// used to examine that value within the map.
	const T* find(const std::string& key) const;
	// If no association exists with the given key, return nullptr; otherwise, 
	// return a pointer to the value associated with that key. This pointer can be 
	// used to examine that value or modify it directly within the map. 
	T* find(const std::string& key) {
		const auto& hm = *this;
		return const_cast<T*>(hm.find(key));
	}

private:
	// prevent copying and assigning HashMaps
	HashMap(const HashMap& other) {}
	HashMap& operator=(const HashMap& other) {}

	struct Node {
		std::string key;
		T value;
		Node* next;
	};

	int hash(const std::string& key, int mod = -1) const;
	void grow();
	void insertNodeAt(Node** map, Node* node, int index);

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
void HashMap<T>::grow()
{
	// create a new array of Node pointers with
	// double the size and initialize to nullptr
	int new_size = m_size * 2;
	Node** new_map = new Node*[new_size];
	for (int i = 0; i < new_size; i++)
		new_map[i] = nullptr;

	// insert Node pointers from current array to
	// correct location in new array
	for (int i = 0; i < m_size; i++) {
		Node* curr = m_map[i];
		Node* next;
		while (curr != nullptr) {
			next = curr->next;
			int j = hash(curr->key, new_size);
			insertNodeAt(new_map, curr, j);
			curr = next;
		}
	}

	delete [] m_map;
	m_map = new_map;
	m_size = new_size;
}

template <typename T>
void HashMap<T>::insertNodeAt(Node** map, Node* node, int index)
{
	node->next = nullptr;
	Node* curr = map[index];

	if (curr == nullptr) {
		map[index] = node;
		return;
	}

	Node* prev;
	while (curr != nullptr) {
		prev = curr;
		curr = curr->next;
	}

	prev->next = node;
}


template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value)
{
	if ( ((double)m_used+1) / m_size > m_max_load )
		grow();

	int i = hash(key);
	Node* curr = m_map[i];

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
const T* HashMap<T>::find(const std::string& key) const
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

	T val = T();
	insert(key, val);
	val_ptr = find(key);
	return *val_ptr;
}

template <typename T>
int HashMap<T>::hash(const std::string& key, int mod) const
{
	return std::hash<std::string>()(key) % (mod == -1 ? m_size : mod);
}

#endif // HashMap_h
