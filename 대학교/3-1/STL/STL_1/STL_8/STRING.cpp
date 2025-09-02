#include <iostream>
#include <memory>
#include <print>
#include "STRING.h"


bool 관찰{ true };
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

std::ostream& operator<<(std::ostream& os, const STRING& str) {
    for (int i = 0; i < str.len; ++i) {
        os << str.p[i];
    }
    return os;
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