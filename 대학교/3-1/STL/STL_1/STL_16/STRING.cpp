#include <iostream>
#include <memory>
#include <print>
#include <algorithm>
#include "STRING.h"


bool 관찰{ false };
size_t STRING::gid{ 0 };
STRING::STRING()
    : id{ ++gid }
{
    if (관찰) {
        std::println("[{:8}]- {:<20} 자원수:{:<6} 주소: {:>18}, 자원의 주소:{:>18}",
            id, "default 생성자", len, (void*)this, (void*)p.get());
    }
}

STRING::~STRING() {
    if (관찰) {
        std::println("[{:8}]- {:<20} 자원수:{:<6} 주소: {:>18}, 자원의 주소:{:>18}",
            id, "default 소멸자", len, (void*)this, (void*)p.get());
    }
}

STRING::STRING(const char* s)
    : id{ ++gid }, len{ strlen(s) }
{
    p.reset();
    p = std::make_unique<char[]>(len);        // p가 자원을 재확보하게 한다.
    memcpy(p.get(), s, len);
    if (관찰) {
        std::println("[{:8}]- {:<20} 자원수:{:<6} 주소: {:>18}, 자원의 주소:{:>18}",
            id, "생성자(char*)", len, (void*)this, (void*)p.get());
    }
}

STRING::STRING(const STRING& other)
    :id{ ++gid }, len{ other.len }
{
    p.reset();
    p = std::make_unique<char[]>(len);
    memcpy(p.get(), other.p.get(), len);

    if (관찰) {
        std::println("[{:8}]- {:<20} 자원수:{:<6} 주소: {:>18}, 자원의 주소:{:>18}",
            id, "생성자(STRING&)", len, (void*)this, (void*)p.get());
    }
}

STRING::STRING(STRING&& other)
    :id{ ++gid }, len{ other.len }
{

    p.reset(other.p.release());
    other.len = 0;

    if (관찰) {
        std::println("[{:8}]- {:<20} 자원수:{:<6} 주소: {:>18}, 자원의 주소:{:>18}",
            id, "이동 생성자", len, (void*)this, (void*)p.get());
    }

}

STRING& STRING::operator=(STRING&& other) {
    if (this == &other)
        return *this;
    len = other.len;
    // unique_ptr의 get:        포인터를 리턴
    // unique_ptr의 release:    포인터를 리턴하고 릴리즈
    p.reset(other.p.release());
    if (관찰) {
        std::println("[{:8}]- {:<20} 자원수:{:<6} 주소: {:>18}, 자원의 주소:{:>18}",
            id, "이동 operator=", len, (void*)this, (void*)p.get());
    }
    return *this;
}


size_t STRING::size() const {
    return len;
}

char* STRING::begin() const {
	return p.get(); // &p[0] 과 같다.
}

char* STRING::end() const {
	return p.get() + len;
}

STRING_Reverse_Iterator STRING::rbegin() const {
	return p.get() + len;
}

STRING_Reverse_Iterator STRING::rend() const {
	return p.get();
}

std::ostream& operator<<(std::ostream& os, const STRING& str) {
    for (int i = 0; i < str.len; ++i) {
        os << str.p[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, STRING& str) {
    std::string s;
	is >> s;
	str.p.release();
    str.p = std::make_unique<char[]>(s.size());
	str.len = s.size();
    std::memcpy(str.p.get(), s.data(), str.len);
    return is;
}

bool STRING::operator<(const STRING& other) const {
	return len < other.len;
}

bool STRING::operator==(const STRING& rhs) const {
    /*if (len != rhs.len) {
        return false;
    }

    for (int i = 0; i < len; ++i) {
        if (p[i] != rhs.p[i]) {
            return false;
        }
    }

    return true;*/ // -> 이런식으로 코딩하면 안댐 (이런식으로 비교하면서 하는 코딩을 lexicographical compare 라고함.

    // 이미 이런걸 비교해 주는 알고리즘이 있다.

    //return std::equal(p.get(), p.get() + len, rhs.p.get(), rhs.p.get() + len);
    return std::equal(&p[0], &p[0] + len, &rhs.p[0], &rhs.p[0] + len); //위나 아래나 같은거임.

}

STRING& STRING::operator=(const STRING& other)
{
    if (this == &other) {
        return *this;
    }

    len = other.len;
    p.release();
    p = std::make_unique<char[]>(len);
    memcpy(p.get(), other.p.get(), len);
    if (관찰) {
        std::println("[{:8}]- {:<20} 자원수:{:<6} 주소: {:>18}, 자원의 주소:{:>18}",
            id, "복사 operator=", len, (void*)this, (void*)p.get());
    }
    return *this;

}