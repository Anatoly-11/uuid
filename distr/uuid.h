#pragma once
#pragma once
//---------------------------------------------------------------------------------------------------------------------------------
#ifndef _UUID_H_
#define _UUID_H_ 1.0
//---------------------------------------------------------------------------------------------------------------------------------
#ifdef UUID_EXPORTS
#define UUID_DLL_API __declspec(dllexport)
#else
#define UUID_DLL_API __declspec(dllimport)
#endif
//---------------------------------------------------------------------------------------------------------------------------------
#include <cstdint>
#include <string>
//---------------------------------------------------------------------------------------------------------------------------------
namespace MyUuid {
  //-------------------------------------------------------------------------------------------------------------------------------
  class UUID_DLL_API UUID {
    uint64_t d[2];
  public:
    UUID() noexcept;

    ~UUID() noexcept;
    
    UUID &operator --() noexcept;

    UUID &operator ++() noexcept;

    bool operator <(const UUID &uid) const noexcept;
    
    bool operator ==(const UUID &uid) const noexcept;

    bool operator !=(const UUID &uid) const noexcept;

    std::string toStr() const noexcept;

  };

  UUID_DLL_API size_t getNumberOfLostUUIDs() noexcept;

  UUID_DLL_API void getUUID(UUID &uid) noexcept;

  UUID_DLL_API void releaseUUID(const UUID &uid) noexcept;
}
//---------------------------------------------------------------------------------------------------------------------------------
#endif // !_UUID_H_
//---------------------------------------------------------------------------------------------------------------------------------