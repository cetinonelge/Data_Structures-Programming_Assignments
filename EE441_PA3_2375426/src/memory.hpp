#pragma once

void* operator new(size_t count);
void* operator new[](size_t count);
void operator delete(void* ptr, size_t count);
void operator delete[](void* ptr, size_t count);

void* operator new(size_t count, const char* fileName, size_t lineNo);
void* operator new[](size_t count, const char* fileName, size_t lineNo);
void operator delete(void* ptr, size_t count, const char* fileName, size_t lineNo);
void operator delete[](void* ptr, size_t count, const char* fileName, size_t lineNo);

#define new new(__FILE__, __LINE__)
