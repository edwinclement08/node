#include "node_internals.h"
#include "string_bytes.h"

#include <array>
#include <errno.h>
#include <string.h>

#ifdef __MINGW32__
# include <io.h>
#endif  // __MINGW32__

#ifdef __POSIX__
# include <limits.h>        // PATH_MAX on Solaris.
# include <netdb.h>         // MAXHOSTNAMELEN on Solaris.
# include <unistd.h>        // gethostname, sysconf
# include <sys/param.h>     // MAXHOSTNAMELEN on Linux and the BSDs.
# include <sys/utsname.h>
#endif  // __POSIX__


namespace node {
namespace keytar {

using v8::Array;
using v8::ArrayBuffer;
using v8::Boolean;
using v8::Context;
using v8::Float64Array;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Int32;
using v8::Integer;
using v8::Local;
using v8::MaybeLocal;
using v8::Null;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

static void GetFreeMemory(const FunctionCallbackInfo<Value>& args) {
  double amount = uv_get_free_memory();
  if (amount < 0)
    return;
  args.GetReturnValue().Set(amount);
}

void Initialize(Local<Object> target,
                Local<Value> unused,
                Local<Context> context) {
  Environment* env = Environment::GetCurrent(context);
  env->SetMethod(target, "getFreeMem", GetFreeMemory);
  target->Set(FIXED_ONE_BYTE_STRING(env->isolate(), "isBigEndian"),
              Boolean::New(env->isolate(), IsBigEndian()));
}

}  // namespace keytar
}  // namespace node

NODE_BUILTIN_MODULE_CONTEXT_AWARE(keytar, node::keytar::Initialize)
