#include <iostream>
#include <rados/librados.hpp>
#include "libzlog/log_impl.h" 
#include <map>

namespace zlog {

class ZlogKVImpl : public ZlogKV {
  public:

    //create zlog object
   // Log *log_;
    //ZlogKVImpl(Log *log);

    //~ZlogKVImpl();

    void kv_insert(std::string& key, ceph::bufferlist& data);

    void kv_read(std::string key);

  private:
    std::map<std::string, uint64_t> key_to_position_;
};
}
