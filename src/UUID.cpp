#include <UUID.h>
#include <cstdint>
#include <format>
#include <vector>
#include <mutex>
//---------------------------------------------------------------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------------------------------------------------------------
namespace MyUuid {
  class UUID_DLL_API UUID : public IUUID {
    uint64_t d[2];
  public:
    UUID() noexcept: d{0, 0} {
    }

    ~UUID() {
    }

    /*virtual UUID &operator =(const UUID &uid) noexcept override {
      d[0] = uid.d[0];
      d[1] = uid.d[1];
      return *this;
    };

    virtual UUID &operator =(UUID &&uid) noexcept override{
      d[0] = uid.d[0];
      d[1] = uid.d[1];
      return *this;
    };*/

    virtual UUID &operator --() noexcept override {
      // не нужна блокировка потому как Вы свой UUID редактируете
      if(d[0] != ULLONG_MAX) --d[0];
      else --d[1];
      return *this;
    }

    virtual UUID &operator ++() noexcept override {
      // не нужна блокировка потому как Вы свой UUID редактируете
      if(d[0] != ULLONG_MAX) ++d[0];
      else ++d[1];
      return *this;
    }

    virtual bool operator <(const UUID &uid) const noexcept override {
      return d[1] == uid.d[1] ? d[0] < uid.d[0] : d[1] < uid.d[1];
    }

    virtual bool operator ==(const UUID &uid) const noexcept override {
      return d[1] == uid.d[1] && d[0] == uid.d[0];
    }

    virtual bool operator !=(const UUID &uid) const noexcept override {
      return !(*this == uid);
    }

    virtual std::string toStr() const noexcept override {
      return std::format("{:08X}-{:04X}-{:04X}-{:04X}-{:012X}", *((uint32_t *)d + 3), *((uint16_t *)d + 5), *((uint16_t *)d + 4),
        (*d) >> 48, (*d) & 0xFFFFFFFFFFFF);
    }
  };
}
//---------------------------------------------------------------------------------------------------------------------------------
mutex mtx;
//---------------------------------------------------------------------------------------------------------------------------------
static std::vector<MyUuid::UUID> lost;
//---------------------------------------------------------------------------------------------------------------------------------
UUID_DLL_API size_t MyUuid::getNumberOfLostUUIDs() noexcept {
  return lost.size();
}
//---------------------------------------------------------------------------------------------------------------------------------
static MyUuid::UUID max_uuid{};
//---------------------------------------------------------------------------------------------------------------------------------
UUID_DLL_API void MyUuid::getUUID(MyUuid::UUID &uid) noexcept {
  lock_guard<mutex> grd(mtx);
  if(!lost.empty()) {
    max_uuid = lost.back();
    lost.pop_back();
  } else {
    ++max_uuid;
  }
  uid = max_uuid;
}
//---------------------------------------------------------------------------------------------------------------------------------
UUID_DLL_API void MyUuid::releaseUUID(const MyUuid::UUID &uid) noexcept {
  lock_guard<mutex> grd(mtx);
  if(uid == max_uuid)
    --max_uuid;
  else
    lost.push_back(uid);
}
//---------------------------------------------------------------------------------------------------------------------------------