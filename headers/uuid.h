#pragma once
#pragma once
#ifndef _UUID_H_
#define _UUID_H_ 1.0

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
  class UUID_DLL_API UUID final{
  private:
    uint64_t d[2];
  public:
    ~UUID();

    UUID(const UUID &uid) noexcept;

    UUID &operator =(const UUID &uid) noexcept;

    UUID(UUID &&uid) noexcept;

    UUID &operator =(UUID &&uid) noexcept;

    UUID() noexcept;

    UUID &operator --() noexcept;

    UUID &operator ++() noexcept;

    bool operator <(const UUID &uid) const noexcept;
    
    bool operator ==(const UUID &uid) const noexcept;

    bool operator !=(const UUID &uid) const noexcept;

    std::string toStr() const noexcept;
  };

  UUID_DLL_API size_t getNumberOfLostUUIDs() noexcept;

  UUID_DLL_API void getUUID(UUID &v) noexcept;

  UUID_DLL_API void releaseUUID(const UUID &v) noexcept;
}
//---------------------------------------------------------------------------------------------------------------------------------
#endif // !_UUID_H_
//---------------------------------------------------------------------------------------------------------------------------------