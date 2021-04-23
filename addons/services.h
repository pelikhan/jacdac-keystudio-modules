#pragma once

#include "jd_drivers.h"
#include "services/jd_services.h"

// Soil moisture service.
// pinM is sampled, while pinL is set low, and pinH is set high.
// When not sampling, pinL and pinH are left as inputs, reducing power consumption.
// pinL and/or pinH can be -1 (it only really makes sense to use one of them).
void soil_moisture_init(uint8_t pinL, uint8_t pinM, uint8_t pinH);
