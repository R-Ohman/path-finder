#include "String.h"


String::String() {
    str = nullptr;
    length = 0;
}


String::String(const char* str) {
    length = strlen(str);
    this->str = new char[length + 1];
    strncpy(this->str, str, length);
    this->str[length] = '\0';
}


String::String(const String& other) {
    length = other.length;
    str = new char[length + 1];
    strcpy_s(str, length + 1, other.str);
}


String::String(String&& other) noexcept {
    length = other.length;
    str = other.str;
    other.length = 0;
    other.str = nullptr;
}


String::~String() {
    if (this->length != 0) {
        length = 0;
        delete[] str;
    }
}


String& String::operator = (const String& other) {
    if (this == &other) {
        return *this;
    }
    if (str != nullptr) {
        delete[] this->str;
    }

    if (other.str == nullptr) {
        str = nullptr;
        return *this;
    }
    else {
        length = other.length;
        str = new char[length + 1];
        strcpy_s(this->str, length + 1, other.str);
    }
    return *this;
}


String& String::operator = (String&& other) noexcept {
    if (this != &other) {
        delete[] str;
        length = other.length;
        str = other.str;

        other.length = 0;
        other.str = nullptr;
    }
    return *this;
}


String& String::operator = (const char* other) {
    this->length = strlen(str);
    if (this->str != nullptr) {
        delete[] this->str;
    }
    this->str = new char[length + 1];
    strcpy_s(this->str, length + 1, other);
    return *this;
}


bool String::operator == (const char* otherStr) const {
    return strcmp(str, otherStr) == 0;
}

bool String::operator == (const String& other) const {
    return strcmp(str, other.str) == 0;
}


bool String::operator != (const String& other) {
    return strcmp(this->str, other.str) != 0;
}


String String::operator + (const String& other) {
    String result;
    result.length = this->length + other.length;
    char* temp = new char[result.length + 1];
    strcpy_s(temp, result.length + 1, this->str);
    strcat_s(temp, result.length + 1, other.str);
    result.str = temp;
    return result;
}


String String::operator + (const char* other) {
    String result;
    result.length = this->length + strlen(other);
    char* temp = new char[length + 1];
    strcpy_s(temp, length + 1, this->str);
    strcat_s(temp, length + 1, other);
    result.str = temp;
    return result;
}


String& String::operator += (const String& other) {
    length += other.length;
    char* temp = new char[length + 1];
    strcpy_s(temp, length + 1, this->str);
    strcat_s(temp, length + 1, other.str);
    this->str = temp;
    return *this;
}


String& String::operator += (const char* other) {
    length += strlen(other);
    char* temp = new char[length + 1];
    strcpy_s(temp, length + 1, this->str);
    strcat_s(temp, length + 1, other);
    this->str = temp;
    return *this;
}


String& String::operator += (const char ch) {
    length++;
    char* temp = new char[length + 1];
    strcpy_s(temp, length + 1, this->str);
    temp[length - 1] = ch;
    temp[length] = '\0';
    this->str = temp;
    return *this;
}


bool String::operator > (const String& other) {
    return strcmp(this->str, other.str) > 0;
}


bool String::operator < (const String& other) {
    return strcmp(this->str, other.str) < 0;
}


bool String::operator >= (const String& other) {
    return strcmp(this->str, other.str) >= 0;
}


bool String::operator <= (const String& other) {
    return strcmp(this->str, other.str) <= 0;
}


char& String::operator [](size_t index) const {
    if (index < length) {
        return this->str[index];
    }
    return this->str[length];
}


void String::PushFront(char c)
{
	char* temp = new char[length + 2];
	temp[0] = c;
    // warn, c = '.'
    if (str != nullptr) {
        strcpy_s(temp + 1, length + 1, str);
        delete[] str;
    }
	str = temp;
	temp[length + 1] = '\0';
	length++;
}

String String::CutString(int start, int end) const {
    String result;
    result.length = end - start;
    result.str = new char[result.length + 1];
    strncpy(result.str, str + start, result.length);
    result.str[result.length] = '\0';
    return result;
}


String String::DeleteSpaces() const {
    int start = 0, end = length - 1;
    while (str[start] <= ' ') {
        start++;
    }
    while (str[end] <= ' ') {
        end--;
    }
    if (start > end) {
        return "";
    }
    if (start == 0 && end == length - 1) {
        return *this;
    }
    return CutString(start, end + 1);
}


