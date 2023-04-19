#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class String
{
private:
    char* str;
    size_t length;

public:
    String();
    String(const char* str);
    String(const String& other);
    String(String&& other) noexcept;
    ~String();

    String& operator = (const String& other);
    String& operator = (String&& other) noexcept;
    String& operator = (const char* other);

    bool operator == (const char* otherStr) const;
    bool operator == (const String& other) const;
    bool operator != (const String& other);

    String operator + (const String& other);
    String operator + (const char* other);

    String& operator += (const String& other);
    String& operator += (const char* other);
    String& operator += (const char ch);

    bool operator > (const String& other);
    bool operator < (const String& other);
    bool operator >= (const String& other);
    bool operator <= (const String& other);

    char& operator [](size_t index) const;

    void PushFront(char c);
    String CutString(int start, int end) const;
    String DeleteSpaces() const;
    String* SplitByChar(char ch) const;

    int containString(const char* other) const;
    int containString(const String& other) const;

    unsigned int CountChar(char ch) const;
    unsigned int CountWords() const;
    unsigned int FindChar(char ch, int start) const;
    unsigned int GetLength() const;

    friend std::ostream& operator << (std::ostream& out, const String& other);
    friend std::istream& operator >> (std::istream& in, String& s);
};