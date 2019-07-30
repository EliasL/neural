/*
 * Code generated from START.
 *
 * This file will be overwritten when reconfiguring your START project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <port.h>

/**
 * \brief Set PA1 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PA1_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTA_set_pin_pull_mode(1, pull_mode);
}

/**
 * \brief Set PA1 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PA1_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(1, dir);
}

/**
 * \brief Set PA1 input/sense configuration
 *
 * Enable/disable PA1 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PA1_set_isc(const PORT_ISC_t isc)
{
	PORTA_pin_set_isc(1, isc);
}

/**
 * \brief Set PA1 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PA1 is inverted
 *                     false = I/O on PA1 is not inverted
 */
static inline void PA1_set_inverted(const bool inverted)
{
	PORTA_pin_set_inverted(1, inverted);
}

/**
 * \brief Set PA1 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PA1_set_level(const bool level)
{
	PORTA_set_pin_level(1, level);
}

/**
 * \brief Toggle output level on PA1
 *
 * Toggle the pin level
 */
static inline void PA1_toggle_level()
{
	PORTA_toggle_pin_level(1);
}

/**
 * \brief Get level on PA1
 *
 * Reads the level on a pin
 */
static inline bool PA1_get_level()
{
	return PORTA_get_pin_level(1);
}

/**
 * \brief Set PA2 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PA2_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTA_set_pin_pull_mode(2, pull_mode);
}

/**
 * \brief Set PA2 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PA2_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(2, dir);
}

/**
 * \brief Set PA2 input/sense configuration
 *
 * Enable/disable PA2 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PA2_set_isc(const PORT_ISC_t isc)
{
	PORTA_pin_set_isc(2, isc);
}

/**
 * \brief Set PA2 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PA2 is inverted
 *                     false = I/O on PA2 is not inverted
 */
static inline void PA2_set_inverted(const bool inverted)
{
	PORTA_pin_set_inverted(2, inverted);
}

/**
 * \brief Set PA2 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PA2_set_level(const bool level)
{
	PORTA_set_pin_level(2, level);
}

/**
 * \brief Toggle output level on PA2
 *
 * Toggle the pin level
 */
static inline void PA2_toggle_level()
{
	PORTA_toggle_pin_level(2);
}

/**
 * \brief Get level on PA2
 *
 * Reads the level on a pin
 */
static inline bool PA2_get_level()
{
	return PORTA_get_pin_level(2);
}

/**
 * \brief Set PA3 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PA3_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTA_set_pin_pull_mode(3, pull_mode);
}

/**
 * \brief Set PA3 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PA3_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(3, dir);
}

/**
 * \brief Set PA3 input/sense configuration
 *
 * Enable/disable PA3 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PA3_set_isc(const PORT_ISC_t isc)
{
	PORTA_pin_set_isc(3, isc);
}

/**
 * \brief Set PA3 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PA3 is inverted
 *                     false = I/O on PA3 is not inverted
 */
static inline void PA3_set_inverted(const bool inverted)
{
	PORTA_pin_set_inverted(3, inverted);
}

/**
 * \brief Set PA3 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PA3_set_level(const bool level)
{
	PORTA_set_pin_level(3, level);
}

/**
 * \brief Toggle output level on PA3
 *
 * Toggle the pin level
 */
static inline void PA3_toggle_level()
{
	PORTA_toggle_pin_level(3);
}

/**
 * \brief Get level on PA3
 *
 * Reads the level on a pin
 */
static inline bool PA3_get_level()
{
	return PORTA_get_pin_level(3);
}

/**
 * \brief Set PA4 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PA4_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTA_set_pin_pull_mode(4, pull_mode);
}

/**
 * \brief Set PA4 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PA4_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(4, dir);
}

/**
 * \brief Set PA4 input/sense configuration
 *
 * Enable/disable PA4 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PA4_set_isc(const PORT_ISC_t isc)
{
	PORTA_pin_set_isc(4, isc);
}

/**
 * \brief Set PA4 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PA4 is inverted
 *                     false = I/O on PA4 is not inverted
 */
static inline void PA4_set_inverted(const bool inverted)
{
	PORTA_pin_set_inverted(4, inverted);
}

/**
 * \brief Set PA4 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PA4_set_level(const bool level)
{
	PORTA_set_pin_level(4, level);
}

/**
 * \brief Toggle output level on PA4
 *
 * Toggle the pin level
 */
static inline void PA4_toggle_level()
{
	PORTA_toggle_pin_level(4);
}

/**
 * \brief Get level on PA4
 *
 * Reads the level on a pin
 */
