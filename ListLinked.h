#include <ostream>
#include <exception>
#include "List.h"
#include "Node.h"

using namespace std;

template <typename T>
class ListLinked : public List<T> {
	private:
		Node<T> *first;
		int n;
		// ...
	public:
		ListLinked(){
			first=nullptr;
			n=0;
		}
		~ListLinked(){
			Node<T> *aux;
			for (int i=0;i<n;i++){
				aux=first->next;
				delete first;
				first=aux;
			}
		}
		T operator[](int pos){
			if(pos<0||pos>=n) throw std::out_of_range("fuera del intervalo");
			Node<T> *aux=first;
			for (int i=0;i<pos;i++){
				aux=aux->next;
			}
			return aux->data;
		}
		friend std::ostream& operator << (std::ostream &out, const ListLinked<T> &List){
			Node<T> *aux=List.first;
			for (int i=0; i<List.n; i++){
				out<<aux->data<<" ";
				aux=aux->next;
			}
			return out;
		}
		void insert(int pos, T e) override{
			if (pos < 0 || pos > n) throw std::out_of_range("Posición fuera de rango");
			Node<T>* aux = new Node<T>{e, nullptr};
			if (pos == 0) {
				aux->next = first;
				first = aux;
			} else {
				Node<T>* otroaux = first;
				for (int i = 0; i < pos - 1; ++i) {
					otroaux = otroaux->next;
				}
				aux->next = otroaux->next;
				otroaux->next = aux;
			}
			++n;
		}
		void append(T e) override{
			insert(n,e);
		}
		void prepend(T e) override{
			insert(0,e);
		}
		T remove(int pos) override{
			if(pos<0||pos>=n) throw out_of_range("Posición no válida");
			T e;
			if(pos!=0){
				Node<T> *aux=first;
				for(int i=0;i<pos-1;i++){
					aux=aux->next;
				}
				Node<T> *otroaux=aux->next;
				aux->next=aux->next->next;
				e=otroaux->data;
				delete otroaux;
			}
			else{
				Node<T> *aux=first;
				e=aux->data;
				first=first->next;
				delete aux;
			}
			n--;
			return e;
		}
		T get(int pos) override{
			if(pos<0||pos>=n) throw out_of_range("Posición no válida");
			Node<T> *aux=first;
			for(int i=0;i<pos;i++){
				aux=aux->next;
			}
			return aux->data;
		}
		int search(T e) override{
			Node<T> *aux=first;
			for(int i=0;i<n;i++){
				if(aux->data==e) return i;
				aux=aux->next;
			}
			return -1;
		}
		bool empty() override{
			return n==0;
		}
		int size() override{
			return n;
		}
		// ...
};
