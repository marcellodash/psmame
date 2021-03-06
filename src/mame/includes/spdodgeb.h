class spdodgeb_state : public driver_device
{
public:
	spdodgeb_state(running_machine &machine, const driver_device_config_base &config)
		: driver_device(machine, config) { }

	int m_toggle;
	int m_adpcm_pos[2];
	int m_adpcm_end[2];
	int m_adpcm_idle[2];
	int m_adpcm_data[2];
	int m_mcu63701_command;
	int m_inputs[4];
	UINT8 m_tapc[4];
	UINT8 m_last_port[2];
	UINT8 m_last_dash[2];
#if 0
	int m_running[2];
	int m_jumped[2];
	int m_prev[2][2];
	int m_countup[2][2];
	int m_countdown[2][2];
	int m_prev[2];
#endif
	UINT8 *m_videoram;
	int m_tile_palbank;
	int m_sprite_palbank;
	tilemap_t *m_bg_tilemap;
	int m_lastscroll;
	UINT8 *m_spriteram;
	size_t m_spriteram_size;
};


/*----------- defined in video/spdodgeb.c -----------*/

PALETTE_INIT( spdodgeb );
VIDEO_START( spdodgeb );
SCREEN_UPDATE( spdodgeb );
INTERRUPT_GEN( spdodgeb_interrupt );
WRITE8_HANDLER( spdodgeb_scrollx_lo_w );
WRITE8_HANDLER( spdodgeb_ctrl_w );
WRITE8_HANDLER( spdodgeb_videoram_w );
