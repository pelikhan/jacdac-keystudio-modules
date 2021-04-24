#include "jd_services.h"
#include "interfaces/jd_pins.h"
#include "interfaces/jd_adc.h"
#include "jacdac/dist/c/analogbutton.h"
#include "addons/services.h"

struct srv_state {
    SENSOR_COMMON;
    uint8_t inited;
    uint8_t pinH, pinL, pinM;
    uint16_t sample;
    uint32_t nextSample;
};

static void update(srv_t *state) {
    pin_setup_output(state->pinH);
    pin_set(state->pinH, 1);
    pin_setup_output(state->pinL);
    pin_set(state->pinL, 0);

    int isample = adc_read_pin(state->pinM) << 4;
    if (isample > 0xffff)
        isample = 0xffff;
    state->sample = isample;

    // save power
    pin_setup_analog_input(state->pinH);
    pin_setup_analog_input(state->pinL);
}

static void maybe_init(srv_t *state) {
    if (state->got_query && !state->inited) {
        state->inited = true;
        update(state);
    }
}

void analog_button_process(srv_t *state) {
    maybe_init(state);

    if (jd_should_sample(&state->nextSample, 9000) && state->inited)
        update(state);

    sensor_process_simple(state, &state->sample, sizeof(state->sample));
}

void analog_button_handle_packet(srv_t *state, jd_packet_t *pkt) {
    sensor_handle_packet_simple(state, pkt, &state->sample, sizeof(state->sample));
}

SRV_DEF(analog_button, JD_SERVICE_CLASS_ANALOG_BUTTON);

void analog_button_init(uint8_t pinL, uint8_t pinM, uint8_t pinH) {
    SRV_ALLOC(analog_button);
    state->pinL = pinL;
    state->pinM = pinM;
    state->pinH = pinH;
}
