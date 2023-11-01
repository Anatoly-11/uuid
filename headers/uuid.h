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
//#include <cstdint>
#include <string>
//---------------------------------------------------------------------------------------------------------------------------------
namespace MyUuid {
  //-------------------------------------------------------------------------------------------------------------------------------
  class UUID;
  //-------------------------------------------------------------------------------------------------------------------------------
  class UUID_DLL_API IUUID {
  public:
    virtual UUID &operator --() noexcept = 0;

    virtual UUID &operator ++() noexcept = 0;

    virtual bool operator <(const UUID &uid) const noexcept = 0;
    
    virtual bool operator ==(const UUID &uid) const noexcept = 0;

    virtual bool operator !=(const UUID &uid) const noexcept = 0;

    virtual std::string toStr() const noexcept = 0;
  };

  UUID_DLL_API size_t getNumberOfLostUUIDs() noexcept;

  UUID_DLL_API void getUUID(UUID &v) noexcept;

  UUID_DLL_API void releaseUUID(const UUID &v) noexcept;
}
//---------------------------------------------------------------------------------------------------------------------------------
#endif // !_UUID_H_
//---------------------------------------------------------------------------------------------------------------------------------