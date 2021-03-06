#pragma once

#ifndef __PHC25__
#define __PHC25__

#define ADDRESS_MAP_MODERN

#include "emu.h"
#include "cpu/z80/z80.h"
#include "imagedev/cassette.h"
#include "machine/ram.h"
#include "machine/ctronics.h"
#include "video/m6847.h"
#include "sound/ay8910.h"

#define SCREEN_TAG		"screen"
#define Z80_TAG			"z80"
#define AY8910_TAG		"ay8910"
#define MC6847_TAG		"mc6847"
#define CASSETTE_TAG	"cassette"
#define CENTRONICS_TAG	"centronics"

#define PHC25_VIDEORAM_SIZE		0x1800

class phc25_state : public driver_device
{
public:
	phc25_state(running_machine &machine, const driver_device_config_base &config)
		: driver_device(machine, config),
		  m_maincpu(*this, Z80_TAG),
		  m_vdg(*this, MC6847_TAG),
		  m_centronics(*this, CENTRONICS_TAG),
		  m_cassette(*this, CASSETTE_TAG)
	{ }

	required_device<cpu_device> m_maincpu;
	required_device<device_t> m_vdg;
	required_device<device_t> m_centronics;
	required_device<device_t> m_cassette;

	virtual void video_start();
	virtual bool screen_update(screen_device &screen, bitmap_t &bitmap, const rectangle &cliprect);

	DECLARE_READ8_MEMBER( port40_r );
	DECLARE_WRITE8_MEMBER( port40_w );
	DECLARE_READ8_MEMBER( video_ram_r );

	/* video state */
	UINT8 *m_video_ram;
	UINT8 *m_char_rom;
};

#endif
