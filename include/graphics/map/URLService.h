#pragma once

#include "graphics/map/TileService.h"
#include <functional>

#ifdef ARDUINO_ARCH_ESP32
// esp_http_client.h is IDF-native and available on all ESP32 targets

class URLService : public ITileService
{
  public:
    using Callback = std::function<bool(const char *name, void *img, size_t len)>;

    URLService(Callback cb = nullptr);
    bool load(const char *name, void *img) override;
    bool loadImpl(const char *name, void *img);
    virtual ~URLService();

  private:
    Callback saveCB = nullptr;
};

#endif