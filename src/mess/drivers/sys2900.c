/***************************************************************************

    System 2900

    12/05/2009 Skeleton driver.

    The system contains 4 S100 boards, 2 8" floppies, enormous power supply,
    1/4" thick mother board, 4 RS232 I/F boards, and an Australian made
    "Computer Patch Board".
    The S100 boards that make up the unit are:
            CPU board - Model CPC2810 Rev D
                    The board has a Z80A CPU, CTC, PIO, DART and SIO.
                    U16 (24 pin) is missing (boot EPROM?).
                    It has a lot of jumpers and an 8 way DIP switch.
            Memory board - Model HDM2800 Rev B
                    This contains 18 4164's and a lot of logic.
                    Again, a lot of jumpers, and several banks of links.
                    Also contains 2 Motorola chips I cannot identify,
                    MC3480P (24 pin) and MC3242AP (28 pin).
                    (I have searched the Motorola site and the Chip
                     Directory; nothing even close.)
            Disk Controller board - Model FDC2800 Rev D
                    This board is damaged. The small voltage regulators
                    for +/- 12V have been fried.
                    Also, 3 sockets are empty - U1 and U38 (16 pin)
                    appear to be spares, and U10 (14 pin).
            8 port Serial I/O board - Model INO2808 Rev C
                    Room for 8 8251 USART's.
                    I have traced out this board and managed to get it
                    working in another S100 system.
    The "Computer Patch Board" seems to provide some sort of watch dog
    facility.

****************************************************************************/

#include "emu.h"
#include "cpu/z80/z80.h"


class sys2900_state : public driver_device
{
public:
	sys2900_state(running_machine &machine, const driver_device_config_base &config)
		: driver_device(machine, config) { }

};


static ADDRESS_MAP_START(sys2900_mem, AS_PROGRAM, 8)
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE( 0x0000, 0x07ff ) AM_RAMBANK("boot")
	AM_RANGE( 0x0800, 0xefff ) AM_RAM
	AM_RANGE( 0xf000, 0xf7ff ) AM_ROM
	AM_RANGE( 0xf800, 0xffff ) AM_RAM
ADDRESS_MAP_END

static ADDRESS_MAP_START( sys2900_io , AS_IO, 8)
	ADDRESS_MAP_UNMAP_HIGH
ADDRESS_MAP_END

/* Input ports */
static INPUT_PORTS_START( sys2900 )
INPUT_PORTS_END


/* after the first 4 bytes have been read from ROM, switch the ram back in */
static TIMER_CALLBACK( sys2900_boot )
{
	memory_set_bank(machine, "boot", 0);
}

static MACHINE_RESET(sys2900)
{
	memory_set_bank(machine, "boot", 1);
	machine.scheduler().timer_set(attotime::from_usec(5), FUNC(sys2900_boot));
}

DRIVER_INIT( sys2900 )
{
	UINT8 *RAM = machine.region("maincpu")->base();
	memory_configure_bank(machine, "boot", 0, 2, &RAM[0x0000], 0xf000);
}

static VIDEO_START( sys2900 )
{
}

static SCREEN_UPDATE( sys2900 )
{
	return 0;
}

static MACHINE_CONFIG_START( sys2900, sys2900_state )
	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu",Z80, XTAL_4MHz)
	MCFG_CPU_PROGRAM_MAP(sys2900_mem)
	MCFG_CPU_IO_MAP(sys2900_io)

	MCFG_MACHINE_RESET(sys2900)

	/* video hardware */
	MCFG_SCREEN_ADD("screen", RASTER)
	MCFG_SCREEN_REFRESH_RATE(50)
	MCFG_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(2500)) /* not accurate */
	MCFG_SCREEN_FORMAT(BITMAP_FORMAT_INDEXED16)
	MCFG_SCREEN_SIZE(640, 480)
	MCFG_SCREEN_VISIBLE_AREA(0, 640-1, 0, 480-1)
	MCFG_SCREEN_UPDATE(sys2900)

	MCFG_PALETTE_LENGTH(2)
	MCFG_PALETTE_INIT(black_and_white)

	MCFG_VIDEO_START(sys2900)
MACHINE_CONFIG_END

/* ROM definition */
ROM_START( sys2900 )
	ROM_REGION( 0x10000, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD( "104401cpc.bin", 0xf000, 0x0800, CRC(6c8848bc) SHA1(890e0578e5cb0e3433b4b173e5ed71d72a92af26))
ROM_END

/* Driver */

/*    YEAR  NAME    PARENT  COMPAT   MACHINE    INPUT    INIT    COMPANY   FULLNAME       FLAGS */
COMP( 1981, sys2900,  0,       0,    sys2900, sys2900, sys2900,  "Systems Group",   "System 2900", GAME_NOT_WORKING | GAME_NO_SOUND)

