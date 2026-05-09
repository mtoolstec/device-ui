#include "graphics/map/URLService.h"
#include <WiFi.h>
#include "graphics/map/MapTileSettings.h"
#include "graphics/map/TileProvider.h"
#include "lvgl.h"
#include "util/ILog.h"

#ifdef ARDUINO_ARCH_ESP32

// from ConvertPNG.c
extern "C" {
bool decodeImgGrey(const void *data, size_t size, lv_img_dsc_t **img);
bool decodeImgColor(const void *data, size_t size, lv_img_dsc_t **img);
}

URLService::URLService(Callback cb) : ITileService("HTTP:"), saveCB(cb) {}

URLService::~URLService() {}

bool URLService::load(const char *name, void *img)
{
    return loadImpl(name, img);
}

bool URLService::loadImpl(const char *name, void *img)
{
    std::string url = TileProvider::url(name);
    ILOG_DEBUG("URLService: no network available on ESP32-P4, tile skipped: %s", url.c_str());
    // On ESP32-P4, networking is handled by the C6 coprocessor; direct HTTP is not
    // available. Return false so the map shows the no-tile placeholder.
    return false;
}

#endif
