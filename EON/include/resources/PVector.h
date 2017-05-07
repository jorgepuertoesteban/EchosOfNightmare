#pragma once

#include "nocopy.h"

template <class T>
class PVector : nocopy{
	public:
		explicit PVector(){
		}
		~PVector() {
			for(unsigned int i = 0 ; i<m_rs.size() ; i++){
				if(m_rs.at(i))delete m_rs.at(i);
			}
			m_rs.clear();
			std::vector<T*>().swap(m_rs);
		}
		T * Add(T *a = nullptr){
			if(a){
				m_rs.push_back(a);
				return a;
			}
			return nullptr;
		}
		void Remove(int i){
			if(m_rs.at(i))delete m_rs.at(i);
			m_rs.erase(m_rs.begin()+i);
		}
		std::vector<T*> Get() const{
			return m_rs;
		}
		T* Get(int i){
			return m_rs.at(i);
		}
		int Size(){
			return m_rs.size();
		}
	private:
		std::vector<T*> m_rs;
};