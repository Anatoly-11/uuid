#include <UUID.h>
#include <format>
#include <vector>
#include <mutex>
#include <cstdint>
#include <random>
#include <chrono>
#include <functional>
//---------------------------------------------------------------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------------------------------------------------------------
mutex mtx;
//---------------------------------------------------------------------------------------------------------------------------------
namespace MyUuid {
  UUID::UUID() noexcept: d{0, 0} {
  }

  UUID::~UUID() noexcept {
  }

  UUID &UUID::operator=(const void *_d) noexcept{
    lock_guard<mutex> grd(mtx);
    uint64_t v[2]{d[0], d[1]}; // Сохраняем предыдущее значение
    try {
      const uint64_t *dd = reinterpret_cast<const uint64_t*>(_d);
      d[0] = dd[0];
      d[1] = dd[1];
    }
    catch(...) { // Игнорируется исключение 
      // Восстанавливаем возможно испорченое значение
      d[0] = v[0];
      d[1] = v[1];
    }
    return *this;
  };


  UUID &UUID::operator--() noexcept {
    // не нужна блокировка потому как Вы свой UUID редактируете
    if(d[0] != ULLONG_MAX) --d[0];
    else --d[1];
    return *this;
  }

  UUID &UUID::operator++() noexcept {
    // не нужна блокировка потому как Вы свой UUID редактируете
    if(d[0] != ULLONG_MAX) ++d[0];
    else ++d[1];
    return *this;
  }

  bool UUID::operator<(const UUID &uid) const noexcept {
    return d[1] == uid.d[1] ? d[0] < uid.d[0] : d[1] < uid.d[1];
  }

  bool UUID::operator==(const UUID &uid) const noexcept {
    return d[1] == uid.d[1] && d[0] == uid.d[0];
  }

  bool UUID::operator !=(const UUID &uid) const noexcept {
    return !(*this == uid);
  }

  std::string UUID::toStr() const noexcept {
    return std::format("{:08X}-{:04X}-{:04X}-{:04X}-{:012X}", *((uint32_t *)d + 3), *((uint16_t *)d + 5), *((uint16_t *)d + 4),
      (*d) >> 48, (*d) & 0xFFFFFFFFFFFF);
  }
}
//---------------------------------------------------------------------------------------------------------------------------------
//MyUuid::IUUID::~IUUID() noexcept {}
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
    uid = lost.back();
    lost.pop_back();
  } else {
    uid = ++max_uuid;
  }
}
//---------------------------------------------------------------------------------------------------------------------------------
UUID_DLL_API void MyUuid::getUUIDRnd(MyUuid::UUID &uid) noexcept {
  lock_guard<mutex> grd(mtx);
  static int count{};
  mt19937_64 engine{random_device{}()};
  uniform_int_distribution<uint64_t> distr{0, ULLONG_MAX};
  count+=2;
  if(count > 32) {
    count %= 32;
    engine.seed(chrono::system_clock::now().time_since_epoch().count() / 100ull);
  }
  uint64_t d[2]{std::bind(distr, engine)(), std::bind(distr, engine)()};
  uid = d;
}
//---------------------------------------------------------------------------------------------------------------------------------
UUID_DLL_API void MyUuid::releaseUUID(const MyUuid::UUID &uid) noexcept {
  lock_guard<mutex> grd(mtx);
  lost.push_back(uid);
}
//---------------------------------------------------------------------------------------------------------------------------------