String* String::SplitByChar(char ch) const {
    unsigned int countWords;
    if (ch == ';') {
        countWords = CountChar(':');
    }
    else {
        countWords = CountWords();
    }

    if (countWords == 0) {
        return nullptr;
    }
    String* arraySplit = new String[countWords];
    unsigned int startChar = 0;

    for (size_t word = 0; word < countWords; word++) {
        unsigned int lastChar;
        // Skip all "ch" symbols
        while (startChar < length && str[startChar] == ch) {
            startChar++;
        }

        // Find next "ch" symbol
        lastChar = FindChar(ch, startChar);
        if (lastChar == startChar) {
            continue;
        }
        arraySplit[word] = CutString(startChar, lastChar);
        startChar = lastChar + 1;
    }
    return arraySplit;
}


int String::containString(const char* other) const {
    // The function returns the index of the first occurrence of the substring in the string, or -1 if the substring is not present in the string
    unsigned int lengthString = strlen(this->str);
    unsigned int lengthSubString = strlen(other);
    bool flag = false;
    int index = -1;

    for (size_t i = 0; i < lengthString; i++) {
        // If the remaining string is smaller than the substring, then we can't have a match
        if (!flag && lengthSubString > lengthString - i) {
            return -1;
        }
        // If the current character matches the first character of the substring, we have a potential match
        if (!flag && this->str[i] == *other) {
            flag = true;
            index = i;
        }
        // If the characters don't match, then the substring doesn't match
        if (this->str[i] != other[i - index]) {
            flag = false;
        }
        // If we have matched all the characters in the substring, then we have a match, return the starting index of the substring
        if (i - index == lengthSubString - 1 && flag) {
            return index;
        }
    }
    return -1;
}


int String::containString(const String& other) const {
    // The function returns the index of the first occurrence of the substring in the string, or -1 if the substring is not present in the string
    unsigned int lengthString = strlen(this->str);
    unsigned int lengthSubString = strlen(other.str);
    bool flag = false;
    int index = -1;

    for (size_t i = 0; i < lengthString; i++) {
        // If the remaining string is smaller than the substring, then we can't have a match
        if (!flag && lengthSubString > lengthString - i) {
            return -1;
        }
        // If the current character matches the first character of the substring, we have a potential match
        if (!flag && this->str[i] == *other.str) {
            flag = true;
            index = i;
        }
        // If the characters don't match, then the substring doesn't match
        if (this->str[i] != other.str[i - index]) {
            flag = false;
        }
        // If we have matched all the characters in the substring, then we have a match, return the starting index of the substring
        if (i - index == lengthSubString - 1 && flag) {
            return index;
        }
    }
    return -1;
}


unsigned int String::CountChar(char ch) const {
    int counter = 0;
    for (size_t i = 0; i < this->length; i++) {
        if (str[i] == ch) {
            counter++;
        }
    }
    return counter;
}


unsigned int String::CountWords() const {
    // This function counts the number of words in the string
    // The function considers words to be separated by commas (',')
    int result = 0;
    bool flag = true;
    for (size_t i = 0; i < length; i++) {
        if (str[i] == ',') {
            flag = true;    // Set the flag to indicate that we are not in the middle of a word
        }
        else if (flag) {
            result++;
            flag = false;
        }
    }
    return result;
}


unsigned int String::FindChar(char ch, int start) const {
    // This function finds the first occurrence of the character "ch" in the string, starting from the index "start"
    // If the character is not found, the function returns the length of the string
    for (size_t i = start; i < this->length; i++) {
        if (str[i] == ch) {
            return i;
        }
    }
    return length;
}


unsigned int String::GetLength() const {
    return length;
}

std::ostream& operator << (std::ostream& out, const String& other) {
    out << other.str;
    return out;
}

std::istream& operator >> (std::istream& in, String& s) {
    static const int buffer_size = 20001;
    static char buffer[buffer_size];
    bool isEOF = false;
    if (!in.getline(buffer, buffer_size - 1)) {
        isEOF = true;
    }

    s.length = strlen(buffer);
    if (s.length <= 0 && !isEOF) {
        s.str = nullptr;
        return in;
    }
    if (s.length <= 0 && isEOF) {
        // If the end of the file is reached, then the last character is set to 1 to indicate it
        s.str = new char[1];
        s.str[0] = 1;
        s.length = 1;
        return in;
    }

    s.str = new char[s.length + 1];
    std::memcpy(s.str, buffer, s.length);

    if (isEOF) {
        // If the end of the file is reached, then the last character is set to 1 to indicate it
        s.str[s.length] = 1;
    }
    else {
        s.str[s.length] = '\0';
    }

    return in;
}