#pragma once

#include "nocopy.h"

template <class T>
class Pointer : nocopy{
	public:
		explicit Pointer(T *t = nullptr):m_t(t){
		}
		~Pointer() {
			if (m_t) {
				delete m_t;
				m_t = nullptr;
			}
		}
		void Reset(T *t = nullptr){
    		 if(m_t){
        		delete m_t;
        		m_t = nullptr;
			}
			m_t = t;
		}
		T *Get() const{
			return m_t;
		}
	private:
		T *m_t;
};