static inline bool PA4_get_level()
{
	return PORTA_get_pin_level(4);
}

/**
 * \brief Set DEN2_PIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void DEN2_PIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTA_set_pin_pull_mode(5, pull_mode);
}

/**
 * \brief Set DEN2_PIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void DEN2_PIN_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(5, dir);
}

/**
 * \brief Set DEN2_PIN input/sense configuration
 *
 * Enable/disable DEN2_PIN digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void DEN2_PIN_set_isc(const PORT_ISC_t isc)
{
	PORTA_pin_set_isc(5, isc);
}

/**
 * \brief Set DEN2_PIN inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on DEN2_PIN is inverted
 *                     false = I/O on DEN2_PIN is not inverted
 */
static inline void DEN2_PIN_set_inverted(const bool inverted)
{
	PORTA_pin_set_inverted(5, inverted);
}

/**
 * \brief Set DEN2_PIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void DEN2_PIN_set_level(const bool level)
{
	PORTA_set_pin_level(5, level);
}

/**
 * \brief Toggle output level on DEN2_PIN
 *
 * Toggle the pin level
 */
static inline void DEN2_PIN_toggle_level()
{
	PORTA_toggle_pin_level(5);
}

/**
 * \brief Get level on DEN2_PIN
 *
 * Reads the level on a pin
 */
static inline bool DEN2_PIN_get_level()
{
	return PORTA_get_pin_level(5);
}

/**
 * \brief Set AXON_PIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void AXON_PIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTA_set_pin_pull_mode(6, pull_mode);
}

/**
 * \brief Set AXON_PIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void AXON_PIN_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(6, dir);
}

/**
 * \brief Set AXON_PIN input/sense configuration
 *
 * Enable/disable AXON_PIN digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void AXON_PIN_set_isc(const PORT_ISC_t isc)
{
	PORTA_pin_set_isc(6, isc);
}

/**
 * \brief Set AXON_PIN inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on AXON_PIN is inverted
 *                     false = I/O on AXON_PIN is not inverted
 */
static inline void AXON_PIN_set_inverted(const bool inverted)
{
	PORTA_pin_set_inverted(6, inverted);
}

/**
 * \brief Set AXON_PIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void AXON_PIN_set_level(const bool level)
{
	PORTA_set_pin_level(6, level);
}

/**
 * \brief Toggle output level on AXON_PIN
 *
 * Toggle the pin level
 */
static inline void AXON_PIN_toggle_level()
{
	PORTA_toggle_pin_level(6);
}

/**
 * \brief Get level on AXON_PIN
 *
 * Reads the level on a pin
 */
static inline bool AXON_PIN_get_level()
{
	return PORTA_get_pin_level(6);
}

/**
 * \brief Set DEN1_PIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void DEN1_PIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTA_set_pin_pull_mode(7, pull_mode);
}

/**
 * \brief Set DEN1_PIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void DEN1_PIN_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(7, dir);
}

/**
 * \brief Set DEN1_PIN input/sense configuration
 *
 * Enable/disable DEN1_PIN digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void DEN1_PIN_set_isc(const PORT_ISC_t isc)
{
	PORTA_pin_set_isc(7, isc);
}

/**
 * \brief Set DEN1_PIN inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on DEN1_PIN is inverted
 *                     false = I/O on DEN1_PIN is not inverted
 */
static inline void DEN1_PIN_set_inverted(const bool inverted)
{
	PORTA_pin_set_inverted(7, inverted);
}

/**
 * \brief Set DEN1_PIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void DEN1_PIN_set_level(const bool level)
{
	PORTA_set_pin_level(7, level);
}

/**
 * \brief Toggle output level on DEN1_PIN
 *
 * Toggle the pin level
 */
static inline void DEN1_PIN_toggle_level()
{
	PORTA_toggle_pin_level(7);
}

/**
 * \brief Get level on DEN1_PIN
 *
 * Reads the level on a pin
 */
static inline bool DEN1_PIN_get_level()
{
	return PORTA_get_pin_level(7);
}

/**
 * \brief Set PB2 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PB2_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(2, pull_mode);
}

/**
 * \brief Set PB2 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PB2_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(2, dir);
}

/**
 * \brief Set PB2 input/sense configuration
 *
 * Enable/disable PB2 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PB2_set_isc(const PORT_ISC_t isc)
{
	PORTB_pin_set_isc(2, isc);
}

/**
 * \brief Set PB2 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PB2 is inverted
 *                     false = I/O on PB2 is not inverted
 */
static inline void PB2_set_inverted(const bool inverted)
{
	PORTB_pin_set_inverted(2, inverted);
}

