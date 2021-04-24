#include "jdprofile.h"
#include "addons/services.h"

// Edit the string below to match your company name, the device name, and hardware revision.
// Do not change the 0x3.... value, as that would break the firmware update process.
FIRMWARE_IDENTIFIER(0x32cafbc2, "KeyStudio Light Level v1.0");

void app_init_services() {
    light_level_init(-1, PIN_X0, -1);
}
