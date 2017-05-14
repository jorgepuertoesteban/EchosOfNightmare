#pragma once

#include "nocopy.h"
#include <vector>

template <class T>
class PVector : nocopy {
public:
	explicit PVector() {
	}
	~PVector() {
		auto it = m_rs.begin();
		while (it != m_rs.end()) {
			delete *it;
			it = m_rs.erase(it);
		}
		m_rs.clear();
		std::vector<T*>().swap(m_rs);
	}
	void Clear() {
		auto it = m_rs.begin();
		while (it != m_rs.end()) {
			delete *it;
			it = m_rs.erase(it);
		}
		m_rs.clear();
		std::vector<T*>().swap(m_rs);
	}
	T * Add(T *a = nullptr) {
		if (a) {
			m_rs.push_back(a);
			return a;
		}
		return nullptr;
	}
	auto Remove(int i) {
		if (m_rs.at(i))delete m_rs.at(i);
		return m_rs.erase(m_rs.begin() + i);
	}
	auto Get() const {
		return m_rs;
	}
	auto Get(int i) const {
		return m_rs.at(i);
	}
	int Size() const {
		return m_rs.size();
	}
	auto GetBegin() const {
		return m_rs.begin();
	}
	auto GetEnd() const {
		return m_rs.end();
	}
private:
	std::vector<T*> m_rs;
};