/**
 * \brief Set PB2 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PB2_set_level(const bool level)
{
	PORTB_set_pin_level(2, level);
}

/**
 * \brief Toggle output level on PB2
 *
 * Toggle the pin level
 */
static inline void PB2_toggle_level()
{
	PORTB_toggle_pin_level(2);
}

/**
 * \brief Get level on PB2
 *
 * Reads the level on a pin
 */
static inline bool PB2_get_level()
{
	return PORTB_get_pin_level(2);
}

/**
 * \brief Set PB3 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PB3_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(3, pull_mode);
}

/**
 * \brief Set PB3 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PB3_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(3, dir);
}

/**
 * \brief Set PB3 input/sense configuration
 *
 * Enable/disable PB3 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PB3_set_isc(const PORT_ISC_t isc)
{
	PORTB_pin_set_isc(3, isc);
}

/**
 * \brief Set PB3 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PB3 is inverted
 *                     false = I/O on PB3 is not inverted
 */
static inline void PB3_set_inverted(const bool inverted)
{
	PORTB_pin_set_inverted(3, inverted);
}

/**
 * \brief Set PB3 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PB3_set_level(const bool level)
{
	PORTB_set_pin_level(3, level);
}

/**
 * \brief Toggle output level on PB3
 *
 * Toggle the pin level
 */
static inline void PB3_toggle_level()
{
	PORTB_toggle_pin_level(3);
}

/**
 * \brief Get level on PB3
 *
 * Reads the level on a pin
 */
static inline bool PB3_get_level()
{
	return PORTB_get_pin_level(3);
}

/**
 * \brief Set LED_PIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void LED_PIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(4, pull_mode);
}

/**
 * \brief Set LED_PIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void LED_PIN_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(4, dir);
}

/**
 * \brief Set LED_PIN input/sense configuration
 *
 * Enable/disable LED_PIN digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void LED_PIN_set_isc(const PORT_ISC_t isc)
{
	PORTB_pin_set_isc(4, isc);
}

/**
 * \brief Set LED_PIN inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on LED_PIN is inverted
 *                     false = I/O on LED_PIN is not inverted
 */
static inline void LED_PIN_set_inverted(const bool inverted)
{
	PORTB_pin_set_inverted(4, inverted);
}

/**
 * \brief Set LED_PIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void LED_PIN_set_level(const bool level)
{
	PORTB_set_pin_level(4, level);
}

/**
 * \brief Toggle output level on LED_PIN
 *
 * Toggle the pin level
 */
static inline void LED_PIN_toggle_level()
{
	PORTB_toggle_pin_level(4);
}

/**
 * \brief Get level on LED_PIN
 *
 * Reads the level on a pin
 */
static inline bool LED_PIN_get_level()
{
	return PORTB_get_pin_level(4);
}

/**
 * \brief Set PB5 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PB5_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(5, pull_mode);
}

/**
 * \brief Set PB5 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PB5_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(5, dir);
}

/**
 * \brief Set PB5 input/sense configuration
 *
 * Enable/disable PB5 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PB5_set_isc(const PORT_ISC_t isc)
{
	PORTB_pin_set_isc(5, isc);
}

/**
 * \brief Set PB5 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PB5 is inverted
 *                     false = I/O on PB5 is not inverted
 */
static inline void PB5_set_inverted(const bool inverted)
{
	PORTB_pin_set_inverted(5, inverted);
}

/**
 * \brief Set PB5 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PB5_set_level(const bool level)
{
	PORTB_set_pin_level(5, level);
}

/**
 * \brief Toggle output level on PB5
 *
 * Toggle the pin level
 */
static inline void PB5_toggle_level()
{
	PORTB_toggle_pin_level(5);
}

/**
 * \brief Get level on PB5
 *
 * Reads the level on a pin
 */
static inline bool PB5_get_level()
{
	return PORTB_get_pin_level(5);
}

/**
 * \brief Set CHARGING_STATUS_PIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void CHARGING_STATUS_PIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(6, pull_mode);
}

/**
 * \brief Set CHARGING_STATUS_PIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void CHARGING_STATUS_PIN_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(6, dir);
}

/**
 * \brief Set CHARGING_STATUS_PIN input/sense configuration
 *
 * Enable/disable CHARGING_STATUS_PIN digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void CHARGING_STATUS_PIN_set_isc(const PORT_ISC_t isc)
{
	PORTB_pin_set_isc(6, isc);
}

/**
 * \brief Set CHARGING_STATUS_PIN inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on CHARGING_STATUS_PIN is inverted
 *                     false = I/O on CHARGING_STATUS_PIN is not inverted
 */
