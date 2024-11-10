#include <ostream>

template <typename T> 
class Node {
	public:
		//atributos
		T data;
		Node<T> *next;
		//métodos
		Node(T data, Node<T> *next=nullptr){
			this->data=data;
			this->next=next;
		}
		friend std::ostream& operator << (std::ostream &out, const Node<T> &node){
			out<<node.data;
			return out;
		}
};
