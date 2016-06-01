#ifndef LIBZLOG_ZLOG_HPP
#define LIBZLOG_ZLOG_HPP
#include <rados/librados.hpp>
#include "libseq/libseqr.h"
#include "zlog/stream.h"

namespace zlog {

class AioCompletion {
 public:
  virtual ~AioCompletion();
  virtual void SetCallback(std::function<void()> callback) = 0;
  virtual void WaitForComplete() = 0;
  virtual int ReturnValue() = 0;
};

class Log {
 public:
  Log() {}
  //virtual ~Log() {}
  /*
   * Synchronous API
   */
  virtual int Append(ceph::bufferlist& data, uint64_t *pposition = NULL) = 0;
  virtual int Read(uint64_t position, ceph::bufferlist& bl) = 0;
  virtual int Fill(uint64_t position) = 0;
  virtual int CheckTail(uint64_t *pposition) = 0;
  virtual int Trim(uint64_t position) = 0;

  /*
   * Asynchronous API
   */
  virtual int AioAppend(AioCompletion *c, ceph::bufferlist& data, uint64_t *pposition = NULL) = 0;
  virtual int AioRead(uint64_t position, AioCompletion *c, ceph::bufferlist *bpl) = 0;

  static AioCompletion *aio_create_completion();
  static AioCompletion *aio_create_completion(
      std::function<void()> callback);

  /*
   * Stream API
   */
  virtual int OpenStream(uint64_t stream_id, Stream **streamptr) = 0;
  virtual int MultiAppend(ceph::bufferlist& data,
      const std::set<uint64_t>& stream_ids, uint64_t *pposition = NULL) = 0;
  virtual int StreamMembership(std::set<uint64_t>& stream_ids, uint64_t position) = 0;

  virtual int kvinsert(std::string key, ceph::bufferlist& data) = 0;
  virtual int kvread(std::string key, ceph::bufferlist& bl) = 0;
  /*
   * Log Management
   */

  static int Create(librados::IoCtx& ioctx, const std::string& name,
      SeqrClient *seqr, Log **logptr);

  static int Open(librados::IoCtx& ioctx, const std::string& name,
      SeqrClient *seqr, Log **logptr);

  static int OpenOrCreate(librados::IoCtx& ioctx, const std::string& name,
      SeqrClient *seqr, Log **logptr) {
    int ret = Open(ioctx, name, seqr, logptr);
    if (ret != -ENOENT)
      return ret;
    return Create(ioctx, name, seqr, logptr);
  }

 private:
  Log(const Log&);
  void operator=(const Log&);
  //std::map<std::string, uint64_t> key_to_position_;
};


}


#endif
