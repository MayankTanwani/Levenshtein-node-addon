#include <napi.h>
#include <string.h>
#include <vector>
Napi::Value editDistance(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  // if (info.Length() < 2) {
  //   Napi::TypeError::New(env, "Wrong number of arguments")
  //       .ThrowAsJavaScriptException();
  //   return env.Null();
  // }

  // if (!info[0].IsNumber() || !info[1].IsNumber()) {
  //   Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
  //   return env.Null();
  // }

  std::string x = info[0].As<Napi::String>().Utf8Value();
  std::string y = info[1].As<Napi::String>().Utf8Value();

  int n = x.length();
  int m = y.length();
  std::vector<int> prev(m+1,-1);
  for(int i = 0;i<=n;i++){
      std::vector<int> curr(m+1, -1);
      for(int j = 0;j<=m;j++){
          if(std::min(i,j) == 0) 
              curr[j] = std::max(i,j);
          else if(x[i-1] == y[j-1])
              curr[j] = prev[j-1];
          else
              curr[j] = 1 + std::min(curr[j-1],std::min(prev[j],prev[j-1]));
      }
      prev = curr;
  }
  Napi::Number num = Napi::Number::New(env, prev[m]);
  return num;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "editDistance"), Napi::Function::New(env, editDistance));
  return exports;
}

NODE_API_MODULE(addon, Init)
