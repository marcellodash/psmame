class rocnrope_state : public driver_device
{
public:
	rocnrope_state(running_machine &machine, const driver_device_config_base &config)
		: driver_device(machine, config) { }

	/* memory pointers */
	UINT8 *  m_videoram;
	UINT8 *  m_colorram;
	UINT8 *  m_spriteram;
	UINT8 *  m_spriteram2;
	size_t   m_spriteram_size;

	/* video-related */
	tilemap_t  *m_bg_tilemap;
};

/*----------- defined in video/rocnrope.c -----------*/

WRITE8_HANDLER( rocnrope_videoram_w );
WRITE8_HANDLER( rocnrope_colorram_w );
WRITE8_HANDLER( rocnrope_flipscreen_w );

PALETTE_INIT( rocnrope );
VIDEO_START( rocnrope );
SCREEN_UPDATE( rocnrope );
