#include <ostream>
#include <exception>
#include "List.h"

using namespace std;

template <typename T>
class ListArray : public List<T>{
	private:
		T* arr;
		int max;
		int n;
		static const int MINSIZE;
	public:
		ListArray(){
			arr=new T(MINSIZE);
			max=MINSIZE;
			n=0;
		}
		~ListArray(){
			delete[] arr;
		}
		T operator[](int pos){
			if(pos<0 || pos>=n) throw out_of_range("No existe el elemento");
			return arr[pos];
		}
		friend std::ostream& operator<<(std::ostream &out, const ListArray<T> &list){
			for(int i=0;i<list.n;i++){
				out<<list.arr[i]<<" ";
			}
			return out;
		}
		void resize(int new_size){
			T* new_arr=new T(new_size);
			for(int i=0;i<n;i++){
				new_arr[i]=arr[i];
			}
			delete[] arr;
			arr=new_arr;
			max=new_size;
		}
		void insert(int pos, T e) override{
			if(pos<0 || pos>n) throw out_of_range("Posicion no valida");
			if(n==max) resize(max*2);
			for(int i=n;i>pos;i--){
				arr[i]=arr[i-1];
			}
			arr[pos]=e;
			n++;
		}
		void append(T e) override{
			insert(n,e);
		}
		void prepend(T e) override{
			insert(0,e);
		}
		T remove(int pos) override{
			if(pos<0 || pos>=n) throw out_of_range("Posicion no valida");
			T e=arr[pos];
			for(int i=pos;i<n-1;i++){
				arr[i]=arr[i+1];
			}
			n--;
			if(n<max/4) resize(max/2);
			return e;
		}
		T get(int pos) override{
			if(pos<0 || pos>=n) throw out_of_range("Posicion no valida");
			return arr[pos];
		}
		int search (T e) override{
			for(int i=0;i<n;i++){
				if(arr[i]==e) return i;
			}
			return -1;
		}
		bool empty() override{
			return n==0;
		}
		int size() override{
			return n;
		}
};

template <typename T>
const int ListArray<T>::MINSIZE = 2;
