#include <iostream>
#include <rados/librados.hpp>
#include "include/zlog/log.h"
#include <map>
//#include "zlog-kv.h"

namespace zlog {

void ZlogKV::kv_insert(std::string& key, ceph::bufferlist& data)
{
  // concat key and data before appending in the log
  ceph::bufferlist zlog_data;
  zlog_data.append(key);
  zlog_data.append(data);

  uint64_t pos;
  // append zlog_data to the log
  int ret = log_->Append(zlog_data, &pos);
  // add key, pos to the kv map
  key_to_position_.insert(std::pair<std::string&, uint64_t>(key, pos));
  std::cout << "Append at position: " << pos << std::endl;
}

void ZlogKV::kv_read(std::string key)
{
  //lookup the map to find the log position
  std::map<std::string, uint64_t>::const_iterator it = 
                                         key_to_position_.find(key); 
  uint64_t pos;
  pos = it->second;
  ceph::bufferlist zlog_data;
  
  // read the data from the log position
  int ret = log_->Read(pos, zlog_data);
  std::cout<<"Read: "<< zlog_data.c_str() << " at position " <<pos << std::endl;
}

}
