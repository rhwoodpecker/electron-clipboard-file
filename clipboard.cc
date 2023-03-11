#include <napi.h>
#include <iostream>
#include <string>
#include <cstdlib>

#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

Napi::Value CopyFileToClipboard(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() != 1 || !info[0].IsString())
    {
        Napi::TypeError::New(env, "Expected a file path string").ThrowAsJavaScriptException();
        return env.Null();
    }

    // 获取文件路径
    std::string filePath = info[0].As<Napi::String>().Utf8Value();

    // 将文件路径转换成 CFURL
    CFURLRef url = CFURLCreateFromFileSystemRepresentation(kCFAllocatorDefault, (const UInt8 *)filePath.c_str(), filePath.size(), false);
    if (url == NULL)
    {
        Napi::TypeError::New(env, "Unable to create CFURL").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    // 将 CFURL 转换成 CFData
    CFDataRef urlData = CFURLCreateData(kCFAllocatorDefault, url, kCFStringEncodingUTF8, false);
    if (urlData == NULL)
    {
        CFRelease(url);
        Napi::TypeError::New(env, "Unable to create CFData").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    // 获取剪贴板
    PasteboardRef pasteboard;
    OSStatus result = PasteboardCreate(kPasteboardClipboard, &pasteboard);
    if (result != noErr)
    {
        CFRelease(url);
        CFRelease(urlData);
        Napi::TypeError::New(env, "Unable to create pasteboard").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    // 清空剪贴板
    PasteboardClear(pasteboard);

    // 将文件内容添加到剪贴板
    result = PasteboardPutItemFlavor(pasteboard, (PasteboardItemID)1, CFSTR("public.file-url"), urlData, 0);
    if (result != noErr)
    {
        CFRelease(url);
        CFRelease(urlData);
        Napi::TypeError::New(env, "Unable to put file on pasteboard").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    // 释放资源
    CFRelease(url);
    CFRelease(urlData);
    PasteboardSynchronize(pasteboard);

    return env.Undefined();
}

// 初始化 addon
Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "copyFileToClipboard"), Napi::Function::New(env, CopyFileToClipboard));
    return exports;
}

// 声明 addon
NODE_API_MODULE(addon, Init)