static inline void CHARGING_STATUS_PIN_set_inverted(const bool inverted)
{
	PORTB_pin_set_inverted(6, inverted);
}

/**
 * \brief Set CHARGING_STATUS_PIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void CHARGING_STATUS_PIN_set_level(const bool level)
{
	PORTB_set_pin_level(6, level);
}

/**
 * \brief Toggle output level on CHARGING_STATUS_PIN
 *
 * Toggle the pin level
 */
static inline void CHARGING_STATUS_PIN_toggle_level()
{
	PORTB_toggle_pin_level(6);
}

/**
 * \brief Get level on CHARGING_STATUS_PIN
 *
 * Reads the level on a pin
 */
static inline bool CHARGING_STATUS_PIN_get_level()
{
	return PORTB_get_pin_level(6);
}

/**
 * \brief Set AXON_CHECK_PIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void AXON_CHECK_PIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(7, pull_mode);
}

/**
 * \brief Set AXON_CHECK_PIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void AXON_CHECK_PIN_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(7, dir);
}

/**
 * \brief Set AXON_CHECK_PIN input/sense configuration
 *
 * Enable/disable AXON_CHECK_PIN digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void AXON_CHECK_PIN_set_isc(const PORT_ISC_t isc)
{
	PORTB_pin_set_isc(7, isc);
}

/**
 * \brief Set AXON_CHECK_PIN inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on AXON_CHECK_PIN is inverted
 *                     false = I/O on AXON_CHECK_PIN is not inverted
 */
static inline void AXON_CHECK_PIN_set_inverted(const bool inverted)
{
	PORTB_pin_set_inverted(7, inverted);
}

/**
 * \brief Set AXON_CHECK_PIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void AXON_CHECK_PIN_set_level(const bool level)
{
	PORTB_set_pin_level(7, level);
}

/**
 * \brief Toggle output level on AXON_CHECK_PIN
 *
 * Toggle the pin level
 */
static inline void AXON_CHECK_PIN_toggle_level()
{
	PORTB_toggle_pin_level(7);
}

/**
 * \brief Get level on AXON_CHECK_PIN
 *
 * Reads the level on a pin
 */
static inline bool AXON_CHECK_PIN_get_level()
{
	return PORTB_get_pin_level(7);
}

/**
 * \brief Set DEN3_PIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void DEN3_PIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(0, pull_mode);
}

/**
 * \brief Set DEN3_PIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void DEN3_PIN_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(0, dir);
}

/**
 * \brief Set DEN3_PIN input/sense configuration
 *
 * Enable/disable DEN3_PIN digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void DEN3_PIN_set_isc(const PORT_ISC_t isc)
{
	PORTC_pin_set_isc(0, isc);
}

/**
 * \brief Set DEN3_PIN inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on DEN3_PIN is inverted
 *                     false = I/O on DEN3_PIN is not inverted
 */
static inline void DEN3_PIN_set_inverted(const bool inverted)
{
	PORTC_pin_set_inverted(0, inverted);
}

/**
 * \brief Set DEN3_PIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void DEN3_PIN_set_level(const bool level)
{
	PORTC_set_pin_level(0, level);
}

/**
 * \brief Toggle output level on DEN3_PIN
 *
 * Toggle the pin level
 */
static inline void DEN3_PIN_toggle_level()
{
	PORTC_toggle_pin_level(0);
}

/**
 * \brief Get level on DEN3_PIN
 *
 * Reads the level on a pin
 */
static inline bool DEN3_PIN_get_level()
{
	return PORTC_get_pin_level(0);
}

/**
 * \brief Set DEN5_PIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void DEN5_PIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(1, pull_mode);
}

/**
 * \brief Set DEN5_PIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void DEN5_PIN_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(1, dir);
}

/**
 * \brief Set DEN5_PIN input/sense configuration
 *
 * Enable/disable DEN5_PIN digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void DEN5_PIN_set_isc(const PORT_ISC_t isc)
{
	PORTC_pin_set_isc(1, isc);
}

/**
 * \brief Set DEN5_PIN inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on DEN5_PIN is inverted
 *                     false = I/O on DEN5_PIN is not inverted
 */
static inline void DEN5_PIN_set_inverted(const bool inverted)
{
	PORTC_pin_set_inverted(1, inverted);
}

/**
 * \brief Set DEN5_PIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void DEN5_PIN_set_level(const bool level)
{
	PORTC_set_pin_level(1, level);
}

/**
 * \brief Toggle output level on DEN5_PIN
 *
 * Toggle the pin level
 */
