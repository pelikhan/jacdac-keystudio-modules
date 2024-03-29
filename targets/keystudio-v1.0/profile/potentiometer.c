#include "jdprofile.h"
#include "jd_drivers.h"
#include "services/jd_services.h"

// Edit the string below to match your company name, the device name, and hardware revision.
// Do not change the 0x3.... value, as that would break the firmware update process.
FIRMWARE_IDENTIFIER(0x3bdb5f6e, "KeyStudio KS0361 Potentiometer v1.0");

void app_init_services() {
    potentiometer_init(-1, PIN_X0, -1);
}