static inline void DEN5_PIN_toggle_level()
{
	PORTC_toggle_pin_level(1);
}

/**
 * \brief Get level on DEN5_PIN
 *
 * Reads the level on a pin
 */
static inline bool DEN5_PIN_get_level()
{
	return PORTC_get_pin_level(1);
}

/**
 * \brief Set BUTTON_PIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void BUTTON_PIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(2, pull_mode);
}

/**
 * \brief Set BUTTON_PIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void BUTTON_PIN_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(2, dir);
}

/**
 * \brief Set BUTTON_PIN input/sense configuration
 *
 * Enable/disable BUTTON_PIN digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void BUTTON_PIN_set_isc(const PORT_ISC_t isc)
{
	PORTC_pin_set_isc(2, isc);
}

/**
 * \brief Set BUTTON_PIN inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on BUTTON_PIN is inverted
 *                     false = I/O on BUTTON_PIN is not inverted
 */
static inline void BUTTON_PIN_set_inverted(const bool inverted)
{
	PORTC_pin_set_inverted(2, inverted);
}

/**
 * \brief Set BUTTON_PIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void BUTTON_PIN_set_level(const bool level)
{
	PORTC_set_pin_level(2, level);
}

/**
 * \brief Toggle output level on BUTTON_PIN
 *
 * Toggle the pin level
 */
static inline void BUTTON_PIN_toggle_level()
{
	PORTC_toggle_pin_level(2);
}

/**
 * \brief Get level on BUTTON_PIN
 *
 * Reads the level on a pin
 */
static inline bool BUTTON_PIN_get_level()
{
	return PORTC_get_pin_level(2);
}

/**
 * \brief Set DEN4_PIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void DEN4_PIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(3, pull_mode);
}

/**
 * \brief Set DEN4_PIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void DEN4_PIN_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(3, dir);
}

/**
 * \brief Set DEN4_PIN input/sense configuration
 *
 * Enable/disable DEN4_PIN digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void DEN4_PIN_set_isc(const PORT_ISC_t isc)
{
	PORTC_pin_set_isc(3, isc);
}

/**
 * \brief Set DEN4_PIN inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on DEN4_PIN is inverted
 *                     false = I/O on DEN4_PIN is not inverted
 */
static inline void DEN4_PIN_set_inverted(const bool inverted)
{
	PORTC_pin_set_inverted(3, inverted);
}

/**
 * \brief Set DEN4_PIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void DEN4_PIN_set_level(const bool level)
{
	PORTC_set_pin_level(3, level);
}

/**
 * \brief Toggle output level on DEN4_PIN
 *
 * Toggle the pin level
 */
static inline void DEN4_PIN_toggle_level()
{
	PORTC_toggle_pin_level(3);
}

/**
 * \brief Get level on DEN4_PIN
 *
 * Reads the level on a pin
 */
static inline bool DEN4_PIN_get_level()
{
	return PORTC_get_pin_level(3);
}

/**
 * \brief Set CHARGING_SWITCHES_PIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void CHARGING_SWITCHES_PIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(5, pull_mode);
}

/**
 * \brief Set CHARGING_SWITCHES_PIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void CHARGING_SWITCHES_PIN_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(5, dir);
}

/**
 * \brief Set CHARGING_SWITCHES_PIN input/sense configuration
 *
 * Enable/disable CHARGING_SWITCHES_PIN digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void CHARGING_SWITCHES_PIN_set_isc(const PORT_ISC_t isc)
{
	PORTC_pin_set_isc(5, isc);
}

/**
 * \brief Set CHARGING_SWITCHES_PIN inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on CHARGING_SWITCHES_PIN is inverted
 *                     false = I/O on CHARGING_SWITCHES_PIN is not inverted
 */
static inline void CHARGING_SWITCHES_PIN_set_inverted(const bool inverted)
{
	PORTC_pin_set_inverted(5, inverted);
}

/**
 * \brief Set CHARGING_SWITCHES_PIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void CHARGING_SWITCHES_PIN_set_level(const bool level)
{
	PORTC_set_pin_level(5, level);
}

/**
 * \brief Toggle output level on CHARGING_SWITCHES_PIN
 *
 * Toggle the pin level
 */
static inline void CHARGING_SWITCHES_PIN_toggle_level()
{
	PORTC_toggle_pin_level(5);
}

/**
 * \brief Get level on CHARGING_SWITCHES_PIN
 *
 * Reads the level on a pin
 */
static inline bool CHARGING_SWITCHES_PIN_get_level()
{
	return PORTC_get_pin_level(5);
}

#endif /* ATMEL_START_PINS_H_INCLUDED */
